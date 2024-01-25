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
		, "ts2_gamedb", mSERVER_INFO.mDB_1_ID, mSERVER_INFO.mDB_1_PASSWORD) < 0) {
		return FALSE;
	}
	if (!mDB01.connect()) {
		return FALSE;
	}
	if (mDB01_FOR_THREAD.set_db_conn_info(mSERVER_INFO.mDB_1_IP, mSERVER_INFO.mDB_1_IP, mSERVER_INFO.mDB_1_PORT
		, "ts2_gamedb", mSERVER_INFO.mDB_1_ID, mSERVER_INFO.mDB_1_PASSWORD) < 0) {
		return false;
	}
	if (!mDB01_FOR_THREAD.connect()) {
		return FALSE;
	}
	if (mDB02.set_db_conn_info(mSERVER_INFO.mDB_2_IP, mSERVER_INFO.mDB_2_IP, mSERVER_INFO.mDB_2_PORT
		, "ts2_gamedb", mSERVER_INFO.mDB_2_ID, mSERVER_INFO.mDB_2_PASSWORD) < 0) {
		return false;
	}
	if (!mDB02.connect()) {
		return FALSE;
	}
	if (mDB02_FOR_THREAD.set_db_conn_info(mSERVER_INFO.mDB_2_IP, mSERVER_INFO.mDB_2_IP, mSERVER_INFO.mDB_2_PORT
		, "ts2_gamedb", mSERVER_INFO.mDB_2_ID, mSERVER_INFO.mDB_2_PASSWORD) < 0) {
		return false;
	}
	if (!mDB02_FOR_THREAD.connect()) {
		return FALSE;
	}

	Logger("![%s] OK", __FUNCTION__);
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
		printf("![%s] : reconnect failed\n", __FUNCTION__);
		return FALSE;
	}
	printf("![%s] : reconnected\n", __FUNCTION__);
	return TRUE;
}
//RECONNECT_TO_DATABASE01_FOR_THREAD
BOOL MyDB::RECONNECT_TO_DATABASE01_FOR_THREAD(void)
{
	if (mDB01_FOR_THREAD.IsConnected())
	{
		return TRUE;
	}
	if (!mDB01_FOR_THREAD.Reconnect())
	{
		printf("![%s] : reconnect failed\n", __FUNCTION__);
		return FALSE;
	}
	printf("![%s] : reconnected\n", __FUNCTION__);
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
		printf("![%s] : reconnect failed\n", __FUNCTION__);
		return FALSE;
	}
	printf("![%s] : reconnected\n", __FUNCTION__);
	return TRUE;
}
//RECONNECT_TO_DATABASE02_FOR_THREAD
BOOL MyDB::RECONNECT_TO_DATABASE02_FOR_THREAD(void)
{
	if (mDB02_FOR_THREAD.IsConnected())
	{
		return TRUE;
	}
	if (!mDB02_FOR_THREAD.Reconnect())
	{
		__LogMgr()->Log("![%s] : reconnect failed\n", __FUNCTION__);
		return FALSE;
	}
	__LogMgr()->Log("![%s] : reconnected\n", __FUNCTION__);
	return TRUE;
}

