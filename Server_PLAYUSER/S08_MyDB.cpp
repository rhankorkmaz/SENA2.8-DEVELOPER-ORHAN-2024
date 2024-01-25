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
#ifdef __COMMIT__
	if (mDB01.exec_query("SET AUTOCOMMIT=1;", CMySQL::CLEAR) != 0) {
		__LogMgr()->Log("[%s] DB character false(%s)! \n", __FUNCTION__, mDB01.get_error_msg().c_str());
		return FALSE;
	}
#endif
#ifdef __TK__
	if (mDB01.exec_query("SET character SET latin5;", CMySQL::CLEAR) != 0) {
		__LogMgr()->Log("[%s] DB character false(%s)! \n", __FUNCTION__, mDB01.get_error_msg().c_str());
		return FALSE;
	}
#endif
	if (mDB01_FOR_THREAD.set_db_conn_info(mSERVER_INFO.mDB_1_IP, mSERVER_INFO.mDB_1_IP, mSERVER_INFO.mDB_1_PORT
		, "ts2_gamedb", mSERVER_INFO.mDB_1_ID, mSERVER_INFO.mDB_1_PASSWORD) < 0) {
		return false;
	}
	if (!mDB01_FOR_THREAD.connect()) {
		return FALSE;
	}
#ifdef __COMMIT__
	if (mDB01_FOR_THREAD.exec_query("SET AUTOCOMMIT=1;", CMySQL::CLEAR) != 0) {
		__LogMgr()->Log("[%s] DB character false(%s)! \n", __FUNCTION__, mDB01.get_error_msg().c_str());
		return FALSE;
	}
#endif
#ifdef __TK__
	if (mDB01_FOR_THREAD.exec_query("SET character SET latin5;", CMySQL::CLEAR) != 0) {
		__LogMgr()->Log("[%s] DB character false(%s)! \n", __FUNCTION__, mDB01.get_error_msg().c_str());
		return FALSE;
	}
#endif

	if (mDB02.set_db_conn_info(mSERVER_INFO.mDB_2_IP, mSERVER_INFO.mDB_2_IP, mSERVER_INFO.mDB_2_PORT
		, "ts2_gamedb", mSERVER_INFO.mDB_2_ID, mSERVER_INFO.mDB_2_PASSWORD) < 0) {
		return false;
	}
	if (!mDB02.connect()) {
		return FALSE;
	}
#ifdef __COMMIT__
	if (mDB02.exec_query("SET AUTOCOMMIT=1;", CMySQL::CLEAR) != 0) {
		__LogMgr()->Log("[%s] DB character false(%s)! \n", __FUNCTION__, mDB02.get_error_msg().c_str());
		return FALSE;
	}
#endif
#ifdef __TK__
	if (mDB02.exec_query("SET character SET latin5;", CMySQL::CLEAR) != 0) {
		__LogMgr()->Log("[%s] DB character false(%s)! \n", __FUNCTION__, mDB02.get_error_msg().c_str());
		return FALSE;
	}
#endif
	if (mDB02_FOR_THREAD.set_db_conn_info(mSERVER_INFO.mDB_2_IP, mSERVER_INFO.mDB_2_IP, mSERVER_INFO.mDB_2_PORT
		, "ts2_gamedb", mSERVER_INFO.mDB_2_ID, mSERVER_INFO.mDB_2_PASSWORD) < 0) {
		return false;
	}
	if (!mDB02_FOR_THREAD.connect()) {
		return FALSE;
	}
#ifdef __COMMIT__
	if (mDB02_FOR_THREAD.exec_query("SET AUTOCOMMIT=1;", CMySQL::CLEAR) != 0) {
		__LogMgr()->Log("[%s] DB character false(%s)! \n", __FUNCTION__, mDB02.get_error_msg().c_str());
		return FALSE;
	}
#endif
#ifdef __TK__
	if (mDB02_FOR_THREAD.exec_query("SET character SET latin5;", CMySQL::CLEAR) != 0) {
		__LogMgr()->Log("[%s] DB character false(%s)! \n", __FUNCTION__, mDB02.get_error_msg().c_str());
		return FALSE;
	}
#endif

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
		__LogMgr()->Log("![%s] : reconnect failed\n", __FUNCTION__);
		return FALSE;
	}
#ifdef __COMMIT__
	if (mDB01.exec_query("SET AUTOCOMMIT=1;", CMySQL::CLEAR) != 0) {
		__LogMgr()->Log("[%s] DB character false(%s)! \n", __FUNCTION__, mDB01.get_error_msg().c_str());
		return FALSE;
	}
#endif
	__LogMgr()->Log("![%s] : reconnected\n", __FUNCTION__);
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
		__LogMgr()->Log("![%s] : reconnect failed\n", __FUNCTION__);
		return FALSE;
	}
#ifdef __COMMIT__
	if (mDB01_FOR_THREAD.exec_query("SET AUTOCOMMIT=1;", CMySQL::CLEAR) != 0) {
		__LogMgr()->Log("[%s] DB character false(%s)! \n", __FUNCTION__, mDB01.get_error_msg().c_str());
		return FALSE;
	}
#endif
#ifdef __TK__
	if (mDB01_FOR_THREAD.exec_query("SET character SET latin5;", CMySQL::CLEAR) != 0) {
		__LogMgr()->Log("[%s] DB character false(%s)! \n", __FUNCTION__, mDB01.get_error_msg().c_str());
		return FALSE;
	}
#endif
	__LogMgr()->Log("![%s] : reconnected\n", __FUNCTION__);
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
		__LogMgr()->Log("![%s] : reconnect failed\n", __FUNCTION__);
		return FALSE;
	}
#ifdef __COMMIT__
	if (mDB02.exec_query("SET AUTOCOMMIT=1;", CMySQL::CLEAR) != 0) {
		__LogMgr()->Log("[%s] DB character false(%s)! \n", __FUNCTION__, mDB02.get_error_msg().c_str());
		return FALSE;
	}
#endif
#ifdef __TK__
	if (mDB02.exec_query("SET character SET latin5;", CMySQL::CLEAR) != 0) {
		__LogMgr()->Log("[%s] DB character false(%s)! \n", __FUNCTION__, mDB02.get_error_msg().c_str());
		return FALSE;
	}
#endif
	__LogMgr()->Log("![%s] : reconnected\n", __FUNCTION__);
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
#ifdef __COMMIT__
	if (mDB02_FOR_THREAD.exec_query("SET AUTOCOMMIT=1;", CMySQL::CLEAR) != 0) {
		__LogMgr()->Log("[%s] DB character false(%s)! \n", __FUNCTION__, mDB02.get_error_msg().c_str());
		return FALSE;
	}
#endif
#ifdef __TK__
	if (mDB02_FOR_THREAD.exec_query("SET character SET latin5;", CMySQL::CLEAR) != 0) {
		__LogMgr()->Log("[%s] DB character false(%s)! \n", __FUNCTION__, mDB02.get_error_msg().c_str());
		return FALSE;
	}
