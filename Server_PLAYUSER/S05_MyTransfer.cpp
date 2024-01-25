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
//B_LOGIN_FOR_PLAYUSER_RECV
void MyTransfer::B_LOGIN_FOR_PLAYUSER_RECV( void )
{
	mOriginal[0] = P_LOGIN_FOR_PLAYUSER_RECV;
	mOriginalSize = S_LOGIN_FOR_PLAYUSER_RECV;
}
//B_REGISTER_USER_FOR_LOGIN_RECV
void MyTransfer::B_REGISTER_USER_FOR_LOGIN_RECV( int tResult, int tPlayUserIndex )
{
	mOriginal[0] = P_REGISTER_USER_FOR_LOGIN_RECV;
	CopyMemory( &mOriginal[1], &tResult, 4 );
	CopyMemory( &mOriginal[5], &tPlayUserIndex, 4 );
	mOriginalSize = S_REGISTER_USER_FOR_LOGIN_RECV;
}
//B_UNREGISTER_USER_FOR_LOGIN_RECV
void MyTransfer::B_UNREGISTER_USER_FOR_LOGIN_RECV( void )
{
	mOriginal[0] = P_UNREGISTER_USER_FOR_LOGIN_RECV;
	mOriginalSize = S_UNREGISTER_USER_FOR_LOGIN_RECV;
}
//B_GET_PRESENT_USER_NUM_FOR_LOGIN_RECV
void MyTransfer::B_GET_PRESENT_USER_NUM_FOR_LOGIN_RECV( int tPresentUserNum )
{
	mOriginal[0] = P_GET_PRESENT_USER_NUM_FOR_LOGIN_RECV;
	CopyMemory( &mOriginal[1], &tPresentUserNum, 4 );
	mOriginalSize = S_GET_PRESENT_USER_NUM_FOR_LOGIN_RECV;
}
//B_BLOCK_USER_FOR_LOGIN_RECV
void MyTransfer::B_BLOCK_USER_FOR_LOGIN_RECV( int tResult )
{
	mOriginal[0] = P_BLOCK_USER_FOR_LOGIN_RECV;
	CopyMemory( &mOriginal[1], &tResult, 4 );
	mOriginalSize = S_BLOCK_USER_FOR_LOGIN_RECV;
}
//B_ZONE_FOR_PLAYUSER_RECV
void MyTransfer::B_ZONE_FOR_PLAYUSER_RECV( void )
{
	mOriginal[0] = P_ZONE_FOR_PLAYUSER_RECV;
	mOriginalSize = S_ZONE_FOR_PLAYUSER_RECV;
}
//B_REGISTER_USER_FOR_ZONE_0_RECV
void MyTransfer::B_REGISTER_USER_FOR_ZONE_0_RECV( int tResult, int tPlayUserIndex )
{
	mOriginal[0] = P_REGISTER_USER_FOR_ZONE_0_RECV;
	CopyMemory( &mOriginal[1], &tResult, 4 );
	CopyMemory( &mOriginal[5], &tPlayUserIndex, 4 );
	mOriginalSize = S_REGISTER_USER_FOR_ZONE_0_RECV;
}
//B_REGISTER_USER_FOR_ZONE_1_RECV
void MyTransfer::B_REGISTER_USER_FOR_ZONE_1_RECV( int tResult, int tUserSort, int tGoodFellow, int tUserRandom, int tLoginPremium, int tLoginPremiumPCRoom, int tTraceState, char tBonus100Money, int tPremiumServerExpirationDate, AVATAR_INFO *tAvatarInfo, int tEffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2], int tCheckFirstZone, AUTH_INFO *tAuthInfo, MOVE_ITEM_INFO *tMoveItemInfo , int AnimalOn) // 함수 선언 수정 - int tPremiumServerExpirationDate 추가. // @_Premium_Server_@ // 이동서 사용정보(MOVE_ITEM_INFO *tMoveItemInfo) 추가.
{
	mOriginal[0] = P_REGISTER_USER_FOR_ZONE_1_RECV;
	CopyMemory( &mOriginal[1], &tResult, 4 );
	CopyMemory( &mOriginal[5], &tUserSort, 4 );
	CopyMemory( &mOriginal[9], &tGoodFellow, 4 );
	CopyMemory( &mOriginal[13], &tUserRandom, 4 );
	CopyMemory( &mOriginal[17], &tLoginPremium, 4 );
	CopyMemory( &mOriginal[21], &tLoginPremiumPCRoom, 4 );
	CopyMemory( &mOriginal[25], &tTraceState, 4 );
	CopyMemory( &mOriginal[29], &tBonus100Money, 1);
	CopyMemory( &mOriginal[30], &tPremiumServerExpirationDate, 4); // @_Premium_Server_@
	CopyMemory( &mOriginal[34], tAvatarInfo, sizeof( AVATAR_INFO ) );
	CopyMemory( &mOriginal[( 34 + sizeof( AVATAR_INFO ) )], tEffectValue, ( MAX_AVATAR_EFFECT_SORT_NUM * 8 ) );
	CopyMemory( &mOriginal[( 34 + sizeof( AVATAR_INFO ) + MAX_AVATAR_EFFECT_SORT_NUM * 8 )], &tCheckFirstZone, 4 );
	CopyMemory( &mOriginal[( 38 + sizeof( AVATAR_INFO ) + MAX_AVATAR_EFFECT_SORT_NUM * 8 )], tAuthInfo, sizeof(AUTH_INFO) );
	CopyMemory( &mOriginal[( 38 + sizeof( AVATAR_INFO ) + MAX_AVATAR_EFFECT_SORT_NUM * 8 + sizeof(AUTH_INFO))], tMoveItemInfo, sizeof(MOVE_ITEM_INFO) );
	CopyMemory( &mOriginal[(38 + sizeof(AVATAR_INFO) + MAX_AVATAR_EFFECT_SORT_NUM * 8 + sizeof(AUTH_INFO) + sizeof(MOVE_ITEM_INFO))], &AnimalOn, 4);
	mOriginalSize = S_REGISTER_USER_FOR_ZONE_1_RECV;
}
//B_REGISTER_USER_FOR_ZONE_2_RECV
void MyTransfer::B_REGISTER_USER_FOR_ZONE_2_RECV( int tResult )
{
	mOriginal[0] = P_REGISTER_USER_FOR_ZONE_2_RECV;
	CopyMemory( &mOriginal[1], &tResult, 4 );
	mOriginalSize = S_REGISTER_USER_FOR_ZONE_2_RECV;
}
//B_REGISTER_USER_FOR_ZONE_3_RECV
void MyTransfer::B_REGISTER_USER_FOR_ZONE_3_RECV( int tResult )
{
	mOriginal[0] = P_REGISTER_USER_FOR_ZONE_3_RECV;
	CopyMemory( &mOriginal[1], &tResult, 4 );
	mOriginalSize = S_REGISTER_USER_FOR_ZONE_3_RECV;
}
//B_UNREGISTER_USER_FOR_ZONE_RECV
void MyTransfer::B_UNREGISTER_USER_FOR_ZONE_RECV( void )
{
	mOriginal[0] = P_UNREGISTER_USER_FOR_ZONE_RECV;
	mOriginalSize = S_UNREGISTER_USER_FOR_ZONE_RECV;
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
	mOriginal[0] = P_VALETINFOONLINECHECK;
	CopyMemory(&mOriginal[1], &tResult, 4);
	mOriginalSize = S_VALETINFOONLINECHECK;
}
void MyTransfer::B_VALETSHOPBUY(int tResult)
{
	mOriginal[0] = P_VALETINFOBUYSEND;
	CopyMemory(&mOriginal[1], &tResult, 4);
	mOriginalSize = S_VALETINFOBUYSEND;
}
//B_FIND_AVATAR_FOR_ZONE_RECV
void MyTransfer::B_FIND_AVATAR_FOR_ZONE_RECV( int tZoneNumber, int tTribe )
{
	mOriginal[0] = P_FIND_AVATAR_FOR_ZONE_RECV;
	CopyMemory( &mOriginal[1], &tZoneNumber, 4 );
	CopyMemory( &mOriginal[5], &tTribe, 4 );
	mOriginalSize = S_FIND_AVATAR_FOR_ZONE_RECV;
}
//B_TRIBE_BANK_INFO_SAVE_RECV
void MyTransfer::B_TRIBE_BANK_INFO_SAVE_RECV( void )
{
	mOriginal[0] = P_TRIBE_BANK_INFO_SAVE_RECV;
	mOriginalSize = S_TRIBE_BANK_INFO_SAVE_RECV;
}
//B_TRIBE_BANK_INFO_VIEW_RECV
void MyTransfer::B_TRIBE_BANK_INFO_VIEW_RECV( int tResult, int tTribeBankInfo[MAX_TRIBE_BANK_SLOT_NUM] )
{
	mOriginal[0] = P_TRIBE_BANK_INFO_VIEW_RECV;
	CopyMemory( &mOriginal[1], &tResult, 4 );
	CopyMemory( &mOriginal[5], &tTribeBankInfo[0], ( MAX_TRIBE_BANK_SLOT_NUM * 4 ) );
	mOriginalSize = S_TRIBE_BANK_INFO_VIEW_RECV;
}
//B_TRIBE_BANK_INFO_LOAD_RECV
void MyTransfer::B_TRIBE_BANK_INFO_LOAD_RECV( int tResult, int tMoney )
{
	mOriginal[0] = P_TRIBE_BANK_INFO_LOAD_RECV;
	CopyMemory( &mOriginal[1], &tResult, 4 );
	CopyMemory( &mOriginal[5], &tMoney, 4 );
	mOriginalSize = S_TRIBE_BANK_INFO_LOAD_RECV;
}
//B_HACK_NAME_RECV
void MyTransfer::B_HACK_NAME_RECV( int tResult )
{
	mOriginal[0] = P_HACK_NAME_RECV;
	CopyMemory( &mOriginal[1], &tResult, 4 );
	mOriginalSize = S_HACK_NAME_RECV;
}
//B_BLOCK_USER_FOR_ZONE_RECV
void MyTransfer::B_BLOCK_USER_FOR_ZONE_RECV( int tResult )
{
	mOriginal[0] = P_BLOCK_USER_FOR_ZONE_RECV;
	CopyMemory( &mOriginal[1], &tResult, 4 );
	mOriginalSize = S_BLOCK_USER_FOR_ZONE_RECV;
}
//B_ADD_AUTO_USER_LIST_RECV
void MyTransfer::B_ADD_AUTO_USER_LIST_RECV( int tResult )
{
	mOriginal[0] = P_ADD_AUTO_USER_LIST_RECV;
	CopyMemory( &mOriginal[1], &tResult, 4 );
	mOriginalSize = S_ADD_AUTO_USER_LIST_RECV;
}
//B_CHECK_KILL_OTHER_TRIBE_RECV
void MyTransfer::B_CHECK_KILL_OTHER_TRIBE_RECV( int tResult )
{
	mOriginal[0] = P_CHECK_KILL_OTHER_TRIBE_RECV;
	CopyMemory( &mOriginal[1], &tResult, 4 );
	mOriginalSize = S_CHECK_KILL_OTHER_TRIBE_RECV;
}
//B_EVENT_INFO_RECV
void MyTransfer::B_EVENT_INFO_RECV( void )
{
	mOriginal[0] = P_EVENT_INFO_RECV;
	mOriginalSize = S_EVENT_INFO_RECV;
}
//B_CHANGE_AVATAR_NAME_FOR_ZONE_RECV
void MyTransfer::B_CHANGE_AVATAR_NAME_FOR_ZONE_RECV(int tResult)
{
	mOriginal[0] = P_CHANGE_AVATAR_NAME_FOR_ZONE_RECV;
	CopyMemory( &mOriginal[1], &tResult, 4 );
	mOriginalSize = S_CHANGE_AVATAR_NAME_FOR_ZONE_RECV;
}
//B_BONUS_100_MONEY_FOR_ZONE_RECV
void MyTransfer::B_BONUS_100_MONEY_FOR_ZONE_RECV(int tResult){
	mOriginal[0] = P_BONUS_100_MONEY_FOR_ZONE_RECV;
	CopyMemory( &mOriginal[1], &tResult, 4 );
	mOriginalSize = S_BONUS_100_MONEY_FOR_ZONE_RECV;
}

