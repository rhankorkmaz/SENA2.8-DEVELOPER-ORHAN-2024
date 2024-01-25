

#ifndef H012_SPHINX_ALGORITHM_H
#define H012_SPHINX_ALGORITHM_H

#include "Shengming.h"
#include "H11_Sphinx.h"
#include "H13_Math_For_Server.h"


template<int BITS>
struct Bits2Byte
{
	enum {BYTES=BITS/8,};
};

template<int BitsPerPixel>
struct proxy {BYTE bytes[ Bits2Byte< BitsPerPixel >::BYTES ];};

template<int BitsPerPixel>
class CSphinxAlgorithm
{
protected:
	typedef proxy<BitsPerPixel>			TEXEL_T;
	typedef proxy<BitsPerPixel> *		LPTEXEL_T;
	typedef proxy<BitsPerPixel> const *	LPCTEXEL_T;

private:
	COMPILETIME_ASSERT(bitsperpixel_must_be_8_16_24_32, BitsPerPixel/8 == 1 || BitsPerPixel/8 == 2 || BitsPerPixel/8 == 3 || BitsPerPixel/8 == 4);
	COMPILETIME_ASSERT(bitsperpixel_must_be_mutiplier_by_8, BitsPerPixel%8 == 0);

public:
	CSphinxAlgorithm(){};
	virtual ~CSphinxAlgorithm(){};

	virtual void Transform_Data(BYTE* out
		, BYTE const * in
		, TGA_HEADER const * hdr)const=0;
};

template<int BitsPerPixel>
class CBILATERAL_SYMMETRY : public CSphinxAlgorithm<BitsPerPixel>
{
	typedef typename CSphinxAlgorithm<BitsPerPixel>::TEXEL_T	TEXEL_T;
	typedef typename CSphinxAlgorithm<BitsPerPixel>::LPTEXEL_T	LPTEXEL_T;
	typedef typename CSphinxAlgorithm<BitsPerPixel>::LPCTEXEL_T	LPCTEXEL_T;

	void Transform_Data(BYTE* out
		, BYTE const * in
		, TGA_HEADER const * hdr)const
	{
		LPTEXEL_T	tout = LPTEXEL_T(out);
		LPCTEXEL_T	tin	 = LPCTEXEL_T(in);

		int base_index = 0;
		int oper_index = 0;
		for (  int i = 0; i < int(hdr->height); i++ )
		{
			oper_index = base_index + int(hdr->width) - 1;
			for (  int j = 0; j < int(hdr->width); j++ )
			{
				tout[base_index] = tin[oper_index];
				--oper_index;
				++base_index;
			}
		}
	}
};

template<int BitsPerPixel>
class CDOTSCREEN_BACKGROUND : public CSphinxAlgorithm<BitsPerPixel>
{
	typedef typename CSphinxAlgorithm<BitsPerPixel>::TEXEL_T	TEXEL_T;
	typedef typename CSphinxAlgorithm<BitsPerPixel>::LPTEXEL_T	LPTEXEL_T;
	typedef typename CSphinxAlgorithm<BitsPerPixel>::LPCTEXEL_T	LPCTEXEL_T;

	void Transform_Data(BYTE* out
		, BYTE const * in
		, TGA_HEADER const * hdr)const
	{
		LPTEXEL_T	tout = LPTEXEL_T(out);
		LPCTEXEL_T	tin	 = LPCTEXEL_T(in);

		for (  int i = 0; i < int(hdr->height); i++ )
		{
			for (  int j = 0; j < int(hdr->width); j++ )
			{
				*tout = *tin;
				if(IsBlack(*tin))
				{
					SetRGB(*tout, (BYTE)(rand()%0xff));
				}

				++tout;
				++tin;
			} /// end For Loop : Width
		}/// end  For Loop : Height
	}

	BOOL IsBlack(TEXEL_T texel)const;
	void SetRGB(TEXEL_T & texel, BYTE val)const;
};

template<int BitsPerPixel>
class H_SHIFT : public CSphinxAlgorithm<BitsPerPixel>
{
	typedef typename CSphinxAlgorithm<BitsPerPixel>::TEXEL_T	TEXEL_T;
	typedef typename CSphinxAlgorithm<BitsPerPixel>::LPTEXEL_T	LPTEXEL_T;
	typedef typename CSphinxAlgorithm<BitsPerPixel>::LPCTEXEL_T	LPCTEXEL_T;

	const int shift_;

	void Transform_Data(BYTE* out
		, BYTE const * in
		, TGA_HEADER const * hdr)const
	{
		LPTEXEL_T	tout = LPTEXEL_T(out);
		LPCTEXEL_T	tin	 = LPCTEXEL_T(in);

		int shifted=0;
		for(int i=1; i<int(hdr->height); i+=2)
		{
			tout = LPTEXEL_T(out) + i*int(hdr->width);
			tin = LPTEXEL_T(in) + i*int(hdr->width);
			for ( int j=0; j < int(hdr->width); j++ )
			{
				shifted=j+shift_;
				if(shifted>=int(hdr->width))
				{
					shifted -= int(hdr->width);
				}
				*tout++ = *(tin + shifted);
			}
		}
	}

