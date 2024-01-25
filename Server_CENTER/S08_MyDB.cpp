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
MyDB::MyDB(void)
{
}
//INIT
BOOL MyDB::Init(void)
{
	if (mDB01.set_db_conn_info(mSERVER_INFO.mDB_1_IP, mSERVER_INFO.mDB_1_IP, mSERVER_INFO.mDB_1_PORT
		, "ts2_gamedb", mSERVER_INFO.mDB_1_ID, mSERVER_INFO.mDB_1_PASSWORD) < 0)
	{
		return false;
	}
	if (!mDB01.connect()) {
		printf("Baglanýlamadý1\n");
		return FALSE;
	}

	if (mDB01.exec_query("SET character SET latin5;", CMySQL::CLEAR) != 0) {
		printf("[%s] DB character false(%s)! \n", __FUNCTION__, mDB01.get_error_msg().c_str());
		return FALSE;
	}


	//Account DB
	if (mDB02.set_db_conn_info(mSERVER_INFO.mDB_1_IP, mSERVER_INFO.mDB_1_IP, mSERVER_INFO.mDB_1_PORT
		, "ts2_gamedb", mSERVER_INFO.mDB_1_ID, mSERVER_INFO.mDB_1_PASSWORD) < 0)
	{
		return false;
	}
	if (!mDB02.connect()) {
		printf("Baglanýlamadý2\n");
		return FALSE;
	}
	if (mDB02.exec_query("SET character SET latin5;", CMySQL::CLEAR) != 0) {
		printf("[%s] DB character false(%s)! \n", __FUNCTION__, mDB02.get_error_msg().c_str());
		return FALSE;
	}
	return TRUE;
}
//FREE
void MyDB::Free(void)
{
#ifdef __WIN32__
	CoUninitialize();
#endif
}
//RECONNECT_TO_DATABASE01
BOOL MyDB::RECONNECT_TO_DATABASE01(void)
{
	if (mDB01.IsConnected())
	{
		return TRUE;
	}
	if (!mDB01.Reconnect())
	{
		return FALSE;
	}
	if (mDB01.exec_query("SET character SET latin5;", CMySQL::CLEAR) != 0) {
		__LogMgr()->Log("[%s] DB character false(%s)! \n", __FUNCTION__, mDB01.get_error_msg().c_str());
		return FALSE;
	}
	return TRUE;
}
//RECONNECT_TO_DATABASE02
BOOL MyDB::RECONNECT_TO_DATABASE02(void)
{
	if (mDB02.IsConnected())
	{
		return TRUE;
	}
	if (!mDB02.Reconnect())
	{
		return FALSE;
	}
	if (mDB02.exec_query("SET character SET latin5;", CMySQL::CLEAR) != 0) {
		__LogMgr()->Log("[%s] DB character false(%s)! \n", __FUNCTION__, mDB02.get_error_msg().c_str());
		return FALSE;
	}
	return TRUE;
}
//DB_PROCESS_01
BOOL MyDB::DB_PROCESS_01(WORLD_INFO* tWorldInfo)
{
	int iAffected;
	int iCounts;
	MYSQL_ROW row;
	MYSQL_RES* res = NULL;
	printf("The db process 02 called");
	sprintf(mQUERY, "select mZone38WinTribe,mTribe1Symbol,mTribe2Symbol,mTribe3Symbol,mTribe4Symbol,mMonsterSymbol,mTribe1Point,mTribe2Point,mTribe3Point,mTribe4Point,mCloseTime,mCloseTribe,mPossibleAlliance01Date,mPossibleAlliance01Info,mPossibleAlliance02Date,mPossibleAlliance02Info,mPossibleAlliance03Date,mPossibleAlliance03Info,mPossibleAlliance04Date,mPossibleAlliance04Info,mAlliance0101,mAlliance0102,mAlliance0201,mAlliance0202,mTribe1VoteState,mTribe2VoteState,mTribe3VoteState,mTribe4VoteState,mClose1VoteState,mClose2VoteState,mClose3VoteState,mClose4VoteState,mTribe4QuestDate,mTribe4QuestState,mTribe4QuestName from %s where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, g_env.world_num);
	if (!RECONNECT_TO_DATABASE01())
	{
		return FALSE;
	}

	iAffected = 0;




	if ((iAffected = mDB01.exec_query(mQUERY)) < 0)
	{
		__LogMgr()->Log("![CRITICAL - (1)] The query execution failed in (%s - %d).\n", __FILE__, __LINE__);
		__LogMgr()->Log("\t\t\tWhy - %s\n", mDB01.get_error_msg().c_str());
		return FALSE;
	}

	printf("%s execute query\n", __FUNCTION__);
	iCounts = 0;
	res = mDB01.get_res();
	if (res == NULL) {
		return false;
	}
	while ((row = mysql_fetch_row(res))) {
		tWorldInfo->mZone038WinTribe = atoi(row[0]);
		tWorldInfo->mTribe1Symbol = atoi(row[1]);
		tWorldInfo->mTribe2Symbol = atoi(row[2]);
		tWorldInfo->mTribe3Symbol = atoi(row[3]);
		tWorldInfo->mTribe4Symbol = atoi(row[4]);
		tWorldInfo->mMonsterSymbol = atoi(row[5]);
		tWorldInfo->mTribePoint[0] = atoi(row[6]);
		tWorldInfo->mTribePoint[1] = atoi(row[7]);
		tWorldInfo->mTribePoint[2] = atoi(row[8]);
		tWorldInfo->mTribePoint[3] = atoi(row[9]);
		tWorldInfo->mTribeCloseInfo[0] = atoi(row[10]);
		tWorldInfo->mTribeCloseInfo[1] = atoi(row[11]);
		tWorldInfo->mPossibleAllianceInfo[0][0] = atoi(row[12]);
		tWorldInfo->mPossibleAllianceInfo[0][1] = atoi(row[13]);
		tWorldInfo->mPossibleAllianceInfo[1][0] = atoi(row[14]);
		tWorldInfo->mPossibleAllianceInfo[1][1] = atoi(row[15]);
		tWorldInfo->mPossibleAllianceInfo[2][0] = atoi(row[16]);
		tWorldInfo->mPossibleAllianceInfo[2][1] = atoi(row[17]);
		tWorldInfo->mPossibleAllianceInfo[3][0] = atoi(row[18]);
		tWorldInfo->mPossibleAllianceInfo[3][1] = atoi(row[19]);
		tWorldInfo->mAllianceState[0][0] = atoi(row[20]);
		tWorldInfo->mAllianceState[0][1] = atoi(row[21]);
		tWorldInfo->mAllianceState[1][0] = atoi(row[22]);
		tWorldInfo->mAllianceState[1][1] = atoi(row[23]);
		tWorldInfo->mTribeVoteState[0] = atoi(row[24]);
		tWorldInfo->mTribeVoteState[1] = atoi(row[25]);
		tWorldInfo->mTribeVoteState[2] = atoi(row[26]);
		tWorldInfo->mTribeVoteState[3] = atoi(row[27]);
		tWorldInfo->mCloseVoteState[0] = atoi(row[28]);
		tWorldInfo->mCloseVoteState[1] = atoi(row[29]);
		tWorldInfo->mCloseVoteState[2] = atoi(row[30]);
		tWorldInfo->mCloseVoteState[3] = atoi(row[31]);
		tWorldInfo->mTribe4QuestDate = atoi(row[32]);
		tWorldInfo->mTribe4QuestState = atoi(row[33]);
		_snprintf(tWorldInfo->mTribe4QuestName, MAX_TRIBE4_QUEST_NAME_LENGTH, "%s", row[34]);
		iCounts++;
	}
	printf("%s Fetch row, iCounts : %d\n", __FUNCTION__, iCounts);
	mDB01.clear_res();
	if (iCounts != 1)
	{
		return FALSE;
	}
	printf("%s end, clear_res\n", __FUNCTION__);

	return TRUE;
}
//DB_PROCESS_02
BOOL MyDB::DB_PROCESS_02(WORLD_INFO* tWorldInfo)
{
	int iAffected;
	int iCounts;
	MYSQL_ROW row;
	MYSQL_RES* res = NULL;
	long tTribePoint[4];

	__LogMgr()->Log("The db process 02 called");
	sprintf(mQUERY, "select mTribe1Point,mTribe2Point,mTribe3Point,mTribe4Point from %s where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, g_env.world_num);
	if (!RECONNECT_TO_DATABASE01())
	{
		return FALSE;
	}
	iAffected = 0;

	if ((iAffected = mDB01.exec_query(mQUERY)) < 0)
	{
		return FALSE;
	}
	iCounts = 0;
	res = mDB01.get_res();
	if (res == NULL) {
		return false;
	}
	while ((row = mysql_fetch_row(res)))
	{
		tWorldInfo->mTribePoint[0] = atoi(row[0]);
		tWorldInfo->mTribePoint[1] = atoi(row[1]);
		tWorldInfo->mTribePoint[2] = atoi(row[2]);
		tWorldInfo->mTribePoint[3] = atoi(row[3]);
		iCounts++;
	}
	mDB01.clear_res();
	if (iCounts != 1)
	{
		return FALSE;
	}

	return TRUE;
}
//DB_PROCESS_03
BOOL MyDB::DB_PROCESS_03(int tTribe)
{
	int iAffected;

	sprintf(mQUERY, "update %s set mZone38WinTribeDate=now(),mZone38WinTribe=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tTribe, g_env.world_num);
	if (!RECONNECT_TO_DATABASE01())
	{
		return FALSE;
	}
	iAffected = 0;

	if ((iAffected = mDB01.exec_query(mQUERY, CMySQL::CLEAR)) < 0)
	{
		return FALSE;
	}

	return TRUE;
}
//DB_PROCESS_04
BOOL MyDB::DB_PROCESS_04(int zeroRank ,int tSort, int tTribe)
{
	int iAffected;

	switch (tSort)
	{
	case 1:
		sprintf(mQUERY, "update %s set mTribe1SymbolDate=now(),mTribe1Symbol=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tTribe, g_env.world_num);
		break;
	case 2:
		sprintf(mQUERY, "update %s set mTribe2SymbolDate=now(),mTribe2Symbol=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tTribe, g_env.world_num);
		break;
	case 3:
		sprintf(mQUERY, "update %s set mTribe3SymbolDate=now(),mTribe3Symbol=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tTribe, g_env.world_num);
		break;
	case 4:
		sprintf(mQUERY, "update %s set mTribe4SymbolDate=now(),mTribe4Symbol=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tTribe, g_env.world_num);
		break;
	case 5:
		sprintf(mQUERY, "update %s set mMonsterSymbolDate=now(),mMonsterSymbol=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tTribe, g_env.world_num);
		break;
	default:
		return FALSE;
	}
	if (!RECONNECT_TO_DATABASE01())
	{
		return FALSE;
	}
	iAffected = 0;

	if ((iAffected = mDB01.exec_query(mQUERY, CMySQL::CLEAR)) < 0)
	{
		return FALSE;
	}

	//Rank Sýfýrlama
	if (zeroRank == 1)
	{
		sprintf(mQUERY, "update avatarinfo set aRankPoint = 0, aRank = 0");
		if (!RECONNECT_TO_DATABASE01())
		{
			return FALSE;
		}
		iAffected = 0;
		if ((iAffected = mDB01.exec_query(mQUERY, CMySQL::CLEAR)) < 0)
		{
			return FALSE;
		}		
	}
	return TRUE;
}
//DB_PROCESS_05
BOOL MyDB::DB_PROCESS_05(int tDate, int tTribe)
{
	int iAffected;

	sprintf(mQUERY, "update %s set mCloseTime=%d,mCloseTribe=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tDate, tTribe, g_env.world_num);
	if (!RECONNECT_TO_DATABASE01())
	{
		return FALSE;
	}
	iAffected = 0;

	if ((iAffected = mDB01.exec_query(mQUERY, CMySQL::CLEAR)) < 0)
	{
		return FALSE;
	}

	return TRUE;
}
//DB_PROCESS_06
BOOL MyDB::DB_PROCESS_06(int tSort, int tDate, int tValue)
{
	int iAffected;

	switch (tSort)
	{
	case 1:
		sprintf(mQUERY, "update %s set mPossibleAlliance01Date=%d,mPossibleAlliance01Info=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tDate, tValue, g_env.world_num);
		break;
	case 2:
		sprintf(mQUERY, "update %s set mPossibleAlliance02Date=%d,mPossibleAlliance02Info=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tDate, tValue, g_env.world_num);
		break;
	case 3:
		sprintf(mQUERY, "update %s set mPossibleAlliance03Date=%d,mPossibleAlliance03Info=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tDate, tValue, g_env.world_num);
		break;
	case 4:
		sprintf(mQUERY, "update %s set mPossibleAlliance04Date=%d,mPossibleAlliance04Info=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tDate, tValue, g_env.world_num);
		break;
	default:
		return FALSE;
	}
	iAffected = 0;

	if (!RECONNECT_TO_DATABASE01())
	{
		return FALSE;
	}
	if ((iAffected = mDB01.exec_query(mQUERY, CMySQL::CLEAR)) < 0)
	{
		return FALSE;
	}

	return TRUE;
}
//DB_PROCESS_07
BOOL MyDB::DB_PROCESS_07(int tSort, int tAlliance01, int tAlliance02)
{
	int iAffected;

	switch (tSort)
	{
	case 1:
		sprintf(mQUERY, "update %s set mAlliance01Date=now(),mAlliance0101=%d,mAlliance0102=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tAlliance01, tAlliance02, g_env.world_num);
		break;
	case 2:
		sprintf(mQUERY, "update %s set mAlliance02Date=now(),mAlliance0201=%d,mAlliance0202=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tAlliance01, tAlliance02, g_env.world_num);
		break;
	default:
		return FALSE;
	}
	iAffected = 0;

	if (!RECONNECT_TO_DATABASE01())
	{
		return FALSE;
	}

	if ((iAffected = mDB01.exec_query(mQUERY, CMySQL::CLEAR)) < 0)
	{
		return FALSE;
	}

	return TRUE;
}
//DB_PROCESS_08
BOOL MyDB::DB_PROCESS_08(int tSort, int tValue)
{
	int iAffected;

	switch (tSort)
	{
	case 1:
		sprintf(mQUERY, "update %s set mTribe1VoteDate=now(),mTribe1VoteState=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tValue, g_env.world_num);
		break;
	case 2:
		sprintf(mQUERY, "update %s set mTribe2VoteDate=now(),mTribe2VoteState=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tValue, g_env.world_num);
		break;
	case 3:
		sprintf(mQUERY, "update %s set mTribe3VoteDate=now(),mTribe3VoteState=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tValue, g_env.world_num);
		break;
	case 4:
		sprintf(mQUERY, "update %s set mTribe4VoteDate=now(),mTribe4VoteState=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tValue, g_env.world_num);
		break;
	default:
		return FALSE;
	}
	iAffected = 0;
#ifdef __WIN32__
	if (!mDB01.Execute(mQUERY, iAffected))
	{
		return FALSE;
	}
#else
	if (!RECONNECT_TO_DATABASE01())
	{
		return FALSE;
	}
	if ((iAffected = mDB01.exec_query(mQUERY), CMySQL::CLEAR) < 0)
	{
		return FALSE;
	}
#endif
	return TRUE;
}
//DB_PROCESS_09
BOOL MyDB::DB_PROCESS_09(int tSort, int tValue)
{
	int iAffected;

	switch (tSort)
	{
	case 1:
		sprintf(mQUERY, "update %s set mClose1VoteDate=now(),mClose1VoteState=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tValue, g_env.world_num);
		break;
	case 2:
		sprintf(mQUERY, "update %s set mClose2VoteDate=now(),mClose2VoteState=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tValue, g_env.world_num);
		break;
	case 3:
		sprintf(mQUERY, "update %s set mClose3VoteDate=now(),mClose3VoteState=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tValue, g_env.world_num);
		break;
	case 4:
		sprintf(mQUERY, "update %s set mClose4VoteDate=now(),mClose4VoteState=%d where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table01, tValue, g_env.world_num);
		break;
	default:
		return FALSE;
	}
	iAffected = 0;
#ifdef __WIN32__
	if (!mDB01.Execute(mQUERY, iAffected))
	{
		return FALSE;
	}
#else
	if (!RECONNECT_TO_DATABASE01())
	{
		return FALSE;
	}
	if ((iAffected = mDB01.exec_query(mQUERY, CMySQL::CLEAR)) < 0)
	{
		return FALSE;
	}
#endif
	return TRUE;
}
//DB_PROCESS_10
BOOL MyDB::DB_PROCESS_10(TRIBE_INFO* tTribeInfo)
{
	MYSQL_ROW row;
	MYSQL_RES* res = NULL;
	int index01;
	int index02;
	int index03;
	char tempString01[1000];
	int iAffected;
	int iCounts;
	char mTribeVoteInfo[1041];
	char mTribe01Master[MAX_AVATAR_NAME_LENGTH];
	char mTribe01SubMasterInfo[145];
	char mTribe02Master[MAX_AVATAR_NAME_LENGTH];
	char mTribe02SubMasterInfo[145];
	char mTribe03Master[MAX_AVATAR_NAME_LENGTH];
	char mTribe03SubMasterInfo[145];
	char mTribe04Master[MAX_AVATAR_NAME_LENGTH];
	char mTribe04SubMasterInfo[145];

	sprintf(mQUERY, "select mTribeVoteInfo,mTribe01Master,mTribe01SubMasterInfo,mTribe02Master,mTribe02SubMasterInfo,mTribe03Master,mTribe03SubMasterInfo,mTribe04Master,mTribe04SubMasterInfo from %s where aWorldNumber = %d", mSERVER_INFO.mDB_1_Table02, g_env.world_num);
	if (!RECONNECT_TO_DATABASE01())
	{
		return FALSE;
	}
	iAffected = 0;

	if ((iAffected = mDB01.exec_query(mQUERY)) < 0)
	{
		return FALSE;
	}
	//LOG_TO_FILE_1 ("%s execute query\n", __FUNCTION__);
	iCounts = 0;
	res = mDB01.get_res();
	if (res == NULL) {
		return false;
	}
	while ((row = mysql_fetch_row(res)))
	{
		_snprintf(mTribeVoteInfo, 1041, "%s", row[0]);
		_snprintf(mTribe01Master, MAX_AVATAR_NAME_LENGTH, "%s", row[1]);
		_snprintf(mTribe01SubMasterInfo, 145, "%s", row[2]);
		_snprintf(mTribe02Master, MAX_AVATAR_NAME_LENGTH, "%s", row[3]);
		_snprintf(mTribe02SubMasterInfo, 145, "%s", row[4]);
		_snprintf(mTribe03Master, MAX_AVATAR_NAME_LENGTH, "%s", row[5]);
		_snprintf(mTribe03SubMasterInfo, 145, "%s", row[6]);
		_snprintf(mTribe04Master, MAX_AVATAR_NAME_LENGTH, "%s", row[7]);
		_snprintf(mTribe04SubMasterInfo, 145, "%s", row[8]);
		iCounts++;
	}
	__LogMgr()->Log("%s fetch row, iCounts : %d\n", __FUNCTION__, iCounts);

	mDB01.clear_res();
	if (iCounts != 1)
	{
		return FALSE;
	}
	//LOG_TO_FILE_1 ("%s end, clear_res \n", __FUNCTION__);

	if (strlen(mTribeVoteInfo) == 0)
	{
		strcpy(mTribeVoteInfo, "");
		for (index01 = 0; index01 < (4 * MAX_TRIBE_VOTE_AVATAR_NUM); index01++)
		{
			strcat(mTribeVoteInfo, "@@@@@@@@@@@@00000000000000");
		}
	}
	if (strlen(mTribeVoteInfo) != 1040)
	{
		__LogMgr()->Log("%d %d\n", __LINE__, strlen(mTribeVoteInfo));
		return FALSE;
	}
	if (strlen(mTribe01SubMasterInfo) == 0)
	{
		strcpy(mTribe01SubMasterInfo, "");
		for (index01 = 0; index01 < MAX_TRIBE_SUBMASTER_NUM; index01++)
		{
			strcat(mTribe01SubMasterInfo, "@@@@@@@@@@@@");
		}
	}
	if (strlen(mTribe01SubMasterInfo) != 144)
	{
		__LogMgr()->Log("%d %d\n", __LINE__, strlen(mTribe01SubMasterInfo));
		return FALSE;
	}
	if (strlen(mTribe02SubMasterInfo) == 0)
	{
		strcpy(mTribe02SubMasterInfo, "");
		for (index01 = 0; index01 < MAX_TRIBE_SUBMASTER_NUM; index01++)
		{
			strcat(mTribe02SubMasterInfo, "@@@@@@@@@@@@");
		}
	}
	if (strlen(mTribe02SubMasterInfo) != 144)
	{
		__LogMgr()->Log("%d %d\n", __LINE__, strlen(mTribe02SubMasterInfo));
		return FALSE;
	}
	if (strlen(mTribe03SubMasterInfo) == 0)
	{
		strcpy(mTribe03SubMasterInfo, "");
		for (index01 = 0; index01 < MAX_TRIBE_SUBMASTER_NUM; index01++)
		{
			strcat(mTribe03SubMasterInfo, "@@@@@@@@@@@@");
		}
	}
	if (strlen(mTribe03SubMasterInfo) != 144)
	{
		__LogMgr()->Log("%d %d\n", __LINE__, strlen(mTribe03SubMasterInfo));
		return FALSE;
	}
	if (strlen(mTribe04SubMasterInfo) == 0)
	{
		strcpy(mTribe04SubMasterInfo, "");
		for (index01 = 0; index01 < MAX_TRIBE_SUBMASTER_NUM; index01++)
		{
			strcat(mTribe04SubMasterInfo, "@@@@@@@@@@@@");
		}
	}
	if (strlen(mTribe04SubMasterInfo) != 144)
	{
		//__LogMgr()->Log("%d %d\n", __LINE__, strlen( mTribe04SubMasterInfo ));
		return FALSE;
	}
	for (index01 = 0; index01 < 4; index01++)
	{
		for (index02 = 0; index02 < MAX_TRIBE_VOTE_AVATAR_NUM; index02++)
		{
			CopyMemory(&tTribeInfo->mTribeVoteName[index01][index02][0], &mTribeVoteInfo[((index01 * MAX_TRIBE_VOTE_AVATAR_NUM + index02) * 26 + 0)], 12);
			for (index03 = 0; index03 < 12; index03++)
			{
				if (::IsDBCSLeadByte(tTribeInfo->mTribeVoteName[index01][index02][index03]) == TRUE) {
					if (index03 != 11) index03++;
					continue;
				}

				if (tTribeInfo->mTribeVoteName[index01][index02][index03] == '@')
				{
					break;
				}
			}
			tTribeInfo->mTribeVoteName[index01][index02][index03] = '\0';
			CopyMemory(&tempString01[0], &mTribeVoteInfo[((index01 * MAX_TRIBE_VOTE_AVATAR_NUM + index02) * 26 + 12)], 2);
			tempString01[2] = '\0';
			tTribeInfo->mTribeVoteLevel[index01][index02] = atoi(tempString01);
			CopyMemory(&tempString01[0], &mTribeVoteInfo[((index01 * MAX_TRIBE_VOTE_AVATAR_NUM + index02) * 26 + 14)], 6);
			tempString01[6] = '\0';
			tTribeInfo->mTribeVoteKillOtherTribe[index01][index02] = atoi(tempString01);
			CopyMemory(&tempString01[0], &mTribeVoteInfo[((index01 * MAX_TRIBE_VOTE_AVATAR_NUM + index02) * 26 + 20)], 6);
			tempString01[6] = '\0';
			tTribeInfo->mTribeVotePoint[index01][index02] = atoi(tempString01);
		}
	}
	strcpy(tTribeInfo->mTribeMaster[0], mTribe01Master);
	for (index01 = 0; index01 < MAX_TRIBE_SUBMASTER_NUM; index01++)
	{
		CopyMemory(&tTribeInfo->mTribeSubMaster[0][index01][0], &mTribe01SubMasterInfo[(index01 * 12 + 0)], 12);
		for (index02 = 0; index02 < 12; index02++)
		{
			if (::IsDBCSLeadByte(tTribeInfo->mTribeSubMaster[0][index01][index02]) == TRUE) {
				if (index02 != 11) index02++;
				continue;
			}

			if (tTribeInfo->mTribeSubMaster[0][index01][index02] == '@')
			{
				break;
			}
		}
		tTribeInfo->mTribeSubMaster[0][index01][index02] = '\0';
	}
	strcpy(tTribeInfo->mTribeMaster[1], mTribe02Master);
	for (index01 = 0; index01 < MAX_TRIBE_SUBMASTER_NUM; index01++)
	{
		CopyMemory(&tTribeInfo->mTribeSubMaster[1][index01][0], &mTribe02SubMasterInfo[(index01 * 12 + 0)], 12);
		for (index02 = 0; index02 < 12; index02++)
		{
			if (::IsDBCSLeadByte(tTribeInfo->mTribeSubMaster[1][index01][index02]) == TRUE) {
				if (index02 != 11) index02++;
				continue;
			}

			if (tTribeInfo->mTribeSubMaster[1][index01][index02] == '@')
			{
				break;
			}
		}
		tTribeInfo->mTribeSubMaster[1][index01][index02] = '\0';
	}
	strcpy(tTribeInfo->mTribeMaster[2], mTribe03Master);
	for (index01 = 0; index01 < MAX_TRIBE_SUBMASTER_NUM; index01++)
	{
		CopyMemory(&tTribeInfo->mTribeSubMaster[2][index01][0], &mTribe03SubMasterInfo[(index01 * 12 + 0)], 12);
		for (index02 = 0; index02 < 12; index02++)
		{
			if (::IsDBCSLeadByte(tTribeInfo->mTribeSubMaster[2][index01][index02]) == TRUE) {
				if (index02 != 11) index02++;
				continue;
			}

			if (tTribeInfo->mTribeSubMaster[2][index01][index02] == '@')
			{
				break;
			}
		}
		tTribeInfo->mTribeSubMaster[2][index01][index02] = '\0';
	}
	strcpy(tTribeInfo->mTribeMaster[3], mTribe04Master);
	for (index01 = 0; index01 < MAX_TRIBE_SUBMASTER_NUM; index01++)
	{
		CopyMemory(&tTribeInfo->mTribeSubMaster[3][index01][0], &mTribe04SubMasterInfo[(index01 * 12 + 0)], 12);
		for (index02 = 0; index02 < 12; index02++)
		{
			if (::IsDBCSLeadByte(tTribeInfo->mTribeSubMaster[3][index01][index02]) == TRUE) {
				if (index02 != 11) index02++;
				continue;
			}

			if (tTribeInfo->mTribeSubMaster[3][index01][index02] == '@')
			{
				break;
			}
		}
		tTribeInfo->mTribeSubMaster[3][index01][index02] = '\0';
	}
	return TRUE;
}
//DB_PROCESS_11
BOOL MyDB::DB_PROCESS_11(TRIBE_INFO* tTribeInfo)
{
	int index01;
	int index02;
	char tempString01[1000];
	int iAffected;
	char mTribeVoteInfo[1041];
	char mTribe01SubMasterInfo[145];
	char mTribe02SubMasterInfo[145];
	char mTribe03SubMasterInfo[145];
	char mTribe04SubMasterInfo[145];

	strcpy(mTribeVoteInfo, "");
	for (index01 = 0; index01 < 4; index01++)
	{
		for (index02 = 0; index02 < MAX_TRIBE_VOTE_AVATAR_NUM; index02++)
		{
			strcpy(tempString01, "@@@@@@@@@@@@");
			CopyMemory(&tempString01[0], &tTribeInfo->mTribeVoteName[index01][index02][0], strlen(tTribeInfo->mTribeVoteName[index01][index02]));
			tempString01[12] = '\0';
			strcat(mTribeVoteInfo, tempString01);
			sprintf(tempString01, "%02d%06d%06d", (tTribeInfo->mTribeVoteLevel[index01][index02] % 100), (tTribeInfo->mTribeVoteKillOtherTribe[index01][index02] % 1000000), (tTribeInfo->mTribeVotePoint[index01][index02] % 1000000));
			strcat(mTribeVoteInfo, tempString01);
		}
	}
	strcpy(mTribe01SubMasterInfo, "");
	for (index01 = 0; index01 < MAX_TRIBE_SUBMASTER_NUM; index01++)
	{
		strcpy(tempString01, "@@@@@@@@@@@@");
		CopyMemory(&tempString01[0], &tTribeInfo->mTribeSubMaster[0][index01][0], strlen(tTribeInfo->mTribeSubMaster[0][index01]));
		tempString01[12] = '\0';
		strcat(mTribe01SubMasterInfo, tempString01);
	}
	strcpy(mTribe02SubMasterInfo, "");
	for (index01 = 0; index01 < MAX_TRIBE_SUBMASTER_NUM; index01++)
	{
		strcpy(tempString01, "@@@@@@@@@@@@");
		CopyMemory(&tempString01[0], &tTribeInfo->mTribeSubMaster[1][index01][0], strlen(tTribeInfo->mTribeSubMaster[1][index01]));
		tempString01[12] = '\0';
		strcat(mTribe02SubMasterInfo, tempString01);
	}
	strcpy(mTribe03SubMasterInfo, "");
	for (index01 = 0; index01 < MAX_TRIBE_SUBMASTER_NUM; index01++)
	{
		strcpy(tempString01, "@@@@@@@@@@@@");
		CopyMemory(&tempString01[0], &tTribeInfo->mTribeSubMaster[2][index01][0], strlen(tTribeInfo->mTribeSubMaster[2][index01]));
		tempString01[12] = '\0';
		strcat(mTribe03SubMasterInfo, tempString01);
	}
	strcpy(mTribe04SubMasterInfo, "");
	for (index01 = 0; index01 < MAX_TRIBE_SUBMASTER_NUM; index01++)
	{
		strcpy(tempString01, "@@@@@@@@@@@@");
		CopyMemory(&tempString01[0], &tTribeInfo->mTribeSubMaster[3][index01][0], strlen(tTribeInfo->mTribeSubMaster[3][index01]));
		tempString01[12] = '\0';
		strcat(mTribe04SubMasterInfo, tempString01);
	}
	sprintf(mQUERY, "update %s set mTribeVoteInfo='%s',mTribe01Master='%s',mTribe01SubMasterInfo='%s',mTribe02Master='%s',mTribe02SubMasterInfo='%s',mTribe03Master='%s',mTribe03SubMasterInfo='%s',mTribe04Master='%s',mTribe04SubMasterInfo='%s' where aWorldNumber = %d",
		mSERVER_INFO.mDB_1_Table02,
		mTribeVoteInfo,
		tTribeInfo->mTribeMaster[0],
		mTribe01SubMasterInfo,
		tTribeInfo->mTribeMaster[1],
		mTribe02SubMasterInfo,
		tTribeInfo->mTribeMaster[2],
		mTribe03SubMasterInfo,
		tTribeInfo->mTribeMaster[3],
		mTribe04SubMasterInfo,
		g_env.world_num);
	iAffected = 0;
	if (!RECONNECT_TO_DATABASE01())
	{
		return FALSE;
	}

	if ((iAffected = mDB01.exec_query(mQUERY, CMySQL::CLEAR)) < 0)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL MyDB::DB_PROCESS_12(int up_check)
{
	int i = 0;
	int nSize = 0;
	int nSize2 = 0;
	int nCount = 0;
	int packetSize = 0;
	MYSQL_ROW row;
	MYSQL_RES* res = NULL;
	rank_kill_t tmp_rank_kill;
	rank_level_t tmp_rank_level;
	list<rank_kill_t>::iterator kill_it;
	list<rank_level_t>::iterator level_it;

	if ((!up_check) && (list_rank_level.size() > 0) && (list_rank_kill.size() > 0)) {
		return TRUE;
	}
	sprintf(mQUERY,
		"(SELECT '1' AS type, aName, aLevel, aTribe, aGeneralExperience "
		"FROM RankInfo  "
		"WHERE aWorldNumber = %d "
		"ORDER BY aLevel DESC, aGeneralExperience DESC "
		"LIMIT 100) "
		"UNION ALL "
		"(SELECT '2' AS type, aName, aKillOtherTribe, aTribe, aGeneralExperience "
		"FROM RankInfo  "
		"WHERE aWorldNumber = %d "
		"ORDER BY aKillOtherTribe DESC, aGeneralExperience DESC "
		"LIMIT 100)", g_env.world_num, g_env.world_num);

	if (!RECONNECT_TO_DATABASE01()) {
		return FALSE;
	}
	if (mDB01.exec_query(mQUERY) < 0) {
		return FALSE;
	}

	__LogMgr()->Log("%s execute query\n", __FUNCTION__);
	mGAME.m_rank_kill_size = 0;
	mGAME.m_rank_level_size = 0;
	list_rank_kill.clear();
	list_rank_level.clear();

	res = mDB01.get_res();
	if (res == NULL) {
		return false;
	}
	while ((row = mysql_fetch_row(res))) {
		if (*(row[0]) == '1') {
			_snprintf(tmp_rank_level.aName, MAX_AVATAR_NAME_LENGTH, "%s", row[1]);
			tmp_rank_level.level = atoi(row[2]);
			tmp_rank_level.tribe = atoi(row[3]);
			list_rank_level.push_back(tmp_rank_level);
			mGAME.m_rank_level_size += sizeof(tmp_rank_level);
		}
		else {
			_snprintf(tmp_rank_kill.aName, MAX_AVATAR_NAME_LENGTH, "%s", row[1]);
			tmp_rank_kill.kill = atoi(row[2]);
			tmp_rank_kill.tribe = atoi(row[3]);
			list_rank_kill.push_back(tmp_rank_kill);
			mGAME.m_rank_kill_size += sizeof(tmp_rank_kill);
		}
		nCount++;
	}
	__LogMgr()->Log("![%s] : nCount(%d)\n", __FUNCTION__, nCount);
	mDB01.clear_res();

	packetSize = mGAME.m_rank_level_size + mGAME.m_rank_kill_size;
	::memcpy(&mGAME.mBuffer[0], &packetSize, 4);
	::memcpy(&mGAME.mBuffer[4], &mGAME.m_rank_level_size, 4);
	::memcpy(&mGAME.mBuffer[8], &mGAME.m_rank_kill_size, 4);

	for (level_it = (mDB.list_rank_level).begin();
		level_it != (mDB.list_rank_level).end(); ++level_it) {
		nSize = i * sizeof(rank_level_t);
		::memcpy(&mGAME.mBuffer[12] + nSize, (const void*)&(*level_it), sizeof(rank_level_t));
		i++;
	}

	if (i != 0) {
		nSize += (12 + sizeof(rank_level_t));
	}
	else {
		nSize += 12;
	}

	i = 0;

	for (kill_it = (mDB.list_rank_kill).begin();
		kill_it != (mDB.list_rank_kill).end(); ++kill_it) {
		nSize2 = i * sizeof(rank_kill_t);
		//__LogMgr()->Log("%s %d\n", kill_it->aName, kill_it->kill);
		::memcpy(&mGAME.mBuffer[nSize] + nSize2, (const void*)&(*kill_it), sizeof(rank_kill_t));
		i++;
	}

	if (i != 0) {
		mGAME.mBufferSize = (nSize + nSize2 + sizeof(rank_kill_t));
	}
	else {
		mGAME.mBufferSize = (nSize + nSize2);
	}

	return TRUE;
}

BOOL MyDB::DB_PROCESS_13(const char* aName, rank_info_t* rank_info)
{
	return TRUE;
}
//DB_PROCESS_03
BOOL MyDB::DB_PROCESS_14(int tTribe)
{
	int i = 0;
	int nSize = 0;
	int nSize2 = 0;
	int nCount = 0;
	MYSQL_ROW row;
	MYSQL_RES* res = NULL;

	sprintf(mQUERY, "SELECT gName,GuldPoint From guildinfo and GuldPoint != 0 ORDER BY GuldPoint DESC LIMIT 3");

	if (!RECONNECT_TO_DATABASE02()) {
		return FALSE;
	}
	if (mDB02.exec_query(mQUERY) < 0) {
		return FALSE;
	}

	res = mDB02.get_res();
	if (res == NULL) {
		return false;
	}


	while ((row = mysql_fetch_row(res))) {
		_snprintf(mGAME.mWorldInfo.GuildRank1[nCount], MAX_AVATAR_NAME_LENGTH, "%s", row[0]);
		mGAME.mWorldInfo.GuildRankPoint[nCount] = atoi(row[1]);
		nCount++;
	}
	mDB02.clear_res();

	return TRUE;
}
//-------------------------------------------------------------------------------------------------
//DB_PROCESS_03
BOOL MyDB::DB_PROCESS_15(int tTribe)
{
	int i = 0;
	int nCount = 0;
	int index01;
	int index02;
	int index03;
	MYSQL_ROW row;
	MYSQL_RES* res = NULL;
	char RankInfo[4][121];
	char RankPoint[4][51];
	char tempString01[1000];

	ZeroMemory(&mGAME.mRankInfo, sizeof(RANK_INFO));

	for (index01 = 0; index01 < 4; index01++)
	{
		nCount = 0;
		sprintf(mQUERY, "SELECT aName,RankPoint From avatarinfo WHERE aTribe = %d and RankPoint !=0 ORDER BY RankPoint DESC LIMIT 10", index01);
		if (!RECONNECT_TO_DATABASE02()) {
			return FALSE;
		}
		if (mDB02.exec_query(mQUERY) < 0) {
			return FALSE;
		}
		res = mDB02.get_res();
		if (res == NULL) {
			return false;
		}
		while ((row = mysql_fetch_row(res))) {			
			_snprintf(mGAME.mRankInfo.NewRank[index01][nCount], MAX_AVATAR_NAME_LENGTH, "%s", row[0]);
			mGAME.mRankInfo.NewRankPoint[index01][nCount] = atoi(row[1]);
			nCount++;
		}
		mDB02.clear_res();
	}
	sprintf(mQUERY, "SELECT RankInfoDragon,RankPointDragon,RankInfoSnake,RankPointSnake,RankInfoTiger,RankPointTiger,RankInfoSky,RankPointSky From oldrankinfo");
	if (!RECONNECT_TO_DATABASE02()) {
		return FALSE;
	}
	if (mDB02.exec_query(mQUERY) < 0) {
		return FALSE;
	}
	res = mDB02.get_res();
	if (res == NULL) {
		return false;
	}
	while ((row = mysql_fetch_row(res))) {
		::strncpy(RankInfo[0], row[0], 121);//Ejder
		::strncpy(RankPoint[0], row[1], 51);//Ejder
		::strncpy(RankInfo[1], row[2], 121);//Yýlan
		::strncpy(RankPoint[1], row[3], 51);//Yýlan
		::strncpy(RankInfo[2], row[4], 121);//Pars
		::strncpy(RankPoint[2], row[5], 51);//Pars
		::strncpy(RankInfo[3], row[6], 121);//Gök
		::strncpy(RankPoint[3], row[7], 51);//Gök
		nCount++;
	}
	mDB02.clear_res();
	nCount = 0;
	for (index01 = 0; index01 < 4; index01++)
	{

		for (index02 = 0; index02 < MAX_FRIEND_NUM; index02++)
		{	
			CopyMemory(&tempString01[0], &RankPoint[index01][(index02 * 5 + 0)], 5);
			tempString01[5] = '\0';
			if (atoi(tempString01) == 0)
			{
				continue;
			}
			mGAME.mOldRankInfo.OldRankPoint[index01][index02] = atoi(tempString01);
			CopyMemory(&mGAME.mOldRankInfo.OldRank[index01][index02][0], &RankInfo[index01][(index02 * 12 + 0)], 12);
			for (index03 = 0; index03 < 12; index03++)
			{
				if (::IsDBCSLeadByte(mGAME.mOldRankInfo.OldRank[index01][index02][index03]) == TRUE) {
					if (index03 != 11) index03++;
					continue;
				}
				if (mGAME.mOldRankInfo.OldRank[index01][index02][index03] == '@')
				{
					break;
				}
			}
			mGAME.mOldRankInfo.OldRank[index01][index02][index03] = '\0';
		}
	}
	return TRUE;
}

BOOL MyDB::DB_PROCESS_16(int tTribe)
{
	int i = 0;
	int nCount = 0;
	MYSQL_ROW row;
	MYSQL_RES* res = NULL;
	int iAffected;
	char RankInfo[4][121];
	char RankPoint[4][51];
	int index01;
	char tempString01[1000];
	char mQUERY1[1000];
	char mQUERY2[1000];
	char mQUERY3[1000];
	char tempQuery[1000];


	CopyMemory(&mGAME.mOldRankInfo, &mGAME.mRankInfo, sizeof(RANK_INFO));
	ZeroMemory(&mGAME.mRankInfo, sizeof(RANK_INFO));



	for (index01 = 0; index01 < 4; index01++)
	{
		RankPoint[index01][0] = '\0';
		memset(RankInfo[index01], '@', (10 * (MAX_AVATAR_NAME_LENGTH - 1)));

		for (i = 0; i < 10; i++)
		{
			sprintf(tempString01, "%05d", (mGAME.mOldRankInfo.OldRankPoint[index01][i] % 100000));
			strcat(RankPoint[index01], tempString01);
			CopyMemory(&RankInfo[index01][(i * 12 + 0)], &mGAME.mOldRankInfo.OldRank[index01][i][0], strlen(mGAME.mOldRankInfo.OldRank[index01][i]));			
		}
		RankInfo[index01][120] = '\0';
	}


	//Þimdiki rank infoyu sýfýrlýyor
	sprintf(mQUERY1, "Update avatarinfo SET RankPoint = 0, RankPrize = 0 ");
	iAffected = 0;
	if (!RECONNECT_TO_DATABASE01())
	{
		return FALSE;
	}
	if ((iAffected = mDB01.exec_query(mQUERY1, CMySQL::CLEAR)) < 0)
	{
		return FALSE;
	}

	//Eski Rank infoyu kaydediyor
	strcpy(mQUERY3, "UPDATE oldrankinfo SET ");
	sprintf(tempQuery, "RankInfoDragon = '%s', ", RankInfo[0]);
	strcat(mQUERY3, tempQuery);
	sprintf(tempQuery, "RankPointDragon = '%s', ", RankPoint[0]);
	strcat(mQUERY3, tempQuery);
	sprintf(tempQuery, "RankInfoSnake = '%s', ", RankInfo[1]);
	strcat(mQUERY3, tempQuery);
	sprintf(tempQuery, "RankPointSnake = '%s', ", RankPoint[1]);
	strcat(mQUERY3, tempQuery);
	sprintf(tempQuery, "RankInfoTiger = '%s', ", RankInfo[2]);
	strcat(mQUERY3, tempQuery);
	sprintf(tempQuery, "RankPointTiger = '%s', ", RankPoint[2]);
	strcat(mQUERY3, tempQuery);
	sprintf(tempQuery, "RankInfoSky = '%s', ", RankInfo[3]);
	strcat(mQUERY3, tempQuery);
	sprintf(tempQuery, "RankPointSky = '%s'; ", RankPoint[3]);
	strcat(mQUERY3, tempQuery);

	iAffected = 0;
	if (!RECONNECT_TO_DATABASE01())
	{
		return FALSE;
	}
	if ((iAffected = mDB01.exec_query(mQUERY3, CMySQL::CLEAR)) < 0)
	{
		return FALSE;
	}
	return TRUE;
}

