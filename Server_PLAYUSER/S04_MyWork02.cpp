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
//---------------//
//LOGIN->PLAYUSER//
//---------------//
//W_LOGIN_FOR_PLAYUSER_SEND
void W_LOGIN_FOR_PLAYUSER_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 0)
	{
		mUSER[tUserIndex].Quit(3001);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int index01;

	for (index01 = 0; index01 < MAX_USER_NUM; index01++)
	{
		if (mUSER[index01].mCheckServerType == 1)
		{
			mUSER[index01].Quit(3002);
		}
	}

	mUSER[tUserIndex].mCheckServerType = 1;
	mTRANSFER.B_LOGIN_FOR_PLAYUSER_RECV();
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_LOGIN_OK_FOR_PLAYUSER_SEND
void W_LOGIN_OK_FOR_PLAYUSER_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 1)
	{
		mUSER[tUserIndex].Quit(3003);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();
}
//W_REGISTER_USER_FOR_LOGIN_1_SEND
void W_REGISTER_USER_FOR_LOGIN_1_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 1)
	{
		mUSER[tUserIndex].Quit(3004);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	char tIP[16];
	char tID[MAX_USER_ID_LENGTH];
	int tUserSort;
	int tGoodFellow;
	int tUserRandom;
	int tLoginPremium;
	int tLoginPremiumPCRoom;
	int tTraceState;
	char tBonus100Money;
	int tPremiumServerExpirationDate; // 프리미엄 서버(월드) 입장권 유효 기한(YYYYMMDD 형태의 정수). // @_Premium_Server_@
	AUTH_INFO tAuthInfo;
	CopyMemory(&tIP[0], &tPacket[1], 16);
	tIP[15] = '\0';
	CopyMemory(&tID[0], &tPacket[17], MAX_USER_ID_LENGTH);
	tID[(MAX_USER_ID_LENGTH - 1)] = '\0';
	CopyMemory(&tUserSort, &tPacket[(17 + MAX_USER_ID_LENGTH)], 4);
	CopyMemory(&tGoodFellow, &tPacket[(21 + MAX_USER_ID_LENGTH)], 4);
	CopyMemory(&tUserRandom, &tPacket[(25 + MAX_USER_ID_LENGTH)], 4);
	CopyMemory(&tLoginPremium, &tPacket[(29 + MAX_USER_ID_LENGTH)], 4);
	CopyMemory(&tLoginPremiumPCRoom, &tPacket[(33 + MAX_USER_ID_LENGTH)], 4);
	CopyMemory(&tTraceState, &tPacket[(37 + MAX_USER_ID_LENGTH)], 4);
	CopyMemory(&tBonus100Money, &tPacket[(41 + MAX_USER_ID_LENGTH)], 1);
	CopyMemory(&tPremiumServerExpirationDate, &tPacket[(42 + MAX_USER_ID_LENGTH)], 4); // @_Premium_Server_@
	CopyMemory(&tAuthInfo, &tPacket[(46 + MAX_USER_ID_LENGTH)], sizeof(AUTH_INFO));

	int tResult;
	int tPlayUserIndex;

	tResult = mGAME.RegisterUserForLogin_01(&tIP[0], &tID[0], tUserSort, tGoodFellow, tUserRandom, tLoginPremium, tLoginPremiumPCRoom, tTraceState, tBonus100Money, tPremiumServerExpirationDate, &tPlayUserIndex, &tAuthInfo); // tPremiumServerExpirationDate 추가. // @_Premium_Server_@
	mTRANSFER.B_REGISTER_USER_FOR_LOGIN_RECV(tResult, tPlayUserIndex);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

}
//W_REGISTER_USER_FOR_LOGIN_2_SEND
void W_REGISTER_USER_FOR_LOGIN_2_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 1)
	{
		mUSER[tUserIndex].Quit(3005);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tPlayUserIndex;
	char tID[MAX_USER_ID_LENGTH];
	CopyMemory(&tPlayUserIndex, &tPacket[1], 4);
	CopyMemory(&tID[0], &tPacket[5], MAX_USER_ID_LENGTH);
	tID[(MAX_USER_ID_LENGTH - 1)] = '\0';

	int tResult;

	tResult = mGAME.RegisterUserForLogin_02(tPlayUserIndex, &tID[0]);
	mTRANSFER.B_REGISTER_USER_FOR_LOGIN_RECV(tResult, tPlayUserIndex);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_REGISTER_USER_FOR_LOGIN_3_SEND
void W_REGISTER_USER_FOR_LOGIN_3_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 1)
	{
		mUSER[tUserIndex].Quit(3006);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tPlayUserIndex;
	char tID[MAX_USER_ID_LENGTH];
	AVATAR_INFO tAvatarInfo;
	CopyMemory(&tPlayUserIndex, &tPacket[1], 4);
	CopyMemory(&tID[0], &tPacket[5], MAX_USER_ID_LENGTH);
	tID[(MAX_USER_ID_LENGTH - 1)] = '\0';
	CopyMemory(&tAvatarInfo, &tPacket[(5 + MAX_USER_ID_LENGTH)], sizeof(AVATAR_INFO));
	mGAME.SafeAvatarInfoData(&tAvatarInfo);

	int tResult;

	tResult = mGAME.RegisterUserForLogin_03(tPlayUserIndex, &tID[0], &tAvatarInfo);
	mTRANSFER.B_REGISTER_USER_FOR_LOGIN_RECV(tResult, tPlayUserIndex);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_UNREGISTER_USER_FOR_LOGIN_SEND
void W_UNREGISTER_USER_FOR_LOGIN_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 1)
	{
		mUSER[tUserIndex].Quit(3007);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tPlayUserIndex;
	char tID[MAX_USER_ID_LENGTH];
	CopyMemory(&tPlayUserIndex, &tPacket[1], 4);
	CopyMemory(&tID[0], &tPacket[5], MAX_USER_ID_LENGTH);
	tID[(MAX_USER_ID_LENGTH - 1)] = '\0';

	mGAME.UnRegisterUserForLogin(tPlayUserIndex, &tID[0]);
	mTRANSFER.B_UNREGISTER_USER_FOR_LOGIN_RECV();
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_GET_PRESENT_USER_NUM_FOR_LOGIN_SEND
void W_GET_PRESENT_USER_NUM_FOR_LOGIN_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 1)
	{
		mUSER[tUserIndex].Quit(3008);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tPresentUserNum;

	tPresentUserNum = mGAME.ReturnPresentUserNum(0);
	mTRANSFER.B_GET_PRESENT_USER_NUM_FOR_LOGIN_RECV(tPresentUserNum);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_BLOCK_USER_FOR_LOGIN_1_SEND
void W_BLOCK_USER_FOR_LOGIN_1_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 1)
	{
		mUSER[tUserIndex].Quit(3009);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tSort;
	char tID[MAX_USER_ID_LENGTH];
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tID[0], &tPacket[5], MAX_USER_ID_LENGTH);
	tID[(MAX_USER_ID_LENGTH - 1)] = '\0';

	int tResult;

	tResult = 0;
	if (!mDB.DB_PROCESS_06(&tID[0], tSort, ""))
	{
		tResult = 1;
	}
	mTRANSFER.B_BLOCK_USER_FOR_LOGIN_RECV(tResult);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_BLOCK_USER_FOR_LOGIN_2_SEND
