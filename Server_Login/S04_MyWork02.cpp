//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "Shengming.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//WORKER_FUNCTION
//-------------------------------------------------------------------------------------------------
//INSTANCE
//WORKER_FUNCTION
//-------------------------------------------------------------------------------------------------
//INSTANCE
WORKER_FUNCTION W_FUNCTION[256];
//W_LOGIN_SEND

typedef struct
{
	int mTotalNPCNum;
	int mNPCNumber[MAX_NPC_OBJECT_NUM];
	float mNPCCoord[MAX_NPC_OBJECT_NUM][3];
	float mNPCAngle[MAX_NPC_OBJECT_NUM];
}
ZONENPCINFODATA;
//DEFINE




ZONENPCINFODATA mDATA[MAX_ZONE_NUMBER_NUM];



void W_LOGIN_SEND(int tUserIndex)
{

	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	
	char tID[MAX_USER_ID_LENGTH];
	char tPassword[MAX_USER_PASSWORD_LENGTH];
	int tVersion;
	CopyMemory(&tID[0], &tPacket[1], MAX_USER_ID_LENGTH);
	tID[(MAX_USER_ID_LENGTH - 1)] = '\0';
	CopyMemory(&tPassword[0], &tPacket[(1 + MAX_USER_ID_LENGTH)], MAX_USER_PASSWORD_LENGTH);
	tPassword[(MAX_USER_PASSWORD_LENGTH - 1)] = '\0';
	CopyMemory(&tVersion, &tPacket[(1 + MAX_USER_ID_LENGTH + MAX_USER_PASSWORD_LENGTH)], 4);

	::memset(mUSER[tUserIndex].mAvatarInfo, 0, sizeof(AVATAR_INFO) * 3);

	//__LogMgr()->Log_2("--------> %d %d\n", MAX_USER_ID_LENGTH, MAX_USER_PASSWORD_LENGTH);



	int index01;
	int index02;
	int index03;
	int tResult;
	char first_login = '0';
	char tMousePassword[MAX_MOUSE_PASSWORD_LENGTH];
	if (mGAME.mMaxPlayerNum == 0)
	{
		mTRANSFER.B_LOGIN_RECV(1, &tID[0],  0, 0, 0, 0, 0, "0000", 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		for (index01 = 0; index01 < MAX_USER_AVATAR_NUM; index01++)
		{
			mTRANSFER.B_USER_AVATAR_INFO(&mUSER[tUserIndex].mAvatarInfo[index01]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		__LogMgr()->Log("![WARNING - (1)] The server is not yet ready - Maximum User Number is 0.\n");
		mTRANSFER.B_RCMD_WORLD_SEND();
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mGAME.CompareBlockIPInfo(mUSER[tUserIndex].mIPPart[0], mUSER[tUserIndex].mIPPart[1], mUSER[tUserIndex].mIPPart[2], mUSER[tUserIndex].mIPPart[3]))
	{
		mTRANSFER.B_LOGIN_RECV(2, &tID[0],  0, 0, 0, 0, 0, "0000", 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		for (index01 = 0; index01 < MAX_USER_AVATAR_NUM; index01++)
		{
			mTRANSFER.B_USER_AVATAR_INFO(&mUSER[tUserIndex].mAvatarInfo[index01]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		__LogMgr()->Log("![WARNING - (2)] IP[%s] is blocked from connection attempt.\n", mUSER[tUserIndex].mIP);
		mTRANSFER.B_RCMD_WORLD_SEND();
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mGAME.mPresentPlayerNum >= mGAME.mMaxPlayerNum)
	{
		mTRANSFER.B_LOGIN_RECV(3, &tID[0],  0, 0, 0, 0, 0, "0000", 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		for (index01 = 0; index01 < MAX_USER_AVATAR_NUM; index01++)
		{
			mTRANSFER.B_USER_AVATAR_INFO(&mUSER[tUserIndex].mAvatarInfo[index01]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		__LogMgr()->Log("![WARNING - (3)] You cannot connect to exceed the maximum user number of connections.\n");
		mTRANSFER.B_RCMD_WORLD_SEND();
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (tVersion != mSERVER_INFO.mServerVersion)
	{
		mTRANSFER.B_LOGIN_RECV(4, &tID[0],  0, 0, 0, 0, 0, "0000", 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		for (index01 = 0; index01 < MAX_USER_AVATAR_NUM; index01++)
		{
			mTRANSFER.B_USER_AVATAR_INFO(&mUSER[tUserIndex].mAvatarInfo[index01]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		__LogMgr()->Log("![WARNING - (4)] This differs from server-version(%d) of the client-version(%d).\n",
			mSERVER_INFO.mServerVersion, tVersion);
		mTRANSFER.B_RCMD_WORLD_SEND();
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	mUSER[tUserIndex].uLoginPremiumPCRoom = mDB.DB_PROCESS_14(mUSER[tUserIndex].mIP, tID);
	mDB.DB_PROCESS_02(&mUSER[tUserIndex].mIP[0], &tID[0], &tPassword[0], &mUSER[tUserIndex].uID[0], &mUSER[tUserIndex].uCheckMOTP, &mUSER[tUserIndex].uMousePassword[0], &mUSER[tUserIndex].uSecretCard, &mUSER[tUserIndex].uUserSort, &mUSER[tUserIndex].uGoodFellow, &mUSER[tUserIndex].UserRandom, &mUSER[tUserIndex].uLoginPremium, &mUSER[tUserIndex].uTraceState, &mUSER[tUserIndex].uBonus100Money, &mUSER[tUserIndex].uPremiumServerExpirationDate, &mUSER[tUserIndex].uSaveMoney, mUSER[tUserIndex].uSaveItem, mUSER[tUserIndex].mAvatarInfo, &mUSER[tUserIndex].mAuthInfo, &tResult, &first_login, &mUSER[tUserIndex].uSeyisBar, mUSER[tUserIndex].uSaveSocket);
	if (tResult != 0)
	{
		mTRANSFER.B_LOGIN_RECV(tResult, &tID[0],  0, 0, 0, 0, 0, "0000", 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		for (index01 = 0; index01 < MAX_USER_AVATAR_NUM; index01++)
		{
			mTRANSFER.B_USER_AVATAR_INFO(&mUSER[tUserIndex].mAvatarInfo[index01]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		mTRANSFER.B_RCMD_WORLD_SEND();
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		__LogMgr()->Log("![WARNING - (%d)] Login failed by database.\n", tResult);
		return;
	}

	mUSER[tUserIndex].UserRandom = rand() % 10000;
	mUSER[tUserIndex].uLoginPremium = mUSER[tUserIndex].uUserSort;
	mUSER[tUserIndex].mAuthInfo.IlkMapeGiris = 0;


	
	mPLAYUSER_COM.U_REGISTER_USER_FOR_LOGIN_1_SEND(&mUSER[tUserIndex].mIP[0], &mUSER[tUserIndex].uID[0], mUSER[tUserIndex].uUserSort, mUSER[tUserIndex].uGoodFellow, mUSER[tUserIndex].UserRandom, mUSER[tUserIndex].uLoginPremium, mUSER[tUserIndex].uLoginPremiumPCRoom, mUSER[tUserIndex].uTraceState, mUSER[tUserIndex].uBonus100Money, mUSER[tUserIndex].uPremiumServerExpirationDate, &mUSER[tUserIndex].mAuthInfo); // mUSER[tUserIndex].uPremiumServerExpirationDate Ãß°¡. // @_Premium_Server_@
	__LogMgr()->Log("PLAYUSER_COM.mRecv_Result === %d", mPLAYUSER_COM.mRecv_Result);
	switch (mPLAYUSER_COM.mRecv_Result)
	{
	case 0:
		break;
	case 1:
		mTRANSFER.B_LOGIN_RECV(8, &tID[0],  0, 0, 0, 0, 0, "0000", 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		for (index01 = 0; index01 < MAX_USER_AVATAR_NUM; index01++)
		{
			mTRANSFER.B_USER_AVATAR_INFO(&mUSER[tUserIndex].mAvatarInfo[index01]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		mTRANSFER.B_RCMD_WORLD_SEND();
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		__LogMgr()->Log("![WARNING - (8)] You cannot connect to exceed the maximum user number of connections.\n");
		return;
	case 2:
		mTRANSFER.B_LOGIN_RECV(5, &tID[0],  0, 0, 0, 0, 0, "0000", 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		for (index01 = 0; index01 < MAX_USER_AVATAR_NUM; index01++)
		{
			mTRANSFER.B_USER_AVATAR_INFO(&mUSER[tUserIndex].mAvatarInfo[index01]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		mTRANSFER.B_RCMD_WORLD_SEND();
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		__LogMgr()->Log("![WARNING - (5)] You cannot connect to exceed the maximum user number of connections.\n");
		return;
	case 3:
		mTRANSFER.B_LOGIN_RECV(5, &tID[0], 0, 0, 0, 0, 0, "0000", 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		for (index01 = 0; index01 < MAX_USER_AVATAR_NUM; index01++)
		{
			mTRANSFER.B_USER_AVATAR_INFO(&mUSER[tUserIndex].mAvatarInfo[index01]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		mTRANSFER.B_RCMD_WORLD_SEND();
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		__LogMgr()->Log("![WARNING - (5)] Login failed state change.\n", tResult);
		return;
	case 4:
		mTRANSFER.B_LOGIN_RECV(13, &tID[0], 0, 0, 0, 0, 0, "0000", 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		for (index01 = 0; index01 < MAX_USER_AVATAR_NUM; index01++)
		{
			mTRANSFER.B_USER_AVATAR_INFO(&mUSER[tUserIndex].mAvatarInfo[index01]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		mTRANSFER.B_RCMD_WORLD_SEND();
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		__LogMgr()->Log("![WARNING - (13)] Have the right to the same IP can not log on the premium.\n");
		return;
	default:
		mTRANSFER.B_LOGIN_RECV(5, &tID[0], 0, 0, 0, 0, 0, "0000", 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		for (index01 = 0; index01 < MAX_USER_AVATAR_NUM; index01++)
		{
			mTRANSFER.B_USER_AVATAR_INFO(&mUSER[tUserIndex].mAvatarInfo[index01]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		mTRANSFER.B_RCMD_WORLD_SEND();
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	mUSER[tUserIndex].mCheckValidState = TRUE;
	mUSER[tUserIndex].mRegisterTime = GetTickCount();
	mUSER[tUserIndex].mPlayUserIndex = mPLAYUSER_COM.mRecv_PlayUserIndex;
	mUSER[tUserIndex].mSecondLoginTryNum = 0;
	mUSER[tUserIndex].mSecondLoginSort = 0;

	if (mUSER[tUserIndex].uCheckMOTP == 0)
	{
		mUSER[tUserIndex].mSecondLoginSort = 1;
	}
	else
	{
		mUSER[tUserIndex].mSecondLoginSort = 0;
	}

	mUSER[tUserIndex].mCheckDemandGiftIfo = FALSE;
	mUSER[tUserIndex].mMoveZoneResult = 0;
	if (strcmp(mUSER[tUserIndex].uMousePassword, "") == 0)
	{
		strcpy(tMousePassword, "");
	}
	else
	{
		strcpy(tMousePassword, "****");
	}

	__LogMgr()->Log("first_login : %c\n", first_login);
	mTRANSFER.B_LOGIN_RECV(0, &mUSER[tUserIndex].uID[0], mUSER[tUserIndex].uUserSort, mUSER[tUserIndex].UserRandom, mUSER[tUserIndex].uLoginPremium, mUSER[tUserIndex].uLoginPremiumPCRoom, mUSER[tUserIndex].mSecondLoginSort, &tMousePassword[0], mUSER[tUserIndex].mSecretCardIndex01, mUSER[tUserIndex].mSecretCardIndex02, first_login);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);


	for (index01 = 0; index01 < MAX_USER_AVATAR_NUM; index01++)
	{
		if (strcmp(&mUSER[tUserIndex].mAvatarInfo[index01].aName[0], "") == 0)
		{
			continue;
		}

		if (mUSER[tUserIndex].mAvatarInfo[index01].AutoBuffScroll < mGAME.ReturnNowDate())
		{
			mUSER[tUserIndex].mAvatarInfo[index01].AutoBuffScroll = 0;
		}

		if (mUSER[tUserIndex].mAvatarInfo[index01].aExpandInventoryDate < mGAME.ReturnNowDate())
		{
			mUSER[tUserIndex].mAvatarInfo[index01].aExpandInventoryDate = 0;
		}

		if (mUSER[tUserIndex].mAvatarInfo[index01].aExpandStoreDate < mGAME.ReturnNowDate())
		{
			mUSER[tUserIndex].mAvatarInfo[index01].aExpandStoreDate = 0;
		}

		for (index02 = 0; index02 < MAX_EQUIP_SLOT_NUM; index02++)
		{
			if (mGAME.CheckDeleteItem(mUSER[tUserIndex].mAvatarInfo[index01].aEquip[index02][0]))
			{
				mUSER[tUserIndex].mAvatarInfo[index01].aEquip[index02][0] = 0;
				mUSER[tUserIndex].mAvatarInfo[index01].aEquip[index02][1] = 0;
				mUSER[tUserIndex].mAvatarInfo[index01].aEquip[index02][2] = 0;
				mUSER[tUserIndex].mAvatarInfo[index01].aEquip[index02][3] = 0;
			}
		}

		for (index02 = 0; index02 < 2; index02++)
		{
			for (index03 = 0; index03 < MAX_INVENTORY_SLOT_NUM; index03++)
			{
				if (mGAME.CheckDeleteItem(mUSER[tUserIndex].mAvatarInfo[index01].aInventory[index02][index03][0]))
				{
					mUSER[tUserIndex].mAvatarInfo[index01].aInventory[index02][index03][0] = 0;
					mUSER[tUserIndex].mAvatarInfo[index01].aInventory[index02][index03][1] = 0;
					mUSER[tUserIndex].mAvatarInfo[index01].aInventory[index02][index03][2] = 0;
					mUSER[tUserIndex].mAvatarInfo[index01].aInventory[index02][index03][3] = 0;
					mUSER[tUserIndex].mAvatarInfo[index01].aInventory[index02][index03][4] = 0;
					mUSER[tUserIndex].mAvatarInfo[index01].aInventory[index02][index03][5] = 0;
				}
			}
		}
		for (index02 = 0; index02 < MAX_TRADE_SLOT_NUM; index02++)
		{
			if (mGAME.CheckDeleteItem(mUSER[tUserIndex].mAvatarInfo[index01].aTrade[index02][0]))
			{
				mUSER[tUserIndex].mAvatarInfo[index01].aTrade[index02][0] = 0;
				mUSER[tUserIndex].mAvatarInfo[index01].aTrade[index02][1] = 0;
				mUSER[tUserIndex].mAvatarInfo[index01].aTrade[index02][2] = 0;
				mUSER[tUserIndex].mAvatarInfo[index01].aTrade[index02][3] = 0;
			}
		}
		for (index02 = 0; index02 < 2; index02++)
		{
			for (index03 = 0; index03 < MAX_STORE_ITEM_SLOT_NUM; index03++)
			{
				if (mGAME.CheckDeleteItem(mUSER[tUserIndex].mAvatarInfo[index01].aStoreItem[index02][index03][0]))
				{
					mUSER[tUserIndex].mAvatarInfo[index01].aStoreItem[index02][index03][0] = 0;
					mUSER[tUserIndex].mAvatarInfo[index01].aStoreItem[index02][index03][1] = 0;
					mUSER[tUserIndex].mAvatarInfo[index01].aStoreItem[index02][index03][2] = 0;
					mUSER[tUserIndex].mAvatarInfo[index01].aStoreItem[index02][index03][3] = 0;
				}
			}
		}
		for (index02 = 0; index02 < 3; index02++)
		{
			for (index03 = 0; index03 < MAX_HOT_KEY_NUM; index03++)
			{
				switch (mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][2])
				{
				case 1:
					if ((mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][0] < 1) || (mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][1] < 1))
					{
						mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][0] = 0;
						mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][1] = 0;
						mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][2] = 0;
					}
					break;
				case 2:
					if ((mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][0] < 1) || (mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][1] != 0))
					{
						mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][0] = 0;
						mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][1] = 0;
						mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][2] = 0;
					}
					break;
				case 3:
					if ((mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][0] < 1) || (mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][1] < 1))
					{
						mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][0] = 0;
						mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][1] = 0;
						mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][2] = 0;
					}
					if (mGAME.CheckDeleteItem(mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][0]))
					{
						mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][0] = 0;
						mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][1] = 0;
						mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][2] = 0;
					}
					break;
				default:
					mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][0] = 0;
					mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][1] = 0;
					mUSER[tUserIndex].mAvatarInfo[index01].aHotKey[index02][index03][2] = 0;
					break;
				}
			}
		}

		for (index02 = 0; index02 < MAX_SAVE_ITEM_SLOT_NUM; index02++)
		{
			if (mGAME.CheckDeleteItem(mUSER[tUserIndex].mAvatarInfo[index01].uSaveItem[index02][0]))
			{
				mUSER[tUserIndex].mAvatarInfo[index01].uSaveItem[index02][0] = 0;
				mUSER[tUserIndex].mAvatarInfo[index01].uSaveItem[index02][1] = 0;
				mUSER[tUserIndex].mAvatarInfo[index01].uSaveItem[index02][2] = 0;
				mUSER[tUserIndex].mAvatarInfo[index01].uSaveItem[index02][3] = 0;
			}
		}
		// @ __WEB_MALL__
		if (0 == index01)
			CopyMemory(mUSER[tUserIndex].uSaveItem, mUSER[tUserIndex].mAvatarInfo[0].uSaveItem, (MAX_SAVE_ITEM_SLOT_NUM * 4 * 4));
		// __WEB_MALL__ @
	}


	// @ __WEB_MALL__
	mDB.DB_PROCESS_11(&mUSER[tUserIndex].uID[0], mUSER[tUserIndex].uSaveItem);
	// __WEB_MALL__ @

	for (index01 = 0; index01 < MAX_USER_AVATAR_NUM; index01++)
	{
		if (strcmp(&mUSER[tUserIndex].mAvatarInfo[index01].aName[0], "") == 0)
		{
			continue;
		}
		switch (mUSER[tUserIndex].mAvatarInfo[index01].aTribe)
		{
		case 0:
			if (mZONEMAININFO.ReturnZoneTribeInfo1(mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[0]) != 0)
			{
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[0] = 1;
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[1] = 5;
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[2] = 0;
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[3] = 4;
			}
			break;
		case 1:
			if (mZONEMAININFO.ReturnZoneTribeInfo1(mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[0]) != 1)
			{
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[0] = 6;
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[1] = -190;
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[2] = 0;
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[3] = 1270;
			}
			break;
		case 2:
			if (mZONEMAININFO.ReturnZoneTribeInfo1(mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[0]) != 2)
			{
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[0] = 11;
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[1] = 447;
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[2] = 1;
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[3] = 440;
			}
			break;
		case 3:
			if (mZONEMAININFO.ReturnZoneTribeInfo1(mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[0]) != 3)
			{
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[0] = 140;
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[1] = 0;
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[2] = 0;
				mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[3] = -6;
			}
			break;
		}

		if (mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[4] < 1)
		{
			mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[4] = 1;
		}
		if (mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[5] < 0)
		{
			mUSER[tUserIndex].mAvatarInfo[index01].aLogoutInfo[5] = 0;
		}
	}

	for (index01 = 0; index01 < MAX_USER_AVATAR_NUM; index01++)
	{
		mTRANSFER.B_USER_AVATAR_INFO(&mUSER[tUserIndex].mAvatarInfo[index01]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}
	mTRANSFER.B_RCMD_WORLD_SEND();
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_CLIENT_OK_FOR_LOGIN_SEND
void W_CLIENT_OK_FOR_LOGIN_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();
}
//W_CREATE_MOUSE_PASSWORD_SEND
void W_CREATE_MOUSE_PASSWORD_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	if (mUSER[tUserIndex].mSecondLoginSort != 1)
	{
		//mUSER[tUserIndex].Quit();
		//return;
	}
	if (strcmp(mUSER[tUserIndex].uMousePassword, "") != 0)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	char tMousePassword[MAX_MOUSE_PASSWORD_LENGTH];
	CopyMemory(&tMousePassword[0], &tPacket[1], MAX_MOUSE_PASSWORD_LENGTH);

	int index01;

	if (strlen(tMousePassword) != 4)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	for (index01 = 0; index01 < 4; index01++)
	{
		if ((tMousePassword[index01] != '1') && (tMousePassword[index01] != '2') && (tMousePassword[index01] != '3') && (tMousePassword[index01] != '4') && (tMousePassword[index01] != '5') && (tMousePassword[index01] != '6') && (tMousePassword[index01] != '7') && (tMousePassword[index01] != '8') && (tMousePassword[index01] != '9') && (tMousePassword[index01] != '0'))
		{
			mUSER[tUserIndex].Quit();
			return;
		}
	}
	if (!mDB.DB_PROCESS_03(&mUSER[tUserIndex].uID[0], &tMousePassword[0]))
	{
		mTRANSFER.B_CREATE_MOUSE_PASSWORD_RECV(1, "0000");
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	strcpy(mUSER[tUserIndex].uMousePassword, tMousePassword);
	mUSER[tUserIndex].mSecondLoginSort = 0;
	mTRANSFER.B_CREATE_MOUSE_PASSWORD_RECV(0, &mUSER[tUserIndex].uMousePassword[0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_CHANGE_MOUSE_PASSWORD_SEND
void W_CHANGE_MOUSE_PASSWORD_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	if (mUSER[tUserIndex].mSecondLoginSort != 1)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	if (strcmp(mUSER[tUserIndex].uMousePassword, "") == 0)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	char tMousePassword[MAX_MOUSE_PASSWORD_LENGTH];
	char tChangeMousePassword[MAX_MOUSE_PASSWORD_LENGTH];
	CopyMemory(&tMousePassword[0], &tPacket[1], MAX_MOUSE_PASSWORD_LENGTH);
	CopyMemory(&tChangeMousePassword[0], &tPacket[(1 + MAX_MOUSE_PASSWORD_LENGTH)], MAX_MOUSE_PASSWORD_LENGTH);

	int index01;

	if (strlen(tMousePassword) != 4)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	for (index01 = 0; index01 < 4; index01++)
	{
		if ((tMousePassword[index01] != '1') && (tMousePassword[index01] != '2') && (tMousePassword[index01] != '3') && (tMousePassword[index01] != '4') && (tMousePassword[index01] != '5') && (tMousePassword[index01] != '6') && (tMousePassword[index01] != '7') && (tMousePassword[index01] != '8') && (tMousePassword[index01] != '9') && (tMousePassword[index01] != '0'))
		{
			mUSER[tUserIndex].Quit();
			return;
		}
	}
	if (strlen(tChangeMousePassword) != 4)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	for (index01 = 0; index01 < 4; index01++)
	{
		if ((tChangeMousePassword[index01] != '1') && (tChangeMousePassword[index01] != '2') && (tChangeMousePassword[index01] != '3') && (tChangeMousePassword[index01] != '4') && (tChangeMousePassword[index01] != '5') && (tChangeMousePassword[index01] != '6') && (tChangeMousePassword[index01] != '7') && (tChangeMousePassword[index01] != '8') && (tChangeMousePassword[index01] != '9') && (tChangeMousePassword[index01] != '0'))
		{
			mUSER[tUserIndex].Quit();
			return;
		}
	}
	if (strcmp(mUSER[tUserIndex].uMousePassword, tMousePassword) != 0)
	{
		//mGAMELOG.GL_502_MISMATCH_MOUSE_PASSWORD(&mUSER[tUserIndex].uID[0], &mUSER[tUserIndex].uMousePassword[0], &tMousePassword[0]);
		mTRANSFER.B_CHANGE_MOUSE_PASSWORD_RECV(1, "0000");
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUSER[tUserIndex].mSecondLoginTryNum++;
		if (mUSER[tUserIndex].mSecondLoginTryNum == 3)
		{
			mUSER[tUserIndex].Quit();
			mPLAYUSER_COM.U_BLOCK_USER_FOR_LOGIN_1_SEND(503, &mUSER[tUserIndex].uID[0]);
			return;
		}
		return;
	}
	if (!mDB.DB_PROCESS_03(&mUSER[tUserIndex].uID[0], &tChangeMousePassword[0]))
	{
		mTRANSFER.B_CHANGE_MOUSE_PASSWORD_RECV(2, "0000");
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	strcpy(mUSER[tUserIndex].uMousePassword, tChangeMousePassword);
	mUSER[tUserIndex].mSecondLoginSort = 0;
	mTRANSFER.B_CHANGE_MOUSE_PASSWORD_RECV(0, &mUSER[tUserIndex].uMousePassword[0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_LOGIN_MOUSE_PASSWORD_SEND
void W_LOGIN_MOUSE_PASSWORD_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	if (mUSER[tUserIndex].mSecondLoginSort != 1)
	{
		//mUSER[tUserIndex].Quit();
		//return;
	}
	if (strcmp(mUSER[tUserIndex].uMousePassword, "") == 0)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	char tMousePasswordInput[MAX_MOUSE_PASSWORD_LENGTH];
	CopyMemory(&tMousePasswordInput[0], &tPacket[1], MAX_MOUSE_PASSWORD_LENGTH);

	int index01;

	if (strlen(tMousePasswordInput) != 4)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	for (index01 = 0; index01 < 4; index01++)
	{
		if ((tMousePasswordInput[index01] != '1') && (tMousePasswordInput[index01] != '2') && (tMousePasswordInput[index01] != '3') && (tMousePasswordInput[index01] != '4') && (tMousePasswordInput[index01] != '5') && (tMousePasswordInput[index01] != '6') && (tMousePasswordInput[index01] != '7') && (tMousePasswordInput[index01] != '8') && (tMousePasswordInput[index01] != '9') && (tMousePasswordInput[index01] != '0'))
		{
			mUSER[tUserIndex].Quit();
			return;
		}
	}
	if (strcmp(mUSER[tUserIndex].uMousePassword, tMousePasswordInput) != 0)
	{
		//mGAMELOG.GL_502_MISMATCH_MOUSE_PASSWORD(&mUSER[tUserIndex].uID[0], &mUSER[tUserIndex].uMousePassword[0], &tMousePasswordInput[0]);
		mTRANSFER.B_LOGIN_MOUSE_PASSWORD_RECV(1);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUSER[tUserIndex].mSecondLoginTryNum++;
		if (mUSER[tUserIndex].mSecondLoginTryNum == 3)
		{
			mUSER[tUserIndex].Quit();
			//mGAMELOG.GL_504_MOUSE_PASS_THREE_OUT(mUSER[tUserIndex].uID);
			//mPLAYUSER_COM.U_BLOCK_USER_FOR_LOGIN_1_SEND( 504, &mUSER[tUserIndex].uID[0] );
			return;
		}
		return;
	}
	mUSER[tUserIndex].mSecondLoginSort = 0;
	mTRANSFER.B_LOGIN_MOUSE_PASSWORD_RECV(0);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_LOGIN_SECRET_CARD_SEND
void W_LOGIN_SECRET_CARD_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	if (mUSER[tUserIndex].mSecondLoginSort != 2)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	char tSecretCardInput01[3];
	char tSecretCardInput02[3];
	CopyMemory(&tSecretCardInput01[0], &tPacket[1], 3);
	CopyMemory(&tSecretCardInput02[0], &tPacket[4], 3);

	int index01;
	char tSecretCardInput03[5];
	char tSecretCardContent01[5];
	char tSecretCardContent02[5];
	char tSecretCardContent03[5];

	if (strlen(tSecretCardInput01) != 2)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	for (index01 = 0; index01 < 2; index01++)
	{
		if ((tSecretCardInput01[index01] != '1') && (tSecretCardInput01[index01] != '2') && (tSecretCardInput01[index01] != '3') && (tSecretCardInput01[index01] != '4') && (tSecretCardInput01[index01] != '5') && (tSecretCardInput01[index01] != '6') && (tSecretCardInput01[index01] != '7') && (tSecretCardInput01[index01] != '8') && (tSecretCardInput01[index01] != '9') && (tSecretCardInput01[index01] != '0'))
		{
			mUSER[tUserIndex].Quit();
			return;
		}
	}
	if (strlen(tSecretCardInput02) != 2)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	for (index01 = 0; index01 < 2; index01++)
	{
		if ((tSecretCardInput02[index01] != '1') && (tSecretCardInput02[index01] != '2') && (tSecretCardInput02[index01] != '3') && (tSecretCardInput02[index01] != '4') && (tSecretCardInput02[index01] != '5') && (tSecretCardInput02[index01] != '6') && (tSecretCardInput02[index01] != '7') && (tSecretCardInput02[index01] != '8') && (tSecretCardInput02[index01] != '9') && (tSecretCardInput02[index01] != '0'))
		{
			mUSER[tUserIndex].Quit();
			return;
		}
	}
	tSecretCardInput03[0] = tSecretCardInput01[0];
	tSecretCardInput03[1] = tSecretCardInput01[1];
	tSecretCardInput03[2] = tSecretCardInput02[0];
	tSecretCardInput03[3] = tSecretCardInput02[1];
	tSecretCardInput03[4] = '\0';
	if (!mDB.DB_PROCESS_04(mUSER[tUserIndex].uSecretCard, mUSER[tUserIndex].mSecretCardIndex01, &tSecretCardContent01[0]))
	{
		mTRANSFER.B_LOGIN_SECRET_CARD_RECV(2);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (!mDB.DB_PROCESS_04(mUSER[tUserIndex].uSecretCard, mUSER[tUserIndex].mSecretCardIndex02, &tSecretCardContent02[0]))
	{
		mTRANSFER.B_LOGIN_SECRET_CARD_RECV(2);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	tSecretCardContent03[0] = tSecretCardContent01[0];
	tSecretCardContent03[1] = tSecretCardContent01[1];
	tSecretCardContent03[2] = tSecretCardContent02[2];
	tSecretCardContent03[3] = tSecretCardContent02[3];
	tSecretCardContent03[4] = '\0';
	if (strcmp(tSecretCardContent03, tSecretCardInput03) != 0)
	{
		mTRANSFER.B_LOGIN_SECRET_CARD_RECV(1);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
#if 0	
		mUSER[tUserIndex].mSecondLoginTryNum++;
		if (mUSER[tUserIndex].mSecondLoginTryNum == 3)
		{
			mUSER[tUserIndex].Quit();
			mPLAYUSER_COM.U_BLOCK_USER_FOR_LOGIN_1_SEND(505, &mUSER[tUserIndex].uID[0]);
			return;
		}
#endif
		return;
	}
	mUSER[tUserIndex].mSecondLoginSort = 0;
	mTRANSFER.B_LOGIN_SECRET_CARD_RECV(0);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}

int ChangeIUValue(int tValue, int tIUValue)
{
	char tempValue01[4];
	int tResultIValue;

	CopyMemory(&tempValue01[0], &tValue, 4);
	tempValue01[1] += (char)tIUValue;
	CopyMemory(&tResultIValue, &tempValue01[0], 4);
	return tResultIValue;
}

//W_CREATE_AVATAR_SEND
void W_CREATE_AVATAR_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];



	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	if (mUSER[tUserIndex].mSecondLoginSort != 0)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tAvatarPost;
	AVATAR_INFO tAvatarInfo;
	CopyMemory(&tAvatarPost, &tPacket[1], 4);
	CopyMemory(&tAvatarInfo, &tPacket[5], sizeof(AVATAR_INFO));
	mGAME.SafeAvatarInfoData(&tAvatarInfo);

	if ((tAvatarPost < 0) || (tAvatarPost > 2) || (strcmp(mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName, "") != 0) || (strcmp(tAvatarInfo.aName, "") == 0) || (tAvatarInfo.aTribe < 0) || (tAvatarInfo.aTribe > 2) || (tAvatarInfo.aHeadType < 0) || (tAvatarInfo.aHeadType > 6) || (tAvatarInfo.aFaceType < 0) || (tAvatarInfo.aFaceType > 2))
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	if (!mGAME.CheckNameString(tAvatarInfo.aName))
	{
		mTRANSFER.B_CREATE_AVATAR_RECV(4, &tAvatarInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
		//mUSER[tUserIndex].Quit();
		return;
	}

	int index01;
	int index02;
	WORLD_INFO tWorldInfo;
	int tWeaponItemIndex;
	int tResult;
	if (!mDB.DB_PROCESS_12(&tWorldInfo))
	{
		mTRANSFER.B_CREATE_AVATAR_RECV(1, &tAvatarInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
#if 1 
	//__LogMgr()->Log_4("---> %d %d %d %d\n", tWorldInfo.mTribePoint[0], tWorldInfo.mTribePoint[1], tWorldInfo.mTribePoint[2], tWorldInfo.mTribePoint[3]);
	//__LogMgr()->Log("---> %d \n", tAvatarInfo.aTribe);
	switch (tAvatarInfo.aTribe)
	{
	case 0:
		if ((tWorldInfo.mTribePoint[0] >= 100) && (tWorldInfo.mTribePoint[0] > tWorldInfo.mTribePoint[3]))
		{
			if ((tWorldInfo.mTribePoint[0] > (tWorldInfo.mTribePoint[1] + tWorldInfo.mTribePoint[2])) && (tWorldInfo.mTribePoint[0] > (tWorldInfo.mTribePoint[1] + tWorldInfo.mTribePoint[3])) && (tWorldInfo.mTribePoint[0] > (tWorldInfo.mTribePoint[2] + tWorldInfo.mTribePoint[3])))
			{
				mTRANSFER.B_CREATE_AVATAR_RECV(3, &tAvatarInfo);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
		}
		break;
	case 1:

		//// yilan kapali
		//mTRANSFER.B_CREATE_AVATAR_RECV(3, &tAvatarInfo);
		//mUSER[tUserIndex].Send(TRUE, (char *)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//return;
		if ((tWorldInfo.mTribePoint[1] >= 100) && (tWorldInfo.mTribePoint[1] > tWorldInfo.mTribePoint[3]))
		{
			if ((tWorldInfo.mTribePoint[1] > (tWorldInfo.mTribePoint[0] + tWorldInfo.mTribePoint[2])) && (tWorldInfo.mTribePoint[1] > (tWorldInfo.mTribePoint[0] + tWorldInfo.mTribePoint[3])) && (tWorldInfo.mTribePoint[1] > (tWorldInfo.mTribePoint[2] + tWorldInfo.mTribePoint[3])))
			{
				mTRANSFER.B_CREATE_AVATAR_RECV(3, &tAvatarInfo);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
		}
		break;
	case 2:
		if ((tWorldInfo.mTribePoint[2] >= 100) && (tWorldInfo.mTribePoint[2] > tWorldInfo.mTribePoint[3]))
		{
			if ((tWorldInfo.mTribePoint[2] > (tWorldInfo.mTribePoint[0] + tWorldInfo.mTribePoint[1])) && (tWorldInfo.mTribePoint[2] > (tWorldInfo.mTribePoint[0] + tWorldInfo.mTribePoint[3])) && (tWorldInfo.mTribePoint[2] > (tWorldInfo.mTribePoint[1] + tWorldInfo.mTribePoint[3])))
			{
				mTRANSFER.B_CREATE_AVATAR_RECV(3, &tAvatarInfo);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
		}
		break;
	}
#endif


	if (!mDB.DB_PROCESS_15(tAvatarInfo.aTribe)) {
		mTRANSFER.B_CREATE_AVATAR_RECV(12, &tAvatarInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	char isim[13];
	int Kavim;
	int cinsiyet;
	int headtype;
	int facetype;

	// CREATE AVATAR
	Kavim = tAvatarInfo.aTribe;
	cinsiyet = tAvatarInfo.aGender;
	headtype = tAvatarInfo.aHeadType;
	facetype = tAvatarInfo.aFaceType;
	strncpy(isim, tAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH);
	tWeaponItemIndex = tAvatarInfo.aEquip[7][0];
	ZeroMemory(&tAvatarInfo, sizeof(tAvatarInfo));
	strncpy(tAvatarInfo.aName, isim, MAX_AVATAR_NAME_LENGTH);
	tAvatarInfo.aVisibleState = 1;
	tAvatarInfo.aSpecialState = 0;
	tAvatarInfo.aPlayTime1 = 0;
	tAvatarInfo.aPlayTime2 = 0;
	tAvatarInfo.aKillOtherTribe = 0;
	tAvatarInfo.aTribe = Kavim;
	tAvatarInfo.aPreviousTribe = Kavim;
	tAvatarInfo.aGender = cinsiyet;
	tAvatarInfo.aHeadType = headtype;
	tAvatarInfo.aFaceType = facetype;
	tAvatarInfo.aLevel1 = 1; // level
	tAvatarInfo.aLevel2 = 0; // god 
	tAvatarInfo.aGeneralExperience1 = 0;
	tAvatarInfo.aGeneralExperience2 = 0;
	tAvatarInfo.aVitality = 1;
	tAvatarInfo.aStrength = 1;
	tAvatarInfo.aKi = 1;
	tAvatarInfo.aWisdom = 1;
	tAvatarInfo.aEatLifePotion = 0;
	tAvatarInfo.aEatManaPotion = 0;
	tAvatarInfo.aStateBonusPoint = 0;
	tAvatarInfo.aSkillPoint = 0;
	
	for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM; index01++)
	{
		tAvatarInfo.aEquip[index01][0] = 0;
		tAvatarInfo.aEquip[index01][1] = 0;
		tAvatarInfo.aEquip[index01][2] = 0;
		tAvatarInfo.aEquip[index01][3] = 0;
	}

	switch (tAvatarInfo.aTribe)
	{
	case 0:
		if (tWeaponItemIndex == 5) {
			tWeaponItemIndex = 5;//sword
		}
		if (tWeaponItemIndex == 6) {
			tWeaponItemIndex = 6;//bldade
		}
		if (tWeaponItemIndex == 7) {
			tWeaponItemIndex = 7;//marble
		}

		tAvatarInfo.aEquip[0][0] = 0; //Amulet Ejder
		tAvatarInfo.aEquip[0][2] = 0; //Enchant %	
		tAvatarInfo.aEquip[0][3] = 0; //Parçalanmama %

		tAvatarInfo.aEquip[2][0] = 8; //Armor
		tAvatarInfo.aEquip[2][2] = 0; //Enchant %	
		tAvatarInfo.aEquip[2][3] = 0; //Parçalanmama %	

		tAvatarInfo.aEquip[3][0] = 9; //Gloves
		tAvatarInfo.aEquip[3][2] = 0; //Enchant %	
		tAvatarInfo.aEquip[3][3] = 0; //Parçalanmama %	

		tAvatarInfo.aEquip[4][0] = 0; //Ring
		tAvatarInfo.aEquip[4][2] = 0; //Enchant %	
		tAvatarInfo.aEquip[4][3] = 0; //Parçalanmama %	

		tAvatarInfo.aEquip[5][0] = 10; //Boot
		tAvatarInfo.aEquip[5][2] = 0; //Enchant %
		tAvatarInfo.aEquip[5][3] = 0; //Parçalanmama %

		tAvatarInfo.aEquip[7][0] = tWeaponItemIndex;
		tAvatarInfo.aEquip[7][2] = 0; //Enchant %	
		tAvatarInfo.aEquip[7][3] = 0; //Parçalanmama %	

		tAvatarInfo.aEquip[8][0] = 0; //Pet
		tAvatarInfo.aEquip[8][1] = 0; //Health
		tAvatarInfo.aEquip[8][2] = 0; //Exp %+
		break;
	case 1:
		if (tWeaponItemIndex == 11) {
			tWeaponItemIndex = 11;
		}
		if (tWeaponItemIndex == 12) {
			tWeaponItemIndex = 12;
		}
		if (tWeaponItemIndex == 13) {
			tWeaponItemIndex = 13;
		}

		tAvatarInfo.aEquip[0][0] = 0; //Amulet 
		tAvatarInfo.aEquip[0][2] = 0; //Enchant %	
		tAvatarInfo.aEquip[0][3] = 0; //Parçalanmama %

		tAvatarInfo.aEquip[2][0] = 14; //Armor
		tAvatarInfo.aEquip[2][2] = 0; //Enchant %	
		tAvatarInfo.aEquip[2][3] = 0; //Parçalanmama %	

		tAvatarInfo.aEquip[3][0] = 15; //Gloves
		tAvatarInfo.aEquip[3][2] = 0; //Enchant %	
		tAvatarInfo.aEquip[3][3] = 0; //Parçalanmama %	

		tAvatarInfo.aEquip[4][0] = 0; //Ring
		tAvatarInfo.aEquip[4][2] = 0; //Enchant %	
		tAvatarInfo.aEquip[4][3] = 0; //Parçalanmama %	

		tAvatarInfo.aEquip[5][0] = 16; //Boot
		tAvatarInfo.aEquip[5][2] = 0; //Enchant %
		tAvatarInfo.aEquip[5][3] = 0; //Parçalanmama %

		tAvatarInfo.aEquip[7][0] = tWeaponItemIndex;
		tAvatarInfo.aEquip[7][2] = 0; //Enchant %	
		tAvatarInfo.aEquip[7][3] = 0; //Parçalanmama %	

		tAvatarInfo.aEquip[8][0] = 0; //Pet
		tAvatarInfo.aEquip[8][1] = 0; //Health
		tAvatarInfo.aEquip[8][2] = 0; //Exp %+
		break;
	case 2:
		if (tWeaponItemIndex == 17) {
			tWeaponItemIndex = 17;//blade
		}
		if (tWeaponItemIndex == 18) {
			tWeaponItemIndex = 18;//spear
		}
		if (tWeaponItemIndex == 19) {
			tWeaponItemIndex = 19;
		}

		tAvatarInfo.aEquip[0][0] = 0; //Amulet PARS
		tAvatarInfo.aEquip[0][2] = 0; //Enchant %	
		tAvatarInfo.aEquip[0][3] = 0; //Parçalanmama %

		tAvatarInfo.aEquip[2][0] = 20; //Armor
		tAvatarInfo.aEquip[2][2] = 0; //Enchant %	
		tAvatarInfo.aEquip[2][3] = 0; //Parçalanmama %	

		tAvatarInfo.aEquip[3][0] = 21; //Gloves
		tAvatarInfo.aEquip[3][2] = 0; //Enchant %	
		tAvatarInfo.aEquip[3][3] = 0; //Parçalanmama %	

		tAvatarInfo.aEquip[4][0] = 0; //Ring
		tAvatarInfo.aEquip[4][2] = 0; //Enchant %	
		tAvatarInfo.aEquip[4][3] = 0; //Parçalanmama %	

		tAvatarInfo.aEquip[5][0] = 22; //Boot
		tAvatarInfo.aEquip[5][2] = 0; //Enchant %
		tAvatarInfo.aEquip[5][3] = 0; //Parçalanmama %

		tAvatarInfo.aEquip[7][0] = tWeaponItemIndex;
		tAvatarInfo.aEquip[7][2] = 0; //Enchant %	
		tAvatarInfo.aEquip[7][3] = 0; //Parçalanmama %	

		tAvatarInfo.aEquip[8][0] = 0; //Pet
		tAvatarInfo.aEquip[8][1] = 0; //Health
		tAvatarInfo.aEquip[8][2] = 0; //Exp %+
		break;
	}

	tAvatarInfo.aEquip[1][0] = 1407;
	tAvatarInfo.aEquip[1][1] = 0;
	tAvatarInfo.aEquip[1][2] = 0;
	tAvatarInfo.aEquip[1][3] = 0;
	tAvatarInfo.aExpandInventoryDate = mGAME.ReturnAddDate(0, 30);
	tAvatarInfo.aMoney = 0;
	for (index01 = 0; index01 < 2; index01++)
	{
		for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
		{
			tAvatarInfo.aInventory[index01][index02][0] = 0;
			tAvatarInfo.aInventory[index01][index02][1] = 0;
			tAvatarInfo.aInventory[index01][index02][2] = 0;
			tAvatarInfo.aInventory[index01][index02][3] = 0;
			tAvatarInfo.aInventory[index01][index02][4] = 0;
			tAvatarInfo.aInventory[index01][index02][5] = 0;
		}
	}
	tAvatarInfo.aInventory[0][0][0] = 1026;
	tAvatarInfo.aInventory[0][0][1] = 0;
	tAvatarInfo.aInventory[0][0][2] = 0;
	tAvatarInfo.aInventory[0][0][3] = 12;
	tAvatarInfo.aInventory[0][0][4] = 0;
	tAvatarInfo.aInventory[0][0][5] = 0;

	tAvatarInfo.aTradeMoney = 0;
	for (index01 = 0; index01 < MAX_TRADE_SLOT_NUM; index01++)
	{
		tAvatarInfo.aTrade[index01][0] = 0;
		tAvatarInfo.aTrade[index01][1] = 0;
		tAvatarInfo.aTrade[index01][2] = 0;
		tAvatarInfo.aTrade[index01][3] = 0;
	}
	tAvatarInfo.aExpandStoreDate = mGAME.ReturnAddDate(0, 30);
	tAvatarInfo.aStoreMoney = 0;
	
	for (index01 = 0; index01 < 2; index01++)
	{
		for (index02 = 0; index02 < MAX_STORE_ITEM_SLOT_NUM; index02++)
		{
			tAvatarInfo.aStoreItem[index01][index02][0] = 0;
			tAvatarInfo.aStoreItem[index01][index02][1] = 0;
			tAvatarInfo.aStoreItem[index01][index02][2] = 0;
			tAvatarInfo.aStoreItem[index01][index02][3] = 0;
		}
	}
	for (index01 = 0; index01 < MAX_SKILL_SLOT_NUM; index01++)
	{
		tAvatarInfo.aSkill[index01][0] = 0;
		tAvatarInfo.aSkill[index01][1] = 0;
	}
	for (index01 = 0; index01 < 3; index01++)
	{
		for (index02 = 0; index02 < MAX_HOT_KEY_NUM; index02++)
		{
			tAvatarInfo.aHotKey[index01][index02][0] = 0;
			tAvatarInfo.aHotKey[index01][index02][1] = 0;
			tAvatarInfo.aHotKey[index01][index02][2] = 0;
		}
	}
	switch (tAvatarInfo.aTribe)
	{
	case 0:
#pragma region Genel Buff
		tAvatarInfo.aSkill[0][0] = 1;
		tAvatarInfo.aSkill[0][1] = 20;
		tAvatarInfo.aSkill[1][0] = 0;
		tAvatarInfo.aSkill[1][1] = 0;
		tAvatarInfo.aSkill[2][0] = 0;
		tAvatarInfo.aSkill[2][1] = 0;
		tAvatarInfo.aSkill[3][0] = 0;
		tAvatarInfo.aSkill[3][1] = 0;
		tAvatarInfo.aSkill[4][0] = 0;
		tAvatarInfo.aSkill[4][1] = 0;
		tAvatarInfo.aSkill[5][0] = 0;
		tAvatarInfo.aSkill[5][1] = 0;
		tAvatarInfo.aSkill[6][0] = 0;
		tAvatarInfo.aSkill[6][1] = 0;
#pragma endregion
//#pragma region Silah Buff
//		tAvatarInfo.aSkill[10][0] = 15;
//		tAvatarInfo.aSkill[10][1] = 30;
//		tAvatarInfo.aSkill[11][0] = 11;
//		tAvatarInfo.aSkill[11][1] = 30;
//		tAvatarInfo.aSkill[12][0] = 19;
//		tAvatarInfo.aSkill[12][1] = 30;
//#pragma endregion
//#pragma region Hasar Skill
//		tAvatarInfo.aSkill[20][0] = 14;
//		tAvatarInfo.aSkill[20][1] = 30;
//		tAvatarInfo.aSkill[21][0] = 121;
//		tAvatarInfo.aSkill[21][1] = 45;
//		tAvatarInfo.aSkill[22][0] = 122;
//		tAvatarInfo.aSkill[22][1] = 45;
//		tAvatarInfo.aSkill[23][0] = 123;
//		tAvatarInfo.aSkill[23][1] = 45;
//		tAvatarInfo.aSkill[24][0] = 124;
//		tAvatarInfo.aSkill[24][1] = 45;
//		tAvatarInfo.aSkill[25][0] = 125;
//		tAvatarInfo.aSkill[25][1] = 45;
//		tAvatarInfo.aSkill[26][0] = 126;
//		tAvatarInfo.aSkill[26][1] = 45;
//#pragma endregion
		break;
	case 1:
#pragma region Genel Buff
		tAvatarInfo.aSkill[0][0] = 20;
		tAvatarInfo.aSkill[0][1] = 20;
		tAvatarInfo.aSkill[1][0] = 0;
		tAvatarInfo.aSkill[1][1] = 0;
		tAvatarInfo.aSkill[2][0] = 0;
		tAvatarInfo.aSkill[2][1] = 0;
		tAvatarInfo.aSkill[3][0] = 0;
		tAvatarInfo.aSkill[3][1] = 0;
		tAvatarInfo.aSkill[4][0] = 0;
		tAvatarInfo.aSkill[4][1] = 0;
		tAvatarInfo.aSkill[5][0] = 0;
		tAvatarInfo.aSkill[5][1] = 0;
		tAvatarInfo.aSkill[6][0] = 0;
		tAvatarInfo.aSkill[6][1] = 0;
#pragma endregion
//#pragma region Silah Buff
//		tAvatarInfo.aSkill[10][0] = 34;
//		tAvatarInfo.aSkill[10][1] = 30;
//		tAvatarInfo.aSkill[11][0] = 30;
//		tAvatarInfo.aSkill[11][1] = 30;
//		tAvatarInfo.aSkill[12][0] = 38;
//		tAvatarInfo.aSkill[12][1] = 30;
//#pragma endregion
//#pragma region Hasar Skill
//		tAvatarInfo.aSkill[20][0] = 29;
//		tAvatarInfo.aSkill[20][1] = 30;
//		tAvatarInfo.aSkill[21][0] = 127;
//		tAvatarInfo.aSkill[21][1] = 45;
//		tAvatarInfo.aSkill[22][0] = 128;
//		tAvatarInfo.aSkill[22][1] = 45;
//		tAvatarInfo.aSkill[23][0] = 129;
//		tAvatarInfo.aSkill[23][1] = 45;
//		tAvatarInfo.aSkill[24][0] = 130;
//		tAvatarInfo.aSkill[24][1] = 45;
//		tAvatarInfo.aSkill[25][0] = 131;
//		tAvatarInfo.aSkill[25][1] = 45;
//		tAvatarInfo.aSkill[26][0] = 132;
//		tAvatarInfo.aSkill[26][1] = 45;
//#pragma endregion
		break;
	case 2:
#pragma region Genel Buff
		tAvatarInfo.aSkill[0][0] = 39;
		tAvatarInfo.aSkill[0][1] = 20;
		tAvatarInfo.aSkill[1][0] = 0;
		tAvatarInfo.aSkill[1][1] = 0;
		tAvatarInfo.aSkill[2][0] = 0;
		tAvatarInfo.aSkill[2][1] = 0;
		tAvatarInfo.aSkill[3][0] = 0;
		tAvatarInfo.aSkill[3][1] = 0;
		tAvatarInfo.aSkill[4][0] = 0;
		tAvatarInfo.aSkill[4][1] = 0;
		tAvatarInfo.aSkill[5][0] = 0;
		tAvatarInfo.aSkill[5][1] = 0;
		tAvatarInfo.aSkill[6][0] = 0;
		tAvatarInfo.aSkill[6][1] = 0;
#pragma endregion
//#pragma region Silah Buff
//		tAvatarInfo.aSkill[10][0] = 53;
//		tAvatarInfo.aSkill[10][1] = 30;
//		tAvatarInfo.aSkill[11][0] = 49;
//		tAvatarInfo.aSkill[11][1] = 30;
//		tAvatarInfo.aSkill[12][0] = 57;
//		tAvatarInfo.aSkill[12][1] = 30;
//#pragma endregion
//#pragma region Hasar Skill
//		tAvatarInfo.aSkill[20][0] = 52;
//		tAvatarInfo.aSkill[20][1] = 30;
//		tAvatarInfo.aSkill[21][0] = 133;
//		tAvatarInfo.aSkill[21][1] = 45;
//		tAvatarInfo.aSkill[22][0] = 134;
//		tAvatarInfo.aSkill[22][1] = 45;
//		tAvatarInfo.aSkill[23][0] = 135;
//		tAvatarInfo.aSkill[23][1] = 45;
//		tAvatarInfo.aSkill[24][0] = 136;
//		tAvatarInfo.aSkill[24][1] = 45;
//		tAvatarInfo.aSkill[25][0] = 137;
//		tAvatarInfo.aSkill[25][1] = 45;
//		tAvatarInfo.aSkill[26][0] = 138;
//		tAvatarInfo.aSkill[26][1] = 45;
//#pragma endregion
		break;
	}
	tAvatarInfo.aHotKey[0][0][0] = 4;
	tAvatarInfo.aHotKey[0][0][1] = 99;
	tAvatarInfo.aHotKey[0][0][2] = 3;
	tAvatarInfo.aHotKey[0][1][0] = 4;
	tAvatarInfo.aHotKey[0][1][1] = 99;
	tAvatarInfo.aHotKey[0][1][2] = 3;
	tAvatarInfo.aHotKey[0][2][0] = 4;
	tAvatarInfo.aHotKey[0][2][1] = 99;
	tAvatarInfo.aHotKey[0][2][2] = 3;
	tAvatarInfo.aHotKey[0][3][0] = 4;
	tAvatarInfo.aHotKey[0][3][1] = 99;
	tAvatarInfo.aHotKey[0][3][2] = 3;

	tAvatarInfo.aAnimalIndex = -1;

	tAvatarInfo.aQuestInfo[0] = 0;
	tAvatarInfo.aQuestInfo[1] = 0;
	tAvatarInfo.aQuestInfo[2] = 0;
	tAvatarInfo.aQuestInfo[3] = 0;
	tAvatarInfo.aQuestInfo[4] = 0;
	for (index01 = 0; index01 < MAX_FRIEND_NUM; index01++)
	{
		strcpy(tAvatarInfo.aFriend[index01], "");
	}
	strcpy(tAvatarInfo.aTeacher, "");
	strcpy(tAvatarInfo.aStudent, "");
	tAvatarInfo.aTeacherPoint = 0;
	strcpy(tAvatarInfo.aGuildName, "");
	tAvatarInfo.aGuildRole = 0;
	strcpy(tAvatarInfo.aCallName, "");
	tAvatarInfo.aGuildMarkNum = 0;
	tAvatarInfo.aGuildMarkEffect = 1;
	switch (tAvatarInfo.aTribe)
	{
	case 0:
		tAvatarInfo.aLogoutInfo[0] = 1;
		tAvatarInfo.aLogoutInfo[1] = 5;
		tAvatarInfo.aLogoutInfo[2] = 0;
		tAvatarInfo.aLogoutInfo[3] = 4;
		tAvatarInfo.aLogoutInfo[4] = 30;
		tAvatarInfo.aLogoutInfo[5] = 21;
		break;
	case 1:
		tAvatarInfo.aLogoutInfo[0] = 6;
		tAvatarInfo.aLogoutInfo[1] = -190;
		tAvatarInfo.aLogoutInfo[2] = 0;
		tAvatarInfo.aLogoutInfo[3] = 1270;
		tAvatarInfo.aLogoutInfo[4] = 30;
		tAvatarInfo.aLogoutInfo[5] = 21;
		break;
	case 2:
		tAvatarInfo.aLogoutInfo[0] = 11;
		tAvatarInfo.aLogoutInfo[1] = 447;
		tAvatarInfo.aLogoutInfo[2] = 1;
		tAvatarInfo.aLogoutInfo[3] = 440;
		tAvatarInfo.aLogoutInfo[4] = 30;
		tAvatarInfo.aLogoutInfo[5] = 21;
		break;
	}

	// auto hunt scroll - Character Creation
	tAvatarInfo.AutoBuffScroll = 0;
	tAvatarInfo.aSearch = 0;
	tAvatarInfo.Hunt7d = mGAME.ReturnAddDate(0, 30);
	tAvatarInfo.SolemGrounds = 180;
	tAvatarInfo.Beginner = 0;
	tAvatarInfo.BeginnerLevel = 0;


	tAvatarInfo.uSaveMoney = mUSER[tUserIndex].uSaveMoney;
	tAvatarInfo.SeyisBar = mUSER[tUserIndex].uSeyisBar;
	for (index01 = 0; index01 < MAX_SAVE_ITEM_SLOT_NUM; index01++)
	{
		tAvatarInfo.uSaveItem[index01][0] = mUSER[tUserIndex].uSaveItem[index01][0];
		tAvatarInfo.uSaveItem[index01][1] = mUSER[tUserIndex].uSaveItem[index01][1];
		tAvatarInfo.uSaveItem[index01][2] = mUSER[tUserIndex].uSaveItem[index01][2];
		tAvatarInfo.uSaveItem[index01][3] = mUSER[tUserIndex].uSaveItem[index01][3];
		tAvatarInfo.SaveSocket[index01][0] = mUSER[tUserIndex].uSaveSocket[index01][0];
		tAvatarInfo.SaveSocket[index01][1] = mUSER[tUserIndex].uSaveSocket[index01][1];
		tAvatarInfo.SaveSocket[index01][2] = mUSER[tUserIndex].uSaveSocket[index01][2];
	}

	mDB.DB_PROCESS_05(tUserIndex, tAvatarPost, &tAvatarInfo, &tResult);

	if (tResult != 0)
	{
		__LogMgr()->Log("![%s] : tResult[%d]\n", __FUNCTION__, tResult);
		mTRANSFER.B_CREATE_AVATAR_RECV(tResult, &tAvatarInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	int tResult1 = mDB.DB_PROCESS_21(tAvatarInfo.aName);
	if (tResult1 != 0)
	{
		__LogMgr()->Log("![%s] : tResult[%d]\n", __FUNCTION__, tResult1);
		mTRANSFER.B_CREATE_AVATAR_RECV(tResult1, &tAvatarInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	CopyMemory(&mUSER[tUserIndex].mAvatarInfo[tAvatarPost], &tAvatarInfo, sizeof(AVATAR_INFO));


	mTRANSFER.B_CREATE_AVATAR_RECV(0, &tAvatarInfo);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_DELETE_AVATAR_SEND
void W_DELETE_AVATAR_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	if (mUSER[tUserIndex].mSecondLoginSort != 0)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tAvatarPost;
	CopyMemory(&tAvatarPost, &tPacket[1], 4);

	if ((tAvatarPost < 0) || (tAvatarPost > 2) || (strcmp(mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName, "") == 0))
	{
		mUSER[tUserIndex].Quit();
		return;
	}

	TRIBE_INFO tTribeInfo;


	if (!mDB.DB_PROCESS_13(&tTribeInfo))
	{
		__LogMgr()->Log("![WARNING - (1)] Database failed to delete character.\n");
		mTRANSFER.B_DELETE_AVATAR_RECV(1);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mGAME.ReturnTribeRole(&tTribeInfo, &mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName[0], mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aTribe) != 0)
	{
		__LogMgr()->Log("![WARNING - (2) Because the character can not delete the leader of group.\n");
		mTRANSFER.B_DELETE_AVATAR_RECV(2);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (strcmp(mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aGuildName, "") != 0)
	{
		__LogMgr()->Log("![WARNING - (3) You can not delete the character joined the guild.\n");
		mTRANSFER.B_DELETE_AVATAR_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aLevel1 >= 999)
	{
		mTRANSFER.B_DELETE_AVATAR_RECV(4);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	if (!mDB.DB_PROCESS_06(tUserIndex, tAvatarPost))
	{
		__LogMgr()->Log("![WARNING - (1) Database failed to delete character.\n");
		mTRANSFER.B_DELETE_AVATAR_RECV(1);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	strcpy(mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName, "");
	mTRANSFER.B_DELETE_AVATAR_RECV(0);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}

//W_CHANGE_AVATAR_NAME_SEND
// 2009.12.16 : ±èŒºŒö
// ¹«žíº¯È¯Œ­ Ã³ž® ŒöÁ€
void W_CHANGE_AVATAR_NAME_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	if (mUSER[tUserIndex].mSecondLoginSort != 0)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tAvatarPost;
	char tChangeAvatarName[MAX_AVATAR_NAME_LENGTH];
	int tPage;
	int tIndex;
	CopyMemory(&tAvatarPost, &tPacket[1], 4);
	CopyMemory(&tChangeAvatarName[0], &tPacket[5], MAX_AVATAR_NAME_LENGTH);
	tChangeAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
	CopyMemory(&tPage, &tPacket[(5 + MAX_AVATAR_NAME_LENGTH)], 4);
	CopyMemory(&tIndex, &tPacket[(9 + MAX_AVATAR_NAME_LENGTH)], 4);

	TRIBE_INFO tTribeInfo;
	int tResult;
	bool isChangeNameIntegration = false;

	// 2009.12.18  : ±èŒºŒö
	// ÅëÇÕ¿¡ ÀÇÇÑ ¹«žíº¯È¯ÀÇ °æ¿ì¿¡ ŸÆ·¡žŠ ÃŒÅ© ÇÏÁö ŸÊŽÂŽÙ.
	//if(!(tPage == -1 && tIndex == -1 && !mGAME.CheckNameString( mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName )))
	if (!(tPage == -1 && tIndex == -1))
	{
		if ((tAvatarPost < 0) || (tAvatarPost > 2)
			|| (strcmp(mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName, "") == 0)
			|| (strcmp(tChangeAvatarName, "") == 0)
			|| (strcmp(tChangeAvatarName, mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName) == 0)
			|| (tPage < 0)
			|| (tPage > 1)
			|| (tIndex < 0)
			|| (tIndex > (MAX_INVENTORY_SLOT_NUM - 1)))
		{
			mUSER[tUserIndex].Quit();
			return;
		}

		//ŸÆÀÌÅÛÀÌ ŸøŽÂ °æ¿ì
		if (mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aInventory[tPage][tIndex][0] != 1133)
		{
			mTRANSFER.B_CHANGE_AVATAR_NAME_RECV(8);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mUSER[tUserIndex].Quit();
			return;
		}
	}
	else // Œ­¹ö ÅëÇÕ¿¡ ÀÇÇÑ ¹«ží º¯È¯ÀÇ °æ¿ì == ŸÆ¹ÙÅž ¹«ží¿¡ Æ¯Œö¹®ÀÚ°¡ µéŸî °¡ ÀÖŽÂ °æ¿ì == tPage, tIndex °¡ -1ÀÎ °æ¿ì.
	{
		if (mGAME.CheckNameString(mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName) == FALSE)
		{
			isChangeNameIntegration = true;
		}
		else // Œ­¹ö ÅëÇÕ¿¡ ÀÇÇÑ ¹«ží º¯È¯µµ ŸÆŽÑµ¥ -1, -1À» ºž³»ŽÙŽÏ...
		{
			mUSER[tUserIndex].Quit();
			return;
		}
	}

#ifndef __TK__
	//ÀßžøµÈ ¹®ÀÚ
	if (!mGAME.CheckNameString(tChangeAvatarName))
	{
		mTRANSFER.B_CHANGE_AVATAR_NAME_RECV(1);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	}
#endif



	// ±æµå¿¡ °¡ÀÔµÇŸî ÀÖŽÂ °æ¿ì
	if (strcmp(mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aGuildName, "") != 0)
	{
		mTRANSFER.B_CHANGE_AVATAR_NAME_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	}

	// œÃœºÅÛ Ã³ž®Áß ¹®ÁŠ (DB) - ŒŒ·ÂÀå ÈÄºžÀÎ°æ¿ìµµ Æ÷ÇÔ
	if (!mDB.DB_PROCESS_13(&tTribeInfo))
	{
		mTRANSFER.B_CHANGE_AVATAR_NAME_RECV(9);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	//ŒŒ·ÂÀå È€Àº ºÎŒŒ·ÂÀåÀÎ °æ¿ì
	if (mGAME.ReturnTribeRole(&tTribeInfo, &mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName[0], mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aTribe) != 0)
	{
		mTRANSFER.B_CHANGE_AVATAR_NAME_RECV(4);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	//ºØ¿ì°¡ ÀÖŽÂ °æ¿ì
	for (int i = 0; i < MAX_FRIEND_NUM; ++i)
	{
		if (strcmp(mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aFriend[i], "") != 0)
		{
			mTRANSFER.B_CHANGE_AVATAR_NAME_RECV(5);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
	}

	//œºœÂÀÌ ÀÖŽÂ °æ¿ì
	if (strcmp(mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aTeacher, "") != 0)
	{
		mTRANSFER.B_CHANGE_AVATAR_NAME_RECV(6);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	//ÁŠÀÚ°¡ ÀÖŽÂ °æ¿ì
	if (strcmp(mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aStudent, "") != 0)
	{
		mTRANSFER.B_CHANGE_AVATAR_NAME_RECV(7);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}



	//ÀÌž§º¯°æ - ÀÌ°Ô œÇÆÐ ÇÑŽÙŽÂ °ÍÀº µ¿ÀÏ ¹«žíÀÌ ÀÖŽÂ °æ¿ì¿Í ±×¿Ü¿¡ Äõž®°¡ ÀßžøµÇŸúÀ» °æ¿ìÀÌŽÙ.
	// µû¶óŒ­ ÀÌ °æ¿ì œÇÆÐœÃ¿¡ µ¿ÀÏ ¹«žíÀÌ ÀÖŽÙ°í ÆÇŽÜÇÑŽÙ.
	mDB.DB_PROCESS_07(&mUSER[tUserIndex].uID[0], tAvatarPost, &mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName[0], &tChangeAvatarName[0], &tResult);
	if (tResult != 0)
	{
		printf("tResult === %d\n", tResult);
		mTRANSFER.B_CHANGE_AVATAR_NAME_RECV(2);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	//mGAMELOG.GL_501_CHANGE_AVATAR_NAME(&mUSER[tUserIndex].uID[0], &mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName[0], &tChangeAvatarName[0]);
	strcpy(mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName, tChangeAvatarName);
	if (isChangeNameIntegration == false)
	{
		mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aInventory[tPage][tIndex][5] = 0;
		mDB.DB_PROCESS_08(&mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName[0], mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aInventory);
	}
	mTRANSFER.B_CHANGE_AVATAR_NAME_RECV(0);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_DEMAND_GIFT_SEND
void W_DEMAND_GIFT_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	if (mUSER[tUserIndex].mSecondLoginSort != 0)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	char tCardNumber[MAX_USER_CARD_NUMBER_LENGTH];
	CopyMemory(&tCardNumber[0], &tPacket[1], MAX_USER_CARD_NUMBER_LENGTH);
	tCardNumber[(MAX_USER_CARD_NUMBER_LENGTH - 1)] = '\0';

	char tID[MAX_USER_ID_LENGTH];

	// 	if( !mDB.DB_PROCESS_09( &tCardNumber[0], &tID[0], &mUSER[tUserIndex].mGiftInfo[0] ) )
	// 	{
	// 		mUSER[tUserIndex].mCheckDemandGiftIfo = FALSE;
	// 		mTRANSFER.B_DEMAND_GIFT_RECV( 1, &mUSER[tUserIndex].mGiftInfo[0] );
	// 		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	// 		return;
	// 	}
	// 	if( strcmp( mUSER[tUserIndex].uID, tID ) != 0 )
	// 	{
	// 		mUSER[tUserIndex].mCheckDemandGiftIfo = FALSE;
	// 		mTRANSFER.B_DEMAND_GIFT_RECV( 2, &mUSER[tUserIndex].mGiftInfo[0] );
	// 		mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
	// 		return;
	// 	}

	//mGiftBankComm.U_CHECK_GIFTISSUESERIAL(tUserIndex, tCardNumber);

	/*mUSER[tUserIndex].mCheckDemandGiftIfo = TRUE;
	strcpy( mUSER[tUserIndex].mCardNumber, tCardNumber );
	mTRANSFER.B_DEMAND_GIFT_RECV( 0, &mUSER[tUserIndex].mGiftInfo[0] );
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );*/
}
//W_WANT_GIFT_SEND
void W_WANT_GIFT_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	if (mUSER[tUserIndex].mSecondLoginSort != 0)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	if (!mUSER[tUserIndex].mCheckDemandGiftIfo)
	{
		mTRANSFER.B_WANT_GIFT_RECV(1);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tGiftInfoindex;
	CopyMemory(&tGiftInfoindex, &tPacket[1], 4);
	if ((tGiftInfoindex != 0) && (tGiftInfoindex != 2) && (tGiftInfoindex != 4) && (tGiftInfoindex != 6) && (tGiftInfoindex != 8))
	{
		mUSER[tUserIndex].Quit();
		return;
	}

	int index01;
	int index02;

	if (mUSER[tUserIndex].mGiftInfo[(tGiftInfoindex + 1)] < 1)
	{
		mTRANSFER.B_WANT_GIFT_RECV(1);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mUSER[tUserIndex].mGiftInfo[tGiftInfoindex] < 1) || (mUSER[tUserIndex].mGiftInfo[tGiftInfoindex] > MAX_GIFT_SORT_NUM))
	{
		mTRANSFER.B_WANT_GIFT_RECV(2);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	index02 = 0;
	for (index01 = 0; index01 < MAX_SAVE_ITEM_SLOT_NUM; index01++)
	{
		if (mUSER[tUserIndex].uSaveItem[index01][0] < 1)
		{
			index02++;
		}
	}
	if (index02 < mGAME.mGiftInfo[(mUSER[tUserIndex].mGiftInfo[tGiftInfoindex] - 1)].mTotalGiftNum)
	{
		mTRANSFER.B_WANT_GIFT_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	/*if (mGiftBankComm.U_UPDATE_GIFTISSUEINFO(tUserIndex, mUSER[tUserIndex].mCardNumber,
		mUSER[tUserIndex].uID) == false)
		return;
		*/
	for (index01 = 0; index01 < mGAME.mGiftInfo[(mUSER[tUserIndex].mGiftInfo[tGiftInfoindex] - 1)].mTotalGiftNum; index01++)
	{
		for (index02 = 0; index02 < MAX_SAVE_ITEM_SLOT_NUM; index02++)
		{
			if (mUSER[tUserIndex].uSaveItem[index02][0] > 0)
			{
				continue;
			}
#if 0
			__LogMgr()->Log("![%s] : %d %d\n", __FUNCTION__
				, mGAME.mGiftInfo[(mUSER[tUserIndex].mGiftInfo[tGiftInfoindex] - 1)].mGiftData[index01][0]
				, mGAME.mGiftInfo[(mUSER[tUserIndex].mGiftInfo[tGiftInfoindex] - 1)].mGiftData[index01][1]);
#endif
			mUSER[tUserIndex].uSaveItem[index02][0] = mGAME.mGiftInfo[(mUSER[tUserIndex].mGiftInfo[tGiftInfoindex] - 1)].mGiftData[index01][0];
			mUSER[tUserIndex].uSaveItem[index02][1] = mGAME.mGiftInfo[(mUSER[tUserIndex].mGiftInfo[tGiftInfoindex] - 1)].mGiftData[index01][1];
			mUSER[tUserIndex].uSaveItem[index02][2] = 0;
			mUSER[tUserIndex].uSaveItem[index02][3] = 0;
			break;
		}
	}
	CopyMemory(&mUSER[tUserIndex].mAvatarInfo[0].uSaveItem[0][0], &mUSER[tUserIndex].uSaveItem[0][0], (MAX_SAVE_ITEM_SLOT_NUM * 4 * 4));
	CopyMemory(&mUSER[tUserIndex].mAvatarInfo[1].uSaveItem[0][0], &mUSER[tUserIndex].uSaveItem[0][0], (MAX_SAVE_ITEM_SLOT_NUM * 4 * 4));
	CopyMemory(&mUSER[tUserIndex].mAvatarInfo[2].uSaveItem[0][0], &mUSER[tUserIndex].uSaveItem[0][0], (MAX_SAVE_ITEM_SLOT_NUM * 4 * 4));
	mUSER[tUserIndex].mGiftInfo[(tGiftInfoindex + 1)]--;
	mDB.DB_PROCESS_10(&mUSER[tUserIndex].mCardNumber[0], &mUSER[tUserIndex].mGiftInfo[0]);
	mDB.DB_PROCESS_11(&mUSER[tUserIndex].uID[0], mUSER[tUserIndex].uSaveItem);
	mTRANSFER.B_WANT_GIFT_RECV(0);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	//mGAMELOG.GL_503_GIFT(&mUSER[tUserIndex].uID[0], mUSER[tUserIndex].mGiftInfo[tGiftInfoindex]);
}
//W_DEMAND_ZONE_SERVER_INFO_1
void W_DEMAND_ZONE_SERVER_INFO_1(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	if (mUSER[tUserIndex].mSecondLoginSort != 0)
	{
		printf("!MOTP are not certified by the state can not ask the server information.\n");
		mUSER[tUserIndex].Quit();
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		printf("!Go to the status of the client not be able to request information on the server.\n");
		mUSER[tUserIndex].Quit();
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tAvatarPost;
	CopyMemory(&tAvatarPost, &tPacket[1], 4);

	if ((tAvatarPost < 0) || (tAvatarPost > 2) || (strcmp(mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aName, "") == 0))
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	mCENTER_COM.U_GET_ZONE_SERVER_INFO_1(mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aLogoutInfo[0]);
	if (mCENTER_COM.mRecv_Result != 0)
	{
		mTRANSFER.B_DEMAND_ZONE_SERVER_INFO_1_RESULT(1, &mCENTER_COM.mRecv_IP[0], mCENTER_COM.mRecv_Port, mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aLogoutInfo[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		printf("!Did not receive the information about zone(%d) server address [%s:%d].\n",
			mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aLogoutInfo[0],
			mCENTER_COM.mRecv_IP, mCENTER_COM.mRecv_Port);
		return;
	}
	mPLAYUSER_COM.U_REGISTER_USER_FOR_LOGIN_3_SEND(mUSER[tUserIndex].mPlayUserIndex, &mUSER[tUserIndex].uID[0], &mUSER[tUserIndex].mAvatarInfo[tAvatarPost]);
	if (mPLAYUSER_COM.mRecv_Result != 0)
	{
		printf("!Failed to register a character on the playuser server(%d).\n", mPLAYUSER_COM.mRecv_Result);
		mUSER[tUserIndex].Quit();
		return;
	}
	mUSER[tUserIndex].mRegisterTime = GetTickCount();
	mUSER[tUserIndex].mMoveZoneResult = 1;
	printf("Connected\n");
	mTRANSFER.B_DEMAND_ZONE_SERVER_INFO_1_RESULT(0, &mCENTER_COM.mRecv_IP[0], mCENTER_COM.mRecv_Port, mUSER[tUserIndex].mAvatarInfo[tAvatarPost].aLogoutInfo[0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_FAIL_MOVE_ZONE_1_SEND
void W_FAIL_MOVE_ZONE_1_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	if (mUSER[tUserIndex].mSecondLoginSort != 0)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 0)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();
	mUSER[tUserIndex].mMoveZoneResult = 0;
	mPLAYUSER_COM.U_REGISTER_USER_FOR_LOGIN_2_SEND(mUSER[tUserIndex].mPlayUserIndex, &mUSER[tUserIndex].uID[0]);
	if (mPLAYUSER_COM.mRecv_Result != 0)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	mUSER[tUserIndex].mRegisterTime = GetTickCount();
}
//W_RCMD_WORLD_SEND
void W_RCMD_WORLD_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (mUSER[tUserIndex].mCheckValidState) {
		mUSER[tUserIndex].Quit();
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	mTRANSFER.B_RCMD_WORLD_SEND();
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//-------------------------------------------------------------------------------------------------
void W_RECIVE_GIFT_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	if (mUSER[tUserIndex].mSecondLoginSort != 0)
	{
		__LogMgr()->Log("!MOTP are not certified by the state can not ask the server information.\n");
		mUSER[tUserIndex].Quit();
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();
	int unk[10][2];
	ZeroMemory(unk, sizeof(unk));
	mTRANSFER.B_RECIVE_GIFT_ITEM_SEND(0, unk);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
void W_EVENT_ITEM_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit();
		return;
	}
	if (mUSER[tUserIndex].mSecondLoginSort != 0)
	{
		__LogMgr()->Log("!MOTP are not certified by the state can not ask the server information.\n");
		mUSER[tUserIndex].Quit();
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();
	int unk2[5][10][4];

	unk2[0][0][0] = 2;//İTEM ıd
	unk2[0][0][1] = 1;//item fiyatı
	unk2[0][0][2] = 3;
	unk2[0][0][3] = 4;

	ZeroMemory(unk2, sizeof(unk2));

	mTRANSFER.B_ITEM_EVENT_SEND(0, 0, 0, unk2);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}


