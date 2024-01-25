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
//B_LOGIN_FOR_CENTER_RECV
void MyTransfer::B_LOGIN_FOR_CENTER_RECV( void )
{
	mOriginal[0] = P_LOGIN_FOR_CENTER_RECV;
	mOriginalSize = S_LOGIN_FOR_CENTER_RECV;
}
//B_GET_ZONE_SERVER_INFO_1_RESULT
void MyTransfer::B_GET_ZONE_SERVER_INFO_1_RESULT( int tResult, char tIP[16], int tPort )
{
	mOriginal[0] = P_GET_ZONE_SERVER_INFO_1_RESULT;
	CopyMemory( &mOriginal[1], &tResult, 4 );
	CopyMemory( &mOriginal[5], &tIP[0], 16 );
	CopyMemory( &mOriginal[21], &tPort, 4 );
	mOriginalSize = S_GET_ZONE_SERVER_INFO_1_RESULT;
}

void MyTransfer::B_GTOL_BAN_PLAYER (char szID[MAX_USER_ID_LENGTH])
{
	GTOL_BAN_PLAYER pack;
	::CopyMemory (pack.m_szID, szID, MAX_USER_ID_LENGTH - 1);

	::CopyMemory (mOriginal, &pack, GTOL_BAN_PLAYER_SIZE);
	mOriginalSize = GTOL_BAN_PLAYER_SIZE;
}
//B_ZONE_FOR_CENTER_RECV
void MyTransfer::B_ZONE_FOR_CENTER_RECV( void )
{
	mOriginal[0] = P_ZONE_FOR_CENTER_RECV;
	mOriginalSize = S_ZONE_FOR_CENTER_RECV;
}
//B_TOTAL_ZONE_CONNECTION_INFO
void MyTransfer::B_TOTAL_ZONE_CONNECTION_INFO( ZONE_CONNECTION_INFO *tZoneConnectionInfo )
{
	mOriginal[0] = P_TOTAL_ZONE_CONNECTION_INFO;
	CopyMemory( &mOriginal[1], tZoneConnectionInfo, sizeof( ZONE_CONNECTION_INFO ) );
	mOriginalSize = S_TOTAL_ZONE_CONNECTION_INFO;
}
//B_WORLD_INFO
void MyTransfer::B_WORLD_INFO( WORLD_INFO *tWorldInfo, TRIBE_INFO *tTribeInfo )
{
	mOriginal[0] = P_WORLD_INFO;
	CopyMemory( &mOriginal[1], tWorldInfo, sizeof( WORLD_INFO ) );
	CopyMemory( &mOriginal[( 1 + sizeof( WORLD_INFO ) )], tTribeInfo, sizeof( TRIBE_INFO ) );
	mOriginalSize = S_WORLD_INFO;
}
//B_ZONE_CONNECTION_INFO
void MyTransfer::B_ZONE_CONNECTION_INFO( int tZoneNumber, char tIP[16], int tPort )
{
	mOriginal[0] = P_ZONE_CONNECTION_INFO;
	CopyMemory( &mOriginal[1], &tZoneNumber, 4 );
	CopyMemory( &mOriginal[5], &tIP[0], 16 );
	CopyMemory( &mOriginal[21], &tPort, 4 );
	mOriginalSize = S_ZONE_CONNECTION_INFO;
}
//B_BROADCAST_INFO
void MyTransfer::B_BROADCAST_INFO( int tInfoSort, BYTE tInfoData[MAX_BROADCAST_INFO_SIZE] )
{ 

	mOriginal[0] = P_BROADCAST_INFO;
	CopyMemory( &mOriginal[1], &tInfoSort, 4 );
	CopyMemory( &mOriginal[5], &tInfoData[0], MAX_BROADCAST_INFO_SIZE );
	mOriginalSize = S_BROADCAST_INFO;
}
//B_START
void MyTransfer::B_START( void )
{
	mOriginal[0] = P_START;
	mOriginalSize = S_START;
}
//B_NOTICE
void MyTransfer::B_NOTICE( char tContent[MAX_CHAT_CONTENT_LENGTH], int tTribe )
{
	mOriginal[0] = P_NOTICE;
	CopyMemory( &mOriginal[1], &tContent[0], MAX_CHAT_CONTENT_LENGTH );
	CopyMemory( &mOriginal[( 1 + MAX_CHAT_CONTENT_LENGTH )], &tTribe, 4 );
	mOriginalSize = S_NOTICE;
}
//B_SET_EVENT
void MyTransfer::B_SET_EVENT( int tEventSort, int tEventValue )
{
	mOriginal[0] = P_SET_EVENT;
	CopyMemory( &mOriginal[1], &tEventSort, 4 );
	CopyMemory( &mOriginal[5], &tEventValue, 4 );
	mOriginalSize = S_SET_EVENT;
}
//B_SHUTDOWN
void MyTransfer::B_SHUTDOWN( void )
{
	mOriginal[0] = P_SHUTDOWN;
	mOriginalSize = S_SHUTDOWN;
}
//B_SET_GM_ORDER
void MyTransfer::B_SET_GM_ORDER( int tEventSort, int tMoveZoneNumber, char tAvatarName01[13])
{
	mOriginal[0] = P_SET_GM_ORDER;
	CopyMemory( &mOriginal[1], &tEventSort, 4 );
	CopyMemory( &mOriginal[5], &tMoveZoneNumber, 4 );
	CopyMemory( &mOriginal[9], &tAvatarName01[0], 13 );
	mOriginalSize = S_SET_GM_ORDER;
}
//B_SERCH_AVATAR
void MyTransfer::B_SERCH_AVATAR( char tAvatarName01[13], int tUserIndex, int tGmIndex)
{
	mOriginal[0] = P_SERCH_AVATAR;	
	CopyMemory( &mOriginal[1], &tAvatarName01[0], 13 );
	CopyMemory( &mOriginal[14], &tUserIndex, 4 );
	CopyMemory( &mOriginal[18], &tGmIndex, 4 );
	mOriginalSize = S_SERCH_AVATAR;
}
void MyTransfer::B_SET_GM_ORDER_MOVE_AVATAR( char tAvatarName01[13], int tPosX, int tPosY, int tPosZ )
{
	mOriginal[0] = P_SET_GM_ORDER_MOVE_AVATAR;			
	CopyMemory( &mOriginal[1], &tAvatarName01[0], 13 );
	CopyMemory( &mOriginal[14], &tPosX, 4 );	
	CopyMemory( &mOriginal[18], &tPosY, 4 );	
	CopyMemory( &mOriginal[22], &tPosZ, 4 );
	mOriginalSize = S_SET_GM_ORDER_MOVE_AVATAR;
}
//B_TRIBE_CHAT
void MyTransfer::B_TRIBE_CHAT( int tZoneNumber, int tTribe, char tAvatarName01[13], char tAvatarName02[13], char tContent[51] )
{
	mOriginal[0] = P_TRIBE_CHAT;
	CopyMemory( &mOriginal[1], &tZoneNumber, 4 );
	CopyMemory( &mOriginal[5], &tTribe, 4 );
	CopyMemory( &mOriginal[9], &tAvatarName01[0], 13 );
	CopyMemory( &mOriginal[22], &tAvatarName02[0], 13 );
	CopyMemory( &mOriginal[35], &tContent[0], 51 );
	mOriginalSize = S_TRIBE_CHAT;
}
//B_SECRET_CHAT
void MyTransfer::B_SECRET_CHAT( int tZoneNumber, int tTribe, char tAvatarName01[13], char tAvatarName02[13], char tContent[51] )
{
	mOriginal[0] = P_SECRET_CHAT;
	CopyMemory( &mOriginal[1], &tZoneNumber, 4 );
	CopyMemory( &mOriginal[5], &tTribe, 4 );
	CopyMemory( &mOriginal[9], &tAvatarName01[0], 13 );
	CopyMemory( &mOriginal[22], &tAvatarName02[0], 13 );
	CopyMemory( &mOriginal[35], &tContent[0], 51 );
	mOriginalSize = S_SECRET_CHAT;
}
//B_POLICE_INFO
void MyTransfer::B_POLICE_INFO( char tID[33], int tLoginTime, int tLogoutTime )
{
	mOriginal[0] = P_POLICE_INFO;
	CopyMemory( &mOriginal[1], &tID[0], 33 );
	CopyMemory( &mOriginal[34], &tLoginTime, 4 );
	CopyMemory( &mOriginal[38], &tLogoutTime, 4 );
	mOriginalSize = S_POLICE_INFO;
}
void MyTransfer::B_GTOZ_BAN_PLAYER (char szID[MAX_USER_ID_LENGTH])
{
    GTOZ_BAN_PLAYER pack;
    ::CopyMemory (pack.m_szID, szID, MAX_USER_ID_LENGTH - 1);

    ::CopyMemory (mOriginal, &pack, GTOZ_BAN_PLAYER_SIZE);
    mOriginalSize = GTOZ_BAN_PLAYER_SIZE;
}
//B_TOOL_FOR_CENTER_RECV
void MyTransfer::B_TOOL_FOR_CENTER_RECV( void )
{
	mOriginal[0] = P_TOOL_FOR_CENTER_RECV;
	mOriginalSize = S_TOOL_FOR_CENTER_RECV;
}
//B_TOOL_DEMAND_RESULT
void MyTransfer::B_TOOL_DEMAND_RESULT( void )
{
	mOriginal[0] = P_TOOL_DEMAND_RESULT;
	mOriginalSize = S_TOOL_DEMAND_RESULT;
}
//B_TOOL_SERCH_AVATAR_RESULT
void MyTransfer::B_TOOL_SERCH_AVATAR_RESULT( int tZoneNumber, int tGmIndex )
{
	mOriginal[0] = P_TOOL_SERCH_AVATAR_RESULT;
	CopyMemory( &mOriginal[1], &tZoneNumber, 4 );
    CopyMemory( &mOriginal[5], &tGmIndex, 4 );
	mOriginalSize = S_TOOL_SERCH_AVATAR_RESULT;
}
//B_TOOL_CHECK_EVENT_RESULT
void MyTransfer::B_TOOL_CHECK_EVENT_RESULT( int tGmIndex, int tEventSort, int tResult, int tWorldNumber, int tZoneNumber )
{
	mOriginal[0] = P_TOOL_CHECK_EVENT_RESULT;
	CopyMemory( &mOriginal[1], &tGmIndex, 4 );
	CopyMemory( &mOriginal[5], &tEventSort, 4 );
	CopyMemory( &mOriginal[9], &tResult, 4 );
	CopyMemory( &mOriginal[13], &tWorldNumber, 4 );
	CopyMemory( &mOriginal[17], &tZoneNumber, 4 );
	mOriginalSize = S_TOOL_CHECK_EVENT_RESULT;
}
//B_CHAT_TOOL_FOR_CENTER_RECV
void MyTransfer::B_CHAT_TOOL_FOR_CENTER_RECV( void )
{
	mOriginal[0] = P_CHAT_TOOL_FOR_CENTER_RECV;
	mOriginalSize = S_CHAT_TOOL_FOR_CENTER_RECV;
}
//B_POLICE_FOR_CENTER_RECV
void MyTransfer::B_POLICE_FOR_CENTER_RECV( void )
{
	mOriginal[0] = P_POLICE_FOR_CENTER_RECV;
	mOriginalSize = S_POLICE_FOR_CENTER_RECV;
}
//B_CHECK_EVENT
void MyTransfer::B_CHECK_EVENT( int tEventSort, int tUserIndex, int tGmIndex )
{
	mOriginal[0] = P_CHECK_EVENT;
	CopyMemory( &mOriginal[1], &tEventSort, 4 );
	CopyMemory( &mOriginal[5], &tUserIndex, 4 );
	CopyMemory( &mOriginal[9], &tGmIndex, 4 );
	mOriginalSize = S_CHECK_EVENT;
}