//DB_PROCESS_14
void MyDB::DB_PROCESS_20(char aName[MAX_AVATAR_NAME_LENGTH], VALETSHOP_INFO* tValetShop, int* tResult)
{
	MYSQL_ROW row;
	MYSQL_RES* res;
	int iAffected;
	int iCounts;
	char tCnt = 0;
	char ValetShopInfo[5][5][200];
	char tempString01[1000];
	ZeroMemory(tValetShop, sizeof(VALETSHOP_INFO));
	ZeroMemory(ValetShopInfo, sizeof(ValetShopInfo));
	int index01;
	int index02;
	char mQUERYValetShop[MAX_QUERY_BUFFER_SIZE];

	sprintf(mQUERYValetShop, "Select ValetShopName, ValetShop00, ValetShop01, ValetShop02, ValetShop03, ValetShop04,"
		" ValetShop10, ValetShop11, ValetShop12, ValetShop13, ValetShop14,"
		" ValetShop20, ValetShop21, ValetShop22, ValetShop23, ValetShop24,"
		" ValetShop30, ValetShop31, ValetShop32, ValetShop33, ValetShop34,"
		" ValetShop40, ValetShop41, ValetShop42, ValetShop43, ValetShop44,"
		" ValetShopBar, ValetShopMoney from valetshopinfo Where ValetShopName = '%s' ", aName);
	if (!RECONNECT_TO_DATABASE01())
	{
		*tResult = 1;
		return;
	}
	iAffected = 0;
	if ((iAffected = mDB01.exec_query(mQUERYValetShop)) < 0) {
		*tResult = 1;
		return;
	}
	iCounts = 0;
	res = mDB01.get_res();
	if (res == NULL) {
		*tResult = 1;
		return;
	}
	while ((row = mysql_fetch_row(res))) {
		::snprintf(tValetShop->mName, MAX_AVATAR_NAME_LENGTH, "%s", row[0]);
		::strncpy(ValetShopInfo[0][0], row[1], sizeof(ValetShopInfo[0][0]));
		::strncpy(ValetShopInfo[0][1], row[2], sizeof(ValetShopInfo[0][1]));
		::strncpy(ValetShopInfo[0][2], row[3], sizeof(ValetShopInfo[0][2]));
		::strncpy(ValetShopInfo[0][3], row[4], sizeof(ValetShopInfo[0][3]));
		::strncpy(ValetShopInfo[0][4], row[5], sizeof(ValetShopInfo[0][4]));
		::strncpy(ValetShopInfo[1][0], row[6], sizeof(ValetShopInfo[1][0]));
		::strncpy(ValetShopInfo[1][1], row[7], sizeof(ValetShopInfo[1][1]));
		::strncpy(ValetShopInfo[1][2], row[8], sizeof(ValetShopInfo[1][2]));
		::strncpy(ValetShopInfo[1][3], row[9], sizeof(ValetShopInfo[1][3]));
		::strncpy(ValetShopInfo[1][4], row[10], sizeof(ValetShopInfo[1][4]));
		::strncpy(ValetShopInfo[2][0], row[11], sizeof(ValetShopInfo[2][0]));
		::strncpy(ValetShopInfo[2][1], row[12], sizeof(ValetShopInfo[2][1]));
		::strncpy(ValetShopInfo[2][2], row[13], sizeof(ValetShopInfo[2][2]));
		::strncpy(ValetShopInfo[2][3], row[14], sizeof(ValetShopInfo[2][3]));
		::strncpy(ValetShopInfo[2][4], row[15], sizeof(ValetShopInfo[2][4]));
		::strncpy(ValetShopInfo[3][0], row[16], sizeof(ValetShopInfo[3][0]));
		::strncpy(ValetShopInfo[3][1], row[17], sizeof(ValetShopInfo[3][1]));
		::strncpy(ValetShopInfo[3][2], row[18], sizeof(ValetShopInfo[3][2]));
		::strncpy(ValetShopInfo[3][3], row[19], sizeof(ValetShopInfo[3][3]));
		::strncpy(ValetShopInfo[3][4], row[20], sizeof(ValetShopInfo[3][4]));
		::strncpy(ValetShopInfo[4][0], row[21], sizeof(ValetShopInfo[4][0]));
		::strncpy(ValetShopInfo[4][1], row[22], sizeof(ValetShopInfo[4][1]));
		::strncpy(ValetShopInfo[4][2], row[23], sizeof(ValetShopInfo[4][2]));
		::strncpy(ValetShopInfo[4][3], row[24], sizeof(ValetShopInfo[4][3]));
		::strncpy(ValetShopInfo[4][4], row[25], sizeof(ValetShopInfo[4][4]));
		tValetShop->mShopBar = ::atoi(row[26]);
		tValetShop->mShopMoney = ::atoi(row[27]);
		iCounts++;
	}
	mDB01.clear_res();
	if (iCounts != 1) {
		*tResult = 1;
		return;
	}
	for (index01 = 0; index01 < 5; index01++)
	{
		for (index02 = 0; index02 < 5; index02++)
		{
			//İtem Id
			CopyMemory(&tempString01[0], &ValetShopInfo[index01][index02][0], 9);
			tempString01[9] = '\0';
			tValetShop->mItemInfo[index01][index02][0] = atoi(tempString01);
			CopyMemory(&tempString01[0], &ValetShopInfo[index01][index02][9], 9);
			tempString01[9] = '\0';
			tValetShop->mItemInfo[index01][index02][1] = atoi(tempString01);
			//Item Yüzde
			CopyMemory(&tempString01[0], &ValetShopInfo[index01][index02][18], 9);
			tempString01[9] = '\0';
			tValetShop->mItemInfo[index01][index02][2] = atoi(tempString01);

			CopyMemory(&tempString01[0], &ValetShopInfo[index01][index02][27], 9);
			tempString01[9] = '\0';
			tValetShop->mItemInfo[index01][index02][3] = atoi(tempString01);
			//Item Fiyatı
			CopyMemory(&tempString01[0], &ValetShopInfo[index01][index02][36], 9);
			tempString01[9] = '\0';
			tValetShop->mItemInfo[index01][index02][4] = atoi(tempString01);
			//Item Soket 1
			CopyMemory(&tempString01[0], &ValetShopInfo[index01][index02][45], 9);
			tempString01[9] = '\0';
			tValetShop->mSoketInfo[index01][index02][0] = atoi(tempString01);
			//Item Soket 2
			CopyMemory(&tempString01[0], &ValetShopInfo[index01][index02][54], 9);
			tempString01[9] = '\0';
			tValetShop->mSoketInfo[index01][index02][1] = atoi(tempString01);
			//Item Soket 3
			CopyMemory(&tempString01[0], &ValetShopInfo[index01][index02][63], 9);
			tempString01[9] = '\0';
			tValetShop->mSoketInfo[index01][index02][2] = atoi(tempString01);

		}
	}
	*tResult = 0;
	return;
}

