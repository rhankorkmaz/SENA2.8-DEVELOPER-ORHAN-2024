//-------------------------------------------------------------------------------------------------
//MAIN_HEADER_FILE
//-------------------------------------------------------------------------------------------------
#include "Shengming.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_SUMMON_SYSTEM
//-------------------------------------------------------------------------------------------------
//INSTANCE
MySummonSystem mSUMMON;
//CREATE
MySummonSystem::MySummonSystem( void )
{
	mTotalMonsterSummonInfoNum = 0;
	mMONSTER_SUMMON = NULL;
	mTotalBossMonsterSummonInfoNum = 0;
	mBOSS_MONSTER_SUMMON = NULL;
}
//INIT
 void MySummonSystem::Init(void)
{
#if 1
	char tFileName[1000];
#if 0
	char tFileNamePart01[4];
	tFileNamePart01[0] = (mSERVER_INFO.mServerNumber % 1000) / 100 + '0';
	tFileNamePart01[1] = (mSERVER_INFO.mServerNumber % 100) / 10 + '0';
	tFileNamePart01[2] = (mSERVER_INFO.mServerNumber % 10) / 1 + '0';
	tFileNamePart01[3] = '\0';
#endif
	sprintf(tFileName, "DATA/Shuaguai/Z%03d_SUMMONMONSTER.WREGION", mSERVER_INFO.mServerNumber);
	LoadRegionInfo_1(tFileName);
	sprintf(tFileName, "DATA/Shuaguai/Z%03d_SUMMONBOSSMONSTER.WREGION", mSERVER_INFO.mServerNumber);
	LoadRegionInfo_2(tFileName);
#endif
}
//void MySummonSystem::Init( void )
//{
//#if 1
//	char tFileName[1000];
//#if 0
//	char tFileNamePart01[4];
//	tFileNamePart01[0] = ( mSERVER_INFO.mServerNumber % 1000 ) / 100 + '0';
//	tFileNamePart01[1] = ( mSERVER_INFO.mServerNumber % 100 ) / 10 + '0';
//	tFileNamePart01[2] = ( mSERVER_INFO.mServerNumber % 10 ) / 1 + '0';
//	tFileNamePart01[3] = '\0';
//#endif
//	//sprintf( tFileName, "DATA/Shuaguai/Z%03d_SUMMONMONSTER.WREGION", mSERVER_INFO.mServerNumber );
//
//	//Katlardaki mobb
//	if (mGAME.mCheckZone101TypeServer == TRUE)
//	{
//		//sprintf(tFileName, "DATA/Shuaguai/Z104_SUMMONMONSTER.WREGION");
//		sprintf(tFileName, "DATA/Shuaguai/Z%03d_SUMMONMONSTER.WREGION", mSERVER_INFO.mServerNumber);
//	}
//	else if (mGAME.mCheckZone126TypeServer == TRUE)
//	{
//		sprintf(tFileName, "DATA/Shuaguai/Z126_SUMMONMONSTER.WREGION");
//	}
//	else
//	{
//		sprintf(tFileName, "DATA/Shuaguai/Z%03d_SUMMONMONSTER.WREGION", mSERVER_INFO.mServerNumber);
//	}
//
//	if (mSERVER_INFO.mServerNumber == 235 || mSERVER_INFO.mServerNumber == 236 ||
//		mSERVER_INFO.mServerNumber == 237 || mSERVER_INFO.mServerNumber == 238 || mSERVER_INFO.mServerNumber == 239 || mSERVER_INFO.mServerNumber == 240)
//	{
//		return;
//	}
//	LoadRegionInfo_1( tFileName );
//	sprintf( tFileName, "DATA/Shuaguai/Z%03d_SUMMONBOSSMONSTER.WREGION", mSERVER_INFO.mServerNumber );
//	LoadRegionInfo_2( tFileName );
//#endif
//}
 ////FREE
//void MySummonSystem::Free( void )
//{
//	mTotalMonsterSummonInfoNum = 0;
//	if( mMONSTER_SUMMON )
//	{
//		GlobalFree( mMONSTER_SUMMON );
//		mMONSTER_SUMMON = NULL;
//	}
//	mTotalBossMonsterSummonInfoNum = 0;
//	if( mBOSS_MONSTER_SUMMON )
//	{
//		GlobalFree( mBOSS_MONSTER_SUMMON );
//		mBOSS_MONSTER_SUMMON = NULL;
//	}
//}
 //FREE
 void MySummonSystem::Free(void)
 {
	 mTotalMonsterSummonInfoNum = 0;
	 if (mMONSTER_SUMMON)
	 {
		 GlobalFree(mMONSTER_SUMMON);
		 mMONSTER_SUMMON = NULL;
	 }
	 mTotalBossMonsterSummonInfoNum = 0;
	 if (mBOSS_MONSTER_SUMMON)
	 {
		 GlobalFree(mBOSS_MONSTER_SUMMON);
		 mBOSS_MONSTER_SUMMON = NULL;
	 }
 }

////LOAD_REGION_INFO_1
//void MySummonSystem::LoadRegionInfo_1( char *tFileName )
//{
//	int index01;
//	int index02;
//	int index03;
//	DWORD nReadByte;
//	int tTotalRegionInfoNum;
//	WORLD_REGION_INFO *tRegionInfo;
//	MONSTER_INFO *tMONSTER_INFO;
//	unsigned int tRandom = 0;
//
//	HANDLE hFile;
//	hFile = CreateFile( tFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
//	if( hFile == INVALID_HANDLE_VALUE )
//	{
//		return;
//	}
//	if( !ReadFile( hFile, &tTotalRegionInfoNum, 4, &nReadByte, NULL ) )
//	{
//		CloseHandle( hFile );
//		return;
//	}
//	if( nReadByte != 4 )
//	{
//		CloseHandle( hFile );
//		return;
//	}
//	if( tTotalRegionInfoNum > 0 )
//	{
//		tRegionInfo = (WORLD_REGION_INFO *) GlobalAlloc( GMEM_FIXED, ( tTotalRegionInfoNum * sizeof( WORLD_REGION_INFO ) ) );
//		if( tRegionInfo == NULL )
//		{
//			CloseHandle( hFile );
//			return;
//		}
//		if( !ReadFile( hFile, &tRegionInfo[0], ( tTotalRegionInfoNum * sizeof( WORLD_REGION_INFO ) ), &nReadByte, NULL ) )
//		{
//			GlobalFree( tRegionInfo );
//			CloseHandle( hFile );
//			return;
//		}
//		if( nReadByte != ( tTotalRegionInfoNum * sizeof( WORLD_REGION_INFO ) ) )
//		{
//			GlobalFree( tRegionInfo );
//			CloseHandle( hFile );
//			return;
//		}
//	}
//	else
//	{
//		tTotalRegionInfoNum = 0;
//		tRegionInfo = NULL;
//	}
//	if( !CloseHandle( hFile ) )
//	{
//		GlobalFree( tRegionInfo );
//		return;
//	}
//	mTotalMonsterSummonInfoNum = tTotalRegionInfoNum;
//	mMONSTER_SUMMON = tRegionInfo;
//	index02 = 0;
//	for( index01 = 0 ; index01 < mTotalMonsterSummonInfoNum ; index01++ )
//	{
//		//nova - mob slot num in caves
//		if (mGAME.mCheckZone126TypeServer == TRUE)
//		{
//			mMONSTER_SUMMON[index01].mVALUE04 = 20;//sos
//		}
//		if (mGAME.mCheckZone101TypeServer == TRUE)
//		{
//			mMONSTER_SUMMON[index01].mVALUE04 = 15;//caves
//		}
//		index02 += mMONSTER_SUMMON[index01].mVALUE04;
//	}
//	if( index02 > MAX_MONSTER_OBJECT_NUM)
//	{
//		mTotalMonsterSummonInfoNum = 0;
//		if( mMONSTER_SUMMON )
//		{
//			GlobalFree( mMONSTER_SUMMON );
//			mMONSTER_SUMMON = NULL;
//		}
//	}
//	index03 = 0;
//	for( index01 = 0 ; index01 < mTotalMonsterSummonInfoNum ; index01++ )
//	{
//		for( index02 = 0 ; index02 < mMONSTER_SUMMON[index01].mVALUE04 ; index02++ )
//		{
//			tMONSTER_INFO = mMONSTER.Search( mMONSTER_SUMMON[index01].mVALUE02 );
//			if( tMONSTER_INFO == NULL )
//			{
//				index03++;
//				continue;
//			}
//			tRandom = rand();
//			mMonsterSummonPostTime[index03] = tMONSTER_INFO->mSummonTime[0] + (int) ( ( (float) ( tMONSTER_INFO->mSummonTime[1] - tMONSTER_INFO->mSummonTime[0] ) * (float) ( tRandom % 101 ) ) / 100.0f );
//			index03++;
//		}
//	}
//}