void W_BLOCK_USER_FOR_LOGIN_2_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 1)
	{
		mUSER[tUserIndex].Quit(3010);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tSort;
	char tID[MAX_USER_ID_LENGTH];
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tID[0], &tPacket[5], MAX_USER_ID_LENGTH);
	tID[(MAX_USER_ID_LENGTH - 1)] = '\0';

	int tResult;

	tResult = 0;
	if (!mDB.DB_PROCESS_07(&tID[0], tSort, ""))
	{
		tResult = 1;
	}
	mTRANSFER.B_BLOCK_USER_FOR_LOGIN_RECV(tResult);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//--------------//
//ZONE->PLAYUSER//
//--------------//
//W_ZONE_FOR_PLAYUSER_SEND
void W_ZONE_FOR_PLAYUSER_SEND(int tUserIndex)
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
void W_ZONE_OK_FOR_PLAYUSER_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(4004);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();
}
//W_REGISTER_USER_FOR_ZONE_0_SEND
void W_REGISTER_USER_FOR_ZONE_0_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(4005);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	char tID[MAX_USER_ID_LENGTH];
	CopyMemory(&tID[0], &tPacket[1], MAX_USER_ID_LENGTH);
	tID[(MAX_USER_ID_LENGTH - 1)] = '\0';

	int tResult;
	int tPlayUserIndex;

	tResult = mGAME.RegisterUserForZone_00(mUSER[tUserIndex].mZoneServerNumber, &tID[0], &tPlayUserIndex);
	mTRANSFER.B_REGISTER_USER_FOR_ZONE_0_RECV(tResult, tPlayUserIndex);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_REGISTER_USER_FOR_ZONE_1_SEND