#endif
	__LogMgr()->Log("![%s] : reconnected\n", __FUNCTION__);
	return TRUE;
}
//MAKE_QUERY_FOR_SAVE
void MyDB::MakeQueryForSave(int tSort, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO* tAvatarInfo, int tLoginPremiumPCRoom)
{
	int index01;
	int index02;
	char tempString01[100000];
	char uSaveItem[701];
	char aEquip[326];
	char InventorySocket[3456];
	char EquipSocket[352];
	char TradeSocket[217];
	char StoreSocket[1513];
	char SaveSocket[757];
	char aInventory[3457];
	char aTrade[201];
	char aStoreItem[1401];
	char aSkill[241];
	char aHotKey[421];
	char aQuestInfo[26];
	char aFriend[121];
	char AutoBuff[49];
	char AnimalExp[91];
	char AnimalStat[91];
	char PetInventory[121];
	char aAutoConfig[82];
	FILE* fp;
	ZeroMemory(tempString01, sizeof(tempString01));
	switch (tSort)
	{
	case 1:
		uSaveItem[0] = '\0';
		for (index01 = 0; index01 < MAX_SAVE_ITEM_SLOT_NUM; index01++)
		{
			sprintf(tempString01, "%05d%03d%09d%08d", (tAvatarInfo->uSaveItem[index01][0] % 100000), (tAvatarInfo->uSaveItem[index01][1] % 1000), (tAvatarInfo->uSaveItem[index01][2] % 1000000000), (tAvatarInfo->uSaveItem[index01][3] % 100000000));
			strcat(uSaveItem, tempString01);
		}
		ZeroMemory(tempString01, sizeof(tempString01));
		SaveSocket[0] = '\0';
		for (index01 = 0; index01 < MAX_SAVE_ITEM_SLOT_NUM; index01++)
		{
			sprintf(tempString01, "%09d%09d%09d", (tAvatarInfo->SaveSocket[index01][0] % 1000000000), (tAvatarInfo->SaveSocket[index01][1] % 1000000000), (tAvatarInfo->SaveSocket[index01][2] % 1000000000));
			strcat(SaveSocket, tempString01);
		}
		ZeroMemory(tempString01, sizeof(tempString01));
		sprintf(mQUERY_FOR_THREAD,
			"update %s set uSaveMoney=%d,uSaveItem='%s',SeyisBar=%d ,SaveSocket='%s'"
			"where uID='%s' AND aWorldNumber = '%d'; "
			, mSERVER_INFO.mDB_1_Table07, tAvatarInfo->uSaveMoney
			, uSaveItem, tAvatarInfo->SeyisBar, SaveSocket, tID, g_env.world_num);

		return;
	case 2:
		aEquip[0] = '\0';
		for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM; index01++)
		{
			sprintf(tempString01, "%05d%03d%09d%08d", (tAvatarInfo->aEquip[index01][0] % 100000), (tAvatarInfo->aEquip[index01][1] % 1000), (tAvatarInfo->aEquip[index01][2] % 1000000000), (tAvatarInfo->aEquip[index01][3] % 100000000));
			strcat(aEquip, tempString01);
		}
		ZeroMemory(tempString01, sizeof(tempString01));
		EquipSocket[0] = '\0';
		for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM; index01++)
		{
			sprintf(tempString01, "%09d%09d%09d", (tAvatarInfo->EquipSocket[index01][0] % 1000000000), (tAvatarInfo->EquipSocket[index01][1] % 1000000000), (tAvatarInfo->EquipSocket[index01][2] % 1000000000));
			strcat(EquipSocket, tempString01);
		}
		ZeroMemory(tempString01, sizeof(tempString01));
		aInventory[0] = '\0';
		for (index01 = 0; index01 < 2; index01++)
		{
			for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
			{
				sprintf(tempString01, "%05d%01d%01d%03d%09d%08d", (tAvatarInfo->aInventory[index01][index02][0] % 100000), (tAvatarInfo->aInventory[index01][index02][1] % 10), (tAvatarInfo->aInventory[index01][index02][2] % 10), (tAvatarInfo->aInventory[index01][index02][3] % 1000), (tAvatarInfo->aInventory[index01][index02][4] % 1000000000), (tAvatarInfo->aInventory[index01][index02][5] % 100000000));
				strcat(aInventory, tempString01);
			}
		}
		ZeroMemory(tempString01, sizeof(tempString01));
		InventorySocket[0] = '\0';
		for (index01 = 0; index01 < 2; index01++)
		{
			for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
			{
				sprintf(tempString01, "%09d%09d%09d", (tAvatarInfo->InventorySocket[index01][index02][0] % 1000000000), (tAvatarInfo->InventorySocket[index01][index02][1] % 1000000000), (tAvatarInfo->InventorySocket[index01][index02][2] % 1000000000));
				strcat(InventorySocket, tempString01);
			}
		}
		ZeroMemory(tempString01, sizeof(tempString01));
		aTrade[0] = '\0';
		for (index01 = 0; index01 < MAX_TRADE_SLOT_NUM; index01++)
		{
			sprintf(tempString01, "%05d%03d%09d%08d", (tAvatarInfo->aTrade[index01][0] % 100000), (tAvatarInfo->aTrade[index01][1] % 1000), (tAvatarInfo->aTrade[index01][2] % 1000000000), (tAvatarInfo->aTrade[index01][3] % 100000000));
			strcat(aTrade, tempString01);
		}
		ZeroMemory(tempString01, sizeof(tempString01));
		aStoreItem[0] = '\0';
		for (index01 = 0; index01 < 2; index01++)
		{
			for (index02 = 0; index02 < MAX_STORE_ITEM_SLOT_NUM; index02++)
			{
				sprintf(tempString01, "%05d%03d%09d%08d", (tAvatarInfo->aStoreItem[index01][index02][0] % 100000), (tAvatarInfo->aStoreItem[index01][index02][1] % 1000), (tAvatarInfo->aStoreItem[index01][index02][2] % 1000000000), (tAvatarInfo->aStoreItem[index01][index02][3] % 100000000));
				strcat(aStoreItem, tempString01);
			}
		}
		ZeroMemory(tempString01, sizeof(tempString01));
		StoreSocket[0] = '\0';
		for (index01 = 0; index01 < 2; index01++)
		{
			for (index02 = 0; index02 < MAX_STORE_ITEM_SLOT_NUM; index02++)
			{
				sprintf(tempString01, "%09d%09d%09d", (tAvatarInfo->StoreSocket[index01][index02][0] % 1000000000), (tAvatarInfo->StoreSocket[index01][index02][1] % 1000000000), (tAvatarInfo->StoreSocket[index01][index02][2] % 1000000000));
				strcat(StoreSocket, tempString01);
			}
		}
		ZeroMemory(tempString01, sizeof(tempString01));
		aSkill[0] = '\0';
		for (index01 = 0; index01 < MAX_SKILL_SLOT_NUM; index01++)
		{
			sprintf(tempString01, "%03d%03d", (tAvatarInfo->aSkill[index01][0] % 1000), (tAvatarInfo->aSkill[index01][1] % 1000));
			strcat(aSkill, tempString01);
		}
		ZeroMemory(tempString01, sizeof(tempString01));
		aHotKey[0] = '\0';
		for (index01 = 0; index01 < 3; index01++)
		{
			for (index02 = 0; index02 < MAX_HOT_KEY_NUM; index02++)
			{
				sprintf(tempString01, "%05d%03d%02d", (tAvatarInfo->aHotKey[index01][index02][0] % 100000), (tAvatarInfo->aHotKey[index01][index02][1] % 1000), (tAvatarInfo->aHotKey[index01][index02][2] % 100));
				strcat(aHotKey, tempString01);
			}
		}
		ZeroMemory(tempString01, sizeof(tempString01));
		aQuestInfo[0] = '\0';
		sprintf(tempString01, "%05d%05d%05d%05d%05d", (tAvatarInfo->aQuestInfo[0] % 100000), (tAvatarInfo->aQuestInfo[1] % 100000), (tAvatarInfo->aQuestInfo[2] % 100000), (tAvatarInfo->aQuestInfo[3] % 100000), (tAvatarInfo->aQuestInfo[4] % 100000));
		strcat(aQuestInfo, tempString01);
		//FillMemory( &aFriend[0], ( MAX_FRIEND_NUM * ( MAX_AVATAR_NAME_LENGTH - 1 ) ), '@' );
		ZeroMemory(tempString01, sizeof(tempString01));
		memset(aFriend, '@', (MAX_FRIEND_NUM * (MAX_AVATAR_NAME_LENGTH - 1)));
		for (index01 = 0; index01 < MAX_FRIEND_NUM; index01++)
		{
			CopyMemory(&aFriend[(index01 * 12 + 0)], &tAvatarInfo->aFriend[index01][0], strlen(tAvatarInfo->aFriend[index01]));
		}
		aFriend[120] = '\0';

		AutoBuff[0] = '\0';
		for (index01 = 0; index01 < MAX_AUTOBUFF_SKİLL; index01++)
		{
			sprintf(tempString01, "%03d%03d", (tAvatarInfo->AutoBuffSmenu[index01][0] % 1000), (tAvatarInfo->AutoBuffSmenu[index01][1] % 1000));
			strcat(AutoBuff, tempString01);
		}
		ZeroMemory(tempString01, sizeof(tempString01));
		AnimalExp[0] = '\0';
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			sprintf(tempString01, "%09d", (tAvatarInfo->AnimalExp[index01] % 1000000000));
			strcat(AnimalExp, tempString01);
		}
		ZeroMemory(tempString01, sizeof(tempString01));
		AnimalStat[0] = '\0';
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			sprintf(tempString01, "%09d", (tAvatarInfo->AnimalStat[index01] % 1000000000));
			strcat(AnimalStat, tempString01);
		}
		ZeroMemory(tempString01, sizeof(tempString01));
		PetInventory[0] = '\0';
		for (index01 = 0; index01 < 2; index01++)
		{
			for (index02 = 0; index02 < MAX_AVATAR_ANIMAL_NUM; index02++)
			{
				sprintf(tempString01, "%06d", (tAvatarInfo->PetInventoryTick[index01][index02] % 1000000));
				strcat(PetInventory, tempString01);
			}
		}
		ZeroMemory(tempString01, sizeof(tempString01));
		TradeSocket[0] = '\0';
		for (index01 = 0; index01 < MAX_TRADE_SLOT_NUM; index01++)
		{
			sprintf(tempString01, "%09d%09d%09d", (tAvatarInfo->TradeSocket[index01][0] % 1000000000), (tAvatarInfo->TradeSocket[index01][1] % 1000000000), (tAvatarInfo->TradeSocket[index01][2] % 1000000000));
			strcat(TradeSocket, tempString01);
		}
		ZeroMemory(tempString01, sizeof(tempString01));
		::memset(aAutoConfig, 0, 82);

		::snprintf(aAutoConfig, 82,
			"%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d"
			"%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d"
			"%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d"
			"%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d"
			"%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d"
			"%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d"
			"%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d"
			"%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d"
			"%03d"
			, tAvatarInfo->AutoHunt.BuffType
			, tAvatarInfo->AutoHunt.HuntBuff[0][0]
			, tAvatarInfo->AutoHunt.HuntBuff[0][1]
			, tAvatarInfo->AutoHunt.HuntBuff[1][0]
			, tAvatarInfo->AutoHunt.HuntBuff[1][1]
			, tAvatarInfo->AutoHunt.HuntBuff[2][0]
			, tAvatarInfo->AutoHunt.HuntBuff[2][1]
			, tAvatarInfo->AutoHunt.HuntBuff[3][0]
			, tAvatarInfo->AutoHunt.HuntBuff[3][1]
			, tAvatarInfo->AutoHunt.HuntBuff[4][0]
			, tAvatarInfo->AutoHunt.HuntBuff[4][1]
			, tAvatarInfo->AutoHunt.HuntBuff[5][0]
			, tAvatarInfo->AutoHunt.HuntBuff[5][1]
			, tAvatarInfo->AutoHunt.HuntBuff[6][0]
			, tAvatarInfo->AutoHunt.HuntBuff[6][1]
			, tAvatarInfo->AutoHunt.HuntBuff[7][0]
			, tAvatarInfo->AutoHunt.HuntBuff[7][1]
			, tAvatarInfo->AutoHunt.HuntType
			, tAvatarInfo->AutoHunt.AtakType[0][0]
			, tAvatarInfo->AutoHunt.AtakType[0][1]
			, tAvatarInfo->AutoHunt.AtakType[1][0]
			, tAvatarInfo->AutoHunt.AtakType[1][1]
			, tAvatarInfo->AutoHunt.OfMonster
			, tAvatarInfo->AutoHunt.HuntPickUp
			, tAvatarInfo->AutoHunt.HuntInsuficcent
			, tAvatarInfo->AutoHunt.HuntPetFood
			, tAvatarInfo->AutoHunt.HuntPetFood);

		char tempQuery[100000];

		strcpy(mQUERY_FOR_THREAD, "UPDATE AvatarInfo SET ");
		sprintf(tempQuery, "aVisibleState = %d, ", tAvatarInfo->aVisibleState);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aSpecialState = %d, ", tAvatarInfo->aSpecialState);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aPlayTime1 = %d, ", tAvatarInfo->aPlayTime1);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aPlayTime2 = %d, ", tAvatarInfo->aPlayTime2);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aKillOtherTribe = %d, ", tAvatarInfo->aKillOtherTribe);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aworldnumber = 1, ", 1); //aworldnumber
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aName = '%s', ", tAvatarInfo->aName);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aTribe = %d, ", tAvatarInfo->aTribe);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aPreviousTribe = %d, ", tAvatarInfo->aPreviousTribe);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aGender = %d, ", tAvatarInfo->aGender);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aHeadType = %d, ", tAvatarInfo->aHeadType);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aFaceType = %d, ", tAvatarInfo->aFaceType);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aLevel1 = %d, ", tAvatarInfo->aLevel1);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aLevel2 = %d, ", tAvatarInfo->aLevel2);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aGeneralExperience1 = %d, ", tAvatarInfo->aGeneralExperience1);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aGeneralExperience2 = %d, ", tAvatarInfo->aGeneralExperience2);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aVitality = %d, ", tAvatarInfo->aVitality);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aStrength = %d, ", tAvatarInfo->aStrength);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aKi = %d, ", tAvatarInfo->aKi);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aWisdom = %d, ", tAvatarInfo->aWisdom);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aEatLifePotion = %d, ", tAvatarInfo->aEatLifePotion);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aEatManaPotion = %d, ", tAvatarInfo->aEatManaPotion);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "StrElx = %d, ", tAvatarInfo->StrElx);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "AgiElx = %d, ", tAvatarInfo->AgiElx);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "AttAtakElixir = %d, ", (tAvatarInfo->YeniElx / 1000));
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "AttDefElixir = %d, ",  (tAvatarInfo->YeniElx % 1000));
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aStateBonusPoint = %d, ", tAvatarInfo->aStateBonusPoint);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aSkillPoint = %d, ", tAvatarInfo->aSkillPoint);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aEquip = '%s', ", aEquip);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aExpandInventoryDate = %d, ", tAvatarInfo->aExpandInventoryDate);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aMoney = %d, ", tAvatarInfo->aMoney);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aInventory = '%s', ", aInventory);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aTradeMoney = %d, ", tAvatarInfo->aTradeMoney);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aTrade = '%s', ", aTrade);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aExpandStoreDate = %d, ", tAvatarInfo->aExpandStoreDate);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aStoreMoney = %d, ", tAvatarInfo->aStoreMoney);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aStoreItem = '%s', ", aStoreItem);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aSkill = '%s', ", aSkill);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aHotKey = '%s', ", aHotKey);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aQuestInfo = '%s', ", aQuestInfo);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aFriend = '%s', ", aFriend);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aTeacher = '%s', ", tAvatarInfo->aTeacher);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aStudent = '%s', ", tAvatarInfo->aStudent);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aTeacherPoint = %d, ", tAvatarInfo->aTeacherPoint);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aGuildName = '%s', ", tAvatarInfo->aGuildName);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aGuildRole = %d, ", tAvatarInfo->aGuildRole);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aCallName = '%s', ", tAvatarInfo->aCallName);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aGuildMarkNum = %d, ", tAvatarInfo->aGuildMarkNum);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aGuildMarkEffect = %d, ", tAvatarInfo->aGuildMarkEffect);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aLogoutInfo01 = %d, ", tAvatarInfo->aLogoutInfo[0]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aLogoutInfo02 = %d, ", tAvatarInfo->aLogoutInfo[1]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aLogoutInfo03 = %d, ", tAvatarInfo->aLogoutInfo[2]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aLogoutInfo04 = %d, ", tAvatarInfo->aLogoutInfo[3]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aLogoutInfo05 = %d, ", tAvatarInfo->aLogoutInfo[4]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aLogoutInfo06 = %d, ", tAvatarInfo->aLogoutInfo[5]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "ProtectionScroll = %d, ", tAvatarInfo->ProtectionScroll);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "ProtectionCharm = %d, ", tAvatarInfo->ProtectionCharm);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "HolyWater = %d, ", tAvatarInfo->HolyWater);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "SuperiorPill = %d, ", tAvatarInfo->SuperiorPill);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "ScrollofLoyality = %d, ", tAvatarInfo->ScrollofLoyality);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "ScrollofBattle = %d, ", tAvatarInfo->ScrollofBattle);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "GodTempleKey = %d, ", tAvatarInfo->GodTempleKey);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "SolemGrounds = %d, ", tAvatarInfo->SolemGrounds);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "EdgeOfTaiyan = %d, ", tAvatarInfo->EdgeOfTaiyan);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "ScrollOfSeekers = %d, ", tAvatarInfo->ScrollOfSeekers);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aKillMonsterNum = %d, ", tAvatarInfo->aKillMonsterNum);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "RankPoint = %d, ", tAvatarInfo->RankPoint);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "RankPrize = %d, ", tAvatarInfo->RankPrize);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aSearch = %d, ", tAvatarInfo->aSearch);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "ExchangeHealtiks = %d, ", tAvatarInfo->ExchangeHealtiks);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "ExchangeChiiks = %d, ", tAvatarInfo->ExchangeChiiks);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aTribeVoteDate = %d, ", tAvatarInfo->aTribeVoteDate);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "HealtAutoPot = %d, ", tAvatarInfo->HealtAutoPot);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "ManaAutoPot = %d, ", tAvatarInfo->ManaAutoPot);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aAnimal01 = %d, ", tAvatarInfo->aAnimal[0]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aAnimal02 = %d, ", tAvatarInfo->aAnimal[1]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aAnimal03 = %d, ", tAvatarInfo->aAnimal[2]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aAnimal04 = %d, ", tAvatarInfo->aAnimal[3]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aAnimal05 = %d, ", tAvatarInfo->aAnimal[4]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aAnimal06 = %d, ", tAvatarInfo->aAnimal[5]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aAnimal07 = %d, ", tAvatarInfo->aAnimal[6]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aAnimal08 = %d, ", tAvatarInfo->aAnimal[7]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aAnimal09 = %d, ", tAvatarInfo->aAnimal[8]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aAnimal10 = %d, ", tAvatarInfo->aAnimal[9]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aAnimalIndex = %d, ", tAvatarInfo->aAnimalIndex);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aAnimalTime = %d, ", tAvatarInfo->aAnimalTime);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "LuckyCombine = %d, ", tAvatarInfo->LuckyCombine);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "LuckyUpgrade = %d, ", tAvatarInfo->LuckyUpgrade);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "LuckyDrop = %d, ", tAvatarInfo->LuckyDrop);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Title = %d, ", tAvatarInfo->Title);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "ExtinctionScroll = %d, ", tAvatarInfo->ExtinctionScroll);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aUpradgeValue = %d, ", tAvatarInfo->aUpradgeValue);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Beginner = %d, ", tAvatarInfo->Beginner);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "BeginnerLevel = %d, ", tAvatarInfo->BeginnerLevel);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OnlineHour = %d, ", tAvatarInfo->OnlineHour);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Cppc = %d, ", tAvatarInfo->Cppc);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "iUseOrnament = %d, ", tAvatarInfo->iUseOrnament);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "iSilverOrnamentRemainsTime = %d, ", tAvatarInfo->iSilverOrnamentRemainsTime);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "IslandOfBlood = %d, ", tAvatarInfo->IslandOfBlood);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "IslandOfSoulMReal1 = %d, ", tAvatarInfo->IslandOfSoulMReal1);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "IslandOfSoulMReal2 = %d, ", tAvatarInfo->IslandOfSoulMReal2);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "IslandOfSoulMReal3 = %d, ", tAvatarInfo->IslandOfSoulMReal3);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "IslandOfSoulMReal4 = %d, ", tAvatarInfo->IslandOfSoulMReal4);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "IslandOfSoulMReal5 = %d, ", tAvatarInfo->IslandOfSoulMReal5);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "IslandOfSoulMReal6 = %d, ", tAvatarInfo->IslandOfSoulMReal6);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "SkillIncreaseCritHit = %d, ", tAvatarInfo->SkillIncreaseCritHit);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "LifeOrDeath = %d, ", tAvatarInfo->LifeOrDeath);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "iGoldOrnamentRemainsTime = %d, ", tAvatarInfo->iGoldOrnamentRemainsTime);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "BloodBoost = %d, ", tAvatarInfo->BloodBoost);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "SoulBoost = %d, ", tAvatarInfo->SoulBoost);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Registration = %d, ", tAvatarInfo->Registration);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "ExpPill = %d, ", tAvatarInfo->ExpPill);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "FactReturnScroll = %d, ", tAvatarInfo->FactReturnScroll);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "PetExpBoost = %d, ", tAvatarInfo->PetExpBoost);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Costume1 = %d, ", tAvatarInfo->Costume[0]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Costume2 = %d, ", tAvatarInfo->Costume[1]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Costume3 = %d, ", tAvatarInfo->Costume[2]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Costume4 = %d, ", tAvatarInfo->Costume[3]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Costume5 = %d, ", tAvatarInfo->Costume[4]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Costume6 = %d, ", tAvatarInfo->Costume[5]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Costume7 = %d, ", tAvatarInfo->Costume[6]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Costume8 = %d, ", tAvatarInfo->Costume[7]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Costume9 = %d, ", tAvatarInfo->Costume[8]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Costume10 = %d, ", tAvatarInfo->Costume[9]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "CostumeInventory1 = %d, ", tAvatarInfo->CostumeInventory[0]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "CostumeInventory2 = %d, ", tAvatarInfo->CostumeInventory[1]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "CostumeInventory3 = %d, ", tAvatarInfo->CostumeInventory[2]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "CostumeInventory4 = %d, ", tAvatarInfo->CostumeInventory[3]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "CostumeInventory5 = %d, ", tAvatarInfo->CostumeInventory[4]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "CostumeInventory6 = %d, ", tAvatarInfo->CostumeInventory[5]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "CostumeInventory7 = %d, ", tAvatarInfo->CostumeInventory[6]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "CostumeInventory8 = %d, ", tAvatarInfo->CostumeInventory[7]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "CostumeInventory9 = %d, ", tAvatarInfo->CostumeInventory[8]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "CostumeInventory10 = %d, ", tAvatarInfo->CostumeInventory[9]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "SelectCostume = %d, ", tAvatarInfo->SelectCostume);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "DamegeBoostScroll = %d, ", tAvatarInfo->DamegeBoostScroll);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "HealtBoostScroll = %d, ", tAvatarInfo->HealtBoostScroll);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "CritBoostScroll = %d, ", tAvatarInfo->CritBoostScroll);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "AutoBuffScroll = %d, ", tAvatarInfo->AutoBuffScroll);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "AutoBuffSmenu = '%s', ", AutoBuff);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "FishBread = %d, ", tAvatarInfo->Hisar);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "SweetPateto = %d, ", tAvatarInfo->SweetPateto);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "InventorySocket = '%s', ", InventorySocket);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "EquipSocket = '%s', ", EquipSocket);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "TradeSocket = '%s', ", TradeSocket);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "StoreSocket = '%s', ", StoreSocket);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Hunt7d = %d, ", tAvatarInfo->Hunt7d);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Hunt5h = %d, ", tAvatarInfo->Hunt5h);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Inventorybar = %d, ", tAvatarInfo->Inventorybar);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "TradeBar = %d, ", tAvatarInfo->TradeBar);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "BankBar = %d, ", tAvatarInfo->BankBar);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "RebirtHall = %d, ", tAvatarInfo->RebirtHall);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "PreServeCharm = %d, ", tAvatarInfo->PreServeCharm);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Chenjoho = %d, ", tAvatarInfo->Chenjoho);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aRankPoint = %d, ", tAvatarInfo->aRankPoint);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "aRank = %d, ", tAvatarInfo->aRank);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "FanctionNoticeScroll = %d, ", tAvatarInfo->FanctionNoticeScroll);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "AnimalExp = '%s', ", AnimalExp);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "AnimalStat = '%s', ", AnimalStat);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "DoubleMouthExp2x = %d, ", tAvatarInfo->DoubleMouthExp2x);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "VigilanteScroll = %d, ", tAvatarInfo->VigilanteScroll);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "RafflaTicket = %d, ", tAvatarInfo->RafflaTicket);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "MountAbsorb = %d, ", tAvatarInfo->MountAbsorb);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "MountAbsorbe = %d, ", tAvatarInfo->MountAbsorbe);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "BurstPill = %d, ", tAvatarInfo->BurstPill);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "RagePill = %d, ", tAvatarInfo->RagePill);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "WarriorScroll = %d, ", tAvatarInfo->WarriorScroll);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "HeroPill = %d, ", tAvatarInfo->HeroPill);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "WingProtectionRune = %d, ", tAvatarInfo->WingProtectionRune);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "LessDecressScroll = %d, ", tAvatarInfo->LessDecressScroll);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "PetInventory = %d, ", tAvatarInfo->PetInventory);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "PetInventoryTick = '%s', ", PetInventory);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "JoinWar = %d, ", tAvatarInfo->JoinWar);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "PlayerKill = %d, ", tAvatarInfo->PlayerKill);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "MonsterKill = %d, ", tAvatarInfo->MonsterKill);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "PlayTimeDay = %d, ", tAvatarInfo->PlayTimeDay);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "AutoHuntConfing = '%s', ", aAutoConfig);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "BloodStained = %d, ", tAvatarInfo->BloodStained);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "FishingTime = %d, ", tAvatarInfo->FishingTime);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "BottleIndex = %d, ", tAvatarInfo->BottleIndex);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "BottleTime = %d, ", tAvatarInfo->BottleTime);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Bottle1 = %d, ", tAvatarInfo->Bottle[0]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Bottle2 = %d, ", tAvatarInfo->Bottle[1]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Bottle3 = %d, ", tAvatarInfo->Bottle[2]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Bottle4 = %d, ", tAvatarInfo->Bottle[3]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Bottle5 = %d, ", tAvatarInfo->Bottle[4]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Bottle6 = %d, ", tAvatarInfo->Bottle[5]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Bottle7 = %d, ", tAvatarInfo->Bottle[6]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Bottle8 = %d, ", tAvatarInfo->Bottle[7]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Bottle9 = %d, ", tAvatarInfo->Bottle[8]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Bottle10 = %d, ", tAvatarInfo->Bottle[9]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "BottlePrice1 = %d, ", tAvatarInfo->BottlePrice[0]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "BottlePrice2 = %d, ", tAvatarInfo->BottlePrice[1]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "BottlePrice3 = %d, ", tAvatarInfo->BottlePrice[2]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "BottlePrice4 = %d, ", tAvatarInfo->BottlePrice[3]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "BottlePrice5 = %d, ", tAvatarInfo->BottlePrice[4]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "BottlePrice6 = %d, ", tAvatarInfo->BottlePrice[5]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "BottlePrice7 = %d, ", tAvatarInfo->BottlePrice[6]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "BottlePrice8 = %d, ", tAvatarInfo->BottlePrice[7]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "BottlePrice9 = %d, ", tAvatarInfo->BottlePrice[8]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "BottlePrice10 = %d, ", tAvatarInfo->BottlePrice[9]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OtherSkill1 = %d, ", tAvatarInfo->OtherSkill[0]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OtherSkill2 = %d, ", tAvatarInfo->OtherSkill[1]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OtherSkill3 = %d, ", tAvatarInfo->OtherSkill[2]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OtherSkill4 = %d, ", tAvatarInfo->OtherSkill[3]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OtherSkill5 = %d, ", tAvatarInfo->OtherSkill[4]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OtherSkill6 = %d, ", tAvatarInfo->OtherSkill[5]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OtherSkill7 = %d, ", tAvatarInfo->OtherSkill[6]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OtherSkill8 = %d, ", tAvatarInfo->OtherSkill[7]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OtherSkill9 = %d, ", tAvatarInfo->OtherSkill[8]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OtherSkill10 = %d, ", tAvatarInfo->OtherSkill[9]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OtherSkill11 = %d, ", tAvatarInfo->OtherSkill[10]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OtherSkill12 = %d, ", tAvatarInfo->OtherSkill[11]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OtherSkill13 = %d, ", tAvatarInfo->OtherSkill[12]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OtherSkill14 = %d, ", tAvatarInfo->OtherSkill[13]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OtherSkillState11 = %d, ", tAvatarInfo->OtherSkillState1[0]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OtherSkillState12 = %d, ", tAvatarInfo->OtherSkillState1[1]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OtherSkillState13 = %d, ", tAvatarInfo->OtherSkillState1[2]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OtherSkillState14 = %d, ", tAvatarInfo->OtherSkillState1[3]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OtherSkillState15 = %d, ", tAvatarInfo->OtherSkillState1[4]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OtherSkillState16 = %d, ", tAvatarInfo->OtherSkillState1[5]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OtherSkillState17 = %d, ", tAvatarInfo->OtherSkillState1[6]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OtherSkillState18 = %d, ", tAvatarInfo->OtherSkillState1[7]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OtherSkillState19 = %d, ", tAvatarInfo->OtherSkillState1[8]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OtherSkillState110 = %d, ", tAvatarInfo->OtherSkillState1[9]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OtherSkillState111 = %d, ", tAvatarInfo->OtherSkillState1[10]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OtherSkillState112 = %d, ", tAvatarInfo->OtherSkillState1[11]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OtherSkillState113 = %d, ", tAvatarInfo->OtherSkillState1[12]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OtherSkillState114 = %d, ", tAvatarInfo->OtherSkillState1[13]);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "OtherSkillSolUst = %d, ", tAvatarInfo->OtherSkillSolUst);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Fury = %d, ", tAvatarInfo->Fury);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "Premium = %d, ", tAvatarInfo->Premium);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "HideCostumeRegister = %d, ", tAvatarInfo->HideCostumeRegister);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "BuffDurationPill = %d ", tAvatarInfo->BuffDurationPill);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "where aName = '%s' ", tAvatarInfo->aName);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		sprintf(tempQuery, "AND aWorldNumber = %d;", g_env.world_num);
		strcat(mQUERY_FOR_THREAD, tempQuery);
		return;
	case 3:
		sprintf(mQUERY_FOR_THREAD, "update %s set uLoginState=0, uUpdateTime=now() where uID='%s'; "
			, mSERVER_INFO.mDB_2_Table01, tID);
		return;
	default:
		strcpy(mQUERY_FOR_THREAD, "");
		return;
	}
}
//DB_PROCESS_01
BOOL MyDB::DB_PROCESS_01(char tID[MAX_USER_ID_LENGTH], char* tIp)
{
	int iAffected;
	//long uLoginState;
	//__LogMgr()->Log("10dk yedi 2 %d %d", uLoginState,tID);

	sprintf(mQUERY, "update %s set uLoginState=1,uUpdateTime=now(),uIP='%s' where uID='%s'; "
		, mSERVER_INFO.mDB_2_Table01, tIp, tID);
	if (!RECONNECT_TO_DATABASE02())
	{
		return FALSE;
	}
	iAffected = 0;

	if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		return FALSE;
	}
