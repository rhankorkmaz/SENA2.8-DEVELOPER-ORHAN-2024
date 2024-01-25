
#include "Shengming.h"
#include <cassert>
#include <stdlib.h>

template<> BOOL CDOTSCREEN_BACKGROUND<32>::IsBlack(TEXEL_T texel)const
{
	return ( texel.bytes[0] == 0
		  && texel.bytes[1] == 0
		  && texel.bytes[2] == 0 );
}
template<> BOOL CDOTSCREEN_BACKGROUND<24>::IsBlack(TEXEL_T texel)const
{
	return ( texel.bytes[0] == 0
		  && texel.bytes[1] == 0
		  && texel.bytes[2] == 0 );
}
template<> BOOL CDOTSCREEN_BACKGROUND<16>::IsBlack(TEXEL_T texel)const
{
	return ( texel.bytes[0] == 0
		  && texel.bytes[1] == 0);
}
template<> BOOL CDOTSCREEN_BACKGROUND< 8>::IsBlack(TEXEL_T texel)const
{
	return ( texel.bytes[0] == 0 );
}

template<> void CDOTSCREEN_BACKGROUND<32>::SetRGB(TEXEL_T & texel, BYTE val)const
{
	texel.bytes[0] = val;
	texel.bytes[1] = val;
	texel.bytes[2] = val;
}				
template<> void CDOTSCREEN_BACKGROUND<24>::SetRGB(TEXEL_T & texel, BYTE val)const
{
	texel.bytes[0] = val;
	texel.bytes[1] = val;
	texel.bytes[2] = val;
}				
template<> void CDOTSCREEN_BACKGROUND<16>::SetRGB(TEXEL_T & texel, BYTE val)const
{
	texel.bytes[0] = val;
	texel.bytes[1] = val;
}				
template<> void CDOTSCREEN_BACKGROUND< 8>::SetRGB(TEXEL_T & texel, BYTE val)const
{
	texel.bytes[0] = val;
}