void MyTransfer::B_TOTAL_RANK_INFO_RESULT(void)
{
	//LOG_TO_FILE_3("packetSize = %d %d %d\n", packetSize, mDB.m_rank_level_size, mDB.m_rank_kill_size);
	//LOG_TO_FILE_1("==================> %d\n", mGAME.mBufferSize);
	mOriginal[0] = P_TOTAL_RANK_INFO_RECV;
	::memcpy(&mOriginal[1], &mGAME.mBuffer[0], mGAME.mBufferSize);
	mOriginalSize = mGAME.mBufferSize + 1;
}

void MyTransfer::B_RANK_INFO_RESULT(const char *aName)
{
	rank_info_t rank_info;
	char szAvatarName[MAX_AVATAR_NAME_LENGTH];
	::memset(&rank_info, 0x00, sizeof(rank_info_t));
	::memset(szAvatarName, 0x00, MAX_AVATAR_NAME_LENGTH);

	::memcpy(szAvatarName, aName, MAX_AVATAR_NAME_LENGTH);
	mOriginal[0] = P_RANK_INFO_RECV;
	::memcpy(&mOriginal[1], (const void *)&rank_info, sizeof(rank_info_t));
	::memcpy(&mOriginal[1 + sizeof(rank_info_t)], aName + MAX_AVATAR_NAME_LENGTH, 4);
	mOriginalSize = S_RANK_INFO_RECV;
}
// # X-Trap # {
// @ Cost Info Download @
void MyTransfer::B_UPDATE_CASH_ITEM_INFO_FOR_ZONE() // -> Zone
{
    mOriginal[0] = P_UPDATE_CASH_ITEM_INFO_FOR_ZONE;
    mOriginalSize = S_UPDATE_CASH_ITEM_INFO_FOR_ZONE;
}

//B_WORLD_INFO
void MyTransfer::B_CP_TOWER(CP_TOWERS* tCpTower)
{
	mOriginal[0] = P_CPTOWER;
	CopyMemory(&mOriginal[1], tCpTower, sizeof(CP_TOWERS));
	mOriginalSize = S_CPTOWER;
}// @

void MyTransfer::B_RANKPOINT(RANK_INFO* tRankPoint)
{
	mOriginal[0] = P_RankPoint;
	CopyMemory(&mOriginal[1], tRankPoint, sizeof(RANK_INFO));
	mOriginalSize = S_RankPoint;
}
void MyTransfer::B_RANKPOINTOLD(int Reset,OLD_RANK_INFO* tOldRanKPoint)
{
	mOriginal[0] = P_RankPointOld;
	CopyMemory(&mOriginal[1], &Reset, 4);
	CopyMemory(&mOriginal[5], tOldRanKPoint, sizeof(RANK_INFO));
	mOriginalSize = S_RankPointOld;
}// @
//-------------------------------------------------------------------------------------------------
