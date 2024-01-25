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
	//--------------//
	//ZONE->VALET//
	//--------------//
	//W_ZONE_FOR_PLAYUSER_SEND
	mWorkerPacketSize[P_ZONE_FOR_VALET_SEND] = S_ZONE_FOR_VALET_SEND;
	W_FUNCTION[P_ZONE_FOR_VALET_SEND].PROC = W_ZONE_FOR_VALET_SEND;
	//W_ZONE_OK_FOR_PLAYUSER_SEND
	mWorkerPacketSize[P_ZONE_OK_FOR_VALET_SEND] = S_ZONE_OK_FOR_VALET_SEND;
	W_FUNCTION[P_ZONE_OK_FOR_VALET_SEND].PROC = W_ZONE_OK_FOR_VALET_SEND;
	//W_DUPEFIX
	mWorkerPacketSize[P_VALET_DUPEFIX] = S_VALET_DUPEFIX;
	W_FUNCTION[P_VALET_DUPEFIX].PROC = W_VALET_DUPEFIX;
	//W_DUPEFIX1
	mWorkerPacketSize[P_VALET_DUPEFIX1] = S_VALET_DUPEFIX1;
	W_FUNCTION[P_VALET_DUPEFIX1].PROC = W_VALET_DUPEFIX1;
	//W_VALET_SHOP_INFO
	mWorkerPacketSize[P_VALET_VALETSHOPINFO] = S_VALET_VALETSHOPINFO;
	W_FUNCTION[P_VALET_VALETSHOPINFO].PROC = W_VALET_SHOP_INFO;
	//W_VALET_SHOP_UPDATE
	mWorkerPacketSize[P_VALET_UPDATEVALATINFO] = S_VALET_UPDATEVALATINFO;
	W_FUNCTION[P_VALET_UPDATEVALATINFO].PROC = W_VALET_SHOP_UPDATE;
	//W_SET_MOVE_ITEM_FOR_ZONE_SEND
	mWorkerPacketSize[P_VALET_VALETSHOPBUY] = S_VALET_VALETSHOPBUY;
	W_FUNCTION[P_VALET_VALETSHOPBUY].PROC = W_VALET_SHOP_BUY;

	Logger("![%s] OK", __FUNCTION__);
	return TRUE;
}
//FREE
void MyWork::Free( void )
{
}
//-------------------------------------------------------------------------------------------------
