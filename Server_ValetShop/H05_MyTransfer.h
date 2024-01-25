//-------------------------------------------------------------------------------------------------
//MY_TRANSFER_H
//-------------------------------------------------------------------------------------------------
#ifndef MY_TRANSFER_H
#define MY_TRANSFER_H
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_TRANSFER
//-------------------------------------------------------------------------------------------------
//MACRO
#define MAX_TRANSFER_BUFFER_SIZE									10000
//DEFINE
class MyTransfer
{

public :

	BYTE mOriginal[MAX_TRANSFER_BUFFER_SIZE];
	DWORD mOriginalSize;

	BYTE mOriginal2[MAX_TRANSFER_BUFFER_SIZE];
	DWORD mOriginalSize2;

	MyTransfer( void );

	BOOL Init( void );
	void Free( void );

	void B_CONNECT_OK( void );
	//---------------//
	//PLAYUSER->LOGIN//
	//---------------//
	void B_LOGIN_FOR_PLAYUSER_RECV( void );
	void B_REGISTER_USER_FOR_LOGIN_RECV( int tResult, int tPlayUserIndex );
	void B_UNREGISTER_USER_FOR_LOGIN_RECV( void );
	void B_GET_PRESENT_USER_NUM_FOR_LOGIN_RECV( int tPresentUserNum );
	void B_BLOCK_USER_FOR_LOGIN_RECV( int tResult );
	//--------------//
	//PLAYUSER->ZONE//
	//--------------//
	void B_ZONE_FOR_PLAYUSER_RECV( void );
	void B_REGISTER_USER_FOR_ZONE_0_RECV( int tResult, int tPlayUserIndex );
	void B_REGISTER_USER_FOR_ZONE_1_RECV( int tResult, int tUserSort, int tGoodFellow, int tUserRandom, int tLoginPremium, int tLoginPremiumPCRoom, int tTraceState, char tBonus100Money, int tPremiumServerExpirationDate, AVATAR_INFO *tAvatarInfo, int tEffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2], int tCheckFirstZone, AUTH_INFO *tAuthInfo, MOVE_ITEM_INFO *tMoveItemInfo, int AnimalOn ); // 함수 선언 수정 - int tPremiumServerExpirationDate 추가. // @_Premium_Server_@ // 이동서 사용정보(MOVE_ITEM_INFO *tMoveItemInfo) 추가.
	void B_REGISTER_USER_FOR_ZONE_2_RECV( int tResult );
	void B_REGISTER_USER_FOR_ZONE_3_RECV( int tResult );
	void B_UNREGISTER_USER_FOR_ZONE_RECV( void );
	void B_DUPEFIX(void);
	void B_DUPEFIX1(void);
	void B_FIND_AVATAR_FOR_ZONE_RECV( int tZoneNumber, int tTribe );
	void B_TRIBE_BANK_INFO_SAVE_RECV( void );
	void B_TRIBE_BANK_INFO_VIEW_RECV( int tResult, int tTribeBankInfo[MAX_TRIBE_BANK_SLOT_NUM] );
	void B_TRIBE_BANK_INFO_LOAD_RECV( int tResult, int tMoney );
	void B_HACK_NAME_RECV( int tResult );
	void B_BLOCK_USER_FOR_ZONE_RECV( int tResult );
	void B_ADD_AUTO_USER_LIST_RECV( int tResult );
	void B_CHECK_KILL_OTHER_TRIBE_RECV( int tResult );
	void B_EVENT_INFO_RECV( void );
	void B_CHANGE_AVATAR_NAME_FOR_ZONE_RECV(int tResult);
	void B_BONUS_100_MONEY_FOR_ZONE_RECV(int tResult);
	void B_VALETSHOPUPDATE(int tResult);
	void B_VALETSHOPINFO(int tResult, VALETSHOP_INFO* tValetShopInfo);
	void B_VALETSHOPBUY(int tResult);
	//--------------//
	//PLAYUSER->TOOL//
	//--------------//
	void B_TOOL_FOR_PLAYUSER_RECV( void );
	void B_CHANGE_LOGIN_USER_NUM_RECV( int tResult );
	void B_CHECK_ZONE_FOR_TOOL_RECV( int tResult );
	void B_GET_PRESENT_USER_NUM_FOR_TOOL_RECV( int tPresentUserNum );
	void B_FIND_AVATAR_FOR_TOOL_RECV( int tZoneNumber );
	void B_FIND_USER_FOR_TOOL_RECV( int tZoneNumber );
	void B_BLOCK_USER_FOR_TOOL_RECV( int tResult );
	void B_CHECK_AUTH_KEY (BYTE bResult);
	void B_UPDATE_AUTH_KEY (BYTE bResult);
	void B_GET_PRESENT_USER_NUM_2_FOR_TOOL_RECV( int tLength, char* tBuffer );
	//----------------//
	//PLAYUSER->POLICE//
	//----------------//
	void B_POLICE_FOR_PLAYUSER_RECV( void );
	void B_USER_INFO_FOR_POLICE( char tID[33], char tIP[16], const char tLoginState );
	void B_USER_INFO_FOR_POLICE2( char tID[33], char tIP[16], const char tLoginState );
};
//INSTANCE
extern MyTransfer mTRANSFER;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
