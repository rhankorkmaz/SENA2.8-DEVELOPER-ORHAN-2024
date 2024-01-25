//-------------------------------------------------------------------------------------------------
//MY_DB_H
//-------------------------------------------------------------------------------------------------
#ifndef MY_DB_H
#define MY_DB_H
//-------------------------------------------------------------------------------------------------
// 2008.11.18 Kim SungSoo
// Intro : 1.  Add include for DB
//-------------------------------------------------------------------------------------------------	
#include "..\include\cts_mysql.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_DB
//-------------------------------------------------------------------------------------------------
//MACRO
#define MAX_QUERY_BUFFER_SIZE										10000
//DEFINE
class MyDB
{

private :

	char mQUERY[MAX_QUERY_BUFFER_SIZE];

//-------------------------------------------------------------------------------------------------
// 2008.11.18 Kim SungSoo
// Intro : 	1.  Change DB class from win32 ado to linux c++
//					2. DB use 1DB
//-------------------------------------------------------------------------------------------------

  CMySQL mDB01;
  CMySQL mDB02;

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// 2008.11.18 Kim SungSoo
// Intro : 	1. Change DB reconnect function from win32 ado to linux c++
//					2. DB use 1DB
//-------------------------------------------------------------------------------------------------
	BOOL RECONNECT_TO_DATABASE01( void );
	
	BOOL RECONNECT_TO_DATABASE02( void );
//-------------------------------------------------------------------------------------------------

public :

	MyDB( void );

	BOOL Init( void );
	void Free( void );

	BOOL DB_PROCESS_01( char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tGuildName[MAX_GUILD_NAME_LENGTH], int tGuildRole, char tCallName[MAX_CALL_NAME_LENGTH] );
	BOOL DB_PROCESS_02( char tGuildName[MAX_GUILD_NAME_LENGTH] );
	BOOL DB_PROCESS_03( char tGuildName[MAX_GUILD_NAME_LENGTH], char tMasterName[MAX_AVATAR_NAME_LENGTH] );
	BOOL DB_PROCESS_04( char tGuildName[MAX_GUILD_NAME_LENGTH], GUILD_INFO *tGuildInfo );
	BOOL DB_PROCESS_05( char tGuildName[MAX_GUILD_NAME_LENGTH], GUILD_INFO *tGuildInfo );
	BOOL DB_PROCESS_06( char tGuildName[MAX_GUILD_NAME_LENGTH] );
	BOOL DB_PROCESS_07( char tID[MAX_USER_ID_LENGTH], int *tCash, int *tBonusCash );
	BOOL DB_PROCESS_08( char tID[MAX_USER_ID_LENGTH], int tCash, int tBonusCash );

};
//INSTANCE
extern MyDB mDB;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
