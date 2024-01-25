//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "Shengming.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_DB
//-------------------------------------------------------------------------------------------------
//INSTANCE
MyDB mDB;
//CREATE
MyDB::MyDB( void )
{
}
//INIT
BOOL MyDB::Init( void )
{
	//-------------------------------------------------------------------------------------------------
	// 2008.11.18 Kim SungSoo
	// Intro : 	1. Change DB connecttion string and process from win32 ado to linux c++
	//-------------------------------------------------------------------------------------------------

	if(mDB01.set_db_conn_info(mSERVER_INFO.mDB_1_IP, mSERVER_INFO.mDB_1_IP, mSERVER_INFO.mDB_1_PORT
		,"ts2_gamedb", mSERVER_INFO.mDB_1_ID, mSERVER_INFO.mDB_1_PASSWORD) < 0) {
			return FALSE;
		}
		if(!mDB01.connect()) {
			return FALSE;
		}

		if(mDB02.set_db_conn_info(mSERVER_INFO.mDB2_1_IP, mSERVER_INFO.mDB2_1_IP, mSERVER_INFO.mDB2_1_PORT
			, "ts2_gamedb", mSERVER_INFO.mDB2_1_ID, mSERVER_INFO.mDB2_1_PASSWORD) < 0) {
				return FALSE;
			}
			if(!mDB02.connect()) {
				return FALSE;
			}

			//-------------------------------------------------------------------------------------------------
			return TRUE;
}
//FREE
void MyDB::Free( void )
{
	//-------------------------------------------------------------------------------------------------
	// 2008.11.18 Kim SungSoo
	// Intro : 	1. Delete win32 api for com+
	//-------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------

}
//RECONNECT_TO_DATABASE01
BOOL MyDB::RECONNECT_TO_DATABASE01( void )
{
	if( mDB01.IsConnected() )
	{
		return TRUE;
	}

	// 2008.11.19 Kim SungSoo : Add log for call reconnection
	__LogMgr()->Log("[%s] DB reonnection call! \n" , __FUNCTION__);

	if( !mDB01.Reconnect() )
	{
		// 2008.11.19 Kim SungSoo : Add log for reconnect false
		__LogMgr()->Log("[%s] DB reonnection false! \n" , __FUNCTION__);
		return FALSE;
	}
	return TRUE;
}
//RECONNECT_TO_DATABASE02
//-------------------------------------------------------------------------------------------------
// 2008.11.18 Kim SungSoo
// Intro : 	1. Delete mDB2 (use 1DB)
//-------------------------------------------------------------------------------------------------
BOOL MyDB::RECONNECT_TO_DATABASE02( void )
{
	if( mDB02.IsConnected() )
	{
		return TRUE;
	}
	if( !mDB02.Reconnect() )
	{
		return FALSE;
	}
	return TRUE;
}
//-------------------------------------------------------------------------------------------------

