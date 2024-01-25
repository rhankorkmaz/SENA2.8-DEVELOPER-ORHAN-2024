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
//-------------//
//LOGIN->CENTER//
//-------------//
//W_LOGIN_FOR_CENTER_SEND
void W_LOGIN_FOR_CENTER_SEND( int tUserIndex )
{
	//__LogMgr()->Log ("%s packet recv\n", __FUNCTION__);
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 0 )
	{
		mUSER[tUserIndex].Quit( 3001 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int index01;

	for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
	{
		if( mUSER[index01].mCheckServerType == 1 )
		{
			mUSER[index01].Quit( 3002 );
		}
	}
	//__LogMgr()->Log("send");
	mUSER[tUserIndex].mCheckServerType = 1;
	mTRANSFER.B_LOGIN_FOR_CENTER_RECV();
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	//LOG_TO_FILE_1 ("%s packet complete\n", __FUNCTION__);
}
//W_LOGIN_OK_FOR_CENTER_SEND
void W_LOGIN_OK_FOR_CENTER_SEND( int tUserIndex )
{
	//LOG_TO_FILE_1 ("%s packet recv\n", __FUNCTION__);
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 1 )
	{
		mUSER[tUserIndex].Quit( 3003 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();
	//LOG_TO_FILE_1 ("%s packet complete\n", __FUNCTION__);
}
//W_GET_ZONE_SERVER_INFO_1
void W_GET_ZONE_SERVER_INFO_1( int tUserIndex )
{
	//LOG_TO_FILE_1 ("%s packet recv\n", __FUNCTION__);
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 1 )
	{
		mUSER[tUserIndex].Quit( 3004 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tZoneNumber;
	CopyMemory( &tZoneNumber, &tPacket[1], 4 );

	int index01;

	for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
	{
		if( ( mUSER[index01].mCheckServerType == 2 ) && ( mUSER[index01].mZoneServerNumber == tZoneNumber ) )
		{
			break;
		}
	}
	if( index01 == MAX_USER_NUM )
	{
		mTRANSFER.B_GET_ZONE_SERVER_INFO_1_RESULT( 1, "127.0.0.1", 0 );
		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return;
	}
	//LOG_TO_FILE_2("![%d], %s\n", tZoneNumber, mUSER[index01].mIP);
	mTRANSFER.B_GET_ZONE_SERVER_INFO_1_RESULT( 0, &mSERVER_INFO.ServerIP[0], mUSER[index01].mZoneServerPort );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	//LOG_TO_FILE_1 ("%s packet complete\n", __FUNCTION__);
}
void W_BAN_PLAYER (int iUserIndex)
{
    char *tPacket = &mUSER[iUserIndex].mBUFFER_FOR_RECV[0];
    if( mUSER[iUserIndex].mCheckServerType != 1 )
    {
        mUSER[iUserIndex].Quit( 3004 );
        return;
    }
    mUSER[iUserIndex].mUsedTime = GetTickCount();

    LTOG_BAN_PLAYER pack1;
    ::CopyMemory (&pack1, tPacket, LTOG_BAN_PLAYER_SIZE);

    for (int i = 0; i < MAX_USER_NUM; i++)
    {
        //if (mUSER[i].mCheckServerType == 1) {
        //    mTRANSFER.B_GTOL_BAN_PLAYER (pack1.m_szID);
        //    mUSER[i].Send (TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
        //} 

        if (mUSER[i].mCheckServerType == 2) {
            mTRANSFER.B_GTOZ_BAN_PLAYER (pack1.m_szID);
            mUSER[i].Send (TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
        }
    }
}
//------------//
//ZONE->CENTER//
//------------//
//W_ZONE_FOR_CENTER_SEND
void W_ZONE_FOR_CENTER_SEND( int tUserIndex )
{
	//LOG_TO_FILE_1 ("%s packet recv\n", __FUNCTION__);
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 0 )
	{
		mUSER[tUserIndex].Quit( 4001 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tZoneNumber;
	int tPort;
	CopyMemory( &tZoneNumber, &tPacket[1], 4 );
	CopyMemory( &tPort, &tPacket[5], 4 );

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
	mUSER[tUserIndex].mZoneServerPort = tPort;
	mTRANSFER.B_ZONE_FOR_CENTER_RECV();
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	
	strcpy( mGAME.mZoneConnectionInfo.mIP[( tZoneNumber - 1 )], mUSER[tUserIndex].mIP );
	mGAME.mZoneConnectionInfo.mPort[( tZoneNumber - 1 )] = tPort;
	mTRANSFER.B_TOTAL_ZONE_CONNECTION_INFO( &mGAME.mZoneConnectionInfo );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );



	mTRANSFER.B_WORLD_INFO( &mGAME.mWorldInfo, &mGAME.mTribeInfo );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );

	mTRANSFER.B_ZONE_CONNECTION_INFO( tZoneNumber, &mGAME.mZoneConnectionInfo.mIP[( tZoneNumber - 1 )][0], mGAME.mZoneConnectionInfo.mPort[( tZoneNumber - 1 )] );
	for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
	{
		if( ( mUSER[index01].mCheckServerType == 2 ) && ( mUSER[index01].mZoneServerNumber != tZoneNumber ) )
		{
			mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		}
	}
	//LOG_TO_FILE_1 ("%s packet complete\n", __FUNCTION__);
}

//W_ZONE_FOR_CENTER_CONNECTION_SEND
void W_ZONE_FOR_CENTER_CONNECTION_SEND( int tUserIndex )
{
	//LOG_TO_FILE_1 ("%s packet recv\n", __FUNCTION__);
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 0 && mUSER[tUserIndex].mCheckServerType != 2)
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

	mTRANSFER.B_ZONE_CONNECTION_INFO( tZoneNumber, &mGAME.mZoneConnectionInfo.mIP[( tZoneNumber - 1 )][0], mGAME.mZoneConnectionInfo.mPort[( tZoneNumber - 1 )] );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	//LOG_TO_FILE_1 ("%s packet complete\n", __FUNCTION__);
}

//W_ZONE_OK_FOR_CENTER_SEND
void W_ZONE_OK_FOR_CENTER_SEND( int tUserIndex )
{
	//LOG_TO_FILE_1 ("%s packet recv\n", __FUNCTION__);
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 2 )
	{
		mUSER[tUserIndex].Quit( 4004 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();
	//LOG_TO_FILE_1 ("%s packet complete\n", __FUNCTION__);
}
//W_DEMAND_BROADCAST_INFO
void W_DEMAND_BROADCAST_INFO( int tUserIndex )
{
	//LOG_TO_FILE_1 ("%s packet recv\n", __FUNCTION__);
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 2 )
	{
		mUSER[tUserIndex].Quit( 4005 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tInfoSort;
	BYTE tInfoData[MAX_BROADCAST_INFO_SIZE];
	CopyMemory( &tInfoSort, &tPacket[1], 4 );
	CopyMemory( &tInfoData[0], &tPacket[5], MAX_BROADCAST_INFO_SIZE );

	int index01;
	int index02;
	int index03;
	int tZone049TypeZoneIndex;
	int tZone051TypeZoneIndex;
	int tZone053TypeZoneIndex;
	int tTribeGuardIndex1;
	int tTribeGuardIndex2;
	int tTribe;
	int tZone195LevelType;
	int tTribeSymbolIndex;
	int tWinTribeForSymbol;
	int tAllianceIndex;
	int tAllianceTribe1;
	int tAllianceTribe2;
	int tPossibleAllianceDate01;
	int tPossibleAllianceDate02;
	int tTribeForTribeVote;
	int tIndexForTribeVote;
	char tAvatarNameForTribeVote[MAX_AVATAR_NAME_LENGTH];
	int tLevelForTribeVote;
	int tKillOtherTribeForTribeVote;
	int tPointForTribeVote;
	int tTribeForTribeRole;
	int tIndexForTribeRole;
	char tAvatarNameForTribeRole[MAX_AVATAR_NAME_LENGTH];
	int tZone175TypeZoneIndex1;
	int tZone175TypeZoneIndex2;

#ifdef __GOD__	
	int tEventSort;
	int tEventValue;
	int tZone267TypeZoneIndex;
#endif
	int LifeorDeathTypeZoneIndex;
	int CpTowerZoneIndex;
	int CpTowerType;
	int CpTowerTime;
    // @ Tribe Formation Skill @
    int tTribeSkillSort = 0;
    // @

	time_t tCountSeconds;
	struct tm* tPresentTime;
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);

	printf_s("tInfoSort2====%d\n", tInfoSort);
	switch( tInfoSort )
	{
	//-------------//
	//ZONE_049_TYPE//
	//-------------//
	case   1 : break;
	case   2 :
		CopyMemory( &tZone049TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone049TypeState[tZone049TypeZoneIndex] = 1;
		break;
	case   3 :
		CopyMemory( &tZone049TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone049TypeState[tZone049TypeZoneIndex] = 2;
		break;
	case   4 :
		CopyMemory( &tZone049TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone049TypeState[tZone049TypeZoneIndex] = 3;
		break;
	case   5 :
		CopyMemory( &tZone049TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone049TypeState[tZone049TypeZoneIndex] = 5;
		break;
	case   6 :
		CopyMemory( &tZone049TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone049TypeState[tZone049TypeZoneIndex] = 5;
		break;
	case   7 :
		CopyMemory( &tZone049TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone049TypeState[tZone049TypeZoneIndex] = 4;
		break;
	case   8 :
		CopyMemory( &tZone049TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone049TypeState[tZone049TypeZoneIndex] = 5;

		//Tekrar sayma zamanýný yolla
		mGAME.mWorldInfo.mZone049TypeStateTime[tZone049TypeZoneIndex] = ((tPresentTime->tm_hour * 100) + tPresentTime->tm_min + 100);
		break;
	case   9 :
		CopyMemory( &tZone049TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone049TypeState[tZone049TypeZoneIndex] = 0;
		break;
	//-------------//
	//ZONE_051_TYPE//
	//-------------//
	case  10 : break;
	case  11 :
		CopyMemory( &tZone051TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone051TypeState[tZone051TypeZoneIndex] = 1;
		break;
	case  12 :
		CopyMemory( &tZone051TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone051TypeState[tZone051TypeZoneIndex] = 2;
		break;
	case  13 :
		CopyMemory( &tZone051TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone051TypeState[tZone051TypeZoneIndex] = 3;
		break;
	case  14 :
		CopyMemory( &tZone051TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone051TypeState[tZone051TypeZoneIndex] = 5;
		break;
	case  15 :
		CopyMemory( &tZone051TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone051TypeState[tZone051TypeZoneIndex] = 5;
		break;
	case  16 :
		CopyMemory( &tZone051TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone051TypeState[tZone051TypeZoneIndex] = 4;
		break;
	case  17 :
		CopyMemory( &tZone051TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone051TypeState[tZone051TypeZoneIndex] = 5;
		break;
	case  18 :
		CopyMemory( &tZone051TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone051TypeState[tZone051TypeZoneIndex] = 0;
		break;
	//-------------//
	//ZONE_053_TYPE//
	//-------------//
	case  19 : break;
	case  20 :
		CopyMemory( &tZone053TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone053TypeState[tZone053TypeZoneIndex] = 1;
		break;
	case  21 :
		CopyMemory( &tZone053TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone053TypeState[tZone053TypeZoneIndex] = 2;
		break;
	case  22 :
		CopyMemory( &tZone053TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone053TypeState[tZone053TypeZoneIndex] = 3;
		break;
	case  23 :
		CopyMemory( &tZone053TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone053TypeState[tZone053TypeZoneIndex] = 5;
		break;
	case  24 :
		CopyMemory( &tZone053TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone053TypeState[tZone053TypeZoneIndex] = 5;
		break;
	case  25 : break;
	case  26 : break;
	case  27 : break;
	case  28 :
		CopyMemory( &tZone053TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone053TypeState[tZone053TypeZoneIndex] = 4;
		break;
	case  29 :
		CopyMemory( &tZone053TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone053TypeState[tZone053TypeZoneIndex] = 5;
		break;
	case  30 :
		CopyMemory( &tZone053TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone053TypeState[tZone053TypeZoneIndex] = 0;
		break;
	//------//
	//¼öÈ£¼®//
	//------//
	case  31 :
		CopyMemory( &tTribeGuardIndex1, &tInfoData[0], 4 );
		CopyMemory( &tTribeGuardIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mTribeGuardState[tTribeGuardIndex1][tTribeGuardIndex2] = 0;
		break;
	case  32 :
		CopyMemory( &tTribeGuardIndex1, &tInfoData[0], 4 );
		CopyMemory( &tTribeGuardIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mTribeGuardState[tTribeGuardIndex1][tTribeGuardIndex2] = 1;
		break;
	//--------//
	//ZONE_038//
	//--------//
	case  33 : break;
	case  34 : break;
	case  35 : break;
	case  36 : break;
	case  37 : break;
	case  38 :
		CopyMemory( &tTribe, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone038WinTribe = tTribe;
		mDB.DB_PROCESS_03( tTribe );
		break;
	//----//
	//¼º¼®//
	//----//
	case  39 : break;
	case  40 :
		mGAME.mWorldInfo.mTribeSymbolBattle = 1;
		mGAME.mWorldInfo.HollyBattleRank = 1;

//		mGAMELOG.GL_201_START_TRIBE_SYMBOL_BATTLE();
		/** 2009. 11. 02 : ¼º¼®Àü ¸®´º¾ó (wolf) */
		mGAME.mWorldInfo.mTribe1Symbol = 0;
		mGAME.mWorldInfo.mTribe2Symbol = 1;
		mGAME.mWorldInfo.mTribe3Symbol = 2;
		mGAME.mWorldInfo.mTribe4Symbol = 3;
		mDB.DB_PROCESS_04(1, 1, 0 );
		mDB.DB_PROCESS_04(0, 2, 1 );
		mDB.DB_PROCESS_04(0, 3, 2 );
		mDB.DB_PROCESS_04(0, 4, 3 );
		/** 2009. 11. 02 : ¼º¼®Àü ¸®´º¾ó (wolf) */
		break;
	case  41 : break;
	case  42 :
		CopyMemory( &tTribeSymbolIndex, &tInfoData[0], 4 );
		CopyMemory( &tWinTribeForSymbol, &tInfoData[4], 4 );
		switch( tTribeSymbolIndex )
		{
		case 0 :
			mGAME.mWorldInfo.mTribe1Symbol = tWinTribeForSymbol;
			mDB.DB_PROCESS_04(0, 1, tWinTribeForSymbol );
			break;
		case 1 :
			mGAME.mWorldInfo.mTribe2Symbol = tWinTribeForSymbol;
			mDB.DB_PROCESS_04(0, 2, tWinTribeForSymbol );
			break;
		case 2 :
			mGAME.mWorldInfo.mTribe3Symbol = tWinTribeForSymbol;
			mDB.DB_PROCESS_04(0, 3, tWinTribeForSymbol );
			break;
		case 3 :
			mGAME.mWorldInfo.mTribe4Symbol = tWinTribeForSymbol;
			mDB.DB_PROCESS_04(0, 4, tWinTribeForSymbol );
			break;
		case 4 :
			mGAME.mWorldInfo.mMonsterSymbol = tWinTribeForSymbol;
			mDB.DB_PROCESS_04(0, 5, tWinTribeForSymbol );
			break;
		}
		break;
	case  43 : break;
	case  44 : break;
	case  45 :
		mGAME.mWorldInfo.mTribeSymbolBattle = 0;
		mGAME.mWorldInfo.HollyBattleRank = 0;
        // @ Tribe Formation Skill @
        mGAME.mWorldInfo.mTribeMasterCallAbility[0] = 0;
        mGAME.mWorldInfo.mTribeMasterCallAbility[1] = 0;
        mGAME.mWorldInfo.mTribeMasterCallAbility[2] = 0;
        mGAME.mWorldInfo.mTribeMasterCallAbility[3] = 0;
        // @
//		mGAMELOG.GL_202_END_TRIBE_SYMBOL_BATTLE();
		break;
	//------//
	//µ¿¸Í¼®//
	//------//
	case  46 :
		CopyMemory( &tAllianceTribe1, &tInfoData[0], 4 );
		CopyMemory( &tAllianceTribe2, &tInfoData[4], 4 );
		if( ( mGAME.mWorldInfo.mAllianceState[0][0] == -1 ) && ( mGAME.mWorldInfo.mAllianceState[0][1] == -1 ) )
		{
			tAllianceIndex = 0;
		}
		else
		{
			tAllianceIndex = 1;
		}
        mGAME.mWorldInfo.mPossibleAllianceInfo[tAllianceTribe1][0] = 0;
		mGAME.mWorldInfo.mPossibleAllianceInfo[tAllianceTribe1][1] = 0;
		switch( tAllianceTribe1 )
		{
		case 0 :
			mDB.DB_PROCESS_06( 1, 0, 0 );
			break;
		case 1 :
			mDB.DB_PROCESS_06( 2, 0, 0 );
			break;
		case 2 :
			mDB.DB_PROCESS_06( 3, 0, 0 );
			break;
		case 3 :
			mDB.DB_PROCESS_06( 4, 0, 0 );
			break;
		}
		mGAME.mWorldInfo.mPossibleAllianceInfo[tAllianceTribe2][0] = 0;
		mGAME.mWorldInfo.mPossibleAllianceInfo[tAllianceTribe2][1] = 0;
		switch( tAllianceTribe2 )
		{
		case 0 :
			mDB.DB_PROCESS_06( 1, 0, 0 );
			break;
		case 1 :
			mDB.DB_PROCESS_06( 2, 0, 0 );
			break;
		case 2 :
			mDB.DB_PROCESS_06( 3, 0, 0 );
			break;
		case 3 :
			mDB.DB_PROCESS_06( 4, 0, 0 );
			break;
		}
		mGAME.mWorldInfo.mAllianceState[tAllianceIndex][0] = tAllianceTribe1;
		mGAME.mWorldInfo.mAllianceState[tAllianceIndex][1] = tAllianceTribe2;
		switch( tAllianceIndex )
		{
		case 0 :
			mDB.DB_PROCESS_07( 1, tAllianceTribe1, tAllianceTribe2 );
			break;
		case 1 :
			mDB.DB_PROCESS_07( 2, tAllianceTribe1, tAllianceTribe2 );
			break;
		}
		break;
	case  47 :
		CopyMemory( &tAllianceTribe1, &tInfoData[0], 4 );
		CopyMemory( &tAllianceTribe2, &tInfoData[4], 4 );
		CopyMemory( &tPossibleAllianceDate01, &tInfoData[8], 4 );
		CopyMemory( &tPossibleAllianceDate02, &tInfoData[12], 4 );
		if( ( ( mGAME.mWorldInfo.mAllianceState[0][0] == tAllianceTribe1 ) && ( mGAME.mWorldInfo.mAllianceState[0][1] == tAllianceTribe2 ) ) || ( ( mGAME.mWorldInfo.mAllianceState[0][1] == tAllianceTribe1 ) && ( mGAME.mWorldInfo.mAllianceState[0][0] == tAllianceTribe2 ) ) )
		{
			tAllianceIndex = 0;
		}
		else
		{
			tAllianceIndex = 1;
		}
		mGAME.mWorldInfo.mPossibleAllianceInfo[tAllianceTribe1][0] = tPossibleAllianceDate01;
		mGAME.mWorldInfo.mPossibleAllianceInfo[tAllianceTribe1][1] = 1;
		switch( tAllianceTribe1 )
		{
		case 0 :
			mDB.DB_PROCESS_06( 1, tPossibleAllianceDate01, 1 );
			break;
		case 1 :
			mDB.DB_PROCESS_06( 2, tPossibleAllianceDate01, 1 );
			break;
		case 2 :
			mDB.DB_PROCESS_06( 3, tPossibleAllianceDate01, 1 );
			break;
		case 3 :
			mDB.DB_PROCESS_06( 4, tPossibleAllianceDate01, 1 );
			break;
		}
		mGAME.mWorldInfo.mPossibleAllianceInfo[tAllianceTribe2][0] = tPossibleAllianceDate02;
		mGAME.mWorldInfo.mPossibleAllianceInfo[tAllianceTribe2][1] = 1;
		switch( tAllianceTribe2 )
		{
		case 0 :
			mDB.DB_PROCESS_06( 1, tPossibleAllianceDate02, 1 );
			break;
		case 1 :
			mDB.DB_PROCESS_06( 2, tPossibleAllianceDate02, 1 );
			break;
		case 2 :
			mDB.DB_PROCESS_06( 3, tPossibleAllianceDate02, 1 );
			break;
		case 3 :
			mDB.DB_PROCESS_06( 4, tPossibleAllianceDate02, 1 );
			break;
		}
		mGAME.mWorldInfo.mAllianceState[tAllianceIndex][0] = -1;
		mGAME.mWorldInfo.mAllianceState[tAllianceIndex][1] = -1;
		switch( tAllianceIndex )
		{
		case 0 :
			mDB.DB_PROCESS_07( 1, -1, -1 );
			break;
		case 1 :
			mDB.DB_PROCESS_07( 2, -1, -1 );
			break;
		}
		break;
	case  48 : break;
	case  49 :
		CopyMemory( &tAllianceTribe1, &tInfoData[0], 4 );
		CopyMemory( &tAllianceTribe2, &tInfoData[4], 4 );
		CopyMemory( &tPossibleAllianceDate01, &tInfoData[8], 4 );
		CopyMemory( &tPossibleAllianceDate02, &tInfoData[12], 4 );
		if( ( ( mGAME.mWorldInfo.mAllianceState[0][0] == tAllianceTribe1 ) && ( mGAME.mWorldInfo.mAllianceState[0][1] == tAllianceTribe2 ) ) || ( ( mGAME.mWorldInfo.mAllianceState[0][1] == tAllianceTribe1 ) && ( mGAME.mWorldInfo.mAllianceState[0][0] == tAllianceTribe2 ) ) )
		{
			tAllianceIndex = 0;
		}
		else
		{
			tAllianceIndex = 1;
		}
		mGAME.mWorldInfo.mPossibleAllianceInfo[tAllianceTribe1][0] = tPossibleAllianceDate01;
		mGAME.mWorldInfo.mPossibleAllianceInfo[tAllianceTribe1][1] = 1;
		switch( tAllianceTribe1 )
		{
		case 0 :
			mDB.DB_PROCESS_06( 1, tPossibleAllianceDate01, 1 );
			break;
		case 1 :
			mDB.DB_PROCESS_06( 2, tPossibleAllianceDate01, 1 );
			break;
		case 2 :
			mDB.DB_PROCESS_06( 3, tPossibleAllianceDate01, 1 );
			break;
		case 3 :
			mDB.DB_PROCESS_06( 4, tPossibleAllianceDate01, 1 );
			break;
		}
		mGAME.mWorldInfo.mPossibleAllianceInfo[tAllianceTribe2][0] = tPossibleAllianceDate02;
		mGAME.mWorldInfo.mPossibleAllianceInfo[tAllianceTribe2][1] = 1;
		switch( tAllianceTribe2 )
		{
		case 0 :
			mDB.DB_PROCESS_06( 1, tPossibleAllianceDate02, 1 );
			break;
		case 1 :
			mDB.DB_PROCESS_06( 2, tPossibleAllianceDate02, 1 );
			break;
		case 2 :
			mDB.DB_PROCESS_06( 3, tPossibleAllianceDate02, 1 );
			break;
		case 3 :
			mDB.DB_PROCESS_06( 4, tPossibleAllianceDate02, 1 );
			break;
		}
		mGAME.mWorldInfo.mAllianceState[tAllianceIndex][0] = -1;
		mGAME.mWorldInfo.mAllianceState[tAllianceIndex][1] = -1;
		switch( tAllianceIndex )
		{
		case 0 :
			mDB.DB_PROCESS_07( 1, -1, -1 );
			break;
		case 1 :
			mDB.DB_PROCESS_07( 2, -1, -1 );
			break;
		}
		break;
	case  50 : break;
	//--------//
	//³¶ÀÎ¼±¾ð//
	//--------//
	case  51 : break;
	//-----------//
	//¼¼·ÂÀå_ÅõÇ¥//
	//-----------//
	case  52 :
		mGAME.mWorldInfo.mTribeVoteState[0] = 1;
		mGAME.mWorldInfo.mTribeVoteState[1] = 1;
		mGAME.mWorldInfo.mTribeVoteState[2] = 1;
		mGAME.mWorldInfo.mTribeVoteState[3] = 1;
		for( index01 = 0 ; index01 < 4 ; index01++ )
		{
			for( index02 = 0 ; index02 < MAX_TRIBE_VOTE_AVATAR_NUM ; index02++ )
			{
				strcpy( mGAME.mTribeInfo.mTribeVoteName[index01][index02], "" );
				mGAME.mTribeInfo.mTribeVoteLevel[index01][index02] = 0;
				mGAME.mTribeInfo.mTribeVoteKillOtherTribe[index01][index02] = 0;
				mGAME.mTribeInfo.mTribeVotePoint[index01][index02] = 0;
			}
		}
		mDB.DB_PROCESS_08( 1, 1 );
		mDB.DB_PROCESS_08( 2, 1 );
		mDB.DB_PROCESS_08( 3, 1 );
		mDB.DB_PROCESS_08( 4, 1 );
		mDB.DB_PROCESS_11( &mGAME.mTribeInfo );
		break;
	case  53 :
		mGAME.mWorldInfo.mTribeVoteState[0] = 2;
		mGAME.mWorldInfo.mTribeVoteState[1] = 2;
		mGAME.mWorldInfo.mTribeVoteState[2] = 2;
		mGAME.mWorldInfo.mTribeVoteState[3] = 2;
		mDB.DB_PROCESS_08( 1, 2 );
		mDB.DB_PROCESS_08( 2, 2 );
		mDB.DB_PROCESS_08( 3, 2 );
		mDB.DB_PROCESS_08( 4, 2 );
		break;
	case  54 :
		mGAME.mWorldInfo.mTribeVoteState[0] = 3;
		mGAME.mWorldInfo.mTribeVoteState[1] = 3;
		mGAME.mWorldInfo.mTribeVoteState[2] = 3;
		mGAME.mWorldInfo.mTribeVoteState[3] = 3;
		mDB.DB_PROCESS_08( 1, 3 );
		mDB.DB_PROCESS_08( 2, 3 );
		mDB.DB_PROCESS_08( 3, 3 );
		mDB.DB_PROCESS_08( 4, 3 );
		break;
	case  55 :
		mGAME.mWorldInfo.mTribeVoteState[0] = 4;
		mGAME.mWorldInfo.mTribeVoteState[1] = 4;
		mGAME.mWorldInfo.mTribeVoteState[2] = 4;
		mGAME.mWorldInfo.mTribeVoteState[3] = 4;
		for( index01 = 0 ; index01 < 4 ; index01++ )
		{
			index03 = -1;
			for( index02 = 0 ; index02 < MAX_TRIBE_VOTE_AVATAR_NUM ; index02++ )
			{
				if( strcmp( mGAME.mTribeInfo.mTribeVoteName[index01][index02], "" ) == 0 )
				{
					continue;
				}
				if( mGAME.mTribeInfo.mTribeVotePoint[index01][index02] < 1 )
				{
					continue;
				}
				if( index03 == -1 )
				{
					index03 = index02;
				}
				else
				{
					if( mGAME.mTribeInfo.mTribeVotePoint[index01][index02] > mGAME.mTribeInfo.mTribeVotePoint[index01][index03] )
					{
						index03 = index02;
					}
				}
			}
			if( index03 == -1 )
			{
				strcpy( mGAME.mTribeInfo.mTribeMaster[index01], "" );
			}
			else
			{
				strcpy( mGAME.mTribeInfo.mTribeMaster[index01], mGAME.mTribeInfo.mTribeVoteName[index01][index03] );
			}
			for( index02 = 0 ; index02 < MAX_TRIBE_SUBMASTER_NUM ; index02++ )
			{
				strcpy( mGAME.mTribeInfo.mTribeSubMaster[index01][index02], "" );
			}
		}
		mDB.DB_PROCESS_08( 1, 4 );
		mDB.DB_PROCESS_08( 2, 4 );
		mDB.DB_PROCESS_08( 3, 4 );
		mDB.DB_PROCESS_08( 4, 4 );
		mDB.DB_PROCESS_11( &mGAME.mTribeInfo );
		break;
	case  56 :
		mGAME.mWorldInfo.mTribeVoteState[0] = 0;
		mGAME.mWorldInfo.mTribeVoteState[1] = 0;
		mGAME.mWorldInfo.mTribeVoteState[2] = 0;
		mGAME.mWorldInfo.mTribeVoteState[3] = 0;
		for( index01 = 0 ; index01 < 4 ; index01++ )
		{
			for( index02 = 0 ; index02 < MAX_TRIBE_VOTE_AVATAR_NUM ; index02++ )
			{
				strcpy( mGAME.mTribeInfo.mTribeVoteName[index01][index02], "" );
				mGAME.mTribeInfo.mTribeVoteLevel[index01][index02] = 0;
				mGAME.mTribeInfo.mTribeVoteKillOtherTribe[index01][index02] = 0;
				mGAME.mTribeInfo.mTribeVotePoint[index01][index02] = 0;
			}
		}
		mDB.DB_PROCESS_08( 1, 0 );
		mDB.DB_PROCESS_08( 2, 0 );
		mDB.DB_PROCESS_08( 3, 0 );
		mDB.DB_PROCESS_08( 4, 0 );
		mDB.DB_PROCESS_11( &mGAME.mTribeInfo );
		break;
	case  57 :
		CopyMemory( &tTribeForTribeVote, &tInfoData[0], 4 );
		CopyMemory( &tIndexForTribeVote, &tInfoData[4], 4 );
		CopyMemory( &tAvatarNameForTribeVote[0], &tInfoData[8], MAX_AVATAR_NAME_LENGTH );
		CopyMemory( &tLevelForTribeVote, &tInfoData[( 8 + MAX_AVATAR_NAME_LENGTH )], 4 );
		CopyMemory( &tKillOtherTribeForTribeVote, &tInfoData[( 12 + MAX_AVATAR_NAME_LENGTH )], 4 );
		strcpy( mGAME.mTribeInfo.mTribeVoteName[tTribeForTribeVote][tIndexForTribeVote], tAvatarNameForTribeVote );
		mGAME.mTribeInfo.mTribeVoteLevel[tTribeForTribeVote][tIndexForTribeVote] = tLevelForTribeVote;
		mGAME.mTribeInfo.mTribeVoteKillOtherTribe[tTribeForTribeVote][tIndexForTribeVote] = tKillOtherTribeForTribeVote;
		mGAME.mTribeInfo.mTribeVotePoint[tTribeForTribeVote][tIndexForTribeVote] = 0;
		mDB.DB_PROCESS_11( &mGAME.mTribeInfo );
		break;
	case  58 :
		CopyMemory( &tTribeForTribeVote, &tInfoData[0], 4 );
		CopyMemory( &tIndexForTribeVote, &tInfoData[4], 4 );
		strcpy( mGAME.mTribeInfo.mTribeVoteName[tTribeForTribeVote][tIndexForTribeVote], "" );
		mGAME.mTribeInfo.mTribeVoteLevel[tTribeForTribeVote][tIndexForTribeVote] = 0;
		mGAME.mTribeInfo.mTribeVoteKillOtherTribe[tTribeForTribeVote][tIndexForTribeVote] = 0;
		mGAME.mTribeInfo.mTribeVotePoint[tTribeForTribeVote][tIndexForTribeVote] = 0;
		mDB.DB_PROCESS_11( &mGAME.mTribeInfo );
		break;
	case  59 :
		CopyMemory( &tTribeForTribeVote, &tInfoData[0], 4 );
		CopyMemory( &tIndexForTribeVote, &tInfoData[4], 4 );
		CopyMemory( &tPointForTribeVote, &tInfoData[8], 4 );
		mGAME.mTribeInfo.mTribeVotePoint[tTribeForTribeVote][tIndexForTribeVote] += tPointForTribeVote;
		mDB.DB_PROCESS_11( &mGAME.mTribeInfo );
		break;
	//--------//
	//ºÎ¼¼·ÂÀå//
	//--------//
	case  60 :
		CopyMemory( &tTribeForTribeRole, &tInfoData[0], 4 );
		CopyMemory( &tIndexForTribeRole, &tInfoData[4], 4 );
		CopyMemory( &tAvatarNameForTribeRole[0], &tInfoData[8], MAX_AVATAR_NAME_LENGTH );
		strcpy( mGAME.mTribeInfo.mTribeSubMaster[tTribeForTribeRole][tIndexForTribeRole], tAvatarNameForTribeRole );
		mDB.DB_PROCESS_11( &mGAME.mTribeInfo );
		break;
	case  61 :
		CopyMemory( &tTribeForTribeRole, &tInfoData[0], 4 );
		CopyMemory( &tIndexForTribeRole, &tInfoData[4], 4 );
		CopyMemory( &tAvatarNameForTribeRole[0], &tInfoData[8], MAX_AVATAR_NAME_LENGTH );
		strcpy( mGAME.mTribeInfo.mTribeSubMaster[tTribeForTribeRole][tIndexForTribeRole], "" );
		mDB.DB_PROCESS_11( &mGAME.mTribeInfo );
		break;
	//--------//
	//¼¼·Â±Ý°í//
	//--------//
	case  62 : break;
	//--------//
	//Ãµ½Å¹Ì±Ã//
	//--------//
	case  63 : break;
	case  64 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 1;
		break;
	case  65 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 2;
		break;
	case  66 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 3;
		break;
	case  67 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 4;
		break;
	case  68 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 5;
		break;
	case  69 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case  70 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case  71 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 6;
		break;
	case  72 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case  73 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 7;
		break;
	case  74 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 8;
		break;
	case  75 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 9;
		break;
	case  76 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case  77 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case  78 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 10;
		break;
	case  79 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case  80 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 11;
		break;
	case  81 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 12;
		break;
	case  82 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 13;
		break;
	case  83 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case  84 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case  85 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 14;
		break;
	case  86 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case  87 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 15;
		break;
	case  88 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 16;
		break;
	case  89 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 17;
		break;
	case  90 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case  91 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case  92 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 18;
		break;
	case  93 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case  94 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 19;
		break;
	case  95 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 20;
		break;
	case  96 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 21;
		break;
	case  97 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case  98 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case  99 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 22;
		break;
	case 100 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case 110 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mGAME.mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 0;
		break;
	case 111:
		break;
	case 112:
		break;
	//----//
	//¹®ÆÄ//
	//----//
	case 101 : break;
	case 102 : break;
	case 103 : break;
	case 104 : break;
	case 105 : break;
	case 106 : break;
	case 107 : break;
	case 108 : break;
	case 109 : break;
	/** 2009. 10. 27 : MonsterSymbol edit */
  case 114 : break;
  /** 2009. 10. 27 : MonsterSymbol edit */
  // @ Tribe Formation Skill @
#ifdef __GOD__  

	//--------//
	//ZONE_194//
	//--------//
	case 201 : break;
	case 202 :
		mGAME.mWorldInfo.mZone194State = 1;
		break;
	case 203 :
		mGAME.mWorldInfo.mZone194State = 2;
		break;
	case 204 :
		mGAME.mWorldInfo.mZone194State = 3;
		break;
	case 205 :
		mGAME.mWorldInfo.mZone194State = 5;
		break;
	case 206 :
		mGAME.mWorldInfo.mZone194State = 4;
		break;
	case 207 :
		mGAME.mWorldInfo.mZone194State = 5;
		break;
	case 208 :
		mGAME.mWorldInfo.mZone194State = 0;
		break;
	//--------------//
	//Á¾Á·_ÇýÅÃ_Á¤º¸//
	//--------------//
	case 301 :
		CopyMemory( &tEventSort, &tInfoData[0], 4 );
		CopyMemory( &tEventValue, &tInfoData[4], 4 );
		switch( tEventSort )
		{
		case 21 :
			mGAME.mWorldInfo.mTribeGeneralExperienceUpRatioInfo[0] = (float) tEventValue * 0.1f;
			break;
		case 22 :
			mGAME.mWorldInfo.mTribeGeneralExperienceUpRatioInfo[1] = (float) tEventValue * 0.1f;
			break;
		case 23 :
			mGAME.mWorldInfo.mTribeGeneralExperienceUpRatioInfo[2] = (float) tEventValue * 0.1f;
			break;
		case 24 :
			mGAME.mWorldInfo.mTribeGeneralExperienceUpRatioInfo[3] = (float) tEventValue * 0.1f;
			break;
		case 31 :
			mGAME.mWorldInfo.mTribeItemDropUpRatioInfo[0] = (float) tEventValue * 0.1f;
			break;
		case 32 :
			mGAME.mWorldInfo.mTribeItemDropUpRatioInfo[1] = (float) tEventValue * 0.1f;
			break;
		case 33 :
			mGAME.mWorldInfo.mTribeItemDropUpRatioInfo[2] = (float) tEventValue * 0.1f;
			break;
		case 34 :
			mGAME.mWorldInfo.mTribeItemDropUpRatioInfo[3] = (float) tEventValue * 0.1f;
			break;
		case 41 :
			mGAME.mWorldInfo.mTribeItemDropUpRatioForMyoungInfo[0] = (float) tEventValue * 0.1f;
			break;
		case 42 :
			mGAME.mWorldInfo.mTribeItemDropUpRatioForMyoungInfo[1] = (float) tEventValue * 0.1f;
			break;
		case 43 :
			mGAME.mWorldInfo.mTribeItemDropUpRatioForMyoungInfo[2] = (float) tEventValue * 0.1f;
			break;
		case 44 :
			mGAME.mWorldInfo.mTribeItemDropUpRatioForMyoungInfo[3] = (float) tEventValue * 0.1f;
			break;
		case 51 :
			mGAME.mWorldInfo.mTribeKillOtherTribeAddValueInfo[0] = tEventValue;
			break;
		case 52 :
			mGAME.mWorldInfo.mTribeKillOtherTribeAddValueInfo[1] = tEventValue;
			break;
		case 53 :
			mGAME.mWorldInfo.mTribeKillOtherTribeAddValueInfo[2] = tEventValue;
			break;
		case 54 :
			mGAME.mWorldInfo.mTribeKillOtherTribeAddValueInfo[3] = tEventValue;
			break;
		}
		break;
#endif		
  case 302 :
      CopyMemory( &tTribe, &tInfoData[0], 4 );
      CopyMemory( &tTribeSkillSort, &tInfoData[4], 4 );
      mGAME.mWorldInfo.mTribeMasterCallAbility[tTribe] = tTribeSkillSort;
      break; // @     
#ifdef __GOD__
  //-------------//
	//ZONE_267_TYPE//
	//-------------//
	case 402 : break;
	case 403 :
		CopyMemory( &tZone267TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone267TypeState[tZone267TypeZoneIndex] = 1;
		break;
	case 404 :
		CopyMemory( &tZone267TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone267TypeState[tZone267TypeZoneIndex] = 2;
		break;
	case 405 :
		CopyMemory( &tZone267TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone267TypeState[tZone267TypeZoneIndex] = 3;
		break;
	case 406 :
		CopyMemory( &tZone267TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone267TypeState[tZone267TypeZoneIndex] = 5;
		break;
	case 407 :
		CopyMemory( &tZone267TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone267TypeState[tZone267TypeZoneIndex] = 5;
		break;
	case 408 :
		CopyMemory( &tZone267TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone267TypeState[tZone267TypeZoneIndex] = 4;
		break;
	case 409 :
		CopyMemory( &tZone267TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone267TypeState[tZone267TypeZoneIndex] = 5;
		break;
	case 410 :
		CopyMemory( &tZone267TypeZoneIndex, &tInfoData[0], 4 );
		mGAME.mWorldInfo.mZone267TypeState[tZone267TypeZoneIndex] = 0;
		break;
#endif
	case 411:
		CopyMemory(&LifeorDeathTypeZoneIndex, &tInfoData[0], 4);
		mGAME.mWorldInfo.LifeOrDeath[LifeorDeathTypeZoneIndex] = 1;
		break;
	case 412:
		CopyMemory(&LifeorDeathTypeZoneIndex, &tInfoData[0], 4);
		mGAME.mWorldInfo.LifeOrDeath[LifeorDeathTypeZoneIndex] = 2;
		break;
	case 413:
		CopyMemory(&LifeorDeathTypeZoneIndex, &tInfoData[0], 4);
		mGAME.mWorldInfo.LifeOrDeath[LifeorDeathTypeZoneIndex] = 2;
		break;
	case 414:
		CopyMemory(&LifeorDeathTypeZoneIndex, &tInfoData[0], 4);
		mGAME.mWorldInfo.LifeOrDeath[LifeorDeathTypeZoneIndex] = 2;
		break;
	case 415:
		CopyMemory(&LifeorDeathTypeZoneIndex, &tInfoData[0], 4);
		mGAME.mWorldInfo.LifeOrDeath[LifeorDeathTypeZoneIndex] = 0;
		break;
	case 672: break;//96 rütbe duyurusu
	case 673: break;//20 üstü döküm duyurusu
	case 676: break;
	case 752://Oluþturma Ve yýkma
		CopyMemory(&CpTowerZoneIndex, &tInfoData[0], 4);
		CopyMemory(&CpTowerType, &tInfoData[4], 4);
		mGAME.mCPtowers.CpTowers[CpTowerZoneIndex] = CpTowerType;
		break;
	case 753://Oluþturma Ve yýkma
		CopyMemory(&CpTowerZoneIndex, &tInfoData[0], 4);
		CopyMemory(&CpTowerType, &tInfoData[4], 4);
		mGAME.mCPtowers.CpTowersAtakType[CpTowerZoneIndex] = CpTowerType;
		break;
	case  754: break;

	case 659: 
		mGAME.mWorldInfo.CemberVadisi = 1;
		break;
	case 660:
		mGAME.mWorldInfo.CemberVadisi = 2;
		break;
	case 661:
		mGAME.mWorldInfo.CemberVadisi = 2;
		break;
	case 662:
		mGAME.mWorldInfo.CemberVadisi = 3;
		break;
	case 663:
		mGAME.mWorldInfo.CemberVadisi = 4;
		break;
	case 664:
		mGAME.mWorldInfo.CemberVadisi = 7;
		break;
	case 665:
		mGAME.mWorldInfo.CemberVadisi = 7;
		break;
	case 666:
		mGAME.mWorldInfo.CemberVadisi = 5;
		break;
	case 667:
		mGAME.mWorldInfo.CemberVadisi = 6;
		break;
	case 668:
		mGAME.mWorldInfo.CemberVadisi = 7;
		break;
	case 669:
		mGAME.mWorldInfo.CemberVadisi = 0;
		break;
	case 771: break;
	case 772: break;
	case 773: break;
	case 774:
		CopyMemory(&tTribe, &tInfoData[0], 4);
		CopyMemory(&tZone195LevelType, &tInfoData[8 + MAX_AVATAR_NAME_LENGTH], 4);
		mGAME.mWorldInfo.mProvingGroundsState[tZone195LevelType] = (tTribe + 1);
		mGAME.mWorldInfo.mProvingGroundsPoint[0] = mGAME.CheckPVNumber(0);
		mGAME.mWorldInfo.mProvingGroundsPoint[1] = mGAME.CheckPVNumber(1);
		mGAME.mWorldInfo.mProvingGroundsPoint[2] = mGAME.CheckPVNumber(2);
		mGAME.mWorldInfo.mProvingGroundsPoint[3] = mGAME.CheckPVNumber(3);
		break;
	}
	mTRANSFER.B_BROADCAST_INFO( tInfoSort, &tInfoData[0] );
	for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
	{
		if( mUSER[index01].mCheckServerType == 2 )
		{
			
			mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		}
	}
	mGAMELOG.SendToLogServer(31);
	//LOG_TO_FILE_1 ("%s packet complete\n", __FUNCTION__);
}
//W_SERCH_AVATAR_SEND
void W_SERCH_AVATAR_SEND ( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 2 )
	{
		mUSER[tUserIndex].Quit( 4006 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();
	
	int tZoneNumber;
	int tResult;	
	int tSendUserIndex;
	int tGmIndex;

	CopyMemory( &tZoneNumber, &tPacket[1], 4 );
	CopyMemory( &tResult, &tPacket[5], 4 );
	CopyMemory( &tSendUserIndex, &tPacket[9], 4 );
	CopyMemory( &tGmIndex, &tPacket[13], 4 );

    if ( tResult == 1 )
	{
		mTRANSFER.B_TOOL_SERCH_AVATAR_RESULT( tZoneNumber, tGmIndex );
		mUSER[tSendUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	}else
	{
		return;
	}	
}

//W_CHECK_EVENT_SEND
void W_CHECK_EVENT_SEND( int tUserIndex ) 
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 2 )
	{
		mUSER[tUserIndex].Quit( 4007 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tEventSort;
	int tResult;	
	int tSendUserIndex;
	int tGmIndex;

	CopyMemory( &tEventSort, &tPacket[1], 4 );
	CopyMemory( &tResult, &tPacket[5], 4 );
	CopyMemory( &tSendUserIndex, &tPacket[9], 4 );
	CopyMemory( &tGmIndex, &tPacket[13], 4 );

	//LOG_TO_FILE_3("sort  %d %d %d\n", tUserIndex, tEventSort, tResult);
	
	// 2010.02.01 : KimSungSoo
	// max over user do not send
	__LogMgr()->Log("! W_CHECK_EVENT_SEND Send user  = %d \n", tSendUserIndex);
	if(tSendUserIndex >=MAX_USER_NUM )
	{
		return;
	}
	
	mTRANSFER.B_TOOL_CHECK_EVENT_RESULT( tGmIndex, tEventSort, tResult, mSERVER_INFO.mWorldNumber, mUSER[tUserIndex].mZoneServerNumber );
	mUSER[tSendUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );	
}
// @ Cost Info Download @
void W_UPDATE_CASH_ITEM_INFO_FOR_CENTER(int tUserIndex)
{
    char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];

    if( mUSER[tUserIndex].mCheckServerType != 2 )
    {
        mUSER[tUserIndex].Quit( 4008 );
        return;
    }

    mTRANSFER.B_UPDATE_CASH_ITEM_INFO_FOR_ZONE();
    for( int index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
    {
        if( mUSER[index01].mCheckServerType == 2 )
        {
            mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
        }
    }
} // @

//------------//
//TOOL->CENTER//
//------------//
//W_TOOL_FOR_CENTER_SEND
void W_TOOL_FOR_CENTER_SEND( int tUserIndex )
{
	mUSER[tUserIndex].Quit(5001);
	return;
	cout << "tool1" << endl;
	//LOG_TO_FILE_1 ("%s packet recv\n", __FUNCTION__);
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 0 )
	{
		mUSER[tUserIndex].Quit( 5001 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	mUSER[tUserIndex].mCheckServerType = 3;
	mTRANSFER.B_TOOL_FOR_CENTER_RECV();
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	//LOG_TO_FILE_1 ("%s packet complete\n", __FUNCTION__);
}
//W_TOOL_OK_FOR_CENTER_SEND
void W_TOOL_OK_FOR_CENTER_SEND( int tUserIndex )
{
	mUSER[tUserIndex].Quit(5002);
	return;
	cout << "tool2" << endl;
	//LOG_TO_FILE_1 ("%s packet recv\n", __FUNCTION__);
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 3 )
	{
		mUSER[tUserIndex].Quit( 5002 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();
	//LOG_TO_FILE_1 ("%s packet complete\n", __FUNCTION__);
}
//W_DEMAND_START_FOR_TOOL
void W_DEMAND_START_FOR_TOOL( int tUserIndex )
{
	mUSER[tUserIndex].Quit(5003);
	return;
	cout << "tool3" << endl;
	//LOG_TO_FILE_1 ("%s packet recv\n", __FUNCTION__);
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 3 )
	{
		mUSER[tUserIndex].Quit( 5003 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int index01;

	mTRANSFER.B_START();
	for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
	{
		if( mUSER[index01].mCheckServerType == 2 )
		{
			mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		}
	}
	mTRANSFER.B_TOOL_DEMAND_RESULT();
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	//LOG_TO_FILE_1 ("%s packet complete\n", __FUNCTION__);
}
//W_DEMAND_NOTICE_FOR_TOOL
void W_DEMAND_NOTICE_FOR_TOOL( int tUserIndex )
{
	mUSER[tUserIndex].Quit(5004);
	return;
	cout << "tool4" << endl;
	//LOG_TO_FILE_1 ("%s packet recv\n", __FUNCTION__);
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 3 )
	{
		mUSER[tUserIndex].Quit( 5004 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	char tContent[MAX_CHAT_CONTENT_LENGTH];
	int tZoneNumber;
	int tTribe;
	CopyMemory( &tContent[0], &tPacket[1], MAX_CHAT_CONTENT_LENGTH );
	tContent[( MAX_CHAT_CONTENT_LENGTH - 1 )] = '\0';
	CopyMemory( &tZoneNumber, &tPacket[( 1 + MAX_CHAT_CONTENT_LENGTH )], 4 );
	CopyMemory( &tTribe, &tPacket[( 5 + MAX_CHAT_CONTENT_LENGTH )], 4 );

	int index01;

	mTRANSFER.B_NOTICE( &tContent[0], tTribe );
	if( tZoneNumber == 0 )
	{
		for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
		{
			if( mUSER[index01].mCheckServerType == 2 )
			{
				mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			}
		}
	}
	else
	{
		for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
		{
			if( ( mUSER[index01].mCheckServerType == 2 ) && ( mUSER[index01].mZoneServerNumber == tZoneNumber ) )
			{
				mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			}
		}
	}
	mTRANSFER.B_TOOL_DEMAND_RESULT();
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	//LOG_TO_FILE_1 ("%s packet complete\n", __FUNCTION__);
}
//W_DEMAND_SET_EVENT_FOR_TOOL
void W_DEMAND_SET_EVENT_FOR_TOOL( int tUserIndex )
{
	mUSER[tUserIndex].Quit(5005);
	return;
	cout << "tool5" << endl;
	//LOG_TO_FILE_1 ("%s packet recv\n", __FUNCTION__);
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 3 )
	{
		mUSER[tUserIndex].Quit( 5005 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tEventSort;
	int tEventValue;
	int tZoneNumber;
	CopyMemory( &tEventSort, &tPacket[1], 4 );
	CopyMemory( &tEventValue, &tPacket[5], 4 );
	CopyMemory( &tZoneNumber, &tPacket[9], 4 );

	int index01;

	mTRANSFER.B_SET_EVENT( tEventSort, tEventValue );
	if( tZoneNumber == 0 )
	{
		for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
		{
			if( mUSER[index01].mCheckServerType == 2 )
			{
				mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			}
		}
	}
	else
	{
		for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
		{
			if( ( mUSER[index01].mCheckServerType == 2 ) && ( mUSER[index01].mZoneServerNumber == tZoneNumber ) )
			{
				mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			}
		}
	}
	mTRANSFER.B_TOOL_DEMAND_RESULT();
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	//LOG_TO_FILE_1 ("%s packet complete\n", __FUNCTION__);
}
//W_DEMAND_SHUTDOWN_FOR_TOOL
void W_DEMAND_SHUTDOWN_FOR_TOOL( int tUserIndex )
{
	mUSER[tUserIndex].Quit(5006);
	return;
	cout << "tool6" << endl;
	//LOG_TO_FILE_1 ("%s packet recv\n", __FUNCTION__);
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 3 )
	{
		mUSER[tUserIndex].Quit( 5006 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int index01;

	mTRANSFER.B_SHUTDOWN();
	for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
	{
		if( mUSER[index01].mCheckServerType == 2 )
		{
			mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		}
	}
	mTRANSFER.B_TOOL_DEMAND_RESULT();
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	//LOG_TO_FILE_1 ("%s packet complete\n", __FUNCTION__);
}
//W_DEMAND_SET_GM_ORDER_FOR_GMTOOL
void W_DEMAND_SET_GM_ORDER_FOR_GMTOOL( int tUserIndex )
{
	mUSER[tUserIndex].Quit(5007);
	return;
	cout << "tool6" << endl;
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 3 )
	{
		mUSER[tUserIndex].Quit( 5007 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tEventSort;	
	int tZoneNumber;
	int tMoveZoneNumber;
	char tAvatarName01[13];
	CopyMemory( &tEventSort, &tPacket[1], 4 );	
	CopyMemory( &tZoneNumber, &tPacket[5], 4 );
	CopyMemory( &tMoveZoneNumber, &tPacket[9], 4 );
	CopyMemory( &tAvatarName01, &tPacket[13], 13 );

	int index01;

	mTRANSFER.B_SET_GM_ORDER(tEventSort, tMoveZoneNumber, tAvatarName01);
	for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
	{
		if( ( mUSER[index01].mCheckServerType == 2 ) && ( mUSER[index01].mZoneServerNumber == tZoneNumber ) )
		{
			mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		}
	}
}
//W_DEMAND_SERCH_AVATAR_FOR_GMTOOL
void W_DEMAND_SERCH_AVATAR_FOR_GMTOOL( int tUserIndex )
{
	mUSER[tUserIndex].Quit(5008);
	return;
	cout << "tool7" << endl;
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 3 )
	{
		mUSER[tUserIndex].Quit( 5008 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();
	
	char tAvatarName01[13];
	int tGmIndex;
	CopyMemory( &tAvatarName01, &tPacket[1], 13 );	
	CopyMemory( &tGmIndex, &tPacket[14], 4 );	

	//LOG_TO_FILE_1("!********************************************************************Name : %s\n", tAvatarName01);
	
	int index01;

	mTRANSFER.B_SERCH_AVATAR( tAvatarName01, tUserIndex, tGmIndex);
	for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
	{
		if( mUSER[index01].mCheckServerType == 2 )
		{
			mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		}
	}	
}
//W_DEMAND_SET_GM_ORDER_FOR_GMTOOL_MOVE_AVATAR
void W_DEMAND_SET_GM_ORDER_FOR_GMTOOL_MOVE_AVATAR( int tUserIndex )
{
	mUSER[tUserIndex].Quit(5009);
	return;
	cout << "tool8" << endl;
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 3 )
	{
		mUSER[tUserIndex].Quit( 5009 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();
	//protocol(1) + tZoneNumber(4) + AvatarName01(13) + tPosX(4) + tPosY(4) + tPosZ(4)
	int tZoneNumber;		
	char tAvatarName01[13];
	int tPosX;
	int tPosY;
	int tPosZ;	
	CopyMemory( &tZoneNumber, &tPacket[1], 4 );	
	CopyMemory( &tAvatarName01, &tPacket[5], 13 );
	CopyMemory( &tPosX, &tPacket[18], 4 );	
	CopyMemory( &tPosY, &tPacket[22], 4 );	
	CopyMemory( &tPosZ, &tPacket[26], 4 );	

	int index01;

	mTRANSFER.B_SET_GM_ORDER_MOVE_AVATAR(tAvatarName01, tPosX, tPosY, tPosZ);
	for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
	{
		if( ( mUSER[index01].mCheckServerType == 2 ) && ( mUSER[index01].mZoneServerNumber == tZoneNumber ) )
		{
			mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		}
	}
}
//W_DEMAND_CHECK_EVENT_FOR_TOOL
void W_DEMAND_CHECK_EVENT_FOR_TOOL( int tUserIndex )
{
	mUSER[tUserIndex].Quit(5010);
	return;
	cout << "tool9" << endl;
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 3 )
	{
		mUSER[tUserIndex].Quit( 5010 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tEventSort;
	int tGmIndex;
	CopyMemory( &tEventSort, &tPacket[1], 4 );	
	CopyMemory( &tGmIndex, &tPacket[5], 4 );	

	int index01;

	mTRANSFER.B_CHECK_EVENT( tEventSort, tUserIndex, tGmIndex );
	
	for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
	{
		if( mUSER[index01].mCheckServerType == 2 )
		{
			mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		}
	}
	mTRANSFER.B_TOOL_DEMAND_RESULT();
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}

void W_GET_TOTAL_RANK_INFO_SEND(int tUserIndex)
{
	if( mUSER[tUserIndex].mCheckServerType != 2 ) {
		mUSER[tUserIndex].Quit( 5011 );
		return;
	}
	mTRANSFER.B_TOTAL_RANK_INFO_RESULT();
	mUSER[tUserIndex].Send(TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}

void W_GET_RANK_INFO_SEND(int tUserIndex)
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];

	if( mUSER[tUserIndex].mCheckServerType != 2 
			&& (int)tPacket[0] != P_GET_RANK_INFO_SEND) {
		mUSER[tUserIndex].Quit( 5012 );
		return;
	}

	mTRANSFER.B_RANK_INFO_RESULT(&mUSER[tUserIndex].mBUFFER_FOR_RECV[1]);
	mUSER[tUserIndex].Send(TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}

// # X-Trap # {
// W_XTRAP_MAP_FILE_CHANGE_FOR_CENTER // TOOL -> CENTER

//-----------------------//
//[CHAT_TOOL] -> [CENTER]//
//-----------------------//
//W_CHAT_TOOL_FOR_CENTER_SEND
void W_CHAT_TOOL_FOR_CENTER_SEND( int tUserIndex )
{
	return;
	cout << "tool10" << endl;
	//LOG_TO_FILE_1 ("%s packet recv\n", __FUNCTION__);
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 0 )
	{
		mUSER[tUserIndex].Quit( 6001 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	mUSER[tUserIndex].mCheckServerType = 4;
	mTRANSFER.B_CHAT_TOOL_FOR_CENTER_RECV();
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	//LOG_TO_FILE_1 ("%s packet complete\n", __FUNCTION__);
}
//W_CHAT_TOOL_OK_FOR_CENTER_SEND
void W_CHAT_TOOL_OK_FOR_CENTER_SEND( int tUserIndex )
{
	return;
	cout << "tool11" << endl;
	//LOG_TO_FILE_1 ("%s packet recv\n", __FUNCTION__);
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 4 )
	{
		mUSER[tUserIndex].Quit( 6002 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();
	//LOG_TO_FILE_1 ("%s packet complete\n", __FUNCTION__);
}
//W_TRIBE_CHAT_FOR_CHAT_TOOL_SEND
void W_TRIBE_CHAT_FOR_CHAT_TOOL_SEND( int tUserIndex )
{
	return;
	cout << "tool12" << endl;
	//LOG_TO_FILE_1 ("%s packet recv\n", __FUNCTION__);
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 4 )
	{
		mUSER[tUserIndex].Quit( 6003 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tZoneNumber;
	int tTribe;
	char tAvatarName01[13];
	char tAvatarName02[13];
	char tContent[51];
	CopyMemory( &tZoneNumber, &tPacket[1], 4 );
	CopyMemory( &tTribe, &tPacket[5], 4 );
	CopyMemory( &tAvatarName01[0], &tPacket[9], 13 );
	CopyMemory( &tAvatarName02[0], &tPacket[22], 13 );
	CopyMemory( &tContent[0], &tPacket[35], 51 );

	int index01;

	mTRANSFER.B_TRIBE_CHAT( tZoneNumber, tTribe, &tAvatarName01[0], &tAvatarName02[0], &tContent[0] );
	for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
	{
		if( ( mUSER[index01].mCheckServerType == 2 ) && ( mUSER[index01].mZoneServerNumber == tZoneNumber ) )
		{
			mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		}
	}
	//LOG_TO_FILE_1 ("%s packet complete\n", __FUNCTION__);
}
//W_SECRET_CHAT_FOR_CHAT_TOOL_SEND
void W_SECRET_CHAT_FOR_CHAT_TOOL_SEND( int tUserIndex )
{
	return;
	cout << "tool13" << endl;
	//LOG_TO_FILE_1 ("%s packet recv\n", __FUNCTION__);
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 4 )
	{
		mUSER[tUserIndex].Quit( 6004 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tZoneNumber;
	int tTribe;
	char tAvatarName01[13];
	char tAvatarName02[13];
	char tContent[51];
	CopyMemory( &tZoneNumber, &tPacket[1], 4 );
	CopyMemory( &tTribe, &tPacket[5], 4 );
	CopyMemory( &tAvatarName01[0], &tPacket[9], 13 );
	CopyMemory( &tAvatarName02[0], &tPacket[22], 13 );
	CopyMemory( &tContent[0], &tPacket[35], 51 );

	int index01;

	mTRANSFER.B_SECRET_CHAT( tZoneNumber, tTribe, &tAvatarName01[0], &tAvatarName02[0], &tContent[0] );
	for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
	{
		if( mUSER[index01].mCheckServerType == 2 )
		{
			mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		}
	}
	//LOG_TO_FILE_1 ("%s packet complete\n", __FUNCTION__);
}
//--------------------//
//[POLICE] -> [CENTER]//
//--------------------//
//W_POLICE_FOR_CENTER_SEND
void W_POLICE_FOR_CENTER_SEND( int tUserIndex )
{
	//LOG_TO_FILE_1 ("%s packet recv\n", __FUNCTION__);
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 0 )
	{
		mUSER[tUserIndex].Quit( 7001 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	mUSER[tUserIndex].mCheckServerType = 5;
	mTRANSFER.B_POLICE_FOR_CENTER_RECV();
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	//LOG_TO_FILE_1 ("%s packet complete\n", __FUNCTION__);
}
//W_POLICE_OK_FOR_CENTER_SEND
void W_POLICE_OK_FOR_CENTER_SEND( int tUserIndex )
{
	//LOG_TO_FILE_1 ("%s packet recv\n", __FUNCTION__);
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 5 )
	{
		mUSER[tUserIndex].Quit( 7002 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();
	//LOG_TO_FILE_1 ("%s packet complete\n", __FUNCTION__);
}
//W_POLICE_INFO_FOR_CENTER_SEND
void W_POLICE_INFO_FOR_CENTER_SEND( int tUserIndex )
{
	//LOG_TO_FILE_1 ("%s packet recv\n", __FUNCTION__);
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 5 )
	{
		mUSER[tUserIndex].Quit( 7003 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	char tID[33];
	int tLoginTime;
	int tLogoutTime;
	CopyMemory( &tID[0], &tPacket[1], 33 );
	CopyMemory( &tLoginTime, &tPacket[34], 4 );
	CopyMemory( &tLogoutTime, &tPacket[38], 4 );

	int index01;

	mTRANSFER.B_POLICE_INFO( &tID[0], tLoginTime, tLogoutTime );
	for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
	{
		if( mUSER[index01].mCheckServerType == 2 )
		{
			mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		}
	}
	//LOG_TO_FILE_1 ("%s packet complete\n", __FUNCTION__);
}

//-------------------------------------------------------------------------------------------------
