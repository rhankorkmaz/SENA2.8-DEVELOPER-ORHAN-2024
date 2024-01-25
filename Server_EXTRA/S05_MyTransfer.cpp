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
//B_ZONE_FOR_EXTRA_RECV
// @ Cost Info Download @
void MyTransfer::B_ZONE_FOR_EXTRA_RECV(int tVersion, const int tCashItemInfo[4][14][10][4])
{
	mOriginal[0] = P_ZONE_FOR_EXTRA_RECV;
	CopyMemory( &mOriginal[1], &tVersion, 4 );
	CopyMemory( &mOriginal[5], tCashItemInfo, MAX_CASH_ITEM_INFO_SIZE );
	mOriginalSize = S_ZONE_FOR_EXTRA_RECV;
} // @
//B_GUILD_WORK_FOR_EXTRA_RECV
void MyTransfer::B_GUILD_WORK_FOR_EXTRA_RECV( int tResult, GUILD_INFO *tGuildInfo )
{
	mOriginal[0] = P_GUILD_WORK_FOR_EXTRA_RECV;
	CopyMemory( &mOriginal[1], &tResult, 4 );
	CopyMemory( &mOriginal[5], tGuildInfo, sizeof( GUILD_INFO ) );
	mOriginalSize = S_GUILD_WORK_FOR_EXTRA_RECV;
}
//B_GET_CASH_SIZE_FOR_EXTRA_RECV
void MyTransfer::B_GET_CASH_SIZE_FOR_EXTRA_RECV( int tCashSize, int tBonusCashSize )
{
	mOriginal[0] = P_GET_CASH_SIZE_FOR_EXTRA_RECV;
	CopyMemory( &mOriginal[1], &tCashSize, 4 );
	CopyMemory( &mOriginal[5], &tBonusCashSize, 4 );
	mOriginalSize = S_GET_CASH_SIZE_FOR_EXTRA_RECV;
}
//B_BUY_CASH_ITEM_FOR_EXTRA_RECV
void MyTransfer::B_BUY_CASH_ITEM_FOR_EXTRA_RECV( int tResult, int tCashSize, int tBonusCashSize, int tCostSize, int tBonusCostSize )
{
	mOriginal[0] = P_BUY_CASH_ITEM_FOR_EXTRA_RECV;
	CopyMemory( &mOriginal[1], &tResult, 4 );
	CopyMemory( &mOriginal[5], &tCashSize, 4 );
	CopyMemory( &mOriginal[9], &tBonusCashSize, 4 );
	CopyMemory( &mOriginal[13], &tCostSize, 4 );
	CopyMemory( &mOriginal[17], &tBonusCostSize, 4 );
	mOriginalSize = S_BUY_CASH_ITEM_FOR_EXTRA_RECV;
}
// @ Cost Info Download @
void MyTransfer::B_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_RECV( int tResult )
{
	mOriginal[0] = P_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_RECV;
	CopyMemory( &mOriginal[1], &tResult, 4 );
	mOriginalSize = S_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_RECV;
}

void MyTransfer::B_GET_CASH_ITEM_INFO_FOR_EXTRA_RECV( int tResult, int tVersion, const int tCashItemInfo[4][14][10][4] )
{
	mOriginal[0] = P_GET_CASH_ITEM_INFO_FOR_EXTRA_RECV;
	CopyMemory( &mOriginal[1], &tResult, 4 );
	CopyMemory( &mOriginal[5], &tVersion, 4 );
	CopyMemory( &mOriginal[9], tCashItemInfo, MAX_CASH_ITEM_INFO_SIZE );
	mOriginalSize = S_GET_CASH_ITEM_INFO_FOR_EXTRA_RECV;
} // @

void MyTransfer::B_USE_PACKAGE_ITEM_FOR_EXTRA_SEND( int tResult )
{
	mOriginal[0] = P_USE_PACKAGE_ITEM_FOR_EXTRA_RECV;
	CopyMemory( &mOriginal[1], &tResult, 4 );
	mOriginalSize = S_USE_PACKAGE_ITEM_FOR_EXTRA_RECV;
}
void MyTransfer::B_BLOOD_ITEM_FOR_EXTRA_SEND(int tResult, const int mBloodItemInfo[4][50][3])
{
	mOriginal[0] = P_BLOOD_ITEM_FOR_EXTRA_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], mBloodItemInfo, 2400);
	mOriginalSize = S_BLOOD_ITEM_FOR_EXTRA_RECV;
}
//-------------------------------------------------------------------------------------------------