#ifdef __COMMIT__
	if (mDB02.exec_query("commit", CMySQL::CLEAR) != 0) {
		return FALSE;
	}
#endif

	return TRUE;
}
//DB_PROCESS_02
BOOL MyDB::DB_PROCESS_02(char tID[MAX_USER_ID_LENGTH])
{
	int iAffected;
	//long uLoginState;
	//__LogMgr()->Log("10dk yedi 2 %s %s %d", uLoginState, tID[MAX_USER_ID_LENGTH], tID[MAX_USER_ID_LENGTH]);

	sprintf(mQUERY, "update %s set uLoginState=0, uUpdateTime=now() where uID='%s'; ", mSERVER_INFO.mDB_2_Table01, tID);
	if (!RECONNECT_TO_DATABASE02())
	{
		WRITE_FOR_DB_LOG_FOR_QUERY();
		return FALSE;
	}
	iAffected = 0;

	if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		WRITE_FOR_DB_LOG_FOR_QUERY();
		return FALSE;
	}
#ifdef __COMMIT__
	if (mDB02.exec_query("commit", CMySQL::CLEAR) != 0) {
		WRITE_FOR_DB_LOG_FOR_QUERY();
		return FALSE;
	}
#endif

	return TRUE;
}
//DB_PROCESS_03
BOOL MyDB::DB_PROCESS_03(int tSort, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO* tAvatarInfo, AUTH_INFO* tAuthInfo, int tLoginPremiumPCRoom)
{
	int iAffected;
	int iCounts;
	long tAvatarNameNum;
	long tIDNum;
	char tQuery[100000];
	MYSQL_ROW row;
	MYSQL_RES* res = NULL;

	MakeQueryForSave(1, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
	if (!RECONNECT_TO_DATABASE01_FOR_THREAD())
	{
		MakeQueryForSave(1, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave(2, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave(3, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		return FALSE;
	}
	iAffected = 0;

	if (mDB01_FOR_THREAD.exec_query(mQUERY_FOR_THREAD, CMySQL::CLEAR) != 0) {
		__LogMgr()->Log("![%s] : %s - [%d]\n", __FUNCTION__, mDB01_FOR_THREAD.get_error_msg().c_str(), __LINE__);
		MakeQueryForSave(1, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave(2, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave(3, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		return FALSE;
	}
#ifdef __COMMIT__
	if (mDB01_FOR_THREAD.exec_query("commit", CMySQL::CLEAR) != 0) {
		return FALSE;
	}
#endif
	//__LogMgr()->Log("====> 1 result %s\n", mDB02_FOR_THREAD.get_error_msg().c_str());

	MakeQueryForSave(2, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);

	if (!RECONNECT_TO_DATABASE01_FOR_THREAD())
	{
		MakeQueryForSave(1, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave(2, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave(3, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		return FALSE;
	}
	iAffected = 0;
	if (mDB01_FOR_THREAD.exec_query(mQUERY_FOR_THREAD, CMySQL::CLEAR) != 0) {
		__LogMgr()->Log("![%s] : %s - [%d]\n", __FUNCTION__, mDB01_FOR_THREAD.get_error_msg().c_str(), __LINE__);
		MakeQueryForSave(1, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave(2, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave(3, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		return FALSE;
	}
#ifdef __COMMIT__
	if (mDB01_FOR_THREAD.exec_query("commit", CMySQL::CLEAR) != 0) {
		return FALSE;
	}
#endif

	sprintf(mQUERY_FOR_THREAD, "SELECT count(uID) FROM %s WHERE uID='%s';", mSERVER_INFO.mDB_2_Table02, tID);
	//__LogMgr()->Log("====> 5 %s\n", mQUERY_FOR_THREAD);
	if (!RECONNECT_TO_DATABASE02_FOR_THREAD())
	{
		MakeQueryForSave(1, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave(2, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave(3, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		return FALSE;
	}
	iAffected = 0;
	if ((iAffected = mDB02_FOR_THREAD.exec_query(mQUERY_FOR_THREAD)) < 0) {
		__LogMgr()->Log("![%s] : %s - [%d]\n", __FUNCTION__, mDB02_FOR_THREAD.get_error_msg().c_str(), __LINE__);
		MakeQueryForSave(1, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave(2, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave(3, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		return FALSE;
	}
	iCounts = 0;
	res = mDB02_FOR_THREAD.get_res();
	if (res == NULL) {
		return false;
	}
	while ((row = mysql_fetch_row(res))) {
		tIDNum = atol(row[0]);
		iCounts++;
	}
	mDB02_FOR_THREAD.clear_res();

	if (iCounts != 1) {
		__LogMgr()->Log("![%s] : %s - [%d]\n", __FUNCTION__, mDB02_FOR_THREAD.get_error_msg().c_str(), __LINE__);
		MakeQueryForSave(1, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave(2, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave(3, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		return FALSE;
	}

	if (tIDNum == 0)
	{
		sprintf(mQUERY_FOR_THREAD,
			"insert into %s values ('%s',%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d);"
			, mSERVER_INFO.mDB_2_Table02, tID,
			tAuthInfo->AuthType, tAuthInfo->FindFlag, tAuthInfo->MoveFlag, tAuthInfo->MoveZoneFlag, tAuthInfo->CallFlag,
			tAuthInfo->HideFlag, tAuthInfo->ShowFlag, tAuthInfo->KickFlag, tAuthInfo->BlockFlag, tAuthInfo->MonCallFlag, tAuthInfo->EquipFlag,
			tAuthInfo->UnequipFlag, tAuthInfo->YchatFlag, tAuthInfo->NchatFlag, tAuthInfo->NoticeFlag, tAuthInfo->ItemFlag, tAuthInfo->MoneyFlag,
			tAuthInfo->ExpFlag, tAuthInfo->DieFlag, tAuthInfo->GodFlag, tAuthInfo->ChatFlag, tAuthInfo->TradeFlag, tAuthInfo->ShopFlag,
			tAuthInfo->PShopFlag, tAuthInfo->GItemFlag, tAuthInfo->DItemFlag, tAuthInfo->AttackFlag, tAuthInfo->UZonemoveFlag, tAuthInfo->DailyRewardTime, tAuthInfo->Explock);
	}
	else
	{
		sprintf(mQUERY_FOR_THREAD,
			"update %s set AuthType=%d,FindFlag=%d,MoveFlag=%d,MoveZoneFlag=%d,CallFlag=%d,HideFlag=%d,ShowFlag=%d,KickFlag=%d,BlockFlag=%d,MonCallFlag=%d"
			",EquipFlag=%d,UnequipFlag=%d,YchatFlag=%d,NchatFlag=%d,NoticeFlag=%d,ItemFlag=%d,MoneyFlag=%d,ExpFlag=%d,DieFlag=%d,GodFlag=%d,ChatFlag=%d"
			",TradeFlag=%d,ShopFlag=%d,PShopFlag=%d,GItemFlag=%d,DItemFlag=%d,AttackFlag=%d,UZonemoveFlag=%d,DailyRewardTime=%d,Explock=%d"
			" where uID='%s';"
			, mSERVER_INFO.mDB_2_Table02, tAuthInfo->AuthType, tAuthInfo->FindFlag, tAuthInfo->MoveFlag, tAuthInfo->MoveZoneFlag, tAuthInfo->CallFlag,
			tAuthInfo->HideFlag, tAuthInfo->ShowFlag, tAuthInfo->KickFlag, tAuthInfo->BlockFlag, tAuthInfo->MonCallFlag, tAuthInfo->EquipFlag,
			tAuthInfo->UnequipFlag, tAuthInfo->YchatFlag, tAuthInfo->NchatFlag, tAuthInfo->NoticeFlag, tAuthInfo->ItemFlag, tAuthInfo->MoneyFlag,
			tAuthInfo->ExpFlag, tAuthInfo->DieFlag, tAuthInfo->GodFlag, tAuthInfo->ChatFlag, tAuthInfo->TradeFlag, tAuthInfo->ShopFlag,
			tAuthInfo->PShopFlag, tAuthInfo->GItemFlag, tAuthInfo->DItemFlag, tAuthInfo->AttackFlag, tAuthInfo->UZonemoveFlag, tAuthInfo->DailyRewardTime, tAuthInfo->Explock,
			tID);
	}
	//__LogMgr()->Log("query [%s]\n",mQUERY_FOR_THREAD);
	CopyMemory(tQuery, mQUERY_FOR_THREAD, sizeof(mQUERY_FOR_THREAD));
	//__LogMgr()->Log("====> 6 %s\n", mQUERY_FOR_THREAD);
	if (!RECONNECT_TO_DATABASE02_FOR_THREAD())
	{
		MakeQueryForSave(1, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave(2, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave(3, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		CopyMemory(mQUERY_FOR_THREAD, tQuery, sizeof(tQuery));
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		return FALSE;
	}
	iAffected = 0;

	if (mDB02_FOR_THREAD.exec_query(mQUERY_FOR_THREAD, CMySQL::CLEAR) != 0) {
		__LogMgr()->Log("![%s] : %s - [%d]\n", __FUNCTION__, mDB02_FOR_THREAD.get_error_msg().c_str(), __LINE__);
		MakeQueryForSave(1, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave(2, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		MakeQueryForSave(3, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		CopyMemory(mQUERY_FOR_THREAD, tQuery, sizeof(tQuery));
		WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
		return FALSE;
	}
#ifdef __COMMIT__
	if (mDB02_FOR_THREAD.exec_query("commit", CMySQL::CLEAR) != 0) {
		return FALSE;
	}
#endif
	//__LogMgr()->Log("====> 2 result %s\n", mDB02_FOR_THREAD.get_error_msg().c_str());
	if (tSort == 1) {
		/* MIR */
		MakeQueryForSave(3, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
		if (!RECONNECT_TO_DATABASE02_FOR_THREAD())
		{
			MakeQueryForSave(1, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
			WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
			MakeQueryForSave(2, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
			WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
			MakeQueryForSave(3, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
			WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
			//__LogMgr()->Log("====> 3-1 result %s\n", mDB01_FOR_THREAD.get_error_msg().c_str());
			return FALSE;
		}
		iAffected = 0;
		if (mDB02_FOR_THREAD.exec_query(mQUERY_FOR_THREAD, CMySQL::CLEAR) != 0) {
			__LogMgr()->Log("![%s] : %s - [%d]\n", __FUNCTION__, mDB02_FOR_THREAD.get_error_msg().c_str(), __LINE__);
			MakeQueryForSave(1, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
			WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
			MakeQueryForSave(2, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
			WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
			MakeQueryForSave(3, &tID[0], tAvatarInfo, tLoginPremiumPCRoom);
			WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD();
			//__LogMgr()->Log("!====> 3 result %s %s\n", mDB02_FOR_THREAD.get_error_msg().c_str(), mQUERY_FOR_THREAD);
			return FALSE;
		}
#ifdef __COMMIT__
		if (mDB02_FOR_THREAD.exec_query("commit", CMySQL::CLEAR) != 0) {
			return FALSE;
		}
#endif
	}
	if (tAvatarInfo->aLevel1 >= 113 && tAuthInfo->AuthType != 1)
	{
		sprintf(mQUERY_FOR_THREAD,
			"SELECT count(aName) "
			"FROM %s "
			"WHERE aName='%s' AND aWorldNumber = '%d' "
			, mSERVER_INFO.mDB_2_Table04
			, tAvatarInfo->aName
			, g_env.world_num);
		//__LogMgr()->Log("====> 5 %s\n", mQUERY_FOR_THREAD);
		if (!RECONNECT_TO_DATABASE01_FOR_THREAD())
		{
			return TRUE;
		}
		iAffected = 0;
		if ((iAffected = mDB01_FOR_THREAD.exec_query(mQUERY_FOR_THREAD)) < 0) {
			return TRUE;
		}
		iCounts = 0;
		res = mDB01_FOR_THREAD.get_res();
		if (res == NULL) {
			return false;
		}
		while ((row = mysql_fetch_row(res))) {
			tAvatarNameNum = atol(row[0]);
			iCounts++;
		}
		mDB01_FOR_THREAD.clear_res();
		if (iCounts != 1) {
			return TRUE;
		}

		if (tAvatarNameNum == 0)
		{
#ifdef __GOD__
			if (tAvatarInfo->aLevel2 < 1) {
#endif		
				sprintf(mQUERY_FOR_THREAD,
					"insert into %s values ( now(),now(),'%s','%d','%s',%d,%d,%d,%d,'%s',%d )"
					, mSERVER_INFO.mDB_2_Table04, tID
					, g_env.world_num, tAvatarInfo->aName
					, tAvatarInfo->aTribe, tAvatarInfo->aPreviousTribe
					, tAvatarInfo->aLevel1 + tAvatarInfo->aLevel2, tAvatarInfo->aGeneralExperience1
					, tAvatarInfo->aGuildName, tAvatarInfo->aKillOtherTribe);
#ifdef __GOD__
			}
			else {
				sprintf(mQUERY_FOR_THREAD,
					"insert into %s values ( now(),now(),'%s','%d','%s',%d,%d,%d,%d,'%s',%d )"
					, mSERVER_INFO.mDB_2_Table04, tID
					, g_env.world_num, tAvatarInfo->aName
					, tAvatarInfo->aTribe, tAvatarInfo->aPreviousTribe
					, tAvatarInfo->aLevel1 + tAvatarInfo->aLevel2, tAvatarInfo->aGeneralExperience2
					, tAvatarInfo->aGuildName, tAvatarInfo->aKillOtherTribe);
			}
#endif
		}
		else
		{
#ifdef __GOD__
			if (tAvatarInfo->aLevel2 < 1) {
#endif
				sprintf(mQUERY_FOR_THREAD,
					"update %s "
					"set aUpdateTime=now(),uID='%s',aTribe=%d,aPreviousTribe=%d "
					"	,aLevel=%d,aGeneralExperience=%d,aGuildName='%s',aKillOtherTribe=%d "
					"where aName='%s' AND aWorldNumber = '%d'; "
					, mSERVER_INFO.mDB_2_Table04, tID, tAvatarInfo->aTribe, tAvatarInfo->aPreviousTribe
					, tAvatarInfo->aLevel1 + tAvatarInfo->aLevel2, tAvatarInfo->aGeneralExperience1, tAvatarInfo->aGuildName
					, tAvatarInfo->aKillOtherTribe, tAvatarInfo->aName, g_env.world_num);
#ifdef __GOD__
			}
			else {

				sprintf(mQUERY_FOR_THREAD,
					"update %s "
					"set aUpdateTime=now(),uID='%s',aTribe=%d,aPreviousTribe=%d "
					"	,aLevel=%d,aGeneralExperience=%d,aGuildName='%s',aKillOtherTribe=%d "
					"where aName='%s' AND aWorldNumber = '%d'; "
					, mSERVER_INFO.mDB_2_Table04, tID, tAvatarInfo->aTribe, tAvatarInfo->aPreviousTribe
					, tAvatarInfo->aLevel1 + tAvatarInfo->aLevel2, tAvatarInfo->aGeneralExperience2, tAvatarInfo->aGuildName
					, tAvatarInfo->aKillOtherTribe, tAvatarInfo->aName, g_env.world_num);
			}
#endif
		}
		//__LogMgr()->Log("====> 6 %s\n", mQUERY_FOR_THREAD);
		if (!RECONNECT_TO_DATABASE01_FOR_THREAD())
		{
			return TRUE;
		}
		iAffected = 0;

		if (mDB01_FOR_THREAD.exec_query(mQUERY_FOR_THREAD, CMySQL::CLEAR) != 0) {
			__LogMgr()->Log("![%s] : %s - [%d]\n", __FUNCTION__, mDB01_FOR_THREAD.get_error_msg().c_str(), __LINE__);
			return TRUE;
		}
#ifdef __COMMIT__
		if (mDB01_FOR_THREAD.exec_query("commit", CMySQL::CLEAR) != 0) {
			return TRUE;
		}
#endif
	}
	return TRUE;
}
//DB_PROCESS_04
void MyDB::DB_PROCESS_04(char tID[MAX_USER_ID_LENGTH], char tHackName[MAX_HACK_NAME_LENGTH], int tHackSize, int* tResult)
{
	MYSQL_ROW row;
	MYSQL_RES* res;
	int iAffected;
	int iCounts;
	long hSize;

	sprintf(mQUERY, "select hSize from %s where hName='%s'", mSERVER_INFO.mDB_1_Table02, tHackName);
	if (!RECONNECT_TO_DATABASE01())
	{
		*tResult = 2;
		return;
	}
	iAffected = 0;
	if ((iAffected = mDB01.exec_query(mQUERY)) < 0) {
		*tResult = 2;
		return;
	}
	iCounts = 0;
	res = mDB01.get_res();
	if (res == NULL) {
		*tResult = 2;
		return;
	}
	while ((row = mysql_fetch_row(res))) {
		hSize = atol(row[0]);
		iCounts++;
	}

	mDB01.clear_res();

	if (iCounts != 1) {
		*tResult = 0;
		return;
	}
	if ((hSize > 0) && (hSize != (long)tHackSize))
	{
		*tResult = 0;
		return;
	}
	DB_PROCESS_07(&tID[0], 0, &tHackName[0]);
	*tResult = 1;
	return;
}
//DB_PROCESS_05
BOOL MyDB::DB_PROCESS_05(int tUserNum)
{
	int iAffected;

	sprintf(mQUERY, "update %s set mMaxUserNum=%d WHERE aWorldNumber = '%d'; "
		, mSERVER_INFO.mDB_1_Table01, tUserNum, g_env.world_num);
	if (!RECONNECT_TO_DATABASE02())
	{
		return FALSE;
	}
	iAffected = 0;
#ifdef __WIN32__
	if (!mDB02.Execute(mQUERY, iAffected))
	{
		return FALSE;
	}
#else
	if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		return FALSE;
	}
#ifdef __COMMIT__
	if (mDB02.exec_query("commit", CMySQL::CLEAR) != 0) {
		return FALSE;
	}
#endif
#endif

	return TRUE;
}
//DB_PROCESS_06
BOOL MyDB::DB_PROCESS_06(char tID[MAX_USER_ID_LENGTH], int tSort, char tHackName[MAX_HACK_NAME_LENGTH])
{
	int iAffected;

	sprintf(mQUERY, "update %s set uBlockInfo=99999999 where uID='%s'; ", mSERVER_INFO.mDB_2_Table01, tID);
	if (!RECONNECT_TO_DATABASE02())
	{
		return FALSE;
	}
	iAffected = 0;
	if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		return FALSE;
	}
	return TRUE;
}
//DB_PROCESS_07
BOOL MyDB::DB_PROCESS_07(char tID[MAX_USER_ID_LENGTH], int tSort, char tHackName[MAX_HACK_NAME_LENGTH])
{
	MYSQL_ROW row;
	MYSQL_RES* res;
	int iAffected;
	int iCounts;
	long tIDNum;

	sprintf(mQUERY, "insert into %s values ( now(),'%s',%d,'%s' )", mSERVER_INFO.mDB_1_Table04, tID, tSort, tHackName);
	if (!RECONNECT_TO_DATABASE01())
	{
		return FALSE;
	}
	iAffected = 0;
#ifdef __WIN32__
	if (!mDB01.Execute(mQUERY, iAffected))
	{
		return FALSE;
	}
#else
	if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		return FALSE;
	}
#ifdef __COMMIT__
	if (mDB01.exec_query("commit", CMySQL::CLEAR) != 0) {
		return FALSE;
	}
#endif
#endif
	sprintf(mQUERY, "select count(uID) from %s where uID='%s'", mSERVER_INFO.mDB_1_Table03, tID);
	if (!RECONNECT_TO_DATABASE01())
	{
		return FALSE;
	}
	iAffected = 0;
#ifdef __WIN32__
	if (!mDB01.ExecuteAndReceive(mQUERY, iAffected))
	{
		return FALSE;
	}
	iCounts = 0;
	if (!mDB01.GetResultCounts(iCounts))
	{
		return FALSE;
	}
	if (iCounts != 1)
	{
		return FALSE;
	}
	if (!mDB01.GetLong(0, tIDNum))
	{
		return FALSE;
	}
#else
	if ((iAffected = mDB01.exec_query(mQUERY)) < 0) {
		return TRUE;
	}
	iCounts = 0;
	res = mDB01.get_res();
	if (res == NULL) {
		return false;
	}
	while ((row = mysql_fetch_row(res))) {
		tIDNum = atol(row[0]);
		iCounts++;
	}
	mDB01.clear_res();

	if (iCounts != 1) {
		return TRUE;
	}
#endif
	if (tIDNum == 0)
	{
		sprintf(mQUERY, "insert into %s values ( now(),'%s',1 )", mSERVER_INFO.mDB_1_Table03, tID);
		if (!RECONNECT_TO_DATABASE01())
		{
			return FALSE;
		}
		iAffected = 0;
#ifdef __WIN32__
		if (!mDB01.Execute(mQUERY, iAffected))
		{
			return FALSE;
		}
#else
		if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			return TRUE;
		}
#ifdef __COMMIT__
		if (mDB01.exec_query("commit", CMySQL::CLEAR) != 0) {
			return TRUE;
		}
#endif
#endif
		return TRUE;
	}
	sprintf(mQUERY, "update %s set uWarningNum=uWarningNum+1 where uID='%s'; ", mSERVER_INFO.mDB_1_Table03, tID);
	if (!RECONNECT_TO_DATABASE01())
	{
		return FALSE;
	}
	iAffected = 0;
#ifdef __WIN32__
	if (!mDB01.Execute(mQUERY, iAffected))
	{
		return FALSE;
	}
#else
	if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		return TRUE;
	}
#ifdef __COMMIT__
	if (mDB01.exec_query("commit", CMySQL::CLEAR) != 0) {
		return TRUE;
	}
#endif
#endif
	return TRUE;
}
//DB_PROCESS_08
BOOL MyDB::DB_PROCESS_08(char tID[MAX_USER_ID_LENGTH], char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tWorldNumber, int tZoneNumber)
{
	int iAffected;

	sprintf(mQUERY, "insert into %s values ( now(),1,'%s','%s',%d,%d )", mSERVER_INFO.mDB_1_Table10, tID, tAvatarName, tWorldNumber, tZoneNumber);
	if (!RECONNECT_TO_DATABASE01())
	{
		return FALSE;
	}
	iAffected = 0;
#ifdef __WIN32__
	if (!mDB01.Execute(mQUERY, iAffected))
	{
		return FALSE;
	}
#else
	if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		return TRUE;
	}
#ifdef __COMMIT__
	if (mDB01.exec_query("commit", CMySQL::CLEAR) != 0) {
		return TRUE;
	}
#endif
#endif
	return TRUE;
}
//DB_PROCESS_09
void MyDB::DB_PROCESS_09(char tID[MAX_USER_ID_LENGTH], int tSort)
{
	int iAffected;

	sprintf(mQUERY, "insert into %s values ( '%s',0,0 )", mSERVER_INFO.mDB_1_Table06, tID);
	RECONNECT_TO_DATABASE01();
	iAffected = 0;
#ifdef __WIN32__
	mDB01.Execute(mQUERY, iAffected);
#else
	mDB01.exec_query(mQUERY, CMySQL::CLEAR);
#ifdef __COMMIT__
	mDB01.exec_query("commit", CMySQL::CLEAR);
#endif
#endif
	switch (tSort)
	{
	case 1:
		sprintf(mQUERY, "update %s set uEventNum01=uEventNum01+1 where uID='%s'; ", mSERVER_INFO.mDB_1_Table06, tID);
		RECONNECT_TO_DATABASE01();
		iAffected = 0;
#ifdef __WIN32__
		mDB01.Execute(mQUERY, iAffected);
#else
		mDB01.exec_query(mQUERY, CMySQL::CLEAR);
#ifdef __COMMIT__
		mDB01.exec_query("commit", CMySQL::CLEAR);
#endif
#endif
		return;
	case 2:
		sprintf(mQUERY, "update %s set uEventNum02=uEventNum02+1 where uID='%s'; ", mSERVER_INFO.mDB_1_Table06, tID);
		RECONNECT_TO_DATABASE01();
		iAffected = 0;
#ifdef __WIN32__
		mDB01.Execute(mQUERY, iAffected);
#else
		mDB01.exec_query(mQUERY, CMySQL::CLEAR);
#ifdef __COMMIT__
		mDB01.exec_query("commit", CMySQL::CLEAR);
#endif
#endif
		return;
	}
}

bool MyDB::DB_COMPARE_AUTH_KEY(char tID[MAX_USER_ID_LENGTH], char szAuthKey[MAX_MOUSE_PASSWORD_LENGTH], BYTE& bResult)
{
	MYSQL_ROW row;
	MYSQL_RES* res = NULL;
	int iAffected = 0, iCounts = 0;
	char StoredAuthKey[MAX_MOUSE_PASSWORD_LENGTH] = { 0, };

	bResult = 1;

	sprintf(mQUERY, "SELECT uMousePassword FROM %s WHERE uID = '%s'", mSERVER_INFO.mDB_2_Table01, tID);
	if (!RECONNECT_TO_DATABASE02())
	{
		return false;
	}
	iAffected = 0;
#ifdef __WIN32__
	if (!mDB02.ExecuteAndReceive(mQUERY, iAffected))
	{
		return false;
	}
	iCounts = 0;
	if (!mDB02.GetResultCounts(iCounts))
	{
		return false;
	}
	if (iCounts != 1)
	{
		return false;
	}
	if (!mDB02.GetText(0, StoredAuthKey, MAX_MOUSE_PASSWORD_LENGTH - 1))
	{
		return false;
	}
#else
	if ((iAffected = mDB02.exec_query(mQUERY)) < 0) {
		return false;
	}
	iCounts = 0;
	res = mDB02.get_res();
	if (res == NULL) {
		return false;
	}
	while ((row = mysql_fetch_row(res))) {
		_snprintf(StoredAuthKey, MAX_MOUSE_PASSWORD_LENGTH, "%s", row[0]);
		iCounts++;
	}

	mDB02.clear_res();

	//__LogMgr()->Log_4("***********************%s %s %s %d\n", mQUERY, StoredAuthKey, szAuthKey, iCounts);
	if (iCounts != 1) {
		return false;
	}

#endif
	if (strncmp(szAuthKey, StoredAuthKey, MAX_MOUSE_PASSWORD_LENGTH - 1) == 0)
		bResult = 0;

	return true;
}

bool MyDB::DB_UPDATE_AUTH_KEY(char tID[MAX_USER_ID_LENGTH], char szAuthKey[3][MAX_MOUSE_PASSWORD_LENGTH], BYTE& bResult)
{
	MYSQL_ROW row;
	MYSQL_RES* res = NULL;
	int iAffected = 0, iCounts = 0;
	char StoredAuthKey[MAX_MOUSE_PASSWORD_LENGTH] = { 0, };

	bResult = 1;

	sprintf(mQUERY, "SELECT uMousePassword FROM %s WHERE uID = '%s'", mSERVER_INFO.mDB_2_Table01, tID);
	if (!RECONNECT_TO_DATABASE02())
	{
		return false;
	}
	iAffected = 0;
#ifdef __WIN32__
	if (!mDB02.ExecuteAndReceive(mQUERY, iAffected))
	{
		return false;
	}
	iCounts = 0;
	if (!mDB02.GetResultCounts(iCounts))
	{
		return false;
	}
	if (iCounts != 1)
	{
		return false;
	}
	if (!mDB02.GetText(0, StoredAuthKey, MAX_MOUSE_PASSWORD_LENGTH - 1))
	{
		return false;
	}
#else 
	if ((iAffected = mDB02.exec_query(mQUERY)) < 0) {
		return false;
	}
	iCounts = 0;
	res = mDB02.get_res();
	if (res == NULL) {
		return false;
	}
	while ((row = mysql_fetch_row(res))) {
		_snprintf(StoredAuthKey, MAX_MOUSE_PASSWORD_LENGTH, "%s", row[0]);
		iCounts++;
	}

	mDB02.clear_res();

	//__LogMgr()->Log_4("***********************%s %s %s %d\n", mQUERY, StoredAuthKey, szAuthKey, iCounts);
	if (iCounts != 1) {
		return false;
	}
#endif
	if (strncmp(szAuthKey[0], StoredAuthKey, MAX_MOUSE_PASSWORD_LENGTH - 1) == 0) {
		sprintf(mQUERY, "UPDATE %s SET uMousePassword = '%s' WHERE uID = '%s'", mSERVER_INFO.mDB_2_Table01, szAuthKey[1], tID);
		RECONNECT_TO_DATABASE02();
		iAffected = 0;

		if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			return false;
		}
#ifdef __COMMIT__
		if (mDB02.exec_query("commit", CMySQL::CLEAR) != 0) {
			return false;
		}
#endif
		bResult = 0;
	}

	return true;
}
//DB_PROCESS_10
BOOL MyDB::DB_PROCESS_10(TRIBE_INFO* tTribeInfo)
{
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
	MYSQL_ROW row;
	MYSQL_RES* res = NULL;

	sprintf(mQUERY, "select mTribeVoteInfo,mTribe01Master,mTribe01SubMasterInfo,mTribe02Master,mTribe02SubMasterInfo,mTribe03Master,mTribe03SubMasterInfo,mTribe04Master,mTribe04SubMasterInfo from %s WHERE aWorldNumber = %d", mSERVER_INFO.mDB_1_Table08, mSERVER_INFO.mWorldNumber);
	if (!RECONNECT_TO_DATABASE01())
	{
		__LogMgr()->Log("!Unable to connect to the database[%s] in %s method.\n",
			mSERVER_INFO.mDB_1_Table08, __FUNCTION__);
		return FALSE;
	}
	iAffected = 0;
	if ((iAffected = mDB01.exec_query(mQUERY)) < 0) {
		__LogMgr()->Log("!The query execution failed in %s.\n", __FUNCTION__);
		__LogMgr()->Log("\t\t\tWhy - %s\n", mDB01.get_error_msg().c_str());
		return FALSE;
	}
	iCounts = 0;
	res = mDB01.get_res();
	if (res == NULL) {
		__LogMgr()->Log("!Query failed - (%s).\n", mQUERY);
		__LogMgr()->Log("\t\t\tWhy - %s\n", mDB01.get_error_msg().c_str());
		return FALSE;
	}
	while (row = mysql_fetch_row(res)) {
		::strncpy(mTribeVoteInfo, row[0], 1041);
		::strncpy(mTribe01Master, row[1], MAX_AVATAR_NAME_LENGTH - 1);
		::strncpy(mTribe01SubMasterInfo, row[2], 145);
		::strncpy(mTribe02Master, row[3], MAX_AVATAR_NAME_LENGTH - 1);
		::strncpy(mTribe02SubMasterInfo, row[4], 145);
		::strncpy(mTribe03Master, row[5], MAX_AVATAR_NAME_LENGTH - 1);
		::strncpy(mTribe03SubMasterInfo, row[6], 145);
		::strncpy(mTribe04Master, row[7], MAX_AVATAR_NAME_LENGTH - 1);
		::strncpy(mTribe04SubMasterInfo, row[8], 145);
		++iCounts;
	}
	mDB01.clear_res();
	if (1 != iCounts) {
		__LogMgr()->Log("!As a result of a number of rows is not returned by the query.\n");
		__LogMgr()->Log("\t\t\tRow counts = %d.\n", iCounts);
		return FALSE;
	}
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
		__LogMgr()->Log("!TribeVoteInfo, the length of the problem was different in %s.\n",
			__FUNCTION__);
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
		__LogMgr()->Log("!Tribe01SubMasterInfo, the length of the problem was different in %s.\n",
			__FUNCTION__);
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
		__LogMgr()->Log("!Tribe02SubMasterInfo, the length of the problem was different in %s.\n",
			__FUNCTION__);
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
		__LogMgr()->Log("!Tribe03SubMasterInfo, the length of the problem was different in %s.\n",
			__FUNCTION__);
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
		__LogMgr()->Log("!Tribe04SubMasterInfo, the length of the problem was different in %s.\n",
			__FUNCTION__);
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
				\
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
	strcpy(tTribeInfo->mTribeMaster[1], mTribe01Master);
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
	strcpy(tTribeInfo->mTribeMaster[2], mTribe01Master);
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
	strcpy(tTribeInfo->mTribeMaster[3], mTribe01Master);
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
void MyDB::DB_PROCESS_11(char tID[MAX_USER_ID_LENGTH], char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tChangeAvatarName[MAX_AVATAR_NAME_LENGTH], int* tResult)
{
	int tAvatarPost;
	int iAffected;

	DB_PROCESS_12(tID, tAvatarName, &tAvatarPost);
	if (-1 == tAvatarPost) {
		*tResult = 1;
		return;
	}

	sprintf(mQUERY, "update %s set aName='%s' where aName='%s'", mSERVER_INFO.mDB_2_Table03, tChangeAvatarName, tAvatarName);
	if (!RECONNECT_TO_DATABASE02())
	{
		*tResult = 2;
		return;
	}
	iAffected = 0;
	if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		*tResult = 3;
		return;
	}
	sprintf(mQUERY, "update %s set aName='%s' where aName='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_1_Table09, tChangeAvatarName, tAvatarName, mSERVER_INFO.mWorldNumber);
	if (!RECONNECT_TO_DATABASE01())
	{
		sprintf(mQUERY, "update %s set aName='%s' where aName='%s'", mSERVER_INFO.mDB_2_Table03, tAvatarName, tChangeAvatarName);
		RECONNECT_TO_DATABASE02();
		iAffected = 0;
		if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 4;
			return;
		}
		*tResult = 2;
		return;
	}
	iAffected = 0;
	if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		sprintf(mQUERY, "update %s set aName='%s' where aName='%s'", mSERVER_INFO.mDB_2_Table03, tAvatarName, tChangeAvatarName);
		RECONNECT_TO_DATABASE02();
		iAffected = 0;
		if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 5;
			return;
		}
		*tResult = 2;
		return;
	}
	switch (tAvatarPost)
	{
	case 0:
		sprintf(mQUERY, "update %s set aName01='%s' where uID='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_1_Table07, tChangeAvatarName, tID, mSERVER_INFO.mWorldNumber);
		break;
	case 1:
		sprintf(mQUERY, "update %s set aName02='%s' where uID='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_1_Table07, tChangeAvatarName, tID, mSERVER_INFO.mWorldNumber);
		break;
	case 2:
		sprintf(mQUERY, "update %s set aName03='%s' where uID='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_1_Table07, tChangeAvatarName, tID, mSERVER_INFO.mWorldNumber);
		break;
	default:
		sprintf(mQUERY, "update %s set aName='%s' where aName='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_1_Table09, tAvatarName, tChangeAvatarName, mSERVER_INFO.mWorldNumber);
		RECONNECT_TO_DATABASE01();
		iAffected = 0;
		if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 6;
			return;
		}
		sprintf(mQUERY, "update %s set aName='%s' where aName='%s'", mSERVER_INFO.mDB_2_Table03, tAvatarName, tChangeAvatarName);
		RECONNECT_TO_DATABASE02();
		iAffected = 0;
		if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 7;
			return;
		}
		*tResult = 2;
		return;
	}
	if (!RECONNECT_TO_DATABASE01())
	{
		sprintf(mQUERY, "update %s set aName='%s' where aName='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_1_Table09, tAvatarName, tChangeAvatarName, mSERVER_INFO.mWorldNumber);
		RECONNECT_TO_DATABASE01();
		iAffected = 0;
		if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 8;
			return;
		}
		sprintf(mQUERY, "update %s set aName='%s' where aName='%s'", mSERVER_INFO.mDB_2_Table03, tAvatarName, tChangeAvatarName);
		RECONNECT_TO_DATABASE02();
		iAffected = 0;
		if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 9;
			return;
		}
		*tResult = 2;
		return;
	}
	iAffected = 0;
	if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		sprintf(mQUERY, "update %s set aName='%s' where aName='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_1_Table09, tAvatarName, tChangeAvatarName, mSERVER_INFO.mWorldNumber);
		RECONNECT_TO_DATABASE01();
		iAffected = 0;
		if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 10;
			return;
		}
		sprintf(mQUERY, "update %s set aName='%s' where aName='%s'", mSERVER_INFO.mDB_2_Table03, tAvatarName, tChangeAvatarName);
		RECONNECT_TO_DATABASE02();
		iAffected = 0;
		if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 10;
			return;
		}
		*tResult = 2;
		return;
	}
	*tResult = 0;
}
//DB_PROCESS_12
void MyDB::DB_PROCESS_12(char* tID, char* tAvatarName, int* tResult)
{
	MYSQL_ROW row;
	MYSQL_RES* res;
	int iAffected;
	int iCounts;

	char tName01[MAX_AVATAR_NAME_LENGTH];
	char tName02[MAX_AVATAR_NAME_LENGTH];
	char tName03[MAX_AVATAR_NAME_LENGTH];
	*tResult = -1;

	sprintf(mQUERY, "select aName01, aName02, aName03 from %s where uID ='%s' AND aWorldNumber = '%d';", mSERVER_INFO.mDB_1_Table07, tID, mSERVER_INFO.mWorldNumber);
	if (!RECONNECT_TO_DATABASE01())
	{
		return;
	}
	iAffected = 0;
	if ((iAffected = mDB01.exec_query(mQUERY)) < 0) {
		return;
	}
	iCounts = 0;
	res = mDB01.get_res();
	if (res == NULL) {
		return;
	}
	while ((row = mysql_fetch_row(res))) {
		_snprintf(tName01, MAX_AVATAR_NAME_LENGTH, "%s", row[0]);
		_snprintf(tName02, MAX_AVATAR_NAME_LENGTH, "%s", row[1]);
		_snprintf(tName03, MAX_AVATAR_NAME_LENGTH, "%s", row[2]);
		iCounts++;
	}

	mDB01.clear_res();

	if (iCounts != 1) {
		return;
	}
	if (0 == strcmp(tName01, tAvatarName)) {
		*tResult = 0;
	}
	else if (0 == strcmp(tName02, tAvatarName)) {
		*tResult = 1;
	}
	else if (0 == strcmp(tName03, tAvatarName)) {
		*tResult = 2;
	}
	else;
}
//DB_PROCESS_13
void MyDB::DB_PROCESS_13(char* tID, int* tResult)
{
	MYSQL_ROW row;
	MYSQL_RES* res;
	int iAffected;
	int iCounts;
	char tBonus100Money;
	*tResult = 0;

	sprintf(mQUERY, "select uBonus100Money from %s where uID ='%s' AND aWorldNumber = '%d';", mSERVER_INFO.mDB_2_Table01, tID, mSERVER_INFO.mWorldNumber);
	if (!RECONNECT_TO_DATABASE02())
	{
		*tResult = 1;
		return;
	}
	iAffected = 0;
	if ((iAffected = mDB02.exec_query(mQUERY)) < 0) {
		*tResult = 2;
		return;
	}
	iCounts = 0;
	res = mDB02.get_res();
	if (res == NULL) {
		*tResult = 3;
		return;
	}
	while ((row = mysql_fetch_row(res))) {
		tBonus100Money = *row[0];
		iCounts++;
	}

	mDB02.clear_res();

	if (iCounts != 1) {
		*tResult = 3;
		return;
	}
	if ('1' == tBonus100Money) {
		*tResult = 4;
		return;
	}
}
//DB_PROCESS_14
void MyDB::DB_PROCESS_14(char tID[MAX_USER_ID_LENGTH], int* tResult)
{
	int iAffected;

	mDB.DB_PROCESS_13(tID, tResult);
	if (0 != tResult) {
		return;
	}

	sprintf(mQUERY, "update %s set uBonus100Money='%c' where uID='%s';", mSERVER_INFO.mDB_2_Table01, '1', tID);
	if (!RECONNECT_TO_DATABASE02())
	{
		*tResult = 5;
		return;
	}
	iAffected = 0;
	if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		*tResult = 6;
		return;
	}
	sprintf(mQUERY, "update %s set uBonusCash=uBonusCash+%d where uID='%s';", mSERVER_INFO.mDB_2_Table01, 100, tID);
	if (!RECONNECT_TO_DATABASE02())
	{
		sprintf(mQUERY, "update %s set uBonus100Money='%c' where uID='%s';", mSERVER_INFO.mDB_2_Table01, '0', tID);
		RECONNECT_TO_DATABASE02();
		iAffected = 0;
		if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 7;
			return;
		}
		*tResult = 8;
		return;
	}
	iAffected = 0;
	if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		sprintf(mQUERY, "update %s set uBonus100Money='%c' where uID='%s';", mSERVER_INFO.mDB_2_Table01, '0', tID);
		RECONNECT_TO_DATABASE02();
		iAffected = 0;
		if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 9;
			return;
		}
		*tResult = 10;
		return;
	}
	*tResult = 0;
}
//DB_PROCESS_15
void MyDB::DB_PROCESS_15(char* tID, char* tName, int tTribe, int tKillNum)
{
	MYSQL_ROW row;
	MYSQL_RES* res;
	int iAffected;
	int iCounts;
	char tCnt = 0;

	sprintf(mQUERY, "select count(*) from %s where aWorldNumber = %d and aName = '%s';", mSERVER_INFO.mDB_1_Table05, mSERVER_INFO.mWorldNumber, tName);
	if (!RECONNECT_TO_DATABASE01())
	{
		return;
	}
	iAffected = 0;
	if ((iAffected = mDB01.exec_query(mQUERY)) < 0) {
		return;
	}
	iCounts = 0;
	res = mDB01.get_res();
	if (res == NULL) {
		return;
	}
	while ((row = mysql_fetch_row(res))) {
		tCnt = ::atol(row[0]);
		iCounts++;
	}

	mDB01.clear_res();

	if (iCounts != 1) {
		return;
	}

	if (0 == tCnt) {
		sprintf(mQUERY, "insert into %s values (%d, '%s', '%s', %d, %d);",
			mSERVER_INFO.mDB_1_Table05, mSERVER_INFO.mWorldNumber, tName, tID, tTribe, tKillNum);
		if (!RECONNECT_TO_DATABASE01())
		{
			return;
		}
		iAffected = 0;
		if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			return;
		}
	}
	else {
		sprintf(mQUERY, "update %s set aKillOtherTribe = aKillOtherTribe + %d where aWorldNumber = %d and aName = '%s';",
			mSERVER_INFO.mDB_1_Table05, tKillNum, mSERVER_INFO.mWorldNumber, tName);
		if (!RECONNECT_TO_DATABASE01())
		{
			return;
		}
		iAffected = 0;
		if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			return;
		}
	}
}
void MyDB::DB_PROCESS_DUPE(char tID[MAX_USER_ID_LENGTH], AVATAR_INFO* tAvatarInfo, AUTH_INFO* tAuthInfo)
{
	int iAffected;
	int iCounts;
	long tAvatarNameNum;
	long tIDNum;
	char tQuery[MAX_QUERY_BUFFER_SIZE];
	char mQUERY_FOR_THREAD1[MAX_QUERY_BUFFER_SIZE];
	MYSQL_ROW row;
	MYSQL_RES* res = NULL;
	int index01;
	int index02;
	char tempString01[MAX_QUERY_BUFFER_SIZE];
	char uSaveItem[701];
	char aEquip[326];
	char InventorySocket[3456];
	char EquipSocket[352];
	char TradeSocket[217];
	char StoreSocket[1513];
	char SaveSocket[757];
	char aInventory[3457];
	char aTrade[201];
	char aStoreItem[1401];
	char aSkill[241];
	char aHotKey[421];
	char aQuestInfo[26];
	char aFriend[121];
	char AutoBuff[49];
	char AnimalExp[91];
	char AnimalStat[91];
	char PetInventory[121];
	char aAutoConfig[82];
	char tempQuery[MAX_QUERY_BUFFER_SIZE];
	ZeroMemory(mQUERY_FOR_THREAD1, sizeof(mQUERY_FOR_THREAD1));

	uSaveItem[0] = '\0';
	for (index01 = 0; index01 < MAX_SAVE_ITEM_SLOT_NUM; index01++)
	{
		sprintf(tempString01, "%05d%03d%09d%08d", (tAvatarInfo->uSaveItem[index01][0] % 100000), (tAvatarInfo->uSaveItem[index01][1] % 1000), (tAvatarInfo->uSaveItem[index01][2] % 1000000000), (tAvatarInfo->uSaveItem[index01][3] % 100000000));
		strcat(uSaveItem, tempString01);
	}
	SaveSocket[0] = '\0';
	for (index01 = 0; index01 < MAX_SAVE_ITEM_SLOT_NUM; index01++)
	{
		sprintf(tempString01, "%09d%09d%09d", (tAvatarInfo->SaveSocket[index01][0] % 1000000000), (tAvatarInfo->SaveSocket[index01][1] % 1000000000), (tAvatarInfo->SaveSocket[index01][2] % 1000000000));
		strcat(SaveSocket, tempString01);
	}
	sprintf(mQUERY_FOR_THREAD1,
		"update %s set uSaveMoney=%d,uSaveItem='%s',SeyisBar=%d ,SaveSocket='%s'"
		"where uID='%s' AND aWorldNumber = '%d'; "
		, mSERVER_INFO.mDB_1_Table07, tAvatarInfo->uSaveMoney
		, uSaveItem, tAvatarInfo->SeyisBar, SaveSocket, tID, g_env.world_num);
	if (!RECONNECT_TO_DATABASE02())
	{
		__LogMgr()->Log("!%s  %d Line\n", mQUERY_FOR_THREAD1, __LINE__);
		return;
	}
	iAffected = 0;
	if (mDB02.exec_query(mQUERY_FOR_THREAD1, CMySQL::CLEAR) != 0) {
		__LogMgr()->Log("!%s  %d Line\n", mQUERY_FOR_THREAD1, __LINE__);
		return;
	}
	ZeroMemory(mQUERY_FOR_THREAD1, sizeof(mQUERY_FOR_THREAD1));

	aEquip[0] = '\0';
	for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM; index01++)
	{
		sprintf(tempString01, "%05d%03d%09d%08d", (tAvatarInfo->aEquip[index01][0] % 100000), (tAvatarInfo->aEquip[index01][1] % 1000), (tAvatarInfo->aEquip[index01][2] % 1000000000), (tAvatarInfo->aEquip[index01][3] % 100000000));
		strcat(aEquip, tempString01);
	}
	EquipSocket[0] = '\0';
	for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM; index01++)
	{
		sprintf(tempString01, "%09d%09d%09d", (tAvatarInfo->EquipSocket[index01][0] % 1000000000), (tAvatarInfo->EquipSocket[index01][1] % 1000000000), (tAvatarInfo->EquipSocket[index01][2] % 1000000000));
		strcat(EquipSocket, tempString01);
	}
	aInventory[0] = '\0';
	for (index01 = 0; index01 < 2; index01++)
	{
		for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
		{
			sprintf(tempString01, "%05d%01d%01d%03d%09d%08d", (tAvatarInfo->aInventory[index01][index02][0] % 100000), (tAvatarInfo->aInventory[index01][index02][1] % 10), (tAvatarInfo->aInventory[index01][index02][2] % 10), (tAvatarInfo->aInventory[index01][index02][3] % 1000), (tAvatarInfo->aInventory[index01][index02][4] % 1000000000), (tAvatarInfo->aInventory[index01][index02][5] % 100000000));
			strcat(aInventory, tempString01);
		}
	}
	InventorySocket[0] = '\0';
	for (index01 = 0; index01 < 2; index01++)
	{
		for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
		{
			sprintf(tempString01, "%09d%09d%09d", (tAvatarInfo->InventorySocket[index01][index02][0] % 1000000000), (tAvatarInfo->InventorySocket[index01][index02][1] % 1000000000), (tAvatarInfo->InventorySocket[index01][index02][2] % 1000000000));
			strcat(InventorySocket, tempString01);
		}
	}

	aTrade[0] = '\0';
	for (index01 = 0; index01 < MAX_TRADE_SLOT_NUM; index01++)
	{
		sprintf(tempString01, "%05d%03d%09d%08d", (tAvatarInfo->aTrade[index01][0] % 100000), (tAvatarInfo->aTrade[index01][1] % 1000), (tAvatarInfo->aTrade[index01][2] % 1000000000), (tAvatarInfo->aTrade[index01][3] % 100000000));
		strcat(aTrade, tempString01);
	}
	aStoreItem[0] = '\0';
	for (index01 = 0; index01 < 2; index01++)
	{
		for (index02 = 0; index02 < MAX_STORE_ITEM_SLOT_NUM; index02++)
		{
			sprintf(tempString01, "%05d%03d%09d%08d", (tAvatarInfo->aStoreItem[index01][index02][0] % 100000), (tAvatarInfo->aStoreItem[index01][index02][1] % 1000), (tAvatarInfo->aStoreItem[index01][index02][2] % 1000000000), (tAvatarInfo->aStoreItem[index01][index02][3] % 100000000));
			strcat(aStoreItem, tempString01);
		}
	}
	StoreSocket[0] = '\0';
	for (index01 = 0; index01 < 2; index01++)
	{
		for (index02 = 0; index02 < MAX_STORE_ITEM_SLOT_NUM; index02++)
		{
			sprintf(tempString01, "%09d%09d%09d", (tAvatarInfo->StoreSocket[index01][index02][0] % 1000000000), (tAvatarInfo->StoreSocket[index01][index02][1] % 1000000000), (tAvatarInfo->StoreSocket[index01][index02][2] % 1000000000));
			strcat(StoreSocket, tempString01);
		}
	}
	aSkill[0] = '\0';
	for (index01 = 0; index01 < MAX_SKILL_SLOT_NUM; index01++)
	{
		sprintf(tempString01, "%03d%03d", (tAvatarInfo->aSkill[index01][0] % 1000), (tAvatarInfo->aSkill[index01][1] % 1000));
		strcat(aSkill, tempString01);
	}
	aHotKey[0] = '\0';
	for (index01 = 0; index01 < 3; index01++)
	{
		for (index02 = 0; index02 < MAX_HOT_KEY_NUM; index02++)
		{
			sprintf(tempString01, "%05d%03d%02d", (tAvatarInfo->aHotKey[index01][index02][0] % 100000), (tAvatarInfo->aHotKey[index01][index02][1] % 1000), (tAvatarInfo->aHotKey[index01][index02][2] % 100));
			strcat(aHotKey, tempString01);
		}
	}
	aQuestInfo[0] = '\0';
	sprintf(tempString01, "%05d%05d%05d%05d%05d", (tAvatarInfo->aQuestInfo[0] % 100000), (tAvatarInfo->aQuestInfo[1] % 100000), (tAvatarInfo->aQuestInfo[2] % 100000), (tAvatarInfo->aQuestInfo[3] % 100000), (tAvatarInfo->aQuestInfo[4] % 100000));
	strcat(aQuestInfo, tempString01);
	//FillMemory( &aFriend[0], ( MAX_FRIEND_NUM * ( MAX_AVATAR_NAME_LENGTH - 1 ) ), '@' );

	memset(aFriend, '@', (MAX_FRIEND_NUM * (MAX_AVATAR_NAME_LENGTH - 1)));
	for (index01 = 0; index01 < MAX_FRIEND_NUM; index01++)
	{
		CopyMemory(&aFriend[(index01 * 12 + 0)], &tAvatarInfo->aFriend[index01][0], strlen(tAvatarInfo->aFriend[index01]));
	}
	aFriend[120] = '\0';
	ZeroMemory(tempString01, sizeof(tempString01));
	AutoBuff[0] = '\0';
	for (index01 = 0; index01 < MAX_AUTOBUFF_SKİLL; index01++)
	{
		sprintf(tempString01, "%03d%03d", (tAvatarInfo->AutoBuffSmenu[index01][0] % 1000), (tAvatarInfo->AutoBuffSmenu[index01][1] % 1000));
		strcat(AutoBuff, tempString01);
	}
	ZeroMemory(tempString01, sizeof(tempString01));
	AnimalExp[0] = '\0';
	for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
	{
		sprintf(tempString01, "%09d", (tAvatarInfo->AnimalExp[index01] % 1000000000));
		strcat(AnimalExp, tempString01);
	}
	ZeroMemory(tempString01, sizeof(tempString01));
	AnimalStat[0] = '\0';
	for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
	{
		sprintf(tempString01, "%09d", (tAvatarInfo->AnimalStat[index01] % 1000000000));
		strcat(AnimalStat, tempString01);
	}
	ZeroMemory(tempString01, sizeof(tempString01));
	PetInventory[0] = '\0';
	for (index01 = 0; index01 < 2; index01++)
	{
		for (index02 = 0; index02 < MAX_AVATAR_ANIMAL_NUM; index02++)
		{
			sprintf(tempString01, "%06d", (tAvatarInfo->PetInventoryTick[index01][index02] % 1000000));
			strcat(PetInventory, tempString01);
		}
	}
	ZeroMemory(tempString01, sizeof(tempString01));
	TradeSocket[0] = '\0';
	for (index01 = 0; index01 < MAX_TRADE_SLOT_NUM; index01++)
	{
		sprintf(tempString01, "%09d%09d%09d", (tAvatarInfo->TradeSocket[index01][0] % 1000000000), (tAvatarInfo->TradeSocket[index01][1] % 1000000000), (tAvatarInfo->TradeSocket[index01][2] % 1000000000));
		strcat(TradeSocket, tempString01);
	}
	ZeroMemory(tempString01, sizeof(tempString01));
	aEquip[0] = '\0';
	for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM; index01++)
	{
		sprintf(tempString01, "%05d%03d%09d%08d", (tAvatarInfo->aEquip[index01][0] % 100000), (tAvatarInfo->aEquip[index01][1] % 1000), (tAvatarInfo->aEquip[index01][2] % 1000000000), (tAvatarInfo->aEquip[index01][3] % 100000000));
		strcat(aEquip, tempString01);
	}
	ZeroMemory(tempString01, sizeof(tempString01));
	EquipSocket[0] = '\0';
	for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM; index01++)
	{
		sprintf(tempString01, "%09d%09d%09d", (tAvatarInfo->EquipSocket[index01][0] % 1000000000), (tAvatarInfo->EquipSocket[index01][1] % 1000000000), (tAvatarInfo->EquipSocket[index01][2] % 1000000000));
		strcat(EquipSocket, tempString01);
	}
	ZeroMemory(tempString01, sizeof(tempString01));
	InventorySocket[0] = '\0';
	for (index01 = 0; index01 < 2; index01++)
	{
		for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
		{
			sprintf(tempString01, "%09d%09d%09d", (tAvatarInfo->InventorySocket[index01][index02][0] % 1000000000), (tAvatarInfo->InventorySocket[index01][index02][1] % 1000000000), (tAvatarInfo->InventorySocket[index01][index02][2] % 1000000000));
			strcat(InventorySocket, tempString01);
		}
	}
	ZeroMemory(tempString01, sizeof(tempString01));
	aTrade[0] = '\0';
	for (index01 = 0; index01 < MAX_TRADE_SLOT_NUM; index01++)
	{
		sprintf(tempString01, "%05d%03d%09d%08d", (tAvatarInfo->aTrade[index01][0] % 100000), (tAvatarInfo->aTrade[index01][1] % 1000), (tAvatarInfo->aTrade[index01][2] % 1000000000), (tAvatarInfo->aTrade[index01][3] % 100000000));
		strcat(aTrade, tempString01);
	}
	ZeroMemory(tempString01, sizeof(tempString01));
	aStoreItem[0] = '\0';
	for (index01 = 0; index01 < 2; index01++)
	{
		for (index02 = 0; index02 < MAX_STORE_ITEM_SLOT_NUM; index02++)
		{
			sprintf(tempString01, "%05d%03d%09d%08d", (tAvatarInfo->aStoreItem[index01][index02][0] % 100000), (tAvatarInfo->aStoreItem[index01][index02][1] % 1000), (tAvatarInfo->aStoreItem[index01][index02][2] % 1000000000), (tAvatarInfo->aStoreItem[index01][index02][3] % 100000000));
			strcat(aStoreItem, tempString01);
		}
	}
	ZeroMemory(tempString01, sizeof(tempString01));
	StoreSocket[0] = '\0';
	for (index01 = 0; index01 < 2; index01++)
	{
		for (index02 = 0; index02 < MAX_STORE_ITEM_SLOT_NUM; index02++)
		{
			sprintf(tempString01, "%09d%09d%09d", (tAvatarInfo->StoreSocket[index01][index02][0] % 1000000000), (tAvatarInfo->StoreSocket[index01][index02][1] % 1000000000), (tAvatarInfo->StoreSocket[index01][index02][2] % 1000000000));
			strcat(StoreSocket, tempString01);
		}
	}
	ZeroMemory(tempString01, sizeof(tempString01));
	aSkill[0] = '\0';
	for (index01 = 0; index01 < MAX_SKILL_SLOT_NUM; index01++)
	{
		sprintf(tempString01, "%03d%03d", (tAvatarInfo->aSkill[index01][0] % 1000), (tAvatarInfo->aSkill[index01][1] % 1000));
		strcat(aSkill, tempString01);
	}
	ZeroMemory(tempString01, sizeof(tempString01));
	aHotKey[0] = '\0';
	for (index01 = 0; index01 < 3; index01++)
	{
		for (index02 = 0; index02 < MAX_HOT_KEY_NUM; index02++)
		{
			sprintf(tempString01, "%05d%03d%02d", (tAvatarInfo->aHotKey[index01][index02][0] % 100000), (tAvatarInfo->aHotKey[index01][index02][1] % 1000), (tAvatarInfo->aHotKey[index01][index02][2] % 100));
			strcat(aHotKey, tempString01);
		}
	}
	ZeroMemory(tempString01, sizeof(tempString01));
	aQuestInfo[0] = '\0';
	sprintf(tempString01, "%05d%05d%05d%05d%05d", (tAvatarInfo->aQuestInfo[0] % 100000), (tAvatarInfo->aQuestInfo[1] % 100000), (tAvatarInfo->aQuestInfo[2] % 100000), (tAvatarInfo->aQuestInfo[3] % 100000), (tAvatarInfo->aQuestInfo[4] % 100000));
	strcat(aQuestInfo, tempString01);
	//FillMemory( &aFriend[0], ( MAX_FRIEND_NUM * ( MAX_AVATAR_NAME_LENGTH - 1 ) ), '@' );
	ZeroMemory(tempString01, sizeof(tempString01));
	memset(aFriend, '@', (MAX_FRIEND_NUM * (MAX_AVATAR_NAME_LENGTH - 1)));
	for (index01 = 0; index01 < MAX_FRIEND_NUM; index01++)
	{
		CopyMemory(&aFriend[(index01 * 12 + 0)], &tAvatarInfo->aFriend[index01][0], strlen(tAvatarInfo->aFriend[index01]));
	}
	aFriend[120] = '\0';
	ZeroMemory(tempString01, sizeof(tempString01));
	AutoBuff[0] = '\0';
	for (index01 = 0; index01 < MAX_AUTOBUFF_SKİLL; index01++)
	{
		sprintf(tempString01, "%03d%03d", (tAvatarInfo->AutoBuffSmenu[index01][0] % 1000), (tAvatarInfo->AutoBuffSmenu[index01][1] % 1000));
		strcat(AutoBuff, tempString01);
	}
	ZeroMemory(tempString01, sizeof(tempString01));
	AnimalExp[0] = '\0';
	for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
	{
		sprintf(tempString01, "%09d", (tAvatarInfo->AnimalExp[index01] % 1000000000));
		strcat(AnimalExp, tempString01);
	}
	ZeroMemory(tempString01, sizeof(tempString01));
	AnimalStat[0] = '\0';
	for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
	{
		sprintf(tempString01, "%09d", (tAvatarInfo->AnimalStat[index01] % 1000000000));
		strcat(AnimalStat, tempString01);
	}
	ZeroMemory(tempString01, sizeof(tempString01));
	PetInventory[0] = '\0';
	for (index01 = 0; index01 < 2; index01++)
	{
		for (index02 = 0; index02 < MAX_AVATAR_ANIMAL_NUM; index02++)
		{
			sprintf(tempString01, "%06d", (tAvatarInfo->PetInventoryTick[index01][index02] % 1000000));
			strcat(PetInventory, tempString01);
		}
	}
	ZeroMemory(tempString01, sizeof(tempString01));
	TradeSocket[0] = '\0';
	for (index01 = 0; index01 < MAX_TRADE_SLOT_NUM; index01++)
	{
		sprintf(tempString01, "%09d%09d%09d", (tAvatarInfo->TradeSocket[index01][0] % 1000000000), (tAvatarInfo->TradeSocket[index01][1] % 1000000000), (tAvatarInfo->TradeSocket[index01][2] % 1000000000));
		strcat(TradeSocket, tempString01);
	}
	ZeroMemory(tempString01, sizeof(tempString01));
	aInventory[0] = '\0';
	for (index01 = 0; index01 < 2; index01++)
	{
		for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
		{
			sprintf(tempString01, "%05d%01d%01d%03d%09d%08d", (tAvatarInfo->aInventory[index01][index02][0] % 100000), (tAvatarInfo->aInventory[index01][index02][1] % 10), (tAvatarInfo->aInventory[index01][index02][2] % 10), (tAvatarInfo->aInventory[index01][index02][3] % 1000), (tAvatarInfo->aInventory[index01][index02][4] % 1000000000), (tAvatarInfo->aInventory[index01][index02][5] % 100000000));
			strcat(aInventory, tempString01);
		}
	}

	
	::memset(aAutoConfig, 0, 82);

	::snprintf(aAutoConfig, 82,
		"%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d"
		"%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d"
		"%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d"
		"%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d"
		"%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d"
		"%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d"
		"%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d"
		"%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d"
		"%03d"
		, tAvatarInfo->AutoHunt.BuffType
		, tAvatarInfo->AutoHunt.HuntBuff[0][0]
		, tAvatarInfo->AutoHunt.HuntBuff[0][1]
		, tAvatarInfo->AutoHunt.HuntBuff[1][0]
		, tAvatarInfo->AutoHunt.HuntBuff[1][1]
		, tAvatarInfo->AutoHunt.HuntBuff[2][0]
		, tAvatarInfo->AutoHunt.HuntBuff[2][1]
		, tAvatarInfo->AutoHunt.HuntBuff[3][0]
		, tAvatarInfo->AutoHunt.HuntBuff[3][1]
		, tAvatarInfo->AutoHunt.HuntBuff[4][0]
		, tAvatarInfo->AutoHunt.HuntBuff[4][1]
		, tAvatarInfo->AutoHunt.HuntBuff[5][0]
		, tAvatarInfo->AutoHunt.HuntBuff[5][1]
		, tAvatarInfo->AutoHunt.HuntBuff[6][0]
		, tAvatarInfo->AutoHunt.HuntBuff[6][1]
		, tAvatarInfo->AutoHunt.HuntBuff[7][0]
		, tAvatarInfo->AutoHunt.HuntBuff[7][1]
		, tAvatarInfo->AutoHunt.HuntType
		, tAvatarInfo->AutoHunt.AtakType[0][0]
		, tAvatarInfo->AutoHunt.AtakType[0][1]
		, tAvatarInfo->AutoHunt.AtakType[1][0]
		, tAvatarInfo->AutoHunt.AtakType[1][1]
		, tAvatarInfo->AutoHunt.OfMonster
		, tAvatarInfo->AutoHunt.HuntPickUp
		, tAvatarInfo->AutoHunt.HuntInsuficcent
		, tAvatarInfo->AutoHunt.HuntPetFood
		, tAvatarInfo->AutoHunt.HuntPetFood);

	strcpy(mQUERY_FOR_THREAD1, "UPDATE AvatarInfo SET ");
	sprintf(tempQuery, "aVisibleState = %d, ", tAvatarInfo->aVisibleState);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aSpecialState = %d, ", tAvatarInfo->aSpecialState);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aPlayTime1 = %d, ", tAvatarInfo->aPlayTime1);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aPlayTime2 = %d, ", tAvatarInfo->aPlayTime2);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aKillOtherTribe = %d, ", tAvatarInfo->aKillOtherTribe);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aworldnumber = 1, ", 1); //aworldnumber
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aName = '%s', ", tAvatarInfo->aName);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aTribe = %d, ", tAvatarInfo->aTribe);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aPreviousTribe = %d, ", tAvatarInfo->aPreviousTribe);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aGender = %d, ", tAvatarInfo->aGender);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aHeadType = %d, ", tAvatarInfo->aHeadType);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aFaceType = %d, ", tAvatarInfo->aFaceType);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aLevel1 = %d, ", tAvatarInfo->aLevel1);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aLevel2 = %d, ", tAvatarInfo->aLevel2);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aGeneralExperience1 = %d, ", tAvatarInfo->aGeneralExperience1);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aGeneralExperience2 = %d, ", tAvatarInfo->aGeneralExperience2);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aVitality = %d, ", tAvatarInfo->aVitality);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aStrength = %d, ", tAvatarInfo->aStrength);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aKi = %d, ", tAvatarInfo->aKi);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aWisdom = %d, ", tAvatarInfo->aWisdom);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aEatLifePotion = %d, ", tAvatarInfo->aEatLifePotion);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aEatManaPotion = %d, ", tAvatarInfo->aEatManaPotion);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "StrElx = %d, ", tAvatarInfo->StrElx);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "AgiElx = %d, ", tAvatarInfo->AgiElx);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "AttAtakElixir = %d, ", (tAvatarInfo->YeniElx / 1000));
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "AttDefElixir = %d, ", (tAvatarInfo->YeniElx % 1000));
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aStateBonusPoint = %d, ", tAvatarInfo->aStateBonusPoint);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aSkillPoint = %d, ", tAvatarInfo->aSkillPoint);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aEquip = '%s', ", aEquip);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aExpandInventoryDate = %d, ", tAvatarInfo->aExpandInventoryDate);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aMoney = %d, ", tAvatarInfo->aMoney);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aInventory = '%s', ", aInventory);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aTradeMoney = %d, ", tAvatarInfo->aTradeMoney);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aTrade = '%s', ", aTrade);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aExpandStoreDate = %d, ", tAvatarInfo->aExpandStoreDate);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aStoreMoney = %d, ", tAvatarInfo->aStoreMoney);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aStoreItem = '%s', ", aStoreItem);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aSkill = '%s', ", aSkill);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aHotKey = '%s', ", aHotKey);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aQuestInfo = '%s', ", aQuestInfo);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aFriend = '%s', ", aFriend);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aTeacher = '%s', ", tAvatarInfo->aTeacher);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aStudent = '%s', ", tAvatarInfo->aStudent);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aTeacherPoint = %d, ", tAvatarInfo->aTeacherPoint);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aGuildName = '%s', ", tAvatarInfo->aGuildName);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aGuildRole = %d, ", tAvatarInfo->aGuildRole);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aCallName = '%s', ", tAvatarInfo->aCallName);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aGuildMarkNum = %d, ", tAvatarInfo->aGuildMarkNum);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aGuildMarkEffect = %d, ", tAvatarInfo->aGuildMarkEffect);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aLogoutInfo01 = %d, ", tAvatarInfo->aLogoutInfo[0]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aLogoutInfo02 = %d, ", tAvatarInfo->aLogoutInfo[1]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aLogoutInfo03 = %d, ", tAvatarInfo->aLogoutInfo[2]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aLogoutInfo04 = %d, ", tAvatarInfo->aLogoutInfo[3]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aLogoutInfo05 = %d, ", tAvatarInfo->aLogoutInfo[4]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aLogoutInfo06 = %d, ", tAvatarInfo->aLogoutInfo[5]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "ProtectionScroll = %d, ", tAvatarInfo->ProtectionScroll);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "ProtectionCharm = %d, ", tAvatarInfo->ProtectionCharm);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "HolyWater = %d, ", tAvatarInfo->HolyWater);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "SuperiorPill = %d, ", tAvatarInfo->SuperiorPill);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "ScrollofLoyality = %d, ", tAvatarInfo->ScrollofLoyality);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "ScrollofBattle = %d, ", tAvatarInfo->ScrollofBattle);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "GodTempleKey = %d, ", tAvatarInfo->GodTempleKey);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "SolemGrounds = %d, ", tAvatarInfo->SolemGrounds);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "EdgeOfTaiyan = %d, ", tAvatarInfo->EdgeOfTaiyan);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "ScrollOfSeekers = %d, ", tAvatarInfo->ScrollOfSeekers);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aKillMonsterNum = %d, ", tAvatarInfo->aKillMonsterNum);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "RankPoint = %d, ", tAvatarInfo->RankPoint);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "RankPrize = %d, ", tAvatarInfo->RankPrize);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aSearch = %d, ", tAvatarInfo->aSearch);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "ExchangeHealtiks = %d, ", tAvatarInfo->ExchangeHealtiks);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "ExchangeChiiks = %d, ", tAvatarInfo->ExchangeChiiks);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "HealtAutoPot = %d, ", tAvatarInfo->HealtAutoPot);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aTribeVoteDate = %d, ", tAvatarInfo->aTribeVoteDate);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "ManaAutoPot = %d, ", tAvatarInfo->ManaAutoPot);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aAnimal01 = %d, ", tAvatarInfo->aAnimal[0]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aAnimal02 = %d, ", tAvatarInfo->aAnimal[1]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aAnimal03 = %d, ", tAvatarInfo->aAnimal[2]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aAnimal04 = %d, ", tAvatarInfo->aAnimal[3]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aAnimal05 = %d, ", tAvatarInfo->aAnimal[4]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aAnimal06 = %d, ", tAvatarInfo->aAnimal[5]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aAnimal07 = %d, ", tAvatarInfo->aAnimal[6]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aAnimal08 = %d, ", tAvatarInfo->aAnimal[7]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aAnimal09 = %d, ", tAvatarInfo->aAnimal[8]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aAnimal10 = %d, ", tAvatarInfo->aAnimal[9]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aAnimalIndex = %d, ", tAvatarInfo->aAnimalIndex);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aAnimalTime = %d, ", tAvatarInfo->aAnimalTime);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "LuckyCombine = %d, ", tAvatarInfo->LuckyCombine);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "LuckyUpgrade = %d, ", tAvatarInfo->LuckyUpgrade);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "LuckyDrop = %d, ", tAvatarInfo->LuckyDrop);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Title = %d, ", tAvatarInfo->Title);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "ExtinctionScroll = %d, ", tAvatarInfo->ExtinctionScroll);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aUpradgeValue = %d, ", tAvatarInfo->aUpradgeValue);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Beginner = %d, ", tAvatarInfo->Beginner);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "BeginnerLevel = %d, ", tAvatarInfo->BeginnerLevel);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OnlineHour = %d, ", tAvatarInfo->OnlineHour);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Cppc = %d, ", tAvatarInfo->Cppc);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "iUseOrnament = %d, ", tAvatarInfo->iUseOrnament);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "iSilverOrnamentRemainsTime = %d, ", tAvatarInfo->iSilverOrnamentRemainsTime);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "IslandOfBlood = %d, ", tAvatarInfo->IslandOfBlood);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "IslandOfSoulMReal1 = %d, ", tAvatarInfo->IslandOfSoulMReal1);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "IslandOfSoulMReal2 = %d, ", tAvatarInfo->IslandOfSoulMReal2);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "IslandOfSoulMReal3 = %d, ", tAvatarInfo->IslandOfSoulMReal3);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "IslandOfSoulMReal4 = %d, ", tAvatarInfo->IslandOfSoulMReal4);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "IslandOfSoulMReal5 = %d, ", tAvatarInfo->IslandOfSoulMReal5);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "IslandOfSoulMReal6 = %d, ", tAvatarInfo->IslandOfSoulMReal6);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "SkillIncreaseCritHit = %d, ", tAvatarInfo->SkillIncreaseCritHit);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "LifeOrDeath = %d, ", tAvatarInfo->LifeOrDeath);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "iGoldOrnamentRemainsTime = %d, ", tAvatarInfo->iGoldOrnamentRemainsTime);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "BloodBoost = %d, ", tAvatarInfo->BloodBoost);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "SoulBoost = %d, ", tAvatarInfo->SoulBoost);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Registration = %d, ", tAvatarInfo->Registration);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "ExpPill = %d, ", tAvatarInfo->ExpPill);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "FactReturnScroll = %d, ", tAvatarInfo->FactReturnScroll);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "PetExpBoost = %d, ", tAvatarInfo->PetExpBoost);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Costume1 = %d, ", tAvatarInfo->Costume[0]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Costume2 = %d, ", tAvatarInfo->Costume[1]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Costume3 = %d, ", tAvatarInfo->Costume[2]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Costume4 = %d, ", tAvatarInfo->Costume[3]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Costume5 = %d, ", tAvatarInfo->Costume[4]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Costume6 = %d, ", tAvatarInfo->Costume[5]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Costume7 = %d, ", tAvatarInfo->Costume[6]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Costume8 = %d, ", tAvatarInfo->Costume[7]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Costume9 = %d, ", tAvatarInfo->Costume[8]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Costume10 = %d, ", tAvatarInfo->Costume[9]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "CostumeInventory1 = %d, ", tAvatarInfo->CostumeInventory[0]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "CostumeInventory2 = %d, ", tAvatarInfo->CostumeInventory[1]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "CostumeInventory3 = %d, ", tAvatarInfo->CostumeInventory[2]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "CostumeInventory4 = %d, ", tAvatarInfo->CostumeInventory[3]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "CostumeInventory5 = %d, ", tAvatarInfo->CostumeInventory[4]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "CostumeInventory6 = %d, ", tAvatarInfo->CostumeInventory[5]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "CostumeInventory7 = %d, ", tAvatarInfo->CostumeInventory[6]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "CostumeInventory8 = %d, ", tAvatarInfo->CostumeInventory[7]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "CostumeInventory9 = %d, ", tAvatarInfo->CostumeInventory[8]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "CostumeInventory10 = %d, ", tAvatarInfo->CostumeInventory[9]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "SelectCostume = %d, ", tAvatarInfo->SelectCostume);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "DamegeBoostScroll = %d, ", tAvatarInfo->DamegeBoostScroll);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "HealtBoostScroll = %d, ", tAvatarInfo->HealtBoostScroll);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "CritBoostScroll = %d, ", tAvatarInfo->CritBoostScroll);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "AutoBuffScroll = %d, ", tAvatarInfo->AutoBuffScroll);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "AutoBuffSmenu = '%s', ", AutoBuff);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "FishBread = %d, ", tAvatarInfo->Hisar);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "SweetPateto = %d, ", tAvatarInfo->SweetPateto);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "InventorySocket = '%s', ", InventorySocket);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "EquipSocket = '%s', ", EquipSocket);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "TradeSocket = '%s', ", TradeSocket);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "StoreSocket = '%s', ", StoreSocket);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Hunt7d = %d, ", tAvatarInfo->Hunt7d);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Hunt5h = %d, ", tAvatarInfo->Hunt5h);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Inventorybar = %d, ", tAvatarInfo->Inventorybar);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "TradeBar = %d, ", tAvatarInfo->TradeBar);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "BankBar = %d, ", tAvatarInfo->BankBar);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "RebirtHall = %d, ", tAvatarInfo->RebirtHall);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "PreServeCharm = %d, ", tAvatarInfo->PreServeCharm);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Chenjoho = %d, ", tAvatarInfo->Chenjoho);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aRankPoint = %d, ", tAvatarInfo->aRankPoint);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "aRank = %d, ", tAvatarInfo->aRank);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "FanctionNoticeScroll = %d, ", tAvatarInfo->FanctionNoticeScroll);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "AnimalExp = '%s', ", AnimalExp);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "AnimalStat = '%s', ", AnimalStat);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "DoubleMouthExp2x = %d, ", tAvatarInfo->DoubleMouthExp2x);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "VigilanteScroll = %d, ", tAvatarInfo->VigilanteScroll);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "RafflaTicket = %d, ", tAvatarInfo->RafflaTicket);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "MountAbsorb = %d, ", tAvatarInfo->MountAbsorb);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "MountAbsorbe = %d, ", tAvatarInfo->MountAbsorbe);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "BurstPill = %d, ", tAvatarInfo->BurstPill);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "RagePill = %d, ", tAvatarInfo->RagePill);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "WarriorScroll = %d, ", tAvatarInfo->WarriorScroll);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "HeroPill = %d, ", tAvatarInfo->HeroPill);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "WingProtectionRune = %d, ", tAvatarInfo->WingProtectionRune);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "LessDecressScroll = %d, ", tAvatarInfo->LessDecressScroll);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "PetInventory = %d, ", tAvatarInfo->PetInventory);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "PetInventoryTick = '%s', ", PetInventory);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "JoinWar = %d, ", tAvatarInfo->JoinWar);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "PlayerKill = %d, ", tAvatarInfo->PlayerKill);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "MonsterKill = %d, ", tAvatarInfo->MonsterKill);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "PlayTimeDay = %d, ", tAvatarInfo->PlayTimeDay);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "AutoHuntConfing = '%s', ", aAutoConfig);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "BloodStained = %d, ", tAvatarInfo->BloodStained);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "FishingTime = %d, ", tAvatarInfo->FishingTime);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "BottleIndex = %d, ", tAvatarInfo->BottleIndex);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "BottleTime = %d, ", tAvatarInfo->BottleTime);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Bottle1 = %d, ", tAvatarInfo->Bottle[0]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Bottle2 = %d, ", tAvatarInfo->Bottle[1]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Bottle3 = %d, ", tAvatarInfo->Bottle[2]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Bottle4 = %d, ", tAvatarInfo->Bottle[3]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Bottle5 = %d, ", tAvatarInfo->Bottle[4]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Bottle6 = %d, ", tAvatarInfo->Bottle[5]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Bottle7 = %d, ", tAvatarInfo->Bottle[6]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Bottle8 = %d, ", tAvatarInfo->Bottle[7]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Bottle9 = %d, ", tAvatarInfo->Bottle[8]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Bottle10 = %d, ", tAvatarInfo->Bottle[9]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "BottlePrice1 = %d, ", tAvatarInfo->BottlePrice[0]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "BottlePrice2 = %d, ", tAvatarInfo->BottlePrice[1]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "BottlePrice3 = %d, ", tAvatarInfo->BottlePrice[2]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "BottlePrice4 = %d, ", tAvatarInfo->BottlePrice[3]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "BottlePrice5 = %d, ", tAvatarInfo->BottlePrice[4]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "BottlePrice6 = %d, ", tAvatarInfo->BottlePrice[5]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "BottlePrice7 = %d, ", tAvatarInfo->BottlePrice[6]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "BottlePrice8 = %d, ", tAvatarInfo->BottlePrice[7]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "BottlePrice9 = %d, ", tAvatarInfo->BottlePrice[8]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "BottlePrice10 = %d, ", tAvatarInfo->BottlePrice[9]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OtherSkill1 = %d, ", tAvatarInfo->OtherSkill[0]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OtherSkill2 = %d, ", tAvatarInfo->OtherSkill[1]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OtherSkill3 = %d, ", tAvatarInfo->OtherSkill[2]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OtherSkill4 = %d, ", tAvatarInfo->OtherSkill[3]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OtherSkill5 = %d, ", tAvatarInfo->OtherSkill[4]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OtherSkill6 = %d, ", tAvatarInfo->OtherSkill[5]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OtherSkill7 = %d, ", tAvatarInfo->OtherSkill[6]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OtherSkill8 = %d, ", tAvatarInfo->OtherSkill[7]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OtherSkill9 = %d, ", tAvatarInfo->OtherSkill[8]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OtherSkill10 = %d, ", tAvatarInfo->OtherSkill[9]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OtherSkill11 = %d, ", tAvatarInfo->OtherSkill[10]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OtherSkill12 = %d, ", tAvatarInfo->OtherSkill[11]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OtherSkill13 = %d, ", tAvatarInfo->OtherSkill[12]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OtherSkill14 = %d, ", tAvatarInfo->OtherSkill[13]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OtherSkillState11 = %d, ", tAvatarInfo->OtherSkillState1[0]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OtherSkillState12 = %d, ", tAvatarInfo->OtherSkillState1[1]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OtherSkillState13 = %d, ", tAvatarInfo->OtherSkillState1[2]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OtherSkillState14 = %d, ", tAvatarInfo->OtherSkillState1[3]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OtherSkillState15 = %d, ", tAvatarInfo->OtherSkillState1[4]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OtherSkillState16 = %d, ", tAvatarInfo->OtherSkillState1[5]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OtherSkillState17 = %d, ", tAvatarInfo->OtherSkillState1[6]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OtherSkillState18 = %d, ", tAvatarInfo->OtherSkillState1[7]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OtherSkillState19 = %d, ", tAvatarInfo->OtherSkillState1[8]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OtherSkillState110 = %d, ", tAvatarInfo->OtherSkillState1[9]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OtherSkillState111 = %d, ", tAvatarInfo->OtherSkillState1[10]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OtherSkillState112 = %d, ", tAvatarInfo->OtherSkillState1[11]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OtherSkillState113 = %d, ", tAvatarInfo->OtherSkillState1[12]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OtherSkillState114 = %d, ", tAvatarInfo->OtherSkillState1[13]);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "OtherSkillSolUst = %d, ", tAvatarInfo->OtherSkillSolUst);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Fury = %d, ", tAvatarInfo->Fury);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "Premium = %d, ", tAvatarInfo->Premium);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "HideCostumeRegister = %d, ", tAvatarInfo->HideCostumeRegister);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "BuffDurationPill = %d ", tAvatarInfo->BuffDurationPill);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "where aName = '%s' ", tAvatarInfo->aName);
	strcat(mQUERY_FOR_THREAD1, tempQuery);
	sprintf(tempQuery, "AND aWorldNumber = %d;", g_env.world_num);
	strcat(mQUERY_FOR_THREAD1, tempQuery);

	if (!RECONNECT_TO_DATABASE02())
	{
		printf("!%s  %d Line\n", mQUERY_FOR_THREAD1, __LINE__);
		return;
	}
	iAffected = 0;
	if (mDB02.exec_query(mQUERY_FOR_THREAD1, CMySQL::CLEAR) != 0) {
		printf("! %d Line\n", __LINE__);
		return;
	}	
	return;
}

//WRITE_FOR_DB_LOG_FOR_QUERY
void MyDB::WRITE_FOR_DB_LOG_FOR_QUERY(void)
{
	__LogMgr()->Log("!%s\n", mQUERY);
}
//WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD
void MyDB::WRITE_FOR_DB_LOG_FOR_QUERY_FOR_THREAD(void)
{
	__LogMgr()->Log("!%s\n", mQUERY_FOR_THREAD);
}
//-------------------------------------------------------------------------------------------------