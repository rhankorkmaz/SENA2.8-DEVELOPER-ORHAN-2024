//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "Shengming.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_WORK
//-------------------------------------------------------------------------------------------------
//INSTANCE
MyWork mWORK;
//CREATE
MyWork::MyWork( void )
{
}
//INIT
BOOL MyWork::Init( void )
{
	int index01;

	for( index01 = 0 ; index01 < 256 ; index01++ )
	{
		W_FUNCTION[index01].PROC = NULL;
	}
	//W_ZONE_FOR_RELAY_SEND
	mWorkerPacketSize[P_ZONE_FOR_RELAY_SEND] = S_ZONE_FOR_RELAY_SEND;
	W_FUNCTION[P_ZONE_FOR_RELAY_SEND].PROC = W_ZONE_FOR_RELAY_SEND;
	//W_ZONE_OK_FOR_RELAY_SEND
	mWorkerPacketSize[P_ZONE_OK_FOR_RELAY_SEND] = S_ZONE_OK_FOR_RELAY_SEND;
	W_FUNCTION[P_ZONE_OK_FOR_RELAY_SEND].PROC = W_ZONE_OK_FOR_RELAY_SEND;
	//W_DEMAND_BROADCAST_DATA
	mWorkerPacketSize[P_DEMAND_BROADCAST_DATA] = S_DEMAND_BROADCAST_DATA;
	W_FUNCTION[P_DEMAND_BROADCAST_DATA].PROC = W_DEMAND_BROADCAST_DATA;
	return TRUE;
}
//FREE
void MyWork::Free( void )
{
}
//-------------------------------------------------------------------------------------------------
