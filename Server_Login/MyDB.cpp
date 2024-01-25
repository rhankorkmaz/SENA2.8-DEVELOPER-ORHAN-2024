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
	if (mDB01.set_db_conn_info(mSERVER_INFO.mDB_1_IP[0], mSERVER_INFO.mDB_1_IP[1], mSERVER_INFO.mDB_1_PORT
		, g_env.db_name_str_obj.c_str(), mSERVER_INFO.mDB_1_ID, mSERVER_INFO.mDB_1_PASSWORD) < 0) {
		return FALSE;
	}
	if (!mDB01.connect()) {
		//mDB01.get_error_msg ().c_str ());
		return FALSE;
	}
#ifdef __COMMIT__
	if (mDB01.exec_query("SET AUTOCOMMIT=1;", CMySQL::CLEAR) != 0) {
		//LOG_TO_FILE_2 ("![%s] DB character false(%s).\n", __FUNCTION__, 
		mDB01.get_error_msg().c_str());
		return FALSE;
	}
#endif
#ifdef __TK__
	if (mDB01.exec_query("SET character SET latin5;", CMySQL::CLEAR) != 0) {
		//LOG_TO_FILE_2 ("![%s] DB character false(%s).\n", __FUNCTION__, 
		mDB01.get_error_msg().c_str());
		return FALSE;
	}
#endif

	//LOG_TO_FILE_4("%s, %d, %s, %s", mSERVER_INFO.mDB_2_IP[0], mSERVER_INFO.mDB_2_PORT, g_env.db2_name_str_obj.c_str (),mSERVER_INFO.mDB_2_ID);
	////LOG_TO_FILE_2("%s, %s\n", mSERVER_INFO.mDB_2_IP[1], mSERVER_INFO.mDB_2_PASSWORD);

	if (mDB02.set_db_conn_info(mSERVER_INFO.mDB_2_IP[0], mSERVER_INFO.mDB_2_IP[1], mSERVER_INFO.mDB_2_PORT
		, g_env.db2_name_str_obj.c_str(), mSERVER_INFO.mDB_2_ID, mSERVER_INFO.mDB_2_PASSWORD) < 0) {
		return FALSE;
	}
	if (!mDB02.connect()) {
		return FALSE;
	}

#ifdef __COMMIT__
	if (mDB02.exec_query("SET AUTOCOMMIT=1;", CMySQL::CLEAR) != 0) {
		//LOG_TO_FILE_2 ("![%s] DB character false(%s).\n", __FUNCTION__,
		mDB02.get_error_msg().c_str());
		return FALSE;
	}
#endif
#ifdef __TK__
	if (mDB02.exec_query("SET character SET latin5;", CMySQL::CLEAR) != 0) {
		//LOG_TO_FILE_2 ("![%s] DB character false(%s).\n", __FUNCTION__,
		mDB02.get_error_msg().c_str());
		return FALSE;
	}
#endif
	return TRUE;
}
//FREE
void MyDB::Free(void)
{
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
#ifdef __COMMIT__
	if (mDB01.exec_query("SET AUTOCOMMIT=1;", CMySQL::CLEAR) != 0) {
		//LOG_TO_FILE_2 ("![%s] DB character false(%s).\n", __FUNCTION__,
		mDB01.get_error_msg().c_str());
		return FALSE;
	}
#endif
#ifdef __TK__
	if (mDB01.exec_query("SET character SET latin5;", CMySQL::CLEAR) != 0) {
		//LOG_TO_FILE_2 ("![%s] DB character false(%s).\n", __FUNCTION__,
		mDB01.get_error_msg().c_str());
		return FALSE;
	}
#endif
	//LOG_TO_FILE("!Established reconnection with database server#01.\n");
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
		__LogMgr()->Log("!Reconnect to the database failed.\n");
		return FALSE;
	}
	__LogMgr()->Log("!Established reconnection with database server#02.\n");
	
	return TRUE;
}
//MAKE_QUERY_FOR_INSERT
void MyDB::MakeQueryForInsert(int tSort, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO* tAvatarInfo)
{
	int index01;
	int index02;
	char tempString01[1000];
	char tTableName[100];
	char aEquip[326];
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
	char InventorySocket[3456];
	char EquipSocket[352];
	char TradeSocket[217];
	char StoreSocket[1513];
	char SaveSocket[757];
	char aAutoConfig[82];

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
	TradeSocket[0] = '\0';
	for (index01 = 0; index01 < MAX_TRADE_SLOT_NUM; index01++)
	{
		sprintf(tempString01, "%09d%09d%09d", (tAvatarInfo->TradeSocket[index01][0] % 1000000000), (tAvatarInfo->TradeSocket[index01][1] % 1000000000), (tAvatarInfo->TradeSocket[index01][2] % 1000000000));
		strcat(TradeSocket, tempString01);
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

	AutoBuff[0] = '\0';
	for (index01 = 0; index01 < MAX_AUTOBUFF_SKİLL; index01++)
	{
		sprintf(tempString01, "%03d%03d", (tAvatarInfo->AutoBuffSmenu[index01][0] % 1000), (tAvatarInfo->AutoBuffSmenu[index01][1] % 1000));
		strcat(AutoBuff, tempString01);
	}

	AnimalExp[0] = '\0';
	for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
	{
		sprintf(tempString01, "%09d", (tAvatarInfo->AnimalExp[index01] % 1000000000));
		strcat(AnimalExp, tempString01);
	}

	AnimalStat[0] = '\0';
	for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
	{
		sprintf(tempString01, "%09d", (tAvatarInfo->AnimalStat[index01] % 1000000000));
		strcat(AnimalStat, tempString01);
	}

	PetInventory[0] = '\0';
	for (index01 = 0; index01 < 2; index01++)
	{
		for (index02 = 0; index02 < MAX_AVATAR_ANIMAL_NUM; index02++)
		{
			sprintf(tempString01, "%06d", (tAvatarInfo->PetInventoryTick[index01][index02] % 1000000));
			strcat(PetInventory, tempString01);
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


	char tempQuery[MAX_QUERY_BUFFER_SIZE];

	if (tSort == 1)
	{
		strcpy(mQUERY, "INSERT INTO AvatarInfo VALUES( now(), ");
	}
	if (tSort == 2)
	{
		strcpy(mQUERY, "INSERT INTO DeleteAvatarInfo VALUES( now(), ");
	}
	sprintf(tempQuery, "'%s', ", tID);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aVisibleState);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aSpecialState);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aPlayTime1);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aPlayTime2);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aKillOtherTribe);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", 1); //aworldnumber
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "'%s', ", tAvatarInfo->aName);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aTribe);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aPreviousTribe);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aGender);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aHeadType);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aFaceType);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aLevel1);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aLevel2);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aGeneralExperience1);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aGeneralExperience2);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aVitality);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aStrength);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aKi);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aWisdom);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aEatLifePotion);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aEatManaPotion);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->StrElx);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->AgiElx);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", (tAvatarInfo->YeniElx / 1000));
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", (tAvatarInfo->YeniElx % 1000));
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aStateBonusPoint);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aSkillPoint);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "'%s', ", aEquip);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aExpandInventoryDate);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aMoney);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "'%s', ", aInventory);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aTradeMoney);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "'%s', ", aTrade);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aExpandStoreDate);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aStoreMoney);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "'%s', ", aStoreItem);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "'%s', ", aSkill);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "'%s', ", aHotKey);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "'%s', ", aQuestInfo);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "'%s', ", aFriend);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "'%s', ", tAvatarInfo->aTeacher);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "'%s', ", tAvatarInfo->aStudent);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aTeacherPoint);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "'%s', ", tAvatarInfo->aGuildName);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aGuildRole);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "'%s', ", tAvatarInfo->aCallName);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aGuildMarkNum);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aGuildMarkEffect);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aLogoutInfo[0]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aLogoutInfo[1]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aLogoutInfo[2]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aLogoutInfo[3]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aLogoutInfo[4]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aLogoutInfo[5]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->ProtectionScroll);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->ProtectionCharm);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->HolyWater);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->SuperiorPill);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->ScrollofLoyality);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->ScrollofBattle);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->GodTempleKey);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->SolemGrounds);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->EdgeOfTaiyan);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->ScrollOfSeekers);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aKillMonsterNum);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->RankPoint);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->RankPrize);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aSearch);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->ExchangeHealtiks);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->ExchangeChiiks);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aTribeVoteDate);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->HealtAutoPot);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->ManaAutoPot);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aAnimal[0]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aAnimal[1]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aAnimal[2]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aAnimal[3]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aAnimal[4]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aAnimal[5]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aAnimal[6]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aAnimal[7]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aAnimal[8]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aAnimal[9]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aAnimalIndex);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aAnimalTime);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->LuckyCombine);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->LuckyUpgrade);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->LuckyDrop);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Title);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->ExtinctionScroll);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aUpradgeValue);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Beginner);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->BeginnerLevel);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OnlineHour);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Cppc);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->iUseOrnament);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->iSilverOrnamentRemainsTime);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->IslandOfBlood);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->IslandOfSoulMReal1);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->IslandOfSoulMReal2);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->IslandOfSoulMReal3);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->IslandOfSoulMReal4);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->IslandOfSoulMReal5);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->IslandOfSoulMReal6);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->SkillIncreaseCritHit);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->LifeOrDeath);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->iGoldOrnamentRemainsTime);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->BloodBoost);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->SoulBoost);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Registration);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->ExpPill);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->FactReturnScroll);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->PetExpBoost);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Costume[0]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Costume[1]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Costume[2]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Costume[3]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Costume[4]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Costume[5]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Costume[6]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Costume[7]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Costume[8]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Costume[9]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->CostumeInventory[0]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->CostumeInventory[1]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->CostumeInventory[2]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->CostumeInventory[3]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->CostumeInventory[4]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->CostumeInventory[5]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->CostumeInventory[6]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->CostumeInventory[7]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->CostumeInventory[8]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->CostumeInventory[9]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->SelectCostume);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->DamegeBoostScroll);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->HealtBoostScroll);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->CritBoostScroll);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->AutoBuffScroll);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "'%s', ", AutoBuff);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Hisar);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->SweetPateto);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "'%s', ", InventorySocket);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "'%s', ", EquipSocket);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "'%s', ", TradeSocket);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "'%s', ", StoreSocket);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Hunt7d);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Hunt5h);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Inventorybar);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->TradeBar);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d,", tAvatarInfo->BankBar);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->RebirtHall);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->PreServeCharm);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Chenjoho);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aRankPoint);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->aRank);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->FanctionNoticeScroll);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "'%s', ", AnimalExp);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "'%s', ", AnimalStat);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->DoubleMouthExp2x);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->VigilanteScroll);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->RafflaTicket);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->MountAbsorb);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->MountAbsorbe);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->FuryTime);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->BurstPill);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->RagePill);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->WarriorScroll);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->HeroPill);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->WingProtectionRune);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->LessDecressScroll);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->PetInventory);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "'%s', ", PetInventory);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->JoinWar);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->PlayerKill);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->MonsterKill);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->PlayTimeDay);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "'%s', ", aAutoConfig);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->BloodStained);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->FishingTime);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->BottleIndex);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->BottleTime);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Bottle[0]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Bottle[1]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Bottle[2]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Bottle[3]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Bottle[4]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Bottle[5]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Bottle[6]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Bottle[7]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Bottle[8]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Bottle[9]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->BottlePrice[0]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->BottlePrice[1]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->BottlePrice[2]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->BottlePrice[3]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->BottlePrice[4]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->BottlePrice[5]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->BottlePrice[6]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->BottlePrice[7]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->BottlePrice[8]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->BottlePrice[9]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OtherSkill[0]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OtherSkill[1]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OtherSkill[2]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OtherSkill[3]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OtherSkill[4]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OtherSkill[5]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OtherSkill[6]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OtherSkill[7]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OtherSkill[8]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OtherSkill[9]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OtherSkill[10]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OtherSkill[11]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OtherSkill[12]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OtherSkill[13]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OtherSkillState1[0]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OtherSkillState1[1]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OtherSkillState1[2]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OtherSkillState1[3]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OtherSkillState1[4]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OtherSkillState1[5]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OtherSkillState1[6]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OtherSkillState1[7]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OtherSkillState1[8]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OtherSkillState1[9]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OtherSkillState1[10]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OtherSkillState1[11]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OtherSkillState1[12]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OtherSkillState1[13]);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->OtherSkillSolUst);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Fury);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->Premium);
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d, ", tAvatarInfo->HideCostumeRegister); // FanctionNoticeScroll BuffDurationPill
	strcat(mQUERY, tempQuery);
	sprintf(tempQuery, "%d ", tAvatarInfo->BuffDurationPill);// FanctionNoticeScroll BuffDurationPill
	strcat(mQUERY, tempQuery);
	strcat(mQUERY, ")");
}
//DB_PROCESS_01
BOOL MyDB::DB_PROCESS_01(void)
{
	int iAffected;
	int iCounts;
	long tMaxPlayerNum;
	long tAddPlayerNum;
	long tGagePlayerNum;
	MYSQL_ROW row;
	MYSQL_RES* res = NULL;

	sprintf(mQUERY,
		"SELECT mMaxUserNum, mAddUserNum, mGageUserNum "
		"FROM %s "
		"WHERE aWorldNumber = %d", mSERVER_INFO.mDB_2_Table01, mSERVER_INFO.mWorldNumber);
	if (!RECONNECT_TO_DATABASE02())
	{
		return FALSE;
	}
	iAffected = 0;
	if ((iAffected = mDB02.exec_query(mQUERY)) < 0)
	{
		//LOG_TO_FILE_2 ("![CRITICAL - (1)] The query execution failed in (%s - %d).\n", __FILE__, __LINE__);
		//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mDB02.get_error_msg ().c_str ());
		return FALSE;
	}

	iCounts = 0;
	res = mDB02.get_res();
	if (res == NULL) {
		//LOG_TO_FILE_1 ("!Query failed - (%s).\n", mQUERY);
		//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mDB02.get_error_msg ().c_str ());
		return FALSE;
	}

	while ((row = mysql_fetch_row(res))) {
		tMaxPlayerNum = ::atol(row[0]);
		tAddPlayerNum = ::atol(row[1]);
		tGagePlayerNum = ::atol(row[2]);
		iCounts++;
	}
	mDB02.clear_res();
	if (iCounts != 1) {
		//LOG_TO_FILE_1 ("!Result record set count = %d.\n", iCounts);
		return FALSE;
	}

	if (tMaxPlayerNum < 1)
	{
		mGAME.mMaxPlayerNum = 0;
		mGAME.mAddPlayerNum = 0;
		mGAME.mGagePlayerNum = tGagePlayerNum;
		mGAME.mPresentPlayerNum = -1;
	}
	else
	{
		mGAME.mMaxPlayerNum = tMaxPlayerNum;
		mGAME.mAddPlayerNum = tAddPlayerNum;
		mGAME.mGagePlayerNum = tGagePlayerNum;
		if (mGAME.mPresentPlayerNum == -1)
		{
			mGAME.mPresentPlayerNum = 0;
		}
	}

	sprintf(mQUERY,
		"SELECT Island, `Partition`, World "
		"FROM RecommandInfo "
		"ORDER BY Island, `Partition`, World "
		"LIMIT %d ", MAX_SIZE_OF_RCMD);

	if (!RECONNECT_TO_DATABASE02())
	{
		return FALSE;
	}
	iAffected = 0;
	if ((iAffected = mDB02.exec_query(mQUERY)) < 0)
	{
		//LOG_TO_FILE_2 ("![CRITICAL - (1)] The query execution failed in (%s - %d).\n", __FILE__, __LINE__);
		//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mDB02.get_error_msg ().c_str ());
		return FALSE;
	}

	iCounts = 0;
	res = mDB02.get_res();
	if (res == NULL) {
		//LOG_TO_FILE_1 ("!Query failed - (%s).\n", mQUERY);
		//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mDB02.get_error_msg ().c_str ());
		return FALSE;
	}

	while ((row = mysql_fetch_row(res))) {
		mGAME.mRcmdIld[iCounts] = ::atoi(row[0]);
		mGAME.mRcmdPtt[iCounts] = ::atoi(row[1]);
		mGAME.mRcmdWrd[iCounts] = ::atoi(row[2]);
		//LOG_TO_FILE_3("Recommand world : %d %d %d\n", mGAME.mRcmdIld[iCounts], mGAME.mRcmdPtt[iCounts], mGAME.mRcmdWrd[iCounts]);
		iCounts++;
	}
	mDB02.clear_res();

	if (iCounts != 4) {
		for (iCounts = 0; iCounts < MAX_SIZE_OF_RCMD; iCounts++) {
			if (mGAME.mRcmdIld[iCounts] > 0) {
				continue;
			}
			else {
				mGAME.mRcmdIld[iCounts] = 0;
				mGAME.mRcmdPtt[iCounts] = 0;
				mGAME.mRcmdWrd[iCounts] = iCounts + 1;
			}
		}
	}

	//LOG_TO_FILE("!MyDB::DB_PROCESS_01 success.\n");
	return TRUE;
}

