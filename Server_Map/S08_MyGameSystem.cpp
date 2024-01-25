//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "Shengming.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_LEVELSYSTEM
//-------------------------------------------------------------------------------------------------
//INSTANCE
LEVELSYSTEM mLEVEL;
//CREATE
LEVELSYSTEM::LEVELSYSTEM(void)
{
	int index01;

	for (index01 = 0; index01 < MAX_LIMIT_LEVEL_NUM; index01++)
	{
		mGainExpInfoForKillOtherTribe[index01] = 0.0f;
	}
	mGainExpInfoForKillOtherTribe[0] = 40.0f;
	mGainExpInfoForKillOtherTribe[1] = 40.0f;
	mGainExpInfoForKillOtherTribe[2] = 40.0f;
	mGainExpInfoForKillOtherTribe[3] = 40.0f;
	mGainExpInfoForKillOtherTribe[4] = 40.0f;
	mGainExpInfoForKillOtherTribe[5] = 40.0f;
	mGainExpInfoForKillOtherTribe[6] = 40.0f;
	mGainExpInfoForKillOtherTribe[7] = 40.0f;
	mGainExpInfoForKillOtherTribe[8] = 40.0f;
	mGainExpInfoForKillOtherTribe[9] = 40.0f;
	mGainExpInfoForKillOtherTribe[10] = 40.0f;
	mGainExpInfoForKillOtherTribe[11] = 40.0f;
	mGainExpInfoForKillOtherTribe[12] = 40.0f;
	mGainExpInfoForKillOtherTribe[13] = 40.0f;
	mGainExpInfoForKillOtherTribe[14] = 40.0f;
	mGainExpInfoForKillOtherTribe[15] = 40.0f;
	mGainExpInfoForKillOtherTribe[16] = 40.0f;
	mGainExpInfoForKillOtherTribe[17] = 40.0f;
	mGainExpInfoForKillOtherTribe[18] = 40.0f;
	mGainExpInfoForKillOtherTribe[19] = 40.0f;
	mGainExpInfoForKillOtherTribe[20] = 40.0f;
	mGainExpInfoForKillOtherTribe[21] = 40.0f;
	mGainExpInfoForKillOtherTribe[22] = 40.0f;
	mGainExpInfoForKillOtherTribe[23] = 40.0f;
	mGainExpInfoForKillOtherTribe[24] = 40.0f;
	mGainExpInfoForKillOtherTribe[25] = 40.0f;
	mGainExpInfoForKillOtherTribe[26] = 40.0f;
	mGainExpInfoForKillOtherTribe[27] = 40.0f;
	mGainExpInfoForKillOtherTribe[28] = 40.0f;
	mGainExpInfoForKillOtherTribe[29] = 40.0f;
	mGainExpInfoForKillOtherTribe[30] = 40.0f;
	mGainExpInfoForKillOtherTribe[31] = 40.0f;
	mGainExpInfoForKillOtherTribe[32] = 40.0f;
	mGainExpInfoForKillOtherTribe[33] = 50.0f;
	mGainExpInfoForKillOtherTribe[34] = 50.0f;
	mGainExpInfoForKillOtherTribe[35] = 50.0f;
	mGainExpInfoForKillOtherTribe[36] = 50.0f;
	mGainExpInfoForKillOtherTribe[37] = 50.0f;
	mGainExpInfoForKillOtherTribe[38] = 50.0f;
	mGainExpInfoForKillOtherTribe[39] = 50.0f;
	mGainExpInfoForKillOtherTribe[40] = 50.0f;
	mGainExpInfoForKillOtherTribe[41] = 50.0f;
	mGainExpInfoForKillOtherTribe[42] = 50.0f;
	mGainExpInfoForKillOtherTribe[43] = 50.0f;
	mGainExpInfoForKillOtherTribe[44] = 50.0f;
	mGainExpInfoForKillOtherTribe[45] = 50.0f;
	mGainExpInfoForKillOtherTribe[46] = 50.0f;
	mGainExpInfoForKillOtherTribe[47] = 50.0f;
	mGainExpInfoForKillOtherTribe[48] = 50.0f;
	mGainExpInfoForKillOtherTribe[49] = 50.0f;
	mGainExpInfoForKillOtherTribe[50] = 50.0f;
	mGainExpInfoForKillOtherTribe[51] = 50.0f;
	mGainExpInfoForKillOtherTribe[52] = 50.0f;
	mGainExpInfoForKillOtherTribe[53] = 50.0f;
	mGainExpInfoForKillOtherTribe[54] = 50.0f;
	mGainExpInfoForKillOtherTribe[55] = 50.0f;
	mGainExpInfoForKillOtherTribe[56] = 50.0f;
	mGainExpInfoForKillOtherTribe[57] = 50.0f;
	mGainExpInfoForKillOtherTribe[58] = 50.0f;
	mGainExpInfoForKillOtherTribe[59] = 50.0f;
	mGainExpInfoForKillOtherTribe[60] = 50.0f;
	mGainExpInfoForKillOtherTribe[61] = 50.0f;
	mGainExpInfoForKillOtherTribe[62] = 50.0f;
	mGainExpInfoForKillOtherTribe[63] = 50.0f;
	mGainExpInfoForKillOtherTribe[64] = 50.0f;
	mGainExpInfoForKillOtherTribe[65] = 50.0f;
	mGainExpInfoForKillOtherTribe[66] = 60.0f;
	mGainExpInfoForKillOtherTribe[67] = 60.0f;
	mGainExpInfoForKillOtherTribe[68] = 60.0f;
	mGainExpInfoForKillOtherTribe[69] = 60.0f;
	mGainExpInfoForKillOtherTribe[70] = 60.0f;
	mGainExpInfoForKillOtherTribe[71] = 60.0f;
	mGainExpInfoForKillOtherTribe[72] = 60.0f;
	mGainExpInfoForKillOtherTribe[73] = 60.0f;
	mGainExpInfoForKillOtherTribe[74] = 60.0f;
	mGainExpInfoForKillOtherTribe[75] = 60.0f;
	mGainExpInfoForKillOtherTribe[76] = 60.0f;
	mGainExpInfoForKillOtherTribe[77] = 60.0f;
	mGainExpInfoForKillOtherTribe[78] = 60.0f;
	mGainExpInfoForKillOtherTribe[79] = 60.0f;
	mGainExpInfoForKillOtherTribe[80] = 60.0f;
	mGainExpInfoForKillOtherTribe[81] = 60.0f;
	mGainExpInfoForKillOtherTribe[82] = 60.0f;
	mGainExpInfoForKillOtherTribe[83] = 60.0f;
	mGainExpInfoForKillOtherTribe[84] = 60.0f;
	mGainExpInfoForKillOtherTribe[85] = 60.0f;
	mGainExpInfoForKillOtherTribe[86] = 60.0f;
	mGainExpInfoForKillOtherTribe[87] = 60.0f;
	mGainExpInfoForKillOtherTribe[88] = 60.0f;
	mGainExpInfoForKillOtherTribe[89] = 60.0f;
	mGainExpInfoForKillOtherTribe[90] = 60.0f;
	mGainExpInfoForKillOtherTribe[91] = 60.0f;
	mGainExpInfoForKillOtherTribe[92] = 60.0f;
	mGainExpInfoForKillOtherTribe[93] = 60.0f;
	mGainExpInfoForKillOtherTribe[94] = 60.0f;
	mGainExpInfoForKillOtherTribe[95] = 60.0f;
	mGainExpInfoForKillOtherTribe[96] = 60.0f;
	mGainExpInfoForKillOtherTribe[97] = 60.0f;
	mGainExpInfoForKillOtherTribe[98] = 60.0f;
	mGainExpInfoForKillOtherTribe[99] = 66.0f;
	mGainExpInfoForKillOtherTribe[100] = 66.0f;
	mGainExpInfoForKillOtherTribe[101] = 66.0f;
	mGainExpInfoForKillOtherTribe[102] = 66.0f;
	mGainExpInfoForKillOtherTribe[103] = 72.0f;
	mGainExpInfoForKillOtherTribe[104] = 72.0f;
	mGainExpInfoForKillOtherTribe[105] = 72.0f;
	mGainExpInfoForKillOtherTribe[106] = 78.0f;
	mGainExpInfoForKillOtherTribe[107] = 78.0f;
	mGainExpInfoForKillOtherTribe[108] = 78.0f;
	mGainExpInfoForKillOtherTribe[109] = 84.0f;
	mGainExpInfoForKillOtherTribe[110] = 84.0f;
	mGainExpInfoForKillOtherTribe[111] = 84.0f;
	mGainExpInfoForKillOtherTribe[112] = 90.0f;
	mGainExpInfoForKillOtherTribe[113] = 90.0f;
	mGainExpInfoForKillOtherTribe[114] = 90.0f;
	mGainExpInfoForKillOtherTribe[115] = 90.0f;
	mGainExpInfoForKillOtherTribe[116] = 90.0f;
	mGainExpInfoForKillOtherTribe[117] = 90.0f;
	mGainExpInfoForKillOtherTribe[118] = 90.0f;
	mGainExpInfoForKillOtherTribe[119] = 90.0f;
	mGainExpInfoForKillOtherTribe[120] = 90.0f;
	mGainExpInfoForKillOtherTribe[121] = 90.0f;
	mGainExpInfoForKillOtherTribe[122] = 90.0f;
	mGainExpInfoForKillOtherTribe[123] = 100.0f;
	mGainExpInfoForKillOtherTribe[124] = 100.0f;
	mGainExpInfoForKillOtherTribe[125] = 100.0f;
	mGainExpInfoForKillOtherTribe[126] = 100.0f;
	mGainExpInfoForKillOtherTribe[127] = 100.0f;
	mGainExpInfoForKillOtherTribe[128] = 100.0f;
	mGainExpInfoForKillOtherTribe[129] = 100.0f;
	mGainExpInfoForKillOtherTribe[130] = 100.0f;
	mGainExpInfoForKillOtherTribe[131] = 100.0f;
	mGainExpInfoForKillOtherTribe[132] = 100.0f;
	mGainExpInfoForKillOtherTribe[133] = 100.0f;
	mGainExpInfoForKillOtherTribe[134] = 110.0f;
	mGainExpInfoForKillOtherTribe[135] = 110.0f;
	mGainExpInfoForKillOtherTribe[136] = 110.0f;
	mGainExpInfoForKillOtherTribe[137] = 110.0f;
	mGainExpInfoForKillOtherTribe[138] = 110.0f;
	mGainExpInfoForKillOtherTribe[139] = 110.0f;
	mGainExpInfoForKillOtherTribe[140] = 110.0f;
	mGainExpInfoForKillOtherTribe[141] = 110.0f;
	mGainExpInfoForKillOtherTribe[142] = 110.0f;
	mGainExpInfoForKillOtherTribe[143] = 110.0f;
	mGainExpInfoForKillOtherTribe[144] = 110.0f;
	mGainExpInfoForKillOtherTribe[145] = 330.0f;
	mGainExpInfoForKillOtherTribe[146] = 330.0f;
	mGainExpInfoForKillOtherTribe[147] = 330.0f;
	mGainExpInfoForKillOtherTribe[148] = 330.0f;
	mGainExpInfoForKillOtherTribe[149] = 360.0f;
	mGainExpInfoForKillOtherTribe[150] = 360.0f;
	mGainExpInfoForKillOtherTribe[151] = 360.0f;
	mGainExpInfoForKillOtherTribe[152] = 360.0f;
	mGainExpInfoForKillOtherTribe[153] = 390.0f;
	mGainExpInfoForKillOtherTribe[154] = 390.0f;
	mGainExpInfoForKillOtherTribe[155] = 390.0f;
	mGainExpInfoForKillOtherTribe[156] = 390.0f;
	mRangeForHigh[0] = 962105896;
	mRangeForHigh[1] = 1000590131;
	mRangeForHigh[2] = 1040613736;
	mRangeForHigh[3] = 1082238285;
	mRangeForHigh[4] = 1125527816;
	mRangeForHigh[5] = 1170548928;
	mRangeForHigh[6] = 1217370885;
	mRangeForHigh[7] = 1266065720;
	mRangeForHigh[8] = 1316708348;
	mRangeForHigh[9] = 1369376681;
	mRangeForHigh[10] = 1424151748;
	mRangeForHigh[11] = 1481117817;
}
//CHECK_VALID_ELEMENT
BOOL LEVELSYSTEM::CheckValidElement(int tArrayIndex)
{

	if ((mDATA[tArrayIndex].lIndex < 1) || (mDATA[tArrayIndex].lIndex > MAX_LIMIT_LEVEL_NUM))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mDATA[tArrayIndex].lIndex != (tArrayIndex + 1))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].lRangeInfo[0] < 0) || (mDATA[tArrayIndex].lRangeInfo[0] > MAX_NUMBER_SIZE))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].lRangeInfo[1] < 1) || (mDATA[tArrayIndex].lRangeInfo[1] > MAX_NUMBER_SIZE))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mDATA[tArrayIndex].lRangeInfo[0] >= mDATA[tArrayIndex].lRangeInfo[1])
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (tArrayIndex < 144)
	{
		if (mDATA[tArrayIndex].lRangeInfo[1] != (mDATA[(tArrayIndex + 1)].lRangeInfo[0] - 1))
		{
			printf("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	if ((mDATA[tArrayIndex].lRangeInfo[2] < 0) || (mDATA[tArrayIndex].lRangeInfo[2] > 100))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].lAttackPower < 0) || (mDATA[tArrayIndex].lAttackPower > 10000))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].lDefensePower < 0) || (mDATA[tArrayIndex].lDefensePower > 10000))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].lAttackSuccess < 0) || (mDATA[tArrayIndex].lAttackSuccess > 10000))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].lAttackBlock < 0) || (mDATA[tArrayIndex].lAttackBlock > 10000))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].lElementAttack < 0) || (mDATA[tArrayIndex].lElementAttack > 10000))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].lLife < 0) || (mDATA[tArrayIndex].lLife > 10000))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].lMana < 0) || (mDATA[tArrayIndex].lMana > 10000))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	return TRUE;
}
//INIT
BOOL LEVELSYSTEM::Init(char* tFileName)
{
	int index01;
	DWORD nReadByte;
	DWORD tOriginalSize;
	BYTE* tOriginal;
	DWORD tCompressSize;
	BYTE* tCompress;
	int tDataNum;

	Free();

	HANDLE hFile;
	hFile = CreateFile(tFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	if (!ReadFile(hFile, &tOriginalSize, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	tOriginal = (BYTE*)GlobalAlloc(GMEM_FIXED, tOriginalSize);
	if (tOriginal == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!ReadFile(hFile, &tCompressSize, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	tCompress = (BYTE*)GlobalAlloc(GMEM_FIXED, tCompressSize);
	if (tCompress == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!ReadFile(hFile, tCompress, tCompressSize, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != tCompressSize)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!CloseHandle(hFile))
	{
		return FALSE;
	}

	if (!mGAME.Decompress(tCompressSize, tCompress, tOriginalSize, tOriginal))
	{
		return FALSE;
	}

	CopyMemory(&tDataNum, &tOriginal[0], 4);
	tDataNum = 145;
	if (tDataNum != MAX_LIMIT_LEVEL_NUM)
	{
		return FALSE;
	}

	CopyMemory(&mDATA[0], &tOriginal[14], (tDataNum * sizeof(LEVEL_INFO)));
	GlobalFree(tCompress);
	GlobalFree(tOriginal);

	for (index01 = 0; index01 < tDataNum; index01++)
	{
		if (!CheckValidElement(index01))
		{
			printf("! [%s] %d", __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	return TRUE;
}
//FREE
void LEVELSYSTEM::Free(void)
{
}
//RETURN_LEVEL
int LEVELSYSTEM::ReturnLevel(int tGeneralExperience)
{
	int index01;

	if (tGeneralExperience < mDATA[0].lRangeInfo[0])
	{
		return 1;
	}
	for (index01 = 0; index01 < (MAX_LIMIT_LEVEL_NUM - 1); index01++)
	{
		if ((tGeneralExperience >= mDATA[index01].lRangeInfo[0]) && (tGeneralExperience <= mDATA[index01].lRangeInfo[1]))
		{
			return (index01 + 1);
		}
	}
	return MAX_LIMIT_LEVEL_NUM;
}
//RETURN_LEVEL_FACTOR_1
int LEVELSYSTEM::ReturnLevelFactor1(int tLevel)
{
	if ((tLevel < 1) || (tLevel > MAX_LIMIT_LEVEL_NUM))
	{
		return 0;
	}
	return mDATA[(tLevel - 1)].lRangeInfo[0];
}
//RETURN_LEVEL_FACTOR_2
int LEVELSYSTEM::ReturnLevelFactor2(int tLevel)
{
	if ((tLevel < 1) || (tLevel > MAX_LIMIT_LEVEL_NUM))
	{
		return 0;
	}
	return mDATA[(tLevel - 1)].lRangeInfo[1];
}
//RETURN_LEVEL_FACTOR_3
int LEVELSYSTEM::ReturnLevelFactor3(int tLevel)
{
	if ((tLevel < 1) || (tLevel > MAX_LIMIT_LEVEL_NUM))
	{
		return 0;
	}

	return mDATA[(tLevel - 1)].lRangeInfo[2];
}
//RETURN_LEVEL_FACTOR_ATTACK_POWER
int LEVELSYSTEM::ReturnLevelFactorAttackPower(int tLevel)
{
	if ((tLevel < 1) || (tLevel > (MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM)))
	{
		return 0;
	}
#ifdef __GOD__
	if (tLevel > MAX_LIMIT_LEVEL_NUM)
		tLevel = MAX_LIMIT_LEVEL_NUM;
#endif
	return mDATA[(tLevel - 1)].lAttackPower;
}
//RETURN_LEVEL_FACTOR_DEFENSE_POWER
int LEVELSYSTEM::ReturnLevelFactorDefensePower(int tLevel)
{
#ifdef __GOD__
	if ((tLevel < 1) || (tLevel > (MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM)))
#else
	if ((tLevel < 1) || (tLevel > MAX_LIMIT_LEVEL_NUM))
#endif
	{
		return 0;
	}
#ifdef __GOD__
	if (tLevel > MAX_LIMIT_LEVEL_NUM)
		tLevel = MAX_LIMIT_LEVEL_NUM;
#endif
	return mDATA[(tLevel - 1)].lDefensePower;
}
//RETURN_LEVEL_FACTOR_ATTACK_SUCCESS
int LEVELSYSTEM::ReturnLevelFactorAttackSuccess(int tLevel)
{
#ifdef __GOD__
	if ((tLevel < 1) || (tLevel > (MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM)))
#else
	if ((tLevel < 1) || (tLevel > MAX_LIMIT_LEVEL_NUM))
#endif
	{
		return 0;
	}
#ifdef __GOD__
	if (tLevel > MAX_LIMIT_LEVEL_NUM)
		tLevel = MAX_LIMIT_LEVEL_NUM;
#endif
	return mDATA[(tLevel - 1)].lAttackSuccess;
}
//RETURN_LEVEL_FACTOR_ATTACK_BLOCK
int LEVELSYSTEM::ReturnLevelFactorAttackBlock(int tLevel)
{
#ifdef __GOD__
	if ((tLevel < 1) || (tLevel > (MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM)))
#else
	if ((tLevel < 1) || (tLevel > MAX_LIMIT_LEVEL_NUM))
#endif
	{
		return 0;
	}
#ifdef __GOD__
	if (tLevel > MAX_LIMIT_LEVEL_NUM)
		tLevel = MAX_LIMIT_LEVEL_NUM;
#endif
	return mDATA[(tLevel - 1)].lAttackBlock;
}
//RETURN_LEVEL_FACTOR_ELEMENT_ATTACK
int LEVELSYSTEM::ReturnLevelFactorElementAttack(int tLevel)
{
#ifdef __GOD__
	if ((tLevel < 1) || (tLevel > (MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM)))
#else
	if ((tLevel < 1) || (tLevel > MAX_LIMIT_LEVEL_NUM))
#endif
	{
		return 0;
	}
#ifdef __GOD__
	if (tLevel > MAX_LIMIT_LEVEL_NUM)
		tLevel = MAX_LIMIT_LEVEL_NUM;
#endif
	return mDATA[(tLevel - 1)].lElementAttack;
}
//RETURN_LEVEL_FACTOR_LIFE
int LEVELSYSTEM::ReturnLevelFactorLife(int tLevel)
{
#ifdef __GOD__
	if ((tLevel < 1) || (tLevel > (MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM)))
#else
	if ((tLevel < 1) || (tLevel > MAX_LIMIT_LEVEL_NUM))
#endif
	{
		return 0;
	}
#ifdef __GOD__
	if (tLevel > MAX_LIMIT_LEVEL_NUM)
		tLevel = MAX_LIMIT_LEVEL_NUM;
#endif
	return mDATA[(tLevel - 1)].lLife;
}
//RETURN_LEVEL_FACTOR_MANA
int LEVELSYSTEM::ReturnLevelFactorMana(int tLevel)
{
#ifdef __GOD__
	if ((tLevel < 1) || (tLevel > (MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM)))
#else
	if ((tLevel < 1) || (tLevel > MAX_LIMIT_LEVEL_NUM))
#endif
	{
		return 0;
	}
#ifdef __GOD__
	if (tLevel > MAX_LIMIT_LEVEL_NUM)
		tLevel = MAX_LIMIT_LEVEL_NUM;
#endif
	return mDATA[(tLevel - 1)].lMana;
}

#ifdef __GOD__
//RETURN_HIGH_EXP_VALUE
int LEVELSYSTEM::ReturnHighExpValue(int tLevel)
{
	if ((tLevel < 1) || (tLevel > MAX_LIMIT_HIGH_LEVEL_NUM))
	{
		return 0;
	}
	return mRangeForHigh[(tLevel - 1)];
}
#endif

//RETURN_GAIN_EXP_FOR_KILL_OTHER_TRIBE
int LEVELSYSTEM::ReturnGainExpForKillOtherTribe(int tAttackLevel, int tDefenseLevel)
{
	if ((tAttackLevel < 1) || (tAttackLevel > (MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM)) || (tDefenseLevel < 1) || (tDefenseLevel > (MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM)) || ((tAttackLevel - tDefenseLevel) > 9))
	{
		return 0;
	}
	if (tAttackLevel < tDefenseLevel)
	{
		return (int)(mGainExpInfoForKillOtherTribe[(tDefenseLevel - 1)] + (mGainExpInfoForKillOtherTribe[(tDefenseLevel - 1)] * ((float)(tDefenseLevel - tAttackLevel) * 0.1f)));
	}
	else
	{
		return (int)(mGainExpInfoForKillOtherTribe[(tDefenseLevel - 1)] - (mGainExpInfoForKillOtherTribe[(tDefenseLevel - 1)] * ((float)(tAttackLevel - tDefenseLevel) * 0.1f)));
	}
	return 0;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_ITEMSYSTEM
//-------------------------------------------------------------------------------------------------
//INSTANCE
ITEMSYSTEM mITEM;
//CREATE
ITEMSYSTEM::ITEMSYSTEM(void)
{
	int index01;
	int index02;
	int index03;

	mDataNum = 0;
	mDATA = NULL;
	for (index01 = 0; index01 < MAX_LIMIT_LEVEL_NUM; index01++)
	{
		for (index02 = 0; index02 < 6; index02++)
		{
			for (index03 = 0; index03 < 32; index03++)
			{
				mPartNum[index01][index02][index03] = 0;
				mPART[index01][index02][index03] = NULL;
			}
		}
	}
	//mSharedMemMap = NULL;
	mSharedMemMap = 0;
	mSharedPostMem = NULL;
}
//CHECK_VALID_ELEMENT
BOOL ITEMSYSTEM::CheckValidElement(int tArrayIndex)
{
	int index01;
	int index02;

	if (mDATA[tArrayIndex].iIndex == 0)
	{
		return TRUE;
	}
	if ((mDATA[tArrayIndex].iIndex < 1) || (mDATA[tArrayIndex].iIndex > 99999))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mDATA[tArrayIndex].iIndex != (tArrayIndex + 1))
	{
		printf("! [%s] %d ", __FUNCTION__, __LINE__);
		printf("!iIndex = %d , tArrayIndex = %d \n", mDATA[tArrayIndex].iIndex, tArrayIndex);
		return FALSE;
	}
	for (index01 = 0; index01 < 25; index01++)
	{
		if (mDATA[tArrayIndex].iName[index01] == '\0')
		{
			break;
		}
	}
	if (index01 == 25)
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	for (index01 = 0; index01 < 3; index01++)
	{
		for (index02 = 0; index02 < 51; index02++)
		{
			if (mDATA[tArrayIndex].iDescription[index01][index02] == '\0')
			{
				break;
			}
		}
		if (index02 == 51)
		{
			printf("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	if ((mDATA[tArrayIndex].iType < 1) || (mDATA[tArrayIndex].iType > 6))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iSort < 1) || (mDATA[tArrayIndex].iSort > 32))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iDataNumber2D < 1) || (mDATA[tArrayIndex].iDataNumber2D > 10000))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iDataNumber3D < 0) || (mDATA[tArrayIndex].iDataNumber3D > 10000))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iAddDataNumber3D < 0) || (mDATA[tArrayIndex].iAddDataNumber3D > 10000))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iLevel < 1) || (mDATA[tArrayIndex].iLevel > MAX_LIMIT_LEVEL_NUM))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
#ifdef __GOD__
	if ((mDATA[tArrayIndex].iMartialLevel < 0) || (mDATA[tArrayIndex].iMartialLevel > 12))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
#endif
	if ((mDATA[tArrayIndex].iEquipInfo[0] < 1) || (mDATA[tArrayIndex].iEquipInfo[0] > 4))
	{
		printf("! [%s] %d", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iEquipInfo[1] < 1) || (mDATA[tArrayIndex].iEquipInfo[1] > 14))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iBuyCost < 1) || (mDATA[tArrayIndex].iBuyCost > MAX_NUMBER_SIZE))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iSellCost < 0) || (mDATA[tArrayIndex].iSellCost > MAX_NUMBER_SIZE))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iBuyCPCost < 0) || (mDATA[tArrayIndex].iBuyCPCost > MAX_NUMBER_SIZE))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iLevelLimit < 1) || (mDATA[tArrayIndex].iLevelLimit > MAX_LIMIT_LEVEL_NUM))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
#ifdef __GOD__
	if ((mDATA[tArrayIndex].iMartialLevelLimit < 0) || (mDATA[tArrayIndex].iMartialLevelLimit > 12))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
#endif
	if ((mDATA[tArrayIndex].iCheckMonsterDrop < 1) || (mDATA[tArrayIndex].iCheckMonsterDrop > 2))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCheckNPCSell < 1) || (mDATA[tArrayIndex].iCheckNPCSell > 2))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCheckNPCShop < 1) || (mDATA[tArrayIndex].iCheckNPCShop > 2))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCheckAvatarDrop < 1) || (mDATA[tArrayIndex].iCheckAvatarDrop > 2))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCheckAvatarTrade < 1) || (mDATA[tArrayIndex].iCheckAvatarTrade > 2))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCheckAvatarShop < 1) || (mDATA[tArrayIndex].iCheckAvatarShop > 2))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCheckImprove < 1) || (mDATA[tArrayIndex].iCheckImprove > 2))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCheckHighImprove < 1) || (mDATA[tArrayIndex].iCheckHighImprove > 2))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCheckHighItem < 1) || (mDATA[tArrayIndex].iCheckHighItem > 2))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCheckLowItem < 1) || (mDATA[tArrayIndex].iCheckLowItem > 2))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCheckExchange < 1) || (mDATA[tArrayIndex].iCheckExchange > 2))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iSetBonus < 0) || (mDATA[tArrayIndex].iSetBonus > 10000))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCostumeTime < 0) || (mDATA[tArrayIndex].iCostumeTime > 365))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iStrength < 0) || (mDATA[tArrayIndex].iStrength > 10000))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iWisdom < 0) || (mDATA[tArrayIndex].iWisdom > 10000))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iVitality < 0) || (mDATA[tArrayIndex].iVitality > 10000))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iKi < 0) || (mDATA[tArrayIndex].iKi > 10000))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iLuck < 0) || (mDATA[tArrayIndex].iLuck > 10000))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iAttackPower < 0) || (mDATA[tArrayIndex].iAttackPower > 20000))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iDefensePower < 0) || (mDATA[tArrayIndex].iDefensePower > 20000))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iAttackSucess < 0) || (mDATA[tArrayIndex].iAttackSucess > 20000))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iAttackBlock < 0) || (mDATA[tArrayIndex].iAttackBlock > 20000))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iElementAttackPower < 0) || (mDATA[tArrayIndex].iElementAttackPower > 20000))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iElementDefensePower < 0) || (mDATA[tArrayIndex].iElementDefensePower > 20000))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCritical < 0) || (mDATA[tArrayIndex].iCritical > 100))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	/** 2009. 10. 26 : DarkAttack Potion add (wolf) */
	// Potion Type add 11 -> 13
	/** 2009. 10. 26 : DarkAttack Potion add (wolf) */
	if ((mDATA[tArrayIndex].iPotionType[0] < 0) || (mDATA[tArrayIndex].iPotionType[0] > 16))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iPotionType[1] < 0) || (mDATA[tArrayIndex].iPotionType[1] > 10000))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mDATA[tArrayIndex].iPotionType[0] == 9)
	{
		if ((mDATA[tArrayIndex].iPotionType[1] < 1) || (mDATA[tArrayIndex].iPotionType[1] > 3))
		{
			printf("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	if ((mDATA[tArrayIndex].iGainSkillNumber < 0) || (mDATA[tArrayIndex].iGainSkillNumber > 300))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iLastAttackBonusInfo[0] < 0) || (mDATA[tArrayIndex].iLastAttackBonusInfo[0] > 100))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iLastAttackBonusInfo[1] < 0) || (mDATA[tArrayIndex].iLastAttackBonusInfo[1] > 1000))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCapeInfo[0] < 0) || (mDATA[tArrayIndex].iCapeInfo[0] > 100))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCapeInfo[1] < 0) || (mDATA[tArrayIndex].iCapeInfo[1] > 100))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCapeInfo[2] < 0) || (mDATA[tArrayIndex].iCapeInfo[2] > 100))
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
#ifdef __GOD__
	for (index01 = 0; index01 < 8; index01++)
#else
	for (index01 = 0; index01 < 5; index01++)
#endif
	{
		if ((mDATA[tArrayIndex].iBonusSkillInfo[index01][0] < 0) || (mDATA[tArrayIndex].iBonusSkillInfo[index01][0] > 300))
		{
			printf("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((mDATA[tArrayIndex].iBonusSkillInfo[index01][1] < 0) || (mDATA[tArrayIndex].iBonusSkillInfo[index01][1] > 100))
		{
			printf("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	return TRUE;
}
//INIT
BOOL ITEMSYSTEM::Init(char* tFileName)
{
	int index01 = NULL;
	int index02;
	int index03;
	DWORD nReadByte;
	DWORD tOriginalSize;
	BYTE* tOriginal;
	DWORD tCompressSize;
	BYTE* tCompress;
	int tDataNum;
	ITEM_INFO* tDATA;
	int tLevel;
	int tType;
	int tSort;
	BOOL tCheckFirstCreate;

	Free();

	HANDLE hFile;
	hFile = CreateFileA(tFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	if (!ReadFile(hFile, &tOriginalSize, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	tOriginal = (BYTE*)GlobalAlloc(GMEM_FIXED, tOriginalSize);
	if (tOriginal == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!ReadFile(hFile, &tCompressSize, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	tCompress = (BYTE*)GlobalAlloc(GMEM_FIXED, tCompressSize);
	if (tCompress == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!ReadFile(hFile, tCompress, tCompressSize, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != tCompressSize)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!CloseHandle(hFile))
	{
		return FALSE;
	}
	if (!mGAME.Decompress(tCompressSize, tCompress, tOriginalSize, tOriginal))
	{
		return FALSE;
	}
	mSharedMemSize = 0;
	CopyMemory(&tDataNum, &tOriginal[0], 4);
	mSharedMemSize += 4;
	tDataNum = 99999;
	if (tDataNum != 99999)
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}

	tDATA = (ITEM_INFO*)GlobalAlloc(0, (tDataNum * sizeof(ITEM_INFO)));
	if (tDATA == NULL)
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	CopyMemory(&tDATA[0], &tOriginal[40], (tDataNum * sizeof(ITEM_INFO)));
	mSharedMemSize += (tDataNum * sizeof(ITEM_INFO));
	GlobalFree(tCompress);
	GlobalFree(tOriginal);
	mDataNum = tDataNum;
	mDATA = tDATA;

	for (index01 = 0; index01 < mDataNum; index01++)
	{
		if (!CheckValidElement(index01))
		{
			return FALSE;
		}
	}
	for (index01 = 0; index01 < mDataNum; index01++)
	{
		if (mDATA[index01].iIndex == 0)
		{
			continue;
		}
		tLevel = (mDATA[index01].iLevel + mDATA[index01].iMartialLevel - 1);
		tType = mDATA[index01].iType - 1;
		tSort = mDATA[index01].iSort - 1;
		mPartNum[tLevel][tType][tSort]++;
	}
	for (index01 = 0; index01 < 157; index01++)
	{
		for (index02 = 0; index02 < 6; index02++)
		{
			for (index03 = 0; index03 < 32; index03++)
			{
				mSharedMemSize += 4;
				if (mPartNum[index01][index02][index03] < 1)
				{
					continue;
				}
				mSharedMemSize += (mPartNum[index01][index02][index03] * 4);
				mPART[index01][index02][index03] = (int*)calloc(1, (mPartNum[index01][index02][index03] * 4));
				if (mPART[index01][index02][index03] == NULL)
				{
					printf("! [%s] %d\n", __FUNCTION__, __LINE__);
					return FALSE;
				}
				mPartNum[index01][index02][index03] = 0;
			}
		}
	}
	for (index01 = 0; index01 < mDataNum; index01++)
	{
		if (mDATA[index01].iIndex == 0)
		{
			continue;
		}
		tLevel = (mDATA[index01].iLevel + mDATA[index01].iMartialLevel - 1);
		tType = mDATA[index01].iType - 1;
		tSort = mDATA[index01].iSort - 1;
		mPART[tLevel][tType][tSort][mPartNum[tLevel][tType][tSort]] = index01;
		mPartNum[tLevel][tType][tSort]++;
	}

	
	mSharedMemMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, mSharedMemSize, "SHAREMEM_ITEMSYSTEM");
	if (mSharedMemMap == NULL)
	{
		return FALSE;
	}
	if (GetLastError() != ERROR_ALREADY_EXISTS)
	{
		tCheckFirstCreate = TRUE;
	}
	else
	{
		tCheckFirstCreate = FALSE;
	}
	mSharedPostMem = (BYTE*)MapViewOfFile(mSharedMemMap, FILE_MAP_ALL_ACCESS, 0, 0, mSharedMemSize);
	//mSharedPostMem = (BYTE *)shmat(mSharedMemMap, (char *)0, 0);
	if (mSharedPostMem == NULL)
	{
		return FALSE;
	}

	mSharedMemSizeForCheck = 0;
	if (tCheckFirstCreate)
	{
		CopyMemory(&mSharedPostMem[mSharedMemSizeForCheck], &mDataNum, 4);
	}
	CopyMemory(&mSharedItemData.mDataNum, &mSharedPostMem[mSharedMemSizeForCheck], 4);
	mSharedMemSizeForCheck += 4;
	if (tCheckFirstCreate)
	{
		CopyMemory(&mSharedPostMem[mSharedMemSizeForCheck], mDATA, (mDataNum * sizeof(ITEM_INFO)));
	}
	mSharedItemData.mDATA = (ITEM_INFO*)&mSharedPostMem[mSharedMemSizeForCheck];
	mSharedMemSizeForCheck += (mDataNum * sizeof(ITEM_INFO));
	for (index01 = 0; index01 < 157; index01++)
	{
		for (index02 = 0; index02 < 6; index02++)
		{
			for (index03 = 0; index03 < 32; index03++)
			{
				if (tCheckFirstCreate)
				{
					memcpy(&mSharedPostMem[mSharedMemSizeForCheck], &mPartNum[index01][index02][index03], 4);
				}
				CopyMemory(&mSharedItemData.mPartNum[index01][index02][index03], &mSharedPostMem[mSharedMemSizeForCheck], 4);
				mSharedMemSizeForCheck += 4;
			}
		}
	}
	for (index01 = 0; index01 < 157; index01++)
	{
		for (index02 = 0; index02 < 6; index02++)
		{
			for (index03 = 0; index03 < 32; index03++)
			{
				if (mPartNum[index01][index02][index03] < 1)
				{
					continue;
				}
				if (tCheckFirstCreate)
				{
					CopyMemory(&mSharedPostMem[mSharedMemSizeForCheck], mPART[index01][index02][index03], (mPartNum[index01][index02][index03] * 4));
				}
				mSharedItemData.mPART[index01][index02][index03] = (int*)&mSharedPostMem[mSharedMemSizeForCheck];
				mSharedMemSizeForCheck += (mPartNum[index01][index02][index03] * 4);
			}
		}
	}
	if (mSharedMemSize != mSharedMemSizeForCheck)
	{
		return FALSE;
	}
	mDataNum = 0;
	if (mDATA)
	{
		free(mDATA);
		mDATA = NULL;
	}
	for (index01 = 0; index01 < 157; index01++)
	{
		for (index02 = 0; index02 < 6; index02++)
		{
			for (index03 = 0; index03 < 32; index03++)
			{
				mPartNum[index01][index02][index03] = 0;
				if (mPART[index01][index02][index03])
				{
					free(mPART[index01][index02][index03]);
					mPART[index01][index02][index03] = NULL;
				}
			}
		}
	}

	return TRUE;
}
//FREE
void ITEMSYSTEM::Free(void)
{
	int index01;
	int index02;
	int index03;

	mDataNum = 0;
	if (mDATA)
	{
		GlobalFree(mDATA);
		mDATA = NULL;
	}
	for (index01 = 0; index01 < 157; index01++)
	{
		for (index02 = 0; index02 < 6; index02++)
		{
			for (index03 = 0; index03 < 32; index03++)
			{
				mPartNum[index01][index02][index03] = 0;
				if (mPART[index01][index02][index03])
				{
					GlobalFree(mPART[index01][index02][index03]);
					mPART[index01][index02][index03] = NULL;
				}
			}
		}
	}
	if (mSharedPostMem != NULL)
	{
		UnmapViewOfFile(mSharedPostMem);
	}
	if (mSharedMemMap != 0)
	{
		CloseHandle(mSharedMemMap);
		mSharedMemMap = NULL;
	}
}
//SEARCH
ITEM_INFO* ITEMSYSTEM::Search(int iIndex)
{


	if ((iIndex < 1) || (iIndex > mSharedItemData.mDataNum))
	{
		return NULL;
	}

	if (mSharedItemData.mDATA[(iIndex - 1)].iIndex == 0)
	{
		return NULL;
	}
	return &mSharedItemData.mDATA[(iIndex - 1)];
}
//RETURN
ITEM_INFO* ITEMSYSTEM::Return(int iLevel, int iType, int iSort)
{
	if ((iLevel < 1) || (iLevel > (MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM)) || (iType < 1) || (iType > 6) || (iSort < 1) || (iSort > 32))
	{
		return NULL;
	}

	int index01;
	int tTotalSearchItemNum;
	int tSearchItemIndex[1000];

	if (mSharedItemData.mPartNum[(iLevel - 1)][(iType - 1)][(iSort - 1)] < 1)
	{
		
		return NULL;
	}
	tTotalSearchItemNum = 0;
	for (index01 = 0; index01 < mSharedItemData.mPartNum[(iLevel - 1)][(iType - 1)][(iSort - 1)]; index01++)
	{
		if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(iType - 1)][(iSort - 1)][index01]].iSetBonus == 1)
		{
			if (tTotalSearchItemNum < 1000)
			{
				tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[(iLevel - 1)][(iType - 1)][(iSort - 1)][index01];
				tTotalSearchItemNum++;
			}
		}
	}
	if (tTotalSearchItemNum == 0)
	{
		return NULL;
	}
	return &mSharedItemData.mDATA[tSearchItemIndex[(rand() % tTotalSearchItemNum)]];
}
//RETURN
ITEM_INFO* ITEMSYSTEM::ReturnTalih(int iLevel, int iType, int iSort, int iSetBonus)
{
	if ((iLevel < 1) || (iLevel > (MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM)) || (iType < 1) || (iType > 6) || (iSort < 1) || (iSort > 32))
	{
		return NULL;
	}

	int index01;
	int tTotalSearchItemNum;
	int tSearchItemIndex[1000];

	if (mSharedItemData.mPartNum[(iLevel - 1)][(iType - 1)][(iSort - 1)] < 1)
	{
		return NULL;
	}
	tTotalSearchItemNum = 0;
	for (index01 = 0; index01 < mSharedItemData.mPartNum[(iLevel - 1)][(iType - 1)][(iSort - 1)]; index01++)
	{
		if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(iType - 1)][(iSort - 1)][index01]].iSetBonus == iSetBonus)
		{
			if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(iType - 1)][(iSort - 1)][index01]].iCheckExchange == 2)
			{
				if (tTotalSearchItemNum < 1000)
				{
					tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[(iLevel - 1)][(iType - 1)][(iSort - 1)][index01];
					tTotalSearchItemNum++;
				}
			}
		}
	}
	if (tTotalSearchItemNum == 0)
	{
		return NULL;
	}
	return &mSharedItemData.mDATA[tSearchItemIndex[(rand() % tTotalSearchItemNum)]];
}
//RETURN
ITEM_INFO* ITEMSYSTEM::Return31(int iLevel, int iType, int iSort)
{
	if ((iLevel < 1) || (iLevel > (MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM)) || (iType < 1) || (iType > 6) || (iSort < 1) || (iSort > 32))
	{
		return NULL;
	}

	int index01;
	int tTotalSearchItemNum;
	int tSearchItemIndex[1000];

	if (mSharedItemData.mPartNum[(iLevel - 1)][(iType - 1)][(iSort - 1)] < 1)
	{
		return NULL;
	}
	tTotalSearchItemNum = 0;
	for (index01 = 0; index01 < mSharedItemData.mPartNum[(iLevel - 1)][(iType - 1)][(iSort - 1)]; index01++)
	{
		if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(iType - 1)][(iSort - 1)][index01]].iSetBonus == 1)
		{
			if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(iType - 1)][(iSort - 1)][index01]].iCheckAvatarTrade == 2)
			{
				if (tTotalSearchItemNum < 1000)
				{
					tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[(iLevel - 1)][(iType - 1)][(iSort - 1)][index01];
					tTotalSearchItemNum++;
				}
			}
		}
	}
	if (tTotalSearchItemNum == 0)
	{
		return NULL;
	}

	return &mSharedItemData.mDATA[tSearchItemIndex[(rand() % tTotalSearchItemNum)]];
}
ITEM_INFO* ITEMSYSTEM::GetSkillByTribeInfo(int iLevel, int iType, int iSort, int tribe)
{
	if ((iLevel < 1) || (iLevel > (MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM)) || (iType < 1) || (iType > 6) || (iSort < 1) || (iSort > 32))
	{
		return NULL;
	}

	int index01;
	int tTotalSearchItemNum;
	int tSearchItemIndex[1000];

	if (mSharedItemData.mPartNum[(iLevel - 1)][(iType - 1)][(iSort - 1)] < 1)
	{
		return NULL;
	}

	tTotalSearchItemNum = 0;

	for (index01 = 0; index01 < mSharedItemData.mPartNum[(iLevel - 1)][(iType - 1)][(iSort - 1)]; index01++)
	{
		if ((mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(iType - 1)][(iSort - 1)][index01]].iEquipInfo[0] - 2) == tribe || mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(iType - 1)][(iSort - 1)][index01]].iEquipInfo[0] == 1)
		{
			if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(iType - 1)][(iSort - 1)][index01]].iCheckAvatarTrade == 2)
			{
				if (tTotalSearchItemNum < 1000)
				{
					tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[(iLevel - 1)][(iType - 1)][(iSort - 1)][index01];
					tTotalSearchItemNum++;
				}
			}
		}
	}

	if (tTotalSearchItemNum == 0)
	{
		return NULL;
	}

	int randomNumber = rand() % tTotalSearchItemNum;

	return &mSharedItemData.mDATA[tSearchItemIndex[randomNumber]];
}
//RETURN
ITEM_INFO* ITEMSYSTEM::Return(int iLevel, int iType, int iSort, ITEM_INFO* tITEM_INFO)
{

	if ((iLevel < 1) || (iLevel > (MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM)) || (iType < 1) || (iType > 6) || (iSort < 1) || (iSort > 32) || (tITEM_INFO == NULL))
	{
		return NULL;
	}

	int index01;
	int tTotalSearchItemNum;
	int tSearchItemIndex[1000];
	unsigned int tRandom = 0;

	
	tTotalSearchItemNum = 0;
	for (index01 = 0; index01 < mSharedItemData.mPartNum[(iLevel - 1)][(iType - 1)][(iSort - 1)]; index01++)
	{
		if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(iType - 1)][(iSort - 1)][index01]].iEquipInfo[0] == tITEM_INFO->iEquipInfo[0])
		{
			if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(iType - 1)][(iSort - 1)][index01]].iCheckExchange == tITEM_INFO->iCheckExchange)
			{
				if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(iType - 1)][(iSort - 1)][index01]].iSetBonus == tITEM_INFO->iSetBonus)
				{
					if (tTotalSearchItemNum < 1000)
					{
						tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[(iLevel - 1)][(iType - 1)][(iSort - 1)][index01];
						tTotalSearchItemNum++;
						
					}
				}
			}
		}
	}
	if (tTotalSearchItemNum == 0)
	{
		return NULL;
	}
	return &mSharedItemData.mDATA[tSearchItemIndex[(rand() % tTotalSearchItemNum)]];
}

