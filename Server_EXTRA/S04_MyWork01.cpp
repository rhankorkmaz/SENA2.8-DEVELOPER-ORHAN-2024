//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "Shengming.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_WORK
//-------------------------------------------------------------------------------------------------
//INSTANCE
MyWork mWORK;
//CREATE
MyWork::MyWork( void )
{
}
//INIT
BOOL MyWork::Init( void )
{
	int index01;

	for( index01 = 0 ; index01 < 256 ; index01++ )
	{
		W_FUNCTION[index01].PROC = NULL;
	}
	//W_ZONE_FOR_EXTRA_SEND
	mWorkerPacketSize[P_ZONE_FOR_EXTRA_SEND] = S_ZONE_FOR_EXTRA_SEND;
	W_FUNCTION[P_ZONE_FOR_EXTRA_SEND].PROC = W_ZONE_FOR_EXTRA_SEND;
	//W_ZONE_OK_FOR_EXTRA_SEND
	mWorkerPacketSize[P_ZONE_OK_FOR_EXTRA_SEND] = S_ZONE_OK_FOR_EXTRA_SEND;
	W_FUNCTION[P_ZONE_OK_FOR_EXTRA_SEND].PROC = W_ZONE_OK_FOR_EXTRA_SEND;
	//W_GUILD_WORK_FOR_EXTRA_SEND
	mWorkerPacketSize[P_GUILD_WORK_FOR_EXTRA_SEND] = S_GUILD_WORK_FOR_EXTRA_SEND;
	W_FUNCTION[P_GUILD_WORK_FOR_EXTRA_SEND].PROC = W_GUILD_WORK_FOR_EXTRA_SEND;
	//W_GET_CASH_SIZE_FOR_EXTRA_SEND
	mWorkerPacketSize[P_GET_CASH_SIZE_FOR_EXTRA_SEND] = S_GET_CASH_SIZE_FOR_EXTRA_SEND;
	W_FUNCTION[P_GET_CASH_SIZE_FOR_EXTRA_SEND].PROC = W_GET_CASH_SIZE_FOR_EXTRA_SEND;
	//W_BUY_CASH_ITEM_FOR_EXTRA_SEND
	mWorkerPacketSize[P_BUY_CASH_ITEM_FOR_EXTRA_SEND] = S_BUY_CASH_ITEM_FOR_EXTRA_SEND;
	W_FUNCTION[P_BUY_CASH_ITEM_FOR_EXTRA_SEND].PROC = W_BUY_CASH_ITEM_FOR_EXTRA_SEND;
	// @ Cost Info Download @
	//W_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_SEND
	mWorkerPacketSize[P_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_SEND] = S_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_SEND;
	W_FUNCTION[P_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_SEND].PROC = W_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_SEND;
	//W_GET_CASH_ITEM_INFO_FOR_EXTRA_SEND
	mWorkerPacketSize[P_GET_CASH_ITEM_INFO_FOR_EXTRA_SEND] = S_GET_CASH_ITEM_INFO_FOR_EXTRA_SEND;
	W_FUNCTION[P_GET_CASH_ITEM_INFO_FOR_EXTRA_SEND].PROC = W_GET_CASH_ITEM_INFO_FOR_EXTRA_SEND;
	// @
	//W_USE_PACKAGE_ITEM_FOR_EXTRA_SEND
	mWorkerPacketSize[P_USE_PACKAGE_ITEM_FOR_EXTRA_SEND] = S_USE_PACKAGE_ITEM_FOR_EXTRA_SEND;
	W_FUNCTION[P_USE_PACKAGE_ITEM_FOR_EXTRA_SEND].PROC = W_USE_PACKAGE_ITEM_FOR_EXTRA_SEND;
	//W_USE_PACKAGE_ITEM_FOR_EXTRA_SEND
	mWorkerPacketSize[P_GET_BLOOD_ITEM_FOR_EXTRA_SEND] = S_GET_BLOOD_ITEM_FOR_EXTRA_SEND;
	W_FUNCTION[P_GET_BLOOD_ITEM_FOR_EXTRA_SEND].PROC = W_BLOOD_ITEM_INFO;
	return TRUE;
}
//FREE
void MyWork::Free( void )
{
}
//-------------------------------------------------------------------------------------------------