void MyDB::DB_PROCESS_02(char tIP[16], char tID[MAX_USER_ID_LENGTH], char tPassword[MAX_USER_PASSWORD_LENGTH], char uID[MAX_USER_ID_LENGTH], int* tCheckMOTP,
	char tMousePassword[MAX_MOUSE_PASSWORD_LENGTH], int* tSecretCard, int* tUserSort, int* tGoodFellow, int* tUserRandom, int* tLoginPremium, int* tTraceState,
	char* tBonus100Money, int* tPremiumServerExpirationDate, int* tSaveMoney, int tSaveItem[MAX_SAVE_ITEM_SLOT_NUM][4], AVATAR_INFO tAvatarInfo[MAX_USER_AVATAR_NUM],
	AUTH_INFO* tAuthInfo, int* tResult, char* tFirstLogin, int* tSeyisbar, int tSaveSocket[MAX_SAVE_ITEM_SLOT_NUM][3])
{
	int index01;
	int index02;
	int index03;
	int aWorldNumber = 0;
	char tempString01[1000];
	char tempBuffer[4];
	int iAffected;
	int iCounts;
	long uLoginState;
	char uIP[16];
	char uPassword[MAX_USER_PASSWORD_LENGTH];
	long uCheckMOTP;
	char uMousePassword[MAX_MOUSE_PASSWORD_LENGTH];
	long uSecretCard;
	long uBlockInfo;
	long uUserSort;
	long uGoodFellow;
	long UserRandom;
	long uLoginPremium;
	long uTraceState;
	char uBonus100Money;
	long uPremiumServerExpirationDate;
	long uIDNum;
	long uSaveMoney;
	int  SeyisBar;
	char uSaveItem[701];
	char aName[MAX_USER_AVATAR_NUM][MAX_AVATAR_NAME_LENGTH];
	char uIDForCheck[MAX_USER_ID_LENGTH];
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
	char gMember[851];
	char AutoBuff[49];
	char AnimalExp[91];
	char AnimalStat[91];
	char PetInventory[121];
	char aAutoConfig[82];
	float tMaxGeneralExperienceRange;
	int tPresentGeneralExperienceRatio;
	int tNextGeneralExperienceRatio;
	bool RealGuild[MAX_USER_AVATAR_NUM];
	bool CheckGuild[MAX_USER_AVATAR_NUM];
	byte AuthType;
	byte FindFlag;
	byte MoveFlag;
	byte MoveZoneFlag;
	byte CallFlag;
	byte HideFlag;
	byte ShowFlag;
	byte KickFlag;
	byte BlockFlag;
	byte MonCallFlag;
	byte EquipFlag;
	byte UnequipFlag;
	byte YchatFlag;
	byte NchatFlag;
	byte NoticeFlag;
	byte ItemFlag;
	byte MoneyFlag;
	byte ExpFlag;
	byte DieFlag;
	byte GodFlag;
	byte ChatFlag;
	byte TradeFlag;
	byte ShopFlag;
	byte PShopFlag;
	byte GItemFlag;
	byte DItemFlag;
	byte AttackFlag;
	byte UZonemoveFlag;
	long Explock;
	int DailyRewardTime;
	MYSQL_ROW row;
	MYSQL_RES* res = NULL;
	sprintf(mQUERY, "select uLoginState,uIP,a.uID,uPassword,uCheckMOTP,ifnull(uMousePassword, ''), "
		"uSecretCard, uBlockInfo, uUserSort, uGoodFellow, uLoginPremium, uTraceState, ifnull(AuthType, 0), "
		"ifnull(FindFlag, 0), ifnull(MoveFlag, 0), ifnull(MoveZoneFlag, 0), ifnull(CallFlag, 0), ifnull(HideFlag, 0), "
		"ifnull(ShowFlag, 0), ifnull(KickFlag, 0), ifnull(BlockFlag, 0), ifnull(MonCallFlag, 0), ifnull(EquipFlag, 0), "
		"ifnull(UnequipFlag, 0), ifnull(YchatFlag, 0), ifnull(NchatFlag, 0), ifnull(NoticeFlag, 0), ifnull(ItemFlag, 0), "
		"ifnull(MoneyFlag, 0), ifnull(ExpFlag, 0), ifnull(DieFlag, 0), ifnull(GodFlag, 0), ifnull(ChatFlag, 0), "
		"ifnull(TradeFlag, 0), ifnull(ShopFlag, 0), ifnull(PShopFlag, 0), ifnull(GItemFlag, 0), ifnull(DItemFlag, 0), "
		"ifnull(AttackFlag, 0), ifnull(UZonemoveFlag, 0), ifnull(DailyRewardTime, 0),uBonus100Money, uSecretCard, uPremiumServerExpirationDate , ifnull(Explock,0) from % s a left join % s b on a.uID = b.uID where a.uID = '%s'; ",
		mSERVER_INFO.mDB_1_Table01, mSERVER_INFO.mDB_1_Table08, tID);

	if (!RECONNECT_TO_DATABASE02())
	{
		__LogMgr()->Log("![WARNING - (6)] Unable to connect to the database[%s].\n",
			mSERVER_INFO.mDB_1_Table01);
		*tResult = 6;
		return;
	}
	iAffected = 0;
	if ((iAffected = mDB02.exec_query(mQUERY)) < 0) {
		__LogMgr()->Log("![WARNING - (6)] The query execution failed.\n");
		__LogMgr()->Log("\t\t\tWhy - %s\n", mDB02.get_error_msg().c_str());
		*tResult = 6;
		return;
	}
	iCounts = 0;

	res = mDB02.get_res();
	if (res == NULL) {
		__LogMgr()->Log("!Query failed - (%s).\n", mQUERY);
		__LogMgr()->Log("\t\t\tWhy - %s\n", mDB02.get_error_msg().c_str());
		*tResult = 6;
		return;
	}
	while ((row = mysql_fetch_row(res))) {
		uLoginState = ::atol(row[0]);
		snprintf(uIP, 16, "%s", row[1]);
		snprintf(uID, MAX_USER_ID_LENGTH, "%s", row[2]);
		snprintf(uPassword, MAX_USER_PASSWORD_LENGTH, "%s", row[3]);
		uCheckMOTP = ::atol(row[4]);
		snprintf(uMousePassword, MAX_MOUSE_PASSWORD_LENGTH, "%s", row[5]);
		uSecretCard = ::atol(row[6]);
		uBlockInfo = ::atol(row[7]);
		uUserSort = ::atol(row[8]);
		uGoodFellow = ::atol(row[9]);
		uLoginPremium = ::atol(row[10]);
		uTraceState = ::atol(row[11]);
		AuthType = ::atol(row[12]);
		FindFlag = ::atol(row[13]);
		MoveFlag = ::atol(row[14]);
		MoveZoneFlag = ::atol(row[15]);
		CallFlag = ::atol(row[16]);
		HideFlag = ::atol(row[17]);
		ShowFlag = ::atol(row[18]);
		KickFlag = ::atol(row[19]);
		BlockFlag = ::atol(row[20]);
		MonCallFlag = ::atol(row[21]);
		EquipFlag = ::atol(row[22]);
		UnequipFlag = ::atol(row[23]);
		YchatFlag = ::atol(row[24]);
		NchatFlag = ::atol(row[25]);
		NoticeFlag = ::atol(row[26]);
		ItemFlag = ::atol(row[27]);
		MoneyFlag = ::atol(row[28]);
		ExpFlag = ::atol(row[29]);
		DieFlag = ::atol(row[30]);
		GodFlag = ::atol(row[31]);
		ChatFlag = ::atol(row[32]);
		TradeFlag = ::atol(row[33]);
		ShopFlag = ::atol(row[34]);
		PShopFlag = ::atol(row[35]);
		GItemFlag = ::atol(row[36]);
		DItemFlag = ::atol(row[37]);
		AttackFlag = ::atol(row[38]);
		UZonemoveFlag = ::atol(row[39]);
		DailyRewardTime = ::atoi(row[40]);
		uBonus100Money = *row[41];
		uSecretCard = ::atol(row[42]);
		uPremiumServerExpirationDate = ::atol(row[43]); // @_Premium_Server_@
		Explock = ::atol(row[44]);
		++iCounts;
	}

	mDB02.clear_res();
	if (iCounts != 1) {
		__LogMgr()->Log("![WARNING - (6)] As a result of a number of rows is not returned by the query 1.\n");
		__LogMgr()->Log("\t\t\tRow counts = %d.\n", iCounts);
		*tResult = 6;
		return;
	}

	if (strcmp(tPassword, uPassword) != 0)
	{
		__LogMgr()->Log("![WARNING - (7)] Your password is difference.\n");
		*tResult = 7;
		return;
	}
	if (uLoginState == 1)
	{
		*tResult = 8;
		return;
	}
	if (uBlockInfo >= mGAME.ReturnNowDate())
	{
		*tResult = 9;
		return;
	}
	if (0 < uUserSort)
		AuthType = 1;
	*tCheckMOTP = uCheckMOTP;
	strcpy(tMousePassword, uMousePassword);
	*tSecretCard = uSecretCard;
	*tUserSort = uUserSort;
	*tGoodFellow = uGoodFellow;
	*tUserRandom = UserRandom;
	*tLoginPremium = uLoginPremium;
	*tTraceState = uTraceState;
	*tBonus100Money = uBonus100Money;
	*tPremiumServerExpirationDate = uPremiumServerExpirationDate;
	tAuthInfo->AuthType = AuthType;
	tAuthInfo->FindFlag = FindFlag;
	tAuthInfo->MoveFlag = MoveFlag;
	tAuthInfo->MoveZoneFlag = MoveZoneFlag;
	tAuthInfo->CallFlag = CallFlag;
	tAuthInfo->HideFlag = HideFlag;
	tAuthInfo->ShowFlag = ShowFlag;
	tAuthInfo->KickFlag = KickFlag;
	tAuthInfo->BlockFlag = BlockFlag;
	tAuthInfo->MonCallFlag = MonCallFlag;
	tAuthInfo->EquipFlag = EquipFlag;
	tAuthInfo->UnequipFlag = UnequipFlag;
	tAuthInfo->YchatFlag = YchatFlag;
	tAuthInfo->NchatFlag = NchatFlag;
	tAuthInfo->NoticeFlag = NoticeFlag;
	tAuthInfo->ItemFlag = ItemFlag;
	tAuthInfo->MoneyFlag = MoneyFlag;
	tAuthInfo->ExpFlag = ExpFlag;
	tAuthInfo->DieFlag = DieFlag;
	tAuthInfo->GodFlag = GodFlag;
	tAuthInfo->ChatFlag = ChatFlag;
	tAuthInfo->TradeFlag = TradeFlag;
	tAuthInfo->ShopFlag = ShopFlag;
	tAuthInfo->PShopFlag = PShopFlag;
	tAuthInfo->GItemFlag = GItemFlag;
	tAuthInfo->DItemFlag = DItemFlag;
	tAuthInfo->AttackFlag = AttackFlag;
	tAuthInfo->UZonemoveFlag = UZonemoveFlag;
	tAuthInfo->DailyRewardTime = DailyRewardTime;
	tAuthInfo->Explock = Explock;

	sprintf(mQUERY, "select count(uID) from %s where uID='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_2_Table02, uID, mSERVER_INFO.mWorldNumber);
	if (!RECONNECT_TO_DATABASE01())
	{
		*tResult = 6;
		return;
	}
	iAffected = 0;
	if ((iAffected = mDB01.exec_query(mQUERY)) < 0) {
		*tResult = 6;
		return;
	}
	res = mDB01.get_res();
	if (res == NULL) {
		*tResult = 6;
		return;
	}
	iCounts = 0;

	while ((row = mysql_fetch_row(res))) {
		uIDNum = ::atol(row[0]);
		++iCounts;
	}
	mDB01.clear_res();

	if (iCounts != 1) {
		*tResult = 6;
		return;
	}

	::memset(uSaveItem, '0', 700);
	::memset(SaveSocket, '0', sizeof(SaveSocket));
	if (uIDNum == 0)
	{
		uSaveMoney = 0;
		SeyisBar = 0;
		uSaveItem[700] = '\0';
		strcpy(aName[0], "");
		strcpy(aName[1], "");
		strcpy(aName[2], "");
		SaveSocket[756] = '\0';
		sprintf(mQUERY, "insert into %s values ( now(),%d, '%s',%d,'%s','%s','%s','%s',%d,'%s')", mSERVER_INFO.mDB_2_Table02, mSERVER_INFO.mWorldNumber, uID, uSaveMoney, uSaveItem, aName[0], aName[1], aName[2], SeyisBar, SaveSocket);
		//*tFirstLogin = '1';
		if (!RECONNECT_TO_DATABASE01())
		{
			*tResult = 6;
			return;
		}
		iAffected = 0;
		if ((mDB01.exec_query(mQUERY, CMySQL::CLEAR)) != 0) {
			*tResult = 6;
			return;
		}
	}
	else
	{
		sprintf(mQUERY, "select uSaveMoney,uSaveItem,aName01,aName02,aName03,SeyisBar,SaveSocket from %s where uID='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_2_Table02, uID, mSERVER_INFO.mWorldNumber);
		//*tFirstLogin = '0';
		if (!RECONNECT_TO_DATABASE01())
		{
			*tResult = 6;
			return;
		}
		iAffected = 0;
		if ((iAffected = mDB01.exec_query(mQUERY)) < 0) {
			*tResult = 6;
			return;
		}
		iCounts = 0;

		res = mDB01.get_res();
		if (res == NULL) {
			*tResult = 6;
			return;
		}
		while (row = mysql_fetch_row(res)) {
			uSaveMoney = ::atol(row[0]);
			snprintf(uSaveItem, 701, "%s", row[1]);
			::snprintf(aName[0], MAX_AVATAR_NAME_LENGTH, "%s", row[2]);
			::snprintf(aName[1], MAX_AVATAR_NAME_LENGTH, "%s", row[3]);
			::snprintf(aName[2], MAX_AVATAR_NAME_LENGTH, "%s", row[4]);
			SeyisBar = ::atoi(row[5]);
			snprintf(SaveSocket, sizeof(SaveSocket), "%s", row[6]);
			++iCounts;
		}
		mDB01.clear_res();

		if (1 != iCounts) {
			
			*tResult = 6;
			return;
		}
	}

	*tSaveMoney = uSaveMoney;
	*tSeyisbar = SeyisBar;
	for (index01 = 0; index01 < MAX_SAVE_ITEM_SLOT_NUM; index01++)
	{
		CopyMemory(&tempString01[0], &uSaveItem[(index01 * 25 + 0)], 5);
		tempString01[5] = '\0';
		tSaveItem[index01][0] = atoi(tempString01);
		CopyMemory(&tempString01[0], &uSaveItem[(index01 * 25 + 5)], 3);
		tempString01[3] = '\0';
		tSaveItem[index01][1] = atoi(tempString01);
		CopyMemory(&tempString01[0], &uSaveItem[(index01 * 25 + 8)], 9);
		tempString01[9] = '\0';
		tSaveItem[index01][2] = atoi(tempString01);
		CopyMemory(&tempString01[0], &uSaveItem[(index01 * 25 + 17)], 8);
		tempString01[8] = '\0';
		tSaveItem[index01][3] = atoi(tempString01);
		//LOG_TO_FILE_4("------> %d %d %d %d\n", tSaveItem[index01][0], tSaveItem[index01][1], tSaveItem[index01][2], tSaveItem[index01][3]);
	}
	for (index01 = 0; index01 < MAX_SAVE_ITEM_SLOT_NUM; index01++)
	{
		CopyMemory(&tempString01[0], &SaveSocket[(index01 * 27 + 0)], 9);
		tempString01[9] = '\0';
		tSaveSocket[index01][0] = atoi(tempString01);
		CopyMemory(&tempString01[0], &SaveSocket[(index01 * 27 + 9)], 9);
		tempString01[9] = '\0';
		tSaveSocket[index01][1] = atoi(tempString01);
		CopyMemory(&tempString01[0], &SaveSocket[(index01 * 27 + 18)], 9);
		tempString01[9] = '\0';
		tSaveSocket[index01][2] = atoi(tempString01);
		//LOG_TO_FILE_4("------> %d %d %d %d\n", tSaveItem[index01][0], tSaveItem[index01][1], tSaveItem[index01][2], tSaveItem[index01][3]);
	}
	for (index01 = 0; index01 < MAX_USER_AVATAR_NUM; index01++)
	{
		RealGuild[index01] = false;
		CheckGuild[index01] = false;
		::memset(gMember, 0, 851);
		strcpy(tAvatarInfo[index01].aName, aName[index01]);
		if (strcmp(tAvatarInfo[index01].aName, "") == 0)
		{
			continue;
		}
		sprintf(mQUERY,
			"SELECT IFNULL(b.aWorldNumber, %d), IFNULL(b.gMember, '') "
			",a.uID"//2
			",a.aVisibleState"//3
			",a.aSpecialState"//4
			",a.aPlayTime1"//5
			",a.aPlayTime2"//6
			",a.aKillOtherTribe"//7
			",a.aTribe"//9
			",a.aPreviousTribe"//10
			",a.aGender"//11
			",a.aHeadType"//12
			",a.aFaceType"//13
			",a.aLevel1"
			",a.aLevel2"
			",a.aGeneralExperience1"
			",a.aGeneralExperience2"
			",a.aVitality"
			",a.aStrength"
			",a.aKi"//20
			",a.aWisdom"
			",a.aEatLifePotion"
			",a.aEatManaPotion"
			",a.StrElx"
			",a.AgiElx"//
			",a.aStateBonusPoint"
			",a.aSkillPoint"
			",a.aEquip"
			",a.aExpandInventoryDate"
			",a.aMoney"
			",a.aInventory"
			",a.aTradeMoney"//30
			",a.aTrade"
			",a.aExpandStoreDate"
			",a.aStoreMoney"
			",a.aStoreItem"
			",a.aSkill"
			",a.aHotKey"
			",a.aQuestInfo"
			",a.aFriend"
			",a.aTeacher"
			",a.aStudent"//40
			",a.aTeacherPoint"
			",a.aGuildName"
			",a.aGuildRole"
			",a.aCallName"
			",a.aGuildMarkNum"
			",a.aGuildMarkEffect"
			",a.aLogoutInfo01"
			",a.aLogoutInfo02"
			",a.aLogoutInfo03"
			",a.aLogoutInfo04"//50
			",a.aLogoutInfo05"
			",a.aLogoutInfo06"
			",a.ProtectionScroll"
			",a.ProtectionCharm"
			",a.HolyWater"
			",a.SuperiorPill"
			",a.ScrollofLoyality"
			",a.ScrollofBattle"
			",a.GodTempleKey"
			",a.SolemGrounds"//60
			",a.EdgeOfTaiyan"
			",a.ScrollOfSeekers"
			",a.aKillMonsterNum"
			",a.RankPoint"
			",a.RankPrize"
			",a.aSearch"
			",a.ExchangeHealtiks"
			",a.ExchangeChiiks"
			",a.aTribeVoteDate"
			",a.HealtAutoPot"
			",a.ManaAutoPot"			
			",a.aAnimal01"
			",a.aAnimal02"
			",a.aAnimal03"
			",a.aAnimal04"
			",a.aAnimal05"
			",a.aAnimal06"
			",a.aAnimal07"
			",a.aAnimal08"
			",a.aAnimal09"
			",a.aAnimal10"//80
			",a.aAnimalIndex"
			",a.aAnimalTime"
			",a.LuckyCombine"
			",a.LuckyUpgrade"
			",a.LuckyDrop"
			",a.Title"//86
			",a.ExtinctionScroll"
			",a.aUpradgeValue"
			",a.Beginner"
			",a.BeginnerLevel"
			",a.OnlineHour"//90
			",a.Cppc"
			",a.iUseOrnament"
			",a.iSilverOrnamentRemainsTime"
			",a.IslandOfBlood"
			",a.IslandOfSoulMReal1"
			",a.IslandOfSoulMReal2"
			",a.IslandOfSoulMReal3"
			",a.IslandOfSoulMReal4"
			",a.IslandOfSoulMReal5"
			",a.IslandOfSoulMReal6"//100
			",a.SkillIncreaseCritHit"
			",a.LifeOrDeath"
			",a.iGoldOrnamentRemainsTime"
			",a.BloodBoost"
			",a.SoulBoost"
			",a.Registration"
			",a.ExpPill"
			",a.FactReturnScroll"
			",a.PetExpBoost"
			",a.Costume1"//110
			",a.Costume2"
			",a.Costume3"
			",a.Costume4"
			",a.Costume5"
			",a.Costume6"
			",a.Costume7"
			",a.Costume8"
			",a.Costume9"
			",a.Costume10"
			",a.CostumeInventory1"//120
			",a.CostumeInventory2"
			",a.CostumeInventory3"
			",a.CostumeInventory4"
			",a.CostumeInventory5"
			",a.CostumeInventory6"
			",a.CostumeInventory7"
			",a.CostumeInventory8"
			",a.CostumeInventory9"
			",a.CostumeInventory10"
			",a.SelectCostume"//130
			",a.DamegeBoostScroll"
			",a.HealtBoostScroll"
			",a.CritBoostScroll"
			",a.AutoBuffScroll"
			",a.AutoBuffSmenu"
			",a.FishBread"
			",a.SweetPateto"
			",a.InventorySocket"
			",a.EquipSocket"
			",a.TradeSocket"//140
			",a.StoreSocket"
			",a.Hunt7d"
			",a.Hunt5h"
			",a.Inventorybar"
			",a.TradeBar"
			",a.BankBar"
			",a.RebirtHall"
			",a.PreServeCharm"
			",a.Chenjoho"
			",a.aRankPoint"
			",a.aRank"
			",a.FanctionNoticeScroll"
			",a.AnimalExp"
			",a.AnimalStat"
			",a.DoubleMouthExp2x"
			",a.VigilanteScroll"
			",a.RafflaTicket"
			",a.MountAbsorb"
			",a.MountAbsorbe"//160
			",a.DamageIcreaseSolUst"
			",a.BurstPill"
			",a.RagePill"
			",a.WarriorScroll"
			",a.HeroPill"
			",a.WingProtectionRune"
			",a.LessDecressScroll"
			",a.PetInventory"
			",a.PetInventoryTick"//168
			",a.JoinWar"
			",a.PlayerKill"
			",a.MonsterKill"
			",a.PlayTimeDay"//175
			",a.AttAtakElixir"
			",a.AttDefElixir"
			",a.AutoHuntConfing"
			",a.BloodStained"
			",a.FishingTime"
			",a.BottleIndex"
			",a.BottleTime"
			//",a.Bottle0"
			",a.Bottle1"
			",a.Bottle2"
			",a.Bottle3"
			",a.Bottle4"
			",a.Bottle5"
			",a.Bottle6"
			",a.Bottle7"
			",a.Bottle8"
			",a.Bottle9"
			",a.Bottle10"//80			
			",a.BottlePrice1"
			",a.BottlePrice2"
			",a.BottlePrice3"
			",a.BottlePrice4"
			",a.BottlePrice5"
			",a.BottlePrice6"
			",a.BottlePrice7"
			",a.BottlePrice8"
			",a.BottlePrice9"
			",a.BottlePrice10"//80
			",a.OtherSkill1"
			",a.OtherSkill2"
			",a.OtherSkill3"
			",a.OtherSkill4"
			",a.OtherSkill5"
			",a.OtherSkill6"
			",a.OtherSkill7"
			",a.OtherSkill8"
			",a.OtherSkill9"
			",a.OtherSkill10"//80
			",a.OtherSkill11"
			",a.OtherSkill12"
			",a.OtherSkill13"
			",a.OtherSkill14"
			",a.OtherSkillState11"
			",a.OtherSkillState12"
			",a.OtherSkillState13"
			",a.OtherSkillState14"
			",a.OtherSkillState15"
			",a.OtherSkillState16"//80
			",a.OtherSkillState17"
			",a.OtherSkillState18"
			",a.OtherSkillState19"
			",a.OtherSkillState110"
			",a.OtherSkillState111"
			",a.OtherSkillState112"//80
			",a.OtherSkillState113"
			",a.OtherSkillState114"
			",a.OtherSkillSolUst"
			",a.Fury"
			",a.Premium"
			",a.HideCostumeRegister"//// FanctionNoticeScroll BuffDurationPill
			",a.BuffDurationPill"
			" FROM %s a "
			"LEFT OUTER JOIN GuildInfo b ON a.aGuildName = b.gName "
			"WHERE a.aName='%s' AND a.aWorldNumber = %d "
			, mSERVER_INFO.mWorldNumber, mSERVER_INFO.mDB_2_Table03, tAvatarInfo[index01].aName, mSERVER_INFO.mWorldNumber);

		if (!RECONNECT_TO_DATABASE01())
		{
	
			*tResult = 6;
			return;
		}
		iAffected = 0;
		if ((iAffected = mDB01.exec_query(mQUERY)) < 0) {
			
			*tResult = 6;
			return;
		}
		iCounts = 0;
		res = mDB01.get_res();
		if (res == NULL) {
		
			*tResult = 6;
			return;
		}
		while (row = mysql_fetch_row(res)) {
			aWorldNumber = ::atoi(row[0]);
			if (aWorldNumber == mSERVER_INFO.mWorldNumber) {
				RealGuild[index01] = true;
				::snprintf(gMember, 851, "%s", row[1]);
			}
			else if (!RealGuild[index01]) {
				::strcpy(gMember, "");
			}

			if (iCounts == 0) {
				::strncpy(uIDForCheck, row[2], MAX_USER_ID_LENGTH - 1);
				tAvatarInfo[index01].aVisibleState = ::atoi(row[3]);
				tAvatarInfo[index01].aSpecialState = ::atoi(row[4]);
				tAvatarInfo[index01].aPlayTime1 = ::atoi(row[5]);
				tAvatarInfo[index01].aPlayTime2 = ::atoi(row[6]);
				tAvatarInfo[index01].aKillOtherTribe = ::atoi(row[7]);
				tAvatarInfo[index01].aTribe = ::atoi(row[8]);
				tAvatarInfo[index01].aPreviousTribe = ::atoi(row[9]);
				tAvatarInfo[index01].aGender = ::atoi(row[10]);
				tAvatarInfo[index01].aHeadType = ::atoi(row[11]);
				tAvatarInfo[index01].aFaceType = ::atoi(row[12]);
				tAvatarInfo[index01].aLevel1 = ::atoi(row[13]);
				tAvatarInfo[index01].aLevel2 = ::atoi(row[14]);
				tAvatarInfo[index01].aGeneralExperience1 = ::atoi(row[15]);
				tAvatarInfo[index01].aGeneralExperience2 = ::atoi(row[16]);
				tAvatarInfo[index01].aVitality = ::atoi(row[17]);
				tAvatarInfo[index01].aStrength = ::atoi(row[18]);
				tAvatarInfo[index01].aKi = ::atoi(row[19]);
				tAvatarInfo[index01].aWisdom = ::atoi(row[20]);
				tAvatarInfo[index01].aEatLifePotion = ::atoi(row[21]);
				tAvatarInfo[index01].aEatManaPotion = ::atoi(row[22]);
				tAvatarInfo[index01].StrElx = ::atoi(row[23]);
				tAvatarInfo[index01].AgiElx = ::atoi(row[24]);
				tAvatarInfo[index01].aStateBonusPoint = ::atoi(row[25]);
				tAvatarInfo[index01].aSkillPoint = ::atoi(row[26]);
				::strncpy(aEquip, row[27], sizeof(aEquip));
				tAvatarInfo[index01].aExpandInventoryDate = ::atoi(row[28]);
				tAvatarInfo[index01].aMoney = ::atoi(row[29]);
				::strncpy(aInventory, row[30], sizeof(aInventory));
				tAvatarInfo[index01].aTradeMoney = ::atoi(row[31]);
				::strncpy(aTrade, row[32], sizeof(aTrade));
				tAvatarInfo[index01].aExpandStoreDate = ::atoi(row[33]);
				tAvatarInfo[index01].aStoreMoney = ::atoi(row[34]);
				::strncpy(aStoreItem, row[35], sizeof(aStoreItem));
				::strncpy(aSkill, row[36], sizeof(aSkill));
				::strncpy(aHotKey, row[37], sizeof(aHotKey));
				::strncpy(aQuestInfo, row[38], sizeof(aQuestInfo));
				::strncpy(aFriend, row[39], sizeof(aFriend));
				::strncpy(tAvatarInfo[index01].aTeacher, row[40], MAX_AVATAR_NAME_LENGTH - 1);
				::strncpy(tAvatarInfo[index01].aStudent, row[41], MAX_AVATAR_NAME_LENGTH - 1);
				tAvatarInfo[index01].aTeacherPoint = ::atoi(row[42]);
				::strncpy(tAvatarInfo[index01].aGuildName, row[43], MAX_GUILD_NAME_LENGTH - 1);
				tAvatarInfo[index01].aGuildRole = ::atoi(row[44]);
				::strncpy(tAvatarInfo[index01].aCallName, row[45], MAX_CALL_NAME_LENGTH - 1);
				tAvatarInfo[index01].aGuildMarkNum = ::atoi(row[46]);
				tAvatarInfo[index01].aGuildMarkEffect = ::atoi(row[47]);
				tAvatarInfo[index01].aLogoutInfo[0] = ::atoi(row[48]);
				tAvatarInfo[index01].aLogoutInfo[1] = ::atoi(row[49]);
				tAvatarInfo[index01].aLogoutInfo[2] = ::atoi(row[50]);
				tAvatarInfo[index01].aLogoutInfo[3] = ::atoi(row[51]);
				tAvatarInfo[index01].aLogoutInfo[4] = ::atoi(row[52]);
				tAvatarInfo[index01].aLogoutInfo[5] = ::atoi(row[53]);
				tAvatarInfo[index01].ProtectionScroll = ::atoi(row[54]);
				tAvatarInfo[index01].ProtectionCharm = ::atoi(row[55]);
				tAvatarInfo[index01].HolyWater = ::atoi(row[56]);
				tAvatarInfo[index01].SuperiorPill = ::atoi(row[57]);
				tAvatarInfo[index01].ScrollofLoyality = ::atoi(row[58]);
				tAvatarInfo[index01].ScrollofBattle = ::atoi(row[59]);
				tAvatarInfo[index01].GodTempleKey = ::atoi(row[60]);
				tAvatarInfo[index01].SolemGrounds = ::atoi(row[61]);
				tAvatarInfo[index01].EdgeOfTaiyan = ::atoi(row[62]);
				tAvatarInfo[index01].ScrollOfSeekers = ::atoi(row[63]);
				tAvatarInfo[index01].aKillMonsterNum = ::atoi(row[64]);
				tAvatarInfo[index01].RankPoint = ::atoi(row[65]);
				tAvatarInfo[index01].RankPrize = ::atoi(row[66]);
				tAvatarInfo[index01].aSearch = ::atoi(row[67]);
				tAvatarInfo[index01].ExchangeHealtiks = ::atoi(row[68]);
				tAvatarInfo[index01].ExchangeChiiks = ::atoi(row[69]);
				tAvatarInfo[index01].aTribeVoteDate = ::atoi(row[70]);
				tAvatarInfo[index01].HealtAutoPot = ::atoi(row[71]);
				tAvatarInfo[index01].ManaAutoPot = ::atoi(row[72]);
				for (int i = 0; i < 10; i++)
				{
					tAvatarInfo[index01].aAnimal[i] = ::atoi(row[73 + i]);
				}
				tAvatarInfo[index01].aAnimalIndex = ::atoi(row[83]);
				tAvatarInfo[index01].aAnimalTime = ::atoi(row[84]);
				tAvatarInfo[index01].LuckyCombine = ::atoi(row[85]);
				tAvatarInfo[index01].LuckyUpgrade = ::atoi(row[86]);
				tAvatarInfo[index01].LuckyDrop = ::atoi(row[87]);
				tAvatarInfo[index01].Title = ::atoi(row[88]);
				tAvatarInfo[index01].ExtinctionScroll = ::atoi(row[89]);
				tAvatarInfo[index01].aUpradgeValue = ::atoi(row[90]);
				tAvatarInfo[index01].Beginner = ::atoi(row[91]);
				tAvatarInfo[index01].BeginnerLevel = ::atoi(row[92]);
				tAvatarInfo[index01].OnlineHour = ::atoi(row[93]);
				tAvatarInfo[index01].Cppc = ::atoi(row[94]);
				tAvatarInfo[index01].iUseOrnament = ::atoi(row[95]);
				tAvatarInfo[index01].iSilverOrnamentRemainsTime = ::atoi(row[96]);
				tAvatarInfo[index01].IslandOfBlood = ::atoi(row[97]);
				tAvatarInfo[index01].IslandOfSoulMReal1 = ::atoi(row[98]);
				tAvatarInfo[index01].IslandOfSoulMReal2 = ::atoi(row[99]);
				tAvatarInfo[index01].IslandOfSoulMReal3 = ::atoi(row[100]);
				tAvatarInfo[index01].IslandOfSoulMReal4 = ::atoi(row[101]);
				tAvatarInfo[index01].IslandOfSoulMReal5 = ::atoi(row[102]);
				tAvatarInfo[index01].IslandOfSoulMReal6 = ::atoi(row[103]);
				tAvatarInfo[index01].SkillIncreaseCritHit = ::atoi(row[104]);
				tAvatarInfo[index01].LifeOrDeath = ::atoi(row[105]);
				tAvatarInfo[index01].iGoldOrnamentRemainsTime = ::atoi(row[106]);
				tAvatarInfo[index01].BloodBoost = ::atoi(row[107]);
				tAvatarInfo[index01].SoulBoost = ::atoi(row[108]);
				tAvatarInfo[index01].Registration = ::atoi(row[109]);
				tAvatarInfo[index01].ExpPill = ::atoi(row[110]);
				tAvatarInfo[index01].FactReturnScroll = ::atoi(row[111]);
				tAvatarInfo[index01].PetExpBoost = ::atoi(row[112]);//109

				for (int i = 1; i <= 10; i++)
				{
					tAvatarInfo[index01].Costume[i - 1] = ::atoi(row[112 + i]);
				}

				for (int i = 1; i <= 10; i++)
				{
					tAvatarInfo[index01].CostumeInventory[i - 1] = ::atoi(row[122 + i]);
				}
				tAvatarInfo[index01].SelectCostume = ::atoi(row[133]);
				tAvatarInfo[index01].DamegeBoostScroll = ::atoi(row[134]);
				tAvatarInfo[index01].HealtBoostScroll = ::atoi(row[135]);
				tAvatarInfo[index01].CritBoostScroll = ::atoi(row[136]);
				tAvatarInfo[index01].AutoBuffScroll = ::atoi(row[137]);
				::strncpy(AutoBuff, row[138], 49);
				tAvatarInfo[index01].Hisar = ::atoi(row[139]);
				tAvatarInfo[index01].SweetPateto = ::atoi(row[140]);
				::strncpy(InventorySocket, row[141], sizeof(InventorySocket));
				::strncpy(EquipSocket, row[142], sizeof(EquipSocket));
				::strncpy(TradeSocket, row[143], sizeof(TradeSocket));
				::strncpy(StoreSocket, row[144], sizeof(StoreSocket));
				tAvatarInfo[index01].Hunt7d = ::atoi(row[145]);
				tAvatarInfo[index01].Hunt5h = ::atoi(row[146]);
				tAvatarInfo[index01].Inventorybar = ::atoi(row[147]);
				tAvatarInfo[index01].TradeBar = ::atoi(row[148]);
				tAvatarInfo[index01].BankBar = ::atoi(row[149]);
				tAvatarInfo[index01].RebirtHall = ::atoi(row[150]);
				tAvatarInfo[index01].PreServeCharm = ::atoi(row[151]);
				tAvatarInfo[index01].Chenjoho = ::atoi(row[152]);
				tAvatarInfo[index01].aRankPoint = ::atoi(row[153]);
				tAvatarInfo[index01].aRank = ::atoi(row[154]);
				tAvatarInfo[index01].FanctionNoticeScroll = ::atoi(row[155]);
				::strncpy(AnimalExp, row[156], sizeof(AnimalExp));
				::strncpy(AnimalStat, row[157], sizeof(AnimalStat));
				tAvatarInfo[index01].DoubleMouthExp2x = ::atoi(row[158]);
				tAvatarInfo[index01].VigilanteScroll = ::atoi(row[159]);
				tAvatarInfo[index01].RafflaTicket = ::atoi(row[160]);
				tAvatarInfo[index01].MountAbsorb = ::atoi(row[161]);
				tAvatarInfo[index01].MountAbsorbe = ::atoi(row[162]);
				tAvatarInfo[index01].FuryTime = ::atoi(row[163]);
				tAvatarInfo[index01].BurstPill = ::atoi(row[164]);
				tAvatarInfo[index01].RagePill = ::atoi(row[165]);
				tAvatarInfo[index01].WarriorScroll = ::atoi(row[166]);
				tAvatarInfo[index01].HeroPill = ::atoi(row[167]);
				tAvatarInfo[index01].WingProtectionRune = ::atoi(row[168]);
				tAvatarInfo[index01].LessDecressScroll = ::atoi(row[169]);
				tAvatarInfo[index01].PetInventory = ::atoi(row[170]);
				::strncpy(PetInventory, row[171], sizeof(PetInventory));
				tAvatarInfo[index01].JoinWar = ::atoi(row[172]);
				tAvatarInfo[index01].PlayerKill = ::atoi(row[173]);
				tAvatarInfo[index01].MonsterKill = ::atoi(row[174]);
				tAvatarInfo[index01].PlayTimeDay = ::atoi(row[175]);
				tAvatarInfo[index01].YeniElx  = (::atoi(row[176]) * 1000);
				tAvatarInfo[index01].YeniElx += ::atoi(row[177]);
				::strncpy(aAutoConfig, row[178],sizeof(aAutoConfig));
				tAvatarInfo[index01].BloodStained = ::atoi(row[179]);
				tAvatarInfo[index01].FishingTime = ::atoi(row[180]);
				tAvatarInfo[index01].BottleIndex = ::atoi(row[181]);
				tAvatarInfo[index01].BottleTime = ::atoi(row[182]);

				for (int i = 1; i <= 10; ++i)
				{
					tAvatarInfo[index01].Bottle[i - 1] = ::atoi(row[182 + i]);
				}

				for (int i = 1; i <= 10; ++i)
				{
					tAvatarInfo[index01].BottlePrice[i - 1] = ::atoi(row[192 + i]);
				}


				for (int i = 1; i <= 14; ++i)
				{
					tAvatarInfo[index01].OtherSkill[i - 1] = ::atoi(row[202 + i]);
				}

				for (int i = 1; i <= 14; ++i)
				{
					tAvatarInfo[index01].OtherSkillState1[i - 1] = ::atoi(row[216 + i]);
				}

				tAvatarInfo[index01].OtherSkillSolUst = ::atoi(row[231]);
				tAvatarInfo[index01].Fury = ::atoi(row[232]);
				tAvatarInfo[index01].Premium = ::atoi(row[233]);
				tAvatarInfo[index01].HideCostumeRegister = ::atoi(row[234]); 
				tAvatarInfo[index01].BuffDurationPill = ::atoi(row[235]);
				++iCounts;
			}


			if ((::strstr(gMember, tAvatarInfo[index01].aName) == NULL)
				&& (RealGuild[index01])
				&& (::strlen(tAvatarInfo[index01].aGuildName) > 0)) {
				::strcpy(tAvatarInfo[index01].aGuildName, "");
				tAvatarInfo[index01].aGuildRole = 0;
				::strcpy(tAvatarInfo[index01].aCallName, "");
				CheckGuild[index01] = true;
			}
		}
		mDB01.clear_res();

		if (1 != iCounts) {
			//LOG_TO_FILE("![WARNING - (6)] As a result of a number of rows is not returned by the query.\n");
			//LOG_TO_FILE_1 ("\t\t\tRow counts = %d.\n", iCounts);
			*tResult = 6;
			return;
		}

		if (CheckGuild[index01]) {
			sprintf(mQUERY,
				"UPDATE AvatarInfo "
				"SET aGuildName = '', aGuildRole = 0, aCallName = '' "
				"WHERE aName = '%s' AND aWorldNumber = %d "
				, tAvatarInfo[index01].aName, mSERVER_INFO.mWorldNumber);
			if (!RECONNECT_TO_DATABASE01()) {
				*tResult = 7;
				return;
			}

			if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0)
			{
				//LOG_TO_FILE_2("[%s] Query execute false : %s! \n" , __FUNCTION__ , mQUERY);
				*tResult = 8;
				return;
			}
			//LOG_TO_FILE_2("![%s] - Guild bug fix(%s)\n", __FUNCTION__, mQUERY);
		}

		if (strcmp(uIDForCheck, uID) != 0)
		{
			//LOG_TO_FILE("![WARNING - (10)] Your account is different.\n");
			*tResult = 10;
			return;
		}
		tAvatarInfo[index01].aPlayTime2 = 0;
		for (index02 = 0; index02 < MAX_EQUIP_SLOT_NUM; index02++)
		{
			CopyMemory(&tempString01[0], &aEquip[(index02 * 25 + 0)], 5);
			tempString01[5] = '\0';
			tAvatarInfo[index01].aEquip[index02][0] = atoi(tempString01);
			CopyMemory(&tempString01[0], &aEquip[(index02 * 25 + 5)], 3);
			tempString01[3] = '\0';
			tAvatarInfo[index01].aEquip[index02][1] = atoi(tempString01);
			CopyMemory(&tempString01[0], &aEquip[(index02 * 25 + 8)], 9);
			tempString01[9] = '\0';
			tAvatarInfo[index01].aEquip[index02][2] = atoi(tempString01);
			CopyMemory(&tempString01[0], &aEquip[(index02 * 25 + 17)], 8);
			tempString01[8] = '\0';
			tAvatarInfo[index01].aEquip[index02][3] = atoi(tempString01);
		}
		for (index02 = 0; index02 < MAX_EQUIP_SLOT_NUM; index02++)
		{
			CopyMemory(&tempString01[0], &EquipSocket[(index02 * 27 + 0)], 9);
			tempString01[9] = '\0';
			tAvatarInfo[index01].EquipSocket[index02][0] = atoi(tempString01);
			CopyMemory(&tempString01[0], &EquipSocket[(index02 * 27 + 9)], 9);
			tempString01[9] = '\0';
			tAvatarInfo[index01].EquipSocket[index02][1] = atoi(tempString01);
			CopyMemory(&tempString01[0], &EquipSocket[(index02 * 27 + 18)], 9);
			tempString01[9] = '\0';
			tAvatarInfo[index01].EquipSocket[index02][2] = atoi(tempString01);
		}
		for (index02 = 0; index02 < (MAX_INVENTORY_SLOT_NUM * 2); index02++)
		{
			CopyMemory(&tempString01[0], &aInventory[(index02 * 27 + 0)], 5);
			tempString01[5] = '\0';
			tAvatarInfo[index01].aInventory[(index02 / MAX_INVENTORY_SLOT_NUM)][(index02 % MAX_INVENTORY_SLOT_NUM)][0] = atoi(tempString01);
			CopyMemory(&tempString01[0], &aInventory[(index02 * 27 + 5)], 1);
			tempString01[1] = '\0';
			tAvatarInfo[index01].aInventory[(index02 / MAX_INVENTORY_SLOT_NUM)][(index02 % MAX_INVENTORY_SLOT_NUM)][1] = atoi(tempString01);
			CopyMemory(&tempString01[0], &aInventory[(index02 * 27 + 6)], 1);
			tempString01[1] = '\0';
			tAvatarInfo[index01].aInventory[(index02 / MAX_INVENTORY_SLOT_NUM)][(index02 % MAX_INVENTORY_SLOT_NUM)][2] = atoi(tempString01);
			CopyMemory(&tempString01[0], &aInventory[(index02 * 27 + 7)], 3);
			tempString01[3] = '\0';
			tAvatarInfo[index01].aInventory[(index02 / MAX_INVENTORY_SLOT_NUM)][(index02 % MAX_INVENTORY_SLOT_NUM)][3] = atoi(tempString01);
			CopyMemory(&tempString01[0], &aInventory[(index02 * 27 + 10)], 9);
			tempString01[9] = '\0';
			tAvatarInfo[index01].aInventory[(index02 / MAX_INVENTORY_SLOT_NUM)][(index02 % MAX_INVENTORY_SLOT_NUM)][4] = atoi(tempString01);
			CopyMemory(&tempString01[0], &aInventory[(index02 * 27 + 19)], 8);
			tempString01[8] = '\0';
			tAvatarInfo[index01].aInventory[(index02 / MAX_INVENTORY_SLOT_NUM)][(index02 % MAX_INVENTORY_SLOT_NUM)][5] = atoi(tempString01);
			if (tAvatarInfo[index01].aInventory[(index02 / MAX_INVENTORY_SLOT_NUM)][(index02 % MAX_INVENTORY_SLOT_NUM)][0] == 0) {
				tAvatarInfo[index01].aInventory[(index02 / MAX_INVENTORY_SLOT_NUM)][(index02 % MAX_INVENTORY_SLOT_NUM)][1] = 0;
				tAvatarInfo[index01].aInventory[(index02 / MAX_INVENTORY_SLOT_NUM)][(index02 % MAX_INVENTORY_SLOT_NUM)][2] = 0;
				tAvatarInfo[index01].aInventory[(index02 / MAX_INVENTORY_SLOT_NUM)][(index02 % MAX_INVENTORY_SLOT_NUM)][3] = 0;
				tAvatarInfo[index01].aInventory[(index02 / MAX_INVENTORY_SLOT_NUM)][(index02 % MAX_INVENTORY_SLOT_NUM)][4] = 0;
				tAvatarInfo[index01].aInventory[(index02 / MAX_INVENTORY_SLOT_NUM)][(index02 % MAX_INVENTORY_SLOT_NUM)][5] = 0;
				tAvatarInfo[index01].InventorySocket[(index02 / MAX_INVENTORY_SLOT_NUM)][(index02 % MAX_INVENTORY_SLOT_NUM)][0] = 0;
				tAvatarInfo[index01].InventorySocket[(index02 / MAX_INVENTORY_SLOT_NUM)][(index02 % MAX_INVENTORY_SLOT_NUM)][1] = 0;
				tAvatarInfo[index01].InventorySocket[(index02 / MAX_INVENTORY_SLOT_NUM)][(index02 % MAX_INVENTORY_SLOT_NUM)][2] = 0;
			}
		}
		for (index02 = 0; index02 < (MAX_INVENTORY_SLOT_NUM * 2); index02++)
		{
			CopyMemory(&tempString01[0], &InventorySocket[(index02 * 27 + 0)], 9);
			tempString01[9] = '\0';
			tAvatarInfo[index01].InventorySocket[(index02 / MAX_INVENTORY_SLOT_NUM)][(index02 % MAX_INVENTORY_SLOT_NUM)][0] = atoi(tempString01);
			CopyMemory(&tempString01[0], &InventorySocket[(index02 * 27 + 9)], 9);
			tempString01[9] = '\0';
			tAvatarInfo[index01].InventorySocket[(index02 / MAX_INVENTORY_SLOT_NUM)][(index02 % MAX_INVENTORY_SLOT_NUM)][1] = atoi(tempString01);
			CopyMemory(&tempString01[0], &InventorySocket[(index02 * 27 + 18)], 9);
			tempString01[9] = '\0';
			tAvatarInfo[index01].InventorySocket[(index02 / MAX_INVENTORY_SLOT_NUM)][(index02 % MAX_INVENTORY_SLOT_NUM)][2] = atoi(tempString01);
		}
		for (index02 = 0; index02 < MAX_TRADE_SLOT_NUM; index02++)
		{
			CopyMemory(&tempString01[0], &aTrade[(index02 * 25 + 0)], 5);
			tempString01[5] = '\0';
			tAvatarInfo[index01].aTrade[index02][0] = atoi(tempString01);
			CopyMemory(&tempString01[0], &aTrade[(index02 * 25 + 5)], 3);
			tempString01[3] = '\0';
			tAvatarInfo[index01].aTrade[index02][1] = atoi(tempString01);
			CopyMemory(&tempString01[0], &aTrade[(index02 * 25 + 8)], 9);
			tempString01[9] = '\0';
			tAvatarInfo[index01].aTrade[index02][2] = atoi(tempString01);
			CopyMemory(&tempString01[0], &aTrade[(index02 * 25 + 17)], 8);
			tempString01[8] = '\0';
			tAvatarInfo[index01].aTrade[index02][3] = atoi(tempString01);
		}
		for (index02 = 0; index02 < MAX_TRADE_SLOT_NUM; index02++)
		{
			CopyMemory(&tempString01[0], &TradeSocket[(index02 * 27 + 0)], 9);
			tempString01[9] = '\0';
			tAvatarInfo[index01].TradeSocket[index02][0] = atoi(tempString01);
			CopyMemory(&tempString01[0], &TradeSocket[(index02 * 27 + 9)], 9);
			tempString01[9] = '\0';
			tAvatarInfo[index01].TradeSocket[index02][1] = atoi(tempString01);
			CopyMemory(&tempString01[0], &TradeSocket[(index02 * 27 + 18)], 9);
			tempString01[9] = '\0';
			tAvatarInfo[index01].TradeSocket[index02][2] = atoi(tempString01);

		}
		for (index02 = 0; index02 < (MAX_STORE_ITEM_SLOT_NUM * 2); index02++)
		{
			CopyMemory(&tempString01[0], &aStoreItem[(index02 * 25 + 0)], 5);
			tempString01[5] = '\0';
			tAvatarInfo[index01].aStoreItem[(index02 / MAX_STORE_ITEM_SLOT_NUM)][(index02 % MAX_STORE_ITEM_SLOT_NUM)][0] = atoi(tempString01);
			CopyMemory(&tempString01[0], &aStoreItem[(index02 * 25 + 5)], 3);
			tempString01[3] = '\0';
			tAvatarInfo[index01].aStoreItem[(index02 / MAX_STORE_ITEM_SLOT_NUM)][(index02 % MAX_STORE_ITEM_SLOT_NUM)][1] = atoi(tempString01);
			CopyMemory(&tempString01[0], &aStoreItem[(index02 * 25 + 8)], 9);
			tempString01[9] = '\0';
			tAvatarInfo[index01].aStoreItem[(index02 / MAX_STORE_ITEM_SLOT_NUM)][(index02 % MAX_STORE_ITEM_SLOT_NUM)][2] = atoi(tempString01);
			CopyMemory(&tempString01[0], &aStoreItem[(index02 * 25 + 17)], 8);
			tempString01[8] = '\0';
			tAvatarInfo[index01].aStoreItem[(index02 / MAX_STORE_ITEM_SLOT_NUM)][(index02 % MAX_STORE_ITEM_SLOT_NUM)][3] = atoi(tempString01);
		}

		for (index02 = 0; index02 < (MAX_STORE_ITEM_SLOT_NUM * 2); index02++)
		{
			CopyMemory(&tempString01[0], &StoreSocket[(index02 * 27 + 0)], 9);
			tempString01[9] = '\0';
			tAvatarInfo[index01].StoreSocket[(index02 / MAX_STORE_ITEM_SLOT_NUM)][(index02 % MAX_STORE_ITEM_SLOT_NUM)][0] = atoi(tempString01);
			CopyMemory(&tempString01[0], &StoreSocket[(index02 * 27 + 9)], 9);
			tempString01[9] = '\0';
			tAvatarInfo[index01].StoreSocket[(index02 / MAX_STORE_ITEM_SLOT_NUM)][(index02 % MAX_STORE_ITEM_SLOT_NUM)][1] = atoi(tempString01);
			CopyMemory(&tempString01[0], &StoreSocket[(index02 * 27 + 18)], 9);
			tempString01[9] = '\0';
			tAvatarInfo[index01].StoreSocket[(index02 / MAX_STORE_ITEM_SLOT_NUM)][(index02 % MAX_STORE_ITEM_SLOT_NUM)][2] = atoi(tempString01);
		}

		for (index02 = 0; index02 < MAX_SKILL_SLOT_NUM; index02++)
		{
			CopyMemory(&tempString01[0], &aSkill[(index02 * 6 + 0)], 3);
			tempString01[3] = '\0';
			tAvatarInfo[index01].aSkill[index02][0] = atoi(tempString01);
			CopyMemory(&tempString01[0], &aSkill[(index02 * 6 + 3)], 3);
			tempString01[3] = '\0';
			tAvatarInfo[index01].aSkill[index02][1] = atoi(tempString01);
		}
		for (index02 = 0; index02 < (MAX_HOT_KEY_NUM * 3); index02++)
		{
			CopyMemory(&tempString01[0], &aHotKey[(index02 * 10 + 0)], 5);
			tempString01[5] = '\0';
			tAvatarInfo[index01].aHotKey[(index02 / MAX_HOT_KEY_NUM)][(index02 % MAX_HOT_KEY_NUM)][0] = atoi(tempString01);
			CopyMemory(&tempString01[0], &aHotKey[(index02 * 10 + 5)], 3);
			tempString01[3] = '\0';
			tAvatarInfo[index01].aHotKey[(index02 / MAX_HOT_KEY_NUM)][(index02 % MAX_HOT_KEY_NUM)][1] = atoi(tempString01);
			CopyMemory(&tempString01[0], &aHotKey[(index02 * 10 + 8)], 2);
			tempString01[2] = '\0';
			tAvatarInfo[index01].aHotKey[(index02 / MAX_HOT_KEY_NUM)][(index02 % MAX_HOT_KEY_NUM)][2] = atoi(tempString01);
		}
		CopyMemory(&tempString01[0], &aQuestInfo[0], 5);
		tempString01[5] = '\0';
		tAvatarInfo[index01].aQuestInfo[0] = atoi(tempString01);
		CopyMemory(&tempString01[0], &aQuestInfo[5], 5);
		tempString01[5] = '\0';
		tAvatarInfo[index01].aQuestInfo[1] = atoi(tempString01);
		CopyMemory(&tempString01[0], &aQuestInfo[10], 5);
		tempString01[5] = '\0';
		tAvatarInfo[index01].aQuestInfo[2] = atoi(tempString01);
		CopyMemory(&tempString01[0], &aQuestInfo[15], 5);
		tempString01[5] = '\0';
		tAvatarInfo[index01].aQuestInfo[3] = atoi(tempString01);
		CopyMemory(&tempString01[0], &aQuestInfo[20], 5);
		tempString01[5] = '\0';
		tAvatarInfo[index01].aQuestInfo[4] = atoi(tempString01);
		for (index02 = 0; index02 < MAX_FRIEND_NUM; index02++)
		{
			CopyMemory(&tAvatarInfo[index01].aFriend[index02][0], &aFriend[(index02 * 12 + 0)], 12);
			for (index03 = 0; index03 < 12; index03++)
			{
				if (::IsDBCSLeadByte(tAvatarInfo[index01].aFriend[index02][index03]) == TRUE) {
					if (index03 != 11) index03++;
					continue;
				}

				if (tAvatarInfo[index01].aFriend[index02][index03] == '@')
				{
					break;
				}
			}
			tAvatarInfo[index01].aFriend[index02][index03] = '\0';
		}
		tAvatarInfo[index01].uSaveMoney = *tSaveMoney;
		tAvatarInfo[index01].SeyisBar = *tSeyisbar;
		////LOG_TO_FILE_1("%s---", uID);
		for (index02 = 0; index02 < MAX_SAVE_ITEM_SLOT_NUM; index02++)
		{
			tAvatarInfo[index01].uSaveItem[index02][0] = tSaveItem[index02][0];
			tAvatarInfo[index01].uSaveItem[index02][1] = tSaveItem[index02][1];
			tAvatarInfo[index01].uSaveItem[index02][2] = tSaveItem[index02][2];
			tAvatarInfo[index01].uSaveItem[index02][3] = tSaveItem[index02][3];
			tAvatarInfo[index01].SaveSocket[index02][0] = tSaveSocket[index02][0];
			tAvatarInfo[index01].SaveSocket[index02][1] = tSaveSocket[index02][1];
			tAvatarInfo[index01].SaveSocket[index02][2] = tSaveSocket[index02][2];
			//LOG_TO_FILE_4("------> %d %d %d %d\n", tSaveItem[index02][0], tSaveItem[index02][1], tSaveItem[index02][2], tSaveItem[index02][3]);
		}

		for (index02 = 0; index02 < MAX_AUTOBUFF_SKİLL; index02++)
		{
			CopyMemory(&tempString01[0], &AutoBuff[(index02 * 6 + 0)], 3);
			tempString01[3] = '\0';
			tAvatarInfo[index01].AutoBuffSmenu[index02][0] = atoi(tempString01);
			CopyMemory(&tempString01[0], &AutoBuff[(index02 * 6 + 3)], 3);
			tempString01[3] = '\0';
			tAvatarInfo[index01].AutoBuffSmenu[index02][1] = atoi(tempString01);
		}

		for (index02 = 0; index02 < MAX_AVATAR_ANIMAL_NUM; index02++)
		{
			CopyMemory(&tempString01[0], &AnimalExp[(index02 * 9 + 0)], 9);
			tempString01[9] = '\0';
			tAvatarInfo[index01].AnimalExp[index02] = atoi(tempString01);
		}

		for (index02 = 0; index02 < MAX_AVATAR_ANIMAL_NUM; index02++)
		{
			CopyMemory(&tempString01[0], &AnimalStat[(index02 * 9 + 0)], 9);
			tempString01[9] = '\0';
			tAvatarInfo[index01].AnimalStat[index02] = atoi(tempString01);
		}

		for (index02 = 0; index02 < (MAX_AVATAR_ANIMAL_NUM * 2); index02++)
		{
			CopyMemory(&tempString01[0], &PetInventory[(index02 * 6 + 0)], 6);
			tempString01[6] = '\0';
			tAvatarInfo[index01].PetInventoryTick[(index02 / MAX_STORE_ITEM_SLOT_NUM)][(index02 % MAX_STORE_ITEM_SLOT_NUM)] = atoi(tempString01);
		}

		for (index02 = 0; index02 < 27; index02++) {
			::memcpy(tempBuffer, &aAutoConfig[index02 * 3], 3);
			tempBuffer[3] = '\0';
			switch (index02) {
			case 0:
				tAvatarInfo[index01].AutoHunt.BuffType = ::atoi(tempBuffer);
				break;
			case 1:
			case 2:
				tAvatarInfo[index01].AutoHunt.HuntBuff[0][(index02 + 1) % 2] = ::atoi(tempBuffer);
				break;
			case 3:
			case 4:
				tAvatarInfo[index01].AutoHunt.HuntBuff[1][(index02 + 1) % 2] = ::atoi(tempBuffer);
				break;
			case 5:
			case 6:
				tAvatarInfo[index01].AutoHunt.HuntBuff[2][(index02 + 1) % 2] = ::atoi(tempBuffer);
				break;
			case 7:
			case 8:
				tAvatarInfo[index01].AutoHunt.HuntBuff[3][(index02 + 1) % 2] = ::atoi(tempBuffer);
				break;
			case 9:
			case 10:
				tAvatarInfo[index01].AutoHunt.HuntBuff[4][(index02 + 1) % 2] = ::atoi(tempBuffer);
				break;
			case 11:
			case 12:
				tAvatarInfo[index01].AutoHunt.HuntBuff[5][(index02 + 1) % 2] = ::atoi(tempBuffer);
				break;
			case 13:
			case 14:
				tAvatarInfo[index01].AutoHunt.HuntBuff[6][(index02 + 1) % 2] = ::atoi(tempBuffer);
				break;
			case 15:
			case 16:
				tAvatarInfo[index01].AutoHunt.HuntBuff[7][(index02 + 1) % 2] = ::atoi(tempBuffer);
				break;
			case 17:
				tAvatarInfo[index01].AutoHunt.HuntType = ::atoi(tempBuffer);
				break;
			case 18:
			case 19:
				tAvatarInfo[index01].AutoHunt.AtakType[0][index02 % 2] = ::atoi(tempBuffer);
				break;
			case 20:
			case 21:
				tAvatarInfo[index01].AutoHunt.AtakType[1][index02 % 2] = ::atoi(tempBuffer);
				break;
			case 22:
				tAvatarInfo[index01].AutoHunt.OfMonster = ::atoi(tempBuffer);
				break;
			case 23:
				tAvatarInfo[index01].AutoHunt.HuntPickUp = ::atoi(tempBuffer);
				break;
			case 24:
				tAvatarInfo[index01].AutoHunt.HuntInsuficcent = ::atoi(tempBuffer);
				break;
			case 25:
				tAvatarInfo[index01].AutoHunt.HuntPetFood = ::atoi(tempBuffer);
				break;
			case 26:
				tAvatarInfo[index01].AutoHunt.HuntPetFoodExp = ::atoi(tempBuffer);
				break;
			}
		}




		//-----------------------//
		//\B9\AB\BDŰ\E6_\B4\A9\C0\FB_\B0\E6\C7\E8ġ_ó\B8\AE//
		//-----------------------//
#ifdef __GOD__
		if ((tAvatarInfo[index01].aLevel2 < 1) && (tAvatarInfo[index01].aGeneralExperience2 > 0))
		{
			tAvatarInfo[index01].aGeneralExperience2 = (int)((float)tAvatarInfo[index01].aGeneralExperience2 / 2.3f);
			tAvatarInfo[index01].aSkillPoint += 100;
			tAvatarInfo[index01].aLevel2 = 1;
			tMaxGeneralExperienceRange = 962105896.0f;
			tPresentGeneralExperienceRatio = 0;
			tNextGeneralExperienceRatio = (int)((float)tAvatarInfo[index01].aGeneralExperience2 * 100.0f / tMaxGeneralExperienceRange);
			tAvatarInfo[index01].aStateBonusPoint += (tNextGeneralExperienceRatio - tPresentGeneralExperienceRatio);
			tAvatarInfo[index01].aStateBonusPoint += (tAvatarInfo[index01].aVitality + tAvatarInfo[index01].aStrength + tAvatarInfo[index01].aKi + tAvatarInfo[index01].aWisdom - 4);
			tAvatarInfo[index01].aVitality = 1;
			tAvatarInfo[index01].aStrength = 1;
			tAvatarInfo[index01].aKi = 1;
			tAvatarInfo[index01].aWisdom = 1;
			tAvatarInfo[index01].aLogoutInfo[4] = 1;
			tAvatarInfo[index01].aLogoutInfo[5] = 0;
		}
#endif
		//-----------------------//
		//-----------------------//
		//-----------------------//
	}

	*tResult = 0;
}
//DB_PROCESS_03
BOOL MyDB::DB_PROCESS_03(char tID[MAX_USER_ID_LENGTH], char tMousePassword[MAX_MOUSE_PASSWORD_LENGTH])
{
	int iAffected;

	sprintf(mQUERY, "update %s set uMousePassword='%s' where uID='%s'", mSERVER_INFO.mDB_1_Table01, tMousePassword, tID);
	if (!RECONNECT_TO_DATABASE02())
	{
		return FALSE;
	}

	iAffected = 0;
	if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0)
		return FALSE;

	return TRUE;
}
//DB_PROCESS_04
BOOL MyDB::DB_PROCESS_04(int tSecretCardNumber, int tSecretCardIndex, char tSecretCardContent[5])
{
	int iAffected;
	int iCounts;
	MYSQL_ROW row;
	MYSQL_RES* res = NULL;

	switch (tSecretCardIndex)
	{
	case  0: sprintf(mQUERY, "select cNumber01 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case  1: sprintf(mQUERY, "select cNumber02 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case  2: sprintf(mQUERY, "select cNumber03 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case  3: sprintf(mQUERY, "select cNumber04 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case  4: sprintf(mQUERY, "select cNumber05 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case  5: sprintf(mQUERY, "select cNumber06 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case  6: sprintf(mQUERY, "select cNumber07 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case  7: sprintf(mQUERY, "select cNumber08 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case  8: sprintf(mQUERY, "select cNumber09 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case  9: sprintf(mQUERY, "select cNumber10 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 10: sprintf(mQUERY, "select cNumber11 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 11: sprintf(mQUERY, "select cNumber12 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 12: sprintf(mQUERY, "select cNumber13 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 13: sprintf(mQUERY, "select cNumber14 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 14: sprintf(mQUERY, "select cNumber15 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 15: sprintf(mQUERY, "select cNumber16 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 16: sprintf(mQUERY, "select cNumber17 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 17: sprintf(mQUERY, "select cNumber18 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 18: sprintf(mQUERY, "select cNumber19 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 19: sprintf(mQUERY, "select cNumber20 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 20: sprintf(mQUERY, "select cNumber21 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 21: sprintf(mQUERY, "select cNumber22 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 22: sprintf(mQUERY, "select cNumber23 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 23: sprintf(mQUERY, "select cNumber24 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 24: sprintf(mQUERY, "select cNumber25 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 25: sprintf(mQUERY, "select cNumber26 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 26: sprintf(mQUERY, "select cNumber27 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 27: sprintf(mQUERY, "select cNumber28 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 28: sprintf(mQUERY, "select cNumber29 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 29: sprintf(mQUERY, "select cNumber30 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 30: sprintf(mQUERY, "select cNumber31 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 31: sprintf(mQUERY, "select cNumber32 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 32: sprintf(mQUERY, "select cNumber33 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 33: sprintf(mQUERY, "select cNumber34 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 34: sprintf(mQUERY, "select cNumber35 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 35: sprintf(mQUERY, "select cNumber36 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 36: sprintf(mQUERY, "select cNumber37 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 37: sprintf(mQUERY, "select cNumber38 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 38: sprintf(mQUERY, "select cNumber39 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 39: sprintf(mQUERY, "select cNumber40 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 40: sprintf(mQUERY, "select cNumber41 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 41: sprintf(mQUERY, "select cNumber42 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 42: sprintf(mQUERY, "select cNumber43 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 43: sprintf(mQUERY, "select cNumber44 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 44: sprintf(mQUERY, "select cNumber45 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 45: sprintf(mQUERY, "select cNumber46 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 46: sprintf(mQUERY, "select cNumber47 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 47: sprintf(mQUERY, "select cNumber48 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 48: sprintf(mQUERY, "select cNumber49 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	case 49: sprintf(mQUERY, "select cNumber50 from %s where cID=%d", mSERVER_INFO.mDB_1_Table04, tSecretCardNumber); break;
	default:
		return FALSE;
	}
	if (!RECONNECT_TO_DATABASE02())
	{
		return FALSE;
	}
	iAffected = 0;
	if ((iAffected = mDB02.exec_query(mQUERY)) < 0)
		return FALSE;
	iCounts = 0;
#if 0
	if ((iCounts = mDB01.get_num_rows()) != 1)
		return FALSE;

	::strncpy(tSecretCardContent, mDB01.get_value(0, 0), 5);
	mDB01.clear_res();
#endif
	res = mDB02.get_res();
	if (res == NULL) {
		//LOG_TO_FILE_1 ("!Query failed - (%s).\n", mQUERY);
		//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mDB02.get_error_msg ().c_str ());
		return FALSE;
	}
	while (row = mysql_fetch_row(res)) {
		::strncpy(tSecretCardContent, row[0], 5);
		++iCounts;
	}
	mDB02.clear_res();
	if (1 != iCounts) {
		return FALSE;
	}

	return TRUE;
}
//DB_PROCESS_05
void MyDB::DB_PROCESS_05(int tUserIndex, int tAvatarPost, AVATAR_INFO* tAvatarInfo, int* tResult)
{
	int iAffected;
	//LOG_TO_FILE_2("!burda [%s] [%d]\n", __FUNCTION__,__LINE__);

	sprintf(mQUERY, "insert into %s values ( now(),'%s' )", mSERVER_INFO.mDB_1_Table02, tAvatarInfo->aName);
	//LOG_TO_FILE_2("!burda [%s] [%d]\n", mQUERY,__LINE__);
	if (!RECONNECT_TO_DATABASE02())
	{
		*tResult = 1;
		//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mDB02.get_error_msg ().c_str ());
		//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mQUERY);
		return;
	}
	iAffected = 0;
	if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		*tResult = 2;
		//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mDB02.get_error_msg ().c_str ());
		__LogMgr()->Log("\t\t\tWhy - %s\n", mQUERY);
		return;
	}

	//LOG_TO_FILE_2("!burda [%s] [%d]\n", __FUNCTION__,__LINE__);

	MakeQueryForInsert(1, &mUSER[tUserIndex].uID[0], tAvatarInfo);

	//LOG_TO_FILE_2("!burda [%s] [%d]\n", __FUNCTION__,__LINE__);
	if (!RECONNECT_TO_DATABASE01())
	{
		sprintf(mQUERY, "delete from %s where aName='%s'", mSERVER_INFO.mDB_1_Table02, tAvatarInfo->aName);
		RECONNECT_TO_DATABASE02();
		iAffected = 0;
		if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 3;
			//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mDB02.get_error_msg ().c_str ());
			//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mQUERY);
			return;
		}
		*tResult = 1;
		return;
	}
	iAffected = 0;
	if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0)
	{
		__LogMgr()->Log("\t\t\tWhy - %s\n", mDB01.get_error_msg().c_str());
		//__LogMgr()->Log("\t\t\tWhy - %s\n", mQUERY);
		sprintf(mQUERY, "delete from %s where aName='%s'", mSERVER_INFO.mDB_1_Table02, tAvatarInfo->aName);
		RECONNECT_TO_DATABASE02();
		iAffected = 0;
		if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 4;
			//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mDB02.get_error_msg ().c_str ());
			//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mQUERY);
			return;
		}

		*tResult = 2;
		return;
	}
	switch (tAvatarPost)
	{
	case 0:
		sprintf(mQUERY, "update %s set aName01='%s' where uID='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_2_Table02, tAvatarInfo->aName, mUSER[tUserIndex].uID, mSERVER_INFO.mWorldNumber);
		break;
	case 1:
		sprintf(mQUERY, "update %s set aName02='%s' where uID='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_2_Table02, tAvatarInfo->aName, mUSER[tUserIndex].uID, mSERVER_INFO.mWorldNumber);
		break;
	case 2:
		sprintf(mQUERY, "update %s set aName03='%s' where uID='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_2_Table02, tAvatarInfo->aName, mUSER[tUserIndex].uID, mSERVER_INFO.mWorldNumber);
		break;
	default:
		sprintf(mQUERY, "delete from %s where aName='%s'", mSERVER_INFO.mDB_1_Table02, tAvatarInfo->aName);
		RECONNECT_TO_DATABASE02();
		iAffected = 0;
		if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 5;
			//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mDB02.get_error_msg ().c_str ());
			//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mQUERY);
			return;
		}
		*tResult = 1;
		return;
	}
	if (!RECONNECT_TO_DATABASE01())
	{
		sprintf(mQUERY, "delete from %s where aName='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_2_Table03, tAvatarInfo->aName, mSERVER_INFO.mWorldNumber);
		RECONNECT_TO_DATABASE02();
		iAffected = 0;
		if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 6;
			//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mDB01.get_error_msg ().c_str ());
			//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mQUERY);
			return;
		}
		sprintf(mQUERY, "delete from %s where aName='%s'", mSERVER_INFO.mDB_1_Table02, tAvatarInfo->aName);
		RECONNECT_TO_DATABASE02();
		iAffected = 0;
		if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 7;
			//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mDB02.get_error_msg ().c_str ());
			//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mQUERY);
			return;
		}
		*tResult = 1;
		return;
	}
	iAffected = 0;
	if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0)
	{
		sprintf(mQUERY, "delete from %s where aName='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_2_Table03, tAvatarInfo->aName, mSERVER_INFO.mWorldNumber);
		RECONNECT_TO_DATABASE01();
		iAffected = 0;
		if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 8;
			//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mDB01.get_error_msg ().c_str ());
			//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mQUERY);
			return;
		}
		sprintf(mQUERY, "delete from %s where aName='%s'", mSERVER_INFO.mDB_1_Table02, tAvatarInfo->aName);
		RECONNECT_TO_DATABASE02();
		iAffected = 0;
		if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 9;
			//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mDB02.get_error_msg ().c_str ());
			//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mQUERY);
			return;
		}
		*tResult = 1;
		return;
	}

	RECONNECT_TO_DATABASE01();
	switch (tAvatarInfo->aTribe) {
	case 0:
		sprintf(mQUERY,
			"UPDATE TribeControl "
			"SET aTribeType0Count = aTribeType0Count + 1 "
			"WHERE aWorldNumber = %d", mSERVER_INFO.mWorldNumber);
		break;
	case 1:
		sprintf(mQUERY,
			"UPDATE TribeControl "
			"SET aTribeType1Count = aTribeType1Count + 1 "
			"WHERE aWorldNumber = %d", mSERVER_INFO.mWorldNumber);
		break;
	case 2:
		sprintf(mQUERY,
			"UPDATE TribeControl "
			"SET aTribeType2Count = aTribeType2Count + 1 "
			"WHERE aWorldNumber = %d", mSERVER_INFO.mWorldNumber);
		break;
	default:
		*tResult = 10;
		return;
	}

	if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		*tResult = 11;
		//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mDB01.get_error_msg ().c_str ());
		//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mQUERY);
		return;
	}

	*tResult = 0;
}
//DB_PROCESS_06
BOOL MyDB::DB_PROCESS_06(int tUserIndex, int tAvatarPost)
{
	int iAffected;
	int TribeCount[3];
	MYSQL_ROW row;
	MYSQL_RES* res = NULL;

	switch (tAvatarPost)
	{
	case 0:
		sprintf(mQUERY, "update %s set aName01='' where uID='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_2_Table02, mUSER[tUserIndex].uID, mSERVER_INFO.mWorldNumber);
		break;
	case 1:
		sprintf(mQUERY, "update %s set aName02='' where uID='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_2_Table02, mUSER[tUserIndex].uID, mSERVER_INFO.mWorldNumber);
		break;
	case 2:
		sprintf(mQUERY, "update %s set aName03='' where uID='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_2_Table02, mUSER[tUserIndex].uID, mSERVER_INFO.mWorldNumber);
		break;
	default:
		return FALSE;
	}
	if (!RECONNECT_TO_DATABASE01())
	{
		//LOG_TO_FILE_1 ("![WARNING] Unable to connect to the database[%s].\n",
		//               mSERVER_INFO.mDB_2_Table02);
		return FALSE;
	}
	iAffected = 0;
	if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		__LogMgr()->Log ("![WARNING] The query execution failed in %s.\n", __FUNCTION__);
		__LogMgr()->Log("\t\t\tWhy - %s\n", mDB01.get_error_msg ().c_str ());
		//SVR_TRACE();
		////LOG_TO_FILE_1("%s\n", mQUERY);
		return FALSE;
	}
	MakeQueryForInsert( 2, &mUSER[tUserIndex].uID[0], &mUSER[tUserIndex].mAvatarInfo[tAvatarPost] );
	RECONNECT_TO_DATABASE01();
	iAffected = 0;
	if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		__LogMgr()->Log ("![WARNING] The query execution failed in1 %s.\n", __FUNCTION__);
		__LogMgr()->Log("\t\t\tWhy - %s\n", mDB01.get_error_msg ().c_str ());
		//SVR_TRACE();
		////LOG_TO_FILE_1("%s\n", mQUERY);
		return FALSE;
	}
	sprintf(mQUERY, "delete from %s where aName='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_2_Table03, mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName, mSERVER_INFO.mWorldNumber);
	RECONNECT_TO_DATABASE01();
	iAffected = 0;
	if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		__LogMgr()->Log ("![WARNING] The query execution failed in2 %s.\n", __FUNCTION__);
		__LogMgr()->Log ("\t\t\tWhy - %s\n", mDB01.get_error_msg ().c_str ());
		//SVR_TRACE();
		////LOG_TO_FILE_1("%s\n", mQUERY);
		return FALSE;
	}
	sprintf(mQUERY, "delete from %s where aName='%s'", mSERVER_INFO.mDB_1_Table02, mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName);
	RECONNECT_TO_DATABASE02();
	iAffected = 0;
	if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		__LogMgr()->Log ("![WARNING] The query execution failed in3 %s.\n", __FUNCTION__);
		__LogMgr()->Log ("\t\t\tWhy - %s\n", mDB02.get_error_msg ().c_str ());
		//SVR_TRACE();
		////LOG_TO_FILE_1("%s\n", mQUERY);
		return FALSE;
	}
	sprintf(mQUERY, "delete from %s where aName='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_1_Table05, mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName, mSERVER_INFO.mWorldNumber);
	RECONNECT_TO_DATABASE01();
	iAffected = 0;
	if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		__LogMgr()->Log ("![WARNING] The query execution failed in4 %s.\n", __FUNCTION__);
		__LogMgr()->Log ("\t\t\tWhy - %s\n", mDB01.get_error_msg ().c_str ());
		//SVR_TRACE();
		////LOG_TO_FILE_1("%s\n", mQUERY);
		return FALSE;
	}

	sprintf(mQUERY,
		"SELECT aTribeType0Count, aTribeType1Count, aTribeType2Count "
		"FROM TribeControl "
		"WHERE aWorldNumber=%d", mSERVER_INFO.mWorldNumber);

	if (!RECONNECT_TO_DATABASE01()) {
		return false;
	}

	if ((mDB01.exec_query(mQUERY)) != 0) {
		return false;
	}

	res = mDB01.get_res();
	if (res == NULL) {
		//LOG_TO_FILE_1 ("!Query failed - (%s).\n", mQUERY);
		//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mDB01.get_error_msg ().c_str ());
		return false;
	}
	while (row = mysql_fetch_row(res)) {
		TribeCount[0] = ::atoi(row[0]);
		TribeCount[1] = ::atoi(row[1]);
		TribeCount[2] = ::atoi(row[2]);
	}
	mDB01.clear_res();

	if (TribeCount[mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aTribe] == 0) {
		return true;
	}

	switch (mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aTribe) {
	case 0:
		sprintf(mQUERY,
			"UPDATE TribeControl "
			"SET aTribeType0Count = aTribeType0Count - 1 "
			"WHERE aWorldNumber = %d", mSERVER_INFO.mWorldNumber);
		break;
	case 1:
		sprintf(mQUERY,
			"UPDATE TribeControl "
			"SET aTribeType1Count = aTribeType1Count - 1 "
			"WHERE aWorldNumber = %d", mSERVER_INFO.mWorldNumber);
		break;
	case 2:
		sprintf(mQUERY,
			"UPDATE TribeControl "
			"SET aTribeType2Count = aTribeType2Count - 1 "
			"WHERE aWorldNumber = %d", mSERVER_INFO.mWorldNumber);
		break;
	default:
		return FALSE;
	}

	RECONNECT_TO_DATABASE01();
	if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		__LogMgr()->Log ("\t\t\tWhy - %s\n", mDB01.get_error_msg ().c_str ());
		//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mQUERY);
		return TRUE;
	}

	sprintf(mQUERY, "delete from valetshopinfo where ValetShopName ='%s'", mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName);
	RECONNECT_TO_DATABASE02();
	iAffected = 0;
	if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		__LogMgr()->Log ("![WARNING] The query execution failed in5 %s.\n", __FUNCTION__);
		__LogMgr()->Log ("\t\t\tWhy - %s\n", mDB01.get_error_msg ().c_str ());
		//SVR_TRACE();
		////LOG_TO_FILE_1("%s\n", mQUERY);
		return FALSE;
	}

	return TRUE;
}
//DB_PROCESS_07
void MyDB::DB_PROCESS_07(char tID[MAX_USER_ID_LENGTH], int tAvatarPost, char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tChangeAvatarName[MAX_AVATAR_NAME_LENGTH], int* tResult)
{
	int iAffected;

	sprintf(mQUERY, "update %s set aName='%s' where aName='%s'", mSERVER_INFO.mDB_1_Table02, tChangeAvatarName, tAvatarName);
	if (!RECONNECT_TO_DATABASE02())
	{
		*tResult = 1;
		return;
	}
	iAffected = 0;
	if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		*tResult = 2;
		return;
	}
	sprintf(mQUERY, "update %s set aName='%s' where aName='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_2_Table03, tChangeAvatarName, tAvatarName, mSERVER_INFO.mWorldNumber);
	if (!RECONNECT_TO_DATABASE01())
	{
		sprintf(mQUERY, "update %s set aName='%s' where aName='%s'", mSERVER_INFO.mDB_1_Table02, tAvatarName, tChangeAvatarName);
		RECONNECT_TO_DATABASE02();
		iAffected = 0;
		if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 3;
			return;
		}
		*tResult = 4;
		return;
	}
	iAffected = 0;
	if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		sprintf(mQUERY, "update %s set aName='%s' where aName='%s'", mSERVER_INFO.mDB_1_Table02, tAvatarName, tChangeAvatarName);
		RECONNECT_TO_DATABASE02();
		iAffected = 0;
		if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 5;
			return;
		}
		*tResult = 6;
		return;
	}
	switch (tAvatarPost)
	{
	case 0:
		sprintf(mQUERY, "update %s set aName01='%s' where uID='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_2_Table02, tChangeAvatarName, tID, mSERVER_INFO.mWorldNumber);
		break;
	case 1:
		sprintf(mQUERY, "update %s set aName02='%s' where uID='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_2_Table02, tChangeAvatarName, tID, mSERVER_INFO.mWorldNumber);
		break;
	case 2:
		sprintf(mQUERY, "update %s set aName03='%s' where uID='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_2_Table02, tChangeAvatarName, tID, mSERVER_INFO.mWorldNumber);
		break;
	default:
		sprintf(mQUERY, "update %s set aName='%s' where aName='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_2_Table03, tAvatarName, tChangeAvatarName, mSERVER_INFO.mWorldNumber);
		RECONNECT_TO_DATABASE01();
		iAffected = 0;
		if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 7;
			return;
		}
		sprintf(mQUERY, "update %s set aName='%s' where aName='%s'", mSERVER_INFO.mDB_1_Table02, tAvatarName, tChangeAvatarName);
		RECONNECT_TO_DATABASE02();
		iAffected = 0;
		if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 8;
			return;
		}
		*tResult = 9;
		return;
	}
	if (!RECONNECT_TO_DATABASE01())
	{
		sprintf(mQUERY, "update %s set aName='%s' where aName='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_2_Table03, tAvatarName, tChangeAvatarName, mSERVER_INFO.mWorldNumber);
		RECONNECT_TO_DATABASE01();
		iAffected = 0;
		if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 10;
			return;
		}
		sprintf(mQUERY, "update %s set aName='%s' where aName='%s'", mSERVER_INFO.mDB_1_Table02, tAvatarName, tChangeAvatarName);
		RECONNECT_TO_DATABASE02();
		iAffected = 0;
		if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 11;
			return;
		}
		*tResult = 12;
		return;
	}
	iAffected = 0;
	if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		sprintf(mQUERY, "update %s set aName='%s' where aName='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_2_Table03, tAvatarName, tChangeAvatarName, mSERVER_INFO.mWorldNumber);
		RECONNECT_TO_DATABASE01();
		iAffected = 0;
		if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 13;
			return;
		}
		sprintf(mQUERY, "update %s set aName='%s' where aName='%s'", mSERVER_INFO.mDB_1_Table02, tAvatarName, tChangeAvatarName);
		RECONNECT_TO_DATABASE02();
		iAffected = 0;
		if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 14;
			return;
		}
		*tResult = 15;
		return;
	}
	sprintf(mQUERY, "update %s set aName='%s' where aName='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_1_Table05, tChangeAvatarName, tAvatarName, mSERVER_INFO.mWorldNumber);
	if (!RECONNECT_TO_DATABASE01())
	{
		*tResult = 16;
		return;
	}
	iAffected = 0;
	if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		*tResult = 17;
		return;
	}

	sprintf(mQUERY, "update valetshopinfo set ValetShopName='%s' where ValetShopName='%s'", tChangeAvatarName, tAvatarName);
	if (!RECONNECT_TO_DATABASE02())
	{
		*tResult = 18;
		return;
	}
	iAffected = 0;
	if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
		sprintf(mQUERY, "update valetshopinfo set ValetShopName='%s' where ValetShopName='%s'", tAvatarName, tChangeAvatarName);
		RECONNECT_TO_DATABASE02();
		iAffected = 0;
		if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0) {
			*tResult = 19;
			return;
		}
		*tResult = 20;
		return;
	}

	*tResult = 0;
}
//DB_PROCESS_08
BOOL MyDB::DB_PROCESS_08(char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tInventory[2][MAX_INVENTORY_SLOT_NUM][6])
{
	int index01;
	int index02;
	char tempString01[1000];
	int iAffected;
	char aInventory[3457];

	aInventory[0] = '\0';
	for (index01 = 0; index01 < 2; index01++)
	{
		for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
		{
			sprintf(tempString01, "%05d%01d%01d%03d%09d%08d", (tInventory[index01][index02][0] % 100000), (tInventory[index01][index02][1] % 10), (tInventory[index01][index02][2] % 10), (tInventory[index01][index02][3] % 1000), (tInventory[index01][index02][4] % 1000000000), (tInventory[index01][index02][5] % 100000000));
			strcat(aInventory, tempString01);
		}
	}
	sprintf(mQUERY, "update %s set aInventory='%s' where aName='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_2_Table03, aInventory, tAvatarName, mSERVER_INFO.mWorldNumber);
	if (!RECONNECT_TO_DATABASE01())
	{
		return FALSE;
	}
	iAffected = 0;
	if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0)
		return FALSE;

	return TRUE;
}
//DB_PROCESS_09
BOOL MyDB::DB_PROCESS_09(char tCardNumber[MAX_USER_CARD_NUMBER_LENGTH], char tID[MAX_USER_ID_LENGTH], int tGiftInfo[10])
{
	int iAffected;
	int iCounts;
	char uID[MAX_USER_ID_LENGTH];
	long gData1;
	long gNumber1;
	long gData2;
	long gNumber2;
	long gData3;
	long gNumber3;
	long gData4;
	long gNumber4;
	long gData5;
	long gNumber5;
	MYSQL_ROW row;
	MYSQL_RES* res = NULL;

	sprintf(mQUERY, "select uID,gData1,gNumber1,gData2,gNumber2,gData3,gNumber3,gData4,gNumber4,gData5,gNumber5 from %s where gCard='%s'", mSERVER_INFO.mDB_1_Table03, tCardNumber);
	if (!RECONNECT_TO_DATABASE02())
	{
		return FALSE;
	}
	iAffected = 0;
	if ((iAffected = mDB02.exec_query(mQUERY)) < 0)
		return FALSE;
	iCounts = 0;
#if 0
	if ((iCounts = mDB01.get_num_rows()) != 1)
		return FALSE;
#endif
	res = mDB02.get_res();
	if (res == NULL) {
		//LOG_TO_FILE_1 ("!Query failed - (%s).\n", mQUERY);
		//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mDB02.get_error_msg ().c_str ());
		return FALSE;
	}
	while (row = mysql_fetch_row(res)) {
		::strncpy(uID, row[0], MAX_USER_ID_LENGTH - 1);
		gData1 = ::atol(row[1]);
		gNumber1 = ::atol(row[2]);
		gData2 = ::atol(row[3]);
		gNumber2 = ::atol(row[4]);
		gData3 = ::atol(row[5]);
		gNumber3 = ::atol(row[6]);
		gData4 = ::atol(row[7]);
		gNumber4 = ::atol(row[8]);
		gData5 = ::atol(row[9]);
		gNumber5 = ::atol(row[10]);
		++iCounts;
	}
	mDB01.clear_res();
	if (1 != iCounts) {
		return FALSE;
	}
	strcpy(tID, uID);
	tGiftInfo[0] = gData1;
	tGiftInfo[1] = gNumber1;
	tGiftInfo[2] = gData2;
	tGiftInfo[3] = gNumber2;
	tGiftInfo[4] = gData3;
	tGiftInfo[5] = gNumber3;
	tGiftInfo[6] = gData4;
	tGiftInfo[7] = gNumber4;
	tGiftInfo[8] = gData5;
	tGiftInfo[9] = gNumber5;
	return TRUE;
}
//DB_PROCESS_10
BOOL MyDB::DB_PROCESS_10(char tCardNumber[MAX_USER_CARD_NUMBER_LENGTH], int tGiftInfo[10])
{
	int iAffected;

	sprintf(mQUERY, "update %s set gData1=%d,gNumber1=%d,gData2=%d,gNumber2=%d,gData3=%d,gNumber3=%d,gData4=%d,gNumber4=%d,gData5=%d,gNumber5=%d where gCard='%s'", mSERVER_INFO.mDB_1_Table03, tGiftInfo[0], tGiftInfo[1], tGiftInfo[2], tGiftInfo[3], tGiftInfo[4], tGiftInfo[5], tGiftInfo[6], tGiftInfo[7], tGiftInfo[8], tGiftInfo[9], tCardNumber);
	if (!RECONNECT_TO_DATABASE02())
	{
		return FALSE;
	}
	iAffected = 0;
	if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0)
		return FALSE;

	return TRUE;
}
//DB_PROCESS_11
BOOL MyDB::DB_PROCESS_11(char tID[MAX_USER_ID_LENGTH], int tSaveItem[MAX_SAVE_ITEM_SLOT_NUM][4])
{
	int index01;
	char tempString01[1000];
	int iAffected;
	char uSaveItem[701];

	uSaveItem[0] = '\0';
	for (index01 = 0; index01 < MAX_SAVE_ITEM_SLOT_NUM; index01++)
	{
		sprintf(tempString01, "%05d%03d%09d%08d", (tSaveItem[index01][0] % 100000), (tSaveItem[index01][1] % 1000), (tSaveItem[index01][2] % 1000000000), (tSaveItem[index01][3] % 100000000));
		strcat(uSaveItem, tempString01);
	}
	sprintf(mQUERY, "update %s set uSaveItem='%s' where uID='%s' and aWorldNumber = %d", mSERVER_INFO.mDB_2_Table02, uSaveItem, tID, mSERVER_INFO.mWorldNumber);
	if (!RECONNECT_TO_DATABASE01())
	{
		return FALSE;
	}
	iAffected = 0;
	if (mDB01.exec_query(mQUERY, CMySQL::CLEAR) != 0)
		return FALSE;

	return TRUE;
}
//DB_PROCESS_12
BOOL MyDB::DB_PROCESS_12(WORLD_INFO* tWorldInfo)
{
	int iAffected;
	int iCounts;
	MYSQL_ROW row;
	MYSQL_RES* res = NULL;

	sprintf(mQUERY, "select mZone38WinTribe,mTribe1Symbol,mTribe2Symbol,mTribe3Symbol,mTribe4Symbol,mMonsterSymbol,mTribe1Point,mTribe2Point,mTribe3Point,mTribe4Point,mCloseTime,mCloseTribe,mPossibleAlliance01Date,mPossibleAlliance01Info,mPossibleAlliance02Date,mPossibleAlliance02Info,mPossibleAlliance03Date,mPossibleAlliance03Info,mPossibleAlliance04Date,mPossibleAlliance04Info,mAlliance0101,mAlliance0102,mAlliance0201,mAlliance0202,mTribe1VoteState,mTribe2VoteState,mTribe3VoteState,mTribe4VoteState,mClose1VoteState,mClose2VoteState,mClose3VoteState,mClose4VoteState,mTribe4QuestDate,mTribe4QuestState,mTribe4QuestName from %s WHERE aWorldNumber = %d", mSERVER_INFO.mDB_1_Table06, mSERVER_INFO.mWorldNumber);
	if (!RECONNECT_TO_DATABASE01())
	{
		return FALSE;
	}
	iAffected = 0;
	if ((iAffected = mDB01.exec_query(mQUERY)) < 0)
		return FALSE;
	iCounts = 0;
#if 0
	if ((iCounts = mDB01.get_num_rows()) != 1)
		return FALSE;
#endif
	res = mDB01.get_res();
	if (res == NULL) {
		//LOG_TO_FILE_1 ("!Query failed - (%s).\n", mQUERY);
		//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mDB01.get_error_msg ().c_str ());
		return FALSE;
	}
	while (row = mysql_fetch_row(res)) {
		tWorldInfo->mZone038WinTribe = ::atol(row[0]);
		tWorldInfo->mTribe1Symbol = ::atol(row[1]);
		tWorldInfo->mTribe2Symbol = ::atol(row[2]);
		tWorldInfo->mTribe3Symbol = ::atol(row[3]);
		tWorldInfo->mTribe4Symbol = ::atol(row[4]);
		tWorldInfo->mMonsterSymbol = ::atol(row[5]);
		tWorldInfo->mTribePoint[0] = ::atol(row[6]);
		tWorldInfo->mTribePoint[1] = ::atol(row[7]);
		tWorldInfo->mTribePoint[2] = ::atol(row[8]);
		tWorldInfo->mTribePoint[3] = ::atol(row[9]);
		tWorldInfo->mTribeCloseInfo[0] = ::atol(row[10]);
		tWorldInfo->mTribeCloseInfo[1] = ::atol(row[11]);
		tWorldInfo->mPossibleAllianceInfo[0][0] = ::atol(row[12]);
		tWorldInfo->mPossibleAllianceInfo[0][1] = ::atol(row[13]);
		tWorldInfo->mPossibleAllianceInfo[1][0] = ::atol(row[14]);
		tWorldInfo->mPossibleAllianceInfo[1][1] = ::atol(row[15]);
		tWorldInfo->mPossibleAllianceInfo[2][0] = ::atol(row[16]);
		tWorldInfo->mPossibleAllianceInfo[2][1] = ::atol(row[17]);
		tWorldInfo->mPossibleAllianceInfo[3][0] = ::atol(row[18]);
		tWorldInfo->mPossibleAllianceInfo[3][1] = ::atol(row[19]);
		tWorldInfo->mAllianceState[0][0] = ::atol(row[20]);
		tWorldInfo->mAllianceState[0][1] = ::atol(row[21]);
		tWorldInfo->mAllianceState[1][0] = ::atol(row[22]);
		tWorldInfo->mAllianceState[1][1] = ::atol(row[23]);
		tWorldInfo->mTribeVoteState[0] = ::atol(row[24]);
		tWorldInfo->mTribeVoteState[1] = ::atol(row[25]);
		tWorldInfo->mTribeVoteState[2] = ::atol(row[26]);
		tWorldInfo->mTribeVoteState[3] = ::atol(row[27]);
		tWorldInfo->mCloseVoteState[0] = ::atol(row[28]);
		tWorldInfo->mCloseVoteState[1] = ::atol(row[29]);
		tWorldInfo->mCloseVoteState[2] = ::atol(row[30]);
		tWorldInfo->mCloseVoteState[3] = ::atol(row[31]);
		tWorldInfo->mTribe4QuestDate = ::atol(row[32]);
		tWorldInfo->mTribe4QuestState = ::atol(row[33]);
		::strncpy(tWorldInfo->mTribe4QuestName, row[34], MAX_TRIBE4_QUEST_NAME_LENGTH);
		++iCounts;
	}

	mDB01.clear_res();
	if (1 != iCounts) {
		return FALSE;
	}

	return TRUE;
}
//DB_PROCESS_13
BOOL MyDB::DB_PROCESS_13(TRIBE_INFO* tTribeInfo)
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

	sprintf(mQUERY, "select mTribeVoteInfo,mTribe01Master,mTribe01SubMasterInfo,mTribe02Master,mTribe02SubMasterInfo,mTribe03Master,mTribe03SubMasterInfo,mTribe04Master,mTribe04SubMasterInfo from %s WHERE aWorldNumber = %d", mSERVER_INFO.mDB_1_Table07, mSERVER_INFO.mWorldNumber);
	if (!RECONNECT_TO_DATABASE01())
	{
		//LOG_TO_FILE_2 ("!Unable to connect to the database[%s] in %s method.\n", 
		//               mSERVER_INFO.mDB_1_Table07, __FUNCTION__);
		return FALSE;
	}
	iAffected = 0;
	if ((iAffected = mDB01.exec_query(mQUERY)) < 0) {
		//LOG_TO_FILE_1 ("!The query execution failed in %s.\n", __FUNCTION__);
		//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mDB01.get_error_msg ().c_str ());
		return FALSE;
	}
	iCounts = 0;
	res = mDB01.get_res();
	if (res == NULL) {
		//LOG_TO_FILE_1 ("!Query failed - (%s).\n", mQUERY);
		//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mDB01.get_error_msg ().c_str ());
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
		//LOG_TO_FILE("!As a result of a number of rows is not returned by the query.\n");
		//LOG_TO_FILE_1 ("\t\t\tRow counts = %d.\n", iCounts);
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
		//LOG_TO_FILE_1 ("!TribeVoteInfo, the length of the problem was different in %s.\n",
		//               __FUNCTION__);
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
		//LOG_TO_FILE_1 ("!Tribe01SubMasterInfo, the length of the problem was different in %s.\n",
		//               __FUNCTION__);
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
		//LOG_TO_FILE_1 ("!Tribe02SubMasterInfo, the length of the problem was different in %s.\n",
		//              __FUNCTION__);
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
		//LOG_TO_FILE_1 ("!Tribe03SubMasterInfo, the length of the problem was different in %s.\n",
		//               __FUNCTION__);
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
		//LOG_TO_FILE_1 ("!Tribe04SubMasterInfo, the length of the problem was different in %s.\n",
		//               __FUNCTION__);
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

//DB_PROCESS_14
int MyDB::DB_PROCESS_14(const char* ip_addr, const char* user_id)
{
	int iAffected;
	int iCounts;
	int iCheckValue = 0;
	MYSQL_ROW row;
	MYSQL_RES* res = NULL;

#if 0
	sprintf(mQUERY,
		"SELECT COUNT(uStartIP) AS cnt "
		"FROM PcRoomIpInfo "
		"WHERE uStartIP <= '%s' AND uEndIP >= '%s' "
		, ip_addr, ip_addr);
#endif
	sprintf(mQUERY,
		"SELECT COUNT(uStartIP) AS cnt "
		"FROM PcRoomIpInfo "
		"WHERE uStartIP = '%s' ", ip_addr);

	if (!RECONNECT_TO_DATABASE02())
	{
		return 0;
	}
	iAffected = 0;
	if ((iAffected = mDB02.exec_query(mQUERY)) < 0) {
		return 0;
	}
	iCounts = 0;

	res = mDB02.get_res();
	if (res == NULL) {
		//LOG_TO_FILE_1 ("!Query failed - (%s).\n", mQUERY);
		//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mDB02.get_error_msg ().c_str ());
		return 0;
	}
	while (row = mysql_fetch_row(res)) {
		iCheckValue = ::atoi(row[0]);
		++iCounts;
	}
	mDB02.clear_res();

	if (iCheckValue > 0) {
		if (iCheckValue > 1) {
			//LOG_TO_FILE_2("![%s] : duplicate ip address : %s\n", __FUNCTION__, ip_addr);
		}
		return 2;
	}

	return 0;
}

bool MyDB::DB_PROCESS_15(int aTribe)
{
	MYSQL_ROW row;
	MYSQL_RES* res = NULL;
	int iCounts = 0;
	char CreateFlag[3];

	::memset(CreateFlag, 0, 3);

	sprintf(mQUERY,
		"SELECT aCreateFlag0, aCreateFlag1, aCreateFlag2 "
		"FROM TribeControl "
		"WHERE aWorldNumber=%d", mSERVER_INFO.mWorldNumber);

	if (!RECONNECT_TO_DATABASE01()) {
		return false;
	}

	if ((mDB01.exec_query(mQUERY)) != 0) {
		return false;
	}

	res = mDB01.get_res();
	if (res == NULL) {
		//LOG_TO_FILE_1 ("!Query failed - (%s).\n", mQUERY);
		//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mDB01.get_error_msg ().c_str ());
		return 0;
	}
	while (row = mysql_fetch_row(res)) {
		CreateFlag[0] = *(row[0]);
		CreateFlag[1] = *(row[1]);
		CreateFlag[2] = *(row[2]);
		++iCounts;
	}
	mDB01.clear_res();

	if (iCounts != 1) {
		return false;
	}

	if (CreateFlag[aTribe] == '0') {
		return false;
	}

	return true;
}

// @ __WEB_MALL__
//DB_PROCESS_16 // \BAϹ\CC, \C0\AF\B7\B4, \C5\CDŰ\B4\C2 Web Mall\C0\BB \BB\E7\BF\EB\C7ؼ\AD \BC\B1\B9\B0 \B9ޱ\E2 ó\B8\AE\C7\D4.
//DB_PROCESS_17 // \BC\B1\B9\B0 \B9ޱ\E2 ó\B8\AE \BA\B0\B5\B5\B7\CE \C7\CF\C1\F6 \BE\CA\C0\BD.

//DB_PROCESS_18
BOOL MyDB::DB_PROCESS_18(char* tID, int tLimit, int* tList, int& tCount, WEBMALL_INFO* tGiftInfo)
{
	int iAffected;
	int iCounts;
	int index01 = 0;

	MYSQL_ROW row;
	MYSQL_RES* res = NULL;

	sprintf(mQUERY,
		"select a.gGiftItemSetNumber, (a.gPurchaseCnt - a.gUsedCnt), ifnull(b.gGiftItem01, 0), ifnull(b.gGiftItem01Cnt, 0), "
		"ifnull(b.gGiftItem02, 0), ifnull(b.gGiftItem02Cnt, 0), ifnull(b.gGiftItem03, 0), ifnull(b.gGiftItem03Cnt, 0), ifnull(b.gGiftItem04, 0), ifnull(b.gGiftItem04Cnt, 0), "
		"ifnull(b.gGiftItem05, 0), ifnull(b.gGiftItem05Cnt, 0), ifnull(b.gGiftItem06, 0), ifnull(b.gGiftItem06Cnt, 0), ifnull(b.gGiftItem07, 0), ifnull(b.gGiftItem07Cnt, 0), "
		"ifnull(b.gGiftItem08, 0), ifnull(b.gGiftItem08Cnt, 0), ifnull(b.gGiftItem09, 0), ifnull(b.gGiftItem09Cnt, 0), ifnull(b.gGiftItem10, 0), ifnull(b.gGiftItem10Cnt, 0), "
		"a.gWebMallSeq "
		"from %s a left join %s b on a.gGiftItemSetNumber = b.gGiftItemSetNumber where a.gUseID = '%s' and 0 < (a.gPurchaseCnt - a.gUsedCnt) order by a.gWebMallSeq asc limit %d",
		mSERVER_INFO.mDB_1_Table09, mSERVER_INFO.mDB_1_Table10, tID, tLimit);

	if (!RECONNECT_TO_DATABASE02())
	{
		return FALSE;
	}
	iAffected = 0;
	if ((iAffected = mDB02.exec_query(mQUERY)) < 0)
		return FALSE;
	iCounts = 0;
#if 0
	if ((iCounts = mDB01.get_num_rows()) != 1)
		return FALSE;
#endif
	res = mDB02.get_res();
	if (res == NULL) {
		//LOG_TO_FILE_1 ("!Query failed - (%s).\n", mQUERY);
		//LOG_TO_FILE_1 ("\t\t\tWhy - %s\n", mDB02.get_error_msg ().c_str ());
		return FALSE;
	}
	while (row = mysql_fetch_row(res)) {
		tList[iCounts * 3] = ::atoi(row[0]);
		tList[iCounts * 3 + 1] = ::atoi(row[1]);
		tList[iCounts * 3 + 2] = 0;
		tGiftInfo[iCounts].mGiftData[0][0] = ::atoi(row[2]);
		tGiftInfo[iCounts].mGiftData[0][1] = ::atoi(row[3]);
		tGiftInfo[iCounts].mGiftData[1][0] = ::atoi(row[4]);
		tGiftInfo[iCounts].mGiftData[1][1] = ::atoi(row[5]);
		tGiftInfo[iCounts].mGiftData[2][0] = ::atoi(row[6]);
		tGiftInfo[iCounts].mGiftData[2][1] = ::atoi(row[7]);
		tGiftInfo[iCounts].mGiftData[3][0] = ::atoi(row[8]);
		tGiftInfo[iCounts].mGiftData[3][1] = ::atoi(row[9]);
		tGiftInfo[iCounts].mGiftData[4][0] = ::atoi(row[10]);
		tGiftInfo[iCounts].mGiftData[4][1] = ::atoi(row[11]);
		tGiftInfo[iCounts].mGiftData[5][0] = ::atoi(row[12]);
		tGiftInfo[iCounts].mGiftData[5][1] = ::atoi(row[13]);
		tGiftInfo[iCounts].mGiftData[6][0] = ::atoi(row[14]);
		tGiftInfo[iCounts].mGiftData[6][1] = ::atoi(row[15]);
		tGiftInfo[iCounts].mGiftData[7][0] = ::atoi(row[16]);
		tGiftInfo[iCounts].mGiftData[7][1] = ::atoi(row[17]);
		tGiftInfo[iCounts].mGiftData[8][0] = ::atoi(row[18]);
		tGiftInfo[iCounts].mGiftData[8][1] = ::atoi(row[19]);
		tGiftInfo[iCounts].mGiftData[9][0] = ::atoi(row[20]);
		tGiftInfo[iCounts].mGiftData[9][1] = ::atoi(row[21]);
		//2009.10.20 : \B1輺\BC\F6: \C0\A5\B8\F4\C0\C7 \B1\B8\B8\C5 \C0Ϸ\C3 \B9\F8ȣ\B8\A6 \B3ֱ\E2 \C0\A7\C7\D1 \BA\AF\BC\F6 \C3߰\A1
		tGiftInfo[iCounts].mWebMallSeq = ::atoi(row[22]);


		for (index01 = 0; index01 < MAX_GIFT_ITEM_NUM; ++index01) {
			if (0 != tGiftInfo[iCounts].mGiftData[index01][0])
				continue;
			tGiftInfo[iCounts].mTotalGiftNum = index01;
			break;
		}
		++iCounts;
	}
	tCount = iCounts;
	mDB02.clear_res();

	return TRUE;
}
//DB_PROCESS_19
BOOL MyDB::DB_PROCESS_19(char* tID, int tItemSetNumber, int tUsedCnt, int tWebMallSeq)
{
	int iAffected;

	sprintf(mQUERY, "update %s set gUsedCnt = gUsedCnt + %d where gUseID = '%s' and gWebMallSeq = %d ",
		mSERVER_INFO.mDB_1_Table09, tUsedCnt, tID, tWebMallSeq);

	if (!RECONNECT_TO_DATABASE02())
	{
		return FALSE;
	}

	iAffected = 0;
	if (mDB02.exec_query(mQUERY, CMySQL::CLEAR) != 0)
		return FALSE;

	return TRUE;
} // __WEB_MALL__ @
//-------------------------------------------------------------------------------------------------

//DB_PROCESS_19
int MyDB::DB_PROCESS_21(char* aName)
{
	int iAffected;
	int TribeCount[3];
	MYSQL_ROW row;
	MYSQL_RES* res = NULL;
	int index01;
	int index02;
	int ValetBar = 0;
	int ValetMoney = 0;
	FILE* fp;

	char ValetInfo[5][5][200];
	::memset(ValetInfo, '0', sizeof(ValetInfo));

	for (index01 = 0; index01 < 5; index01++)
	{
		for (index02 = 0; index02 < 5; index02++)
		{
			ValetInfo[index01][index02][199] = '\0';;
		}
	}
	sprintf(mQUERY, "insert into valetshopinfo values ('%s',"
		"'%s','%s','%s','%s','%s',"
		"'%s','%s','%s','%s','%s',"
		"'%s','%s','%s','%s','%s',"
		"'%s','%s','%s','%s','%s',"
		"'%s','%s','%s','%s','%s',%d,%d)",
		aName,
		ValetInfo[0][0], ValetInfo[0][1], ValetInfo[0][2], ValetInfo[0][3], ValetInfo[0][4],
		ValetInfo[1][0], ValetInfo[1][1], ValetInfo[1][2], ValetInfo[1][3], ValetInfo[1][4],
		ValetInfo[2][0], ValetInfo[2][1], ValetInfo[2][2], ValetInfo[2][3], ValetInfo[2][4],
		ValetInfo[3][0], ValetInfo[3][1], ValetInfo[3][2], ValetInfo[3][3], ValetInfo[3][4],
		ValetInfo[4][0], ValetInfo[4][1], ValetInfo[4][2], ValetInfo[4][3], ValetInfo[4][4], ValetBar, ValetMoney);
	if (!RECONNECT_TO_DATABASE01())
	{
		return 1;
	}
	iAffected = 0;
	if ((mDB01.exec_query(mQUERY, CMySQL::CLEAR)) != 0) {
		return 2;
	}
	return 0;
}