void MyTransfer::B_CHECK_AUTH_KEY (BYTE bResult)
{
	PTOZ_CHECK_AUTH_KEY pack;
	pack.m_bResult = bResult;
	::CopyMemory (mOriginal, &pack, PTOZ_CHECK_AUTH_KEY_SIZE);
	mOriginalSize = PTOZ_CHECK_AUTH_KEY_SIZE;
}

void MyTransfer::B_UPDATE_AUTH_KEY (BYTE bResult)
{
	PTOZ_UPDATE_AUTH_KEY pack;
	pack.m_bResult = bResult;
	::CopyMemory (mOriginal, &pack, PTOZ_UPDATE_AUTH_KEY_SIZE);
	mOriginalSize = PTOZ_UPDATE_AUTH_KEY_SIZE;
}
//B_TOOL_FOR_PLAYUSER_RECV
void MyTransfer::B_TOOL_FOR_PLAYUSER_RECV( void )
{
	mOriginal[0] = P_TOOL_FOR_PLAYUSER_RECV;
	mOriginalSize = S_TOOL_FOR_PLAYUSER_RECV;
}
//B_CHANGE_LOGIN_USER_NUM_RECV
void MyTransfer::B_CHANGE_LOGIN_USER_NUM_RECV( int tResult )
{
	mOriginal[0] = P_CHANGE_LOGIN_USER_NUM_RECV;
	CopyMemory( &mOriginal[1], &tResult, 4 );
	mOriginalSize = S_CHANGE_LOGIN_USER_NUM_RECV;
}
//B_CHECK_ZONE_FOR_TOOL_RECV
void MyTransfer::B_CHECK_ZONE_FOR_TOOL_RECV( int tResult )
{
	mOriginal[0] = P_CHECK_ZONE_FOR_TOOL_RECV;
	CopyMemory( &mOriginal[1], &tResult, 4 );
	mOriginalSize = S_CHECK_ZONE_FOR_TOOL_RECV;
}
//B_GET_PRESENT_USER_NUM_FOR_TOOL_RECV
void MyTransfer::B_GET_PRESENT_USER_NUM_FOR_TOOL_RECV( int tPresentUserNum )
{
	mOriginal[0] = P_GET_PRESENT_USER_NUM_FOR_TOOL_RECV;
	CopyMemory( &mOriginal[1], &tPresentUserNum, 4 );
	mOriginalSize = S_GET_PRESENT_USER_NUM_FOR_TOOL_RECV;
}
//B_FIND_AVATAR_FOR_TOOL_RECV
void MyTransfer::B_FIND_AVATAR_FOR_TOOL_RECV( int tZoneNumber )
{
	mOriginal[0] = P_FIND_AVATAR_FOR_TOOL_RECV;
	CopyMemory( &mOriginal[1], &tZoneNumber, 4 );
	mOriginalSize = S_FIND_AVATAR_FOR_TOOL_RECV;
}
//B_FIND_USER_FOR_TOOL_RECV
void MyTransfer::B_FIND_USER_FOR_TOOL_RECV( int tZoneNumber )
{
	mOriginal[0] = P_FIND_USER_FOR_TOOL_RECV;
	CopyMemory( &mOriginal[1], &tZoneNumber, 4 );
	mOriginalSize = S_FIND_USER_FOR_TOOL_RECV;
}
//B_BLOCK_USER_FOR_TOOL_RECV
void MyTransfer::B_BLOCK_USER_FOR_TOOL_RECV( int tResult )
{
	mOriginal[0] = P_BLOCK_USER_FOR_TOOL_RECV;
	CopyMemory( &mOriginal[1], &tResult, 4 );
	mOriginalSize = S_BLOCK_USER_FOR_TOOL_RECV;
}

