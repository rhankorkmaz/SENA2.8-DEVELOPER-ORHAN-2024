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
#if 0
	BYTE mOriginal2[MAX_TRANSFER_BUFFER_SIZE];
	DWORD mOriginalSize2;
#endif

	MyTransfer( void );

	BOOL Init( void );
	void Free( void );

	void B_CONNECT_OK( void );
	//-------------//
	//CENTER->LOGIN//
	//-------------//
	void B_LOGIN_FOR_CENTER_RECV( void );
	void B_GET_ZONE_SERVER_INFO_1_RESULT( int tResult, char tIP[16], int tPort );
	void B_GTOL_BAN_PLAYER (char szID[MAX_USER_ID_LENGTH]);	
	//------------//
	//CENTER->ZONE//
	//------------//
	void B_ZONE_FOR_CENTER_RECV( void );
	void B_TOTAL_ZONE_CONNECTION_INFO( ZONE_CONNECTION_INFO *tZoneConnectionInfo );
	void B_WORLD_INFO( WORLD_INFO *tWorldInfo, TRIBE_INFO *tTribeInfo );
	//void B_WORLD_INFO2( WORLD_INFO *tWorldInfo, TRIBE_INFO *tTribeInfo );
	void B_ZONE_CONNECTION_INFO( int tZoneNumber, char tIP[16], int tPort );
	void B_BROADCAST_INFO( int tInfoSort, BYTE tInfoData[MAX_BROADCAST_INFO_SIZE] );
	void B_START( void );
	void B_NOTICE( char tContent[MAX_CHAT_CONTENT_LENGTH], int tTribe );
	void B_SET_EVENT( int tEventSort, int tEventValue );
	void B_SHUTDOWN( void );
	void B_SET_GM_ORDER( int tEventSort, int tMoveZoneNumber, char tAvatarName01[13]);
	void B_SERCH_AVATAR( char tAvatarName01[13], int tUserIndex, int tGmIndex );
	void B_SET_GM_ORDER_MOVE_AVATAR( char tAvatarName01[13], int tPosX, int tPosY, int tPosZ );
	void B_TRIBE_CHAT( int tZoneNumber, int tTribe, char tAvatarName01[13], char tAvatarName02[13], char tContent[51] );
	void B_SECRET_CHAT( int tZoneNumber, int tTribe, char tAvatarName01[13], char tAvatarName02[13], char tContent[51] );
	void B_POLICE_INFO( char tID[33], int tLoginTime, int tLogoutTime );
	void B_GTOZ_BAN_PLAYER (char szID[MAX_USER_ID_LENGTH]);
	void B_CHECK_EVENT( int tEventSort, int tUserIndex, int tGmIndex );
	void B_TOTAL_RANK_INFO_RESULT(void);
	void B_RANK_INFO_RESULT(const char *aName);
    // # X-Trap # {
    void B_XTRAP_MAP_FILE_CHANGE_FOR_ZONE( void );
    // # }
    // @ Cost Info Download @
    void B_UPDATE_CASH_ITEM_INFO_FOR_ZONE();
	void B_CP_TOWER(CP_TOWERS* tCpTower);
	void B_RANKPOINT(RANK_INFO* tRanPoint);
	void B_RANKPOINTOLD(int Reset, OLD_RANK_INFO* tRanPoint);
    // @
	//------------//
	//CENTER->TOOL//
	//------------//
	void B_TOOL_FOR_CENTER_RECV( void );
    void B_TOOL_DEMAND_RESULT( void );
	void B_TOOL_SERCH_AVATAR_RESULT( int tZoneNumber, int tGmIndex );
	void B_TOOL_CHECK_EVENT_RESULT( int tGmIndex, int tEventSort, int tResult, int tWorldNumber, int tZoneNumber );
	//-----------------//
	//CENTER->CHAT_TOOL//
	//-----------------//
	void B_CHAT_TOOL_FOR_CENTER_RECV( void );
	//--------------//
	//CENTER->POLICE//
	//--------------//
	void B_POLICE_FOR_CENTER_RECV( void );

};
//INSTANCE
extern MyTransfer mTRANSFER;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
