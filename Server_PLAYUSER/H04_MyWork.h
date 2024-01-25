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
//---------------//
//LOGIN->PLAYUSER//
//---------------//
//W_LOGIN_FOR_PLAYUSER_SEND
void W_LOGIN_FOR_PLAYUSER_SEND( int tUserIndex );
//W_LOGIN_OK_FOR_PLAYUSER_SEND
void W_LOGIN_OK_FOR_PLAYUSER_SEND( int tUserIndex );
//W_REGISTER_USER_FOR_LOGIN_1_SEND
void W_REGISTER_USER_FOR_LOGIN_1_SEND( int tUserIndex );
//W_REGISTER_USER_FOR_LOGIN_2_SEND
void W_REGISTER_USER_FOR_LOGIN_2_SEND( int tUserIndex );
//W_REGISTER_USER_FOR_LOGIN_3_SEND
void W_REGISTER_USER_FOR_LOGIN_3_SEND( int tUserIndex );
//W_UNREGISTER_USER_FOR_LOGIN_SEND
void W_UNREGISTER_USER_FOR_LOGIN_SEND( int tUserIndex );
//W_GET_PRESENT_USER_NUM_FOR_LOGIN_SEND
void W_GET_PRESENT_USER_NUM_FOR_LOGIN_SEND( int tUserIndex );
//W_BLOCK_USER_FOR_LOGIN_1_SEND
void W_BLOCK_USER_FOR_LOGIN_1_SEND( int tUserIndex );
//W_BLOCK_USER_FOR_LOGIN_2_SEND
void W_BLOCK_USER_FOR_LOGIN_2_SEND( int tUserIndex );
//--------------//
//ZONE->PLAYUSER//
//--------------//
//W_ZONE_FOR_PLAYUSER_SEND
void W_ZONE_FOR_PLAYUSER_SEND( int tUserIndex );
//W_ZONE_OK_FOR_PLAYUSER_SEND
void W_ZONE_OK_FOR_PLAYUSER_SEND( int tUserIndex );
//W_REGISTER_USER_FOR_ZONE_0_SEND
void W_REGISTER_USER_FOR_ZONE_0_SEND( int tUserIndex );
//W_REGISTER_USER_FOR_ZONE_1_SEND
void W_REGISTER_USER_FOR_ZONE_1_SEND( int tUserIndex );
//W_REGISTER_USER_FOR_ZONE_2_SEND
void W_REGISTER_USER_FOR_ZONE_2_SEND( int tUserIndex );
//W_REGISTER_USER_FOR_ZONE_3_SEND
void W_REGISTER_USER_FOR_ZONE_3_SEND( int tUserIndex );
//W_UNREGISTER_USER_FOR_ZONE_SEND
void W_UNREGISTER_USER_FOR_ZONE_SEND( int tUserIndex );
//W_DUPEFIX
void W_DUPEFIX(int tUserIndex);
//W_DUPEFIX1
void W_DUPEFIX1(int tUserIndex);
//W_FIND_AVATAR_FOR_ZONE_SEND
void W_FIND_AVATAR_FOR_ZONE_SEND( int tUserIndex );
//W_TRIBE_BANK_INFO_SAVE_SEND
void W_TRIBE_BANK_INFO_SAVE_SEND( int tUserIndex );
//W_TRIBE_BANK_INFO_VIEW_SEND
void W_TRIBE_BANK_INFO_VIEW_SEND( int tUserIndex );
//W_TRIBE_BANK_INFO_LOAD_SEND
void W_TRIBE_BANK_INFO_LOAD_SEND( int tUserIndex );
//W_HACK_NAME_SEND
void W_HACK_NAME_SEND( int tUserIndex );
//W_BLOCK_USER_FOR_ZONE_1_SEND
void W_BLOCK_USER_FOR_ZONE_1_SEND( int tUserIndex );
//W_BLOCK_USER_FOR_ZONE_2_SEND
void W_BLOCK_USER_FOR_ZONE_2_SEND( int tUserIndex );
//W_ADD_AUTO_USER_LIST_SEND
void W_ADD_AUTO_USER_LIST_SEND( int tUserIndex );
//W_CHECK_KILL_OTHER_TRIBE_SEND
void W_CHECK_KILL_OTHER_TRIBE_SEND( int tUserIndex );
//W_EVENT_INFO_SEND
void W_EVENT_INFO_SEND( int tUserIndex );
void W_CHECK_AUTH_KEY (int tUserIndex);
void W_UPDATE_AUTH_KEY (int tUserIndex);
//W_CHANGE_AVATAR_NAME_FOR_ZONE_SEND
void W_CHANGE_AVATAR_NAME_FOR_ZONE_SEND(int tUserIndex);
//W_BONUS_100_MONEY_FOR_ZONE_SEND
void W_BONUS_100_MONEY_FOR_ZONE_SEND(int tUserIndex);
//W_EVENT_FOR_ZONE_SEND
void W_EVENT_FOR_ZONE_SEND(int tUserIndex);
//W_SET_MOVE_ITEM_FOR_ZONE_SEND
void W_SET_MOVE_ITEM_FOR_ZONE_SEND(int tUserIndex);
//W_CHECK_PLAYER_ONLINE
void W_CHECK_PLAYER_ONLINE(int tUserIndex);
//--------------//
//TOOL->PLAYUSER//
//--------------//
//W_TOOL_FOR_PLAYUSER_SEND
void W_TOOL_FOR_PLAYUSER_SEND( int tUserIndex );
//W_TOOL_OK_FOR_PLAYUSER_SEND
void W_TOOL_OK_FOR_PLAYUSER_SEND( int tUserIndex );
//W_CHANGE_LOGIN_USER_NUM_SEND
void W_CHANGE_LOGIN_USER_NUM_SEND( int tUserIndex );
//W_CHECK_ZONE_FOR_TOOL_SEND
void W_CHECK_ZONE_FOR_TOOL_SEND( int tUserIndex );
//W_GET_PRESENT_USER_NUM_FOR_TOOL_SEND
void W_GET_PRESENT_USER_NUM_FOR_TOOL_SEND( int tUserIndex );
//W_FIND_AVATAR_FOR_TOOL_SEND
void W_FIND_AVATAR_FOR_TOOL_SEND( int tUserIndex );
//W_FIND_USER_FOR_TOOL_SEND
void W_FIND_USER_FOR_TOOL_SEND( int tUserIndex );
//W_BLOCK_USER_FOR_TOOL_1_SEND
void W_BLOCK_USER_FOR_TOOL_1_SEND( int tUserIndex );
//W_BLOCK_USER_FOR_TOOL_2_SEND
void W_BLOCK_USER_FOR_TOOL_2_SEND( int tUserIndex );
//W_GET_PRESENT_USER_NUM_2_FOR_TOOL_SEND
void W_GET_PRESENT_USER_NUM_2_FOR_TOOL_SEND( int tUserIndex );
//----------------------//
//[POLICE] -> [PLAYUSER]//
//----------------------//
//W_POLICE_FOR_PLAYUSER_SEND
void W_POLICE_FOR_PLAYUSER_SEND( int tUserIndex );
//W_POLICE_OK_FOR_PLAYUSER_SEND
void W_POLICE_OK_FOR_PLAYUSER_SEND( int tUserIndex );
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