void W_REGISTER_USER_FOR_ZONE_1_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(4006);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tPlayUserIndex;
	char tID[MAX_USER_ID_LENGTH];
	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	int tLogoutInfo[6];
	CopyMemory(&tPlayUserIndex, &tPacket[1], 4);
	CopyMemory(&tID[0], &tPacket[5], MAX_USER_ID_LENGTH);
	tID[(MAX_USER_ID_LENGTH - 1)] = '\0';
	CopyMemory(&tAvatarName[0], &tPacket[(5 + MAX_USER_ID_LENGTH)], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
	CopyMemory(&tLogoutInfo[0], &tPacket[(5 + MAX_USER_ID_LENGTH + MAX_AVATAR_NAME_LENGTH)], 24);

	int tResult;
	int tUserSort;
	int tGoodFellow;
	int tUserRandom;
	int tLoginPremium;
	int tLoginPremiumPCRoom;
	int tTraceState;
	char tBonus100Money;
	int tPremiumServerExpirationDate;
	int AnimalOn;// 프리미엄 서버(월드) 입장권 유효 기한(YYYYMMDD 형태의 정수). // @_Premium_Server_@
	AVATAR_INFO tAvatarInfo;
	int tEffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2];
	int tCheckFirstZone;
	AUTH_INFO tAuthInfo;
	MOVE_ITEM_INFO tMoveItemInfo = mGAME.mMoveItemInfo[tPlayUserIndex];



	tResult = mGAME.RegisterUserForZone_01(mUSER[tUserIndex].mZoneServerNumber, tPlayUserIndex, &tID[0], &tAvatarName[0], &tLogoutInfo[0], &tUserSort, &tGoodFellow, &tUserRandom, &tLoginPremium, &tLoginPremiumPCRoom, &tTraceState, &tBonus100Money, &tPremiumServerExpirationDate, &tAvatarInfo, tEffectValue, &tCheckFirstZone, &tAuthInfo, &AnimalOn); // &tPremiumServerExpirationDate 추가. // @_Premium_Server_@
	mTRANSFER.B_REGISTER_USER_FOR_ZONE_1_RECV(tResult, tUserSort, tGoodFellow, tUserRandom, tLoginPremium, tLoginPremiumPCRoom, tTraceState, tBonus100Money, tPremiumServerExpirationDate, &tAvatarInfo, tEffectValue, tCheckFirstZone, &tAuthInfo, &tMoveItemInfo, AnimalOn); // tPremiumServerExpirationDate 추가. // @_Premium_Server_@ // 이동서 사용 정보(&tMoveItemInfo) 추가.
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_REGISTER_USER_FOR_ZONE_2_SEND
void W_REGISTER_USER_FOR_ZONE_2_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(4007);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tPlayUserIndex;
	char tID[MAX_USER_ID_LENGTH];
	AVATAR_INFO tAvatarInfo;
	int tEffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2];
	AUTH_INFO tAuthInfo;
	CopyMemory(&tPlayUserIndex, &tPacket[1], 4);
	CopyMemory(&tID[0], &tPacket[5], MAX_USER_ID_LENGTH);
	tID[(MAX_USER_ID_LENGTH - 1)] = '\0';
	CopyMemory(&tAvatarInfo, &tPacket[(5 + MAX_USER_ID_LENGTH)], sizeof(AVATAR_INFO));
	mGAME.SafeAvatarInfoData(&tAvatarInfo);
	CopyMemory(tEffectValue, &tPacket[(5 + MAX_USER_ID_LENGTH + sizeof(AVATAR_INFO))], (MAX_AVATAR_EFFECT_SORT_NUM * 8));
	CopyMemory(&tAuthInfo, &tPacket[(5 + MAX_USER_ID_LENGTH + sizeof(AVATAR_INFO) + (MAX_AVATAR_EFFECT_SORT_NUM * 8))], sizeof(AUTH_INFO));

	int tResult;
	tResult = mGAME.RegisterUserForZone_02(mUSER[tUserIndex].mZoneServerNumber, tPlayUserIndex, &tID[0], &tAvatarInfo, tEffectValue, &tAuthInfo);
	//__LogMgr()->Log("tResult[%d]!!!",tResult);
	mTRANSFER.B_REGISTER_USER_FOR_ZONE_2_RECV(tResult);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_REGISTER_USER_FOR_ZONE_3_SEND
