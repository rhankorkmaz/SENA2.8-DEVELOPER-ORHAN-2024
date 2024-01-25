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
MyGame::MyGame( void )
{
}
//INIT

BOOL MyGame::Init( void )
{
	mTickCount = 0;
	
	if (!UpdateCashItem())
	{
		__LogMgr()->Log("!Cash Info Error\n");
	}
	if (!UpdateBloodItem())
	{
		__LogMgr()->Log("!Cash Info Error\n");
	}
	__LogMgr()->Log("!GAME Init - End.\n");
	//-------------------------------------------------------------------------------------------------
	return TRUE;

}
int MyGame::UpdateCashItem( void )
{
	char tempString01[1000] = { 0, };
	int index01 = 0;
	int index02 = 0;
	//-------------------------------------------------------------------------------------------------
	// 2008.11.18 Kim SungSoo
	// Intro : 1. Modify win32 file IO to linux c++ file IO
	//-------------------------------------------------------------------------------------------------
	HANDLE hFile;
	hFile = CreateFile("DATA/COST_INFO.TXT", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	if (!GetOneValueFromFile(hFile, 1000, &tempString01[0]))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	mTotalCostInfoNum = atoi(tempString01);
	for (index01 = 0; index01 < mTotalCostInfoNum; index01++)
	{
		if (!GetOneValueFromFile(hFile, 1000, &tempString01[0]))
		{
			CloseHandle(hFile);
			return FALSE;
		}
		mCostInfoValue[index01][0] = atoi(tempString01);
		if (!GetOneValueFromFile(hFile, 1000, &tempString01[0]))
		{
			CloseHandle(hFile);
			return FALSE;
		}
		mCostInfoValue[index01][1] = atoi(tempString01);
		if (!GetOneValueFromFile(hFile, 1000, &tempString01[0]))
		{
			CloseHandle(hFile);
			return FALSE;
		}
		mCostInfoValue[index01][2] = atoi(tempString01);
		if (!GetOneValueFromFile(hFile, 1000, &tempString01[0]))
		{
			CloseHandle(hFile);
			return FALSE;
		}
		mCostInfoValue[index01][3] = atoi(tempString01);
		if (!GetOneValueFromFile(hFile, 1000, &tempString01[0]))
		{
			CloseHandle(hFile);
			return FALSE;
		}
		strcpy(mCostInfoCode[index01], tempString01);
	}
	if (!CloseHandle(hFile))
	{
		return FALSE;
	}

	// @ Cost Info Download @
	mIsSellCashItem = false;
	int tVersion = 0;

	__LogMgr()->Log("!GAME Init - Start.\n");

	__LogMgr()->Log("!GAME Init - Load Cost Info.\n");
	if (!LoadCostInfo(&mTotalCostInfoNum, &tVersion, mCostInfoValue, mCostInfoCode))
	{
		return FALSE;
	}

	__LogMgr()->Log("!GAME Init - MakeCashItemInfo.\n");
	if (!MakeCashItemInfo(mCashItemInfo, mCostInfoValue, mTotalCostInfoNum))
	{
		return FALSE;
	}

	mIsSellCashItem = true;
	mCashItemInfoVersion = tVersion;
	return TRUE;
}
int MyGame::UpdateBloodItem(void)
{
	char tempString01[1000] = { 0, };
	int index01 = 0;
	int index02 = 0;
	//-------------------------------------------------------------------------------------------------
	// 2008.11.18 Kim SungSoo
	// Intro : 1. Modify win32 file IO to linux c++ file IO
	//-------------------------------------------------------------------------------------------------
	HANDLE hFile;
	hFile = CreateFile("DATA/BLOOD_INFO.TXT", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	if (!GetOneValueFromFile(hFile, 1000, &tempString01[0]))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	mTotalCostBloodInfoNum = atoi(tempString01);
	for (index01 = 0; index01 < mTotalCostBloodInfoNum; index01++)
	{
		if (!GetOneValueFromFile(hFile, 1000, &tempString01[0]))
		{
			CloseHandle(hFile);
			return FALSE;
		}
		mBloodInfoValue[index01][0] = atoi(tempString01);
		if (!GetOneValueFromFile(hFile, 1000, &tempString01[0]))
		{
			CloseHandle(hFile);
			return FALSE;
		}
		mBloodInfoValue[index01][1] = atoi(tempString01);
		if (!GetOneValueFromFile(hFile, 1000, &tempString01[0]))
		{
			CloseHandle(hFile);
			return FALSE;
		}
		mBloodInfoValue[index01][2] = atoi(tempString01);
		if (!GetOneValueFromFile(hFile, 1000, &tempString01[0]))
		{
			CloseHandle(hFile);
			return FALSE;
		}
		mBloodInfoValue[index01][3] = atoi(tempString01);
		if (!GetOneValueFromFile(hFile, 1000, &tempString01[0]))
		{
			CloseHandle(hFile);
			return FALSE;
		}
		strcpy(mBloodInfoCode[index01], tempString01);
	}
	if (!CloseHandle(hFile))
	{
		return FALSE;
	}
	__LogMgr()->Log("!GAME Init - Load Blood Info.\n");
	if (!LoadBloodInfo(&mTotalCostBloodInfoNum, mBloodInfoValue, mBloodInfoCode))
	{
		return FALSE;
	}
	printf("mTotalCostBloodInfoNum === %d\n", mTotalCostBloodInfoNum);

	__LogMgr()->Log("!GAME Init - MakeBloodItemInfo.\n");
	if (!MakeBloodItemInfo(mBloodCashItemInfo, mBloodInfoValue, mTotalCostBloodInfoNum))
	{
		return FALSE;
	}
	return TRUE;
}

//FREE
void MyGame::Free( void )
{

}
//GET_ONE_VALUE_FROM_FILE

//-------------------------------------------------------------------------------------------------
// 2008.11.18 Kim SungSoo
// Intro : 1. Modify win32 function to linux c++ 
//-------------------------------------------------------------------------------------------------
BOOL MyGame::GetOneValueFromFile( HANDLE hFile, int tBufferSize, char *tBuffer )
{
	int index01;
	DWORD nReadByte;
	BOOL tCheckSaveState;
	char tData;

	index01 = 0;
	tCheckSaveState = FALSE;
	while( TRUE )
	{
		if( !ReadFile( hFile, &tData, 1, &nReadByte, NULL ) )
		{
			return FALSE;
		}
		if( nReadByte != 1 )
		{
			return FALSE;
		}
		if( !tCheckSaveState )
		{
			if( tData == '[' )
			{
				tCheckSaveState = TRUE;
			}
		}
		else
		{
			if( tData == ']' )
			{
				tBuffer[index01] = '\0';
				break;
			}
			else
			{
				if( index01 < ( tBufferSize - 1 ) )
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
// @ Cost Info Download @ {
//int MyGame::GetOneValueFromFile(const char *pBuffer , int iParsorIndex)
bool MyGame::GetOneValueFromFile(const char *pBuffer , int iParsorIndex, int *tResult)
{
	int i = 0;
	int chk = 0;
	char tbuf[20];
	int chk_cnt = 0;
	char *ptr_tmp = (char *)pBuffer;

	while(*ptr_tmp != '\0') {
		if(!chk) {
			if(*ptr_tmp == '[') {
				ptr_tmp++;
				chk_cnt++;
				if(chk_cnt == iParsorIndex)
					chk = 1;
			} else {
				ptr_tmp++;
				continue;
			}
		} else {
			if(chk_cnt == iParsorIndex)
			{
				tbuf[i++] = *ptr_tmp;
				if(*ptr_tmp == ']') {
					tbuf[--i] = '\0';
					*tResult = atoi(tbuf);
					//__LogMgr()->Log("GetOneValueFromFile---> %s\n", tbuf);
					return true;
					//break;
				}
			}
			ptr_tmp++;
		}
	}

	return false;
	//return atoi(tbuf);
} // @

bool MyGame::GetOneValueFromFile(char *pValue , const char *pBuffer , int iParsorIndex)
{
	if(pValue == NULL)
	{
		return false;
	}


	int i = 0;
	int chk = 0;
	char tbuf[51];
	int chk_cnt = 0;
	char *ptr_tmp = (char *)pBuffer;

	while(*ptr_tmp != '\0') {
		if(!chk) {
			if(*ptr_tmp == '[') {
				ptr_tmp++;
				chk_cnt++;
				if(chk_cnt == iParsorIndex)
					chk = 1;
			} else {
				ptr_tmp++;
				continue;
			}
		} else {
			if(chk_cnt == iParsorIndex) {
				tbuf[i++] = *ptr_tmp;
				if(*ptr_tmp == ']') {
					tbuf[--i] = '\0';
					break;
				}
			}
			ptr_tmp++;
		}
	}
	//__LogMgr()->Log("---> %s\n", tbuf);

	strncpy(pValue , (char*)tbuf , sizeof(tbuf) );

	return true;
}


// @ Cost Info Download @ {
int MyGame::GetCostInfoVersion()
{
	FILE *r_fp = NULL;

	if (!(r_fp = fopen("DATA/COST_INFO.TXT", "r")))
	{
		__LogMgr()->Log("!GetCostInfoVersion - file open false : %s\n",  "DATA/COST_INFO.TXT\n");
		return mCashItemInfoVersion; // 파일 열기 실패 시 기존 버전을 리턴.
	}

	char tempString01[1000] = {0};
	char *readResult = fgets(tempString01, 1000, r_fp);
	fclose(r_fp);

	if (readResult != NULL)
	{
		// COST_INFO.TXT 버전 추출
		int tVersion = -1;
		if (GetOneValueFromFile(tempString01 , 2, &tVersion))
		{
			return tVersion;
		}
	}

	__LogMgr()->Log("!GetCostInfoVersion - Version read fail\n");

	return -1;
}

bool MyGame::LoadCostInfo(int *pTotalCostInfoNum, int *pVersion, int tCostInfoValue[MAX_COST_INFO_NUM][MAX_COST_INFO_TYPE], char tCostInfoCode[MAX_COST_INFO_NUM][MAX_COST_INFO_CODE_LEN])
{
	char tempString01[1000] = {0};
	int index01 = 0;
	int index02 = 0;
	FILE *r_fp = NULL;

	if(!(r_fp = fopen("DATA/COST_INFO.TXT", "r"))) 
	{
		__LogMgr()->Log("file open false : %s\n",  "DATA/COST_INFO.TXT\n");
		return false;
	}

	if(fgets(tempString01, 1000, r_fp) != NULL) 
	{
		if (!GetOneValueFromFile(tempString01 , 1, pTotalCostInfoNum)) 
		{
			__LogMgr()->Log("!Error - Get Total Cost Info Num - %s\n", tempString01);
			return false;
		}
		__LogMgr()->Log("!totalcostinfonum[%d] , %s\n", *pTotalCostInfoNum , tempString01);

		// COST_INFO.TXT 버전 추출
		if (!GetOneValueFromFile(tempString01 , 2, pVersion)) 
		{
			__LogMgr()->Log("!Error - Get Cost Info Version.\n");
			return false;
		}
		if (*pVersion <= 0) 
		{
			__LogMgr()->Log("!Error - COST_INFO.TXT Version[%d]\n", *pVersion);
			return false;
		}
		__LogMgr()->Log("!COST_INFO.TXT Version[%d]\n", *pVersion);
	} 
	else 
	{
		__LogMgr()->Log("file load false : %s \n",  tempString01);
		return false;
	}

	// Extra 서버에서 사용할 CostInfo 추출.
	index01 = 0;
	while(fgets(tempString01, 1000, r_fp) != NULL) 
	{
		//__LogMgr()->Log("file load value for one line : %s\n",  tempString01);
		for (index02 = 0; index02 < MAX_COST_INFO_TYPE; ++index02) 
		{
			if (!GetOneValueFromFile(tempString01 , index02+1, &tCostInfoValue[index01][index02])) 
			{
				__LogMgr()->Log("Error - CostInfoValue[%d][%d]\n", index01 ,index02);
				return false;
			}
			//__LogMgr()->Log_3("CostInfoValue[%d][%d] = %d \n", index01 ,index02 , tCostInfoValue[index01][index02] );
		}

		memset(tCostInfoCode[index01] , 0x00 , MAX_COST_INFO_CODE_LEN);
		GetOneValueFromFile(tCostInfoCode[index01] , tempString01 , index02+1 );
		//__LogMgr()->Log_2("CostInfoCode[%d] = %s \n", index01  , tCostInfoCode[index01] );
		index01++;
	}
	fclose(r_fp);

	if (*pTotalCostInfoNum != index01) 
   {
		__LogMgr()->Log("Error - CostInfoNum Total(%d) / Load(%d)\n", *pTotalCostInfoNum, index01);
		return false;
	}

	return true;
}

bool MyGame::MakeCashItemInfo(int tCashItemInfo[4][14][10][4], const int tCostInfoValue[MAX_COST_INFO_NUM][MAX_COST_INFO_TYPE], int totalCostInfoNum)
{
	// 클라이언트에서 사용하는 캐쉬 정보 셋팅.
	const int MAX_CASH_ITEM_NUM = totalCostInfoNum;
	::memset(tCashItemInfo, -1, MAX_CASH_ITEM_INFO_SIZE);

	int showType = 0;
	int pageCount[4] = {0};
	int itemCount[4] = {0};

	for (int costInfoIndex = 0; costInfoIndex < MAX_CASH_ITEM_NUM; ++costInfoIndex) 
	{
		if(tCostInfoValue[costInfoIndex][4] <= 0) 
		{
			__LogMgr()->Log("!MakeCashItemInfo Error - tCostInfoValue[costInfoIndex][4] < 0\n");
			return false;
		}
		showType = tCostInfoValue[costInfoIndex][4] - 1;

		if (pageCount[showType] > 9) 
		{
			__LogMgr()->Log("!MakeCashItemInfo Error - over max page count\n");
			return false;
		}

		tCashItemInfo[showType][pageCount[showType]][itemCount[showType]][0] = costInfoIndex;                     // Cost Info Num - 1
		tCashItemInfo[showType][pageCount[showType]][itemCount[showType]][1] = tCostInfoValue[costInfoIndex][1];  // Item Number.
		tCashItemInfo[showType][pageCount[showType]][itemCount[showType]][2] = tCostInfoValue[costInfoIndex][2];  // Quantity.
		tCashItemInfo[showType][pageCount[showType]][itemCount[showType]][3] = tCostInfoValue[costInfoIndex][0];  // Cost.

		++itemCount[showType];
		if (itemCount[showType] > 9) 
		{
			++pageCount[showType];
			itemCount[showType] = 0;
		}
	}

	return true;
} // @
//-------------------------------------------------------------------------------------------------
bool MyGame::LoadBloodInfo(int* ptotalBloodInfoNum, int tBlooInfoValue[200][4], char tBlooInfoCode[200][MAX_COST_INFO_CODE_LEN])
{
	char tempString01[1000] = { 0 };
	int index01 = 0;
	int index02 = 0;
	FILE* r_fp = NULL;

	if (!(r_fp = fopen("DATA/BLOOD_INFO.TXT", "r")))
	{
		__LogMgr()->Log("file open false : %s\n", "DATA/BLOOD_INFO.TXT\n");
		return false;
	}

	if (fgets(tempString01, 200, r_fp) != NULL)
	{
		if (!GetOneValueFromFile(tempString01, 1, ptotalBloodInfoNum))
		{
			__LogMgr()->Log("!Error - Get BloodInfo Info Num - %s\n", tempString01);
			return false;
		}
		__LogMgr()->Log("!totalcostinfonum[%d] , %s\n", *ptotalBloodInfoNum, tempString01);

	}
	else
	{
		__LogMgr()->Log("file load false : %s \n", tempString01);
		return false;
	}

	// Extra 서버에서 사용할 CostInfo 추출.
	index01 = 0;
	while (fgets(tempString01, 200, r_fp) != NULL)
	{
		//__LogMgr()->Log("file load value for one line : %s\n",  tempString01);
		for (index02 = 0; index02 < 4; ++index02)
		{
			if (!GetOneValueFromFile(tempString01, index02 + 1, &tBlooInfoValue[index01][index02]))
			{
				__LogMgr()->Log("Error - BloodInfoValue[%d][%d]\n", index01, index02);
				return false;
			}
			//__LogMgr()->Log_3("CostInfoValue[%d][%d] = %d \n", index01 ,index02 , tCostInfoValue[index01][index02] );
		}

		memset(tBlooInfoCode[index01], 0x00, MAX_COST_INFO_CODE_LEN);
		GetOneValueFromFile(tBlooInfoCode[index01], tempString01, index02 + 1);
		//__LogMgr()->Log_2("CostInfoCode[%d] = %s \n", index01  , tCostInfoCode[index01] );
		index01++;
	}
	fclose(r_fp);

	if (*ptotalBloodInfoNum != index01)
	{
		__LogMgr()->Log("Error - BloodInfo Total(%d) / Load(%d)\n", *ptotalBloodInfoNum, index01);
		return false;
	}

	return true;
}
bool MyGame::MakeBloodItemInfo(int tBloodItemInfo[4][50][3], const int tCostBloodValue[50][4], int totalBloodInfoNum)
{
	// 클라이언트에서 사용하는 캐쉬 정보 셋팅.
	const int MAX_CASH_ITEM_NUM = totalBloodInfoNum;
	::memset(tBloodItemInfo, -1, 600);

	int showType = 0;
	int pageCount[4] = { 0 };
	int itemCount = { 0 };

	//Ejder
	for (int costInfoIndex = 0; costInfoIndex < MAX_CASH_ITEM_NUM; ++costInfoIndex)
	{
		if (tCostBloodValue[costInfoIndex][3] < 0)
		{
			__LogMgr()->Log("!MakeCashItemInfo Error - tCostInfoValue[costInfoIndex][4] < 0\n");
			return false;
		}
		if (tCostBloodValue[costInfoIndex][0] == 0)
		{
			continue;
		}
		showType = tCostBloodValue[costInfoIndex][3];//Tribe
		if (showType != 0)
		{
			continue;
		}
		tBloodItemInfo[showType][itemCount][0] = tCostBloodValue[costInfoIndex][0];  // Item Number.
		tBloodItemInfo[showType][itemCount][1] = tCostBloodValue[costInfoIndex][1];  // Cost
		tBloodItemInfo[showType][itemCount][2] = tCostBloodValue[costInfoIndex][2];  // unk
		itemCount++;
	}
	itemCount = 0;

	//Ejder
	for (int costInfoIndex = 0; costInfoIndex < MAX_CASH_ITEM_NUM; ++costInfoIndex)
	{
		if (tCostBloodValue[costInfoIndex][3] < 0)
		{
			__LogMgr()->Log("!MakeCashItemInfo Error - tCostInfoValue[costInfoIndex][4] < 0\n");
			return false;
		}
		if (tCostBloodValue[costInfoIndex][0] == 0)
		{
			continue;
		}
		showType = tCostBloodValue[costInfoIndex][3];//Tribe
		if (showType != 1)
		{
			continue;
		}
		tBloodItemInfo[showType][itemCount][0] = tCostBloodValue[costInfoIndex][0];  // Item Number.
		tBloodItemInfo[showType][itemCount][1] = tCostBloodValue[costInfoIndex][1];  // Cost
		tBloodItemInfo[showType][itemCount][2] = tCostBloodValue[costInfoIndex][2];  // unk
		itemCount++;
	}
	itemCount = 0;
	//Ejder
	for (int costInfoIndex = 0; costInfoIndex < MAX_CASH_ITEM_NUM; ++costInfoIndex)
	{
		if (tCostBloodValue[costInfoIndex][3] < 0)
		{
			__LogMgr()->Log("!MakeCashItemInfo Error - tCostInfoValue[costInfoIndex][4] < 0\n");
			return false;
		}
		if (tCostBloodValue[costInfoIndex][0] == 0)
		{
			continue;
		}
		showType = tCostBloodValue[costInfoIndex][3];//Tribe
		if (showType != 2)
		{
			continue;
		}
		tBloodItemInfo[showType][itemCount][0] = tCostBloodValue[costInfoIndex][0];  // Item Number.
		tBloodItemInfo[showType][itemCount][1] = tCostBloodValue[costInfoIndex][1];  // Cost
		tBloodItemInfo[showType][itemCount][2] = tCostBloodValue[costInfoIndex][2];  // unk
		itemCount++;
	}
	itemCount = 0;
	//Ejder
	for (int costInfoIndex = 0; costInfoIndex < MAX_CASH_ITEM_NUM; ++costInfoIndex)
	{
		if (tCostBloodValue[costInfoIndex][3] < 0)
		{
			__LogMgr()->Log("!MakeCashItemInfo Error - tCostInfoValue[costInfoIndex][4] < 0\n");
			return false;
		}
		if (tCostBloodValue[costInfoIndex][0] == 0)
		{
			continue;
		}
		showType = tCostBloodValue[costInfoIndex][3];//Tribe
		if (showType != 3)
		{
			continue;
		}
		tBloodItemInfo[showType][itemCount][0] = tCostBloodValue[costInfoIndex][0];  // Item Number.
		tBloodItemInfo[showType][itemCount][1] = tCostBloodValue[costInfoIndex][1];  // Cost
		tBloodItemInfo[showType][itemCount][2] = tCostBloodValue[costInfoIndex][2];  // unk
		itemCount++;
	}
	itemCount = 0;

	return true;
}