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
//ZONE->PLAYUSER//
//--------------//
//W_ZONE_FOR_PLAYUSER_SEND
void W_ZONE_FOR_VALET_SEND( int tUserIndex );
//W_ZONE_OK_FOR_PLAYUSER_SEND
void W_ZONE_OK_FOR_VALET_SEND( int tUserIndex );
//W_DUPEFIX
void W_VALET_DUPEFIX(int tUserIndex);
//W_DUPEFIX1
void W_VALET_DUPEFIX1(int tUserIndex);
//W_VALET_SHOP_INFO
void W_VALET_SHOP_INFO(int tUserIndex);
//W_VALET_SHOP_UPDATE
void W_VALET_SHOP_UPDATE(int tUserIndex);
//W_VALET_SHOP_BUY
void W_VALET_SHOP_BUY(int tUserIndex);
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