//DB_PROCESS_01
BOOL MyDB::DB_PROCESS_01( char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tGuildName[MAX_GUILD_NAME_LENGTH], int tGuildRole, char tCallName[MAX_CALL_NAME_LENGTH] )
{
	int iAffected;

	sprintf( mQUERY, "update %s set aGuildName='%s',aGuildRole=%d,aCallName='%s' where aName='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_2_Table01, tGuildName, tGuildRole, tCallName, tAvatarName, g_env.world_num );
	if( !RECONNECT_TO_DATABASE01() )
	{
		return FALSE;
	}
	iAffected = 0;

	//-------------------------------------------------------------------------------------------------
	// 2008.11.18 Kim SungSoo
	// Intro : 	1. Change DB connecttion string and process from win32 ado to linux c++
	//-------------------------------------------------------------------------------------------------

	if(mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) 
	{
		// 2008.11.19 Kim SungSoo : Add log for execute query false
		__LogMgr()->Log("[%s] Query execute false : %s! \n" , __FUNCTION__ , mQUERY);

		return FALSE;
	}

	//-------------------------------------------------------------------------------------------------

	return TRUE;
}

//DB_PROCESS_02
BOOL MyDB::DB_PROCESS_02( char tGuildName[MAX_GUILD_NAME_LENGTH] )
{
	int iAffected;
	int iCounts;
	long gNameNum;
	MYSQL_ROW row;
	MYSQL_RES *res = NULL;

	sprintf( mQUERY, "select count(gName) from %s where gName='%s' AND aWorldNumber = %d ", mSERVER_INFO.mDB_2_Table02, tGuildName , g_env.world_num);
	if( !RECONNECT_TO_DATABASE01() )
	{
		return FALSE;
	}
	iAffected = 0;

	//-------------------------------------------------------------------------------------------------
	// 2008.11.18 Kim SungSoo
	// Intro : 	1. Change DB connecttion string and process from win32 ado to linux c++
	//-------------------------------------------------------------------------------------------------

	if((iAffected = mDB01.exec_query(mQUERY)) < 0) {
		// 2008.11.19 Kim SungSoo : Add log for execute query false
		__LogMgr()->Log("![%s] Query execute false : %s! \n" , __FUNCTION__ , mQUERY);
		return false;
	}

	iCounts = 0;
	res = mDB01.get_res();
	if(res == NULL)
		return false;
	while (row = mysql_fetch_row(res)){
		gNameNum = atoi(row[ 0 ]);
		++iCounts;
	}
	mDB01.clear_res();
	if (1 != iCounts){
		return false;
	}
	//-------------------------------------------------------------------------------------------------
	if( gNameNum != 0 )
	{
		return FALSE;
	}
	return TRUE;
}

//DB_PROCESS_03
BOOL MyDB::DB_PROCESS_03( char tGuildName[MAX_GUILD_NAME_LENGTH], char tMasterName[MAX_AVATAR_NAME_LENGTH] )
{
	int iAffected;
	char gMember[851];	

	//-------------------------------------------------------------------------------------------------
	// 2008.11.18 Kim SungSoo
	// Intro : 	1. Change DB connecttion string and process from win32 ado to linux c++
	//-------------------------------------------------------------------------------------------------

	memset(&gMember[0] , '@' , 850);

	//-------------------------------------------------------------------------------------------------


	CopyMemory( &gMember[0], &tMasterName[0], strlen( tMasterName ) );
	gMember[12] = '0';
	gMember[850] = '\0';
	sprintf( mQUERY, "insert into %s values (now() , %d ,'%s',1,'%s','','','%s','','','','',0,0,0,0,0 )", mSERVER_INFO.mDB_2_Table02, g_env.world_num, tGuildName, tMasterName, gMember );
	if( !RECONNECT_TO_DATABASE01() )
	{
		return FALSE;
	}
	iAffected = 0;
	//-------------------------------------------------------------------------------------------------
	// 2008.11.18 Kim SungSoo
	// Intro : 	1. Change DB connecttion string and process from win32 ado to linux c++
	//-------------------------------------------------------------------------------------------------

	if(mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) 
	{
		// 2008.11.19 Kim SungSoo : Add log for execute query false
		__LogMgr()->Log("[%s] Query execute false : %s! \n" , __FUNCTION__ , mQUERY);
		return FALSE;
	}

	//-------------------------------------------------------------------------------------------------

	return TRUE;
}

//DB_PROCESS_04
BOOL MyDB::DB_PROCESS_04( char tGuildName[MAX_GUILD_NAME_LENGTH], GUILD_INFO *tGuildInfo )
{
	int index01;
	int index02;
	int iAffected;
	int iCounts;
	char gName[MAX_GUILD_NAME_LENGTH];
	long gGrade;
	char gMaster01[MAX_AVATAR_NAME_LENGTH];
	char gSubMaster01[MAX_AVATAR_NAME_LENGTH];
	char gSubMaster02[MAX_AVATAR_NAME_LENGTH];
	char gMember[851];
	char gNotice01[MAX_GUILD_NOTICE_LENGTH];
	char gNotice02[MAX_GUILD_NOTICE_LENGTH];
	char gNotice03[MAX_GUILD_NOTICE_LENGTH];
	char gNotice04[MAX_GUILD_NOTICE_LENGTH];
	int GuldPoint;
	int GuldPoint1;
	int GuildTime;
	int GuildTime1;
	int GuildTime2;

	// DB value pointer
	//char *pDBValue = NULL;
	MYSQL_ROW row;
	MYSQL_RES *res;

	sprintf( mQUERY, "select gName,gGrade,gMaster01,gSubMaster01,gSubMaster02,gMember,gNotice01,gNotice02,gNotice03,gNotice04,GuldPoint,GuldPoint1,GuildTime,GuildTime1,GuildTime2 from %s where gName='%s' AND aWorldNumber = %d"
		, mSERVER_INFO.mDB_2_Table02, tGuildName ,  g_env.world_num );
	if( !RECONNECT_TO_DATABASE01() )
	{
		return FALSE;
	}
	iAffected = 0;


	//-------------------------------------------------------------------------------------------------
	// 2008.11.18 Kim SungSoo
	// Intro : 	1. Change DB connecttion string and process from win32 ado to linux c++
	//-------------------------------------------------------------------------------------------------

	if((iAffected = mDB01.exec_query(mQUERY)) < 0) {
		//2008.11.20 Kim SungSoo : Add log for execute query false
		__LogMgr()->Log("![%s] : exec_query fail %s\n", __FUNCTION__, mQUERY);
		return false;
	}
	iCounts = 0;

	res = mDB01.get_res();
	if(res == NULL) {
		return false;
	}
	while (row = mysql_fetch_row(res)){
		strncpy(gName, row[ 0 ], MAX_GUILD_NAME_LENGTH);
		gGrade = ::atol(row[ 1 ]);
		strncpy(gMaster01, row[ 2 ], MAX_AVATAR_NAME_LENGTH);
		strncpy(gSubMaster01, row[ 3 ], MAX_AVATAR_NAME_LENGTH);
		strncpy(gSubMaster02, row[ 4 ], MAX_AVATAR_NAME_LENGTH);
		strncpy(gMember, row[ 5 ], 851);
		strncpy(gNotice01, row[ 6 ], MAX_GUILD_NOTICE_LENGTH);
		strncpy(gNotice02, row[ 7 ], MAX_GUILD_NOTICE_LENGTH);
		strncpy(gNotice03, row[ 8 ], MAX_GUILD_NOTICE_LENGTH);
		strncpy(gNotice04, row[ 9 ], MAX_GUILD_NOTICE_LENGTH);
		GuldPoint = ::atol(row[10]);
		GuldPoint1 = ::atol(row[11]);
		GuildTime = ::atol(row[12]);
		GuildTime1 = ::atol(row[13]);
		GuildTime2 = ::atol(row[14]);
		++iCounts;
	}
	mDB01.clear_res();
	if (1 != iCounts){
		return false;
	}

	//-------------------------------------------------------------------------------------------------


	strcpy( tGuildInfo->gName, gName );
	tGuildInfo->gGrade = gGrade;
	strcpy( tGuildInfo->gMaster01, gMaster01 );
	strcpy( tGuildInfo->gSubMaster01, gSubMaster01 );
	strcpy( tGuildInfo->gSubMaster02, gSubMaster02 );
	for( index01 = 0 ; index01 < MAX_GUILD_AVATAR_NUM ; index01++ )
	{
		CopyMemory( &tGuildInfo->gMemberName[index01][0], &gMember[( index01 * 17 + 0 )], 12 );
		for( index02 = 0 ; index02 < 12 ; index02++ )
		{
			if (::IsDBCSLeadByte (tGuildInfo->gMemberName[index01][index02]) == TRUE) {
				if (index02 != 11) index02++;
				continue;
			}

			if( tGuildInfo->gMemberName[index01][index02] == '@' )
			{
				break;
			}
		}
		tGuildInfo->gMemberName[index01][index02] = '\0';
		if( gMember[( index01 * 17 + 12 )] != '@' )
		{
			tGuildInfo->gMemberRole[index01] = gMember[( index01 * 17 + 12 )] - '0';
		}
		else
		{
			tGuildInfo->gMemberRole[index01] = 0;
		}
		CopyMemory( &tGuildInfo->gMemberCall[index01][0], &gMember[( index01 * 17 + 13 )], 4 );
		for( index02 = 0 ; index02 < 4 ; index02++ )
		{
			if (::IsDBCSLeadByte (tGuildInfo->gMemberCall[index01][index02]) == TRUE) {
				if (index02 != 3) index02++;
				continue;
			}

			if( tGuildInfo->gMemberCall[index01][index02] == '@' )
			{
				break;
			}
		}
		tGuildInfo->gMemberCall[index01][index02] = '\0';
	}
	strcpy( tGuildInfo->gNotice[0], gNotice01 );
	strcpy( tGuildInfo->gNotice[1], gNotice02 );
	strcpy( tGuildInfo->gNotice[2], gNotice03 );
	strcpy( tGuildInfo->gNotice[3], gNotice04 );
	tGuildInfo->GuldPoint = GuldPoint;
	tGuildInfo->GuldPoint1 = GuldPoint1;
	tGuildInfo->GuildTime = GuildTime;
	tGuildInfo->GuildTime1 = GuildTime1;
	tGuildInfo->GuildTime2 = GuildTime2;
	return TRUE;
}

//DB_PROCESS_05
BOOL MyDB::DB_PROCESS_05( char tGuildName[MAX_GUILD_NAME_LENGTH], GUILD_INFO *tGuildInfo )
{
	int index01;
	int iAffected;
	char gMember[851];

	//-------------------------------------------------------------------------------------------------
	// 2008.11.18 Kim SungSoo
	// Intro : 	1. Change DB connecttion string and process from win32 ado to linux c++
	//-------------------------------------------------------------------------------------------------

	memset(&gMember[0] , '@' , 850);
	for( index01 = 0 ; index01 < MAX_GUILD_AVATAR_NUM ; index01++ )
	{
		if( strcmp( tGuildInfo->gMemberName[index01], "" ) == 0 )
		{
			continue;
		}
		CopyMemory( &gMember[( index01 * 17 + 0 )], &tGuildInfo->gMemberName[index01][0], strlen( tGuildInfo->gMemberName[index01] ) );
		gMember[( index01 * 17 + 12 )] = tGuildInfo->gMemberRole[index01] + '0';
		CopyMemory( &gMember[( index01 * 17 + 13 )], &tGuildInfo->gMemberCall[index01][0], strlen( tGuildInfo->gMemberCall[index01] ) );
	}
	gMember[850] = '\0';
	sprintf( mQUERY, "update %s set gGrade=%d,gSubMaster01='%s',gSubMaster02='%s',gMember='%s',gNotice01='%s',gNotice02='%s'\
					 ,gNotice03='%s',gNotice04='%s',GuldPoint=%d,GuldPoint1=%d,GuildTime=%d,GuildTime1=%d,GuildTime2=%d where gName='%s' AND aWorldNumber = %d "
					 , mSERVER_INFO.mDB_2_Table02, tGuildInfo->gGrade, tGuildInfo->gSubMaster01, tGuildInfo->gSubMaster02, gMember, tGuildInfo->gNotice[0]
					 , tGuildInfo->gNotice[1], tGuildInfo->gNotice[2], tGuildInfo->gNotice[3], tGuildInfo->GuildTime, tGuildInfo->GuildTime1, tGuildInfo->GuildTime, tGuildInfo->GuildTime1, tGuildInfo->GuildTime2,tGuildInfo->gName  , g_env.world_num);
					 if( !RECONNECT_TO_DATABASE01() )
					 {
						 return FALSE;
					 }
					 iAffected = 0;

					 //-------------------------------------------------------------------------------------------------
					 // 2008.11.18 Kim SungSoo
					 // Intro : 	1. Change DB connecttion string and process from win32 ado to linux c++
					 //-------------------------------------------------------------------------------------------------
#ifdef __WIN32__	
					 if( !mDB02.Execute( mQUERY, iAffected ) )
					 {

						 return FALSE;
					 }
#else
					 if(mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) 
					 {
						 //2008.11.20 Kim SungSoo : Add log for execute query false
						 __LogMgr()->Log("![%s] : exec_query fail %s\n", __FUNCTION__, mQUERY);
						 return FALSE;
					 }
#endif
					 //-------------------------------------------------------------------------------------------------

					 return TRUE;
}

//DB_PROCESS_06
BOOL MyDB::DB_PROCESS_06( char tGuildName[MAX_GUILD_NAME_LENGTH] )
{
	int iAffected;

	sprintf( mQUERY, "delete from %s where gName='%s' AND aWorldNumber = %d ", mSERVER_INFO.mDB_2_Table02, tGuildName , g_env.world_num );
	if( !RECONNECT_TO_DATABASE01() )
	{
		return FALSE;
	}
	iAffected = 0;
	//-------------------------------------------------------------------------------------------------
	// 2008.11.18 Kim SungSoo
	// Intro : 	1. Change DB connecttion string and process from win32 ado to linux c++
	//-------------------------------------------------------------------------------------------------
#ifdef __WIN32__	
	if( !mDB02.Execute( mQUERY, iAffected ) )
	{
		return FALSE;
	}
#else
	if(mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) 
	{
		//2008.11.20 Kim SungSoo : Add log for execute query false
		__LogMgr()->Log("![%s] : exec_query fail %s\n", __FUNCTION__, mQUERY);
		return FALSE;
	}
#endif
	//-------------------------------------------------------------------------------------------------
	return TRUE;
}

//DB_PROCESS_07
BOOL MyDB::DB_PROCESS_07( char tID[MAX_USER_ID_LENGTH], int *tCash, int *tBonusCash )
{
	int iAffected;
	int iCounts;
	MYSQL_ROW row;
	MYSQL_RES *res;

	sprintf( mQUERY, 
		"SELECT uCash, uBonusCash "
		"FROM %s "
		"WHERE uID='%s'", mSERVER_INFO.mDB2_1_Table01, tID );
	//__LogMgr()->Log(mQUERY);
	if( !RECONNECT_TO_DATABASE02() )
	{
		return FALSE;
	}
	iAffected = 0;

	if((iAffected = mDB02.exec_query(mQUERY)) < 0) 
	{
		//2008.11.20 Kim SungSoo : Add log for execute query false
		__LogMgr()->Log("![%s] : exec_query fail %s\n", __FUNCTION__, mQUERY);
		return false;
	}
	iCounts = 0;

	res = mDB02.get_res();
	if(res == NULL)
	{
		return false;
	}
	while (row = mysql_fetch_row(res))
	{
		*tCash = atol(row[0]);
		*tBonusCash = atol(row[1]);
		++iCounts;
	}
	mDB02.clear_res();
	if (1 != iCounts){
		return FALSE;
	}

	return TRUE;
}

//DB_PROCESS_08
BOOL MyDB::DB_PROCESS_08( char tID[MAX_USER_ID_LENGTH], int tCash, int tBonusCash )
{
	int iAffected;

	sprintf( mQUERY, 
		"update %s "
		"SET uCash = uCash + %d, uBonusCash = uBonusCash + %d "
		"WHERE uID='%s'", mSERVER_INFO.mDB2_1_Table01, tCash, tBonusCash, tID );

	if( !RECONNECT_TO_DATABASE02() )
	{
		return FALSE;
	}
	iAffected = 0;
	//-------------------------------------------------------------------------------------------------
	// 2008.11.18 Kim SungSoo
	// Intro : 	1. Change DB connecttion string and process from win32 ado to linux c++
	//-------------------------------------------------------------------------------------------------
#ifdef __WIN32__	
	if( !mDB02.Execute( mQUERY, iAffected ) )
	{
		return FALSE;
	}
#else
	if(mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) 
	{
		//2008.11.20 Kim SungSoo : Add log for execute query false
		__LogMgr()->Log("![%s] : exec_query fail %s\n", __FUNCTION__, mQUERY);
		return FALSE;
	}

#endif
	//-------------------------------------------------------------------------------------------------
	return TRUE;
}
//-------------------------------------------------------------------------------------------------
