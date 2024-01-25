//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "Shengming.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//WORKER_FUNCTION
//-------------------------------------------------------------------------------------------------
//INSTANCE
WORKER_FUNCTION W_FUNCTION[256];
//W_ZONE_FOR_EXTRA_SEND
void W_ZONE_FOR_EXTRA_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 0 )
	{
		mUSER[tUserIndex].Quit( 4001 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tZoneNumber;
	CopyMemory( &tZoneNumber, &tPacket[1], 4 );

	if( ( tZoneNumber < MIN_VALID_ZONE_NUMBER ) || ( tZoneNumber > MAX_VALID_ZONE_NUMBER ) )
	{
		mUSER[tUserIndex].Quit( 4002 );
		return;
	}

	int index01;

	for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
	{
		if( ( mUSER[index01].mCheckServerType == 2 ) && ( mUSER[index01].mZoneServerNumber == tZoneNumber ) )
		{
			mUSER[index01].Quit( 4003 );
		}
	}
	mUSER[tUserIndex].mCheckServerType = 2;
	mUSER[tUserIndex].mZoneServerNumber = tZoneNumber;
	// @ Cost Info Download @
	mTRANSFER.B_ZONE_FOR_EXTRA_RECV(mGAME.mCashItemInfoVersion, mGAME.mCashItemInfo);
	// @
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_ZONE_OK_FOR_EXTRA_SEND
void W_ZONE_OK_FOR_EXTRA_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 2 )
	{
		mUSER[tUserIndex].Quit( 4004 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();
}
//W_GUILD_WORK_FOR_EXTRA_SEND
void W_GUILD_WORK_FOR_EXTRA_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 2 )
	{
		mUSER[tUserIndex].Quit( 4005 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tSort;
	BYTE tData[MAX_GUILD_WORK_SIZE];
	CopyMemory( &tSort, &tPacket[1], 4 );
	CopyMemory( &tData[0], &tPacket[5], MAX_GUILD_WORK_SIZE );

	int index01;
	GUILD_INFO tGuildInfo1;
	GUILD_INFO tGuildInfo2;
	int tTotalMemberNum;
	char tGuildName[MAX_GUILD_NAME_LENGTH];
	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	char tGuildNotice01[MAX_GUILD_NOTICE_LENGTH];
	char tGuildNotice02[MAX_GUILD_NOTICE_LENGTH];
	char tGuildNotice03[MAX_GUILD_NOTICE_LENGTH];
	char tGuildNotice04[MAX_GUILD_NOTICE_LENGTH];
	int tGuildRole;
	char tCallName[MAX_CALL_NAME_LENGTH];

	switch( tSort )
	{
	case  1 : //[Ã¢¼³]
		CopyMemory( &tGuildName[0], &tData[0], MAX_GUILD_NAME_LENGTH );
		tGuildName[( MAX_GUILD_NAME_LENGTH - 1 )] = '\0';
		CopyMemory( &tAvatarName[0], &tData[MAX_GUILD_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH );
		tAvatarName[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';
		if( !mDB.DB_PROCESS_02( &tGuildName[0] ) )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 2, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( !mDB.DB_PROCESS_03( &tGuildName[0], &tAvatarName[0] ) )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( !mDB.DB_PROCESS_01( &tAvatarName[0], &tGuildName[0], 0, "" ) )
		{
			mDB.DB_PROCESS_06( &tGuildName[0] );
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 0, &tGuildInfo1 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case  2 : //[Á¤º¸]
		CopyMemory( &tGuildName[0], &tData[0], MAX_GUILD_NAME_LENGTH );
		tGuildName[( MAX_GUILD_NAME_LENGTH - 1 )] = '\0';
		if( !mDB.DB_PROCESS_04( &tGuildName[0], &tGuildInfo1 ) )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 0, &tGuildInfo1 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case  3 : //[°¡ÀÔ]
		CopyMemory( &tGuildName[0], &tData[0], MAX_GUILD_NAME_LENGTH );
		tGuildName[( MAX_GUILD_NAME_LENGTH - 1 )] = '\0';
		CopyMemory( &tAvatarName[0], &tData[MAX_GUILD_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH );
		tAvatarName[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';
		if( !mDB.DB_PROCESS_04( &tGuildName[0], &tGuildInfo1 ) )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		CopyMemory( &tGuildInfo2, &tGuildInfo1, sizeof( GUILD_INFO ) );
		tTotalMemberNum = 0;
		for( index01 = 0 ; index01 < MAX_GUILD_AVATAR_NUM ; index01++ )
		{
			if( strcmp( tGuildInfo1.gMemberName[index01], "" ) != 0 )
			{
				tTotalMemberNum++;
			}
		}
		if( tTotalMemberNum >= ( tGuildInfo1.gGrade * 10 ) )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		for( index01 = 0 ; index01 < MAX_GUILD_AVATAR_NUM ; index01++ )
		{
			if( strcmp( tGuildInfo1.gMemberName[index01], tAvatarName ) == 0 )
			{
				break;
			}
		}
		if( index01 < MAX_GUILD_AVATAR_NUM )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		for( index01 = 0 ; index01 < MAX_GUILD_AVATAR_NUM ; index01++ )
		{
			if( strcmp( tGuildInfo1.gMemberName[index01], "" ) == 0 )
			{
				break;
			}
		}
		if( index01 == MAX_GUILD_AVATAR_NUM )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		strcpy( tGuildInfo1.gMemberName[index01], tAvatarName );
		tGuildInfo1.gMemberRole[index01] = 2;
		strcpy( tGuildInfo1.gMemberCall[index01], "" );
		if( !mDB.DB_PROCESS_05( &tGuildName[0], &tGuildInfo1 ) )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( !mDB.DB_PROCESS_01( &tAvatarName[0], &tGuildName[0], 2, "" ) )
		{
			mDB.DB_PROCESS_05( &tGuildName[0], &tGuildInfo2 );
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 0, &tGuildInfo1 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case  4 : //[Å»Åð]
		CopyMemory( &tGuildName[0], &tData[0], MAX_GUILD_NAME_LENGTH );
		tGuildName[( MAX_GUILD_NAME_LENGTH - 1 )] = '\0';
		CopyMemory( &tAvatarName[0], &tData[MAX_GUILD_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH );
		tAvatarName[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';
		if( !mDB.DB_PROCESS_04( &tGuildName[0], &tGuildInfo1 ) )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		CopyMemory( &tGuildInfo2, &tGuildInfo1, sizeof( GUILD_INFO ) );
		if( strcmp( tGuildInfo1.gMaster01, tAvatarName ) == 0 )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		for( index01 = 0 ; index01 < MAX_GUILD_AVATAR_NUM ; index01++ )
		{
			if( strcmp( tGuildInfo1.gMemberName[index01], tAvatarName ) == 0 )
			{
				break;
			}
		}
		if( strcmp( tGuildInfo1.gSubMaster01, tAvatarName ) == 0 )
		{
			strcpy( tGuildInfo1.gSubMaster01, "" );
		}
		if( strcmp( tGuildInfo1.gSubMaster02, tAvatarName ) == 0 )
		{
			strcpy( tGuildInfo1.gSubMaster02, "" );
		}
		tGuildInfo1.gMemberRole[index01] = 0;
		if( index01 == MAX_GUILD_AVATAR_NUM )
		{
			mDB.DB_PROCESS_01( &tAvatarName[0], "", 0, "" );
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 0, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		strcpy( tGuildInfo1.gMemberName[index01], "" );
		strcpy( tGuildInfo1.gMemberCall[index01], "" );
		if( !mDB.DB_PROCESS_05( &tGuildName[0], &tGuildInfo1 ) )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( !mDB.DB_PROCESS_01( &tAvatarName[0], "", 0, "" ) )
		{
			mDB.DB_PROCESS_05( &tGuildName[0], &tGuildInfo2 );
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 0, &tGuildInfo1 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case  5 : //[¾Ë¸²]
		CopyMemory( &tGuildName[0], &tData[0], MAX_GUILD_NAME_LENGTH );
		tGuildName[( MAX_GUILD_NAME_LENGTH - 1 )] = '\0';
		CopyMemory( &tGuildNotice01[0], &tData[MAX_GUILD_NAME_LENGTH], MAX_GUILD_NOTICE_LENGTH );
		tGuildNotice01[( MAX_GUILD_NOTICE_LENGTH - 1 )]='\0';
		CopyMemory( &tGuildNotice02[0], &tData[( MAX_GUILD_NAME_LENGTH + MAX_GUILD_NOTICE_LENGTH )], MAX_GUILD_NOTICE_LENGTH );
		tGuildNotice02[( MAX_GUILD_NOTICE_LENGTH - 1 )]='\0';
		CopyMemory( &tGuildNotice03[0], &tData[( MAX_GUILD_NAME_LENGTH + MAX_GUILD_NOTICE_LENGTH + MAX_GUILD_NOTICE_LENGTH )], MAX_GUILD_NOTICE_LENGTH );
		tGuildNotice03[( MAX_GUILD_NOTICE_LENGTH - 1 )]='\0';
		CopyMemory( &tGuildNotice04[0], &tData[( MAX_GUILD_NAME_LENGTH + MAX_GUILD_NOTICE_LENGTH + MAX_GUILD_NOTICE_LENGTH + MAX_GUILD_NOTICE_LENGTH )], MAX_GUILD_NOTICE_LENGTH );
		tGuildNotice04[( MAX_GUILD_NOTICE_LENGTH - 1 )]='\0';
		if( !mDB.DB_PROCESS_04( &tGuildName[0], &tGuildInfo1 ) )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		strcpy( tGuildInfo1.gNotice[0], tGuildNotice01 );
		strcpy( tGuildInfo1.gNotice[1], tGuildNotice02 );
		strcpy( tGuildInfo1.gNotice[2], tGuildNotice03 );
		strcpy( tGuildInfo1.gNotice[3], tGuildNotice04 );
		if( !mDB.DB_PROCESS_05( &tGuildName[0], &tGuildInfo1 ) )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 0, &tGuildInfo1 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case  6 : //[ÇØ»ê]
		CopyMemory( &tGuildName[0], &tData[0], MAX_GUILD_NAME_LENGTH );
		tGuildName[( MAX_GUILD_NAME_LENGTH - 1 )] = '\0';
		CopyMemory( &tAvatarName[0], &tData[MAX_GUILD_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH );
		tAvatarName[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';
		if( !mDB.DB_PROCESS_04( &tGuildName[0], &tGuildInfo1 ) )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( strcmp( tGuildInfo1.gMaster01, tAvatarName ) != 0 )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		tTotalMemberNum = 0;
		for( index01 = 0 ; index01 < MAX_GUILD_AVATAR_NUM ; index01++ )
		{
			if( strcmp( tGuildInfo1.gMemberName[index01], "" ) != 0 )
			{
				tTotalMemberNum++;
			}
		}
		if( tTotalMemberNum != 1 )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( !mDB.DB_PROCESS_06( &tGuildName[0] ) )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( !mDB.DB_PROCESS_01( &tAvatarName[0], "", 0, "" ) )
		{
			mDB.DB_PROCESS_03( &tGuildName[0], &tAvatarName[0] );
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 0, &tGuildInfo1 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case  7 : //[È®Àå]
		CopyMemory( &tGuildName[0], &tData[0], MAX_GUILD_NAME_LENGTH );
		tGuildName[( MAX_GUILD_NAME_LENGTH - 1 )] = '\0';
		if( !mDB.DB_PROCESS_04( &tGuildName[0], &tGuildInfo1 ) )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		tTotalMemberNum = 0;
		for( index01 = 0 ; index01 < MAX_GUILD_AVATAR_NUM ; index01++ )
		{
			if( strcmp( tGuildInfo1.gMemberName[index01], "" ) != 0 )
			{
				tTotalMemberNum++;
			}
		}
		if( tTotalMemberNum < ( tGuildInfo1.gGrade * 10 ) )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( tGuildInfo1.gGrade == 5 )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		tGuildInfo1.gGrade++;
		if( !mDB.DB_PROCESS_05( &tGuildName[0], &tGuildInfo1 ) )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 0, &tGuildInfo1 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case  8 : //[Á¦¸í]
		CopyMemory( &tGuildName[0], &tData[0], MAX_GUILD_NAME_LENGTH );
		tGuildName[( MAX_GUILD_NAME_LENGTH - 1 )] = '\0';
		CopyMemory( &tAvatarName[0], &tData[MAX_GUILD_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH );
		tAvatarName[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';
		if( !mDB.DB_PROCESS_04( &tGuildName[0], &tGuildInfo1 ) )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		CopyMemory( &tGuildInfo2, &tGuildInfo1, sizeof( GUILD_INFO ) );
		if( strcmp( tGuildInfo1.gMaster01, tAvatarName ) == 0 )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		for( index01 = 0 ; index01 < MAX_GUILD_AVATAR_NUM ; index01++ )
		{
			if( strcmp( tGuildInfo1.gMemberName[index01], tAvatarName ) == 0 )
			{
				break;
			}
		}
		if( index01 == MAX_GUILD_AVATAR_NUM )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( strcmp( tGuildInfo1.gSubMaster01, tAvatarName ) == 0 )
		{
			strcpy( tGuildInfo1.gSubMaster01, "" );
		}
		if( strcmp( tGuildInfo1.gSubMaster02, tAvatarName ) == 0 )
		{
			strcpy( tGuildInfo1.gSubMaster02, "" );
		}
		strcpy( tGuildInfo1.gMemberName[index01], "" );
		tGuildInfo1.gMemberRole[index01] = 0;
		strcpy( tGuildInfo1.gMemberCall[index01], "" );
		if( !mDB.DB_PROCESS_05( &tGuildName[0], &tGuildInfo1 ) )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( !mDB.DB_PROCESS_01( &tAvatarName[0], "", 0, "" ) )
		{
			mDB.DB_PROCESS_05( &tGuildName[0], &tGuildInfo2 );
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 0, &tGuildInfo1 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case  9 : //[ÀÓ¸í]
		CopyMemory( &tGuildName[0], &tData[0], MAX_GUILD_NAME_LENGTH );
		tGuildName[( MAX_GUILD_NAME_LENGTH - 1 )] = '\0';
		CopyMemory( &tAvatarName[0], &tData[MAX_GUILD_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH );
		tAvatarName[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';
		CopyMemory( &tGuildRole, &tData[( MAX_GUILD_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH )], 4 );
		if( !mDB.DB_PROCESS_04( &tGuildName[0], &tGuildInfo1 ) )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		CopyMemory( &tGuildInfo2, &tGuildInfo1, sizeof( GUILD_INFO ) );
		if( strcmp( tGuildInfo1.gMaster01, tAvatarName ) == 0 )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		for( index01 = 0 ; index01 < MAX_GUILD_AVATAR_NUM ; index01++ )
		{
			if( strcmp( tGuildInfo1.gMemberName[index01], tAvatarName ) == 0 )
			{
				break;
			}
		}
		if( index01 == MAX_GUILD_AVATAR_NUM )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( tGuildRole == 1 )
		{
			if( ( strcmp( tGuildInfo1.gSubMaster01, "" ) != 0 ) && ( strcmp( tGuildInfo1.gSubMaster02, "" ) != 0 ) )
			{
				mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
			if( tGuildInfo1.gMemberRole[index01] != 2 )
			{
				mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
			//-------------------------------------------------------------------------------------------------
			// 2008.11.18 Kim SungSoo
			// Intro : 	1. Modify win32 api to linux c++
			//-------------------------------------------------------------------------------------------------	
			if( stricmp( tGuildInfo1.gSubMaster01, "" ) == 0 )
				//-------------------------------------------------------------------------------------------------

			{
				strcpy( tGuildInfo1.gSubMaster01, tGuildInfo1.gMemberName[index01] );
			}
			else
			{
				strcpy( tGuildInfo1.gSubMaster02, tGuildInfo1.gMemberName[index01] );
			}
			tGuildInfo1.gMemberRole[index01] = 1;
		}
		else
		{
			if( ( strcmp( tGuildInfo1.gSubMaster01, tGuildInfo1.gMemberName[index01] ) != 0 ) && ( strcmp( tGuildInfo1.gSubMaster02, tGuildInfo1.gMemberName[index01] ) != 0 ) )
			{
				mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
			if( tGuildInfo1.gMemberRole[index01] != 1 )
			{
				mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
				mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				return;
			}
			if( strcmp( tGuildInfo1.gSubMaster01, tGuildInfo1.gMemberName[index01] ) == 0 )
			{
				strcpy( tGuildInfo1.gSubMaster01, "" );
			}
			else
			{
				strcpy( tGuildInfo1.gSubMaster02, "" );
			}
			tGuildInfo1.gMemberRole[index01] = 2;
		}
		if( !mDB.DB_PROCESS_05( &tGuildName[0], &tGuildInfo1 ) )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( !mDB.DB_PROCESS_01( &tAvatarName[0], &tGuildName[0], tGuildInfo1.gMemberRole[index01], &tGuildInfo1.gMemberCall[index01][0] ) )
		{
			mDB.DB_PROCESS_05( &tGuildName[0], &tGuildInfo2 );
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 0, &tGuildInfo1 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	case 10 : //[ÄªÈ£]
		CopyMemory( &tGuildName[0], &tData[0], MAX_GUILD_NAME_LENGTH );
		tGuildName[( MAX_GUILD_NAME_LENGTH - 1 )] = '\0';
		CopyMemory( &tAvatarName[0], &tData[MAX_GUILD_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH );
		tAvatarName[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';
		CopyMemory( &tCallName[0], &tData[( MAX_GUILD_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH )], MAX_CALL_NAME_LENGTH );
		tCallName[( MAX_CALL_NAME_LENGTH - 1 )] = '\0';
		if( !mDB.DB_PROCESS_04( &tGuildName[0], &tGuildInfo1 ) )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		CopyMemory( &tGuildInfo2, &tGuildInfo1, sizeof( GUILD_INFO ) );
		if( strcmp( tGuildInfo1.gMaster01, tAvatarName ) == 0 )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		for( index01 = 0 ; index01 < MAX_GUILD_AVATAR_NUM ; index01++ )
		{
			if( strcmp( tGuildInfo1.gMemberName[index01], tAvatarName ) == 0 )
			{
				break;
			}
		}
		if( index01 == MAX_GUILD_AVATAR_NUM )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		strcpy( tGuildInfo1.gMemberCall[index01], tCallName );
		if( !mDB.DB_PROCESS_05( &tGuildName[0], &tGuildInfo1 ) )
		{
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		if( !mDB.DB_PROCESS_01( &tAvatarName[0], &tGuildName[0], tGuildInfo1.gMemberRole[index01], &tGuildInfo1.gMemberCall[index01][0] ) )
		{
			mDB.DB_PROCESS_05( &tGuildName[0], &tGuildInfo2 );
			mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 0, &tGuildInfo1 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	default : //[¿À·ù]
		mTRANSFER.B_GUILD_WORK_FOR_EXTRA_RECV( 1, &tGuildInfo1 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
}
//W_GET_CASH_SIZE_FOR_EXTRA_SEND
void W_GET_CASH_SIZE_FOR_EXTRA_SEND( int tUserIndex )
{
	//__LogMgr()->Log ("!GET_CASH_SIZE_FOR_EXTRA_SEND\n");
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 2 )
	{
		mUSER[tUserIndex].Quit( 4006 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	char tID[MAX_USER_ID_LENGTH];
	CopyMemory( &tID[0], &tPacket[1], MAX_USER_ID_LENGTH );
	tID[( MAX_USER_ID_LENGTH - 1 )] = '\0';

	int tCashSize = 0;
	int tBonusCashSize = 0;

	if( !mDB.DB_PROCESS_07( &tID[0], &tCashSize, &tBonusCashSize ) )
	{
		tCashSize = 0;
		tBonusCashSize = 0;
	}
	//For use US, EU
	//For use US, EU

	//__LogMgr()->Log ("!cash[%d]\n", tCashSize);
	mTRANSFER.B_GET_CASH_SIZE_FOR_EXTRA_RECV(tCashSize, tBonusCashSize);
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_BUY_CASH_ITEM_FOR_EXTRA_SEND
void W_BUY_CASH_ITEM_FOR_EXTRA_SEND( int tUserIndex )
{
	//__LogMgr()->Log ("!BUY_CASH_ITEM_FOR_EXTRA\n");
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 2 )
	{
		mUSER[tUserIndex].Quit( 4007 );
		return;
	} 
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	char tID[MAX_USER_ID_LENGTH];
	int tCostInfoIndex;
	int iIndex;
	int iQuantity;
	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	int tTribe;
	int tLevel;
	int tZoneNumber;
	char tSellNo[16];

	CopyMemory( &tID[0], &tPacket[1], MAX_USER_ID_LENGTH );
	tID[( MAX_USER_ID_LENGTH - 1 )] = '\0';
	CopyMemory( &tCostInfoIndex, &tPacket[( 1 + MAX_USER_ID_LENGTH )], 4 );
	//__LogMgr()->Log("tCostInfoIndex = %d \n" ,tCostInfoIndex );

	CopyMemory( &iIndex, &tPacket[( 5 + MAX_USER_ID_LENGTH )], 4 );
	//__LogMgr()->Log("iIndex = %d \n" ,iIndex );

	CopyMemory( &iQuantity, &tPacket[( 9 + MAX_USER_ID_LENGTH )], 4 );
	//__LogMgr()->Log("iQuantity = %d \n" ,iQuantity );

	CopyMemory( &tAvatarName[0], &tPacket[( 13 + MAX_USER_ID_LENGTH )], MAX_AVATAR_NAME_LENGTH );
	tAvatarName[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';
	//__LogMgr()->Log("tAvatarName = %s" ,tAvatarName );

	CopyMemory( &tTribe, &tPacket[( 13 + MAX_USER_ID_LENGTH + MAX_AVATAR_NAME_LENGTH )], 4 );
	//__LogMgr()->Log("tTribe = %d \n" ,tTribe );

	CopyMemory( &tLevel, &tPacket[( 17 + MAX_USER_ID_LENGTH + MAX_AVATAR_NAME_LENGTH )], 4 );
	CopyMemory( &tZoneNumber, &tPacket[( 17 + MAX_USER_ID_LENGTH + MAX_AVATAR_NAME_LENGTH + 4)], 4 );
	//__LogMgr()->Log("tLevel = %d \n" ,tLevel );

	int tCashSize0 = 0;
	int tCashSize1 = 0;
	int tCashSize2 = 0;
	int tCostSize0 = 0;
	int tCostSize1 = 0;
	int tCostSize2 = 0;

	// @ Cost Info Download @
	// ¾ÆÀÌÅÛ ÆÇ¸Å ÁßÁö ÁßÀÎ Áö °Ë»ç
	if (mGAME.mIsSellCashItem == false)
	{
		mTRANSFER.B_BUY_CASH_ITEM_FOR_EXTRA_RECV( 2, 0, 0, 0, 0 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	int tVersion = 0;
	CopyMemory( &tVersion, &tPacket[( 17 + MAX_USER_ID_LENGTH + MAX_AVATAR_NAME_LENGTH + 4 + 4)], 4 );
	// Ä³½¬ ¾ÆÀÌÅÛ Á¤º¸ ¹öÀü °Ë»ç.

	if (tVersion != mGAME.mCashItemInfoVersion)
	{
		mTRANSFER.B_BUY_CASH_ITEM_FOR_EXTRA_RECV( 3, 0, 0, 0, 0 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	} // @

	if( ( tCostInfoIndex < 0 ) || ( tCostInfoIndex > ( mGAME.mTotalCostInfoNum - 1 ) ) )
	{
		__LogMgr()->Log ("!CostInfoIndex error[%d]\n", tCostInfoIndex);
		mTRANSFER.B_BUY_CASH_ITEM_FOR_EXTRA_RECV( 1, 0, 0, 0, 0 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( iIndex != mGAME.mCostInfoValue[tCostInfoIndex][1] )
	{
		__LogMgr()->Log("!CostInfoValue error :tCostInfoIndex = %d iIndex = %d ,mCostInfoValue = %d  \n" 
			, tCostInfoIndex , iIndex , mGAME.mCostInfoValue[tCostInfoIndex][1]);
		mTRANSFER.B_BUY_CASH_ITEM_FOR_EXTRA_RECV( 1, 0, 0, 0, 0 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( iQuantity != mGAME.mCostInfoValue[tCostInfoIndex][2] )
	{
		__LogMgr()->Log ("!iQuantit error\n");
		mTRANSFER.B_BUY_CASH_ITEM_FOR_EXTRA_RECV( 1, 0, 0, 0, 0 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( mGAME.mCostInfoValue[tCostInfoIndex][3] != 1 )
	{
		__LogMgr()->Log ("!not sell error\n");
		mTRANSFER.B_BUY_CASH_ITEM_FOR_EXTRA_RECV( 1, 0, 0, 0, 0 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	if( !mDB.DB_PROCESS_07( &tID[0], &tCashSize1, &tCashSize2 ) )
	{
		tCashSize1 = 0;
	}

	//For use US, EU
	tCashSize1 = 0;
#ifdef __CASH_COM__
	tCashSize1 = mCASH_COM.GetCash( &tID[0] );
#endif
	//For use US, EU

	tCashSize0 = tCashSize1 + tCashSize2;
	tCostSize0 = mGAME.mCostInfoValue[tCostInfoIndex][0];

	//__LogMgr()->Log ("![%s] cash[%d] %d\n", tID, tCashSize0, tCostSize0);

	if( tCashSize0 < tCostSize0 ) {
		__LogMgr()->Log("!not enough money(%d, %d)\n", tCashSize0, tCostSize0);
		mTRANSFER.B_BUY_CASH_ITEM_FOR_EXTRA_RECV( 1, 0, 0, 0, 0 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}

	if((( tCostSize2 = tCashSize2 - tCostSize0)) >= 0) {
		tCostSize1 = 0;
		tCostSize2 = tCostSize0;
		//__LogMgr()->Log("2 : %d %d\n", tCostSize1, tCostSize2);
	} else {
		tCostSize1 = -(tCostSize2);
		tCostSize2 = tCostSize0 + tCostSize2;
		//__LogMgr()->Log("3 : %d %d\n", tCostSize1, tCostSize2);
	}

	if((tCostSize1 > 0) || (tCostSize2 > 0)) {
		//__LogMgr()->Log("4 : %d %d\n", tCostSize1, tCostSize2);
		if( !mDB.DB_PROCESS_08( &tID[0], 0, (-1 * tCostSize2))) {
			mTRANSFER.B_BUY_CASH_ITEM_FOR_EXTRA_RECV( 1, 0, 0, 0, 0 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
		//For use US, EU
#ifdef __CASH_COM__
		if(mCASH_COM.ChangeCash(&tID[0], tCostInfoIndex, &tSellNo[0]) != 1) {
			mTRANSFER.B_BUY_CASH_ITEM_FOR_EXTRA_RECV( 1, 0, 0, 0, 0 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			return;
		}
#endif
		//For use US, EU
	}

	tCashSize0 -= tCostSize0;
	tCashSize1 -= tCostSize1;
	tCashSize2 -= tCostSize2;

	//__LogMgr()->Log("5 : %d %d %d\n", tCashSize0, tCashSize1, tCashSize2);
	//mTRANSFER.B_BUY_CASH_ITEM_FOR_EXTRA_RECV(0, tCashSize0, (tCostSize0));
	mTRANSFER.B_BUY_CASH_ITEM_FOR_EXTRA_RECV(0, tCashSize1, tCashSize2, tCostSize1, tCostSize2);
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
//	mGAMELOG.GL_000_ITEM_LOG( &tID[0], mSERVER_INFO.mWorldNumber, iIndex, tCashSize1, tCashSize2, tCostSize1, tCostSize2, &tAvatarName[0], tTribe, tLevel, tZoneNumber );
}

// @ Cost Info Download @
void W_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_SEND(int tUserIndex)
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 2 )
	{
		mUSER[tUserIndex].Quit( 4008 );
		return;
	}

	/*int tVersion = mGAME.GetCostInfoVersion();
	if (tVersion != mGAME.mCashItemInfoVersion)
	{*/
		__LogMgr()->Log("!--------------------------------------------------------------\n");
		__LogMgr()->Log("!-------------------- Reload COST_INFO.TXT --------------------\n");
		__LogMgr()->Log("!--------------------------------------------------------------\n");
		if (mGAME.UpdateCashItem())
		{
			mTRANSFER.B_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_RECV( 0 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			__LogMgr()->Log("!--------------------   Reload SUCCESS   ----------------------\n");
			__LogMgr()->Log("!--------------------------------------------------------------\n");
			return;
		}
		else // Àß¸øµÈ COST_INFOÀÎ °æ¿ì.
		{
			mTRANSFER.B_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_RECV( 2 );
			mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			__LogMgr()->Log("!--------------------   Reload FAIL !!   ----------------------\n");
			__LogMgr()->Log("!--------------------------------------------------------------\n");
			return;
		}
	}
	//else if (tVersion == mGAME.mCashItemInfoVersion) // Àß¸øµÈ COST_INFOÀÎ °æ¿ì.
	//{
	//	mTRANSFER.B_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_RECV( 2 );
	//	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	//	return;
	//}

	//mTRANSFER.B_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_RECV( 1 );
	//mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
//}

void W_GET_CASH_ITEM_INFO_FOR_EXTRA_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 2 )
	{
		mUSER[tUserIndex].Quit( 4009 );
		return;
	}

	int tZoneNumber = 0;
	CopyMemory( &tZoneNumber, &tPacket[1], 4 );
	__LogMgr()->Log("!Zone(%d) - CashItemInfo Update(Version - %d)!\n", tZoneNumber, mGAME.mCashItemInfoVersion);

	mTRANSFER.B_GET_CASH_ITEM_INFO_FOR_EXTRA_RECV(0, mGAME.mCashItemInfoVersion, mGAME.mCashItemInfo);
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
} // @

void W_USE_PACKAGE_ITEM_FOR_EXTRA_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 2 )
	{
		mUSER[tUserIndex].Quit( 4010 );
		return;
	}

	char tID[MAX_USER_ID_LENGTH] = {0};
	int iIndex = 0;
	char tAvatarName[MAX_AVATAR_NAME_LENGTH] = {0};
	int tZoneNumber = 0;

	CopyMemory( &tID[0], &tPacket[1], MAX_USER_ID_LENGTH );
	tID[( MAX_USER_ID_LENGTH - 1 )] = '\0';

	CopyMemory( &iIndex, &tPacket[( 1 + MAX_USER_ID_LENGTH )], 4 );

	CopyMemory( &tAvatarName[0], &tPacket[( 5 + MAX_USER_ID_LENGTH )], MAX_AVATAR_NAME_LENGTH );
	tAvatarName[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';

	CopyMemory( &tZoneNumber, &tPacket[( 5 + MAX_USER_ID_LENGTH + MAX_AVATAR_NAME_LENGTH)], 4 );

	int tResult = 1;
#ifdef __CASH_COM__
	if (mCASH_COM.UsePackageItem(&tID[0], iIndex) == 1) { // ¼º°ø.
		tResult = 0;
	}
#endif
	mTRANSFER.B_USE_PACKAGE_ITEM_FOR_EXTRA_SEND(tResult);
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//-------------------------------------------------------------------------------------------------
void W_BLOOD_ITEM_INFO(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(4011);
		return;
	}
	int iIndex;
	CopyMemory( &iIndex, &tPacket[1], 4 );

	if (iIndex == 0)
	{
		mTRANSFER.B_BLOOD_ITEM_FOR_EXTRA_SEND(0, mGAME.mBloodCashItemInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	//Güncelleme
	if (iIndex == 1)
	{
		if (mGAME.UpdateBloodItem())
		{
			mTRANSFER.B_BLOOD_ITEM_FOR_EXTRA_SEND(0, mGAME.mBloodCashItemInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			printf("!--------------------   Reload SUCCESS   ----------------------\n");
			printf("!--------------------------------------------------------------\n");
			return;
		}
		else // Àß¸øµÈ COST_INFOÀÎ °æ¿ì.
		{
			mTRANSFER.B_BLOOD_ITEM_FOR_EXTRA_SEND(2, mGAME.mBloodCashItemInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			printf("!--------------------   Reload FAIL !!   ----------------------\n");
			printf("!--------------------------------------------------------------\n");
			return;
		}
	}
	//Güncelleme
	if (iIndex == 2)
	{
		mTRANSFER.B_BLOOD_ITEM_FOR_EXTRA_SEND(0, mGAME.mBloodCashItemInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
}