void MyTransfer::B_GET_PRESENT_USER_NUM_2_FOR_TOOL_RECV( int tLength, char* tBuffer )
{
	mOriginal[0] = P_GET_PRESENT_USER_NUM_2_FOR_TOOL_RECV;
	CopyMemory(&mOriginal[1], &tLength, 4 );
	CopyMemory(&mOriginal[5], tBuffer, 2048);//sizeof (tBuffer));
	mOriginalSize = S_GET_PRESENT_USER_NUM_2_FOR_TOOL_RECV;
}

//B_POLICE_FOR_PLAYUSER_RECV
void MyTransfer::B_POLICE_FOR_PLAYUSER_RECV( void )
{
	mOriginal[0] = P_POLICE_FOR_PLAYUSER_RECV;
	mOriginalSize = S_POLICE_FOR_PLAYUSER_RECV;
}
//B_USER_INFO_FOR_POLICE
void MyTransfer::B_USER_INFO_FOR_POLICE( char tID[33], char tIP[16], const char tLoginState )
{
	char tPoliceID[33];

	strcpy( tPoliceID, tID );
	mOriginal[0] = P_USER_INFO_FOR_POLICE;
	CopyMemory( &mOriginal[1], &tPoliceID[0], 33 );
	CopyMemory( &mOriginal[34], &tIP[0], 16 );
	mOriginal[50] = tLoginState;
	mOriginalSize = S_USER_INFO_FOR_POLICE;
}
void MyTransfer::B_USER_INFO_FOR_POLICE2( char tID[33], char tIP[16], const char tLoginState )
{
	char tPoliceID[33];

	strcpy( tPoliceID, tID );
	mOriginal2[0] = P_USER_INFO_FOR_POLICE;
	CopyMemory( &mOriginal2[1], &tPoliceID[0], 33 );
	CopyMemory( &mOriginal2[34], &tIP[0], 16 );
	mOriginal2[50] = tLoginState;
	mOriginalSize2 = S_USER_INFO_FOR_POLICE;
}

//-------------------------------------------------------------------------------------------------
