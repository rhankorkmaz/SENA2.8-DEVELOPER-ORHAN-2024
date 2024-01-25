//-------------------------------------------------------------------------------------------------
//MY_DB_H
//-------------------------------------------------------------------------------------------------
#ifndef MY_DB_H
#define MY_DB_H
#include "..\include\cts_mysql.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_DB
//-------------------------------------------------------------------------------------------------
//MACRO
#define MAX_QUERY_BUFFER_SIZE										100000
//DEFINE
class MyDB
{

private :

	char mQUERY[MAX_QUERY_BUFFER_SIZE];
	char mQUERY_FOR_THREAD[MAX_QUERY_BUFFER_SIZE];


	CMySQL mDB01;
	CMySQL mDB01_FOR_THREAD;
	CMySQL mDB02;
	CMySQL mDB02_FOR_THREAD;


	BOOL RECONNECT_TO_DATABASE01( void );
	BOOL RECONNECT_TO_DATABASE01_FOR_THREAD( void );
	BOOL RECONNECT_TO_DATABASE02( void );
	BOOL RECONNECT_TO_DATABASE02_FOR_THREAD( void );

	void MakeQueryForSave( int tSort, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO *tAvatarInfo, int tLoginPremiumPCRoom);

public :

	MyDB( void );
	BOOL Init( void );
	void Free( void );
	void DB_PROCESS_20(char aName[MAX_AVATAR_NAME_LENGTH], VALETSHOP_INFO *tValetShop, int *tResult);
	void DB_PROCESS_21(char aName[MAX_AVATAR_NAME_LENGTH], VALETSHOP_INFO* tValetShop, int* tResult);
	void DB_PROCESS_DUPE(char tID[MAX_USER_ID_LENGTH], AVATAR_INFO* tAvatarInfo, AUTH_INFO* tAuthInfo);
	void WRITE_FOR_DB_LOG_FOR_QUERY( const char* tFileName, const char* tFuncName, int tLine );
	void WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD( const char* tFileName, const char* tFuncName, int tLine );


};
//INSTANCE
extern MyDB mDB;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
