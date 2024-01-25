//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "Shengming.h"
//-------------------------------------------------------------------------------------------------
#define M_PI 3.14159265358979323846

//-------------------------------------------------------------------------------------------------
//WORKER_FUNCTION
//-------------------------------------------------------------------------------------------------
//INSTANCE

WORKER_FUNCTION W_FUNCTION[256];
//W_TEMP_REGISTER_SEND
void W_TEMP_REGISTER_SEND(int tUserIndex)
{
	__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (mUSER[tUserIndex].mCheckTempRegister)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	char tID[MAX_USER_ID_LENGTH];
	int tribe;
	int ClientKontrol;
	CopyMemory(&tID[0], &tPacket[1], MAX_USER_ID_LENGTH);
	tID[(MAX_USER_ID_LENGTH - 1)] = '\0';
	CopyMemory(&tribe, &tPacket[(1 + MAX_USER_ID_LENGTH)], 4);
	CopyMemory(&ClientKontrol, &tPacket[(5 + MAX_USER_ID_LENGTH)], 4);
	int index01;
	int tTribeNum[4];

	mUSER[tUserIndex].ClientKontrol = ClientKontrol;

	switch (mSERVER_INFO.mServerNumber)
	{
	case  49:
	case  51:
	case  53:
	case 146:
	case 147:
	case 148:
	case 149:
	case 150:
	case 151:
	case 152:
	case 153:
#ifdef __GOD__
	case 267:
#endif
		if ((tribe < 0) || (tribe > 2))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tTribeNum[0] = 0;
		tTribeNum[1] = 0;
		tTribeNum[2] = 0;
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mUSER[index01].mCheckConnectState)
			{
				continue;
			}
			if (!mUSER[index01].mCheckTempRegister)
			{
				continue;
			}
			tTribeNum[mUSER[index01].mTempRegisterTribe]++;
		}
		if (tTribeNum[tribe] >= (mSERVER.mMAX_USER_NUM / 3))
		{
			mTRANSFER.B_TEMP_REGISTER_RECV(1);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		break;
	case 154:
	case 155:
	case 156:
	case 157:
	case 158:
	case 159:
	case 160:
	case 161:
	case 162:
	case 163:
	case 164:
#ifdef __GOD__
	case 120:
	case 121:
	case 122:
	case 268:
	case 269:
#endif
		if ((tribe < 0) || (tribe > 3))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tTribeNum[0] = 0;
		tTribeNum[1] = 0;
		tTribeNum[2] = 0;
		tTribeNum[3] = 0;
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mUSER[index01].mCheckConnectState)
			{
				continue;
			}
			if (!mUSER[index01].mCheckTempRegister)
			{
				continue;
			}
			tTribeNum[mUSER[index01].mTempRegisterTribe]++;
		}
		if (tTribeNum[tribe] >= (mSERVER.mMAX_USER_NUM / 4))
		{
			mTRANSFER.B_TEMP_REGISTER_RECV(1);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		break;
#ifdef __GOD__
	case 194:
		if ((tribe < 0) || (tribe > 3))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tTribeNum[0] = 0;
		tTribeNum[1] = 0;
		tTribeNum[2] = 0;
		tTribeNum[3] = 0;
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mUSER[index01].mCheckConnectState)
			{
				continue;
			}
			if (!mUSER[index01].mCheckTempRegister)
			{
				continue;
			}
			tTribeNum[mUSER[index01].mTempRegisterTribe]++;
		}
		if (tTribeNum[tribe] >= 25)
		{
			mTRANSFER.B_TEMP_REGISTER_RECV(1);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		break;
#endif
	}
	mPLAYUSER_COM.U_REGISTER_USER_FOR_ZONE_0_SEND(&tID[0]);
	if (mPLAYUSER_COM.mRecv_Result != 0)
	{
		//	__LogMgr()->Log("![%s] : U_REGISTER_USER_FOR_ZONE_0_SEND failed(%d)\n"
		//			, __FUNCTION__, mPLAYUSER_COM.mRecv_Result);
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mTRANSFER.B_TEMP_REGISTER_RECV(0);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	mUSER[tUserIndex].mCheckTempRegister = TRUE;
	mUSER[tUserIndex].mTempRegisterTribe = tribe;
	mUSER[tUserIndex].mRegisterTime = GetTickCount();
	mUSER[tUserIndex].mPlayUserIndex = mPLAYUSER_COM.mRecv_PlayUserIndex;
	strncpy(mUSER[tUserIndex].uID, tID, MAX_USER_ID_LENGTH);
	mUSER[tUserIndex].mHeartCheckTime = ::time(NULL);
}
//W_REGISTER_AVATAR_SEND
void W_REGISTER_AVATAR_SEND(int tUserIndex)
{
	__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if ((!mUSER[tUserIndex].mCheckTempRegister) || (mUSER[tUserIndex].mCheckValidState))
	{
		__LogMgr()->Log("![RUN]  %s. %d\n", __FUNCTION__,__LINE__);
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	char tID[MAX_USER_ID_LENGTH];
	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	ACTION_INFO tAction;
	CopyMemory(&tID[0], &tPacket[1], MAX_USER_ID_LENGTH);
	tID[(MAX_USER_ID_LENGTH - 1)] = '\0';
	CopyMemory(&tAvatarName[0], &tPacket[(1 + MAX_USER_ID_LENGTH)], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
	CopyMemory(&tAction, &tPacket[(1 + MAX_USER_ID_LENGTH + MAX_AVATAR_NAME_LENGTH)], sizeof(ACTION_INFO));
	if ((strcmp(tID, mUSER[tUserIndex].uID) != 0) || (tAction.aType != 0) || ((tAction.aSort != 0) && (tAction.aSort != 1)))
	{
		__LogMgr()->Log("![RUN]  %s. %d\n", __FUNCTION__, __LINE__);
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int index01;
	int tLogoutInfo[6];
	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	time_t tCountSeconds;
	struct tm* tPresentTime;
	char cDate[100];
	unsigned int iDate = 0;

	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);

	tLogoutInfo[0] = mSERVER_INFO.mServerNumber;
	tLogoutInfo[1] = (int)tAction.aLocation[0];
	tLogoutInfo[2] = (int)tAction.aLocation[1];
	tLogoutInfo[3] = (int)tAction.aLocation[2];
	mPLAYUSER_COM.U_REGISTER_USER_FOR_ZONE_1_SEND(mUSER[tUserIndex].mPlayUserIndex, &tID[0], &tAvatarName[0], &tLogoutInfo[0]);
	if (mPLAYUSER_COM.mRecv_Result != 0)
	{
		__LogMgr()->Log("![RUN]  %s. %d\n", __FUNCTION__, __LINE__);
		//__LogMgr()->Log("![%s] : U_REGISTER_USER_FOR_ZONE_1_SEND failed(%d)\n"
		//		, __FUNCTION__, mPLAYUSER_COM.mRecv_Result);
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}


	if (mPLAYUSER_COM.mRecv_AuthInfo.AuthType == 0)
	{
		__LogMgr()->Log("![RUN]  %s. %d\n", __FUNCTION__, __LINE__);
		//-------------------//
		//EXAMINE_TRIBE_STATE//
		//-------------------//
		mUSER[tUserIndex].uUserSort = 0;
		switch (mPLAYUSER_COM.mRecv_AvatarInfo.aTribe)
		{
		case 0:
			if (mPLAYUSER_COM.mRecv_AvatarInfo.aPreviousTribe != 0)
			{
				__LogMgr()->Log("![RUN]  %s. %d\n", __FUNCTION__, __LINE__);
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 1:
			if (mPLAYUSER_COM.mRecv_AvatarInfo.aPreviousTribe != 1)
			{
				__LogMgr()->Log("![RUN]  %s. %d\n", __FUNCTION__, __LINE__);
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 2:
			if (mPLAYUSER_COM.mRecv_AvatarInfo.aPreviousTribe != 2)
			{
				__LogMgr()->Log("![RUN]  %s. %d\n", __FUNCTION__, __LINE__);
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 3:
			if ((mPLAYUSER_COM.mRecv_AvatarInfo.aPreviousTribe != 0) && (mPLAYUSER_COM.mRecv_AvatarInfo.aPreviousTribe != 1) && (mPLAYUSER_COM.mRecv_AvatarInfo.aPreviousTribe != 2))
			{
				__LogMgr()->Log("![RUN]  %s. %d\n", __FUNCTION__, __LINE__);
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		default:
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		//-------------------//
		//-------------------//
		//-------------------//
	
		if ((((mPLAYUSER_COM.mRecv_AvatarInfo.aLevel1 + mPLAYUSER_COM.mRecv_AvatarInfo.aLevel2) < mZONEMAININFO.ReturnMinZoneLevelInfo(mSERVER_INFO.mServerNumber)) ||
			(mPLAYUSER_COM.mRecv_AvatarInfo.aLevel1 + mPLAYUSER_COM.mRecv_AvatarInfo.aLevel2) > mZONEMAININFO.ReturnMaxZoneLevelInfo(mSERVER_INFO.mServerNumber)))

		{
			__LogMgr()->Log("![RUN]  %s. %d\n", __FUNCTION__, __LINE__);
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mGAME.mCheckZone101TypeServer)
		{
			if (mPLAYUSER_COM.mRecv_AvatarInfo.SolemGrounds < 1)
			{
				__LogMgr()->Log("![RUN]  %s. %d\n", __FUNCTION__, __LINE__);
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}

		

		if (mGAME.mCheckZone118Server)
		{
			if (mPLAYUSER_COM.mRecv_AvatarInfo.RebirtHall < 1)
			{
				__LogMgr()->Log("![RUN]  %s. %d\n", __FUNCTION__, __LINE__);
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}


		if (mGAME.mCheckZone125Server)
		{
			if (mPLAYUSER_COM.mRecv_AvatarInfo.EdgeOfTaiyan < 1)
			{
				__LogMgr()->Log("![RUN]  %s. %d\n", __FUNCTION__, __LINE__);
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if (mGAME.mCheckZone126TypeServer)
		{
			if (mPLAYUSER_COM.mRecv_AvatarInfo.ScrollOfSeekers < 1 && mPLAYUSER_COM.mRecv_AvatarInfo.Premium < 1)
			{
				__LogMgr()->Log("![RUN]  %s. %d\n", __FUNCTION__, __LINE__);
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if (mGAME.mCheckZone175TypeServer)
		{
			if (mGAME.mWorldInfo.mZone175TypeState[mGAME.mZone175TypeZoneIndex1][mGAME.mZone175TypeZoneIndex2] != 1)
			{
				__LogMgr()->Log("![RUN]  %s. %d\n", __FUNCTION__, __LINE__);
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if (mPLAYUSER_COM.mRecv_AvatarInfo.GodTempleKey < 1)
			{
				__LogMgr()->Log("![RUN]  %s. %d\n", __FUNCTION__, __LINE__);
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			mPLAYUSER_COM.mRecv_AvatarInfo.GodTempleKey--;
		}
		if (mGAME.LifeorDeathTypeServer)
		{
			if (mPLAYUSER_COM.mRecv_AvatarInfo.LifeOrDeath < 1)
			{
				__LogMgr()->Log("![RUN]  %s. %d\n", __FUNCTION__, __LINE__);
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if (mGAME.mCheckZone234TypeServer)
		{
			if (mPLAYUSER_COM.mRecv_AvatarInfo.IslandOfBlood < 1)
			{
				__LogMgr()->Log("![RUN]  %s. %d\n", __FUNCTION__, __LINE__);
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if (mGAME.mCheckZone235TypeServer)
		{
			if (mPLAYUSER_COM.mRecv_AvatarInfo.IslandOfSoulMReal1 < 1)
			{
				__LogMgr()->Log("![RUN]  %s. %d\n", __FUNCTION__, __LINE__);
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if (mGAME.mCheckZone236TypeServer)
		{
			if (mPLAYUSER_COM.mRecv_AvatarInfo.IslandOfSoulMReal2 < 1)
			{
				__LogMgr()->Log("![RUN]  %s. %d\n", __FUNCTION__, __LINE__);
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if (mGAME.mCheckZone237TypeServer)
		{
			if (mPLAYUSER_COM.mRecv_AvatarInfo.IslandOfSoulMReal3 < 1)
			{
				__LogMgr()->Log("![RUN]  %s. %d\n", __FUNCTION__, __LINE__);
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if (mGAME.mCheckZone238TypeServer)
		{
			if (mPLAYUSER_COM.mRecv_AvatarInfo.IslandOfSoulMReal4 < 1)
			{
				__LogMgr()->Log("![RUN]  %s. %d\n", __FUNCTION__, __LINE__);
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if (mGAME.mCheckZone239TypeServer)
		{
			if (mPLAYUSER_COM.mRecv_AvatarInfo.IslandOfSoulMReal5 < 1)
			{
				__LogMgr()->Log("![RUN]  %s. %d\n", __FUNCTION__, __LINE__);
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if (mGAME.mCheckZone240TypeServer)
		{
			if (mPLAYUSER_COM.mRecv_AvatarInfo.IslandOfSoulMReal6 < 1)
			{
				__LogMgr()->Log("![RUN]  %s. %d\n", __FUNCTION__, __LINE__);
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if (340 == mSERVER_INFO.mServerNumber) {

			mPLAYUSER_COM.mRecv_AvatarInfo.Hisar--;
		}
	}
	if (NULL != tPresentTime) {
		::memset(cDate, 0, 100);
		snprintf(cDate, 100, "%04d%02d%02d", tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);
		iDate = ::atoi(cDate);
	}

	mUSER[tUserIndex].mCheckValidState = TRUE;
	mUSER[tUserIndex].mRegisterTime = GetTickCount();
	mUSER[tUserIndex].uUserSort = mPLAYUSER_COM.mRecv_UserSort;
	mUSER[tUserIndex].uGoodFellow = mPLAYUSER_COM.mRecv_GoodFellow;
	mUSER[tUserIndex].uTraceState = mPLAYUSER_COM.mRecv_TraceState;
	mUSER[tUserIndex].uBonus100Money = mPLAYUSER_COM.mRecv_Bonus100Money;
	mUSER[tUserIndex].uPremiumServerExpirationDate = mPLAYUSER_COM.mRecv_PremiumServerExpirationDate; // ÇÁ¸®¹Ì¾ö ¼­¹ö(¿ùµå) ÀÔÀå±Ç À¯È¿ ±âÇÑ(YYYYMMDD ÇüÅÂÀÇ Á¤¼ö) ¼³Á¤. // @_Premium_Server_@

	// Proxy ValetShop - Lotus Alliance

	mPLAYUSER_COM.mRecv_AvatarInfo.ValetShop = 0;
	CopyMemory(&mUSER[tUserIndex].mAvatarInfo, &mPLAYUSER_COM.mRecv_AvatarInfo, sizeof(AVATAR_INFO));

	mUSER[tUserIndex].DropItemSocketGmAndBos[0] = 0;
	mUSER[tUserIndex].DropItemSocketGmAndBos[1] = 0;
	mUSER[tUserIndex].DropItemSocketGmAndBos[2] = 0;

#ifdef __IVEN_BUG_FIX__
	int iPage = 0;
	int iIndex = 0;
	int iNewPage = 0;
	int iNewIndex = 0;
	bool bItemMove = false;
	ITEM_INFO* pItemInfo = NULL;

	for (iPage = 0; iPage < 2; iPage++) {
		for (iIndex = 0; iIndex < MAX_INVENTORY_SLOT_NUM; iIndex++) {
			bItemMove = false;
			if (((mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][1] >= 7)
				|| (mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][2] >= 7))
				|| ((mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][1] < 0)
					|| (mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][2] < 0))) {
				pItemInfo = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][0]);
				if (pItemInfo == NULL) {
					mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][0] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][1] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][2] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][3] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][4] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][5] = 0;
					mUSER[tUserIndex].mAvatarInfo.InventorySocket[iPage][iIndex][0] = 0;
					mUSER[tUserIndex].mAvatarInfo.InventorySocket[iPage][iIndex][1] = 0;
					mUSER[tUserIndex].mAvatarInfo.InventorySocket[iPage][iIndex][2] = 0;
					continue;
				}

				if ((pItemInfo->iSort != 2) && (pItemInfo->iSort != 7) && (pItemInfo->iSort != 11)) {
					bItemMove = true;
				}
				else if (((mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][1] >= 8)
					|| (mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][2] >= 8))
					|| ((mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][1] < 0)
						|| (mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][2] < 0))) {
					bItemMove = true;
				}
				if (bItemMove) {
					if (mUTIL.FindEmptyInvenForItem(tUserIndex, pItemInfo, iNewPage, iNewIndex)) {
						if (iNewPage == iPage) {
							mUSER[tUserIndex].mAvatarInfo.aInventory[iNewPage][iIndex][1]
								= iNewIndex % 8;
							mUSER[tUserIndex].mAvatarInfo.aInventory[iNewPage][iIndex][2]
								= iNewIndex / 8;

						}
						else {
							mUSER[tUserIndex].mAvatarInfo.aInventory[iNewPage][iIndex][0]
								= mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][0];
							mUSER[tUserIndex].mAvatarInfo.aInventory[iNewPage][iIndex][1]
								= iNewIndex % 8;
							mUSER[tUserIndex].mAvatarInfo.aInventory[iNewPage][iIndex][2]
								= iNewIndex / 8;
							mUSER[tUserIndex].mAvatarInfo.aInventory[iNewPage][iIndex][3]
								= mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][3];
							mUSER[tUserIndex].mAvatarInfo.aInventory[iNewPage][iIndex][4]
								= mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][4];
							mUSER[tUserIndex].mAvatarInfo.aInventory[iNewPage][iIndex][5]
								= mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][5];
							mUSER[tUserIndex].mAvatarInfo.InventorySocket[iNewPage][iIndex][0]
								= mUSER[tUserIndex].mAvatarInfo.InventorySocket[iPage][iIndex][0];
							mUSER[tUserIndex].mAvatarInfo.InventorySocket[iNewPage][iIndex][1]
								= mUSER[tUserIndex].mAvatarInfo.InventorySocket[iPage][iIndex][1];
							mUSER[tUserIndex].mAvatarInfo.InventorySocket[iNewPage][iIndex][2]
								= mUSER[tUserIndex].mAvatarInfo.InventorySocket[iPage][iIndex][2];
							mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][0] = 0;
							mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][1] = 0;
							mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][2] = 0;
							mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][3] = 0;
							mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][4] = 0;
							mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][5] = 0;
							mUSER[tUserIndex].mAvatarInfo.InventorySocket[iPage][iIndex][0] = 0;
							mUSER[tUserIndex].mAvatarInfo.InventorySocket[iPage][iIndex][1] = 0;
							mUSER[tUserIndex].mAvatarInfo.InventorySocket[iPage][iIndex][2] = 0;
						}
					}
				}
			}
		}
	}
#endif
	if (mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[4] < 1)
	{
		mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[4] = 1;
	}
	CopyMemory(mUSER[tUserIndex].mEffectValue, mPLAYUSER_COM.mRecv_EffectValue, (MAX_AVATAR_EFFECT_SORT_NUM * 8));
	if (mUSER[tUserIndex].mAvatarInfo.aPlayTime2 < 1)
	{
		mUSER[tUserIndex].mCheckHealthState = FALSE;
		mUSER[tUserIndex].mHealthState = 1;
	}
	else
	{
		mUSER[tUserIndex].mCheckHealthState = TRUE;
		mUSER[tUserIndex].mHealthState = mUTIL.ReturnHealthState(mUSER[tUserIndex].mAvatarInfo.aPlayTime2);
	}

	/** 2009. 10. 26 : DarkAttack Potion add (wolf)*/
	mUSER[tUserIndex].mTickCountForDarkAttack = 0;
	mUSER[tUserIndex].iKindDarkAttack = 0;
	/** 2009. 10. 26 : DarkAttack Potion add (wolf)*/


	mUSER[tUserIndex].mTickCountFor01Second = mGAME.mTickCount;
	mUSER[tUserIndex].mTickCountFor01SecondForProtect = mGAME.mTickCount;
	mUSER[tUserIndex].mTickCountFor30Second = mGAME.mTickCount;
	mUSER[tUserIndex].mTickCountFor01MinuteForHealth = mGAME.mTickCount;
	mUSER[tUserIndex].mTickCountFor01Minute = mGAME.mTickCount;
	mUSER[tUserIndex].mTickCountFor01Minute_2 = mGAME.mTickCount;
	mUSER[tUserIndex].mTickCountFor03Second = mGAME.mTickCount;
	mUSER[tUserIndex].mCheckMaxAttackPacketNum = 1;
	mUSER[tUserIndex].mAttackPacketSort = 0;
	mUSER[tUserIndex].mMaxAttackPacketNum = 0;
	mUSER[tUserIndex].mNowAttackPacketNum = 0;
	mUSER[tUserIndex].mAutoCheckState = 0;
	mUSER[tUserIndex].mHackCheckTime = GetTickCount();
	mUSER[tUserIndex].mMoveZoneResult = 0;
	mUSER[tUserIndex].AutoBuff1 = 0;
	mUSER[tUserIndex].AutoBuffTick = 0;

	mUSER[tUserIndex].WinFish = 0;
	mUSER[tUserIndex].GainFish = 3;

	CopyMemory(&mUSER[tUserIndex].mAuthInfo, &mPLAYUSER_COM.mRecv_AuthInfo, sizeof(AUTH_INFO));

	mTRANSFER.B_REGISTER_AVATAR_RECV(&mUSER[tUserIndex].mAvatarInfo, mUSER[tUserIndex].mEffectValue, mUSER[tUserIndex].uPremiumServerExpirationDate); // mUSER[tUserIndex].uPremiumServerExpirationDate Ãß°¡. // @_Premium_Server_@
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	mTRANSFER.B_BROADCAST_WORLD_INFO(&mGAME.mWorldInfo, &mGAME.mTribeInfo);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	mTRANSFER.B_CPTOWER(&mGAME.mCpTower);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	mTRANSFER.B_RANKINFO(&mGAME.mRankInfo);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	mTRANSFER.B_OLDRANKINFO(&mGAME.mOldRankInfo);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	mAVATAR_OBJECT[tUserIndex].mCheckValidState = TRUE;
	mAVATAR_OBJECT[tUserIndex].mUniqueNumber = mGAME.mAvatarObjectUniqueNumber;
	mGAME.mAvatarObjectUniqueNumber++;
	mAVATAR_OBJECT[tUserIndex].mDATA.aVisibleState = (unsigned char)mUSER[tUserIndex].mAvatarInfo.aVisibleState;
	mAVATAR_OBJECT[tUserIndex].mDATA.aSpecialState = (unsigned char)mUSER[tUserIndex].mAvatarInfo.aSpecialState;
	mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe = mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe;
	strncpy(mAVATAR_OBJECT[tUserIndex].mDATA.aGuildName, mUSER[tUserIndex].mAvatarInfo.aGuildName, MAX_GUILD_NAME_LENGTH);
	mAVATAR_OBJECT[tUserIndex].mDATA.aGuildRole = mUSER[tUserIndex].mAvatarInfo.aGuildRole;
	strncpy(mAVATAR_OBJECT[tUserIndex].mDATA.aCallName, mUSER[tUserIndex].mAvatarInfo.aCallName, MAX_CALL_NAME_LENGTH);
	mAVATAR_OBJECT[tUserIndex].mDATA.aGuildMarkEffect = mUSER[tUserIndex].mAvatarInfo.aGuildMarkEffect;
	strncpy(mAVATAR_OBJECT[tUserIndex].mDATA.aName, mUSER[tUserIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH);
	strncpy(mAVATAR_OBJECT[tUserIndex].mDATA.aPartyName, mUSER[tUserIndex].mAvatarInfo.aPartyName[0], MAX_AVATAR_NAME_LENGTH);
	mAVATAR_OBJECT[tUserIndex].mDATA.aTribe = mUSER[tUserIndex].mAvatarInfo.aTribe;
	mAVATAR_OBJECT[tUserIndex].mDATA.aPreviousTribe = mUSER[tUserIndex].mAvatarInfo.aPreviousTribe;
	mAVATAR_OBJECT[tUserIndex].mDATA.aGender = mUSER[tUserIndex].mAvatarInfo.aGender;
	mAVATAR_OBJECT[tUserIndex].mDATA.aHeadType = mUSER[tUserIndex].mAvatarInfo.aHeadType;
	mAVATAR_OBJECT[tUserIndex].mDATA.aFaceType = mUSER[tUserIndex].mAvatarInfo.aFaceType;
	mAVATAR_OBJECT[tUserIndex].mDATA.aLevel1 = mUSER[tUserIndex].mAvatarInfo.aLevel1;
	mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = mUSER[tUserIndex].mAvatarInfo.aLevel2;
	mAVATAR_OBJECT[tUserIndex].mDATA.aHalo = mUSER[tUserIndex].mAvatarInfo.aUpradgeValue;
	mAVATAR_OBJECT[tUserIndex].mDATA.aRebirth = mUSER[tUserIndex].mAvatarInfo.SkillIncreaseCritHit;
	mAVATAR_OBJECT[tUserIndex].mDATA.aTitle = mUSER[tUserIndex].mAvatarInfo.Title;
	mAVATAR_OBJECT[tUserIndex].mDATA.aRankPoint = mUSER[tUserIndex].mAvatarInfo.aRankPoint;

	for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM; index01++)
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aEquipForView[index01][0] = mUSER[tUserIndex].mAvatarInfo.aEquip[index01][0];
		mAVATAR_OBJECT[tUserIndex].mDATA.aEquipForView[index01][1] = mUSER[tUserIndex].mAvatarInfo.aEquip[index01][2];
	}
	CopyMemory(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction, &tAction, sizeof(ACTION_INFO));
	mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[4];
	mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[5];
	for (index01 = 0; index01 < MAX_AVATAR_EFFECT_SORT_NUM; index01++)
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aEffectValueForView[index01] = mUSER[tUserIndex].mEffectValue[index01][0];
	}
	if ((mUSER[tUserIndex].mAvatarInfo.aAnimalIndex >= MAX_AVATAR_ANIMAL_NUM) && (mUSER[tUserIndex].mAvatarInfo.aAnimalIndex <= (MAX_AVATAR_ANIMAL_NUM + MAX_AVATAR_ANIMAL_NUM - 1)))
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalNumber = mUSER[tUserIndex].mAvatarInfo.aAnimal[(mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - MAX_AVATAR_ANIMAL_NUM)];

		if (mUSER[tUserIndex].mAvatarInfo.MountAbsorbe == 1)
		{
			mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalOn = mUSER[tUserIndex].mAvatarInfo.MountAbsorbe;
		}
	}
	else
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalNumber = 0;
	}
	if ((mUSER[tUserIndex].mAvatarInfo.SelectCostume <= (MAX_AVATAR_ANIMAL_NUM + MAX_AVATAR_ANIMAL_NUM - 1)))
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aFashionNumber = mUSER[tUserIndex].mAvatarInfo.Costume[(mUSER[tUserIndex].mAvatarInfo.SelectCostume - MAX_AVATAR_ANIMAL_NUM)];
	}
	else
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aFashionNumber = 0;
	}
	for (index01 = 0; index01 < MAX_AVATAR_EFFECT_SORT_NUM; index01++)
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aEffectValueForView[index01] = mUSER[tUserIndex].mEffectValue[index01][0];
	}


	int tStat = (mUSER[tUserIndex].mAvatarInfo.aVitality +
		mUSER[tUserIndex].mAvatarInfo.aStrength +
		mUSER[tUserIndex].mAvatarInfo.aKi +
		mUSER[tUserIndex].mAvatarInfo.aWisdom +
		mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint) - 4;
	if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
	{ 
		//if (tStat > (2975 + mUSER[tUserIndex].mAvatarInfo.SkillIncreaseCritHit * 100))
		//{
		//	mGAMELOG.GL_BAN_SEND(tUserIndex, __FILE__, __FUNCTION__, __LINE__);
		//	//mPLAYUSER_COM.U_BLOCK_USER_FOR_ZONE_1_SEND(605, &mUSER[tUserIndex].uID[0]);
		//	mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		//	return;
		//}
	}

	mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[0] = 0;
	mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[1] = 0;
	mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[2] = 0;
	mAVATAR_OBJECT[tUserIndex].mDATA.aPShopState = 0;
	mAVATAR_OBJECT[tUserIndex].mCheckPossibleEatPotion = TRUE;
	mAVATAR_OBJECT[tUserIndex].mDuelProcessState = 0;
	mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
	mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 0;
	mAVATAR_OBJECT[tUserIndex].mPartyProcessState = 0;
	mAVATAR_OBJECT[tUserIndex].mGuildProcessState = 0;
	mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 0;
	mAVATAR_OBJECT[tUserIndex].SetSpaceIndex();
	// # Defense Hack # {
	mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[0] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0];
	mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[1] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[1];
	mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[2] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[2];
	// # }
	mAVATAR_OBJECT[tUserIndex].mUpdateTimeForBroadcast = GetTickCount();
	mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
	mAVATAR_OBJECT[tUserIndex].mGod = 0;
	mAVATAR_OBJECT[tUserIndex].mChat = 0;
	if (mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue > mAVATAR_OBJECT[tUserIndex].mDATA.aMaxLifeValue)
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].mDATA.aMaxLifeValue;
	}
	if (mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue > mAVATAR_OBJECT[tUserIndex].mDATA.aMaxManaValue)
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].mDATA.aMaxManaValue;
	}
	mTRANSFER.B_AVATAR_ACTION_RECV(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, &mAVATAR_OBJECT[tUserIndex].mDATA, 1);
	if (mUSER[tUserIndex].mAvatarInfo.aVisibleState == 0)
	{
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}
	else
	{
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, tUserIndex, false);
	}
	if ((mUSER[tUserIndex].mAvatarInfo.aVisibleState == 1) && (mPLAYUSER_COM.mRecv_CheckFirstZone == 1) && (strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") != 0))
	{
		tSort = 110;
		CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		CopyMemory(&tData[MAX_GUILD_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
		mRELAY_COM.U_DEMAND_BROADCAST_DATA(tSort, &tData[0]);
	}

	mUSER[tUserIndex].mHeartCheckTime = ::time(NULL);

	mUSER[tUserIndex].mAuthInfo.IlkMapeGiris = 1;

	mAVATAR_OBJECT[tUserIndex].mDATA.aHideCostume = mUSER[tUserIndex].mAvatarInfo.HideCostumeRegister;
	mTRANSFER.B_HIDECOSTUME(mAVATAR_OBJECT[tUserIndex].mDATA.aHideCostume, 0, 0);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_CLIENT_OK_FOR_ZONE_SEND
void W_CLIENT_OK_FOR_ZONE_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (mUSER[tUserIndex].mMoveZoneResult == 1) {
		return;
	}

	int tTribe;
	double speed;
	time_t tCurrentTime = ::time(NULL);
	time_t tCountSeconds;
	struct tm* tPresentTime;
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);

	CopyMemory(&tTribe, &tPacket[1], 4);

	if (mUSER[tUserIndex].mAvatarInfo.aTribe != tTribe)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	//Server ?x exp 
	mTRANSFER.B_AVATAR_CHANGE_INFO_2(56, mSERVER_INFO.WORLD_EXP);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	//Server ?x drop 
	mTRANSFER.B_AVATAR_CHANGE_INFO_2(57, mSERVER_INFO.WORLD_ITEM_DROP);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	//Server ?x cp 
	mTRANSFER.B_AVATAR_CHANGE_INFO_2(58, mSERVER_INFO.WORLD_KTAV);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	//Server Time
	mTRANSFER.B_AVATAR_CHANGE_INFO_2(98, (tPresentTime->tm_mon * 10000000) + (tPresentTime->tm_mday * 100000) + (tPresentTime->tm_hour * 1000) + (tPresentTime->tm_min * 10) + (tPresentTime->tm_wday));
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	if ((tCurrentTime - mUSER[tUserIndex].mHeartCheckTime) < 2) {
		mUSER[tUserIndex].mHeartCheckCount++;
		if (mUSER[tUserIndex].mHeartCheckCount > 10) {
			__LogMgr()->Log("![HACK] : %s, %s, %d, %d\n"
				, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName
				, (tCurrentTime - mUSER[tUserIndex].mHeartCheckTime), mUSER[tUserIndex].mHeartCheckCount);
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		}
		return;
	}
	mAVATAR_OBJECT[tUserIndex].SetSpaceIndex();
	mUSER[tUserIndex].mHeartCheckCount = 0;
	mUSER[tUserIndex].mHeartCheckTime = tCurrentTime;

}
//W_AUTO_CHECK_ASK_RECV
void W_AUTO_CHECK_ASK_RECV(int tUserIndex)
{

	__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tAnswer;
	CopyMemory(&tAnswer, &tPacket[1], 4);

	switch (mUSER[tUserIndex].mAutoCheckState)
	{
	case 0:
		return;
	case 1:
		mUSER[tUserIndex].mAutoCheckState = 0;

		if (mUSER[tUserIndex].mAutoCheckAnswer == tAnswer)
		{
			return;
		}
		mPLAYUSER_COM.U_ADD_AUTO_USER_LIST_SEND(&mUSER[tUserIndex].uID[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], mSERVER_INFO.mWorldNumber, mSERVER_INFO.mServerNumber);
		mTRANSFER.B_RETURN_TO_AUTO_ZONE();
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
}
//W_AVATAR_ACTION_SEND
void W_AVATAR_ACTION_SEND(int tUserIndex)
{

	__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}


	ACTION_INFO tAction;
	CopyMemory(&tAction, &tPacket[1], sizeof(ACTION_INFO));

	int index01;
	int index02;
	int tSkillSort;
	int tUseManaValue;
	int tReduceManaRatio;
	//__LogMgr()->Log("=>1\n");
	if (!mWORK.CheckValidCharacterMotionForSend(tAction.aType, tAction.aSort, tAction.aSkillNumber, &tSkillSort, &mUSER[tUserIndex].mCheckMaxAttackPacketNum, &mUSER[tUserIndex].mAttackPacketSort, &mUSER[tUserIndex].mMaxAttackPacketNum))

	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	//__LogMgr()->Log("=>2 %d\n", tSkillSort);
	mUSER[tUserIndex].mNowAttackPacketNum = 0;
	tUseManaValue = 0;
	switch (tSkillSort)
	{
	case 1:
		for (index01 = 0; index01 < 3; index01++)
		{
			for (index02 = 0; index02 < MAX_HOT_KEY_NUM; index02++)
			{
				if ((mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] == 1) && (mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][0] == tAction.aSkillNumber) && (mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][1] == tAction.aSkillGradeNum1))
				{
					break;
				}
			}
			if (index02 < MAX_HOT_KEY_NUM)
			{
				break;
			}
		}
		if (index01 == 3)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mAVATAR_OBJECT[tUserIndex].GetBonusSkillValue(tAction.aSkillNumber) != tAction.aSkillGradeNum2)
		{

			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 2:
		for (index01 = 0; index01 < 3; index01++)
		{
			for (index02 = 0; index02 < MAX_HOT_KEY_NUM; index02++)
			{
				if ((mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] == 1) && (mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][0] == tAction.aSkillNumber) && (mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][1] == tAction.aSkillGradeNum1))
				{
					break;
				}
			}
			if (index02 < MAX_HOT_KEY_NUM)
			{
				break;
			}
		}
		if (index01 == 3)
		{
			if (mUSER[tUserIndex].mAvatarInfo.HunstStart != 1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}

		if (mAVATAR_OBJECT[tUserIndex].GetBonusSkillValue(tAction.aSkillNumber) != tAction.aSkillGradeNum2)
		{

			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tUseManaValue = (int)mSKILL.ReturnSkillValue(tAction.aSkillNumber, tAction.aSkillGradeNum1, 1);
		tReduceManaRatio = mAVATAR_OBJECT[tUserIndex].GetReduceManaRatio();
#if 0
		if (mUSER[tUserIndex].mAvatarInfo.aHalfManaTime > 0)
		{
			tUseManaValue = tUseManaValue / 2;
		}
#endif
		if (tReduceManaRatio > 0)
		{
			tUseManaValue -= ((tUseManaValue * tReduceManaRatio) / 100);
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue < tUseManaValue)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	}
	//__LogMgr()->Log("=>3 %d %d\n", mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort, tAction.aSort);
	switch (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort)
	{
	case 11:
		return;
	case 12:
		if (tAction.aSort != 0)
		{
			return;
		}
		break;
	}
	if (tUseManaValue > 0)
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue -= tUseManaValue;
	}

	if (tAction.aSkillNumber != 0)
	{
		if (mAVATAR_OBJECT[tUserIndex].CheckSkillForWeapon(tAction.aSkillNumber) == 2)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		// µ¿Çà¹«°øÀº °Ë»ç¿¡¼­ Á¦¿Ü.
		if ((tAction.aSkillNumber != 76) && (tAction.aSkillNumber != 77) && (tAction.aSkillNumber != 78) && (tAction.aSkillNumber != 79) && (tAction.aSkillNumber != 80) && (tAction.aSkillNumber != 81))
		{
			if ((tAction.aSkillGradeNum1 > mUSER[tUserIndex].GetMaxSkillGradeNum(tAction.aSkillNumber)) || (tAction.aSkillGradeNum2 > mAVATAR_OBJECT[tUserIndex].GetBonusSkillValue(tAction.aSkillNumber)))
			{
				//mGAMELOG.GL_702_CHEAT_AVATAR_ACTION(tUserIndex, tAction.aSkillNumber, tAction.aSkillGradeNum1, tAction.aSkillGradeNum2, tAction.aSkillValue);
				//mPLAYUSER_COM.U_BLOCK_USER_FOR_ZONE_1_SEND(605, &mUSER[tUserIndex].uID[0]);
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
	}



	// # Defense Hack # {
	float fRange = 0.0f;
	fRange = mUTIL.ReturnLengthXYZ(&tAction.aLocation[0], &mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[0]);

	if ((fRange > 666.0f) && !mAVATAR_OBJECT[tUserIndex].mCheckDeath
		&& (mUSER[tUserIndex].mAuthInfo.AuthType == 0) && mUSER[tUserIndex].mAvatarInfo.HunstStart == 0 && (mAVATAR_OBJECT[tUserIndex].mCheckCount < 1)
		&& (!mGAME.mCheckZone049TypeServer) && (!mGAME.mCheckZone051TypeServer) && (!mGAME.mCheckZone053TypeServer)) {
		//&& ((mUSER[tUserIndex].mAvatarInfo.aAutoStart == 0))) { // .... Auto .. ... ... .. ..
		//mGAMELOG.GL_659_AUTO_CHECK(tUserIndex, 4, fRange);
		tAction.aLocation[0] = mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[0];
		tAction.aLocation[1] = mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[1];
		tAction.aLocation[2] = mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[2];
		CopyMemory(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction, &tAction, sizeof(ACTION_INFO));
		mTRANSFER.B_AVATAR_ACTION_RECV(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, &mAVATAR_OBJECT[tUserIndex].mDATA, 0);
	}
	else {
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0] = tAction.aLocation[0];
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[1] = tAction.aLocation[1];
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[2] = tAction.aLocation[2];
		CopyMemory(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction, &tAction, sizeof(ACTION_INFO));
		mTRANSFER.B_AVATAR_ACTION_RECV(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, &mAVATAR_OBJECT[tUserIndex].mDATA, 1);
	}
	mAVATAR_OBJECT[tUserIndex].mCheckCount--;
	mAVATAR_OBJECT[tUserIndex].SetSpaceIndex();

	// # }
	CopyMemory(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction, &tAction, sizeof(ACTION_INFO));
	mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0] = tAction.aLocation[0];
	mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[1] = tAction.aLocation[1];
	mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[2] = tAction.aLocation[2];
	mAVATAR_OBJECT[tUserIndex].SetSpaceIndex();
	mTRANSFER.B_AVATAR_ACTION_RECV(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, &mAVATAR_OBJECT[tUserIndex].mDATA, 1);
	if (mUSER[tUserIndex].mAvatarInfo.aVisibleState == 0)
	{
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}
	else
	{
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, tUserIndex, false);
	}
	if (tAction.aSort != 0)
	{
		return;
	}
	mUSER[tUserIndex].mTickCountFor01SecondForProtect = mGAME.mTickCount;
	mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = (mAVATAR_OBJECT[tUserIndex].GetMaxLife() / 3) + 1;
	mTRANSFER.B_AVATAR_CHANGE_INFO_2(10, mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//CHECK_VALID_CHARACTER_MOTION_FOR_SEND
BOOL MyWork::CheckValidCharacterMotionForSend(int tType, int tSort, int tSkillNumber, int* tSkillSort, int* tCheckMaxAttackPacketNum, int* tAttackPacketSort, int* tMaxAttackPacketNum)
{
	__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);

	*tSkillSort = 0;
	*tCheckMaxAttackPacketNum = 1;
	*tMaxAttackPacketNum = 0;
#ifdef __GOD__
	* tAttackPacketSort = 0;
#endif
	switch (tSort)
	{
	case  0:
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case  1:
		switch (tType)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			return TRUE;
		}
		break;
	case  2:
		switch (tType)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			return TRUE;
		}
		break;
	case  3:
		switch (tType)
		{
		case 0:
		case 2:
		case 4:
		case 6:
			return TRUE;
		}
		break;
	case  4:
		switch (tType)
		{
		case 1:
		case 3:
		case 5:
		case 7:
			return TRUE;
		}
		break;
	case  5:
		*tMaxAttackPacketNum = 1;
#ifdef __GOD__
		* tSkillSort = 0;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 1;
#endif
		switch (tType)
		{
		case 1:
		case 3:
		case 5:
		case 7:
			return TRUE;
		}
		break;
	case  6:
		*tMaxAttackPacketNum = 2;
#ifdef __GOD__
		* tSkillSort = 0;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 1;
#endif
		switch (tType)
		{
		case 1:
		case 3:
		case 5:
		case 7:
			return TRUE;
		}
		break;
	case  7:
		*tMaxAttackPacketNum = 3;
#ifdef __GOD__
		* tSkillSort = 0;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 1;
#endif
		switch (tType)
		{
		case 1:
		case 3:
		case 5:
		case 7:
			return TRUE;
		}
		break;
	case  9:
		switch (tType)
		{
		case 1:
		case 3:
		case 5:
		case 7:
			return TRUE;
		}
		break;
	case 10:
		switch (tType)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			return TRUE;
		}
		break;
	case 13:
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 14:
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 15:
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 16:
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 17:
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 18:
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 20:
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 21:
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 22:
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 23:
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 30:
		*tSkillSort = 1;
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 32:
		*tSkillSort = 2;
		switch (tType)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			return TRUE;
		}
		break;
	case 33:
		*tSkillSort = 2;
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 38:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 1;
#ifdef __GOD__
		* tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 2;
#endif
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 39:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 1;
#ifdef __GOD__
		* tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 2;
#endif
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 40:
		*tSkillSort = 2;
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 41:
		*tSkillSort = 2;
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 42:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 1;
#ifdef __GOD__
		* tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
#endif
		switch (tType)
		{
		case 3:
			return TRUE;
		}
		break;
	case 43:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 3;
#ifdef __GOD__
		* tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
#endif
		switch (tType)
		{
		case 3:
			return TRUE;
		}
		break;
	case 44:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 5;
#ifdef __GOD__
		* tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
#endif
		switch (tType)
		{
		case 3:
			return TRUE;
		}
		break;
	case 45:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 1;
#ifdef __GOD__
		* tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
#endif
		switch (tType)
		{
		case 3:
			return TRUE;
		}
		break;
	case 46:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 3;
#ifdef __GOD__
		* tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
#endif
		switch (tType)
		{
		case 3:
			return TRUE;
		}
		break;
	case 48:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 1;
#ifdef __GOD__
		* tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
#endif
		switch (tType)
		{
		case 5:
			return TRUE;
		}
		break;
	case 49:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 3;
#ifdef __GOD__
		* tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
#endif
		switch (tType)
		{
		case 5:
			return TRUE;
		}
		break;
	case 50:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 5;
#ifdef __GOD__
		* tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
#endif
		switch (tType)
		{
		case 5:
			return TRUE;
		}
		break;
	case 51:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 1;
#ifdef __GOD__
		* tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
#endif
		switch (tType)
		{
		case 5:
			return TRUE;
		}
		break;
	case 52:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 3;
#ifdef __GOD__
		* tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
#endif
		switch (tType)
		{
		case 5:
			return TRUE;
		}
		break;
	case 54:
		*tSkillSort = 2;
#ifdef __GOD__
		* tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 4;
		*tMaxAttackPacketNum = 1;
#else
		* tCheckMaxAttackPacketNum = 0;
#endif
		switch (tType)
		{
		case 7:
			return TRUE;
		}
		break;
	case 55:
		*tSkillSort = 2;
#ifdef __GOD__
		* tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 4;
		*tMaxAttackPacketNum = 3;
#else
		* tCheckMaxAttackPacketNum = 0;
#endif
		switch (tType)
		{
		case 7:
			return TRUE;
		}
		break;
	case 56:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 5;
#ifdef __GOD__
		* tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
#endif
		switch (tType)
		{
		case 7:
			return TRUE;
		}
		break;
	case 57:
		*tSkillSort = 2;
#ifdef __GOD__
		* tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 4;
		*tMaxAttackPacketNum = 1;
#else
		* tCheckMaxAttackPacketNum = 0;
#endif
		switch (tType)
		{
		case 7:
			return TRUE;
		}
		break;
	case 58:
		*tSkillSort = 2;
#ifdef __GOD__
		* tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 4;
		*tMaxAttackPacketNum = 3;
#else
		* tCheckMaxAttackPacketNum = 0;
#endif
		switch (tType)
		{
		case 7:
			return TRUE;
		}
		break;
	case 60:
		*tSkillSort = 2;
		switch (tType)
		{
		case 3:
			return TRUE;
		}
		break;
	case 61:
		*tSkillSort = 2;
		switch (tType)
		{
		case 5:
			return TRUE;
		}
		break;
	case 62:
		*tSkillSort = 2;
		switch (tType)
		{
		case 7:
			return TRUE;
		}
		break;
	case 63:
		*tSkillSort = 2;
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 64:
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 65:
#ifdef __GOD__
		* tSkillSort = 0;
		*tAttackPacketSort = 5;
		*tMaxAttackPacketNum = 1;
#endif
		* tCheckMaxAttackPacketNum = 0;
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 66:
		*tSkillSort = 2;
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 67:
		*tSkillSort = 2;
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 68:
		*tSkillSort = 2;
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 69:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 1;
#ifdef __GOD__
		* tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
#endif
		switch (tType)
		{
		case 3:
			return TRUE;
		}
		break;
	case 70:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 3;
#ifdef __GOD__
		* tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
#endif
		switch (tType)
		{
		case 3:
			return TRUE;
		}
		break;
	case 71:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 1;
#ifdef __GOD__
		* tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
#endif
		switch (tType)
		{
		case 5:
			return TRUE;
		}
		break;
	case 72:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 3;
#ifdef __GOD__
		* tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
#endif
		switch (tType)
		{
		case 5:
			return TRUE;
		}
		break;
	case 73:
		*tSkillSort = 2;
#ifdef __GOD__
		* tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 4;
		*tMaxAttackPacketNum = 3;
#else
		* tCheckMaxAttackPacketNum = 0;
#endif
		switch (tType)
		{
		case 7:
			return TRUE;
		}
		break;
	case 74:
		*tSkillSort = 2;
		*tCheckMaxAttackPacketNum = 0;
		switch (tType)
		{
		case 7:
			return TRUE;
		}
		break;
	case 75:
		*tSkillSort = 2;
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 76:
		*tSkillSort = 2;
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 81:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 5;
#ifdef __GOD__
		* tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
#endif
		switch (tType)
		{
		case 3:
			return TRUE;
		}
		break;
	case 82:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 5;
#ifdef __GOD__
		* tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
#endif
		switch (tType)
		{
		case 5:
			return TRUE;
		}
		break;
	case 83:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 5;
#ifdef __GOD__
		* tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
#endif
		switch (tType)
		{
		case 7:
			return TRUE;
		}
		break;
#ifdef __GOD__
	case 85:
		*tSkillSort = 2;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		*tMaxAttackPacketNum = 1;
		switch (tType)
		{
		case 3:
			return TRUE;
		}
		break;
	case 86:
		*tSkillSort = 2;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		*tMaxAttackPacketNum = 3;
		switch (tType)
		{
		case 3:
			return TRUE;
		}
		break;
	case 87:
		*tSkillSort = 2;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		*tMaxAttackPacketNum = 1;
		switch (tType)
		{
		case 5:
			return TRUE;
		}
		break;
	case 88:
		*tSkillSort = 2;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		*tMaxAttackPacketNum = 3;
		switch (tType)
		{
		case 5:
			return TRUE;
		}
		break;
	case 89:
		*tSkillSort = 2;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 4;
		*tMaxAttackPacketNum = 1;
		switch (tType)
		{
		case 7:
			return TRUE;
		}
		break;
	case 90:
		*tSkillSort = 2;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 4;
		*tMaxAttackPacketNum = 3;
		switch (tType)
		{
		case 7:
			return TRUE;
		}
		break;
	case 91:
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 255:
		*tSkillSort = 3;
		switch (tType)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			return TRUE;
		}
		break;
#endif

	}
	return FALSE;
}
//W_UPDATE_AVATAR_ACTION
void W_UPDATE_AVATAR_ACTION(int tUserIndex)
{

	__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	ACTION_INFO tAction;
	CopyMemory(&tAction, &tPacket[1], sizeof(ACTION_INFO));
	switch (tAction.aSort)
	{
	case  1:
		if (mUSER[tUserIndex].AutoBuff1 != 0)
		{
			return;
		}

		mAVATAR_OBJECT[tUserIndex].ProcessForCreateEffectValue(&tAction);
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		break;
	case  2:
		break;
	case 19:
		if (tAction.aType != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 31:
		if (tAction.aType != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 32:
		break;
	case 64:
		if (tAction.aType != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 91:
		if (tAction.aType != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 92:
		if (tAction.aType != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 93:
		if (tAction.aType != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 94:
		if (tAction.aType != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 95:
		if (tAction.aType != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}


	// # Defense Hack # {
	mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[0] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0];
	mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[1] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[1];
	mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[2] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[2];
	// # }

	mAVATAR_OBJECT[tUserIndex].SetSpaceIndex();
	if (tAction.aSkillNumber != 0)
	{
		if (mAVATAR_OBJECT[tUserIndex].CheckSkillForWeapon(tAction.aSkillNumber) == 2)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		// µ¿Çà¹«°øÀº °Ë»ç¿¡¼­ Á¦¿Ü.
		if ((tAction.aSkillNumber != 76) && (tAction.aSkillNumber != 77) && (tAction.aSkillNumber != 78) && (tAction.aSkillNumber != 79) && (tAction.aSkillNumber != 80) && (tAction.aSkillNumber != 81))
		{
			if ((tAction.aSkillGradeNum1 > mUSER[tUserIndex].GetMaxSkillGradeNum(tAction.aSkillNumber)) || (tAction.aSkillGradeNum2 > mAVATAR_OBJECT[tUserIndex].GetBonusSkillValue(tAction.aSkillNumber)))
			{
				//mGAMELOG.GL_702_CHEAT_AVATAR_ACTION(tUserIndex, tAction.aSkillNumber, tAction.aSkillGradeNum1, tAction.aSkillGradeNum2, tAction.aSkillValue);
				mPLAYUSER_COM.U_BLOCK_USER_FOR_ZONE_1_SEND(605, &mUSER[tUserIndex].uID[0]);
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
	}
	CopyMemory(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction, &tAction, sizeof(ACTION_INFO));
	mAVATAR_OBJECT[tUserIndex].SetSpaceIndex();

}
//W_GENERAL_NOTICE_SEND
void W_GENERAL_NOTICE_SEND(int tUserIndex)
{
	__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	char tContent[MAX_CHAT_CONTENT_LENGTH];
	CopyMemory(&tContent[0], &tPacket[1], MAX_CHAT_CONTENT_LENGTH);
	tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
	if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (mUSER[tUserIndex].mAuthInfo.NoticeFlag == 0) {
		return;
	}

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];
	mAVATAR_OBJECT[tUserIndex].SetSpaceIndex();
	tSort = 102;
	CopyMemory(&tData[0], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
	mRELAY_COM.U_DEMAND_BROADCAST_DATA(tSort, &tData[0]);

}
//W_PROCESS_ATTACK_SEND
void W_PROCESS_ATTACK_SEND(int tUserIndex)
{
	__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	ATTACK_FOR_PROTOCOL tAttackInfo;
	CopyMemory(&tAttackInfo, &tPacket[1], sizeof(ATTACK_FOR_PROTOCOL));
	switch (tAttackInfo.mCase)
	{
	case 1: //[ºñ¹«]
		if ((tAttackInfo.mServerIndex1 == tUserIndex) && (tAttackInfo.mUniqueNumber1 == mAVATAR_OBJECT[tUserIndex].mUniqueNumber))
		{
			if (mUSER[tUserIndex].mCheckMaxAttackPacketNum == 1)
			{
				mUSER[tUserIndex].mNowAttackPacketNum++;
				if (mUSER[tUserIndex].mNowAttackPacketNum > mUSER[tUserIndex].mMaxAttackPacketNum)
				{
					return;
				}
				if (tAttackInfo.mAttackActionValue4 != mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort)
				{
					return;
				}
			}
		}
		mGAME.ProcessAttack01(tUserIndex, &tAttackInfo);
		return;
	case 2: //[¼¼·Â]
		if ((tAttackInfo.mServerIndex1 == tUserIndex) && (tAttackInfo.mUniqueNumber1 == mAVATAR_OBJECT[tUserIndex].mUniqueNumber))
		{
			if (mUSER[tUserIndex].mCheckMaxAttackPacketNum == 1)
			{
				mUSER[tUserIndex].mNowAttackPacketNum++;
				if (mUSER[tUserIndex].mNowAttackPacketNum > mUSER[tUserIndex].mMaxAttackPacketNum)
				{
					return;
				}
				if (tAttackInfo.mAttackActionValue4 != mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort)
				{
					return;
				}
			}
		}
		mGAME.ProcessAttack02(tUserIndex, &tAttackInfo);
		return;
	case 3: //[Ä³¸¯ÅÍ->¸ó½ºÅÍ]
		if ((tAttackInfo.mServerIndex1 == tUserIndex) && (tAttackInfo.mUniqueNumber1 == mAVATAR_OBJECT[tUserIndex].mUniqueNumber))
		{
			if (mUSER[tUserIndex].mCheckMaxAttackPacketNum == 1)
			{
				mUSER[tUserIndex].mNowAttackPacketNum++;
				if (mUSER[tUserIndex].mNowAttackPacketNum > mUSER[tUserIndex].mMaxAttackPacketNum)
				{
					return;
				}
				if (tAttackInfo.mAttackActionValue4 != mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort)
				{
					return;
				}
			}
		}
		mGAME.ProcessAttack03(tUserIndex, &tAttackInfo);
		return;
	case 4: //[¸ó½ºÅÍ->Ä³¸¯ÅÍ]
		mGAME.ProcessAttack04(tUserIndex, &tAttackInfo);
		return;
	case 5: //[Á¡Ç÷]
		if ((tAttackInfo.mServerIndex1 == tUserIndex) && (tAttackInfo.mUniqueNumber1 == mAVATAR_OBJECT[tUserIndex].mUniqueNumber))
		{
			if (mUSER[tUserIndex].mCheckMaxAttackPacketNum == 1)
			{
				mUSER[tUserIndex].mNowAttackPacketNum++;
				if (mUSER[tUserIndex].mNowAttackPacketNum > mUSER[tUserIndex].mMaxAttackPacketNum)
				{
					return;
				}
				if (tAttackInfo.mAttackActionValue4 != mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort)
				{
					return;
				}
			}
		}
		mGAME.ProcessAttack05(tUserIndex, &tAttackInfo);
		return;
	case 6: //[ÇØÇ÷]
		if ((tAttackInfo.mServerIndex1 == tUserIndex) && (tAttackInfo.mUniqueNumber1 == mAVATAR_OBJECT[tUserIndex].mUniqueNumber))
		{
			if (mUSER[tUserIndex].mCheckMaxAttackPacketNum == 1)
			{
				mUSER[tUserIndex].mNowAttackPacketNum++;
				if (mUSER[tUserIndex].mNowAttackPacketNum > mUSER[tUserIndex].mMaxAttackPacketNum)
				{
					return;
				}
				if (tAttackInfo.mAttackActionValue4 != mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort)
				{
					return;
				}
			}
		}
		mGAME.ProcessAttack06(tUserIndex, &tAttackInfo);
		return;
	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}
//W_PROCESS_DATA_SEND
void W_PROCESS_DATA_SEND(int tUserIndex)
{
	__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tData[0], &tPacket[5], MAX_BROADCAST_DATA_SIZE);

	mWORK.ProcessForData(tUserIndex, tSort, &tData[0]);
}
//W_DEMAND_ZONE_SERVER_INFO_2
void W_DEMAND_ZONE_SERVER_INFO_2(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	mPLAYUSER_COM.U_DUPEFIX(mUSER[tUserIndex].mPlayUserIndex, &mUSER[tUserIndex].uID[0], &mUSER[tUserIndex].mAvatarInfo, &mUSER[tUserIndex].mAuthInfo);

	int tSort;
	int nCount = 0;
	int tZoneNumber;
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tZoneNumber, &tPacket[5], 4);
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	time_t tCountSeconds;
	struct tm* tPresentTime;
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);

	if ((tZoneNumber < MIN_VALID_ZONE_NUMBER) || (tZoneNumber > MAX_VALID_ZONE_NUMBER) || (tZoneNumber == mSERVER_INFO.mServerNumber))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}


	if (mUSER[tUserIndex].mMoveItemInfo.mZoneNumber > 0)
	{
		if (tSort != 9)
		{
			::memset(&mUSER[tUserIndex].mMoveItemInfo, -1, sizeof(MOVE_ITEM_INFO));
			mPLAYUSER_COM.U_SET_MOVE_ITEM_FOR_ZONE_SEND(mUSER[tUserIndex].mPlayUserIndex, &mUSER[tUserIndex].mMoveItemInfo);
			mTRANSFER.B_DEMAND_ZONE_SERVER_INFO_2_RESULT(1, &mGAME.mZoneConnectionInfo.mIP[(tZoneNumber - 1)][0], mGAME.mZoneConnectionInfo.mPort[(tZoneNumber - 1)]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			__LogMgr()->Log("!MoveItem not match sort(%d).\n", tSort);
			return;
		}
	}

	switch (tSort)
	{
	case  2: //[GM]::[MOVEZONE]
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.MoveZoneFlag == 0) {
			return;
		}
		break;
	case  3: //[DEATH]
		break;
	case  4: //[PORTAL]
		break;
	case  5: //[NPC(MONEY)]
		break;
	case  6: //[NPC(MOVE)]
		break;
	case  7: //[RETURN]
		break;
	case  8: //[RETURN(ITEM)]
		break;
	case  9: //[MOVE(ITEM)] // ÀÌµ¿¼­
		break;
	case 10: //[NPC(ÁöÁ¸¾ËÇö)]
		break;
	case 11: //[AUTO_TO_ZONE_037]
		break;
	case 12://Zone 84
		break;
	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (1 == mUSER[tUserIndex].mAuthInfo.UZonemoveFlag) {
		mTRANSFER.B_DEMAND_ZONE_SERVER_INFO_2_RESULT(1, &mGAME.mZoneConnectionInfo.mIP[(tZoneNumber - 1)][0], mGAME.mZoneConnectionInfo.mPort[(tZoneNumber - 1)]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	if (!strcmp(mGAME.mZoneConnectionInfo.mIP[(tZoneNumber - 1)], "0.0.0.0"))
	{
		mCENTER_COM.W_ZONE_OTHER_CONNECTION_INFO(tZoneNumber);

		if (strcmp(mGAME.mZoneConnectionInfo.mIP[(tZoneNumber - 1)], "0.0.0.0") != 0)
		{
			goto RESULT;
		}

		mTRANSFER.B_DEMAND_ZONE_SERVER_INFO_2_RESULT(1, &mGAME.mZoneConnectionInfo.mIP[(tZoneNumber - 1)][0], mGAME.mZoneConnectionInfo.mPort[(tZoneNumber - 1)]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

RESULT:

	if (tZoneNumber == 200 && mGAME.mWorldInfo.CemberVadisi != 2)
	{
		mTRANSFER.B_DEMAND_ZONE_SERVER_INFO_2_RESULT(3, &mGAME.mZoneConnectionInfo.mIP[(tZoneNumber - 1)][0], mGAME.mZoneConnectionInfo.mPort[(tZoneNumber - 1)]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}


	if (tZoneNumber == 126 || tZoneNumber == 127 ||
		tZoneNumber == 128 || tZoneNumber == 129 ||
		tZoneNumber == 130 || tZoneNumber == 131 ||
		tZoneNumber == 132 || tZoneNumber == 133 ||
		tZoneNumber == 134 || tZoneNumber == 135 ||
		tZoneNumber == 136 || tZoneNumber == 137 ||
		tZoneNumber == 171 || tZoneNumber == 172 ||
		tZoneNumber == 173 || tZoneNumber == 174)
	{
		if (mUSER[tUserIndex].mAvatarInfo.ScrollOfSeekers < 1)
		{
			mTRANSFER.B_DEMAND_ZONE_SERVER_INFO_2_RESULT(10, "0.0.0.0", 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
	}



	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[0] = mSERVER_INFO.mServerNumber;
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[1] = (int)mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0];
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[2] = (int)mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[1];
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[3] = (int)mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[2];
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[4] = mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue;
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[5] = mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue;
	mPLAYUSER_COM.U_REGISTER_USER_FOR_ZONE_3_SEND(mUSER[tUserIndex].mPlayUserIndex, &mUSER[tUserIndex].uID[0], &mUSER[tUserIndex].mAvatarInfo, mUSER[tUserIndex].mEffectValue, &mUSER[tUserIndex].mAuthInfo, mUSER[tUserIndex].AnimalOn);
	if (mPLAYUSER_COM.mRecv_Result != 0)
	{
		//__LogMgr()->Log("![%s] : U_REGISTER_USER_FOR_ZONE_3_SEND failed(%d)\n"
		//		, __FUNCTION__, mPLAYUSER_COM.mRecv_Result);
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	mUSER[tUserIndex].mRegisterTime = GetTickCount();
	mUSER[tUserIndex].mMoveZoneResult = 1;

	mTRANSFER.B_DEMAND_ZONE_SERVER_INFO_2_RESULT(0, &mGAME.mZoneConnectionInfo.mIP[(tZoneNumber - 1)][0], mGAME.mZoneConnectionInfo.mPort[(tZoneNumber - 1)]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	mUSER[tUserIndex].m_bUDPActivated = false;
	mUSER[tUserIndex].m_bUDPArrivedAtClient = false;
}
//W_FAIL_MOVE_ZONE_2_SEND
void W_FAIL_MOVE_ZONE_2_SEND(int tUserIndex)
{
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (mUSER[tUserIndex].mMoveZoneResult == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	mUSER[tUserIndex].mMoveZoneResult = 0;
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[0] = mSERVER_INFO.mServerNumber;
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[1] = (int)mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0];
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[2] = (int)mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[1];
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[3] = (int)mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[2];
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[4] = mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue;
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[5] = mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue;
	mPLAYUSER_COM.U_REGISTER_USER_FOR_ZONE_2_SEND(mUSER[tUserIndex].mPlayUserIndex, &mUSER[tUserIndex].uID[0], &mUSER[tUserIndex].mAvatarInfo, mUSER[tUserIndex].mEffectValue, &mUSER[tUserIndex].mAuthInfo);
	if (mPLAYUSER_COM.mRecv_Result != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mUSER[tUserIndex].mRegisterTime = GetTickCount();

	if (mUSER[tUserIndex].mMoveItemInfo.mZoneNumber > 0)
	{
		::memset(&mUSER[tUserIndex].mMoveItemInfo, -1, sizeof(MOVE_ITEM_INFO));
		mPLAYUSER_COM.U_SET_MOVE_ITEM_FOR_ZONE_SEND(mUSER[tUserIndex].mPlayUserIndex, &mUSER[tUserIndex].mMoveItemInfo);
	}
}
//W_USE_HOTKEY_ITEM_SEND
void W_USE_HOTKEY_ITEM_SEND(int tUserIndex)
{
	__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tPage;
	int tIndex;
	CopyMemory(&tPage, &tPacket[1], 4);
	CopyMemory(&tIndex, &tPacket[5], 4);
	if ((tPage < 0) || (tPage > 2) || (tIndex < 0) || (tIndex > (MAX_HOT_KEY_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	ITEM_INFO* tITEM_INFO;
	ITEM_INFO* tITEM_INFO2;
	int tRandomValue;
	int tGainLifeValue;
	int tGainManaValue;
	int tGainPatActivityValue;
	/** 2009. 10. 26 : DarkAttack Potion add (wolf) */
	int tEffectValueState[MAX_AVATAR_EFFECT_SORT_NUM];
	/** 2009. 10. 26 : DarkAttack Potion add (wolf) */
	int tInvenPage = 0, tInvenIndex = 0, tInvenSlot = 0;
	int tValue;

	switch (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][2])
	{
	case 3:
		if ((mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 11) || (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 12) || (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 38))
		{
			mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tITEM_INFO = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][0]);
		if (tITEM_INFO == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO->iSort != 2)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tGainLifeValue = 0;
		tGainManaValue = 0;
		tGainPatActivityValue = 0;

		//nova - stack mini box 
		// Stack Items
		switch (tITEM_INFO->iIndex) {

		case 44://Diamond Box 
			tITEM_INFO2 = mITEM.Search(1244);
			if (tITEM_INFO2 == NULL) break;
			if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO2, tInvenPage, tInvenIndex))
			{
				tInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, tInvenPage);
				if (tInvenSlot != -1)
				{
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][0] = tITEM_INFO2->iIndex;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][1] = tInvenIndex % 8;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][2] = tInvenIndex / 8;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][3] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][4] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][5] = 0;
				}
			}
			else
			{
				mTRANSFER.B_ITEM_SEND(1, 0, 0, 0, 0);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}

			mTRANSFER.B_ITEM_SEND(0, tITEM_INFO2->iIndex, tInvenPage, tInvenSlot, tInvenIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1]--;
			if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] < 1)
			{
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][2] = 0;
			}

			mTRANSFER.B_USE_HOTKEY_ITEM_RECV(0, tPage, tIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		case 45://Tin
			tITEM_INFO2 = mITEM.Search(1019);
			if (tITEM_INFO2 == NULL) break;
			if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO2, tInvenPage, tInvenIndex))
			{
				tInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, tInvenPage);
				if (tInvenSlot != -1)
				{
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][0] = tITEM_INFO2->iIndex;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][1] = tInvenIndex % 8;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][2] = tInvenIndex / 8;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][3] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][4] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][5] = 0;
				}
			}
			else
			{
				mTRANSFER.B_ITEM_SEND(1, 0, 0, 0, 0);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}

			mTRANSFER.B_ITEM_SEND(0, tITEM_INFO2->iIndex, tInvenPage, tInvenSlot, tInvenIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1]--;
			if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] < 1)
			{
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][2] = 0;
			}

			mTRANSFER.B_USE_HOTKEY_ITEM_RECV(0, tPage, tIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		case 46://Dark Steel
			tITEM_INFO2 = mITEM.Search(1020);
			if (tITEM_INFO2 == NULL) break;
			if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO2, tInvenPage, tInvenIndex))
			{
				tInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, tInvenPage);
				if (tInvenSlot != -1)
				{
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][0] = tITEM_INFO2->iIndex;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][1] = tInvenIndex % 8;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][2] = tInvenIndex / 8;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][3] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][4] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][5] = 0;
				}
			}
			else
			{
				mTRANSFER.B_ITEM_SEND(1, 0, 0, 0, 0);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}

			mTRANSFER.B_ITEM_SEND(0, tITEM_INFO2->iIndex, tInvenPage, tInvenSlot, tInvenIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1]--;
			if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] < 1)
			{
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][2] = 0;
			}

			mTRANSFER.B_USE_HOTKEY_ITEM_RECV(0, tPage, tIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;

		case 47://Black Steel
			tITEM_INFO2 = mITEM.Search(1021);
			if (tITEM_INFO2 == NULL) break;
			if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO2, tInvenPage, tInvenIndex))
			{
				tInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, tInvenPage);
				if (tInvenSlot != -1)
				{
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][0] = tITEM_INFO2->iIndex;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][1] = tInvenIndex % 8;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][2] = tInvenIndex / 8;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][3] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][4] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][5] = 0;
				}
			}
			else
			{
				mTRANSFER.B_ITEM_SEND(1, 0, 0, 0, 0);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}

			mTRANSFER.B_ITEM_SEND(0, tITEM_INFO2->iIndex, tInvenPage, tInvenSlot, tInvenIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1]--;
			if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] < 1)
			{
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][2] = 0;
			}

			mTRANSFER.B_USE_HOTKEY_ITEM_RECV(0, tPage, tIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;

		case 48://Steel of Eternity
			tITEM_INFO2 = mITEM.Search(1022);
			if (tITEM_INFO2 == NULL) break;
			if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO2, tInvenPage, tInvenIndex))
			{
				tInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, tInvenPage);
				if (tInvenSlot != -1)
				{
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][0] = tITEM_INFO2->iIndex;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][1] = tInvenIndex % 8;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][2] = tInvenIndex / 8;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][3] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][4] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][5] = 0;
				}
			}
			else
			{
				mTRANSFER.B_ITEM_SEND(1, 0, 0, 0, 0);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}

			mTRANSFER.B_ITEM_SEND(0, tITEM_INFO2->iIndex, tInvenPage, tInvenSlot, tInvenIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1]--;
			if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] < 1)
			{
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][2] = 0;
			}

			mTRANSFER.B_USE_HOTKEY_ITEM_RECV(0, tPage, tIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		case 49://Gold of Eternity
			tITEM_INFO2 = mITEM.Search(1023);
			if (tITEM_INFO2 == NULL) break;
			if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO2, tInvenPage, tInvenIndex))
			{
				tInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, tInvenPage);
				if (tInvenSlot != -1)
				{
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][0] = tITEM_INFO2->iIndex;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][1] = tInvenIndex % 8;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][2] = tInvenIndex / 8;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][3] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][4] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][5] = 0;
				}
			}
			else
			{
				mTRANSFER.B_ITEM_SEND(1, 0, 0, 0, 0);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}

			mTRANSFER.B_ITEM_SEND(0, tITEM_INFO2->iIndex, tInvenPage, tInvenSlot, tInvenIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1]--;
			if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] < 1)
			{
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][2] = 0;
			}

			mTRANSFER.B_USE_HOTKEY_ITEM_RECV(0, tPage, tIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;

		case 56://Monster Treasure Box
		
			tRandomValue = rand() % 100;
			
			if (tRandomValue < 5) {
				tRandomValue = rand() % 3;
				switch (tRandomValue)
				{
				case 0:
					tValue = 601; // Mount Box
					break;
				case 1:
					tValue = 602; // Pet Box
					break;
				case 2:
					tValue = 1041;
					break;
				}

			}
			else if (tRandomValue < 10) {
	
				if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 100) {
					tValue = 1137; // 1 Stat Reset For level 1~99
				}
				else if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 112) {
					tValue = 1138; // 1 Stat Reset for level 100~112
				}
				else {
					tValue = 1139; // 1 Stat Reset for M1~M33
				}
				
			}
			else if (tRandomValue < 30) {
				tRandomValue = rand() % 5;
				switch(tRandomValue){
				case 0:
					tValue = 691; // +5 CP Ticket
					break;
				case 1:
					tValue = 692; // +10 CP Ticket
					break;
				case 2:
					tValue = 1438; // EXP Pill (s)
					break;
				case 3:
					tValue = 1439; // EXP Pill (m)
					break;
				case 4:
					tValue = 1125; // Luxury Chest
					break;
				}
			}
			else {
				tRandomValue = rand() % 7;
				switch (tRandomValue) {
				case 0:
					tValue = 1022; // SOE
					break;
				case 1:
					tValue = 1023; // GOE
					break;
				case 2:
					tValue = 1024; // PJ
					break;
				case 3:
					tValue = 1025; // RJ
					break;
				case 4:
					tValue = 506;  // HP elix
					break;
				case 5:
					tValue = 507;  // CHI elix
					break;
				case 6:
					tValue = 695;  // WF
					break;
				}
			}

			tITEM_INFO2 = mITEM.Search(tValue);

			if (tITEM_INFO2 == NULL) break;
			if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO2, tInvenPage, tInvenIndex))
			{
				tInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, tInvenPage);
				if (tInvenSlot != -1)
				{
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][0] = tITEM_INFO2->iIndex;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][1] = tInvenIndex % 8;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][2] = tInvenIndex / 8;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][3] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][4] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][5] = 0;
				}
			}
			else
			{
				mTRANSFER.B_ITEM_SEND(1, 0, 0, 0, 0);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}

			mTRANSFER.B_ITEM_SEND(0, tITEM_INFO2->iIndex, tInvenPage, tInvenSlot, tInvenIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1]--;
			if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] < 1)
			{
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][2] = 0;
			}

			mTRANSFER.B_USE_HOTKEY_ITEM_RECV(0, tPage, tIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		case 57://Purple Jade
			tITEM_INFO2 = mITEM.Search(1024);
			if (tITEM_INFO2 == NULL) break;
			if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO2, tInvenPage, tInvenIndex))
			{
				tInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, tInvenPage);
				if (tInvenSlot != -1)
				{
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][0] = tITEM_INFO2->iIndex;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][1] = tInvenIndex % 8;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][2] = tInvenIndex / 8;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][3] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][4] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][5] = 0;
				}
			}
			else
			{
				mTRANSFER.B_ITEM_SEND(1, 0, 0, 0, 0);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}

			mTRANSFER.B_ITEM_SEND(0, tITEM_INFO2->iIndex, tInvenPage, tInvenSlot, tInvenIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1]--;
			if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] < 1)
			{
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][2] = 0;
			}

			mTRANSFER.B_USE_HOTKEY_ITEM_RECV(0, tPage, tIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		case 58://Red Jade
			tITEM_INFO2 = mITEM.Search(1025);
			if (tITEM_INFO2 == NULL) break;
			if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO2, tInvenPage, tInvenIndex))
			{
				tInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, tInvenPage);
				if (tInvenSlot != -1)
				{
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][0] = tITEM_INFO2->iIndex;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][1] = tInvenIndex % 8;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][2] = tInvenIndex / 8;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][3] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][4] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tInvenPage][tInvenSlot][5] = 0;
				}
			}
			else
			{
				mTRANSFER.B_ITEM_SEND(1, 0, 0, 0, 0);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}

			mTRANSFER.B_ITEM_SEND(0, tITEM_INFO2->iIndex, tInvenPage, tInvenSlot, tInvenIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1]--;
			if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] < 1)
			{
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][2] = 0;
			}

			mTRANSFER.B_USE_HOTKEY_ITEM_RECV(0, tPage, tIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		

	







		switch (tITEM_INFO->iPotionType[0])
		{
		case 1:
			if (!mAVATAR_OBJECT[tUserIndex].mCheckPossibleEatPotion)
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			if (mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue >= mAVATAR_OBJECT[tUserIndex].GetMaxLife())
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			tGainLifeValue = tITEM_INFO->iPotionType[1];
			if ((mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue + tGainLifeValue) > mAVATAR_OBJECT[tUserIndex].GetMaxLife())
			{
				tGainLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife() - mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue;
			}
			break;
		case 2:
			if (!mAVATAR_OBJECT[tUserIndex].mCheckPossibleEatPotion)
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			if (mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue >= mAVATAR_OBJECT[tUserIndex].GetMaxLife())
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			tGainLifeValue = (int)((float)(mAVATAR_OBJECT[tUserIndex].GetMaxLife() * tITEM_INFO->iPotionType[1]) * 0.01f);
			if ((mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue + tGainLifeValue) > mAVATAR_OBJECT[tUserIndex].GetMaxLife())
			{
				tGainLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife() - mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue;
			}
			break;
		case 3:
			if (!mAVATAR_OBJECT[tUserIndex].mCheckPossibleEatPotion)
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			if (mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue >= mAVATAR_OBJECT[tUserIndex].GetMaxMana())
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			tGainManaValue = tITEM_INFO->iPotionType[1];
			if ((mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue + tGainManaValue) > mAVATAR_OBJECT[tUserIndex].GetMaxMana())
			{
				tGainManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana() - mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue;
			}
			break;
		case 4:
			if (!mAVATAR_OBJECT[tUserIndex].mCheckPossibleEatPotion)
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			if (mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue >= mAVATAR_OBJECT[tUserIndex].GetMaxMana())
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			tGainManaValue = (int)((float)(mAVATAR_OBJECT[tUserIndex].GetMaxMana() * tITEM_INFO->iPotionType[1]) * 0.01f);
			if ((mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue + tGainManaValue) > mAVATAR_OBJECT[tUserIndex].GetMaxMana())
			{
				tGainManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana() - mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue;
			}
			break;
		case 5:
			if (!mAVATAR_OBJECT[tUserIndex].mCheckPossibleEatPotion)
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			if ((mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue >= mAVATAR_OBJECT[tUserIndex].GetMaxLife()) && (mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue >= mAVATAR_OBJECT[tUserIndex].GetMaxMana()))
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			tGainLifeValue = (int)((float)(mAVATAR_OBJECT[tUserIndex].GetMaxLife() * tITEM_INFO->iPotionType[1]) * 0.01f);
			if ((mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue + tGainLifeValue) > mAVATAR_OBJECT[tUserIndex].GetMaxLife())
			{
				tGainLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife() - mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue;
			}
			tGainManaValue = (int)((float)(mAVATAR_OBJECT[tUserIndex].GetMaxMana() * tITEM_INFO->iPotionType[1]) * 0.01f);
			if ((mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue + tGainManaValue) > mAVATAR_OBJECT[tUserIndex].GetMaxMana())
			{
				tGainManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana() - mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue;
			}
			break;
		case 6:
			if (mUSER[tUserIndex].mAvatarInfo.aEquip[8][0] < 1)
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			if (mUSER[tUserIndex].mAvatarInfo.aEquip[8][1] >= MAX_PAT_ACTIVITY_SIZE)
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			tGainPatActivityValue = tITEM_INFO->iPotionType[1];
			if ((mUSER[tUserIndex].mAvatarInfo.aEquip[8][1] + tGainPatActivityValue) >= MAX_PAT_ACTIVITY_SIZE)
			{
				tGainPatActivityValue = MAX_PAT_ACTIVITY_SIZE - mUSER[tUserIndex].mAvatarInfo.aEquip[8][1];
			}
			break;
		case 9:
			break;
			/** 2009. 10. 26 : DarkAttack Potion add (wolf) */
		case 12:
		{
			if (mUSER[tUserIndex].iKindDarkAttack == 2)
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			else
			{
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1]--;
				if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] < 1)
				{
					mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][0] = 0;
					mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] = 0;
					mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][2] = 0;
				}
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(0, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

				mUSER[tUserIndex].mEffectValue[15][0] = 3;
				mUSER[tUserIndex].mEffectValue[15][1] = 40;
				mUSER[tUserIndex].iKindDarkAttack = 1;
				mAVATAR_OBJECT[tUserIndex].mDATA.aEffectValueForView[15] = mUSER[tUserIndex].mEffectValue[15][0];
				tEffectValueState[15] = 1;
				mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, mUSER[tUserIndex].mEffectValue, &tEffectValueState[0]);
				mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1);
				return;
			}
		}

		case 13:
			if (mUSER[tUserIndex].iKindDarkAttack == 1)
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			else
			{
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1]--;
				if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] < 1)
				{
					mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][0] = 0;
					mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] = 0;
					mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][2] = 0;
				}
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(0, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				mUSER[tUserIndex].mEffectValue[15][0] = 3;
				mUSER[tUserIndex].mEffectValue[15][1] = 30;
				mUSER[tUserIndex].iKindDarkAttack = 2;
				mAVATAR_OBJECT[tUserIndex].mDATA.aEffectValueForView[15] = mUSER[tUserIndex].mEffectValue[15][0];
				tEffectValueState[15] = 1;
				mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, mUSER[tUserIndex].mEffectValue, &tEffectValueState[0]);
				mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1);
				return;
			}
			return;
		case 14:///Atak Rate
		{
			mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1]--;
			if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] < 1)
			{
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][2] = 0;
			}
			mTRANSFER.B_USE_HOTKEY_ITEM_RECV(0, tPage, tIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			mUSER[tUserIndex].mEffectValue[17][0] = 25;
			mUSER[tUserIndex].mEffectValue[17][1] = 60;
			mAVATAR_OBJECT[tUserIndex].mDATA.aEffectValueForView[17] = mUSER[tUserIndex].mEffectValue[17][0];
			tEffectValueState[17] = 1;
			mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, mUSER[tUserIndex].mEffectValue, &tEffectValueState[0]);
			mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1);
			return;
		}
		case 15://Dodge
		{
			mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1]--;
			if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] < 1)
			{
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][2] = 0;
			}
			mTRANSFER.B_USE_HOTKEY_ITEM_RECV(0, tPage, tIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			mUSER[tUserIndex].mEffectValue[18][0] = 25;
			mUSER[tUserIndex].mEffectValue[18][1] = 60;
			mAVATAR_OBJECT[tUserIndex].mDATA.aEffectValueForView[18] = mUSER[tUserIndex].mEffectValue[18][0];
			tEffectValueState[18] = 1;
			mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, mUSER[tUserIndex].mEffectValue, &tEffectValueState[0]);
			mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1);
			return;
		}
		case 16://100100000 bine can
			if (mUSER[tUserIndex].mAvatarInfo.aAnimalIndex < 10)
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			if (mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] / 1000000 == 100)
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] += 50000000;
			if (mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] / 1000000 > 100)
			{
				mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] -= (((mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] / 1000000) - 100) * 1000000);
			}
			mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1]--;
			if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] < 1)
			{
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][2] = 0;
			}
			mTRANSFER.B_USE_HOTKEY_ITEM_RECV(0, tPage, tIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(71, mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;


		default:
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1]--;
		if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] < 1)
		{
			mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][2] = 0;
		}
		mTRANSFER.B_USE_HOTKEY_ITEM_RECV(0, tPage, tIndex);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		if (tGainLifeValue > 0)
		{
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue += tGainLifeValue;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(10, mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		if (tGainManaValue > 0)
		{
			mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue += tGainManaValue;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(11, mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		if (tGainPatActivityValue > 0)
		{
			mUSER[tUserIndex].mAvatarInfo.aEquip[8][1] += tGainPatActivityValue;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(12, mUSER[tUserIndex].mAvatarInfo.aEquip[8][1]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		return;
	case 13:
	{
		if (mUSER[tUserIndex].iKindDarkAttack == 1)
		{
			mTRANSFER.B_USE_HOTKEY_ITEM_RECV(2, tPage, tIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			//__LogMgr()->Log("![%s] : %d \n",__FUNCTION__,__LINE__);
			return;
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1]--;
			if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] < 1)
			{
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][2] = 0;
			}
			mTRANSFER.B_USE_HOTKEY_ITEM_RECV(4, tPage, tIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);


			mUSER[tUserIndex].mEffectValue[15][0] = 3;
			mUSER[tUserIndex].mEffectValue[15][1] = 60;
			mUSER[tUserIndex].iKindDarkAttack = 2;
			mAVATAR_OBJECT[tUserIndex].mDATA.aEffectValueForView[15] = mUSER[tUserIndex].mEffectValue[15][0];
			tEffectValueState[15] = 1;
			mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, mUSER[tUserIndex].mEffectValue, &tEffectValueState[0]);
			mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1);
		}
	}
	return;

	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}

//W_USE_INVENTORY_ITEM_SEND
void W_USE_INVENTORY_ITEM_SEND(int tUserIndex)
{
	__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tPage;
	int tIndex;
	int tValue;


	CopyMemory(&tPage, &tPacket[1], 4);
	CopyMemory(&tIndex, &tPacket[5], 4);
	CopyMemory(&tValue, &tPacket[9], 4);
	// 2009.11.23 : ±è¼º¼ö :µð¹ö±ëÀ» À§ÇÑ ³Ö¾î¶² ÄÚµå	
	// __LogMgr()->Log("![INFO] tPage = %d  , tIndex = %d , tValue = %d \n",tPage ,tIndex ,tValue  );

	if ((tPage < 0) || (tPage > 1) || (tIndex < 0) || (tIndex > (MAX_INVENTORY_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	BYTE tData[MAX_BROADCAST_DATA_SIZE];
	int index01;
	int index02;
	ITEM_INFO* tITEM_INFO;
	ITEM_INFO* tITEM_INFO1;
	SKILL_INFO* tSKILL_INFO;
	int tEquipIndex;
	int tEquip[4];
	int tEquipSocket[3];
	int tItemLLevel;
	int tItemHLevel;
	int tTribeItemList[9];
	int tRandomValue;
	int tItemType;
	int tItemSort;
	int tSearchNum;
	int tMoney;
	int CpTowerNum;
	int CpTowerMapNum;
	int CpToverVlue;
	const int tItemListNum = 5;
	int iPage = 0;
	int iInvenSlot = 0;
	int iInvenPage = 0;
	int iInvenIndex = 0;
	int tItemCount = 0;
	int tPageList[tItemListNum];
	int tInvenSlotList[tItemListNum];
	int tInvenIndexList[tItemListNum];
	int tItemList[tItemListNum][2];
	//int tItemCountList[tItemListNum];ü
	int randomMount;
	int tItemValueList[tItemListNum];
	int tItemRecognitionList[tItemListNum];
	int temp_AddTime = 0;
	int tDumyPageList[tItemListNum];
	int tDumyInvenSlotList[tItemListNum];
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	time_t tCountSeconds;
	struct tm* tPresentTime;
	char cDate[100];
	unsigned int iDate = 0;
	unsigned int tZone84Date = 0;
	int tProtectIS = 0;
	int tItemNumber = 0; // »ç¿ëÇÒ ¾ÆÀÌÅÛ ¹øÈ£ ÀúÀå¿ë º¯¼ö.
	int tAddExp;

	int iInvenPage1[8];
	int iInvenIndex1[8];
	int iInvenSlot1[8];
	int SetBonus = 0;

	int title = 0;
	int CpValue[14];
	int AddCp = 0;
	CpValue[0] = 800;
	CpValue[1] = 1700;
	CpValue[2] = 2500;
	CpValue[3] = 3400;
	CpValue[4] = 4200;
	CpValue[5] = 5100;
	CpValue[6] = 5900;
	CpValue[7] = 6800;
	CpValue[8] = 7600;
	CpValue[9] = 8500;
	CpValue[10] = 9300;
	CpValue[11] = 10000;
	CpValue[12] = 10000;
	CpValue[13] = 10000;

	int petboxadet;
	int capeboxadet;
	int petboxadetinialbi;
	int oran = 0;
	int bonusPointsToAdd =0;
	int enchant = 0;
	int cs = 0;
	int faction;
	int Cash;
	int BonusCash;

	ZeroMemory(tBroadcastInfoData, sizeof(tBroadcastInfoData));

	if (tPage == 1)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	tITEM_INFO = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0]);
	if (tITEM_INFO == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	tItemNumber = tITEM_INFO->iIndex;

	switch (tITEM_INFO->iSort)
	{
	case  5: //[¹«°øºñ±Þ]
		if (tITEM_INFO->iEquipInfo[0] != 1)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe != (tITEM_INFO->iEquipInfo[0] - 2))
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}

		if ((mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2) < (tITEM_INFO->iLevelLimit + tITEM_INFO->iMartialLevelLimit))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_SKILL_SLOT_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] == tITEM_INFO->iGainSkillNumber)
			{
				break;
			}
		}
		if (index01 < MAX_SKILL_SLOT_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tSKILL_INFO = mSKILL.Search(tITEM_INFO->iGainSkillNumber);
		if (tSKILL_INFO == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aSkillPoint < tSKILL_INFO->sLearnSkillPoint)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (tSKILL_INFO->sType)
		{
		case 1:
			for (index01 = 0; index01 < 10; index01++)
			{
				if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] < 1)
				{
					break;
				}
			}
			if (index01 == 10)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 2:
			for (index01 = 20; index01 < 30; index01++)
			{
				if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] < 1)
				{
					break;
				}
			}
			if (index01 == 30)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 3:
			for (index01 = 10; index01 < 20; index01++)
			{
				if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] < 1)
				{
					break;
				}
			}
			if (index01 == 20)
			{
				for (index01 = 30; index01 < 40; index01++)
				{
					if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] < 1)
					{
						break;
					}
				}
				if (index01 == 40)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
			break;
		case 4:
			for (index01 = 10; index01 < 20; index01++)
			{
				if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] < 1)
				{
					break;
				}
			}
			if (index01 == 20)
			{
				for (index01 = 30; index01 < 40; index01++)
				{
					if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] < 1)
					{
						break;
					}
				}
				if (index01 == 40)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
			break;
		default:
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aSkillPoint -= tSKILL_INFO->sLearnSkillPoint;
		mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] = tSKILL_INFO->sIndex;
		mUSER[tUserIndex].mAvatarInfo.aSkill[index01][1] = tSKILL_INFO->sLearnSkillPoint;
		//mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage][tIndex][2] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case  6: //[Àå½Ä]
	case  7: //[¸ñ°ÉÀÌ]
	case  8: //[¸ÁÅä]
	case  9: //[º¹Àå]
	case 10: //[Àå°©]
	case 11: //[¹ÝÁö]
	case 12: //[½Å¹ß]
	case 13: //[°Ë]
	case 14: //[µµ]
	case 15: //[Åõ¿Á]
	case 16: //[ÅÂµµ]
	case 17: //[½Ö±Ø]
	case 18: //[ºñÆÄ]
	case 19: //[¹Úµµ]
	case 20: //[ÀåÃ¢]
	case 21: //[±Ý°­Àú]
	case 22: //[¿µ¹°]
	case 28:
	case 29:
	case 30:
	case 31:
	case 32:
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort != 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (!mUTIL.CheckPossibleEquipItem(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, -1, (mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tEquipIndex = tITEM_INFO->iEquipInfo[1] - 2;
		if ((tEquipIndex < 0) || (tEquipIndex > (MAX_EQUIP_SLOT_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tEquip[0] = mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][0];
		tEquip[1] = mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][1];
		tEquip[2] = mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][2];
		tEquip[3] = mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][3];
		tEquipSocket[0] = mUSER[tUserIndex].mAvatarInfo.EquipSocket[tEquipIndex][0];
		tEquipSocket[1] = mUSER[tUserIndex].mAvatarInfo.EquipSocket[tEquipIndex][1];
		tEquipSocket[2] = mUSER[tUserIndex].mAvatarInfo.EquipSocket[tEquipIndex][2];
		mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][0] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0];
		mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3];
		mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4];
		mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][3] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5];
		mUSER[tUserIndex].mAvatarInfo.EquipSocket[tEquipIndex][0] = mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage][tIndex][0];
		mUSER[tUserIndex].mAvatarInfo.EquipSocket[tEquipIndex][1] = mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage][tIndex][1];
		mUSER[tUserIndex].mAvatarInfo.EquipSocket[tEquipIndex][2] = mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage][tIndex][2];
		mAVATAR_OBJECT[tUserIndex].mDATA.aEquipForView[tEquipIndex][0] = mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][0];
		mAVATAR_OBJECT[tUserIndex].mDATA.aEquipForView[tEquipIndex][1] = mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tEquip[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = tEquip[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = tEquip[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = tEquip[3];
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage][tIndex][0] = tEquipSocket[0];
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage][tIndex][1] = tEquipSocket[1];
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage][tIndex][2] = tEquipSocket[2];
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aType = (unsigned char)mAVATAR_OBJECT[tUserIndex].GetWeaponClass() * 2;
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aFrame = 0.0f;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue > mAVATAR_OBJECT[tUserIndex].GetMaxLife())
		{
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue > mAVATAR_OBJECT[tUserIndex].GetMaxMana())
		{
			mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
		}
		if (tEquipIndex == 7)
		{
			mAVATAR_OBJECT[tUserIndex].ProcessForDeleteEffectValue();
		}

		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 25:
		return;
	case 26:
		for (index01 = 0; index01 < 10; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.Bottle[index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < 10)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < 10; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.Bottle[index01] == 0)
			{
				break;
			}
		}
		if (index01 == 10)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.Bottle[index01] = tITEM_INFO->iIndex;
		mUSER[tUserIndex].mAvatarInfo.BottlePrice[index01] = 30;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, index01);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	switch (tITEM_INFO->iIndex)
	{
	

		//nova - all boxes
	case 601://%5 mount box.
		tRandomValue = rand() % 100;
		//if (tRandomValue < 2) {
		//	tRandomValue = rand() % 8;

		//	// 10% mounts
		//	switch (tRandomValue)
		//	{
		//	case 0:
		//		tValue = 1304; // tiger
		//		break;
		//	case 1:
		//		tValue = 1314;  // bear
		//		break;
		//	case 2: 
		//		tValue = 1318; // ferret
		//		break;
		//	case 3:
		//		tValue = 1321; // bull
		//		break;
		//	case 4:
		//		tValue = 1305; // boar
		//		break;
		//	case 5:
		//		tValue = 1306; // Stag
		//		break;
		//	case 6:
		//		tValue = 1324; // wolf
		//		break;
		//	case 7:
		//		tValue = 1327; // Haechi
		//		break;
		//	}
		//}
		//else 
		   if( tRandomValue < 8) {
			tRandomValue = rand() % 8;
			switch (tRandomValue)
			{
			case 0:
				tValue = 1301; // White Tiger (5%)
				break;
			case 1:
				tValue = 1302; // Stalking Boar (5%)
				break;
			case 2:
				tValue = 1303; // Heaven's Stag (5%)
				break;
			case 3:
				tValue = 1313; // Feral Bear (5%)
				break;
			case 4:
				tValue = 1317; // Ferocious Ferret (5%)
				break;
			case 5:
				tValue = 1320; // Angry Bull (5%)
				break;
			case 6:
				tValue = 1323; // Snow Wolf (5%)
				break;
			case 7:
				tValue = 1326; // Gilden HaeChi (5%)
				break;
			}

		}
		else {
			tRandomValue = rand() % 9;
			switch (tRandomValue) {
				case 0:
					tValue = 1022; // SOE
					break;
				case 1:
					tValue = 1023; // GOE
					break;
				case 2:
					tValue = 1024; // PJ
					break;
				case 3:
					tValue = 1025; // RJ
					break;
				case 4:
					tValue = 506;  // HP elix
					break;
				case 5:
					tValue = 507;  // CHI elix
					break;
				case 6:
					tValue = 508;  // DEX elix 
					break;
				case 7:
					tValue = 509;  // STR elix
					break;
				case 8:
					tValue = 695;  // WF
					break;
			}
		}
		
			tITEM_INFO1 = mITEM.Search(tValue);
			//Box Notice
			if ((tValue >= 1300) && (tValue <= 1330)) {

				string test = "";
				tRandomValue = rand() % 5;
				switch (tRandomValue) {
				case 0:
					test = "I can't belive!I just found ";
					break;
				case 1:
					test = "OMG! So lucky today!Look at this ";
					break;
				case 2:
					test = "WOOOO! Guess who won ";
					break;
				case 3:
					test = "This is my lucky day noobs -> ";
					break;
				case 4:
					test = "Bumshakalaka! I just earned ";
					break;
					
				}
				sprintf((char*)&tData[0], "[%s] %s '%s'", &mUSER[tUserIndex].mAvatarInfo.aName[0], test.c_str(), tITEM_INFO1->iName);
				mRELAY_COM.U_DEMAND_BROADCAST_DATA(102, &tData[0]);
			}
		
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	

	case 512://Event Box
	

		tRandomValue = rand() % 5;
		switch (tRandomValue) {
		case 0:
			tValue = 602;
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		}

		tITEM_INFO1 = mITEM.Search(tValue);
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);

		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

		case 18005:

			Cash = 500;
			BonusCash = 500;
			mTRANSFER.B_GET_CASH_SIZE_RECV(Cash, BonusCash);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;

		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;

		//Lotus Alliance Pet Box
		case 602://Pet Box
			tRandomValue = rand() % 1000;

			// M30 Pet
			if (tRandomValue < 2) {
				tValue = 1016; // LEVIATAN
			}
			// M15 Pet
			else if (tRandomValue < 10) {
				tRandomValue = rand() % 4;
				switch (tRandomValue) {
				case 0:
					tValue = 1012; // Falch
					break;
				case 1:
					tValue = 1013; // Bird
					break;
				case 2:
					tValue = 1014; // Drake
					break;
				case 3:
					tValue = 1015; // Pheonix
					break;
				}
			}
			// M1 PET
			else if (tRandomValue < 50) {
				tRandomValue = rand() % 6;
				switch (tRandomValue) {
					case 0:
						tValue = 1006; // Beetle
					break;
					case 1:
						tValue = 1007; // Owl
						break;
					case 2: 
						tValue = 1008; //Bat
						break;
					case 3:
						tValue = 1009; // Tortoise
						break;
					case 4:
						tValue = 1010; // Unicorn
						break;
					case 5:
						tValue = 1011; // Hellion
						break;	

				}
			}
			// Level 1 Pet
			else if (tRandomValue < 150) {
				tRandomValue = rand() % 4;
				switch (tRandomValue) {
				case 0:
					tValue = 1002; // Damage
					break;
				case 1:
					tValue = 1003; // Def
					break;
				case 2:
					tValue = 1004; // Health
					break;
				case 3:
					tValue = 1005; // Chi
					break;
				}
			}
			else  {
				
				tRandomValue = rand() % 9;
				switch (tRandomValue) {
				case 0:
					tValue = 1022; // SOE
					break;
				case 1:
					tValue = 1023; // GOE
					break;
				case 2:
					tValue = 1024; // PJ
					break;
				case 3:
					tValue = 1025; // RJ
					break;
				case 4:
					tValue = 506; // HP elix
					break;
				case 5:
					tValue = 507; // CHI elix
					break;
				case 6:
					tValue = 508; // DEX elix 
					break;
				case 7:
					tValue = 509; // STR elix
					break;
				case 8:
					tValue = 695; // WF
				break;
				}
			}

			tITEM_INFO1 = mITEM.Search(tValue);
		//Box Notice
		if ((tValue >= 1002) && (tValue <= 1016)) {
			
			string test = "";
			tRandomValue = rand() % 5;
			switch (tRandomValue) {
			case 0:
				test = "AWESOME! Another pet ! ";
				break;
			case 1:
				test = "That's the sound of the ";
				break;
			case 2:
				test = "This is my new friend ";
				break;
			case 3:
				test = "A new pet appeard ";
				break;
			case 4:
				test = "This box was really lucky! ";
				break;

			}
			sprintf((char*)&tData[0], "[%s] %s '%s'", &mUSER[tUserIndex].mAvatarInfo.aName[0], test.c_str(), tITEM_INFO1->iName);
			mRELAY_COM.U_DEMAND_BROADCAST_DATA(102, &tData[0]);
		}
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);

		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;


	case 585://grey fish
		tRandomValue = rand() % 100;
		if (tRandomValue < 20)
		{
			tValue = 1023;
		}
		else if (tRandomValue < 40)
		{
			tValue = 1148; 
		}
		else if (tRandomValue < 60)
		{
			tValue = 1850;
		}
		else if (tRandomValue < 80)
		{
			tValue = 1372;
		}
		else
		{
			tValue = 1375;
		}

		tITEM_INFO1 = mITEM.Search(tValue);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 649: //[Instant 1% Exp Pill]
	
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1)
		{
			tValue = ((mLEVEL.ReturnLevelFactor2(mUSER[tUserIndex].mAvatarInfo.aLevel1) - mLEVEL.ReturnLevelFactor1(mUSER[tUserIndex].mAvatarInfo.aLevel1)) * 0.01f);
			if ((mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 + tValue) > mLEVEL.ReturnLevelFactor2(mUSER[tUserIndex].mAvatarInfo.aLevel1))
			{
				tValue = mLEVEL.ReturnLevelFactor2(mUSER[tUserIndex].mAvatarInfo.aLevel1) - mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1;
			}
			mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 += tValue;
			GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(13, mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		else if(mUSER[tUserIndex].mAvatarInfo.aLevel2 > 0)
		{
			tValue = (mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel1) * 0.01f);
			if ((mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 + tValue) > mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
			{
				tValue = mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2) - mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2;
			}
			mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 += tValue;
			GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(24, mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
	case 650: //[Instant 3% Exp Pill]
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1)
		{
			tValue = ((mLEVEL.ReturnLevelFactor2(mUSER[tUserIndex].mAvatarInfo.aLevel1) - mLEVEL.ReturnLevelFactor1(mUSER[tUserIndex].mAvatarInfo.aLevel1)) * 0.03f);
			if ((mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 + tValue) > mLEVEL.ReturnLevelFactor2(mUSER[tUserIndex].mAvatarInfo.aLevel1))
			{
				tValue = mLEVEL.ReturnLevelFactor2(mUSER[tUserIndex].mAvatarInfo.aLevel1) - mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1;
			}
			mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 += tValue;
			GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(13, mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		else
		{
			tValue = (mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2) * 0.03f);
			if ((mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 + tValue) > mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
			{
				tValue = mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2) - mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2;
			}
			mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 += tValue;
			GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(24, mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
	case 1108: //[Protection Scroll]
		mUSER[tUserIndex].mAvatarInfo.ProtectionScroll += 20 ;
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 584://purple fish
		tRandomValue = rand() % 100;
		if (tRandomValue < 25)
		{
			tValue = 1073; 
		}
		else if (tRandomValue < 50)
		{
			tValue = 1166;
		}
		else if (tRandomValue < 75)
		{
			tValue = 1448;
		}
		else 
		{
			tValue = 1118;
		}

		//Box Notice
		if (tValue == 956) {
			sprintf((char*)&tData[0], "[Amethyst Koi] %s gained 'Bloody Double Blades'", &mUSER[tUserIndex].mAvatarInfo.aName[0], tValue);
			mRELAY_COM.U_DEMAND_BROADCAST_DATA(102, &tData[0]);
		}

		tITEM_INFO1 = mITEM.Search(tValue);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1035: //[Lucky Ticket]
#ifdef __GOD__
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1)
		{
#endif
			tItemLLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 - 5;
			if (tItemLLevel < 1)
			{
				tItemLLevel = 1;
			}
			tItemHLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + 5;
			if (tItemHLevel > MAX_LIMIT_LEVEL_NUM)
			{
				tItemHLevel = MAX_LIMIT_LEVEL_NUM;
			}
#ifdef __GOD__
		}
		else
		{
			tItemLLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2;
			tItemHLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2;
		}

#endif
		switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
		{
		case 0:
			tTribeItemList[0] = 7;
			tTribeItemList[1] = 8;
			tTribeItemList[2] = 9;
			tTribeItemList[3] = 10;
			tTribeItemList[4] = 11;
			tTribeItemList[5] = 12;
			tTribeItemList[6] = 13;
			tTribeItemList[7] = 14;
			tTribeItemList[8] = 15;
			break;
		case 1:
			tTribeItemList[0] = 7;
			tTribeItemList[1] = 8;
			tTribeItemList[2] = 9;
			tTribeItemList[3] = 10;
			tTribeItemList[4] = 11;
			tTribeItemList[5] = 12;
			tTribeItemList[6] = 16;
			tTribeItemList[7] = 17;
			tTribeItemList[8] = 18;
			break;
		case 2:
			tTribeItemList[0] = 7;
			tTribeItemList[1] = 8;
			tTribeItemList[2] = 9;
			tTribeItemList[3] = 10;
			tTribeItemList[4] = 11;
			tTribeItemList[5] = 12;
			tTribeItemList[6] = 19;
			tTribeItemList[7] = 20;
			tTribeItemList[8] = 21;
			break;
		}
		tRandomValue = rand() % 10000;
		if (tRandomValue < 1)
		{
			tItemType = 4;
		}
		else if (tRandomValue < 300)
		{
			tItemType = 3;
		}
		else if (tRandomValue < 9000)
		{
			tItemType = 2;
		}
		else
		{
			tItemType = 1;
		}
		tRandomValue = rand();
		tItemSort = tTribeItemList[tRandomValue % 9];
		tSearchNum = 0;
		while (tSearchNum < 10)
		{
			tRandomValue = rand();
			tITEM_INFO = mITEM.Return((tItemLLevel + (tRandomValue % (tItemHLevel - tItemLLevel + 1))), tItemType, tItemSort);
			if (tITEM_INFO)
			{
				if (((tITEM_INFO->iEquipInfo[0] == 1) || ((tITEM_INFO->iEquipInfo[0] - 2) == mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)) && (tITEM_INFO->iCheckMonsterDrop == 2))
				{
					break;
				}
				tITEM_INFO = NULL;
				tSearchNum++;
			}
			else
			{
				tSearchNum++;
			}
		}
		if (tITEM_INFO == NULL)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tValue = tITEM_INFO->iIndex;
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		//mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], tValue, 0, 0, 100000001 );
		if (tITEM_INFO->iType == 4)
		{
			//mGAMELOG.GL_607_GAIN_SIN_ITEM( tUserIndex, 1, tITEM_INFO->iIndex, 0, 0, 100000001 );
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 100000001;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1036: //[Big Lucky Ticket]
#ifdef __GOD__
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1)
		{
#endif
			tItemLLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 - 5;
			if (tItemLLevel < 1)
			{
				tItemLLevel = 1;
			}
			tItemHLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + 5;
			if (tItemHLevel > MAX_LIMIT_LEVEL_NUM)
			{
				tItemHLevel = MAX_LIMIT_LEVEL_NUM;
			}
#ifdef __GOD__
		}
		else
		{
			tItemLLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2;
			tItemHLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2;
		}

#endif

		switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
		{
		case 0:
			tTribeItemList[0] = 7;
			tTribeItemList[1] = 8;
			tTribeItemList[2] = 9;
			tTribeItemList[3] = 10;
			tTribeItemList[4] = 11;
			tTribeItemList[5] = 12;
			tTribeItemList[6] = 13;
			tTribeItemList[7] = 14;
			tTribeItemList[8] = 15;
			break;
		case 1:
			tTribeItemList[0] = 7;
			tTribeItemList[1] = 8;
			tTribeItemList[2] = 9;
			tTribeItemList[3] = 10;
			tTribeItemList[4] = 11;
			tTribeItemList[5] = 12;
			tTribeItemList[6] = 16;
			tTribeItemList[7] = 17;
			tTribeItemList[8] = 18;
			break;
		case 2:
			tTribeItemList[0] = 7;
			tTribeItemList[1] = 8;
			tTribeItemList[2] = 9;
			tTribeItemList[3] = 10;
			tTribeItemList[4] = 11;
			tTribeItemList[5] = 12;
			tTribeItemList[6] = 19;
			tTribeItemList[7] = 20;
			tTribeItemList[8] = 21;
			break;
		}
		tRandomValue = rand() % 10000;
		if (tRandomValue < 1)
		{
			tItemType = 4;
		}
		else if (tRandomValue < 400)
		{
			tItemType = 3;
		}
		else if (tRandomValue < 9000)
		{
			tItemType = 2;
		}
		else
		{
			tItemType = 1;
		}
		tRandomValue = rand();
		tItemSort = tTribeItemList[(tRandomValue % 9)];
		tSearchNum = 0;
		while (tSearchNum < 10)
		{
			tRandomValue = rand();
			tITEM_INFO = mITEM.Return((tItemLLevel + (tRandomValue % (tItemHLevel - tItemLLevel + 1))), tItemType, tItemSort);
			if (tITEM_INFO)
			{
				if (((tITEM_INFO->iEquipInfo[0] == 1) || ((tITEM_INFO->iEquipInfo[0] - 2) == mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)) && (tITEM_INFO->iCheckMonsterDrop == 2))
				{
					break;
				}
				tITEM_INFO = NULL;
				tSearchNum++;
			}
			else
			{
				tSearchNum++;
			}
		}
		if (tITEM_INFO == NULL)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tValue = tITEM_INFO->iIndex;
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		//mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], tValue, 0, 0, 100000002 );
		if (tITEM_INFO->iType == 4)
		{
			//mGAMELOG.GL_607_GAIN_SIN_ITEM( tUserIndex, 1, tITEM_INFO->iIndex, 0, 0, 100000002 );
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 100000002;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1037: //[God Lucky Ticket]
#ifdef __GOD__
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1)
		{
#endif
			tItemLLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 - 5;
			if (tItemLLevel < 1)
			{
				tItemLLevel = 1;
			}
			tItemHLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + 5;
			if (tItemHLevel > MAX_LIMIT_LEVEL_NUM)
			{
				tItemHLevel = MAX_LIMIT_LEVEL_NUM;
			}
#ifdef __GOD__
		}
		else
		{
			tItemLLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2;
			tItemHLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2;
		}

#endif
		switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
		{
		case 0:
			tTribeItemList[0] = 7;
			tTribeItemList[1] = 8;
			tTribeItemList[2] = 9;
			tTribeItemList[3] = 10;
			tTribeItemList[4] = 11;
			tTribeItemList[5] = 12;
			tTribeItemList[6] = 13;
			tTribeItemList[7] = 14;
			tTribeItemList[8] = 15;
			break;
		case 1:
			tTribeItemList[0] = 7;
			tTribeItemList[1] = 8;
			tTribeItemList[2] = 9;
			tTribeItemList[3] = 10;
			tTribeItemList[4] = 11;
			tTribeItemList[5] = 12;
			tTribeItemList[6] = 16;
			tTribeItemList[7] = 17;
			tTribeItemList[8] = 18;
			break;
		case 2:
			tTribeItemList[0] = 7;
			tTribeItemList[1] = 8;
			tTribeItemList[2] = 9;
			tTribeItemList[3] = 10;
			tTribeItemList[4] = 11;
			tTribeItemList[5] = 12;
			tTribeItemList[6] = 19;
			tTribeItemList[7] = 20;
			tTribeItemList[8] = 21;
			break;
		}
		tRandomValue = rand() % 10000;
		if (tRandomValue < 1)
		{
			tItemType = 4;
		}
		else if (tRandomValue < 500)
		{
			tItemType = 3;
		}
		else if (tRandomValue < 9000)
		{
			tItemType = 2;
		}
		else
		{
			tItemType = 1;
		}
		tRandomValue = rand();
		tItemSort = tTribeItemList[(tRandomValue % 9)];
		tSearchNum = 0;
		while (tSearchNum < 10)
		{
			tRandomValue = rand();
			tITEM_INFO = mITEM.Return((tItemLLevel + (tRandomValue % (tItemHLevel - tItemLLevel + 1))), tItemType, tItemSort);
			if (tITEM_INFO)
			{
				if (((tITEM_INFO->iEquipInfo[0] == 1) || ((tITEM_INFO->iEquipInfo[0] - 2) == mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)) && (tITEM_INFO->iCheckMonsterDrop == 2))
				{
					break;
				}
				tITEM_INFO = NULL;
				tSearchNum++;
			}
			else
			{
				tSearchNum++;
			}
		}
		if (tITEM_INFO == NULL)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tValue = tITEM_INFO->iIndex;
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		//mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], tValue, 0, 0, 100000003 );
		if (tITEM_INFO->iType == 4)
		{
			//mGAMELOG.GL_607_GAIN_SIN_ITEM( tUserIndex, 1, tITEM_INFO->iIndex, 0, 0, 100000003 );
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 100000003;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1850://nova - Blood Point Box. It gives 1 to 5 blood points.
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.BloodStained, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		mUSER[tUserIndex].mAvatarInfo.BloodStained += 1 + rand() % 5;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(121, mUSER[tUserIndex].mAvatarInfo.BloodStained);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 635://%15 mount box.
		tRandomValue = rand() % 100;
		if (tRandomValue < 12)
		{
			tValue = 1307;//Red Tiger
		}
		else if (tRandomValue < 24)
		{
			tValue = 1315;//War Bear
		}
		else if (tRandomValue < 36)
		{
			tValue = 1319;//Doom Ferret
		}
		else if (tRandomValue < 48)
		{
			tValue = 1322;//Demon Bull
		}
		else if (tRandomValue < 60)
		{
			tValue = 1308;//Reverent Boar
		}
		else if (tRandomValue < 72)
		{
			tValue = 1309;// god stag 
		}
		else if (tRandomValue < 86)
		{
			tValue = 1325;//15 wolf
		}
		else
		{
			tValue = 1328;// Black HaeChi
		}

		tITEM_INFO1 = mITEM.Search(tValue);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 586://Ice king box
		tRandomValue = rand() % 100;
		if (tRandomValue < 10) {
			tValue = 1073;
		}
		else if (tRandomValue < 20) {
			tValue = 1074; 
		}
		else if (tRandomValue < 30) {
			tValue = 1499; 
		}
		else if (tRandomValue < 40) {
			tValue = 1447;
		}
		else if (tRandomValue < 50) {
			tValue = 1185; 
		}
		else if (tRandomValue < 60) {
			tValue = 984; 
		}
		else if (tRandomValue < 70) {
			tValue = 828; 
		}
		else if (tRandomValue < 80) {
			tValue = 1024; 
		}
		else if (tRandomValue < 90) {
			tValue = 635; 
		}
		else {
			tValue = 1401; //ultimate cape
		}
		//nova - box notices
		//Box Notice
		if (tValue == 1401) {
			sprintf((char*)&tData[0], "[Ice King Box] %s gained 'Ultimate Cloak'", &mUSER[tUserIndex].mAvatarInfo.aName[0], tValue);
			mRELAY_COM.U_DEMAND_BROADCAST_DATA(102, &tData[0]);
		}

		tITEM_INFO1 = mITEM.Search(tValue);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 828:
	case 837:
		mUSER[tUserIndex].mAvatarInfo.KesinKabuk += 1;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.ProtectionCharm, 5, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 566: //Fanction Notice Scroll
		mUSER[tUserIndex].mAvatarInfo.FanctionNoticeScroll += 5;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.ProtectionCharm, 5, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1132: //BuffDurationPill
		mUSER[tUserIndex].mAvatarInfo.BuffDurationPill += 60;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.ProtectionCharm, 5, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
		// Search Ticket
	case 1168:
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.aSearch, 7);
		if (tValue == -1)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aSearch = tValue;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aSearch, tValue, 0, "", 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1169:
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.aSearch, 15);
		if (tValue == -1)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aSearch = tValue;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aSearch, tValue, 0, "", 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1170:
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.aSearch, 30);
		if (tValue == -1)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aSearch = tValue;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aSearch, tValue, 0, "", 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 577:
		mUSER[tUserIndex].mAvatarInfo.RebirtHall += 30;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.RebirtHall, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 620:
		mUSER[tUserIndex].mAvatarInfo.BurstPill += 1;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.BurstPill, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 301:
	case 302:
	case 303:
	case 304:
	case 305:
	case 306:
	case 307:
	case 308:
	case 309:
	case 310:
	case 311:
	case 312:
	case 313:
	case 314:
	case 315:
	case 316:
	case 317:
	case 318:
	case 319:
	case 320:
	case 321:
	case 322:
	case 323:
	case 324:
	case 325:
	case 326:
	case 327:
	case 328:
	case 329:
	case 330:
	case 331:
	case 332:
	case 333:
	case 334:
	case 335:
	case 336:
	case 337:
	case 338:
	case 339:
	case 340:
	case 341:
	case 342:
	case 343:
	case 344:
	case 345:
	case 346:
	case 347:
	case 348:
	case 349:
	case 350:
	case 351:
	case 352:
	case 353:
	case 354:
	case 355:
	case 356:
	case 357:
	case 358:
	case 359:
	case 360:
	case 361:
	case 362:
	case 363:
	case 364:
	case 365:
	case 366:
	case 367:
	case 368:
	case 369:
	case 370:
	case 371:
	case 372:
	case 373:
	case 374:
	case 375:
	case 376:
	case 377:
	case 378:
	case 379:
	case 380:
	case 381:
	case 382:
	case 383:
	case 384:
	case 385:
	case 386:
	case 387:
	case 394:
	case 395:
	case 396:
	case 397:
	case 398:
	case 399:
	case 1891:
	case 1892:
	case 1893:
	case 2146:
	case 2147:
	case 2148:
	case 7003:
	case 7004:
	case 7005:
	case 7006:
	case 7007:
	case 18028:
	case 18029:
	case 18030:
	case 18031:
	case 18032:
	case 18033:
	case 18034:
	case 18035:
	case 18036:
	case 18037:
	case 18038:
	case 18039:
	case 18040:
	case 18041:
	case 18042:
	case 17140:
	case 17141:
	case 17142:
	case 17143:
	case 17144:
	case 17145:
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.Costume[index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.Costume[index01] == 0)
			{
				break;
			}
		}
		if (index01 == MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = index01;
		mUSER[tUserIndex].mAvatarInfo.Costume[tValue] = tITEM_INFO->iIndex;
		tITEM_INFO1 = mITEM.Search(tValue);
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1301:
	case 1302:
	case 1303:
	case 1304:
	case 1305:
	case 1306:
	case 1307:
	case 1308:
	case 1309:
	case 1313:
	case 1314:
	case 1315:
	case 1316:
	case 1317:
	case 1318:
	case 1319:
	case 1320:
	case 1321:
	case 1322:
	case 1323:
	case 1324:
	case 1325:
	case 1326:
	case 1327:
	case 1328:
	case 1329:
	case 1330:
	case 1331:
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 0)
			{
				break;
			}
		}
		if (index01 == MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = index01;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aAnimal[tValue] = tITEM_INFO->iIndex;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

		//nova - New mounts
	case 2444:// White Leopard
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < 10 && mUSER[tUserIndex].mAvatarInfo.aAnimal[index01]; ++index01)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 0)
			{
				break;
			}
		}
		if (index01 == MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = index01;
		randomMount = rand() % 9;
		mUSER[tUserIndex].mAvatarInfo.aAnimal[tValue] = tITEM_INFO->iIndex - 12 + randomMount;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(mUSER[tUserIndex].mAvatarInfo.aAnimal[tValue] + (100000 * tValue), tPage, tIndex, index01);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2443://  Black Leopard
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < 10 && mUSER[tUserIndex].mAvatarInfo.aAnimal[index01]; ++index01)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 0)
			{
				break;
			}
		}
		if (index01 == MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = index01;
		randomMount = rand() % 9;
		mUSER[tUserIndex].mAvatarInfo.aAnimal[tValue] = tITEM_INFO->iIndex - 21 + randomMount;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(mUSER[tUserIndex].mAvatarInfo.aAnimal[tValue] + (100000 * tValue), tPage, tIndex, index01);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2327:// Purple Kirin
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < 10 && mUSER[tUserIndex].mAvatarInfo.aAnimal[index01]; ++index01)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 0)
			{
				break;
			}
		}
		if (index01 == MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = index01;
		randomMount = rand() % 9;
		mUSER[tUserIndex].mAvatarInfo.aAnimal[tValue] = tITEM_INFO->iIndex - 11;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(mUSER[tUserIndex].mAvatarInfo.aAnimal[tValue] + (100000 * tValue), tPage, tIndex, index01);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2328://  Blue Kirin
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < 10 && mUSER[tUserIndex].mAvatarInfo.aAnimal[index01]; ++index01)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 0)
			{
				break;
			}
		}
		if (index01 == MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = index01;
		randomMount = rand() % 9;
		mUSER[tUserIndex].mAvatarInfo.aAnimal[tValue] = tITEM_INFO->iIndex - 11;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(mUSER[tUserIndex].mAvatarInfo.aAnimal[tValue] + (100000 * tValue), tPage, tIndex, index01);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1938:// Green Deer
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < 10 && mUSER[tUserIndex].mAvatarInfo.aAnimal[index01]; ++index01)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 0)
			{
				break;
			}
		}
		if (index01 == MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = index01;
		randomMount = rand() % 9;
		mUSER[tUserIndex].mAvatarInfo.aAnimal[tValue] = tITEM_INFO->iIndex - 21 + randomMount;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(mUSER[tUserIndex].mAvatarInfo.aAnimal[tValue] + (100000 * tValue), tPage, tIndex, index01);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1939:// Dragon Deer
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < 10 && mUSER[tUserIndex].mAvatarInfo.aAnimal[index01]; ++index01)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 0)
			{
				break;
			}
		}
		if (index01 == MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = index01;
		randomMount = rand() % 9;
		mUSER[tUserIndex].mAvatarInfo.aAnimal[tValue] = tITEM_INFO->iIndex - 12 + randomMount;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(mUSER[tUserIndex].mAvatarInfo.aAnimal[tValue] + (100000 * tValue), tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2298:// Red Nine Tailed Fox
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < 10 && mUSER[tUserIndex].mAvatarInfo.aAnimal[index01]; ++index01)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 0)
			{
				break;
			}
		}
		if (index01 == MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = index01;
		randomMount = rand() % 9;
		mUSER[tUserIndex].mAvatarInfo.aAnimal[tValue] = tITEM_INFO->iIndex - 32 + randomMount;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(mUSER[tUserIndex].mAvatarInfo.aAnimal[tValue] + (100000 * tValue), tPage, tIndex, index01);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2299:// Blue Nine Taile Fox
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < 10 && mUSER[tUserIndex].mAvatarInfo.aAnimal[index01]; ++index01)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 0)
			{
				break;
			}
		}
		if (index01 == MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = index01;
		randomMount = rand() % 9;
		mUSER[tUserIndex].mAvatarInfo.aAnimal[tValue] = tITEM_INFO->iIndex - 25 + randomMount;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(mUSER[tUserIndex].mAvatarInfo.aAnimal[tValue] + (100000 * tValue), tPage, tIndex, index01);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	/*case ://not tested.
	case :
		if (mUSER[tUserIndex].mAvatarInfo.aAnimalIndex < 10 || mUSER[tUserIndex].mAvatarInfo.aAnimalIndex > 19)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 0)
			{
				break;
			}
		}

		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if ((mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] >= 2266 && mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] <= 2275) ||
				(mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] >= 2276 && mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] <= 2285) ||

				(mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] >= 1927 && mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] <= 1936) ||
				(mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] >= 1917 && mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] <= 1926) ||

				(mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] >= 2422 && mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] <= 2431) ||
				(mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] >= 2432 && mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] <= 2441)
				)
			{
				if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 2276 ||
					mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 2286 ||

					mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 1937 ||
					mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 1927 ||

					mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 2432 ||
					mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 2442 
					)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
				mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] += 1;
				break;
			}

		}

		tValue = index01;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;*/

	case 1017:
	case 506:
		if (mUSER[tUserIndex].mAvatarInfo.aEatLifePotion > 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aEatLifePotion += 1;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aEatLifePotion, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1018:
	case 507:
		if (mUSER[tUserIndex].mAvatarInfo.aEatManaPotion > 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aEatManaPotion += 1;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aEatManaPotion, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1093:
	case 508:
		if (mUSER[tUserIndex].mAvatarInfo.AgiElx > 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.AgiElx += 1;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.AgiElx, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1082:
	case 509:
		if (mUSER[tUserIndex].mAvatarInfo.StrElx > 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.StrElx += 1;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.StrElx, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	
	case 553:
		mUSER[tUserIndex].mAvatarInfo.FishingTime += 180;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.FishingTime, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 578:
		if ((mUSER[tUserIndex].mAvatarInfo.YeniElx / 1000) > 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.YeniElx += 1000;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, (mUSER[tUserIndex].mAvatarInfo.YeniElx / 1000), 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 579:
		if ((mUSER[tUserIndex].mAvatarInfo.YeniElx % 1000) > 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.YeniElx += 1;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.YeniElx % 1000, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	
	case 611: // %3 mounth pill
		if (mUSER[tUserIndex].mAvatarInfo.aAnimalIndex < 10)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if ((mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] % 1000000) == 100000)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(2, tPage, tIndex, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] += 3000;
		if ((mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] % 1000000) > 100000)
		{
			mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] = 100000;
		}
		tValue = mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10];
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, (mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] % 1000000), 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	
	case 612: // %1 mounth pill
		if (mUSER[tUserIndex].mAvatarInfo.aAnimalIndex < 10)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if ((mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] % 1000000) == 100000)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(2, tPage, tIndex, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] += 1000;
		if ((mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] % 1000000) > 100000)
		{
			mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] -= ((mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] % 1000000) - 100000);
		}
		tValue = mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10];
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, (mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] % 1000000), 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 613:
		mUSER[tUserIndex].mAvatarInfo.MountAbsorb += 60;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.MountAbsorb, 0, 0, 0, 0, 0);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(78, mUSER[tUserIndex].mAvatarInfo.MountAbsorb);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	
	//case 636: //[È°·Â´Ü]
	//	if (mUSER[tUserIndex].mAvatarInfo.aEatLifePotion > 200)
	//	{
	//		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
	//		return;
	//	}
	//	mUSER[tUserIndex].mAvatarInfo.aEatLifePotion += 10;
	//	if (mUSER[tUserIndex].mAvatarInfo.aEatLifePotion > 200)
	//	{
	//		mUSER[tUserIndex].mAvatarInfo.aEatLifePotion = 200;
	//	}
	//	mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
	//	mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aEatLifePotion, 0, 0, 0, 0, 0);
	//	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
	//	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
	//	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
	//	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
	//	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
	//	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
	//	mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
	//	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	//	return;
	//case 637: //[È°·Â´Ü]
	//	if (mUSER[tUserIndex].mAvatarInfo.aEatManaPotion > 200)
	//	{
	//		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
	//		return;
	//	}
	//	mUSER[tUserIndex].mAvatarInfo.aEatManaPotion += 10;
	//	if (mUSER[tUserIndex].mAvatarInfo.aEatManaPotion > 200)
	//	{
	//		mUSER[tUserIndex].mAvatarInfo.aEatManaPotion = 200;
	//	}
	//	mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
	//	mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aEatManaPotion, 0, 0, 0, 0, 0);
	//	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
	//	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
	//	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
	//	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
	//	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
	//	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
	//	mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
	//	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	//	return;
	//case 638: //[È°·Â´Ü]
	//	if (mUSER[tUserIndex].mAvatarInfo.StrElx > 200)
	//	{
	//		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
	//		return;
	//	}
	//	mUSER[tUserIndex].mAvatarInfo.StrElx += 10;
	//	if (mUSER[tUserIndex].mAvatarInfo.StrElx > 200)
	//	{
	//		mUSER[tUserIndex].mAvatarInfo.StrElx = 200;
	//	}
	//	mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
	//	mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.StrElx, 0, 0, 0, 0, 0);
	//	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
	//	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
	//	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
	//	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
	//	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
	//	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
	//	mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
	//	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	//	return;
	//case 639: //[È°·Â´Ü]
	//	if (mUSER[tUserIndex].mAvatarInfo.AgiElx > 200)
	//	{
	//		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
	//		return;
	//	}
	//	mUSER[tUserIndex].mAvatarInfo.AgiElx += 10;
	//	if (mUSER[tUserIndex].mAvatarInfo.AgiElx > 200)
	//	{
	//		mUSER[tUserIndex].mAvatarInfo.AgiElx = 200;
	//	}
	//	mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
	//	mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.AgiElx, 0, 0, 0, 0, 0);
	//	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
	//	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
	//	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
	//	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
	//	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
	//	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
	//	mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
	//	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	//	return;
	case 640: //[È°·Â´Ü]
		if ((mUSER[tUserIndex].mAvatarInfo.YeniElx / 1000) > 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.YeniElx += 10000;
		if ((mUSER[tUserIndex].mAvatarInfo.YeniElx / 1000) > 200)
		{
			mUSER[tUserIndex].mAvatarInfo.YeniElx -= ((mUSER[tUserIndex].mAvatarInfo.YeniElx / 1000) - 200) * 1000;
		}
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, (mUSER[tUserIndex].mAvatarInfo.YeniElx / 1000), 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 641: //[È°·Â´Ü]
		if ((mUSER[tUserIndex].mAvatarInfo.YeniElx % 1000) > 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.YeniElx += 10;
		if ((mUSER[tUserIndex].mAvatarInfo.YeniElx % 1000) > 200)
		{
			mUSER[tUserIndex].mAvatarInfo.YeniElx = ((mUSER[tUserIndex].mAvatarInfo.YeniElx % 1000) - 200) * 10;
		}
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, (mUSER[tUserIndex].mAvatarInfo.YeniElx % 1000), 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;

	case 652: // %5 mounth pill
		if (mUSER[tUserIndex].mAvatarInfo.aAnimalIndex < 10)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if ((mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] % 1000000) == 100000)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(2, tPage, tIndex, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] += 5000;
		if ((mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] % 1000000) > 100000)
		{
			mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] -= ((mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] % 1000000) - 100000);
		}
		tValue = mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10];
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10], 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 665:
		if ((mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) == 0))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mGAME.CpTowerServer != TRUE)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mGAME.mCpTower.CpTowers[mGAME.CpTowerZoneIndex] != 0)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
		switch (tValue)
		{
		case 1:
			CpTowerNum = 589;
			CpToverVlue = 101;
			break;
		case 2:
			CpTowerNum = 593;
			CpToverVlue = 102;
			break;
		case 3:
			CpTowerNum = 597;
			CpToverVlue = 103;
			break;
		default:
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (!mSUMMON.SummonMonsterForCPTower(CpTowerNum, &mGAME.CpTowerYeri[0]))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		mGAME.mCpTower.CpTowers[mGAME.CpTowerZoneIndex] = CpToverVlue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 800: //[Refined Elixir Chest]
		tRandomValue = rand() % 6;
		switch (tRandomValue)
		{
		case 0: tValue = 801; break; // Ref Hp Lix
		case 1: tValue = 802; break; // Ref Chi Lix
		case 2: tValue = 803; break; // Red Str Lix
		case 3: tValue = 804; break; // Red Dex Lix
		case 4: tValue = 805; break; // Ref E Dmg Lix
		case 5: tValue = 806; break; // Red E Def Lix
		}
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1223: //elixir box.
		tRandomValue = rand() % 100;
		 if (tRandomValue < 16 + 1)
		{
			tValue = 579; 
		}
		else if (tRandomValue < 32 + 1)
		{
			tValue = 578; 
		}
		else if (tRandomValue < 48 + 1)
		{
			tValue = 509; 
		}
		else if (tRandomValue < 64 + 1)
		{
			tValue = 508; 
		}
		else if (tRandomValue < 80 + 1)
		{
			tValue = 507; 
		}
		else 
		{
			tValue = 506; 
		}

		tITEM_INFO1 = mITEM.Search(tValue);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);

		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 829: //[Pet Inventory Expand]
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.PetInventory, 30);
		mUSER[tUserIndex].mAvatarInfo.PetInventory = tValue;
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 864://Skill Box
		tRandomValue = rand();
		int ItemLevel;
		switch (tRandomValue % 4)
		{
		case 0:
			ItemLevel = 60;
			break;
		case 1:
			ItemLevel = 70;
			break;
		case 2:
			ItemLevel = 80;
			break;
		case 3:
			ItemLevel = 146;
			break;
		}

		tITEM_INFO1 = mITEM.GetSkillByTribeInfo(ItemLevel, 3, 5, mUSER[tUserIndex].mAvatarInfo.aPreviousTribe);

		if (tITEM_INFO1 == NULL)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tValue = tITEM_INFO1->iIndex;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 891:
		if (mUSER[tUserIndex].mAvatarInfo.Title % 100 < 12)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.Title % 100 == 14)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 10000)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.Title += 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aTitle += 1;
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 10000;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 10000;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe, 10000, 0, 0, 0, 0);
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1185: //5x prot charm
		mUSER[tUserIndex].mAvatarInfo.ProtectionCharm += 5;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.ProtectionCharm, 5, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1103:
	case 1455:
		mUSER[tUserIndex].mAvatarInfo.ProtectionCharm += 1;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.ProtectionCharm, 1, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1026://return scroll 
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3]--;
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] < 1)
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		}
		mAVATAR_OBJECT[tUserIndex].mCheckDeath = true;
		mAVATAR_OBJECT[tUserIndex].mCheckCount = 9;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;

	case 1041:
		mUSER[tUserIndex].mAvatarInfo.SuperiorPill += 180;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.SuperiorPill, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case  1043:
		tRandomValue = rand() % 1000;
		if (tRandomValue < 334)
		{
			tValue = 1021;
		}
		else if (tRandomValue < 667)
		{
			tValue = 1022;
		}
		else
		{
			tValue = 1023;
		}
		tITEM_INFO1 = mITEM.Search(tValue);
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1045:
		tMoney = (10000 + rand() % 10000) * 10;
		if (mUTIL.CheckOverMaximum(mUSER[tUserIndex].mAvatarInfo.aMoney, tMoney))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aMoney += tMoney;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aMoney, tMoney, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aMoney);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1047:
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 113)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.SolemGrounds += 180;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.SolemGrounds, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1048:
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 100)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.GodTempleKey += 1;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.GodTempleKey, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1049:
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 145)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.EdgeOfTaiyan += 180;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.EdgeOfTaiyan, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1027: //[Book of Amnesia]
		for (index01 = 0; index01 < MAX_SKILL_SLOT_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] < 1)
			{
				continue;
			}
			mUSER[tUserIndex].mAvatarInfo.aSkillPoint += mUSER[tUserIndex].mAvatarInfo.aSkill[index01][1];
			mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aSkill[index01][1] = 0;
		}
		for (index01 = 0; index01 < 3; index01++)
		{
			for (index02 = 0; index02 < MAX_HOT_KEY_NUM; index02++)
			{
				if (mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] != 1)
				{
					continue;
				}
				mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] = 0;
			}
		}
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		//mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0 );
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1066: //[Book of Clear Fog]
		if ((tValue < 0) || (tValue > (MAX_SKILL_SLOT_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][0] < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < 3; index01++)
		{
			for (index02 = 0; index02 < MAX_HOT_KEY_NUM; index02++)
			{
				if (mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] != 1)
				{
					continue;
				}
				if (mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][0] == mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][0])
				{
					mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][0] = 0;
					mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][1] = 0;
					mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] = 0;
				}
			}
		}
		mUSER[tUserIndex].mAvatarInfo.aSkillPoint += mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][1];
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][0], 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case  1069://ejder
		tRandomValue = myrand(0, 100);

		if (tRandomValue < 2)
		{
			tValue = 90787; //Pala
		}
		else if (tRandomValue < 50)
		{
			tValue = 90786; //
		}
		else
		{
			tValue = 90788; //Kopuz
		}

		tITEM_INFO1 = mITEM.Search(tValue);
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case  1070://yılan
		tRandomValue = myrand(0, 100);

		if (tRandomValue < 2)
		{
			tValue = 90789; //Pala
		}
		else if (tRandomValue < 50)
		{
			tValue = 90790; //
		}
		else
		{
			tValue = 90791; //Kopuz
		}
		tITEM_INFO1 = mITEM.Search(tValue);
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case  1071://Pars
		tRandomValue = myrand(0, 100);

		if (tRandomValue < 1)
		{
			tValue = 90793; //Pala
		}
		else if (tRandomValue < 50)
		{
			tValue = 90792; //
		}
		else
		{
			tValue = 90794; //Kopuz
		}
		tITEM_INFO1 = mITEM.Search(tValue);
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case  1075: //[¹ß¼®Â÷(¹é)]
		if ((mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) == 0) || (mUSER[tUserIndex].mAvatarInfo.aTribe != 0))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((mSERVER_INFO.mServerNumber != 2) && (mSERVER_INFO.mServerNumber != 3) && (mSERVER_INFO.mServerNumber != 4) && (mSERVER_INFO.mServerNumber != 7) && (mSERVER_INFO.mServerNumber != 8) && (mSERVER_INFO.mServerNumber != 9) && (mSERVER_INFO.mServerNumber != 12) && (mSERVER_INFO.mServerNumber != 13) && (mSERVER_INFO.mServerNumber != 14) && (mSERVER_INFO.mServerNumber != 141) && (mSERVER_INFO.mServerNumber != 142) && (mSERVER_INFO.mServerNumber != 143))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (!mSUMMON.SummonMonsterForTribeWeapon(543, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0]))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, 0, "Katapult Kullanıldı", 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case  1076: //[¹ß¼®Â÷(ÆÐ)]
		if ((mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) == 0) || (mUSER[tUserIndex].mAvatarInfo.aTribe != 1))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((mSERVER_INFO.mServerNumber != 2) && (mSERVER_INFO.mServerNumber != 3) && (mSERVER_INFO.mServerNumber != 4) && (mSERVER_INFO.mServerNumber != 7) && (mSERVER_INFO.mServerNumber != 8) && (mSERVER_INFO.mServerNumber != 9) && (mSERVER_INFO.mServerNumber != 12) && (mSERVER_INFO.mServerNumber != 13) && (mSERVER_INFO.mServerNumber != 14) && (mSERVER_INFO.mServerNumber != 141) && (mSERVER_INFO.mServerNumber != 142) && (mSERVER_INFO.mServerNumber != 143))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (!mSUMMON.SummonMonsterForTribeWeapon(544, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0]))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, 0, "Katapult Kullanıldı", 0, 0); mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case  1077: //[¹ß¼®Â÷(Ç÷)]
		if ((mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) == 0) || (mUSER[tUserIndex].mAvatarInfo.aTribe != 2))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((mSERVER_INFO.mServerNumber != 2) && (mSERVER_INFO.mServerNumber != 3) && (mSERVER_INFO.mServerNumber != 4) && (mSERVER_INFO.mServerNumber != 7) && (mSERVER_INFO.mServerNumber != 8) && (mSERVER_INFO.mServerNumber != 9) && (mSERVER_INFO.mServerNumber != 12) && (mSERVER_INFO.mServerNumber != 13) && (mSERVER_INFO.mServerNumber != 14) && (mSERVER_INFO.mServerNumber != 141) && (mSERVER_INFO.mServerNumber != 142) && (mSERVER_INFO.mServerNumber != 143))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (!mSUMMON.SummonMonsterForTribeWeapon(545, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0]))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, 0, "Katapult Kullanıldı", 0, 0); mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case  1078: //[¹ß¼®Â÷(³¶)]
		if ((mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) == 0) || (mUSER[tUserIndex].mAvatarInfo.aTribe != 3))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((mSERVER_INFO.mServerNumber != 2) && (mSERVER_INFO.mServerNumber != 3) && (mSERVER_INFO.mServerNumber != 4) && (mSERVER_INFO.mServerNumber != 7) && (mSERVER_INFO.mServerNumber != 8) && (mSERVER_INFO.mServerNumber != 9) && (mSERVER_INFO.mServerNumber != 12) && (mSERVER_INFO.mServerNumber != 13) && (mSERVER_INFO.mServerNumber != 14) && (mSERVER_INFO.mServerNumber != 141) && (mSERVER_INFO.mServerNumber != 142) && (mSERVER_INFO.mServerNumber != 143))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (!mSUMMON.SummonMonsterForTribeWeapon(546, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0]))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, 0, "Katapult Kullanıldı", 0, 0); mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1101:
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.aExpandStoreDate, 30);
		if (tValue == -1)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aExpandStoreDate = tValue;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aExpandStoreDate, tValue, 0, "", 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1102:
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate, 30);
		if (tValue == -1)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate = tValue;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate, tValue, 0, "", 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1109: // tp scroll
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3]--;

		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] == 0)
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		}
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1118:
		mUSER[tUserIndex].mAvatarInfo.ScrollofLoyality += 30;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.ScrollofLoyality, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1119:
		mUSER[tUserIndex].mAvatarInfo.ScrollofBattle += 30;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.ScrollofBattle, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1120:
		mUSER[tUserIndex].mAvatarInfo.ScrollofBattle += 30;
		mUSER[tUserIndex].mAvatarInfo.ScrollofLoyality += 30;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.ScrollofBattle, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1125: //[Luxury Chest]
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 40)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		index02 = 0;
		 tItemLLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1;
		 tItemHLevel = mUSER[tUserIndex].mAvatarInfo.aLevel2;
		tRandomValue = rand() % 100;
		if (tRandomValue < 94)
		{
			if (tItemHLevel == 0) {

				if (tItemLLevel < 55) {
					index02 = 45;
				}
				else if (tItemLLevel < 65) {
					index02 = 55;
				}
				else if (tItemLLevel < 75) {
					index02 = 65;
				}
				else if (tItemLLevel < 85) {
					index02 = 75;
				}
				else if (tItemLLevel < 95) {
					index02 = 85;
				}
				else if (tItemLLevel < 105) {
					index02 = 95;
				}
				else if (tItemLLevel < 114) {
					index02 = 105;
				}
				else if (tItemLLevel < 117) {
					index02 = 114;
				}
				else if (tItemLLevel < 120) {
					index02 = 117;
				}
				else if (tItemLLevel < 123) {
					index02 = 120;
				}
				else if (tItemLLevel < 126) {
					index02 = 123;
				}
				else if (tItemLLevel < 129) {
					index02 = 126;
				}
				else if (tItemLLevel < 132) {
					index02 = 129;
				}
				else if (tItemLLevel < 135) {
					index02 = 132;
				}
				else if (tItemLLevel < 138) {
					index02 = 135;
				}
				else if (tItemLLevel < 141) {
					index02 = 138;
				}
				else if (tItemLLevel < 144) {
					index02 = 141;
				}
				else if (tItemLLevel < 145) {
					index02 = 144;
				}
				else {
					index02 = 145;
				}
			}
			else 
			{
				index02 = 145 + tItemHLevel;

			}
			ITEM_INFO* pItemPtr = NULL;

			if (3 != mUSER[tUserIndex].mAvatarInfo.aTribe)
			{
				pItemPtr = mITEM.ReturnRareItem(mUSER[tUserIndex].mAvatarInfo.aTribe, 3, index02);
			}
			else
			{
				pItemPtr = mITEM.ReturnRareItem(mUSER[tUserIndex].mAvatarInfo.aPreviousTribe,3, index02);
			}
			if (pItemPtr != NULL)
			{
				index01 = mUTIL.ReturnItemRecognitionNumber(pItemPtr->iType);
				//mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], pItemPtr->iIndex, 0, 0, index01);
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = pItemPtr->iIndex;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = index01;
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, pItemPtr->iIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
			else
			{
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV(2, tPage, tIndex, tValue);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			}
			return;
		}
		
		else
		{
			tRandomValue = rand() % 4;
			
			tValue = 506+tRandomValue;
		}
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
		
		//case 1125: //[Luxury Chest]

	//	if (mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1)
	//	{
	//		tItemLLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1;
	//		
	//		if (tItemLLevel < 55 ) {
	//			tItemLLevel = 45;
	//		}
	//		else if (tItemLLevel < 65) {
	//			tItemLLevel = 55;
	//		}
	//		else if (tItemLLevel < 75) {
	//			tItemLLevel = 65;
	//		}
	//		else if (tItemLLevel < 85) {
	//			tItemLLevel = 75;
	//		}
	//		else if (tItemLLevel < 95) {
	//			tItemLLevel = 85;
	//		}
	//		else if (tItemLLevel < 105) {
	//			tItemLLevel = 95;
	//		}
	//		else if (tItemLLevel < 114) {
	//			tItemLLevel = 105;
	//		}
	//		else if (tItemLLevel < 117) {
	//			tItemLLevel = 114;
	//		}
	//		else if (tItemLLevel < 120) {
	//			tItemLLevel = 117;
	//		}
	//		else if (tItemLLevel < 123){
	//			tItemLLevel = 120;
	//		}
	//		else if (tItemLLevel < 126) {
	//			tItemLLevel = 123;
	//		}
	//		else if (tItemLLevel < 129) {
	//			tItemLLevel = 126;
	//		}
	//		else if (tItemLLevel < 132) {
	//			tItemLLevel = 129;
	//		}
	//		else if (tItemLLevel < 135) {
	//			tItemLLevel = 132;
	//		}
	//		else if (tItemLLevel < 138) {
	//			tItemLLevel = 135;
	//		}
	//		else if (tItemLLevel < 141) {
	//			tItemLLevel = 138;
	//		}
	//		else if (tItemLLevel < 144) {
	//			tItemLLevel = 141;
	//		}
	//		else if (tItemLLevel == 144) {
	//			tItemLLevel = 144;
	//		}
	//		else {
	//			
	//			tItemLLevel = 145;
	//		}
	//	}
	//	else
	//	{
	//		tItemLLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2;
	//	}


	//	switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
	//	{
	//	case 0:
	//		tTribeItemList[0] = 7;
	//		tTribeItemList[1] = 8;
	//		tTribeItemList[2] = 9;
	//		tTribeItemList[3] = 10;
	//		tTribeItemList[4] = 11;
	//		tTribeItemList[5] = 12;
	//		tTribeItemList[6] = 13;
	//		tTribeItemList[7] = 14;
	//		tTribeItemList[8] = 15;
	//		break;
	//	case 1:
	//		tTribeItemList[0] = 7;
	//		tTribeItemList[1] = 8;
	//		tTribeItemList[2] = 9;
	//		tTribeItemList[3] = 10;
	//		tTribeItemList[4] = 11;
	//		tTribeItemList[5] = 12;
	//		tTribeItemList[6] = 16;
	//		tTribeItemList[7] = 17;
	//		tTribeItemList[8] = 18;
	//		break;
	//	case 2:
	//		tTribeItemList[0] = 7;
	//		tTribeItemList[1] = 8;
	//		tTribeItemList[2] = 9;
	//		tTribeItemList[3] = 10;
	//		tTribeItemList[4] = 11;
	//		tTribeItemList[5] = 12;
	//		tTribeItemList[6] = 19;
	//		tTribeItemList[7] = 20;
	//		tTribeItemList[8] = 21;
	//		break;
	//	}
	//	
	//		tItemType = 3;
	//	

	//	tRandomValue = rand();
	//	tItemSort = tTribeItemList[(tRandomValue % 9)];
	//	tSearchNum = 0;
	//	while (tSearchNum < 10)
	//	{
	//		tRandomValue = rand();
	//		tITEM_INFO = mITEM.Return(tItemLLevel, tItemType, tItemSort);
	//		if (tITEM_INFO)
	//		{
	//		

	//			if (((tITEM_INFO->iEquipInfo[0] == 1) || (tITEM_INFO->iCheckAvatarTrade != 1) || ((tITEM_INFO->iEquipInfo[0] - 2) == mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)))
	//			{
	//				sprintf((char*)&tData[0], "[%s] '%d' [%d] {%d} ", tITEM_INFO->iName, tITEM_INFO->iEquipInfo[0], tITEM_INFO->iCheckAvatarTrade, tITEM_INFO->iEquipInfo[0] - 2);
	//				mRELAY_COM.U_DEMAND_BROADCAST_DATA(102, &tData[0]);
	//				break;
	//			}
	//			tITEM_INFO = NULL;
	//			tSearchNum++;
	//		}
	//		else
	//		{
	//			tSearchNum++;
	//		}
	//	}
	//	if (tITEM_INFO == NULL)
	//	{
	//		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
	//		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	//		return;
	//	}
	//	tValue = tITEM_INFO->iIndex;
	//	GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
	//	//mGAMELOG.GL_606_USE_INVENTORY_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], tValue, 0, 0, 100000003 );
	//
	//	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
	//	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
	//	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
	//	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 100000003;
	//	mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
	//	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	//	return;



	case 1144: //[Inferno Box]
		tRandomValue = rand() % 400;
		if (tRandomValue <= 100)
		{
			tRandomValue = rand() % 5;
			switch (tRandomValue)
			{
			case 0: tValue = 614; break;
			case 1: tValue = 615; break;
			case 2: tValue = 616; break;
			case 3: tValue = 618; break;
			case 4: tValue = 800; break;
			}

		}
		else
		{
			tRandomValue = rand() % 5;
			switch (tRandomValue)
			{
			case 0: tValue = 1437; break;
			case 1: tValue = 1166; break;
			case 2: tValue = 1023; break;
			case 3: tValue = 612; break;
			case 4: tValue = 613; break;
			}
		}
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;



	case 664: //[Costume Box]
		
		switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe) {
		case 0:
			tRandomValue = rand() % 6;
			switch (tRandomValue) {
			case 0:
				tValue = 310;
				break;
			case 1:
				tValue = 328;
				break;
			case 2:
				tValue = 331;
				break;
			case 3:
				tValue = 334;
				break;
			case 4:
				tValue = 337;
				break;
			case 5:
				tValue = 343;
				break;
			}
			break;
			
		case 1:
			tRandomValue = rand() % 6;
			switch (tRandomValue) {
			case 0:
				tValue = 311;
				break;
			case 1:
				tValue = 329;
				break;
			case 2:
				tValue = 332;
				break;
			case 3:
				tValue = 335;
				break;
			case 4:
				tValue = 338;
				break;
			case 5:
				tValue = 344;
				break;
			}
			break;
			
		case 2:
			tRandomValue = rand() % 6;
			switch (tRandomValue) {
			case 0:
				tValue = 312;
				break;
			case 1:
				tValue = 330;
				break;
			case 2:
				tValue = 333;
				break;
			case 3:
				tValue = 336;
				break;
			case 4:
				tValue = 339;
				break;
			case 5:
				tValue = 345;
				break;
			}
			break;

		}


		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;



	case 998: //[Inferno Wing Box]


		tRandomValue = rand() % 100;
		if (tRandomValue < 5) {

			switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe) {
				//GUANYIN
			case 0:
				tRandomValue = rand() % 100;


				if (tRandomValue < 2)
				{
					if (mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1) {

						tValue = 213;  // Blue Dragon Wings(G)
					}
					else
					{                      
						tValue = 216; // Archangel Wings(G)
					}
				}
				else if (tRandomValue < 10)
				{
					tValue = 213; // Blue Dragon Wings(G)
				}
				else if (tRandomValue < 25)
				{
					tValue = 210; // Red Sparrow Wings(G)
				}
				else if (tRandomValue < 45)
				{
					tValue = 207; // Golden Sparrow Wings(G)
				}
				else if (tRandomValue < 60)
				{
					tValue = 204; // Great Turtle Wings(G)
				}
				else 
				{
					tValue = 201; // white wings 
				}

				break;
				// FUJIN
			case 1:
				tRandomValue = rand() % 100;


				if (tRandomValue < 2)
				{
					if (mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1) {

						tValue = 214; // Archangel Wings(G)
					}
					else
					{
						tValue = 217; // Blue Dragon Wings(G)
					}
				}
				else if (tRandomValue < 10)
				{
					tValue = 214; // Blue Dragon Wings(G)
				}
				else if (tRandomValue < 25)
				{
					tValue = 211; // Red Sparrow Wings(G)
				}
				else if (tRandomValue < 45)
				{
					tValue = 208; // Golden Sparrow Wings(G)
				}
				else if (tRandomValue < 60)
				{
					tValue = 205; // Great Turtle Wings(G)
				}
				else
				{
					tValue = 202; // white wings 
				}

				break;
				// JINONG
			case 2:
				tRandomValue = rand() % 100;


				if (tRandomValue < 2)
				{
					if (mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1) {

						tValue = 215; // Archangel Wings(G)
					}
					else
					{
						tValue = 218; // Blue Dragon Wings(G)
					}
				}
				else if (tRandomValue < 10)
				{
					tValue = 215; // Blue Dragon Wings(G)
				}
				else if (tRandomValue < 25)
				{
					tValue = 212; // Red Sparrow Wings(G)
				}
				else if (tRandomValue < 45)
				{
					tValue = 209; // Golden Sparrow Wings(G)
				}
				else if (tRandomValue < 60)
				{
					tValue = 206; // Great Turtle Wings(G)
				}
				else
				{
					tValue = 203; // white wings 
				}

				break;
			
			}

		}
		else {

			tRandomValue = rand() % 7;
			switch (tRandomValue)
			{

				case 0: tValue = 506	;	break;	// Vit Elix
				case 1: tValue = 507	;	break;	// Chi Elix
				case 2: tValue = 508	;	break;	// Str Elix
				case 3: tValue = 509	;	break;	// Dex Elix
				case 4: tValue = 1022	;	break;	// GOE
				case 5: tValue = 695	;	break;	// wf
				case 6: tValue = 696	;	break;	// bf

			}
		}

		tITEM_INFO1 = mITEM.Search(tValue);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	
		

	case 1186:
		mUSER[tUserIndex].mAvatarInfo.ScrollofBattle += 50;
		mUSER[tUserIndex].mAvatarInfo.ScrollofLoyality += 50;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.ScrollofBattle, 0, 0, 0, 0, 0);
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);

		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1191: //[Damage Boost Scroll L]
		mUSER[tUserIndex].mAvatarInfo.DamegeBoostScroll += 180;
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(46, mUSER[tUserIndex].mAvatarInfo.DamegeBoostScroll);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1192: //[Damage Boost Scroll M]
		mUSER[tUserIndex].mAvatarInfo.DamegeBoostScroll += 90;
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(46, mUSER[tUserIndex].mAvatarInfo.DamegeBoostScroll);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1193: //[Damage Boost Scroll S]
		mUSER[tUserIndex].mAvatarInfo.DamegeBoostScroll += 30;
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(46, mUSER[tUserIndex].mAvatarInfo.DamegeBoostScroll);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1194: //[Health Boost Scroll L]
		mUSER[tUserIndex].mAvatarInfo.HealtBoostScroll += 180;
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(47, mUSER[tUserIndex].mAvatarInfo.HealtBoostScroll);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1195: //[Health Boost Scroll M]
		mUSER[tUserIndex].mAvatarInfo.HealtBoostScroll += 90;
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(47, mUSER[tUserIndex].mAvatarInfo.HealtBoostScroll);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1196: //[Health Boost Scroll S]
		mUSER[tUserIndex].mAvatarInfo.HealtBoostScroll += 30;
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(47, mUSER[tUserIndex].mAvatarInfo.HealtBoostScroll);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1197: //[Critical Boost Scroll L]
		mUSER[tUserIndex].mAvatarInfo.CritBoostScroll += 180;
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(48, mUSER[tUserIndex].mAvatarInfo.CritBoostScroll);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1198: //[Critical Boost Scroll M]
		mUSER[tUserIndex].mAvatarInfo.CritBoostScroll += 90;
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(48, mUSER[tUserIndex].mAvatarInfo.CritBoostScroll);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1199: //[Critical Boost Scroll S]
		mUSER[tUserIndex].mAvatarInfo.CritBoostScroll += 30;
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(48, mUSER[tUserIndex].mAvatarInfo.CritBoostScroll);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;



	
	case 1434:
		mUSER[tUserIndex].mAvatarInfo.LifeOrDeath += 1;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.LifeOrDeath, 0, 0, 0, 0, 0);
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);

		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;

		// Pet Exp  + 3%
	case 1491:
		if (mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] == (mPAT.ReturnMaxPetExp(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]) * 2))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tAddExp = (mPAT.ReturnMaxPetExp(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0])) * 0.03;
		if (mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] > (mPAT.ReturnMaxPetExp(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]) * 2))
		{
			mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] = (mPAT.ReturnMaxPetExp(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]) * 2);
		}

		if (mPAT.ReturnGrowStep(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0], (mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] + tAddExp)) > mPAT.ReturnGrowStep(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0], mUSER[tUserIndex].mAvatarInfo.aEquip[8][2]))
		{
			mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 10, 0, 0, 0);
			mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		}
		mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] += tAddExp;
		mAVATAR_OBJECT[tUserIndex].mDATA.aEquipForView[8][1] += tAddExp;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(14, mUSER[tUserIndex].mAvatarInfo.aEquip[8][2]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);

		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]);
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aEquip[8][2]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
		// PET EXP + 1%
	case 1492:
		if (mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] == (mPAT.ReturnMaxPetExp(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]) * 2))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tAddExp = (mPAT.ReturnMaxPetExp(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0])) * 0.01;
		if (mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] > (mPAT.ReturnMaxPetExp(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]) * 2))
		{
			mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] = (mPAT.ReturnMaxPetExp(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]) * 2);
		}

		if (mPAT.ReturnGrowStep(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0], (mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] + tAddExp)) > mPAT.ReturnGrowStep(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0], mUSER[tUserIndex].mAvatarInfo.aEquip[8][2]))
		{
			mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 10, 0, 0, 0);
			mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		}
		mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] += tAddExp;
		mAVATAR_OBJECT[tUserIndex].mDATA.aEquipForView[8][1] += tAddExp;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(14, mUSER[tUserIndex].mAvatarInfo.aEquip[8][2]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);

		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]);
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aEquip[8][2]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1124:
		mUSER[tUserIndex].mAvatarInfo.ScrollOfSeekers += 180;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.ScrollOfSeekers, 0, 0, 0, 0, 0);
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);

		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1129:
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate, 30);
		if (tValue == -1)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate = tValue;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate, 0, 0, 0, 0, 0);
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);

		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1130:
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.aExpandStoreDate, 30);
		if (tValue == -1)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aExpandStoreDate = tValue;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aExpandStoreDate, 0, 0, 0, 0, 0);
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);

		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1142:
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 145)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aVitality + mUSER[tUserIndex].mAvatarInfo.aStrength + mUSER[tUserIndex].mAvatarInfo.aKi + mUSER[tUserIndex].mAvatarInfo.aWisdom - 4);
		mUSER[tUserIndex].mAvatarInfo.aVitality = 1;
		mUSER[tUserIndex].mAvatarInfo.aStrength = 1;
		mUSER[tUserIndex].mAvatarInfo.aKi = 1;
		mUSER[tUserIndex].mAvatarInfo.aWisdom = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);

		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1134://Stats Clear(S)|Reset all stats|For levels 1 to 99
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 > 99)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aVitality + mUSER[tUserIndex].mAvatarInfo.aStrength + mUSER[tUserIndex].mAvatarInfo.aKi + mUSER[tUserIndex].mAvatarInfo.aWisdom - 4);
		mUSER[tUserIndex].mAvatarInfo.aVitality = 1;
		mUSER[tUserIndex].mAvatarInfo.aStrength = 1;
		mUSER[tUserIndex].mAvatarInfo.aKi = 1;
		mUSER[tUserIndex].mAvatarInfo.aWisdom = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);

		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1135://Stats Clear(M) | Reset all stats | For levels 100 to 112
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 100 && mUSER[tUserIndex].mAvatarInfo.aLevel1 > 112)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aVitality + mUSER[tUserIndex].mAvatarInfo.aStrength + mUSER[tUserIndex].mAvatarInfo.aKi + mUSER[tUserIndex].mAvatarInfo.aWisdom - 4);
		mUSER[tUserIndex].mAvatarInfo.aVitality = 1;
		mUSER[tUserIndex].mAvatarInfo.aStrength = 1;
		mUSER[tUserIndex].mAvatarInfo.aKi = 1;
		mUSER[tUserIndex].mAvatarInfo.aWisdom = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);

		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1136://Stats Clear(L)|Reset all stats|Masters levels 1 to 33
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 113 && mUSER[tUserIndex].mAvatarInfo.aLevel1 > 145)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aVitality + mUSER[tUserIndex].mAvatarInfo.aStrength + mUSER[tUserIndex].mAvatarInfo.aKi + mUSER[tUserIndex].mAvatarInfo.aWisdom - 4);
		mUSER[tUserIndex].mAvatarInfo.aVitality = 1;
		mUSER[tUserIndex].mAvatarInfo.aStrength = 1;
		mUSER[tUserIndex].mAvatarInfo.aKi = 1;
		mUSER[tUserIndex].mAvatarInfo.aWisdom = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);

		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1137: //[Stat Reset One only L1-99]
		if ((mUSER[tUserIndex].mAvatarInfo.aLevel1 < 1) || (mUSER[tUserIndex].mAvatarInfo.aLevel1 > 99))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if ((tValue < 1) || (tValue > 4))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (tValue)
		{
		case 1:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aStrength - 1);
			mUSER[tUserIndex].mAvatarInfo.aStrength = 1;
			break;
		case 2:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aWisdom - 1);
			mUSER[tUserIndex].mAvatarInfo.aWisdom = 1;
			break;
		case 3:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aVitality - 1);
			mUSER[tUserIndex].mAvatarInfo.aVitality = 1;
			break;
		case 4:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aKi - 1);
			mUSER[tUserIndex].mAvatarInfo.aKi = 1;
			break;
		}
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		//mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1138: //[Stat Reset One Only L100-112
		if ((mUSER[tUserIndex].mAvatarInfo.aLevel1 < 100) || (mUSER[tUserIndex].mAvatarInfo.aLevel1 > 112))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
#ifdef __GOD__
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 > 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
#endif
		if ((tValue < 1) || (tValue > 4))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (tValue)
		{
		case 1:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aStrength - 1);
			mUSER[tUserIndex].mAvatarInfo.aStrength = 1;
			break;
		case 2:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aWisdom - 1);
			mUSER[tUserIndex].mAvatarInfo.aWisdom = 1;
			break;
		case 3:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aVitality - 1);
			mUSER[tUserIndex].mAvatarInfo.aVitality = 1;
			break;
		case 4:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aKi - 1);
			mUSER[tUserIndex].mAvatarInfo.aKi = 1;
			break;
		}
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		//mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1139: //[Stat Reset One Only M1-33]
		if ((mUSER[tUserIndex].mAvatarInfo.aLevel1 < 113) || (mUSER[tUserIndex].mAvatarInfo.aLevel1 > 145))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
#ifdef __GOD__
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 > 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
#endif
		if ((tValue < 1) || (tValue > 4))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (tValue)
		{
		case 1:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aStrength - 1);
			mUSER[tUserIndex].mAvatarInfo.aStrength = 1;
			break;
		case 2:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aWisdom - 1);
			mUSER[tUserIndex].mAvatarInfo.aWisdom = 1;
			break;
		case 3:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aVitality - 1);
			mUSER[tUserIndex].mAvatarInfo.aVitality = 1;
			break;
		case 4:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aKi - 1);
			mUSER[tUserIndex].mAvatarInfo.aKi = 1;
			break;
		}
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		//mGAMELOG.GL_605_USE_CASH_ITEM( tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] );
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;


	case 1143:
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 145)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tValue < 1) || (tValue > 4))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (tValue)
		{
		case 1:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aStrength - 1);
			mUSER[tUserIndex].mAvatarInfo.aStrength = 1;
			break;
		case 2:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aWisdom - 1);
			mUSER[tUserIndex].mAvatarInfo.aWisdom = 1;
			break;
		case 3:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aVitality - 1);
			mUSER[tUserIndex].mAvatarInfo.aVitality = 1;
			break;
		case 4:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aKi - 1);
			mUSER[tUserIndex].mAvatarInfo.aKi = 1;
			break;
		}
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);

		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1145:
		mUSER[tUserIndex].mAvatarInfo.aAnimalTime += 180;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aAnimalTime, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aAnimalTime);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1146:
		mUSER[tUserIndex].mAvatarInfo.LuckyCombine += 3;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.LuckyCombine, 0, 0, 0, 0, 0);
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);

		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.LuckyCombine);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1147:
		mUSER[tUserIndex].mAvatarInfo.LuckyCombine += 2;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.LuckyCombine, 0, 0, 0, 0, 0);
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);

		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.LuckyCombine);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1148:
		mUSER[tUserIndex].mAvatarInfo.LuckyCombine += 1;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.LuckyCombine, 0, 0, 0, 0, 0);
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);

		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.LuckyCombine);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1218:
		mUSER[tUserIndex].mAvatarInfo.PreServeCharm += 1;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.PreServeCharm, 0, 0, 0, 0, 0);
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);

		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1221:
		mUSER[tUserIndex].mAvatarInfo.DoubleMouthExp2x += 180;
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);

		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.DoubleMouthExp2x, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1224: // tp scroll
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3]--;

		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] == 0)
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		}
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1166:
		mUSER[tUserIndex].mAvatarInfo.Cppc += 1;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.Cppc, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1167:
		mUSER[tUserIndex].mAvatarInfo.iGoldOrnamentRemainsTime += 240;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.iGoldOrnamentRemainsTime, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1370: //[Silver Plate Scroll]
		mUSER[tUserIndex].mAvatarInfo.iSilverOrnamentRemainsTime += 180;
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(40, mUSER[tUserIndex].mAvatarInfo.iGoldOrnamentRemainsTime);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1171: //Gender Change Scroll
		mUSER[tUserIndex].mAvatarInfo.aGender = tValue % 10 / 1 - 1;
		mUSER[tUserIndex].mAvatarInfo.aHeadType = tValue % 100 / 10 - 1;
		mUSER[tUserIndex].mAvatarInfo.aFaceType = tValue % 1000 / 100 - 1;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);

		mAVATAR_OBJECT[tUserIndex].mDATA.aGender = mUSER[tUserIndex].mAvatarInfo.aGender;
		mAVATAR_OBJECT[tUserIndex].mDATA.aHeadType = mUSER[tUserIndex].mAvatarInfo.aHeadType;
		mAVATAR_OBJECT[tUserIndex].mDATA.aFaceType = mUSER[tUserIndex].mAvatarInfo.aFaceType;
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(mAVATAR_OBJECT[tUserIndex].mIndex,
			mAVATAR_OBJECT[tUserIndex].mUniqueNumber,
			90,
			mUSER[tUserIndex].mAvatarInfo.aGender,
			mUSER[tUserIndex].mAvatarInfo.aHeadType,
			mUSER[tUserIndex].mAvatarInfo.aFaceType);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		return;
	case 603:
		mUSER[tUserIndex].mAvatarInfo.OnlineHour += 720;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.OnlineHour, 720, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1190:
		mUSER[tUserIndex].mAvatarInfo.PetExpBoost += 180;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.PetExpBoost, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1200: 
		if (mUSER[tUserIndex].mAvatarInfo.Title < 1)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			return;
		}
		title = mUSER[tUserIndex].mAvatarInfo.Title % 100;
		for (int i = 0; i < title; i++)
		{
			AddCp += CpValue[i];
		}
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += AddCp;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe = mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe;
		mUSER[tUserIndex].mAvatarInfo.Title = 0;
		mAVATAR_OBJECT[tUserIndex].mDATA.aTitle = mUSER[tUserIndex].mAvatarInfo.Title;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, AddCp, 0, 0, 0, 0);
		if (title == 13 || title == 14)
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 891;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1201:
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.AutoBuffScroll, 7);
		if (tValue == -1)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.AutoBuffScroll = tValue;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.AutoBuffScroll, 7, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1215:
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.AutoBuffScroll, 30);
		if (tValue == -1)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.AutoBuffScroll = tValue;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.AutoBuffScroll, 30, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1216:
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.AutoBuffScroll, 1);
		if (tValue == -1)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.AutoBuffScroll = tValue;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.AutoBuffScroll, 1, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 686:
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.Hunt7d, 1);
		if (tValue == -1)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.Hunt7d = tValue;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.Hunt7d, 1, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 687:
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.Hunt7d, 7);
		if (tValue == -1)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.Hunt7d = tValue;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.Hunt7d, 7, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1217:
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.Hunt7d, 30);
		if (tValue == -1)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.Hunt7d = tValue;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.Hunt7d, 30, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	
		// PLAY Box
	case 1220:
		tRandomValue = rand() % 1000;
		if (tRandomValue < 10) 
		{
				tValue = 1185; // 5 Protection Charm
		}
		else if (tRandomValue < 50) 
		{
				tValue = 1103; // Protection Charm
		}
		else if (tRandomValue < 100) 
		{
				switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe) {
					case 0:
						tValue = 126; // Deco 2 Guanyin
						break;
					case 1:
						tValue = 129; // Deco 2 Fujin
						break;
					case 2:
						tValue = 132; // Deco 2 Jinong
						break;
				}
		}
		else {
			tRandomValue = rand() % 8;
			switch (tRandomValue) {
				case 0:
					tValue = 506; // Vit Elixir
					break;
				case 1:
					tValue = 507; // Chi Elixir
					break;
				case 2:
					tValue = 508; // Str Elixir
					break;
				case 3:
					tValue = 509; // Dex Elixir
					break;
				case 4: 
					tValue = 696;  // Black Feather
					break;
				case 5:
					tValue = 1166; // Guardian Scroll
					break;
				case 6:
					tValue = 1022; // Gold of Eternity
					break;
				case 7:
					tValue = 1152; // Summon Ticket
					break;

			}
		}
		
		tITEM_INFO1 = mITEM.Search(tValue);
		/*char tContent[MAX_CHAT_CONTENT_LENGTH];
		snprintf(tContent, 61, "tValue : %d ",tValue);
		mTRANSFER.B_SECRET_CHAT_RECV(3, mSERVER_INFO.mServerNumber, "SYSTEM", &tContent[0], 1);*/
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize, false);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

		// Summoning Ticket

	case 1152:
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 == 0) {
			if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 90) {
				char tContent[MAX_CHAT_CONTENT_LENGTH];
				snprintf(tContent, 61, "You need to be [Level 90] - RELOG");
				mTRANSFER.B_SECRET_CHAT_RECV(3, mSERVER_INFO.mServerNumber, "SYSTEM", &tContent[0], 1);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize, false);
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			else 
				switch(mUSER[tUserIndex].mAvatarInfo.aLevel1)
			{
				case 90:
				case 91:
				case 92:
				case 93:
				case 94:
				case 95:
				case 96:
				case 97:
				case 98:
				case 99:
					tValue = 501; // Nightmare Swordsman
					break;
				case 100:
				case 101:
				case 102:
				case 103:
				case 104:
				case 105:
				case 106:
				case 107:
				case 108:
				case 109:
				
					tValue = 502; // Sacred Blood Lord
					break;
				case 110:
				case 111:
				case 112:
				case 113:
				case 114:
				case 115:
				case 116:
					tValue = 503; // Skyorne Thunder
					break;
				case 117:
				case 118:
				case 119:
				case 120:
					tValue = 504; // Soaring Firebird
					break;
				case 121:
				case 122:
				case 123:
				case 124:
					tValue = 505;  // Rage Drake
					break;
				case 125:
				case 126:
				case 127:
				case 128:
					tValue = 506; // Cinder Haze
					break;
				case 129:
				case 130:
				case 131:
				case 132:
					tValue = 507; // Black Dagger
					break;
				case 133:
				case 134:
				case 135:
				case 136:
					tValue = 508; // Holy Demonarch
					break;
				case 137:
				case 138:
				case 139:
				case 140:
					tValue = 509; // Benvolent Buddha 
					break;
				case 141:
				case 142:
				case 143:
				case 144:
					tValue = 510; // Blood-drenched Hulk
					break;
				case 145:
					tValue = 511; // Goblinkin Cheiftain
					break;

			}
		}
		else {
			tValue = 1013;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, 506, &tData[0]);
		mSUMMON.SummonMonsterForSpecial(tValue, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], FALSE);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
		case 1153: //[Lucky Drop M]
			mUSER[tUserIndex].mAvatarInfo.LuckyDrop += 120;
			GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;

		case 1154: //[Lucky Drop S]
			mUSER[tUserIndex].mAvatarInfo.LuckyDrop += 60;
			GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;



	case 1222:
		mUSER[tUserIndex].mAvatarInfo.MountAbsorb += 180;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.MountAbsorb, 0, 0, 0, 0, 0);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(78, mUSER[tUserIndex].mAvatarInfo.MountAbsorb);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1227:
		mUSER[tUserIndex].mAvatarInfo.WarriorScroll += 30;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.WarriorScroll, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(87, mUSER[tUserIndex].mAvatarInfo.WarriorScroll);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1237:
		mUSER[tUserIndex].mAvatarInfo.WingProtectionRune += 1;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.WingProtectionRune, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1180:
		mUSER[tUserIndex].mAvatarInfo.BloodBoost += 1;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.SoulBoost, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1181:
		mUSER[tUserIndex].mAvatarInfo.SoulBoost += 1;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.SoulBoost, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1371:
		if (mUSER[tUserIndex].mAvatarInfo.BloodBoost >= 1)
		{
			mUSER[tUserIndex].mAvatarInfo.IslandOfBlood += 60;
			mUSER[tUserIndex].mAvatarInfo.BloodBoost--;
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.IslandOfBlood += 30;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.IslandOfBlood, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1372:
		if (mUSER[tUserIndex].mAvatarInfo.SoulBoost >= 1)
		{
			mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal1 += 60;
			mUSER[tUserIndex].mAvatarInfo.SoulBoost--;
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal1 += 30;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal1, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1373:
		if (mUSER[tUserIndex].mAvatarInfo.SoulBoost >= 1)
		{
			mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal2 += 60;
			mUSER[tUserIndex].mAvatarInfo.SoulBoost--;
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal2 += 30;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal2, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1374:
		if (mUSER[tUserIndex].mAvatarInfo.SoulBoost >= 1)
		{
			mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal3 += 60;
			mUSER[tUserIndex].mAvatarInfo.SoulBoost--;
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal3 += 30;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal3, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1375:
		if (mUSER[tUserIndex].mAvatarInfo.SoulBoost >= 1)
		{
			mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal4 += 60;
			mUSER[tUserIndex].mAvatarInfo.SoulBoost--;
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal4 += 30;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal4, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1376:
		if (mUSER[tUserIndex].mAvatarInfo.SoulBoost >= 1)
		{
			mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal5 += 60;
			mUSER[tUserIndex].mAvatarInfo.SoulBoost--;
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal5 += 30;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal5, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1377:
		if (mUSER[tUserIndex].mAvatarInfo.SoulBoost >= 1)
		{
			mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal6 += 60;
			mUSER[tUserIndex].mAvatarInfo.SoulBoost--;
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal6 += 30;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal6, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;

	case  1378: //Heaven Chest
		tRandomValue = rand() % 100;
		if (tRandomValue < 25)
		{
			switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
			{
			case 0:
				switch (rand() % 8)
				{
				case 0:
					tValue = 87077;//
					break;
				case 1:
					tValue = 87078;//Hafif Kılıç
					break;
				case 2:
					tValue = 87079;//Güç Topu
					break;
				case 3:
					tValue = 87080;//Zırh
					break;
				case 4:
					tValue = 87081;//Eldiven
					break;
				case 5:
					tValue = 87082;//Bot
					break;
				case 6:
					tValue = 87083;//Yüzük
					break;
				case 7:
					tValue = 87084;//Tılsım
					break;
				}
				break;
			case 1:
				switch (rand() % 8)
				{
				case 0:
					tValue = 87099;//Pala
					break;
				case 1:
					tValue = 87100;//
					break;
				case 2:
					tValue = 87101;//Kopuz
					break;
				case 3:
					tValue = 87102;//Zırh
					break;
				case 4:
					tValue = 87103;//Eldiven
					break;
				case 5:
					tValue = 87104;//Bot
					break;
				case 6:
					tValue = 87105;//Yüzük
					break;
				case 7:
					tValue = 87106;//Tılsım
					break;
				}
				break;
			case 2:
				switch (rand() % 8)
				{
				case 0:
					tValue = 87121;//Kısa Bıçak
					break;
				case 1:
					tValue = 87122;//Uzun Mızrak
					break;
				case 2:
					tValue = 87123;//Kama
					break;
				case 3:
					tValue = 87124;//Zırh
					break;
				case 4:
					tValue = 87125;//Eldiven
					break;
				case 5:
					tValue = 87126;//Bot
					break;
				case 6:
					tValue = 87127;//Yüzük
					break;
				case 7:
					tValue = 87128;//Tılsım
					break;
				}
				break;
			}
		}
		else
		{
			tValue = 1379;
		}
		tITEM_INFO1 = mITEM.Search(tValue);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		tITEM_INFO1 = mITEM.Search(tValue);
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

//		case 1220: //PVM Box (S5r Set )
//			tRandomValue = rand() % 100;
//			if (tRandomValue < 10)
//			{
//				switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
//				{
//				case 0:
//					switch (rand() % 8)
//					{
//					case 0:
//						tValue = 87013;// 
//						break;
//					case 1:
//						tValue = 87014;//Hafif Kılıç
//						break;
//					case 2:
//						tValue = 87015;//
//						break;
//					case 3:
//						tValue = 87016;//Zırh
//						break;
//					case 4:
//						tValue = 87017;//Eldiven
//						break;
//					case 5:
//						tValue = 87018;//Bot
//						break;
//					case 6:
//						tValue = 87019;//Yüzük
//						break;
//					case 7:
//						tValue = 87020;//Tılsım
//						break;
//					}
//					break;
//				case 1:
//					switch (rand() % 8)
//					{
//					case 0:
//						tValue = 87034;//Pala
//						break;
//					case 1:
//						tValue = 87035;//
//						break;
//					case 2:
//						tValue = 87036;//Kopuz
//						break;
//					case 3:
//						tValue = 87037;//Zırh
//						break;
//					case 4:
//						tValue = 87038;//Eldiven
//						break;
//					case 5:
//						tValue = 87039;//Bot
//						break;
//					case 6:
//						tValue = 87040;//Yüzük
//						break;
//					case 7:
//						tValue = 87041;//Tılsım
//						break;
//					}
//					break;
//				case 2:
//					switch (rand() % 8)
//					{
//					case 0:
//						tValue = 87055;//Kısa Bıçak
//						break;
//					case 1:
//						tValue = 87056;//Uzun Mızrak
//						break;
//					case 2:
//						tValue = 87057;//Kama
//						break;
//					case 3:
//						tValue = 87058;//Zırh
//						break;
//					case 4:
//						tValue = 87059;//Eldiven /item 8711
//						break;
//					case 5:
//						tValue = 87060;//Bot
//						break;
//					case 6:
//						tValue = 87061;//Yüzük
//						break;
//					case 7:
//						tValue = 87062;//Tılsım
//						break;
//					}
//
//				}
//				
//			}
//			else if (tRandomValue < 25) {
//				tValue = 1422;
//			}
//			else if (tRandomValue < 40) {
//				tValue = 1447;
//			}
//			else if (tRandomValue < 55) {
//			tValue = 1437;
//			}
//			else if (tRandomValue < 70) {
//			tValue = 1125;
//			}
//			else if (tRandomValue < 85) {
//			tValue = 1103;
//			}
//			else {
//			tValue = 1448;
//}
//			tITEM_INFO1 = mITEM.Search(tValue);
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
//			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
//			tITEM_INFO1 = mITEM.Search(tValue);
//			mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4]);
//			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
//			return;


	case  1379: //Earth Chest 
		switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
		{
		case 0:
			switch (rand() % 8)
			{
			case 0:
				tValue = 87071;// 
				break;
			case 1:
				tValue = 87072;//Hafif Kılıç
				break;
			case 2:
				tValue = 87073;//
				break;
			case 3:
				tValue = 87074;//Zırh
				break;
			case 4:
				tValue = 87075;//Eldiven
				break;
			case 5:
				tValue = 87076;//Bot
				break;
			case 6:
				tValue = 87063;//Yüzük
				break;
			case 7:
				tValue = 87064;//Tılsım
				break;
			}
			break;
		case 1:
			switch (rand() % 8)
			{
			case 0:
				tValue = 87093;//Pala
				break;
			case 1:
				tValue = 87094;//
				break;
			case 2:
				tValue = 87095;//Kopuz
				break;
			case 3:
				tValue = 87096;//Zırh
				break;
			case 4:
				tValue = 87097;//Eldiven
				break;
			case 5:
				tValue = 87098;//Bot
				break;
			case 6:
				tValue = 87085;//Yüzük
				break;
			case 7:
				tValue = 87086;//Tılsım
				break;
			}
			break;
		case 2:
			switch (rand() % 8)
			{
			case 0:
				tValue = 87115;//Kısa Bıçak
				break;
			case 1:
				tValue = 87116;//Uzun Mızrak
				break;
			case 2:
				tValue = 87117;//Kama
				break;
			case 3:
				tValue = 87118;//Zırh
				break;
			case 4:
				tValue = 87119;//Eldiven /item 8711
				break;
			case 5:
				tValue = 87120;//Bot
				break;
			case 6:
				tValue = 87107;//Yüzük
				break;
			case 7:
				tValue = 87108;//Tılsım
				break;
			}
			break;
		}
		tITEM_INFO1 = mITEM.Search(tValue);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		tITEM_INFO1 = mITEM.Search(tValue);
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;


	case 1436: //[Exp Pill L]
	case 1458:
		mUSER[tUserIndex].mAvatarInfo.ExpPill += 180;
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1438: //[Exp Pill M]
		mUSER[tUserIndex].mAvatarInfo.ExpPill += 120;
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1439: //[Exp Pill S]
		mUSER[tUserIndex].mAvatarInfo.ExpPill += 60;
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1447:
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 1000;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 1000;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1489: //[Instant 3% Exp Pill Master]
		if ((mUSER[tUserIndex].mAvatarInfo.aLevel1 < 113) || (mUSER[tUserIndex].mAvatarInfo.aLevel2 > 0))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = ((mLEVEL.ReturnLevelFactor2(mUSER[tUserIndex].mAvatarInfo.aLevel1) - mLEVEL.ReturnLevelFactor1(mUSER[tUserIndex].mAvatarInfo.aLevel1)) * 0.03f);
		if ((mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 + tValue) > mLEVEL.ReturnLevelFactor2(mUSER[tUserIndex].mAvatarInfo.aLevel1))
		{
			tValue = mLEVEL.ReturnLevelFactor2(mUSER[tUserIndex].mAvatarInfo.aLevel1) - mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1;
		}
		mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 += tValue;
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(13, mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1490: //[Instant 1% Exp Pill God]
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = (mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2) * 0.01f);
		if ((mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 + tValue) > mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
		{
			tValue = mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2) - mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2;
		}
		mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 += tValue;
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(24, mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 691:
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 5;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 5;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 692:
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 10;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 10;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 693:
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 15;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 15;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 694:
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 20;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 20;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1499:
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 5000;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 5000;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1448:
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 500;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 500;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1449:
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 100;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 100;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;

	case 17139:
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 20;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 20;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 17138:
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 250;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 250;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1494: 
		if (mUSER[tUserIndex].mAvatarInfo.Title < 1)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			return;
		}
		title = (mUSER[tUserIndex].mAvatarInfo.Title % 100);
		AddCp = 0;
		for (int i = 0; i < title; i++)
		{
			AddCp += CpValue[i];
		}
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += (AddCp * 0.7);
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe = mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe;
		mUSER[tUserIndex].mAvatarInfo.Title = 0;
		mAVATAR_OBJECT[tUserIndex].mDATA.aTitle = mUSER[tUserIndex].mAvatarInfo.Title;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, (AddCp * 0.7), 0, 0, 0, 0);
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 7010:
		if (mUSER[tUserIndex].mAvatarInfo.aTribe == 3)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (strcmp(mUSER[tUserIndex].mAvatarInfo.aTeacher, "") != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (strcmp(mUSER[tUserIndex].mAvatarInfo.aStudent, "") != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_FRIEND_NUM; index01++)
		{
			if (strcmp(mUSER[tUserIndex].mAvatarInfo.aFriend[index01], "") != 0)
			{
				break;
			}
		}
		if (index01 < MAX_FRIEND_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		mUSER[tUserIndex].mAvatarInfo.aTribe = 3;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[4] = 0;
		mAVATAR_OBJECT[tUserIndex].mDATA.aTribe = 3;
		mTRANSFER.B_CHANGE_TO_TRIBE4_RECV(0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1189:
		if (mUSER[tUserIndex].mAvatarInfo.aTribe != 3)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (strcmp(mUSER[tUserIndex].mAvatarInfo.aTeacher, "") != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (strcmp(mUSER[tUserIndex].mAvatarInfo.aStudent, "") != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_FRIEND_NUM; index01++)
		{
			if (strcmp(mUSER[tUserIndex].mAvatarInfo.aFriend[index01], "") != 0)
			{
				break;
			}
		}
		if (index01 < MAX_FRIEND_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		mUSER[tUserIndex].mAvatarInfo.aTribe = mUSER[tUserIndex].mAvatarInfo.aPreviousTribe;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[4] = 0;
		mAVATAR_OBJECT[tUserIndex].mDATA.aTribe = mUSER[tUserIndex].mAvatarInfo.aPreviousTribe;
		mTRANSFER.B_RETURN_TO_AUTO_ZONE();
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1894:
		mUSER[tUserIndex].mAvatarInfo.Hisar += 1;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.Hisar, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.Hisar);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2334:
	case 2393:
		mUSER[tUserIndex].mAvatarInfo.LifeOrDeath += 1;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.LifeOrDeath, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 2448:
		tRandomValue = (4 + (rand() % 3));
		index02 = 1;
		for (index01 = 1; index01 < tRandomValue; index01++)
		{
			tITEM_INFO1 = mITEM.Search(531);
			if (tITEM_INFO1 == NULL)
			{
				break;
			}
			if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO1, iInvenPage1[index01], iInvenSlot1[index01]) == false)
			{
				break;
			}
			iInvenIndex1[index01] = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, iInvenPage1[index01]);
			if (iInvenSlot == -1)
			{
				break;
			}
			index02++;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage1[index01]][iInvenIndex1[index01]][0] = 531;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage1[index01]][iInvenIndex1[index01]][1] = iInvenSlot1[index01] % 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage1[index01]][iInvenIndex1[index01]][2] = iInvenSlot1[index01] / 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage1[index01]][iInvenIndex1[index01]][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage1[index01]][iInvenIndex1[index01]][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage1[index01]][iInvenIndex1[index01]][5] = 0;
		}
		if (index01 != tRandomValue)
		{
			for (index01 = 1; index01 < index02; index01++)
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage1[index01]][iInvenIndex1[index01]][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage1[index01]][iInvenIndex1[index01]][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage1[index01]][iInvenIndex1[index01]][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage1[index01]][iInvenIndex1[index01]][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage1[index01]][iInvenIndex1[index01]][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage1[index01]][iInvenIndex1[index01]][5] = 0;
			}
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		for (index01 = 1; index01 < tRandomValue; index01++)
		{
			mTRANSFER.B_ITEM_SEND(0, 531, iInvenPage1[index01], iInvenIndex1[index01], iInvenSlot1[index01]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 531;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, tRandomValue, 0, 0, "", 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, 531);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
		
	case 17020:

		faction = mUSER[tUserIndex].mAvatarInfo.aPreviousTribe;

		tRandomValue = rand() % 100;
		if (tRandomValue < 20) {
			
			switch (faction) {
			case 0:
				tRandomValue = rand() % 6;
				switch (tRandomValue) {
				case 0:
					tValue = 519;
					break;
				case 1:
					tValue = 594;
					break;
				case 2:
					tValue = 1385;
					break;
				case 3:
					tValue = 1386;
					break;
				case 4:
					tValue = 1483;
					break;
				case 5:
					tValue = 1486;
					break;
				}
				break;
			case 1:
				tRandomValue = rand() % 6;
				switch (tRandomValue) {
				case 0:
					tValue = 520;
					break;
				case 1:
					tValue = 595;
					break;
				case 2:
					tValue = 1386;
					break;
				case 3:
					tValue = 1387;
					break;
				case 4:
					tValue = 1484;
					break;
				case 5:
					tValue = 1487;
					break;
				}
				break;
			case 2:
				tRandomValue = rand() % 6;
				switch (tRandomValue) {
				case 0:
					tValue = 521;
					break;
				case 1:
					tValue = 596;
					break;
				case 2:
					tValue = 1387;
					break;
				case 3:
					tValue = 1388;
					break;
				case 4:
					tValue = 1485;
					break;
				case 5:
					tValue = 1488;
					break;
				}
				break;

			}
		}
		else {
			switch (faction) {
			case 0:
				tRandomValue = rand() % 11;
				switch (tRandomValue) {
				case 0: tValue = 101;
					break;
				case 1:tValue = 102;
					break;
				case 2:tValue = 103;
					break;
				case 3:tValue = 104;
					break;
				case 4:tValue = 113;
					break;
				case 5:tValue = 114;
					break;
				case 6:tValue = 115;
					break;
				case 7:tValue = 116;
					break;
				case 8:tValue = 125;
					break;
				case 9:tValue = 126;
					break;
				case 10:tValue = 127;
					break;
				
				}
				break;
			case 1:
				tRandomValue = rand() % 11;
				switch (tRandomValue) {
				case 0: tValue = 105;
					break;
				case 1:tValue = 106;
					break;
				case 2:tValue = 107;
					break;
				case 3:tValue = 108;
					break;
				case 4:tValue = 117;
					break;
				case 5:tValue = 118;
					break;
				case 6:tValue = 119;
					break;
				case 7:tValue = 120;
					break;
				case 8:tValue = 128;
					break;
				case 9:tValue = 129;
					break;
				case 10:tValue = 130;
					break;
				}
				break;
			case 2:
				tRandomValue = rand() % 11;
				switch (tRandomValue) {
				case 0: tValue = 109;
					break;
				case 1:tValue = 110;
					break;
				case 2:tValue = 111;
					break;
				case 3:tValue = 112;
					break;
				case 4:tValue = 121;
					break;
				case 5:tValue = 122;
					break;
				case 6:tValue = 123;
					break;
				case 7:tValue = 124;
					break;
				case 8:tValue = 131;
					break;
				case 9:tValue = 132;
					break;
				case 10:tValue = 133;
					break;
				}
				break;
			}
		}

		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		
		
		break;
		// Treasure Box
	case 17082:
		
		tRandomValue = rand() % 1000;
		if (tRandomValue <= 200)
		{
			tRandomValue = rand() % 100;
				if (tRandomValue < 60) 
				{
					tValue = 720; // Gold Piece
				}
				else if (tRandomValue < 70) 
				{
					tValue = 721; // Blue Piece
				}
				else if (tRandomValue < 80) 
				{
					tValue = 722; // Purple Piece
				}
				else 
				{ 
					tValue = 723; // Green Piece
				}
		}
		else if (tRandomValue < 500) 
		{
			tRandomValue = rand() % 5;
			switch (tRandomValue) {
			case 0:
				tValue = 1108; //Protection Scroll
				break;
			case 1:
				tValue = 1227; // Warrior Scroll
				break;
			case 2:
				tValue = 698; // Gold Feather
				break;
			case 3:
				tValue = 1145; // SkyLord's Blessed Feed
				break;
			case 4:
				tRandomValue = rand() % 7;
				switch (tRandomValue) {
				case 0:
					tValue = 691; // 5CP Ticket
					break;
				case 1:
					tValue = 692; // 10 CP Ticket
					break;
				case 2:
					tValue = 693; // 15 CP Ticket
					break;
				case 3:
					tValue = 694; // 20 CP Ticket
					break;
				case 4:
					tValue = 1118; // Scroll of Loyality
					break;
				case 5:
					tValue = 1119; // Scroll of Battle
					break;
				case 6:
					tValue = 1120; // Scroll of the Gods
					break;
				}
				break;
			}
		}

		else
		{
			tRandomValue = rand() % 9;
			switch (tRandomValue) {
			case 0:
				tValue = 1022; // SOE
				break;
			case 1:
				tValue = 1023; // GOE
				break;
			case 2:
				tValue = 1024; // PJ
				break;
			case 3:
				tValue = 1025; // RJ
				break;
			case 4:
				tValue = 506;  // HP elix
				break;
			case 5:
				tValue = 507;  // CHI elix
				break;
			case 6:
				tValue = 508;  // DEX elix 
				break;
			case 7:
				tValue = 509;  // STR elix
				break;
			case 8:
				tValue = 695;  // WF
				break;
			}
		}
		GameLogger(1, "<USE_INVENTORY_ITEM>(%s),(%s), (%d, %d, %d, %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], mSERVER_INFO.mServerNumber);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	
	default: //[¿À·ù]
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}
//W_IMPROVE_ITEM_SEND
void W_IMPROVE_ITEM_SEND(int tUserIndex)
{
	__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	unsigned int tRandom = 0;
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];

	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	CopyMemory(&tPage1, &tPacket[1], 4);
	CopyMemory(&tIndex1, &tPacket[5], 4);
	CopyMemory(&tPage2, &tPacket[9], 4);
	CopyMemory(&tIndex2, &tPacket[13], 4);

	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	ITEM_INFO* tITEM_INFO1;
	ITEM_INFO* tITEM_INFO2;
	int tCost;
	int iValue;
	int tCPCost;
	int tProbability1;
	int tProbability2;
	int tProtectIS = 0;

	if ((tPage1 == 1) || (tPage2 == 1))
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
	if (tITEM_INFO1 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tITEM_INFO1->iSort != 6) && (tITEM_INFO1->iSort != 7) && (tITEM_INFO1->iSort != 8) && (tITEM_INFO1->iSort != 9) && (tITEM_INFO1->iSort != 10) && (tITEM_INFO1->iSort != 11) && (tITEM_INFO1->iSort != 12) && (tITEM_INFO1->iSort != 13) && (tITEM_INFO1->iSort != 14) && (tITEM_INFO1->iSort != 15) && (tITEM_INFO1->iSort != 16) && (tITEM_INFO1->iSort != 17) && (tITEM_INFO1->iSort != 18) && (tITEM_INFO1->iSort != 19) && (tITEM_INFO1->iSort != 20) && (tITEM_INFO1->iSort != 21))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tITEM_INFO1->iType == 6))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tITEM_INFO1->iCheckImprove != 2)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) >= 50)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
	if (tITEM_INFO2 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (   (tITEM_INFO2->iIndex != 695)
		&& (tITEM_INFO2->iIndex != 633)
		&& (tITEM_INFO2->iIndex != 696)
		&& (tITEM_INFO2->iIndex != 698)
		&& (tITEM_INFO2->iIndex != 825)
		&& (tITEM_INFO2->iIndex != 826)
		&& (tITEM_INFO2->iIndex != 1019)
		&& (tITEM_INFO2->iIndex != 1020)
		&& (tITEM_INFO2->iIndex != 1021)
		&& (tITEM_INFO2->iIndex != 1022)
		&& (tITEM_INFO2->iIndex != 1023)
		&& (tITEM_INFO2->iIndex != 1422)
		&& (tITEM_INFO2->iIndex != 1243)
		&& (tITEM_INFO2->iIndex != 1437))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	switch (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0])
	{
	case 633:
		tCost = 0;
		tCPCost = 0;
		iValue = 1;
		break;
	case 695:
		tCost = 0;
		tCPCost = 50;
		iValue = 1;
		break;
	case 696:
		tCost = 0;
		tCPCost = 50;
		iValue = 2;
		break;
	case 698:
		tCost = 0;
		tCPCost = 50;
		iValue = 3;
		break;
	case 825:
		tCost = 0;
		tCPCost = 0;
		iValue = 50;
		break;
	case 826:
		tCost = 0;
		tCPCost = 0;
		iValue = 40;
		break;
	case 1019:
		tCost = 10000;
		tCPCost = 0;
		iValue = 1;
		break;
	case 1020:
		tCost = 30000;
		tCPCost = 0;
		iValue = 2;
		break;
	case 1021:
		tCost = 50000;
		tCPCost = 0;
		iValue = 3;
		break;
	case 1022:
		tCost = 70000;
		tCPCost = 0;
		iValue = 4;
		break;
	case 1023:
		tCost = 90000;
		tCPCost = 0;
		iValue = 5;
		break;
	case 1422:
		tCost = 90000;
		tCPCost = 0;
		iValue = 1;
		break;
	case 1437:
		tCost = 90000;
		iValue = 1;
		break;

	}
	if (mUSER[tUserIndex].mAvatarInfo.aMoney < tCost)
	{
		char tContent[MAX_CHAT_CONTENT_LENGTH];
		snprintf(tContent, 61, "Not enough Silver.");
		mTRANSFER.B_SECRET_CHAT_RECV(3, mSERVER_INFO.mServerNumber, "SYSTEM", &tContent[0], 1);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize, false);
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < tCPCost)
	{
		char tContent[MAX_CHAT_CONTENT_LENGTH];
		snprintf(tContent, 61, "Not enough CP.");
		mTRANSFER.B_SECRET_CHAT_RECV(3, mSERVER_INFO.mServerNumber, "SYSTEM", &tContent[0], 1);
	
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == 40)
	{
		char tContent[MAX_CHAT_CONTENT_LENGTH];
		snprintf(tContent, 61, "Maximum enchant has been reached!");
		mTRANSFER.B_SECRET_CHAT_RECV(3, mSERVER_INFO.mServerNumber, "SYSTEM", &tContent[0], 1);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize, false);
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
	
		return;
	}
	// Make 15% Mats only 3% On OverUps
	if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) > 40)
	{
		if (tITEM_INFO2->iIndex == 1023)
		{
			iValue = 1;
		}
	}
	//tProbability1 = 125 - (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + iValue) * 3 + (int)((float)mAVATAR_OBJECT[tUserIndex].GetLuck() / 100.0f);
	tProbability1 = 103 - (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + iValue) * 3 + (int)((float)mAVATAR_OBJECT[tUserIndex].GetLuck() / 100.0f);
	if (tProbability1 < 5)
	{
		tProbability1 = 5;
		
		
	}
	
	
	// Over Ups chance is 30% Success
	if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) > 40)
	{
		tProbability1 = 30;
	}
	// Make Tickets 100% Success
	if ((tITEM_INFO2->iIndex == 1422) || (tITEM_INFO2->iIndex == 619) || (tITEM_INFO2->iIndex == 565) || (tITEM_INFO2->iIndex == 540) || (tITEM_INFO2->iIndex == 825) || (tITEM_INFO2->iIndex == 633) || (tITEM_INFO2->iIndex == 826) || (tITEM_INFO2->iIndex == 830))
	{
		tProbability1 = 100;
	}
	// Prevent Item from going straight to 150% when used 120 ET on item with existing enchant
	if (tITEM_INFO2->iIndex == 619)
	{
		if ((mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + iValue) >= 40)
		{
			iValue = 40 - (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]));
		}
	}
	if (tITEM_INFO2->iIndex == 565)
	{
		if ((mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + iValue) >= 40)
		{
			iValue = 40 - (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]));
		}
	}
	if (tITEM_INFO2->iIndex == 540)
	{
		if ((mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + iValue) >= 40)
		{
			iValue = 40 - (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]));
		}
	}
	if (tITEM_INFO2->iIndex == 825)
	{
		if ((mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + iValue) >= 50)
		{
			iValue = 50 - (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]));
		}
	}
	if (tITEM_INFO2->iIndex == 633)
	{
		if ((mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + iValue) >= 50)
		{
			iValue = 50 - (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]));
		}
	}
	if (tITEM_INFO2->iIndex == 826)
	{
		if ((mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + iValue) >= 40)
		{
			iValue = 40 - (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]));
		}
	}
	// Prevent Wings Going over 120
	if (tITEM_INFO1->iSort == 6)
	{
		if ((mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + iValue) >= 40)
		{
			iValue = 40 - (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]));
		}
	}
	//Prevent Going Above 120%
	if ((tITEM_INFO2->iIndex == 1019) || (tITEM_INFO2->iIndex == 1020) || (tITEM_INFO2->iIndex == 1021)
		|| (tITEM_INFO2->iIndex == 1022) || (tITEM_INFO2->iIndex == 1023)
		&& ((mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) < 40)))
	{
		if ((mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + iValue) >= 40)
		{
			iValue = 40 - (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]));
		}
	}

	tProbability2 = -57 + (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + iValue) * 3 - (int)((float)mAVATAR_OBJECT[tUserIndex].GetLuck() / 100.0f);
	if (tProbability2 < 0)
	{
		tProbability2 = 0;
	}
	// Items Above 120% have 100% Chance to Use PC on fail
	if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) > 40)
	{
		tProbability2 = 100;
	}

	tRandom = rand();
	if ((tRandom % 100) < (unsigned int)tProbability1)
	{
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= tCPCost;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] += iValue; //mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], iValue);
		//mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		
		if ((tITEM_INFO2->iIndex == 825) || (tITEM_INFO2->iIndex == 619) || (tITEM_INFO2->iIndex == 565) || (tITEM_INFO2->iIndex == 540))
		{
			mTRANSFER.B_IMPROVE_ITEM_RECV(0, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		else if (tITEM_INFO2->iIndex == 633)
		{
			mTRANSFER.B_IMPROVE_ITEM_RECV(0, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		else
		{
			mTRANSFER.B_IMPROVE_ITEM_RECV(0, tCost, iValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}



		if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) >= MAX_IMPROVE_ITEM_NUM) {
			tBroadcastInfoSort = 111;
			CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
			CopyMemory(&tBroadcastInfoData[4], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
		}
		// Wings 120% Broadcast Success
		if (tITEM_INFO1->iSort == 6)
		{
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) >= 40) {
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tBroadcastInfoSort = 115;
				CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
				CopyMemory(&tBroadcastInfoData[4], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
			}
		}
		return;
	}

	tRandom = rand();
	if ((tRandom % 100) < (unsigned int)tProbability2)
	{
		//For Wings
		if (tITEM_INFO1->iSort == 6)
		{
			if (mUSER[tUserIndex].mAvatarInfo.WingProtectionRune > 0)
			{
				mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
				mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= tCPCost;
				mUSER[tUserIndex].mAvatarInfo.WingProtectionRune--;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(99, mUSER[tUserIndex].mAvatarInfo.WingProtectionRune);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] -= 1;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
				mTRANSFER.B_IMPROVE_ITEM_RECV(1, 50, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
				return;
			}
			else
			{


				mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
				mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= tCPCost;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
				mTRANSFER.B_IMPROVE_ITEM_RECV(2, 50, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
				return;
			}
		}

		if ((mUSER[tUserIndex].mAvatarInfo.ProtectionCharm & 0x0000FFFF) > 0)
		{
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == 41)
			{
				mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
				mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= tCPCost;
				//mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 3, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] -= 1;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
				mTRANSFER.B_IMPROVE_ITEM_RECV(3, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) > 40)
			{
				mUSER[tUserIndex].mAvatarInfo.ProtectionCharm--;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(15, mUSER[tUserIndex].mAvatarInfo.ProtectionCharm);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
				mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= tCPCost;
				//mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 3, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] -= 1;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
				mTRANSFER.B_IMPROVE_ITEM_RECV(1, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}

			mUSER[tUserIndex].mAvatarInfo.ProtectionCharm--;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(15, mUSER[tUserIndex].mAvatarInfo.ProtectionCharm);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= tCPCost;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] -= 1;
			//mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			mTRANSFER.B_IMPROVE_ITEM_RECV(1, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == 41)
		{
			mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= tCPCost;
			//mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 3, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] -= 1;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			mTRANSFER.B_IMPROVE_ITEM_RECV(3, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) > 40)
		{
			mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= tCPCost;
			//mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 3, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] -= (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) - 40);
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			mTRANSFER.B_IMPROVE_ITEM_RECV(3, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= tCPCost;
		//mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 3, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_IMPROVE_ITEM_RECV(2, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
	mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= tCPCost;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] -= 1;
	//mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 4, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
	mTRANSFER.B_IMPROVE_ITEM_RECV(1, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

}
//	tProbability1 = (125 + (mAVATAR_OBJECT[tUserIndex].GetLuck() / 100)) - (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] + iValue) * 3);
//
//	if (tProbability1 < 5)
//	{
//		tProbability1 = 5;
//	}
//	if ((tITEM_INFO2->iIndex == 825) || (tITEM_INFO2->iIndex == 826))
//	{
//		tProbability1 = 100;
//	}
//	tProbability2 = -57 + (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] + iValue) * 3) - (mAVATAR_OBJECT[tUserIndex].GetLuck() / 100.0f);
//
//	if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) < 21)
//	{
//		tProbability2 = 0;
//	}
//
//	if (tProbability2 < 0)
//	{
//		tProbability2 = 0;
//	}
//
//	
//
//	if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == 40 && tITEM_INFO2->iIndex == 1422)
//	{
//		mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] += 1;
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
//		mTRANSFER.B_IMPROVE_ITEM_RECV(0, tCost, iValue);
//		mGAMELOG.GL_IMPROVE_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], "Mühür Açıldı");
//		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
//
//
//		return;
//	}
//
//	//wing upgrade
//
//	if (tITEM_INFO1->iSort == 6 && tITEM_INFO2->iIndex != 826)
//	{
//		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 50) 
//		{
//			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
//			return;
//		}
//		if ((mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + iValue) > 40)
//		{
//			iValue = 40 - mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
//		}
//
//		int itemNewImporveValue = (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + iValue) * 3;
//
//		if (itemNewImporveValue <= 60)
//		{
//			tProbability1 = 100;
//		}
//
//		if (itemNewImporveValue > 60 && itemNewImporveValue < 99)
//		{
//			tProbability1 = 50;
//		}
//
//		tRandom = rand();
//
//		if (tRandom % 100 < (unsigned int)tProbability1)//success
//		{
//			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 50;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] += iValue;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
//			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == 40)
//			{
//				//--------------//
//				//BROADCAST_INFO//
//				//--------------//
//				tBroadcastInfoSort = 115;
//				CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
//				CopyMemory(&tBroadcastInfoData[4], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
//				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
//				//--------------//
//				//--------------//
//				//--------------//
//			}
//			mGAMELOG.GL_IMPROVE_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - iValue, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], "Kanat Basma Başarılı");
//			mTRANSFER.B_IMPROVE_ITEM_RECV(0, tCost, iValue);
//			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
//
//			return;
//		}
//
//
//		tRandom = rand();
//
//		if (tRandom % 100 < (unsigned int)tProbability2)
//		{
//			if (mUSER[tUserIndex].mAvatarInfo.WingProtectionRune > 0)
//			{
//				mUSER[tUserIndex].mAvatarInfo.WingProtectionRune--;
//				mTRANSFER.B_AVATAR_CHANGE_INFO_2(99, mUSER[tUserIndex].mAvatarInfo.WingProtectionRune);
//				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
//				mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 50;
//				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] -= 1;
//				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
//				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
//				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
//				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
//				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
//				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
//				mGAMELOG.GL_IMPROVE_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - iValue, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], "Kanat Koruyucu Kullanıldı");
//				mTRANSFER.B_IMPROVE_ITEM_RECV(1, tCost, iValue);
//				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
//
//				return;
//			}
//			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 50;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
//			mGAMELOG.GL_IMPROVE_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 0, "Kanat Kırıldı");
//			mTRANSFER.B_IMPROVE_ITEM_RECV(2, tCost, 0);
//			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
//
//			return;
//		}
//
//		iValue = -1;
//
//		if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) - iValue < 0)
//		{
//			iValue = 0;
//		}
//
//		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 50;
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] += iValue;
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
//		mGAMELOG.GL_IMPROVE_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - iValue, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], "Kanat Basma Başarısız");
//		mTRANSFER.B_IMPROVE_ITEM_RECV(1, tCost, iValue);
//		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
//
//
//		return;
//	}
//
//	if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) < 40)
//	{
//		tRandom = rand();
//
//		if (tRandom % 100 < (unsigned int)tProbability1)
//		{
//			mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
//
//			if ((mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + iValue) > 40)
//			{
//				iValue = 40 - mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
//			}
//
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], iValue);
//			//mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
//			mGAMELOG.GL_IMPROVE_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - iValue, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], "Item Basma Başarılı");
//			mTRANSFER.B_IMPROVE_ITEM_RECV(0, tCost, iValue);
//			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
//
//			return;
//		}
//
//		tRandom = rand();
//
//		if ((tRandom % 100) < (unsigned int)tProbability2)
//		{
//
//			if (mUSER[tUserIndex].mAvatarInfo.ProtectionCharm > 0)
//			{
//				--mUSER[tUserIndex].mAvatarInfo.ProtectionCharm;
//				mTRANSFER.B_AVATAR_CHANGE_INFO_2(15, mUSER[tUserIndex].mAvatarInfo.ProtectionCharm);
//				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
//				mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
//				iValue = -1;
//				//mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 4, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
//				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] += iValue;
//				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
//				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
//				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
//				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
//				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
//				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
//				mGAMELOG.GL_IMPROVE_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - iValue, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], "Kabuk Kullanıldı");
//				mTRANSFER.B_IMPROVE_ITEM_RECV(1, tCost, iValue);
//				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
//
//				return;
//			}
//
//			mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
//			mGAMELOG.GL_IMPROVE_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - iValue, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], "Item Kırıldı");
//			mTRANSFER.B_IMPROVE_ITEM_RECV(2, tCost, 0);
//			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
//
//			return;
//		}
//
//		mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
//		iValue = -1;
//
//		if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) - iValue < 0)
//		{
//			iValue = 0;
//		}
//
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] += iValue;
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
//		mGAMELOG.GL_IMPROVE_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - iValue, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], "Item Basma Başarısız");
//		mTRANSFER.B_IMPROVE_ITEM_RECV(1, tCost, iValue);
//		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
//
//		return;
//	}
//
//	if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) > 40)
//	{
//		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != 1023
//			&& mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != 1243
//			&& mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != 1437)
//		{
//			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
//			return;
//		}
//
//		switch (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0])
//		{
//		case 1023:
//			iValue = 1;
//			tProbability1 = 40;
//			break;
//		case 1243:
//			iValue = 2;
//			tProbability1 = 40;
//			break;
//		case 1437:
//			iValue = 2;
//			tProbability1 = 40;
//			break;
//		default:
//			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
//			return;
//		}
//		if (mUSER[tUserIndex].mAuthInfo.AuthType == 1)
//		{
//			tProbability1 = 200;
//		}
//
//		tRandom = rand();
//
//		if ((tRandom % 100) < tProbability1)
//		{
//			if ((mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + iValue) > 50)
//			{
//				iValue = MAX_IMPROVE_ITEM_NUM - mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
//			}
//
//			mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], iValue);
//			//mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
//			mGAMELOG.GL_IMPROVE_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - iValue, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], "Item Basma Başarılı");
//			mTRANSFER.B_IMPROVE_ITEM_RECV(0, tCost, iValue);
//			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
//
//
//			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == MAX_IMPROVE_ITEM_NUM) {
//				//--------------//
//				//BROADCAST_INFO//
//				//--------------//
//				tBroadcastInfoSort = 111;
//				CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
//				CopyMemory(&tBroadcastInfoData[4], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
//				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
//				//--------------//
//				//--------------//
//				//--------------//
//			}
//
//			return;
//		}
//
//		if (mUSER[tUserIndex].mAvatarInfo.KesinKabuk > 0 && mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] > 41)
//		{
//
//			--mUSER[tUserIndex].mAvatarInfo.KesinKabuk;
//			mTRANSFER.B_AVATAR_CHANGE_INFO_2(104, mUSER[tUserIndex].mAvatarInfo.KesinKabuk);
//			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
//			mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
//			iValue = 0;
//			//mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 4, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] += iValue;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
//			mGAMELOG.GL_IMPROVE_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - iValue, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], "Kesin Kabuk Kullanıldı");
//			mTRANSFER.B_IMPROVE_ITEM_RECV(4, tCost, iValue);
//			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
//
//			return;
//		}
//
//		if (mUSER[tUserIndex].mAvatarInfo.ProtectionCharm > 0 && mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] > 41)
//		{
//			--mUSER[tUserIndex].mAvatarInfo.ProtectionCharm;
//			mTRANSFER.B_AVATAR_CHANGE_INFO_2(15, mUSER[tUserIndex].mAvatarInfo.ProtectionCharm);
//			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
//			mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
//			iValue = -1;
//			//mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 4, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] += iValue;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
//			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
//			mGAMELOG.GL_IMPROVE_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - iValue, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], "Kabuk Kullanıldı");
//			mTRANSFER.B_IMPROVE_ITEM_RECV(1, tCost, iValue);
//			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
//
//			return;
//		}
//
//		mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
//		//mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 4, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 40 - mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]));
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
//		mGAMELOG.GL_IMPROVE_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 0, "Item Mühürlendi");
//		mTRANSFER.B_IMPROVE_ITEM_RECV(3, tCost, iValue);
//		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
//
//		return;
//	}
//
//}
//W_ADD_ITEM_SEND
//W_ADD_ITEM_SEND
void W_ADD_ITEM_SEND(int tUserIndex)
{
	__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	unsigned int tRandom = 0;
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	CopyMemory(&tPage1, &tPacket[1], 4);
	CopyMemory(&tIndex1, &tPacket[5], 4);
	CopyMemory(&tPage2, &tPacket[9], 4);
	CopyMemory(&tIndex2, &tPacket[13], 4);
	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	ITEM_INFO* tITEM_INFO1;
	ITEM_INFO* tITEM_INFO2;
	int tCost;
	int tProbability;
	int tProbability2;
	int SetBonusPrice = 1;

	if ((tPage1 == 1) || (tPage2 == 1))
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
	if (tITEM_INFO1 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tITEM_INFO1->iType != 3) && (tITEM_INFO1->iType != 4))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tITEM_INFO1->iSort != 7) && (tITEM_INFO1->iSort != 8) && (tITEM_INFO1->iSort != 9) && (tITEM_INFO1->iSort != 10) && (tITEM_INFO1->iSort != 11) && (tITEM_INFO1->iSort != 12) && (tITEM_INFO1->iSort != 13) && (tITEM_INFO1->iSort != 14) && (tITEM_INFO1->iSort != 15) && (tITEM_INFO1->iSort != 16) && (tITEM_INFO1->iSort != 17) && (tITEM_INFO1->iSort != 18) && (tITEM_INFO1->iSort != 19) && (tITEM_INFO1->iSort != 20) && (tITEM_INFO1->iSort != 21))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tITEM_INFO1->iCheckHighImprove != 2)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) >= MAX_ADD_ITEM_NUM)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
	if (tITEM_INFO2 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if ((mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4]) > 0) ||
		(mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4]) > 0))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}


	if (tITEM_INFO2->iIndex == 2001 ||
		tITEM_INFO2->iIndex == 2002 ||
		tITEM_INFO2->iIndex == 2003
		) {
		goto geckontrol;
	}

	if (tITEM_INFO2->iType != 3 && tITEM_INFO2->iType != 4)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tITEM_INFO2->iSort != 7) && (tITEM_INFO2->iSort != 8) && (tITEM_INFO2->iSort != 9) && (tITEM_INFO2->iSort != 10) && (tITEM_INFO2->iSort != 11) && (tITEM_INFO2->iSort != 12) && (tITEM_INFO2->iSort != 13) && (tITEM_INFO2->iSort != 14) && (tITEM_INFO2->iSort != 15) && (tITEM_INFO2->iSort != 16) && (tITEM_INFO2->iSort != 17) && (tITEM_INFO2->iSort != 18) && (tITEM_INFO2->iSort != 19) && (tITEM_INFO2->iSort != 20) && (tITEM_INFO2->iSort != 21))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (tITEM_INFO1->iSort != tITEM_INFO2->iSort)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	switch (tITEM_INFO1->iType)
	{
	case 3:
		if ((tITEM_INFO2->iLevel + tITEM_INFO2->iMartialLevel) != (tITEM_INFO1->iLevel + tITEM_INFO1->iMartialLevel))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 4:
		switch (tITEM_INFO1->iLevel)
		{
		case 100:
			if (tITEM_INFO2->iLevel != 95)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 110:
			if (tITEM_INFO2->iLevel != 105)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 115:
			if (tITEM_INFO2->iLevel != 114)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 118:
			if (tITEM_INFO2->iLevel != 117)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 121:
			if (tITEM_INFO2->iLevel != 120)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 124:
			if (tITEM_INFO2->iLevel != 123)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 127:
			if (tITEM_INFO2->iLevel != 126)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 130:
			if (tITEM_INFO2->iLevel != 129)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 133:
			if (tITEM_INFO2->iLevel != 132)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 136:
			if (tITEM_INFO2->iLevel != 135)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 139:
			if (tITEM_INFO2->iLevel != 138)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 142:
			if (tITEM_INFO2->iLevel != 141)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 145:
			if (tITEM_INFO1->iMartialLevel < 1)
			{
				if ((tITEM_INFO2->iLevel != 144) && (tITEM_INFO2->iLevel != 145))
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
			else
			{
				if ((tITEM_INFO2->iLevel + tITEM_INFO2->iMartialLevel) != (tITEM_INFO1->iLevel + tITEM_INFO1->iMartialLevel))
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
			break;
		}
		break;
	}
	if (tITEM_INFO1->iSetBonus == 2)
	{
		if (tITEM_INFO2->iSetBonus != 2)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO1->iType != tITEM_INFO2->iType)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		SetBonusPrice = 100;
	}

geckontrol:
	if (tITEM_INFO2->iIndex == 2001 || tITEM_INFO2->iIndex == 2002 || tITEM_INFO2->iIndex == 2003)
	{
		if (tITEM_INFO1->iSetBonus == 2)
		{
			SetBonusPrice = 100;
		}
	}

	switch (mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]))
	{
	case  0:
		tCost = 1000000 * SetBonusPrice;
		tProbability = 65;
		break;
	case  1:
		tCost = 1500000 * SetBonusPrice;
		tProbability = 60;
		break;
	case  2:
		tCost = 2000000 * SetBonusPrice;
		tProbability = 55;
		break;
	case  3:
		tCost = 2500000 * SetBonusPrice;
		tProbability = 50;
		break;
	case  4:
		tCost = 3000000 * SetBonusPrice;
		tProbability = 45;
		break;
	case  5:
		tCost = 3500000 * SetBonusPrice;
		tProbability = 40;
		break;
	case  6:
		tCost = 4000000 * SetBonusPrice;
		tProbability = 35;
		break;
	case  7:
		tCost = 4500000 * SetBonusPrice;
		tProbability = 30;
		break;
	case  8:
		tCost = 5000000 * SetBonusPrice;
		tProbability = 25;
		break;
	case  9:
		tCost = 5500000 * SetBonusPrice;
		tProbability = 20;
		break;
	case 10:
		tCost = 6000000 * SetBonusPrice;
		tProbability = 15;
		break;
	case 11:
		tCost = 6500000 * SetBonusPrice;
		tProbability = 10;
		break;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aMoney < tCost)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (tITEM_INFO2->iIndex == 2001) // %50 combine ticket
	{
		//Success
		tRandom = rand() % 100;
		if (tRandom < 50)
		{
			mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 1);
			mGAMELOG.GL_ADD_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - 1), mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - 1), tCost, "Birleştime Başarılı", tITEM_INFO2->iIndex, tITEM_INFO2->iName);
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			mTRANSFER.B_ADD_ITEM_RECV(0, tCost);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		else //fail
		{
			mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
			mGAMELOG.GL_ADD_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - 1), mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - 1), tCost, "Birleştime Başrısız Item Yandı", tITEM_INFO2->iIndex, tITEM_INFO2->iName);
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			mTRANSFER.B_ADD_ITEM_RECV(2, tCost);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
	}

	if (tITEM_INFO2->iIndex == 2002)// %80 combine ticket
	{
		//Success
		tRandom = rand() % 100;
		if (tRandom < 80)
		{
			mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 1);
			mGAMELOG.GL_ADD_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - 1), mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - 1), tCost, "Birleştime Başarılı", tITEM_INFO2->iIndex, tITEM_INFO2->iName);
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			mTRANSFER.B_ADD_ITEM_RECV(0, tCost);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		else //fail
		{
			mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
			mGAMELOG.GL_ADD_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - 1), mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - 1), tCost, "Birleştime Başrısız Item Yandı", tITEM_INFO2->iIndex, tITEM_INFO2->iName);
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			mTRANSFER.B_ADD_ITEM_RECV(2, tCost);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
	}

	if (tITEM_INFO2->iIndex == 2003)//%100 combine ticket
	{
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 1);
		mGAMELOG.GL_ADD_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - 1), mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - 1), tCost, "Birleştime Başarılı", tITEM_INFO2->iIndex, tITEM_INFO2->iName);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_ADD_ITEM_RECV(0, tCost);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	}

	//failure rate
	tProbability2 = 30;
	/** 2009. 12. 16 : °­È­, Á¶ÇÕ, ½Â±ÞºÎ(Æ¯) ¾ÆÀÌÅÛ °³¹ß (wolf) */
	if (mUSER[tUserIndex].mAvatarInfo.LuckyCombine > 0)
	{
		mUSER[tUserIndex].mAvatarInfo.LuckyCombine--;
		tProbability += 10;
		tProbability2 = -1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(27, mUSER[tUserIndex].mAvatarInfo.LuckyCombine);
		mUSER[tUserIndex].Send(TRUE, (char*)mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
	}

	tProbability += (int)((float)mAVATAR_OBJECT[tUserIndex].GetLuck() / 300.0f);
	tProbability += 20;
	tRandom = rand();
	if ((tRandom % 100) < (unsigned int)tProbability)
	{
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 1);
		mGAMELOG.GL_ADD_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - 1), mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - 1), tCost, "Birleştime Başarılı", tITEM_INFO2->iIndex, tITEM_INFO2->iName);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_ADD_ITEM_RECV(0, tCost);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	}

	if ((tRandom % 100) < (unsigned int)tProbability2)
	{
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
		mGAMELOG.GL_ADD_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - 1), mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - 1), tCost, "Birleştime Başrısız Item Yandı", tITEM_INFO2->iIndex, tITEM_INFO2->iName);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_ADD_ITEM_RECV(2, tCost);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	}


	mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
	mGAMELOG.GL_ADD_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - 1), mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]), tCost, "BAŞARISIZ", tITEM_INFO2->iIndex, tITEM_INFO2->iName);
	mTRANSFER.B_ADD_ITEM_RECV(1, tCost);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

}
//W_EXCHANGE_ITEM_SEND 
void W_EXCHANGE_ITEM_SEND(int tUserIndex)
{

	__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	unsigned int tRandom = 0;
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tPage;
	int tIndex;
	int tSort;
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tPage, &tPacket[5], 4);
	CopyMemory(&tIndex, &tPacket[9], 4);
	if ((tPage < 0) || (tPage > 1) || (tIndex < 0) || (tIndex > (MAX_INVENTORY_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	ITEM_INFO* tITEM_INFO1;
	ITEM_INFO* tITEM_INFO2;
	int tCost;
	int tTribeItemList[9];
	int tValue[6];

	if (tSort == 0)
	{

		if (tPage == 1)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0]);


		if (tITEM_INFO1 == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO1->iType != 3 && tITEM_INFO1->iType != 4)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tITEM_INFO1->iSort != 7) && (tITEM_INFO1->iSort != 8) && (tITEM_INFO1->iSort != 9) && (tITEM_INFO1->iSort != 10) && (tITEM_INFO1->iSort != 11) && (tITEM_INFO1->iSort != 12) && (tITEM_INFO1->iSort != 13) && (tITEM_INFO1->iSort != 14) && (tITEM_INFO1->iSort != 15) && (tITEM_INFO1->iSort != 16) && (tITEM_INFO1->iSort != 17) && (tITEM_INFO1->iSort != 18) && (tITEM_INFO1->iSort != 19) && (tITEM_INFO1->iSort != 20) && (tITEM_INFO1->iSort != 21))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO1->iCheckExchange != 2)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		if (tITEM_INFO1->iType == 3)
		{
			switch (tITEM_INFO1->iLevel)
			{
			case 45:
				tCost = 1000000;
				break;
			case 55:
				tCost = 1200000;
				break;
			case 65:
				tCost = 1400000;
				break;
			case 75:
				tCost = 1600000;
				break;
			case 85:
				tCost = 1800000;
				break;
			case 95:
				tCost = 2000000;
				break;
			case 105:
				tCost = 2200000;
				break;
			case 114:
				tCost = 2400000;
				break;
			case 117:
				tCost = 2600000;
				break;
			case 120:
				tCost = 2800000;
				break;
			case 123:
				tCost = 3000000;
				break;
			case 126:
				tCost = 3200000;
				break;
			case 129:
				tCost = 3400000;
				break;
			case 132:
				tCost = 3600000;
				break;
			case 135:
				tCost = 3800000;
				break;
			case 138:
				tCost = 4000000;
				break;
			case 141:
				tCost = 4200000;
				break;
			case 144:
				tCost = 4400000;
				break;
			case 145:
				switch (tITEM_INFO1->iMartialLevel)
				{
				case 0:
					tCost = 4600000;
					break;
				case 1:
					tCost = 4800000;
					break;
				case 2:
					tCost = 5000000;
					break;
				case 3:
					tCost = 5200000;
					break;
				case 4:
					tCost = 5400000;
					break;
				case 5:
					tCost = 5600000;
					break;
				case 6:
					tCost = 5800000;
					break;
				case 7:
					tCost = 6000000;
					break;
				case 8:
					tCost = 6200000;
					break;
				case 9:
					tCost = 6400000;
					break;
				case 10:
					tCost = 6600000;
					break;
				case 11:
					tCost = 6800000;
					break;
				case 12:
					tCost = 7000000;
					break;
				}
				break;

			}
		}
		else if (tITEM_INFO1->iType == 4)
		{
			switch (tITEM_INFO1->iLevel)
			{
			case 100:
				tCost = 4000000;
				break;
			case 110:
				tCost = 4400000;
				break;
			case 113:
				tCost = 4800000;
				break;
			case 115:
				tCost = 5200000;
				break;
			case 118:
				tCost = 5600000;
				break;
			case 121:
				tCost = 6000000;
				break;
			case 124:
				tCost = 6400000;
				break;
			case 127:
				tCost = 6800000;
				break;
			case 130:
				tCost = 7200000;
				break;
			case 133:
				tCost = 7600000;
				break;
			case 136:
				tCost = 8000000;
				break;
			case 139:
				tCost = 8400000;
				break;
			case 142:
				tCost = 8800000;
				break;
			case 145:
				switch (tITEM_INFO1->iMartialLevel)
				{
				case 0:
					tCost = 9200000;
					break;
				case 1:
					tCost = 9600000;
					break;
				case 2:
					tCost = 10000000;
					break;
				case 3:
					tCost = 10400000;
					break;
				case 4:
					tCost = 10800000;
					break;
				case 5:
					tCost = 11200000;
					break;
				case 6:
					tCost = 11600000;
					break;
				case 7:
					tCost = 12000000;
					break;
				case 8:
					tCost = 12400000;
					break;
				case 9:
					tCost = 12800000;
					break;
				case 10:
					tCost = 13200000;
					break;
				case 11:
					tCost = 13600000;
					break;
				case 12:
					tCost = 14000000;
					break;
				}
				break;
			}
		}

		if (mUSER[tUserIndex].mAvatarInfo.aMoney < tCost)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
		{
		case 0:
			tTribeItemList[0] = 7;
			tTribeItemList[1] = 8;
			tTribeItemList[2] = 9;
			tTribeItemList[3] = 10;
			tTribeItemList[4] = 11;
			tTribeItemList[5] = 12;
			tTribeItemList[6] = 13;
			tTribeItemList[7] = 14;
			tTribeItemList[8] = 15;
			break;
		case 1:
			tTribeItemList[0] = 7;
			tTribeItemList[1] = 8;
			tTribeItemList[2] = 9;
			tTribeItemList[3] = 10;
			tTribeItemList[4] = 11;
			tTribeItemList[5] = 12;
			tTribeItemList[6] = 16;
			tTribeItemList[7] = 17;
			tTribeItemList[8] = 18;
			break;
		case 2:
			tTribeItemList[0] = 7;
			tTribeItemList[1] = 8;
			tTribeItemList[2] = 9;
			tTribeItemList[3] = 10;
			tTribeItemList[4] = 11;
			tTribeItemList[5] = 12;
			tTribeItemList[6] = 19;
			tTribeItemList[7] = 20;
			tTribeItemList[8] = 21;
			break;
		}
		tRandom = rand();

		tITEM_INFO2 = mITEM.Return((tITEM_INFO1->iLevel + tITEM_INFO1->iMartialLevel), tITEM_INFO1->iType, tTribeItemList[(rand() % 9)], tITEM_INFO1);

		if ((tITEM_INFO2 == NULL) || (tITEM_INFO2->iIndex == tITEM_INFO1->iIndex))
		{
			//mGAMELOG.GL_637_EXCHANGE_ITEM(tUserIndex, 3, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], tCost);
			mTRANSFER.B_EXCHANGE_ITEM_RECV(1, tCost, &tValue[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
		tValue[0] = tITEM_INFO2->iIndex;
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2];
		tValue[3] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3];
		tValue[4] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4];
		tValue[5] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = tValue[5];
		mGAMELOG.GL_EXCHANGE_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName, tITEM_INFO2->iIndex, tITEM_INFO2->iName);
		mTRANSFER.B_EXCHANGE_ITEM_RECV(0, tCost, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	}
	else if (tSort == 1)
	{
		mTRANSFER.B_EXCHANGE_ITEM_RECV(1, tCost, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	}

}
//W_HIGH_ITEM_SEND 
void W_HIGH_ITEM_SEND(int tUserIndex)
{
	__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	unsigned int tRandom = 0;
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	CopyMemory(&tPage1, &tPacket[1], 4);
	CopyMemory(&tIndex1, &tPacket[5], 4);
	CopyMemory(&tPage2, &tPacket[9], 4);
	CopyMemory(&tIndex2, &tPacket[13], 4);
	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	ITEM_INFO* tITEM_INFO1;
	ITEM_INFO* tITEM_INFO2;
	ITEM_INFO* tITEM_INFO3;
	int tCost;
	int tItemLevel;
	int tProbability;
	int tValue[6];

	if ((tPage1 == 1) || (tPage2 == 1))
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
	if (tITEM_INFO1 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tITEM_INFO1->iType != 3) && (tITEM_INFO1->iType != 4))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tITEM_INFO1->iSort != 7) && (tITEM_INFO1->iSort != 8) && (tITEM_INFO1->iSort != 9) && (tITEM_INFO1->iSort != 10) && (tITEM_INFO1->iSort != 11) && (tITEM_INFO1->iSort != 12) && (tITEM_INFO1->iSort != 13) && (tITEM_INFO1->iSort != 14) && (tITEM_INFO1->iSort != 15) && (tITEM_INFO1->iSort != 16) && (tITEM_INFO1->iSort != 17) && (tITEM_INFO1->iSort != 18) && (tITEM_INFO1->iSort != 19) && (tITEM_INFO1->iSort != 20) && (tITEM_INFO1->iSort != 21))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tITEM_INFO1->iCheckHighItem != 2)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	
	if ((mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) < 4) || 
		(mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) < 1))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tITEM_INFO1->iMartialLevel >= 12)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
	if (tITEM_INFO2 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tITEM_INFO2->iIndex != 1024) && (tITEM_INFO2->iIndex != 1025))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	switch (tITEM_INFO1->iType)
	{
	case 3:
		switch (tITEM_INFO1->iLevel)
		{
		case  45:
			tCost = 100000;
			tItemLevel = 55;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 520;
			}
			else
			{
				tProbability = 570;
			}
			break;
		case  55:
			tCost = 200000;
			tItemLevel = 65;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 490;
			}
			else
			{
				tProbability = 540;
			}
			break;
		case  65:
			tCost = 300000;
			tItemLevel = 75;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 460;
			}
			else
			{
				tProbability = 510;
			}
			break;
		case  75:
			tCost = 400000;
			tItemLevel = 85;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 430;
			}
			else
			{
				tProbability = 480;
			}
			break;
		case  85:
			tCost = 500000;
			tItemLevel = 95;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 400;
			}
			else
			{
				tProbability = 450;
			}
			break;
		case  95:
			tCost = 600000;
			tItemLevel = 105;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 370;
			}
			else
			{
				tProbability = 420;
			}
			break;
		case 105:
			tCost = 700000;
			tItemLevel = 114;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 340;
			}
			else
			{
				tProbability = 390;
			}
			break;
		case 114:
			tCost = 800000;
			tItemLevel = 117;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 310;
			}
			else
			{
				tProbability = 360;
			}
			break;
		case 117:
			tCost = 900000;
			tItemLevel = 120;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 280;
			}
			else
			{
				tProbability = 330;
			}
			break;
		case 120:
			tCost = 1000000;
			tItemLevel = 123;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 250;
			}
			else
			{
				tProbability = 300;
			}
			break;
		case 123:
			tCost = 1100000;
			tItemLevel = 126;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 220;
			}
			else
			{
				tProbability = 270;
			}
			break;
		case 126:
			tCost = 1200000;
			tItemLevel = 129;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 190;
			}
			else
			{
				tProbability = 240;
			}
			break;
		case 129:
			tCost = 1300000;
			tItemLevel = 132;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 160;
			}
			else
			{
				tProbability = 210;
			}
			break;
		case 132:
			tCost = 1400000;
			tItemLevel = 135;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 130;
			}
			else
			{
				tProbability = 180;
			}
			break;
		case 135:
			tCost = 1500000;
			tItemLevel = 138;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 100;
			}
			else
			{
				tProbability = 150;
			}
			break;
		case 138:
			tCost = 1600000;
			tItemLevel = 141;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 70;
			}
			else
			{
				tProbability = 120;
			}
			break;
		case 141:
			tCost = 1700000;
			tItemLevel = 144;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 40;
			}
			else
			{
				tProbability = 90;
			}
			break;
		case 144:
			tCost = 1800000;
			tItemLevel = 145;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 10;
			}
			else
			{
				tProbability = 60;
			}
			break;
#ifdef __GOD__
		case 145:
			switch (tITEM_INFO1->iMartialLevel)
			{
			case  0:
				tCost = 1900000;
				tItemLevel = 146;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 10;
				}
				else
				{
					tProbability = 20;
				}
				break;
			case  1:
				tCost = 2000000;
				tItemLevel = 147;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 10;
				}
				else
				{
					tProbability = 20;
				}
				break;
			case  2:
				tCost = 2100000;
				tItemLevel = 148;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 10;
				}
				else
				{
					tProbability = 20;
				}
				break;
			case  3:
				tCost = 2200000;
				tItemLevel = 149;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 10;
				}
				else
				{
					tProbability = 20;
				}
				break;
			case  4:
				tCost = 2300000;
				tItemLevel = 150;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 10;
				}
				else
				{
					tProbability = 20;
				}
				break;
			case  5:
				tCost = 2400000;
				tItemLevel = 151;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 10;
				}
				else
				{
					tProbability = 20;
				}
				break;
			case  6:
				tCost = 2500000;
				tItemLevel = 152;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 10;
				}
				else
				{
					tProbability = 20;
				}
				break;
			case  7:
				tCost = 2600000;
				tItemLevel = 153;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 10;
				}
				else
				{
					tProbability = 20;
				}
				break;
			case  8:
				tCost = 2700000;
				tItemLevel = 154;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 10;
				}
				else
				{
					tProbability = 20;
				}
				break;
			case  9:
				tCost = 2800000;
				tItemLevel = 155;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 10;
				}
				else
				{
					tProbability = 20;
				}
				break;
			case 10:
				tCost = 2900000;
				tItemLevel = 156;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 10;
				}
				else
				{
					tProbability = 20;
				}
				break;
			case 11:
				tCost = 3000000;
				tItemLevel = 157;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 10;
				}
				else
				{
					tProbability = 20;
				}
				break;
			}
			break;
#endif
		}
		break;
	case 4:
		switch (tITEM_INFO1->iLevel)
		{
		case 100:
			tCost = 1000000;
			tItemLevel = 110;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 340;
			}
			else
			{
				tProbability = 390;
			}
			break;
		case 110:
			tCost = 2000000;
			tItemLevel = 115;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 310;
			}
			else
			{
				tProbability = 360;
			}
			break;
		case 115:
			tCost = 3000000;
			tItemLevel = 118;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 280;
			}
			else
			{
				tProbability = 330;
			}
			break;
		case 118:
			tCost = 4000000;
			tItemLevel = 121;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 250;
			}
			else
			{
				tProbability = 300;
			}
			break;
		case 121:
			tCost = 5000000;
			tItemLevel = 124;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 220;
			}
			else
			{
				tProbability = 270;
			}
			break;
		case 124:
			tCost = 6000000;
			tItemLevel = 127;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 190;
			}
			else
			{
				tProbability = 240;
			}
			break;
		case 127:
			tCost = 7000000;
			tItemLevel = 130;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 160;
			}
			else
			{
				tProbability = 210;
			}
			break;
		case 130:
			tCost = 8000000;
			tItemLevel = 133;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 130;
			}
			else
			{
				tProbability = 180;
			}
			break;
		case 133:
			tCost = 9000000;
			tItemLevel = 136;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 100;
			}
			else
			{
				tProbability = 150;
			}
			break;
		case 136:
			tCost = 10000000;
			tItemLevel = 139;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 70;
			}
			else
			{
				tProbability = 120;
			}
			break;
		case 139:
			tCost = 11000000;
			tItemLevel = 142;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 40;
			}
			else
			{
				tProbability = 90;
			}
			break;
		case 142:
			tCost = 12000000;
			tItemLevel = 145;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 1;
			}
			else
			{
				tProbability = 1;
			}
			break;
#ifdef __GOD__
		case 145:
			switch (tITEM_INFO1->iMartialLevel)
			{

				//upgrade_oranlar©¥
			case  0:
				tCost = 13000000;
				tItemLevel = 146;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case  1:
				tCost = 14000000;
				tItemLevel = 147;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case  2:
				tCost = 15000000;
				tItemLevel = 148;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case  3:
				tCost = 16000000;
				tItemLevel = 149;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case  4:
				tCost = 17000000;
				tItemLevel = 150;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 1;
				}
				break;
			case  5:
				tCost = 18000000;
				tItemLevel = 151;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 2;
				}
				else
				{
					tProbability = 4;
				}
				break;
			case  6:
				tCost = 19000000;
				tItemLevel = 152;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 2;
				}
				else
				{
					tProbability = 4;
				}
				break;
			case  7:
				tCost = 20000000;
				tItemLevel = 153;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 2;
				}
				else
				{
					tProbability = 4;
				}
				break;
			case  8:
				tCost = 21000000;
				tItemLevel = 154;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 2;
				}
				else
				{
					tProbability = 4;
				}
				break;
			case  9:
				tCost = 22000000;
				tItemLevel = 155;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 2;
				}
				else
				{
					tProbability = 4;
				}
				break;
			case 10:
				tCost = 23000000;
				tItemLevel = 156;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 2;
				}
				else
				{
					tProbability = 4;
				}
				break;
			case 11:
				tCost = 24000000;
				tItemLevel = 157;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 2;
				}
				else
				{
					tProbability = 4;
				}
				break;
			}
			break;
#endif
		}
		break;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aMoney < tCost)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	/** 2009. 12. 16 : °­È­, Á¶ÇÕ, ½Â±ÞºÎ(Æ¯) ¾ÆÀÌÅÛ °³¹ß (wolf) */

	tITEM_INFO3 = mITEM.Return_1(tItemLevel, tITEM_INFO1);
	if (tITEM_INFO3 == NULL)
	{
		//mGAMELOG.GL_635_HIGH_ITEM(tUserIndex, 4, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost, tITEM_INFO2->iIndex);
		mTRANSFER.B_HIGH_ITEM_RECV(2, tCost, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	tProbability += (int)((float)mAVATAR_OBJECT[tUserIndex].GetLuck() / 300.0f);
#ifdef __GOD__
#endif	
	tRandom = rand();
	//2010.1.18 : ±è¼º¼ö : ½Â±Þ È®·ü ¸Â°Ô ¼öÁ¤ (100 -> 1000À¸·Î º¯°æ¿¡ µû¸£ ¼öÄ¡ º¯°æ) __GOD__
	if ((tRandom % 10) < (unsigned int)tProbability)
	{
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
		tValue[0] = tITEM_INFO3->iIndex;
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		tValue[3] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3];
		tValue[4] = mUTIL.SetISIUValue((mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) - 4), (mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) - 1)); //Yukseltmedeki dusus oranı
		tValue[5] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5];
		//mGAMELOG.GL_635_HIGH_ITEM(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost, tITEM_INFO2->iIndex);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
		//mGAMELOG.GL_635_HIGH_ITEM(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost, tITEM_INFO2->iIndex);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_HIGH_ITEM_RECV(0, tCost, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	}
	mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
	//mGAMELOG.GL_635_HIGH_ITEM(tUserIndex, 3, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost, tITEM_INFO2->iIndex);
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
	mTRANSFER.B_HIGH_ITEM_RECV(1, tCost, &tValue[0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

}
//W_LOW_ITEM_SEND 
void W_LOW_ITEM_SEND(int tUserIndex)
{
	__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	unsigned int tRandom = 0;
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	CopyMemory(&tPage1, &tPacket[1], 4);
	CopyMemory(&tIndex1, &tPacket[5], 4);
	CopyMemory(&tPage2, &tPacket[9], 4);
	CopyMemory(&tIndex2, &tPacket[13], 4);
	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	ITEM_INFO* tITEM_INFO1;
	ITEM_INFO* tITEM_INFO2;
	ITEM_INFO* tITEM_INFO3;
	int tCost;
	int tItemLevel;
	int tProbability;
	int tValue[6];

	if ((tPage1 == 1) || (tPage2 == 1))
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
	if (tITEM_INFO1 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tITEM_INFO1->iType != 3) && (tITEM_INFO1->iType != 4))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tITEM_INFO1->iSort != 7) && (tITEM_INFO1->iSort != 8) && (tITEM_INFO1->iSort != 9) && (tITEM_INFO1->iSort != 10) && (tITEM_INFO1->iSort != 11) && (tITEM_INFO1->iSort != 12) && (tITEM_INFO1->iSort != 13) && (tITEM_INFO1->iSort != 14) && (tITEM_INFO1->iSort != 15) && (tITEM_INFO1->iSort != 16) && (tITEM_INFO1->iSort != 17) && (tITEM_INFO1->iSort != 18) && (tITEM_INFO1->iSort != 19) && (tITEM_INFO1->iSort != 20) && (tITEM_INFO1->iSort != 21))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tITEM_INFO1->iCheckLowItem != 2)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	switch (tITEM_INFO1->iType)
	{
	case 3:
		if (tITEM_INFO1->iLevel <= 45)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 4:
		if (tITEM_INFO1->iLevel <= 100)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	}
	tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
	if (tITEM_INFO2 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tITEM_INFO2->iIndex != 1024) && (tITEM_INFO2->iIndex != 1025))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	switch (tITEM_INFO1->iType)
	{
	case 3:
		switch (tITEM_INFO1->iLevel)
		{
		case  55:
			tCost = 100000;
			tItemLevel = 45;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 52;
			}
			else
			{
				tProbability = 57;
			}
			break;
		case  65:
			tCost = 200000;
			tItemLevel = 55;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 49;
			}
			else
			{
				tProbability = 54;
			}
			break;
		case  75:
			tCost = 300000;
			tItemLevel = 65;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 46;
			}
			else
			{
				tProbability = 51;
			}
			break;
		case  85:
			tCost = 400000;
			tItemLevel = 75;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 43;
			}
			else
			{
				tProbability = 48;
			}
			break;
		case  95:
			tCost = 500000;
			tItemLevel = 85;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 40;
			}
			else
			{
				tProbability = 45;
			}
			break;
		case 105:
			tCost = 600000;
			tItemLevel = 95;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 37;
			}
			else
			{
				tProbability = 42;
			}
			break;
		case 114:
			tCost = 700000;
			tItemLevel = 105;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 34;
			}
			else
			{
				tProbability = 39;
			}
			break;
		case 117:
			tCost = 800000;
			tItemLevel = 114;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 31;
			}
			else
			{
				tProbability = 36;
			}
			break;
		case 120:
			tCost = 900000;
			tItemLevel = 117;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 28;
			}
			else
			{
				tProbability = 33;
			}
			break;
		case 123:
			tCost = 1000000;
			tItemLevel = 120;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 25;
			}
			else
			{
				tProbability = 30;
			}
			break;
		case 126:
			tCost = 1100000;
			tItemLevel = 123;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 22;
			}
			else
			{
				tProbability = 27;
			}
			break;
		case 129:
			tCost = 1200000;
			tItemLevel = 126;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 19;
			}
			else
			{
				tProbability = 24;
			}
			break;
		case 132:
			tCost = 1300000;
			tItemLevel = 129;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 16;
			}
			else
			{
				tProbability = 21;
			}
			break;
		case 135:
			tCost = 1400000;
			tItemLevel = 132;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 13;
			}
			else
			{
				tProbability = 18;
			}
			break;
		case 138:
			tCost = 1500000;
			tItemLevel = 135;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 10;
			}
			else
			{
				tProbability = 15;
			}
			break;
		case 141:
			tCost = 1600000;
			tItemLevel = 138;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 7;
			}
			else
			{
				tProbability = 12;
			}
			break;
		case 144:
			tCost = 1700000;
			tItemLevel = 141;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 4;
			}
			else
			{
				tProbability = 9;
			}
			break;
		case 145:
#ifdef __GOD__
			switch (tITEM_INFO1->iMartialLevel)
			{
			case  0:
#endif
				tCost = 1800000;
				tItemLevel = 144;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 6;
				}
				break;
#ifdef __GOD__
			case  1:
				tCost = 1900000;
				tItemLevel = 145;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case  2:
				tCost = 2000000;
				tItemLevel = 146;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case  3:
				tCost = 2100000;
				tItemLevel = 147;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case  4:
				tCost = 2200000;
				tItemLevel = 148;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case  5:
				tCost = 2300000;
				tItemLevel = 149;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case  6:
				tCost = 2400000;
				tItemLevel = 150;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case  7:
				tCost = 2500000;
				tItemLevel = 151;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case  8:
				tCost = 2600000;
				tItemLevel = 152;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case  9:
				tCost = 2700000;
				tItemLevel = 153;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 10:
				tCost = 2800000;
				tItemLevel = 154;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 11:
				tCost = 2900000;
				tItemLevel = 155;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 12:
				tCost = 3000000;
				tItemLevel = 156;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			}
			break;
#endif
		}
		break;
	case 4:
		switch (tITEM_INFO1->iLevel)
		{
		case 110:
			tCost = 1000000;
			tItemLevel = 100;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 34;
			}
			else
			{
				tProbability = 39;
			}
			break;
		case 115:
			tCost = 2000000;
			tItemLevel = 110;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 31;
			}
			else
			{
				tProbability = 36;
			}
			break;
		case 118:
			tCost = 3000000;
			tItemLevel = 115;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 28;
			}
			else
			{
				tProbability = 33;
			}
			break;
		case 121:
			tCost = 4000000;
			tItemLevel = 118;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 25;
			}
			else
			{
				tProbability = 30;
			}
			break;
		case 124:
			tCost = 5000000;
			tItemLevel = 121;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 22;
			}
			else
			{
				tProbability = 27;
			}
			break;
		case 127:
			tCost = 6000000;
			tItemLevel = 124;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 19;
			}
			else
			{
				tProbability = 24;
			}
			break;
		case 130:
			tCost = 7000000;
			tItemLevel = 127;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 16;
			}
			else
			{
				tProbability = 21;
			}
			break;
		case 133:
			tCost = 8000000;
			tItemLevel = 130;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 13;
			}
			else
			{
				tProbability = 18;
			}
			break;
		case 136:
			tCost = 9000000;
			tItemLevel = 133;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 10;
			}
			else
			{
				tProbability = 15;
			}
			break;
		case 139:
			tCost = 10000000;
			tItemLevel = 136;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 7;
			}
			else
			{
				tProbability = 12;
			}
			break;
		case 142:
			tCost = 11000000;
			tItemLevel = 139;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 4;
			}
			else
			{
				tProbability = 9;
			}
			break;
		case 145:
#ifdef __GOD__
			switch (tITEM_INFO1->iMartialLevel)
			{
			case  0:
#endif
				tCost = 12000000;
				tItemLevel = 142;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 6;
				}
				break;
#ifdef __GOD__
			case  1:
				tCost = 13000000;
				tItemLevel = 145;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case  2:
				tCost = 14000000;
				tItemLevel = 146;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case  3:
				tCost = 15000000;
				tItemLevel = 147;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case  4:
				tCost = 16000000;
				tItemLevel = 148;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case  5:
				tCost = 17000000;
				tItemLevel = 149;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case  6:
				tCost = 18000000;
				tItemLevel = 150;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case  7:
				tCost = 19000000;
				tItemLevel = 151;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case  8:
				tCost = 20000000;
				tItemLevel = 152;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case  9:
				tCost = 21000000;
				tItemLevel = 153;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 10:
				tCost = 22000000;
				tItemLevel = 154;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 11:
				tCost = 23000000;
				tItemLevel = 155;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 12:
				tCost = 24000000;
				tItemLevel = 156;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			}
			break;
#endif
		}
		break;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aMoney < tCost)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	/** 2009. 12. 16 : °­È­, Á¶ÇÕ, ½Â±ÞºÎ(Æ¯) ¾ÆÀÌÅÛ °³¹ß (wolf) */

	tITEM_INFO3 = mITEM.Return_2(tItemLevel, tITEM_INFO1);
	if (tITEM_INFO3 == NULL)
	{
		//mGAMELOG.GL_636_LOW_ITEM(tUserIndex, 4, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost, tITEM_INFO2->iIndex);
		mTRANSFER.B_LOW_ITEM_RECV(2, tCost, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	tProbability += (int)((float)mAVATAR_OBJECT[tUserIndex].GetLuck() / 300.0f);
	tRandom = rand();
	if ((tRandom % 100) < (unsigned int)tProbability)
	{
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
		tValue[0] = tITEM_INFO3->iIndex;
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		tValue[3] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3];
		tValue[4] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4];
		tValue[5] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5];
		//mGAMELOG.GL_636_LOW_ITEM(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost, tITEM_INFO2->iIndex);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
		//mGAMELOG.GL_636_LOW_ITEM(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost, tITEM_INFO2->iIndex);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_LOW_ITEM_RECV(0, tCost, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	}
	mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
	//mGAMELOG.GL_636_LOW_ITEM(tUserIndex, 3, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost, tITEM_INFO2->iIndex);
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
	mTRANSFER.B_LOW_ITEM_RECV(1, tCost, &tValue[0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

}
//W_MAKE_ITEM_SEND
void W_MAKE_ITEM_SEND(int tUserIndex)
{
	__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	unsigned int tRandom = 0;
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	int tPage3;
	int tIndex3;
	int tPage4;
	int tIndex4;
	int tProbability1;
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tPage1, &tPacket[5], 4);
	CopyMemory(&tIndex1, &tPacket[9], 4);
	CopyMemory(&tPage2, &tPacket[13], 4);
	CopyMemory(&tIndex2, &tPacket[17], 4);
	CopyMemory(&tPage3, &tPacket[21], 4);
	CopyMemory(&tIndex3, &tPacket[25], 4);
	CopyMemory(&tPage4, &tPacket[29], 4);
	CopyMemory(&tIndex4, &tPacket[33], 4);

	ITEM_INFO* item1;
	ITEM_INFO* item2;
	ITEM_INFO* item3;
	ITEM_INFO* item4;
	ITEM_INFO* item5;


	int tRandomNumber;
	int tValue[6];
	int ivenindex[3];

	int Piece;
	int Price;
	int tItem;

	BYTE tData[MAX_BROADCAST_DATA_SIZE];


	switch (tSort)
	{
		//case 0://4x tin = rand mats
		//	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) ||
		//		(tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage3 < 0) || (tPage3 > 1) ||
		//		(tIndex3 < 0) || (tIndex3 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage4 < 0) || (tPage4 > 1) || (tIndex4 < 0) ||
		//		(tIndex4 > (MAX_INVENTORY_SLOT_NUM - 1)))
		//	{
		//		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		//		return;
		//	}
		//	if ((tPage1 == 1) || (tPage2 == 1) || (tPage3 == 1) || (tPage4 == 1))
		//	{
		//		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		//		{
		//			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		//			return;
		//		}
		//	}
		//	if ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] != 1019) ||
		//		(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != 1019) ||
		//		(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] != 1019) ||
		//		(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 1019))
		//	{
		//		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		//		return;
		//	}
		//
		//		tRandom = rand() % 4;
		//		switch (tRandom) {
		//		case 0:
		//			tValue[0] = 1023;
		//			break;
		//		case 1:
		//			tValue[0] = 1022;
		//			break;
		//		case 2:
		//			tValue[0] = 1021;
		//			break;
		//		case 3:
		//			tValue[0] = 1020;
		//			break;
		//		}
		//		
		//		//tValue[0] = 984;
		//		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		//		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		//		tValue[3] = 0;
		//		tValue[4] = 0;
		//		tValue[5] = 0;

		//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
		//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
		//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
		//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
		//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
		//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
		//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] = 0;
		//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][1] = 0;
		//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][2] = 0;
		//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3] = 0;
		//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4] = 0;
		//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] = 0;
		//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] = 0;
		//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][1] = 0;
		//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][2] = 0;
		//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3] = 0;
		//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4] = 0;
		//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] = 0;
		//		mTRANSFER.B_MAKE_ITEM_RECV(0, &tValue[0]);
		//		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//		return;
		//	
		//	
		//	GameLogger(1, "<MAKE_ITEM_SEND>(%s),(%s), (%d, %d, %d, %d), [[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], mSERVER_INFO.mServerNumber);

		//	mTRANSFER.B_MAKE_ITEM_RECV(-1, &tValue[0]);
		//	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		//	return;

	case  0: //[Tin -> Mats]
		if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage3 < 0) || (tPage3 > 1) || (tIndex3 < 0) || (tIndex3 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage4 < 0) || (tPage4 > 1) || (tIndex4 < 0) || (tIndex4 > (MAX_INVENTORY_SLOT_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tPage1 == 1) || (tPage2 == 1) || (tPage3 == 1) || (tPage4 == 1))
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] != 1019) || (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != 1019) || (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] != 1019) || (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 1019))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tRandom = rand();
		switch ((tRandom % 4))
		{
		case 0:
			tValue[0] = 1020;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = mUTIL.ReturnItemRecognitionNumber(0);
			break;
		case 1:
			tValue[0] = 1021;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = mUTIL.ReturnItemRecognitionNumber(0);
			break;
		case 2:
			tValue[0] = 1022;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = mUTIL.ReturnItemRecognitionNumber(0);
			break;
		case 3:
			tValue[0] = 1023;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = mUTIL.ReturnItemRecognitionNumber(0);
			break;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] = 0;
		GameLogger(1, "<MAKE_ITEM_SEND>(%s),(%s), (%d, %d, %d, %d), [[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], mSERVER_INFO.mServerNumber);
		mTRANSFER.B_MAKE_ITEM_RECV(0, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case  1: //[Purple Jade x2 -> Red Jade]
		if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tPage1 == 1) || (tPage2 == 1))
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] != 1024) || (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != 1024))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue[0] = 1025;
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		tValue[3] = 0;
		tValue[4] = 0;
		tValue[5] = mUTIL.ReturnItemRecognitionNumber(0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		GameLogger(1, "<MAKE_ITEM_SEND>(%s),(%s), (%d, %d, %d, %d), [[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], mSERVER_INFO.mServerNumber);
		mTRANSFER.B_MAKE_ITEM_RECV(0, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2:// P L A Y Letters
		if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) ||
			(tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage3 < 0) || (tPage3 > 1) ||
			(tIndex3 < 0) || (tIndex3 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage4 < 0) || (tPage4 > 1) || (tIndex4 < 0) ||
			(tIndex4 > (MAX_INVENTORY_SLOT_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tPage1 == 1) || (tPage2 == 1) || (tPage3 == 1) || (tPage4 == 1))
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] != 522) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != 523) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] != 524) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 525))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}


		tValue[0] = 1220;
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		tValue[3] = 0;
		tValue[4] = 0;
		tValue[5] = 0;

		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] = 0;
		GameLogger(1, "<MAKE_ITEM_SEND>(%s),(%s), (%d, %d, %d, %d), [[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], mSERVER_INFO.mServerNumber);

		mTRANSFER.B_MAKE_ITEM_RECV(0, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 3:// PC to PC(L)
		if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) ||
			(tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage3 < 0) || (tPage3 > 1) ||
			(tIndex3 < 0) || (tIndex3 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage4 < 0) || (tPage4 > 1) || (tIndex4 < 0) ||
			(tIndex4 > (MAX_INVENTORY_SLOT_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tPage1 == 1) || (tPage2 == 1) || (tPage3 == 1) || (tPage4 == 1))
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] != 1103) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != 1103) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] != 1103) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 1103))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tRandom = rand() % 10;
		if (tRandom < 2)
		{
			tValue[0] = 0;
			tValue[1] = 0;
			tValue[2] = 0;
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;

			item1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
			item2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
			item3 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0]);
			item4 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0]);
			item5 = mITEM.Search(tValue[0]);
			mGAMELOG.GL_MAKE_ITEM(tUserIndex, item1->iIndex, item1->iName, item2->iIndex, item2->iName, item3->iIndex, item3->iName, item4->iIndex, item4->iName, 0, "PC Craft Fail");

			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = 0;
			mTRANSFER.B_MAKE_ITEM_RECV(2, &tValue[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		else {

			tValue[0] = 1185;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;

			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] = 0;
			GameLogger(1, "<MAKE_ITEM_SEND>(%s),(%s), (%d, %d, %d, %d), [[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], mSERVER_INFO.mServerNumber);
			//mGAMELOG.GL_MAKE_ITEM(tUserIndex, item1->iIndex, item1->iName, item2->iIndex, item2->iName, item3->iIndex, item3->iName, item4->iIndex, item4->iName, 0, "PC Craft Success");

			mTRANSFER.B_MAKE_ITEM_RECV(0, &tValue[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			return;
		}
	case 4:// PC to PC(L)
		if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) ||
			(tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage3 < 0) || (tPage3 > 1) ||
			(tIndex3 < 0) || (tIndex3 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage4 < 0) || (tPage4 > 1) || (tIndex4 < 0) ||
			(tIndex4 > (MAX_INVENTORY_SLOT_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tPage1 == 1) || (tPage2 == 1) || (tPage3 == 1) || (tPage4 == 1))
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] != 614) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != 615) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] != 616) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 617))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tRandom = rand() % 1000;
		if (tRandom < 1) {
			tItem = 1409;		// 105 Elite Cape
		}
		else if (tRandom < 50) {
			tRandom = rand() % 2;
			switch (tRandom) {
			case 0:
				tItem = 1103;	// PC
				break;
			case 1:
				tItem = 1237;	// Wing PC
				break;
			}
			
		}
		else if (tRandom < 200) {
			tRandom = rand() % 4;
			switch (tRandom) {
			case 0:
				tItem = 1166;	// CP PC
				break;
			case 1:
				tItem = 1190;	// x2 Pet Exp
				break;
			case 2:
				tItem = 1118;	 // Scroll of Loyality
				break;
			case 3:
				tItem = 1072;
				break;

			}
		}
		else if (tRandom < 350) {
			tRandom = rand() % 3;
			switch (tRandom) {
			case 0:
				tItem = 601;	// Mount Box
				break;
			case 1:
				tItem = 602;	// Pet Box
				break;
			case 2:
				tItem = 998;	 // Mystery Box
				break;
			}
		}
		else if(tRandom < 600)
		{
			tRandom = rand() % 5;
			switch (tRandom) {
			case 0:
				tItem = 614;	// Sock
				break;
			case 1:
				tItem = 615;	// Lamp
				break;
			case 2:
				tItem = 616;	// Star
				break;
			case 3:
				tItem = 617;	// Snowflake
				break;
			}
		}
		else {
			tRandom = rand() % 7;
			switch (tRandom) {
			case 0:
				tItem = 1022;	// SOE
				break;
			case 1:
				tItem = 1023;	// GOE
				break;
			case 2:
				tItem = 1024;	 // PJ
				break;
			case 3:
				tItem = 1025;	// RJ
				break;
			case 4:
				tItem = 1222;	 //Absorption Pill (L)
				break;
			case 5:	
				tItem = 613;	// Absorption Pill (S)
				break;
			case 6:
				tItem = 1145;	 // SBF										
				break; 
			}


		}
		
	
			
			tValue[0] = tItem;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;
			item5 = mITEM.Search(tItem);

			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] = 0;
			GameLogger(1, "<MAKE_ITEM_SEND>(%s),(%s), (%d, %d, %d, %d), [[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], mSERVER_INFO.mServerNumber);
			//mGAMELOG.GL_MAKE_ITEM(tUserIndex, item1->iIndex, item1->iName, item2->iIndex, item2->iName, item3->iIndex, item3->iName, item4->iIndex, item4->iName, 0, "PC Craft Success");

			mTRANSFER.B_MAKE_ITEM_RECV(0, &tValue[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			if ((tItem == 1409) || (tItem == 1103) || (tItem == 1237)) {
				sprintf((char*)&tData[0], "[%s] crafted '%s'", &mUSER[tUserIndex].mAvatarInfo.aName[0], item5->iName);
				mRELAY_COM.U_DEMAND_BROADCAST_DATA(102, &tData[0]);
			}
		
			return;
			
	case 40://wing creating
		if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage3 < 0) || (tPage3 > 1) || (tIndex3 < 0) || (tIndex3 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage4 < 0) || (tPage4 > 1) || (tIndex4 < 0) || (tIndex4 > (MAX_INVENTORY_SLOT_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tPage1 == 1) || (tPage2 == 1) || (tPage3 == 1) || (tPage4 == 1))
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if (((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] != 695) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != 695) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] != 695)) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 126 &&
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 129 &&
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 132 &&
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 135 &&
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 138 &&
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 141 &&
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 144 &&
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 147 &&
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 150))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 50)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 50;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 50;

		tRandom = rand() % 100;
		if (tRandom < 70)
		{
			tValue[0] = 0;
			tValue[1] = 0;
			tValue[2] = 0;
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;

			item1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
			item2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
			item3 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0]);
			item4 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0]);
			item5 = mITEM.Search(tValue[0]);
			mGAMELOG.GL_MAKE_ITEM(tUserIndex, item1->iIndex, item1->iName, item2->iIndex, item2->iName, item3->iIndex, item3->iName, item4->iIndex, item4->iName, 0, "Unsuccessful");

			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = 0;
			mTRANSFER.B_MAKE_ITEM_RECV(2, &tValue[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		else
		{
			switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe) {
			case 0:
				tRandom = rand() % 1000;
				if (tRandom < 50) {
					tValue[0] = 213;
				}
				else if (tRandom < 350) {

					tValue[0] = 204;
				}
				else {
					tRandom = rand() % 3;
					switch (tRandom) {
					case 0:
						tValue[0] = 207;
						break;
					case 1:
						tValue[0] = 210;
						break;
					case 2:
						tValue[0] = 201;
						break;
					}
				}
				break;
			case 1:
				tRandom = rand() % 1000;
				if (tRandom < 50) {
					tValue[0] = 214;
				}
				else if (tRandom < 350) {

					tValue[0] = 205;
				}
				else {
					tRandom = rand() % 3;
					switch (tRandom) {
					case 0:
						tValue[0] = 208;
						break;
					case 1:
						tValue[0] = 211;
						break;
					case 2:
						tValue[0] = 202;
						break;
					}
				}
				break;
			case 2:
				tRandom = rand() % 1000;
				if (tRandom < 50) {
					tValue[0] = 215;
				}
				else if (tRandom < 350) {

					tValue[0] = 206;
				}
				else {
					tRandom = rand() % 3;
					switch (tRandom) {
					case 0:
						tValue[0] = 209;
						break;
					case 1:
						tValue[0] = 212;
						break;
					case 2:
						tValue[0] = 203;
						break;
					}
				}
				break;
			}
			//int kanatList[3][5];
			////Dragon		
			//kanatList[0][0] = 201;
			//kanatList[0][1] = 204;
			//kanatList[0][2] = 207;
			//kanatList[0][3] = 210;
			//kanatList[0][4] = 213;
			////Snake
			//kanatList[1][0] = 202;
			//kanatList[1][1] = 205;
			//kanatList[1][2] = 208;
			//kanatList[1][3] = 211;
			//kanatList[1][4] = 214;
			////Tiger
			//kanatList[2][0] = 203;
			//kanatList[2][1] = 206;
			//kanatList[2][2] = 209;
			//kanatList[2][3] = 212;
			//kanatList[2][4] = 215;

			//tValue[0] = kanatList[mUSER[tUserIndex].mAvatarInfo.aPreviousTribe][rand() % 5];
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;

			item1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
			item2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
			item3 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0]);
			item4 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0]);
			item5 = mITEM.Search(tValue[0]);
			mGAMELOG.GL_MAKE_ITEM(tUserIndex, item1->iIndex, item1->iName, item2->iIndex, item2->iName, item3->iIndex, item3->iName, item4->iIndex, item4->iName, item5->iIndex, item5->iName);

			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] = 0;
			mTRANSFER.B_MAKE_ITEM_RECV(1, &tValue[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
	case 41://3 white feather -> 1 black feather
		if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) ||
			(tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage3 < 0) || (tPage3 > 1) ||
			(tIndex3 < 0) || (tIndex3 > (MAX_INVENTORY_SLOT_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tPage1 == 1) || (tPage2 == 1) || (tPage3 == 1))
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] != 695) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != 695) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] != 695))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		

		/*item1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
		item2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
		item3 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0]);
		item5 = mITEM.Search(tValue[0]);*/
		//mGAMELOG.GL_MAKE_ITEM(tUserIndex, item1->iIndex, item1->iName, item2->iIndex, item2->iName, item3->iIndex, item3->iName, 0, 0, item5->iIndex, item5->iName);

		tValue[0] = 696;
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		tValue[3] = 0;
		tValue[4] = 0;
		tValue[5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] = 0;
		mTRANSFER.B_MAKE_ITEM_RECV(0, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;



	case 43:// Piece to Costume Piece
		if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage3 < 0) || (tPage3 > 1) || (tIndex3 < 0) || (tIndex3 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage4 < 0) || (tPage4 > 1) || (tIndex4 < 0) || (tIndex4 > (MAX_INVENTORY_SLOT_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tPage1 == 1) || (tPage2 == 1) || (tPage3 == 1) || (tPage4 == 1))
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if ( (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] != 720) ||
			 (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != 721) ||
			 (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] != 722) ||
			 (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 723) )
			
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}


		tRandom = rand() % 100;
		if (tRandom < 70)
		{
			tValue[0] = 0;
			tValue[1] = 0;
			tValue[2] = 0;
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;

			item1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
			item2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
			item3 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0]);
			item4 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0]);
			item5 = mITEM.Search(tValue[0]);
			mGAMELOG.GL_MAKE_ITEM(tUserIndex, item1->iIndex, item1->iName, item2->iIndex, item2->iName, item3->iIndex, item3->iName, item4->iIndex, item4->iName, 0, "Unsuccessful");

		
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = 0;
			mTRANSFER.B_MAKE_ITEM_RECV(2, &tValue[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		else
		{
			tRandom = rand() % 4;
			tValue[0] = 724 + tRandom;
		}
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;

			item1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
			item2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
			item3 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0]);
			item4 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0]);
			item5 = mITEM.Search(tValue[0]);
			//mGAMELOG.GL_MAKE_ITEM(tUserIndex, item1->iIndex, item1->iName, item2->iIndex, item2->iName, item3->iIndex, item3->iName, item4->iIndex, item4->iName, item5->iIndex, item5->iName);

			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] = 0;
			mTRANSFER.B_MAKE_ITEM_RECV(1, &tValue[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
	case 44:// Mystic Piece to Costume 
		if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage3 < 0) || (tPage3 > 1) || (tIndex3 < 0) || (tIndex3 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage4 < 0) || (tPage4 > 1) || (tIndex4 < 0) || (tIndex4 > (MAX_INVENTORY_SLOT_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tPage1 == 1) || (tPage2 == 1) || (tPage3 == 1) || (tPage4 == 1))
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] != 724) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != 725) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] != 726) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 727))

		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe) {
		case 0:
			tRandom = rand() % 5;
			switch (tRandom) {
			case 0:
				tValue[0] = 310;
				break;
			case 1:
				tValue[0] = 328;
				break;
			case 2:
				tValue[0] = 331;
				break;
			case 3:
				tValue[0] = 334;
				break;
			case 4:
				tValue[0] = 337;
				break;
			case 5:
				tValue[0] = 343;
				break;
			}
			break;

		case 1:
			tRandom = rand() % 5;
			switch (tRandom) {
			case 0:
				tValue[0] = 311;
				break;
			case 1:
				tValue[0] = 329;
				break;
			case 2:
				tValue[0] = 332;
				break;
			case 3:
				tValue[0] = 335;
				break;
			case 4:
				tValue[0] = 338;
				break;
			case 5:
				tValue[0] = 344;
				break;
			}
			break;

		case 2:
			tRandom = rand() % 5;
			switch (tRandom) {
			case 0:
				tValue[0] = 312;
				break;
			case 1:
				tValue[0] = 330;
				break;
			case 2:
				tValue[0] = 333;
				break;
			case 3:
				tValue[0] = 336;
				break;
			case 4:
				tValue[0] = 339;
				break;
			case 5:
				tValue[0] = 345;
				break;
			}
			break;

		}
	
			/*tRandom = rand() % 4;
			tValue[0] = 724 + tRandom;*/
	
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		tValue[3] = 0;
		tValue[4] = 0;
		tValue[5] = 0;

		item1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
		item2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
		item3 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0]);
		item4 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0]);
		item5 = mITEM.Search(tValue[0]);
		//mGAMELOG.GL_MAKE_ITEM(tUserIndex, item1->iIndex, item1->iName, item2->iIndex, item2->iName, item3->iIndex, item3->iName, item4->iIndex, item4->iName, item5->iIndex, item5->iName);

		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] = 0;
		mTRANSFER.B_MAKE_ITEM_RECV(1, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;




		case 45:// Sock , lamp , star , snowflake
			if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) ||
				(tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage3 < 0) || (tPage3 > 1) ||
				(tIndex3 < 0) || (tIndex3 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage4 < 0) || (tPage4 > 1) || (tIndex4 < 0) ||
				(tIndex4 > (MAX_INVENTORY_SLOT_NUM - 1)))
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if ((tPage1 == 1) || (tPage2 == 1) || (tPage3 == 1) || (tPage4 == 1))
			{
				if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
			if ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] != 614) ||
				(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != 615) ||
				(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] != 616) ||
				(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 617))
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			tRandom = rand() % 1000;
			if (tRandom < 1) {
				tItem = 1409;		// 105 Elite Cape
			}
			else if (tRandom < 50) {
				tRandom = rand() % 2;
				switch (tRandom) {
				case 0:
					tItem = 1103;	// PC
					break;
				case 1:
					tItem = 1237;	// Wing PC
					break;
				}

			}
			else if (tRandom < 600) {
				tRandom = rand() % 7;
				switch (tRandom) {
				case 0:
					tItem = 601;	 // Mount Box
					break;
				case 1:
					tItem = 602;	 // Pet Box
					break;
				case 2:
					tItem = 998;	 // Mystery Box
					break;
				case 3:
					tItem = 1166;	 // CP PC
					break;
				case 4:
					tItem = 1190;	 // x2 Pet Exp
					break;
				case 5:
					tItem = 1118;	 // Scroll of Loyality
					break;
				case 6:
					tItem = 1072;    // Silver bar
					break;
				}
			}
			else {
				tRandom = rand() % 7;
				switch (tRandom) {
				case 0:
					tItem = 1022;	 // SOE
					break;
				case 1:
					tItem = 1023;	 // GOE
					break;
				case 2:
					tItem = 1024;	 // PJ
					break;
				case 3:
					tItem = 1025;	 // RJ
					break;
				case 4:
					tItem = 1222;	 //Absorption Pill (L)
					break;
				case 5:
					tItem = 613;	 // Absorption Pill (S)
					break;
				case 6:
					tItem = 1145;	 // SBF										
					break;
				}


			}

			tValue[0] = tItem;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;
			item5 = mITEM.Search(tItem);

			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] = 0;
			GameLogger(1, "<MAKE_ITEM_SEND>(%s),(%s), (%d, %d, %d, %d), [[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], mSERVER_INFO.mServerNumber);
			//mGAMELOG.GL_MAKE_ITEM(tUserIndex, item1->iIndex, item1->iName, item2->iIndex, item2->iName, item3->iIndex, item3->iName, item4->iIndex, item4->iName, 0, "PC Craft Success");

			mTRANSFER.B_MAKE_ITEM_RECV(0, &tValue[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			if ((tItem == 1409) || (tItem == 1103) || (tItem == 1237)) {
				sprintf((char*)&tData[0], "[%s] found '%s' from ", &mUSER[tUserIndex].mAvatarInfo.aName[0], item5->iName);
				mRELAY_COM.U_DEMAND_BROADCAST_DATA(102, &tData[0]);
			}

			return;

		default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}
//W_MAKE_SKILL_SEND
void W_MAKE_SKILL_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	int tPage3;
	int tIndex3;
	int tPage4;
	int tIndex4;
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tPage1, &tPacket[5], 4);
	CopyMemory(&tIndex1, &tPacket[9], 4);
	CopyMemory(&tPage2, &tPacket[13], 4);
	CopyMemory(&tIndex2, &tPacket[17], 4);
	CopyMemory(&tPage3, &tPacket[21], 4);
	CopyMemory(&tIndex3, &tPacket[25], 4);
	CopyMemory(&tPage4, &tPacket[29], 4);
	CopyMemory(&tIndex4, &tPacket[33], 4);

	int tValue[6];

	switch (tSort)
	{
	case 0: //[È­·æ°á]+[³ú½Å°á]+[º®·É°á]+[ÅÂ¾ç°á]->[´ë±Ø¹æÅº¼¼]
		if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage3 < 0) || (tPage3 > 1) || (tIndex3 < 0) || (tIndex3 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage4 < 0) || (tPage4 > 1) || (tIndex4 < 0) || (tIndex4 > (MAX_INVENTORY_SLOT_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tPage1 == 1) || (tPage2 == 1) || (tPage3 == 1) || (tPage4 == 1))
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] != 1054) || (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != 1055) || (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] != 1056) || (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 1057))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue[0] = 90567;
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		tValue[3] = 0;
		tValue[4] = 0;
		tValue[5] = mUTIL.ReturnItemRecognitionNumber(0);
		mGAMELOG.GL_MAKE_SKILL(tUserIndex, tValue[0]);
		//mGAMELOG.GL_639_MAKE_SKILL(tUserIndex, 1, tValue[0], tValue[3], tValue[4], tValue[5]);
		//mGAMELOG.GL_639_MAKE_SKILL(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5]);
		//mGAMELOG.GL_639_MAKE_SKILL(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5]);
		//mGAMELOG.GL_639_MAKE_SKILL(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5]);
		//mGAMELOG.GL_639_MAKE_SKILL(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5]);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] = 0;
		mTRANSFER.B_MAKE_SKILL_RECV(0, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1: //[¼³¿ÕÀü±â]+[ºÏÇ³Àü±â]+[»ç½ÅÀü±â]+[¿ù¶ûÀü±â]->[Ãµ¹®¿ª±Ù°ø]
		if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage3 < 0) || (tPage3 > 1) || (tIndex3 < 0) || (tIndex3 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage4 < 0) || (tPage4 > 1) || (tIndex4 < 0) || (tIndex4 > (MAX_INVENTORY_SLOT_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tPage1 == 1) || (tPage2 == 1) || (tPage3 == 1) || (tPage4 == 1))
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] != 1058) || (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != 1059) || (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] != 1060) || (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 1061))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue[0] = 90568;
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		tValue[3] = 0;
		tValue[4] = 0;
		tValue[5] = mUTIL.ReturnItemRecognitionNumber(0);
		mGAMELOG.GL_MAKE_SKILL(tUserIndex, tValue[0]);
		//mGAMELOG.GL_639_MAKE_SKILL(tUserIndex, 1, tValue[0], tValue[3], tValue[4], tValue[5]);
		//mGAMELOG.GL_639_MAKE_SKILL(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5]);
		//mGAMELOG.GL_639_MAKE_SKILL(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5]);
		//mGAMELOG.GL_639_MAKE_SKILL(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5]);
		//mGAMELOG.GL_639_MAKE_SKILL(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5]);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] = 0;
		mTRANSFER.B_MAKE_SKILL_RECV(0, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 2: //[Ç÷Ãµ·Ï]+[±Í¹®·Ï]+[ÁÖ°æ·Ï]+[¸¶½Å·Ï]->[Å»¸Á¼ÒÈ¥¿ª]
		if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage3 < 0) || (tPage3 > 1) || (tIndex3 < 0) || (tIndex3 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage4 < 0) || (tPage4 > 1) || (tIndex4 < 0) || (tIndex4 > (MAX_INVENTORY_SLOT_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tPage1 == 1) || (tPage2 == 1) || (tPage3 == 1) || (tPage4 == 1))
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] != 1062) || (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != 1063) || (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] != 1064) || (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 1065))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue[0] = 90569;
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		tValue[3] = 0;
		tValue[4] = 0;
		tValue[5] = mUTIL.ReturnItemRecognitionNumber(0);
		mGAMELOG.GL_MAKE_SKILL(tUserIndex, tValue[0]);
		//mGAMELOG.GL_639_MAKE_SKILL(tUserIndex, 1, tValue[0], tValue[3], tValue[4], tValue[5]);
		//mGAMELOG.GL_639_MAKE_SKILL(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5]);
		//mGAMELOG.GL_639_MAKE_SKILL(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5]);
		//mGAMELOG.GL_639_MAKE_SKILL(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5]);
		//mGAMELOG.GL_639_MAKE_SKILL(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5]);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] = 0;
		mTRANSFER.B_MAKE_SKILL_RECV(0, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case  41:
		if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage3 < 0) || (tPage3 > 1) || (tIndex3 < 0) || (tIndex3 > (MAX_INVENTORY_SLOT_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tPage1 == 1) || (tPage2 == 1) || (tPage3 == 1))
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] != 695)
			|| (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != 695)
			|| (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] != 695))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 50)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 50;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 50;

		tValue[0] = 696;
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		tValue[3] = 0;
		tValue[4] = 0;
		tValue[5] = 0;
		mGAMELOG.GL_MAKE_SKILL(tUserIndex, tValue[0]);
		//mGAMELOG.GL_638_MAKE_ITEM(tUserIndex, 1, tValue[0], tValue[3], tValue[4], tValue[5]);
		//mGAMELOG.GL_638_MAKE_ITEM(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5]);
		//mGAMELOG.GL_638_MAKE_ITEM(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5]);
		//mGAMELOG.GL_638_MAKE_ITEM(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5]);
		//mGAMELOG.GL_638_MAKE_ITEM(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5]);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage3][tIndex3][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage3][tIndex3][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage3][tIndex3][2] = 0;
		mTRANSFER.B_MAKE_ITEM_RECV(1, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}
//W_START_PSHOP_SEND 
void W_START_PSHOP_SEND(int tUserIndex)
{
	__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (124 == mSERVER_INFO.mServerNumber)
		return;
	PSHOP_INFO tPShopInfo;
	VALETSHOP_INFO tValetPShopInfoMoney;
	int tSort;
	int index01;
	int index02;
	ITEM_INFO* tITEM_INFO;
	int tValetShopIndex1;

	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tPShopInfo, &tPacket[5], sizeof(PSHOP_INFO));
	switch (tSort)
	{
	case 1://Normal Shop
		if (1 == mUSER[tUserIndex].mAuthInfo.PShopFlag) {
			mTRANSFER.B_START_PSHOP_RECV(1, &tPShopInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aPShopState != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (!mWORK.CheckPossiblePShopRegion(mUSER[tUserIndex].mAvatarInfo.aTribe, mSERVER_INFO.mServerNumber, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0]))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort != 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (strcmp(tPShopInfo.mName, "") == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_PSHOP_PAGE_NUM; index01++)
		{
			for (index02 = 0; index02 < MAX_PSHOP_SLOT_NUM; index02++)
			{
				if (tPShopInfo.mItemInfo[index01][index02][0] > 0)
				{
					break;
				}
			}
			if (index02 < MAX_PSHOP_SLOT_NUM)
			{
				break;
			}
		}
		if (index01 == MAX_PSHOP_PAGE_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_PSHOP_PAGE_NUM; index01++)
		{
			for (index02 = 0; index02 < MAX_PSHOP_SLOT_NUM; index02++)
			{
				if (tPShopInfo.mItemInfo[index01][index02][0] < 1)
				{
					continue;
				}
				tITEM_INFO = mITEM.Search(tPShopInfo.mItemInfo[index01][index02][0]);
				if (tITEM_INFO == NULL)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
				if (tITEM_INFO->iCheckAvatarShop == 1)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
				if ((tPShopInfo.mItemInfo[index01][index02][5] < 0) || (tPShopInfo.mItemInfo[index01][index02][5] > 1) || (tPShopInfo.mItemInfo[index01][index02][6] < 0) || (tPShopInfo.mItemInfo[index01][index02][6] > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPShopInfo.mItemInfo[index01][index02][7] < 0) || (tPShopInfo.mItemInfo[index01][index02][7] > 7) || (tPShopInfo.mItemInfo[index01][index02][8] < 0) || (tPShopInfo.mItemInfo[index01][index02][8] > 7))
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
				if (tPShopInfo.mItemInfo[index01][index02][5] == 1)
				{
					if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
					{
						mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
						return;
					}
				}
				if ((tPShopInfo.mItemInfo[index01][index02][0] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][0]) || (tPShopInfo.mItemInfo[index01][index02][1] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][3]) || (tPShopInfo.mItemInfo[index01][index02][2] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][4]) || (tPShopInfo.mItemInfo[index01][index02][3] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][5]) || (tPShopInfo.mItemInfo[index01][index02][7] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][1]) || (tPShopInfo.mItemInfo[index01][index02][8] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][2]))
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
				if ((tPShopInfo.mItemInfo[index01][index02][4] < 1) || (tPShopInfo.mItemInfo[index01][index02][4] > 999999999))
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
		}
		mAVATAR_OBJECT[tUserIndex].mDATA.aPShopState = 1;
		strncpy(mAVATAR_OBJECT[tUserIndex].mDATA.aPShopName, tPShopInfo.mName, MAX_PSHOP_NAME_LENGTH);
		CopyMemory(&mAVATAR_OBJECT[tUserIndex].mPShopInfo, &tPShopInfo, sizeof(PSHOP_INFO));
		mAVATAR_OBJECT[tUserIndex].mPShopInfo.mUniqueNumber = mGAME.mAvatarPShopUniqueNumber;
		mGAME.mAvatarPShopUniqueNumber++;
		mTRANSFER.B_START_PSHOP_RECV(0, &tPShopInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 2:
		if (mUSER[tUserIndex].mAvatarInfo.ValetShop < 1)
		{
			mTRANSFER.B_START_PSHOP_RECV(104, &tPShopInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (!mWORK.CheckPossiblePShopRegion(mUSER[tUserIndex].mAvatarInfo.aTribe, mSERVER_INFO.mServerNumber, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0]))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort != 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (strcmp(tPShopInfo.mName, "") == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_PSHOP_PAGE_NUM; index01++)
		{
			for (index02 = 0; index02 < MAX_PSHOP_SLOT_NUM; index02++)
			{
				if (tPShopInfo.mItemInfo[index01][index02][0] > 0)
				{
					break;
				}
			}
			if (index02 < MAX_PSHOP_SLOT_NUM)
			{
				break;
			}
		}
		if (index01 == MAX_PSHOP_PAGE_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mVALETINFO.U_VALET_INFO(1, mUSER[tUserIndex].mAvatarInfo.aName);
		if (mVALETINFO.mRecv_Result != 0)
		{
			mTRANSFER.B_START_PSHOP_RECV(105, &tPShopInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		CopyMemory(&tValetPShopInfoMoney, &mVALETINFO.mRecv_ValetInfo, sizeof(VALETSHOP_INFO));
		for (index01 = 0; index01 < MAX_PSHOP_PAGE_NUM; index01++)
		{
			for (index02 = 0; index02 < MAX_PSHOP_SLOT_NUM; index02++)
			{
				if (tPShopInfo.mItemInfo[index01][index02][0] < 1)
				{
					continue;
				}
				tITEM_INFO = mITEM.Search(tPShopInfo.mItemInfo[index01][index02][0]);
				if (tITEM_INFO == NULL)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
				if (tITEM_INFO->iCheckAvatarShop == 1)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
				if (tPShopInfo.mItemInfo[index01][index02][5] == 1)
				{
					if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
					{
						mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
						return;
					}
				}
				if (tPShopInfo.mItemInfo[index01][index02][5] != -1)
				{
					if ((tPShopInfo.mItemInfo[index01][index02][0] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][0]) || (tPShopInfo.mItemInfo[index01][index02][1] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][3]) || (tPShopInfo.mItemInfo[index01][index02][2] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][4]) || (tPShopInfo.mItemInfo[index01][index02][3] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][5]) || (tPShopInfo.mItemInfo[index01][index02][7] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][1]) || (tPShopInfo.mItemInfo[index01][index02][8] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][2]))
					{
						mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
						return;
					}
				}
				else if (tPShopInfo.mItemInfo[index01][index02][5] == -1)
				{
					if (tPShopInfo.mItemInfo[index01][index02][0] != tValetPShopInfoMoney.mItemInfo[index01][index02][0])
					{
						mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
						return;
					}
				}
				if ((tPShopInfo.mItemInfo[index01][index02][4] < 1) || (tPShopInfo.mItemInfo[index01][index02][4] > 999999999))
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
		}

		tValetShopIndex1 = mUTIL.SearchValetShop(1, mUSER[tUserIndex].mAvatarInfo.aName);

		if (tValetShopIndex1 == -1)
		{
			mTRANSFER.B_START_PSHOP_RECV(102, &tPShopInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (tValetShopIndex1 == -2)
		{
			mTRANSFER.B_START_PSHOP_RECV(105, &tPShopInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		ZeroMemory(&mSHOP_OBJECT[tValetShopIndex1], sizeof(mSHOP_OBJECT[tValetShopIndex1]));
		for (index01 = 0; index01 < MAX_PSHOP_PAGE_NUM; index01++)
		{
			for (index02 = 0; index02 < MAX_PSHOP_SLOT_NUM; index02++)
			{
				
				mSHOP_OBJECT[tValetShopIndex1].mValetShopInfo.mItemInfo[index01][index02][0] = tPShopInfo.mItemInfo[index01][index02][0];
				mSHOP_OBJECT[tValetShopIndex1].mValetShopInfo.mItemInfo[index01][index02][1] = tPShopInfo.mItemInfo[index01][index02][1];
				mSHOP_OBJECT[tValetShopIndex1].mValetShopInfo.mItemInfo[index01][index02][2] = tPShopInfo.mItemInfo[index01][index02][2];
				mSHOP_OBJECT[tValetShopIndex1].mValetShopInfo.mItemInfo[index01][index02][3] = tPShopInfo.mItemInfo[index01][index02][3];
				mSHOP_OBJECT[tValetShopIndex1].mValetShopInfo.mItemInfo[index01][index02][4] = tPShopInfo.mItemInfo[index01][index02][4];
				mSHOP_OBJECT[tValetShopIndex1].mValetShopInfo.mSoketInfo[index01][index02][0] = tPShopInfo.mSoketInfo[index01][index02][0];
				mSHOP_OBJECT[tValetShopIndex1].mValetShopInfo.mSoketInfo[index01][index02][1] = tPShopInfo.mSoketInfo[index01][index02][1];
				mSHOP_OBJECT[tValetShopIndex1].mValetShopInfo.mSoketInfo[index01][index02][2] = tPShopInfo.mSoketInfo[index01][index02][2];
			}
		}

		mSHOP_OBJECT[tValetShopIndex1].mValetShopInfo.mShopBar = tValetPShopInfoMoney.mShopBar;
		mSHOP_OBJECT[tValetShopIndex1].mValetShopInfo.mShopMoney = tValetPShopInfoMoney.mShopMoney;

		mSHOP_OBJECT[tValetShopIndex1].mCheckValidState = TRUE;
		mSHOP_OBJECT[tValetShopIndex1].mUniqueNumber = mGAME.mAvatarValetUniqueNumber;
		mGAME.mAvatarValetUniqueNumber++;
		mSHOP_OBJECT[tValetShopIndex1].ValetPlayerUserIndex = mUSER[tUserIndex].mPlayUserIndex;
		mSHOP_OBJECT[tValetShopIndex1].mPresentTime = GetTickCount();
		mSHOP_OBJECT[tValetShopIndex1].mCheckTime = GetTickCount();
		strncpy(mSHOP_OBJECT[tValetShopIndex1].mDATA.aPShopName, tPShopInfo.mName, MAX_PSHOP_NAME_LENGTH);
		strncpy(mSHOP_OBJECT[tValetShopIndex1].mDATA.aName, mUSER[tUserIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH);
		strncpy(mSHOP_OBJECT[tValetShopIndex1].mValetShopInfo.mName, mUSER[tUserIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH);
		mSHOP_OBJECT[tValetShopIndex1].mDATA.aLocation[0] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0];
		mSHOP_OBJECT[tValetShopIndex1].mDATA.aLocation[1] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[1];
		mSHOP_OBJECT[tValetShopIndex1].mDATA.aLocation[2] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[2];
		mSHOP_OBJECT[tValetShopIndex1].SetSpaceIndex();

		mVALETINFO.U_VALET_UPDATE(mSHOP_OBJECT[tValetShopIndex1].mDATA.aName, &mSHOP_OBJECT[tValetShopIndex1].mValetShopInfo);
		if (mVALETINFO.mRecv_Result != 0)
		{
			mSHOP_OBJECT[tValetShopIndex1].mCheckValidState = FALSE;
			mTRANSFER.B_START_PSHOP_RECV(105, &tPShopInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		for (index01 = 0; index01 < MAX_PSHOP_PAGE_NUM; index01++)
		{
			for (index02 = 0; index02 < MAX_PSHOP_SLOT_NUM; index02++)
			{
	
				if (tPShopInfo.mItemInfo[index01][index02][5] != -1)
				{
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][0] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][1] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][2] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][3] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][4] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][5] = 0;
					mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][0] = 0;
					mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][1] = 0;
					mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][2] = 0;
				}

				tPShopInfo.mItemInfo[index01][index02][0] = 0;
				tPShopInfo.mItemInfo[index01][index02][1] = 0;
				tPShopInfo.mItemInfo[index01][index02][2] = 0;
				tPShopInfo.mItemInfo[index01][index02][3] = 0;
				tPShopInfo.mItemInfo[index01][index02][4] = 0;
				tPShopInfo.mItemInfo[index01][index02][5] = -1;
				tPShopInfo.mItemInfo[index01][index02][6] = -1;
				tPShopInfo.mItemInfo[index01][index02][7] = -1;
				tPShopInfo.mItemInfo[index01][index02][8] = -1;
				tPShopInfo.mSoketInfo[index01][index02][0] = 0;
				tPShopInfo.mSoketInfo[index01][index02][1] = 0;
				tPShopInfo.mSoketInfo[index01][index02][2] = 0;
			}
		}

		mTRANSFER.B_START_PSHOP_RECV(100, &tPShopInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		mTRANSFER.B_VALETSHOPUPDATE(tValetShopIndex1, mSHOP_OBJECT[tValetShopIndex1].mUniqueNumber, &mSHOP_OBJECT[tValetShopIndex1].mDATA, 2);
		mUTIL.Broadcast(TRUE, &mSHOP_OBJECT[tValetShopIndex1].mDATA.aLocation[0], UNIT_SCALE_RADIUS1, false);
		return;
	case 3:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	default:
		break;
	}



}
//CHECK_POSSIBLE_PSHOP_REGION
BOOL MyWork::CheckPossiblePShopRegion(int tTribe, int tZoneNumber, float tCoord[3])
{
	float tCenter[3];
	float tRadius;

	switch (tZoneNumber)
	{
	case   1:
		if (tTribe != 0)
		{
			return FALSE;
		}
		tCenter[0] = 4.0f;
		tCenter[1] = 0.0f;
		tCenter[2] = -2.0f;
		tRadius = 1500.0f;
		if (mUTIL.GetLengthXYZ(&tCoord[0], &tCenter[0]) < tRadius)
		{
			return TRUE;
		}
		return FALSE;
	case   6:
		if (tTribe != 1)
		{
			return FALSE;
		}
		tCenter[0] = -189.0f;
		tCenter[1] = 0.0f;
		tCenter[2] = 1150.0f;
		tRadius = 1500.0f;
		if (mUTIL.GetLengthXYZ(&tCoord[0], &tCenter[0]) < tRadius)
		{
			return TRUE;
		}
		return FALSE;
	case  11:
		if (tTribe != 2)
		{
			return FALSE;
		}
		tCenter[0] = 449.0f;
		tCenter[1] = 1.0f;
		tCenter[2] = 439.0f;
		tRadius = 1500.0f;
		if (mUTIL.GetLengthXYZ(&tCoord[0], &tCenter[0]) < tRadius)
		{
			return TRUE;
		}
		return FALSE;
	case 140:
		if (tTribe != 3)
		{
			return FALSE;
		}
		tCenter[0] = 452.0f;
		tCenter[1] = 0.0f;
		tCenter[2] = 487.0f;
		tRadius = 1500.0f;
		if (mUTIL.GetLengthXYZ(&tCoord[0], &tCenter[0]) < tRadius)
		{
			return TRUE;
		}
		return FALSE;
	case  37:
		tCenter[0] = 1.0f;
		tCenter[1] = 0.0f;
		tCenter[2] = -1478.0f;
		tRadius = 1500.0f;
		if (mUTIL.GetLengthXYZ(&tCoord[0], &tCenter[0]) < tRadius)
		{
			return TRUE;
		}
		return FALSE;
	}
	return FALSE;
}
//W_END_PSHOP_SEND 
void W_END_PSHOP_SEND(int tUserIndex)
{
	__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}
	int tSort;
	int ValuShopIndex;
	float tLocation[3];
	CopyMemory(&tSort, &tPacket[1], 4);

	switch (tSort)
	{
	case 1:
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aPShopState != 1)
		{
			return;
		}
		mAVATAR_OBJECT[tUserIndex].mDATA.aPShopState = 0;
		mTRANSFER.B_END_PSHOP_RECV(tSort);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 2:
		ValuShopIndex = mUTIL.SearchValetShop(2, mUSER[tUserIndex].mAvatarInfo.aName);
		//mPLAYUSER_COM.U_VALET_UPDATE(mSHOP_OBJECT[ValuShopIndex].mDATA.aName, &mSHOP_OBJECT[ValuShopIndex].mValetShopInfo);
		mSHOP_OBJECT[ValuShopIndex].mCheckValidState = FALSE;
		mTRANSFER.B_VALETSHOPUPDATE(ValuShopIndex, mSHOP_OBJECT[ValuShopIndex].mUniqueNumber, &mSHOP_OBJECT[ValuShopIndex].mDATA, 3);
		mUTIL.Broadcast(TRUE, &mSHOP_OBJECT[ValuShopIndex].mDATA.aLocation[0], UNIT_SCALE_RADIUS1, false);
		ZeroMemory(&mSHOP_OBJECT[ValuShopIndex], sizeof(mSHOP_OBJECT[ValuShopIndex]));
		mTRANSFER.B_END_PSHOP_RECV(tSort);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	default:
		break;
	}

}
//W_DEMAND_PSHOP_SEND 
void W_DEMAND_PSHOP_SEND(int tUserIndex)
{
	__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory(&tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH);

	int tOtherAvatarIndex;

	tOtherAvatarIndex = mUTIL.SearchAvatar(&tAvatarName[0], tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		mTRANSFER.B_DEMAND_PSHOP_RECV(1, &mAVATAR_OBJECT[0].mPShopInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		mTRANSFER.B_DEMAND_PSHOP_RECV(1, &mAVATAR_OBJECT[0].mPShopInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aPShopState != 1)
	{
		mTRANSFER.B_DEMAND_PSHOP_RECV(2, &mAVATAR_OBJECT[0].mPShopInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	mTRANSFER.B_DEMAND_PSHOP_RECV(0, &mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_PSHOP_ITEM_INFO_SEND 
void W_PSHOP_ITEM_INFO_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tSort1;
	int tSort2;
	CopyMemory(&tSort1, &tPacket[1], 4);
	CopyMemory(&tSort2, &tPacket[5], 4);

	int index01;
	int index02;
	int index03;
	int	tValue[9];
	int tSoketValue[3];
	int Dur;

	for (index01 = 0; index01 < 9; index01++)
	{
		tValue[index01] = 0;
		if (index01 < 3)
		{
			tSoketValue[index01] = 0;
		}
	}
	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (!mAVATAR_OBJECT[index01].mCheckValidState)
		{
			continue;
		}
		if (index01 == tUserIndex)
		{
			continue;
		}
		if (mAVATAR_OBJECT[index01].mDATA.aPShopState == 1)
		{
			for (index02 = 0; index02 < 5; index02++)
			{
				for (index03 = 0; index03 < 5; index03++)
				{
					if (mAVATAR_OBJECT[index01].mPShopInfo.mItemInfo[index02][index03][0] > 0)
					{
						Dur++;
						tValue[0] = mAVATAR_OBJECT[index01].mPShopInfo.mItemInfo[index02][index03][0];
						tValue[1] = mAVATAR_OBJECT[index01].mPShopInfo.mItemInfo[index02][index03][1];
						tValue[2] = mAVATAR_OBJECT[index01].mPShopInfo.mItemInfo[index02][index03][2];
						tValue[3] = mAVATAR_OBJECT[index01].mPShopInfo.mItemInfo[index02][index03][3];
						tValue[4] = mAVATAR_OBJECT[index01].mPShopInfo.mItemInfo[index02][index03][4];
						tValue[5] = mAVATAR_OBJECT[index01].mPShopInfo.mItemInfo[index02][index03][5];
						tValue[6] = mAVATAR_OBJECT[index01].mPShopInfo.mItemInfo[index02][index03][6];
						tValue[7] = mAVATAR_OBJECT[index01].mPShopInfo.mItemInfo[index02][index03][7];
						tValue[8] = mAVATAR_OBJECT[index01].mPShopInfo.mItemInfo[index02][index03][8];
						tSoketValue[0] = mAVATAR_OBJECT[index01].mPShopInfo.mSoketInfo[index02][index03][0];
						tSoketValue[1] = mAVATAR_OBJECT[index01].mPShopInfo.mSoketInfo[index02][index03][1];
						tSoketValue[2] = mAVATAR_OBJECT[index01].mPShopInfo.mSoketInfo[index02][index03][2];
						mTRANSFER.B_PSHOP_ITEM_INFO_RECV(mAVATAR_OBJECT[index01].mPShopInfo.mUniqueNumber, mUSER[index01].mAvatarInfo.aName, index02, index03, &tValue[0], &tSoketValue[0], 0);
						mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
						if (Dur == 500)
						{
							break;
						}
					}
				}
			}
		}
	}
	Dur = 0;
	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (!mSHOP_OBJECT[index01].mCheckValidState)
		{
			continue;
		}
		if (mSHOP_OBJECT[index01].ValetPlayerUserIndex == mUSER[tUserIndex].mPlayUserIndex)
		{
			continue;
		}
		for (index02 = 0; index02 < 5; index02++)
		{
			for (index03 = 0; index03 < 5; index03++)
			{
				if (mSHOP_OBJECT[index01].mValetShopInfo.mItemInfo[index02][index03][0] > 0)
				{
					Dur++;
					tValue[0] = mSHOP_OBJECT[index01].mValetShopInfo.mItemInfo[index02][index03][0];
					tValue[1] = mSHOP_OBJECT[index01].mValetShopInfo.mItemInfo[index02][index03][1];
					tValue[2] = mSHOP_OBJECT[index01].mValetShopInfo.mItemInfo[index02][index03][2];
					tValue[3] = mSHOP_OBJECT[index01].mValetShopInfo.mItemInfo[index02][index03][3];
					tValue[4] = mSHOP_OBJECT[index01].mValetShopInfo.mItemInfo[index02][index03][4];
					tValue[5] = -1;
					tValue[6] = -1;
					tValue[7] = -1;
					tValue[8] = -1;
					tSoketValue[0] = mAVATAR_OBJECT[index01].mPShopInfo.mSoketInfo[index02][index03][0];
					tSoketValue[1] = mAVATAR_OBJECT[index01].mPShopInfo.mSoketInfo[index02][index03][1];
					tSoketValue[2] = mAVATAR_OBJECT[index01].mPShopInfo.mSoketInfo[index02][index03][2];
					mTRANSFER.B_PSHOP_ITEM_INFO_RECV(mSHOP_OBJECT[index01].mUniqueNumber, mSHOP_OBJECT[index01].mValetShopInfo.mName, index02, index03, &tValue[0], &tSoketValue[0], 0);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					if (Dur == 500)
					{
						break;
					}
				}
			}
		}
	}
	return;
}
//W_BUY_PSHOP_SEND 
void W_BUY_PSHOP_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tUniqueNumber;
	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	int tPage1;
	int tIndex1;
	int tQuantity1;
	int tPage2;
	int tIndex2;
	int tXPost2;
	int tYPost2;
	ITEM_INFO* ITEM;
	CopyMemory(&tUniqueNumber, &tPacket[1], 4);
	CopyMemory(&tAvatarName[0], &tPacket[5], MAX_AVATAR_NAME_LENGTH);
	CopyMemory(&tPage1, &tPacket[(5 + MAX_AVATAR_NAME_LENGTH)], 4);
	CopyMemory(&tIndex1, &tPacket[(9 + MAX_AVATAR_NAME_LENGTH)], 4);
	CopyMemory(&tQuantity1, &tPacket[(13 + MAX_AVATAR_NAME_LENGTH)], 4);
	CopyMemory(&tPage2, &tPacket[(17 + MAX_AVATAR_NAME_LENGTH)], 4);
	CopyMemory(&tIndex2, &tPacket[(21 + MAX_AVATAR_NAME_LENGTH)], 4);
	CopyMemory(&tXPost2, &tPacket[(25 + MAX_AVATAR_NAME_LENGTH)], 4);
	CopyMemory(&tYPost2, &tPacket[(29 + MAX_AVATAR_NAME_LENGTH)], 4);

	if ((tPage1 < 0) || (tPage1 > (MAX_PSHOP_PAGE_NUM - 1)) || (tIndex1 < 0) || (tIndex1 > (MAX_PSHOP_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tXPost2 < 0) || (tXPost2 > 7) || (tYPost2 < 0) || (tYPost2 > 7))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	int tOtherAvatarIndex;
	int tItemInfo[9];
	int tSocketInfo[3];
	int tValue[6];
	int tSocketValue[3];
	tOtherAvatarIndex = mUTIL.SearchAvatar(&tAvatarName[0], tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		mTRANSFER.B_BUY_PSHOP_RECV(1, 0, 0, 0, &tValue[0], &tSocketValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	float fRange = 0.0f;
	fRange = mUTIL.ReturnLengthXYZ(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aLocation[1]);
	if (fRange > 10000.0f) {
		//mGAMELOG.GL_659_AUTO_CHECK(tUserIndex, 8, fRange);
		//mGAMELOG.GL_659_AUTO_CHECK(tOtherAvatarIndex, 8, fRange);
		mTRANSFER.B_BUY_PSHOP_RECV(8, 0, 0, 0, &tValue[0], &tSocketValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	if (1 == mUSER[tUserIndex].mAuthInfo.PShopFlag) {
		mTRANSFER.B_BUY_PSHOP_RECV(8, 0, 0, 0, &tValue[0], &tSocketValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		mTRANSFER.B_BUY_PSHOP_RECV(1, 0, 0, 0, &tValue[0], &tSocketValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aPShopState != 1)
	{
		mTRANSFER.B_BUY_PSHOP_RECV(2, 0, 0, 0, &tValue[0], &tSocketValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mUniqueNumber != tUniqueNumber)
	{
		mTRANSFER.B_BUY_PSHOP_RECV(7, 0, 0, 0, &tValue[0], &tSocketValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (1 == mUSER[tOtherAvatarIndex].mAuthInfo.PShopFlag) {
		mTRANSFER.B_BUY_PSHOP_RECV(9, 0, 0, 0, &tValue[0], &tSocketValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	CopyMemory(&tItemInfo[0], &mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][0], 36);
	CopyMemory(&tSocketInfo[0], &mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mSoketInfo[tPage1][tIndex1][0], 12);
	if (tItemInfo[0] < 1)
	{
		mTRANSFER.B_BUY_PSHOP_RECV(3, 0, 0, 0, &tValue[0], &tSocketValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_DEMAND_PSHOP_RECV(0, &mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][0] != tItemInfo[0]) || (mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][1] != tItemInfo[7]) || (mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][2] != tItemInfo[8]) || (mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][3] != tItemInfo[1]) || (mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][4] != tItemInfo[2]) || (mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][5] != tItemInfo[3]))
	{
		mTRANSFER.B_BUY_PSHOP_RECV(4, 0, 0, 0, &tValue[0], &tSocketValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mUTIL.CheckOverMaximum(mUSER[tOtherAvatarIndex].mAvatarInfo.aMoney, tItemInfo[4]))
	{
		mTRANSFER.B_BUY_PSHOP_RECV(5, 0, 0, 0, &tValue[0], &tSocketValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (tPage2 == 1)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	if (mUSER[tUserIndex].mAvatarInfo.aMoney < tItemInfo[4])
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] > 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tValue[0] = tItemInfo[0];
	tValue[1] = tXPost2;
	tValue[2] = tYPost2;
	tValue[3] = tItemInfo[1];
	tValue[4] = tItemInfo[2];
	tValue[5] = tItemInfo[3];
	tSocketValue[0] = tSocketInfo[0];
	tSocketValue[1] = tSocketInfo[1];
	tSocketValue[2] = tSocketInfo[2];
	//mGAMELOG.GL_609_PSHOP_ITEM(tUserIndex, 1, tItemInfo[0], tItemInfo[1], tItemInfo[2], tItemInfo[3], tItemInfo[4]);
	mUSER[tUserIndex].mAvatarInfo.aMoney -= tItemInfo[4];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = tValue[0];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = tValue[1];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = tValue[2];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = tValue[3];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = tValue[4];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = tValue[5];
	mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][0] = tSocketValue[0];
	mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][1] = tSocketValue[1];
	mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][2] = tSocketValue[2];
	mTRANSFER.B_BUY_PSHOP_RECV(0, tItemInfo[4], tPage2, tIndex2, &tValue[0], &tSocketValue[0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	ITEM = mITEM.Search(tValue[0]);

	mGAMELOG.GL_BUY_SHOP_ITEM(tUserIndex, tOtherAvatarIndex, ITEM->iIndex, ITEM->iName, tValue[3], tSocketValue[0], tSocketValue[1], tSocketValue[2], tItemInfo[4]);
	mUSER[tOtherAvatarIndex].mAvatarInfo.aMoney += tItemInfo[4];
	mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][0] = 0;
	mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][1] = 0;
	mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][2] = 0;
	mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][3] = 0;
	mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][4] = 0;
	mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][5] = 0;
	mUSER[tOtherAvatarIndex].mAvatarInfo.InventorySocket[tItemInfo[5]][tItemInfo[6]][0] = 0;
	mUSER[tOtherAvatarIndex].mAvatarInfo.InventorySocket[tItemInfo[5]][tItemInfo[6]][1] = 0;
	mUSER[tOtherAvatarIndex].mAvatarInfo.InventorySocket[tItemInfo[5]][tItemInfo[6]][2] = 0;
	mTRANSFER.B_BUY_PSHOP_RECV(6, tItemInfo[4], tItemInfo[5], tItemInfo[6], &tValue[0], &tSocketValue[0]);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][0] = 0;
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][1] = 0;
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][2] = 0;
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][3] = 0;
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][4] = 0;
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][5] = 0;
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][6] = 0;
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][7] = 0;
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][8] = 0;
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mSoketInfo[tPage1][tIndex1][0] = 0;
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mSoketInfo[tPage1][tIndex1][1] = 0;
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mSoketInfo[tPage1][tIndex1][2] = 0;
	mTRANSFER.B_DEMAND_PSHOP_RECV(0, &mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	mTRANSFER.B_DEMAND_PSHOP_RECV(3, &mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_PROCESS_QUEST_SEND 
void W_PROCESS_QUEST_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	int tPage;
	int tIndex;
	int tXPost;
	int tYPost;
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tPage, &tPacket[5], 4);
	CopyMemory(&tIndex, &tPacket[9], 4);
	CopyMemory(&tXPost, &tPacket[13], 4);
	CopyMemory(&tYPost, &tPacket[17], 4);

	int index01;
	QUEST_INFO* tQUEST_INFO;

	if (mUSER[tUserIndex].mHealthState == 5)
	{
		mTRANSFER.B_PROCESS_QUEST_RECV(1, tSort, tPage, tIndex, tXPost, tYPost);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	switch (tSort)
	{
	case 1: //[ÀÓ¹«_¹ß±Þ]
		if (mAVATAR_OBJECT[tUserIndex].ReturnQuestPresentState() != 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tQUEST_INFO = mQUEST.Search(mUSER[tUserIndex].mAvatarInfo.aTribe, (mUSER[tUserIndex].mAvatarInfo.aQuestInfo[0] + 1));
		if (tQUEST_INFO == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (tQUEST_INFO->qSort)
		{
		case 3:
		case 6:
			if ((tPage < 0) || (tPage > 1) || (tIndex < 0) || (tIndex > (MAX_INVENTORY_SLOT_NUM - 1)) || (tXPost < 0) || (tXPost > 7) || (tYPost < 0) || (tYPost > 7))
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if (tPage == 1)
			{
				if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
			if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] > 0)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tQUEST_INFO->qSolution[0];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = tXPost;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = tYPost;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			break;
		}
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[0]++;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[1] = 1;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[2] = tQUEST_INFO->qSort;
		if (tQUEST_INFO->qSort != 6)
		{
			mUSER[tUserIndex].mAvatarInfo.aQuestInfo[3] = tQUEST_INFO->qSolution[0];
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.aQuestInfo[3] = 1;
		}
		if (tQUEST_INFO->qSort != 6)
		{
			mUSER[tUserIndex].mAvatarInfo.aQuestInfo[4] = 0;
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.aQuestInfo[4] = tQUEST_INFO->qSolution[0];
		}
		mTRANSFER.B_PROCESS_QUEST_RECV(0, tSort, tPage, tIndex, tXPost, tYPost);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 2: //[ÀÓ¹«_¿Ï·á]
		if (mAVATAR_OBJECT[tUserIndex].ReturnQuestEndConditionState() != 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tQUEST_INFO = mQUEST.Search(mUSER[tUserIndex].mAvatarInfo.aTribe, mUSER[tUserIndex].mAvatarInfo.aQuestInfo[0]);
		if (tQUEST_INFO == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tPage != -1)
		{
			if ((tPage < 0) || (tPage > 1) || (tIndex < 0) || (tIndex > (MAX_INVENTORY_SLOT_NUM - 1)) || (tXPost < 0) || (tXPost > 7) || (tYPost < 0) || (tYPost > 7))
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if (tPage == 1)
			{
				if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
			if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] > 0)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			//mGAMELOG.GL_610_QUEST_ITEM(tUserIndex, mAVATAR_OBJECT[tUserIndex].ReturnItemNumberForQuestReward(), mAVATAR_OBJECT[tUserIndex].ReturnItemQuantityForQuestReward(), 0, 0);
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = mAVATAR_OBJECT[tUserIndex].ReturnItemNumberForQuestReward();
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = tXPost;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = tYPost;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = mAVATAR_OBJECT[tUserIndex].ReturnItemQuantityForQuestReward();
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		}
		for (index01 = 0; index01 < 3; index01++)
		{
			switch (tQUEST_INFO->qReward[index01][0])
			{
			case 1:
				break;
			case 2:
				if (mUTIL.CheckOverMaximum(mUSER[tUserIndex].mAvatarInfo.aMoney, tQUEST_INFO->qReward[index01][1]))
				{
					break;
				}
				//mGAMELOG.GL_611_QUEST_MONEY(tUserIndex, tQUEST_INFO->qReward[index01][1]);
				mUSER[tUserIndex].mAvatarInfo.aMoney += tQUEST_INFO->qReward[index01][1];
				break;
			case 3:
				//mGAMELOG.GL_612_QUEST_KILL_NUM(tUserIndex, tQUEST_INFO->qReward[index01][1]);
				mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += tQUEST_INFO->qReward[index01][1];
				mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += tQUEST_INFO->qReward[index01][1];
				break;
			case 4:
				//mGAMELOG.GL_613_QUEST_EXP(tUserIndex, tQUEST_INFO->qReward[index01][1]);
				mUTIL.ProcessForExperience(tUserIndex, tQUEST_INFO->qReward[index01][1], 0, 0);
				break;
			case 5:
				/*//mGAMELOG.GL_614_QUEST_TEACHER_POINT( tUserIndex, tQUEST_INFO->qReward[index01][1] );
				mUSER[tUserIndex].mAvatarInfo.aTeacherPoint += tQUEST_INFO->qReward[index01][1];*/
				break;
			case 6:
				break;
			}
		}
		switch (mUSER[tUserIndex].mAvatarInfo.aQuestInfo[2])
		{
		case 2:
			mAVATAR_OBJECT[tUserIndex].DeleteQuestItem(tQUEST_INFO->qSolution[0]);
			break;
		case 3:
			mAVATAR_OBJECT[tUserIndex].DeleteQuestItem(tQUEST_INFO->qSolution[0]);
			break;
		case 4:
			mAVATAR_OBJECT[tUserIndex].DeleteQuestItem(tQUEST_INFO->qSolution[0]);
			break;
		case 6:
			mAVATAR_OBJECT[tUserIndex].DeleteQuestItem(tQUEST_INFO->qSolution[1]);
			break;
		}
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[4] = 0;
		mTRANSFER.B_PROCESS_QUEST_RECV(0, tSort, tPage, tIndex, tXPost, tYPost);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 3: //[ÀÓ¹«¹°Ç°_¹ÞÀ½]
		switch (mUSER[tUserIndex].mAvatarInfo.aQuestInfo[2])
		{
		case 3:
			if (mAVATAR_OBJECT[tUserIndex].ReturnQuestPresentState() != 2)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 4:
			if (mAVATAR_OBJECT[tUserIndex].ReturnQuestPresentState() != 2)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 6:
			if ((mAVATAR_OBJECT[tUserIndex].ReturnQuestPresentState() != 2) && (mAVATAR_OBJECT[tUserIndex].ReturnQuestPresentState() != 4))
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		default:
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tQUEST_INFO = mQUEST.Search(mUSER[tUserIndex].mAvatarInfo.aTribe, mUSER[tUserIndex].mAvatarInfo.aQuestInfo[0]);
		if (tQUEST_INFO == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tPage < 0) || (tPage > 1) || (tIndex < 0) || (tIndex > (MAX_INVENTORY_SLOT_NUM - 1)) || (tXPost < 0) || (tXPost > 7) || (tYPost < 0) || (tYPost > 7))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tPage == 1)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] > 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tQUEST_INFO->qSolution[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = tXPost;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = tYPost;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_PROCESS_QUEST_RECV(0, tSort, tPage, tIndex, tXPost, tYPost);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 4: //[ÀÓ¹«¹°Ç°_±³È¯]
		switch (mUSER[tUserIndex].mAvatarInfo.aQuestInfo[2])
		{
		case 6:
			if (mAVATAR_OBJECT[tUserIndex].ReturnQuestPresentState() != 3)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		default:
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tQUEST_INFO = mQUEST.Search(mUSER[tUserIndex].mAvatarInfo.aTribe, mUSER[tUserIndex].mAvatarInfo.aQuestInfo[0]);
		if (tQUEST_INFO == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mAVATAR_OBJECT[tUserIndex].ChangeQuestItem(tQUEST_INFO->qSolution[0], tQUEST_INFO->qSolution[1]);
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[3] = 2;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[4] = tQUEST_INFO->qSolution[1];
		mTRANSFER.B_PROCESS_QUEST_RECV(0, tSort, tPage, tIndex, tXPost, tYPost);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 5: //[ÀÓ¹«_Æ÷±â]
		if ((mAVATAR_OBJECT[tUserIndex].ReturnQuestPresentState() == 0) || (mAVATAR_OBJECT[tUserIndex].ReturnQuestPresentState() == 1))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tQUEST_INFO = mQUEST.Search(mUSER[tUserIndex].mAvatarInfo.aTribe, mUSER[tUserIndex].mAvatarInfo.aQuestInfo[0]);
		if (tQUEST_INFO == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tQUEST_INFO->qType != 2)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mAVATAR_OBJECT[tUserIndex].ReturnQuestEndConditionState() != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[4] = 0;
		mTRANSFER.B_PROCESS_QUEST_RECV(0, tSort, tPage, tIndex, tXPost, tYPost);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	default: //[¿À·ù]
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}
//W_CHANGE_TO_TRIBE4_SEND
void W_CHANGE_TO_TRIBE4_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	time_t tCountSeconds;
	struct tm* tPresentTime;

	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		mTRANSFER.B_CHANGE_TO_TRIBE4_RECV(2);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	//saturday, 12:00 ~ 24:00
	if (((tPresentTime->tm_wday != 6) || (tPresentTime->tm_hour < 12)) &&
		((tPresentTime->tm_wday != 0) || (tPresentTime->tm_hour > 0) || (tPresentTime->tm_min > 0)))
	{
		mTRANSFER.B_CHANGE_TO_TRIBE4_RECV(2);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	int index01;
	int iCount = 0;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];

	switch (mUSER[tUserIndex].mAvatarInfo.aTribe)
	{
	case 0:
		if (mSERVER_INFO.mServerNumber != 71)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 1:
		if (mSERVER_INFO.mServerNumber != 72)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 2:
		if (mSERVER_INFO.mServerNumber != 73)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	}

	for (iCount = 0; iCount < MAX_TRIBE_VOTE_AVATAR_NUM; iCount++) {
		if (!::strcmp(mGAME.mTribeInfo.mTribeVoteName[mUSER[tUserIndex].mAvatarInfo.aTribe][iCount]
			, mUSER[tUserIndex].mAvatarInfo.aName)) {
			mTRANSFER.B_CHANGE_TO_TRIBE4_RECV(1);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
	}

	if (mUSER[tUserIndex].mAvatarInfo.aTribe == 3)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 113)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
#if 0
	if (mGAME.ReturnTribePointWithAlliance(mUSER[tUserIndex].mAvatarInfo.aTribe) < 100)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mGAME.CheckPossibleChangeToTribe4(mUSER[tUserIndex].mAvatarInfo.aTribe) != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
#endif
	if (100 > mGAME.mWorldInfo.mTribePoint[mUSER[tUserIndex].mAvatarInfo.aTribe]) {
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mGAME.CheckPossibleChangeToTribe4_2(mUSER[tUserIndex].mAvatarInfo.aTribe) != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aTeacher, "") != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aStudent, "") != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	for (index01 = 0; index01 < MAX_FRIEND_NUM; index01++)
	{
		if (strcmp(mUSER[tUserIndex].mAvatarInfo.aFriend[index01], "") != 0)
		{
			break;
		}
	}
	if (index01 < MAX_FRIEND_NUM)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	mUSER[tUserIndex].mAvatarInfo.aTribe = 3;
	mUSER[tUserIndex].mAvatarInfo.aQuestInfo[0] = 0;
	mUSER[tUserIndex].mAvatarInfo.aQuestInfo[1] = 0;
	mUSER[tUserIndex].mAvatarInfo.aQuestInfo[2] = 0;
	mUSER[tUserIndex].mAvatarInfo.aQuestInfo[3] = 0;
	mUSER[tUserIndex].mAvatarInfo.aQuestInfo[4] = 0;
	mAVATAR_OBJECT[tUserIndex].mDATA.aTribe = 3;
	mTRANSFER.B_CHANGE_TO_TRIBE4_RECV(0);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	//--------------//
	//BROADCAST_INFO//
	//--------------//
	tBroadcastInfoSort = 51;
	CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, 4);
	CopyMemory(&tBroadcastInfoData[4], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
	mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
	//--------------//
	//--------------//
	//--------------//
}
//W_GENERAL_CHAT_SEND ---- Çalışıyor
void W_GENERAL_CHAT_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	//unsigned int tRandom = 0;
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];


	char tContent[MAX_CHAT_CONTENT_LENGTH];
	CopyMemory(&tContent[0], &tPacket[1], MAX_CHAT_CONTENT_LENGTH);
	tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
	if (strcmp(tContent, "") == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	char mSendData[MAX_SEND_DATA_SIZE];
	int mSendDataSize;
	char mRecvData[MAX_RECV_DATA_SIZE];
	int mRecvDataSize;
	int index01;
	int index02;
	int index03;
	float tPostLocation[3];
	int tSpaceIndex[3];
	float tLocation[3];
	BYTE tAuthType = 0;
	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	int Defanse;
	int health;
	int Atak;
	int adet;
	int tMonsterNumber;
	int expFlag;

	tPostLocation[0] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0];
	tPostLocation[1] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[1];
	tPostLocation[2] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[2];
	tSpaceIndex[0] = (int)(tPostLocation[0] / mGAME.MAX_RADIUS);
	tSpaceIndex[1] = (int)(tPostLocation[1] / mGAME.MAX_RADIUS);
	tSpaceIndex[2] = (int)(tPostLocation[2] / mGAME.MAX_RADIUS);
	
	
	
	

	if (1 == mUSER[tUserIndex].mAuthInfo.AuthType) {
		tAuthType = 1;
	}
	

	if (strcmp(tContent, "%%exp") == 0)
	{
		// Display a message if the string matches
		switch (mUSER[tUserIndex].mAuthInfo.Explock)
		{
		case 0:
			// If Explock is 0, change to 1 and send a message "Experience is locked!"
			mTRANSFER.B_SECRET_CHAT_RECV(3, 0, &mUSER[tUserIndex].mAvatarInfo.aName[0], "Experience is locked!", 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize, false);
			mUSER[tUserIndex].mAuthInfo.Explock = 1;
			break;
		case 1:
			// If Explock is 1, change to 0 and send a message "Experience is unlocked"
			mTRANSFER.B_SECRET_CHAT_RECV(3, 0, &mUSER[tUserIndex].mAvatarInfo.aName[0], "Experience is unlocked!", 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize, false);
			mUSER[tUserIndex].mAuthInfo.Explock = 0;
			break;
		default:
			// Handle other cases if needed
			break;
		}
		return;
	}
	
	
	//if (strcmp(tContent, "%%exp") == 0)
	//{

	//	// Display a message if the string matches

	//	mTRANSFER.B_SECRET_CHAT_RECV(3, 0, &mUSER[tUserIndex].mAvatarInfo.aName[0], "Experince is locked!", 0);  // Assuming 3 is a code for a specific message type
	//	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize, false);
	//	mUSER[tUserIndex].mAuthInfo.Explock = 1;
	//	return;
	//}
	//if (strcmp(tContent, "%%expunlock") == 0)
	//{
	//	// Display a message if the string matches

	//	mTRANSFER.B_SECRET_CHAT_RECV(3, 0, &mUSER[tUserIndex].mAvatarInfo.aName[0], "Experince is unlocked!", 0);  // Assuming 3 is a code for a specific message type
	//	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize, false);
	//	mUSER[tUserIndex].mAuthInfo.Explock = 0;
	//	return;
	//}
	if (mUSER[tUserIndex].mAuthInfo.AuthType != 0)
	{
		
		if (strcmp(tContent, "%%war") == 0)
		{
			mUSER[tUserIndex].mAvatarInfo.PlayerKill = 10;
			mUSER[tUserIndex].mAvatarInfo.MonsterKill = 1000;
			mUSER[tUserIndex].mAvatarInfo.PlayTimeDay = 60;
			mTRANSFER.B_DAILY_MISSION(2, 0, mUSER[tUserIndex].mAvatarInfo.JoinWar, mUSER[tUserIndex].mAvatarInfo.PlayerKill, mUSER[tUserIndex].mAvatarInfo.MonsterKill, mUSER[tUserIndex].mAvatarInfo.PlayTimeDay);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		
		
		/*if (strcmp(tContent, "%%test") == 0)
		{
			ZeroMemory(&tData[0], sizeof(tData));
			tSort = 506;
			mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
			mSUMMON.SummonMonsterForSpecial(12, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], FALSE);
			return;
		}*/

	/*	int tMonsterNumber = 0;
		if (sscanf(tContent, "%%test %d", &tMonsterNumber) == 1) {
			ZeroMemory(&tData[0], sizeof(tData));
			tSort = 506;
			mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
			mSUMMON.SummonMonsterForSpecial(tMonsterNumber, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], FALSE);
			return;
		}*/

		
		float centerX = -4;
		float centerY = 0;
		float centerZ = -1353;
		int numPoints = 0; // Initialize numPoints with the default value
		float radius;       // Initialize radius with the default value
		char text;
		int pointsPerSide = numPoints / 4;

		// Calculate and spawn the coordinates of the points for a square
		float halfSide = radius / 2;
		float step = halfSide / (pointsPerSide - 1) * 2; // Calculate the step size





		if (sscanf(tContent, "``event %c %d %d %f", &text, &tMonsterNumber, &numPoints, &radius) == 4) {
			// The input matches the "``event %d" format, and tMonsterNumber, numPoints, and radius contain the extracted values

			if (mSERVER_INFO.mServerNumber != 37 && mSERVER_INFO.mServerNumber != 38 && mSERVER_INFO.mServerNumber != 340) {
				// Server number doesn't match, handle the case accordingly
				// For now, you can just return or do nothing
				return;
			}
			switch (text) {
			case 'c':
				// Calculate and spawn the coordinates of the points
				for (int j = 0; j < numPoints; j++) {
					float angle = 2.0 * M_PI * j / numPoints;
					float x = centerX + radius * cos(angle);
					float y = centerY;
					float z = centerZ + radius * sin(angle);

					// Spawn a monster using mSUMMON with the calculated coordinates
					float tMonsterLocation[3] = { x, y, z };
					mSUMMON.SummonMonsterForSpecial(tMonsterNumber, tMonsterLocation, false);
				}
				
				break;
			case 's':
		
				if (numPoints % 4 != 0) {
					// Ensure that numPoints is a multiple of 4
					numPoints = 100; // or set it to a valid value
				}

				// Calculate and spawn the points on the top side
				for (int j = 0; j < numPoints / 4; j++) {
					float x = centerX - halfSide + j * step;
					float y = centerY;
					float z = centerZ - halfSide;
					float tMonsterLocation[3] = { x, y, z };
					mSUMMON.SummonMonsterForSpecial(tMonsterNumber, tMonsterLocation, false);
				}

				// Calculate and spawn the points on the right side
				for (int j = 1; j < numPoints / 4; j++) {
					float x = centerX + halfSide;
					float y = centerY;
					float z = centerZ - halfSide + j * step;
					float tMonsterLocation[3] = { x, y, z };
					mSUMMON.SummonMonsterForSpecial(tMonsterNumber, tMonsterLocation, false);
				}

				// Calculate and spawn the points on the bottom side
				for (int j = 1; j < numPoints / 4; j++) {
					float x = centerX + halfSide - j * step;
					float y = centerY;
					float z = centerZ + halfSide;
					float tMonsterLocation[3] = { x, y, z };
					mSUMMON.SummonMonsterForSpecial(tMonsterNumber, tMonsterLocation, false);
				}

				// Calculate and spawn the points on the left side
				for (int j = 1; j < numPoints / 4 - 1; j++) {
					float x = centerX - halfSide;
					float y = centerY;
					float z = centerZ + halfSide - j * step;
					float tMonsterLocation[3] = { x, y, z };
					mSUMMON.SummonMonsterForSpecial(tMonsterNumber, tMonsterLocation, false);
				}
				break;

			}
			return;

		}


	




		if (strcmp(tContent, "%%Delete") == 0){
			mSUMMON.DeleteMonster();
			return;
		}
		if (strcmp(tContent, "%%Update") == 0)
		{
			ZeroMemory(&tData[0], sizeof(tData));
			tSort = 999;
			mRELAY_COM.U_DEMAND_BROADCAST_DATA(tSort, &tData[0]);
			return;
		}
		if (strcmp(tContent, "%%Shutdown") == 0) {
			char* tPacket = &mRecvData[0];

			int index01;

			for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
			{
				mUSER[index01].Quit(__FILE__, __FUNCTION__, __LINE__);
			}
			return;
		}
		if (strcmp(tContent, "%%Restart") == 0)
		{
			ZeroMemory(&tData[0], sizeof(tData));
			tSort = 997;
			mRELAY_COM.U_DEMAND_BROADCAST_DATA(tSort, &tData[0]);
			return;
		}

		if (strcmp(tContent, "%%UpdateCostInfo") == 0)
		{
			ZeroMemory(&tData[0], sizeof(tData));
			mEXTRA_COM.U_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_SEND();
			tSort = 998;
			mRELAY_COM.U_DEMAND_BROADCAST_DATA(tSort, &tData[0]);
			return;
		}
		if (strcmp(tContent, "%%UpdateBloodItem") == 0)
		{
		
			ZeroMemory(&tData[0], sizeof(tData));
			mEXTRA_COM.U_BUY_BLOOD_ITEM_FOR_EXTRA_SEND(1);
			tSort = 996;
			mRELAY_COM.U_DEMAND_BROADCAST_DATA(tSort, &tData[0]);
			return;
		}





		if (strcmp(tContent, "%%StartVote1") == 0)
		{
			if (mSERVER_INFO.mServerNumber == 37)
			{
				tBroadcastInfoSort = 52;
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
				mGAME.mWorldInfo.mTribeVoteState[0] = 1;
				mGAME.mWorldInfo.mTribeVoteState[1] = 1;
				mGAME.mWorldInfo.mTribeVoteState[2] = 1;
				mGAME.mWorldInfo.mTribeVoteState[3] = 1;
				for (index01 = 0; index01 < 4; index01++)
				{
					for (index02 = 0; index02 < MAX_TRIBE_VOTE_AVATAR_NUM; index02++)
					{
						strcpy(mGAME.mTribeInfo.mTribeVoteName[index01][index02], "");
						mGAME.mTribeInfo.mTribeVoteLevel[index01][index02] = 0;
						mGAME.mTribeInfo.mTribeVoteKillOtherTribe[index01][index02] = 0;
						mGAME.mTribeInfo.mTribeVotePoint[index01][index02] = 0;
					}
				}
				return;
			}
			return;
		}
		if (strcmp(tContent, "%%StartVote2") == 0)
		{
			if (mSERVER_INFO.mServerNumber == 37)
			{
				tBroadcastInfoSort = 53;
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
				mGAME.mWorldInfo.mTribeVoteState[0] = 2;
				mGAME.mWorldInfo.mTribeVoteState[1] = 2;
				mGAME.mWorldInfo.mTribeVoteState[2] = 2;
				mGAME.mWorldInfo.mTribeVoteState[3] = 2;
				return;
			}
			return;
		}
		if (strcmp(tContent, "%%StartVote3") == 0)
		{
			if (mSERVER_INFO.mServerNumber == 37)
			{
				tBroadcastInfoSort = 54;
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
				mGAME.mWorldInfo.mTribeVoteState[0] = 3;
				mGAME.mWorldInfo.mTribeVoteState[1] = 3;
				mGAME.mWorldInfo.mTribeVoteState[2] = 3;
				mGAME.mWorldInfo.mTribeVoteState[3] = 3;
				return;
			}
			return;
		}
		if (strcmp(tContent, "%%StartVote4") == 0)
		{
			if (mSERVER_INFO.mServerNumber == 37)
			{
				tBroadcastInfoSort = 55;
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
				mGAME.mWorldInfo.mTribeVoteState[0] = 4;
				mGAME.mWorldInfo.mTribeVoteState[1] = 4;
				mGAME.mWorldInfo.mTribeVoteState[2] = 4;
				mGAME.mWorldInfo.mTribeVoteState[3] = 4;
				for (index01 = 0; index01 < 4; index01++)
				{
					index03 = -1;
					for (index02 = 0; index02 < MAX_TRIBE_VOTE_AVATAR_NUM; index02++)
					{
						if (strcmp(mGAME.mTribeInfo.mTribeVoteName[index01][index02], "") == 0)
						{
							continue;
						}
						if (mGAME.mTribeInfo.mTribeVotePoint[index01][index02] < 1)
						{
							continue;
						}
						if (index03 == -1)
						{
							index03 = index02;
						}
						else
						{
							if (mGAME.mTribeInfo.mTribeVotePoint[index01][index02] > mGAME.mTribeInfo.mTribeVotePoint[index01][index03])
							{
								index03 = index02;
							}
						}
					}
					if (index03 == -1)
					{
						strcpy(mGAME.mTribeInfo.mTribeMaster[index01], "");
					}
					else
					{
						strncpy(mGAME.mTribeInfo.mTribeMaster[index01], mGAME.mTribeInfo.mTribeVoteName[index01][index03], MAX_AVATAR_NAME_LENGTH);
					}
					for (index02 = 0; index02 < MAX_TRIBE_SUBMASTER_NUM; index02++)
					{
						strcpy(mGAME.mTribeInfo.mTribeSubMaster[index01][index02], "");
					}
				}
				return;
			}
			return;
		}
		if (strcmp(tContent, "%%EndVote") == 0)
		{
			if (mSERVER_INFO.mServerNumber == 37)
			{
				tBroadcastInfoSort = 56;
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
				mGAME.mWorldInfo.mTribeVoteState[0] = 0;
				mGAME.mWorldInfo.mTribeVoteState[1] = 0;
				mGAME.mWorldInfo.mTribeVoteState[2] = 0;
				mGAME.mWorldInfo.mTribeVoteState[3] = 0;
				return;
			}
			return;
		}
		if (strcmp(tContent, "%%Clear") == 0)
		{
			for (int index01 = 0; index01 < 2; index01++)
			{
				for (int index02 = 0; index02 < 64; index02++)
				{
					mUSER[tUserIndex].mAvatarInfo.aInventory[index01][index02][0] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[index01][index02][1] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[index01][index02][2] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[index01][index02][3] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[index01][index02][4] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[index01][index02][5] = 0;
					mUSER[tUserIndex].mAvatarInfo.InventorySocket[index01][index02][0] = 0;
					mUSER[tUserIndex].mAvatarInfo.InventorySocket[index01][index02][1] = 0;
					mUSER[tUserIndex].mAvatarInfo.InventorySocket[index01][index02][2] = 0;
					mTRANSFER.B_ITEM_SEND(0, 0, index01, index02, 0);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
			}
			return;
		}

		char* content = &tContent[0];
		char itemType;
		int itemCount, itemNumber, enchant = 0, combine = 0;


		// Extract the item type, count, and item number
		int parsedCount = sscanf(content, "%c %d %d %d %d", &itemType, &itemCount, &itemNumber, &enchant, &combine);

		

		if (parsedCount >= 3 && itemType == 'i')
		{
			
		
			if (enchant > 150) {
				enchant = 150;
			}
		
			if (combine > 12) {
				combine = 12;
			}
			if (itemCount < 0) {
				itemCount = 1;
			}
			if (itemCount > 100) {
				itemCount = 100;
			}
			int ench = ((enchant / 3) + combine*256);
			for (int i = 0; i < itemCount; i++)
			{
				
				mUTIL.ProcessForDropItem(4, itemNumber, 0, ench, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], 0, mUSER[tUserIndex].DropItemSocketGmAndBos);

				
			}
			
			GameLogger(3, "<GM_CREATE_ITEM>(%s),(%s),(Item: %d)(Qty:%d),(Enchant:%d)(CS:%d)->(Total:%d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, itemNumber,enchant,combine,ench, mSERVER_INFO.mServerNumber);
			return;
		}


		




		tSort = 115;
		CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&tData[MAX_AVATAR_NAME_LENGTH], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		CopyMemory(&tData[(MAX_AVATAR_NAME_LENGTH + MAX_CHAT_CONTENT_LENGTH)], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
		mRELAY_COM.U_DEMAND_BROADCAST_DATA(tSort, &tData[0]);
		return;
	}

	mTRANSFER.B_GENERAL_CHAT_RECV(&mUSER[tUserIndex].mAvatarInfo.aName[0], tAuthType, &tContent[0]);

	char type[50];
	snprintf(type, 50, "W_GENERAL_CHAT_SEND");
	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (!mAVATAR_OBJECT[index01].mCheckValidState)
		{
			continue;
		}
		if (1 != mUSER[tUserIndex].mAuthInfo.AuthType) {
			if ((1 != mUSER[index01].mAuthInfo.AuthType) || (1 != mAVATAR_OBJECT[index01].mChat)) {
				if ((mAVATAR_OBJECT[index01].mDATA.aTribe != mAVATAR_OBJECT[tUserIndex].mDATA.aTribe)
					&& (mAVATAR_OBJECT[index01].mDATA.aTribe != mGAME.ReturnAllianceTribe(mAVATAR_OBJECT[tUserIndex].mDATA.aTribe))
					&& (mSERVER_INFO.mServerNumber != ZONE_PRISON))
				{
					continue;
				}
			}
		}
		else {
			if (1 != mAVATAR_OBJECT[tUserIndex].mChat) {
				if ((mAVATAR_OBJECT[index01].mDATA.aTribe != mAVATAR_OBJECT[tUserIndex].mDATA.aTribe)
					&& (mAVATAR_OBJECT[index01].mDATA.aTribe != mGAME.ReturnAllianceTribe(mAVATAR_OBJECT[tUserIndex].mDATA.aTribe))
					&& (mSERVER_INFO.mServerNumber != ZONE_PRISON))
				{
					continue;
				}
			}
		}


		if ((1 != mUSER[tUserIndex].mAuthInfo.AuthType) && (1 != mUSER[index01].mAuthInfo.AuthType)) {
			if ((mAVATAR_OBJECT[index01].mDATA.aTribe != mAVATAR_OBJECT[tUserIndex].mDATA.aTribe)
				&& (mAVATAR_OBJECT[index01].mDATA.aTribe != mGAME.ReturnAllianceTribe(mAVATAR_OBJECT[tUserIndex].mDATA.aTribe))
				&& (mSERVER_INFO.mServerNumber != ZONE_PRISON))
			{
				continue;
			}
		}
#ifdef __GOD__
		if ((mAVATAR_OBJECT[index01].mDATA.aTribe != mAVATAR_OBJECT[tUserIndex].mDATA.aTribe) && (mAVATAR_OBJECT[index01].mDATA.aTribe != mGAME.ReturnAllianceTribe(mAVATAR_OBJECT[tUserIndex].mDATA.aTribe)))
		{
			continue;
		}
#endif
		if ((abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[0] - tSpaceIndex[0]) > 1) || (abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[1] - tSpaceIndex[1]) > 1) || (abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[2] - tSpaceIndex[2]) > 1))
		{
			continue;
		}
		tLocation[0] = mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0];
		tLocation[1] = mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[1];
		tLocation[2] = mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[2];
		if (((tLocation[0] - tPostLocation[0]) * (tLocation[0] - tPostLocation[0]) + (tLocation[1] - tPostLocation[1]) * (tLocation[1] - tPostLocation[1]) + (tLocation[2] - tPostLocation[2]) * (tLocation[2] - tPostLocation[2])) > (mGAME.MAX_RADIUS * mGAME.MAX_RADIUS))
		{
			continue;
		}
		mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}

	return;
}
//W_SECRET_CHAT_SEND 
void W_SECRET_CHAT_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	char tContent[MAX_CHAT_CONTENT_LENGTH];
	CopyMemory(&tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
	CopyMemory(&tContent[0], &tPacket[(1 + MAX_AVATAR_NAME_LENGTH)], MAX_CHAT_CONTENT_LENGTH);
	tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
	if (strcmp(tContent, "") == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	if ((strncmp(mUSER[tUserIndex].mAvatarInfo.aName, tAvatarName, MAX_AVATAR_NAME_LENGTH) == 0)
		|| (strcmp(tAvatarName, "") == 0))
	{
		return;
	}
	mPLAYUSER_COM.U_FIND_AVATAR_FOR_ZONE_SEND(&tAvatarName[0]);
	if (mPLAYUSER_COM.mRecv_ZoneNumber < 1)
	{
		mTRANSFER.B_SECRET_CHAT_RECV(1, 0, &tAvatarName[0], &tContent[0], 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize, false);
		return;
	}
	if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
	{
		if ((mUSER[tUserIndex].mAvatarInfo.aTribe != mPLAYUSER_COM.mRecv_Tribe) && (mUSER[tUserIndex].mAvatarInfo.aTribe != mGAME.ReturnAllianceTribe(mPLAYUSER_COM.mRecv_Tribe)))
		{
			mTRANSFER.B_SECRET_CHAT_RECV(2, 0, &tAvatarName[0], &tContent[0], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize, false);
			return;
		}
	}
	mTRANSFER.B_SECRET_CHAT_RECV(0, mPLAYUSER_COM.mRecv_ZoneNumber, &tAvatarName[0], &tContent[0], mUSER[tUserIndex].mAuthInfo.AuthType);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize, false);
	tSort = 103;
	CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
	CopyMemory(&tData[MAX_AVATAR_NAME_LENGTH], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	CopyMemory(&tData[(MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
	CopyMemory(&tData[(MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_CHAT_CONTENT_LENGTH)], &mUSER[tUserIndex].mAuthInfo.AuthType, 1);
	mRELAY_COM.U_DEMAND_BROADCAST_DATA(tSort, &tData[0]);

}
//W_GENERAL_SHOUT_SEND 
void W_GENERAL_SHOUT_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	//unsigned int tRandom = 0;
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	char tContent[MAX_CHAT_CONTENT_LENGTH];
	BYTE tAuthType = 0;
	CopyMemory(&tContent[0], &tPacket[1], MAX_CHAT_CONTENT_LENGTH);
	tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
	if (strcmp(tContent, "") == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (mUSER[tUserIndex].mAvatarInfo.aSpecialState == 2)
	{
		return;
	}
	if ((mSERVER_INFO.mServerNumber != 37) && (mSERVER_INFO.mServerNumber != 119) && (mSERVER_INFO.mServerNumber != 124) &&
		(mSERVER_INFO.mServerNumber != 84) && (mSERVER_INFO.mServerNumber != 170))
	{
		return;
	}
	if (1 == mUSER[tUserIndex].mAuthInfo.AuthType)
		tAuthType = 1;

	mTRANSFER.B_GENERAL_SHOUT_RECV(&mUSER[tUserIndex].mAvatarInfo.aName[0], tAuthType, &tContent[0]);

	char type[50];
	snprintf(type, 50, "W_GENERAL_SHOUT_SEND");
	//mGAMELOG.CHAT_LOG_SEND(tUserIndex, NULL, &tContent[0], type);
	mUTIL.Broadcast(FALSE, NULL, 0, false);
}
//W_GET_CASH_SIZE_SEND 
void W_GET_CASH_SIZE_SEND(int tUserIndex)
{
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	int Cash = 0;
	int BonusCash = 0;

	if (!mEXTRA_COM.U_GET_CASH_SIZE_FOR_EXTRA_SEND(&mUSER[tUserIndex].uID[0], &Cash, &BonusCash))
	{
		mTRANSFER.B_GET_CASH_SIZE_RECV(0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	mTRANSFER.B_GET_CASH_SIZE_RECV(Cash, BonusCash);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_BUY_CASH_ITEM_SEND 
void W_BUY_CASH_ITEM_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tCostInfoIndex;
	int tPage;
	int tIndex;
	int tValue[6];
	CopyMemory(&tCostInfoIndex, &tPacket[1], 4);
	CopyMemory(&tPage, &tPacket[5], 4);
	CopyMemory(&tIndex, &tPacket[9], 4);
	CopyMemory(&tValue[0], &tPacket[13], 24);

	// @ Cost Info Download @
	// Å¬¶óÀÌ¾ðÆ®°¡ °¡Áö°í ÀÖ´Â Ä³½¬ ¾ÆÀÌÅÛ Á¤º¸ÀÇ ¹öÀü°ú
	// Zone ¼­¹ö°¡ °¡Áö°í ÀÖ´Â Ä³½¬ ¾ÆÀÌÅÛ Á¤º¸ÀÇ ¹öÀüÀÌ ´Ù¸£¸é ½ÇÆÐ.
	int tVersion = 0;
	CopyMemory(&tVersion, &tPacket[37], 4);

	if (tVersion != mEXTRA_COM.mCashItemInfoVersion)
	{
		mTRANSFER.B_BUY_CASH_ITEM_RECV(3, 0, 0, tPage, tIndex, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUSER[tUserIndex].mIsValidCashItemInfo = false;
		return;
	}
	if (mEXTRA_COM.mIsValidCashItemInfo == false) // COST_INFO Update Áß È¤Àº Update ¿À·ù·Î ÀÎÇÑ ÆÇ¸Å ÁßÁö.
	{
		mTRANSFER.B_BUY_CASH_ITEM_RECV(4, 0, 0, tPage, tIndex, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	} // @

	if ((tPage < 0) || (tPage > 1) || (tIndex < 0) || (tIndex > (MAX_INVENTORY_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (tPage == 1)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	// @ Cost Info Download @
	//if( !mEXTRA_COM.U_BUY_CASH_ITEM_FOR_EXTRA_SEND( &mUSER[tUserIndex].uID[0], tCostInfoIndex, tValue[0], tValue[3], &mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe, mUSER[tUserIndex].mAvatarInfo.aLevel1 ) )
	// @
	if (!mEXTRA_COM.U_BUY_CASH_ITEM_FOR_EXTRA_SEND(&mUSER[tUserIndex].uID[0], tCostInfoIndex, tValue[0], tValue[3], &mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe, mUSER[tUserIndex].mAvatarInfo.aLevel1, tVersion))
	{
		mTRANSFER.B_BUY_CASH_ITEM_RECV(2, 0, 0, tPage, tIndex, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mEXTRA_COM.mRecv_Result != 0)
	{
		// @ Cost Info Download @
		int result = 1;
		if (mEXTRA_COM.mRecv_Result == 2) // Ä³½¬ ¾ÆÀÌÅÛ ÆÇ¸Å ÁßÁö Áß.
		{
			result = 4;
		}
		else if (mEXTRA_COM.mRecv_Result == 3) // Ä³½¬ ¾ÆÀÌÅÛ Á¤º¸ ¹öÀü ¿À·ù.
		{
			// ¹öÀü ¹ÌÀÏÄ¡ÀÎ °æ¿ì º¸Åë À§¿¡¼­ °Ë»çµÈ´Ù.
			// Center ¼­¹ö¿¡¼­ º¸³» ÁÖ´Â UPDATE_CASH_ITEM_INFO ÆÐÅ¶À» ¸ø ¹Þ¾Æ¼­
			// (ÀÏ½ÃÀûÀÎ Á¢¼Ó ²÷±è µî) ÇöÀç Á¸¼­¹ö°¡ °¡Áö°í ÀÖ´Â Á¤º¸¿¡ ¿À·ù°¡
			// ÀÖÀ» ¼ö ÀÖÀ¸¹Ç·Î ´Ù½Ã ¿äÃ»ÇÑ´Ù.
			mEXTRA_COM.U_GET_CASH_ITEM_INFO_FOR_EXTRA_SEND();
			result = 3;
		}
		mTRANSFER.B_BUY_CASH_ITEM_RECV(result, 0, 0, tPage, tIndex, &tValue[0]);
		// @
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	tValue[0] = tValue[0];
	tValue[1] = tValue[1];
	tValue[2] = tValue[2];
	tValue[3] = tValue[3];
	tValue[4] = 0;
	tValue[5] = mUTIL.ReturnItemRecognitionNumber(0);
	//mGAMELOG.GL_604_BUY_CASH_ITEM(tUserIndex, tValue[0], tValue[3], tValue[4], tValue[5], mEXTRA_COM.mRecv_CostSize, mEXTRA_COM.mRecv_BonusCostSize);
	GameLogger(5, "<BUY_CASH_ITEM>(%s),(%s), (%d, %d, %d, %d),(Cost: %d, Points Left: %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tValue[0], tValue[3], tValue[4], tValue[5], mEXTRA_COM.mRecv_BonusCostSize, mEXTRA_COM.mRecv_BonusCashSize, mSERVER_INFO.mServerNumber);

	// ¼ö·® Ã¼Å©
	if ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] == tValue[0]) && (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] == tValue[1]) && (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] == tValue[2]))
	{
		ITEM_INFO* tITEM_INFO;
		tITEM_INFO = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0]);
		if ((tITEM_INFO != NULL) && (tITEM_INFO->iSort == 2) && (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] + tValue[3] <= 99))
		{
			tValue[3] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] + tValue[3];
		}
	}

	ITEM_INFO* tITEM_INFO;
	tITEM_INFO = mITEM.Search(tValue[0]);

	mGAMELOG.GL_BUY_CASH_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, tValue[3], mEXTRA_COM.mRecv_CashSize);
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue[0];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = tValue[1];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = tValue[2];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = tValue[3];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = tValue[4];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = tValue[5];
	mTRANSFER.B_BUY_CASH_ITEM_RECV(0, mEXTRA_COM.mRecv_CashSize, mEXTRA_COM.mRecv_BonusCashSize, tPage, tIndex, &tValue[0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	return;
}
//W_DUEL_ASK_SEND 
void W_DUEL_ASK_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}
	if (124 == mSERVER_INFO.mServerNumber)
		return;

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	int tSort;
	CopyMemory(&tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
	CopyMemory(&tSort, &tPacket[(1 + MAX_AVATAR_NAME_LENGTH)], 4);

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[0] != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mAVATAR_OBJECT[tUserIndex].CheckCommunityWork())
	{
		mTRANSFER.B_DUEL_ANSWER_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 11) || (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 12))
	{
		mTRANSFER.B_DUEL_ANSWER_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(tAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		mTRANSFER.B_DUEL_ANSWER_RECV(4);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mSERVER_INFO.mServerNumber != 37) && (mSERVER_INFO.mServerNumber != 119) && (mSERVER_INFO.mServerNumber != 124))
	{
		if ((mAVATAR_OBJECT[tUserIndex].mDATA.aTribe != mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aTribe) && (mAVATAR_OBJECT[tUserIndex].mDATA.aTribe != mGAME.ReturnAllianceTribe(mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aTribe)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	if ((mUSER[tOtherAvatarIndex].mMoveZoneResult == 1) || (mAVATAR_OBJECT[tOtherAvatarIndex].CheckCommunityWork()))
	{
		mTRANSFER.B_DUEL_ANSWER_RECV(5);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 11) || (mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 12))
	{
		mTRANSFER.B_DUEL_ANSWER_RECV(5);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mDuelProcessState = 1;
	strncpy(mAVATAR_OBJECT[tUserIndex].mDuelProcessAvatarName, mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH);
	mAVATAR_OBJECT[tUserIndex].mDuelProcessSort = tSort;
	mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState = 2;
	strncpy(mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH);
	mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessSort = tSort;
	mTRANSFER.B_DUEL_ASK_RECV(&mUSER[tUserIndex].mAvatarInfo.aName[0], tSort);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_DUEL_CANCEL_SEND 
void W_DUEL_CANCEL_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mDuelProcessState != 1)
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mDuelProcessState = 0;
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mDuelProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState != 2)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}
	mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState = 0;
	mTRANSFER.B_DUEL_CANCEL_RECV();
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_DUEL_ANSWER_SEND 
void W_DUEL_ANSWER_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tAnswer;
	CopyMemory(&tAnswer, &tPacket[1], 4);

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mDuelProcessState != 2)
	{
		return;
	}
	switch (tAnswer)
	{
	case 0:
		mAVATAR_OBJECT[tUserIndex].mDuelProcessState = 3;
		break;
	case 1:
		mAVATAR_OBJECT[tUserIndex].mDuelProcessState = 0;
		break;
	case 2:
		mAVATAR_OBJECT[tUserIndex].mDuelProcessState = 0;
		break;
	default:
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mDuelProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState != 1)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}
	switch (tAnswer)
	{
	case 0:
		mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState = 3;
		break;
	case 1:
		mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState = 0;
		break;
	case 2:
		mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState = 0;
		break;
	default:
		return;
	}
	mTRANSFER.B_DUEL_ANSWER_RECV(tAnswer);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_DUEL_START_SEND 
void W_DUEL_START_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tAvatarDuelUniqueNumber;
	int tOtherAvatarIndex;

	tAvatarDuelUniqueNumber = mGAME.mAvatarDuelUniqueNumber;
	mGAME.mAvatarDuelUniqueNumber++;
	if (mAVATAR_OBJECT[tUserIndex].mDuelProcessState != 3)
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[0] = 1;
	mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[1] = tAvatarDuelUniqueNumber;
	mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[2] = 1;
	if (mAVATAR_OBJECT[tUserIndex].mDuelProcessSort == 1)
	{
		mAVATAR_OBJECT[tUserIndex].mCheckPossibleEatPotion = FALSE;
	}
	else
	{
		mAVATAR_OBJECT[tUserIndex].mCheckPossibleEatPotion = TRUE;
	}
	mAVATAR_OBJECT[tUserIndex].mDuelProcessState = 4;
	mAVATAR_OBJECT[tUserIndex].mDuelProcessRemainTime = 180;
	mTRANSFER.B_DUEL_START_RECV(&mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[0], mAVATAR_OBJECT[tUserIndex].mDuelProcessRemainTime, mAVATAR_OBJECT[tUserIndex].mDuelProcessSort);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 7, mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[0], mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[1], mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[2]);
	mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mDuelProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState != 3)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}
	mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[0] = 1;
	mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[1] = tAvatarDuelUniqueNumber;
	mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[2] = 2;
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessSort == 1)
	{
		mAVATAR_OBJECT[tOtherAvatarIndex].mCheckPossibleEatPotion = FALSE;
	}
	else
	{
		mAVATAR_OBJECT[tOtherAvatarIndex].mCheckPossibleEatPotion = TRUE;
	}
	mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState = 4;
	mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessRemainTime = 180;
	mTRANSFER.B_DUEL_START_RECV(&mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[0], mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessRemainTime, mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessSort);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	mTRANSFER.B_AVATAR_CHANGE_INFO_1(tOtherAvatarIndex, mAVATAR_OBJECT[tOtherAvatarIndex].mUniqueNumber, 7, mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[0], mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[1], mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[2]);
	mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
}
//W_TRADE_ASK_SEND 
void W_TRADE_ASK_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory(&tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';

	int tOtherAvatarIndex;
	if (1 == mUSER[tUserIndex].mAuthInfo.TradeFlag) {
		mTRANSFER.B_TRADE_ANSWER_RECV(6);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mAVATAR_OBJECT[tUserIndex].CheckCommunityWork())
	{
		mTRANSFER.B_TRADE_ANSWER_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 11) || (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 12))
	{
		mTRANSFER.B_TRADE_ANSWER_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(tAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		mTRANSFER.B_TRADE_ANSWER_RECV(4);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mSERVER_INFO.mServerNumber != 37) && (mSERVER_INFO.mServerNumber != 119) && (mSERVER_INFO.mServerNumber != 124))
	{
		if ((mAVATAR_OBJECT[tUserIndex].mDATA.aTribe != mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aTribe) && (mAVATAR_OBJECT[tUserIndex].mDATA.aTribe != mGAME.ReturnAllianceTribe(mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aTribe)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	if ((mUSER[tOtherAvatarIndex].mMoveZoneResult == 1) || (mAVATAR_OBJECT[tOtherAvatarIndex].CheckCommunityWork()))
	{
		mTRANSFER.B_TRADE_ANSWER_RECV(5);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 11) || (mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 12))
	{
		mTRANSFER.B_TRADE_ANSWER_RECV(5);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (1 == mUSER[tOtherAvatarIndex].mAuthInfo.TradeFlag) {
		mTRANSFER.B_TRADE_ANSWER_RECV(7);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 1;
	strncpy(mAVATAR_OBJECT[tUserIndex].mTradeProcessAvatarName, mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH);
	mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 2;
	strncpy(mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH);

	if (mUSER[tUserIndex].mAvatarInfo.aLevel2 > 0)
	{
		mTRANSFER.B_TRADE_ASK_RECV(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2);
		mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}
	else
	{
		mTRANSFER.B_TRADE_ASK_RECV(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aLevel1);
		mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}
}
//W_TRADE_CANCEL_SEND 
void W_TRADE_CANCEL_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mTradeProcessState != 1)
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mTradeProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState != 2)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}
	mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 0;
	mTRANSFER.B_TRADE_CANCEL_RECV();
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_TRADE_ANSWER_SEND 
void W_TRADE_ANSWER_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tAnswer;
	CopyMemory(&tAnswer, &tPacket[1], 4);

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mTradeProcessState != 2)
	{
		return;
	}
	switch (tAnswer)
	{
	case 0:
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 3;
		break;
	case 1:
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		break;
	case 2:
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		break;
	default:
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mTradeProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState != 1)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}
	switch (tAnswer)
	{
	case 0:
		mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 3;
		break;
	case 1:
		mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 0;
		break;
	case 2:
		mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 0;
		break;
	default:
		return;
	}

	if (1 == mUSER[tUserIndex].mAuthInfo.TradeFlag) {
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 0;
		mTRANSFER.B_TRADE_ANSWER_RECV(6);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_TRADE_ANSWER_RECV(7);
		mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}
	else if (1 == mUSER[tOtherAvatarIndex].mAuthInfo.TradeFlag) {
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 0;
		mTRANSFER.B_TRADE_ANSWER_RECV(7);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_TRADE_ANSWER_RECV(6);
		mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}
	else {
		mTRANSFER.B_TRADE_ANSWER_RECV(tAnswer);
		mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}
}
//W_TRADE_START_SEND
void W_TRADE_START_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mTradeProcessState != 3)
	{
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mTradeProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState != 3)
	{
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		return;
	}
	if (1 == mUSER[tUserIndex].mAuthInfo.TradeFlag) {
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		mTRANSFER.B_TRADE_ANSWER_RECV(6);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_TRADE_ANSWER_RECV(7);
		mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else if (1 == mUSER[tOtherAvatarIndex].mAuthInfo.TradeFlag) {
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		mTRANSFER.B_TRADE_ANSWER_RECV(7);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_TRADE_ANSWER_RECV(6);
		mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 4;
	mAVATAR_OBJECT[tUserIndex].mTradeProcessMenu = 0;
	mTRANSFER.B_TRADE_START_RECV(mUSER[tOtherAvatarIndex].mAvatarInfo.aTradeMoney, mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade, mUSER[tOtherAvatarIndex].mAvatarInfo.TradeSocket, mUSER[tOtherAvatarIndex].mAvatarInfo.TradeBar);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 4;
	mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessMenu = 0;
	mTRANSFER.B_TRADE_START_RECV(mUSER[tUserIndex].mAvatarInfo.aTradeMoney, mUSER[tUserIndex].mAvatarInfo.aTrade, mUSER[tUserIndex].mAvatarInfo.TradeSocket, mUSER[tUserIndex].mAvatarInfo.TradeBar);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_TRADE_MENU_SEND 
void W_TRADE_MENU_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int index01;
	int tOtherAvatarIndex;
	int tTradeMoney;
	int tTradeBar;
	int tTrade[MAX_TRADE_SLOT_NUM][4];
	int tTradeSocket[MAX_TRADE_SLOT_NUM][3];
	ITEM_INFO* ItemInfo;
	int gonderentic[8];
	int alantic[8];

	if (mAVATAR_OBJECT[tUserIndex].mTradeProcessState != 4)
	{
		return;
	}

	switch (mAVATAR_OBJECT[tUserIndex].mTradeProcessMenu)
	{
	case 0:
		tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mTradeProcessAvatarName, tUserIndex);
		if (tOtherAvatarIndex == -1)
		{
			return;
		}
		if (mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState != 4)
		{
			return;
		}
		if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
		{
			return;
		}
		if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
		{
			return;
		}
		if (mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessMenu == 2)
		{
			return;
		}
		if (1 == mUSER[tUserIndex].mAuthInfo.TradeFlag) {
			return;
		}
		else if (1 == mUSER[tOtherAvatarIndex].mAuthInfo.TradeFlag) {
			return;
		}
		mAVATAR_OBJECT[tUserIndex].mTradeProcessMenu = 1;
		mTRANSFER.B_TRADE_MENU_RECV(0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_TRADE_MENU_RECV(1);
		mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1:
		tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mTradeProcessAvatarName, tUserIndex);
		if (tOtherAvatarIndex == -1)
		{
			return;
		}
		if (mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState != 4)
		{
			return;
		}
		if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
		{
			return;
		}
		if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
		{
			return;
		}
		if (mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessMenu == 0)
		{
			return;
		}
		if (1 == mUSER[tUserIndex].mAuthInfo.TradeFlag) {
			return;
		}
		else if (1 == mUSER[tOtherAvatarIndex].mAuthInfo.TradeFlag) {
			return;
		}

		mAVATAR_OBJECT[tUserIndex].mTradeProcessMenu = 2;
		mTRANSFER.B_TRADE_MENU_RECV(0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_TRADE_MENU_RECV(1);
		mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		if (mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessMenu != 2)
		{
			return;
		}
		tTradeMoney = mUSER[tUserIndex].mAvatarInfo.aTradeMoney;
		tTradeBar = mUSER[tUserIndex].mAvatarInfo.TradeBar;
		for (index01 = 0; index01 < MAX_TRADE_SLOT_NUM; index01++)
		{
			
			tTrade[index01][0] = mUSER[tUserIndex].mAvatarInfo.aTrade[index01][0];
			tTrade[index01][1] = mUSER[tUserIndex].mAvatarInfo.aTrade[index01][1];
			tTrade[index01][2] = mUSER[tUserIndex].mAvatarInfo.aTrade[index01][2];
			tTrade[index01][3] = mUSER[tUserIndex].mAvatarInfo.aTrade[index01][3];
			tTradeSocket[index01][0] = mUSER[tUserIndex].mAvatarInfo.TradeSocket[index01][0];
			tTradeSocket[index01][1] = mUSER[tUserIndex].mAvatarInfo.TradeSocket[index01][1];
			tTradeSocket[index01][2] = mUSER[tUserIndex].mAvatarInfo.TradeSocket[index01][2];
		}
		if (mUSER[tOtherAvatarIndex].mAvatarInfo.aTradeMoney > 0 || mUSER[tOtherAvatarIndex].mAvatarInfo.TradeBar > 0)
		{
			mGAMELOG.GL_616_TRADE_MONEY(tOtherAvatarIndex, tUserIndex, mUSER[tOtherAvatarIndex].mAvatarInfo.aTradeMoney, mUSER[tOtherAvatarIndex].mAvatarInfo.TradeBar);
		}
		mUSER[tUserIndex].mAvatarInfo.aTradeMoney = mUSER[tOtherAvatarIndex].mAvatarInfo.aTradeMoney;
		mUSER[tUserIndex].mAvatarInfo.TradeBar = mUSER[tOtherAvatarIndex].mAvatarInfo.TradeBar;
		for (index01 = 0; index01 < MAX_TRADE_SLOT_NUM; index01++)
		{
			if (mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][0] > 0)
			{
				ItemInfo = mITEM.Search(mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][0]);		
				mGAMELOG.GL_615_TRADE_ITEM(tOtherAvatarIndex, tUserIndex, ItemInfo->iIndex, ItemInfo->iName, mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][2], mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][1], mUSER[tOtherAvatarIndex].mAvatarInfo.TradeSocket[index01][0], mUSER[tOtherAvatarIndex].mAvatarInfo.TradeSocket[index01][1], mUSER[tOtherAvatarIndex].mAvatarInfo.TradeSocket[index01][2]);
			}
			mUSER[tUserIndex].mAvatarInfo.aTrade[index01][0] = mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][0];
			mUSER[tUserIndex].mAvatarInfo.aTrade[index01][1] = mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][1];
			mUSER[tUserIndex].mAvatarInfo.aTrade[index01][2] = mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][2];
			mUSER[tUserIndex].mAvatarInfo.aTrade[index01][3] = mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][3];
			mUSER[tUserIndex].mAvatarInfo.TradeSocket[index01][0] = mUSER[tOtherAvatarIndex].mAvatarInfo.TradeSocket[index01][0];
			mUSER[tUserIndex].mAvatarInfo.TradeSocket[index01][1] = mUSER[tOtherAvatarIndex].mAvatarInfo.TradeSocket[index01][1];
			mUSER[tUserIndex].mAvatarInfo.TradeSocket[index01][2] = mUSER[tOtherAvatarIndex].mAvatarInfo.TradeSocket[index01][2];
		}
		if (tTradeMoney > 0 || tTradeBar > 0)
		{
			mGAMELOG.GL_616_TRADE_MONEY(tUserIndex, tOtherAvatarIndex, tTradeMoney, tTradeBar);
		}
		mUSER[tOtherAvatarIndex].mAvatarInfo.aTradeMoney = tTradeMoney;
		mUSER[tOtherAvatarIndex].mAvatarInfo.TradeBar = tTradeBar;
		for (index01 = 0; index01 < MAX_TRADE_SLOT_NUM; index01++)
		{
			if (tTrade[index01][0] > 0)
			{
				ItemInfo = mITEM.Search(tTrade[index01][0]);
				mGAMELOG.GL_615_TRADE_ITEM(tUserIndex, tOtherAvatarIndex, ItemInfo->iIndex, ItemInfo->iName, tTrade[index01][2], tTrade[index01][1], tTradeSocket[index01][0], tTradeSocket[index01][1], tTradeSocket[index01][2]);
			}
			mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][0] = tTrade[index01][0];
			mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][1] = tTrade[index01][1];
			mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][2] = tTrade[index01][2];
			mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][3] = tTrade[index01][3];
			mUSER[tOtherAvatarIndex].mAvatarInfo.TradeSocket[index01][0] = tTradeSocket[index01][0];
			mUSER[tOtherAvatarIndex].mAvatarInfo.TradeSocket[index01][1] = tTradeSocket[index01][1];
			mUSER[tOtherAvatarIndex].mAvatarInfo.TradeSocket[index01][2] = tTradeSocket[index01][2];
		}
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;

		mTRANSFER.B_TRADE_END_RECV(0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		mPLAYUSER_COM.U_DUPEFIX(mUSER[tUserIndex].mPlayUserIndex, &mUSER[tUserIndex].uID[0], &mUSER[tUserIndex].mAvatarInfo, &mUSER[tUserIndex].mAuthInfo);
		mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 0;
		mTRANSFER.B_TRADE_END_RECV(0);
		mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mPLAYUSER_COM.U_DUPEFIX(mUSER[tOtherAvatarIndex].mPlayUserIndex, &mUSER[tOtherAvatarIndex].uID[0], &mUSER[tOtherAvatarIndex].mAvatarInfo, &mUSER[tOtherAvatarIndex].mAuthInfo);
		return;
	}
}
//W_TRADE_END_SEND
void W_TRADE_END_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mTradeProcessState != 4)
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
	mTRANSFER.B_TRADE_END_RECV(1);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mTradeProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState != 4)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}
	mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 0;
	mTRANSFER.B_TRADE_END_RECV(1);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_FRIEND_ASK_SEND
void W_FRIEND_ASK_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}
	if (124 == mSERVER_INFO.mServerNumber)
		return;

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory(&tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';

	int index01;
	int tOtherAvatarIndex;

	for (index01 = 0; index01 < MAX_FRIEND_NUM; index01++)
	{
		if (strcmp(mUSER[tUserIndex].mAvatarInfo.aFriend[index01], "") == 0)
		{
			break;
		}
	}
	if (index01 == MAX_FRIEND_NUM)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	for (index01 = 0; index01 < MAX_FRIEND_NUM; index01++)
	{
		if (strcmp(mUSER[tUserIndex].mAvatarInfo.aFriend[index01], tAvatarName) == 0)
		{
			break;
		}
	}
	if (index01 < MAX_FRIEND_NUM)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mAVATAR_OBJECT[tUserIndex].CheckCommunityWork())
	{
		mTRANSFER.B_FRIEND_ANSWER_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 11) || (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 12))
	{
		mTRANSFER.B_FRIEND_ANSWER_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(tAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		mTRANSFER.B_FRIEND_ANSWER_RECV(4);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mAVATAR_OBJECT[tUserIndex].mDATA.aTribe != mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aTribe)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((mUSER[tOtherAvatarIndex].mMoveZoneResult == 1) || (mAVATAR_OBJECT[tOtherAvatarIndex].CheckCommunityWork()))
	{
		mTRANSFER.B_FRIEND_ANSWER_RECV(5);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 11) || (mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 12))
	{
		mTRANSFER.B_FRIEND_ANSWER_RECV(5);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 1;
	strncpy(mAVATAR_OBJECT[tUserIndex].mFriendProcessAvatarName, mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH);
	mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessState = 2;
	strncpy(mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH);
	mTRANSFER.B_FRIEND_ASK_RECV(&mUSER[tUserIndex].mAvatarInfo.aName[0]);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_FRIEND_CANCEL_SEND
void W_FRIEND_CANCEL_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mFriendProcessState != 1)
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 0;
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mFriendProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessState != 2)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}
	mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessState = 0;
	mTRANSFER.B_FRIEND_CANCEL_RECV();
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_FRIEND_ANSWER_SEND
void W_FRIEND_ANSWER_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tAnswer;
	CopyMemory(&tAnswer, &tPacket[1], 4);

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mFriendProcessState != 2)
	{
		return;
	}
	switch (tAnswer)
	{
	case 0:
		mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 3;
		break;
	case 1:
		mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 0;
		break;
	case 2:
		mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 0;
		break;
	default:
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mFriendProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessState != 1)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}
	switch (tAnswer)
	{
	case 0:
		mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessState = 3;
		break;
	case 1:
		mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessState = 0;
		break;
	case 2:
		mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessState = 0;
		break;
	default:
		return;
	}
	mTRANSFER.B_FRIEND_ANSWER_RECV(tAnswer);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_FRIEND_MAKE_SEND
void W_FRIEND_MAKE_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tIndex;
	CopyMemory(&tIndex, &tPacket[1], 4);
	if ((tIndex < 0) || (tIndex > (MAX_FRIEND_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tOtherAvatarIndex;

	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aFriend[tIndex], "") != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mAVATAR_OBJECT[tUserIndex].mFriendProcessState != 3)
	{
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mFriendProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 0;
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessState != 3)
	{
		mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 0;
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 0;
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 0;
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 0;
	strncpy(mUSER[tUserIndex].mAvatarInfo.aFriend[tIndex], mUSER[tOtherAvatarIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH);
	mTRANSFER.B_FRIEND_MAKE_RECV(tIndex, &mUSER[tOtherAvatarIndex].mAvatarInfo.aName[0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessState = 0;
}
//W_FRIEND_FIND_SEND
void W_FRIEND_FIND_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tIndex;
	CopyMemory(&tIndex, &tPacket[1], 4);
	if ((tIndex < 0) || (tIndex > (MAX_FRIEND_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aFriend[tIndex], "") == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mPLAYUSER_COM.U_FIND_AVATAR_FOR_ZONE_SEND(&mUSER[tUserIndex].mAvatarInfo.aFriend[tIndex][0]);
	if (mUSER[tUserIndex].mAvatarInfo.aTribe != mPLAYUSER_COM.mRecv_Tribe)
	{
		mTRANSFER.B_FRIEND_FIND_RECV(tIndex, -1);
	}
	else
	{
		mTRANSFER.B_FRIEND_FIND_RECV(tIndex, mPLAYUSER_COM.mRecv_ZoneNumber);
	}
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_FRIEND_DELETE_SEND
void W_FRIEND_DELETE_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tIndex;
	CopyMemory(&tIndex, &tPacket[1], 4);
	if ((tIndex < 0) || (tIndex > (MAX_FRIEND_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aFriend[tIndex], "") == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	strcpy(mUSER[tUserIndex].mAvatarInfo.aFriend[tIndex], "");
	mTRANSFER.B_FRIEND_DELETE_RECV(tIndex);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_TEACHER_ASK_SEND
void W_TEACHER_ASK_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory(&tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';

	int tOtherAvatarIndex;

	if ((mUSER[tUserIndex].mAvatarInfo.aLevel1 < 113) || (strcmp(mUSER[tUserIndex].mAvatarInfo.aTeacher, "") != 0) || (strcmp(mUSER[tUserIndex].mAvatarInfo.aStudent, "") != 0))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mAVATAR_OBJECT[tUserIndex].CheckCommunityWork())
	{
		mTRANSFER.B_TEACHER_ANSWER_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 11) || (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 12))
	{
		mTRANSFER.B_TEACHER_ANSWER_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(tAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		mTRANSFER.B_TEACHER_ANSWER_RECV(4);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mAVATAR_OBJECT[tUserIndex].mDATA.aTribe != mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aTribe) || (mUSER[tOtherAvatarIndex].mAvatarInfo.aLevel1 > 112))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((mUSER[tOtherAvatarIndex].mMoveZoneResult == 1) || (mAVATAR_OBJECT[tOtherAvatarIndex].CheckCommunityWork()))
	{
		mTRANSFER.B_TEACHER_ANSWER_RECV(5);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 11) || (mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 12))
	{
		mTRANSFER.B_TEACHER_ANSWER_RECV(5);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (strcmp(mUSER[tOtherAvatarIndex].mAvatarInfo.aTeacher, "") != 0)
	{
		mTRANSFER.B_TEACHER_ANSWER_RECV(6);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (strcmp(mUSER[tOtherAvatarIndex].mAvatarInfo.aStudent, "") != 0)
	{
		mTRANSFER.B_TEACHER_ANSWER_RECV(7);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 1;
	strncpy(mAVATAR_OBJECT[tUserIndex].mTeacherProcessAvatarName, mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH);
	mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessState = 2;
	strncpy(mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH);
	mTRANSFER.B_TEACHER_ASK_RECV(&mUSER[tUserIndex].mAvatarInfo.aName[0]);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_TEACHER_CANCEL_SEND
void W_TEACHER_CANCEL_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mTeacherProcessState != 1)
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 0;
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mTeacherProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessState != 2)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}
	mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessState = 0;
	mTRANSFER.B_TEACHER_CANCEL_RECV();
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_TEACHER_ANSWER_SEND
void W_TEACHER_ANSWER_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tAnswer;
	CopyMemory(&tAnswer, &tPacket[1], 4);

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mTeacherProcessState != 2)
	{
		return;
	}
	switch (tAnswer)
	{
	case 0:
		mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 3;
		break;
	case 1:
		mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 0;
		break;
	case 2:
		mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 0;
		break;
	default:
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mTeacherProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessState != 1)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}
	switch (tAnswer)
	{
	case 0:
		mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessState = 3;
		break;
	case 1:
		mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessState = 0;
		break;
	case 2:
		mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessState = 0;
		break;
	default:
		return;
	}
	mTRANSFER.B_TEACHER_ANSWER_RECV(tAnswer);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_TEACHER_START_SEND
void W_TEACHER_START_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mTeacherProcessState != 3)
	{
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mTeacherProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 0;
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessState != 3)
	{
		mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 0;
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 0;
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 0;
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 0;
	strncpy(mUSER[tUserIndex].mAvatarInfo.aStudent, mUSER[tOtherAvatarIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH);
	mTRANSFER.B_TEACHER_START_RECV(1, &mUSER[tOtherAvatarIndex].mAvatarInfo.aName[0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessState = 0;
	strncpy(mUSER[tOtherAvatarIndex].mAvatarInfo.aTeacher, mUSER[tUserIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH);
	mTRANSFER.B_TEACHER_START_RECV(2, &mUSER[tUserIndex].mAvatarInfo.aName[0]);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_TEACHER_END_SEND
void W_TEACHER_END_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	if ((strcmp(mUSER[tUserIndex].mAvatarInfo.aTeacher, "") == 0) && (strcmp(mUSER[tUserIndex].mAvatarInfo.aStudent, "") == 0))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	strcpy(mUSER[tUserIndex].mAvatarInfo.aTeacher, "");
	strcpy(mUSER[tUserIndex].mAvatarInfo.aStudent, "");
	mTRANSFER.B_TEACHER_END_RECV();
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_TEACHER_STATE_SEND
void W_TEACHER_STATE_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tOtherAvatarIndex;

	if ((strcmp(mUSER[tUserIndex].mAvatarInfo.aTeacher, "") == 0) && (strcmp(mUSER[tUserIndex].mAvatarInfo.aStudent, "") == 0))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aTeacher, "") != 0)
	{
		tOtherAvatarIndex = mUTIL.SearchAvatar(mUSER[tUserIndex].mAvatarInfo.aTeacher, tUserIndex);
		if (tOtherAvatarIndex == -1)
		{
			return;
		}
		if (strcmp(mUSER[tOtherAvatarIndex].mAvatarInfo.aStudent, mUSER[tUserIndex].mAvatarInfo.aName) == 0)
		{
			mTRANSFER.B_TEACHER_STATE_RECV(0);
		}
		else
		{
			mTRANSFER.B_TEACHER_STATE_RECV(1);
		}
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aStudent, "") != 0)
	{
		tOtherAvatarIndex = mUTIL.SearchAvatar(mUSER[tUserIndex].mAvatarInfo.aStudent, tUserIndex);
		if (tOtherAvatarIndex == -1)
		{
			return;
		}
		if (strcmp(mUSER[tOtherAvatarIndex].mAvatarInfo.aTeacher, mUSER[tUserIndex].mAvatarInfo.aName) == 0)
		{
			mTRANSFER.B_TEACHER_STATE_RECV(0);
		}
		else
		{
			mTRANSFER.B_TEACHER_STATE_RECV(1);
		}
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
}
//W_PARTY_ASK_SEND
void W_PARTY_ASK_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}
	if (124 == mSERVER_INFO.mServerNumber)
		return;

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory(&tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].CheckCommunityWork())
	{
		mTRANSFER.B_PARTY_ANSWER_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 11) || (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 12))
	{
		mTRANSFER.B_PARTY_ANSWER_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(tAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		mTRANSFER.B_PARTY_ANSWER_RECV(4);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	if ((mAVATAR_OBJECT[tUserIndex].mDATA.aTribe != mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aTribe) && (mAVATAR_OBJECT[tUserIndex].mDATA.aTribe != mGAME.ReturnAllianceTribe(mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aTribe)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (abs((mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2) - (mUSER[tOtherAvatarIndex].mAvatarInfo.aLevel1 + mUSER[tOtherAvatarIndex].mAvatarInfo.aLevel2)) > 9)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((mUSER[tOtherAvatarIndex].mMoveZoneResult == 1) || (mAVATAR_OBJECT[tOtherAvatarIndex].CheckCommunityWork()))
	{
		mTRANSFER.B_PARTY_ANSWER_RECV(5);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 11) || (mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 12))
	{
		mTRANSFER.B_PARTY_ANSWER_RECV(5);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mPartyProcessState = 1;
	strncpy(mAVATAR_OBJECT[tUserIndex].mPartyProcessAvatarName, mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH);
	mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState = 2;
	strncpy(mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH);
	mTRANSFER.B_PARTY_ASK_RECV(&mUSER[tUserIndex].mAvatarInfo.aName[0]);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

}
//W_PARTY_CANCEL_SEND
void W_PARTY_CANCEL_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mPartyProcessState != 1)
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mPartyProcessState = 0;
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mPartyProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState != 2)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}
	mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState = 0;
	mTRANSFER.B_PARTY_CANCEL_RECV();
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_PARTY_ANSWER_SEND
void W_PARTY_ANSWER_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tAnswer;
	CopyMemory(&tAnswer, &tPacket[1], 4);

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mPartyProcessState != 2)
	{
		return;
	}
	switch (tAnswer)
	{
	case 0:
		mAVATAR_OBJECT[tUserIndex].mPartyProcessState = 3;
		break;
	case 1:
		mAVATAR_OBJECT[tUserIndex].mPartyProcessState = 0;
		break;
	case 2:
		mAVATAR_OBJECT[tUserIndex].mPartyProcessState = 0;
		break;
	default:
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mPartyProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState != 1)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}
	switch (tAnswer)
	{
	case 0:
		mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState = 3;
		break;
	case 1:
		mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState = 0;
		break;
	case 2:
		mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState = 0;
		break;
	default:
		return;
	}

	mTRANSFER.B_PARTY_ANSWER_RECV(tAnswer);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];
	CopyMemory(&tData[0], &mUSER[tOtherAvatarIndex].mAvatarInfo.aPartyName[0], MAX_PARTY_NAME_LENGTH);


	if (tAnswer == 0)
	{
		strncpy(mUSER[tOtherAvatarIndex].mAvatarInfo.aPartyName[0], mUSER[tOtherAvatarIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH);


		if (strcmp(mUSER[tOtherAvatarIndex].mAvatarInfo.aPartyName[1], "") == 0) 
		{
			
			for (int i = 1; i < 5; i++)
			{
				if (strcmp(mUSER[tOtherAvatarIndex].mAvatarInfo.aPartyName[i], "") != 0)
				{
					continue;
				}
				else
				{
					strncpy(mUSER[tOtherAvatarIndex].mAvatarInfo.aPartyName[i], mUSER[tUserIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH);
					strncpy(mAVATAR_OBJECT[tUserIndex].mDATA.aPartyName, mUSER[tOtherAvatarIndex].mAvatarInfo.aPartyName[0], MAX_AVATAR_NAME_LENGTH);
					strncpy(mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aPartyName, mUSER[tOtherAvatarIndex].mAvatarInfo.aPartyName[0], MAX_AVATAR_NAME_LENGTH);
					break;
				}
			}

			

			CopyMemory(mUSER[tUserIndex].mAvatarInfo.aPartyName, mUSER[tOtherAvatarIndex].mAvatarInfo.aPartyName, 65);
			mAVATAR_OBJECT[tUserIndex].mPartyProcessState = 0;
			mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState = 0;
			mTRANSFER.B_PARTY_MAKE_RECV(1, mUSER[tOtherAvatarIndex].mAvatarInfo.aPartyName);
			mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			mTRANSFER.B_PARTY_MAKE_RECV(2, mUSER[tOtherAvatarIndex].mAvatarInfo.aPartyName);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			return;
		}
		else
		{
			
			for (int i = 2; i < 5; i++)
			{
				if (strcmp(mUSER[tOtherAvatarIndex].mAvatarInfo.aPartyName[i], "") != 0)
				{
					continue;
				}
				else
				{
					strncpy(mUSER[tOtherAvatarIndex].mAvatarInfo.aPartyName[i], mUSER[tUserIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH);
					strncpy(mAVATAR_OBJECT[tUserIndex].mDATA.aPartyName, mUSER[tOtherAvatarIndex].mAvatarInfo.aPartyName[0], MAX_AVATAR_NAME_LENGTH);
					break;
				}
			}

			
			tSort = 104;
			CopyMemory(&tData[0], &mUSER[tOtherAvatarIndex].mAvatarInfo.aPartyName[0], MAX_PARTY_NAME_LENGTH);
			CopyMemory(&tData[MAX_PARTY_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
			mRELAY_COM.U_DEMAND_BROADCAST_DATA(tSort, &tData[0]);

			
			/*for (int i = 0; i < 5; i++)
			{
				if (strcmp(mUSER[tOtherAvatarIndex].mAvatarInfo.aPartyName[i], "") != 0)
				{
					strncpy(mUSER[tUserIndex].mAvatarInfo.aPartyName[i], mUSER[tOtherAvatarIndex].mAvatarInfo.aPartyName[i], MAX_AVATAR_NAME_LENGTH);
				}
				else
				{
					strncpy(mUSER[tUserIndex].mAvatarInfo.aPartyName[i], mUSER[tUserIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH);
					break;
				}
			}*/

			strncpy(mAVATAR_OBJECT[tUserIndex].mDATA.aPartyName, mUSER[tOtherAvatarIndex].mAvatarInfo.aPartyName[0], MAX_AVATAR_NAME_LENGTH);
			mAVATAR_OBJECT[tUserIndex].mPartyProcessState = 0;
			
			mTRANSFER.B_PARTY_MAKE_RECV(2, mUSER[tUserIndex].mAvatarInfo.aPartyName);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState = 0;
		}
	}
	return;
}
//W_PARTY_MAKE
void W_PARTY_MAKE_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	if (mAVATAR_OBJECT[tUserIndex].mPartyProcessState != 3)
	{
		return;
	}

	strncpy(mAVATAR_OBJECT[tUserIndex].mDATA.aPartyName, mUSER[tUserIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH);
	//mTRANSFER.B_PARTY_MAKE_RECV();
	//mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	return;
}
//W_PARTY_JOIN_SEND
void W_PARTY_JOIN_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];
	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mPartyProcessState != 3)
	{
		return;
	}
	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aPartyName[0], "") == 0)
	{
		return;
	}
	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aPartyName[0], mUSER[tUserIndex].mAvatarInfo.aName) != 0)
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mPartyProcessState = 0;
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mPartyProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState != 3)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}

	mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState = 0;
	tSort = 104;
	CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aPartyName[0], MAX_PARTY_NAME_LENGTH);
	CopyMemory(&tData[MAX_PARTY_NAME_LENGTH], &mUSER[tOtherAvatarIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
	mRELAY_COM.U_DEMAND_BROADCAST_DATA(tSort, &tData[0]);
}
//W_PARTY_CHAT_SEND
void W_PARTY_CHAT_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	//unsigned int tRandom = 0;
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	char tContent[MAX_CHAT_CONTENT_LENGTH];
	CopyMemory(&tContent[0], &tPacket[1], MAX_CHAT_CONTENT_LENGTH);
	tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
	if (strcmp(tContent, "") == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aPartyName[0], "") == 0)
	{
		return;
	}
	tSort = 105;
	CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aPartyName[0], MAX_PARTY_NAME_LENGTH);
	CopyMemory(&tData[MAX_PARTY_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
	CopyMemory(&tData[(MAX_PARTY_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
	mRELAY_COM.U_DEMAND_BROADCAST_DATA(tSort, &tData[0]);
	GameLogger(2, "<PARTY_CHAT>(%s),(%s), (Message: %s),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tContent, mSERVER_INFO.mServerNumber);
	//char type[50];
	//snprintf(type, 50, "W_PARTY_CHAT_SEND");
	//mGAMELOG.CHAT_LOG_SEND(tUserIndex, NULL, &tContent[0], type);
}
//W_PARTY_LEAVE_SEND
void W_PARTY_LEAVE_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aPartyName[0], "") == 0)
	{
		return;
	}

	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aPartyName[0], mUSER[tUserIndex].mAvatarInfo.aName) == 0)
	{
		return;
	}

	mAVATAR_OBJECT[tUserIndex].mPartyProcessState = 0;

	tSort = 106;
	CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aPartyName[0], MAX_PARTY_NAME_LENGTH);
	CopyMemory(&tData[MAX_PARTY_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
	mRELAY_COM.U_DEMAND_BROADCAST_DATA(tSort, &tData[0]);
}
//W_PARTY_EXILE_SEND
void W_PARTY_EXILE_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory(&tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aPartyName[0], "") == 0)
	{
		return;
	}

	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aPartyName[0], mUSER[tUserIndex].mAvatarInfo.aName) != 0)
	{
		return;
	}

	int tOtherAvatarIndex;
	tOtherAvatarIndex = mUTIL.SearchAvatar(tAvatarName, tUserIndex);
	mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState = 0;

	tSort = 107;
	CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aPartyName[0], MAX_PARTY_NAME_LENGTH);
	CopyMemory(&tData[MAX_PARTY_NAME_LENGTH], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	mRELAY_COM.U_DEMAND_BROADCAST_DATA(tSort, &tData[0]);
}
//W_PARTY_INFO_SEND
void W_PARTY_INFO_SEND(int tUserIndex)
{
}
//W_PARTY_BREAK_SEND
void W_PARTY_BREAK_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	mAVATAR_OBJECT[tUserIndex].mPartyProcessState = 0;

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory(&tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aPartyName[0], "") == 0)
	{
		return;
	}

	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aPartyName[0], mUSER[tUserIndex].mAvatarInfo.aName) != 0)
	{
		return;
	}

	tSort = 109;
	CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aPartyName[0], MAX_PARTY_NAME_LENGTH);
	CopyMemory(&tData[MAX_PARTY_NAME_LENGTH], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	mRELAY_COM.U_DEMAND_BROADCAST_DATA(tSort, &tData[0]);
}
//W_GUILD_ASK_SEND
void W_GUILD_ASK_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}
	if (124 == mSERVER_INFO.mServerNumber)
		return;

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory(&tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';

	int tOtherAvatarIndex;

	if ((strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0) || ((mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0) && (mUSER[tUserIndex].mAvatarInfo.aGuildRole != 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mAVATAR_OBJECT[tUserIndex].CheckCommunityWork())
	{
		mTRANSFER.B_GUILD_ANSWER_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 11) || (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 12))
	{
		mTRANSFER.B_GUILD_ANSWER_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(tAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		mTRANSFER.B_GUILD_ANSWER_RECV(4);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (strcmp(mUSER[tOtherAvatarIndex].mAvatarInfo.aGuildName, "") != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mAVATAR_OBJECT[tUserIndex].mDATA.aTribe != mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aTribe)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((mUSER[tOtherAvatarIndex].mMoveZoneResult == 1) || (mAVATAR_OBJECT[tOtherAvatarIndex].CheckCommunityWork()))
	{
		mTRANSFER.B_GUILD_ANSWER_RECV(5);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 11) || (mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 12))
	{
		mTRANSFER.B_GUILD_ANSWER_RECV(5);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mGuildProcessState = 1;
	strncpy(mAVATAR_OBJECT[tUserIndex].mGuildProcessAvatarName, mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH);
	mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessState = 2;
	strncpy(mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH);
	mTRANSFER.B_GUILD_ASK_RECV(&mUSER[tUserIndex].mAvatarInfo.aName[0]);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_GUILD_CANCEL_SEND
void W_GUILD_CANCEL_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mGuildProcessState != 1)
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mGuildProcessState = 0;
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mGuildProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessState != 2)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}
	mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessState = 0;
	mTRANSFER.B_GUILD_CANCEL_RECV();
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_GUILD_ANSWER_SEND
void W_GUILD_ANSWER_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tAnswer;
	CopyMemory(&tAnswer, &tPacket[1], 4);

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mGuildProcessState != 2)
	{
		return;
	}
	switch (tAnswer)
	{
	case 0:
		mAVATAR_OBJECT[tUserIndex].mGuildProcessState = 3;
		break;
	case 1:
		mAVATAR_OBJECT[tUserIndex].mGuildProcessState = 0;
		break;
	case 2:
		mAVATAR_OBJECT[tUserIndex].mGuildProcessState = 0;
		break;
	default:
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mGuildProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessState != 1)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}
	switch (tAnswer)
	{
	case 0:
		mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessState = 3;
		break;
	case 1:
		mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessState = 0;
		break;
	case 2:
		mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessState = 0;
		break;
	default:
		return;
	}
	mTRANSFER.B_GUILD_ANSWER_RECV(tAnswer);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_GUILD_WORK_SEND
void W_GUILD_WORK_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	BYTE tData[MAX_GUILD_WORK_SIZE];
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tData[0], &tPacket[5], MAX_GUILD_WORK_SIZE);

	int index01;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	int tOtherAvatarIndex;
	char tGuildName[MAX_GUILD_NAME_LENGTH];
	char tGuildNotice[4][MAX_GUILD_NOTICE_LENGTH];
	int tTotalMemberNum;
	int tCost;
	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	int tGuildRole;
	char tCallName[MAX_CALL_NAME_LENGTH];

	if (124 == mSERVER_INFO.mServerNumber) {
		switch (tSort) {
		case 2:
		case 5:
		case 9:
			break;
		default:
			return;
		}
	}

	switch (tSort)
	{
	case  1: //[Ã¢¼³]
		CopyMemory(&tGuildName[0], &tData[0], MAX_GUILD_NAME_LENGTH);
		tGuildName[(MAX_GUILD_NAME_LENGTH - 1)] = '\0';
		if ((strcmp(tGuildName, "") == 0) || (!mUTIL.CheckNameString(tGuildName)) || (strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") != 0))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 30)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aMoney < 10000000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory(&tData[0], &tGuildName[0], MAX_GUILD_NAME_LENGTH);
		CopyMemory(&tData[MAX_GUILD_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
		if (!mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND(tSort, &tData[0]))
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mEXTRA_COM.mRecv_Result != 0)
		{
			mTRANSFER.B_GUILD_WORK_RECV(mEXTRA_COM.mRecv_Result, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		strncpy(mEXTRA_COM.mRecv_GuildInfo.gName, tGuildName, MAX_GUILD_NAME_LENGTH);
		mTRANSFER.B_GUILD_WORK_RECV(0, tSort, &mEXTRA_COM.mRecv_GuildInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 101;
		CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&tBroadcastInfoData[MAX_AVATAR_NAME_LENGTH], &tGuildName[0], MAX_GUILD_NAME_LENGTH);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		//mGAMELOG.GL_617_GUILD_MONEY(tUserIndex, 10000000, 1, mEXTRA_COM.mRecv_GuildInfo.gGrade);
		mUSER[tUserIndex].mAvatarInfo.aMoney -= 10000000;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(19, mUSER[tUserIndex].mAvatarInfo.aMoney);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		strncpy(mUSER[tUserIndex].mAvatarInfo.aGuildName, tGuildName, MAX_GUILD_NAME_LENGTH);
		mUSER[tUserIndex].mAvatarInfo.aGuildRole = 0;
		strcpy(mUSER[tUserIndex].mAvatarInfo.aCallName, "");
		strncpy(mAVATAR_OBJECT[tUserIndex].mDATA.aGuildName, tGuildName, MAX_GUILD_NAME_LENGTH);
		mAVATAR_OBJECT[tUserIndex].mDATA.aGuildRole = 0;
		strcpy(mAVATAR_OBJECT[tUserIndex].mDATA.aCallName, "");
		return;
	case  2: //Aile Kurma
		if (strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;

		}
		CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		if (!mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND(tSort, &tData[0]))
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mEXTRA_COM.mRecv_Result != 0)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_GUILD_WORK_RECV(0, tSort, &mEXTRA_COM.mRecv_GuildInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case  3: //[°¡ÀÔ]
		if ((strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0) || ((mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0) && (mUSER[tUserIndex].mAvatarInfo.aGuildRole != 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mAVATAR_OBJECT[tUserIndex].mGuildProcessState != 3)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mAVATAR_OBJECT[tUserIndex].mGuildProcessState = 0;
		tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mGuildProcessAvatarName, tUserIndex);
		if (tOtherAvatarIndex == -1)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessState != 3)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessState = 0;
		CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		if (!mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND(2, &tData[0]))
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mEXTRA_COM.mRecv_Result != 0)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tTotalMemberNum = 0;
		for (index01 = 0; index01 < MAX_GUILD_AVATAR_NUM; index01++)
		{
			if (strcmp(mEXTRA_COM.mRecv_GuildInfo.gMemberName[index01], "") != 0)
			{
				tTotalMemberNum++;
			}
		}
		if (tTotalMemberNum >= (mEXTRA_COM.mRecv_GuildInfo.gGrade * 10))
		{
			mTRANSFER.B_GUILD_WORK_RECV(2, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		CopyMemory(&tData[MAX_GUILD_NAME_LENGTH], &mUSER[tOtherAvatarIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
		if (!mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND(tSort, &tData[0]))
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mEXTRA_COM.mRecv_Result != 0)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_GUILD_WORK_RECV(0, tSort, &mEXTRA_COM.mRecv_GuildInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 102;
		CopyMemory(&tBroadcastInfoData[0], &mUSER[tOtherAvatarIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&tBroadcastInfoData[MAX_AVATAR_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		strncpy(mUSER[tOtherAvatarIndex].mAvatarInfo.aGuildName, mUSER[tUserIndex].mAvatarInfo.aGuildName, MAX_GUILD_NAME_LENGTH);
		mUSER[tOtherAvatarIndex].mAvatarInfo.aGuildRole = 2;
		strcpy(mUSER[tOtherAvatarIndex].mAvatarInfo.aCallName, "");
		strncpy(mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aGuildName, mUSER[tUserIndex].mAvatarInfo.aGuildName, MAX_GUILD_NAME_LENGTH);
		mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aGuildRole = 2;
		strcpy(mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aCallName, "");
		return;
	case  4: //[Å»Åð]
		if ((strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0) || (mUSER[tUserIndex].mAvatarInfo.aGuildRole == 0))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		CopyMemory(&tData[MAX_GUILD_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
		if (!mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND(tSort, &tData[0]))
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mEXTRA_COM.mRecv_Result != 0)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_GUILD_WORK_RECV(0, tSort, &mEXTRA_COM.mRecv_GuildInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 103;
		CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&tBroadcastInfoData[MAX_AVATAR_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		strcpy(mUSER[tUserIndex].mAvatarInfo.aGuildName, "");
		mUSER[tUserIndex].mAvatarInfo.aGuildRole = 0;
		strcpy(mUSER[tUserIndex].mAvatarInfo.aCallName, "");
		strcpy(mAVATAR_OBJECT[tUserIndex].mDATA.aGuildName, "");
		mAVATAR_OBJECT[tUserIndex].mDATA.aGuildRole = 0;
		strcpy(mAVATAR_OBJECT[tUserIndex].mDATA.aCallName, "");
		return;
	case  5: //[¾Ë¸²]
		CopyMemory(tGuildNotice, &tData[0], (4 * MAX_GUILD_NOTICE_LENGTH));
		tGuildNotice[0][(MAX_GUILD_NOTICE_LENGTH - 1)] = '\0';
		tGuildNotice[1][(MAX_GUILD_NOTICE_LENGTH - 1)] = '\0';
		tGuildNotice[2][(MAX_GUILD_NOTICE_LENGTH - 1)] = '\0';
		tGuildNotice[3][(MAX_GUILD_NOTICE_LENGTH - 1)] = '\0';
		if ((strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0) || (mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		CopyMemory(&tData[MAX_GUILD_NAME_LENGTH], tGuildNotice, (4 * MAX_GUILD_NOTICE_LENGTH));
		if (!mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND(tSort, &tData[0]))
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mEXTRA_COM.mRecv_Result != 0)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_GUILD_WORK_RECV(0, tSort, &mEXTRA_COM.mRecv_GuildInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 104;
		CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		return;
	case  6: //[ÇØ»ê]
		if ((strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0) || (mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		if (!mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND(2, &tData[0]))
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mEXTRA_COM.mRecv_Result != 0)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tTotalMemberNum = 0;
		for (index01 = 0; index01 < MAX_GUILD_AVATAR_NUM; index01++)
		{
			if (strcmp(mEXTRA_COM.mRecv_GuildInfo.gMemberName[index01], "") != 0)
			{
				tTotalMemberNum++;
			}
		}
		if (tTotalMemberNum != 1)
		{
			mTRANSFER.B_GUILD_WORK_RECV(2, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		CopyMemory(&tData[MAX_GUILD_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
		if (!mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND(tSort, &tData[0]))
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mEXTRA_COM.mRecv_Result != 0)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		//mGAMELOG.GL_617_GUILD_MONEY(tUserIndex, 0, 3, mEXTRA_COM.mRecv_GuildInfo.gGrade);
		mTRANSFER.B_GUILD_WORK_RECV(0, tSort, &mEXTRA_COM.mRecv_GuildInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 105;
		CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		strcpy(mUSER[tUserIndex].mAvatarInfo.aGuildName, "");
		mUSER[tUserIndex].mAvatarInfo.aGuildRole = 0;
		strcpy(mUSER[tUserIndex].mAvatarInfo.aCallName, "");
		strcpy(mAVATAR_OBJECT[tUserIndex].mDATA.aGuildName, "");
		mAVATAR_OBJECT[tUserIndex].mDATA.aGuildRole = 0;
		strcpy(mAVATAR_OBJECT[tUserIndex].mDATA.aCallName, "");
		return;
	case  7: //[È®Àå]
		if ((strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0) || (mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		if (!mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND(2, &tData[0]))
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mEXTRA_COM.mRecv_Result != 0)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tTotalMemberNum = 0;
		for (index01 = 0; index01 < MAX_GUILD_AVATAR_NUM; index01++)
		{
			if (strcmp(mEXTRA_COM.mRecv_GuildInfo.gMemberName[index01], "") != 0)
			{
				tTotalMemberNum++;
			}
		}
		if (tTotalMemberNum < (mEXTRA_COM.mRecv_GuildInfo.gGrade * 10))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (mEXTRA_COM.mRecv_GuildInfo.gGrade)
		{
		case 1:
			if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 50)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if (mUSER[tUserIndex].mAvatarInfo.aMoney < 20000000)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			tCost = 20000000;
			break;
		case 2:
			if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 70)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if (mUSER[tUserIndex].mAvatarInfo.aMoney < 30000000)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			tCost = 30000000;
			break;
		case 3:
			if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 90)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if (mUSER[tUserIndex].mAvatarInfo.aMoney < 40000000)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			tCost = 40000000;
			break;
		case 4:
			if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 113)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if (mUSER[tUserIndex].mAvatarInfo.aMoney < 50000000)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			tCost = 50000000;
			break;
		default:
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		if (!mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND(tSort, &tData[0]))
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mEXTRA_COM.mRecv_Result != 0)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_GUILD_WORK_RECV(0, tSort, &mEXTRA_COM.mRecv_GuildInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 106;
		CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		//mGAMELOG.GL_617_GUILD_MONEY(tUserIndex, tCost, 2, mEXTRA_COM.mRecv_GuildInfo.gGrade);
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(19, mUSER[tUserIndex].mAvatarInfo.aMoney);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case  8: //[Á¦¸í]
		CopyMemory(&tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		if ((strcmp(tAvatarName, "") == 0) || (strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0) || (mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		CopyMemory(&tData[MAX_GUILD_NAME_LENGTH], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		if (!mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND(tSort, &tData[0]))
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mEXTRA_COM.mRecv_Result != 0)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_GUILD_WORK_RECV(0, tSort, &mEXTRA_COM.mRecv_GuildInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 107;
		CopyMemory(&tBroadcastInfoData[0], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&tBroadcastInfoData[MAX_AVATAR_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		return;
	case  9: //[ÀÓ¸í]
		CopyMemory(&tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tGuildRole, &tData[MAX_AVATAR_NAME_LENGTH], 4);
		if ((strcmp(tAvatarName, "") == 0) || (tGuildRole < 1) || (tGuildRole > 2) || (strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0) || (mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		CopyMemory(&tData[MAX_GUILD_NAME_LENGTH], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&tData[(MAX_GUILD_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH)], &tGuildRole, 4);
		if (!mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND(tSort, &tData[0]))
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mEXTRA_COM.mRecv_Result != 0)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_GUILD_WORK_RECV(0, tSort, &mEXTRA_COM.mRecv_GuildInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 108;
		CopyMemory(&tBroadcastInfoData[0], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&tBroadcastInfoData[MAX_AVATAR_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		CopyMemory(&tBroadcastInfoData[(MAX_AVATAR_NAME_LENGTH + MAX_GUILD_NAME_LENGTH)], &tGuildRole, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		return;
	case 10: //[ÄªÈ£]
		CopyMemory(&tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tCallName[0], &tData[MAX_AVATAR_NAME_LENGTH], MAX_CALL_NAME_LENGTH);
		tCallName[(MAX_CALL_NAME_LENGTH - 1)] = '\0';
		if ((strcmp(tAvatarName, "") == 0) || (strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0) || (mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		CopyMemory(&tData[MAX_GUILD_NAME_LENGTH], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&tData[(MAX_GUILD_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH)], &tCallName[0], MAX_CALL_NAME_LENGTH);
		if (!mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND(tSort, &tData[0]))
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mEXTRA_COM.mRecv_Result != 0)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_GUILD_WORK_RECV(0, tSort, &mEXTRA_COM.mRecv_GuildInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 109;
		CopyMemory(&tBroadcastInfoData[0], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&tBroadcastInfoData[MAX_AVATAR_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		CopyMemory(&tBroadcastInfoData[(MAX_AVATAR_NAME_LENGTH + MAX_GUILD_NAME_LENGTH)], &tCallName[0], MAX_CALL_NAME_LENGTH);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		return;
	case 11: //[¹®Àå]
		if ((strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0) || (mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0) || (mUSER[tUserIndex].mAvatarInfo.aGuildMarkNum < 1))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aGuildMarkNum--;
		mTRANSFER.B_GUILD_WORK_RECV(0, tSort, &mEXTRA_COM.mRecv_GuildInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 12: //[¹®ÆÄ±ê¹ß-ON]
		if (strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aGuildMarkEffect = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aGuildMarkEffect = 1;
		mTRANSFER.B_GUILD_WORK_RECV(0, tSort, &mEXTRA_COM.mRecv_GuildInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 13: //[¹®ÆÄ±ê¹ß-OFF]
		if (strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aGuildMarkEffect = 0;
		mAVATAR_OBJECT[tUserIndex].mDATA.aGuildMarkEffect = 0;
		mTRANSFER.B_GUILD_WORK_RECV(0, tSort, &mEXTRA_COM.mRecv_GuildInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	default: //[¿À·ù]
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}
//W_GUILD_NOTICE_SEND
void W_GUILD_NOTICE_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	char tContent[MAX_CHAT_CONTENT_LENGTH];
	CopyMemory(&tContent[0], &tPacket[1], MAX_CHAT_CONTENT_LENGTH);
	tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
	if (strcmp(tContent, "") == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	if ((strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0) || (mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0))
	{
		return;
	}
	tSort = 111;
	CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
	CopyMemory(&tData[MAX_GUILD_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
	CopyMemory(&tData[(MAX_GUILD_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
	mRELAY_COM.U_DEMAND_BROADCAST_DATA(tSort, &tData[0]);
}
//W_GUILD_CHAT_SEND
void W_GUILD_CHAT_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	//unsigned int tRandom = 0;
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	char tContent[MAX_CHAT_CONTENT_LENGTH];
	CopyMemory(&tContent[0], &tPacket[1], MAX_CHAT_CONTENT_LENGTH);
	tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
	if (strcmp(tContent, "") == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0)
	{
		return;
	}
	tSort = 112;
	CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
	CopyMemory(&tData[MAX_GUILD_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
	CopyMemory(&tData[(MAX_GUILD_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
	mRELAY_COM.U_DEMAND_BROADCAST_DATA(tSort, &tData[0]);

	char type[50];
	snprintf(type, 50, "W_GUILD_CHAT_SEND");
	GameLogger(2, "<GUILD_CHAT>(%s),(%s), (Message: %s),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tContent, mSERVER_INFO.mServerNumber);
	//mGAMELOG.CHAT_LOG_SEND(tUserIndex, NULL, &tContent[0], type);
}
//W_GUILD_FIND_SEND
void W_GUILD_FIND_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory(&tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';

	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0)
	{
		return;
	}
	mPLAYUSER_COM.U_FIND_AVATAR_FOR_ZONE_SEND(&tAvatarName[0]);
	mTRANSFER.B_GUILD_FIND_RECV(mPLAYUSER_COM.mRecv_ZoneNumber);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_TRIBE_WORK_SEND
void W_TRIBE_WORK_SEND(int tUserIndex)
{
	__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	unsigned int tRandom = 0;
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	int iCount = 0;
	BYTE tData[MAX_TRIBE_WORK_SIZE];
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tData[0], &tPacket[5], MAX_TRIBE_WORK_SIZE);


	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	int tOtherUserIndex;
	int tTribeWeaponItemNumber;
	// @ Tribe Formation Skill @
	int tTribeSkillSort = 0;
	// @
#ifdef __GOD__
	int tKillOtherTribeNum;
	int tRandomNumber;
	ITEM_INFO* tITEM_INFO;
	int Oran;
	int OranAzalma;
	int Title;
	int CpValue;
#endif

	int index01;
	int index02;
	ITEM_INFO* ItemID[8];
	int iPage[8];
	int iIndex[8];
	int iInvenPage[8];
	int	iInvenIndex[8];
	int	iInvenSlot[8];
	int ItemId[8];
	int ItemPage = 0;
	int ItemIndex1 = 0;
	int ItemIndex2 = 0;
	int ItemSlot1 = 0;
	int ItemSlot2 = 0;

	switch (tSort)
	{
	case  1: //[Ç÷¸ÆÅ¸Åë]
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 > 39)
			//if( mUSER[tUserIndex].mAvatarInfo.aLevel1 > 145 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aVitality + mUSER[tUserIndex].mAvatarInfo.aStrength + mUSER[tUserIndex].mAvatarInfo.aKi + mUSER[tUserIndex].mAvatarInfo.aWisdom - 4);
		mUSER[tUserIndex].mAvatarInfo.aVitality = 1;
		mUSER[tUserIndex].mAvatarInfo.aStrength = 1;
		mUSER[tUserIndex].mAvatarInfo.aKi = 1;
		mUSER[tUserIndex].mAvatarInfo.aWisdom = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_TRIBE_WORK_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case  2: //[ºÎ¼¼·ÂÀå_ÀÓ¸í]
		CopyMemory(&tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		if (mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) != 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (mUSER[tUserIndex].mAvatarInfo.aTribe)
		{
		case 0:
			if (mSERVER_INFO.mServerNumber != 71)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 1:
			if (mSERVER_INFO.mServerNumber != 72)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 2:
			if (mSERVER_INFO.mServerNumber != 73)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 3:
			if (mSERVER_INFO.mServerNumber != 140)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		}
		if (strcmp(tAvatarName, "") == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
#ifdef __GOD__
		for (index01 = 0; index01 < MAX_TRIBE_SUBMASTER_NUM; index01++)
		{
			if (strcmp(mGAME.mTribeInfo.mTribeSubMaster[mUSER[tUserIndex].mAvatarInfo.aTribe][index01], tAvatarName) == 0)
			{
				break;
			}
		}
		if (index01 < MAX_TRIBE_SUBMASTER_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
#endif
		for (index01 = 0; index01 < MAX_TRIBE_SUBMASTER_NUM; index01++)
		{
			if (strcmp(mGAME.mTribeInfo.mTribeSubMaster[mUSER[tUserIndex].mAvatarInfo.aTribe][index01], "") == 0)
			{
				break;
			}
		}
		if (index01 == MAX_TRIBE_SUBMASTER_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tOtherUserIndex = mUTIL.SearchAvatar(&tAvatarName[0], tUserIndex);
		if (tOtherUserIndex == -1)
		{
			mTRANSFER.B_TRIBE_WORK_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mUSER[tOtherUserIndex].mMoveZoneResult == 1)
		{
			mTRANSFER.B_TRIBE_WORK_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mUSER[tOtherUserIndex].mAvatarInfo.aLevel1 < 113)
		{
			mTRANSFER.B_TRIBE_WORK_RECV(2, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mUSER[tOtherUserIndex].mAvatarInfo.aKillOtherTribe < 1000)
		{
			mTRANSFER.B_TRIBE_WORK_RECV(3, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		/* SubMaster aName duplicate check */
		for (iCount = 0; iCount < MAX_TRIBE_SUBMASTER_NUM; iCount++) {
			if (!::strcmp(mGAME.mTribeInfo.mTribeSubMaster[mUSER[tUserIndex].mAvatarInfo.aTribe][iCount], tAvatarName)) {
				mTRANSFER.B_TRIBE_WORK_RECV(4, tSort, &tData[0]);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
		}
		/* SubMaster duplicate check */
		mTRANSFER.B_TRIBE_WORK_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 60;
		CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
		CopyMemory(&tBroadcastInfoData[4], &index01, 4);
		CopyMemory(&tBroadcastInfoData[8], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		strncpy(mGAME.mTribeInfo.mTribeSubMaster[mUSER[tUserIndex].mAvatarInfo.aTribe][index01], tAvatarName, MAX_AVATAR_NAME_LENGTH);
		return;
	case  3: //[ºÎ¼¼·ÂÀå_Á¦¸í]
		CopyMemory(&tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		if (mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) != 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (mUSER[tUserIndex].mAvatarInfo.aTribe)
		{
		case 0:
			if (mSERVER_INFO.mServerNumber != 71)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 1:
			if (mSERVER_INFO.mServerNumber != 72)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 2:
			if (mSERVER_INFO.mServerNumber != 73)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 3:
			if (mSERVER_INFO.mServerNumber != 140)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		}
		for (index01 = 0; index01 < MAX_TRIBE_SUBMASTER_NUM; index01++)
		{
			if (strcmp(mGAME.mTribeInfo.mTribeSubMaster[mUSER[tUserIndex].mAvatarInfo.aTribe][index01], tAvatarName) == 0)
			{
				break;
			}
		}
		if (index01 == MAX_TRIBE_SUBMASTER_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mTRANSFER.B_TRIBE_WORK_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 61;
		CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
		CopyMemory(&tBroadcastInfoData[4], &index01, 4);
		CopyMemory(&tBroadcastInfoData[8], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		strcpy(mGAME.mTribeInfo.mTribeSubMaster[mUSER[tUserIndex].mAvatarInfo.aTribe][index01], "");
		return;
	case  4: //[¼¼·Â¹«±â_Á¦ÀÛ]
		if ((mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) != 1) && (mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) != 2))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (mUSER[tUserIndex].mAvatarInfo.aTribe)
		{
		case 0:
			if (mSERVER_INFO.mServerNumber != 1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 1:
			if (mSERVER_INFO.mServerNumber != 6)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 2:
			if (mSERVER_INFO.mServerNumber != 11)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 3:
			if (mSERVER_INFO.mServerNumber != 140)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 500)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (mUSER[tUserIndex].mAvatarInfo.aTribe)
		{
		case 0:
			tTribeWeaponItemNumber = 1075;
			break;
		case 1:
			tTribeWeaponItemNumber = 1076;
			break;
		case 2:
			tTribeWeaponItemNumber = 1077;
			break;
		case 3:
			tTribeWeaponItemNumber = 1078;
			break;
		}
		if (!mUTIL.ProcessForDropItem(10, tTribeWeaponItemNumber, 0, 0, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[tUserIndex].mDATA.aName[0], 0, mUSER[tUserIndex].DropItemSocketGmAndBos))
		{
			mTRANSFER.B_TRIBE_WORK_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		//mGAMELOG.GL_641_MAKE_TRIBE_WEAPON(tUserIndex, tTribeWeaponItemNumber, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 500;
		mTRANSFER.B_TRIBE_WORK_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
		// @ Tribe Formation Skill @
	case  5: //[¼¼·ÂÁø¹ý]
		CopyMemory(&tTribeSkillSort, &tData[0], 4);
		if ((tTribeSkillSort < 0) || (tTribeSkillSort > 4))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) != 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((mGAME.mWorldInfo.mTribePoint[0] <= 100) || (mGAME.mWorldInfo.mTribePoint[1] <= 100) || (mGAME.mWorldInfo.mTribePoint[2] <= 100) || (mGAME.mWorldInfo.mTribePoint[3] <= 100))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mGAME.ReturnSmallTribe() != mUSER[tUserIndex].mAvatarInfo.aTribe)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mGAME.mWorldInfo.mTribeSymbolBattle != 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mTRANSFER.B_TRIBE_WORK_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 302;
		CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
		CopyMemory(&tBroadcastInfoData[4], &tTribeSkillSort, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		return; // @
	case 6:
		CopyMemory(&Title, &tData[0], 4);
		switch (mUSER[tUserIndex].mAvatarInfo.aTribe)
		{
		case 0:
			if (mSERVER_INFO.mServerNumber != 71)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 1:
			if (mSERVER_INFO.mServerNumber != 72)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 2:
			if (mSERVER_INFO.mServerNumber != 73)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 3:
			if (mSERVER_INFO.mServerNumber != 140)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		}
		if ((mUSER[tUserIndex].mAvatarInfo.Title % 100) == 12)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		switch (mUSER[tUserIndex].mAvatarInfo.Title % 100)
		{
		case 0:
			CpValue = 800;
			break;
		case 1:
			CpValue = 1700;
			break;
		case 2:
			CpValue = 2500;
			break;
		case 3:
			CpValue = 3400;
			break;
		case 4:
			CpValue = 4200;
			break;
		case 5:
			CpValue = 5100;
			break;
		case 6:
			CpValue = 5900;
			break;
		case 7:
			CpValue = 6800;
			break;
		case 8:
			CpValue = 7600;
			break;
		case 9:
			CpValue = 8500;
			break;
		case 10:
			CpValue = 9300;
			break;
		case 11:
			CpValue = 10000;
			break;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < CpValue)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		if (mUSER[tUserIndex].mAvatarInfo.Title != 0)
		{
			mUSER[tUserIndex].mAvatarInfo.Title += 1;
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.Title = 100 * (Title - 1) + 1;
		}

		mAVATAR_OBJECT[tUserIndex].mDATA.aTitle = mUSER[tUserIndex].mAvatarInfo.Title;
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= CpValue;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= CpValue;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_TRIBE_WORK_RECV(0, 6, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 7:
		switch (mUSER[tUserIndex].mAvatarInfo.aTribe)
		{
		case 0:
			if (mSERVER_INFO.mServerNumber != 1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 1:
			if (mSERVER_INFO.mServerNumber != 6)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 2:
			if (mSERVER_INFO.mServerNumber != 11)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 3:
			if (mSERVER_INFO.mServerNumber != 140)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aUpradgeValue == 96)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 100)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aMoney < 1000000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		/*if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}*/

		Oran = 106 - mUSER[tUserIndex].mAvatarInfo.aUpradgeValue;
		OranAzalma = -10 + mUSER[tUserIndex].mAvatarInfo.aUpradgeValue;

		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 100;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 100;
		mUSER[tUserIndex].mAvatarInfo.aMoney -= 1000000;

		tRandom = rand();
		if (tRandom % 100 < Oran)
		{
			++mUSER[tUserIndex].mAvatarInfo.aUpradgeValue;
			++mAVATAR_OBJECT[tUserIndex].mDATA.aHalo;
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			mTRANSFER.B_TRIBE_WORK_RECV(0, 7, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			if (mUSER[tUserIndex].mAvatarInfo.aUpradgeValue == 96)
			{
				tBroadcastInfoSort = 672;
				CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
				CopyMemory(&tBroadcastInfoData[4], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			}
			return;
		}
		tRandom = rand();
		if (tRandom % 100 < OranAzalma)
		{
			if (mUSER[tUserIndex].mAvatarInfo.Cppc > 0)
			{
				--mUSER[tUserIndex].mAvatarInfo.Cppc;
				mTRANSFER.B_TRIBE_WORK_RECV(1, 7, &tData[0]);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(31, mUSER[tUserIndex].mAvatarInfo.Cppc);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			--mUSER[tUserIndex].mAvatarInfo.aUpradgeValue;
			--mAVATAR_OBJECT[tUserIndex].mDATA.aHalo;
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			if (mUSER[tUserIndex].mAvatarInfo.aUpradgeValue <= 0)
			{
				mUSER[tUserIndex].mAvatarInfo.aUpradgeValue = 0;
				mTRANSFER.B_TRIBE_WORK_RECV(1, 7, &tData[0]);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			mTRANSFER.B_TRIBE_WORK_RECV(2, 7, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		else
		{
			mTRANSFER.B_TRIBE_WORK_RECV(1, 7, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		return;
	case 8:
		if (mUSER[tUserIndex].mAvatarInfo.Beginner != 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.BeginnerLevel == 0)
		{
			
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		/*mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;*/

		iPage[0] = 1;
		iPage[1] = 10;
		iPage[2] = 100;
		iPage[3] = 1000;
		iPage[4] = 10000;
		iPage[5] = 100000;
		iPage[6] = 1000000;
		iPage[7] = 10000000;
		//iPage[8] = 100000000;
		iIndex[0] = 1; //64
		iIndex[1] = 100;//6400
		iIndex[2] = 10000;
		iIndex[3] = 1000000;
		iIndex[4] = 1;
		iIndex[5] = 100;
		iIndex[6] = 10000;
		iIndex[7] = 1000000;
		//iIndex[8] = 10000000;
		for (index01 = 0; index01 < 8; index01++)
		{
			iInvenSlot[index01] = 0;
			iInvenIndex[index01] = 0;
			iInvenPage[index01] = 0;
			ItemId[index01] = NULL;
		}
		for (index01 = 0; index01 < 6; index01++)
		{
			ItemID[index01] = mITEM.ReturnRareItem1(mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, mUSER[tUserIndex].mAvatarInfo.BeginnerLevel, index01);
			//ItemID[6] = mITEM.Search();
			if (ItemID[index01] == NULL)
			{
				break;
			}
		}
		if (index01 != 6)
		{
			mTRANSFER.B_TRIBE_WORK_RECV(2, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		
		for (index01 = 0; index01 < 6; index01++)
		{
			if (ItemID[index01] == NULL)
			{
				break;
			}
			if (mUTIL.FindEmptyInvenForItem(tUserIndex, ItemID[index01], iInvenPage[index01], iInvenIndex[index01]) == false)
			{
				break;
			}
			iInvenSlot[index01] = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, iInvenPage[index01]);
			if (iInvenSlot[index01] == -1)
			{
				break;
			}
			ItemId[index01] = ItemID[index01]->iIndex;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage[index01]][iInvenSlot[index01]][0] = ItemId[index01];
			mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage[index01]][iInvenSlot[index01]][1] = iInvenIndex[index01] % 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage[index01]][iInvenSlot[index01]][2] = iInvenIndex[index01] / 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage[index01]][iInvenSlot[index01]][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage[index01]][iInvenSlot[index01]][4] = 30;//item %
			mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage[index01]][iInvenSlot[index01]][5] = 30;
			ItemPage += (iPage[index01] * iInvenPage[index01]);
			if (index01 > 3)
			{
				ItemIndex2 += (iInvenIndex[index01] * iIndex[index01]);
				ItemSlot2 += (iInvenSlot[index01] * iIndex[index01]);
			}
			else
			{
				ItemIndex1 += (iInvenIndex[index01] * iIndex[index01]);
				ItemSlot1 += (iInvenSlot[index01] * iIndex[index01]);
			}
		}
		if (index01 != 6)//7
		{
			for (index02 = 0; index02 < index01; index02++)
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage[index02]][iInvenSlot[index02]][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage[index02]][iInvenSlot[index02]][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage[index02]][iInvenSlot[index02]][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage[index02]][iInvenSlot[index02]][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage[index02]][iInvenSlot[index02]][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage[index02]][iInvenSlot[index02]][5] = 0;

			}
			mTRANSFER.B_TRIBE_WORK_RECV(2, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.Beginner = 0;
		mUSER[tUserIndex].mAvatarInfo.BeginnerLevel = 0;
		mTRANSFER.B_AVLANMABONUSU(8008, ItemPage, ItemSlot1, ItemSlot2, ItemIndex1, ItemIndex2, &ItemId[0], 30);//last item %
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_TRIBE_WORK_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		break;
	case 9:
		if (mUSER[tUserIndex].mAvatarInfo.iGoldOrnamentRemainsTime < 0 && mUSER[tUserIndex].mAvatarInfo.iSilverOrnamentRemainsTime < 0)
		{
			mTRANSFER.B_TRIBE_WORK_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.iUseOrnament = 1;
		mTRANSFER.B_TRIBE_WORK_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		return;
	case 10:
		mUSER[tUserIndex].mAvatarInfo.iUseOrnament = 0;
		mTRANSFER.B_TRIBE_WORK_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue > mAVATAR_OBJECT[tUserIndex].mDATA.aMaxLifeValue)
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].mDATA.aMaxLifeValue;
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue > mAVATAR_OBJECT[tUserIndex].mDATA.aMaxManaValue)
			mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].mDATA.aMaxManaValue;
		return;
	case 11:
		switch (mUSER[tUserIndex].mAvatarInfo.aTribe)
		{
		case 0:
			if (mSERVER_INFO.mServerNumber != 71)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 1:
			if (mSERVER_INFO.mServerNumber != 72)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 2:
			if (mSERVER_INFO.mServerNumber != 73)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 3:
			if (mSERVER_INFO.mServerNumber != 140)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 10000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 != 12)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 != 1481117817)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		//nova - Game rebirth limit.
		if (mUSER[tUserIndex].mAvatarInfo.SkillIncreaseCritHit > 12)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		mAVATAR_OBJECT[tUserIndex].mDATA.aRebirth += 1;
		mUSER[tUserIndex].mAvatarInfo.SkillIncreaseCritHit += 1;
		mUSER[tUserIndex].mAvatarInfo.LifeOrDeath += 10;
		mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 10000;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 10000;
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 14, mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe, mUSER[tUserIndex].mAvatarInfo.SkillIncreaseCritHit, mUSER[tUserIndex].mAvatarInfo.LifeOrDeath);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
		mTRANSFER.B_TRIBE_WORK_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case  18:
		if ((mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) != 1) && (mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) != 2))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (mUSER[tUserIndex].mAvatarInfo.aTribe)
		{
		case 0:
			if (mSERVER_INFO.mServerNumber != 1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 1:
			if (mSERVER_INFO.mServerNumber != 6)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 2:
			if (mSERVER_INFO.mServerNumber != 11)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 3:
			if (mSERVER_INFO.mServerNumber != 140)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		}
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
		if (mUSER[tUserIndex].mAvatarInfo.aMoney < 500000000)
		{
			mTRANSFER.B_TRIBE_WORK_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (!mUTIL.ProcessForDropItem(10, 665, 0, 0, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[tUserIndex].mDATA.aName[0], 0, mUSER[tUserIndex].DropItemSocketGmAndBos))
		{
			mTRANSFER.B_TRIBE_WORK_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		//mGAMELOG.GL_641_MAKE_TRIBE_WEAPON(tUserIndex, tTribeWeaponItemNumber, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aMoney -= 500000000;
		mTRANSFER.B_TRIBE_WORK_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	default: //[¿À·ù]
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}
//W_TRIBE_NOTICE_SEND
void W_TRIBE_NOTICE_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	char tContent[MAX_CHAT_CONTENT_LENGTH];
	CopyMemory(&tContent[0], &tPacket[1], MAX_CHAT_CONTENT_LENGTH);
	tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
	if (strcmp(tContent, "") == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	if (mUSER[tUserIndex].mAvatarInfo.aSpecialState == 2)
	{
		return;
	}
	if (mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) != 1 && mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) != 2)
	{
		return;
	}
	tSort = 113;
	CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
	CopyMemory(&tData[MAX_AVATAR_NAME_LENGTH], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
	CopyMemory(&tData[(MAX_AVATAR_NAME_LENGTH + MAX_CHAT_CONTENT_LENGTH)], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
	mRELAY_COM.U_DEMAND_BROADCAST_DATA(tSort, &tData[0]);
}
//W_TRIBE_CHAT_SEND
void W_TRIBE_CHAT_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	//unsigned int tRandom = 0;
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}
	if (10 > mAVATAR_OBJECT[tUserIndex].mDATA.aLevel1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	char tContent[MAX_CHAT_CONTENT_LENGTH];
	CopyMemory(&tContent[0], &tPacket[1], MAX_CHAT_CONTENT_LENGTH);
	tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
	if (strcmp(tContent, "") == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int index01;
	BYTE tAuthType = 0;

	if (mUSER[tUserIndex].mAvatarInfo.aSpecialState == 2)
	{
		return;
	}
	if (1 == mUSER[tUserIndex].mAuthInfo.AuthType)
		tAuthType = 1;
	mTRANSFER.B_TRIBE_CHAT_RECV(&mUSER[tUserIndex].mAvatarInfo.aName[0], tAuthType, &tContent[0]);

	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (!mAVATAR_OBJECT[index01].mCheckValidState)
		{
			continue;
		}
		if ((mAVATAR_OBJECT[index01].mDATA.aTribe != mAVATAR_OBJECT[tUserIndex].mDATA.aTribe) && (mAVATAR_OBJECT[index01].mDATA.aTribe != mGAME.ReturnAllianceTribe(mAVATAR_OBJECT[tUserIndex].mDATA.aTribe)))
		{
			continue;
		}
		mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}
}
//W_TRIBE_BANK_SEND
void W_TRIBE_BANK_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	int tValue;
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tValue, &tPacket[5], 4);

	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	int tMoney;

	switch (tSort)
	{
	case 1: //[Á¶È¸]
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			if (mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) == 0)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		mPLAYUSER_COM.U_TRIBE_BANK_INFO_VIEW_SEND(mUSER[tUserIndex].mAvatarInfo.aTribe);
		mTRANSFER.B_TRIBE_BANK_RECV(mPLAYUSER_COM.mRecv_Result, 1, &mPLAYUSER_COM.mRecv_TribeBankInfo[0], 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 2: //[ÀÎÃâ]
		if ((tValue < 0) || (tValue > (MAX_TRIBE_BANK_SLOT_NUM - 1)) || (mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) != 1) || (mGAME.ReturnTribeSubMasterNum(mUSER[tUserIndex].mAvatarInfo.aTribe) < 3))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mPLAYUSER_COM.U_TRIBE_BANK_INFO_LOAD_SEND(mUSER[tUserIndex].mAvatarInfo.aTribe, tValue, mUSER[tUserIndex].mAvatarInfo.aMoney);
		switch (mPLAYUSER_COM.mRecv_Result)
		{
		case 0:
			tMoney = mPLAYUSER_COM.mRecv_Money - mUSER[tUserIndex].mAvatarInfo.aMoney;
			//mGAMELOG.GL_618_TRIBE_MONEY(tUserIndex, tMoney);
			mUSER[tUserIndex].mAvatarInfo.aMoney = mPLAYUSER_COM.mRecv_Money;
			mTRANSFER.B_TRIBE_BANK_RECV(0, 2, &mPLAYUSER_COM.mRecv_TribeBankInfo[0], mPLAYUSER_COM.mRecv_Money);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 62;
			CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
			CopyMemory(&tBroadcastInfoData[4], &tMoney, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			return;
		default:
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		return;
	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}
//W_TRIBE_VOTE_SEND
void W_TRIBE_VOTE_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	int tValue;
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tValue, &tPacket[5], 4);

	int index01 = 0;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	int tLevelForTribeVote;
	int tPointForTribeVote;
	int VoteDate = mUTIL.ReturnVoteDate();
	switch (tSort)
	{
	case 1:

		if ((tValue < 0) || (tValue > (MAX_TRIBE_VOTE_AVATAR_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}


		if (mGAME.mWorldInfo.mTribeVoteState[mUSER[tUserIndex].mAvatarInfo.aTribe] != 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 113)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}


		/*if (mUSER[tUserIndex].mAvatarInfo.SkillIncreaseCritHit < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}*/

		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 1000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		for (index01 = 0; index01 < MAX_TRIBE_VOTE_AVATAR_NUM; ++index01)
		{
			if (strcmp(mGAME.mTribeInfo.mTribeVoteName[mUSER[tUserIndex].mAvatarInfo.aTribe][index01], mUSER[tUserIndex].mAvatarInfo.aName) == 0)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}

		for (index01 = 0; index01 < MAX_TRIBE_VOTE_AVATAR_NUM; ++index01) {
			if (strcmp(mGAME.mTribeInfo.mTribeVoteName[mUSER[tUserIndex].mAvatarInfo.aTribe][index01], "") != 0)
				continue;
			tValue = index01;
			break;
		}

		if (MAX_TRIBE_VOTE_AVATAR_NUM == index01)
		{
			tValue = 0;

			for (index01 = 1; index01 < MAX_TRIBE_VOTE_AVATAR_NUM; ++index01)
			{
				if (mGAME.mTribeInfo.mTribeVoteKillOtherTribe[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue] < mGAME.mTribeInfo.mTribeVoteKillOtherTribe[mUSER[tUserIndex].mAvatarInfo.aTribe][index01])
				{
					continue;
				}

				tValue = index01;
			}

			if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe <= mGAME.mTribeInfo.mTribeVoteKillOtherTribe[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue])
			{
				mTRANSFER.B_TRIBE_VOTE_RECV(1, tSort, tValue);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

				return;
			}
		}

		mTRANSFER.B_TRIBE_VOTE_RECV(0, tSort, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		tLevelForTribeVote = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2  - 112;

		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 57;
		CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
		CopyMemory(&tBroadcastInfoData[4], &tValue, 4);
		CopyMemory(&tBroadcastInfoData[8], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&tBroadcastInfoData[(8 + MAX_AVATAR_NAME_LENGTH)], &tLevelForTribeVote, 4);
		CopyMemory(&tBroadcastInfoData[(12 + MAX_AVATAR_NAME_LENGTH)], &mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		strncpy(mGAME.mTribeInfo.mTribeVoteName[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue], mUSER[tUserIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH);
		mGAME.mTribeInfo.mTribeVoteLevel[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue] = tLevelForTribeVote;
		mGAME.mTribeInfo.mTribeVoteKillOtherTribe[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue] = mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe;
		mGAME.mTribeInfo.mTribeVotePoint[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue] = 0;
		return;
	case 2:

		if ((tValue < 0) || (tValue > (MAX_TRIBE_VOTE_AVATAR_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		if (mGAME.mWorldInfo.mTribeVoteState[mUSER[tUserIndex].mAvatarInfo.aTribe] != 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		if (strcmp(mGAME.mTribeInfo.mTribeVoteName[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue], mUSER[tUserIndex].mAvatarInfo.aName) != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		mTRANSFER.B_TRIBE_VOTE_RECV(0, tSort, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		tBroadcastInfoSort = 58;
		CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
		CopyMemory(&tBroadcastInfoData[4], &tValue, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);

		strcpy(mGAME.mTribeInfo.mTribeVoteName[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue], "");
		mGAME.mTribeInfo.mTribeVoteLevel[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue] = 0;
		mGAME.mTribeInfo.mTribeVoteKillOtherTribe[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue] = 0;
		mGAME.mTribeInfo.mTribeVotePoint[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue] = 0;

		return;
	case 3:

		if ((tValue < 0) || (tValue > (MAX_TRIBE_VOTE_AVATAR_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		if (mGAME.mWorldInfo.mTribeVoteState[mUSER[tUserIndex].mAvatarInfo.aTribe] != 2)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 113)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		//not r1
		/*if (mUSER[tUserIndex].mAvatarInfo.SkillIncreaseCritHit < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}*/

		if (strcmp(mGAME.mTribeInfo.mTribeVoteName[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue], "") == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		

		if (mUSER[tUserIndex].mAvatarInfo.aTribeVoteDate >= VoteDate)
		{
			mTRANSFER.B_TRIBE_VOTE_RECV(1, tSort, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		mUSER[tUserIndex].mAvatarInfo.aTribeVoteDate = mUTIL.ReturnVoteDate();
		mTRANSFER.B_TRIBE_VOTE_RECV(0, tSort, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		tPointForTribeVote = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2 * 3 - 112;
		tBroadcastInfoSort = 59;
		CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
		CopyMemory(&tBroadcastInfoData[4], &tValue, 4);
		CopyMemory(&tBroadcastInfoData[8], &tPointForTribeVote, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);

		return;
	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

		return;
	}
}
//W_CHECK_HACK_INFO
void W_CHECK_HACK_INFO(int tUserIndex)
{
}
//W_CHECK_N_PROTECT_2
void W_CHECK_N_PROTECT_2(int tUserIndex)
{
}
//W_CHECK_AUTH_KEY
void W_CHECK_AUTH_KEY(int tUserIndex)
{
}
//W_UPDATE_AUTH_KEY
void W_UPDATE_AUTH_KEY(int tUserIndex)
{
}
//W_ACK_INCOMONG_UDP
void W_ACK_INCOMING_UDP(int tUserIndex)
{
}
//W_REQUEST_PRESENT
void W_REQUEST_PRESENT(int tUserIndex)
{
}
//W_CHANGE_PLAYTIMETOTEACHERPOINT
void W_CHANGE_PLAYTIMETOTEACHERPOINT(int tUserIndex)
{
}
//W_CHECK_EVENT_INFO
void W_CHECK_EVENT_INFO(int tUserIndex)
{
}
//W_GET_RANK_INFO
void W_GET_RANK_INFO(int tUserIndex)
{
}
//W_CHANGE_AUTO_INFO
void W_CHANGE_AUTO_INFO(int tUserIndex)
{
}
#ifdef __ANIMAL__
//W_ANIMAL_STATE_SEND
void W_ANIMAL_STATE_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tValue01;
	int tValue02;
	CopyMemory(&tValue01, &tPacket[1], 4);
	CopyMemory(&tValue02, &tPacket[5], 4);
	int trandom;
	int BinekKasma[8];
	int BinekKasılma;
	int KasılmaSayısı = 0;
	int BinekIndex;
	int index01;
	int index02;
	int index03;
	int tPage = -1;
	int tIndex = -1;
	int dur;

	switch (tValue01)
	{
	case 1: //[��������]
		if ((tValue02 < 0) || (tValue02 > (MAX_AVATAR_ANIMAL_NUM - 1)))
		{
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aAnimal[tValue02] == 0)
		{
			return;
		}
		if ((mUSER[tUserIndex].mAvatarInfo.aAnimalIndex >= MAX_AVATAR_ANIMAL_NUM) && (mUSER[tUserIndex].mAvatarInfo.aAnimalIndex <= (MAX_AVATAR_ANIMAL_NUM + MAX_AVATAR_ANIMAL_NUM - 1)))
		{
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aAnimalIndex = tValue02;
		mTRANSFER.B_ANIMAL_STATE_RECV(tValue01, tValue02);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 2: //[��������]
		if ((mUSER[tUserIndex].mAvatarInfo.aAnimalIndex >= MAX_AVATAR_ANIMAL_NUM) && (mUSER[tUserIndex].mAvatarInfo.aAnimalIndex <= (MAX_AVATAR_ANIMAL_NUM + MAX_AVATAR_ANIMAL_NUM - 1)))
		{
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aAnimalIndex = -1;
		mTRANSFER.B_ANIMAL_STATE_RECV(tValue01, tValue02);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 3: //[������ȯ]
		if ((mUSER[tUserIndex].mAvatarInfo.aAnimalIndex < 0) || (mUSER[tUserIndex].mAvatarInfo.aAnimalIndex > (MAX_AVATAR_ANIMAL_NUM - 1)))
		{
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aAnimalTime < 1)
		{
			return;
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort != 1)
		{
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aAnimalIndex += MAX_AVATAR_ANIMAL_NUM;
		mTRANSFER.B_ANIMAL_STATE_RECV(tValue01, tValue02);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalNumber = mUSER[tUserIndex].mAvatarInfo.aAnimal[(mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - MAX_AVATAR_ANIMAL_NUM)];
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aFrame = 0.0f;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue > mAVATAR_OBJECT[tUserIndex].mDATA.aMaxLifeValue)
		{
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].mDATA.aMaxLifeValue;
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue > mAVATAR_OBJECT[tUserIndex].mDATA.aMaxManaValue)
		{
			mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].mDATA.aMaxManaValue;
		}
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 12, mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalNumber, 0, 0);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
		mUSER[tUserIndex].mTickCountFor01Minute_2 = mGAME.mTickCount;
		return;
	case 4: //[��ȯ����]
		if ((mUSER[tUserIndex].mAvatarInfo.aAnimalIndex < MAX_AVATAR_ANIMAL_NUM) || (mUSER[tUserIndex].mAvatarInfo.aAnimalIndex > (MAX_AVATAR_ANIMAL_NUM + MAX_AVATAR_ANIMAL_NUM - 1)))
		{
			return;
		}

		mUSER[tUserIndex].mAvatarInfo.aAnimalIndex -= MAX_AVATAR_ANIMAL_NUM;
		mTRANSFER.B_ANIMAL_STATE_RECV(tValue01, tValue02);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalNumber = 0;
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aFrame = 0.0f;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue > mAVATAR_OBJECT[tUserIndex].mDATA.aMaxLifeValue)
		{
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].mDATA.aMaxLifeValue;
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue > mAVATAR_OBJECT[tUserIndex].mDATA.aMaxManaValue)
		{
			mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].mDATA.aMaxManaValue;
		}
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 13, 0, 0, 0);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
		return;
	case 5: //[Delete Mount]
		if ((mUSER[tUserIndex].mAvatarInfo.aAnimalIndex >= MAX_AVATAR_ANIMAL_NUM) && (mUSER[tUserIndex].mAvatarInfo.aAnimalIndex <= (MAX_AVATAR_ANIMAL_NUM + MAX_AVATAR_ANIMAL_NUM - 1)))
		{
			return;
		}
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == tValue02)
			{
				if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] < 1)
				{
					return;
				}
				if (mUSER[tUserIndex].mAvatarInfo.aMoney < 10000000) {
					return;
				}
				mUSER[tUserIndex].mAvatarInfo.aMoney -= 10000000;
				mUSER[tUserIndex].mAvatarInfo.aAnimalIndex = -1;
				mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] = 0;
				mUSER[tUserIndex].mAvatarInfo.AnimalExp[index01] = 0;
				mUSER[tUserIndex].mAvatarInfo.AnimalStat[index01] = 0;

				mTRANSFER.B_ANIMAL_STATE_RECV(tValue01, tValue02);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

				mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 50;
				mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 50;

				mTRANSFER.B_AVATAR_CHANGE_INFO_2(3, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

				
				
				break;
			}

		}
		return;
	case 6: //[��������]
		BinekIndex = mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - MAX_AVATAR_ANIMAL_NUM;
		if (mUSER[tUserIndex].mAvatarInfo.AnimalExp[BinekIndex] % 1000000 != 100000)
		{
			return;
		}
		BinekKasılma = mUSER[tUserIndex].mAvatarInfo.AnimalStat[BinekIndex];
		KasılmaSayısı = 0;
		for (index01 = 0; index01 < 8; ++index01)
		{
			(BinekKasma[index01]) = BinekKasılma % 10;
			BinekKasılma = BinekKasılma / 10;
			KasılmaSayısı += BinekKasma[index01];
		}
		if (KasılmaSayısı == 25)
		{
			return;
		}
	LABEL_31:
		trandom = rand() % 8;
		switch (trandom)
		{
		case 0:
			if (BinekKasma[0] == 9)
			{
				goto LABEL_31;
			}
			mUSER[tUserIndex].mAvatarInfo.AnimalStat[BinekIndex] += 1;
			break;
		case 1:
			if (BinekKasma[1] == 9)
			{
				goto LABEL_31;
			}
			mUSER[tUserIndex].mAvatarInfo.AnimalStat[BinekIndex] += 10;
			break;
		case 2:
			if (BinekKasma[2] == 9)
			{
				goto LABEL_31;
			}
			mUSER[tUserIndex].mAvatarInfo.AnimalStat[BinekIndex] += 100;
			break;
		case 3:
			if (BinekKasma[3] == 9)
			{
				goto LABEL_31;
			}
			mUSER[tUserIndex].mAvatarInfo.AnimalStat[BinekIndex] += 1000;
			break;
		case 4:
			if (BinekKasma[4] == 9)
			{
				goto LABEL_31;
			}
			mUSER[tUserIndex].mAvatarInfo.AnimalStat[BinekIndex] += 10000;
			break;
		case 5:
			if (BinekKasma[5] == 9)
			{
				goto LABEL_31;
			}
			mUSER[tUserIndex].mAvatarInfo.AnimalStat[BinekIndex] += 100000;
			break;
		case 6:
			if (BinekKasma[6] == 9)
			{
				goto LABEL_31;
			}
			mUSER[tUserIndex].mAvatarInfo.AnimalStat[BinekIndex] += 1000000;
			break;
		case 7:
			if (BinekKasma[7] == 9)
			{
				goto LABEL_31;
			}
			mUSER[tUserIndex].mAvatarInfo.AnimalStat[BinekIndex] += 10000000;
			break;
		}

		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mUSER[tUserIndex].mAvatarInfo.AnimalExp[BinekIndex] -= (mUSER[tUserIndex].mAvatarInfo.AnimalExp[BinekIndex] % 1000000);
		mTRANSFER.B_ANIMAL_STATE_RECV(tValue01, mUSER[tUserIndex].mAvatarInfo.AnimalStat[BinekIndex]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 8:
		BinekIndex = mUSER[tUserIndex].mAvatarInfo.aAnimalIndex;
		BinekKasılma = mUSER[tUserIndex].mAvatarInfo.AnimalStat[BinekIndex];
		KasılmaSayısı = 0;

		if (BinekIndex > 9)
		{
			BinekIndex -= 10;
		}
		for (index02 = 0; index02 < 2; ++index02)
		{
			for (index03 = 0; index03 < 64; ++index03)
			{
				if (mUSER[tUserIndex].mAvatarInfo.aInventory[index02][index03][0] == 1226)
				{
					tPage = index02;
					tIndex = index03;
					dur++;
					break;
				}
			}
			if (dur == 1)
			{
				break;
			}
		}
		if (index02 == 2 && index03 == 64)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage][tIndex][2] = 0;
		mTRANSFER.B_ITEM_SEND(0, 0, tPage, tIndex, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		for (index01 = 0; index01 < 8; ++index01)
		{
			(BinekKasma[index01]) = BinekKasılma % 10;
			BinekKasılma = BinekKasılma / 10;
			KasılmaSayısı += BinekKasma[index01];
		}
		switch (tValue02)
		{
		case 1:
			mUSER[tUserIndex].mAvatarInfo.AnimalStat[BinekIndex] -= 10000000;
			break;
		case 2:
			mUSER[tUserIndex].mAvatarInfo.AnimalStat[BinekIndex] -= 1000000;
			break;
		case 3:
			mUSER[tUserIndex].mAvatarInfo.AnimalStat[BinekIndex] -= 100000;
			break;
		case 4:
			mUSER[tUserIndex].mAvatarInfo.AnimalStat[BinekIndex] -= 10000;
			break;
		case 5:
			mUSER[tUserIndex].mAvatarInfo.AnimalStat[BinekIndex] -= 1000;
			break;
		case 6:
			mUSER[tUserIndex].mAvatarInfo.AnimalStat[BinekIndex] -= 100;
			break;
		case 7:
			mUSER[tUserIndex].mAvatarInfo.AnimalStat[BinekIndex] -= 10;
			break;
		case 8:
			mUSER[tUserIndex].mAvatarInfo.AnimalStat[BinekIndex] -= 1;
			break;
		}
		BinekKasılma = mUSER[tUserIndex].mAvatarInfo.AnimalStat[BinekIndex];
		KasılmaSayısı = 0;
		for (index01 = 0; index01 < 8; ++index01)
		{
			(BinekKasma[index01]) = BinekKasılma % 10;
			BinekKasılma = BinekKasılma / 10;
			KasılmaSayısı += BinekKasma[index01];
		}
	LABEL_32:
		trandom = rand() % 8;
		switch (trandom)
		{
		case 0:
			if (BinekKasma[0] == 9 || tValue02 == 8)
			{
				goto LABEL_32;
			}
			mUSER[tUserIndex].mAvatarInfo.AnimalStat[BinekIndex] += 1;
			break;
		case 1:
			if (BinekKasma[1] == 9 || tValue02 == 7)
			{
				goto LABEL_32;
			}
			mUSER[tUserIndex].mAvatarInfo.AnimalStat[BinekIndex] += 10;
			break;
		case 2:
			if (BinekKasma[2] == 9 || tValue02 == 6)
			{
				goto LABEL_32;
			}
			mUSER[tUserIndex].mAvatarInfo.AnimalStat[BinekIndex] += 100;
			break;
		case 3:
			if (BinekKasma[3] == 9 || tValue02 == 5)
			{
				goto LABEL_32;
			}
			mUSER[tUserIndex].mAvatarInfo.AnimalStat[BinekIndex] += 1000;
			break;
		case 4:
			if (BinekKasma[4] == 9 || tValue02 == 4)
			{
				goto LABEL_32;
			}
			mUSER[tUserIndex].mAvatarInfo.AnimalStat[BinekIndex] += 10000;
			break;
		case 5:
			if (BinekKasma[5] == 9 || tValue02 == 3)
			{
				goto LABEL_32;
			}
			mUSER[tUserIndex].mAvatarInfo.AnimalStat[BinekIndex] += 100000;
			break;
		case 6:
			if (BinekKasma[6] == 9 || tValue02 == 2)
			{
				goto LABEL_32;
			}
			mUSER[tUserIndex].mAvatarInfo.AnimalStat[BinekIndex] += 1000000;
			break;
		case 7:
			if (BinekKasma[7] == 9 || tValue02 == 1)
			{
				goto LABEL_32;
			}
			mUSER[tUserIndex].mAvatarInfo.AnimalStat[BinekIndex] += 10000000;
			break;
		}
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_ANIMAL_STATE_RECV(tValue01, mUSER[tUserIndex].mAvatarInfo.AnimalStat[BinekIndex]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}
#endif
// @ Cost Info Download @
void W_GET_CASH_ITEM_INFO_SEND(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mIsValidCashItemInfo == true)
	{
		return;
	}

	mTRANSFER.B_GET_CASH_ITEM_INFO_RECV(0, mEXTRA_COM.mCashItemInfoVersion, mEXTRA_COM.mCashItemInfo);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	mUSER[tUserIndex].mIsValidCashItemInfo = true;
} // @

//W_MOUT_ABSORBE
void w_MOUT_ABSORB(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.MountAbsorb < 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	int tAbsord;
	CopyMemory(&tAbsord, &tPacket[1], 4);


	if (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort != 1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalOn == 0)
	{
		mUSER[tUserIndex].mAvatarInfo.MountAbsorbe = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalOn = mUSER[tUserIndex].mAvatarInfo.MountAbsorbe;

		mTRANSFER.B_AVATAR_CHANGE_INFO_2(79, mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalOn);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 26, mUSER[tUserIndex].mAvatarInfo.MountAbsorbe, 0, 0);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
		mUSER[tUserIndex].mTickCountFor01Minute_2 = mGAME.mTickCount;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		return;
	}
	if (mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalOn == 1)
	{
		mUSER[tUserIndex].mAvatarInfo.MountAbsorbe = 0;
		mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalOn = mUSER[tUserIndex].mAvatarInfo.MountAbsorbe;

		mTRANSFER.B_AVATAR_CHANGE_INFO_2(79, mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalOn);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 26, mUSER[tUserIndex].mAvatarInfo.MountAbsorbe, 0, 0);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
		mUSER[tUserIndex].mTickCountFor01Minute_2 = mGAME.mTickCount;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue > mAVATAR_OBJECT[tUserIndex].mDATA.aMaxLifeValue)
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].mDATA.aMaxLifeValue;
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue > mAVATAR_OBJECT[tUserIndex].mDATA.aMaxManaValue)
			mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].mDATA.aMaxManaValue;
		return;
	}
}
//W_AUTO_POT
void W_AUTO_POT(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}


	int Value1;
	int Value2;
	CopyMemory(&Value1, &tPacket[1], 4);
	CopyMemory(&Value2, &tPacket[5], 4);
	mUSER[tUserIndex].mAvatarInfo.HealtAutoPot = Value1;
	mUSER[tUserIndex].mAvatarInfo.ManaAutoPot = Value2;
	return;
}
//W_COSTUME
void W_COSTUME(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}


	int Value1;
	int Value2;
	CopyMemory(&Value1, &tPacket[1], 4);
	CopyMemory(&Value2, &tPacket[5], 4);

	ITEM_INFO* pItemInfo = NULL;

	int iPage = 0, iInvenIndex = 0, iInvenSlot = 0;

	switch (Value1)
	{
	case 1:
		if (Value2 < 0 || Value2 > 10)
		{
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.Costume[Value2] == 0)
		{
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.SelectCostume = Value2;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_COSTUME(0, Value1, Value2, 0, 0, 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 2:
		if (Value2 < 0 || Value2 > 10)
		{
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.SelectCostume = -1;
		mTRANSFER.B_COSTUME(0, Value1, Value2, 0, 0, 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue > mAVATAR_OBJECT[tUserIndex].mDATA.aMaxLifeValue)
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].mDATA.aMaxLifeValue;
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue > mAVATAR_OBJECT[tUserIndex].mDATA.aMaxManaValue)
			mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].mDATA.aMaxManaValue;
		return;
	case 3:
		if (mUSER[tUserIndex].mAvatarInfo.SelectCostume == -1)
		{
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.SelectCostume += MAX_AVATAR_ANIMAL_NUM;
		mTRANSFER.B_COSTUME(0, Value1, Value2, 0, 0, 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mAVATAR_OBJECT[tUserIndex].mDATA.aFashionNumber = mUSER[tUserIndex].mAvatarInfo.Costume[mUSER[tUserIndex].mAvatarInfo.SelectCostume - MAX_AVATAR_ANIMAL_NUM];
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 16, mAVATAR_OBJECT[tUserIndex].mDATA.aFashionNumber, 1, 0);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
		return;

	case 4:
		if (mUSER[tUserIndex].mAvatarInfo.SelectCostume == -1)
		{
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.SelectCostume -= MAX_AVATAR_ANIMAL_NUM;
		mTRANSFER.B_COSTUME(0, Value1, Value2, 0, 0, 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mAVATAR_OBJECT[tUserIndex].mDATA.aFashionNumber = 0;
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 17, 0, 0, 0);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue > mAVATAR_OBJECT[tUserIndex].mDATA.aMaxLifeValue)
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].mDATA.aMaxLifeValue;
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue > mAVATAR_OBJECT[tUserIndex].mDATA.aMaxManaValue)
			mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].mDATA.aMaxManaValue;
		return;
	case 5:
		if (mUSER[tUserIndex].mAvatarInfo.Costume[Value2] < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		pItemInfo = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.Costume[Value2]);
		if (pItemInfo == NULL)
		{
			return;
		}
		if (mUTIL.FindEmptyInvenForItem(tUserIndex, pItemInfo, iPage, iInvenIndex) == false)
		{
			return;
		}
		iInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, iPage);
		if (iInvenSlot == -1)
		{
			return;
		}
		for (int c = Value2; c < 9; c++)
		{
			mUSER[tUserIndex].mAvatarInfo.Costume[c] = mUSER[tUserIndex].mAvatarInfo.Costume[c + 1];
		}
		mUSER[tUserIndex].mAvatarInfo.Costume[9] = 0;
		mGAMELOG.GL_COSTUME_ITEM(tUserIndex, pItemInfo->iIndex, pItemInfo->iName);
		mUSER[tUserIndex].mAvatarInfo.SelectCostume = -1;
		mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = pItemInfo->iIndex;
		mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
		mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
		mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 0;
		mTRANSFER.B_COSTUME(0, Value1, Value2, iPage, iInvenSlot, iInvenIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	default:
		return;
		break;
	}

}
//W_AUTOBUFF
void W_AUTOBUFF(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.AutoBuffScroll < mUTIL.ReturnNowDate())
	{
		mUSER[tUserIndex].mAvatarInfo.AutoBuffScroll = 0;
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	BYTE tData[64];
	CopyMemory(&tData[0], &tPacket[1], 64);
	int index01;
	int AutoBuff;


	for (index01 = 0; index01 < 8; index01++)
	{
		CopyMemory(&AutoBuff, &tData[(index01 * 8 + 0)], 4);
		mUSER[tUserIndex].mAvatarInfo.AutoBuffSmenu[index01][0] = AutoBuff;
		CopyMemory(&AutoBuff, &tData[(index01 * 8 + 4)], 4);
		mUSER[tUserIndex].mAvatarInfo.AutoBuffSmenu[index01][1] = AutoBuff;
	}
	mTRANSFER.B_AUTOBUFF(0);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	return;

}
//W_AUTOBUFF1
void W_AUTOBUFF1(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.AutoBuffScroll < mUTIL.ReturnNowDate())
	{
		mUSER[tUserIndex].mAvatarInfo.AutoBuffScroll = 0;
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}


	int tValue2;
	float Konum[3];
	ACTION_INFO tAction;
	int tCheckMotion;
	Konum[3] = 0;
	Konum[3] = 0;
	Konum[2] = 0;
	CopyMemory(&Konum[0], &tPacket[1], 4);
	CopyMemory(&Konum[1], &tPacket[5], 4);
	CopyMemory(&Konum[2], &tPacket[9], 4);
	CopyMemory(&tValue2, &tPacket[13], 4);
	mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0] = Konum[0];
	mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[1] = Konum[1];
	mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[2] = Konum[2];
	mAVATAR_OBJECT[tUserIndex].SetSpaceIndex();
	switch (tValue2)
	{
	case 1:
		mUSER[tUserIndex].AutoBuffTick = mGAME.mTickCount;
		mUSER[tUserIndex].AutoBuff1 = tValue2;
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort = 41;
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aType = 0;
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aFrame = 0.0f;
		mTRANSFER.B_AVATAR_ACTION_RECV(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, &mAVATAR_OBJECT[tUserIndex].mDATA, 1);
		mUTIL.Broadcast(TRUE, &Konum[0], 1);
		mTRANSFER.B_AUTOBUFF1(0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = (mAVATAR_OBJECT[tUserIndex].mDATA.aMaxManaValue / 10);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(11, mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 2:
		if ((mGAME.mTickCount - mUSER[tUserIndex].AutoBuffTick) < 2)
		{
			return;
		}
		if (mUSER[tUserIndex].AutoBuff1 != 1)
		{
			return;
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort != 41)
		{
			return;
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 2)
		{
			return;
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 32)
		{
			return;
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aType != 0)
		{
			return;
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aType == 4)
		{
			return;
		}

		::memset(&tAction, 0, sizeof(ACTION_INFO));
		for (int i = 0; i < 8; i++)
		{
			tAction.aSkillNumber = mUSER[tUserIndex].mAvatarInfo.AutoBuffSmenu[i][0];
			tAction.aSkillGradeNum1 = mUSER[tUserIndex].mAvatarInfo.AutoBuffSmenu[i][1];
			tAction.aSkillGradeNum2 = mAVATAR_OBJECT[tUserIndex].GetBonusSkillValue(tAction.aSkillNumber);
			mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSkillNumber = tAction.aSkillNumber;
			mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSkillGradeNum1 = tAction.aSkillGradeNum1;
			mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSkillGradeNum2 = tAction.aSkillGradeNum2;
			mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSkillValue = 0;
			mAVATAR_OBJECT[tUserIndex].ProcessForCreateEffectValue(&tAction);
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort != 41)
		{
			mAVATAR_OBJECT[tUserIndex].ProcessForDeleteEffectValue();
			mUSER[tUserIndex].AutoBuff1 = 0;
			mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort = 1;
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			return;
		}
		mUSER[tUserIndex].AutoBuff1 = 0;
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort = 1;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		return;
	default:
		break;
	}
}
//W_CRAFT
void W_CRAFT(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	unsigned int tRandom = 0;
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];

	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}


	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];

	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	CopyMemory(&tPage1, &tPacket[1], 4);
	CopyMemory(&tIndex1, &tPacket[5], 4);
	CopyMemory(&tPage2, &tPacket[9], 4);
	CopyMemory(&tIndex2, &tPacket[13], 4);
	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	ITEM_INFO* tITEM_INFO1;
	ITEM_INFO* tITEM_INFO2;
	int tCost;
	int iValue;
	int tProbability1;
	int tProbability2;
	int tProtectIS = 0;
	int refinedegeri;
	int deger;

	if ((tPage1 == 1) || (tPage2 == 1))
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);

	if (tITEM_INFO1 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tITEM_INFO1->iType == 2 || tITEM_INFO1->iType == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
	if (tITEM_INFO2 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tITEM_INFO2->iIndex != 576) && (tITEM_INFO2->iIndex != 699) && (tITEM_INFO2->iIndex != 2395))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	switch (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0])
	{
	case 576:
		tCost = 50;
		iValue = 1;
		break;
	case 699:
	case 2395:
		tCost = 50;
		tRandom = rand() % 100;
		if (tRandom < 45)
		{
			iValue = 1;
		}
		else if (tRandom < 45)
		{
			iValue = 2;
		}
		else
		{
			iValue = 3;
		}
		break;
	}
	if (mUTIL.ReturnIBValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == 25)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	tProbability1 = 80 - ((mUTIL.ReturnIBValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] + iValue)) * 3) + (mAVATAR_OBJECT[tUserIndex].GetLuck() / 100);

	tProbability2 = -30 + ((mUTIL.ReturnIBValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] + iValue)) * 3);

	tRandom = rand();

	if (tRandom % 100 < tProbability1)//success
	{
		if (mUTIL.ReturnIBValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + iValue > 25) {

			iValue = 25 - mUTIL.ReturnIBValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
		}

		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= tCost;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeIBValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], iValue);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][4] = 0;
		mGAMELOG.GL_CRAFT_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUTIL.ReturnIBValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - iValue), mUTIL.ReturnIBValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]), "Döküm Başarılı");
		mTRANSFER.B_CRAFT_ITEM_RECV(0, tCost, iValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		if (mUTIL.ReturnIBValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) > 20) {
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			int DokumDeger;
			DokumDeger = mUTIL.ReturnIBValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
			tBroadcastInfoSort = 673;
			CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
			CopyMemory(&tBroadcastInfoData[4], &DokumDeger, 4);//Item
			CopyMemory(&tBroadcastInfoData[8], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
		}
		return;
	}
	//fail 
	if ((tRandom % 100) < tProbability2)
	{
		if (mUSER[tUserIndex].mAvatarInfo.PreServeCharm > 0)
		{
			mUSER[tUserIndex].mAvatarInfo.PreServeCharm--;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(63, mUSER[tUserIndex].mAvatarInfo.PreServeCharm);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			iValue = -1;
			if (mUTIL.ReturnIBValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) > 0)
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeIBValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], iValue);
			}
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= tCost;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][4] = 0;
			mGAMELOG.GL_CRAFT_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUTIL.ReturnIBValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - iValue), mUTIL.ReturnIBValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]), "Döküm Tılsımı Kullanıldı");
			mTRANSFER.B_CRAFT_ITEM_RECV(1, tCost, iValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= tCost;
		mGAMELOG.GL_CRAFT_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUTIL.ReturnIBValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - iValue), mUTIL.ReturnIBValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]), "Item Kırıldı");
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][4] = 0;

		mTRANSFER.B_CRAFT_ITEM_RECV(2, tCost, iValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	}

	iValue = -1;
	mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= tCost;
	if (mUTIL.ReturnIBValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) > 0)
	{
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeIBValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], iValue);
	}
	mGAMELOG.GL_CRAFT_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUTIL.ReturnIBValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] + iValue), mUTIL.ReturnIBValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]), "Döküm Baarısız");
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
	mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][0] = 0;
	mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][1] = 0;
	mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][2] = 0;
	mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][3] = 0;
	mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][4] = 0;
	mTRANSFER.B_CRAFT_ITEM_RECV(1, tCost, iValue);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	return;
}
//W_MUHAFIZ
void W_MUHAFIZ(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}
	return;
}
//W_GENERAL_NOTICE_SEND
void W_FUNCITON_NOTICE(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	char tContent[MAX_CHAT_CONTENT_LENGTH];
	CopyMemory(&tContent[0], &tPacket[1], MAX_CHAT_CONTENT_LENGTH);
	tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
	if (strcmp(tContent, "") == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (mUSER[tUserIndex].mAvatarInfo.FanctionNoticeScroll < 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	
	mUSER[tUserIndex].mAvatarInfo.FanctionNoticeScroll -= 1;
	int tSort;
	int index01;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	mTRANSFER.B_AVATAR_CHANGE_INFO_2(69, mUSER[tUserIndex].mAvatarInfo.FanctionNoticeScroll);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	tSort = 114;
	CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
	CopyMemory(&tData[MAX_AVATAR_NAME_LENGTH], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
	CopyMemory(&tData[(MAX_AVATAR_NAME_LENGTH + MAX_CHAT_CONTENT_LENGTH)], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
	mRELAY_COM.U_DEMAND_BROADCAST_DATA(tSort, &tData[0]);

}
//W_AUTOHUNT
void W_AUTOHUNT(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	CopyMemory(&mUSER[tUserIndex].mAvatarInfo.HunstStart, &tPacket[1], 4);
	CopyMemory(&mUSER[tUserIndex].mAvatarInfo.AutoHunt, &tPacket[5], sizeof(AUTO_HUNT));

	if (mUSER[tUserIndex].mAvatarInfo.Hunt5h < 0 && mUSER[tUserIndex].mAvatarInfo.Hunt7d < mUTIL.ReturnNowDate())
	{
		mUSER[tUserIndex].mAvatarInfo.Hunt5h = 0;
		mUSER[tUserIndex].mAvatarInfo.Hunt7d = 0;
		mUSER[tUserIndex].mAvatarInfo.HunstStart = 0;
		mAVATAR_OBJECT[tUserIndex].mDATA.BotOn = 0;
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (!mUTIL.CheckSkillNumber(tUserIndex))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if ((mUSER[tUserIndex].mAvatarInfo.HunstStart == 1))
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.BotOn = 1;
	}
	else
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.BotOn = 0;
	}

	mAVATAR_OBJECT[tUserIndex].AutoBuff();

	mTRANSFER.B_AUTOHUNT(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, mAVATAR_OBJECT[tUserIndex].mDATA.BotOn);
	if (mUSER[tUserIndex].mAvatarInfo.aVisibleState == 0)
	{
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}
	else
	{
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, tUserIndex, false);
	}

	return;
}
//HUNT
bool MyWork::SkillForMotion(int tUserIndex, ACTION_INFO* pAction, int tCheckMotion)
{
	switch (pAction->aSkillNumber) {
	case 6:
	case 25:
	case 44:
		return 40;
	case 7:
	case 26:
	case 45:
		pAction->aType = 0;
		pAction->aSort = 41;
		pAction->aFrame = 0.0f;
		pAction->aTargetLocation[0] = 0.0f;
		pAction->aTargetLocation[1] = 0.0f;
		pAction->aTargetLocation[2] = 0.0f;
		pAction->aTargetObjectSort = 0;
		pAction->aTargetObjectIndex = -1;
		pAction->aTargetObjectUniqueNumber = 0;
		pAction->aSkillValue = 0;
		return true;
	case 11:
	case 30:
	case 49:
		pAction->aType = mAVATAR_OBJECT[tUserIndex].GetWeaponClass() * 2 + 1;// - tCheckMotion;
		if (pAction->aType == 1)
			return false;
		pAction->aSort = 60;
		pAction->aFrame = 0.0f;
		pAction->aTargetLocation[0] = 0.0f;
		pAction->aTargetLocation[1] = 0.0f;
		pAction->aTargetLocation[2] = 0.0f;
		pAction->aTargetObjectSort = 0;
		pAction->aTargetObjectIndex = -1;
		pAction->aTargetObjectUniqueNumber = 0;
		pAction->aSkillValue = 0;
		return true;
	case 15:
	case 34:
	case 53:
		pAction->aType = mAVATAR_OBJECT[tUserIndex].GetWeaponClass() * 2 + 1;// - tCheckMotion;
		if (pAction->aType == 1)
			return false;
		pAction->aSort = 61;
		pAction->aFrame = 0.0f;
		pAction->aTargetLocation[0] = 0.0f;
		pAction->aTargetLocation[1] = 0.0f;
		pAction->aTargetLocation[2] = 0.0f;
		pAction->aTargetObjectSort = 0;
		pAction->aTargetObjectIndex = -1;
		pAction->aTargetObjectUniqueNumber = 0;
		pAction->aSkillValue = 0;
		return true;
	case 19:
	case 38:
	case 57:
		pAction->aType = mAVATAR_OBJECT[tUserIndex].GetWeaponClass() * 2 + 1;// - tCheckMotion;
		if (pAction->aType == 1)
			return false;
		pAction->aSort = 62;
		pAction->aFrame = 0.0f;
		pAction->aTargetLocation[0] = 0.0f;
		pAction->aTargetLocation[1] = 0.0f;
		pAction->aTargetLocation[2] = 0.0f;
		pAction->aTargetObjectSort = 0;
		pAction->aTargetObjectIndex = -1;
		pAction->aTargetObjectUniqueNumber = 0;
		pAction->aSkillValue = 0;
		return true;
	case 82:
		pAction->aType = 0;
		pAction->aSort = 66;
		pAction->aFrame = 0.0f;
		pAction->aTargetLocation[0] = 0.0f;
		pAction->aTargetLocation[1] = 0.0f;
		pAction->aTargetLocation[2] = 0.0f;
		pAction->aTargetObjectSort = 0;
		pAction->aTargetObjectIndex = -1;
		pAction->aTargetObjectUniqueNumber = 0;
		pAction->aSkillValue = 0;
		return true;
	case 83:
		pAction->aType = 0;
		pAction->aSort = 67;
		pAction->aFrame = 0.0f;
		pAction->aTargetLocation[0] = 0.0f;
		pAction->aTargetLocation[1] = 0.0f;
		pAction->aTargetLocation[2] = 0.0f;
		pAction->aTargetObjectSort = 0;
		pAction->aTargetObjectIndex = -1;
		pAction->aTargetObjectUniqueNumber = 0;
		pAction->aSkillValue = 0;
		return true;
	case 84:
		pAction->aType = 0;
		pAction->aSort = 68;
		pAction->aFrame = 0.0f;
		pAction->aTargetLocation[0] = 0.0f;
		pAction->aTargetLocation[1] = 0.0f;
		pAction->aTargetLocation[2] = 0.0f;
		pAction->aTargetObjectSort = 0;
		pAction->aTargetObjectIndex = -1;
		pAction->aTargetObjectUniqueNumber = 0;
		pAction->aSkillValue = 0;
		return true;
	case 103:
	case 104:
	case 105:
		pAction->aType = 0;
		pAction->aSort = 75;
		pAction->aFrame = 0.0f;
		pAction->aTargetLocation[0] = 0.0f;
		pAction->aTargetLocation[1] = 0.0f;
		pAction->aTargetLocation[2] = 0.0f;
		pAction->aTargetObjectSort = 0;
		pAction->aTargetObjectIndex = -1;
		pAction->aTargetObjectUniqueNumber = 0;
		pAction->aSkillValue = 0;
		return true;
	default:
		return false;
	}

	return false;
}
bool MyWork::ReturnEffectState(int tUserIndex, int tSkillNumber)
{
	switch (tSkillNumber) {
#if 0
	case 6:
	case 25:
	case 44:
		if (mUSER[tUserIndex].mEffectValue[8][0] == 0)
			return true;
		break;
#endif
	case 7:
	case 26:
	case 45:
		if (mUSER[tUserIndex].mEffectValue[4][0] == 0)
			return true;
		break;
	case 11:
	case 34:
	case 49:
		if (mUSER[tUserIndex].mEffectValue[1][0] == 0)
			return true;
		break;
	case 15:
	case 30:
	case 53:
		if (mUSER[tUserIndex].mEffectValue[0][0] == 0)
			return true;
		break;
	case 19:
	case 38:
	case 57:
		if ((mUSER[tUserIndex].mEffectValue[3][0] == 0)
			|| (mUSER[tUserIndex].mEffectValue[7][0] == 0))
			return true;
		break;
	case 82:
		if (mUSER[tUserIndex].mEffectValue[9][0] == 0)
			return true;
		break;
	case 83:
		if (mUSER[tUserIndex].mEffectValue[10][0] == 0)
			return true;
		break;
	case 84:
		if (mUSER[tUserIndex].mEffectValue[11][0] == 0)
			return true;
		break;
	case 103:
		if (mUSER[tUserIndex].mEffectValue[12][0] == 0)
			return true;
		break;
	case 104:
		if (mUSER[tUserIndex].mEffectValue[13][0] == 0)
			return true;
		break;
	case 105:
		if (mUSER[tUserIndex].mEffectValue[14][0] == 0)
			return true;
		break;
	default:
		return false;
	}
	return false;
}
//DAILY_MISSION
void W_DAILY_MISSION(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	int tSort;
	CopyMemory(&tSort, &tPacket[1], 4);
	int tRandomValue;
	int tValue;

	ITEM_INFO* pItemInfo = NULL;
	int iPage = 0, iInvenIndex = 0, iInvenSlot = 0;

	switch (tSort)
	{
	case 1:
		mTRANSFER.B_DAILY_MISSION(tSort, 0, mUSER[tUserIndex].mAvatarInfo.JoinWar, mUSER[tUserIndex].mAvatarInfo.PlayerKill, mUSER[tUserIndex].mAvatarInfo.MonsterKill, mUSER[tUserIndex].mAvatarInfo.PlayTimeDay);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		break;
	case 2:
		//Lotus Alliance - Daily mission reward can only be claimed once per day.
		/*if (mUSER[tUserIndex].mAuthInfo.DailyRewardTime >= mUTIL.ReturnNowDate())
		{
			mTRANSFER.B_DAILY_MISSION(1, 1, mUSER[tUserIndex].mAvatarInfo.JoinWar, mUSER[tUserIndex].mAvatarInfo.PlayerKill, mUSER[tUserIndex].mAvatarInfo.MonsterKill, mUSER[tUserIndex].mAvatarInfo.PlayTimeDay);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			
			return;
		}*/
		/*if (mUSER[tUserIndex].mAvatarInfo.JoinWar != 3)
		{
			mTRANSFER.B_DAILY_MISSION(tSort, 2, mUSER[tUserIndex].mAvatarInfo.JoinWar, mUSER[tUserIndex].mAvatarInfo.PlayerKill, mUSER[tUserIndex].mAvatarInfo.MonsterKill, mUSER[tUserIndex].mAvatarInfo.PlayTimeDay);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}*/
		if (mUSER[tUserIndex].mAvatarInfo.PlayerKill != 10)
		{
			mTRANSFER.B_DAILY_MISSION(tSort, 2, mUSER[tUserIndex].mAvatarInfo.JoinWar, mUSER[tUserIndex].mAvatarInfo.PlayerKill, mUSER[tUserIndex].mAvatarInfo.MonsterKill, mUSER[tUserIndex].mAvatarInfo.PlayTimeDay);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.MonsterKill != 1000)
		{
			mTRANSFER.B_DAILY_MISSION(tSort, 2, mUSER[tUserIndex].mAvatarInfo.JoinWar, mUSER[tUserIndex].mAvatarInfo.PlayerKill, mUSER[tUserIndex].mAvatarInfo.MonsterKill, mUSER[tUserIndex].mAvatarInfo.PlayTimeDay);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.PlayTimeDay != 60)
		{
			mTRANSFER.B_DAILY_MISSION(tSort, 2, mUSER[tUserIndex].mAvatarInfo.JoinWar, mUSER[tUserIndex].mAvatarInfo.PlayerKill, mUSER[tUserIndex].mAvatarInfo.MonsterKill, mUSER[tUserIndex].mAvatarInfo.PlayTimeDay);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}


		//Daily Mission Reward
		  
		tRandomValue = rand() % 12;
		switch (tRandomValue) {
		case 0:
			tValue = 1190;		// x2 Exp Pet
			break;
		case 1:
			tValue = 1167;		// Gold Plate Scroll
			break;
		case 2:
			tValue = 1166;		// CP PC
			break;
		case 3:
			tValue = 1216;		// ABS 1 day
			break;
		case 4:
			tValue = 602;		// Pet Box
			break;
		case 5:
			tValue = 601;		// Mount Box
			break;
		case 6:
			tValue = 506;		// Vit Elix
			break;
		case 7:
			tValue = 508;		// Str Elix
			break;
		case 8:
			tValue = 509;		// Dex Elix
			break;
		case 9:
			tValue = 1438;		// Green Pill(M)
			break;
		case 10:
			tValue = 1439;		// Green Pill(S)
			break;
		case 11:
			switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe) {
			case 0:
				tValue = 594;	// Guanyin Orange Glasses Deco
				break;
			case 1:
				tValue = 595;	// Fujin Orange Glasses Deco
				break; 
			case 2:
				tValue = 596;	// Jinong Orange Glasses Deco
				break;
			}
			break;
		

		}




		//tRandomValue = rand() % 1000;
		//if (tRandomValue < 70)
		//{
		//	//tValue = 2448;//Diamond Package
		//	tValue = 1447;//1k cp
		//}
		//else if (tRandomValue < 140)
		//{
		//	tValue = 601;// MountBox t
		//}
		//else if (tRandomValue < 210) // bebe
		//{
		//	tValue = 984;// Beyaz Birleştirme t
		//}
		//else if (tRandomValue < 280)
		//{
		//	tValue = 1491;// %3 PET  t
		//}
		//else if (tRandomValue < 350)
		//{
		//	tValue = 1227;// Warrior Scroll t
		//}
		//else if (tRandomValue < 420)
		//{
		//	tValue = 1437;//Asırlık Altın t
		//}
		//else if (tRandomValue < 490)
		//{
		//	tValue = 1124;//Ferman t
		//}
		//else if (tRandomValue < 560)
		//{
		//	tValue = 1118;//Scroll of Loyalty t
		//}
		//else if (tRandomValue < 630)
		//{
		//	//tValue = 1449;//100 CP ticket t
		//	tValue = 1448;//500 CP ticket t
		//}
		//else if (tRandomValue < 700)
		//{
		//	tValue = 1455;//Kabuk t
		//}
		//else if (tRandomValue < 770)
		//{
		//	tValue = 2249;//capebox t 
		//}
		//else if (tRandomValue < 840)
		//{

		//	tValue = 1073;//500m t
		//}
		//else if (tRandomValue < 910)
		//{
		//	tValue = 1166;//Aff t
		//}
		//else
		//{
		//	tValue = 602;//pet box t
		//}
		pItemInfo = mITEM.Search(tValue);
		if (pItemInfo != NULL)
		{
			if (mUTIL.FindEmptyInvenForItem(tUserIndex, pItemInfo, iPage, iInvenIndex) == true)
			{
				iInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, iPage);
				if (iInvenSlot != -1)
				{
					mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = pItemInfo->iIndex;
					mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
					mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
					mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 0;
					mTRANSFER.B_ITEM_SEND(0, pItemInfo->iIndex, iPage, iInvenSlot, iInvenIndex);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				else
				{
					mTRANSFER.B_DAILY_MISSION(tSort, 3, mUSER[tUserIndex].mAvatarInfo.JoinWar, mUSER[tUserIndex].mAvatarInfo.PlayerKill, mUSER[tUserIndex].mAvatarInfo.MonsterKill, mUSER[tUserIndex].mAvatarInfo.PlayTimeDay);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					return;
				}
			}
			else
			{
				mTRANSFER.B_DAILY_MISSION(tSort, 3, mUSER[tUserIndex].mAvatarInfo.JoinWar, mUSER[tUserIndex].mAvatarInfo.PlayerKill, mUSER[tUserIndex].mAvatarInfo.MonsterKill, mUSER[tUserIndex].mAvatarInfo.PlayTimeDay);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			mUSER[tUserIndex].mAuthInfo.DailyRewardTime = mUTIL.ReturnNowDate(); // Daily Mission Time
			mUSER[tUserIndex].mAvatarInfo.JoinWar = 0;
			mUSER[tUserIndex].mAvatarInfo.PlayerKill = 0;
			mUSER[tUserIndex].mAvatarInfo.MonsterKill = 0;
			mUSER[tUserIndex].mAvatarInfo.PlayTimeDay = 0;
			mGAMELOG.GL_DAILY_ITEM(tUserIndex, pItemInfo->iIndex, pItemInfo->iName);
			mTRANSFER.B_DAILY_MISSION(tSort, 0, mUSER[tUserIndex].mAvatarInfo.JoinWar, mUSER[tUserIndex].mAvatarInfo.PlayerKill, mUSER[tUserIndex].mAvatarInfo.MonsterKill, mUSER[tUserIndex].mAvatarInfo.PlayTimeDay);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			break;
		}
		else {
			mUSER[tUserIndex].mAvatarInfo.JoinWar = 0;
			mUSER[tUserIndex].mAvatarInfo.PlayerKill = 10;
			mUSER[tUserIndex].mAvatarInfo.MonsterKill = 1000;
			mUSER[tUserIndex].mAvatarInfo.PlayTimeDay = 60;
			//mGAMELOG.GL_DAILY_ITEM(tUserIndex, pItemInfo->iIndex, pItemInfo->iName);
			mTRANSFER.B_DAILY_MISSION(tSort, 0, mUSER[tUserIndex].mAvatarInfo.JoinWar, mUSER[tUserIndex].mAvatarInfo.PlayerKill, mUSER[tUserIndex].mAvatarInfo.MonsterKill, mUSER[tUserIndex].mAvatarInfo.PlayTimeDay);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		break;
	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}
//W_PET_COMBINE_SEND
void W_PET_COMBINE_SEND(int tUserIndex)
{
	unsigned int tRandom = 0;
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit();
		return;
	}

	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	BYTE tData[MAX_BROADCAST_DATA_SIZE];
	int tSort;
	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	int tPage3;
	int tIndex3;
	int tPage4;
	int tIndex4;
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tPage1, &tPacket[5], 4);
	CopyMemory(&tIndex1, &tPacket[9], 4);
	CopyMemory(&tPage2, &tPacket[13], 4);
	CopyMemory(&tIndex2, &tPacket[17], 4);
	CopyMemory(&tPage3, &tPacket[21], 4);
	CopyMemory(&tIndex3, &tPacket[25], 4);
	CopyMemory(&tPage4, &tPacket[29], 4);
	CopyMemory(&tIndex4, &tPacket[33], 4);

	int tRandomNumber;
	int tValue[6];
	int tValue2[6];
	int tValue3[6];
	int tValue4[6];
	int ivenindex[3];
	int a;
	int b;
	int c;
	int CP;
	ITEM_INFO* item1;
	ITEM_INFO* item2;
	ITEM_INFO* item3;
	ITEM_INFO* item4;
	ITEM_INFO* item5;
	switch (tSort)
	{
	case 0:
		if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage3 < 0) || (tPage3 > 1) || (tIndex3 < 0) || (tIndex3 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage4 < 0) || (tPage4 > 1) || (tIndex4 < 0) || (tIndex4 > (MAX_INVENTORY_SLOT_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tPage1 == 1) || (tPage2 == 1) || (tPage3 == 1) || (tPage4 == 1))
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] == 1002) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] == 1003) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] == 1004) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] == 1005))
		{
			a = 1;
		}
		if ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] == 1002) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] == 1003) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] == 1004) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] == 1005))
		{
			b = 2;
		}
		if ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] == 1002) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] == 1003) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] == 1004) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] == 1005))
		{
			c = 3;
		}
		if ((a != 1) || (b != 2) || (c != 3) || (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 1235))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		tRandom = rand() % 100;
		if (tRandom < 45)
		{
			tValue[0] = 0;
			tValue[1] = 0;
			tValue[2] = 0;
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] = 0;
			mTRANSFER.B_MAKE_ITEM_RECV(-1, &tValue[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			ivenindex[0] = ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] * 8) + mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1]);
			ivenindex[1] = ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] * 8) + mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1]);
			ivenindex[2] = ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][2] * 8) + mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][1]);
			mTRANSFER.B_ITEM_SEND(0, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], tPage1, tIndex1, ivenindex[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mTRANSFER.B_ITEM_SEND(0, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0], tPage2, tIndex2, ivenindex[1]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mTRANSFER.B_ITEM_SEND(0, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0], tPage3, tIndex3, ivenindex[2]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tRandom = rand();
		switch ((tRandom % 6))
		{
		case 0:
			tValue[0] = 1006;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = mUTIL.ReturnItemRecognitionNumber(0);
			break;
		case 1:
			tValue[0] = 1007;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = mUTIL.ReturnItemRecognitionNumber(0);
			break;
		case 2:
			tValue[0] = 1008;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = mUTIL.ReturnItemRecognitionNumber(0);
			break;
		case 3:
			tValue[0] = 1009;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = mUTIL.ReturnItemRecognitionNumber(0);
			break;
		case 4:
			tValue[0] = 1010;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = mUTIL.ReturnItemRecognitionNumber(0);
			break;
		case 5:
			tValue[0] = 1011;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = mUTIL.ReturnItemRecognitionNumber(0);
			break;
		}

		item1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
		item2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
		item3 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0]);
		item4 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0]);
		item5 = mITEM.Search(tValue[0]);
	
		
		sprintf((char*)&tData[0], "[%s] just crafted '%s'", &mUSER[tUserIndex].mAvatarInfo.aName[0], item5->iName);
		mRELAY_COM.U_DEMAND_BROADCAST_DATA(102, &tData[0]);



		mGAMELOG.GL_PETCOMBINE_ITEM(tUserIndex, item1->iIndex, item1->iName, item2->iIndex, item2->iName, item3->iIndex, item3->iName, item4->iIndex, item4->iName, item5->iIndex, item5->iName);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] = 0;
		mTRANSFER.B_PET_COMBINE(0, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		
		return;

	case 1:
		if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage3 < 0) || (tPage3 > 1) || (tIndex3 < 0) || (tIndex3 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage4 < 0) || (tPage4 > 1) || (tIndex4 < 0) || (tIndex4 > (MAX_INVENTORY_SLOT_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tPage1 == 1) || (tPage2 == 1) || (tPage3 == 1) || (tPage4 == 1))
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] == 1006) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] == 1007) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] == 1008) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] == 1009) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] == 1010) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] == 1011))
		{
			a = 1;
		}
		if ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] == 1006) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] == 1007) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] == 1008) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] == 1009) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] == 1010) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] == 1011))
		{
			b = 2;
		}
		if ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] == 1006) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] == 1007) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] == 1008) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] == 1009) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] == 1010) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] == 1011))
		{
			c = 3;
		}
		if ((a != 1) || (b != 2) || (c != 3) || (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] != 1235))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tRandom = rand() % 100;
		if (tRandom < 31)
		{
			tValue[0] = 0;
			tValue[1] = 0;
			tValue[2] = 0;
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] = 0;
			mTRANSFER.B_MAKE_ITEM_RECV(-1, &tValue[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			ivenindex[0] = ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] * 8) + mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1]);
			ivenindex[1] = ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] * 8) + mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1]);
			ivenindex[2] = ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][2] * 8) + mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][1]);
			mTRANSFER.B_ITEM_SEND(0, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], tPage1, tIndex1, ivenindex[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mTRANSFER.B_ITEM_SEND(0, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0], tPage2, tIndex2, ivenindex[1]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mTRANSFER.B_ITEM_SEND(0, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0], tPage3, tIndex3, ivenindex[2]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tRandom = rand() % 1000;
		if (tRandom < 5) {
			if(mUSER[tUserIndex].mAvatarInfo.aLevel1>135){
				tValue[0] = 1016;
				tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
				tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
				tValue[3] = 0;
				tValue[4] = 0;
				tValue[5] = mUTIL.ReturnItemRecognitionNumber(0);
			}
			else {
				tValue[0] = 1012;
				tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
				tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
				tValue[3] = 0;
				tValue[4] = 0;
				tValue[5] = mUTIL.ReturnItemRecognitionNumber(0);
			}
		}
		else if (tRandom < 70) {
			tValue[0] = 1012;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = mUTIL.ReturnItemRecognitionNumber(0);
		}
		else {
			tRandom = rand();
			switch ((tRandom % 3))
			{
			case 0:
				tValue[0] = 1013;
				tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
				tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
				tValue[3] = 0;
				tValue[4] = 0;
				tValue[5] = mUTIL.ReturnItemRecognitionNumber(0);
				break;
			case 1:
				tValue[0] = 1014;
				tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
				tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
				tValue[3] = 0;
				tValue[4] = 0;
				tValue[5] = mUTIL.ReturnItemRecognitionNumber(0);
				break;
			case 2:
				tValue[0] = 1015;
				tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
				tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
				tValue[3] = 0;
				tValue[4] = 0;
				tValue[5] = mUTIL.ReturnItemRecognitionNumber(0);
				break;
			}
		}
		item1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
		item2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
		item3 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0]);
		item4 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0]);
		item5 = mITEM.Search(tValue[0]);

		sprintf((char*)&tData[0], "[%s] just crafted '%s'", &mUSER[tUserIndex].mAvatarInfo.aName[0], item5->iName);
		mRELAY_COM.U_DEMAND_BROADCAST_DATA(102, &tData[0]);

		mGAMELOG.GL_PETCOMBINE_ITEM(tUserIndex, item1->iIndex, item1->iName, item2->iIndex, item2->iName, item3->iIndex, item3->iName, item4->iIndex, item4->iName, item5->iIndex, item5->iName);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] = 0;
		mTRANSFER.B_PET_COMBINE(0, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}