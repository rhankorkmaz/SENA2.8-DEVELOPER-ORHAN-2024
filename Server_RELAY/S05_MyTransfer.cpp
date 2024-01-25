//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "Shengming.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_TRANSFER
//-------------------------------------------------------------------------------------------------
//INSTANCE
MyTransfer mTRANSFER;
//CREATE
MyTransfer::MyTransfer( void )
{
}
//INIT
BOOL MyTransfer::Init( void )
{
	return TRUE;
}
//FREE
void MyTransfer::Free( void )
{
}
//B_CONNECT_OK
void MyTransfer::B_CONNECT_OK( void )
{
	mOriginal[0] = 0;
	mOriginalSize = 1;
}
//B_ZONE_FOR_RELAY_RECV
void MyTransfer::B_ZONE_FOR_RELAY_RECV( void )
{
	mOriginal[0] = P_ZONE_FOR_RELAY_RECV;
	mOriginalSize = S_ZONE_FOR_RELAY_RECV;
}
//B_BROADCAST_DATA
void MyTransfer::B_BROADCAST_DATA( int tSort, BYTE tData[MAX_BROADCAST_DATA_SIZE] )
{
	mOriginal[0] = P_BROADCAST_DATA;
	CopyMemory( &mOriginal[1], &tSort, 4 );
	CopyMemory( &mOriginal[5], &tData[0], MAX_BROADCAST_DATA_SIZE );
	mOriginalSize = S_BROADCAST_DATA;
}
//-------------------------------------------------------------------------------------------------
