

#ifndef H012_SPHINX_H
#define H012_SPHINX_H


/*#include "win2unix.h"*/


#ifdef _DEBUG	//for compile time assert
#define COMPILETIME_ASSERT(chkname, exp)	char chkname[(exp) ? 1 : -1]
#else 
#define COMPILETIME_ASSERT(chkname, exp)
#endif	//_DEBUG

const int MAX_PUZZLE_NUM	= 10;
const int MAX_OUTPUT_IMG	= 5;


#pragma pack(push, pack_for_TGA_HEADER, 1)
typedef struct tagTGA_HEADER{
	char  idlength;
	char  colourmaptype;
	char  datatypecode;
	short int colourmaporigin;
	short int colourmaplength;
	char  colourmapdepth;
	short int x_origin;
	short int y_origin;
	short width;
	short height;
	char  bitsperpixel;
	char  imagedescriptor;
} TGA_HEADER;
#pragma pack(pop, pack_for_TGA_HEADER)


template<int WIDTH, int HEIGHT, int BITS_PER_PIXEL>
struct TGA_IMAGE
{
	enum {	eWidth=WIDTH, eHeight=HEIGHT, eBPP=BITS_PER_PIXEL,};
	enum {	IMG_FILE_SIZE_FOR_AUTO_QUIZE = 4140,	///< 18 + 32*32*4 + 26
			FOOTER_SIZE = 26,
			PIXEL_DATA_SIZE = WIDTH * HEIGHT * (BITS_PER_PIXEL/8),
			BUFF_SIZE = sizeof(TGA_HEADER) + PIXEL_DATA_SIZE + FOOTER_SIZE,};
private:
	BYTE m_bImgData[ BUFF_SIZE ];
	BOOL m_bReady;

	COMPILETIME_ASSERT(header_size_must_be_18bytes, sizeof(TGA_HEADER) == 18 );
	COMPILETIME_ASSERT(bitsperpixel_must_be_8_16_24_32, BITS_PER_PIXEL/8 == 1 || BITS_PER_PIXEL/8 == 2 || BITS_PER_PIXEL/8 == 3 || BITS_PER_PIXEL/8 == 4);
	COMPILETIME_ASSERT(bitsperpixel_must_be_mutiplier_by_8, BITS_PER_PIXEL%8 == 0);
	//이미지 크기나 포멧이 바뀌면 아래 체크를 바꿔줘야함. S_QUESTION_OF_SPHINX @ TS_MAIN_Data
	COMPILETIME_ASSERT(buffersize_must_be_4140, BUFF_SIZE == 4140  );

public:
	TGA_IMAGE():m_bReady(0){};
	~TGA_IMAGE(){};

	TGA_HEADER const * Get_Header()const{return reinterpret_cast<TGA_HEADER const *>(m_bImgData);}
	BYTE const * Get_Img_Buffer()const	{return m_bImgData + sizeof(TGA_HEADER);}
	BYTE const * Get_Footer()const		{return m_bImgData + sizeof(TGA_HEADER) + PIXEL_DATA_SIZE;}
	BOOL IsReady()const { return m_bReady; }

	BOOL Load(char const * tFilename);
};
template<int WIDTH, int HEIGHT, int BITS_PER_PIXEL>
BOOL TGA_IMAGE<WIDTH, HEIGHT, BITS_PER_PIXEL>::Load(char const * tFilename)
{
	struct ScopeFile{
		FILE* fp;
		ScopeFile( char const * fname, char const * mod ) 
			: fp(fopen(fname, mod)){ /*assert( fp );*/ };
		~ScopeFile(){ if(fp) fclose(fp); fp = NULL; };
		operator FILE* () { return fp; };
		FILE* operator -> () {return fp;}
	};

	ScopeFile fp(tFilename, "r");
	if(fp)
	{
		fseek( fp, 0, SEEK_END );
		long const FILE_SIZE = ftell( fp );
		fseek( fp, 0, SEEK_SET );

		if(BUFF_SIZE != FILE_SIZE)
		{
			//assert(!"FILE_SIZE != BUFF_SIZE!");
			return 0;
		}

		if( BUFF_SIZE != fread(m_bImgData, sizeof(BYTE), FILE_SIZE, fp) )
		{
			//assert(!"fread faild!");
			return 0;
		}

		//http://en.wikipedia.org/wiki/Truevision_TGA#Header
		TGA_HEADER const * hdr = Get_Header();
		BYTE const * footer = Get_Footer();
		if( hdr->bitsperpixel != eBPP
			|| hdr->width != eWidth
			|| hdr->height != eHeight
			|| hdr->datatypecode != 2 
			|| (0!=strncmp((char const *)footer+8, "TRUEVISION-XFILE", 16))
			)
		{
			//assert(!"invalid image!");
			return 0;
		}

		m_bReady = 1;
		return 1;
	}

	//assert(!"fopen failed!");
	return 0;
};

class CSphinx
{
	typedef TGA_IMAGE<32,32,32>	tga_image;

	BOOL		m_bReady;
	tga_image	m_Img_Data[MAX_PUZZLE_NUM];
public:
	enum {IMG_FILE_SIZE = tga_image::BUFF_SIZE,};

public:
	CSphinx();
	virtual ~CSphinx();

	BOOL WakeUp_Sphinx();
	void ToSleep_Sphinx( void );

	BOOL Get_Transform_Num(BYTE out[], int index)const;

private:
	BOOL Transform_Manager(BYTE out[], BYTE const in[], TGA_HEADER const * hdr)const;
};
extern CSphinx mSphinx;

#endif //H012_SPHINX_H
