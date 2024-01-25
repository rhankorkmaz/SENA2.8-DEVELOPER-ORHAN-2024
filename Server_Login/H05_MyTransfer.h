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

	MyTransfer( void );

	BOOL Init( void );
	void Free( void );

	void B_CONNECT_OK( int tRandomNumber, int tMaxPlayerNum, int tGagePlayerNum, int tPresentPlayerNum );
	void B_LOGIN_RECV( int tResult, char tID[MAX_USER_ID_LENGTH], int tUserSort, int tUserRandom, int tLoginPremium, int tLoginPremiumPCRoom, int tSecondLoginSort, char tMousePassword[MAX_MOUSE_PASSWORD_LENGTH], int tSecretCardIndex01, int tSecretCardIndex02, char tFirstLogin = '0' );
	void B_USER_AVATAR_INFO( AVATAR_INFO *tAvatarInfo );
	void B_CREATE_MOUSE_PASSWORD_RECV( int tResult, char tMousePassword[MAX_MOUSE_PASSWORD_LENGTH] );
	void B_CHANGE_MOUSE_PASSWORD_RECV( int tResult, char tMousePassword[MAX_MOUSE_PASSWORD_LENGTH] );
	void B_LOGIN_MOUSE_PASSWORD_RECV( int tResult );
	void B_LOGIN_SECRET_CARD_RECV( int tResult );
	void B_CREATE_AVATAR_RECV( int tResult, AVATAR_INFO *tAvatarInfo );
	void B_DELETE_AVATAR_RECV( int tResult );
	void B_CHANGE_AVATAR_NAME_RECV( int tResult );
	void B_DEMAND_GIFT_RECV( int tResult, int tGiftInfo[10] );
	void B_WANT_GIFT_RECV( int tResult );
	void B_DEMAND_ZONE_SERVER_INFO_1_RESULT( int tResult, char tIP[16], int tPort, int tZoneNumber );
	void B_RCMD_WORLD_SEND(void);
	void B_ITEM_EVENT_SEND(int tResult, int unk, int unk1, int unk2[5][10][4]);
	void B_RECIVE_GIFT_ITEM_SEND(int tResult,int unk[10][2]);
};
//INSTANCE
extern MyTransfer mTRANSFER;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
