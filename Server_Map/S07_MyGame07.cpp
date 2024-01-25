//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "Shengming.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_GAME
//-------------------------------------------------------------------------------------------------
//PROCESS_FOR_BROADCAST_INFO
void MyGame::ProcessForBroadcastInfo( int tInfoSort, BYTE tInfoData[MAX_BROADCAST_INFO_SIZE] )
{	
	int index01;
	int index02;
	int index03;
	int tZone049TypeZoneIndex;
	int tZone051TypeZoneIndex;
	int tZone053TypeZoneIndex;
	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
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
	char tGuildName[MAX_GUILD_NAME_LENGTH];
	int tGuildRole;
	char tCallName[MAX_CALL_NAME_LENGTH];
	// @ Tribe Formation Skill @
	int tTribeSkillSort = 0;
	// @
#ifdef __GOD__
	int tEventSort;
	int tEventValue;
	int tZone267TypeZoneIndex;
#endif
	int tZone999State;

	int LifeorDeathZoneIndex;
	int CpTowerZoneIndex;
	int CpTowerType;

	int FullMoonGroundsZoneIndex;
	int HeavenlyCstleIndex;
	int F4BGZoneIndex;
	time_t tCountSeconds;
	struct tm* tPresentTime;
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);

	switch( tInfoSort )
	{
		//-------------//
		//ZONE_049_TYPE//
		//-------------//
	case   1 : break;
	case   2 :
		CopyMemory( &tZone049TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone049TypeState[tZone049TypeZoneIndex] = 1;
		break;
	case   3 :
		CopyMemory( &tZone049TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone049TypeState[tZone049TypeZoneIndex] = 2;
		break;
	case   4 :
		CopyMemory( &tZone049TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone049TypeState[tZone049TypeZoneIndex] = 3;
		break;
	case   5 :
		CopyMemory( &tZone049TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone049TypeState[tZone049TypeZoneIndex] = 5;
		break;
	case   6 :
		CopyMemory( &tZone049TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone049TypeState[tZone049TypeZoneIndex] = 5;
		break;
	case   7 :
		CopyMemory( &tZone049TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone049TypeState[tZone049TypeZoneIndex] = 4;
		break;
	case   8 :
		CopyMemory( &tZone049TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone049TypeState[tZone049TypeZoneIndex] = 5;
		//Tekrar sayma zamanýný yolla
		mWorldInfo.mZone049TypeStateTime[tZone049TypeZoneIndex] = ((tPresentTime->tm_hour * 100) + tPresentTime->tm_min + 100);
		break;
	case   9 :
		CopyMemory( &tZone049TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone049TypeState[tZone049TypeZoneIndex] = 0;
		break;
		//-------------//
		//ZONE_051_TYPE//
		//-------------//
	case  10 : break;
	case  11 :
		CopyMemory( &tZone051TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone051TypeState[tZone051TypeZoneIndex] = 1;
		break;
	case  12 :
		CopyMemory( &tZone051TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone051TypeState[tZone051TypeZoneIndex] = 2;
		break;
	case  13 :
		CopyMemory( &tZone051TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone051TypeState[tZone051TypeZoneIndex] = 3;
		break;
	case  14 :
		CopyMemory( &tZone051TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone051TypeState[tZone051TypeZoneIndex] = 5;
		break;
	case  15 :
		CopyMemory( &tZone051TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone051TypeState[tZone051TypeZoneIndex] = 5;
		break;
	case  16 :
		CopyMemory( &tZone051TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone051TypeState[tZone051TypeZoneIndex] = 4;
		break;
	case  17 :
		CopyMemory( &tZone051TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone051TypeState[tZone051TypeZoneIndex] = 5;
		break;
	case  18 :
		CopyMemory( &tZone051TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone051TypeState[tZone051TypeZoneIndex] = 0;
		break;
		//-------------//
		//ZONE_053_TYPE//
		//-------------//
	case  19 : break;
	case  20 :
		CopyMemory( &tZone053TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone053TypeState[tZone053TypeZoneIndex] = 1;
		break;
	case  21 :
		CopyMemory( &tZone053TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone053TypeState[tZone053TypeZoneIndex] = 2;
		break;
	case  22 :
		CopyMemory( &tZone053TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone053TypeState[tZone053TypeZoneIndex] = 3;
		break;
	case  23 :
		CopyMemory( &tZone053TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone053TypeState[tZone053TypeZoneIndex] = 5;
		break;
	case  24 :
		CopyMemory( &tZone053TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone053TypeState[tZone053TypeZoneIndex] = 5;
		break;
	case  25 : break;
	case  26 : break;
	case  27 : break;
	case  28 :
		CopyMemory( &tZone053TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone053TypeState[tZone053TypeZoneIndex] = 4;
		break;
	case  29 :
		CopyMemory( &tZone053TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone053TypeState[tZone053TypeZoneIndex] = 5;
		break;
	case  30 :
		CopyMemory( &tZone053TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone053TypeState[tZone053TypeZoneIndex] = 0;
		break;
		//------//
		//¼öÈ£¼®//
		//------//
	case  31 :
		CopyMemory( &tTribeGuardIndex1, &tInfoData[0], 4 );
		CopyMemory( &tTribeGuardIndex2, &tInfoData[4], 4 );
		mWorldInfo.mTribeGuardState[tTribeGuardIndex1][tTribeGuardIndex2] = 0;
		break;
	case  32 :
		CopyMemory( &tTribeGuardIndex1, &tInfoData[0], 4 );
		CopyMemory( &tTribeGuardIndex2, &tInfoData[4], 4 );
		mWorldInfo.mTribeGuardState[tTribeGuardIndex1][tTribeGuardIndex2] = 1;
		break;
		//--------//
		//ZONE_038//
		//--------//
	case  33 : break;
	case  34 : break;
	case  35 : 
		CopyMemory(&tTribe, &tInfoData[0], 4);
		CopyMemory(&tAvatarName[0], &tInfoData[4], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		
		
		break;
	case  36 : break;
	case  37 : break;
	case  38 :
		CopyMemory( &tTribe, &tInfoData[0], 4 );
		CopyMemory(&tAvatarName[0], &tInfoData[4], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		mWorldInfo.mZone038WinTribe = tTribe;
		if( mCheckZone039TypeServer )
		{
			mZone039TypeBattleState = 1;
			mZone039TypePostTick = 0;
		}
		break;
		//----//
		//¼º¼®//
		//----//
	case  39 : break;
	case  40 :
		mWorldInfo.mTribeSymbolBattle = 1;
		/** 2009. 10. 27 : TribeWar renewal (wolf) */
		mWorldInfo.HollyBattleRank = 1;
		mWorldInfo.mTribe1Symbol = 0;
		mWorldInfo.mTribe2Symbol = 1;
		mWorldInfo.mTribe3Symbol = 2;
		mWorldInfo.mTribe4Symbol = 3;
		//Sýnýflar sýfýrlanýyor
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (mUSER[index01].mMoveZoneResult == 1)
			{
				continue;
			}
			mAVATAR_OBJECT[index01].mDATA.aRankPoint = 0;
			mUSER[index01].mAvatarInfo.aRankPoint = 0;
			mUSER[index01].mAvatarInfo.aRank = 0;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(68, 0);
			mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}

		mSUMMON.SummonTribeSymbol();
		/** 2009. 10. 27 : TribeWar renewal (wolf) */

		break;
	case  41 : break;
	case  42 :
		CopyMemory( &tTribeSymbolIndex, &tInfoData[0], 4 );
		CopyMemory( &tWinTribeForSymbol, &tInfoData[4], 4 );
		switch( tTribeSymbolIndex )
		{
		case 0 :
			mWorldInfo.mTribe1Symbol = tWinTribeForSymbol;
			break;
		case 1 :
			mWorldInfo.mTribe2Symbol = tWinTribeForSymbol;
			break;
		case 2 :
			mWorldInfo.mTribe3Symbol = tWinTribeForSymbol;
			break;
		case 3 :
			mWorldInfo.mTribe4Symbol = tWinTribeForSymbol;
			break;
		case 4 :
			mWorldInfo.mMonsterSymbol = tWinTribeForSymbol;
			break;
		}
		break;
	case  43 : break;
	case  44 : break;
	case  45 :
		mWorldInfo.HollyBattleRank = 0;
		mWorldInfo.mTribeSymbolBattle = 0;
		// @ Tribe Formation Skill @
		mWorldInfo.mTribeMasterCallAbility[0] = 0;
		mWorldInfo.mTribeMasterCallAbility[1] = 0;
		mWorldInfo.mTribeMasterCallAbility[2] = 0;
		mWorldInfo.mTribeMasterCallAbility[3] = 0;
		// @
		break;
		//------//
		//µ¿¸Í¼®//
		//------//
	case  46 :
		CopyMemory( &tAllianceTribe1, &tInfoData[0], 4 );
		CopyMemory( &tAllianceTribe2, &tInfoData[4], 4 );
		if( ( mWorldInfo.mAllianceState[0][0] == -1 ) && ( mWorldInfo.mAllianceState[0][1] == -1 ) )
		{
			tAllianceIndex = 0;
		}
		else
		{
			tAllianceIndex = 1;
		}
		mWorldInfo.mPossibleAllianceInfo[tAllianceTribe1][0] = 0;
		mWorldInfo.mPossibleAllianceInfo[tAllianceTribe1][1] = 0;
		mWorldInfo.mPossibleAllianceInfo[tAllianceTribe2][0] = 0;
		mWorldInfo.mPossibleAllianceInfo[tAllianceTribe2][1] = 0;
		mWorldInfo.mAllianceState[tAllianceIndex][0] = tAllianceTribe1;
		mWorldInfo.mAllianceState[tAllianceIndex][1] = tAllianceTribe2;
		break;
	case  47 :
		CopyMemory( &tAllianceTribe1, &tInfoData[0], 4 );
		CopyMemory( &tAllianceTribe2, &tInfoData[4], 4 );
		CopyMemory( &tPossibleAllianceDate01, &tInfoData[8], 4 );
		CopyMemory( &tPossibleAllianceDate02, &tInfoData[12], 4 );
		if( ( ( mWorldInfo.mAllianceState[0][0] == tAllianceTribe1 ) && ( mWorldInfo.mAllianceState[0][1] == tAllianceTribe2 ) ) || ( ( mWorldInfo.mAllianceState[0][1] == tAllianceTribe1 ) && ( mWorldInfo.mAllianceState[0][0] == tAllianceTribe2 ) ) )
		{
			tAllianceIndex = 0;
		}
		else
		{
			tAllianceIndex = 1;
		}
		mWorldInfo.mPossibleAllianceInfo[tAllianceTribe1][0] = tPossibleAllianceDate01;
		mWorldInfo.mPossibleAllianceInfo[tAllianceTribe1][1] = 1;
		mWorldInfo.mPossibleAllianceInfo[tAllianceTribe2][0] = tPossibleAllianceDate02;
		mWorldInfo.mPossibleAllianceInfo[tAllianceTribe2][1] = 1;
		mWorldInfo.mAllianceState[tAllianceIndex][0] = -1;
		mWorldInfo.mAllianceState[tAllianceIndex][1] = -1;
		break;
	case  48 : break;
	case  49 :
		CopyMemory( &tAllianceTribe1, &tInfoData[0], 4 );
		CopyMemory( &tAllianceTribe2, &tInfoData[4], 4 );
		CopyMemory( &tPossibleAllianceDate01, &tInfoData[8], 4 );
		CopyMemory( &tPossibleAllianceDate02, &tInfoData[12], 4 );
		if( ( ( mWorldInfo.mAllianceState[0][0] == tAllianceTribe1 ) && ( mWorldInfo.mAllianceState[0][1] == tAllianceTribe2 ) ) || ( ( mWorldInfo.mAllianceState[0][1] == tAllianceTribe1 ) && ( mWorldInfo.mAllianceState[0][0] == tAllianceTribe2 ) ) )
		{
			tAllianceIndex = 0;
		}
		else
		{
			tAllianceIndex = 1;
		}
		mWorldInfo.mPossibleAllianceInfo[tAllianceTribe1][0] = tPossibleAllianceDate01;
		mWorldInfo.mPossibleAllianceInfo[tAllianceTribe1][1] = 1;
		mWorldInfo.mPossibleAllianceInfo[tAllianceTribe2][0] = tPossibleAllianceDate02;
		mWorldInfo.mPossibleAllianceInfo[tAllianceTribe2][1] = 1;
		mWorldInfo.mAllianceState[tAllianceIndex][0] = -1;
		mWorldInfo.mAllianceState[tAllianceIndex][1] = -1;
		break;
	case  50 : break;//Taþ yenlendi
		//--------//
		//³¶ÀÎ¼±¾ð//
		//--------//
	case  51 : break;//Taþ yýkýldý
		//-----------//
		//¼¼·ÂÀå_ÅõÇ¥//
		//-----------//
	case  52 :
		mWorldInfo.mTribeVoteState[0] = 1;
		mWorldInfo.mTribeVoteState[1] = 1;
		mWorldInfo.mTribeVoteState[2] = 1;
		mWorldInfo.mTribeVoteState[3] = 1;
		for( index01 = 0 ; index01 < 4 ; index01++ )
		{
			for( index02 = 0 ; index02 < MAX_TRIBE_VOTE_AVATAR_NUM ; index02++ )
			{
				strcpy( mTribeInfo.mTribeVoteName[index01][index02], "" );
				mTribeInfo.mTribeVoteLevel[index01][index02] = 0;
				mTribeInfo.mTribeVoteKillOtherTribe[index01][index02] = 0;
				mTribeInfo.mTribeVotePoint[index01][index02] = 0;
			}
		}
		break;
	case  53 :
		mWorldInfo.mTribeVoteState[0] = 2;
		mWorldInfo.mTribeVoteState[1] = 2;
		mWorldInfo.mTribeVoteState[2] = 2;
		mWorldInfo.mTribeVoteState[3] = 2;
		break;
	case  54 :
		mWorldInfo.mTribeVoteState[0] = 3;
		mWorldInfo.mTribeVoteState[1] = 3;
		mWorldInfo.mTribeVoteState[2] = 3;
		mWorldInfo.mTribeVoteState[3] = 3;
		break;
	case  55 :
		mWorldInfo.mTribeVoteState[0] = 4;
		mWorldInfo.mTribeVoteState[1] = 4;
		mWorldInfo.mTribeVoteState[2] = 4;
		mWorldInfo.mTribeVoteState[3] = 4;
		for( index01 = 0 ; index01 < 4 ; index01++ )
		{
			index03 = -1;
			for( index02 = 0 ; index02 < MAX_TRIBE_VOTE_AVATAR_NUM ; index02++ )
			{
				if( strcmp( mTribeInfo.mTribeVoteName[index01][index02], "" ) == 0 )
				{
					continue;
				}
				if( mTribeInfo.mTribeVotePoint[index01][index02] < 1 )
				{
					continue;
				}
				if( index03 == -1 )
				{
					index03 = index02;
				}
				else
				{
					if( mTribeInfo.mTribeVotePoint[index01][index02] > mTribeInfo.mTribeVotePoint[index01][index03] )
					{
						index03 = index02;
					}
				}
			}
			if( index03 == -1 )
			{
				strcpy( mTribeInfo.mTribeMaster[index01], "" );
			}
			else
			{
				strncpy( mTribeInfo.mTribeMaster[index01], mTribeInfo.mTribeVoteName[index01][index03], MAX_AVATAR_NAME_LENGTH );
			}
			for( index02 = 0 ; index02 < MAX_TRIBE_SUBMASTER_NUM ; index02++ )
			{
				strcpy( mTribeInfo.mTribeSubMaster[index01][index02], "" );
			}
		}
		break;
	case  56 :
		mWorldInfo.mTribeVoteState[0] = 0;
		mWorldInfo.mTribeVoteState[1] = 0;
		mWorldInfo.mTribeVoteState[2] = 0;
		mWorldInfo.mTribeVoteState[3] = 0;
		for( index01 = 0 ; index01 < 4 ; index01++ )
		{
			for( index02 = 0 ; index02 < MAX_TRIBE_VOTE_AVATAR_NUM ; index02++ )
			{
				strcpy( mTribeInfo.mTribeVoteName[index01][index02], "" );
				mTribeInfo.mTribeVoteLevel[index01][index02] = 0;
				mTribeInfo.mTribeVoteKillOtherTribe[index01][index02] = 0;
				mTribeInfo.mTribeVotePoint[index01][index02] = 0;
			}
		}
		break;
	case  57 :
		CopyMemory( &tTribeForTribeVote, &tInfoData[0], 4 );
		CopyMemory( &tIndexForTribeVote, &tInfoData[4], 4 );
		CopyMemory( &tAvatarNameForTribeVote[0], &tInfoData[8], MAX_AVATAR_NAME_LENGTH );
		CopyMemory( &tLevelForTribeVote, &tInfoData[( 8 + MAX_AVATAR_NAME_LENGTH )], 4 );
		CopyMemory( &tKillOtherTribeForTribeVote, &tInfoData[( 12 + MAX_AVATAR_NAME_LENGTH )], 4 );
		strncpy( mTribeInfo.mTribeVoteName[tTribeForTribeVote][tIndexForTribeVote], tAvatarNameForTribeVote, MAX_AVATAR_NAME_LENGTH );
		mTribeInfo.mTribeVoteLevel[tTribeForTribeVote][tIndexForTribeVote] = tLevelForTribeVote;
		mTribeInfo.mTribeVoteKillOtherTribe[tTribeForTribeVote][tIndexForTribeVote] = tKillOtherTribeForTribeVote;
		mTribeInfo.mTribeVotePoint[tTribeForTribeVote][tIndexForTribeVote] = 0;
		break;
	case  58 :
		CopyMemory( &tTribeForTribeVote, &tInfoData[0], 4 );
		CopyMemory( &tIndexForTribeVote, &tInfoData[4], 4 );
		strcpy( mTribeInfo.mTribeVoteName[tTribeForTribeVote][tIndexForTribeVote], "" );
		mTribeInfo.mTribeVoteLevel[tTribeForTribeVote][tIndexForTribeVote] = 0;
		mTribeInfo.mTribeVoteKillOtherTribe[tTribeForTribeVote][tIndexForTribeVote] = 0;
		mTribeInfo.mTribeVotePoint[tTribeForTribeVote][tIndexForTribeVote] = 0;
		break;
	case  59 :
		CopyMemory( &tTribeForTribeVote, &tInfoData[0], 4 );
		CopyMemory( &tIndexForTribeVote, &tInfoData[4], 4 );
		CopyMemory( &tPointForTribeVote, &tInfoData[8], 4 );
		mTribeInfo.mTribeVotePoint[tTribeForTribeVote][tIndexForTribeVote] += tPointForTribeVote;
		break;
		//--------//
		//ºÎ¼¼·ÂÀå//
		//--------//
	case  60 :
		CopyMemory( &tTribeForTribeRole, &tInfoData[0], 4 );
		CopyMemory( &tIndexForTribeRole, &tInfoData[4], 4 );
		CopyMemory( &tAvatarNameForTribeRole[0], &tInfoData[8], MAX_AVATAR_NAME_LENGTH );
		strncpy( mTribeInfo.mTribeSubMaster[tTribeForTribeRole][tIndexForTribeRole], tAvatarNameForTribeRole, MAX_AVATAR_NAME_LENGTH );
		break;
	case  61 :
		CopyMemory( &tTribeForTribeRole, &tInfoData[0], 4 );
		CopyMemory( &tIndexForTribeRole, &tInfoData[4], 4 );
		CopyMemory( &tAvatarNameForTribeRole[0], &tInfoData[8], MAX_AVATAR_NAME_LENGTH );
		strcpy( mTribeInfo.mTribeSubMaster[tTribeForTribeRole][tIndexForTribeRole], "" );
		break;
		//--------//
		//¼¼·Â±Ý°í//
		//--------//
	case  62 : break;//The clan leader withdrew money
		//--------//
		//Ãµ½Å¹Ì±Ã//
		//--------//
	case  63 : break;
	case  64 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 1;
		break;
	case  65 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 2;
		break;
	case  66 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 3;
		break;
	case  67 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 4;
		break;
	case  68 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 5;
		break;
	case  69 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case  70 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case  71 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 6;
		break;
	case  72 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case  73 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 7;
		break;
	case  74 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 8;
		break;
	case  75 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 9;
		break;
	case  76 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case  77 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case  78 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 10;
		break;
	case  79 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case  80 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 11;
		break;
	case  81 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 12;
		break;
	case  82 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 13;
		break;
	case  83 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case  84 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case  85 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 14;
		break;
	case  86 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case  87 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 15;
		break;
	case  88 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 16;
		break;
	case  89 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 17;
		break;
	case  90 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case  91 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case  92 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 18;
		break;
	case  93 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case  94 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 19;
		break;
	case  95 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 20;
		break;
	case  96 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 21;
		break;
	case  97 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case  98 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case  99 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 22;
		break;
	case 100 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 23;
		break;
	case 110 :
		CopyMemory( &tZone175TypeZoneIndex1, &tInfoData[0], 4 );
		CopyMemory( &tZone175TypeZoneIndex2, &tInfoData[4], 4 );
		mWorldInfo.mZone175TypeState[tZone175TypeZoneIndex1][tZone175TypeZoneIndex2] = 0;
		break;

		//----//
		//¹®ÆÄ//
		//----//
	case 101 : //[Ã¢¼³]
		break;
	case 102 : //[°¡ÀÔ]
		break;
	case 103 : //[Å»Åð]
		break;
	case 104 : //[¾Ë¸²]
		CopyMemory( &tGuildName[0], &tInfoData[0], MAX_GUILD_NAME_LENGTH );
		tGuildName[( MAX_GUILD_NAME_LENGTH - 1 )] = '\0';
		mTRANSFER.B_BROADCAST_INFO_RECV2( tInfoSort, &tInfoData[0] );
		for( index01 = 0 ; index01 < mSERVER.mMAX_USER_NUM ; index01++ )
		{
			if( !mAVATAR_OBJECT[index01].mCheckValidState )
			{
				continue;
			}
			if( strcmp( mAVATAR_OBJECT[index01].mDATA.aGuildName, tGuildName ) != 0 )
			{
				continue;
			}
			mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal_C[0], mTRANSFER.mOriginalSize_C );
		}
		return;
	case 105 : //[ÇØ»ê]
		break;
	case 106 : //[È®Àå]
		break;
	case 107 : //[Á¦¸í]
		CopyMemory( &tAvatarName[0], &tInfoData[0], MAX_AVATAR_NAME_LENGTH );
		tAvatarName[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';
		CopyMemory( &tGuildName[0], &tInfoData[MAX_AVATAR_NAME_LENGTH], MAX_GUILD_NAME_LENGTH );
		tGuildName[( MAX_GUILD_NAME_LENGTH - 1 )] = '\0';
		for( index01 = 0 ; index01 < mSERVER.mMAX_USER_NUM ; index01++ )
		{
			if( !mAVATAR_OBJECT[index01].mCheckValidState )
			{
				continue;
			}
			if( ( strcmp( mAVATAR_OBJECT[index01].mDATA.aGuildName, tGuildName ) == 0 ) && ( strcmp( mAVATAR_OBJECT[index01].mDATA.aName, tAvatarName ) == 0 ) )
			{
				strcpy( mUSER[index01].mAvatarInfo.aGuildName, "" );
				mUSER[index01].mAvatarInfo.aGuildRole = 0;
				strcpy( mUSER[index01].mAvatarInfo.aCallName, "" );
				strcpy( mAVATAR_OBJECT[index01].mDATA.aGuildName, "" );
				mAVATAR_OBJECT[index01].mDATA.aGuildRole = 0;
				strcpy( mAVATAR_OBJECT[index01].mDATA.aCallName, "" );
				break;
			}
		}
		break;
	case 108 : //[ÀÓ¸í]
		CopyMemory( &tAvatarName[0], &tInfoData[0], MAX_AVATAR_NAME_LENGTH );
		tAvatarName[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';
		CopyMemory( &tGuildName[0], &tInfoData[MAX_AVATAR_NAME_LENGTH], MAX_GUILD_NAME_LENGTH );
		tGuildName[( MAX_GUILD_NAME_LENGTH - 1 )] = '\0';
		CopyMemory( &tGuildRole, &tInfoData[( MAX_AVATAR_NAME_LENGTH + MAX_GUILD_NAME_LENGTH )], 4 );
		for( index01 = 0 ; index01 < mSERVER.mMAX_USER_NUM ; index01++ )
		{
			if( !mAVATAR_OBJECT[index01].mCheckValidState )
			{
				continue;
			}
			if( ( strcmp( mAVATAR_OBJECT[index01].mDATA.aGuildName, tGuildName ) == 0 ) && ( strcmp( mAVATAR_OBJECT[index01].mDATA.aName, tAvatarName ) == 0 ) )
			{
				mUSER[index01].mAvatarInfo.aGuildRole = tGuildRole;
				mAVATAR_OBJECT[index01].mDATA.aGuildRole = tGuildRole;
				break;
			}
		}
		mTRANSFER.B_BROADCAST_INFO_RECV2( tInfoSort, &tInfoData[0] );
		for( index01 = 0 ; index01 < mSERVER.mMAX_USER_NUM ; index01++ )
		{
			if( !mAVATAR_OBJECT[index01].mCheckValidState )
			{
				continue;
			}
			if( strcmp( mAVATAR_OBJECT[index01].mDATA.aGuildName, tGuildName ) != 0 )
			{
				continue;
			}
			mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal_C[0], mTRANSFER.mOriginalSize_C );
		}
		return;
	case 109 : //[ÄªÈ£]
		CopyMemory( &tAvatarName[0], &tInfoData[0], MAX_AVATAR_NAME_LENGTH );
		tAvatarName[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';
		CopyMemory( &tGuildName[0], &tInfoData[MAX_AVATAR_NAME_LENGTH], MAX_GUILD_NAME_LENGTH );
		tGuildName[( MAX_GUILD_NAME_LENGTH - 1 )] = '\0';
		CopyMemory( &tCallName[0], &tInfoData[( MAX_AVATAR_NAME_LENGTH + MAX_GUILD_NAME_LENGTH )], MAX_CALL_NAME_LENGTH );
		tCallName[( MAX_CALL_NAME_LENGTH - 1 )] = '\0';
		for( index01 = 0 ; index01 < mSERVER.mMAX_USER_NUM ; index01++ )
		{
			if( !mAVATAR_OBJECT[index01].mCheckValidState )
			{
				continue;
			}
			if( ( strcmp( mAVATAR_OBJECT[index01].mDATA.aGuildName, tGuildName ) == 0 ) && ( strcmp( mAVATAR_OBJECT[index01].mDATA.aName, tAvatarName ) == 0 ) )
			{
				strncpy( mUSER[index01].mAvatarInfo.aCallName, tCallName, MAX_CALL_NAME_LENGTH);
				strncpy( mAVATAR_OBJECT[index01].mDATA.aCallName, tCallName, MAX_CALL_NAME_LENGTH );
				break;
			}
		}
		mTRANSFER.B_BROADCAST_INFO_RECV2( tInfoSort, &tInfoData[0] );
		for( index01 = 0 ; index01 < mSERVER.mMAX_USER_NUM ; index01++ )
		{
			if( !mAVATAR_OBJECT[index01].mCheckValidState )
			{
				continue;
			}
			if( strcmp( mAVATAR_OBJECT[index01].mDATA.aGuildName, tGuildName ) != 0 )
			{
				continue;
			}
			mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal_C[0], mTRANSFER.mOriginalSize_C );
		}
		return;
		/* Mir added 08.12.12 */

	case 111://150 duyurusu
		break;

	//aile bufflarý
	case 112:
		break;
	case 113:
		break;

	case 114 : break;

	case 115://120 kanat duyurusu
		break;

#ifdef __GOD__
		//--------//
		//ZONE_194//
		//--------//
	case 201 : break;
	case 202 :
		mWorldInfo.mZone194State = 1;
		break;
	case 203 :
		mWorldInfo.mZone194State = 2;
		break;
	case 204 :
		mWorldInfo.mZone194State = 3;
		break;
	case 205 :
		mWorldInfo.mZone194State = 5;
		break;
	case 206 :
		mWorldInfo.mZone194State = 4;
		break;
	case 207 :
		mWorldInfo.mZone194State = 5;
		break;
	case 208 :
		mWorldInfo.mZone194State = 0;
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
			mWorldInfo.mTribeGeneralExperienceUpRatioInfo[0] = (float) tEventValue * 0.1f;
			break;
		case 22 :
			mWorldInfo.mTribeGeneralExperienceUpRatioInfo[1] = (float) tEventValue * 0.1f;
			break;
		case 23 :
			mWorldInfo.mTribeGeneralExperienceUpRatioInfo[2] = (float) tEventValue * 0.1f;
			break;
		case 24 :
			mWorldInfo.mTribeGeneralExperienceUpRatioInfo[3] = (float) tEventValue * 0.1f;
			break;
		case 31 :
			mWorldInfo.mTribeItemDropUpRatioInfo[0] = (float) tEventValue * 0.1f;
			break;
		case 32 :
			mWorldInfo.mTribeItemDropUpRatioInfo[1] = (float) tEventValue * 0.1f;
			break;
		case 33 :
			mWorldInfo.mTribeItemDropUpRatioInfo[2] = (float) tEventValue * 0.1f;
			break;
		case 34 :
			mWorldInfo.mTribeItemDropUpRatioInfo[3] = (float) tEventValue * 0.1f;
			break;
		case 41 :
			mWorldInfo.mTribeItemDropUpRatioForMyoungInfo[0] = (float) tEventValue * 0.1f;
			break;
		case 42 :
			mWorldInfo.mTribeItemDropUpRatioForMyoungInfo[1] = (float) tEventValue * 0.1f;
			break;
		case 43 :
			mWorldInfo.mTribeItemDropUpRatioForMyoungInfo[2] = (float) tEventValue * 0.1f;
			break;
		case 44 :
			mWorldInfo.mTribeItemDropUpRatioForMyoungInfo[3] = (float) tEventValue * 0.1f;
			break;
		case 51 :
			mWorldInfo.mTribeKillOtherTribeAddValueInfo[0] = tEventValue;
			break;
		case 52 :
			mWorldInfo.mTribeKillOtherTribeAddValueInfo[1] = tEventValue;
			break;
		case 53 :
			mWorldInfo.mTribeKillOtherTribeAddValueInfo[2] = tEventValue;
			break;
		case 54 :
			mWorldInfo.mTribeKillOtherTribeAddValueInfo[3] = tEventValue;
			break;
		}
		break;
#endif

		/* Mir end */
		// @ Tribe Formation Skill @
		//--------//
		//¼¼·ÂÁø¹ý//
		//--------//
	case 302 :
		CopyMemory( &tTribe, &tInfoData[0], 4 );
		CopyMemory( &tTribeSkillSort, &tInfoData[4], 4 );
		mWorldInfo.mTribeMasterCallAbility[tTribe] = tTribeSkillSort;
		break; // @


	case 401://Battle of Legacy Holy Stone has begun!
		break;




#ifdef __GOD__        
		//-------------//
		//ZONE_267_TYPE//
		//-------------//
	case 402 : break;
	case 403 :
		CopyMemory( &tZone267TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone267TypeState[tZone267TypeZoneIndex] = 1;
		break;
	case 404 :
		CopyMemory( &tZone267TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone267TypeState[tZone267TypeZoneIndex] = 2;
		break;
	case 405 :
		CopyMemory( &tZone267TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone267TypeState[tZone267TypeZoneIndex] = 3;
		break;
	case 406 :
		CopyMemory( &tZone267TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone267TypeState[tZone267TypeZoneIndex] = 5;
		break;
	case 407 :
		CopyMemory( &tZone267TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone267TypeState[tZone267TypeZoneIndex] = 5;
		break;
	case 408 :
		CopyMemory( &tZone267TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone267TypeState[tZone267TypeZoneIndex] = 4;
		break;
	case 409 :
		CopyMemory( &tZone267TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone267TypeState[tZone267TypeZoneIndex] = 5;
		break;
	case 410 :
		CopyMemory( &tZone267TypeZoneIndex, &tInfoData[0], 4 );
		mWorldInfo.mZone267TypeState[tZone267TypeZoneIndex] = 0;
		break;
#endif
	case 411:
		CopyMemory(&LifeorDeathZoneIndex, &tInfoData[0], 4);
		CopyMemory(&tAvatarName[0], &tInfoData[8], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		mWorldInfo.LifeOrDeath[LifeorDeathZoneIndex] = 1;
		break;
	case 412:
		CopyMemory(&LifeorDeathZoneIndex, &tInfoData[0], 4);
		CopyMemory(&tAvatarName[0], &tInfoData[4], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		mWorldInfo.LifeOrDeath[LifeorDeathZoneIndex] = 2;
		break;
	case 413:
		CopyMemory(&LifeorDeathZoneIndex, &tInfoData[0], 4);
		CopyMemory(&tAvatarName[0], &tInfoData[4], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		mWorldInfo.LifeOrDeath[LifeorDeathZoneIndex] = 2;
		break;
	case 414:
		CopyMemory(&LifeorDeathZoneIndex, &tInfoData[0], 4);
		CopyMemory(&tAvatarName[0], &tInfoData[4], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		mWorldInfo.LifeOrDeath[LifeorDeathZoneIndex] = 2;
		break;
	case 415:
		CopyMemory(&LifeorDeathZoneIndex, &tInfoData[0], 4);
		CopyMemory(&tAvatarName[0], &tInfoData[4], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		mWorldInfo.LifeOrDeath[LifeorDeathZoneIndex] = 0;
		break;

	case 416:
		break;
	case 417:
		break;
	case 418:
		break;



	//Ana kavmine geri döndü
	case 419:
		break;


	//case 420den 429a kadar lost soul
	case 420://Dk sayýyorr
		break;
	case 421://Savaþ baþlýyor eðer mapteyse 30dk kaldý diyor
		break;
	case 422://Baþarýyla fethedildi
		break;
	case 423://Dk sayýyor
		break;
	case 424://savunan kazandý diyor
		break;
	case 425://Arene imhasý baþlýyor
		break;
	case 426://Arena imhasý baþladý
		break;
	case 427://Arena imhasý baþarýlý
		break;
	case 428://Arena imhasý baþarýsýz
		break;
	case 429://Dk sayýyor
		break;


	//ittifak bozan paket
	case 500:
		break;

	//case 601den 610a kadar çember vadi kayýtlý
	case 600://Kayýt yapýyor
		break;
	case 601://istek yolluyor kayýt yapanlara
		break;
	case 602://Kapýyý kapýyor ve saniye sayýyor
		break;
	case 603://Savaþý baþlatýyor
		break;
	case 604:
		break;
	case 605://süre dolunca gidiyor
		break;
	case 606://Kazanana kapýyý açýyor
		break;
	case 607://Kazanana yeni mob çýkarýyor
		break;
	case 608://kazanana item veriyor 
		break;
	case 609://Çember vadi sona erdi yazdýrýyor
		break;
	case 610://Dk sayýyor
		break;


	//Resistance Invasion Canavar istilasý
	case 611://Dk sayýyor
		break;
	case 612://Savaþ baþlýyor
		break;
	case 613://Kaybetti diyor
		break;
	case 614://Kazandý diyor
		break;
	case 615://Ddk sayýyor
		break;


	//Alcatraz Savaþý
	case 620://Dk sayýyor
		break;
	case 621://Kapýyý açýyor
		break;
	case 622://Savaþý baþlatýyor
		break;
	case 624://Kazananý kavmi yazýyorsun
		mGAME.mWorldInfo.CemberVadisi = 1;
		break;
	case 625://zaman sayýyor
		break;
	case 626://zaman limiti aþýldý ve mapi sýfýrlýyor
		mGAME.mWorldInfo.CemberVadisi = -1;
		break;



	//Kýrmýzý çember saldýrýyor 
	case 628:
		break;


	//4bg sonra kodlanacak
	case 629:
		CopyMemory(&F4BGZoneIndex, &tInfoData[4], 4);
		CopyMemory(&tGuildName[0], &tInfoData[4], MAX_AVATAR_NAME_LENGTH);
		break;
	case 630://Savaþ sayýyor
		CopyMemory(&F4BGZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FourBigCastle[F4BGZoneIndex] = 1;
		break;
	case 631://1. aileyi çaðýrýyor
		CopyMemory(&F4BGZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FourBigCastle[F4BGZoneIndex] = 2;
		break;
	case 632://2. aileyi çaðýrýyor
		CopyMemory(&F4BGZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FourBigCastle[F4BGZoneIndex] = 2;
		break;
	case 633://Kapý kapandý
		CopyMemory(&F4BGZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FourBigCastle[F4BGZoneIndex] = 3;
		break;
	case 634://1. maç baþladý
		CopyMemory(&F4BGZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FourBigCastle[F4BGZoneIndex] = 4;
		break;
	case 635://1 tur sonuçlarý
		CopyMemory(&F4BGZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FourBigCastle[F4BGZoneIndex] = 5;
		break;
	case 636://Ara
		CopyMemory(&F4BGZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FourBigCastle[F4BGZoneIndex] = 5;
		break;
	case 637://2. tur için aileyi çaðýrýyor
		CopyMemory(&F4BGZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FourBigCastle[F4BGZoneIndex] = 6;
		break;
	case 638://2. tur için diðer aileyi çaðýrýyor
		CopyMemory(&F4BGZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FourBigCastle[F4BGZoneIndex] = 6;
		break;
	case 639://2.Tur baþlýyor
		CopyMemory(&F4BGZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FourBigCastle[F4BGZoneIndex] = 7;
		break;
	case 640://2. tur sonuçlarý
		CopyMemory(&F4BGZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FourBigCastle[F4BGZoneIndex] = 8;
		break;
	case 641://Ara
		CopyMemory(&F4BGZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FourBigCastle[F4BGZoneIndex] = 8;
		break;
	case 642://3. tur için aileyi çaðýrýyor
		CopyMemory(&F4BGZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FourBigCastle[F4BGZoneIndex] = 9;
		break;
	case 643://3. tur için diðer aileyi çaðýrýyor
		CopyMemory(&F4BGZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FourBigCastle[F4BGZoneIndex] = 9;
		break;
	case 644://3. tur  baþladý
		CopyMemory(&F4BGZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FourBigCastle[F4BGZoneIndex] = 10;
		break;
	case 645://3. tur sonuçlarý
		CopyMemory(&F4BGZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FourBigCastle[F4BGZoneIndex] = 11;
		break;
	case 646://3.tur ara
		CopyMemory(&F4BGZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FourBigCastle[F4BGZoneIndex] = 11;
		break;
	case 647://4.tur için aileyi çaðýrýyor
		CopyMemory(&F4BGZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FourBigCastle[F4BGZoneIndex] = 12;
		break;
	case 648://4.tur diðer için aileyi çaðýrýyor
		CopyMemory(&F4BGZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FourBigCastle[F4BGZoneIndex] = 12;
		break;
	case 649://4.tur baþladý
		CopyMemory(&F4BGZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FourBigCastle[F4BGZoneIndex] = 13;
		break;
	case 650://4.tur sonuçlarý
		CopyMemory(&F4BGZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FourBigCastle[F4BGZoneIndex] = 14;
		break;
	case 651://4.tur bitti
		CopyMemory(&F4BGZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FourBigCastle[F4BGZoneIndex] = 14;
		break;
	case 652://Savaþ bitti
		CopyMemory(&F4BGZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FourBigCastle[F4BGZoneIndex] = 0;
		break;

	//Çember Vadisi
	case 659://Çember vadi dk sayýyor
		mGAME.mWorldInfo.CemberVadisi = 1;
		break;
	case 660://Ýstek yolluyor
		mGAME.mWorldInfo.CemberVadisi = 2;
		break;
	case 661://Kapý kapanmasýna sayýyor
		mGAME.mWorldInfo.CemberVadisi = 2;
		break;
	case 662://Kapýyý kapatýyor
		mGAME.mWorldInfo.CemberVadisi = 3;
		break;
	case 663://Savaþ baþlýyor
		mGAME.mWorldInfo.CemberVadisi = 4;
		break;
	case 664://Kimse yoksa þehre yolluor
		mGAME.mWorldInfo.CemberVadisi = 7;
		break;
	case 665://Kimse yoksa þehre yolluor
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

	case 671: break;//7. seviye kale ulaþtý
	case 672: break;//96 rütbe duyurusu
	case 673: break;//20 üstü döküm duyurusu
	case 674: break;//Ultimate cape kazandý
	case 675: break;//8.bk kazandý
	case 676: break;//4. ve 5. soketi açtý
	case 677: break;//kapsülden 8.bk aldý

	//FullMoon Grounds
	case 700:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 0;
		break;
	case 701:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 1;
		break;
	case 702:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 2;
		break;
	case 703:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 3;
		break;
	case 704:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 4;
		break;
	case 705:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 5;
		break;
	case 706:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 30;
		break;
	case 707:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 26;
		break;
	case 708:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 6;
		break;
	case 709:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 7;
		break;
	case 710:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 8;
		break;
	case 711:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 9;
		break;
	case 712:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 11;
		break;
	case 713:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 12;
		break;
	case 714:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 13;
		break;
	case 715:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 14;
		break;
	case 716:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 15;
		break;
	case 717:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 16;
		break;
	case 718:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 17;
		break;
	case 719:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 18;
		break;
	case 720:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 19;
		break;
	case 721:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 20;
		break;
	case 722:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 19;
		break;
	case 723:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 21;
		break;
	case 724:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 22;
		break;
	case 725:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 23;
		break;
	case 726:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 24;
		break;
	case 727:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 25;
		break;
	case 728:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 30;
		break;
	case 729:
		CopyMemory(&FullMoonGroundsZoneIndex, &tInfoData[4], 4);
		mGAME.mWorldInfo.FullMoonGrounds[FullMoonGroundsZoneIndex] = 0;
		break;
	//Golden Moon
	case 740://Dk sayýyor
		mGAME.mWorldInfo.GoldenMoon = 0;
		break;
	case 741://Kapýyý açýyor
		mGAME.mWorldInfo.GoldenMoon = 1;
		break;
	case 742://Kapýyý kapýyor
		mGAME.mWorldInfo.GoldenMoon = 2;
		break;
	case 743://Dk sonra sona erecek yolluyor
		mGAME.mWorldInfo.GoldenMoon = 3;
		break;
	case 744://Boþ
		mGAME.mWorldInfo.GoldenMoon = 6;
		break;
	case 745://Dolunay taþý imhasý baþlayacak
		mGAME.mWorldInfo.GoldenMoon = 6;
		break;
	case 746://Dk sonra sona erecek
		mGAME.mWorldInfo.GoldenMoon = 5;
		break;
	case 747://Berabere
		mGAME.mWorldInfo.GoldenMoon = 7;
		break;
	case 748://2. adýmý kazanan
		mGAME.mWorldInfo.GoldenMoon = 6;
		break;
	case 749:
		mGAME.mWorldInfo.GoldenMoon = 0;
		break;
		//Green Valley
	case 751:
		break;

	//Cp kuleleri
	case 752://Oluþturma Ve yýkma
		CopyMemory(&CpTowerZoneIndex, &tInfoData[0], 4);
		CopyMemory(&CpTowerType, &tInfoData[4], 4);
		mGAME.mCpTower.CpTowers[CpTowerZoneIndex] = CpTowerType;
		break;
	case 753://Geliþtirme
		CopyMemory(&CpTowerZoneIndex, &tInfoData[0], 4);
		CopyMemory(&CpTowerType, &tInfoData[4], 4);
		mGAME.mCpTower.CpTowersAtakType[CpTowerZoneIndex] = CpTowerType;
		break;
	case 754://Saldýrý
		break;


	//Heavenly Cstle
	case 755://Dk sayýyor
		break;
	case 756://istek yolluyor
		mGAME.mWorldInfo.HevanlyCastle[HeavenlyCstleIndex] = 1;
		break;
	case 757://Kapýlarý kapanmasýna sayýyor
		mGAME.mWorldInfo.HevanlyCastle[HeavenlyCstleIndex] = 2;
		break;
	case 758://kapýlar kapanýyor ve saniye saymaya baþlýyor
		mGAME.mWorldInfo.HevanlyCastle[HeavenlyCstleIndex] = 3;
		break;
	case 759:
		mGAME.mWorldInfo.HevanlyCastle[HeavenlyCstleIndex] = 5;
		break;
	case 760://Berabere
		mGAME.mWorldInfo.HevanlyCastle[HeavenlyCstleIndex] = 5;
		break;
	case 761://Kazananlarý yolluyor
		mGAME.mWorldInfo.HevanlyCastle[HeavenlyCstleIndex] = 4;
		break;
	case 762://Eve dönüþ
		mGAME.mWorldInfo.HevanlyCastle[HeavenlyCstleIndex] = 5;
		break;
	case 763://Haritayý sýfýrlýyor
		mGAME.mWorldInfo.HevanlyCastle[HeavenlyCstleIndex] = 0;
		break;

	//Green Valley capture
	case 771: break;
	case 772: break;
	case 773: break;
	case 774:
		CopyMemory(&tTribe, &tInfoData[0], 4);
		CopyMemory(&tZone195LevelType, &tInfoData[8 + MAX_AVATAR_NAME_LENGTH], 4);
		mGAME.mWorldInfo.mProvingGroundsState[tZone195LevelType] = (tTribe + 1);
		mGAME.mWorldInfo.mProvingGroundsPoint[0] = mUTIL.CheckPVNumber(0);
		mGAME.mWorldInfo.mProvingGroundsPoint[1] = mUTIL.CheckPVNumber(1);
		mGAME.mWorldInfo.mProvingGroundsPoint[2] = mUTIL.CheckPVNumber(2);
		mGAME.mWorldInfo.mProvingGroundsPoint[3] = mUTIL.CheckPVNumber(3);
		break;
	//Heavenly Paradise
	case 780://Dk sayýyor ve girmelisiniz diyor
		mGAME.mWorldInfo.RainWaterHeaven = 0;
		break;
	case 781://Savaþ baþladý diyor 
		break;
	case 782://kazananý belirliyor  ve kaybedeni yolluyor
		break;
	case 784://Savaþ bitiyor ve kazananý yolluyor
		break;
	case 785://Herkesi yolluyor
		break;
	case 786://Mapi sýfýrlýyor
		break;

	case 788: break; // [Wuhun Fist Fighter] appeared yazýyor
	case 789: break; // [Poison Devil Generals] disappeared
	case 790: break; // [Poison Devil Generals] defeated
	case 791: break; // Ulitimate cape yükseltti

	case 795: break; // Ultimate stage refine

	
	}
	mTRANSFER.B_BROADCAST_INFO_RECV2( tInfoSort, &tInfoData[0] );
	mUTIL.Broadcast( FALSE, NULL, 0, false, 2 );
}
//-------------------------------------------------------------------------------------------------