//RETURN_1
ITEM_INFO* ITEMSYSTEM::Return_1(int iLevel, ITEM_INFO* tITEM_INFO)
{
	if ((iLevel < 1) || (iLevel > (MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM)) || (tITEM_INFO == NULL))
	{
		return NULL;
	}

	int index01;
	int tTotalSearchItemNum;
	int tSearchItemIndex[1000];
	unsigned int tRandom = 0;

	tTotalSearchItemNum = 0;
	for (index01 = 0; index01 < mSharedItemData.mPartNum[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)]; index01++)
	{
		if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iEquipInfo[0] == tITEM_INFO->iEquipInfo[0])
		{
			if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iCheckExchange == tITEM_INFO->iCheckExchange)
			{
				if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iSetBonus == tITEM_INFO->iSetBonus)
				{
					if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iBonusSkillInfo[0][0] == tITEM_INFO->iBonusSkillInfo[0][0])
					{
						if (tTotalSearchItemNum < 1000)
						{
							tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01];
							tTotalSearchItemNum++;
						}
					}
					else
					{
						if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iBonusSkillInfo[1][0] == tITEM_INFO->iBonusSkillInfo[0][0])
						{
							if (tTotalSearchItemNum < 1000)
							{
								tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01];
								tTotalSearchItemNum++;
							}
						}
					}
				}
			}
		}
	}
	if (tTotalSearchItemNum == 0)
	{
		return NULL;
	}
	tRandom = rand();
	return &mSharedItemData.mDATA[tSearchItemIndex[(tRandom % tTotalSearchItemNum)]];
}

