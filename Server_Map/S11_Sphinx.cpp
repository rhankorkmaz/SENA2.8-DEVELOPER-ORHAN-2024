#include <cassert>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "Shengming.h"

CSphinx mSphinx;
CSphinx::CSphinx() : m_bReady( 0 )
{}
CSphinx::~CSphinx()
{
	ToSleep_Sphinx();
}

BOOL CSphinx::WakeUp_Sphinx()
{
	m_bReady=0;

	char tTemp_String[ 128 ] = "";

	for(int i=0; i<MAX_PUZZLE_NUM; ++i)
	{
		sprintf( tTemp_String, "DATA/001_040%d.TGA", 38 + i );
		if(0 == m_Img_Data[i].Load(tTemp_String))
		{
			__LogMgr()->Log("Error -- IMG Load Failed!", __FUNCTION__);
			return 0;
		}
	}

	m_bReady=1;
	return 1;
}


void CSphinx::ToSleep_Sphinx( void )
{
	m_bReady=0;
}

BOOL CSphinx::Get_Transform_Num(BYTE out[], int index)const
{
	if(!m_bReady || !out)
	{
		//assert(!"!m_bReady || !out");
		return 0;
	}

	if(index<0 || index>=MAX_PUZZLE_NUM || 0==m_Img_Data[index].IsReady())
	{
		//assert(!"index<0 || index>=MAX_PUZZLE_NUM || 0==m_Img_Data[index].IsReady()");
		return 0;
	}

	//header
	TGA_HEADER const * hdr = m_Img_Data[index].Get_Header();
	memcpy(out, hdr, sizeof(TGA_HEADER));

	//image data
	BYTE const * img_buffer = m_Img_Data[index].Get_Img_Buffer();
	if(0 == Transform_Manager(out + sizeof(TGA_HEADER), img_buffer, hdr))
	{
		//assert(!"Transform_Manager failed");
		return 0;
	}

	//footer
	BYTE const * footer = m_Img_Data[index].Get_Footer();
	memcpy(out+sizeof(TGA_HEADER)+tga_image::PIXEL_DATA_SIZE, footer, tga_image::FOOTER_SIZE);

	return 1;
}

BOOL CSphinx::Transform_Manager(BYTE out[], BYTE const in[], TGA_HEADER const * hdr)const
{
	const int BPP = 32;
	const int FILTER_CASE = 6;	//토네이도, 볼록이 제거.
	int fillter_type = rand() % FILTER_CASE;
	//static int cnt = 0;
	//if(cnt % 5 == 0)
	//{
	//	LOG_TO_FILE_1("!== ================ %d\n", cnt);
	//}
	//++cnt;
	//LOG_TO_FILE_1("!== fillter_type = %d\n", fillter_type);
	switch(fillter_type)
	{
	case 0:
		{
			CSphinxAlgorithm<BPP> const & filter = CBILATERAL_SYMMETRY<BPP>();
			filter.Transform_Data(out, in, hdr);
		}break;
	case 1:
		{
			CSphinxAlgorithm<BPP> const & filter = CDOTSCREEN_BACKGROUND<BPP>();
			filter.Transform_Data(out, in, hdr);
		}break;
	case 2:
		{
			CSphinxAlgorithm<BPP> const & filter = SINE_WAVE<BPP>(3.f, 2.24f);
			filter.Transform_Data(out, in, hdr);
		}break;
	case 3:
		{
			CSphinxAlgorithm<BPP> const & filter = CONCAVE_LENS<BPP>();
			filter.Transform_Data(out, in, hdr);
		}break;
	case 4:
		{
			CSphinxAlgorithm<BPP> const & filter = V_SHIFT<BPP>(2);
			filter.Transform_Data(out, in, hdr);
		}break;
	case 5:
		{
			CSphinxAlgorithm<BPP> const & filter = H_SHIFT<BPP>(2);
			filter.Transform_Data(out, in, hdr);
		}break;
	case 6:
		{
			CSphinxAlgorithm<BPP> const & filter = TONADO<BPP>();
			filter.Transform_Data(out, in, hdr);
		}break;
	case 7:
		{
			CSphinxAlgorithm<BPP> const & filter = CONVEX_LENS<BPP>();
			filter.Transform_Data(out, in, hdr);
		}break;
	}
	return 1;
}