void W_REGISTER_USER_FOR_ZONE_3_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(4008);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tPlayUserIndex;
	char tID[MAX_USER_ID_LENGTH];
	AVATAR_INFO tAvatarInfo;
	int tEffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2];
	AUTH_INFO tAuthInfo;
	int AnimalOn;
	CopyMemory(&tPlayUserIndex, &tPacket[1], 4);
	CopyMemory(&tID[0], &tPacket[5], MAX_USER_ID_LENGTH);
	tID[(MAX_USER_ID_LENGTH - 1)] = '\0';
	CopyMemory(&tAvatarInfo, &tPacket[(5 + MAX_USER_ID_LENGTH)], sizeof(AVATAR_INFO));
	mGAME.SafeAvatarInfoData(&tAvatarInfo);
	CopyMemory(tEffectValue, &tPacket[(5 + MAX_USER_ID_LENGTH + sizeof(AVATAR_INFO))], (MAX_AVATAR_EFFECT_SORT_NUM * 8));
	CopyMemory(&tAuthInfo, &tPacket[(5 + MAX_USER_ID_LENGTH + sizeof(AVATAR_INFO) + (MAX_AVATAR_EFFECT_SORT_NUM * 8))], sizeof(AUTH_INFO));
	CopyMemory(&AnimalOn, &tPacket[(5 + MAX_USER_ID_LENGTH + sizeof(AVATAR_INFO) + (MAX_AVATAR_EFFECT_SORT_NUM * 8) + sizeof(AUTH_INFO))], 4);
	int tResult;
	tResult = mGAME.RegisterUserForZone_03(mUSER[tUserIndex].mZoneServerNumber, tPlayUserIndex, &tID[0], &tAvatarInfo, tEffectValue, &tAuthInfo, AnimalOn);
	mTRANSFER.B_REGISTER_USER_FOR_ZONE_3_RECV(tResult);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_UNREGISTER_USER_FOR_ZONE_SEND
