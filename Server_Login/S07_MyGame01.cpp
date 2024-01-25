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
	mTickCount = 0;
	mMaxPlayerNum = 0;
	mAddPlayerNum = 0;
	mGagePlayerNum = 0;
	mPresentPlayerNum = -1;
	if (!mDB.DB_PROCESS_01())
	{
		printf("error DB_PROCESS_01");
		return FALSE;
	}

	if (!LoadBlockIPInfo())
	{
		printf("error LoadBlockIPInfo");
		return FALSE;
	}

	if (!mGMEnableLoginIPList.LoadIPInfo("GM_ENABLE_LOGIN_IP_INFO.TXT"))
	{
		printf("error GM_ENABLE_LOGIN_IP_INFO");
		return FALSE;
	}

	if (!mZONEMAININFO.Init())
	{
		printf("error mZONEMAININFO");
		return FALSE;
	}
	return TRUE;
}
//FREE
void MyGame::Free(void)
{
	mZONEMAININFO.Free();
}
static char *ALLOWED_CHARACTERS[] = {
	"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "r", "s", "t", "u", "w", "y", "x", "z", "q", "v",
	"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "R", "S", "T", "U", "W", "Y", "X", "Z", "Q", "V",
	"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"
};

static int ALLOWED_CHARACTERS_SIZE = sizeof(ALLOWED_CHARACTERS) / sizeof(*ALLOWED_CHARACTERS);
//CHECK_NAME_STRING
BOOL MyGame::CheckNameString(char *tString)
{
	int index01;
	WORD tUnicode;

	int tStringLen = strlen(tString);

	if (tStringLen < 4) {
		return FALSE;
	}

	for (index01 = 0; index01 < tStringLen; index01++)
	{
		char character = tString[index01];

		bool whitelisted = FALSE;

		for (int aStringIndex = 0; aStringIndex < ALLOWED_CHARACTERS_SIZE; aStringIndex++) {
			char allowed = *ALLOWED_CHARACTERS[aStringIndex];

			if (character == allowed) {
				whitelisted = TRUE;
				break;
			}
		}

		if (!whitelisted) {
			cout << "Not allowed character: " << character << endl;
			return FALSE;
		}

	}
	return TRUE;
}
//RETURN_NOW_DATE
int MyGame::ReturnNowDate(void)
{
	time_t tCountSeconds;
	struct tm *tPresentTime;
	char tempString01[1000];
	char tempString02[1000];

	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return 0;
	}
	strcpy(tempString01, "");
	sprintf(tempString02, "%d", tPresentTime->tm_year + 1900);
	strcat(tempString01, tempString02);
	if (tPresentTime->tm_mon < 9)
	{
		tempString02[0] = '0';
		tempString02[1] = tPresentTime->tm_mon + 1 + '0';
		tempString02[2] = '\0';
	}
	else
	{
		sprintf(tempString02, "%d", tPresentTime->tm_mon + 1);
	}
	strcat(tempString01, tempString02);
	if (tPresentTime->tm_mday < 10)
	{
		tempString02[0] = '0';
		tempString02[1] = tPresentTime->tm_mday + '0';
		tempString02[2] = '\0';
	}
	else
	{
		sprintf(tempString02, "%d", tPresentTime->tm_mday);
	}
	strcat(tempString01, tempString02);
	return atoi(tempString01);
}
//RETURN_ADD_DATE
int MyGame::ReturnAddDate(int tPostDateValue, int tAddDayValue)
{
	if (tAddDayValue < 0)
	{
		return -1;
	}

	time_t tCountSeconds;
	struct tm* tPresentTime;
	char tempString01[1000];
	char tempString02[1000];
	int tPresentDateValue;

	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return -1;
	}

	_snprintf(tempString01, 1000, "%4.4d%2.2d%2.2d"
		, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1
		, tPresentTime->tm_mday);

	tPresentDateValue = atoi(tempString01);
	if (tPostDateValue > tPresentDateValue)
	{
		//tAddDayValue += ReturnSubDate( tPostDateValue, tCountSeconds );
		tAddDayValue += ReturnSubDate(tPostDateValue, tPresentDateValue);
	}
	time(&tCountSeconds);
	tCountSeconds += (tAddDayValue * 24 * 3600);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return -1;
	}

	_snprintf(tempString01, 1000, "%4.4d%2.2d%2.2d"
		, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1
		, tPresentTime->tm_mday);

	return atoi(tempString01);
}
//RETURN_SUB_DATE
int MyGame::ReturnSubDate(int tPostDateValue, int tSubDayValue)
{
	if (tPostDateValue <= tSubDayValue)
	{
		return 0;
	}

#if 0
	struct tm time_str;
	time_t uPostDataValue;
	char tmpBuffer[8];
	char tempString01[1000];

	::snprintf(tempString01, 1000, "%s", tPostDateValue);
	memcpy(&tmpBuffer, &tempString01[0], 4);
	tmpBuffer[4] = '\0';
	time_str.tm_year = atoi(tmpBuffer) - 1900;
	memcpy(&tmpBuffer, &tempString01[4], 2);
	tmpBuffer[2] = '\0';
	time_str.tm_mon = atoi(tmpBuffer) - 1;
	tmpBuffer[2] = '\0';
	memcpy(&tmpBuffer, &tempString01[6], 2);
	time_str.tm_mday = atoi(tmpBuffer);
	time_str.tm_hour = 0;
	time_str.tm_min = 0;
	time_str.tm_sec = 0;

	if ((uPostDataValue = mktime(&time_str)) == -1) {
		return 0;
	}

	return ((uPostDataValue - tSubDayValue) / (24 * 3600)) + 1;
#endif
#if 1
	int index01;
	char tempString01[1000];
	char tempString02[1000];
	int tMonthDay[12];
	int tYear[2];
	int tMonth[2];
	int tDay[2];

	tMonthDay[0] = 31;
	tMonthDay[1] = 29;
	tMonthDay[2] = 31;
	tMonthDay[3] = 30;
	tMonthDay[4] = 31;
	tMonthDay[5] = 30;
	tMonthDay[6] = 31;
	tMonthDay[7] = 31;
	tMonthDay[8] = 30;
	tMonthDay[9] = 31;
	tMonthDay[10] = 30;
	tMonthDay[11] = 31;
#ifdef __WIN32__
	itoa(tPostDateValue, &tempString01[0], 10);
#else
	sprintf(&tempString01[0], "%d", tPostDateValue);
#endif
	CopyMemory(&tempString02[0], &tempString01[0], 4);
	tempString02[4] = '\0';
	tYear[0] = atoi(tempString02);
	if ((tYear[0] < 1) || (tYear[0] > 9000))
	{
		return 0;
	}
	CopyMemory(&tempString02[0], &tempString01[4], 2);
	tempString02[2] = '\0';
	tMonth[0] = atoi(tempString02);
	if ((tMonth[0] < 1) || (tMonth[0] > 12))
	{
		return 0;
	}
	CopyMemory(&tempString02[0], &tempString01[6], 2);
	tempString02[2] = '\0';
	tDay[0] = atoi(tempString02);
	if ((tDay[0] < 1) || (tDay[0] > 31))
	{
		return 0;
	}
	tDay[0] += (tYear[0] * 365);
	for (index01 = 0; index01 < (tMonth[0] - 1); index01++)
	{
		tDay[0] += tMonthDay[index01];
	}
#ifdef __WIN32__
	itoa(tSubDayValue, &tempString01[0], 10);
#else
	sprintf(&tempString01[0], "%d", tSubDayValue);
#endif
	CopyMemory(&tempString02[0], &tempString01[0], 4);
	tempString02[4] = '\0';
	tYear[1] = atoi(tempString02);
	if ((tYear[1] < 1) || (tYear[1] > 9000))
	{
		return 0;
	}
	CopyMemory(&tempString02[0], &tempString01[4], 2);
	tempString02[2] = '\0';
	tMonth[1] = atoi(tempString02);
	if ((tMonth[1] < 1) || (tMonth[1] > 12))
	{
		return 0;
	}
	CopyMemory(&tempString02[0], &tempString01[6], 2);
	tempString02[2] = '\0';
	tDay[1] = atoi(tempString02);
	if ((tDay[1] < 1) || (tDay[1] > 31))
	{
		return 0;
	}
	tDay[1] += (tYear[1] * 365);
	for (index01 = 0; index01 < (tMonth[1] - 1); index01++)
	{
		tDay[1] += tMonthDay[index01];
	}
	return (tDay[0] - tDay[1]);
#endif
}
//SAFE_AVATAR_INFO_DATA
void MyGame::SafeAvatarInfoData(AVATAR_INFO *tAvatarInfo)
{
	int index01;

	tAvatarInfo->aName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
	for (index01 = 0; index01 < MAX_FRIEND_NUM; index01++)
	{
		tAvatarInfo->aFriend[index01][(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
	}
	tAvatarInfo->aTeacher[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
	tAvatarInfo->aStudent[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
	tAvatarInfo->aGuildName[(MAX_GUILD_NAME_LENGTH - 1)] = '\0';
	tAvatarInfo->aCallName[(MAX_CALL_NAME_LENGTH - 1)] = '\0';
	for (index01 = 0; index01 < 5; index01++)
	{
		tAvatarInfo->aPartyName[index01][(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
	}
}
//RETURN_TRIBE_ROLE
int MyGame::ReturnTribeRole(TRIBE_INFO *tTribeInfo, char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tTribe)
{
	int index01;

	if (strcmp(tAvatarName, tTribeInfo->mTribeMaster[tTribe]) == 0)
	{
		return 1;
	}
	for (index01 = 0; index01 < MAX_TRIBE_SUBMASTER_NUM; index01++)
	{
		if (strcmp(tAvatarName, tTribeInfo->mTribeSubMaster[tTribe][index01]) == 0)
		{
			return 2;
		}
	}

	for (index01 = 0; index01 < MAX_TRIBE_VOTE_AVATAR_NUM; ++index01) {
		if (0 == strcmp(tAvatarName, tTribeInfo->mTribeVoteName[tTribe][index01])) {
			return 3;
		}
	}

	return 0;
}
//LOAD_BLOCK_IP_INFO
BOOL MyGame::LoadBlockIPInfo(void)
{
	int index01;
	int index02;
	int index03;
	char tempString01[1000];
	char tempString02[1000];
	FILE* fp = NULL;

	fp = ::fopen("BlockIPInfo.TXT", "r");
	if (fp == NULL) {
		__LogMgr()->Log("![%s] : fopen failed (%s) - BlockIPInfo.TXT\n",
			__FUNCTION__, ::strerror(errno));
		return FALSE;
	}
	if (!GetOneValueFromFile(fp, 1000, &tempString01[0]))
	{
		::fclose(fp);
		return FALSE;
	}
	mTotalBlockIPInfo = atoi(tempString01);
	if ((mTotalBlockIPInfo < 0) || (mTotalBlockIPInfo > MAX_BLOCK_IP_INFO_NUM))
	{
		::fclose(fp);
		return FALSE;
	}
	for (index01 = 0; index01 < mTotalBlockIPInfo; index01++)
	{
		if (!GetOneValueFromFile(fp, 1000, &tempString01[0]))
		{
			::fclose(fp);
			return FALSE;
		}
		index02 = 0;
		index03 = 0;
		for (; index02 < (int)strlen(tempString01); index02++)
		{
			tempString02[index03] = tempString01[index02];
			index03++;
			if (tempString01[index02] == '.')
			{
				tempString02[index03] = '\0';
				break;
			}
		}
		if (index02 == (int)strlen(tempString01))
		{
			::fclose(fp);
			return FALSE;
		}
		mBlockIPInfo[index01][0][0] = atoi(tempString02);
		index02++;
		index03 = 0;
		for (; index02 < (int)strlen(tempString01); index02++)
		{
			tempString02[index03] = tempString01[index02];
			index03++;
			if (tempString01[index02] == '.')
			{
				tempString02[index03] = '\0';
				break;
			}
		}
		if (index02 == (int)strlen(tempString01))
		{
			::fclose(fp);
			return FALSE;
		}
		mBlockIPInfo[index01][0][1] = atoi(tempString02);
		index02++;
		index03 = 0;
		for (; index02 < (int)strlen(tempString01); index02++)
		{
			tempString02[index03] = tempString01[index02];
			index03++;
			if (tempString01[index02] == '.')
			{
				tempString02[index03] = '\0';
				break;
			}
		}
		if (index02 == (int)strlen(tempString01))
		{
			::fclose(fp);
			return FALSE;
		}
		mBlockIPInfo[index01][0][2] = atoi(tempString02);
		index02++;
		index03 = 0;
		for (; index02 < (int)strlen(tempString01); index02++)
		{
			tempString02[index03] = tempString01[index02];
			index03++;
		}
		tempString02[index03] = '\0';
		mBlockIPInfo[index01][0][3] = atoi(tempString02);
		if (!GetOneValueFromFile(fp, 1000, &tempString01[0]))
		{
			::fclose(fp);
			return FALSE;
		}
		index02 = 0;
		index03 = 0;
		for (; index02 < (int)strlen(tempString01); index02++)
		{
			tempString02[index03] = tempString01[index02];
			index03++;
			if (tempString01[index02] == '.')
			{
				tempString02[index03] = '\0';
				break;
			}
		}
		if (index02 == (int)strlen(tempString01))
		{
			::fclose(fp);
			return FALSE;
		}
		mBlockIPInfo[index01][1][0] = atoi(tempString02);
		index02++;
		index03 = 0;
		for (; index02 < (int)strlen(tempString01); index02++)
		{
			tempString02[index03] = tempString01[index02];
			index03++;
			if (tempString01[index02] == '.')
			{
				tempString02[index03] = '\0';
				break;
			}
		}
		if (index02 == (int)strlen(tempString01))
		{
			::fclose(fp);
			return FALSE;
		}
		mBlockIPInfo[index01][1][1] = atoi(tempString02);
		index02++;
		index03 = 0;
		for (; index02 < (int)strlen(tempString01); index02++)
		{
			tempString02[index03] = tempString01[index02];
			index03++;
			if (tempString01[index02] == '.')
			{
				tempString02[index03] = '\0';
				break;
			}
		}
		if (index02 == (int)strlen(tempString01))
		{
			::fclose(fp);
			return FALSE;
		}
		mBlockIPInfo[index01][1][2] = atoi(tempString02);
		index02++;
		index03 = 0;
		for (; index02 < (int)strlen(tempString01); index02++)
		{
			tempString02[index03] = tempString01[index02];
			index03++;
		}
		tempString02[index03] = '\0';
		mBlockIPInfo[index01][1][3] = atoi(tempString02);
	}
	if (::fclose(fp) != 0)
	{
		return FALSE;
	}

	return TRUE;
}
//GET_ONE_VALUE_FROM_FILE
BOOL MyGame::GetOneValueFromFile(FILE* fp, int tBufferSize, char *tBuffer)
{
	int index01;
	DWORD nReadByte;
	BOOL tCheckSaveState;
	char tData;

	index01 = 0;
	tCheckSaveState = FALSE;
	while (TRUE)
	{
		if (fread(&tData, 1, 1, fp) != 1)
		{
			return FALSE;
		}
		if (!tCheckSaveState)
		{
			if (tData == '[')
			{
				tCheckSaveState = TRUE;
			}
		}
		else
		{
			if (tData == ']')
			{
				tBuffer[index01] = '\0';
				break;
			}
			else
			{
				if (index01 < (tBufferSize - 1))
				{
					tBuffer[index01] = tData;
					index01++;
				}
				else
				{
					return FALSE;
				}
			}
		}
	}
	return TRUE;
}
//COMPARE_BLOCK_IP_INFO
BOOL MyGame::CompareBlockIPInfo(int tIP1, int tIP2, int tIP3, int tIP4)
{
	int index01;
	char tempString01[1000];
	long long tIP;
	long long tBlockIP01;
	long long tBlockIP02;

	sprintf(tempString01, "%03d%03d%03d%03d", tIP1, tIP2, tIP3, tIP4);
	tIP = ::atol(tempString01);
	for (index01 = 0; index01 < mTotalBlockIPInfo; index01++)
	{
		sprintf(tempString01, "%03d%03d%03d%03d", mBlockIPInfo[index01][0][0], mBlockIPInfo[index01][0][1], mBlockIPInfo[index01][0][2], mBlockIPInfo[index01][0][3]);
		tBlockIP01 = ::atol(tempString01);
		sprintf(tempString01, "%03d%03d%03d%03d", mBlockIPInfo[index01][1][0], mBlockIPInfo[index01][1][1], mBlockIPInfo[index01][1][2], mBlockIPInfo[index01][1][3]);
		tBlockIP02 = ::atol(tempString01);
		if ((tBlockIP01 <= tIP) && (tBlockIP02 >= tIP))
		{
			return TRUE;
		}
	}
	return FALSE;
}
//LOAD_GIFT_INFO
BOOL MyGame::LoadGiftInfo(void)
{
	FILE* fp = NULL;
	DWORD nReadByte;
	int tDataNum;

	fp = ::fopen("/user/service/bin/DATA/GIFT.DAT", "r");
	if (fp == NULL)
	{
		return FALSE;
	}
	if (::fread(&tDataNum, 1, sizeof(int), fp) != 4)
	{
		::fclose(fp);
		return FALSE;
	}
	if (tDataNum != MAX_GIFT_SORT_NUM)
	{
		::fclose(fp);
		return FALSE;
	}
	int iTotalBytes = tDataNum * sizeof(GIFT_INFO);
	if (::fread(mGiftInfo, 1, iTotalBytes, fp) != iTotalBytes)
	{
		::fclose(fp);
		return FALSE;
	}
	if (::fclose(fp) != 0)
	{
		return FALSE;
	}

	return TRUE;
}
//CHECK_DELETE_ITEM
BOOL MyGame::CheckDeleteItem(int iIndex)
{
	switch (iIndex)
	{
	case 1079:
	case 1080:
	case 1081:
	case 1082:
	case 1083:
	case 1084:
	case 1085:
	case 1086:
	case 1087:
		return TRUE;
	}
	return FALSE;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_ZONEMAININFO
//-------------------------------------------------------------------------------------------------
//INSTANCE
ZONEMAININFO mZONEMAININFO;
//CREATE
ZONEMAININFO::ZONEMAININFO(void)
{
}
//INIT
BOOL ZONEMAININFO::Init(void)
{
	int index01;

	for (index01 = 0; index01 < MAX_ZONE_NUMBER_NUM; index01++)
	{
		mZoneLevelInfo[index01][0] = 0;
		mZoneLevelInfo[index01][1] = 0;
		mZoneTribeInfo[index01][0] = -1;
		mZoneTribeInfo[index01][1] = 0;
		switch ((index01 + 1))
		{

			//-------------------------------------------------------------------------------------------------
			// 2010.01.15 : KimSungSoo
			// musin		
		case   1: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 1; break;
		case   2: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 1; break;
		case   3: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 1; break;
		case   4: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 1; break;
		case   6: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 1; break;
		case   7: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 1; break;
		case   8: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 1; break;
		case   9: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 1; break;
		case  11: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 1; break;
		case  12: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 1; break;
		case  13: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 1; break;
		case  14: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 1; break;
		case  16: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 0; break;
		case  17: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 0; break;
		case  18: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 0; break;
		case  19: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 149; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case  20: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 149; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case  21: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 149; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case  22: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 0; break;
		case  23: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 0; break;
		case  24: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 0; break;
		case  25: mZoneLevelInfo[index01][0] = 150; mZoneLevelInfo[index01][1] = 153; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case  26: mZoneLevelInfo[index01][0] = 150; mZoneLevelInfo[index01][1] = 153; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case  27: mZoneLevelInfo[index01][0] = 150; mZoneLevelInfo[index01][1] = 153; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case  28: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 0; break;
		case  29: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 0; break;
		case  30: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 0; break;
		case  31: mZoneLevelInfo[index01][0] = 154; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case  32: mZoneLevelInfo[index01][0] = 154; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case  33: mZoneLevelInfo[index01][0] = 154; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case  34: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 149; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case  35: mZoneLevelInfo[index01][0] = 150; mZoneLevelInfo[index01][1] = 153; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case  36: mZoneLevelInfo[index01][0] = 154; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case  37: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 0; break;
		case  38: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case  39: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 99; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 0; break;
		case  40: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 0; break;
		case  41: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 0; break;
		case  42: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 0; break;
		case  43: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 0; break;
		case  44: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 0; break;
		case  45: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 0; break;
		case  46: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 0; break;
		case  47: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 0; break;
		case  48: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 0; break;
		case  49: mZoneLevelInfo[index01][0] = 10; mZoneLevelInfo[index01][1] = 19; mZoneTribeInfo[index01][0] = 11; mZoneTribeInfo[index01][1] = 1; break;
		case  51: mZoneLevelInfo[index01][0] = 20; mZoneLevelInfo[index01][1] = 29; mZoneTribeInfo[index01][0] = 12; mZoneTribeInfo[index01][1] = 1; break;
		case  53: mZoneLevelInfo[index01][0] = 30; mZoneLevelInfo[index01][1] = 39; mZoneTribeInfo[index01][0] = 13; mZoneTribeInfo[index01][1] = 1; break;
		case  55: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case  56: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 0; break;
		case  57: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 0; break;
		case  58: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 0; break;
		case  59: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 0; break;
		case  60: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 0; break;
		case  61: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 0; break;
		case  62: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 0; break;
		case  63: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 0; break;
		case  64: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 0; break;
		case  65: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 0; break;
		case  66: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 0; break;
		case  67: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 0; break;
		case  68: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 0; break;
		case  69: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 0; break;
		case  70: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 0; break;
		case  71: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 0; break;
		case  72: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 0; break;
		case  73: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 0; break;
		case  74: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 0; break;
		case  75: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case  76: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case  77: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case  78: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case  79: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case  80: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case  81: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case  82: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case  83: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case  84: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 0; break;
		case  85: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 149; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case  86: mZoneLevelInfo[index01][0] = 150; mZoneLevelInfo[index01][1] = 153; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case  87: mZoneLevelInfo[index01][0] = 154; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case  88: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 0; break;
		case  89: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case  90: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case  91: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case  92: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case  93: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case  94: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case  95: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case  96: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case  97: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case  98: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 101: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 102: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 103: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 104: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 105: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 106: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 107: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 108: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 109: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 110: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 111: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 112: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 113: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 114: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 115: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 116: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 117: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 120: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 149; mZoneTribeInfo[index01][0] = 11; mZoneTribeInfo[index01][1] = 1; break;
		case 121: mZoneLevelInfo[index01][0] = 150; mZoneLevelInfo[index01][1] = 153; mZoneTribeInfo[index01][0] = 11; mZoneTribeInfo[index01][1] = 1; break;
		case 122: mZoneLevelInfo[index01][0] = 154; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 11; mZoneTribeInfo[index01][1] = 1; break;
		case 124: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 0; break;
		case 125: mZoneLevelInfo[index01][0] = 145; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case 126: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 127: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 128: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 129: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 130: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 131: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 132: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 133: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 134: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 135: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 136: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 137: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 140: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 3; mZoneTribeInfo[index01][1] = 1; break;
		case 141: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 3; mZoneTribeInfo[index01][1] = 1; break;
		case 142: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 3; mZoneTribeInfo[index01][1] = 1; break;
		case 143: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 3; mZoneTribeInfo[index01][1] = 1; break;
		case 144: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 112; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 0; break;
		case 145: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 0; break;
		case 146: mZoneLevelInfo[index01][0] = 40; mZoneLevelInfo[index01][1] = 49; mZoneTribeInfo[index01][0] = 11; mZoneTribeInfo[index01][1] = 1; break;
		case 147: mZoneLevelInfo[index01][0] = 50; mZoneLevelInfo[index01][1] = 59; mZoneTribeInfo[index01][0] = 12; mZoneTribeInfo[index01][1] = 1; break;
		case 148: mZoneLevelInfo[index01][0] = 60; mZoneLevelInfo[index01][1] = 69; mZoneTribeInfo[index01][0] = 13; mZoneTribeInfo[index01][1] = 1; break;
		case 149: mZoneLevelInfo[index01][0] = 70; mZoneLevelInfo[index01][1] = 79; mZoneTribeInfo[index01][0] = 11; mZoneTribeInfo[index01][1] = 1; break;
		case 150: mZoneLevelInfo[index01][0] = 80; mZoneLevelInfo[index01][1] = 89; mZoneTribeInfo[index01][0] = 12; mZoneTribeInfo[index01][1] = 1; break;
		case 151: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 99; mZoneTribeInfo[index01][0] = 13; mZoneTribeInfo[index01][1] = 1; break;
		case 152: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 105; mZoneTribeInfo[index01][0] = 13; mZoneTribeInfo[index01][1] = 1; break;
		case 153: mZoneLevelInfo[index01][0] = 106; mZoneLevelInfo[index01][1] = 112; mZoneTribeInfo[index01][0] = 13; mZoneTribeInfo[index01][1] = 1; break;
		case 154: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 115; mZoneTribeInfo[index01][0] = 11; mZoneTribeInfo[index01][1] = 1; break;
		case 155: mZoneLevelInfo[index01][0] = 116; mZoneLevelInfo[index01][1] = 118; mZoneTribeInfo[index01][0] = 12; mZoneTribeInfo[index01][1] = 1; break;
		case 156: mZoneLevelInfo[index01][0] = 119; mZoneLevelInfo[index01][1] = 121; mZoneTribeInfo[index01][0] = 13; mZoneTribeInfo[index01][1] = 1; break;
		case 157: mZoneLevelInfo[index01][0] = 122; mZoneLevelInfo[index01][1] = 124; mZoneTribeInfo[index01][0] = 11; mZoneTribeInfo[index01][1] = 1; break;
		case 158: mZoneLevelInfo[index01][0] = 125; mZoneLevelInfo[index01][1] = 127; mZoneTribeInfo[index01][0] = 12; mZoneTribeInfo[index01][1] = 1; break;
		case 159: mZoneLevelInfo[index01][0] = 128; mZoneLevelInfo[index01][1] = 130; mZoneTribeInfo[index01][0] = 13; mZoneTribeInfo[index01][1] = 1; break;
		case 160: mZoneLevelInfo[index01][0] = 131; mZoneLevelInfo[index01][1] = 133; mZoneTribeInfo[index01][0] = 11; mZoneTribeInfo[index01][1] = 1; break;
		case 161: mZoneLevelInfo[index01][0] = 134; mZoneLevelInfo[index01][1] = 136; mZoneTribeInfo[index01][0] = 12; mZoneTribeInfo[index01][1] = 1; break;
		case 162: mZoneLevelInfo[index01][0] = 137; mZoneLevelInfo[index01][1] = 139; mZoneTribeInfo[index01][0] = 13; mZoneTribeInfo[index01][1] = 1; break;
		case 163: mZoneLevelInfo[index01][0] = 140; mZoneLevelInfo[index01][1] = 142; mZoneTribeInfo[index01][0] = 13; mZoneTribeInfo[index01][1] = 1; break;
		case 164: mZoneLevelInfo[index01][0] = 143; mZoneLevelInfo[index01][1] = 145; mZoneTribeInfo[index01][0] = 13; mZoneTribeInfo[index01][1] = 1; break;
		case 167: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 168: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 169: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 170: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case 171: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 172: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 173: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 174: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 175: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 112; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 176: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 112; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 177: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 112; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 178: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 122; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 179: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 122; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 180: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 122; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 181: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 122; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 182: mZoneLevelInfo[index01][0] = 123; mZoneLevelInfo[index01][1] = 132; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 183: mZoneLevelInfo[index01][0] = 123; mZoneLevelInfo[index01][1] = 132; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 184: mZoneLevelInfo[index01][0] = 123; mZoneLevelInfo[index01][1] = 132; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 185: mZoneLevelInfo[index01][0] = 123; mZoneLevelInfo[index01][1] = 132; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 186: mZoneLevelInfo[index01][0] = 133; mZoneLevelInfo[index01][1] = 142; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 187: mZoneLevelInfo[index01][0] = 133; mZoneLevelInfo[index01][1] = 142; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 188: mZoneLevelInfo[index01][0] = 133; mZoneLevelInfo[index01][1] = 142; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 189: mZoneLevelInfo[index01][0] = 133; mZoneLevelInfo[index01][1] = 142; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 190: mZoneLevelInfo[index01][0] = 143; mZoneLevelInfo[index01][1] = 145; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 191: mZoneLevelInfo[index01][0] = 143; mZoneLevelInfo[index01][1] = 145; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 192: mZoneLevelInfo[index01][0] = 143; mZoneLevelInfo[index01][1] = 145; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 193: mZoneLevelInfo[index01][0] = 143; mZoneLevelInfo[index01][1] = 145; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 194: mZoneLevelInfo[index01][0] = 157; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 14; mZoneTribeInfo[index01][1] = 2; break;
		case 195: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 112; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case 196: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 145; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break; // modified to mZoneLevelInfo[index01][1] = 122
		case 197: mZoneLevelInfo[index01][0] = 123; mZoneLevelInfo[index01][1] = 132; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case 198: mZoneLevelInfo[index01][0] = 133; mZoneLevelInfo[index01][1] = 142; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case 199: mZoneLevelInfo[index01][0] = 143; mZoneLevelInfo[index01][1] = 145; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case 200: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case 201: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case 202: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 203: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 204: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 205: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 206: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 207: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 208: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 209: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 210: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 211: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 212: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 213: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 214: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 215: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 216: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 217: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 218: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 219: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 220: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 221: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 222: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 223: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 224: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 225: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 226: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 227: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 228: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 229: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 230: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 231: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 232: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 233: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 235: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 236: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 237: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 238: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 239: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 240: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 241: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 242: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 243: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 244: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 245: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 246: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 247: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 248: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 249: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 250: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 251: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 252: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 253: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 254: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 255: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 256: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 257: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 258: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 259: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 260: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 261: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 262: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 263: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 264: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 265: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 266: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 267: mZoneLevelInfo[index01][0] = 70; mZoneLevelInfo[index01][1] = 112; mZoneTribeInfo[index01][0] = 15; mZoneTribeInfo[index01][1] = 1; break;
		case 268: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 145; mZoneTribeInfo[index01][0] = 15; mZoneTribeInfo[index01][1] = 1; break;
		case 269: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 15; mZoneTribeInfo[index01][1] = 1; break;
		case 296: mZoneLevelInfo[index01][0] = 157; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 11; mZoneTribeInfo[index01][1] = 1; break;
		case 292: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 293: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 294: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;

			//-------------------------------------------------------------------------------------------------
		}
	}
	return TRUE;
}
//FREE
void ZONEMAININFO::Free(void)
{
}
//RETURN_MIN_ZONE_LEVEL_INFO
int ZONEMAININFO::ReturnMinZoneLevelInfo(int tZoneNumber)
{
	
	if ((tZoneNumber < MIN_VALID_ZONE_NUMBER) || (tZoneNumber > MAX_VALID_ZONE_NUMBER))
	{
		
		return 0;
	}
	return mZoneLevelInfo[(tZoneNumber - 1)][0];
}
//RETURN_MAX_ZONE_LEVEL_INFO
int ZONEMAININFO::ReturnMaxZoneLevelInfo(int tZoneNumber)
{

	if ((tZoneNumber < MIN_VALID_ZONE_NUMBER) || (tZoneNumber > MAX_VALID_ZONE_NUMBER))
	{
	
		return 0;
	}
	return mZoneLevelInfo[(tZoneNumber - 1)][1];
}
//RETURN_ZONE_TRIBE_INFO_1
int ZONEMAININFO::ReturnZoneTribeInfo1(int tZoneNumber)
{
	if ((tZoneNumber < MIN_VALID_ZONE_NUMBER) || (tZoneNumber > MAX_VALID_ZONE_NUMBER))
	{
		return -1;
	}
	return mZoneTribeInfo[(tZoneNumber - 1)][0];
}
//RETURN_ZONE_TRIBE_INFO_2
int ZONEMAININFO::ReturnZoneTribeInfo2(int tZoneNumber)
{
	if ((tZoneNumber < MIN_VALID_ZONE_NUMBER) || (tZoneNumber > MAX_VALID_ZONE_NUMBER))
	{
		return -1;
	}
	return mZoneTribeInfo[(tZoneNumber - 1)][1];
}
// # GM Enable Login IP # {
//-------------------------------------------------------------------------------------------------
//CLASS_OF_CIPINFOLIST
//-------------------------------------------------------------------------------------------------
CIPInfoList::CIPInfoList()
{
}
CIPInfoList::~CIPInfoList()
{
}

// [123.123.123.0][123.123.123.10]
// --> 123.123.123.0 ~ 123.123.123.10
BOOL CIPInfoList::LoadIPInfo(const char* ipInfoListPath)
{
	int index01;
	int index02;
	int index03;
	char tempString01[1000];
	char tempString02[1000];
	FILE* fp = NULL;

	fp = ::fopen(ipInfoListPath, "r");
	if (fp == NULL) {
		__LogMgr()->Log("![%s] : fopen failed (%s) - %s\n",
			__FUNCTION__, ::strerror(errno), ipInfoListPath);
		return FALSE;
	}
	if (!GetOneValueFromFile(fp, 1000, &tempString01[0]))
	{
		::fclose(fp);
		return FALSE;
	}
	mTotalIPInfoNum = atoi(tempString01);
	if ((mTotalIPInfoNum < 0) || (mTotalIPInfoNum > MAX_BLOCK_IP_INFO_NUM))
	{
		::fclose(fp);
		return FALSE;
	}
	for (index01 = 0; index01 < mTotalIPInfoNum; index01++)
	{
		if (!GetOneValueFromFile(fp, 1000, &tempString01[0]))
		{
			::fclose(fp);
			return FALSE;
		}
		index02 = 0;
		index03 = 0;
		for (; index02 < (int)strlen(tempString01); index02++)
		{
			tempString02[index03] = tempString01[index02];
			index03++;
			if (tempString01[index02] == '.')
			{
				tempString02[index03] = '\0';
				break;
			}
		}
		if (index02 == (int)strlen(tempString01))
		{
			::fclose(fp);
			return FALSE;
		}
		mIPInfoList[index01][0][0] = atoi(tempString02);
		index02++;
		index03 = 0;
		for (; index02 < (int)strlen(tempString01); index02++)
		{
			tempString02[index03] = tempString01[index02];
			index03++;
			if (tempString01[index02] == '.')
			{
				tempString02[index03] = '\0';
				break;
			}
		}
		if (index02 == (int)strlen(tempString01))
		{
			::fclose(fp);
			return FALSE;
		}
		mIPInfoList[index01][0][1] = atoi(tempString02);
		index02++;
		index03 = 0;
		for (; index02 < (int)strlen(tempString01); index02++)
		{
			tempString02[index03] = tempString01[index02];
			index03++;
			if (tempString01[index02] == '.')
			{
				tempString02[index03] = '\0';
				break;
			}
		}
		if (index02 == (int)strlen(tempString01))
		{
			::fclose(fp);
			return FALSE;
		}
		mIPInfoList[index01][0][2] = atoi(tempString02);
		index02++;
		index03 = 0;
		for (; index02 < (int)strlen(tempString01); index02++)
		{
			tempString02[index03] = tempString01[index02];
			index03++;
		}
		tempString02[index03] = '\0';
		mIPInfoList[index01][0][3] = atoi(tempString02);
		if (!GetOneValueFromFile(fp, 1000, &tempString01[0]))
		{
			::fclose(fp);
			return FALSE;
		}
		index02 = 0;
		index03 = 0;
		for (; index02 < (int)strlen(tempString01); index02++)
		{
			tempString02[index03] = tempString01[index02];
			index03++;
			if (tempString01[index02] == '.')
			{
				tempString02[index03] = '\0';
				break;
			}
		}
		if (index02 == (int)strlen(tempString01))
		{
			::fclose(fp);
			return FALSE;
		}
		mIPInfoList[index01][1][0] = atoi(tempString02);
		index02++;
		index03 = 0;
		for (; index02 < (int)strlen(tempString01); index02++)
		{
			tempString02[index03] = tempString01[index02];
			index03++;
			if (tempString01[index02] == '.')
			{
				tempString02[index03] = '\0';
				break;
			}
		}
		if (index02 == (int)strlen(tempString01))
		{
			::fclose(fp);
			return FALSE;
		}
		mIPInfoList[index01][1][1] = atoi(tempString02);
		index02++;
		index03 = 0;
		for (; index02 < (int)strlen(tempString01); index02++)
		{
			tempString02[index03] = tempString01[index02];
			index03++;
			if (tempString01[index02] == '.')
			{
				tempString02[index03] = '\0';
				break;
			}
		}
		if (index02 == (int)strlen(tempString01))
		{
			::fclose(fp);
			return FALSE;
		}
		mIPInfoList[index01][1][2] = atoi(tempString02);
		index02++;
		index03 = 0;
		for (; index02 < (int)strlen(tempString01); index02++)
		{
			tempString02[index03] = tempString01[index02];
			index03++;
		}
		tempString02[index03] = '\0';
		mIPInfoList[index01][1][3] = atoi(tempString02);
	}
	if (::fclose(fp) != 0)
	{
		return FALSE;
	}

	return TRUE;
}
//COMPARE_IP_INFO
BOOL CIPInfoList::CompareIPInfo(int tIP1, int tIP2, int tIP3, int tIP4)
{
	int index01;
	char tempString01[1000];
	long long tIP;
	long long tBlockIP01;
	long long tBlockIP02;

	sprintf(tempString01, "%03d%03d%03d%03d", tIP1, tIP2, tIP3, tIP4);
	tIP = ::atol(tempString01);
	for (index01 = 0; index01 < mTotalIPInfoNum; index01++)
	{
		sprintf(tempString01, "%03d%03d%03d%03d", mIPInfoList[index01][0][0], mIPInfoList[index01][0][1], mIPInfoList[index01][0][2], mIPInfoList[index01][0][3]);
		tBlockIP01 = ::atol(tempString01);
		sprintf(tempString01, "%03d%03d%03d%03d", mIPInfoList[index01][1][0], mIPInfoList[index01][1][1], mIPInfoList[index01][1][2], mIPInfoList[index01][1][3]);
		tBlockIP02 = ::atol(tempString01);
		if ((tBlockIP01 <= tIP) && (tBlockIP02 >= tIP))
		{
			return TRUE;
		}
	}
	return FALSE;
}
//GET_ONE_VALUE_FROM_FILE
BOOL CIPInfoList::GetOneValueFromFile(FILE* fp, int tBufferSize, char *tBuffer)
{
	int index01;
	DWORD nReadByte;
	BOOL tCheckSaveState;
	char tData;

	index01 = 0;
	tCheckSaveState = FALSE;
	while (TRUE)
	{
		if (fread(&tData, 1, 1, fp) != 1)
		{
			return FALSE;
		}
		if (!tCheckSaveState)
		{
			if (tData == '[')
			{
				tCheckSaveState = TRUE;
			}
		}
		else
		{
			if (tData == ']')
			{
				tBuffer[index01] = '\0';
				break;
			}
			else
			{
				if (index01 < (tBufferSize - 1))
				{
					tBuffer[index01] = tData;
					index01++;
				}
				else
				{
					return FALSE;
				}
			}
		}
	}
	return TRUE;
}

//-------------------------------------------------------------------------------------------------