	H_SHIFT & operator = (H_SHIFT const &);
public:
	explicit H_SHIFT(int shift):shift_(shift){};
};

template<int BitsPerPixel>
class V_SHIFT : public CSphinxAlgorithm<BitsPerPixel>
{
	typedef typename CSphinxAlgorithm<BitsPerPixel>::TEXEL_T	TEXEL_T;
	typedef typename CSphinxAlgorithm<BitsPerPixel>::LPTEXEL_T	LPTEXEL_T;
	typedef typename CSphinxAlgorithm<BitsPerPixel>::LPCTEXEL_T	LPCTEXEL_T;

	const int shift_;

	void Transform_Data(BYTE* out
		, BYTE const * in
		, TGA_HEADER const * hdr)const
	{
		LPTEXEL_T	tout = LPTEXEL_T(out) + 1;
		LPCTEXEL_T	tin	 = LPCTEXEL_T(in);

		int shifted=0;
		for(int i=0; i<int(hdr->height); i++)
		{
			for ( int j=1; j < int(hdr->width); j+=2 )
			{
				shifted=i+shift_;
				if(shifted>=int(hdr->height))
				{
					shifted -= int(hdr->height);
				}
				*tout = *(tin+shifted*int(hdr->width) + j);

				tout+=2;
			}
		}
	}

	V_SHIFT & operator = (V_SHIFT const &);
public:
	explicit V_SHIFT(int shift):shift_(shift){};
};

template<int BitsPerPixel>
class SINE_WAVE : public CSphinxAlgorithm<BitsPerPixel>
{
	typedef typename CSphinxAlgorithm<BitsPerPixel>::TEXEL_T	TEXEL_T;
	typedef typename CSphinxAlgorithm<BitsPerPixel>::LPTEXEL_T	LPTEXEL_T;
	typedef typename CSphinxAlgorithm<BitsPerPixel>::LPCTEXEL_T	LPCTEXEL_T;

	const float cycle_;
	const float amplitude_;

	void Transform_Data(BYTE* out
		, BYTE const * in
		, TGA_HEADER const * hdr)const
	{
		LPTEXEL_T	tout = LPTEXEL_T(out);
		LPCTEXEL_T	tin	 = LPCTEXEL_T(in);

		const float step_in_radians = cycle_ * Math::TWO_PI / float(hdr->width);
        
		float angle = 0.f;
		int yindex = 0;
		for (  int i = 0; i < int(hdr->height); i++ )
		{
			angle = 0.f;
			for ( int j = 0; j < int(hdr->width); j++ )
			{
				//TODO : sin 태이블을 이용하자.
				yindex = i + (int)(amplitude_*sinf(angle));
				while(yindex<0)
				{
					yindex += int(hdr->height);
				}
				while(yindex>=int(hdr->height))
				{
					yindex -= int(hdr->height);
				}
				*tout++ = tin[yindex*int(hdr->width) + j];
				angle += step_in_radians;
			}
		}
	}

	SINE_WAVE & operator = (SINE_WAVE const &);
public:
	SINE_WAVE(float cycle, float amplitude):cycle_(cycle), amplitude_(amplitude){};
};


template<class T>
T clamp( T const & val, T const & min, T const & max )
{
	return ( val < min ) ? min : ((val>max) ? max : val);
}

template<int BitsPerPixel>
class CONCAVE_LENS : public CSphinxAlgorithm<BitsPerPixel>
{
	typedef typename CSphinxAlgorithm<BitsPerPixel>::TEXEL_T	TEXEL_T;
	typedef typename CSphinxAlgorithm<BitsPerPixel>::LPTEXEL_T	LPTEXEL_T;
	typedef typename CSphinxAlgorithm<BitsPerPixel>::LPCTEXEL_T	LPCTEXEL_T;

	void Transform_Data(BYTE* out
		, BYTE const * in
		, TGA_HEADER const * hdr)const
	{
		LPTEXEL_T	tout = LPTEXEL_T(out);
		LPCTEXEL_T	tin	 = LPCTEXEL_T(in);

		const float		Y_OF_CENTER = sqrtf(float(hdr->width)*float(hdr->width) + float(hdr->height)*float(hdr->height))*0.5f;
		const Vector3	center_of_sphere(float(hdr->width/2), Y_OF_CENTER, float(hdr->height/2));
		const float		RADIUS = Vec3Length(&center_of_sphere);

		Vector3 point(0,0,0);
		Vector3 c2p;

		for (  int i = 0; i < int(hdr->height); i++ )
		{
			point.z = float(i);
			for ( int j = 0; j < int(hdr->width); j++ )
			{
				point.x = float(j);

				c2p = point - center_of_sphere;
				Vec3Normalize(&c2p,&c2p);
				c2p = c2p * RADIUS + center_of_sphere;

				int x = clamp(int(c2p.x), 0, int(hdr->width-1));
				int y = clamp(int(c2p.z), 0, int(hdr->height-1));
				tout[i*int(hdr->width)+j] = tin[y*int(hdr->width)+x];
			}
		}
	}