//RETURN_2
ITEM_INFO* ITEMSYSTEM::Return_2(int iLevel, ITEM_INFO* tITEM_INFO)
{
	if ((iLevel < 1) || (iLevel > (MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM)) || (tITEM_INFO == NULL))
	{
		return NULL;
	}

	int index01;
	int tTotalSearchItemNum;
	unsigned int tRandom = 0;
	int tSearchItemIndex[1000];


	tTotalSearchItemNum = 0;
	for (index01 = 0; index01 < mSharedItemData.mPartNum[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)]; index01++)
	{
		if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iEquipInfo[0] == tITEM_INFO->iEquipInfo[0])
		{
			if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iCheckExchange == tITEM_INFO->iCheckExchange)
			{
				if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iSetBonus == tITEM_INFO->iSetBonus)
				{
					if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iBonusSkillInfo[0][0] == tITEM_INFO->iBonusSkillInfo[0][0])
					{
						if (tTotalSearchItemNum < 1000)
						{
							tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01];
							tTotalSearchItemNum++;
						}
					}
				}
			}
		}
	}
	if (tTotalSearchItemNum == 0)
	{
		return NULL;
	}
	tRandom = rand();
	return &mSharedItemData.mDATA[tSearchItemIndex[(tRandom % tTotalSearchItemNum)]];
}
ITEM_INFO* ITEMSYSTEM::ReturnRareItem2(int iTribe, int iLevel)
{
	int iSortNum = 0;
	int iSort[9] = { 0, };
	unsigned int tRandom = 0;
	ITEM_INFO* pItemInfoPtr = NULL;

	iSort[0] = 7;   // ....
	iSort[1] = 9;   // ...
	iSort[2] = 10;  // ...
	iSort[3] = 11;  // ...
	iSort[4] = 12;  // ...

	switch (iTribe) {
	case 0: // ...
		iSort[5] = 13;  // ..
		iSort[6] = 14;  // ..
		iSort[7] = 15;  // ...
		break;
	case 1: // ...
		iSort[5] = 16;  // ...
		iSort[6] = 17;  // ...
		iSort[7] = 18;  // ...
		break;
	case 2: // ...
		iSort[5] = 19;  // ...
		iSort[6] = 20;  // ...
		iSort[7] = 21;  // ....
		break;
	default: // .. ...
		return NULL;
	}

	tRandom = rand();
	iSortNum = iSort[tRandom % 8];

	while (true) {
		pItemInfoPtr = Return(iLevel, 3, iSortNum);
		if (pItemInfoPtr != NULL) {
			if ((pItemInfoPtr->iEquipInfo[0] == 1) || ((pItemInfoPtr->iEquipInfo[0] - 2) == iTribe))
				break;

			pItemInfoPtr = NULL;
		}
	}

	return pItemInfoPtr;
}

ITEM_INFO* ITEMSYSTEM::ReturnRareItem1(int iTribe, int iLevel, int iSort)
{
	ITEM_INFO* pItemInfoPtr = NULL;
	int tSort[5];
	int iSortNum = 0;

	int tSearchItemTryNumForSameTribe = 0;

	tSort[0] = 7;  // 0 --- Týlsým
	tSort[1] = 11; // 1 --- Yüzük
	tSort[2] = 9;  // 2 --- Zýrh
	tSort[3] = 10; // 3 --- Eldiven
	tSort[4] = 12; // 4 --- Ayakkabý

	switch (iTribe) {
	case 0:
		tSort[5] = 14;  // 5 --- Saldýrý itemi
		break;
	case 1:
		tSort[5] = 16; // 5 --- Saldýrý itemi
		break;
	case 2:
		tSort[5] = 20; // 5 --- Saldýrý itemi
		break;
	default:
		return NULL;
	}

	tSearchItemTryNumForSameTribe = 0;
	pItemInfoPtr = NULL;
	while (tSearchItemTryNumForSameTribe < 10)
	{
		pItemInfoPtr = Return31(iLevel, 3, tSort[iSort]);
		if (pItemInfoPtr)
		{
			if ((pItemInfoPtr->iEquipInfo[0] == 1) || ((pItemInfoPtr->iEquipInfo[0] - 2) == iTribe))
				break;
			pItemInfoPtr = NULL;
			tSearchItemTryNumForSameTribe++;
		}
		else
		{
			tSearchItemTryNumForSameTribe++;
		}
	}

	return pItemInfoPtr;
}

ITEM_INFO* ITEMSYSTEM::ReturnRareItem(int iTribe, int iType, int iLevel)
{
	int iSortNum = 0;
	int iSort[9] = { 0, };
	unsigned int tRandom = 0;
	ITEM_INFO* pItemInfoPtr = NULL;

	iSort[0] = 7;   // ....
	iSort[1] = 9;   // ...
	iSort[2] = 10;  // ...
	iSort[3] = 11;  // ...
	iSort[4] = 12;  // ...

	switch (iTribe) {
	case 0: // ...
		iSort[5] = 13;  // ..
		iSort[6] = 14;  // ..
		iSort[7] = 15;  // ...
		break;
	case 1: // ...
		iSort[5] = 16;  // ...
		iSort[6] = 17;  // ...
		iSort[7] = 18;  // ...
		break;
	case 2: // ...
		iSort[5] = 19;  // ...
		iSort[6] = 20;  // ...
		iSort[7] = 21;  // ....
		break;
	default: // .. ...
		return NULL;
	}

	tRandom = rand();
	iSortNum = iSort[tRandom % 8];

	while (true) {
		pItemInfoPtr = Return(iLevel, iType, iSortNum);
		if (pItemInfoPtr != NULL) {
			if ((pItemInfoPtr->iEquipInfo[0] == 1) || ((pItemInfoPtr->iEquipInfo[0] - 2) == iTribe))
				break;

			pItemInfoPtr = NULL;
		}
	}

	return pItemInfoPtr;
}

