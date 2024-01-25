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
	Logger("![%s] OK", __FUNCTION__);
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
//B_ZONE_FOR_PLAYUSER_RECV
void MyTransfer::B_ZONE_FOR_PLAYUSER_RECV( void )
{
	mOriginal[0] = P_ZONE_FOR_PLAYUSER_RECV;
	mOriginalSize = S_ZONE_FOR_PLAYUSER_RECV;
}
//B_DUPEFIX
void MyTransfer::B_DUPEFIX(void)
{
	mOriginal[0] = P_DUPEFIX_PLAYUSER;
	mOriginalSize = S_DUPEFIX_PLAYUSER;
}
//B_DUPEFIX
void MyTransfer::B_DUPEFIX1(void)
{
	mOriginal[0] = P_DUPEFIX_PLAYUSER1;
	mOriginalSize = S_DUPEFIX_PLAYUSER1;
}
//B_VALETSHOPINFO
void MyTransfer::B_VALETSHOPINFO(int tResult, VALETSHOP_INFO* tValetShopInfo)
{
	mOriginal[0] = P_VALETINFOPLAYUSERSEND;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], tValetShopInfo, sizeof(VALETSHOP_INFO));
	mOriginalSize = S_VALETINFOPLAYUSERSEND;
}
void MyTransfer::B_VALETSHOPUPDATE(int tResult)
{
	mOriginal[0] = P_VALET_UPDATERESULT;
	CopyMemory(&mOriginal[1], &tResult, 4);
	mOriginalSize = S_VALET_UPDATERESULT;
}
void MyTransfer::B_VALETSHOPBUY(int tResult)
{
	mOriginal[0] = P_VALETINFOBUYSEND;
	CopyMemory(&mOriginal[1], &tResult, 4);
	mOriginalSize = S_VALETINFOBUYSEND;
}