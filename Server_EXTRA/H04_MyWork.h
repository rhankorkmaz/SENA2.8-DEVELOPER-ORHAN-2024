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
//W_ZONE_FOR_EXTRA_SEND
void W_ZONE_FOR_EXTRA_SEND( int tUserIndex );
//W_ZONE_OK_FOR_EXTRA_SEND
void W_ZONE_OK_FOR_EXTRA_SEND( int tUserIndex );
//W_GUILD_WORK_FOR_EXTRA_SEND
void W_GUILD_WORK_FOR_EXTRA_SEND( int tUserIndex );
//W_GET_CASH_SIZE_FOR_EXTRA_SEND
void W_GET_CASH_SIZE_FOR_EXTRA_SEND( int tUserIndex );
//W_BUY_CASH_ITEM_FOR_EXTRA_SEND
void W_BUY_CASH_ITEM_FOR_EXTRA_SEND( int tUserIndex );
// @ Cost Info Download @
//W_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_SEND
void W_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_SEND( int tUserIndex );
//W_GET_CASH_ITEM_INFO_FOR_EXTRA_SEND
void W_GET_CASH_ITEM_INFO_FOR_EXTRA_SEND( int tUserIndex );
// @
//W_USE_PACKAGE_ITEM_FOR_EXTRA_SEND
void W_USE_PACKAGE_ITEM_FOR_EXTRA_SEND( int tUserIndex );
//W_USE_PACKAGE_ITEM_FOR_EXTRA_SEND
void W_BLOOD_ITEM_INFO(int tUserIndex);
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