//LOAD_REGION_INFO_1
void MySummonSystem::LoadRegionInfo_1(char* tFileName)
{
	int index01;
	int index02;
	int index03;
	DWORD nReadByte;
	int tTotalRegionInfoNum;
	WORLD_REGION_INFO* tRegionInfo;
	MONSTER_INFO* tMONSTER_INFO;
	unsigned int tRandom = 0;

	HANDLE hFile;
	hFile = CreateFile(tFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return;
	}
	if (!ReadFile(hFile, &tTotalRegionInfoNum, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return;
	}
	if (tTotalRegionInfoNum > 0)
	{
		tRegionInfo = (WORLD_REGION_INFO*)GlobalAlloc(GMEM_FIXED, (tTotalRegionInfoNum * sizeof(WORLD_REGION_INFO)));
		if (tRegionInfo == NULL)
		{
			CloseHandle(hFile);
			return;
		}
		if (!ReadFile(hFile, &tRegionInfo[0], (tTotalRegionInfoNum * sizeof(WORLD_REGION_INFO)), &nReadByte, NULL))
		{
			GlobalFree(tRegionInfo);
			CloseHandle(hFile);
			return;
		}
		if (nReadByte != (tTotalRegionInfoNum * sizeof(WORLD_REGION_INFO)))
		{
			GlobalFree(tRegionInfo);
			CloseHandle(hFile);
			return;
		}
	}
	else
	{
		tTotalRegionInfoNum = 0;
		tRegionInfo = NULL;
	}
	if (!CloseHandle(hFile))
	{
		GlobalFree(tRegionInfo);
		return;
	}
	mTotalMonsterSummonInfoNum = tTotalRegionInfoNum;
	mMONSTER_SUMMON = tRegionInfo;
	index02 = 0;
	for (index01 = 0; index01 < mTotalMonsterSummonInfoNum; index01++)
	{
		index02 += mMONSTER_SUMMON[index01].mVALUE04;
	}
	if (index02 > MAX_MONSTER_OBJECT_BASE_1_NUM)
	{
		mTotalMonsterSummonInfoNum = 0;
		if (mMONSTER_SUMMON)
		{
			GlobalFree(mMONSTER_SUMMON);
			mMONSTER_SUMMON = NULL;
		}
	}
	index03 = 0;
	for (index01 = 0; index01 < mTotalMonsterSummonInfoNum; index01++)
	{
		for (index02 = 0; index02 < mMONSTER_SUMMON[index01].mVALUE04; index02++)
		{
			tMONSTER_INFO = mMONSTER.Search(mMONSTER_SUMMON[index01].mVALUE02);
			if (tMONSTER_INFO == NULL)
			{
				index03++;
				continue;
			}
			tRandom = rand();
			mMonsterSummonPostTime[index03] = tMONSTER_INFO->mSummonTime[0] + (int)(((float)(tMONSTER_INFO->mSummonTime[1] - tMONSTER_INFO->mSummonTime[0]) * (float)(tRandom % 101)) / 100.0f);
			index03++;
		}
	}
}

////LOAD_REGION_INFO_2
//void MySummonSystem::LoadRegionInfo_2( char *tFileName )
//{
//	DWORD nReadByte;
//	int tTotalRegionInfoNum;
//	WORLD_REGION_INFO *tRegionInfo;
//	HANDLE hFile;
//	hFile = CreateFile( tFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
//	if( hFile == INVALID_HANDLE_VALUE )
//	{
//		return;
//	}
//	if( !ReadFile( hFile, &tTotalRegionInfoNum, 4, &nReadByte, NULL ) )
//	{
//		CloseHandle( hFile );
//		return;
//	}
//	if( nReadByte != 4 )
//	{
//		CloseHandle( hFile );
//		return;
//	}
//	if( tTotalRegionInfoNum > 0 )
//	{
//		tRegionInfo = (WORLD_REGION_INFO *) GlobalAlloc( GMEM_FIXED, ( tTotalRegionInfoNum * sizeof( WORLD_REGION_INFO ) ) );
//		if( tRegionInfo == NULL )
//		{
//			CloseHandle( hFile );
//			return;
//		}
//		if( !ReadFile( hFile, &tRegionInfo[0], ( tTotalRegionInfoNum * sizeof( WORLD_REGION_INFO ) ), &nReadByte, NULL ) )
//		{
//			GlobalFree( tRegionInfo );
//			CloseHandle( hFile );
//			return;
//		}
//		if( nReadByte != ( tTotalRegionInfoNum * sizeof( WORLD_REGION_INFO ) ) )
//		{
//			GlobalFree( tRegionInfo );
//			CloseHandle( hFile );
//			return;
//		}
//	}
//	else
//	{
//		tTotalRegionInfoNum = 0;
//		tRegionInfo = NULL;
//	}
//	if( !CloseHandle( hFile ) )
//	{
//		GlobalFree( tRegionInfo );
//		return;
//	}
//	mTotalBossMonsterSummonInfoNum = tTotalRegionInfoNum;
//	mBOSS_MONSTER_SUMMON = tRegionInfo;
//	mBossMonsterSummonState = 1;
//	mPostTickCountForBossMonsterSummon = GetTickCount();
//}
//LOAD_REGION_INFO_2
void MySummonSystem::LoadRegionInfo_2(char* tFileName)
{
	DWORD nReadByte;
	int tTotalRegionInfoNum;
	WORLD_REGION_INFO* tRegionInfo;
	HANDLE hFile;
	hFile = CreateFile(tFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return;
	}
	if (!ReadFile(hFile, &tTotalRegionInfoNum, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return;
	}
	if (tTotalRegionInfoNum > 0)
	{
		tRegionInfo = (WORLD_REGION_INFO*)GlobalAlloc(GMEM_FIXED, (tTotalRegionInfoNum * sizeof(WORLD_REGION_INFO)));
		if (tRegionInfo == NULL)
		{
			CloseHandle(hFile);
			return;
		}
		if (!ReadFile(hFile, &tRegionInfo[0], (tTotalRegionInfoNum * sizeof(WORLD_REGION_INFO)), &nReadByte, NULL))
		{
			GlobalFree(tRegionInfo);
			CloseHandle(hFile);
			return;
		}
		if (nReadByte != (tTotalRegionInfoNum * sizeof(WORLD_REGION_INFO)))
		{
			GlobalFree(tRegionInfo);
			CloseHandle(hFile);
			return;
		}
	}
	else
	{
		tTotalRegionInfoNum = 0;
		tRegionInfo = NULL;
	}
	if (!CloseHandle(hFile))
	{
		GlobalFree(tRegionInfo);
		return;
	}
	mTotalBossMonsterSummonInfoNum = tTotalRegionInfoNum;
	mBOSS_MONSTER_SUMMON = tRegionInfo;
	mBossMonsterSummonState = 1;
	mPostTickCountForBossMonsterSummon = GetTickCount64();
}


//RETURN_SPECIAL_SORT_NUMBER
int MySummonSystem::ReturnSpecialSortNumber( MONSTER_INFO *tMONSTER_INFO )
{
	switch( tMONSTER_INFO->mType )
	{
	case 1 :
		switch( tMONSTER_INFO->mSpecialType )
		{
		case 10: return 2;
		case 11 : return 2;
		case 12 : return 2;
		case 13 : return 2;
		case 28 : return 2;
		case 14 : return 2;
		case 15 : return 2;
		case 21 : return 3;
		case 22 : return 3;
		case 23 : return 3;
		case 29 : return 3;
		case 31 : return 4;
		case 32 : return 4;
		case 33 : return 4;
		case 34 : return 4;
		case 18 : return 6;
		case 35 : return 6;
		case 36 : return 6;
		case 37 : return 6;
		case 38 : return 6;
		}
		break;
	case 6 : return 5;
	case 7 : return 5;
	case 8 : return 5;
	case 9 : return 5;
	}
	return 1;
}
//DELETE_MONSTER
void MySummonSystem::DeleteMonster( void )
{
	int index01;

	for( index01 = 0 ; index01 < MAX_MONSTER_OBJECT_NUM ; index01++ )
	{
		mMONSTER_OBJECT[index01].mCheckValidState = FALSE;
		mMONSTER_OBJECT[index01].mInvalidTimeForSummon = GetTickCount();
	}
}
////SUMMON_MONSTER

void MySummonSystem::SummonMonster(void)
{
	int index01;
	int index02;
	int index03;
	MONSTER_INFO* tMONSTER_INFO;
	float tDirection[3];
	float tLength;
	float tRadius;
	float tLocation[3];
	unsigned int tRandom = 0;

	index03 = 0;
	for (index01 = 0; index01 < mTotalMonsterSummonInfoNum; index01++)
	{
		for (index02 = 0; index02 < mMONSTER_SUMMON[index01].mVALUE04; index02++)
		{
			if (mMONSTER_OBJECT[index03].mCheckValidState)
			{
				index03++;
				continue;
			}
			tMONSTER_INFO = mMONSTER.Search(mMONSTER_SUMMON[index01].mVALUE02);
			if (tMONSTER_INFO == NULL)
			{
				index03++;
				continue;
			}
			if (((float)(GetTickCount64() - mMONSTER_OBJECT[index03].mInvalidTimeForSummon) / 1000.0f) < (float)mMonsterSummonPostTime[index03])
			{
				index03++;
				continue;
			}
			tDirection[0] = mUTIL.RandomNumber(-100.0f, 100.0f);
			tDirection[2] = mUTIL.RandomNumber(-100.0f, 100.0f);
			tLength = sqrtf(tDirection[0] * tDirection[0] + tDirection[2] * tDirection[2]);
			if (tLength > 0.0f)
			{
				tDirection[0] /= tLength;
				tDirection[2] /= tLength;
			}
			if (mMONSTER_SUMMON[index01].mRADIUS > 0)
			{
				tRandom = rand();
				tRadius = (float)(tRandom % mMONSTER_SUMMON[index01].mRADIUS);
			}
			else
			{
				tRadius = 0.0f;
			}
			tLocation[0] = (float)mMONSTER_SUMMON[index01].mCENTER[0] + tDirection[0] * tRadius;
			tLocation[2] = (float)mMONSTER_SUMMON[index01].mCENTER[2] + tDirection[2] * tRadius;
			if (!mWORLD.GetYCoord(tLocation[0], tLocation[2], &tLocation[1], FALSE, 0.0f, FALSE, TRUE))
			{
				index03++;
				continue;
			}
			tRandom = rand();
			mMonsterSummonPostTime[index03] = tMONSTER_INFO->mSummonTime[0] + (int)(((float)(tMONSTER_INFO->mSummonTime[1] - tMONSTER_INFO->mSummonTime[0]) * (float)(tRandom % 101)) / 100.0f);
			mMONSTER_OBJECT[index03].mCheckValidState = TRUE;
			mMONSTER_OBJECT[index03].mUniqueNumber = mGAME.mMonsterObjectUniqueNumber;
			mGAME.mMonsterObjectUniqueNumber++;
			mMONSTER_OBJECT[index03].mDATA.mIndex = tMONSTER_INFO->mIndex;
			mMONSTER_OBJECT[index03].mDATA.mAction.aType = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aSort = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aFrame = 0.0f;
			mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0] = tLocation[0];
			mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[1] = tLocation[1];
			mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[2] = tLocation[2];
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetLocation[0] = 0.0f;
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetLocation[1] = 0.0f;
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetLocation[2] = 0.0f;
			tRandom = rand();
			mMONSTER_OBJECT[index03].mDATA.mAction.aFront = (float)(tRandom % 360);
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetFront = 0.0f;
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetObjectSort = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetObjectIndex = -1;
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetObjectUniqueNumber = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aSkillNumber = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aSkillGradeNum1 = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aSkillGradeNum2 = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aSkillValue = 0;
			mMONSTER_OBJECT[index03].mDATA.mLifeValue = tMONSTER_INFO->mLife;
			mMONSTER_OBJECT[index03].SetSpaceIndex();
			mMONSTER_OBJECT[index03].mMONSTER_INFO = tMONSTER_INFO;
			tRandom = rand();
			mMONSTER_OBJECT[index03].mSameTargetPostNum = tMONSTER_INFO->mFollowInfo[0] + (tRandom % (tMONSTER_INFO->mFollowInfo[1] - tMONSTER_INFO->mFollowInfo[0] + 1));
			mMONSTER_OBJECT[index03].mInvalidTimeForSummon = GetTickCount64();
			mMONSTER_OBJECT[index03].mCheckFirstLocationTime = GetTickCount64();
			mMONSTER_OBJECT[index03].mFirstLocation[0] = tLocation[0];
			mMONSTER_OBJECT[index03].mFirstLocation[1] = tLocation[1];
			mMONSTER_OBJECT[index03].mFirstLocation[2] = tLocation[2];
			mMONSTER_OBJECT[index03].mCheckDetectEnemyTime = GetTickCount64();
			mMONSTER_OBJECT[index03].mCheckAttackState = FALSE;
			mMONSTER_OBJECT[index03].mTotalAttackNum = 0;
			mMONSTER_OBJECT[index03].mUpdateTimeForBroadcast = GetTickCount64();
			mMONSTER_OBJECT[index03].mSpecialSortNumber = ReturnSpecialSortNumber(tMONSTER_INFO);
			mMONSTER_OBJECT[index03].mCheckFirstAttackForTribeSymbol = FALSE;
			mMONSTER_OBJECT[index03].mFirstAttackTimeForTribeSymbol = GetTickCount64();
			mMONSTER_OBJECT[index03].mTribeDamageForTribeSymbol[0] = 0;
			mMONSTER_OBJECT[index03].mTribeDamageForTribeSymbol[1] = 0;
			mMONSTER_OBJECT[index03].mTribeDamageForTribeSymbol[2] = 0;
			mMONSTER_OBJECT[index03].mTribeDamageForTribeSymbol[3] = 0;
			mMONSTER_OBJECT[index03].mCheckFirstAttackForAllianceStone = FALSE;
			mMONSTER_OBJECT[index03].mFirstAttackTimeForAllianceStone = GetTickCount64();
			mMONSTER_OBJECT[index03].mCheckAttackPacketRecv = FALSE;
			mMONSTER_OBJECT[index03].mRadiusForSize = sqrtf((float)(tMONSTER_INFO->mSize[0] * tMONSTER_INFO->mSize[0] + tMONSTER_INFO->mSize[2] * tMONSTER_INFO->mSize[2])) * 0.5f;
			//------------------------//
			//BROADCAST_MONSTER_ACTION//
			//------------------------//
			mTRANSFER.B_MONSTER_ACTION_RECV(index03, mMONSTER_OBJECT[index03].mUniqueNumber, &mMONSTER_OBJECT[index03].mDATA, 1);
			//-----------------------------------------------------------------//
			//[01].일반,[02].성석,[03].수호비,[04].동맹석,[05].수호석,[06].석차//
			//-----------------------------------------------------------------//
			switch (mMONSTER_OBJECT[index03].mSpecialSortNumber)
			{
			case 1:
				mUTIL.Broadcast(TRUE, &mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS1, false, 0);
				break;
			case 2:
				mUTIL.Broadcast(TRUE, &mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
				break;
			case 3:
				mUTIL.Broadcast(TRUE, &mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
				break;
			case 4:
				mUTIL.Broadcast(TRUE, &mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
				break;
			case 5:
				mUTIL.Broadcast(TRUE, &mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS2, false, 0);
				break;
			case 6:
				mUTIL.Broadcast(TRUE, &mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
				break;
			}
			//------------------------//
			//------------------------//
			//------------------------//
			index03++;
		}
	}
}


//void MySummonSystem::SummonMonster( void )
//{
//	int index01;
//	int index02;
//	int index03;
//	MONSTER_INFO *tMONSTER_INFO;
//	float tDirection[3];
//	float tLength;
//	float tRadius;
//	float tLocation[3];
//	unsigned int tRandom = 0;
//
//	if (mSERVER_INFO.mServerNumber == 235 || mSERVER_INFO.mServerNumber == 236 ||
//		mSERVER_INFO.mServerNumber == 237 || mSERVER_INFO.mServerNumber == 238 || mSERVER_INFO.mServerNumber == 239 || mSERVER_INFO.mServerNumber == 240)
//	{
//		return;
//	}
//
//	index03 = 0;
//	for( index01 = 0 ; index01 < mTotalMonsterSummonInfoNum ; index01++ )
//	{
//		for( index02 = 0 ; index02 < mMONSTER_SUMMON[index01].mVALUE04 ; index02++ )
//		{
//			if( mMONSTER_OBJECT[index03].mCheckValidState )
//			{
//				index03++;
//				continue;
//			}
//			//nova - caves mobs 
//			/*mGAME.mCheckZone101TypeServer == TRUE ||*/
//			if ( mGAME.mCheckZone126TypeServer == TRUE || mGAME.mCheckZone200TypeServer == TRUE)
//			{
//				mMONSTER_SUMMON[index01].mVALUE02 = 120;
//				mMONSTER_SUMMON[index01].mRADIUS = 175;
//			}
//			tMONSTER_INFO = mMONSTER.Search( mMONSTER_SUMMON[index01].mVALUE02 );
//			if( tMONSTER_INFO == NULL )
//			{
//				index03++;
//				continue;
//			}
//			if( ( (float) ( GetTickCount() - mMONSTER_OBJECT[index03].mInvalidTimeForSummon ) / 1000.0f ) < (float) mMonsterSummonPostTime[index03] )
//			{
//				index03++;
//				continue;
//			}
//			tDirection[0] = mUTIL.RandomNumber( -100.0f, 100.0f );
//			tDirection[2] = mUTIL.RandomNumber( -100.0f, 100.0f );
//			tLength = sqrtf( tDirection[0] * tDirection[0] + tDirection[2] * tDirection[2] );
//			if( tLength > 0.0f )
//			{
//				tDirection[0] /= tLength;
//				tDirection[2] /= tLength;
//			}
//			if( mMONSTER_SUMMON[index01].mRADIUS > 0 )
//			{
//				tRandom = rand();
//				tRadius = (float) ( tRandom % mMONSTER_SUMMON[index01].mRADIUS );
//			}
//			else
//			{
//				tRadius = 0.0f;
//			}
//			tLocation[0] = (float) mMONSTER_SUMMON[index01].mCENTER[0] + tDirection[0] * tRadius;
//			tLocation[2] = (float) mMONSTER_SUMMON[index01].mCENTER[2] + tDirection[2] * tRadius;
//			if( !mWORLD.GetYCoord( tLocation[0], tLocation[2], &tLocation[1], FALSE, 0.0f, FALSE, TRUE ) )
//			{
//				index03++;
//				continue;
//			}
//
//			tRandom = rand();
//			mMonsterSummonPostTime[index03] = tMONSTER_INFO->mSummonTime[0] + (int) ( ( (float) ( tMONSTER_INFO->mSummonTime[1] - tMONSTER_INFO->mSummonTime[0] ) * (float) ( tRandom % 101 ) ) / 100.0f );
//			//Katlardaki mobb
//			if (mGAME.mCheckZone126TypeServer == TRUE)
//			{
//				mMonsterSummonPostTime[index03] = 4;
//			}
//			mMONSTER_OBJECT[index03].mCheckValidState = TRUE;
//			mMONSTER_OBJECT[index03].mUniqueNumber = mGAME.mMonsterObjectUniqueNumber;
//			mGAME.mMonsterObjectUniqueNumber++;
//			mMONSTER_OBJECT[index03].mDATA.mIndex = tMONSTER_INFO->mIndex;
//			mMONSTER_OBJECT[index03].mDATA.mAction.aType = 0;
//			mMONSTER_OBJECT[index03].mDATA.mAction.aSort = 0;
//			mMONSTER_OBJECT[index03].mDATA.mAction.aFrame = 0.0f;
//			mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0] = tLocation[0];
//			mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[1] = tLocation[1];
//			mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[2] = tLocation[2];
//			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetLocation[0] = 0.0f;
//			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetLocation[1] = 0.0f;
//			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetLocation[2] = 0.0f;
//			tRandom = rand();
//			mMONSTER_OBJECT[index03].mDATA.mAction.aFront = (float) ( tRandom % 360 );
//			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetFront = 0.0f;
//			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetObjectSort = 0;
//			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetObjectIndex = -1;
//			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetObjectUniqueNumber = 0;
//			mMONSTER_OBJECT[index03].mDATA.mAction.aSkillNumber = 0;
//			mMONSTER_OBJECT[index03].mDATA.mAction.aSkillGradeNum1 = 0;
//			mMONSTER_OBJECT[index03].mDATA.mAction.aSkillGradeNum2 = 0;
//			mMONSTER_OBJECT[index03].mDATA.mAction.aSkillValue = 0;
//			mMONSTER_OBJECT[index03].mDATA.mLifeValue = tMONSTER_INFO->mLife;
//			mMONSTER_OBJECT[index03].SetSpaceIndex();
//			mMONSTER_OBJECT[index03].mMONSTER_INFO = tMONSTER_INFO;
//			tRandom = rand();
//			mMONSTER_OBJECT[index03].mSameTargetPostNum = tMONSTER_INFO->mFollowInfo[0] + ( tRandom % ( tMONSTER_INFO->mFollowInfo[1] - tMONSTER_INFO->mFollowInfo[0] + 1 ) );
//			mMONSTER_OBJECT[index03].mInvalidTimeForSummon = GetTickCount();
//			mMONSTER_OBJECT[index03].mCheckFirstLocationTime = GetTickCount();
//			mMONSTER_OBJECT[index03].mFirstLocation[0] = tLocation[0];
//			mMONSTER_OBJECT[index03].mFirstLocation[1] = tLocation[1];
//			mMONSTER_OBJECT[index03].mFirstLocation[2] = tLocation[2];
//			mMONSTER_OBJECT[index03].mCheckDetectEnemyTime = GetTickCount();
//			mMONSTER_OBJECT[index03].mCheckAttackState = FALSE;
//			mMONSTER_OBJECT[index03].mTotalAttackNum = 0;
//			mMONSTER_OBJECT[index03].mUpdateTimeForBroadcast = GetTickCount();
//			mMONSTER_OBJECT[index03].mSpecialSortNumber = ReturnSpecialSortNumber( tMONSTER_INFO );
//			mMONSTER_OBJECT[index03].mCheckFirstAttackForTribeSymbol = FALSE;
//			mMONSTER_OBJECT[index03].mFirstAttackTimeForTribeSymbol = GetTickCount();
//			mMONSTER_OBJECT[index03].mTribeDamageForTribeSymbol[0] = 0;
//			mMONSTER_OBJECT[index03].mTribeDamageForTribeSymbol[1] = 0;
//			mMONSTER_OBJECT[index03].mTribeDamageForTribeSymbol[2] = 0;
//			mMONSTER_OBJECT[index03].mTribeDamageForTribeSymbol[3] = 0;
//			mMONSTER_OBJECT[index03].mCheckFirstAttackForAllianceStone = FALSE;
//			mMONSTER_OBJECT[index03].mFirstAttackTimeForAllianceStone = GetTickCount();
//			mMONSTER_OBJECT[index03].mCheckAttackPacketRecv = FALSE;
//			mMONSTER_OBJECT[index03].mRadiusForSize = sqrtf( (float) ( tMONSTER_INFO->mSize[0] * tMONSTER_INFO->mSize[0] + tMONSTER_INFO->mSize[2] * tMONSTER_INFO->mSize[2] ) ) * 0.5f;
//			//------------------------//
//			//BROADCAST_MONSTER_ACTION//
//			//------------------------//
//			mTRANSFER.B_MONSTER_ACTION_RECV( index03, mMONSTER_OBJECT[index03].mUniqueNumber, &mMONSTER_OBJECT[index03].mDATA, 1 );
//			//-----------------------------------------------------------------//
//			//[01].일반,[02].성석,[03].수호비,[04].동맹석,[05].수호석,[06].석차//
//			//-----------------------------------------------------------------//
//			switch( mMONSTER_OBJECT[index03].mSpecialSortNumber )
//			{
//			case 1 :
//                mUTIL.Broadcast( TRUE, &mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS1, false, 0 );
//				break;
//			case 2 :
//                mUTIL.Broadcast( TRUE, &mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0 );
//				break;
//			case 3 :
//                mUTIL.Broadcast( TRUE, &mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0 );
//				break;
//			case 4 :
//                mUTIL.Broadcast( TRUE, &mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0 );
//				break;
//			case 5 :
//                mUTIL.Broadcast( TRUE, &mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS2, false, 0 );
//				break;
//			case 6 :
//                mUTIL.Broadcast( TRUE, &mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0 );
//				break;
//			}
//			//------------------------//
//			//------------------------//
//			//------------------------//
//			index03++;
//		}
//	}
//}
//SUMMON_BOSS_MONSTER
void MySummonSystem::SummonBossMonster( void )
{
	int index01;
	int tSelectRegionInfoIndex;
	MONSTER_INFO *tMONSTER_INFO;
	int tTotalBossMonsterNum;
	unsigned int tRandom = 0;

	if( mTotalBossMonsterSummonInfoNum < 1 )
	{
		return;
	}
	switch( mBossMonsterSummonState )
	{
	case 1 :
		if( ( GetTickCount() - mPostTickCountForBossMonsterSummon ) < 10800000 )
		{
			return;
		}
		tRandom = rand();
		tSelectRegionInfoIndex = tRandom % mTotalBossMonsterSummonInfoNum;
		tMONSTER_INFO = mMONSTER.Search( mBOSS_MONSTER_SUMMON[tSelectRegionInfoIndex].mVALUE02 );
		if( tMONSTER_INFO == NULL )
		{
			return;
		}
		tTotalBossMonsterNum = 0;
		for( index01 = MAX_MONSTER_OBJECT_BASE_5_NUM ; index01 < MAX_MONSTER_OBJECT_NUM ; index01++ )
		{
			if( mMONSTER_OBJECT[index01].mCheckValidState )
			{
				continue;
			}
			mMONSTER_OBJECT[index01].mCheckValidState = TRUE;
			mMONSTER_OBJECT[index01].mUniqueNumber = mGAME.mMonsterObjectUniqueNumber;
			mGAME.mMonsterObjectUniqueNumber++;
			mMONSTER_OBJECT[index01].mDATA.mIndex = tMONSTER_INFO->mIndex;
			mMONSTER_OBJECT[index01].mDATA.mAction.aType = 0;
			mMONSTER_OBJECT[index01].mDATA.mAction.aSort = 0;
			mMONSTER_OBJECT[index01].mDATA.mAction.aFrame = 0.0f;
			mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0] = (float) mMONSTER_SUMMON[tSelectRegionInfoIndex].mCENTER[0];
			mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[1] = (float) mMONSTER_SUMMON[tSelectRegionInfoIndex].mCENTER[1];
			mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[2] = (float) mMONSTER_SUMMON[tSelectRegionInfoIndex].mCENTER[2];
			mMONSTER_OBJECT[index01].mDATA.mAction.aTargetLocation[0] = 0.0f;
			mMONSTER_OBJECT[index01].mDATA.mAction.aTargetLocation[1] = 0.0f;
			mMONSTER_OBJECT[index01].mDATA.mAction.aTargetLocation[2] = 0.0f;
			tRandom = rand();
			mMONSTER_OBJECT[index01].mDATA.mAction.aFront = (float) ( tRandom % 360 );
			mMONSTER_OBJECT[index01].mDATA.mAction.aTargetFront = 0.0f;
			mMONSTER_OBJECT[index01].mDATA.mAction.aTargetObjectSort = 0;
			mMONSTER_OBJECT[index01].mDATA.mAction.aTargetObjectIndex = -1;
			mMONSTER_OBJECT[index01].mDATA.mAction.aTargetObjectUniqueNumber = 0;
			mMONSTER_OBJECT[index01].mDATA.mAction.aSkillNumber = 0;
			mMONSTER_OBJECT[index01].mDATA.mAction.aSkillGradeNum1 = 0;
			mMONSTER_OBJECT[index01].mDATA.mAction.aSkillGradeNum2 = 0;
			mMONSTER_OBJECT[index01].mDATA.mAction.aSkillValue = 0;
			mMONSTER_OBJECT[index01].mDATA.mLifeValue = tMONSTER_INFO->mLife;
			mMONSTER_OBJECT[index01].SetSpaceIndex();
			mMONSTER_OBJECT[index01].mMONSTER_INFO = tMONSTER_INFO;
			tRandom = rand();
			mMONSTER_OBJECT[index01].mSameTargetPostNum = tMONSTER_INFO->mFollowInfo[0] + ( tRandom % ( tMONSTER_INFO->mFollowInfo[1] - tMONSTER_INFO->mFollowInfo[0] + 1 ) );
			mMONSTER_OBJECT[index01].mInvalidTimeForSummon = GetTickCount();
			mMONSTER_OBJECT[index01].mCheckFirstLocationTime = GetTickCount();
			mMONSTER_OBJECT[index01].mFirstLocation[0] = (float) mMONSTER_SUMMON[tSelectRegionInfoIndex].mCENTER[0];
			mMONSTER_OBJECT[index01].mFirstLocation[1] = (float) mMONSTER_SUMMON[tSelectRegionInfoIndex].mCENTER[1];
			mMONSTER_OBJECT[index01].mFirstLocation[2] = (float) mMONSTER_SUMMON[tSelectRegionInfoIndex].mCENTER[2];
			mMONSTER_OBJECT[index01].mCheckDetectEnemyTime = GetTickCount();
			mMONSTER_OBJECT[index01].mCheckAttackState = FALSE;
			mMONSTER_OBJECT[index01].mTotalAttackNum = 0;
			mMONSTER_OBJECT[index01].mUpdateTimeForBroadcast = GetTickCount();
			mMONSTER_OBJECT[index01].mSpecialSortNumber = ReturnSpecialSortNumber( tMONSTER_INFO );
			mMONSTER_OBJECT[index01].mCheckFirstAttackForTribeSymbol = FALSE;
			mMONSTER_OBJECT[index01].mFirstAttackTimeForTribeSymbol = GetTickCount();
			mMONSTER_OBJECT[index01].mTribeDamageForTribeSymbol[0] = 0;
			mMONSTER_OBJECT[index01].mTribeDamageForTribeSymbol[1] = 0;
			mMONSTER_OBJECT[index01].mTribeDamageForTribeSymbol[2] = 0;
			mMONSTER_OBJECT[index01].mTribeDamageForTribeSymbol[3] = 0;
			mMONSTER_OBJECT[index01].mCheckFirstAttackForAllianceStone = FALSE;
			mMONSTER_OBJECT[index01].mFirstAttackTimeForAllianceStone = GetTickCount();
			mMONSTER_OBJECT[index01].mCheckAttackPacketRecv = FALSE;
			mMONSTER_OBJECT[index01].mRadiusForSize = sqrtf( (float) ( tMONSTER_INFO->mSize[0] * tMONSTER_INFO->mSize[0] + tMONSTER_INFO->mSize[2] * tMONSTER_INFO->mSize[2] ) ) * 0.5f;
			//------------------------//
			//BROADCAST_MONSTER_ACTION//
			//------------------------//
			mTRANSFER.B_MONSTER_ACTION_RECV( index01, mMONSTER_OBJECT[index01].mUniqueNumber, &mMONSTER_OBJECT[index01].mDATA, 1 );
			//-----------------------------------------------------------------//
			//[01].일반,[02].성석,[03].수호비,[04].동맹석,[05].수호석,[06].석차//
			//-----------------------------------------------------------------//
			switch( mMONSTER_OBJECT[index01].mSpecialSortNumber )
			{
			case 1 :
                mUTIL.Broadcast( TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS1, false, 0 );
				break;
			case 2 :
                mUTIL.Broadcast( TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0 );
				break;
			case 3 :
                mUTIL.Broadcast( TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0 );
				break;
			case 4 :
                mUTIL.Broadcast( TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0 );
				break;
			case 5 :
                mUTIL.Broadcast( TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS2, false, 0 );
				break;
			case 6 :
                mUTIL.Broadcast( TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0 );
				break;
			}
			//------------------------//
			//------------------------//
			//------------------------//
			tTotalBossMonsterNum++;
			if( tTotalBossMonsterNum == 5 )
			{
				break;
			}
		}
		mBossMonsterSummonState = 2;
		mPostTickCountForBossMonsterSummon = GetTickCount();
		return;
	case 2 :
		for( index01 = MAX_MONSTER_OBJECT_BASE_5_NUM ; index01 < MAX_MONSTER_OBJECT_NUM ; index01++ )
		{
			if( !mMONSTER_OBJECT[index01].mCheckValidState )
			{
				continue;
			}
			if( mMONSTER_OBJECT[index01].mMONSTER_INFO->mIndex == mBOSS_MONSTER_SUMMON[0].mVALUE02 )
			{
				return;
			}
		}
		mBossMonsterSummonState = 1;
		mPostTickCountForBossMonsterSummon = GetTickCount();
		return;
	}
}
//SUMMON_MONSTER_WITHOUT_TIME_LIMIT
void MySummonSystem::SummonMonsterWithoutTimeLimit( void )
{
	int index01;
	int index02;
	int index03;
	char tFileName[1000];
	MONSTER_INFO *tMONSTER_INFO;
	float tDirection[3];
	float tLength;
	float tRadius;
	float tLocation[3];
	unsigned int tRandom = 0;

	Free();
	/*
	char tFileNamePart01[4];
	tFileNamePart01[0] = ( mSERVER_INFO.mServerNumber % 1000 ) / 100 + '0';
	tFileNamePart01[1] = ( mSERVER_INFO.mServerNumber % 100 ) / 10 + '0';
	tFileNamePart01[2] = ( mSERVER_INFO.mServerNumber % 10 ) / 1 + '0';
	tFileNamePart01[3] = '\0';
	//sprintf( tFileName, "DATA\\Z%s_SUMMONMONSTER.WREGION", tFileNamePart01 );
	*/
	if (mGAME.mCheckZone101TypeServer == TRUE)
	{
		sprintf(tFileName, "DATA/Shuaguai/Z104_SUMMONMONSTER.WREGION");
	}
	else if (mGAME.mCheckZone126TypeServer == TRUE)
	{
		sprintf(tFileName, "DATA/Shuaguai/Z126_SUMMONMONSTER.WREGION");
	}
	else
	{
		sprintf(tFileName, "DATA/Shuaguai/Z%03d_SUMMONMONSTER.WREGION", mSERVER_INFO.mServerNumber);
	}
	LoadRegionInfo_1(tFileName);
	index03 = 0;
	for( index01 = 0 ; index01 < mTotalMonsterSummonInfoNum ; index01++ )
	{
		for( index02 = 0 ; index02 < mMONSTER_SUMMON[index01].mVALUE04 ; index02++ )
		{
			if( mMONSTER_OBJECT[index03].mCheckValidState )
			{
				index03++;
				continue;
			}
			//Katlardaki mobb
			if (mGAME.mCheckZone101TypeServer == TRUE || mGAME.mCheckZone126TypeServer == TRUE)
			{
				mMONSTER_SUMMON[index01].mVALUE02 = 120;
			}

			tMONSTER_INFO = mMONSTER.Search( mMONSTER_SUMMON[index01].mVALUE02 );
			if( tMONSTER_INFO == NULL )
			{
				index03++;
				continue;
			}
			tDirection[0] = mUTIL.RandomNumber( -100.0f, 100.0f );
			tDirection[2] = mUTIL.RandomNumber( -100.0f, 100.0f );
			tLength = sqrtf( tDirection[0] * tDirection[0] + tDirection[2] * tDirection[2] );
			if( tLength > 0.0f )
			{
				tDirection[0] /= tLength;
				tDirection[2] /= tLength;
			}
			if( mMONSTER_SUMMON[index01].mRADIUS > 0 )
			{
				tRandom = rand();
				tRadius = (float) ( tRandom % mMONSTER_SUMMON[index01].mRADIUS );
			}
			else
			{
				tRadius = 0.0f;
			}
			tLocation[0] = (float) mMONSTER_SUMMON[index01].mCENTER[0] + tDirection[0] * tRadius;
			tLocation[2] = (float) mMONSTER_SUMMON[index01].mCENTER[2] + tDirection[2] * tRadius;
			if( !mWORLD.GetYCoord( tLocation[0], tLocation[2], &tLocation[1], FALSE, 0.0f, FALSE, TRUE ) )
			{
				index03++;
				continue;
			}
			mMonsterSummonPostTime[index03] = tMONSTER_INFO->mSummonTime[0];
			mMONSTER_OBJECT[index03].mCheckValidState = TRUE;
			mMONSTER_OBJECT[index03].mUniqueNumber = mGAME.mMonsterObjectUniqueNumber;
			mGAME.mMonsterObjectUniqueNumber++;
			mMONSTER_OBJECT[index03].mDATA.mIndex = tMONSTER_INFO->mIndex;
			mMONSTER_OBJECT[index03].mDATA.mAction.aType = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aSort = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aFrame = 0.0f;
			mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0] = tLocation[0];
			mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[1] = tLocation[1];
			mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[2] = tLocation[2];
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetLocation[0] = 0.0f;
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetLocation[1] = 0.0f;
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetLocation[2] = 0.0f;
			tRandom = rand();
			mMONSTER_OBJECT[index03].mDATA.mAction.aFront = (float) ( tRandom % 360 );
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetFront = 0.0f;
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetObjectSort = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetObjectIndex = -1;
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetObjectUniqueNumber = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aSkillNumber = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aSkillGradeNum1 = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aSkillGradeNum2 = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aSkillValue = 0;
			mMONSTER_OBJECT[index03].mDATA.mLifeValue = tMONSTER_INFO->mLife;
			mMONSTER_OBJECT[index03].SetSpaceIndex();
			mMONSTER_OBJECT[index03].mMONSTER_INFO = tMONSTER_INFO;
			tRandom = rand();
			mMONSTER_OBJECT[index03].mSameTargetPostNum = tMONSTER_INFO->mFollowInfo[0] + ( tRandom % ( tMONSTER_INFO->mFollowInfo[1] - tMONSTER_INFO->mFollowInfo[0] + 1 ) );
			mMONSTER_OBJECT[index03].mInvalidTimeForSummon = GetTickCount();
			mMONSTER_OBJECT[index03].mCheckFirstLocationTime = GetTickCount();
			mMONSTER_OBJECT[index03].mFirstLocation[0] = tLocation[0];
			mMONSTER_OBJECT[index03].mFirstLocation[1] = tLocation[1];
			mMONSTER_OBJECT[index03].mFirstLocation[2] = tLocation[2];
			mMONSTER_OBJECT[index03].mCheckDetectEnemyTime = GetTickCount();
			mMONSTER_OBJECT[index03].mCheckAttackState = FALSE;
			mMONSTER_OBJECT[index03].mTotalAttackNum = 0;
			mMONSTER_OBJECT[index03].mUpdateTimeForBroadcast = GetTickCount();
			mMONSTER_OBJECT[index03].mSpecialSortNumber = ReturnSpecialSortNumber( tMONSTER_INFO );
			mMONSTER_OBJECT[index03].mCheckFirstAttackForTribeSymbol = FALSE;
			mMONSTER_OBJECT[index03].mFirstAttackTimeForTribeSymbol = GetTickCount();
			mMONSTER_OBJECT[index03].mTribeDamageForTribeSymbol[0] = 0;
			mMONSTER_OBJECT[index03].mTribeDamageForTribeSymbol[1] = 0;
			mMONSTER_OBJECT[index03].mTribeDamageForTribeSymbol[2] = 0;
			mMONSTER_OBJECT[index03].mTribeDamageForTribeSymbol[3] = 0;
			mMONSTER_OBJECT[index03].mCheckFirstAttackForAllianceStone = FALSE;
			mMONSTER_OBJECT[index03].mFirstAttackTimeForAllianceStone = GetTickCount();
			mMONSTER_OBJECT[index03].mCheckAttackPacketRecv = FALSE;
			mMONSTER_OBJECT[index03].mRadiusForSize = sqrtf( (float) ( tMONSTER_INFO->mSize[0] * tMONSTER_INFO->mSize[0] + tMONSTER_INFO->mSize[2] * tMONSTER_INFO->mSize[2] ) ) * 0.5f;
			//------------------------//
			//BROADCAST_MONSTER_ACTION//
			//------------------------//
			mTRANSFER.B_MONSTER_ACTION_RECV( index03, mMONSTER_OBJECT[index03].mUniqueNumber, &mMONSTER_OBJECT[index03].mDATA, 1 );
			//-----------------------------------------------------------------//
			//[01].일반,[02].성석,[03].수호비,[04].동맹석,[05].수호석,[06].석차//
			//-----------------------------------------------------------------//
			switch( mMONSTER_OBJECT[index03].mSpecialSortNumber )
			{
			case 1 :
                mUTIL.Broadcast( TRUE, &mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS1, false, 0 );
				break;
			case 2 :
                mUTIL.Broadcast( TRUE, &mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0 );
				break;
			case 3 :
                mUTIL.Broadcast( TRUE, &mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0 );
				break;
			case 4 :
                mUTIL.Broadcast( TRUE, &mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0 );
				break;
			case 5 :
                mUTIL.Broadcast( TRUE, &mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS2, false, 0 );
				break;
			case 6 :
                mUTIL.Broadcast( TRUE, &mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0 );
				break;
			}
			//------------------------//
			//------------------------//
			//------------------------//
			index03++;
		}
	}
}
//SUMMON_MONSTER_FOR_SPECIAL
void MySummonSystem::SummonMonsterForSpecial( int tMonsterNumber, float tMonsterLocation[3], BOOL tCheckExistMonster, int tUserIndex /*= -1*/ )
{
	int index01;
	unsigned int tRandom = 0;
	MONSTER_INFO *tMONSTER_INFO;

	if( tCheckExistMonster )
	{
		for( index01 = MAX_MONSTER_OBJECT_BASE_5_NUM ; index01 < MAX_MONSTER_OBJECT_NUM ; index01++ )
		{
			if( !mMONSTER_OBJECT[index01].mCheckValidState )
			{
				continue;
			}
			if( mMONSTER_OBJECT[index01].mMONSTER_INFO->mIndex == tMonsterNumber )
			{
				return;
			}
		}
	}
	for( index01 = MAX_MONSTER_OBJECT_BASE_5_NUM ; index01 < MAX_MONSTER_OBJECT_NUM ; index01++ )
	{
		if( !mMONSTER_OBJECT[index01].mCheckValidState )
		{
			break;
		}
	}
	if( index01 == MAX_MONSTER_OBJECT_NUM )
	{
		return;
	}
	tMONSTER_INFO = mMONSTER.Search( tMonsterNumber );
	if( tMONSTER_INFO == NULL )
	{
		return;
	}
	mMONSTER_OBJECT[index01].mCheckValidState = TRUE;
	mMONSTER_OBJECT[index01].mUniqueNumber = mGAME.mMonsterObjectUniqueNumber;
	mGAME.mMonsterObjectUniqueNumber++;
	mMONSTER_OBJECT[index01].mDATA.mIndex = tMONSTER_INFO->mIndex;
	mMONSTER_OBJECT[index01].mDATA.mAction.aType = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aSort = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aFrame = 0.0f;
	mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0] = tMonsterLocation[0];
	mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[1] = tMonsterLocation[1];
	mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[2] = tMonsterLocation[2];
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetLocation[0] = 0.0f;
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetLocation[1] = 0.0f;
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetLocation[2] = 0.0f;
	tRandom = rand();
	mMONSTER_OBJECT[index01].mDATA.mAction.aFront = (float) ( tRandom % 360 );
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetFront = 0.0f;
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetObjectSort = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetObjectIndex = -1;
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetObjectUniqueNumber = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aSkillNumber = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aSkillGradeNum1 = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aSkillGradeNum2 = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aSkillValue = 0;
	mMONSTER_OBJECT[index01].mDATA.mLifeValue = tMONSTER_INFO->mLife;
	mMONSTER_OBJECT[index01].SetSpaceIndex();
	mMONSTER_OBJECT[index01].mMONSTER_INFO = tMONSTER_INFO;
	tRandom = rand();
	mMONSTER_OBJECT[index01].mSameTargetPostNum = tMONSTER_INFO->mFollowInfo[0] + ( tRandom % ( tMONSTER_INFO->mFollowInfo[1] - tMONSTER_INFO->mFollowInfo[0] + 1 ) );
	mMONSTER_OBJECT[index01].mInvalidTimeForSummon = GetTickCount();
	mMONSTER_OBJECT[index01].mCheckFirstLocationTime = GetTickCount();
	mMONSTER_OBJECT[index01].mFirstLocation[0] = tMonsterLocation[0];
	mMONSTER_OBJECT[index01].mFirstLocation[1] = tMonsterLocation[1];
	mMONSTER_OBJECT[index01].mFirstLocation[2] = tMonsterLocation[2];
	mMONSTER_OBJECT[index01].mCheckDetectEnemyTime = GetTickCount();
	mMONSTER_OBJECT[index01].mCheckAttackState = FALSE;
	mMONSTER_OBJECT[index01].mTotalAttackNum = 0;
	mMONSTER_OBJECT[index01].mUpdateTimeForBroadcast = GetTickCount();
	mMONSTER_OBJECT[index01].mSpecialSortNumber = ReturnSpecialSortNumber( tMONSTER_INFO );
	mMONSTER_OBJECT[index01].mCheckFirstAttackForTribeSymbol = FALSE;
	mMONSTER_OBJECT[index01].mFirstAttackTimeForTribeSymbol = GetTickCount();
	mMONSTER_OBJECT[index01].mTribeDamageForTribeSymbol[0] = 0;
	mMONSTER_OBJECT[index01].mTribeDamageForTribeSymbol[1] = 0;
	mMONSTER_OBJECT[index01].mTribeDamageForTribeSymbol[2] = 0;
	mMONSTER_OBJECT[index01].mTribeDamageForTribeSymbol[3] = 0;
	mMONSTER_OBJECT[index01].mCheckFirstAttackForAllianceStone = FALSE;
	mMONSTER_OBJECT[index01].mFirstAttackTimeForAllianceStone = GetTickCount();
	mMONSTER_OBJECT[index01].mCheckAttackPacketRecv = FALSE;
	mMONSTER_OBJECT[index01].mRadiusForSize = sqrtf( (float) ( tMONSTER_INFO->mSize[0] * tMONSTER_INFO->mSize[0] + tMONSTER_INFO->mSize[2] * tMONSTER_INFO->mSize[2] ) ) * 0.5f;
    ::memset(mMONSTER_OBJECT[index01].mAvatarName, 0, MAX_AVATAR_NAME_LENGTH);
	if(tUserIndex != -1) { // 몬스터 소유자 정보 지정 - 지정된 소유자 외에는 타격 불가.
		::memcpy(mMONSTER_OBJECT[index01].mAvatarName, mUSER[tUserIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH);
	}
	//------------------------//
	//BROADCAST_MONSTER_ACTION//
	//------------------------//
	mTRANSFER.B_MONSTER_ACTION_RECV( index01, mMONSTER_OBJECT[index01].mUniqueNumber, &mMONSTER_OBJECT[index01].mDATA, 1 );
	//-----------------------------------------------------------------//
	//[01].일반,[02].성석,[03].수호비,[04].동맹석,[05].수호석,[06].석차//
	//-----------------------------------------------------------------//
	switch( mMONSTER_OBJECT[index01].mSpecialSortNumber )
	{
	case 1 :
        mUTIL.Broadcast( TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS1, false, 0 );
		break;
	case 2 :
        mUTIL.Broadcast( TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0 );
		break;
	case 3 :
        mUTIL.Broadcast( TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0 );
		break;
	case 4 :
        mUTIL.Broadcast( TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0 );
		break;
	case 5 :
        mUTIL.Broadcast( TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS2, false, 0 );
		break;
	case 6 :
        mUTIL.Broadcast( TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0 );
		break;
	}
	//------------------------//
	//------------------------//
	//------------------------//
}
//SUMMON_GUARD
void MySummonSystem::SummonGuard( BOOL tCheckZone038, BOOL tCheckFirst )
{
	int index01;
	int index02;
	int index03;
	const int tGuardTribePostNum = 5;
	int tGuardTotalNum[5];
	int tGuardMainType[5];
	int tGuardSpecialType[5];
	float tGuardSummonCoord[5][tGuardTribePostNum][3];
	int tSMonsterObjectIndex;
	int tEMonsterObjectIndex;
	unsigned int tRandom = 0;
	MONSTER_INFO *tMONSTER_INFO;

	tGuardTotalNum[0] = 0;
	tGuardTotalNum[1] = 0;
	tGuardTotalNum[2] = 0;
	tGuardTotalNum[3] = 0;
	tGuardTotalNum[4] = 0;
	if( !tCheckZone038 )
	{
		switch( mSERVER_INFO.mServerNumber )
		{
		case  38 :
			tGuardTotalNum[0] = tGuardTribePostNum;
			tGuardMainType[0] = 6;
			tGuardSpecialType[0] = 24;
			tGuardSummonCoord[0][0][0] = -1767.0f;
			tGuardSummonCoord[0][0][1] = 160.0f;
			tGuardSummonCoord[0][0][2] = 2511.0f;
			tGuardSummonCoord[0][1][0] = -1724.0f;
			tGuardSummonCoord[0][1][1] = 160.0f;
			tGuardSummonCoord[0][1][2] = 2414.0f;
			tGuardSummonCoord[0][2][0] = -1801.0f;
			tGuardSummonCoord[0][2][1] = 160.0f;
			tGuardSummonCoord[0][2][2] = 2340.0f;
			tGuardSummonCoord[0][3][0] = -1902.0f;
			tGuardSummonCoord[0][3][1] = 160.0f;
			tGuardSummonCoord[0][3][2] = 2388.0f;
			tGuardSummonCoord[0][4][0] = -1881.0f;
			tGuardSummonCoord[0][4][1] = 160.0f;
			tGuardSummonCoord[0][4][2] = 2503.0f;
			tGuardTotalNum[1] = tGuardTribePostNum;
			tGuardMainType[1] = 7;
			tGuardSpecialType[1] = 24;
			tGuardSummonCoord[1][0][0] = 209.0f;
			tGuardSummonCoord[1][0][1] = 160.0f;
			tGuardSummonCoord[1][0][2] = 311.0f;
			tGuardSummonCoord[1][1][0] = 155.0f;
			tGuardSummonCoord[1][1][1] = 160.0f;
			tGuardSummonCoord[1][1][2] = 393.0f;
			tGuardSummonCoord[1][2][0] = 206.0f;
			tGuardSummonCoord[1][2][1] = 160.0f;
			tGuardSummonCoord[1][2][2] = 474.0f;
			tGuardSummonCoord[1][3][0] = 300.0f;
			tGuardSummonCoord[1][3][1] = 160.0f;
			tGuardSummonCoord[1][3][2] = 445.0f;
			tGuardSummonCoord[1][4][0] = 298.0f;
			tGuardSummonCoord[1][4][1] = 160.0f;
			tGuardSummonCoord[1][4][2] = 344.0f;
			tGuardTotalNum[2] = tGuardTribePostNum;
			tGuardMainType[2] = 8;
			tGuardSpecialType[2] = 24;
			tGuardSummonCoord[2][0][0] = 2527.0f;
			tGuardSummonCoord[2][0][1] = 160.0f;
			tGuardSummonCoord[2][0][2] = 257.0f;
			tGuardSummonCoord[2][1][0] = 2433.0f;
			tGuardSummonCoord[2][1][1] = 160.0f;
			tGuardSummonCoord[2][1][2] = 287.0f;
			tGuardSummonCoord[2][2][0] = 2438.0f;
			tGuardSummonCoord[2][2][1] = 160.0f;
			tGuardSummonCoord[2][2][2] = 390.0f;
			tGuardSummonCoord[2][3][0] = 2533.0f;
			tGuardSummonCoord[2][3][1] = 160.0f;
			tGuardSummonCoord[2][3][2] = 416.0f;
			tGuardSummonCoord[2][4][0] = 2594.0f;
			tGuardSummonCoord[2][4][1] = 160.0f;
			tGuardSummonCoord[2][4][2] = 334.0f;
			tGuardTotalNum[3] = tGuardTribePostNum;
			tGuardMainType[3] = 9;
			tGuardSpecialType[3] = 24;
			tGuardSummonCoord[3][0][0] = 4692.0f;
			tGuardSummonCoord[3][0][1] = 160.0f;
			tGuardSummonCoord[3][0][2] = 2433.0f;
			tGuardSummonCoord[3][1][0] = 4615.0f;
			tGuardSummonCoord[3][1][1] = 160.0f;
			tGuardSummonCoord[3][1][2] = 2372.0f;
			tGuardSummonCoord[3][2][0] = 4531.0f;
			tGuardSummonCoord[3][2][1] = 160.0f;
			tGuardSummonCoord[3][2][2] = 2442.0f;
			tGuardSummonCoord[3][3][0] = 4560.0f;
			tGuardSummonCoord[3][3][1] = 161.0f;
			tGuardSummonCoord[3][3][2] = 2529.0f;
			tGuardSummonCoord[3][4][0] = 4665.0f;
			tGuardSummonCoord[3][4][1] = 161.0f;
			tGuardSummonCoord[3][4][2] = 2527.0f;
			break;
		case   2 :
			tGuardTotalNum[0] = tGuardTribePostNum;
			tGuardMainType[0] = 6;
			tGuardSpecialType[0] = 27;
			tGuardSummonCoord[0][0][0] = -4154.0f;
			tGuardSummonCoord[0][0][1] = -3.0f;
			tGuardSummonCoord[0][0][2] = -2856.0f;
			tGuardSummonCoord[0][1][0] = -4066.0f;
			tGuardSummonCoord[0][1][1] = -1.0f;
			tGuardSummonCoord[0][1][2] = -2919.0f;
			tGuardSummonCoord[0][2][0] = -4089.0f;
			tGuardSummonCoord[0][2][1] = -2.0f;
			tGuardSummonCoord[0][2][2] = -3020.0f;
			tGuardSummonCoord[0][3][0] = -4209.0f;
			tGuardSummonCoord[0][3][1] = -3.0f;
			tGuardSummonCoord[0][3][2] = -3021.0f;
			tGuardSummonCoord[0][4][0] = -4241.0f;
			tGuardSummonCoord[0][4][1] = 0.0f;
			tGuardSummonCoord[0][4][2] = -2921.0f;
			if( mGAME.mWorldInfo.mTribe1Symbol == 0 )
			{
				tGuardTotalNum[4] = tGuardTribePostNum;
				tGuardMainType[4] = 6;
				tGuardSpecialType[4] = 27;
				tGuardSummonCoord[4][0][0] = -1898.0f;
				tGuardSummonCoord[4][0][1] = -4.0f;
				tGuardSummonCoord[4][0][2] = 3173.0f;
				tGuardSummonCoord[4][1][0] = -1826.0f;
				tGuardSummonCoord[4][1][1] = -9.0f;
				tGuardSummonCoord[4][1][2] = 3241.0f;
				tGuardSummonCoord[4][2][0] = -1725.0f;
				tGuardSummonCoord[4][2][1] = -4.0f;
				tGuardSummonCoord[4][2][2] = 3198.0f;
				tGuardSummonCoord[4][3][0] = -1742.0f;
				tGuardSummonCoord[4][3][1] = -1.0f;
				tGuardSummonCoord[4][3][2] = 3092.0f;
				tGuardSummonCoord[4][4][0] = -1854.0f;
				tGuardSummonCoord[4][4][1] = -1.0f;
				tGuardSummonCoord[4][4][2] = 3077.0f;
			}
			break;
		case   3 :
			tGuardTotalNum[0] = tGuardTribePostNum;
			tGuardMainType[0] = 6;
			tGuardSpecialType[0] = 26;
			tGuardSummonCoord[0][0][0] = -98.0f;
			tGuardSummonCoord[0][0][1] = -9.0f;
			tGuardSummonCoord[0][0][2] = 908.0f;
			tGuardSummonCoord[0][1][0] = -11.0f;
			tGuardSummonCoord[0][1][1] = -9.0f;
			tGuardSummonCoord[0][1][2] = 863.0f;
			tGuardSummonCoord[0][2][0] = -27.0f;
			tGuardSummonCoord[0][2][1] = -9.0f;
			tGuardSummonCoord[0][2][2] = 762.0f;
			tGuardSummonCoord[0][3][0] = -147.0f;
			tGuardSummonCoord[0][3][1] = -9.0f;
			tGuardSummonCoord[0][3][2] = 771.0f;
			tGuardSummonCoord[0][4][0] = -175.0f;
			tGuardSummonCoord[0][4][1] = -9.0f;
			tGuardSummonCoord[0][4][2] = 850.0f;
			break;
		case   4 :
			tGuardTotalNum[0] = tGuardTribePostNum;
			tGuardMainType[0] = 6;
			tGuardSpecialType[0] = 25;
			tGuardSummonCoord[0][0][0] = -70.0f;
			tGuardSummonCoord[0][0][1] = -10.0f;
			tGuardSummonCoord[0][0][2] = 1916.0f;
			tGuardSummonCoord[0][1][0] = 18.0f;
			tGuardSummonCoord[0][1][1] = -10.0f;
			tGuardSummonCoord[0][1][2] = 1868.0f;
			tGuardSummonCoord[0][2][0] = -3.0f;
			tGuardSummonCoord[0][2][1] = -10.0f;
			tGuardSummonCoord[0][2][2] = 1760.0f;
			tGuardSummonCoord[0][3][0] = -95.0f;
			tGuardSummonCoord[0][3][1] = -10.0f;
			tGuardSummonCoord[0][3][2] = 1748.0f;
			tGuardSummonCoord[0][4][0] = -144.0f;
			tGuardSummonCoord[0][4][1] = -10.0f;
			tGuardSummonCoord[0][4][2] = 1847.0f;
			break;
		case   7 :
			tGuardTotalNum[1] = tGuardTribePostNum;
			tGuardMainType[1] = 7;
			tGuardSpecialType[1] = 27;
			tGuardSummonCoord[1][0][0] = 3274.0f;
			tGuardSummonCoord[1][0][1] = 28.0f;
			tGuardSummonCoord[1][0][2] = -4636.0f;
			tGuardSummonCoord[1][1][0] = 3356.0f;
			tGuardSummonCoord[1][1][1] = 29.0f;
			tGuardSummonCoord[1][1][2] = -4697.0f;
			tGuardSummonCoord[1][2][0] = 3330.0f;
			tGuardSummonCoord[1][2][1] = 31.0f;
			tGuardSummonCoord[1][2][2] = -4795.0f;
			tGuardSummonCoord[1][3][0] = 3219.0f;
			tGuardSummonCoord[1][3][1] = 31.0f;
			tGuardSummonCoord[1][3][2] = -4796.0f;
			tGuardSummonCoord[1][4][0] = 3195.0f;
			tGuardSummonCoord[1][4][1] = 32.0f;
			tGuardSummonCoord[1][4][2] = -4695.0f;
			if( mGAME.mWorldInfo.mTribe2Symbol == 1 )
			{
				tGuardTotalNum[4] = tGuardTribePostNum;
				tGuardMainType[4] = 7;
				tGuardSpecialType[4] = 27;
				tGuardSummonCoord[4][0][0] = -826.0f;
				tGuardSummonCoord[4][0][1] = 11.0f;
				tGuardSummonCoord[4][0][2] = -3480.0f;
				tGuardSummonCoord[4][1][0] = -914.0f;
				tGuardSummonCoord[4][1][1] = 9.0f;
				tGuardSummonCoord[4][1][2] = -3410.0f;
				tGuardSummonCoord[4][2][0] = -883.0f;
				tGuardSummonCoord[4][2][1] = 5.0f;
				tGuardSummonCoord[4][2][2] = -3309.0f;
				tGuardSummonCoord[4][3][0] = -778.0f;
				tGuardSummonCoord[4][3][1] = 7.0f;
				tGuardSummonCoord[4][3][2] = -3317.0f;
				tGuardSummonCoord[4][4][0] = -743.0f;
				tGuardSummonCoord[4][4][1] = 10.0f;
				tGuardSummonCoord[4][4][2] = -3409.0f;
			}
			break;
		case   8 :
			tGuardTotalNum[1] = tGuardTribePostNum;
			tGuardMainType[1] = 7;
			tGuardSpecialType[1] = 26;
			tGuardSummonCoord[1][0][0] = 215.0f;
			tGuardSummonCoord[1][0][1] = 1.0f;
			tGuardSummonCoord[1][0][2] = 1591.0f;
			tGuardSummonCoord[1][1][0] = 293.0f;
			tGuardSummonCoord[1][1][1] = 0.0f;
			tGuardSummonCoord[1][1][2] = 1526.0f;
			tGuardSummonCoord[1][2][0] = 261.0f;
			tGuardSummonCoord[1][2][1] = 0.0f;
			tGuardSummonCoord[1][2][2] = 1427.0f;
			tGuardSummonCoord[1][3][0] = 159.0f;
			tGuardSummonCoord[1][3][1] = 0.0f;
			tGuardSummonCoord[1][3][2] = 1432.0f;
			tGuardSummonCoord[1][4][0] = 130.0f;
			tGuardSummonCoord[1][4][1] = 0.0f;
			tGuardSummonCoord[1][4][2] = 1533.0f;
			break;
		case   9 :
			tGuardTotalNum[1] = tGuardTribePostNum;
			tGuardMainType[1] = 7;
			tGuardSpecialType[1] = 25;
			tGuardSummonCoord[1][0][0] = -226.0f;
			tGuardSummonCoord[1][0][1] = -11.0f;
			tGuardSummonCoord[1][0][2] = 1513.0f;
			tGuardSummonCoord[1][1][0] = -135.0f;
			tGuardSummonCoord[1][1][1] = -14.0f;
			tGuardSummonCoord[1][1][2] = 1451.0f;
			tGuardSummonCoord[1][2][0] = -160.0f;
			tGuardSummonCoord[1][2][1] = -9.0f;
			tGuardSummonCoord[1][2][2] = 1352.0f;
			tGuardSummonCoord[1][3][0] = -274.0f;
			tGuardSummonCoord[1][3][1] = 0.0f;
			tGuardSummonCoord[1][3][2] = 1348.0f;
			tGuardSummonCoord[1][4][0] = -306.0f;
			tGuardSummonCoord[1][4][1] = 0.0f;
			tGuardSummonCoord[1][4][2] = 1442.0f;
			break;
		case  12 :
			tGuardTotalNum[2] = tGuardTribePostNum;
			tGuardMainType[2] = 8;
			tGuardSpecialType[2] = 27;
			tGuardSummonCoord[2][0][0] = -4606.0f;
			tGuardSummonCoord[2][0][1] = -1.0f;
			tGuardSummonCoord[2][0][2] = -4211.0f;
			tGuardSummonCoord[2][1][0] = -4516.0f;
			tGuardSummonCoord[2][1][1] = -11.0f;
			tGuardSummonCoord[2][1][2] = -4271.0f;
			tGuardSummonCoord[2][2][0] = -4533.0f;
			tGuardSummonCoord[2][2][1] = -3.0f;
			tGuardSummonCoord[2][2][2] = -4374.0f;
			tGuardSummonCoord[2][3][0] = -4654.0f;
			tGuardSummonCoord[2][3][1] = 1.0f;
			tGuardSummonCoord[2][3][2] = -4384.0f;
			tGuardSummonCoord[2][4][0] = -4691.0f;
			tGuardSummonCoord[2][4][1] = 1.0f;
			tGuardSummonCoord[2][4][2] = -4283.0f;
			if( mGAME.mWorldInfo.mTribe3Symbol == 2 )
			{
				tGuardTotalNum[4] = tGuardTribePostNum;
				tGuardMainType[4] = 8;
				tGuardSpecialType[4] = 27;
				tGuardSummonCoord[4][0][0] = -4053.0f;
				tGuardSummonCoord[4][0][1] = 0.0f;
				tGuardSummonCoord[4][0][2] = 1743.0f;
				tGuardSummonCoord[4][1][0] = -3962.0f;
				tGuardSummonCoord[4][1][1] = 0.0f;
				tGuardSummonCoord[4][1][2] = 1681.0f;
				tGuardSummonCoord[4][2][0] = -3986.0f;
				tGuardSummonCoord[4][2][1] = -5.0f;
				tGuardSummonCoord[4][2][2] = 1575.0f;
				tGuardSummonCoord[4][3][0] = -4091.0f;
				tGuardSummonCoord[4][3][1] = -4.0f;
				tGuardSummonCoord[4][3][2] = 1566.0f;
				tGuardSummonCoord[4][4][0] = -4135.0f;
				tGuardSummonCoord[4][4][1] = 0.0f;
				tGuardSummonCoord[4][4][2] = 1664.0f;
			}
			break;
		case  13 :
			tGuardTotalNum[2] = tGuardTribePostNum;
			tGuardMainType[2] = 8;
			tGuardSpecialType[2] = 26;
			tGuardSummonCoord[2][0][0] = 33.0f;
			tGuardSummonCoord[2][0][1] = 13.0f;
			tGuardSummonCoord[2][0][2] = 1569.0f;
			tGuardSummonCoord[2][1][0] = 105.0f;
			tGuardSummonCoord[2][1][1] = 9.0f;
			tGuardSummonCoord[2][1][2] = 1486.0f;
			tGuardSummonCoord[2][2][0] = 46.0f;
			tGuardSummonCoord[2][2][1] = 13.0f;
			tGuardSummonCoord[2][2][2] = 1386.0f;
			tGuardSummonCoord[2][3][0] = -61.0f;
			tGuardSummonCoord[2][3][1] = 13.0f;
			tGuardSummonCoord[2][3][2] = 1412.0f;
			tGuardSummonCoord[2][4][0] = -62.0f;
			tGuardSummonCoord[2][4][1] = 13.0f;
			tGuardSummonCoord[2][4][2] = 1528.0f;
			break;
		case  14 :
			tGuardTotalNum[2] = tGuardTribePostNum;
			tGuardMainType[2] = 8;
			tGuardSpecialType[2] = 25;
			tGuardSummonCoord[2][0][0] = 9.0f;
			tGuardSummonCoord[2][0][1] = 12.0f;
			tGuardSummonCoord[2][0][2] = 1905.0f;
			tGuardSummonCoord[2][1][0] = 115.0f;
			tGuardSummonCoord[2][1][1] = 10.0f;
			tGuardSummonCoord[2][1][2] = 1863.0f;
			tGuardSummonCoord[2][2][0] = 111.0f;
			tGuardSummonCoord[2][2][1] = 12.0f;
			tGuardSummonCoord[2][2][2] = 1752.0f;
			tGuardSummonCoord[2][3][0] = 10.0f;
			tGuardSummonCoord[2][3][1] = 12.0f;
			tGuardSummonCoord[2][3][2] = 1724.0f;
			tGuardSummonCoord[2][4][0] = -56.0f;
			tGuardSummonCoord[2][4][1] = 12.0f;
			tGuardSummonCoord[2][4][2] = 1808.0f;
			break;
		case 141 :
			tGuardTotalNum[3] = tGuardTribePostNum;
			tGuardMainType[3] = 9;
			tGuardSpecialType[3] = 27;
			tGuardSummonCoord[3][0][0] = -1.0f;
			tGuardSummonCoord[3][0][1] = -16.0f;
			tGuardSummonCoord[3][0][2] = 1540.0f;
			tGuardSummonCoord[3][1][0] = 75.0f;
			tGuardSummonCoord[3][1][1] = -19.0f;
			tGuardSummonCoord[3][1][2] = 1464.0f;
			tGuardSummonCoord[3][2][0] = 25.0f;
			tGuardSummonCoord[3][2][1] = -19.0f;
			tGuardSummonCoord[3][2][2] = 1362.0f;
			tGuardSummonCoord[3][3][0] = -73.0f;
			tGuardSummonCoord[3][3][1] = -19.0f;
			tGuardSummonCoord[3][3][2] = 1375.0f;
			tGuardSummonCoord[3][4][0] = -98.0f;
			tGuardSummonCoord[3][4][1] = -19.0f;
			tGuardSummonCoord[3][4][2] = 1484.0f;
			if( mGAME.mWorldInfo.mTribe4Symbol == 3 )
			{
				tGuardTotalNum[4] = tGuardTribePostNum;
				tGuardMainType[4] = 9;
				tGuardSpecialType[4] = 27;
				tGuardSummonCoord[4][0][0] = -1164.0f;
				tGuardSummonCoord[4][0][1] = 0.0f;
				tGuardSummonCoord[4][0][2] = 3568.0f;
				tGuardSummonCoord[4][1][0] = -1060.0f;
				tGuardSummonCoord[4][1][1] = 0.0f;
				tGuardSummonCoord[4][1][2] = 3542.0f;
				tGuardSummonCoord[4][2][0] = -1060.0f;
				tGuardSummonCoord[4][2][1] = 2.0f;
				tGuardSummonCoord[4][2][2] = 3429.0f;
				tGuardSummonCoord[4][3][0] = -1149.0f;
				tGuardSummonCoord[4][3][1] = 3.0f;
				tGuardSummonCoord[4][3][2] = 3395.0f;
				tGuardSummonCoord[4][4][0] = -1224.0f;
				tGuardSummonCoord[4][4][1] = 0.0f;
				tGuardSummonCoord[4][4][2] = 3480.0f;
			}
			break;
		case 142 :
			tGuardTotalNum[3] = tGuardTribePostNum;
			tGuardMainType[3] = 9;
			tGuardSpecialType[3] = 26;
			tGuardSummonCoord[3][0][0] = -44.0f;
			tGuardSummonCoord[3][0][1] = -13.0f;
			tGuardSummonCoord[3][0][2] = 940.0f;
			tGuardSummonCoord[3][1][0] = 40.0f;
			tGuardSummonCoord[3][1][1] = -14.0f;
			tGuardSummonCoord[3][1][2] = 872.0f;
			tGuardSummonCoord[3][2][0] = 4.0f;
			tGuardSummonCoord[3][2][1] = -14.0f;
			tGuardSummonCoord[3][2][2] = 763.0f;
			tGuardSummonCoord[3][3][0] = -104.0f;
			tGuardSummonCoord[3][3][1] = -14.0f;
			tGuardSummonCoord[3][3][2] = 769.0f;
			tGuardSummonCoord[3][4][0] = -138.0f;
			tGuardSummonCoord[3][4][1] = -14.0f;
			tGuardSummonCoord[3][4][2] = 879.0f;
			break;
		case 143 :
			tGuardTotalNum[3] = tGuardTribePostNum;
			tGuardMainType[3] = 9;
			tGuardSpecialType[3] = 25;
			tGuardSummonCoord[3][0][0] = 16.0f;
			tGuardSummonCoord[3][0][1] = -13.0f;
			tGuardSummonCoord[3][0][2] = 976.0f;
			tGuardSummonCoord[3][1][0] = 96.0f;
			tGuardSummonCoord[3][1][1] = -14.0f;
			tGuardSummonCoord[3][1][2] = 913.0f;
			tGuardSummonCoord[3][2][0] = 60.0f;
			tGuardSummonCoord[3][2][1] = -14.0f;
			tGuardSummonCoord[3][2][2] = 804.0f;
			tGuardSummonCoord[3][3][0] = -38.0f;
			tGuardSummonCoord[3][3][1] = -14.0f;
			tGuardSummonCoord[3][3][2] = 811.0f;
			tGuardSummonCoord[3][4][0] = -70.0f;
			tGuardSummonCoord[3][4][1] = -14.0f;
			tGuardSummonCoord[3][4][2] = 921.0f;
			break;
		default :
			{

			}
			/*return;*/
		}
		tSMonsterObjectIndex = MAX_MONSTER_OBJECT_BASE_1_NUM;
		tEMonsterObjectIndex = MAX_MONSTER_OBJECT_BASE_2_NUM;
	}
	else
	{
		if( mGAME.mWorldInfo.mZone038WinTribe == -1 )
		{
			return;
		}
		switch( mSERVER_INFO.mServerNumber )
		{
		case  38 :
			//LOG_TO_FILE_2("=> %d %d\n", mSERVER_INFO.mServerNumber, mGAME.mWorldInfo.mZone038WinTribe);
			switch( mGAME.mWorldInfo.mZone038WinTribe )
			{
			case 0 :
				tGuardTotalNum[0] = tGuardTribePostNum;
				tGuardMainType[0] = 6;
				tGuardSpecialType[0] = 30;
				break;
			case 1 :
				tGuardTotalNum[1] = tGuardTribePostNum;
				tGuardMainType[1] = 7;
				tGuardSpecialType[1] = 30;
				break;
			case 2 :
				tGuardTotalNum[2] = tGuardTribePostNum;
				tGuardMainType[2] = 8;
				tGuardSpecialType[2] = 30;
				break;
			case 3 :
				tGuardTotalNum[3] = tGuardTribePostNum;
				tGuardMainType[3] = 9;
				tGuardSpecialType[3] = 30;
				break;
			default :
				return;
			}
			break;
		default :
			return;
		}
		tGuardSummonCoord[mGAME.mWorldInfo.mZone038WinTribe][0][0] = -1.0f;
		tGuardSummonCoord[mGAME.mWorldInfo.mZone038WinTribe][0][1] = 200.0f;
		tGuardSummonCoord[mGAME.mWorldInfo.mZone038WinTribe][0][2] = 6379.0f;
		tGuardSummonCoord[mGAME.mWorldInfo.mZone038WinTribe][1][0] = -30.0f;
		tGuardSummonCoord[mGAME.mWorldInfo.mZone038WinTribe][1][1] = 200.0f;
		tGuardSummonCoord[mGAME.mWorldInfo.mZone038WinTribe][1][2] = 6344.0f;
		tGuardSummonCoord[mGAME.mWorldInfo.mZone038WinTribe][2][0] = -73.0f;
		tGuardSummonCoord[mGAME.mWorldInfo.mZone038WinTribe][2][1] = 200.0f;
		tGuardSummonCoord[mGAME.mWorldInfo.mZone038WinTribe][2][2] = 6357.0f;
		tGuardSummonCoord[mGAME.mWorldInfo.mZone038WinTribe][3][0] = -72.0f;
		tGuardSummonCoord[mGAME.mWorldInfo.mZone038WinTribe][3][1] = 200.0f;
		tGuardSummonCoord[mGAME.mWorldInfo.mZone038WinTribe][3][2] = 6398.0f;
		tGuardSummonCoord[mGAME.mWorldInfo.mZone038WinTribe][4][0] = -31.0f;
		tGuardSummonCoord[mGAME.mWorldInfo.mZone038WinTribe][4][1] = 200.0f;
		tGuardSummonCoord[mGAME.mWorldInfo.mZone038WinTribe][4][2] = 6414.0f;
		tSMonsterObjectIndex = MAX_MONSTER_OBJECT_BASE_2_NUM;
		tEMonsterObjectIndex = MAX_MONSTER_OBJECT_BASE_3_NUM;
	}
	if( tCheckFirst )
	{
		for( index01 = tSMonsterObjectIndex ; index01 < tEMonsterObjectIndex ; index01++ )
		{
			mMONSTER_OBJECT[index01].mCheckValidState = FALSE;
			mMONSTER_OBJECT[index01].mInvalidTimeForSummon = GetTickCount();
		}
	}
	index03 = tSMonsterObjectIndex;
	for( index01 = 0 ; index01 < 5 ; index01++ )
	{
		//LOG_TO_FILE_3("1 %d %d %d\n", tGuardTotalNum[index01], tGuardMainType[index01], tGuardSpecialType[index01]);
		if( tGuardTotalNum[index01] < 1 )
		{
			index03 += tGuardTribePostNum;
			continue;
		}
		tMONSTER_INFO = mMONSTER.Search( tGuardMainType[index01], tGuardSpecialType[index01] );
		if( tMONSTER_INFO == NULL )
		{
			index03 += tGuardTribePostNum;
			continue;
		}
		for( index02 = 0 ; index02 < tGuardTribePostNum ; index02++ )
		{
		//LOG_TO_FILE_3("2 %d %d %d\n", index02, mMONSTER_OBJECT[index03].mCheckValidState, tCheckFirst);
			if( mMONSTER_OBJECT[index03].mCheckValidState )
			{
				index03++;
				continue;
			}
			if( !tCheckFirst )
			{
				if( ( (float) ( GetTickCount() - mMONSTER_OBJECT[index03].mInvalidTimeForSummon ) / 1000.0f ) < (float) tMONSTER_INFO->mSummonTime[0] )
				{
					index03++;
					continue;
				}
			}
			mMONSTER_OBJECT[index03].mCheckValidState = TRUE;
			mMONSTER_OBJECT[index03].mUniqueNumber = mGAME.mMonsterObjectUniqueNumber;
			mGAME.mMonsterObjectUniqueNumber++;
			mMONSTER_OBJECT[index03].mDATA.mIndex = tMONSTER_INFO->mIndex;
			mMONSTER_OBJECT[index03].mDATA.mAction.aType = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aSort = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aFrame = 0.0f;
			mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0] = tGuardSummonCoord[index01][index02][0];
			mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[1] = tGuardSummonCoord[index01][index02][1];
			mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[2] = tGuardSummonCoord[index01][index02][2];
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetLocation[0] = 0.0f;
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetLocation[1] = 0.0f;
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetLocation[2] = 0.0f;
			tRandom = rand();
			mMONSTER_OBJECT[index03].mDATA.mAction.aFront = (float) ( tRandom % 360 );
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetFront = 0.0f;
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetObjectSort = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetObjectIndex = -1;
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetObjectUniqueNumber = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aSkillNumber = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aSkillGradeNum1 = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aSkillGradeNum2 = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aSkillValue = 0;
			mMONSTER_OBJECT[index03].mDATA.mLifeValue = tMONSTER_INFO->mLife;
			mMONSTER_OBJECT[index03].SetSpaceIndex();
			mMONSTER_OBJECT[index03].mMONSTER_INFO = tMONSTER_INFO;
			tRandom = rand();
			mMONSTER_OBJECT[index03].mSameTargetPostNum = tMONSTER_INFO->mFollowInfo[0] + ( tRandom % ( tMONSTER_INFO->mFollowInfo[1] - tMONSTER_INFO->mFollowInfo[0] + 1 ) );
			mMONSTER_OBJECT[index03].mInvalidTimeForSummon = GetTickCount();
			mMONSTER_OBJECT[index03].mCheckFirstLocationTime = GetTickCount();
			mMONSTER_OBJECT[index03].mFirstLocation[0] = tGuardSummonCoord[index01][index02][0];
			mMONSTER_OBJECT[index03].mFirstLocation[1] = tGuardSummonCoord[index01][index02][1];
			mMONSTER_OBJECT[index03].mFirstLocation[2] = tGuardSummonCoord[index01][index02][2];
			mMONSTER_OBJECT[index03].mCheckDetectEnemyTime = GetTickCount();
			mMONSTER_OBJECT[index03].mCheckAttackState = FALSE;
			mMONSTER_OBJECT[index03].mTotalAttackNum = 0;
			mMONSTER_OBJECT[index03].mUpdateTimeForBroadcast = GetTickCount();
			mMONSTER_OBJECT[index03].mSpecialSortNumber = ReturnSpecialSortNumber( tMONSTER_INFO );
			mMONSTER_OBJECT[index03].mCheckFirstAttackForTribeSymbol = FALSE;
			mMONSTER_OBJECT[index03].mFirstAttackTimeForTribeSymbol = GetTickCount();
			mMONSTER_OBJECT[index03].mTribeDamageForTribeSymbol[0] = 0;
			mMONSTER_OBJECT[index03].mTribeDamageForTribeSymbol[1] = 0;
			mMONSTER_OBJECT[index03].mTribeDamageForTribeSymbol[2] = 0;
			mMONSTER_OBJECT[index03].mTribeDamageForTribeSymbol[3] = 0;
			mMONSTER_OBJECT[index03].mCheckFirstAttackForAllianceStone = FALSE;
			mMONSTER_OBJECT[index03].mFirstAttackTimeForAllianceStone = GetTickCount();
			mMONSTER_OBJECT[index03].mCheckAttackPacketRecv = FALSE;
			mMONSTER_OBJECT[index03].mRadiusForSize = sqrtf( (float) ( tMONSTER_INFO->mSize[0] * tMONSTER_INFO->mSize[0] + tMONSTER_INFO->mSize[2] * tMONSTER_INFO->mSize[2] ) ) * 0.5f;
			//------------------------//
			//BROADCAST_MONSTER_ACTION//
			//------------------------//
			mTRANSFER.B_MONSTER_ACTION_RECV( index03, mMONSTER_OBJECT[index03].mUniqueNumber, &mMONSTER_OBJECT[index03].mDATA, 1 );
            mUTIL.Broadcast( TRUE, &mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS2, false, 0 );
			//------------------------//
			//------------------------//
			//------------------------//
			index03++;
		}
	}
}
//SUMMON_TRIBE_SYMBOL
void MySummonSystem::SummonTribeSymbol( void )
{
	int index01;
	int index02;
	int index03;
	int tSymbolZoneNumber[5];
	int tSymbolSpecialType[5];
	float tSymbolLocation[5][3];
	unsigned int tRandom = 0;
	MONSTER_INFO *tMONSTER_INFO;

	tSymbolZoneNumber[0] = 0;
	tSymbolZoneNumber[1] = 0;
	tSymbolZoneNumber[2] = 0;
	tSymbolZoneNumber[3] = 0;
	tSymbolZoneNumber[4] = 0;

	/** 2009. 10. 27 : TribeWar renewal (wolf) */
    int iMinTribe;
    int iTribePoint;

    iMinTribe = mGAME.ReturnSmallTribe();
    /** 2009. 10. 27 : TribeWar renewal (wolf) */

	switch( mGAME.mWorldInfo.mTribe1Symbol )
	{
	case 0 :
		tSymbolZoneNumber[0] = 2;
		tSymbolSpecialType[0] = 11;
		tSymbolLocation[0][0] = -1810.0f;
		tSymbolLocation[0][1] = -1.0f;
		tSymbolLocation[0][2] = 3155.0f;
		break;
	case 1 :
		tSymbolZoneNumber[0] = 8;
		tSymbolSpecialType[0] = 11;
		tSymbolLocation[0][0] = 4410.0f;
		tSymbolLocation[0][1] = 28.0f;
		tSymbolLocation[0][2] = 4666.0f;
		break;
	case 2 :
		tSymbolZoneNumber[0] = 13;
		tSymbolSpecialType[0] = 11;
		tSymbolLocation[0][0] = -7610.0f;
		tSymbolLocation[0][1] = 0.0f;
		tSymbolLocation[0][2] = 5763.0f;
		break;
	case 3 :
		tSymbolZoneNumber[0] = 142;
		tSymbolSpecialType[0] = 11;
		tSymbolLocation[0][0] = -2505.0f;
		tSymbolLocation[0][1] = 0.0f;
		tSymbolLocation[0][2] = 7201.0f;
		break;
	}
	switch( mGAME.mWorldInfo.mTribe2Symbol )
	{
	case 0 :
		tSymbolZoneNumber[1] = 3;
		tSymbolSpecialType[1] = 12;
		tSymbolLocation[1][0] = -6760.0f;
		tSymbolLocation[1][1] = 0.0f;
		tSymbolLocation[1][2] = 1187.0f;
		break;
	case 1 :
		tSymbolZoneNumber[1] = 7;
		tSymbolSpecialType[1] = 12;
		tSymbolLocation[1][0] = -831.0f;
		tSymbolLocation[1][1] = 10.0f;
		tSymbolLocation[1][2] = -3392.0f;
		break;
	case 2 :
		tSymbolZoneNumber[1] = 13;
		tSymbolSpecialType[1] = 12;
		tSymbolLocation[1][0] = -6684.0f;
		tSymbolLocation[1][1] = 0.0f;
		tSymbolLocation[1][2] = 5319.0f;
		break;
	case 3 :
		tSymbolZoneNumber[1] = 142;
		tSymbolSpecialType[1] = 12;
		tSymbolLocation[1][0] = -2063.0f;
		tSymbolLocation[1][1] = 1.0f;
		tSymbolLocation[1][2] = 6846.0f;
		break;
	}
	switch( mGAME.mWorldInfo.mTribe3Symbol )
	{
	case 0 :
		tSymbolZoneNumber[2] = 3;
		tSymbolSpecialType[2] = 13;
		tSymbolLocation[2][0] = -7780.0f;
		tSymbolLocation[2][1] = 0.0f;
		tSymbolLocation[2][2] = 400.0f;
		break;
	case 1 :
		tSymbolZoneNumber[2] = 8;
		tSymbolSpecialType[2] = 13;
		tSymbolLocation[2][0] = 5493.0f;
		tSymbolLocation[2][1] = 38.0f;
		tSymbolLocation[2][2] = 4174.0f;
		break;
	case 2 :
		tSymbolZoneNumber[2] = 12;
		tSymbolSpecialType[2] = 13;
		tSymbolLocation[2][0] = -4045.0f;
		tSymbolLocation[2][1] = 0.0f;
		tSymbolLocation[2][2] = 1648.0f;
		break;
	case 3 :
		tSymbolZoneNumber[2] = 142;
		tSymbolSpecialType[2] = 13;
		tSymbolLocation[2][0] = -2948.0f;
		tSymbolLocation[2][1] = 8.0f;
		tSymbolLocation[2][2] = 6105.0f;
		break;
	}
	switch( mGAME.mWorldInfo.mTribe4Symbol )
	{
	case 0 :
		tSymbolZoneNumber[3] = 3;
		tSymbolSpecialType[3] = 28;
		tSymbolLocation[3][0] = -6864.0f;
		tSymbolLocation[3][1] = 0.0f;
		tSymbolLocation[3][2] = 2761.0f;
		break;
	case 1 :
		tSymbolZoneNumber[3] = 8;
		tSymbolSpecialType[3] = 28;
		tSymbolLocation[3][0] = 5545.0f;
		tSymbolLocation[3][1] = 41.0f;
		tSymbolLocation[3][2] = 6452.0f;
		break;
	case 2 :
		tSymbolZoneNumber[3] = 13;
		tSymbolSpecialType[3] = 28;
		tSymbolLocation[3][0] = -5397.0f;
		tSymbolLocation[3][1] = 0.0f;
		tSymbolLocation[3][2] = 5819.0f;
		break;
	case 3 :
		tSymbolZoneNumber[3] = 141;
		tSymbolSpecialType[3] = 28;
		tSymbolLocation[3][0] = -1132.0f;
		tSymbolLocation[3][1] = 0.0f;
		tSymbolLocation[3][2] = 3486.0f;
		break;
	}
	switch( mGAME.mWorldInfo.mMonsterSymbol )
	{
	case -1 :
		tSymbolZoneNumber[4] = 74;
		tSymbolSpecialType[4] = 14;
		tSymbolLocation[4][0] = -2.0f;
		tSymbolLocation[4][1] = 0.0f;
		tSymbolLocation[4][2] = 2626.0f;
		break;
	case 0 :
		tSymbolZoneNumber[4] = 4;
		tSymbolSpecialType[4] = 14;
		tSymbolLocation[4][0] = 7839.0f;
		tSymbolLocation[4][1] = 461.0f;
		tSymbolLocation[4][2] = 6520.0f;
		break;
	case 1 :
		tSymbolZoneNumber[4] = 9;
		tSymbolSpecialType[4] = 14;
		tSymbolLocation[4][0] = -2438.0f;
		tSymbolLocation[4][1] = -590.0f;
		tSymbolLocation[4][2] = 6697.0f;
		break;
	case 2 :
		tSymbolZoneNumber[4] = 14;
		tSymbolSpecialType[4] = 14;
		tSymbolLocation[4][0] = 7174.0f;
		tSymbolLocation[4][1] = 336.0f;
		tSymbolLocation[4][2] = 6191.0f;
		break;
	case 3 :
		tSymbolZoneNumber[4] = 143;
		tSymbolSpecialType[4] = 14;
		tSymbolLocation[4][0] = -38.0f;
		tSymbolLocation[4][1] = 0.0f;
		tSymbolLocation[4][2] = 4432.0f;
		break;
	}
	for( index01 = 0 ; index01 < 5 ; index01++ )
	{
		tMONSTER_INFO = mMONSTER.Search( 1, tSymbolSpecialType[index01] );
		if( tMONSTER_INFO == NULL )
		{
			continue;
		}
		for( index02 = MAX_MONSTER_OBJECT_BASE_3_NUM ; index02 < MAX_MONSTER_OBJECT_BASE_4_NUM ; index02++ )
		{
			if( !mMONSTER_OBJECT[index02].mCheckValidState )
			{
				continue;
			}
			if( mMONSTER_OBJECT[index02].mMONSTER_INFO->mIndex == tMONSTER_INFO->mIndex )
			{
				break;
			}
		}
		if( index02 < MAX_MONSTER_OBJECT_BASE_4_NUM )
		{
			if( tSymbolZoneNumber[index01] != mSERVER_INFO.mServerNumber )
			{
				mMONSTER_OBJECT[index02].mCheckValidState = FALSE;
				mMONSTER_OBJECT[index02].mInvalidTimeForSummon = GetTickCount();
			}
			continue;
		}
		else
		{
			if( tSymbolZoneNumber[index01] != mSERVER_INFO.mServerNumber )
			{
				continue;
			}
		}
		for( index03 = MAX_MONSTER_OBJECT_BASE_3_NUM ; index03 < MAX_MONSTER_OBJECT_BASE_4_NUM ; index03++ )
		{
			if( !mMONSTER_OBJECT[index03].mCheckValidState )
			{
				break;
			}
		}
		if( index03 == MAX_MONSTER_OBJECT_BASE_4_NUM )
		{
			continue;
		}

		/** 2009. 10. 27 : Monster Symbol edit (wolf) */
        if( tSymbolSpecialType[index01] == 14 && tSymbolZoneNumber[index01] != 74 )
        {
            mGAME.bAttackMonsterSymbol = false;
            mGAME.dwAttackMonsterSymbolTime = GetTickCount();
        }
        /** 2009. 10. 27 : Monster Symbol edit (wolf) */

		mMONSTER_OBJECT[index03].mCheckValidState = TRUE;
		mMONSTER_OBJECT[index03].mUniqueNumber = mGAME.mMonsterObjectUniqueNumber;
		mGAME.mMonsterObjectUniqueNumber++;
		mMONSTER_OBJECT[index03].mDATA.mIndex = tMONSTER_INFO->mIndex;
		mMONSTER_OBJECT[index03].mDATA.mAction.aType = 0;
		mMONSTER_OBJECT[index03].mDATA.mAction.aSort = 0;
		mMONSTER_OBJECT[index03].mDATA.mAction.aFrame = 0.0f;
		mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0] = tSymbolLocation[index01][0];
		mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[1] = tSymbolLocation[index01][1];
		mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[2] = tSymbolLocation[index01][2];
		mMONSTER_OBJECT[index03].mDATA.mAction.aTargetLocation[0] = 0.0f;
		mMONSTER_OBJECT[index03].mDATA.mAction.aTargetLocation[1] = 0.0f;
		mMONSTER_OBJECT[index03].mDATA.mAction.aTargetLocation[2] = 0.0f;
		mMONSTER_OBJECT[index03].mDATA.mAction.aFront = 0.0f;
		mMONSTER_OBJECT[index03].mDATA.mAction.aTargetFront = 0.0f;
		mMONSTER_OBJECT[index03].mDATA.mAction.aTargetObjectSort = 0;
		mMONSTER_OBJECT[index03].mDATA.mAction.aTargetObjectIndex = -1;
		mMONSTER_OBJECT[index03].mDATA.mAction.aTargetObjectUniqueNumber = 0;
		mMONSTER_OBJECT[index03].mDATA.mAction.aSkillNumber = 0;
		mMONSTER_OBJECT[index03].mDATA.mAction.aSkillGradeNum1 = 0;
		mMONSTER_OBJECT[index03].mDATA.mAction.aSkillGradeNum2 = 0;
		mMONSTER_OBJECT[index03].mDATA.mAction.aSkillValue = 0;
		mMONSTER_OBJECT[index03].mDATA.mLifeValue = tMONSTER_INFO->mLife;

		/** 2009. 10. 27 : TribeWar renewal (wolf) */
        if( (iMinTribe == 0 && tSymbolSpecialType[index01] == 11 && tSymbolZoneNumber[index01] == 2) ||
            (iMinTribe == 1 && tSymbolSpecialType[index01] == 12 && tSymbolZoneNumber[index01] == 7) ||
            (iMinTribe == 2 && tSymbolSpecialType[index01] == 13 && tSymbolZoneNumber[index01] == 12) ||
            (iMinTribe == 3 && tSymbolSpecialType[index01] == 28 && tSymbolZoneNumber[index01] == 141) )
        {
            mMONSTER_OBJECT[index03].mDATA.mLifeValue *= 2;
            //LOG_TO_FILE_3("![%s] Min Point Tribe -> %d, LifeValue -> %d\n",__FUNCTION__, iMinTribe, mMONSTER_OBJECT[index03].mDATA.mLifeValue );
        }
        /** 2009. 10. 27 : TribeWar renewal (wolf) */

		mMONSTER_OBJECT[index03].SetSpaceIndex();
		mMONSTER_OBJECT[index03].mMONSTER_INFO = tMONSTER_INFO;
		tRandom = rand();
		mMONSTER_OBJECT[index03].mSameTargetPostNum = tMONSTER_INFO->mFollowInfo[0] + ( tRandom % ( tMONSTER_INFO->mFollowInfo[1] - tMONSTER_INFO->mFollowInfo[0] + 1 ) );
		mMONSTER_OBJECT[index03].mInvalidTimeForSummon = GetTickCount();
		mMONSTER_OBJECT[index03].mCheckFirstLocationTime = GetTickCount();
		mMONSTER_OBJECT[index03].mFirstLocation[0] = tSymbolLocation[index01][0];
		mMONSTER_OBJECT[index03].mFirstLocation[1] = tSymbolLocation[index01][1];
		mMONSTER_OBJECT[index03].mFirstLocation[2] = tSymbolLocation[index01][2];
		mMONSTER_OBJECT[index03].mCheckDetectEnemyTime = GetTickCount();
		mMONSTER_OBJECT[index03].mCheckAttackState = FALSE;
		mMONSTER_OBJECT[index03].mTotalAttackNum = 0;
		mMONSTER_OBJECT[index03].mUpdateTimeForBroadcast = GetTickCount();
		mMONSTER_OBJECT[index03].mSpecialSortNumber = ReturnSpecialSortNumber( tMONSTER_INFO );
		mMONSTER_OBJECT[index03].mCheckFirstAttackForTribeSymbol = FALSE;
		mMONSTER_OBJECT[index03].mFirstAttackTimeForTribeSymbol = GetTickCount();
		mMONSTER_OBJECT[index03].mTribeDamageForTribeSymbol[0] = 0;
		mMONSTER_OBJECT[index03].mTribeDamageForTribeSymbol[1] = 0;
		mMONSTER_OBJECT[index03].mTribeDamageForTribeSymbol[2] = 0;
		mMONSTER_OBJECT[index03].mTribeDamageForTribeSymbol[3] = 0;
		mMONSTER_OBJECT[index03].mCheckFirstAttackForAllianceStone = FALSE;
		mMONSTER_OBJECT[index03].mFirstAttackTimeForAllianceStone = GetTickCount();
		mMONSTER_OBJECT[index03].mCheckAttackPacketRecv = FALSE;
		mMONSTER_OBJECT[index03].mRadiusForSize = sqrtf( (float) ( tMONSTER_INFO->mSize[0] * tMONSTER_INFO->mSize[0] + tMONSTER_INFO->mSize[2] * tMONSTER_INFO->mSize[2] ) ) * 0.5f;
		//------------------------//
		//BROADCAST_MONSTER_ACTION//
		//------------------------//
		mTRANSFER.B_MONSTER_ACTION_RECV( index03, mMONSTER_OBJECT[index03].mUniqueNumber, &mMONSTER_OBJECT[index03].mDATA, 1 );
        mUTIL.Broadcast( TRUE, &mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0 );
		//------------------------//
		//------------------------//
		//------------------------//
	}
}
//SUMMON_MONSTER_FOR_TRIBE_WEAPON
BOOL MySummonSystem::SummonMonsterForCPTower( int tMonsterNumber, float tMonsterLocation[3] )
{
	int index01;
	int tPresentMonsterNum;
	unsigned int tRandom = 0;
	MONSTER_INFO *tMONSTER_INFO;

	tPresentMonsterNum = 0;
	for( index01 = MAX_MONSTER_OBJECT_BASE_5_NUM ; index01 < MAX_MONSTER_OBJECT_NUM ; index01++ )
	{
		if( !mMONSTER_OBJECT[index01].mCheckValidState )
		{
			continue;
		}
		if( mMONSTER_OBJECT[index01].mMONSTER_INFO->mIndex == tMonsterNumber )
		{
			tPresentMonsterNum++;
		}
	}
	if( tPresentMonsterNum >= 1 )
	{
		return FALSE;
	}
	for( index01 = MAX_MONSTER_OBJECT_BASE_5_NUM ; index01 < MAX_MONSTER_OBJECT_NUM ; index01++ )
	{
		if( !mMONSTER_OBJECT[index01].mCheckValidState )
		{
			break;
		}
	}
	if( index01 == MAX_MONSTER_OBJECT_NUM )
	{
		return FALSE;
	}
	tMONSTER_INFO = mMONSTER.Search( tMonsterNumber );
	if( tMONSTER_INFO == NULL )
	{
		return FALSE;
	}
	mMONSTER_OBJECT[index01].mCheckValidState = TRUE;
	mMONSTER_OBJECT[index01].mUniqueNumber = mGAME.mMonsterObjectUniqueNumber;
	mGAME.mMonsterObjectUniqueNumber++;
	mMONSTER_OBJECT[index01].mDATA.mIndex = tMONSTER_INFO->mIndex;
	mMONSTER_OBJECT[index01].mDATA.mAction.aType = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aSort = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aFrame = 0.0f;
	mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0] = tMonsterLocation[0];
	mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[1] = tMonsterLocation[1];
	mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[2] = tMonsterLocation[2];
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetLocation[0] = 0.0f;
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetLocation[1] = 0.0f;
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetLocation[2] = 0.0f;
	mMONSTER_OBJECT[index01].mDATA.mAction.aFront = 0.0f;
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetFront = 0.0f;
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetObjectSort = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetObjectIndex = -1;
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetObjectUniqueNumber = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aSkillNumber = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aSkillGradeNum1 = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aSkillGradeNum2 = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aSkillValue = 0;
	mMONSTER_OBJECT[index01].mDATA.mLifeValue = tMONSTER_INFO->mLife;
	mMONSTER_OBJECT[index01].SetSpaceIndex();
	mMONSTER_OBJECT[index01].mMONSTER_INFO = tMONSTER_INFO;
	tRandom = rand();
	mMONSTER_OBJECT[index01].mSameTargetPostNum = tMONSTER_INFO->mFollowInfo[0] + (tRandom % (tMONSTER_INFO->mFollowInfo[1] - tMONSTER_INFO->mFollowInfo[0] + 1));
	mMONSTER_OBJECT[index01].mInvalidTimeForSummon = GetTickCount();
	mMONSTER_OBJECT[index01].mCheckFirstLocationTime = GetTickCount();
	mMONSTER_OBJECT[index01].mFirstLocation[0] = tMonsterLocation[0];
	mMONSTER_OBJECT[index01].mFirstLocation[1] = tMonsterLocation[1];
	mMONSTER_OBJECT[index01].mFirstLocation[2] = tMonsterLocation[2];
	mMONSTER_OBJECT[index01].mCheckDetectEnemyTime = GetTickCount();
	mMONSTER_OBJECT[index01].mCheckAttackState = FALSE;
	mMONSTER_OBJECT[index01].mTotalAttackNum = 0;
	mMONSTER_OBJECT[index01].mUpdateTimeForBroadcast = GetTickCount();
	mMONSTER_OBJECT[index01].mSpecialSortNumber = ReturnSpecialSortNumber(tMONSTER_INFO);
	mMONSTER_OBJECT[index01].mCheckFirstAttackForTribeSymbol = FALSE;
	mMONSTER_OBJECT[index01].mFirstAttackTimeForTribeSymbol = GetTickCount();
	mMONSTER_OBJECT[index01].mTribeDamageForTribeSymbol[0] = 0;
	mMONSTER_OBJECT[index01].mTribeDamageForTribeSymbol[1] = 0;
	mMONSTER_OBJECT[index01].mTribeDamageForTribeSymbol[2] = 0;
	mMONSTER_OBJECT[index01].mTribeDamageForTribeSymbol[3] = 0;
	mMONSTER_OBJECT[index01].mCheckFirstAttackForAllianceStone = FALSE;
	mMONSTER_OBJECT[index01].mFirstAttackTimeForAllianceStone = GetTickCount();
	mMONSTER_OBJECT[index01].mCheckAttackPacketRecv = FALSE;
	mMONSTER_OBJECT[index01].mRadiusForSize = sqrtf((float)(tMONSTER_INFO->mSize[0] * tMONSTER_INFO->mSize[0] + tMONSTER_INFO->mSize[2] * tMONSTER_INFO->mSize[2])) * 0.5f;
	//------------------------//
	//BROADCAST_MONSTER_ACTION//
	//------------------------//
	mTRANSFER.B_MONSTER_ACTION_RECV(index01, mMONSTER_OBJECT[index01].mUniqueNumber, &mMONSTER_OBJECT[index01].mDATA, 1);
	mUTIL.Broadcast(TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
	//------------------------//
	//------------------------//
	//------------------------//
	return TRUE;
}
//SUMMON_MONSTER_WITHOUT_TIME_LIMIT_FOR_ZONE_175_TYPE
void MySummonSystem::SummonMonsterWithoutTimeLimitForZone175Type( int tStep )
{
	int index01;
	int index02;
	int index03;
	float tRadius;
	char tFileName[1000];
	unsigned int tRandom = 0;
	//char tFileNamePart01[4];
	MONSTER_INFO *tMONSTER_INFO;

	Free();
	switch( tStep )
	{
	case 1 :
		/*
		tFileNamePart01[0] = ( mSERVER_INFO.mServerNumber % 1000 ) / 100 + '0';
		tFileNamePart01[1] = ( mSERVER_INFO.mServerNumber % 100 ) / 10 + '0';
		tFileNamePart01[2] = ( mSERVER_INFO.mServerNumber % 10 ) / 1 + '0';
		tFileNamePart01[3] = '\0';
		sprintf( tFileName, "DATA\\Z%s_SUMMONMONSTER_1.WREGION", tFileNamePart01 );
		*/
		sprintf(tFileName, "DATA/Shuaguai/Z%03d_SUMMONMONSTER_1.WREGION", mSERVER_INFO.mServerNumber);
		break;
	case 2 :
		/*
		tFileNamePart01[0] = ( mSERVER_INFO.mServerNumber % 1000 ) / 100 + '0';
		tFileNamePart01[1] = ( mSERVER_INFO.mServerNumber % 100 ) / 10 + '0';
		tFileNamePart01[2] = ( mSERVER_INFO.mServerNumber % 10 ) / 1 + '0';
		tFileNamePart01[3] = '\0';
		sprintf( tFileName, "DATA\\Z%s_SUMMONMONSTER_2.WREGION", tFileNamePart01 );
		*/
		sprintf(tFileName, "DATA/Shuaguai/Z%03d_SUMMONMONSTER_2.WREGION", mSERVER_INFO.mServerNumber);
		break;
	case 3 :
		/*
		tFileNamePart01[0] = ( mSERVER_INFO.mServerNumber % 1000 ) / 100 + '0';
		tFileNamePart01[1] = ( mSERVER_INFO.mServerNumber % 100 ) / 10 + '0';
		tFileNamePart01[2] = ( mSERVER_INFO.mServerNumber % 10 ) / 1 + '0';
		tFileNamePart01[3] = '\0';
		sprintf( tFileName, "DATA\\Z%s_SUMMONMONSTER_3.WREGION", tFileNamePart01 );
		*/
		sprintf(tFileName, "DATA/Shuaguai/Z%03d_SUMMONMONSTER_3.WREGION", mSERVER_INFO.mServerNumber);
		break;
	case 4 :
		/*
		tFileNamePart01[0] = ( mSERVER_INFO.mServerNumber % 1000 ) / 100 + '0';
		tFileNamePart01[1] = ( mSERVER_INFO.mServerNumber % 100 ) / 10 + '0';
		tFileNamePart01[2] = ( mSERVER_INFO.mServerNumber % 10 ) / 1 + '0';
		tFileNamePart01[3] = '\0';
		sprintf( tFileName, "DATA\\Z%s_SUMMONMONSTER_4.WREGION", tFileNamePart01 );
		*/
		sprintf(tFileName, "DATA/Shuaguai/Z%03d_SUMMONMONSTER_4.WREGION", mSERVER_INFO.mServerNumber);
		break;
	case 5 :
		/*
		tFileNamePart01[0] = ( mSERVER_INFO.mServerNumber % 1000 ) / 100 + '0';
		tFileNamePart01[1] = ( mSERVER_INFO.mServerNumber % 100 ) / 10 + '0';
		tFileNamePart01[2] = ( mSERVER_INFO.mServerNumber % 10 ) / 1 + '0';
		tFileNamePart01[3] = '\0';
		sprintf( tFileName, "DATA\\Z%s_SUMMONMONSTER_5.WREGION", tFileNamePart01 );
		*/
		sprintf(tFileName, "DATA/Shuaguai/Z%03d_SUMMONMONSTER_5.WREGION", mSERVER_INFO.mServerNumber);
		break;
	default :
		return;
	}
	LoadRegionInfo_1( tFileName );
	index03 = 0;
	for( index01 = 0 ; index01 < mTotalMonsterSummonInfoNum ; index01++ )
	{
		for( index02 = 0 ; index02 < mMONSTER_SUMMON[index01].mVALUE04 ; index02++ )
		{
			if( mMONSTER_OBJECT[index03].mCheckValidState )
			{
				index03++;
				continue;
			}
			tMONSTER_INFO = mMONSTER.Search( mMONSTER_SUMMON[index01].mVALUE02 );
			if( tMONSTER_INFO == NULL )
			{
				index03++;
				continue;
			}
			mMONSTER_SUMMON[index01].mRADIUS = 175;
			if (mMONSTER_SUMMON[index01].mRADIUS > 0)
			{
				tRandom = rand();
				tRadius = (float)(tRandom % mMONSTER_SUMMON[index01].mRADIUS);
			}
			
			mMonsterSummonPostTime[index03] = tMONSTER_INFO->mSummonTime[0];
			mMONSTER_OBJECT[index03].mCheckValidState = TRUE;
			mMONSTER_OBJECT[index03].mUniqueNumber = mGAME.mMonsterObjectUniqueNumber;
			mGAME.mMonsterObjectUniqueNumber++;
			mMONSTER_OBJECT[index03].mDATA.mIndex = tMONSTER_INFO->mIndex;
			mMONSTER_OBJECT[index03].mDATA.mAction.aType = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aSort = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aFrame = 0.0f;
			mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0] = (float) mMONSTER_SUMMON[index01].mCENTER[0];
			mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[1] = (float) mMONSTER_SUMMON[index01].mCENTER[1];
			mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[2] = (float) mMONSTER_SUMMON[index01].mCENTER[2];
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetLocation[0] = 0.0f;
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetLocation[1] = 0.0f;
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetLocation[2] = 0.0f;
			tRandom = rand();
			mMONSTER_OBJECT[index03].mDATA.mAction.aFront = (float) ( tRandom % 360 );
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetFront = 0.0f;
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetObjectSort = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetObjectIndex = -1;
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetObjectUniqueNumber = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aSkillNumber = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aSkillGradeNum1 = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aSkillGradeNum2 = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aSkillValue = 0;
			mMONSTER_OBJECT[index03].mDATA.mLifeValue = tMONSTER_INFO->mLife;
			mMONSTER_OBJECT[index03].SetSpaceIndex();
			mMONSTER_OBJECT[index03].mMONSTER_INFO = tMONSTER_INFO;
			tRandom = rand();
			mMONSTER_OBJECT[index03].mSameTargetPostNum = tMONSTER_INFO->mFollowInfo[0] + ( tRandom % ( tMONSTER_INFO->mFollowInfo[1] - tMONSTER_INFO->mFollowInfo[0] + 1 ) );
			mMONSTER_OBJECT[index03].mInvalidTimeForSummon = GetTickCount();
			mMONSTER_OBJECT[index03].mCheckFirstLocationTime = GetTickCount();
			mMONSTER_OBJECT[index03].mFirstLocation[0] = (float) mMONSTER_SUMMON[index01].mCENTER[0];
			mMONSTER_OBJECT[index03].mFirstLocation[1] = (float) mMONSTER_SUMMON[index01].mCENTER[1];
			mMONSTER_OBJECT[index03].mFirstLocation[2] = (float) mMONSTER_SUMMON[index01].mCENTER[2];
			mMONSTER_OBJECT[index03].mCheckDetectEnemyTime = GetTickCount();
			mMONSTER_OBJECT[index03].mCheckAttackState = FALSE;
			mMONSTER_OBJECT[index03].mTotalAttackNum = 0;
			mMONSTER_OBJECT[index03].mUpdateTimeForBroadcast = GetTickCount();
			mMONSTER_OBJECT[index03].mSpecialSortNumber = ReturnSpecialSortNumber( tMONSTER_INFO );
			mMONSTER_OBJECT[index03].mCheckFirstAttackForTribeSymbol = FALSE;
			mMONSTER_OBJECT[index03].mFirstAttackTimeForTribeSymbol = GetTickCount();
			mMONSTER_OBJECT[index03].mTribeDamageForTribeSymbol[0] = 0;
			mMONSTER_OBJECT[index03].mTribeDamageForTribeSymbol[1] = 0;
			mMONSTER_OBJECT[index03].mTribeDamageForTribeSymbol[2] = 0;
			mMONSTER_OBJECT[index03].mTribeDamageForTribeSymbol[3] = 0;
			mMONSTER_OBJECT[index03].mCheckFirstAttackForAllianceStone = FALSE;
			mMONSTER_OBJECT[index03].mFirstAttackTimeForAllianceStone = GetTickCount();
			mMONSTER_OBJECT[index03].mCheckAttackPacketRecv = FALSE;
			mMONSTER_OBJECT[index03].mRadiusForSize = sqrtf( (float) ( tMONSTER_INFO->mSize[0] * tMONSTER_INFO->mSize[0] + tMONSTER_INFO->mSize[2] * tMONSTER_INFO->mSize[2] ) ) * 0.5f;
			//------------------------//
			//BROADCAST_MONSTER_ACTION//
			//------------------------//
			mTRANSFER.B_MONSTER_ACTION_RECV( index03, mMONSTER_OBJECT[index03].mUniqueNumber, &mMONSTER_OBJECT[index03].mDATA, 1 );
			switch( tMONSTER_INFO->mSpecialType )
			{
			case 40 :
			case 41 :
			case 42 :
			case 43 :
			case 44 :
                mUTIL.Broadcast( TRUE, &mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0 );
				break;
			default :
                mUTIL.Broadcast( TRUE, &mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS1, false, 0 );
				break;
			}
			//------------------------//
			//------------------------//
			//------------------------//
			index03++;
		}
	}
}
//SUMMON_MONSTER_FOR_ZONE_175_TYPE
void MySummonSystem::SummonMonsterForZone175Type( void )
{
	int index01;
	int index02;
	int index03;
	unsigned int tRandom = 0;
	MONSTER_INFO *tMONSTER_INFO;

	index03 = 0;
	for( index01 = 0 ; index01 < mTotalMonsterSummonInfoNum ; index01++ )
	{
		for( index02 = 0 ; index02 < mMONSTER_SUMMON[index01].mVALUE04 ; index02++ )
		{
			if( mMONSTER_OBJECT[index03].mCheckValidState )
			{
				index03++;
				continue;
			}
			tMONSTER_INFO = mMONSTER.Search( mMONSTER_SUMMON[index01].mVALUE02 );
			if( tMONSTER_INFO == NULL )
			{
				index03++;
				continue;
			}
			if( ( tMONSTER_INFO->mSpecialType == 40 ) || ( tMONSTER_INFO->mSpecialType == 41 ) || ( tMONSTER_INFO->mSpecialType == 42 ) || ( tMONSTER_INFO->mSpecialType == 43 ) || ( tMONSTER_INFO->mSpecialType == 44 ) )
			{
				index03++;
				continue;
			}
			if( ( (float) ( GetTickCount() - mMONSTER_OBJECT[index03].mInvalidTimeForSummon ) / 1000.0f ) < (float) mMonsterSummonPostTime[index03] )
			{
				index03++;
				continue;
			}
			mMonsterSummonPostTime[index03] = tMONSTER_INFO->mSummonTime[0];
			mMONSTER_OBJECT[index03].mCheckValidState = TRUE;
			mMONSTER_OBJECT[index03].mUniqueNumber = mGAME.mMonsterObjectUniqueNumber;
			mGAME.mMonsterObjectUniqueNumber++;
			mMONSTER_OBJECT[index03].mDATA.mIndex = tMONSTER_INFO->mIndex;
			mMONSTER_OBJECT[index03].mDATA.mAction.aType = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aSort = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aFrame = 0.0f;
			mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0] = (float) mMONSTER_SUMMON[index01].mCENTER[0];
			mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[1] = (float) mMONSTER_SUMMON[index01].mCENTER[1];
			mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[2] = (float) mMONSTER_SUMMON[index01].mCENTER[2];
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetLocation[0] = 0.0f;
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetLocation[1] = 0.0f;
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetLocation[2] = 0.0f;
			tRandom = rand();
			mMONSTER_OBJECT[index03].mDATA.mAction.aFront = (float) ( tRandom % 360 );
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetFront = 0.0f;
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetObjectSort = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetObjectIndex = -1;
			mMONSTER_OBJECT[index03].mDATA.mAction.aTargetObjectUniqueNumber = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aSkillNumber = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aSkillGradeNum1 = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aSkillGradeNum2 = 0;
			mMONSTER_OBJECT[index03].mDATA.mAction.aSkillValue = 0;
			mMONSTER_OBJECT[index03].mDATA.mLifeValue = tMONSTER_INFO->mLife;
			mMONSTER_OBJECT[index03].SetSpaceIndex();
			mMONSTER_OBJECT[index03].mMONSTER_INFO = tMONSTER_INFO;
			tRandom = rand();
			mMONSTER_OBJECT[index03].mSameTargetPostNum = tMONSTER_INFO->mFollowInfo[0] + ( tRandom % ( tMONSTER_INFO->mFollowInfo[1] - tMONSTER_INFO->mFollowInfo[0] + 1 ) );
			mMONSTER_OBJECT[index03].mInvalidTimeForSummon = GetTickCount();
			mMONSTER_OBJECT[index03].mCheckFirstLocationTime = GetTickCount();
			mMONSTER_OBJECT[index03].mFirstLocation[0] = (float) mMONSTER_SUMMON[index01].mCENTER[0];
			mMONSTER_OBJECT[index03].mFirstLocation[1] = (float) mMONSTER_SUMMON[index01].mCENTER[1];
			mMONSTER_OBJECT[index03].mFirstLocation[2] = (float) mMONSTER_SUMMON[index01].mCENTER[2];
			mMONSTER_OBJECT[index03].mCheckDetectEnemyTime = GetTickCount();
			mMONSTER_OBJECT[index03].mCheckAttackState = FALSE;
			mMONSTER_OBJECT[index03].mTotalAttackNum = 0;
			mMONSTER_OBJECT[index03].mUpdateTimeForBroadcast = GetTickCount();
			mMONSTER_OBJECT[index03].mSpecialSortNumber = ReturnSpecialSortNumber( tMONSTER_INFO );
			mMONSTER_OBJECT[index03].mCheckFirstAttackForTribeSymbol = FALSE;
			mMONSTER_OBJECT[index03].mFirstAttackTimeForTribeSymbol = GetTickCount();
			mMONSTER_OBJECT[index03].mTribeDamageForTribeSymbol[0] = 0;
			mMONSTER_OBJECT[index03].mTribeDamageForTribeSymbol[1] = 0;
			mMONSTER_OBJECT[index03].mTribeDamageForTribeSymbol[2] = 0;
			mMONSTER_OBJECT[index03].mTribeDamageForTribeSymbol[3] = 0;
			mMONSTER_OBJECT[index03].mCheckFirstAttackForAllianceStone = FALSE;
			mMONSTER_OBJECT[index03].mFirstAttackTimeForAllianceStone = GetTickCount();
			mMONSTER_OBJECT[index03].mCheckAttackPacketRecv = FALSE;
			mMONSTER_OBJECT[index03].mRadiusForSize = sqrtf( (float) ( tMONSTER_INFO->mSize[0] * tMONSTER_INFO->mSize[0] + tMONSTER_INFO->mSize[2] * tMONSTER_INFO->mSize[2] ) ) * 0.5f;
			//------------------------//
			//BROADCAST_MONSTER_ACTION//
			//------------------------//
			mTRANSFER.B_MONSTER_ACTION_RECV( index03, mMONSTER_OBJECT[index03].mUniqueNumber, &mMONSTER_OBJECT[index03].mDATA, 1 );
            mUTIL.Broadcast( TRUE, &mMONSTER_OBJECT[index03].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS1, false, 0 );
			//------------------------//
			//------------------------//
			//------------------------//
			index03++;
		}
	}
}
//-----------------------------------------------------------------------------------------------
//SUMMON_MONSTER_FOR_TRIBE_WEAPON
BOOL MySummonSystem::SummonMonsterForTribeWeapon(int tMonsterNumber, float tMonsterLocation[3])
{
	int index01;
	int tPresentMonsterNum;
	unsigned int tRandom = 0;
	MONSTER_INFO* tMONSTER_INFO;

	tPresentMonsterNum = 0;
	for (index01 = MAX_MONSTER_OBJECT_BASE_5_NUM; index01 < MAX_MONSTER_OBJECT_NUM; index01++)
	{
		if (!mMONSTER_OBJECT[index01].mCheckValidState)
		{
			continue;
		}
		if (mMONSTER_OBJECT[index01].mMONSTER_INFO->mIndex == tMonsterNumber)
		{
			tPresentMonsterNum++;
		}
	}
	if (tPresentMonsterNum >= 5)
	{
		return FALSE;
	}
	for (index01 = MAX_MONSTER_OBJECT_BASE_5_NUM; index01 < MAX_MONSTER_OBJECT_NUM; index01++)
	{
		if (!mMONSTER_OBJECT[index01].mCheckValidState)
		{
			break;
		}
	}
	if (index01 == MAX_MONSTER_OBJECT_NUM)
	{
		return FALSE;
	}
	tMONSTER_INFO = mMONSTER.Search(tMonsterNumber);
	if (tMONSTER_INFO == NULL)
	{
		return FALSE;
	}
	mMONSTER_OBJECT[index01].mCheckValidState = TRUE;
	mMONSTER_OBJECT[index01].mUniqueNumber = mGAME.mMonsterObjectUniqueNumber;
	mGAME.mMonsterObjectUniqueNumber++;
	mMONSTER_OBJECT[index01].mDATA.mIndex = tMONSTER_INFO->mIndex;
	mMONSTER_OBJECT[index01].mDATA.mAction.aType = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aSort = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aFrame = 0.0f;
	mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0] = tMonsterLocation[0];
	mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[1] = tMonsterLocation[1];
	mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[2] = tMonsterLocation[2];
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetLocation[0] = 0.0f;
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetLocation[1] = 0.0f;
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetLocation[2] = 0.0f;
	tRandom = rand();
	mMONSTER_OBJECT[index01].mDATA.mAction.aFront = (float)(tRandom % 360);
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetFront = 0.0f;
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetObjectSort = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetObjectIndex = -1;
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetObjectUniqueNumber = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aSkillNumber = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aSkillGradeNum1 = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aSkillGradeNum2 = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aSkillValue = 0;
	mMONSTER_OBJECT[index01].mDATA.mLifeValue = tMONSTER_INFO->mLife;
	mMONSTER_OBJECT[index01].SetSpaceIndex();
	mMONSTER_OBJECT[index01].mMONSTER_INFO = tMONSTER_INFO;
	tRandom = rand();
	mMONSTER_OBJECT[index01].mSameTargetPostNum = tMONSTER_INFO->mFollowInfo[0] + (tRandom % (tMONSTER_INFO->mFollowInfo[1] - tMONSTER_INFO->mFollowInfo[0] + 1));
	mMONSTER_OBJECT[index01].mInvalidTimeForSummon = GetTickCount();
	mMONSTER_OBJECT[index01].mCheckFirstLocationTime = GetTickCount();
	mMONSTER_OBJECT[index01].mFirstLocation[0] = tMonsterLocation[0];
	mMONSTER_OBJECT[index01].mFirstLocation[1] = tMonsterLocation[1];
	mMONSTER_OBJECT[index01].mFirstLocation[2] = tMonsterLocation[2];
	mMONSTER_OBJECT[index01].mCheckDetectEnemyTime = GetTickCount();
	mMONSTER_OBJECT[index01].mCheckAttackState = FALSE;
	mMONSTER_OBJECT[index01].mTotalAttackNum = 0;
	mMONSTER_OBJECT[index01].mUpdateTimeForBroadcast = GetTickCount();
	mMONSTER_OBJECT[index01].mSpecialSortNumber = ReturnSpecialSortNumber(tMONSTER_INFO);
	mMONSTER_OBJECT[index01].mCheckFirstAttackForTribeSymbol = FALSE;
	mMONSTER_OBJECT[index01].mFirstAttackTimeForTribeSymbol = GetTickCount();
	mMONSTER_OBJECT[index01].mTribeDamageForTribeSymbol[0] = 0;
	mMONSTER_OBJECT[index01].mTribeDamageForTribeSymbol[1] = 0;
	mMONSTER_OBJECT[index01].mTribeDamageForTribeSymbol[2] = 0;
	mMONSTER_OBJECT[index01].mTribeDamageForTribeSymbol[3] = 0;
	mMONSTER_OBJECT[index01].mCheckFirstAttackForAllianceStone = FALSE;
	mMONSTER_OBJECT[index01].mFirstAttackTimeForAllianceStone = GetTickCount();
	mMONSTER_OBJECT[index01].mCheckAttackPacketRecv = FALSE;
	mMONSTER_OBJECT[index01].mRadiusForSize = sqrtf((float)(tMONSTER_INFO->mSize[0] * tMONSTER_INFO->mSize[0] + tMONSTER_INFO->mSize[2] * tMONSTER_INFO->mSize[2])) * 0.5f;
	//------------------------//
	//BROADCAST_MONSTER_ACTION//
	//------------------------//
	mTRANSFER.B_MONSTER_ACTION_RECV(index01, mMONSTER_OBJECT[index01].mUniqueNumber, &mMONSTER_OBJECT[index01].mDATA, 1);
	//-----------------------------------------------------------------//
	//[01].일반,[02].성석,[03].수호비,[04].동맹석,[05].수호석,[06].석차//
	//-----------------------------------------------------------------//
	switch (mMONSTER_OBJECT[index01].mSpecialSortNumber)
	{
	case 1:
		mUTIL.Broadcast(TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS1, false, 0);
		break;
	case 2:
		mUTIL.Broadcast(TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
		break;
	case 3:
		mUTIL.Broadcast(TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
		break;
	case 4:
		mUTIL.Broadcast(TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
		break;
	case 5:
		mUTIL.Broadcast(TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS2, false, 0);
		break;
	case 6:
		mUTIL.Broadcast(TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
		break;
	}
	//------------------------//
	//------------------------//
	//------------------------//
	return TRUE;
}
//CHANGECPTower
BOOL MySummonSystem::CHANGECPTower(int TowerOldCode, int TowerNewCode, float tMonsterLocation[3])
{
	int index01;
	int tPresentMonsterNum;
	unsigned int tRandom = 0;
	MONSTER_INFO* tMONSTER_INFO;

	tPresentMonsterNum = 0;
	for (index01 = MAX_MONSTER_OBJECT_BASE_5_NUM; index01 < MAX_MONSTER_OBJECT_NUM; index01++)
	{
		if (!mMONSTER_OBJECT[index01].mCheckValidState)
		{
			continue;
		}
		if (mMONSTER_OBJECT[index01].mMONSTER_INFO->mIndex == TowerOldCode)
		{
			mMONSTER_OBJECT[index01].mCheckValidState = FALSE;
			mMONSTER_OBJECT[index01].mInvalidTimeForSummon = GetTickCount();
			mTRANSFER.B_MONSTER_ACTION_RECV(index01, mMONSTER_OBJECT[index01].mUniqueNumber, &mMONSTER_OBJECT[index01].mDATA, 3);
			mUTIL.Broadcast(TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
			break;
		}
	}
	

	for (index01 = MAX_MONSTER_OBJECT_BASE_5_NUM; index01 < MAX_MONSTER_OBJECT_NUM; index01++)
	{
		if (!mMONSTER_OBJECT[index01].mCheckValidState)
		{
			break;
		}
	}
	tMONSTER_INFO = mMONSTER.Search(TowerNewCode);
	if (tMONSTER_INFO == NULL)
	{
		return FALSE;
	}
	mMONSTER_OBJECT[index01].mCheckValidState = TRUE;
	mMONSTER_OBJECT[index01].mUniqueNumber = mGAME.mMonsterObjectUniqueNumber;
	mGAME.mMonsterObjectUniqueNumber++;
	mMONSTER_OBJECT[index01].mDATA.mIndex = tMONSTER_INFO->mIndex;
	mMONSTER_OBJECT[index01].mDATA.mAction.aType = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aSort = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aFrame = 0.0f;
	mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0] = tMonsterLocation[0];
	mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[1] = tMonsterLocation[1];
	mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[2] = tMonsterLocation[2];
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetLocation[0] = 0.0f;
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetLocation[1] = 0.0f;
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetLocation[2] = 0.0f;
	mMONSTER_OBJECT[index01].mDATA.mAction.aFront = 0.0f;
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetFront = 0.0f;
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetObjectSort = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetObjectIndex = -1;
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetObjectUniqueNumber = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aSkillNumber = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aSkillGradeNum1 = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aSkillGradeNum2 = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aSkillValue = 0;
	mMONSTER_OBJECT[index01].mDATA.mLifeValue = tMONSTER_INFO->mLife;
	mMONSTER_OBJECT[index01].SetSpaceIndex();
	mMONSTER_OBJECT[index01].mMONSTER_INFO = tMONSTER_INFO;
	tRandom = rand();
	mMONSTER_OBJECT[index01].mSameTargetPostNum = tMONSTER_INFO->mFollowInfo[0] + (tRandom % (tMONSTER_INFO->mFollowInfo[1] - tMONSTER_INFO->mFollowInfo[0] + 1));
	mMONSTER_OBJECT[index01].mInvalidTimeForSummon = GetTickCount();
	mMONSTER_OBJECT[index01].mCheckFirstLocationTime = GetTickCount();
	mMONSTER_OBJECT[index01].mFirstLocation[0] = tMonsterLocation[0];
	mMONSTER_OBJECT[index01].mFirstLocation[1] = tMonsterLocation[1];
	mMONSTER_OBJECT[index01].mFirstLocation[2] = tMonsterLocation[2];
	mMONSTER_OBJECT[index01].mCheckDetectEnemyTime = GetTickCount();
	mMONSTER_OBJECT[index01].mCheckAttackState = FALSE;
	mMONSTER_OBJECT[index01].mTotalAttackNum = 0;
	mMONSTER_OBJECT[index01].mUpdateTimeForBroadcast = GetTickCount();
	mMONSTER_OBJECT[index01].mSpecialSortNumber = ReturnSpecialSortNumber(tMONSTER_INFO);
	mMONSTER_OBJECT[index01].mCheckFirstAttackForTribeSymbol = FALSE;
	mMONSTER_OBJECT[index01].mFirstAttackTimeForTribeSymbol = GetTickCount();
	mMONSTER_OBJECT[index01].mTribeDamageForTribeSymbol[0] = 0;
	mMONSTER_OBJECT[index01].mTribeDamageForTribeSymbol[1] = 0;
	mMONSTER_OBJECT[index01].mTribeDamageForTribeSymbol[2] = 0;
	mMONSTER_OBJECT[index01].mTribeDamageForTribeSymbol[3] = 0;
	mMONSTER_OBJECT[index01].mCheckFirstAttackForAllianceStone = FALSE;
	mMONSTER_OBJECT[index01].mFirstAttackTimeForAllianceStone = GetTickCount();
	mMONSTER_OBJECT[index01].mCheckAttackPacketRecv = FALSE;
	mMONSTER_OBJECT[index01].mRadiusForSize = sqrtf((float)(tMONSTER_INFO->mSize[0] * tMONSTER_INFO->mSize[0] + tMONSTER_INFO->mSize[2] * tMONSTER_INFO->mSize[2])) * 0.5f;
	//------------------------//
	//BROADCAST_MONSTER_ACTION//
	//------------------------//
	mTRANSFER.B_MONSTER_ACTION_RECV(index01, mMONSTER_OBJECT[index01].mUniqueNumber, &mMONSTER_OBJECT[index01].mDATA, 1);
	mUTIL.Broadcast(TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
	//------------------------//
	//------------------------//
	//------------------------//
	return TRUE;
}
////////////////////////////////////////
//MonsterForZone38
int MySummonSystem::MonsterForZone38(int tMonsterNumber, float tMonsterLocation[3])
{
	int index01;
	int tPresentMonsterNum;
	unsigned int tRandom = 0;
	MONSTER_INFO* tMONSTER_INFO;

	for (index01 = MAX_MONSTER_OBJECT_BASE_5_NUM; index01 < MAX_MONSTER_OBJECT_NUM; index01++)
	{
		if (!mMONSTER_OBJECT[index01].mCheckValidState)
		{
			break;
		}
	}
	if (index01 == MAX_MONSTER_OBJECT_NUM)
	{
		return FALSE;
	}
	tMONSTER_INFO = mMONSTER.Search(tMonsterNumber);
	if (tMONSTER_INFO == NULL)
	{
		return FALSE;
	}
	mMONSTER_OBJECT[index01].mCheckValidState = TRUE;
	mMONSTER_OBJECT[index01].mUniqueNumber = mGAME.mMonsterObjectUniqueNumber;
	mGAME.mMonsterObjectUniqueNumber++;
	mMONSTER_OBJECT[index01].mDATA.mIndex = tMONSTER_INFO->mIndex;
	mMONSTER_OBJECT[index01].mDATA.mAction.aType = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aSort = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aFrame = 0.0f;
	mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0] = tMonsterLocation[0];
	mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[1] = tMonsterLocation[1];
	mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[2] = tMonsterLocation[2];
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetLocation[0] = 0.0f;
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetLocation[1] = 0.0f;
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetLocation[2] = 0.0f;
	tRandom = rand();
	mMONSTER_OBJECT[index01].mDATA.mAction.aFront = (float)(tRandom % 360);
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetFront = 0.0f;
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetObjectSort = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetObjectIndex = -1;
	mMONSTER_OBJECT[index01].mDATA.mAction.aTargetObjectUniqueNumber = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aSkillNumber = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aSkillGradeNum1 = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aSkillGradeNum2 = 0;
	mMONSTER_OBJECT[index01].mDATA.mAction.aSkillValue = 0;
	mMONSTER_OBJECT[index01].mDATA.mLifeValue = tMONSTER_INFO->mLife;
	mMONSTER_OBJECT[index01].SetSpaceIndex();
	mMONSTER_OBJECT[index01].mMONSTER_INFO = tMONSTER_INFO;
	tRandom = rand();
	mMONSTER_OBJECT[index01].mSameTargetPostNum = tMONSTER_INFO->mFollowInfo[0] + (tRandom % (tMONSTER_INFO->mFollowInfo[1] - tMONSTER_INFO->mFollowInfo[0] + 1));
	mMONSTER_OBJECT[index01].mInvalidTimeForSummon = GetTickCount();
	mMONSTER_OBJECT[index01].mCheckFirstLocationTime = GetTickCount();
	mMONSTER_OBJECT[index01].mFirstLocation[0] = tMonsterLocation[0];
	mMONSTER_OBJECT[index01].mFirstLocation[1] = tMonsterLocation[1];
	mMONSTER_OBJECT[index01].mFirstLocation[2] = tMonsterLocation[2];
	mMONSTER_OBJECT[index01].mCheckDetectEnemyTime = GetTickCount();
	mMONSTER_OBJECT[index01].mCheckAttackState = FALSE;
	mMONSTER_OBJECT[index01].mTotalAttackNum = 0;
	mMONSTER_OBJECT[index01].mUpdateTimeForBroadcast = GetTickCount();
	mMONSTER_OBJECT[index01].mSpecialSortNumber = ReturnSpecialSortNumber(tMONSTER_INFO);
	mMONSTER_OBJECT[index01].mCheckFirstAttackForTribeSymbol = FALSE;
	mMONSTER_OBJECT[index01].mFirstAttackTimeForTribeSymbol = GetTickCount();
	mMONSTER_OBJECT[index01].mTribeDamageForTribeSymbol[0] = 0;
	mMONSTER_OBJECT[index01].mTribeDamageForTribeSymbol[1] = 0;
	mMONSTER_OBJECT[index01].mTribeDamageForTribeSymbol[2] = 0;
	mMONSTER_OBJECT[index01].mTribeDamageForTribeSymbol[3] = 0;
	mMONSTER_OBJECT[index01].mCheckFirstAttackForAllianceStone = FALSE;
	mMONSTER_OBJECT[index01].mFirstAttackTimeForAllianceStone = GetTickCount();
	mMONSTER_OBJECT[index01].mCheckAttackPacketRecv = FALSE;
	mMONSTER_OBJECT[index01].mRadiusForSize = sqrtf((float)(tMONSTER_INFO->mSize[0] * tMONSTER_INFO->mSize[0] + tMONSTER_INFO->mSize[2] * tMONSTER_INFO->mSize[2])) * 0.5f;
	//------------------------//
	//BROADCAST_MONSTER_ACTION//
	//------------------------//
	mTRANSFER.B_MONSTER_ACTION_RECV(index01, mMONSTER_OBJECT[index01].mUniqueNumber, &mMONSTER_OBJECT[index01].mDATA, 1);
	//-----------------------------------------------------------------//
	//[01].일반,[02].성석,[03].수호비,[04].동맹석,[05].수호석,[06].석차//
	//-----------------------------------------------------------------//
	switch (mMONSTER_OBJECT[index01].mSpecialSortNumber)
	{
	case 1:
		mUTIL.Broadcast(TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS1, false, 0);
		break;
	case 2:
		mUTIL.Broadcast(TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
		break;
	case 3:
		mUTIL.Broadcast(TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
		break;
	case 4:
		mUTIL.Broadcast(TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
		break;
	case 5:
		mUTIL.Broadcast(TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS2, false, 0);
		break;
	case 6:
		mUTIL.Broadcast(TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
		break;
	}
	//------------------------//
	//------------------------//
	//------------------------//
	return index01;
}