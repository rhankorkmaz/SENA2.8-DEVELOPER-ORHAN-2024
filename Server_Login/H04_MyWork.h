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
//W_LOGIN_SEND
void W_LOGIN_SEND( int tUserIndex );
//W_CLIENT_OK_FOR_LOGIN_SEND
void W_CLIENT_OK_FOR_LOGIN_SEND( int tUserIndex );
//W_CREATE_MOUSE_PASSWORD_SEND
void W_CREATE_MOUSE_PASSWORD_SEND( int tUserIndex );
//W_CHANGE_MOUSE_PASSWORD_SEND
void W_CHANGE_MOUSE_PASSWORD_SEND( int tUserIndex );
//W_LOGIN_MOUSE_PASSWORD_SEND
void W_LOGIN_MOUSE_PASSWORD_SEND( int tUserIndex );
//W_LOGIN_SECRET_CARD_SEND
void W_LOGIN_SECRET_CARD_SEND( int tUserIndex );
//W_CREATE_AVATAR_SEND
void W_CREATE_AVATAR_SEND( int tUserIndex );
//W_DELETE_AVATAR_SEND
void W_DELETE_AVATAR_SEND( int tUserIndex );
//W_CHANGE_AVATAR_NAME_SEND
void W_CHANGE_AVATAR_NAME_SEND( int tUserIndex );
//W_DEMAND_GIFT_SEND
void W_DEMAND_GIFT_SEND( int tUserIndex );
//W_WANT_GIFT_SEND
void W_WANT_GIFT_SEND( int tUserIndex );
//W_DEMAND_ZONE_SERVER_INFO_1
void W_DEMAND_ZONE_SERVER_INFO_1( int tUserIndex );
//W_FAIL_MOVE_ZONE_1_SEND
void W_FAIL_MOVE_ZONE_1_SEND( int tUserIndex );
//W_RCMD_WORLD_SEND
void W_RCMD_WORLD_SEND(int tUserIndex);
//W_EVENT_ITEM_SEND
void W_EVENT_ITEM_SEND(int tUserIndex);
//W_EVENT_ITEM_SEND
void W_RECIVE_GIFT_SEND(int tUserIndex);
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