ITEM_INFO* ITEMSYSTEM::GetResultItemPtrByGigabyteItem(void)
{
	int iRandom = 0, iResultItemIndex = 0;
	iRandom = rand() % 1000;
	if (iRandom < 450) // 45.00%
		iResultItemIndex = 3;
	else if (iRandom < 700) // 25.00%
		iResultItemIndex = 4;
	else if (iRandom < 800) // 10.00%
		iResultItemIndex = 27;
	else if (iRandom < 860) // 6.00%
		iResultItemIndex = 28;
	else if (iRandom < 900) // 4.00%
		iResultItemIndex = 23;
	else if (iRandom < 930) // 3.00%
		iResultItemIndex = 29;
	else if (iRandom < 955) // 2.50%
		iResultItemIndex = 24;
	else if (iRandom < 975) // 2.00%
		iResultItemIndex = 30;
	else if (iRandom < 990) // 1.50%
		iResultItemIndex = 32;
	else
		iResultItemIndex = 33;

	return Search(iResultItemIndex);
}

ITEM_INFO* ITEMSYSTEM::GetMoneyBy1WonLuckyBag(void)
{
	int iRandom = 0;
	int tItemIndex = 0;
	iRandom = rand() % 10000;
	if (iRandom < 3000) {
		tItemIndex = 1308;
	}
	else if (iRandom < 3350) {
		tItemIndex = 1310;
	}
	else if (iRandom < 5350) {
		tItemIndex = 1019;
	}
	else if (iRandom < 6350) {
		tItemIndex = 1045;
	}
	else if (iRandom < 8150) {
		tItemIndex = 1020;
	}
	else if (iRandom < 8950) {
		tItemIndex = 1036;
	}
	else if (iRandom < 9950) {
		tItemIndex = 1021;
	}
	else if (iRandom < 9999) {
		tItemIndex = 1035;
	}
	else {
		tItemIndex = 1103;
	}
	return Search(tItemIndex); // ....
}

ITEM_INFO* ITEMSYSTEM::GetPresentItemPtrByGoodwillAmbassador(int& iCounts)
{
	int iRandom = 0;

	iCounts = 0;
	iRandom = rand() % 1000;

	if (iRandom < 400) {
		return Search(1036);     // ... (.).
	}
	else if (iRandom < 700) {
		return Search(1379);     // ... (.)
	}
	else if (iRandom < 900) {
		return Search(1022);   // ... (9%)
	}
	else if (iRandom < 990) {
		return Search(1047);   // 1. ....
	}
	else {
		return Search(1108);   // . ...
	}
	return NULL;
}

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_SKILLSYSTEM
//-------------------------------------------------------------------------------------------------
//INSTANCE
SKILLSYSTEM mSKILL;
//CREATE
SKILLSYSTEM::SKILLSYSTEM(void)
{
	mDataNum = 0;
	mDATA = NULL;
}
//CHECK_VALID_ELEMENT
BOOL SKILLSYSTEM::CheckValidElement(int tArrayIndex)
{
	int index01;
	int index02;

	if (mDATA[tArrayIndex].sIndex == 0)
	{
		return TRUE;
	}
	if ((mDATA[tArrayIndex].sIndex < 1) || (mDATA[tArrayIndex].sIndex > 300))
	{
		return FALSE;
	}
	if (mDATA[tArrayIndex].sIndex != (tArrayIndex + 1))
	{
		return FALSE;
	}
	for (index01 = 0; index01 < 25; index01++)
	{
		if (mDATA[tArrayIndex].sName[index01] == '\0')
		{
			break;
		}
	}
	if (index01 == 25)
	{
		return FALSE;
	}
	for (index01 = 0; index01 < 10; index01++)
	{
		for (index02 = 0; index02 < 51; index02++)
		{
			if (mDATA[tArrayIndex].sDescription[index01][index02] == '\0')
			{
				break;
			}
		}
		if (index02 == 51)
		{
			return FALSE;
		}
	}
	if ((mDATA[tArrayIndex].sType < 1) || (mDATA[tArrayIndex].sType > 4))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].sAttackType < 1) || (mDATA[tArrayIndex].sAttackType > 5))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].sDataNumber2D < 1) || (mDATA[tArrayIndex].sDataNumber2D > 10000))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].sTribeInfo[0] < 1) || (mDATA[tArrayIndex].sTribeInfo[0] > 4))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].sTribeInfo[1] < 1) || (mDATA[tArrayIndex].sTribeInfo[1] > 10))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].sLearnSkillPoint < 1) || (mDATA[tArrayIndex].sLearnSkillPoint > 1000))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].sMaxUpgradePoint < 1) || (mDATA[tArrayIndex].sMaxUpgradePoint > 1000))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].sTotalHitNumber < 0) || (mDATA[tArrayIndex].sTotalHitNumber > 10))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].sValidRadius < 0) || (mDATA[tArrayIndex].sValidRadius > 1000))
	{
		return FALSE;
	}
	for (index01 = 0; index01 < 2; index01++)
	{
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sManaUse < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sManaUse > 10000))
		{
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sRecoverInfo[0] < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sRecoverInfo[0] > 10000))
		{
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sRecoverInfo[1] < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sRecoverInfo[1] > 10000))
		{
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sStunAttack < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sStunAttack > 100))
		{
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sStunDefense < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sStunDefense > 100))
		{
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sFastRunSpeed < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sFastRunSpeed > 1000))
		{
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sAttackInfo[0] < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sAttackInfo[0] > 1000))
		{
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sAttackInfo[1] < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sAttackInfo[1] > 1000))
		{
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sAttackInfo[2] < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sAttackInfo[2] > 1000))
		{
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sRunTime < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sRunTime > 10000))
		{
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sChargingDamageUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sChargingDamageUp > 1000))
		{
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sAttackPowerUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sAttackPowerUp > 1000))
		{
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sDefensePowerUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sDefensePowerUp > 1000))
		{
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sAttackSuccessUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sAttackSuccessUp > 1000))
		{
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sAttackBlockUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sAttackBlockUp > 1000))
		{
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sElementAttackUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sElementAttackUp > 1000))
		{
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sElementDefenseUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sElementDefenseUp > 1000))
		{
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sAttackSpeedUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sAttackSpeedUp > 1000))
		{
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sRunSpeedUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sRunSpeedUp > 1000))
		{
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sShieldLifeUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sShieldLifeUp > 1000))
		{
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sLuckUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sLuckUp > 1000))
		{
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sCriticalUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sCriticalUp > 1000))
		{
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sReturnSuccessUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sReturnSuccessUp > 10000))
		{
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sStunDefenseUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sStunDefenseUp > 1000))
		{
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sDestroySuccessUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sDestroySuccessUp > 10000))
		{
			return FALSE;
		}
	}
	return TRUE;
}
//INIT
BOOL SKILLSYSTEM::Init(char* tFileName)
{
	int index01;
	DWORD nReadByte;
	DWORD tOriginalSize;
	BYTE* tOriginal;
	DWORD tCompressSize;
	BYTE* tCompress;
	int tDataNum;
	SKILL_INFO* tDATA;

	Free();
	HANDLE hFile;
	hFile = CreateFile(tFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	if (!ReadFile(hFile, &tOriginalSize, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	tOriginal = (BYTE*)GlobalAlloc(GMEM_FIXED, tOriginalSize);
	if (tOriginal == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!ReadFile(hFile, &tCompressSize, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	tCompress = (BYTE*)GlobalAlloc(GMEM_FIXED, tCompressSize);
	if (tCompress == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!ReadFile(hFile, tCompress, tCompressSize, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != tCompressSize)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!CloseHandle(hFile))
	{
		return FALSE;
	}
	if (!mGAME.Decompress(tCompressSize, tCompress, tOriginalSize, tOriginal))
	{
		return FALSE;
	}

	CopyMemory(&tDataNum, &tOriginal[0], 4);
	tDataNum = 300;
	if (tDataNum != 300)
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	tDATA = (SKILL_INFO*)calloc(1, (tDataNum * sizeof(SKILL_INFO)));
	if (tDATA == NULL)
	{
		printf("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	CopyMemory(&tDATA[0], &tOriginal[84], (tDataNum * sizeof(SKILL_INFO)));
	GlobalFree(tCompress);
	GlobalFree(tOriginal);

	mDataNum = tDataNum;
	mDATA = tDATA;
	for (index01 = 0; index01 < mDataNum; index01++)
	{
		if (!CheckValidElement(index01))
		{
			printf("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	return TRUE;
}
//FREE
void SKILLSYSTEM::Free(void)
{
	mDataNum = 0;
	if (mDATA)
	{
		free(mDATA);
		mDATA = NULL;
	}
}
//SEARCH
SKILL_INFO* SKILLSYSTEM::Search(int sIndex)
{
	if ((sIndex < 1) || (sIndex > mDataNum))
	{
		return NULL;
	}
	if (mDATA[(sIndex - 1)].sIndex == 0)
	{
		return NULL;
	}
	return &mDATA[(sIndex - 1)];
}
//RETURN_ATTACK_TYPE
int SKILLSYSTEM::ReturnAttackType(int sIndex)
{
	SKILL_INFO* tSKILL_INFO;

	tSKILL_INFO = Search(sIndex);
	if (tSKILL_INFO == NULL)
	{
		return 0;
	}
	return tSKILL_INFO->sAttackType;
}
//RETURN_TOTAL_HIT_NUMBER
int SKILLSYSTEM::ReturnTotalHitNumber(int sIndex)
{
	SKILL_INFO* tSKILL_INFO;

	tSKILL_INFO = Search(sIndex);
	if (tSKILL_INFO == NULL)
	{
		return 0;
	}
	return tSKILL_INFO->sTotalHitNumber;
}
//RETURN_SKILL_VALUE
float SKILLSYSTEM::ReturnSkillValue(int sIndex, int sPoint, int sFactor)
{
	SKILL_INFO* tSKILL_INFO;
	int tMinValue;
	int tMaxValue;
	float tValue;

	tSKILL_INFO = Search(sIndex);
	if (tSKILL_INFO == NULL)
	{
		return 0.0f;
	}
	if (sPoint < 1)
	{
		return 0.0f;
	}
	switch (sFactor)
	{
	case  1:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sManaUse;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sManaUse;
		break;
	case  2:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sRecoverInfo[0];
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sRecoverInfo[0];
		break;
	case  3:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sRecoverInfo[1];
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sRecoverInfo[1];
		break;
	case  4:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sStunAttack;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sStunAttack;
		break;
	case  5:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sStunDefense;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sStunDefense;
		break;
	case  6:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sFastRunSpeed;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sFastRunSpeed;
		break;
	case  7:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sAttackInfo[0];
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sAttackInfo[0];
		break;
	case  8:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sAttackInfo[1];
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sAttackInfo[1];
		break;
	case  9:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sAttackInfo[2];
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sAttackInfo[2];
		break;
	case 10:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sRunTime;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sRunTime;
		break;
	case 11:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sChargingDamageUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sChargingDamageUp;
		break;
	case 12:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sAttackPowerUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sAttackPowerUp;
		break;
	case 13:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sDefensePowerUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sDefensePowerUp;
		break;
	case 14:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sAttackSuccessUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sAttackSuccessUp;
		break;
	case 15:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sAttackBlockUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sAttackBlockUp;
		break;
	case 16:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sElementAttackUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sElementAttackUp;
		break;
	case 17:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sElementDefenseUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sElementDefenseUp;
		break;
	case 18:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sAttackSpeedUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sAttackSpeedUp;
		break;
	case 19:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sRunSpeedUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sRunSpeedUp;
		break;
	case 20:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sShieldLifeUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sShieldLifeUp;
		break;
	case 21:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sLuckUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sLuckUp;
		break;
	case 22:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sCriticalUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sCriticalUp;
		break;
	case 23:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sReturnSuccessUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sReturnSuccessUp;
		break;
	case 24:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sStunDefenseUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sStunDefenseUp;
		break;
	case 25:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sDestroySuccessUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sDestroySuccessUp;
		break;
	default:
		return 0.0f;
	}

	tValue = (float)tMinValue + (float)((tMaxValue - tMinValue) * sPoint) / (float)tSKILL_INFO->sMaxUpgradePoint;
	if (tValue <= 0.0f)
	{
		return 0.0f;
	}
	if (tValue < 1.0f)
	{
		return 1.0f;
	}
	return tValue;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MONSTERSYSTEM
//-------------------------------------------------------------------------------------------------
//INSTANCE
MONSTERSYSTEM mMONSTER;
//CREATE
MONSTERSYSTEM::MONSTERSYSTEM(void)
{
	mDataNum = 0;
	mDATA = NULL;
	mSharedMemMap = 0;
	mSharedPostMem = NULL;
}
//CHECK_VALID_ELEMENT
BOOL MONSTERSYSTEM::CheckValidElement(int tArrayIndex)
{
	int index01;
	int index02;

	if (mDATA[tArrayIndex].mIndex == 0)
	{
		return TRUE;
	}
	if ((mDATA[tArrayIndex].mIndex < 1) || (mDATA[tArrayIndex].mIndex > 10000))
	{
		return FALSE;
	}

	if (mDATA[tArrayIndex].mIndex != (tArrayIndex + 1))
	{
		return FALSE;
	}
	for (index01 = 0; index01 < 25; index01++)
	{
		if (mDATA[tArrayIndex].mName[index01] == '\0')
		{
			break;
		}
	}
	if (index01 == 25)
	{
		return FALSE;
	}
	for (index01 = 0; index01 < 2; index01++)
	{
		for (index02 = 0; index02 < 101; index02++)
		{
			if (mDATA[tArrayIndex].mChatInfo[index01][index02] == '\0')
			{
				break;
			}
		}
		if (index02 == 101)
		{
			return FALSE;
		}
	}
	if ((mDATA[tArrayIndex].mType < 1) || (mDATA[tArrayIndex].mType > 16))

	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mSpecialType < 1) || (mDATA[tArrayIndex].mSpecialType > 51))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mDamageType < 1) || (mDATA[tArrayIndex].mDamageType > 2))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mDataSortNumber < 1) || (mDATA[tArrayIndex].mDataSortNumber > 10000))
	{
		return FALSE;
	}
	for (index01 = 0; index01 < 3; index01++)
	{
		if ((mDATA[tArrayIndex].mSize[index01] < 1) || (mDATA[tArrayIndex].mSize[index01] > 1000))
		{
			return FALSE;
		}
	}
	if ((mDATA[tArrayIndex].mSize[3] < 0) || (mDATA[tArrayIndex].mSize[3] > 1000))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mSizeCategory < 1) || (mDATA[tArrayIndex].mSizeCategory > 4))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mCheckCollision < 1) || (mDATA[tArrayIndex].mCheckCollision > 2))
	{
		return FALSE;
	}
	for (index01 = 0; index01 < 6; index01++)
	{
		if ((mDATA[tArrayIndex].mFrameInfo[index01] < 1) || (mDATA[tArrayIndex].mFrameInfo[index01] > 10000))
		{
			return FALSE;
		}
	}
	if ((mDATA[tArrayIndex].mTotalHitNum < 0) || (mDATA[tArrayIndex].mTotalHitNum > 3))
	{
		return FALSE;
	}
	for (index01 = 0; index01 < 3; index01++)
	{
		if ((mDATA[tArrayIndex].mHitFrame[index01] < 0) || (mDATA[tArrayIndex].mHitFrame[index01] > 10000))
		{
			return FALSE;
		}
	}
	if ((mDATA[tArrayIndex].mTotalSkillHitNum < 0) || (mDATA[tArrayIndex].mTotalSkillHitNum > 3))
	{
		return FALSE;
	}
	for (index01 = 0; index01 < 3; index01++)
	{
		if ((mDATA[tArrayIndex].mSkillHitFrame[index01] < 0) || (mDATA[tArrayIndex].mSkillHitFrame[index01] > 10000))
		{
			return FALSE;
		}
	}
	if ((mDATA[tArrayIndex].mBulletInfo[0] < 1) || (mDATA[tArrayIndex].mBulletInfo[0] > 10000))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mBulletInfo[1] < 1) || (mDATA[tArrayIndex].mBulletInfo[1] > 10000))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mSummonTime[0] < 1) || (mDATA[tArrayIndex].mSummonTime[0] > 1000000))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mSummonTime[1] < 1) || (mDATA[tArrayIndex].mSummonTime[1] > 1000000))
	{
		return FALSE;
	}
	if (mDATA[tArrayIndex].mSummonTime[0] > mDATA[tArrayIndex].mSummonTime[1])
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mItemLevel < 1) || (mDATA[tArrayIndex].mItemLevel > MAX_LIMIT_LEVEL_NUM))
	{
		return FALSE;
	}
#ifdef __GOD__
	if ((mDATA[tArrayIndex].mMartialItemLevel < 0) || (mDATA[tArrayIndex].mMartialItemLevel > 12))
	{
		return FALSE;
	}
#endif
	if ((mDATA[tArrayIndex].mRealLevel < 1) || (mDATA[tArrayIndex].mRealLevel > 1000))
	{
		return FALSE;
	}
#ifdef __GOD__
	if ((mDATA[tArrayIndex].mMartialRealLevel < 0) || (mDATA[tArrayIndex].mMartialRealLevel > 1000))
	{
		return FALSE;
	}
