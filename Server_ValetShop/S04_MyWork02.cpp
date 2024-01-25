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
//--------------//
//ZONE->PLAYUSER//
//--------------//
//W_ZONE_FOR_PLAYUSER_SEND
void W_ZONE_FOR_VALET_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 0)
	{
		mUSER[tUserIndex].Quit(4001);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tZoneNumber;
	CopyMemory(&tZoneNumber, &tPacket[1], 4);

	if ((tZoneNumber < MIN_VALID_ZONE_NUMBER) || (tZoneNumber > MAX_VALID_ZONE_NUMBER))
	{
		mUSER[tUserIndex].Quit(4002);
		return;
	}

	int index01;

	for (index01 = 0; index01 < MAX_USER_NUM; index01++)
	{
		if ((mUSER[index01].mCheckServerType == 2) && (mUSER[index01].mZoneServerNumber == tZoneNumber))
		{
			mUSER[index01].Quit(4003);
		}
	}
	mUSER[tUserIndex].mCheckServerType = 2;
	mUSER[tUserIndex].mZoneServerNumber = tZoneNumber;
	mTRANSFER.B_ZONE_FOR_PLAYUSER_RECV();
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_ZONE_OK_FOR_PLAYUSER_SEND
void W_ZONE_OK_FOR_VALET_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(4004);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();
}
//void W_DUPEFIX
void W_VALET_DUPEFIX(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];

	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(1001);
		return;
	}

	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tPlayUserIndex;
	char tID[MAX_USER_ID_LENGTH];
	AVATAR_INFO tAvatarInfo;
	AUTH_INFO tAuthInfo;
	CopyMemory(&tPlayUserIndex, &tPacket[1], 4);
	CopyMemory(&tID[0], &tPacket[5], MAX_USER_ID_LENGTH);
	tID[(MAX_USER_ID_LENGTH - 1)] = '\0';
	CopyMemory(&tAvatarInfo, &tPacket[(5 + MAX_USER_ID_LENGTH)], sizeof(AVATAR_INFO));
	CopyMemory(&tAuthInfo, &tPacket[(5 + MAX_USER_ID_LENGTH + sizeof(AVATAR_INFO))], sizeof(AUTH_INFO));
	mTRANSFER.B_DUPEFIX();
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//void W_DUPEFIX1
void W_VALET_DUPEFIX1(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(1002);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tPlayUserIndex;
	char tID[MAX_USER_ID_LENGTH];
	AVATAR_INFO tAvatarInfo;
	AUTH_INFO tAuthInfo;
	CopyMemory(&tPlayUserIndex, &tPacket[1], 4);
	CopyMemory(&tID[0], &tPacket[5], MAX_USER_ID_LENGTH);
	tID[(MAX_USER_ID_LENGTH - 1)] = '\0';
	CopyMemory(&tAvatarInfo, &tPacket[(5 + MAX_USER_ID_LENGTH)], sizeof(AVATAR_INFO));
	CopyMemory(&tAuthInfo, &tPacket[(5 + MAX_USER_ID_LENGTH + sizeof(AVATAR_INFO))], sizeof(AUTH_INFO));
	mTRANSFER.B_DUPEFIX1();
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//ValetShop
//W_VALET_SHOP_INFO
void W_VALET_SHOP_INFO(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(1003);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tResult;
	int tSort;
	char aName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&aName[0], &tPacket[5], MAX_AVATAR_NAME_LENGTH);
	aName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
	VALETSHOP_INFO tValetShop;


	

	switch (tSort)
	{
	case 1:
	case 2:
	case 3://Bilgisini yolluyor
		mDB.DB_PROCESS_20(aName, &tValetShop, &tResult);
		Logger("![%s][%d][%s][%d]",__FUNCTION__, tSort, aName, tResult);
		mTRANSFER.B_VALETSHOPINFO(tResult, &tValetShop);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	default:
		break;
	}
}
//W_VALET_SHOP_UPDATE
void W_VALET_SHOP_UPDATE(int tUserIndex)
{

	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(1004);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tResult;
	char aName[MAX_AVATAR_NAME_LENGTH];
	VALETSHOP_INFO tValetShop;
	CopyMemory(&aName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH);
	aName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
	CopyMemory(&tValetShop, &tPacket[(1 + MAX_AVATAR_NAME_LENGTH)], sizeof(VALETSHOP_INFO));
	mDB.DB_PROCESS_21(aName, &tValetShop, &tResult);
	mTRANSFER.B_VALETSHOPUPDATE(tResult);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	Logger("![%s][%s][%d]",__FUNCTION__, aName, tResult);
	return;
}
//W_VALET_SHOP_BUY
void W_VALET_SHOP_BUY(int tUserIndex)
{

	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(1005);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	printf("Geldissdsd\n");

	int tResult;
	int tPage;
	int tSlot;
	int tItemNumber;
	int tSort;
	int tValue[8];


	char aName[MAX_AVATAR_NAME_LENGTH];
	VALETSHOP_INFO tValetShop;
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&aName[0], &tPacket[5], MAX_AVATAR_NAME_LENGTH);
	aName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
	CopyMemory(&tPage, &tPacket[5 + MAX_AVATAR_NAME_LENGTH], 4);
	CopyMemory(&tSlot, &tPacket[9 + MAX_AVATAR_NAME_LENGTH], 4);
	CopyMemory(&tItemNumber, &tPacket[13 + MAX_AVATAR_NAME_LENGTH], 4);

	switch (tSort)
	{
	case 1://Keni valet shopu
		//Valet Shopu Çekiyor
		mDB.DB_PROCESS_20(aName, &tValetShop, &tResult);
		//1 Yolla geri dönüþ?		printf("aName === %s , tResult === %d, W_VALET_SHOP_UPDATE\n", aName, tResult);
		if (tValetShop.mItemInfo[tPage][tSlot][0] != tItemNumber)
		{
			mTRANSFER.B_VALETSHOPBUY(1);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tValetShop.mItemInfo[tPage][tSlot][0] = 0;
		tValetShop.mItemInfo[tPage][tSlot][1] = 0;
		tValetShop.mItemInfo[tPage][tSlot][2] = 0;
		tValetShop.mItemInfo[tPage][tSlot][3] = 0;
		tValetShop.mItemInfo[tPage][tSlot][4] = 0;
		tValetShop.mSoketInfo[tPage][tSlot][0] = 0;
		tValetShop.mSoketInfo[tPage][tSlot][1] = 0;
		tValetShop.mSoketInfo[tPage][tSlot][2] = 0;
		//Valet Shopu Güncelliyor
		mDB.DB_PROCESS_21(aName, &tValetShop, &tResult);
		Logger("![%s][%d][%s][%d]",__FUNCTION__, tSort, aName, tResult);
		mTRANSFER.B_VALETSHOPBUY(tResult);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 2://Alýþveri?		//Valet Shopu Çekiyor
		mDB.DB_PROCESS_20(aName, &tValetShop, &tResult);
		//1 Yolla geri dönüþ?
		if (tValetShop.mItemInfo[tPage][tSlot][0] != tItemNumber)
		{
			mTRANSFER.B_VALETSHOPBUY(1);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tValetShop.mShopMoney += tValetShop.mItemInfo[tPage][tSlot][4];

		if (tValetShop.mShopMoney > 999999999)
		{
			tValetShop.mShopMoney -= 1000000000;
			tValetShop.mShopBar += 1;
		}
		tValetShop.mItemInfo[tPage][tSlot][0] = 0;
		tValetShop.mItemInfo[tPage][tSlot][1] = 0;
		tValetShop.mItemInfo[tPage][tSlot][2] = 0;
		tValetShop.mItemInfo[tPage][tSlot][3] = 0;
		tValetShop.mItemInfo[tPage][tSlot][4] = 0;
		tValetShop.mSoketInfo[tPage][tSlot][0] = 0;
		tValetShop.mSoketInfo[tPage][tSlot][1] = 0;
		tValetShop.mSoketInfo[tPage][tSlot][2] = 0;
		//Valet Shopu Güncelliyor
		mDB.DB_PROCESS_21(aName, &tValetShop , &tResult);
		//0 yolla
		Logger("![%s][%d][%s][%d]",__FUNCTION__, tSort, aName, tResult);
		mTRANSFER.B_VALETSHOPBUY(tResult);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	default:
		break;
	}
	return;
}

