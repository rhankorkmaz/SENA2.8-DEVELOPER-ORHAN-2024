//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "Shengming.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_GAME
//-------------------------------------------------------------------------------------------------
//INSTANCE
MyGame mGAME;
//CREATE
MyGame::MyGame(void)
{
}
//INIT
BOOL MyGame::Init(void)
{
	int index01;
	int index02;

	for (index01 = 0; index01 < MAX_ZONE_NUMBER_NUM; index01++)
	{
		strcpy(mZoneConnectionInfo.mIP[index01], "0.0.0.0");
		mZoneConnectionInfo.mPort[index01] = 0;
	}

	Sifirlama = 0;

	mTickCount = 0;
	mWorldInfo.mZone038WinTribe = 0;
	mWorldInfo.mProvingGroundsPoint[0] = 0;
	mWorldInfo.mProvingGroundsPoint[1] = 0;
	mWorldInfo.mProvingGroundsPoint[2] = 0;
	mWorldInfo.mProvingGroundsPoint[3] = 0;
	mWorldInfo.mProvingGroundsState[0] = 0;
	mWorldInfo.mProvingGroundsState[1] = 0;
	mWorldInfo.mProvingGroundsState[2] = 0;
	mWorldInfo.mProvingGroundsState[3] = 0;
	mWorldInfo.mTribeSymbolBattle = 0;
	mWorldInfo.HollyBattleRank = 0;
	mWorldInfo.mTribe1Symbol = 0;
	mWorldInfo.mTribe2Symbol = 1;
	mWorldInfo.mTribe3Symbol = 2;
	mWorldInfo.mTribe4Symbol = 3;
	mWorldInfo.mMonsterSymbol = 0;
	mWorldInfo.mTribePoint[0] = 0;
	mWorldInfo.mTribePoint[1] = 0;
	mWorldInfo.mTribePoint[2] = 0;
	mWorldInfo.mTribePoint[3] = 0;
	mWorldInfo.mTribeCloseInfo[0] = 0;
	mWorldInfo.mTribeCloseInfo[1] = -1;
	mWorldInfo.mPossibleAllianceInfo[0][0] = 0;
	mWorldInfo.mPossibleAllianceInfo[0][1] = 0;
	mWorldInfo.mPossibleAllianceInfo[1][0] = 0;
	mWorldInfo.mPossibleAllianceInfo[1][1] = 0;
	mWorldInfo.mPossibleAllianceInfo[2][0] = 0;
	mWorldInfo.mPossibleAllianceInfo[2][1] = 0;
	mWorldInfo.mPossibleAllianceInfo[3][0] = 0;
	mWorldInfo.mPossibleAllianceInfo[3][1] = 0;
	mWorldInfo.mAllianceState[0][0] = -1;
	mWorldInfo.mAllianceState[0][1] = -1;
	mWorldInfo.mAllianceState[1][0] = -1;
	mWorldInfo.mAllianceState[1][1] = -1;
	mWorldInfo.mTribeVoteState[0] = 0;
	mWorldInfo.mTribeVoteState[1] = 0;
	mWorldInfo.mTribeVoteState[2] = 0;
	mWorldInfo.mTribeVoteState[3] = 0;
	mWorldInfo.mCloseVoteState[0] = 0;
	mWorldInfo.mCloseVoteState[1] = 0;
	mWorldInfo.mCloseVoteState[2] = 0;
	mWorldInfo.mCloseVoteState[3] = 0;
	mWorldInfo.mTribe4QuestDate = 0;
	mWorldInfo.mTribe4QuestState = 0;
	mWorldInfo.mTribe4QuestName[0] = '\0';
	mWorldInfo.SeizedGuild[0] = '\0';
	mWorldInfo.ChallengeGuild[0] = '\0';
	mWorldInfo.mZone049TypeState[0] = 0;
	mWorldInfo.mZone049TypeState[1] = 0;
	mWorldInfo.mZone049TypeState[2] = 0;
	mWorldInfo.mZone049TypeState[3] = 0;
	mWorldInfo.mZone049TypeState[4] = 0;
	mWorldInfo.mZone049TypeState[5] = 0;
#ifdef __GOD__
	mWorldInfo.mZone049TypeState[6] = 0;
	mWorldInfo.mZone049TypeState[7] = 0;
	mWorldInfo.mZone049TypeState[8] = 0;
#endif
	mWorldInfo.mZone051TypeState[0] = 0;
	mWorldInfo.mZone051TypeState[1] = 0;
	mWorldInfo.mZone051TypeState[2] = 0;
	mWorldInfo.mZone051TypeState[3] = 0;
	mWorldInfo.mZone051TypeState[4] = 0;
	mWorldInfo.mZone051TypeState[5] = 0;
	mWorldInfo.mZone053TypeState[0] = 0;
	mWorldInfo.mZone053TypeState[1] = 0;
	mWorldInfo.mZone053TypeState[2] = 0;
	mWorldInfo.mZone053TypeState[3] = 0;
	mWorldInfo.mZone053TypeState[4] = 0;
	mWorldInfo.mZone053TypeState[5] = 0;
	mWorldInfo.mZone053TypeState[6] = 0;
	mWorldInfo.mZone053TypeState[7] = 0;
	mWorldInfo.mZone053TypeState[8] = 0;
	mWorldInfo.mZone053TypeState[9] = 0;
	mWorldInfo.mZone175TypeState[0][0] = 0;
	mWorldInfo.mZone175TypeState[0][1] = 0;
	mWorldInfo.mZone175TypeState[0][2] = 0;
	mWorldInfo.mZone175TypeState[0][3] = 0;
	mWorldInfo.mZone175TypeState[0][4] = 0;
#ifdef __GOD__
	mWorldInfo.mZone175TypeState[0][5] = 0;
	mWorldInfo.mZone175TypeState[0][6] = 0;
	mWorldInfo.mZone175TypeState[0][7] = 0;
#endif
	mWorldInfo.mZone175TypeState[1][0] = 0;
	mWorldInfo.mZone175TypeState[1][1] = 0;
	mWorldInfo.mZone175TypeState[1][2] = 0;
	mWorldInfo.mZone175TypeState[1][3] = 0;
	mWorldInfo.mZone175TypeState[1][4] = 0;
#ifdef __GOD__
	mWorldInfo.mZone175TypeState[1][5] = 0;
	mWorldInfo.mZone175TypeState[1][6] = 0;
	mWorldInfo.mZone175TypeState[1][7] = 0;
#endif
	mWorldInfo.mZone175TypeState[2][0] = 0;
	mWorldInfo.mZone175TypeState[2][1] = 0;
	mWorldInfo.mZone175TypeState[2][2] = 0;
	mWorldInfo.mZone175TypeState[2][3] = 0;
	mWorldInfo.mZone175TypeState[2][4] = 0;
#ifdef __GOD__	
	mWorldInfo.mZone175TypeState[2][5] = 0;
	mWorldInfo.mZone175TypeState[2][6] = 0;
	mWorldInfo.mZone175TypeState[2][7] = 0;
#endif	
	mWorldInfo.mZone175TypeState[3][0] = 0;
	mWorldInfo.mZone175TypeState[3][1] = 0;
	mWorldInfo.mZone175TypeState[3][2] = 0;
	mWorldInfo.mZone175TypeState[3][3] = 0;
	mWorldInfo.mZone175TypeState[3][4] = 0;
#ifdef __GOD__	
	mWorldInfo.mZone175TypeState[3][5] = 0;
	mWorldInfo.mZone175TypeState[3][6] = 0;
	mWorldInfo.mZone175TypeState[3][7] = 0;
#endif
	mWorldInfo.mTribeGuardState[0][0] = 1;
	mWorldInfo.mTribeGuardState[0][1] = 1;
	mWorldInfo.mTribeGuardState[0][2] = 1;
	mWorldInfo.mTribeGuardState[0][3] = 1;
	mWorldInfo.mTribeGuardState[1][0] = 1;
	mWorldInfo.mTribeGuardState[1][1] = 1;
	mWorldInfo.mTribeGuardState[1][2] = 1;
	mWorldInfo.mTribeGuardState[1][3] = 1;
	mWorldInfo.mTribeGuardState[2][0] = 1;
	mWorldInfo.mTribeGuardState[2][1] = 1;
	mWorldInfo.mTribeGuardState[2][2] = 1;
	mWorldInfo.mTribeGuardState[2][3] = 1;
	mWorldInfo.mTribeGuardState[3][0] = 1;
	mWorldInfo.mTribeGuardState[3][1] = 1;
	mWorldInfo.mTribeGuardState[3][2] = 1;
	mWorldInfo.mTribeGuardState[3][3] = 1;
#ifdef __GOD__		
	mWorldInfo.mZone194State = 0;
	mWorldInfo.mTribeGeneralExperienceUpRatioInfo[0] = 0.0f;
	mWorldInfo.mTribeGeneralExperienceUpRatioInfo[1] = 0.0f;
	mWorldInfo.mTribeGeneralExperienceUpRatioInfo[2] = 0.0f;
	mWorldInfo.mTribeGeneralExperienceUpRatioInfo[3] = 0.0f;
	mWorldInfo.mTribeItemDropUpRatioInfo[0] = 0.0f;
	mWorldInfo.mTribeItemDropUpRatioInfo[1] = 0.0f;
	mWorldInfo.mTribeItemDropUpRatioInfo[2] = 0.0f;
	mWorldInfo.mTribeItemDropUpRatioInfo[3] = 0.0f;
	mWorldInfo.mTribeItemDropUpRatioForMyoungInfo[0] = 0.0f;
	mWorldInfo.mTribeItemDropUpRatioForMyoungInfo[1] = 0.0f;
	mWorldInfo.mTribeItemDropUpRatioForMyoungInfo[2] = 0.0f;
	mWorldInfo.mTribeItemDropUpRatioForMyoungInfo[3] = 0.0f;
	mWorldInfo.mTribeKillOtherTribeAddValueInfo[0] = 0;
	mWorldInfo.mTribeKillOtherTribeAddValueInfo[1] = 0;
	mWorldInfo.mTribeKillOtherTribeAddValueInfo[2] = 0;
	mWorldInfo.mTribeKillOtherTribeAddValueInfo[3] = 0;
#endif	
	for (int life = 0; life < 14; life++)
	{
		mWorldInfo.LifeOrDeath[life] = 0;
	}
	mWorldInfo.CemberVadisi = 0;

	// @ Tribe Formation Skill @
	mWorldInfo.mTribeMasterCallAbility[0] = 0;
	mWorldInfo.mTribeMasterCallAbility[1] = 0;
	mWorldInfo.mTribeMasterCallAbility[2] = 0;
	mWorldInfo.mTribeMasterCallAbility[3] = 0;
	// @
#ifdef __GOD__	    
	mWorldInfo.mZone267TypeState[0] = 0;
	mWorldInfo.mZone267TypeState[1] = 0;
	mWorldInfo.mZone267TypeState[2] = 0;
#endif		

	mCPtowers.CpTowers[0] = 0;
	mCPtowers.CpTowers[1] = 0;
	mCPtowers.CpTowers[2] = 0;
	mCPtowers.CpTowers[3] = 0;
	mCPtowers.CpTowers[4] = 0;
	mCPtowers.CpTowers[5] = 0;
	mCPtowers.CpTowers[6] = 0;
	mCPtowers.CpTowers[7] = 0;
	mCPtowers.CpTowers[8] = 0;
	mCPtowers.CpTowers[9] = 0;
	mCPtowers.CpTowers[10] = 0;
	mCPtowers.CpTowers[11] = 0;

	for (index01 = 0; index01 < 12; index01++)
	{
		mCPtowers.CpTowersAtakType[index01] = -1;
	}

	printf ("The mGame Init start\n");

	//LOG_TO_FILE ("DB process 01 end\n");

	for (index01 = 0; index01 < 3; index01++)
	{
		strcpy(mWorldInfo.GuildRank1[index01], "");
	}

	for (index01 = 0; index01 < 4; index01++)
	{
		for (index02 = 0; index02 < MAX_TRIBE_VOTE_AVATAR_NUM; index02++)
		{
			strcpy(mTribeInfo.mTribeVoteName[index01][index02], "");
			mTribeInfo.mTribeVoteLevel[index01][index02] = 0;
			mTribeInfo.mTribeVoteKillOtherTribe[index01][index02] = 0;
			mTribeInfo.mTribeVotePoint[index01][index02] = 0;
		}
	}
	for (index01 = 0; index01 < 4; index01++)
	{
		strcpy(mTribeInfo.mTribeMaster[index01], "");
		for (index02 = 0; index02 < MAX_TRIBE_SUBMASTER_NUM; index02++)
		{
			strcpy(mTribeInfo.mTribeSubMaster[index01][index02], "");
		}
	}
	if (!mDB.DB_PROCESS_01(&mWorldInfo))
	{
		printf("error DB_PROCESS_01\n");
		return FALSE;
	}
	//LOG_TO_FILE ("DB process 01 end\n");
	for (index01 = 0; index01 < 4; index01++)
	{
		for (index02 = 0; index02 < MAX_TRIBE_VOTE_AVATAR_NUM; index02++)
		{
			strcpy(mTribeInfo.mTribeVoteName[index01][index02], "");
			mTribeInfo.mTribeVoteLevel[index01][index02] = 0;
			mTribeInfo.mTribeVoteKillOtherTribe[index01][index02] = 0;
			mTribeInfo.mTribeVotePoint[index01][index02] = 0;
		}
	}
	for (index01 = 0; index01 < 4; index01++)
	{
		strcpy(mTribeInfo.mTribeMaster[index01], "");
		for (index02 = 0; index02 < MAX_TRIBE_SUBMASTER_NUM; index02++)
		{
			strcpy(mTribeInfo.mTribeSubMaster[index01][index02], "");
		}
	}
	//LOG_TO_FILE ("Value Init end\n");
	if (!mDB.DB_PROCESS_10(&mTribeInfo))
	{
		printf("error DB_PROCESS_10");
		return FALSE;
	}

	/*if (!mDB.DB_PROCESS_14(1))
	{
		printf("test mGame DB012 Init\n");
		return FALSE;
	}*/

	//LOG_TO_FILE ("The mGame Init end\n");
	return TRUE;
}
//CheckPVNumber
int MyGame::CheckPVNumber(int tTribe)
{
	int a = 0;

	if (mGAME.mWorldInfo.mProvingGroundsState[0] == (tTribe + 1))
	{
		a++;
	}
	if (mGAME.mWorldInfo.mProvingGroundsState[1] == (tTribe + 1))
	{
		a++;
	}
	if (mGAME.mWorldInfo.mProvingGroundsState[2] == (tTribe + 1))
	{
		a++;
	}
	if (mGAME.mWorldInfo.mProvingGroundsState[3] == (tTribe + 1))
	{
		a++;
	}

	return a;
}
//FREE
void MyGame::Free(void)
{
}
//-------------------------------------------------------------------------------------------------