#endif
	if ((mDATA[tArrayIndex].mGeneralExperience < 0) || (mDATA[tArrayIndex].mGeneralExperience > 100000000))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mPatExperience < 0) || (mDATA[tArrayIndex].mPatExperience > 100000000))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mLife < 1) || (mDATA[tArrayIndex].mLife > MAX_NUMBER_SIZE))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mAttackType < 1) || (mDATA[tArrayIndex].mAttackType > 6))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mRadiusInfo[0] < 0) || (mDATA[tArrayIndex].mRadiusInfo[0] > 10000))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mRadiusInfo[1] < 0) || (mDATA[tArrayIndex].mRadiusInfo[1] > 10000))
	{
		return FALSE;
	}
	if (mDATA[tArrayIndex].mRadiusInfo[0] > mDATA[tArrayIndex].mRadiusInfo[1])
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mWalkSpeed < 0) || (mDATA[tArrayIndex].mWalkSpeed > 1000))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mRunSpeed < 0) || (mDATA[tArrayIndex].mRunSpeed > 1000))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mDeathSpeed < 0) || (mDATA[tArrayIndex].mDeathSpeed > 1000))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mAttackPower < 0) || (mDATA[tArrayIndex].mAttackPower > 200000))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mDefensePower < 0) || (mDATA[tArrayIndex].mDefensePower > 200000))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mAttackSuccess < 0) || (mDATA[tArrayIndex].mAttackSuccess > 200000))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mAttackBlock < 0) || (mDATA[tArrayIndex].mAttackBlock > 200000))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mElementAttackPower < 0) || (mDATA[tArrayIndex].mElementAttackPower > 200000))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mElementDefensePower < 0) || (mDATA[tArrayIndex].mElementDefensePower > 200000))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mCritical < 0) || (mDATA[tArrayIndex].mCritical > 100))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mFollowInfo[0] < 0) || (mDATA[tArrayIndex].mFollowInfo[0] > 100))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mFollowInfo[1] < 0) || (mDATA[tArrayIndex].mFollowInfo[1] > 100))
	{
		return FALSE;
	}
	if (mDATA[tArrayIndex].mFollowInfo[0] > mDATA[tArrayIndex].mFollowInfo[1])
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mDropMoneyInfo[0] < 0) || (mDATA[tArrayIndex].mDropMoneyInfo[0] > 10000000))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mDropMoneyInfo[1] < 0) || (mDATA[tArrayIndex].mDropMoneyInfo[1] > 100000000))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mDropMoneyInfo[2] < 0) || (mDATA[tArrayIndex].mDropMoneyInfo[2] > 100000000))
	{
		return FALSE;
	}
	if (mDATA[tArrayIndex].mDropMoneyInfo[1] > mDATA[tArrayIndex].mDropMoneyInfo[2])
	{
		return FALSE;
	}
	for (index01 = 0; index01 < 5; index01++)
	{
		if ((mDATA[tArrayIndex].mDropPotionInfo[index01][0] < 0) || (mDATA[tArrayIndex].mDropPotionInfo[index01][0] > 1000000))
		{
			return FALSE;
		}
		if ((mDATA[tArrayIndex].mDropPotionInfo[index01][1] < 0) || (mDATA[tArrayIndex].mDropPotionInfo[index01][1] > 99999))
		{
			return FALSE;
		}
	}
	for (index01 = 0; index01 < 12; index01++)
	{
		if ((mDATA[tArrayIndex].mDropItemInfo[index01] < 0) || (mDATA[tArrayIndex].mDropItemInfo[index01] > 1000000))
		{
			return FALSE;
		}
	}
	if ((mDATA[tArrayIndex].mDropQuestItemInfo[0] < 0) || (mDATA[tArrayIndex].mDropQuestItemInfo[0] > 1000000))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mDropQuestItemInfo[1] < 0) || (mDATA[tArrayIndex].mDropQuestItemInfo[1] > 99999))
	{
		return FALSE;
	}
	for (index01 = 0; index01 < 50; index01++)
	{
		if ((mDATA[tArrayIndex].mDropExtraItemInfo[index01][0] < 0) || (mDATA[tArrayIndex].mDropExtraItemInfo[index01][0] > 1000000))
		{
			return FALSE;
		}
		if ((mDATA[tArrayIndex].mDropExtraItemInfo[index01][1] < 0) || (mDATA[tArrayIndex].mDropExtraItemInfo[index01][1] > 99999))
		{
			return FALSE;
		}
	}
	return TRUE;
}
//INIT
BOOL MONSTERSYSTEM::Init(char* tFileName)
{
	int index01;
	DWORD nReadByte;
	DWORD tOriginalSize;
	BYTE* tOriginal;
	DWORD tCompressSize;
	BYTE* tCompress;
	int tDataNum;
	MONSTER_INFO* tDATA;
	BOOL tCheckFirstCreate;

	Free();
	HANDLE hFile;
	hFile = CreateFile(tFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	if (!ReadFile(hFile, &tOriginalSize, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	tOriginal = (BYTE*)GlobalAlloc(GMEM_FIXED, tOriginalSize);
	if (tOriginal == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!ReadFile(hFile, &tCompressSize, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	tCompress = (BYTE*)GlobalAlloc(GMEM_FIXED, tCompressSize);
	if (tCompress == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!ReadFile(hFile, tCompress, tCompressSize, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != tCompressSize)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!CloseHandle(hFile))
	{
		return FALSE;
	}
	if (!mGAME.Decompress(tCompressSize, tCompress, tOriginalSize, tOriginal))
	{
		return FALSE;
	}
	mSharedMemSize = 0;
	CopyMemory(&tDataNum, &tOriginal[0], 4);
	mSharedMemSize += 4;
	tDataNum = 10000;
	if (tDataNum != 10000)
	{
		return FALSE;
	}
	tDATA = (MONSTER_INFO*)GlobalAlloc(GMEM_FIXED, (tDataNum * sizeof(MONSTER_INFO)));
	if (tDATA == NULL)
	{
		return FALSE;
	}
	CopyMemory(&tDATA[0], &tOriginal[64], (tDataNum * sizeof(MONSTER_INFO)));
	mSharedMemSize += (tDataNum * sizeof(MONSTER_INFO));
	GlobalFree(tCompress);
	GlobalFree(tOriginal);
	mDataNum = tDataNum;
	mDATA = tDATA;
	for (index01 = 0; index01 < mDataNum; index01++)
	{
		if (!CheckValidElement(index01))
		{
			return FALSE;
		}
	}
	mSharedMemMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, mSharedMemSize, "SHAREMEM_MONSTERSYSTEM");
	if (mSharedMemMap == NULL)
	{
		return FALSE;
	}
	if (GetLastError() != ERROR_ALREADY_EXISTS)
	{
		tCheckFirstCreate = TRUE;
	}
	else
	{
		tCheckFirstCreate = FALSE;
	}
	mSharedPostMem = (BYTE*)MapViewOfFile(mSharedMemMap, FILE_MAP_ALL_ACCESS, 0, 0, mSharedMemSize);
	if (mSharedPostMem == NULL)
	{
		return FALSE;
	}
	mSharedMemSizeForCheck = 0;
	if (tCheckFirstCreate)
	{
		CopyMemory(&mSharedPostMem[mSharedMemSizeForCheck], &mDataNum, 4);
	}
	CopyMemory(&mSharedMonsterData.mDataNum, &mSharedPostMem[mSharedMemSizeForCheck], 4);
	mSharedMemSizeForCheck += 4;
	if (tCheckFirstCreate)
	{
		CopyMemory(&mSharedPostMem[mSharedMemSizeForCheck], mDATA, (mDataNum * sizeof(MONSTER_INFO)));
	}
	mSharedMonsterData.mDATA = (MONSTER_INFO*)&mSharedPostMem[mSharedMemSizeForCheck];
	mSharedMemSizeForCheck += (mDataNum * sizeof(MONSTER_INFO));
	if (mSharedMemSize != mSharedMemSizeForCheck)
	{
		return FALSE;
	}
	mDataNum = 0;
	if (mDATA)
	{
		GlobalFree(mDATA);
		mDATA = NULL;
	}
	return TRUE;
}
//FREE
void MONSTERSYSTEM::Free(void)
{
	mDataNum = 0;
	if (mDATA)
	{
		free(mDATA);
		mDATA = NULL;
	}
	if (mSharedPostMem != NULL)
	{
		UnmapViewOfFile(mSharedPostMem);
		//shmdt( mSharedPostMem );
		mSharedPostMem = NULL;
	}
	if (mSharedMemMap != 0)
	{
		CloseHandle(mSharedMemMap);
		//shmctl(mSharedMemMap, IPC_RMID, 0);
		mSharedMemMap = 0;
	}
}
//SEARCH
MONSTER_INFO* MONSTERSYSTEM::Search(int mIndex)
{
	if ((mIndex < 1) || (mIndex > mSharedMonsterData.mDataNum))
	{
		return NULL;
	}
	if (mSharedMonsterData.mDATA[(mIndex - 1)].mIndex == 0)
	{
		return NULL;
	}
	return &mSharedMonsterData.mDATA[(mIndex - 1)];
}
//SEARCH
MONSTER_INFO* MONSTERSYSTEM::Search(int tMonsterType, int tMonsterSpecialType)
{
	int index01;

	for (index01 = 0; index01 < mSharedMonsterData.mDataNum; index01++)
	{
		if (mSharedMonsterData.mDATA[index01].mIndex == 0)
		{
			continue;
		}
		//LOG_TO_FILE_4("---> %d %d %d %d\n", mSharedMonsterData.mDATA[index01].mType, tMonsterType, mSharedMonsterData.mDATA[index01].mSpecialType, tMonsterSpecialType);
		if ((mSharedMonsterData.mDATA[index01].mType == tMonsterType) && (mSharedMonsterData.mDATA[index01].mSpecialType == tMonsterSpecialType))
		{
			return &mSharedMonsterData.mDATA[index01];
		}
	}
	//SVR_TRACE();
	return NULL;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_NPCSYSTEM
//-------------------------------------------------------------------------------------------------
//INSTANCE
NPCSYSTEM mNPC;
//CREATE
NPCSYSTEM::NPCSYSTEM(void)
{
	mDataNum = 0;
	mDATA = NULL;
	mSharedMemMap = 0;
	mSharedPostMem = NULL;
}
//CHECK_VALID_ELEMENT
BOOL NPCSYSTEM::CheckValidElement(int tArrayIndex)
{
	int index01;
	int index02;
	int index03;
	int index04;

	if (mDATA[tArrayIndex].nIndex == 0)
	{
		return TRUE;
	}
	if ((mDATA[tArrayIndex].nIndex < 1) || (mDATA[tArrayIndex].nIndex > 500))
	{
		return FALSE;
	}
	if (mDATA[tArrayIndex].nIndex != (tArrayIndex + 1))
	{
		return FALSE;
	}
	for (index01 = 0; index01 < 25; index01++)
	{
		if (mDATA[tArrayIndex].nName[index01] == '\0')
		{
			break;
		}
	}
	if (index01 == 25)
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].nSpeechNum < 1) || (mDATA[tArrayIndex].nSpeechNum > 5))
	{
		return FALSE;
	}
	for (index01 = 0; index01 < 5; index01++)
	{
		for (index02 = 0; index02 < 5; index02++)
		{
			for (index03 = 0; index03 < 51; index03++)
			{
				if (mDATA[tArrayIndex].nSpeech[index01][index02][index03] == '\0')
				{
					break;
				}
			}
			if (index03 == 51)
			{
				return FALSE;
			}
		}
	}
	if ((mDATA[tArrayIndex].nTribe < 1) || (mDATA[tArrayIndex].nTribe > 5))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].nType < 1) || (mDATA[tArrayIndex].nType > 17))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].nDataSortNumber2D < 1) || (mDATA[tArrayIndex].nDataSortNumber2D > 10000))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].nDataSortNumber3D < 1) || (mDATA[tArrayIndex].nDataSortNumber3D > 10000))
	{
		return FALSE;
	}
	for (index01 = 0; index01 < 3; index01++)
	{
		if ((mDATA[tArrayIndex].nSize[index01] < 1) || (mDATA[tArrayIndex].nSize[index01] > 1000))
		{
			return FALSE;
		}
	}
	for (index01 = 0; index01 < 50; index01++)
	{
		if ((mDATA[tArrayIndex].nMenu[index01] < 1) || (mDATA[tArrayIndex].nMenu[index01] > 2))
		{
			return FALSE;
		}
	}
	for (index01 = 0; index01 < 3; index01++)
	{
		for (index02 = 0; index02 < 28; index02++)
		{
			if ((mDATA[tArrayIndex].nShopInfo[index01][index02] < 0) || (mDATA[tArrayIndex].nShopInfo[index01][index02] > 99999))
			{
				return FALSE;
			}
		}
	}
	for (index01 = 0; index01 < 3; index01++)
	{
		for (index02 = 0; index02 < 8; index02++)
		{
			if ((mDATA[tArrayIndex].nSkillInfo1[index01][index02] < 0) || (mDATA[tArrayIndex].nSkillInfo1[index01][index02] > 300))
			{
				return FALSE;
			}
		}
	}
	for (index01 = 0; index01 < 3; index01++)
	{
		for (index02 = 0; index02 < 3; index02++)
		{
			for (index03 = 0; index03 < 3; index03++)
			{
				for (index04 = 0; index04 < 8; index04++)
				{
					if ((mDATA[tArrayIndex].nSkillInfo2[index01][index02][index03][index04] < 0) || (mDATA[tArrayIndex].nSkillInfo2[index01][index02][index03][index04] > 300))
					{
						return FALSE;
					}
				}
			}
		}
	}
	for (index01 = 0; index01 < 145; index01++)
	{
		for (index02 = 0; index02 < 15; index02++)
		{
			if ((mDATA[tArrayIndex].nGambleCostInfo[index01][index02] < 0) || (mDATA[tArrayIndex].nGambleCostInfo[index01][index02] > 100000000))
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}
//INIT
BOOL NPCSYSTEM::Init(char* tFileName)
{
	int index01;
	DWORD nReadByte;
	DWORD tOriginalSize;
	BYTE* tOriginal;
	DWORD tCompressSize;
	BYTE* tCompress;
	int tDataNum;
	NPC_INFO* tDATA;
	BOOL tCheckFirstCreate;

	Free();
	HANDLE hFile;
	hFile = CreateFileA(tFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	if (!ReadFile(hFile, &tOriginalSize, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	tOriginal = (BYTE*)GlobalAlloc(GMEM_FIXED, tOriginalSize);
	if (tOriginal == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!ReadFile(hFile, &tCompressSize, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	tCompress = (BYTE*)GlobalAlloc(GMEM_FIXED, tCompressSize);
	if (tCompress == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!ReadFile(hFile, tCompress, tCompressSize, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != tCompressSize)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!CloseHandle(hFile))
	{
		return FALSE;
	}
	if (!mGAME.Decompress(tCompressSize, tCompress, tOriginalSize, tOriginal))
	{
		return FALSE;
	}
	mSharedMemSize = 0;
	CopyMemory(&tDataNum, &tOriginal[0], 4);
	mSharedMemSize += 4;
	tDataNum = 500;
	if (tDataNum != 500)
	{
		return FALSE;
	}
	tDATA = (NPC_INFO*)GlobalAlloc(GMEM_FIXED, (tDataNum * sizeof(NPC_INFO)));
	if (tDATA == NULL)
	{
		return FALSE;
	}
	CopyMemory(&tDATA[0], &tOriginal[36], (tDataNum * sizeof(NPC_INFO)));
	mSharedMemSize += (tDataNum * sizeof(NPC_INFO));
	GlobalFree(tCompress);
	GlobalFree(tOriginal);
	mDataNum = tDataNum;
	mDATA = tDATA;
	for (index01 = 0; index01 < mDataNum; index01++)
	{
		if (!CheckValidElement(index01))
		{
			return FALSE;
		}
	}
	mSharedMemMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, mSharedMemSize, "SHAREMEM_NPCSYSTEM");
	if (mSharedMemMap == NULL)
	{
		return FALSE;
	}
	if (GetLastError() != ERROR_ALREADY_EXISTS)
	{
		tCheckFirstCreate = TRUE;
	}
	else
	{
		tCheckFirstCreate = FALSE;
	}
	mSharedPostMem = (BYTE*)MapViewOfFile(mSharedMemMap, FILE_MAP_ALL_ACCESS, 0, 0, mSharedMemSize);
	if (mSharedPostMem == NULL)
	{
		return FALSE;
	}
	mSharedMemSizeForCheck = 0;
	if (tCheckFirstCreate)
	{
		CopyMemory(&mSharedPostMem[mSharedMemSizeForCheck], &mDataNum, 4);
	}
	CopyMemory(&mSharedNPCData.mDataNum, &mSharedPostMem[mSharedMemSizeForCheck], 4);
	mSharedMemSizeForCheck += 4;
	if (tCheckFirstCreate)
	{
		CopyMemory(&mSharedPostMem[mSharedMemSizeForCheck], mDATA, (mDataNum * sizeof(NPC_INFO)));
	}
	mSharedNPCData.mDATA = (NPC_INFO*)&mSharedPostMem[mSharedMemSizeForCheck];
	mSharedMemSizeForCheck += (mDataNum * sizeof(NPC_INFO));
	if (mSharedMemSize != mSharedMemSizeForCheck)
	{
		return FALSE;
	}
	mDataNum = 0;
	if (mDATA)
	{
		GlobalFree(mDATA);
		mDATA = NULL;
	}
	return TRUE;
}
//FREE
void NPCSYSTEM::Free(void)
{
	mDataNum = 0;
	if (mDATA)
	{
		free(mDATA);
		mDATA = NULL;
	}
	if (mSharedPostMem != NULL)
	{
		UnmapViewOfFile(mSharedPostMem);
		mSharedPostMem = NULL;
	}
	if (mSharedMemMap != 0)
	{
		CloseHandle(mSharedMemMap);
		mSharedMemMap = 0;
	}
}
//SEARCH
NPC_INFO* NPCSYSTEM::Search(int nIndex)
{
	if ((nIndex < 1) || (nIndex > mSharedNPCData.mDataNum))
	{
		return NULL;
	}
	if (mSharedNPCData.mDATA[(nIndex - 1)].nIndex == 0)
	{
		return NULL;
	}
	return &mSharedNPCData.mDATA[(nIndex - 1)];
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_QUESTSYSTEM
//-------------------------------------------------------------------------------------------------
//INSTANCE
QUESTSYSTEM mQUEST;
//CREATE
QUESTSYSTEM::QUESTSYSTEM(void)
{
	mDataNum = 0;
	mDATA = NULL;
	mSharedMemMap = 0;
	mSharedPostMem = NULL;
}
//CHECK_VALID_ELEMENT
BOOL QUESTSYSTEM::CheckValidElement(int tArrayIndex)
{
	int index01;
	int index02;

	if (strcmp(mDATA[tArrayIndex].qSubject, "") == 0)
	{
		return TRUE;
	}
	if ((mDATA[tArrayIndex].qIndex < 1) || (mDATA[tArrayIndex].qIndex > 1000))
	{
		return FALSE;
	}
	if (mDATA[tArrayIndex].qIndex != (tArrayIndex + 1))
	{
		return FALSE;
	}
	for (index01 = 0; index01 < 51; index01++)
	{
		if (mDATA[tArrayIndex].qSubject[index01] == '\0')
		{
			break;
		}
	}
	if (index01 == 51)
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].qCategory < 1) || (mDATA[tArrayIndex].qCategory > 4))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].qStep < 1) || (mDATA[tArrayIndex].qStep > 1000))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].qLevel < 1) || (mDATA[tArrayIndex].qLevel > 145))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].qType < 1) || (mDATA[tArrayIndex].qType > 2))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].qSort < 1) || (mDATA[tArrayIndex].qSort > 8))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].qSummonInfo[0] < 0) || (mDATA[tArrayIndex].qSummonInfo[0] > 200))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].qStartNPCNumber < 1) || (mDATA[tArrayIndex].qStartNPCNumber > 500))
	{
		return FALSE;
	}
	for (index01 = 0; index01 < 5; index01++)
	{
		if ((mDATA[tArrayIndex].qKeyNPCNumber[index01] < 0) || (mDATA[tArrayIndex].qKeyNPCNumber[index01] > 500))
		{
			return FALSE;
		}
	}
	if ((mDATA[tArrayIndex].qEndNPCNumber < 1) || (mDATA[tArrayIndex].qEndNPCNumber > 500))
	{
		return FALSE;
	}
	for (index01 = 0; index01 < 3; index01++)
	{
		if ((mDATA[tArrayIndex].qReward[index01][0] < 1) || (mDATA[tArrayIndex].qReward[index01][0] > 6))
		{
			return FALSE;
		}
		if ((mDATA[tArrayIndex].qReward[index01][1] < 0) || (mDATA[tArrayIndex].qReward[index01][1] > 100000000))
		{
			return FALSE;
		}
	}
	if ((mDATA[tArrayIndex].qNextIndex < 0) || (mDATA[tArrayIndex].qNextIndex > 1000))
	{
		return FALSE;
	}
	for (index01 = 0; index01 < 15; index01++)
	{
		for (index02 = 0; index02 < 51; index02++)
		{
			if (mDATA[tArrayIndex].qStartSpeech[index01][index02] == '\0')
			{
				break;
			}
		}
		if (index02 == 51)
		{
			return FALSE;
		}
	}
	for (index01 = 0; index01 < 15; index01++)
	{
		for (index02 = 0; index02 < 51; index02++)
		{
			if (mDATA[tArrayIndex].qHurrySpeech[index01][index02] == '\0')
			{
				break;
			}
		}
		if (index02 == 51)
		{
			return FALSE;
		}
	}
	for (index01 = 0; index01 < 15; index01++)
	{
		for (index02 = 0; index02 < 51; index02++)
		{
			if (mDATA[tArrayIndex].qProcessSpeech1[index01][index02] == '\0')
			{
				break;
			}
		}
		if (index02 == 51)
		{
			return FALSE;
		}
	}
	for (index01 = 0; index01 < 15; index01++)
	{
		for (index02 = 0; index02 < 51; index02++)
		{
			if (mDATA[tArrayIndex].qProcessSpeech2[index01][index02] == '\0')
			{
				break;
			}
		}
		if (index02 == 51)
		{
			return FALSE;
		}
	}
	for (index01 = 0; index01 < 15; index01++)
	{
		for (index02 = 0; index02 < 51; index02++)
		{
			if (mDATA[tArrayIndex].qProcessSpeech3[index01][index02] == '\0')
			{
				break;
			}
		}
		if (index02 == 51)
		{
			return FALSE;
		}
	}
	for (index01 = 0; index01 < 15; index01++)
	{
		for (index02 = 0; index02 < 51; index02++)
		{
			if (mDATA[tArrayIndex].qProcessSpeech4[index01][index02] == '\0')
			{
				break;
			}
		}
		if (index02 == 51)
		{
			return FALSE;
		}
	}
	for (index01 = 0; index01 < 15; index01++)
	{
		for (index02 = 0; index02 < 51; index02++)
		{
			if (mDATA[tArrayIndex].qProcessSpeech5[index01][index02] == '\0')
			{
				break;
			}
		}
		if (index02 == 51)
		{
			return FALSE;
		}
	}
	for (index01 = 0; index01 < 15; index01++)
	{
		for (index02 = 0; index02 < 51; index02++)
		{
			if (mDATA[tArrayIndex].qSuccessSpeech[index01][index02] == '\0')
			{
				break;
			}
		}
		if (index02 == 51)
		{
			return FALSE;
		}
	}
	for (index01 = 0; index01 < 15; index01++)
	{
		for (index02 = 0; index02 < 51; index02++)
		{
			if (mDATA[tArrayIndex].qFailureSpeech[index01][index02] == '\0')
			{
				break;
			}
		}
		if (index02 == 51)
		{
			return FALSE;
		}
	}
	for (index01 = 0; index01 < 15; index01++)
	{
		for (index02 = 0; index02 < 51; index02++)
		{
			if (mDATA[tArrayIndex].qCallSpeech[index01][index02] == '\0')
			{
				break;
			}
		}
		if (index02 == 51)
		{
			return FALSE;
		}
	}
	return TRUE;
}
//INIT
BOOL QUESTSYSTEM::Init(char* tFileName)
{
	int index01;
	DWORD nReadByte;
	DWORD tOriginalSize;
	BYTE* tOriginal;
	DWORD tCompressSize;
	BYTE* tCompress;
	int tDataNum;
	QUEST_INFO* tDATA;
	BOOL tCheckFirstCreate;

	Free();
	HANDLE hFile;
	hFile = CreateFile(tFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	if (!ReadFile(hFile, &tOriginalSize, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	tOriginal = (BYTE*)GlobalAlloc(GMEM_FIXED, tOriginalSize);
	if (tOriginal == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!ReadFile(hFile, &tCompressSize, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	tCompress = (BYTE*)GlobalAlloc(GMEM_FIXED, tCompressSize);
	if (tCompress == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!ReadFile(hFile, tCompress, tCompressSize, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != tCompressSize)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!CloseHandle(hFile))
	{
		return FALSE;
	}
	if (!mGAME.Decompress(tCompressSize, tCompress, tOriginalSize, tOriginal))
	{
		return FALSE;
	}
	mSharedMemSize = 0;
	CopyMemory(&tDataNum, &tOriginal[0], 4);
	mSharedMemSize += 4;
	if (tDataNum != 1000)
	{
		return FALSE;
	}
	tDATA = (QUEST_INFO*)GlobalAlloc(GMEM_FIXED, (tDataNum * sizeof(QUEST_INFO)));
	if (tDATA == NULL)
	{
		return FALSE;
	}
	CopyMemory(&tDATA[0], &tOriginal[4], (tDataNum * sizeof(QUEST_INFO)));
	mSharedMemSize += (tDataNum * sizeof(QUEST_INFO));
	GlobalFree(tCompress);
	GlobalFree(tOriginal);
	mDataNum = tDataNum;
	mDATA = tDATA;
	for (index01 = 0; index01 < mDataNum; index01++)
	{
		if (!CheckValidElement(index01))
		{
			return FALSE;
		}
	}
	mSharedMemMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, mSharedMemSize, "SHAREMEM_QUESTSYSTEM");
	if (mSharedMemMap == NULL)
	{
		return FALSE;
	}
	if (GetLastError() != ERROR_ALREADY_EXISTS)
	{
		tCheckFirstCreate = TRUE;
	}
	else
	{
		tCheckFirstCreate = FALSE;
	}
	mSharedPostMem = (BYTE*)MapViewOfFile(mSharedMemMap, FILE_MAP_ALL_ACCESS, 0, 0, mSharedMemSize);
	if (mSharedPostMem == NULL)
	{
		return FALSE;
	}
	mSharedMemSizeForCheck = 0;
	if (tCheckFirstCreate)
	{
		CopyMemory(&mSharedPostMem[mSharedMemSizeForCheck], &mDataNum, 4);
	}
	CopyMemory(&mSharedQuestData.mDataNum, &mSharedPostMem[mSharedMemSizeForCheck], 4);
	mSharedMemSizeForCheck += 4;
	if (tCheckFirstCreate)
	{
		CopyMemory(&mSharedPostMem[mSharedMemSizeForCheck], mDATA, (mDataNum * sizeof(QUEST_INFO)));
	}
	mSharedQuestData.mDATA = (QUEST_INFO*)&mSharedPostMem[mSharedMemSizeForCheck];
	mSharedMemSizeForCheck += (mDataNum * sizeof(QUEST_INFO));
	if (mSharedMemSize != mSharedMemSizeForCheck)
	{
		return FALSE;
	}
	mDataNum = 0;
	if (mDATA)
	{
		HeapFree(GetProcessHeap(), 0, mDATA);
		mDATA = NULL;
	}
	return TRUE;
}
//FREE
void QUESTSYSTEM::Free(void)
{
	mDataNum = 0;
	if (mDATA)
	{
		free(mDATA);
		mDATA = NULL;
	}
	if (mSharedPostMem != NULL)
	{
		UnmapViewOfFile(mSharedPostMem);
		mSharedPostMem = NULL;
	}
	if (mSharedMemMap != 0)
	{
		CloseHandle(mSharedMemMap);
		mSharedMemMap = 0;
	}
}
//SEARCH
QUEST_INFO* QUESTSYSTEM::Search(int qTribe, int qStep)
{
	int index01;

	for (index01 = 0; index01 < mSharedQuestData.mDataNum; index01++)
	{
		if (strcmp(mSharedQuestData.mDATA[index01].qSubject, "") == 0)
		{
			continue;
		}
		if ((mSharedQuestData.mDATA[index01].qCategory == (qTribe + 1)) && (mSharedQuestData.mDATA[index01].qStep == qStep))
		{
			return &mSharedQuestData.mDATA[index01];
		}
	}
	return NULL;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_PATSYSTEM
//-------------------------------------------------------------------------------------------------
//INSTANCE
PATSYSTEM mPAT;					// PET SÝSTEMÝ
//CREATE
PATSYSTEM::PATSYSTEM(void)
{
	mMaxRangeValue[0] = 40000000;
	mMaxRangeValue[1] = 80000000;
	mMaxRangeValue[2] = 160000000;
	mMaxRangeValue[3] = 320000000;
	mMaxRangeValue[4] = 80000000;
	mMaxRangeValue[5] = 160000000;
	mMaxRangeValue[6] = 320000000;
	mMaxRangeValue[7] = 640000000;
}
//INIT
BOOL PATSYSTEM::Init(void)
{
	return TRUE;
}
//FREE
void PATSYSTEM::Free(void)
{
}
//RETURN_GROW_STEP
float PATSYSTEM::ReturnGrowStep(int pIndex, int pGrowUpValue)
{
	int tMaxRangeValueIndex;
	float tDegree;
	if (pGrowUpValue < 1)
		return 0.0;
	if (pIndex <= 1005)
	{
		if (pIndex < 1002)
		{
			switch (pIndex)
			{
			case 541:
			case 542:
			case 547:
			case 560:
				break;
			case 543:
			case 544:
			case 548:
			case 561:
				goto LABEL_24;
			case 545:
			case 549:
			case 562:
				goto LABEL_25;
			case 546:
			case 550:
				goto LABEL_26;
			default:
				return 0.0;
			}
		}
		tMaxRangeValueIndex = 0;
		goto LABEL_28;
	}
	if (pIndex > 2144)
	{
		if (pIndex > 17057)
		{
			if (pIndex == 86819)
				goto LABEL_24;
			if (pIndex != 86820)
				return 0.0;
		}
		else
		{
			if (pIndex >= 17055 || pIndex == 2160)
				goto LABEL_26;
			if (pIndex == 17052)
				goto LABEL_24;
			if (pIndex != 17053)
				return 0.0;
		}
	LABEL_25:
		tMaxRangeValueIndex = 2;
		goto LABEL_28;
	}
	if (pIndex == 2144)
		goto LABEL_26;
	if (pIndex <= 1312)
	{
		if (pIndex < 1310)
		{
			switch (pIndex)
			{
			case 1006:
			case 1007:
			case 1008:
			case 1009:
			case 1010:
			case 1011:
				goto LABEL_24;
			case 1012:
			case 1013:
			case 1014:
			case 1015:
				goto LABEL_25;
			case 1016:
				goto LABEL_26;
			default:
				return 0.0;
			}
		}
		goto LABEL_26;
	}
	if (pIndex == 1452)
	{
	LABEL_24:
		tMaxRangeValueIndex = 1;
		goto LABEL_28;
	}
	if (pIndex != 2133)
		return 0.0;
LABEL_26:
	tMaxRangeValueIndex = 3;
LABEL_28:
	if (pGrowUpValue >= mMaxRangeValue[tMaxRangeValueIndex])
		return 4.0;
	tDegree = ((float)pGrowUpValue * 100.0f) / (float)mMaxRangeValue[tMaxRangeValueIndex];
	if (tDegree < 25.0)
		return 0.0;
	if (tDegree < 50.0)
		return 1.0;
	if (tDegree < 75.0)
		return 2.0;
	if (tDegree >= 100.0)
		return 4.0;
	return 3.0;
}
//RETURN_GROW_PERCENT
float PATSYSTEM::ReturnGrowPercent(int pIndex, int pGrowUpValue)
{
	int tMaxRangeValueIndex;

	if (pGrowUpValue < 1)
	{
		return 0.0f;
	}
	switch (pIndex)
	{
	case 1002:
	case 1003:
	case 1004:
	case 1005:
		tMaxRangeValueIndex = 0;
		break;
	case 1006:
	case 1007:
	case 1008:
	case 1009:
	case 1010:
	case 1011:
		tMaxRangeValueIndex = 1;
		break;
	case 1012:
	case 1013:
	case 1014:
	case 1015:
		tMaxRangeValueIndex = 2;
		break;
	case 1016:
		tMaxRangeValueIndex = 3;
		break;
	default:
		return 0.0f;
	}
	if (pGrowUpValue >= mMaxRangeValue[tMaxRangeValueIndex])
	{
		return 100.0f;
	}
	return (((float)pGrowUpValue * 100.0f) / (float)mMaxRangeValue[tMaxRangeValueIndex]);
}
//RETURN_ATTACK_POWER
float PATSYSTEM::ReturnAttackPower(int pIndex, int pGrowUpValue, int pActivityValue)
{
	int tMaxRangeValueIndex;
	float result;

	if (pIndex != 1002
		&& pIndex != 1006
		&& pIndex != 17052
		&& pIndex != 1007
		&& pIndex != 1008
		&& pIndex != 1012
		&& pIndex != 17053
		&& pIndex != 1013
		&& pIndex != 1014
		&& pIndex != 1016
		&& pIndex != 1310
		&& pIndex != 17055
		&& pIndex != 1311
		&& pIndex != 17056
		&& pIndex != 1312
		&& pIndex != 17057
		&& pIndex != 548
		&& pIndex != 549
		&& pIndex != 550
		&& pIndex != 86819
		&& pIndex != 86820
		&& pIndex != 541
		&& pIndex != 1452
		&& pIndex != 544
		&& pIndex != 545
		&& pIndex != 546
		&& pIndex != 543
		&& pIndex != 560
		&& pIndex != 561
		&& pIndex != 562
		&& pIndex != 2133
		&& pIndex != 2144
		&& pIndex != 2160)
	{
		return 0.0;
	}
	if (pGrowUpValue < 1 || pActivityValue < 1)
		return 0.0;
	if (pIndex <= 1005)
	{
		if (pIndex < 1002)
		{
			switch (pIndex)
			{
			case 541:
			case 542:
			case 547:
			case 560:
				break;
			case 543:
			case 544:
			case 548:
			case 561:
				goto LABEL_56;
			case 545:
			case 549:
			case 562:
				goto LABEL_57;
			case 546:
			case 550:
				goto LABEL_58;
			default:
				goto LABEL_59;
			}
		}
		tMaxRangeValueIndex = 0;
		goto LABEL_60;
	}
	if (pIndex > 2144)
	{
		if (pIndex > 17057)
		{
			if (pIndex != 86819)
			{
			LABEL_57:
				tMaxRangeValueIndex = 2;
				goto LABEL_60;
			}
		}
		else
		{
			if (pIndex >= 17055 || pIndex == 2160)
				goto LABEL_58;
			if (pIndex != 17052)
				goto LABEL_57;
		}
	LABEL_56:
		tMaxRangeValueIndex = 1;
	LABEL_60:
		if (pIndex == 1312 || pIndex == 17057 || pIndex == 2133 || pIndex == 2144 || pIndex == 2160)
		{
			if (pGrowUpValue < mMaxRangeValue[tMaxRangeValueIndex])
			{
				result = (float)pGrowUpValue * 2000.0 / (float)mMaxRangeValue[tMaxRangeValueIndex];
			}
			else
			{
				result = 2200.0;
			}
		}
		else if (pGrowUpValue < mMaxRangeValue[tMaxRangeValueIndex])
		{
			result = (float)pGrowUpValue * 1000.0 / (float)mMaxRangeValue[tMaxRangeValueIndex];
		}
		else
		{
			result = 1100.0;
		}
		return result;
	}
	if (pIndex == 2144)
	{
	LABEL_58:
		tMaxRangeValueIndex = 3;
		goto LABEL_60;
	}
	if (pIndex > 1312)
	{
		if (pIndex != 1452)
			goto LABEL_58;
		goto LABEL_56;
	}
	if (pIndex >= 1310)
		goto LABEL_58;
	switch (pIndex)
	{
	case 1006:
	case 1007:
	case 1008:
	case 1009:
	case 1010:
	case 1011:
		goto LABEL_56;
	case 1012:
	case 1013:
	case 1014:
	case 1015:
		goto LABEL_57;
	case 1016:
		goto LABEL_58;
	default:
	LABEL_59:
		result = 0.0;
		break;
	}
	return result;

}
//RETURN_DEFENSE_POWER
float PATSYSTEM::ReturnDefensePower(int pIndex, int pGrowUpValue, int pActivityValue)
{
	int tMaxRangeValueIndex = 0;
	float result = 0.0;
	if (pIndex != 1003
		&& pIndex != 1006
		&& pIndex != 17052
		&& pIndex != 1009
		&& pIndex != 1010
		&& pIndex != 1012
		&& pIndex != 17053
		&& pIndex != 1013
		&& pIndex != 1015
		&& pIndex != 1016
		&& pIndex != 1310
		&& pIndex != 17055
		&& pIndex != 1311
		&& pIndex != 17056
		&& pIndex != 1312
		&& pIndex != 17057
		&& pIndex != 547
		&& pIndex != 548
		&& pIndex != 549
		&& pIndex != 550
		&& pIndex != 543
		&& pIndex != 86819
		&& pIndex != 86820
		&& pIndex != 542
		&& pIndex != 1452
		&& pIndex != 545
		&& pIndex != 546
		&& pIndex != 561
		&& pIndex != 562
		&& pIndex != 2133
		&& pIndex != 2144
		&& pIndex != 2160)
	{
		return 0.0;
	}
	if (pGrowUpValue < 1 || pActivityValue < 1)
		return 0.0;
	if (pIndex <= 1005)
	{
		if (pIndex < 1002)
		{
			switch (pIndex)
			{
			case 541:
			case 542:
			case 547:
			case 560:
				break;
			case 543:
			case 544:
			case 548:
			case 561:
				goto LABEL_55;
			case 545:
			case 549:
			case 562:
				goto LABEL_56;
			case 546:
			case 550:
				goto LABEL_57;
			default:
				goto LABEL_58;
			}
		}
		tMaxRangeValueIndex = 0;
		goto LABEL_59;
	}
	if (pIndex > 2144)
	{
		if (pIndex > 17057)
		{
			if (pIndex != 86819)
			{
			LABEL_56:
				tMaxRangeValueIndex = 2;
				goto LABEL_59;
			}
		}
		else
		{
			if (pIndex >= 17055 || pIndex == 2160)
				goto LABEL_57;
			if (pIndex != 17052)
				goto LABEL_56;
		}
	LABEL_55:
		tMaxRangeValueIndex = 1;
	LABEL_59:
		if (pIndex == 1311 || pIndex == 17056)
		{
			if (pGrowUpValue < mMaxRangeValue[tMaxRangeValueIndex])
			{
				result = (float)pGrowUpValue * 4000.0 / (float)mMaxRangeValue[tMaxRangeValueIndex];
				
			}
			else
			{
				result = 4400.0;
			}
		}
		else if (pGrowUpValue < mMaxRangeValue[tMaxRangeValueIndex])
		{
			result = (float)pGrowUpValue * 2000.0 / (float)mMaxRangeValue[tMaxRangeValueIndex];
		}
		else
		{
			result = 2200.0;
		}
		return result;
	}
	if (pIndex == 2144)
	{
	LABEL_57:
		tMaxRangeValueIndex = 3;
		goto LABEL_59;
	}
	if (pIndex > 1312)
	{
		if (pIndex != 1452)
			goto LABEL_57;
		goto LABEL_55;
	}
	if (pIndex >= 1310)
		goto LABEL_57;
	switch (pIndex)
	{
	case 1006:
	case 1007:
	case 1008:
	case 1009:
	case 1010:
	case 1011:
		goto LABEL_55;
	case 1012:
	case 1013:
	case 1014:
	case 1015:
		goto LABEL_56;
	case 1016:
		goto LABEL_57;
	default:
	LABEL_58:
		result = 0.0;
		break;
	}
	return result;
}
//RETURN_LIFE_VALUE
float PATSYSTEM::ReturnLifeValue(int pIndex, int pGrowUpValue)
{
	int tMaxRangeValueIndex;
	float result;
	if (pIndex != 1004
		&& pIndex != 1007
		&& pIndex != 1009
		&& pIndex != 1011
		&& pIndex != 1012
		&& pIndex != 17053
		&& pIndex != 1014
		&& pIndex != 1015
		&& pIndex != 1016
		&& pIndex != 1310
		&& pIndex != 17055
		&& pIndex != 1311
		&& pIndex != 17056
		&& pIndex != 1312
		&& pIndex != 17057
		&& pIndex != 549
		&& pIndex != 550
		&& pIndex != 544
		&& pIndex != 545
		&& pIndex != 546
		&& pIndex != 562
		&& pIndex != 86820
		&& pIndex != 2133
		&& pIndex != 2144
		&& pIndex != 2160)
	{
		return 0.0;
	}
	if (pGrowUpValue < 1)
		return 0.0;
	if (pIndex <= 1005)
	{
		if (pIndex < 1002)
		{
			switch (pIndex)
			{
			case 541:
			case 542:
			case 547:
			case 560:
				break;
			case 543:
			case 544:
			case 548:
			case 561:
				goto LABEL_44;
			case 545:
			case 549:
			case 562:
				goto LABEL_45;
			case 546:
			case 550:
				goto LABEL_46;
			default:
				goto LABEL_47;
			}
		}
		tMaxRangeValueIndex = 0;
		goto LABEL_48;
	}
	if (pIndex > 2144)
	{
		if (pIndex > 17053)
		{
			if (pIndex <= 17057)
			{
			LABEL_46:
				tMaxRangeValueIndex = 3;
				goto LABEL_48;
			}
		}
		else if (pIndex != 17053)
		{
			goto LABEL_46;
		}
	LABEL_45:
		tMaxRangeValueIndex = 2;
	LABEL_48:
		if (pIndex == 1310 || pIndex == 17055)
		{
			if (pGrowUpValue < mMaxRangeValue[tMaxRangeValueIndex])
			{
				result = (float)pGrowUpValue * 4000.0 / (float)mMaxRangeValue[tMaxRangeValueIndex];
			}
			else
			{
				result = 4400.0;
			}
		}
		else if (pGrowUpValue < mMaxRangeValue[tMaxRangeValueIndex])
		{
			result = (float)pGrowUpValue * 2000.0 / (float)mMaxRangeValue[tMaxRangeValueIndex];
		}
		else
		{
			result = 2200.0;
		}
		return result;
	}
	if (pIndex == 2144 || pIndex > 1312 || pIndex >= 1310)
		goto LABEL_46;
	switch (pIndex)
	{
	case 1006:
	case 1007:
	case 1008:
	case 1009:
	case 1010:
	case 1011:
	LABEL_44:
		tMaxRangeValueIndex = 1;
		goto LABEL_48;
	case 1012:
	case 1013:
	case 1014:
	case 1015:
		goto LABEL_45;
	case 1016:
		goto LABEL_46;
	default:
	LABEL_47:
		result = 0.0;
		break;
	}
	return result;
}
//RETURN_MANA_VALUE
float PATSYSTEM::ReturnManaValue(int pIndex, int pGrowUpValue)
{
	int tMaxRangeValueIndex;
	float result;
	if (pIndex != 1005
		&& pIndex != 1008
		&& pIndex != 1010
		&& pIndex != 1011
		&& pIndex != 1013
		&& pIndex != 1014
		&& pIndex != 1015
		&& pIndex != 1016
		&& pIndex != 1310
		&& pIndex != 17055
		&& pIndex != 1311
		&& pIndex != 17056
		&& pIndex != 1312
		&& pIndex != 17057
		&& pIndex != 550
		&& pIndex != 546
		&& pIndex != 2133
		&& pIndex != 2144
		&& pIndex != 2160)
	{
		return 0.0;
	}
	if (pGrowUpValue < 1)
		return 0.0;
	if (pIndex <= 1005)
	{
		if (pIndex < 1002)
		{
			switch (pIndex)
			{
			case 541:
			case 542:
			case 547:
			case 560:
				break;
			case 543:
			case 544:
			case 548:
			case 561:
				goto LABEL_34;
			case 545:
			case 549:
			case 562:
				goto LABEL_35;
			case 546:
			case 550:
				goto LABEL_36;
			default:
				goto LABEL_37;
			}
		}
		tMaxRangeValueIndex = 0;
		goto LABEL_38;
	}
	if (pIndex > 2144 || pIndex == 2144 || pIndex > 1312 || pIndex >= 1310)
	{
	LABEL_36:
		tMaxRangeValueIndex = 3;
	LABEL_38:
		if (pIndex == 1310 || pIndex == 17055)
		{
			if (pGrowUpValue < mMaxRangeValue[tMaxRangeValueIndex])
			{
				result = (float)pGrowUpValue * 3600.0 / (float)mMaxRangeValue[tMaxRangeValueIndex];
			}
			else
			{
				result = 4000.0;
			}
		}
		else if (pGrowUpValue < mMaxRangeValue[tMaxRangeValueIndex])
		{
			result = (float)pGrowUpValue * 1800.0 / (float)mMaxRangeValue[tMaxRangeValueIndex];
		}
		else
		{
			result = 2000.0;
		}
		return result;
	}
	switch (pIndex)
	{
	case 1006:
	case 1007:
	case 1008:
	case 1009:
	case 1010:
	case 1011:
	LABEL_34:
		tMaxRangeValueIndex = 1;
		goto LABEL_38;
	case 1012:
	case 1013:
	case 1014:
	case 1015:
	LABEL_35:
		tMaxRangeValueIndex = 2;
		goto LABEL_38;
	case 1016:
		goto LABEL_36;
	default:
	LABEL_37:
		result = 0.0;
		break;
	}
	return result;
}
//PetExp200
int PATSYSTEM::PetExp200(int pIndex, int pGrowUpValue, int pActivityValue)
{
	int result = 0;
	int tMaxRangeValueIndex = 0;;

	if (pIndex != 1002
		&& pIndex != 1003
		&& pIndex != 1004
		&& pIndex != 1005
		&& pIndex != 1006
		&& pIndex != 17052
		&& pIndex != 1007
		&& pIndex != 1008
		&& pIndex != 1009
		&& pIndex != 1010
		&& pIndex != 1011
		&& pIndex != 1012
		&& pIndex != 17053
		&& pIndex != 1013
		&& pIndex != 1014
		&& pIndex != 1015
		&& pIndex != 1016
		&& pIndex != 1310
		&& pIndex != 17055
		&& pIndex != 1311
		&& pIndex != 17056
		&& pIndex != 1312
		&& pIndex != 17057
		&& pIndex != 2133
		&& pIndex != 2144
		&& pIndex != 2160)
	{
		return 0;
	}
	if (pActivityValue < 1)
		return 0;
	if (pIndex > 2133)
	{
		if (pIndex > 2160 || pIndex != 2160 && pIndex == 2140)
		{
			tMaxRangeValueIndex = 0;
			goto LABEL_SONUC;
		}
		tMaxRangeValueIndex = 3;
		goto LABEL_SONUC;
	}
	if (pIndex == 2133)
	{
	LABEL_SONUC:
		if (pGrowUpValue < mMaxRangeValue[tMaxRangeValueIndex])
		{
			return 0;
		}
		if ((double)(pGrowUpValue / (mMaxRangeValue[tMaxRangeValueIndex] / 100000)) / 1000 < 101.0)
			return 0;
		if ((double)(pGrowUpValue / (mMaxRangeValue[tMaxRangeValueIndex] / 100000)) / 1000 < 125.0)
			return 50;
		if ((double)(pGrowUpValue / (mMaxRangeValue[tMaxRangeValueIndex] / 100000)) / 1000 < 150.0)
			return 100;
		if ((double)(pGrowUpValue / (mMaxRangeValue[tMaxRangeValueIndex] / 100000)) / 1000 < 175.0)
			return 150;
		if ((double)(pGrowUpValue / (mMaxRangeValue[tMaxRangeValueIndex] / 100000)) / 1000 >= 200.0)
			return 250;
		return 200;
	}
	switch (pIndex)
	{
	case 1002:
	case 1003:
	case 1004:
	case 1005:
		tMaxRangeValueIndex = 0;
		goto LABEL_SONUC;
	case 1006:
	case 1007:
	case 1008:
	case 1009:
	case 1010:
	case 1011:
		tMaxRangeValueIndex = 1;
		goto LABEL_SONUC;
	case 1012:
	case 1013:
	case 1014:
	case 1015:
	LABEL_35:
		tMaxRangeValueIndex = 2;
		goto LABEL_SONUC;
	case 1016:
		tMaxRangeValueIndex = 3;
		goto LABEL_SONUC;
	default:
		result = 0;
		break;
	}
	return result;
}
//ReturnNewPets
int PATSYSTEM::ReturnNewPets(int PetKodu, int PetExp, int tSort)
{
	int result; // eax
	int v5; // [esp+24h] [ebp-8h]
	int tMaxRangeValueIndex; // [esp+28h] [ebp-4h]
	ITEM_INFO* ItemInfo;

	if (PetKodu == -1 || !PetKodu)
		return 0;
	if (!PetExp)
		return 0;
	ItemInfo = mITEM.Search(PetKodu);
	if (!ItemInfo)
		return 0;
	if (ItemInfo->iSort != 28)
		return 0;
	if (ItemInfo->iIndex == 2253 || ItemInfo->iIndex == 2254)
		return 0;
	if (ItemInfo->iIndex == 2261 || ItemInfo->iIndex == 2262 || ItemInfo->iIndex == 2300 || ItemInfo->iIndex == 2301)
		return 0;
	v5 = mUTIL.ReturnISValue(PetExp);
	if (v5 < 10)
		return 0;
	tMaxRangeValueIndex = v5 % 10;
	if (v5 / 10 != tSort)
		return 0;
	switch (tSort)
	{
	case 1:
		switch (tMaxRangeValueIndex)
		{
		case 0:
			result = 30;
			break;
		case 1:
			result = 60;
			break;
		case 2:
			result = 90;
			break;
		case 3:
			result = 120;
			break;
		case 4:
			result = 150;
			break;
		case 5:
			result = 180;
			break;
		case 6:
			result = 210;
			break;
		case 7:
			result = 240;
			break;
		case 8:
			result = 270;
			break;
		case 9:
			result = 300;
			break;
		default:
			result = 0;
			break;
		}
		break;
	case 2:
		switch (tMaxRangeValueIndex)
		{
		case 0:
			result = 200;
			break;
		case 1:
			result = 400;
			break;
		case 2:
			result = 600;
			break;
		case 3:
			result = 800;
			break;
		case 4:
			result = 1000;
			break;
		case 5:
			result = 1200;
			break;
		case 6:
			result = 1400;
			break;
		case 7:
			result = 1600;
			break;
		case 8:
			result = 1800;
			break;
		case 9:
			result = 2000;
			break;
		default:
			result = 0;
			break;
		}
		break;
	case 3:
		switch (tMaxRangeValueIndex)
		{
		case 0:
			result = 20;
			break;
		case 1:
			result = 40;
			break;
		case 2:
			result = 60;
			break;
		case 3:
			result = 80;
			break;
		case 4:
			result = 100;
			break;
		case 5:
			result = 120;
			break;
		case 6:
			result = 140;
			break;
		case 7:
			result = 160;
			break;
		case 8:
			result = 180;
			break;
		case 9:
			result = 200;
			break;
		default:
			result = 0;
			break;
		}
		break;
	case 4:
		switch (tMaxRangeValueIndex)
		{
		case 0:
			result = 250;
			break;
		case 1:
			result = 500;
			break;
		case 2:
			result = 750;
			break;
		case 3:
			result = 1000;
			break;
		case 4:
			result = 1250;
			break;
		case 5:
			result = 1500;
			break;
		case 6:
			result = 1750;
			break;
		case 7:
			result = 2000;
			break;
		case 8:
			result = 2250;
			break;
		case 9:
			result = 2500;
			break;
		default:
			result = 0;
			break;
		}
		break;
	case 5:
		switch (tMaxRangeValueIndex)
		{
		case 0:
			result = 100;
			break;
		case 1:
			result = 200;
			break;
		case 2:
			result = 300;
			break;
		case 3:
			result = 400;
			break;
		case 4:
			result = 500;
			break;
		case 5:
			result = 600;
			break;
		case 6:
			result = 700;
			break;
		case 7:
			result = 800;
			break;
		case 8:
			result = 900;
			break;
		case 9:
			result = 1000;
			break;
		default:
			result = 0;
			break;
		}
		break;
	case 6:
		switch (tMaxRangeValueIndex)
		{
		case 0:
			result = 100;
			break;
		case 1:
			result = 200;
			break;
		case 2:
			result = 300;
			break;
		case 3:
			result = 400;
			break;
		case 4:
			result = 500;
			break;
		case 5:
			result = 600;
			break;
		case 6:
			result = 700;
			break;
		case 7:
			result = 800;
			break;
		case 8:
			result = 900;
			break;
		case 9:
			result = 1000;
			break;
		default:
			result = 0;
			break;
		}
		break;
	default:
		result = 0;
		break;
	}
	return result;
}
//ReturnNewPetCombine
float PATSYSTEM::ReturnNewPetCombine(int PetKodu, int PetExp, int tSort)
{

	float result; // eax
	int v5; // [esp+24h] [ebp-8h]
	int tMaxRangeValueIndex; // [esp+28h] [ebp-4h]
	ITEM_INFO* ItemInfo;

	if (PetKodu == -1 || !PetKodu)
		return 0.0;
	if (!PetExp)
		return 0.0;
	ItemInfo = mITEM.Search(PetKodu);
	if (!PetKodu)
		return 0.0;
	if (ItemInfo->iSort != 28)
		return 0.0;
	if (ItemInfo->iIndex == 2253 || ItemInfo->iIndex == 2254)
		return 0.0;
	if (ItemInfo->iIndex == 2261 || ItemInfo->iIndex == 2262 || ItemInfo->iIndex == 2300 || ItemInfo->iIndex == 2301)
		return 0.0;
	v5 = mUTIL.ReturnIBValue(PetExp);
	if (v5 < 10)
		return 0.0;
	tMaxRangeValueIndex = v5 % 10;
	if (v5 / 10 != tSort)
		return 0.0;
	switch (tSort)
	{
	case 1:
		switch (tMaxRangeValueIndex)
		{
		case 0:
			result = 30.0;
			break;
		case 1:
			result = 60.0;
			break;
		case 2:
			result = 90.0;
			break;
		case 3:
			result = 120.0;
			break;
		case 4:
			result = 150.0;
			break;
		case 5:
			result = 180.0;
			break;
		case 6:
			result = 210.0;
			break;
		case 7:
			result = 240.0;
			break;
		case 8:
			result = 270.0;
			break;
		case 9:
			result = 300.0;
			break;
		default:
			result = 0.0;
			break;
		}
		break;
	case 2:
		switch (tMaxRangeValueIndex)
		{
		case 0:
			result = 200.0;
			break;
		case 1:
			result = 400.0;
			break;
		case 2:
			result = 600.0;
			break;
		case 3:
			result = 800.0;
			break;
		case 4:
			result = 1000.0;
			break;
		case 5:
			result = 1200.0;
			break;
		case 6:
			result = 1400.0;
			break;
		case 7:
			result = 1600.0;
			break;
		case 8:
			result = 1800.0;
			break;
		case 9:
			result = 2000.0;
			break;
		default:
			result = 0.0;
			break;
		}
		break;
	case 3:
		switch (tMaxRangeValueIndex)
		{
		case 0:
			result = 100.0;
			break;
		case 1:
			result = 200.0;
			break;
		case 2:
			result = 300.0;
			break;
		case 3:
			result = 400.0;
			break;
		case 4:
			result = 500.0;
			break;
		case 5:
			result = 600.0;
			break;
		case 6:
			result = 700.0;
			break;
		case 7:
			result = 800.0;
			break;
		case 8:
			result = 900.0;
			break;
		case 9:
			result = 1000.0;
			break;
		default:
			result = 0.0;
			break;
		}
		break;
	case 4:
		switch (tMaxRangeValueIndex)
		{
		case 0:
			result = 100.0;
			break;
		case 1:
			result = 200.0;
			break;
		case 2:
			result = 300.0;
			break;
		case 3:
			result = 400.0;
			break;
		case 4:
			result = 500.0;
			break;
		case 5:
			result = 600.0;
			break;
		case 6:
			result = 700.0;
			break;
		case 7:
			result = 800.0;
			break;
		case 8:
			result = 900.0;
			break;
		case 9:
			result = 1000.0;
			break;
		default:
			result = 0.0;
			break;
		}
		break;
	case 5:
		switch (tMaxRangeValueIndex)
		{
		case 0:
			result = 0.30000001;
			break;
		case 1:
			result = 0.30000001;
			break;
		case 2:
			result = 0.89999998;
			break;
		case 3:
			result = 1.2;
			break;
		case 4:
			result = 1.5;
			break;
		case 5:
			result = 1.8;
			break;
		case 6:
			result = 2.0999999;
			break;
		case 7:
			result = 2.4000001;
			break;
		case 8:
			result = 2.7;
			break;
		case 9:
			result = 3.0;
			break;
		default:
			result = 0.0;
			break;
		}
		break;
	default:
		result = 0.0;
		break;
	}
	return result;
}

float PATSYSTEM::ReturnEpicPets(int PetKodu)
{
	double result; // st7
	ITEM_INFO* ItemInfo;

	ItemInfo = mITEM.Search(PetKodu);
	if (!ItemInfo)
		return 0.0;
	if (ItemInfo->iSort != 28)
		return 0.0;
	if (PetKodu > 2409)
	{
		switch (PetKodu)
		{
		case 2410:
			result = 4000.0;
			break;
		case 2411:
			result = 3800.0;
			break;
		case 2412:
			result = 3600.0;
			break;
		case 2413:
			result = 3000.0;
			break;
		case 2414:
			result = 3000.0;
			break;
		case 2415:
			result = 3000.0;
			break;
		case 2416:
			result = 3500.0;
			break;
		case 2417:
			result = 3400.0;
			break;
		case 2418:
			result = 3300.0;
			break;
		case 2419:
			result = 3500.0;
			break;
		case 2420:
			result = 3400.0;
			break;
		case 2421:
			result = 3300.0;
			break;
		default:
			result = 0.0;
			break;
		}
	}
	else
	{
		switch (PetKodu)
		{
		case 2151:
			result = 4000.0;
			break;
		case 2152:
			result = 3500.0;
			break;
		case 2153:
			result = 3000.0;
			break;
		case 2154:
			result = 3500.0;
			break;
		case 2174:
			result = 3800.0;
			break;
		case 2175:
			result = 3600.0;
			break;
		case 2176:
			result = 3400.0;
			break;
		case 2177:
			result = 3200.0;
			break;
		case 2178:
			result = 3400.0;
			break;
		case 2179:
			result = 3300.0;
			break;
		case 2180:
			result = 3200.0;
			break;
		case 2181:
			result = 3100.0;
			break;
		case 2182:
			result = 3000.0;
			break;
		case 2183:
			result = 3000.0;
			break;
		case 2184:
			result = 3000.0;
			break;
		case 2185:
			result = 3000.0;
			break;
		case 2186:
			result = 3400.0;
			break;
		case 2187:
			result = 3300.0;
			break;
		case 2188:
			result = 3200.0;
			break;
		case 2189:
			result = 3100.0;
			break;
		case 2195:
			result = 7000.0;
			break;
		case 2196:
			result = 6800.0;
			break;
		case 2197:
			result = 6600.0;
			break;
		case 2198:
			result = 6000.0;
			break;
		case 2199:
			result = 6000.0;
			break;
		case 2200:
			result = 6000.0;
			break;
		case 2201:
			result = 6500.0;
			break;
		case 2202:
			result = 6400.0;
			break;
		case 2203:
			result = 6300.0;
			break;
		case 2204:
			result = 6500.0;
			break;
		case 2205:
			result = 6400.0;
			break;
		case 2206:
			result = 6300.0;
			break;
		case 2253:
			result = 2000.0;
			break;
		case 2254:
			result = 4000.0;
			break;
		case 2261:
			result = 2000.0;
			break;
		case 2262:
			result = 4000.0;
			break;
		case 2300:
			result = 2000.0;
			break;
		case 2301:
			result = 4000.0;
			break;
		case 2302:
			result = 3500.0;
			break;
		default:
			result = 0.0;
			break;
		}
	}
	return result;
}

float PATSYSTEM::ReturnLegandryPets(int PetKodu)
{
	double result; // st7
	int v2; // [esp+8h] [ebp-4h]
	ITEM_INFO* ItemInfo;

	ItemInfo = mITEM.Search(PetKodu);
	if (!ItemInfo)
		return 0.0;
	if (ItemInfo->iSort != 31 && ItemInfo->iSort != 32)
		return 0.0;
	if (PetKodu > 1887)
	{
		if (PetKodu > 17203)
		{
			if (PetKodu == 17204)
				return 8000.0;
		}
		else
		{
			switch (PetKodu)
			{
			case 17203:
				return 8000.0;
			case 1889:
				return 8000.0;
			case 17202:
				return 8000.0;
			}
		}
		result = 0.0;
	}
	else if (PetKodu == 1887)
	{
		result = 8000.0;
	}
	else
	{
		switch (PetKodu)
		{
		case 1838:
			result = 8000.0;
			break;
		case 1840:
			result = 8000.0;
			break;
		case 1841:
			result = 8000.0;
			break;
		case 1842:
			result = 8000.0;
			break;
		default:
			result = 0.0;
			break;
		}
	}
	return result;
}
//-------------------------------------------------------------------------------------------------
//RETURN_MAX_PET_EXP
int PATSYSTEM::ReturnMaxPetExp(int pIndex)
{
	int maxExp = 0;
	if (pIndex <= 1005)
	{
		if (pIndex < 1002)
		{
			switch (pIndex)
			{
			case 541:
			case 542:
			case 547:
			case 560:
				break;
			case 543:
			case 544:
			case 548:
			case 561:
				goto LABEL_24;
			case 545:
			case 549:
			case 562:
				goto LABEL_25;
			case 546:
			case 550:
				goto LABEL_26;
			default:
				return 0.0;
			}
		}
		maxExp = 0;
		return mMaxRangeValue[maxExp];
	}
	if (pIndex <= 2144)
	{
		if (pIndex == 2144)
			goto LABEL_26;
		if (pIndex <= 1312)
		{
			if (pIndex < 1310)
			{
				switch (pIndex)
				{
				case 1006:
				case 1007:
				case 1008:
				case 1009:
				case 1010:
				case 1011:
					goto LABEL_24;
				case 1012:
				case 1013:
				case 1014:
				case 1015:
					goto LABEL_25;
				case 1016:
					goto LABEL_26;
				default:
					return 0.0;
				}
			}
			goto LABEL_26;
		}
		if (pIndex != 1452)
		{
			if (pIndex != 2133)
				return 0.0;
		LABEL_26:
			maxExp = 3;
			return mMaxRangeValue[maxExp];
		}
		goto LABEL_24;
	}
	if (pIndex > 17057)
	{
		if (pIndex != 86819)
		{
			if (pIndex != 86820)
				return 0.0;
		LABEL_25:
			maxExp = 2;
			return mMaxRangeValue[maxExp];
		}
	}
	else
	{
		if (pIndex >= 17055 || pIndex == 2160)
			goto LABEL_26;
		if (pIndex != 17052)
		{
			if (pIndex != 17053)
				return 0.0;
			goto LABEL_25;
		}
	}
LABEL_24:
	maxExp = 1;
	return mMaxRangeValue[maxExp];
}
//-------------------------------------------------------------------------------------------------
//CLASS_OF_SKILLSYSTEM
//-------------------------------------------------------------------------------------------------
//INSTANCE
SOCKETSYSTEM mSocket;
//CREATE
SOCKETSYSTEM::SOCKETSYSTEM(void)
{
	mDataNum = 0;
	mDATA = NULL;
}
//CHECK_VALID_ELEMENT
BOOL SOCKETSYSTEM::CheckValidElement(int tArrayIndex)
{

	if (!mDATA[tArrayIndex].SocketSirasi)
		return 1;
	if (!mDATA[tArrayIndex].Type)
		return 1;
	if (mDATA[tArrayIndex].Type < 1 || mDATA[tArrayIndex].Type > 54)
		return 0;
	if (mDATA[tArrayIndex].unk1 < 0 && mDATA[tArrayIndex].Type > 10000)
		return 0;
	if (mDATA[tArrayIndex].Type == 1)
	{
		if (mDATA[tArrayIndex].SocketSirasi < 1 || mDATA[tArrayIndex].SocketSirasi > 33)
			return 0;
		if (mDATA[tArrayIndex].Stat1 < 0 || mDATA[tArrayIndex].Stat1 > 400)
			return 0;
		if (mDATA[tArrayIndex].Stat2 < 0 || mDATA[tArrayIndex].Stat2 > 400)
			return 0;
	}
	return 1;
}

//INIT
BOOL SOCKETSYSTEM::Init(char* tFileName)
{
	int index01;
	DWORD nReadByte;
	DWORD tOriginalSize;
	BYTE* tOriginal;
	DWORD tCompressSize;
	BYTE* tCompress;
	int tDataNum;
	SOCKET_INFO* tDATA;
	BOOL tCheckFirstCreate;

	Free();
	HANDLE hFile;
	hFile = CreateFile(tFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	if (!ReadFile(hFile, &tOriginalSize, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	tOriginal = (BYTE*)GlobalAlloc(GMEM_FIXED, tOriginalSize);
	if (tOriginal == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!ReadFile(hFile, &tCompressSize, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	tCompress = (BYTE*)GlobalAlloc(GMEM_FIXED, tCompressSize);
	if (tCompress == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!ReadFile(hFile, tCompress, tCompressSize, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != tCompressSize)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!CloseHandle(hFile))
	{
		return FALSE;
	}
	if (!mGAME.Decompress(tCompressSize, tCompress, tOriginalSize, tOriginal))
	{
		return FALSE;
	}
	mSharedMemSize = 0;
	CopyMemory(&tDataNum, &tOriginal[0], 4);
	mSharedMemSize += 4;
	tDataNum = 500;
	if (tDataNum != 500)
	{
		return FALSE;
	}
	tDATA = (SOCKET_INFO*)GlobalAlloc(GMEM_FIXED, (tDataNum * sizeof(SOCKET_INFO)));
	if (tDATA == NULL)
	{
		return FALSE;
	}
	CopyMemory(&tDATA[0], &tOriginal[26], (tDataNum * sizeof(SOCKET_INFO)));
	mSharedMemSize += (tDataNum * sizeof(SOCKET_INFO));
	GlobalFree(tCompress);
	GlobalFree(tOriginal);
	mDataNum = tDataNum;
	mDATA = tDATA;
	for (index01 = 0; index01 < mDataNum; index01++)
	{
		if (!CheckValidElement(index01))
		{
			return FALSE;
		}
	}
	mSharedMemMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, mSharedMemSize, "SHAREMEM_SOCKETSYSTEM");
	if (mSharedMemMap == NULL)
	{
		return FALSE;
	}
	if (GetLastError() != ERROR_ALREADY_EXISTS)
	{
		tCheckFirstCreate = TRUE;
	}
	else
	{
		tCheckFirstCreate = FALSE;
	}
	mSharedPostMem = (BYTE*)MapViewOfFile(mSharedMemMap, FILE_MAP_ALL_ACCESS, 0, 0, mSharedMemSize);
	if (mSharedPostMem == NULL)
	{
		return FALSE;
	}
	mSharedMemSizeForCheck = 0;
	if (tCheckFirstCreate)
	{
		CopyMemory(&mSharedPostMem[mSharedMemSizeForCheck], &mDataNum, 4);
	}
	CopyMemory(&mSharedSocketData.mDataNum, &mSharedPostMem[mSharedMemSizeForCheck], 4);
	mSharedMemSizeForCheck += 4;
	if (tCheckFirstCreate)
	{
		CopyMemory(&mSharedPostMem[mSharedMemSizeForCheck], mDATA, (mDataNum * sizeof(SOCKET_INFO)));
	}
	mSharedSocketData.mDATA = (SOCKET_INFO*)&mSharedPostMem[mSharedMemSizeForCheck];
	mSharedMemSizeForCheck += (mDataNum * sizeof(SOCKET_INFO));
	if (mSharedMemSize != mSharedMemSizeForCheck)
	{
		return FALSE;
	}
	mDataNum = 0;
	if (mDATA)
	{
		GlobalFree(mDATA);
		mDATA = NULL;
	}
	return TRUE;
}
//FREE
void SOCKETSYSTEM::Free(void)
{
	mDataNum = 0;
	if (mDATA)
	{
		free(mDATA);
		mDATA = NULL;
	}
	if (mSharedPostMem != NULL)
	{
		UnmapViewOfFile(mSharedPostMem);
		//shmdt( mSharedPostMem );
		mSharedPostMem = NULL;
	}
	if (mSharedMemMap != 0)
	{
		CloseHandle(mSharedMemMap);
		//shmctl(mSharedMemMap, IPC_RMID, 0);
		mSharedMemMap = 0;
	}
}
//SEARCH
SOCKET_INFO* SOCKETSYSTEM::Search(int tSort, int pIndex)
{
	int i; // [esp+4h] [ebp-4h]

	if (pIndex < 1 || tSort < 1)
		return 0;
	for (i = 0; i < 3500; ++i)
	{
		if (mSharedSocketData.mDATA[i].Type == tSort && mSharedSocketData.mDATA[i].SocketSirasi == pIndex)
			return &mSharedSocketData.mDATA[(pIndex - 1)];
	}
	return 0;
}