	CONCAVE_LENS & operator = (CONCAVE_LENS const &);
public:
	CONCAVE_LENS(){};
};


template<int BitsPerPixel>
class CONVEX_LENS : public CSphinxAlgorithm<BitsPerPixel>
{
	typedef typename CSphinxAlgorithm<BitsPerPixel>::TEXEL_T	TEXEL_T;
	typedef typename CSphinxAlgorithm<BitsPerPixel>::LPTEXEL_T	LPTEXEL_T;
	typedef typename CSphinxAlgorithm<BitsPerPixel>::LPCTEXEL_T	LPCTEXEL_T;

	void Transform_Data(BYTE* out
		, BYTE const * in
		, TGA_HEADER const * hdr)const
	{
		LPTEXEL_T	tout = LPTEXEL_T(out);
		LPCTEXEL_T	tin	 = LPCTEXEL_T(in);

		const Plane	PLANE_TEX(0,1,0,0);
		const float		Y_OF_CENTER = sqrtf((float)(hdr->width)*(float)(hdr->width) + (float)(hdr->height)*(float)(hdr->height))*0.1f;
		const Vector3	center_of_sphere(float(hdr->width/2), Y_OF_CENTER, float(hdr->height/2));
		const float		Y_SINE		= center_of_sphere.y>0 ? -1.f : 1.f;
		const float		RADIUS		= Vec3Length(&center_of_sphere)*cosf(Math::PI/4.f);
		const float		RADIUS_SQ	= RADIUS*RADIUS;
		Vector3 point_on_sphere;
		Vector3 point_on_tex;
		Vector3 dist;
		Vector3 moved_center_of_sphere;


		for (  int i = 0; i < int(hdr->height); i++ )
		{
			for ( int j = 0; j < int(hdr->width); j++ )
			{
				point_on_sphere.x = float(j);
				point_on_sphere.z = float(i);
				point_on_sphere.y = 0.f;
				dist = point_on_sphere - center_of_sphere;
				point_on_sphere.y = center_of_sphere.y + Y_SINE*sqrtf(RADIUS_SQ-dist.x*dist.x-dist.z*dist.z);

				if( PlaneIntersectLine(&point_on_tex, &PLANE_TEX, &point_on_sphere, &center_of_sphere) )
				{
					int x = clamp(int(point_on_tex.x), 0, int(hdr->width-1));
					int y = clamp(int(point_on_tex.z), 0, int(hdr->height-1));
					tout[i*int(hdr->width)+j] = tin[y*int(hdr->width)+x];
				}
			}
		}
	}

	CONVEX_LENS & operator = (CONVEX_LENS const &);
public:
	CONVEX_LENS(){};
};

template<int BitsPerPixel>
class TONADO : public CSphinxAlgorithm<BitsPerPixel>
{
	typedef typename CSphinxAlgorithm<BitsPerPixel>::TEXEL_T	TEXEL_T;
	typedef typename CSphinxAlgorithm<BitsPerPixel>::LPTEXEL_T	LPTEXEL_T;
	typedef typename CSphinxAlgorithm<BitsPerPixel>::LPCTEXEL_T	LPCTEXEL_T;

	void Transform_Data(BYTE* out
		, BYTE const * in
		, TGA_HEADER const * hdr)const
	{
		LPTEXEL_T	tout = LPTEXEL_T(out);
		LPCTEXEL_T	tin	 = LPCTEXEL_T(in);

		const int cx = int(hdr->width)/2;
		const int cy = int(hdr->height)/2;
		const float radius_sq = (float(cx)*float(cx) + float(cy)*float(cy));
		const float omega = (Math::TWO_PI/radius_sq);
		Vector2 c2p;
		Matrix2 rot;
		float radian;
		float length;

		for (  int i = 0; i < int(hdr->height); i++ )
		{
			for ( int j = 0; j < int(hdr->width); j++ )
			{
				c2p.x = float(j-cx);
				c2p.y = float(i-cy);

				length = Vec2LengthSq(&c2p);
				radian = length * omega;
				Mat2Rotation(&rot, radian);

				Vec2Transform(&c2p, &c2p, &rot);

				int x = clamp(int(c2p.x)+cx, 0, int(hdr->width-1));
				int y = clamp(int(c2p.y)+cy, 0, int(hdr->height-1));
				tout[i*int(hdr->width)+j] = tin[y*int(hdr->width)+x];
			}
		}
	}

	TONADO & operator = (TONADO const &);
public:
	TONADO(){};
};

#endif	//H012_SPHINX_ALGORITHM_H