void W_UNREGISTER_USER_FOR_ZONE_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(4009);
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
	mGAME.SafeAvatarInfoData(&tAvatarInfo);
	mGAME.UnRegisterUserForZone(mUSER[tUserIndex].mZoneServerNumber, tPlayUserIndex, &tID[0], &tAvatarInfo, &tAuthInfo);
	mTRANSFER.B_UNREGISTER_USER_FOR_ZONE_RECV();
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//void W_DUPEFIX
void W_DUPEFIX(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];

	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(3131);
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
	mGAME.SafeAvatarInfoData(&tAvatarInfo);
	mDB.DB_PROCESS_DUPE(&tID[0], &tAvatarInfo, &tAuthInfo);
}
//void W_DUPEFIX1
void W_DUPEFIX1(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(3131);
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
	mGAME.SafeAvatarInfoData(&tAvatarInfo);
	mGAME.UnRegisterUserForZone(mUSER[tUserIndex].mZoneServerNumber, tPlayUserIndex, &tID[0], &tAvatarInfo, &tAuthInfo);
	mTRANSFER.B_DUPEFIX1();
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_FIND_AVATAR_FOR_ZONE_SEND
void W_FIND_AVATAR_FOR_ZONE_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(4010);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory(&tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';

	int tZoneNumber;
	int tTribe;

	tZoneNumber = mGAME.ReturnExistZoneNumberForAvatarName(&tAvatarName[0], &tTribe);
	mTRANSFER.B_FIND_AVATAR_FOR_ZONE_RECV(tZoneNumber, tTribe);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_TRIBE_BANK_INFO_SAVE_SEND
void W_TRIBE_BANK_INFO_SAVE_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(4011);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tMoney[4];
	CopyMemory(&tMoney[0], &tPacket[1], 16);

	int index01;
	int index02;

	for (index01 = 0; index01 < 4; index01++)
	{
		if (tMoney[index01] < 1)
		{
			continue;
		}
		for (index02 = 0; index02 < MAX_TRIBE_BANK_SLOT_NUM; index02++)
		{
			if (!mGAME.CheckOverMaximum(mGAME.mTribeBankInfo[index01][index02], tMoney[index01]))
			{
				break;
			}
		}
		if (index02 < MAX_TRIBE_BANK_SLOT_NUM)
		{
			mGAME.mTribeBankInfo[index01][index02] += tMoney[index01];
		}
		else
		{
			for (index02 = 0; index02 < MAX_TRIBE_BANK_SLOT_NUM; index02++)
			{
				if (mGAME.mTribeBankInfo[index01][index02] < MAX_NUMBER_SIZE)
				{
					break;
				}
			}
			if (index02 < MAX_TRIBE_BANK_SLOT_NUM)
			{
				mGAME.mTribeBankInfo[index01][index02] = MAX_NUMBER_SIZE;
			}
		}
	}
	mGAME.SaveForTribeBankInfo();
	mTRANSFER.B_TRIBE_BANK_INFO_SAVE_RECV();
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_TRIBE_BANK_INFO_VIEW_SEND
void W_TRIBE_BANK_INFO_VIEW_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(4012);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tTribe;
	CopyMemory(&tTribe, &tPacket[1], 4);

	int index01;
	int tTribeBankInfo[MAX_TRIBE_BANK_SLOT_NUM];

	if ((tTribe < 0) || (tTribe > 3))
	{
		mTRANSFER.B_TRIBE_BANK_INFO_VIEW_RECV(1, &tTribeBankInfo[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	for (index01 = 0; index01 < MAX_TRIBE_BANK_SLOT_NUM; index01++)
	{
		tTribeBankInfo[index01] = mGAME.mTribeBankInfo[tTribe][index01];
	}
	mTRANSFER.B_TRIBE_BANK_INFO_VIEW_RECV(0, &tTribeBankInfo[0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_TRIBE_BANK_INFO_LOAD_SEND
void W_TRIBE_BANK_INFO_LOAD_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(4013);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tTribe;
	int tTribeBankInfoIndex;
	int tInventoryMoney;
	CopyMemory(&tTribe, &tPacket[1], 4);
	CopyMemory(&tTribeBankInfoIndex, &tPacket[5], 4);
	CopyMemory(&tInventoryMoney, &tPacket[9], 4);

	if ((tTribe < 0) || (tTribe > 3) || (tTribeBankInfoIndex < 0) || (tTribeBankInfoIndex > (MAX_TRIBE_BANK_SLOT_NUM - 1)) || (tInventoryMoney < 0))
	{
		mTRANSFER.B_TRIBE_BANK_INFO_LOAD_RECV(1, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mGAME.mTribeBankInfo[tTribe][tTribeBankInfoIndex] < 1)
	{
		mTRANSFER.B_TRIBE_BANK_INFO_LOAD_RECV(2, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mGAME.CheckOverMaximum(tInventoryMoney, mGAME.mTribeBankInfo[tTribe][tTribeBankInfoIndex]))
	{
		mTRANSFER.B_TRIBE_BANK_INFO_LOAD_RECV(3, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	tInventoryMoney += mGAME.mTribeBankInfo[tTribe][tTribeBankInfoIndex];
	mGAME.mTribeBankInfo[tTribe][tTribeBankInfoIndex] = 0;
	mGAME.SaveForTribeBankInfo();
	mTRANSFER.B_TRIBE_BANK_INFO_LOAD_RECV(0, tInventoryMoney);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_HACK_NAME_SEND
void W_HACK_NAME_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(4014);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	char tID[MAX_USER_ID_LENGTH];
	char tHackName[MAX_HACK_NAME_LENGTH];
	int tHackSize;
	CopyMemory(&tID[0], &tPacket[1], MAX_USER_ID_LENGTH);
	tID[(MAX_USER_ID_LENGTH - 1)] = '\0';
	CopyMemory(&tHackName[0], &tPacket[(1 + MAX_USER_ID_LENGTH)], MAX_HACK_NAME_LENGTH);
	tHackName[(MAX_HACK_NAME_LENGTH - 1)] = '\0';
	CopyMemory(&tHackSize, &tPacket[(1 + MAX_USER_ID_LENGTH + MAX_HACK_NAME_LENGTH)], 4);

	mDB.DB_PROCESS_07(&tID[0], tHackSize, &tHackName[0]);
	mTRANSFER.B_HACK_NAME_RECV(0);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_BLOCK_USER_FOR_ZONE_1_SEND
void W_BLOCK_USER_FOR_ZONE_1_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(4015);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tSort;
	char tID[MAX_USER_ID_LENGTH];
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tID[0], &tPacket[5], MAX_USER_ID_LENGTH);
	tID[(MAX_USER_ID_LENGTH - 1)] = '\0';

	int tResult;

	tResult = 0;
	if (!mDB.DB_PROCESS_06(&tID[0], tSort, ""))
	{
		tResult = 1;
	}
	mTRANSFER.B_BLOCK_USER_FOR_ZONE_RECV(tResult);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_BLOCK_USER_FOR_ZONE_2_SEND
void W_BLOCK_USER_FOR_ZONE_2_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(4016);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tSort;
	char tID[MAX_USER_ID_LENGTH];
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tID[0], &tPacket[5], MAX_USER_ID_LENGTH);
	tID[(MAX_USER_ID_LENGTH - 1)] = '\0';

	int tResult;

	tResult = 0;
	if (!mDB.DB_PROCESS_07(&tID[0], tSort, ""))
	{
		tResult = 1;
	}
	mTRANSFER.B_BLOCK_USER_FOR_ZONE_RECV(tResult);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_ADD_AUTO_USER_LIST_SEND
void W_ADD_AUTO_USER_LIST_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(4017);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	char tID[MAX_USER_ID_LENGTH];
	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	int tWorldNumber;
	int tZoneNumber;
	CopyMemory(&tID[0], &tPacket[1], MAX_USER_ID_LENGTH);
	tID[(MAX_USER_ID_LENGTH - 1)] = '\0';
	CopyMemory(&tAvatarName[0], &tPacket[(1 + MAX_USER_ID_LENGTH)], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
	CopyMemory(&tWorldNumber, &tPacket[(1 + MAX_USER_ID_LENGTH + MAX_AVATAR_NAME_LENGTH)], 4);
	CopyMemory(&tZoneNumber, &tPacket[(5 + MAX_USER_ID_LENGTH + MAX_AVATAR_NAME_LENGTH)], 4);

	int tResult;

	tResult = 0;
	if (!mDB.DB_PROCESS_08(&tID[0], &tAvatarName[0], tWorldNumber, tZoneNumber))
	{
		tResult = 1;
	}
	mTRANSFER.B_ADD_AUTO_USER_LIST_RECV(tResult);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_CHECK_KILL_OTHER_TRIBE_SEND
void W_CHECK_KILL_OTHER_TRIBE_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(4018);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	char tAvatarName1[MAX_AVATAR_NAME_LENGTH];
	char tAvatarName2[MAX_AVATAR_NAME_LENGTH];
	CopyMemory(&tAvatarName1[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH);
	tAvatarName1[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
	CopyMemory(&tAvatarName2[0], &tPacket[(1 + MAX_AVATAR_NAME_LENGTH)], MAX_AVATAR_NAME_LENGTH);
	tAvatarName2[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';

	int tResult;

	tResult = mGAME.ProcessKillOtherTribe(&tAvatarName1[0], &tAvatarName2[0]);
	mTRANSFER.B_CHECK_KILL_OTHER_TRIBE_RECV(tResult);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_EVENT_INFO_SEND
void W_EVENT_INFO_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(4019);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	char tID[MAX_USER_ID_LENGTH];
	int tSort;
	CopyMemory(&tID[0], &tPacket[1], MAX_USER_ID_LENGTH);
	tID[(MAX_USER_ID_LENGTH - 1)] = '\0';
	CopyMemory(&tSort, &tPacket[(1 + MAX_USER_ID_LENGTH)], 4);

	mDB.DB_PROCESS_09(&tID[0], tSort);
	mTRANSFER.B_EVENT_INFO_RECV();
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
void W_CHECK_AUTH_KEY(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(4019);
		return;
	}

	BYTE bResult = 0;

	ZTOP_CHECK_AUTH_KEY pack;
	::CopyMemory(&pack, tPacket, ZTOP_CHECK_AUTH_KEY_SIZE);
	mDB.DB_COMPARE_AUTH_KEY(pack.m_szUserID, pack.m_szAuthKey, bResult);

	mTRANSFER.B_CHECK_AUTH_KEY(bResult);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}

void W_UPDATE_AUTH_KEY(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(4019);
		return;
	}

	BYTE bResult = 0;

	ZTOP_UPDATE_AUTH_KEY pack;
	::CopyMemory(&pack, tPacket, ZTOP_UPDATE_AUTH_KEY_SIZE);
	mDB.DB_UPDATE_AUTH_KEY(pack.m_szUserID, pack.m_szAuthKey, bResult);

	mTRANSFER.B_UPDATE_AUTH_KEY(bResult);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
void W_CHANGE_AVATAR_NAME_FOR_ZONE_SEND(int tUserIndex) {
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(4020);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tPlayUserIndex;
	char tChangeAvatarName[MAX_AVATAR_NAME_LENGTH];
	int tResult;

	CopyMemory(&tPlayUserIndex, &tPacket[1], 4);
	CopyMemory(&tChangeAvatarName[0], &tPacket[5], MAX_AVATAR_NAME_LENGTH);
	tChangeAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';

	tResult = mGAME.ChangeAvatarNameForZone(tPlayUserIndex, tChangeAvatarName);
	mTRANSFER.B_CHANGE_AVATAR_NAME_FOR_ZONE_RECV(tResult);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
void W_BONUS_100_MONEY_FOR_ZONE_SEND(int tUserIndex) {
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(4020);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tPlayUserIndex;
	int tResult;

	CopyMemory(&tPlayUserIndex, &tPacket[1], 4);

	tResult = mGAME.Bonus100Money(tPlayUserIndex);
	mTRANSFER.B_BONUS_100_MONEY_FOR_ZONE_RECV(tResult);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
#ifdef __EVENT_KILL__
void W_EVENT_FOR_ZONE_SEND(int tUserIndex) {
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(4020);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tPlayUserIndex = -1;
	int tKillNum = 0;

	CopyMemory(&tPlayUserIndex, &tPacket[1], 4);
	CopyMemory(&tKillNum, &tPacket[5], 4);

	if (0 >= tKillNum)
		return;

	mDB.DB_PROCESS_15(mGAME.mID[tPlayUserIndex], mGAME.mAvatarInfo[tPlayUserIndex].aName, mGAME.mAvatarInfo[tPlayUserIndex].aTribe, tKillNum);
}
#elif __EVENT_GOLD_PHONE__
void W_EVENT_FOR_ZONE_SEND(int tUserIndex) {
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(4020);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tPlayUserIndex = -1;

	CopyMemory(&tPlayUserIndex, &tPacket[1], 4);
	mDB.DB_PROCESS_15(mGAME.mID[tPlayUserIndex], mGAME.mAvatarInfo[tPlayUserIndex].aName);
}
#endif
// 이동서를 사용중인 지 여부를 설정하는 함수.
void W_SET_MOVE_ITEM_FOR_ZONE_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(4021);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tPlayUserIndex;
	CopyMemory(&tPlayUserIndex, &tPacket[1], 4);
	CopyMemory(&mGAME.mMoveItemInfo[tPlayUserIndex], &tPacket[5], sizeof(MOVE_ITEM_INFO));
}


//--------------//
//TOOL->PLAYUSER//
//--------------//
//W_TOOL_FOR_PLAYUSER_SEND
void W_TOOL_FOR_PLAYUSER_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 0)
	{
		mUSER[tUserIndex].Quit(5001);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	mUSER[tUserIndex].mCheckServerType = 3;
	mTRANSFER.B_TOOL_FOR_PLAYUSER_RECV();
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_TOOL_OK_FOR_PLAYUSER_SEND
void W_TOOL_OK_FOR_PLAYUSER_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 3)
	{
		mUSER[tUserIndex].Quit(5002);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();
}
//W_CHANGE_LOGIN_USER_NUM_SEND
void W_CHANGE_LOGIN_USER_NUM_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 3)
	{
		mUSER[tUserIndex].Quit(5003);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tUserNum;
	CopyMemory(&tUserNum, &tPacket[1], 4);

	int tResult;

	tResult = 0;
	if (!mDB.DB_PROCESS_05(tUserNum))
	{
		tResult = 1;
	}
	mTRANSFER.B_CHANGE_LOGIN_USER_NUM_RECV(tResult);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_CHECK_ZONE_FOR_TOOL_SEND
void W_CHECK_ZONE_FOR_TOOL_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 3)
	{
		mUSER[tUserIndex].Quit(5004);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tZoneNumber;
	CopyMemory(&tZoneNumber, &tPacket[1], 4);

	int index01;

	for (index01 = 0; index01 < MAX_USER_NUM; index01++)
	{
		if ((mUSER[index01].mCheckServerType == 2) && (mUSER[index01].mZoneServerNumber == tZoneNumber))
		{
			break;
		}
	}
	if (index01 < MAX_USER_NUM)
	{
		mTRANSFER.B_CHECK_ZONE_FOR_TOOL_RECV(1);
	}
	else
	{
		mTRANSFER.B_CHECK_ZONE_FOR_TOOL_RECV(0);
	}
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_GET_PRESENT_USER_NUM_FOR_TOOL_SEND
void W_GET_PRESENT_USER_NUM_FOR_TOOL_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 3)
	{
		mUSER[tUserIndex].Quit(5005);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tZoneNumber;
	CopyMemory(&tZoneNumber, &tPacket[1], 4);

	int tPresentUserNum;

	tPresentUserNum = mGAME.ReturnPresentUserNum(tZoneNumber);
	mTRANSFER.B_GET_PRESENT_USER_NUM_FOR_TOOL_RECV(tPresentUserNum);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_FIND_AVATAR_FOR_TOOL_SEND
void W_FIND_AVATAR_FOR_TOOL_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 3)
	{
		mUSER[tUserIndex].Quit(5006);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory(&tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';

	int tZoneNumber;
	int tTribe;

	tZoneNumber = mGAME.ReturnExistZoneNumberForAvatarName(&tAvatarName[0], &tTribe);
	mTRANSFER.B_FIND_AVATAR_FOR_TOOL_RECV(tZoneNumber);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_FIND_USER_FOR_TOOL_SEND
void W_FIND_USER_FOR_TOOL_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 3)
	{
		mUSER[tUserIndex].Quit(5007);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	char tID[MAX_USER_ID_LENGTH];
	CopyMemory(&tID[0], &tPacket[1], MAX_USER_ID_LENGTH);
	tID[(MAX_USER_ID_LENGTH - 1)] = '\0';

	int tZoneNumber;

	tZoneNumber = mGAME.ReturnExistZoneNumberForUserID(&tID[0]);
	mTRANSFER.B_FIND_USER_FOR_TOOL_RECV(tZoneNumber);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_BLOCK_USER_FOR_TOOL_1_SEND
void W_BLOCK_USER_FOR_TOOL_1_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 3)
	{
		mUSER[tUserIndex].Quit(5008);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tSort;
	char tID[MAX_USER_ID_LENGTH];
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tID[0], &tPacket[5], MAX_USER_ID_LENGTH);
	tID[(MAX_USER_ID_LENGTH - 1)] = '\0';

	int tResult;

	tResult = 0;
	if (!mDB.DB_PROCESS_06(&tID[0], tSort, ""))
	{
		tResult = 1;
	}
	mTRANSFER.B_BLOCK_USER_FOR_TOOL_RECV(tResult);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_BLOCK_USER_FOR_TOOL_2_SEND
void W_BLOCK_USER_FOR_TOOL_2_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 3)
	{
		mUSER[tUserIndex].Quit(5009);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tSort;
	char tID[MAX_USER_ID_LENGTH];
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tID[0], &tPacket[5], MAX_USER_ID_LENGTH);
	tID[(MAX_USER_ID_LENGTH - 1)] = '\0';

	int tResult;

	tResult = 0;
	if (!mDB.DB_PROCESS_07(&tID[0], tSort, ""))
	{
		tResult = 1;
	}
	mTRANSFER.B_BLOCK_USER_FOR_TOOL_RECV(tResult);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_GET_PRESENT_USER_NUM_2_FOR_TOOL_SEND
void W_GET_PRESENT_USER_NUM_2_FOR_TOOL_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 3)
	{
		mUSER[tUserIndex].Quit(5005);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tLength;
	char tPresentUserNum[2048];
	::memset(tPresentUserNum, 0, 2048);

	mGAME.ReturnPresentUserNum(tPresentUserNum + 0);
	tLength = strlen(tPresentUserNum);
	mTRANSFER.B_GET_PRESENT_USER_NUM_2_FOR_TOOL_RECV(tLength, tPresentUserNum);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	//LOG_TO_FILE_2("![%s] : %s\n", __FUNCTION__, mTRANSFER.mOriginal);
}
//----------------------//
//[POLICE] -> [PLAYUSER]//
//----------------------//
//W_POLICE_FOR_PLAYUSER_SEND
void W_POLICE_FOR_PLAYUSER_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 0)
	{
		mUSER[tUserIndex].Quit(6001);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	mUSER[tUserIndex].mCheckServerType = 4;
	mTRANSFER.B_POLICE_FOR_PLAYUSER_RECV();
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_POLICE_OK_FOR_PLAYUSER_SEND
void W_POLICE_OK_FOR_PLAYUSER_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 4)
	{
		mUSER[tUserIndex].Quit(6002);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();
}
//-------------------------------------------------------------------------------------------------
//ValetShop
//W_VALET_SHOP_INFO
void W_CHECK_PLAYER_ONLINE(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if (mUSER[tUserIndex].mCheckServerType != 2)
	{
		mUSER[tUserIndex].Quit(3131);
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();
	int tResult;
	int tPlayUserIndex;
	char aName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory(&tPlayUserIndex, &tPacket[1], 4);
	CopyMemory(&aName[0], &tPacket[5], MAX_AVATAR_NAME_LENGTH);
	aName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';

	tResult = mGAME.ProccesForFindAvatar(tPlayUserIndex, aName);
	mTRANSFER.B_VALETSHOPUPDATE(tResult);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	return;
}