//DB_PROCESS_14
void MyDB::DB_PROCESS_21(char aName[MAX_AVATAR_NAME_LENGTH], VALETSHOP_INFO* tValetShop, int* tResult)
{
	int index01;
	int index02;
	char ValetShop[5][5][200];
	char tempString01[100000];
	char tempQuery[100000];
	int iAffected;
	char mQUERYValetShop[MAX_QUERY_BUFFER_SIZE];

	for (index01 = 0; index01 < 5; index01++)
	{

		for (index02 = 0; index02 < 5; index02++)
		{
			ValetShop[index01][index02][0] = '\0';
			sprintf(tempString01, "%09d%09d%09d%09d%09d%09d%09d%09d", (tValetShop->mItemInfo[index01][index02][0] % 1000000000), (tValetShop->mItemInfo[index01][index02][1] % 1000000000)
				, (tValetShop->mItemInfo[index01][index02][2] % 1000000000), (tValetShop->mItemInfo[index01][index02][3] % 1000000000), (tValetShop->mItemInfo[index01][index02][4] % 1000000000)
				, (tValetShop->mSoketInfo[index01][index02][0] % 1000000000), (tValetShop->mSoketInfo[index01][index02][1] % 1000000000), (tValetShop->mSoketInfo[index01][index02][2] % 1000000000));
			strcat(ValetShop[index01][index02], tempString01);
		}
	}

	strcpy(mQUERYValetShop, "UPDATE valetshopinfo SET ");
	sprintf(tempQuery, "ValetShop00 = '%s', ", ValetShop[0][0]);
	strcat(mQUERYValetShop, tempQuery);
	sprintf(tempQuery, "ValetShop01 = '%s', ", ValetShop[0][1]);
	strcat(mQUERYValetShop, tempQuery);
	sprintf(tempQuery, "ValetShop02 = '%s', ", ValetShop[0][2]);
	strcat(mQUERYValetShop, tempQuery);
	sprintf(tempQuery, "ValetShop03 = '%s', ", ValetShop[0][3]);
	strcat(mQUERYValetShop, tempQuery);
	sprintf(tempQuery, "ValetShop04 = '%s', ", ValetShop[0][4]);
	strcat(mQUERYValetShop, tempQuery);
	sprintf(tempQuery, "ValetShop10 = '%s', ", ValetShop[1][0]);
	strcat(mQUERYValetShop, tempQuery);
	sprintf(tempQuery, "ValetShop11 = '%s', ", ValetShop[1][1]);
	strcat(mQUERYValetShop, tempQuery);
	sprintf(tempQuery, "ValetShop12 = '%s', ", ValetShop[1][2]);
	strcat(mQUERYValetShop, tempQuery);
	sprintf(tempQuery, "ValetShop13 = '%s', ", ValetShop[1][3]);
	strcat(mQUERYValetShop, tempQuery);
	sprintf(tempQuery, "ValetShop14 = '%s', ", ValetShop[1][4]);
	strcat(mQUERYValetShop, tempQuery);
	sprintf(tempQuery, "ValetShop20 = '%s', ", ValetShop[2][0]);
	strcat(mQUERYValetShop, tempQuery);
	sprintf(tempQuery, "ValetShop21 = '%s', ", ValetShop[2][1]);
	strcat(mQUERYValetShop, tempQuery);
	sprintf(tempQuery, "ValetShop22 = '%s', ", ValetShop[2][2]);
	strcat(mQUERYValetShop, tempQuery);
	sprintf(tempQuery, "ValetShop23 = '%s', ", ValetShop[2][3]);
	strcat(mQUERYValetShop, tempQuery);
	sprintf(tempQuery, "ValetShop24 = '%s', ", ValetShop[2][4]);
	strcat(mQUERYValetShop, tempQuery);
	sprintf(tempQuery, "ValetShop30 = '%s', ", ValetShop[3][0]);
	strcat(mQUERYValetShop, tempQuery);
	sprintf(tempQuery, "ValetShop31 = '%s', ", ValetShop[3][1]);
	strcat(mQUERYValetShop, tempQuery);
	sprintf(tempQuery, "ValetShop32 = '%s', ", ValetShop[3][2]);
	strcat(mQUERYValetShop, tempQuery);
	sprintf(tempQuery, "ValetShop33 = '%s', ", ValetShop[3][3]);
	strcat(mQUERYValetShop, tempQuery);
	sprintf(tempQuery, "ValetShop34 = '%s', ", ValetShop[3][4]);
	strcat(mQUERYValetShop, tempQuery);
	sprintf(tempQuery, "ValetShop40 = '%s', ", ValetShop[4][0]);
	strcat(mQUERYValetShop, tempQuery);
	sprintf(tempQuery, "ValetShop41 = '%s', ", ValetShop[4][1]);
	strcat(mQUERYValetShop, tempQuery);
	sprintf(tempQuery, "ValetShop42 = '%s', ", ValetShop[4][2]);
	strcat(mQUERYValetShop, tempQuery);
	sprintf(tempQuery, "ValetShop43 = '%s', ", ValetShop[4][3]);
	strcat(mQUERYValetShop, tempQuery);
	sprintf(tempQuery, "ValetShop44 = '%s', ", ValetShop[4][4]);
	strcat(mQUERYValetShop, tempQuery);
	sprintf(tempQuery, "ValetShopBar = %d, ", tValetShop->mShopBar);
	strcat(mQUERYValetShop, tempQuery);
	sprintf(tempQuery, "ValetShopMoney = %d ", tValetShop->mShopMoney);
	strcat(mQUERYValetShop, tempQuery);
	sprintf(tempQuery, "where ValetShopName = '%s'", aName);
	strcat(mQUERYValetShop, tempQuery);

	if (!RECONNECT_TO_DATABASE02())
	{
		WRITE_FOR_DB_LOG_FOR_QUERY(__FILE__, __FUNCTION__, __LINE__);
		*tResult = 1;
		return;
	}
	iAffected = 0;
	if (mDB02.exec_query(mQUERYValetShop, CMySQL::CLEAR) != 0) {
		WRITE_FOR_DB_LOG_FOR_QUERY(__FILE__, __FUNCTION__, __LINE__);
		*tResult = 1;
		return;
	}
	*tResult = 0;
	return;
}

//WRITE_FOR_DB_LOG_FOR_QUERY
void MyDB::WRITE_FOR_DB_LOG_FOR_QUERY(const char* tFileName, const char* tFuncName, int tLine)
{
	//__LogMgr()->Log("!%s\n", mQUERY);
	Logger("![%s][%s]\n%s\n", tFuncName, tLine, mQUERY);
}
//WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD
void MyDB::WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD(const char* tFileName, const char* tFuncName, int tLine)
{
	//__LogMgr()->Log("!%s\n", mQUERY_FOR_THREAD);
	Logger("![%s][%s]\n%s\n", tFuncName, tLine, mQUERY_FOR_THREAD);
}
//-------------------------------------------------------------------------------------------------