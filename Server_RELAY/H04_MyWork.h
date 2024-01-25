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
using namespace std;
typedef struct
{
	void (*PROC)( int tUserIndex );
}
WORKER_FUNCTION;

typedef struct
{
	char mPartyAvatarName[5][MAX_AVATAR_NAME_LENGTH];
} party_list;

//INSTANCE
extern WORKER_FUNCTION W_FUNCTION[256];
//W_ZONE_FOR_RELAY_SEND
void W_ZONE_FOR_RELAY_SEND( int tUserIndex );
//W_ZONE_OK_FOR_RELAY_SEND
void W_ZONE_OK_FOR_RELAY_SEND( int tUserIndex );
//W_DEMAND_BROADCAST_DATA
void W_DEMAND_BROADCAST_DATA( int tUserIndex );
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_WORK
//-------------------------------------------------------------------------------------------------
//DEFINE
class MyWork
{

public :

	int mWorkerPacketSize[256];

#ifdef __PARTY_VER_2__
	map<string, party_list> map_party_list;
#endif


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
