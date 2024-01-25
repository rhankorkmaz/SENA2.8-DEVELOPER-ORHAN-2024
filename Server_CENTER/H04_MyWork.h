//-------------------------------------------------------------------------------------------------
//MY_WORK_H
//-------------------------------------------------------------------------------------------------
#ifndef MY_WORK_H
#define MY_WORK_H
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//WORKER_FUNCTION
//-------------------------------------------------------------------------------------------------
//DEFINE
typedef struct
{
	void (*PROC)( int tUserIndex );
}
WORKER_FUNCTION;
//INSTANCE
extern WORKER_FUNCTION W_FUNCTION[256];
//-------------//
//LOGIN->CENTER//
//-------------//
//W_LOGIN_FOR_CENTER_SEND
void W_LOGIN_FOR_CENTER_SEND( int tUserIndex );
//W_LOGIN_OK_FOR_CENTER_SEND
void W_LOGIN_OK_FOR_CENTER_SEND( int tUserIndex );
//W_GET_ZONE_SERVER_INFO_1
void W_GET_ZONE_SERVER_INFO_1( int tUserIndex );
void W_BAN_PLAYER (int iUserIndex);
//------------//
//ZONE->CENTER//
//------------//
//W_ZONE_FOR_CENTER_SEND
void W_ZONE_FOR_CENTER_SEND( int tUserIndex );
//W_ZONE_OK_FOR_CENTER_SEND
void W_ZONE_OK_FOR_CENTER_SEND( int tUserIndex );
//W_DEMAND_BROADCAST_INFO
void W_DEMAND_BROADCAST_INFO( int tUserIndex );
//W_SERCH_AVATAR_SEND
void W_SERCH_AVATAR_SEND ( int tUserIndex );
//W_CHECK_EVENT_SEND
void W_CHECK_EVENT_SEND ( int tUserIndex );
//W_GET_TOTAL_RANK_INFO_SEND
void W_GET_TOTAL_RANK_INFO_SEND(int tUserIndex);
//W_GET_RANK_INFO_SEND
void W_GET_RANK_INFO_SEND(int tUserIndex);
//W_ZONE_FOR_CENTER_CONNECTION_SEND
void W_ZONE_FOR_CENTER_CONNECTION_SEND( int tUserIndex);
// @ Cost Info Download @
//W_UPDATE_CASH_ITEM_INFO_FOR_CENTER
void W_UPDATE_CASH_ITEM_INFO_FOR_CENTER( int tUserIndex );
// @

//------------//
//TOOL->CENTER//
//------------//
//W_TOOL_FOR_CENTER_SEND
void W_TOOL_FOR_CENTER_SEND( int tUserIndex );
//W_TOOL_OK_FOR_CENTER_SEND
void W_TOOL_OK_FOR_CENTER_SEND( int tUserIndex );
//W_DEMAND_START_FOR_TOOL
void W_DEMAND_START_FOR_TOOL( int tUserIndex );
//W_DEMAND_NOTICE_FOR_TOOL
void W_DEMAND_NOTICE_FOR_TOOL( int tUserIndex );
//W_DEMAND_SET_EVENT_FOR_TOOL
void W_DEMAND_SET_EVENT_FOR_TOOL( int tUserIndex );
//W_DEMAND_SHUTDOWN_FOR_TOOL
void W_DEMAND_SHUTDOWN_FOR_TOOL( int tUserIndex );
//W_DEMAND_SET_GM_ORDER_FOR_GMTOOL
void W_DEMAND_SET_GM_ORDER_FOR_GMTOOL( int tUserIndex );
//W_DEMAND_SERCH_AVATAR_FOR_GMTOOL
void W_DEMAND_SERCH_AVATAR_FOR_GMTOOL( int tUserIndex );
//W_DEMAND_SET_GM_ORDER_FOR_GMTOOL_MOVE_AVATAR
void W_DEMAND_SET_GM_ORDER_FOR_GMTOOL_MOVE_AVATAR( int tUserIndex );
//W_DEMAND_CHECK_EVENT_FOR_TOOL
void W_DEMAND_CHECK_EVENT_FOR_TOOL( int tUserIndex );
//-----------------------//
//[CHAT_TOOL] -> [CENTER]//
//-----------------------//
//W_CHAT_TOOL_FOR_CENTER_SEND
void W_CHAT_TOOL_FOR_CENTER_SEND( int tUserIndex );
//W_CHAT_TOOL_OK_FOR_CENTER_SEND
void W_CHAT_TOOL_OK_FOR_CENTER_SEND( int tUserIndex );
//W_TRIBE_CHAT_FOR_CHAT_TOOL_SEND
void W_TRIBE_CHAT_FOR_CHAT_TOOL_SEND( int tUserIndex );
//W_SECRET_CHAT_FOR_CHAT_TOOL_SEND
void W_SECRET_CHAT_FOR_CHAT_TOOL_SEND( int tUserIndex );
//--------------------//
//[POLICE] -> [CENTER]//
//--------------------//
//W_POLICE_FOR_CENTER_SEND
void W_POLICE_FOR_CENTER_SEND( int tUserIndex );
//W_POLICE_OK_FOR_CENTER_SEND
void W_POLICE_OK_FOR_CENTER_SEND( int tUserIndex );
//W_POLICE_INFO_FOR_CENTER_SEND
void W_POLICE_INFO_FOR_CENTER_SEND( int tUserIndex );
// # X-Trap # {
// W_XTRAP_MAP_FILE_CHANGE_FOR_CENTER
void W_XTRAP_MAP_FILE_CHANGE_FOR_CENTER( int tUserIndex );
// # }
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_WORK
//-------------------------------------------------------------------------------------------------
//DEFINE
class MyWork
{

public :

	int mWorkerPacketSize[256];

	MyWork( void );

	BOOL Init( void );
	void Free( void );

};
//INSTANCE
extern MyWork mWORK;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
