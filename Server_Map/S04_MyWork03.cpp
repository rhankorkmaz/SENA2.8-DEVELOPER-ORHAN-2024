//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "Shengming.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_WORK
//-------------------------------------------------------------------------------------------------
#define USER_SEND() {\
	if(type == 0) {\
		mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );\
	} else if(type == 1) {\
		mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal_C[0], mTRANSFER.mOriginalSize_C );\
	} else if(type == 2) {\
		mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal_R[0], mTRANSFER.mOriginalSize_R );\
	}\
}
void MyWork::ProcessForRelay(int tSort, BYTE tData[MAX_BROADCAST_DATA_SIZE], int type)
{
	int index01;
	char tContent[MAX_CHAT_CONTENT_LENGTH];
	//int tUserSort;
	BYTE tAuthType;
	int tTribe;
	int tPartyMoveZone = 1;
#ifdef __PARTY_BUG_FIX__
	party_check_t PartyCheck;
	::memset(&PartyCheck, 0, sizeof(party_check_t));
#endif
	char tPartyName[MAX_PARTY_NAME_LENGTH];
	char tGuildName[MAX_GUILD_NAME_LENGTH];
	char tAvatarName01[MAX_AVATAR_NAME_LENGTH];
	char tAvatarName02[MAX_AVATAR_NAME_LENGTH];
	char tAvatarName03[MAX_AVATAR_NAME_LENGTH];
	char tAvatarName04[MAX_AVATAR_NAME_LENGTH];
	char tAvatarName05[MAX_AVATAR_NAME_LENGTH];
	switch (tSort)
	{
	case 101: //[NOTICE]<-[TOOL]

		//LOG_TO_FILE("---> notice gec\n");

		CopyMemory(&tContent[0], &tData[0], MAX_CHAT_CONTENT_LENGTH);
		tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
		CopyMemory(&tTribe, &tData[MAX_CHAT_CONTENT_LENGTH], 4);
		mTRANSFER.B_GENERAL_NOTICE_RECV(&tContent[0], type);
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (tTribe == 0)
			{
				USER_SEND();
			}
			else
			{
				if (mAVATAR_OBJECT[index01].mDATA.aTribe == (tTribe - 1))
				{
					USER_SEND();
				}
			}
		}
		return;
	case 102: //[NOTICE]<-[GM]
		CopyMemory(&tContent[0], &tData[0], MAX_CHAT_CONTENT_LENGTH);
		tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
		mTRANSFER.B_GENERAL_NOTICE_RECV(&tContent[0], type);
		if (strcmp(tContent, "%%Shutdown") == 0)
		{
			mCENTER_COM.W_SHUTDOWN();
		}
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			USER_SEND();
		}
		return;
	case 103: //[SECRET_CHAT]
		CopyMemory(&tAvatarName01[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName01[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName02[0], &tData[MAX_AVATAR_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
		tAvatarName02[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tContent[0], &tData[(MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH)], MAX_CHAT_CONTENT_LENGTH);
		tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
		CopyMemory(&tAuthType, &tData[(MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_CHAT_CONTENT_LENGTH)], 1);
		mTRANSFER.B_SECRET_CHAT_RECV(3, 0, &tAvatarName01[0], &tContent[0], tAuthType, type);
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (strcmp(mUSER[index01].mAvatarInfo.aName, tAvatarName02) == 0)
			{
				USER_SEND();
				return;
			}
		}
		return;
	case 104: //[PARTY_JOIN]
		CopyMemory(&tPartyName[0], &tData[0], MAX_PARTY_NAME_LENGTH);
		tPartyName[(MAX_PARTY_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName01[0], &tData[MAX_PARTY_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
		tAvatarName01[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		mTRANSFER.B_PARTY_JOIN_RECV(tAvatarName01, type);

		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}

			if (strcmp(mUSER[index01].mAvatarInfo.aName, tAvatarName01) == 0)
			{
				continue;
			}

			if (strcmp(mAVATAR_OBJECT[index01].mDATA.aPartyName, tPartyName) == 0)
			{
				for (int i = 0; i < 5; i++)
				{
					if (strcmp(mUSER[index01].mAvatarInfo.aPartyName[i], "") == 0)
					{
						strncpy(mUSER[index01].mAvatarInfo.aPartyName[i], tAvatarName01, MAX_AVATAR_NAME_LENGTH);
						break;
					}
				}

				USER_SEND();
			}
		}
		return;
	case 105: //[PARTY_CHAT]
		CopyMemory(&tPartyName[0], &tData[0], MAX_PARTY_NAME_LENGTH);
		tPartyName[(MAX_PARTY_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName01[0], &tData[MAX_PARTY_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
		tAvatarName01[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tContent[0], &tData[(MAX_PARTY_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH)], MAX_CHAT_CONTENT_LENGTH);
		tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
		mTRANSFER.B_PARTY_CHAT_RECV(&tAvatarName01[0], &tContent[0], type);
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (strcmp(mAVATAR_OBJECT[index01].mDATA.aPartyName, tPartyName) == 0)
			{
				USER_SEND();
			}

		}
		return;
	case 106: //[PARTY_LEAVE]
		CopyMemory(&tPartyName[0], &tData[0], MAX_PARTY_NAME_LENGTH);
		tPartyName[(MAX_PARTY_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName01[0], &tData[MAX_PARTY_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
		tAvatarName01[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		mTRANSFER.B_PARTY_LEAVE_RECV(tAvatarName01, type);
		tPartyMoveZone = 1;
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}

			if (strcmp(mAVATAR_OBJECT[index01].mDATA.aPartyName, tPartyName) == 0)
			{
				for (int i = 0; i < 5; i++)
				{
					if (strcmp(mUSER[index01].mAvatarInfo.aPartyName[i], tAvatarName01) == 0)
					{
						for (int y = i; y < 5; y++)
						{
							if (y < 4)
							{
								strncpy(mUSER[index01].mAvatarInfo.aPartyName[y], mUSER[index01].mAvatarInfo.aPartyName[y + 1], MAX_AVATAR_NAME_LENGTH);
							}
							else
							{
								strncpy(mUSER[index01].mAvatarInfo.aPartyName[y], "", MAX_AVATAR_NAME_LENGTH);
							}
						}
					}
				}
				USER_SEND();
			}

			if (strcmp(mUSER[index01].mAvatarInfo.aName, tAvatarName01) == 0)
			{
				for (int i = 0; i < 5; i++)
				{
					strncpy(mUSER[index01].mAvatarInfo.aPartyName[i], "", MAX_AVATAR_NAME_LENGTH);
				}
				strncpy(mAVATAR_OBJECT[index01].mDATA.aPartyName, "", MAX_AVATAR_NAME_LENGTH);
			}
		}
#ifdef __PARTY_BUG_FIX__
		if (tPartyMoveZone) {
			::strncpy(PartyCheck.aName, tAvatarName01, MAX_AVATAR_NAME_LENGTH);
			PartyCheck.tSort = tSort;
			PartyCheck.RegDateTime = ::time(NULL);
			mGAME.map_party_check.insert(pair<string, party_check_t>(tPartyName, PartyCheck));
			//LOG_TO_FILE_4("----> insert : %d %s %s %lu\n", tSort, tPartyName, PartyCheck.aName, PartyCheck.RegDateTime);
			}
#endif
		return;
	case 107: //[PARTY_EXILE]
		CopyMemory(&tPartyName[0], &tData[0], MAX_PARTY_NAME_LENGTH);
		tPartyName[(MAX_PARTY_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName01[0], &tData[MAX_PARTY_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
		tAvatarName01[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		mTRANSFER.B_PARTY_EXILE_RECV(tAvatarName01, type);
		tPartyMoveZone = 1;
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}

			if (strcmp(mAVATAR_OBJECT[index01].mDATA.aPartyName, tPartyName) == 0)
			{
				for (int i = 0; i < 5; i++)
				{
					if (strcmp(mUSER[index01].mAvatarInfo.aPartyName[i], tAvatarName01) == 0)
					{
						for (int y = i; y < 5; y++)
						{
							if (y < 4)
							{
								strncpy(mUSER[index01].mAvatarInfo.aPartyName[y], mUSER[index01].mAvatarInfo.aPartyName[y + 1], MAX_AVATAR_NAME_LENGTH);
							}
							else
							{
								strncpy(mUSER[index01].mAvatarInfo.aPartyName[y], "", MAX_AVATAR_NAME_LENGTH);
							}
						}
					}
				}
				USER_SEND();
			}

			if (strcmp(mUSER[index01].mAvatarInfo.aName, tAvatarName01) == 0)
			{
				for (int i = 0; i < 5; i++)
				{
					strncpy(mUSER[index01].mAvatarInfo.aPartyName[i], "", MAX_AVATAR_NAME_LENGTH);
				}
				strncpy(mAVATAR_OBJECT[index01].mDATA.aPartyName, "", MAX_AVATAR_NAME_LENGTH);
			}
		}
#ifdef __PARTY_BUG_FIX__
		if (tPartyMoveZone) {
			::strncpy(PartyCheck.aName, tAvatarName01, MAX_AVATAR_NAME_LENGTH);
			PartyCheck.tSort = tSort;
			PartyCheck.RegDateTime = ::time(NULL);
			mGAME.map_party_check.insert(pair<string, party_check_t>(tPartyName, PartyCheck));
			//LOG_TO_FILE_4("----> insert : %d %s %s %lu\n", tSort, tPartyName, PartyCheck.aName, PartyCheck.RegDateTime);
		}
#endif
		return;
	case 108: //[PARTY_INFO]
		return;
	case 109: //[PARTY_BREAK]
		CopyMemory(&tPartyName[0], &tData[0], MAX_PARTY_NAME_LENGTH);
		tPartyName[(MAX_PARTY_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName01[0], &tData[MAX_PARTY_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
		tAvatarName01[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		strcpy(tAvatarName02, "");
		tPartyMoveZone = 1;

		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}

			if (strcmp(mAVATAR_OBJECT[index01].mDATA.aPartyName, tPartyName) == 0)
			{
				if (strcmp(mUSER[index01].mAvatarInfo.aPartyName[0], mUSER[index01].mAvatarInfo.aName) == 0) //Parti Başkanıysa
				{
					mTRANSFER.B_PARTY_BREAK_RECV(1, tAvatarName02, type);
					for (int y = 0; y < 5; y++)
					{
						strncpy(mUSER[index01].mAvatarInfo.aPartyName[y], "", MAX_PARTY_NAME_LENGTH);
					}
					strncpy(mAVATAR_OBJECT[index01].mDATA.aPartyName, "", MAX_AVATAR_NAME_LENGTH);
					USER_SEND();
				}
				else
				{
					for (int i = 1; i < 5; i++)
					{
						mTRANSFER.B_PARTY_BREAK_RECV(3, tAvatarName01, type);
						strncpy(mUSER[index01].mAvatarInfo.aPartyName[i - 1], mUSER[index01].mAvatarInfo.aPartyName[i], MAX_PARTY_NAME_LENGTH);
					}
					strncpy(mUSER[index01].mAvatarInfo.aPartyName[4], "", MAX_PARTY_NAME_LENGTH);
					strncpy(mAVATAR_OBJECT[index01].mDATA.aPartyName, mUSER[index01].mAvatarInfo.aPartyName[0], MAX_AVATAR_NAME_LENGTH);
					USER_SEND();
				}
				mAVATAR_OBJECT[index01].mPartyProcessState = 0;
			}
		}
#ifdef __PARTY_BUG_FIX__
		if (tPartyMoveZone) {
			::strncpy(PartyCheck.aName, tAvatarName01, MAX_AVATAR_NAME_LENGTH);
			PartyCheck.tSort = tSort;
			PartyCheck.RegDateTime = ::time(NULL);
			mGAME.map_party_check.insert(pair<string, party_check_t>(tPartyName, PartyCheck));
			//LOG_TO_FILE_4("----> insert : %d %s %s %lu\n", tSort, tPartyName, PartyCheck.aName, PartyCheck.RegDateTime);
		}
#endif
		return;
	case 110: //[GUILD_LOGIN]
		CopyMemory(&tGuildName[0], &tData[0], MAX_GUILD_NAME_LENGTH);
		tGuildName[(MAX_GUILD_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName01[0], &tData[MAX_GUILD_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
		tAvatarName01[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		mTRANSFER.B_GUILD_LOGIN_INFO(&tAvatarName01[0], type);
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (strcmp(mUSER[index01].mAvatarInfo.aGuildName, tGuildName) == 0)
			{
				USER_SEND();
			}
		}
		return;
	case 111: //[GUILD_NOTICE]
		CopyMemory(&tGuildName[0], &tData[0], MAX_GUILD_NAME_LENGTH);
		tGuildName[(MAX_GUILD_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName01[0], &tData[MAX_GUILD_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
		tAvatarName01[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tContent[0], &tData[(MAX_GUILD_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH)], MAX_CHAT_CONTENT_LENGTH);
		tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
		mTRANSFER.B_GUILD_NOTICE_RECV(&tAvatarName01[0], &tContent[0], type);
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (strcmp(mUSER[index01].mAvatarInfo.aGuildName, tGuildName) == 0)
			{
				USER_SEND();
			}
		}
		return;
	case 112: //[GUILD_CHAT]
		CopyMemory(&tGuildName[0], &tData[0], MAX_GUILD_NAME_LENGTH);
		tGuildName[(MAX_GUILD_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName01[0], &tData[MAX_GUILD_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
		tAvatarName01[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tContent[0], &tData[(MAX_GUILD_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH)], MAX_CHAT_CONTENT_LENGTH);
		tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
		mTRANSFER.B_GUILD_CHAT_RECV(&tAvatarName01[0], &tContent[0], type);
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (strcmp(mUSER[index01].mAvatarInfo.aGuildName, tGuildName) == 0)
			{
				USER_SEND();
			}
		}
		return;
	case 113: //[TRIBE_NOTICE]
		CopyMemory(&tAvatarName01[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName01[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tContent[0], &tData[MAX_AVATAR_NAME_LENGTH], MAX_CHAT_CONTENT_LENGTH);
		tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
		CopyMemory(&tTribe, &tData[(MAX_AVATAR_NAME_LENGTH + MAX_CHAT_CONTENT_LENGTH)], 4);

		if (mGAME.ReturnTribeRole(tAvatarName01, tTribe) == 1)
		{
			tSort = 1;
		}
		else
		{
			tSort = 2;
		}

		mTRANSFER.B_TRIBE_NOTICE_RECV(tSort, &tAvatarName01[0], &tContent[0], type);
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (mAVATAR_OBJECT[index01].mDATA.aTribe == tTribe)
			{

				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
		}
		return;
	case 114: //[FACTION_NOTICE]
		CopyMemory(&tAvatarName01[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName01[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tContent[0], &tData[MAX_AVATAR_NAME_LENGTH], MAX_CHAT_CONTENT_LENGTH);
		tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
		CopyMemory(&tTribe, &tData[(MAX_AVATAR_NAME_LENGTH + MAX_CHAT_CONTENT_LENGTH)], 4);

		mTRANSFER.B_FUNCITON_NOTICE(tTribe, &tAvatarName01[0], &tContent[0]);
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (mAVATAR_OBJECT[index01].mDATA.aTribe == tTribe)
			{

				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
		}
		return;
	case 115: //When you write in the general chat, it sends to everyone in my tribe. (GM)
		CopyMemory(&tAvatarName01[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName01[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tContent[0], &tData[MAX_AVATAR_NAME_LENGTH], MAX_CHAT_CONTENT_LENGTH);
		tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
		CopyMemory(&tTribe, &tData[(MAX_AVATAR_NAME_LENGTH + MAX_CHAT_CONTENT_LENGTH)], 4);

		mTRANSFER.B_FUNCITON_NOTICE(tTribe, &tAvatarName01[0], &tContent[0]);

		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			
			mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}

		return;
	case 116: //When you write in the general chat, it sends to everyone in my tribe
		CopyMemory(&tAvatarName01[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName01[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tContent[0], &tData[MAX_AVATAR_NAME_LENGTH], MAX_CHAT_CONTENT_LENGTH);
		tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
		CopyMemory(&tTribe, &tData[(MAX_AVATAR_NAME_LENGTH + MAX_CHAT_CONTENT_LENGTH)], 4);

		mTRANSFER.B_GENERAL_CHAT_RECV(&tAvatarName01[0], tAuthType, &tContent[0]);

		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}

			mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}

		return;
	case 996:
		mEXTRA_COM.U_BUY_BLOOD_ITEM_FOR_EXTRA_SEND(2);
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			mTRANSFER.B_BLOODMARKET(10, mEXTRA_COM.mBloodItemInfo[mUSER[index01].mAvatarInfo.aTribe]);
			mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		return;
	case 997:
			for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
			{
				if (!mAVATAR_OBJECT[index01].mCheckValidState)
				{
					continue;
				}
				if(mUSER[index01].uUserSort != 100)
					mUSER[index01].Quit(__FILE__, __FUNCTION__, __LINE__);
			}
		return;
	case 998:
		if (mEXTRA_COM.U_GET_CASH_ITEM_INFO_FOR_EXTRA_SEND() == 1)
		{
			mTRANSFER.B_GET_CASH_ITEM_INFO_RECV(0, mEXTRA_COM.mCashItemInfoVersion, mEXTRA_COM.mCashItemInfo);
			for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
			{
				if (!mAVATAR_OBJECT[index01].mCheckValidState)
				{
					continue;
				}
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
		}	
		return;
	case 999:
		ReadServerInfoUpdate();
		mGAME.mGeneralExperienceUpRatio = mSERVER_INFO.WORLD_EXP;
		mGAME.mItemDropUpRatio = mSERVER_INFO.WORLD_ITEM_DROP;
		mGAME.mItemDropUpRatioForMyoung = mSERVER_INFO.WORLD_ITEM_DROP_FM;
		mGAME.mKillOtherTribeAddValue = mSERVER_INFO.WORLD_KTAV;
		mGAME.mBinekExpAddValue = mSERVER_INFO.WORLD_BINEKEXP;
		mGAME.mPatExperienceUpRatio = mSERVER_INFO.WORLD_PATEXP;
		mGAME.mBonusGainGeneralExperienceUpRatio = 1.0f;
		mGAME.mGeneralExperienceDownRatio = mSERVER_INFO.WORLD_EXPLOSS;
		mGAME.mKillOtherTribeExperienceUpRatio = mSERVER_INFO.WORLD_PVPXP;
		mGAME.mItemDropMoney = mSERVER_INFO.WORLD_MONSTER_DROP_MONEY;
		printf("!WORLD_MONSTER_DROP_MONEY: %d\n", mSERVER_INFO.WORLD_MONSTER_DROP_MONEY);
		printf("!WORLD_GODITEM_DROP: %d\n", mSERVER_INFO.WORLD_GODITEM_DROP);
		printf("!WORLD_EARTH_CHEST_DROP: %d\n", mSERVER_INFO.WORLD_EARTH_CHEST_DROP);
		printf("!WORLD_DIAMOND_DROP: %d\n", mSERVER_INFO.WORLD_DIAMOND_DROP);
		printf("!WORLD_FEATHER_DROP: %d\n", mSERVER_INFO.WORLD_FEATHER_DROP);
		printf("!WORLD_SKILL_BOX_DROP: %d\n", mSERVER_INFO.WORLD_SKILL_BOX_DROP);
		printf("!WORLD_IMPROVE_STONE_DROP: %d\n", mSERVER_INFO.WORLD_IMPROVE_STONE_DROP);
		printf("!WORLD_8TH_DROP: %d\n", mSERVER_INFO.WORLD_8TH_DROP);
		printf("!OUTPOST_FEATHER_DROP: %d\n", mSERVER_INFO.OUTPOST_FEATHER_DROP);
		printf("!OUTPOST_DIAMOND_DROP: %d\n", mSERVER_INFO.OUTPOST_DIAMOND_DROP);
		printf("!OUTPOST_5_MOUNT_DROP: %d\n", mSERVER_INFO.OUTPOST_5_MOUNT_DROP);
		printf("!OUTPOST_HEAVENLY_CHEST_DROP: %d\n", mSERVER_INFO.OUTPOST_HEAVENLY_CHEST_DROP);
		printf("!OUTPOST_ASIRLIK_ALTIN_DROP: %d\n", mSERVER_INFO.OUTPOST_ASIRLIK_ALTIN_DROP);
		printf("!OUTPOST_BLACK_FEATHER_DROP: %d\n", mSERVER_INFO.OUTPOST_BLACK_FEATHER_DROP);
		printf("!OUTPOST_IKSIR_DROP: %d\n", mSERVER_INFO.OUTPOST_IKSIR_DROP);
		printf("!OUTPOST_SKILL_BOX_DROP: %d\n", mSERVER_INFO.OUTPOST_SKILL_BOX_DROP);
		printf("!OUTPOST_TREASURE_MONSTER_BOX: %d\n", mSERVER_INFO.OUTPOST_TREASURE_MONSTER_BOX);
		printf("!OUTPOST_10_MOUNT_BOX_DROP: %d\n", mSERVER_INFO.OUTPOST_10_MOUNT_BOX_DROP);
		printf("!OUTPOST_15_MOUNT_BOX_DROP: %d\n", mSERVER_INFO.OUTPOST_15_MOUNT_BOX_DROP);
		printf("!OUTPOST_8_BK_CRAFT_DROP: %d\n", mSERVER_INFO.OUTPOST_8_BK_CRAFT_DROP);
		printf("!PK_IOS_KEY_DROP: %d\n", mSERVER_INFO.PK_IOS_KEY_DROP);
		printf("!WORLD_2_SOCKET_RATE: %d\n", mSERVER_INFO.WORLD_2_SOCKET_RATE);
		printf("!WORLD_3_SOCKET_RATE: %d\n", mSERVER_INFO.WORLD_3_SOCKET_RATE);
		printf("!WORLD_4_SOCKET_RATE: %d\n", mSERVER_INFO.WORLD_4_SOCKET_RATE);
		printf("!WORLD_5_SOCKET_RATE: %d\n", mSERVER_INFO.WORLD_5_SOCKET_RATE);
		return;
	}
}
//PROCESS_FOR_DATA
void MyWork::ProcessForData(int tUserIndex, int tSort, BYTE tData[MAX_BROADCAST_DATA_SIZE])
{
	int tResult;
	int tPage1;
	int tIndex1;
	int tQuantity1;
	int tPage2;
	int tIndex2;
	int tXPost2;
	int tYPost2;
	int nIndex;
	int sIndex;
	int tSkillIndex;
	int tSkillSort;
	int tSkillGrade;
	int tHotKeyPage;
	int tHotKeyIndex;
	int tStatSort;
	int tMoney;
	int tValue;
	float tCoord[3];
	int tChangeTribeSort;
	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	BYTE tGMData[MAX_TRIBE_WORK_SIZE];
	int tOtherUserIndex;
	int tGod;
	int tChat;
	int tLevel;
	char tContent[MAX_CHAT_CONTENT_LENGTH];
	int index01;
#ifdef __GOD__
	int iMaxLevel = 157;
	int tTribe = -1;
	int tZoneNumber = -1;
	int tLevel2 = 0;
	int tGeneralExperience1 = 0;
	int tGeneralExperience2 = 0;
#else
	int iMaxLevel = ((mSERVER_INFO.m_iDeploymentStage > 0) ? MAX_LIMIT_LEVEL_NUM : 145);
#endif
	char tChangeAvatarName[MAX_AVATAR_NAME_LENGTH];
	int tTargetIndex = -1;
	int tRes;
	int tMove;
	int tCount = 0;
	bool tCheck = false;
	int tAvatarDuelUniqueNumber = 0;
	float tDuelCenter[3];
	float tDuelCenter2[3];
	int tRandomValue;
	unsigned int tRandom = 0;

	tDuelCenter[0] = 0.0f;
	tDuelCenter[1] = 0.0f;
	tDuelCenter[2] = 0.0f;
	tDuelCenter2[0] = 0.0f;
	tDuelCenter2[1] = 0.0f;
	tDuelCenter2[2] = 0.0f;


	switch (tSort)
	{
	case 201: //[WORLD]->[INVENTORY]
		if (1 == mUSER[tUserIndex].mAuthInfo.GItemFlag) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForGetItem(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		if (tResult == 0)
		{
			mTRANSFER.B_ITEM_ACTION_RECV(tPage1, mITEM_OBJECT[tPage1].mUniqueNumber, &mITEM_OBJECT[tPage1].mDATA, 3);
			mUTIL.Broadcast(TRUE, &mITEM_OBJECT[tPage1].mDATA.iLocation[0], UNIT_SCALE_RADIUS1, false);
			mITEM_OBJECT[tPage1].mCheckValidState = FALSE;
			//-----------//
			//.._...//
			//-----------//
			if (mUSER[tUserIndex].mHealthState == 5)
			{
				return;
			}
			//-----------//
			//-----------//
			//-----------//
			//-----//
			//QUEST//
			//-----//
			if ((mUSER[tUserIndex].mAvatarInfo.aQuestInfo[2] == 2) && (mUSER[tUserIndex].mAvatarInfo.aQuestInfo[3] == mITEM_OBJECT[tPage1].mDATA.iIndex) && (mAVATAR_OBJECT[tUserIndex].ReturnQuestPresentState() == 2))
			{
				mTRANSFER.B_PROCESS_QUEST_RECV(0, 7, 0, 0, 0, 0);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
			//-----//
			//-----//
			//-----//
		}
		return;
	case 202: //[NPC]->[SKILL]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory(&nIndex, &tData[0], 4);
		CopyMemory(&sIndex, &tData[4], 4);
		if (!ProcessForLearnSkill1(tUserIndex, nIndex, sIndex, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 203: //[SKILL]->[UP]
		CopyMemory(&tSkillIndex, &tData[0], 4);
		if (!ProcessForSkillUpgrade(tUserIndex, tSkillIndex, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 204: //[SKILL,EMOTICON]->[HOTKEY]
		CopyMemory(&tSkillSort, &tData[0], 4);
		CopyMemory(&tSkillIndex, &tData[4], 4);
		CopyMemory(&tSkillGrade, &tData[8], 4);
		CopyMemory(&tHotKeyPage, &tData[12], 4);
		CopyMemory(&tHotKeyIndex, &tData[16], 4);
		if (!ProcessForSkillToHotKey(tUserIndex, tSkillSort, tSkillIndex, tSkillGrade, tHotKeyPage, tHotKeyIndex, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 205: //[HOTKEY(SKILL,EMOTICON)]->[NO]
		CopyMemory(&tHotKeyPage, &tData[0], 4);
		CopyMemory(&tHotKeyIndex, &tData[4], 4);
		if (!ProcessForHotKeyToNo(tUserIndex, tHotKeyPage, tHotKeyIndex, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 206: //[STAT+]
		CopyMemory(&tStatSort, &tData[0], 4);
		if (!ProcessForStatPlus(tUserIndex, tStatSort, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mGAMELOG.GL_PLUSS_STATE(tUserIndex, tStatSort, 
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint, 
			mUSER[tUserIndex].mAvatarInfo.aVitality, 
			mUSER[tUserIndex].mAvatarInfo.aStrength, 
			mUSER[tUserIndex].mAvatarInfo.aKi, mUSER[tUserIndex].mAvatarInfo.aWisdom);
		return;
	case 207: //[MONEY]->[NO]
		CopyMemory(&tMoney, &tData[0], 4);
		if ((tMoney < 0) || (tMoney > 100000000) || (mUSER[tUserIndex].mAvatarInfo.aMoney < tMoney))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tMoney;
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 208: //[INVENTORY]->[INVENTORY]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryToInventory(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 209: //[INVENTORY]->[WORLD]
		if (1 == mUSER[tUserIndex].mAuthInfo.DItemFlag) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryToWorld(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 210: //[INVENTORY]->[EQUIP]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryToEquip(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 211: //[INVENTORY]->[HOTKEY]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryToHotKey(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 212: //[INVENTORY]->[NPC-SHOP]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 4))
		{
			// # Defense Hack # {
			//mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			//mGAMELOG.GL_659_AUTO_CHECK(tUserIndex, 11, 0);
			// #
			return;
		}
		if (1 == mUSER[tUserIndex].mAuthInfo.ShopFlag) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryToNPCShop(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 213: //[EQUIP]->[INVENTORY]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForEquipToInventory(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 214: //[HOTKEY]->[INVENTORY]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForHotKeyToInventory(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 215: //[NPC-SHOP]->[INVENTORY]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 4))
		{
			// # Defense Hack # {
			//mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			//mGAMELOG.GL_659_AUTO_CHECK(tUserIndex, 10, 0);
			// #
			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForNPCShopToInventory(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 216: //[HOTKEY]->[HOTKEY]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForHotKeyToHotKey(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 217:  //[INVENTORY_MONEY]->[WORLD]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryMoneyToWorld(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 218:  //[INVENTORY]->[TRADE]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryToTrade(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 219: //[TRADE]->[INVENTORY]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForTradeToInventory(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 220: //[TRADE]->[TRADE]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForTradeToTrade(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 221: //[INVENTORY_MONEY]->[TRADE_MONEY]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryMoneyToTradeMoney(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 222: //[TRADE_MONEY]->[INVENTORY_MONEY]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForTradeMoneyToInventoryMoney(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 223: //[INVENTORY]->[STORE]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 2))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryToStore(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 224: //[STORE]->[INVENTORY]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 2))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForStoreToInventory(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 225: //[STORE]->[STORE]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 2))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForStoreToStore(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 226: //[INVENTORY_MONEY]->[STORE_MONEY]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 2))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryMoneyToStoreMoney(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 227: //[STORE_MONEY]->[INVENTORY_MONEY]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 2))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForStoreMoneyToInventoryMoney(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 228: //[INVENTORY]->[SAVE]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 8))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryToSave(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 229: //[SAVE]->[INVENTORY]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 8))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForSaveToInventory(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 230: //[SAVE]->[SAVE]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 8))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForSaveToSave(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 231: //[INVENTORY_MONEY]->[SAVE_MONEY]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 8))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryMoneyToSaveMoney(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 232: //[SAVE_MONEY]->[INVENTORY_MONEY]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 8))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForSaveMoneyToInventoryMoney(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 233: //[TRIBE_4_NPC]->[SKILL]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 37))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&nIndex, &tData[0], 4);
		CopyMemory(&sIndex, &tData[4], 4);
		if (!ProcessForLearnSkill2(tUserIndex, nIndex, sIndex, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 234: //[USER]-ITEM
		CopyMemory(&tValue, &tData[0], 4);
		switch (tValue)
		{
		case 1: //[Ȱ\B7´\DC]

			if (!mUTIL.ProcessForDropItem(9, 1017, 0, 0, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[tUserIndex].mDATA.aName[0], 0, mUSER[tUserIndex].DropItemSocketGmAndBos))
			{
				mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			//mGAMELOG.GL_640_USER_CREATE_ITEM(tUserIndex, 1017, 0, 0, 0);

			mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		case 2: //[\B9\E6\C6ĺ\CE]

			if (!mUTIL.ProcessForDropItem(9, 1103, 0, 0, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[tUserIndex].mDATA.aName[0], 0, mUSER[tUserIndex].DropItemSocketGmAndBos))
			{
				mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			//mGAMELOG.GL_640_USER_CREATE_ITEM(tUserIndex, 1103, 0, 0, 0);

			mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		case 3: //[\B3\BB\B0\F8\B4\DC]

			if (!mUTIL.ProcessForDropItem(9, 1018, 0, 0, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[tUserIndex].mDATA.aName[0], 0, mUSER[tUserIndex].DropItemSocketGmAndBos))
			{
				mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			//mGAMELOG.GL_640_USER_CREATE_ITEM(tUserIndex, 1018, 0, 0, 0);

			mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		default:
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		return;
	case 235: //Meritten Cp alımı
		CopyMemory(&tValue, &tData[0], 4);

		if (tValue < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}

		if (mUSER[tUserIndex].mAvatarInfo.aTeacherPoint < (tValue * 100000))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}

		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += tValue;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += tValue;
		mUSER[tUserIndex].mAvatarInfo.aTeacherPoint -= (tValue * 100000);
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 236://cp for item palace
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 30)
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		//mGAMELOG.GL_640_USER_CREATE_ITEM(tUserIndex, 1103, 0, 0, 0);


		tRandom = rand() % 100;
		if (tRandom < 20)
		{
			tValue = 1023;
		}
		else if (tRandom < 40) {
			tValue = 1023; //%15 eritme
		}
		else if (tRandom < 60) {
			tValue = 1379; // Godsent lucky
		}
		else if (tRandom < 75) {
			tValue = 1041; //pill
		}
		else if (tRandom < 80) {
			tValue = 509; // str iksiri
		}
		else if (tRandom < 85) {
			tValue = 508;// Wisdom ikisiri 
		}
		else if (tRandom < 90) {
			tValue = 506;//Can iksiri 
		}
		else {
			tValue = 507;//Mana iksiri 
		}



		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 30;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 30;
		if (!mUTIL.ProcessForDropItem(4, tValue, 0, 0, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[tUserIndex].mDATA.aName[0], 0, mUSER[tUserIndex].DropItemSocketGmAndBos))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 237: //Merit
		if (mUSER[tUserIndex].mAvatarInfo.OnlineHour < 1)
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		mUSER[tUserIndex].mAvatarInfo.aTeacherPoint = 694 * mUSER[tUserIndex].mAvatarInfo.OnlineHour;
		mUSER[tUserIndex].mAvatarInfo.OnlineHour = 0;

		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 240: //[INVENTORY_BAR]->[TRADE_BAR]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 2))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);

		if (!ProcessForInventoryBarToTradeBar(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 241: //[INVENTORY_BAR]->[BANK_BAR]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 2))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);

		if (!ProcessForInventoryBarToBankBar(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 242: //[INVENTORY_BAR]->[SEYIS_BAR]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 2))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);

		if (!ProcessForInventoryBarToSeyisBar(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 243: //[TRADE_BAR]->[INVENTORY_BAR]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 2))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);

		if (!ProcessForTradeBarToInventoryBar(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 244: //[BANK_BAR]->[INVENTORY_BAR]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 2))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);

		if (!ProcessForBankBarToInventoryBar(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 245: //[SEYİS_BAR]->[INVENTORY_BAR]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 2))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);

		if (!ProcessForSeyisBarToInventoryBar(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 246: //[INVENTORY_MONEY]->[INVENTORY_BAR]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 2))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);

		if (!ProcessForInventoryMoneyToInventoryBar(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 247: //[INVENTORY_BAR]->[INVENTORY_MONEY]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 2))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}

		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);


		if (!ProcessForInventoryBarToInventoryMoney(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 248: //[STORE] -> [INVENTORY]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 4))
		{
			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);

		if (!ProcessForStoreToInventory(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}

		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 249: //[SAVE] -> [INVENTORY]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 4))
		{
			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);

		if (!ProcessForSaveToInventory(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}

		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 250: //[INVENTORY] -> [STORE]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 4))
		{
			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);

		if (!ProcessForInventoryToStore(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}

		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 251: //[INVENTORY] -> [SAVE]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 8))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);

		if (!ProcessForInventoryToSave(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}

		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 252: //[INVENTORY]->[NPC-SHOP]
		if (!mZONENPCINFO.CheckNPCFunction(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 4))
		{
			// # Defense Hack # {
			//mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			//mGAMELOG.GL_659_AUTO_CHECK(tUserIndex, 11, 0);
			// #
			return;
		}
		if (1 == mUSER[tUserIndex].mAuthInfo.ShopFlag) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryToNPCShop(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 253: //[INVENTORY] -> [HOTKEY]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tQuantity1, &tData[8], 4);
		CopyMemory(&tPage2, &tData[12], 4);
		CopyMemory(&tIndex2, &tData[16], 4);
		CopyMemory(&tXPost2, &tData[20], 4);
		CopyMemory(&tYPost2, &tData[24], 4);
		if (!ProcessForInventoryToHotKey(tUserIndex, tPage1, tIndex1, tQuantity1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 254: //[INVENTORY] -> [PETINVENTORY]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tPage2, &tData[8], 4);
		CopyMemory(&tIndex2, &tData[12], 4);
		CopyMemory(&tXPost2, &tData[16], 4);
		CopyMemory(&tYPost2, &tData[20], 4);
		if (!ProcessForInventoryToPetInventory(tUserIndex, tPage1, tIndex1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 255: //[PETINVENTORY] -> [INVENTORY]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tPage2, &tData[8], 4);
		CopyMemory(&tIndex2, &tData[12], 4);
		CopyMemory(&tXPost2, &tData[16], 4);
		CopyMemory(&tYPost2, &tData[20], 4);
		if (!ProcessForPetInventoryToInventory(tUserIndex, tPage1, tIndex1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 256: //[PETINVENTORY] -> [PETINVENTORY]
		CopyMemory(&tPage1, &tData[0], 4);
		CopyMemory(&tIndex1, &tData[4], 4);
		CopyMemory(&tPage2, &tData[8], 4);
		CopyMemory(&tIndex2, &tData[12], 4);
		CopyMemory(&tXPost2, &tData[16], 4);
		CopyMemory(&tYPost2, &tData[20], 4);
		if (!ProcessForPetInventoryToPetInventory(tUserIndex, tPage1, tIndex1, tPage2, tIndex2, tXPost2, tYPost2, &tResult))
		{
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(tResult, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
		//------------//
		//[GM]-COMMAND//
		//------------//
	case 501: //[GM]-HIDE
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.HideFlag == 0) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUSER[tUserIndex].mAvatarInfo.aVisibleState = 0;
		mAVATAR_OBJECT[tUserIndex].mDATA.aVisibleState = 0;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(9, mUSER[tUserIndex].mAvatarInfo.aVisibleState);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 502: //[GM]-SHOW
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.ShowFlag == 0) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUSER[tUserIndex].mAvatarInfo.aVisibleState = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aVisibleState = 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(9, mUSER[tUserIndex].mAvatarInfo.aVisibleState);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 503: //[GM]-EXP
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.ExpFlag == 0) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tValue, &tData[0], 4);
		if ((tValue < 1) || (tValue > 100000000))
		{
			return;
		}
		////mGAMELOG.GL_656_GM_EXP(tUserIndex, tValue);
		mUTIL.ProcessForExperience(tUserIndex, tValue, 0, 0);
		return;
	case 504: //[GM]-MONEY
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.MoneyFlag == 0) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tValue, &tData[0], 4);
		if ((tValue < 1) || (tValue > 2000000000))
		{
			return;
		}
		if (!mUTIL.ProcessForDropItem(4, 1, tValue, 0, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], "", 0, mUSER[tUserIndex].DropItemSocketGmAndBos))
		{
			return;
		}
		//mGAMELOG.GL_601_GM_CREATE_MONEY(tUserIndex, tValue);
		return;
	case 505: //[GM]-ITEM
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.ItemFlag == 0) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tValue, &tData[0], 4);
		if ((tValue < 2) || (tValue > 99999))
		{
			return;
		}
		for (int i = 0; i < 4; i++) {
			mUTIL.ProcessForDropItem(4, tValue, 0, 0, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], "", 0, mUSER[tUserIndex].DropItemSocketGmAndBos);
		}
		//if (!mUTIL.ProcessForDropItem(4, tValue, 0, 0, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], "", 0, mUSER[tUserIndex].DropItemSocketGmAndBos))
		//{
		//	return;//item 699
		//}
		//if (!mUTIL.ProcessForDropItem(4, tValue, 0, 0, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], "", 0, mUSER[tUserIndex].DropItemSocketGmAndBos))
		//{
		//	return;
		//}
		//if (!mUTIL.ProcessForDropItem(4, tValue, 0, 0, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], "", 0, mUSER[tUserIndex].DropItemSocketGmAndBos))
		//{
		//	return;
		//}
		//if (!mUTIL.ProcessForDropItem(4, tValue, 0, 0, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], "", 0, mUSER[tUserIndex].DropItemSocketGmAndBos))
		//{
		//	return;
		//}
		//if (!mUTIL.ProcessForDropItem(4, tValue, 0, 0, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], "", 0, mUSER[tUserIndex].DropItemSocketGmAndBos))
		//{
		//	return;
		//}

		
		//mGAMELOG.GL_602_GM_CREATE_ITEM(tUserIndex, tValue, 0, 0, 0);
		return;
	case 506: //[GM]-MONCALL
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.MonCallFlag == 0) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tValue, &tData[0], 4);
		CopyMemory(&tCount, &tData[4], 4);

		/*if ( tCount != 2010771308) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}*/

		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mSUMMON.SummonMonsterForSpecial(tValue, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], FALSE);
		return;
	case 507: //[GM]-MOVE
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.MoveFlag == 0) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tCoord[0], &tData[0], 12);
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0] = tCoord[0];
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[1] = tCoord[1];
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[2] = tCoord[2];
		mAVATAR_OBJECT[tUserIndex].SetSpaceIndex();
		GameLogger(3, "<GM_MOVE>(%s),(%s),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mSERVER_INFO.mServerNumber);
		return;
	//case 508: //[GM]-DIE
	//	if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
	//	{
	//		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

	//		return;
	//	}
	//	if (mUSER[tUserIndex].mAuthInfo.DieFlag == 0) {
	//		mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
	//		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	//		return;
	//	}
	//	mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
	//	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	//	CopyMemory(&tValue, &tData[0], 4);
	//	if ((tValue < 0) || (tValue > (MAX_MONSTER_OBJECT_NUM - 1)))
	//	{
	//		return;
	//	}
	//	if (!mMONSTER_OBJECT[tValue].mCheckValidState)
	//	{
	//		return;
	//	}
	//	//mGAMELOG.GL_657_GM_DIE(tUserIndex, tValue);
	//	mMONSTER_OBJECT[tValue].mCheckValidState = FALSE;
	//	mMONSTER_OBJECT[tValue].mInvalidTimeForSummon = GetTickCount();
	//	return;
	case 508: //[GM]-DIE
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.DieFlag == 0) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tValue, &tData[0], 4);
		if ((tValue < 0) || (tValue > (MAX_MONSTER_OBJECT_NUM - 1)))
		{
			return;
		}
		if (!mMONSTER_OBJECT[tValue].mCheckValidState)
		{
			return;
		}
		//mGAMELOG.GL_657_GM_DIE(tUserIndex, tValue);
		mMONSTER_OBJECT[tValue].mCheckValidState = FALSE;
		mMONSTER_OBJECT[tValue].mInvalidTimeForSummon = GetTickCount64();
		GameLogger(3, "<GM_DIE>(%s),(%s),(Monster ID: %d),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mMONSTER_OBJECT[tValue].mDATA.mIndex, mSERVER_INFO.mServerNumber);
		return;
	//case 509: //[GM]-MAX
	//	if (mUSER[tUserIndex].uUserSort < 100)
	//	{
	//		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
	//		return;
	//	}
	//	mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
	//	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	//	mUSER[tUserIndex].mAvatarInfo.aVitality = 100000;
	//	mUSER[tUserIndex].mAvatarInfo.aStrength = 100000;
	//	mUSER[tUserIndex].mAvatarInfo.aKi = 100000;
	//	mUSER[tUserIndex].mAvatarInfo.aWisdom = 100000;
	//	mUSER[tUserIndex].mAvatarInfo.aSkillPoint = 100000;
	//	mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

	//	return;
	case 509: //[GM]-MAX
		if (mUSER[tUserIndex].uUserSort < 100)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		GameLogger(3, "<GM_MAX>(%s),(%s),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mSERVER_INFO.mServerNumber);
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUSER[tUserIndex].mAvatarInfo.aVitality = 1000000;
		mUSER[tUserIndex].mAvatarInfo.aStrength = 1000000;
		mUSER[tUserIndex].mAvatarInfo.aKi = 1000000;
		mUSER[tUserIndex].mAvatarInfo.aWisdom = 100000;
		mUSER[tUserIndex].mAvatarInfo.aSkillPoint = 1000000;
		mUSER[tUserIndex].mAvatarInfo.aUpradgeValue = 96;
		mUSER[tUserIndex].mAvatarInfo.aLevel1 = 145;
		mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 = MAX_NUMBER_SIZE;
		mUSER[tUserIndex].mAvatarInfo.aLevel2 = 12;
		mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = MAX_NUMBER_SIZE;
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

		return;
	case 510: //[GM]-TRIBE
		if (mUSER[tUserIndex].uUserSort < 100)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tChangeTribeSort, &tData[0], 4);
		switch (tChangeTribeSort)
		{
		case 1:
			if (mUSER[tUserIndex].mAvatarInfo.aTribe == 3)
			{
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aTribe = 3;
			mUSER[tUserIndex].mAvatarInfo.aQuestInfo[0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aQuestInfo[1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aQuestInfo[2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aQuestInfo[3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aQuestInfo[4] = 0;
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		case 2:
			if (mUSER[tUserIndex].mAvatarInfo.aTribe != 3)
			{
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aTribe = mUSER[tUserIndex].mAvatarInfo.aPreviousTribe;
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		return;
	case 511: //[GM]-EQUIP
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.EquipFlag == 0) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUSER[tUserIndex].mAvatarInfo.aSpecialState = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aSpecialState = 1;
		return;
	case 512: //[GM]-UNEQUIP
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.UnequipFlag == 0) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUSER[tUserIndex].mAvatarInfo.aSpecialState = 0;
		mAVATAR_OBJECT[tUserIndex].mDATA.aSpecialState = 0;
		return;
	case 513: //[GM]-FIND
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.FindFlag == 0) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		mPLAYUSER_COM.U_FIND_AVATAR_FOR_ZONE_SEND(&tAvatarName[0]);
		CopyMemory(&tGMData[0], &mPLAYUSER_COM.mRecv_ZoneNumber, 4);
		mTRANSFER.B_GM_COMMAND_INFO(1, &tGMData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 514: //[GM]-CALL
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.CallFlag == 0) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		tOtherUserIndex = mUTIL.SearchAvatar(&tAvatarName[0], tUserIndex);
		if (tOtherUserIndex == -1)
		{
			return;
		}
		mAVATAR_OBJECT[tOtherUserIndex].mDATA.aAction.aLocation[0] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0];
		mAVATAR_OBJECT[tOtherUserIndex].mDATA.aAction.aLocation[1] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[1];
		mAVATAR_OBJECT[tOtherUserIndex].mDATA.aAction.aLocation[2] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[2];
		//mGAMELOG.GL_655_GM_CALL(tUserIndex, tOtherUserIndex);
		CopyMemory(&tGMData[0], &mAVATAR_OBJECT[tOtherUserIndex].mDATA.aAction.aLocation[0], 12);
		mTRANSFER.B_GM_COMMAND_INFO(2, &tGMData[0]);
		mUSER[tOtherUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 515: //[GM]-MOVE
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.MoveFlag == 0) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		tOtherUserIndex = mUTIL.SearchAvatar(&tAvatarName[0], tUserIndex);
		if (tOtherUserIndex == -1)
		{
			return;
		}
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0] = mAVATAR_OBJECT[tOtherUserIndex].mDATA.aAction.aLocation[0];
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[1] = mAVATAR_OBJECT[tOtherUserIndex].mDATA.aAction.aLocation[1];
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[2] = mAVATAR_OBJECT[tOtherUserIndex].mDATA.aAction.aLocation[2];
		CopyMemory(&tGMData[0], &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 12);
		mTRANSFER.B_GM_COMMAND_INFO(2, &tGMData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 516: //[GM]-NCHAT
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.NchatFlag == 0) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		tOtherUserIndex = mUTIL.SearchAvatar(&tAvatarName[0], tUserIndex);
		if (tOtherUserIndex == -1)
		{
			return;
		}
		//mGAMELOG.GL_629_GM_NCHAT(tUserIndex, tOtherUserIndex);
		mUSER[tOtherUserIndex].mAvatarInfo.aSpecialState = 2;
		mAVATAR_OBJECT[tOtherUserIndex].mDATA.aSpecialState = 2;
		return;
	case 517: //[GM]-YCHAT
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.YchatFlag == 0) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		tOtherUserIndex = mUTIL.SearchAvatar(&tAvatarName[0], tUserIndex);
		if (tOtherUserIndex == -1)
		{
			return;
		}
		//mGAMELOG.GL_630_GM_YCHAT(tUserIndex, tOtherUserIndex);
		mUSER[tOtherUserIndex].mAvatarInfo.aSpecialState = 0;
		mAVATAR_OBJECT[tOtherUserIndex].mDATA.aSpecialState = 0;
		return;
	case 518: //[GM]-KICK
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.KickFlag == 0) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		tOtherUserIndex = mUTIL.SearchAvatar(&tAvatarName[0], tUserIndex);
		if (tOtherUserIndex == -1)
		{
			return;
		}
		//mGAMELOG.GL_631_GM_KICK(tUserIndex, tOtherUserIndex);
		mUSER[tOtherUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

		return;
	case 519: //[GM]-BLOCK
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.BlockFlag == 0) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		tOtherUserIndex = mUTIL.SearchAvatar(&tAvatarName[0], tUserIndex);
		if (tOtherUserIndex == -1)
		{
			return;
		}
		//mGAMELOG.GL_632_GM_BLOCK(tUserIndex, tOtherUserIndex);
		mPLAYUSER_COM.U_BLOCK_USER_FOR_ZONE_1_SEND(603, &mUSER[tOtherUserIndex].uID[0]);
		mUSER[tOtherUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

		return;
	case 520: //GOD
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.GodFlag == 0) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		CopyMemory(&tGod, &tData[0], 4);
		mAVATAR_OBJECT[tUserIndex].mGod = tGod;
		//mGAMELOG.GL_648_GM_GOD(tUserIndex, tGod);
		return;
	//case 521: //CHAT
	//	if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
	//	{
	//		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

	//		return;
	//	}
	//	if (mUSER[tUserIndex].mAuthInfo.ChatFlag == 0) {
	//		mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
	//		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	//		return;
	//	}
	//	mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
	//	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	//	CopyMemory(&tChat, &tData[0], 4);
	//	mAVATAR_OBJECT[tUserIndex].mChat = tChat;
	//	////mGAMELOG.GL_649_GM_CHAT( tUserIndex );
	//	return;
	case 521: //LEVEL
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tLevel, &tData[0], 4);
		if ((tLevel > iMaxLevel) || (tLevel < 1)) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
#ifdef __GOD__	
		if (tLevel > 145) {
			tLevel2 = tLevel - 145;
			tLevel = 145;
			tGeneralExperience1 = MAX_NUMBER_SIZE;
			tGeneralExperience2 = 0;
		}
		else {
			tLevel2 = 0;
			tGeneralExperience1 = mLEVEL.ReturnLevelFactor1(tLevel);
			tGeneralExperience2 = 0;
		}
#endif
		GameLogger(3, "<GM_LEVEL>(%s),(%s),[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mSERVER_INFO.mServerNumber);
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//mGAMELOG.GL_651_GM_LEVEL(tUserIndex, tLevel);
		mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 = mLEVEL.ReturnLevelFactor1(tLevel);
		mUSER[tUserIndex].mAvatarInfo.aLevel1 = tLevel;
		mAVATAR_OBJECT[tUserIndex].mDATA.aLevel1 = tLevel;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
#ifdef __GOD__
		mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = tGeneralExperience2;
		mUSER[tUserIndex].mAvatarInfo.aLevel2 = tLevel2;
		mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = tLevel2;
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 11, mUSER[tUserIndex].mAvatarInfo.aLevel2, mUSER[tUserIndex].mAvatarInfo.aSkillPoint, 0);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
#endif		

		return;
	case 522: //UMOVE
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(tAvatarName, &tData[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&tMove, &tData[MAX_AVATAR_NAME_LENGTH], 4);
		if (0 > tMove) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; ++index01) {
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (0 != strcmp(mUSER[index01].mAvatarInfo.aName, tAvatarName)) {
				continue;
			}
			tTargetIndex = index01;
			break;
		}
		if (-1 == tTargetIndex) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		if (mAVATAR_OBJECT[tTargetIndex].CheckCommunityWork()) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tResult = 0;
		CopyMemory(&tData[MAX_AVATAR_NAME_LENGTH + 4], &tResult, 4);
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		tResult = 1;
		CopyMemory(&tData[MAX_AVATAR_NAME_LENGTH + 4], &tResult, 4);
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tTargetIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//mGAMELOG.GL_650_GM_UMOVE(tUserIndex, tTargetIndex, tMove);
		return;
	case 523: //LEVEL
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tLevel, &tData[0], 4);
		if ((tLevel > iMaxLevel) || (tLevel < 1)) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
#ifdef __GOD__	
		if (tLevel > 145) {
			tLevel2 = tLevel - 145;
			tLevel = 145;
			tGeneralExperience1 = MAX_NUMBER_SIZE;
			tGeneralExperience2 = 0;
		}
		else {
			tLevel2 = 0;
			tGeneralExperience1 = mLEVEL.ReturnLevelFactor1(tLevel);
			tGeneralExperience2 = 0;
		}
#endif
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//mGAMELOG.GL_651_GM_LEVEL(tUserIndex, tLevel);
		mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 = mLEVEL.ReturnLevelFactor1(tLevel);
		mUSER[tUserIndex].mAvatarInfo.aLevel1 = tLevel;
		mAVATAR_OBJECT[tUserIndex].mDATA.aLevel1 = tLevel;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
#ifdef __GOD__
		mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = tGeneralExperience2;
		mUSER[tUserIndex].mAvatarInfo.aLevel2 = tLevel2;
		mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = tLevel2;
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 13, mUSER[tUserIndex].mAvatarInfo.aLevel2, mUSER[tUserIndex].mAvatarInfo.aSkillPoint, 0);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
#endif		

		return;
	case 524: //ZNOTICE
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		////mGAMELOG.GL_652_GM_ZNOTICE( tUserIndex );
		CopyMemory(&tContent[0], &tData[0], MAX_CHAT_CONTENT_LENGTH);
		tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
		mTRANSFER.B_GENERAL_NOTICE_RECV(&tContent[0], 0);
		//mTRANSFER.B_TRIBE_CHAT_RECV( &mUSER[tUserIndex].mAvatarInfo.aName[0], &tContent[0] );
		//mCHATLOG.SendToLogServer( mUSER[tUserIndex].mAvatarInfo.aTribe, 6, mUSER[tUserIndex].mAvatarInfo.aName, "", tContent );
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		return;
	case 525: //RES
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(tAvatarName, &tData[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&tRes, &tData[MAX_AVATAR_NAME_LENGTH], 4);
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; ++index01) {
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (0 != strcmp(mUSER[index01].mAvatarInfo.aName, tAvatarName)) {
				continue;
			}
			tTargetIndex = index01;
			break;
		}
		if (-1 == tTargetIndex) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		switch (tRes) {
		case 0:
			mUSER[tTargetIndex].mAuthInfo.TradeFlag = 0;
			mUSER[tTargetIndex].mAuthInfo.ShopFlag = 0;
			mUSER[tTargetIndex].mAuthInfo.PShopFlag = 0;
			mUSER[tTargetIndex].mAuthInfo.GItemFlag = 0;
			mUSER[tTargetIndex].mAuthInfo.DItemFlag = 0;
			mUSER[tTargetIndex].mAuthInfo.AttackFlag = 0;
			mUSER[tTargetIndex].mAuthInfo.UZonemoveFlag = 0;
			break;
		case 1:
			mUSER[tTargetIndex].mAuthInfo.TradeFlag = 1;
			mUSER[tTargetIndex].mAuthInfo.ShopFlag = 1;
			mUSER[tTargetIndex].mAuthInfo.PShopFlag = 1;
			mUSER[tTargetIndex].mAuthInfo.GItemFlag = 1;
			mUSER[tTargetIndex].mAuthInfo.DItemFlag = 1;
			mUSER[tTargetIndex].mAuthInfo.AttackFlag = 1;
			mUSER[tTargetIndex].mAuthInfo.UZonemoveFlag = 1;
			break;
		case 2:
			tResult = 2;
			CopyMemory(&tData[0], &tResult, 4);
			snprintf((char*)&tData[4], MAX_BROADCAST_DATA_SIZE, "%d%d%d%d%d%d%d", \
				mUSER[tTargetIndex].mAuthInfo.TradeFlag, mUSER[tTargetIndex].mAuthInfo.ShopFlag, mUSER[tTargetIndex].mAuthInfo.PShopFlag, \
				mUSER[tTargetIndex].mAuthInfo.GItemFlag, mUSER[tTargetIndex].mAuthInfo.DItemFlag, mUSER[tTargetIndex].mAuthInfo.AttackFlag, \
				mUSER[tTargetIndex].mAuthInfo.UZonemoveFlag);
			break;
		case 11:
			mUSER[tTargetIndex].mAuthInfo.TradeFlag = 1;
			break;
		case 12:
			mUSER[tTargetIndex].mAuthInfo.ShopFlag = 1;
			break;
		case 13:
			mUSER[tTargetIndex].mAuthInfo.PShopFlag = 1;
			break;
		case 14:
			mUSER[tTargetIndex].mAuthInfo.GItemFlag = 1;
			break;
		case 15:
			mUSER[tTargetIndex].mAuthInfo.DItemFlag = 1;
			break;
		case 16:
			mUSER[tTargetIndex].mAuthInfo.AttackFlag = 1;
			break;
		case 17:
			mUSER[tTargetIndex].mAuthInfo.UZonemoveFlag = 1;
			break;
		default:
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//mGAMELOG.GL_653_GM_RES(tUserIndex, tTargetIndex, tRes);
		return;
	case 526: //RENAME
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

			return;
		}
		CopyMemory(&tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tChangeAvatarName[0], &tData[MAX_AVATAR_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
		tChangeAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';

		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; ++index01) {
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (0 != strcmp(mUSER[index01].mAvatarInfo.aName, tAvatarName)) {
				continue;
			}
			tTargetIndex = index01;
			break;
		}
		if (-1 == tTargetIndex) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mPLAYUSER_COM.U_CHANGE_AVATAR_NAME_FOR_ZONE_SEND(mUSER[tTargetIndex].mPlayUserIndex, tChangeAvatarName);

		if (0 != mPLAYUSER_COM.mRecv_Result) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		CopyMemory(&tData[0], &tTargetIndex, 4);
		CopyMemory(&tData[4], &mAVATAR_OBJECT[tTargetIndex].mUniqueNumber, 4);
		CopyMemory(&tData[8], tChangeAvatarName, MAX_AVATAR_NAME_LENGTH);

		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		//mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tTargetIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);

		CopyMemory(mUSER[tTargetIndex].mAvatarInfo.aName, tChangeAvatarName, MAX_AVATAR_NAME_LENGTH);
		CopyMemory(mAVATAR_OBJECT[tTargetIndex].mDATA.aName, tChangeAvatarName, MAX_AVATAR_NAME_LENGTH);
		//mGAMELOG.GL_654_GM_RENAME(tUserIndex, tTargetIndex, tAvatarName, tChangeAvatarName);
		return;
	case 600: //DUEL READY
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		if (124 != mSERVER_INFO.mServerNumber) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		tDuelCenter[0] = -232.0f;
		tDuelCenter[1] = 36.0f;
		tDuelCenter[2] = 2.0f;
		tDuelCenter2[0] = 232.0f;
		tDuelCenter2[1] = 36.0f;
		tDuelCenter2[2] = 2.0f;

		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; ++index01) {
			if (!mAVATAR_OBJECT[index01].mCheckValidState) {
				continue;
			}
			if (mUSER[index01].mMoveZoneResult == 1) {
				continue;
			}
			if (mUSER[index01].mAuthInfo.AuthType == 1) {
				continue;
			}
			if (mAVATAR_OBJECT[index01].mDuelProcessState != 0) {
				continue;
			}
			if (mUTIL.ReturnLengthXYZ(&tDuelCenter[0], &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0]) < 52.0f) {
				__LogMgr()->Log("!0, Name:%s\n", mAVATAR_OBJECT[index01].mDATA.aName);
				mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0] = -157.0f;
				mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[1] = 5.0f;
				mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[2] = 1.0f;
				mTRANSFER.B_AVATAR_ACTION_RECV(index01, mAVATAR_OBJECT[index01].mUniqueNumber, &mAVATAR_OBJECT[index01].mDATA, 0);
				mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
				continue;
			}
			if (mUTIL.ReturnLengthXYZ(&tDuelCenter2[0], &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0]) < 52.0f) {
				__LogMgr()->Log("!1, Name:%s\n", mAVATAR_OBJECT[index01].mDATA.aName);
				mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0] = 157.0f;
				mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[1] = 5.0f;
				mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[2] = 1.0f;
				mTRANSFER.B_AVATAR_ACTION_RECV(index01, mAVATAR_OBJECT[index01].mUniqueNumber, &mAVATAR_OBJECT[index01].mDATA, 0);
				mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
				continue;
			}
		}
		return;
	case 601: //DUEL START
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		if (124 != mSERVER_INFO.mServerNumber) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		tAvatarDuelUniqueNumber = mGAME.mAvatarDuelUniqueNumber;
		mGAME.mAvatarDuelUniqueNumber++;
		tDuelCenter[0] = -157.0f;
		tDuelCenter[1] = 5.0f;
		tDuelCenter[2] = 1.0f;
		tDuelCenter2[0] = 157.0f;
		tDuelCenter2[1] = 5.0f;
		tDuelCenter2[2] = 1.0f;
		mGAME.mDuel_124_AvatarNum[0] = 0;
		mGAME.mDuel_124_AvatarNum[1] = 0;

		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; ++index01) {
			tCheck = false;
			if (!mAVATAR_OBJECT[index01].mCheckValidState) {
				continue;
			}
			if (mUSER[index01].mMoveZoneResult == 1) {
				continue;
			}
			if (mUSER[index01].mAuthInfo.AuthType == 1) {
				continue;
			}
			if (mAVATAR_OBJECT[index01].mDuelProcessState != 0) {
				continue;
			}
			if (mUTIL.GetLengthXYZ(&tDuelCenter[0], &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0]) < 16.0f) {
				tCheck = true;
				mGAME.mDuel_124_AvatarNum[0]++;
				mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0] = -100.0f;
				mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[1] = 2.0f;
				mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[2] = 0.0f;
				mAVATAR_OBJECT[index01].mDATA.aDuelState[2] = 1;
			}
			if (mUTIL.GetLengthXYZ(&tDuelCenter2[0], &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0]) < 16.0f) {
				tCheck = true;
				mGAME.mDuel_124_AvatarNum[1]++;
				mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0] = 100.0f;
				mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[1] = 2.0f;
				mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[2] = 0.0f;
				mAVATAR_OBJECT[index01].mDATA.aDuelState[2] = 2;
			}
			if (tCheck) {
				mAVATAR_OBJECT[index01].mDATA.aDuelState[0] = 1;
				mAVATAR_OBJECT[index01].mDATA.aDuelState[1] = tAvatarDuelUniqueNumber;
				mAVATAR_OBJECT[index01].mCheckPossibleEatPotion = TRUE;
				mAVATAR_OBJECT[index01].mDuelProcessState = 4;
				mAVATAR_OBJECT[index01].mDuelProcessRemainTime = 300;
				mTRANSFER.B_DUEL_START_RECV(&mAVATAR_OBJECT[index01].mDATA.aDuelState[0], mAVATAR_OBJECT[index01].mDuelProcessRemainTime,0);
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				mTRANSFER.B_AVATAR_CHANGE_INFO_1(index01, mAVATAR_OBJECT[index01].mUniqueNumber, 7, mAVATAR_OBJECT[index01].mDATA.aDuelState[0], mAVATAR_OBJECT[index01].mDATA.aDuelState[1], mAVATAR_OBJECT[index01].mDATA.aDuelState[2]);
				mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);

				mTRANSFER.B_AVATAR_ACTION_RECV(index01, mAVATAR_OBJECT[index01].mUniqueNumber, &mAVATAR_OBJECT[index01].mDATA, 0);
				mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			}
		}
		mGAME.mDuel_124 = TRUE;
		mGAME.mDuel_124_RemainTime = 300;
		mGAME.mDuel_124_Pvp = FALSE;
		return;
	case 602: //DUEL END
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0) {
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		if (mSERVER_INFO.mServerNumber != 124) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		mGAME.mDuel_124 = FALSE;
		mGAME.mDuel_124_RemainTime = 0;

		mGAME.mDuel_124_AvatarNum[0] = 0;
		mGAME.mDuel_124_AvatarNum[1] = 0;
		mGAME.mDuel_124_Pvp = FALSE;

		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; ++index01) {
			if (!mAVATAR_OBJECT[index01].mCheckValidState) {
				continue;
			}
			if (mUSER[index01].mMoveZoneResult == 1) {
				continue;
			}
			if (mUSER[index01].mAuthInfo.AuthType == 1) {
				continue;
			}
			if (mAVATAR_OBJECT[index01].mDuelProcessState != 4) {
				continue;
			}
			mAVATAR_OBJECT[index01].mDATA.aDuelState[0] = 0;
			mAVATAR_OBJECT[index01].mDATA.aDuelState[1] = 0;
			mAVATAR_OBJECT[index01].mDATA.aDuelState[2] = 0;
			mAVATAR_OBJECT[index01].mCheckPossibleEatPotion = TRUE;
			mAVATAR_OBJECT[index01].mDuelProcessState = 0;
			mAVATAR_OBJECT[index01].mDuelProcessRemainTime = 0;
			mTRANSFER.B_DUEL_END_RECV(0);
			mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mTRANSFER.B_AVATAR_CHANGE_INFO_1(index01, mAVATAR_OBJECT[index01].mUniqueNumber, 7, mAVATAR_OBJECT[index01].mDATA.aDuelState[0], mAVATAR_OBJECT[index01].mDATA.aDuelState[1], mAVATAR_OBJECT[index01].mDATA.aDuelState[2]);
			mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		}
		return;
	case 603: //DUEL OUT
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0) {
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mSERVER_INFO.mServerNumber != 124) {
			mTRANSFER.B_PROCESS_DATA_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		mTRANSFER.B_PROCESS_DATA_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		mGAME.mDuel_124 = FALSE;
		mGAME.mDuel_124_RemainTime = 0;

		mGAME.mDuel_124_AvatarNum[0] = 0;
		mGAME.mDuel_124_AvatarNum[1] = 0;
		mGAME.mDuel_124_Pvp = FALSE;

		tDuelCenter[0] = -157.0f;
		tDuelCenter[1] = 5.0f;
		tDuelCenter[2] = 1.0f;
		tDuelCenter2[0] = 157.0f;
		tDuelCenter2[1] = 5.0f;
		tDuelCenter2[2] = 1.0f;

		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; ++index01) {
			tCheck = false;
			if (!mAVATAR_OBJECT[index01].mCheckValidState) {
				continue;
			}
			if (mUSER[index01].mMoveZoneResult == 1) {
				continue;
			}
			if (mUSER[index01].mAuthInfo.AuthType == 1) {
				continue;
			}
			if (((mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0] > -122.0f) && (mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0] < 122.0f))
				&& ((mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[2] > -124.0f) && (mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[2] < 124.0f))) {
				tCheck = true;
			}
			if (mUTIL.GetLengthXYZ(&tDuelCenter[0], &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0]) < 52.0f) {
				tCheck = true;
			}
			if (mUTIL.GetLengthXYZ(&tDuelCenter2[0], &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0]) < 52.0f) {
				tCheck = true;
			}
			if (tCheck) {
				mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0] = 0.0f;
				mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[1] = 36.0f;
				mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[2] = -209.0f;
				mAVATAR_OBJECT[index01].mDATA.aDuelState[0] = 0;
				mAVATAR_OBJECT[index01].mDATA.aDuelState[1] = 0;
				mAVATAR_OBJECT[index01].mDATA.aDuelState[2] = 0;
				mAVATAR_OBJECT[index01].mCheckPossibleEatPotion = TRUE;
				mAVATAR_OBJECT[index01].mDuelProcessState = 0;
				mAVATAR_OBJECT[index01].mDuelProcessRemainTime = 0;
				mTRANSFER.B_AVATAR_CHANGE_INFO_1(index01, mAVATAR_OBJECT[index01].mUniqueNumber, 7, mAVATAR_OBJECT[index01].mDATA.aDuelState[0], mAVATAR_OBJECT[index01].mDATA.aDuelState[1], mAVATAR_OBJECT[index01].mDATA.aDuelState[2]);
				mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);

				mTRANSFER.B_AVATAR_ACTION_RECV(index01, mAVATAR_OBJECT[index01].mUniqueNumber, &mAVATAR_OBJECT[index01].mDATA, 0);
				mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			}
		}
		return;

	}
}

//------------------------------------------------------------------------------------------------