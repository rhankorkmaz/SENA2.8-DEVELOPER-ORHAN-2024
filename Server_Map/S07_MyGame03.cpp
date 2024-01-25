//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "Shengming.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_UTIL
//-------------------------------------------------------------------------------------------------
//INSTANCE
MyUtil mUTIL;
//CREATE
MyUtil::MyUtil(void)
{
	mEquipPart[0] = 2;
	mEquipPart[1] = 3;
	mEquipPart[2] = 4;
	mEquipPart[3] = 5;
	mEquipPart[4] = 6;
	mEquipPart[5] = 7;
	mEquipPart[6] = 0;
	mEquipPart[7] = 9;
	mEquipPart[8] = 10;
	mEquipPart[9] = 11;
	mEquipPart[10] = 12;
	mEquipPart[11] = 13;
	mEquipPart[12] = 14;
}

static char* ALLOWED_CHARACTERS[] = {
	"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "r", "s", "t", "u", "w", "y", "x", "z", "q", "v",
	"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "R", "S", "T", "U", "W", "Y", "X", "Z", "Q", "V",
	"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"
};

static int ALLOWED_CHARACTERS_SIZE = sizeof(ALLOWED_CHARACTERS) / sizeof(*ALLOWED_CHARACTERS);


//CHECK_NAME_STRING
BOOL MyUtil::CheckNameString(char* tString)
{
	int index01;
	WORD tUnicode;

	int tStringLen = strlen(tString);

	if (tStringLen < 1) {
		return FALSE;
	}

	for (index01 = 0; index01 < tStringLen; index01++)
	{
		char character = tString[index01];

		bool whitelisted = FALSE;

		for (int aStringIndex = 0; aStringIndex < ALLOWED_CHARACTERS_SIZE; aStringIndex++) {
			char allowed = *ALLOWED_CHARACTERS[aStringIndex];

			if (character == allowed) {
				whitelisted = TRUE;
				break;
			}
		}

		if (!whitelisted) {
			cout << "Not allowed character: " << character << endl;
			return FALSE;
		}

	}

	return TRUE;
}
//CHECK_OVER_MAXIMUM
BOOL MyUtil::CheckOverMaximum(int tValue1, int tValue2)
{
	LONGLONG tCheckValue = (LONGLONG)tValue1 + (LONGLONG)tValue2;

	if (tCheckValue > MAX_NUMBER_SIZE)
	{
		return TRUE;
	}
	return FALSE;
}
//RETURN_FIXED_LEVEL
int MyUtil::ReturnFixedLevel(int tLevel)
{
	if (tLevel < 100)
	{
		return tLevel;
	}
	switch (tLevel)
	{
	case 100: return 102;
	case 101: return 105;
	case 102: return 108;
	case 103: return 111;
	case 104: return 114;
	case 105: return 117;
	case 106: return 120;
	case 107: return 123;
	case 108: return 126;
	case 109: return 129;
	case 110: return 132;
	case 111: return 135;
	case 112: return 138;
	case 113: return 143;
	case 114: return 149;
	case 115: return 155;
	case 116: return 161;
	case 117: return 167;
	case 118: return 173;
	case 119: return 179;
	case 120: return 185;
	case 121: return 191;
	case 122: return 197;
	case 123: return 203;
	case 124: return 209;
	case 125: return 215;
	case 126: return 221;
	case 127: return 227;
	case 128: return 233;
	case 129: return 239;
	case 130: return 245;
	case 131: return 251;
	case 132: return 257;
	case 133: return 263;
	case 134: return 269;
	case 135: return 275;
	case 136: return 281;
	case 137: return 287;
	case 138: return 293;
	case 139: return 299;
	case 140: return 305;
	case 141: return 311;
	case 142: return 317;
	case 143: return 323;
	case 144: return 329;
	case 145: return 0;
	case 146: return 355;
	case 147: return 375;
	case 148: return 395;
	case 149: return 415;
	case 150: return 455;
	case 151: return 495;
	case 152: return 535;
	case 153: return 575;
	case 154: return 635;
	case 155: return 695;
	case 156: return 755;
	case 157: return 815;
	}
	return 1;
}
//CHECK_POSSIBLE_EQUIP_ITEM
BOOL MyUtil::CheckPossibleEquipItem(int iIndex, int tTribe, int tEquipIndex, int tLevel)
{
	ITEM_INFO* tITEM_INFO;

	tITEM_INFO = mITEM.Search(iIndex);
	if (tITEM_INFO == NULL)
	{
		return FALSE;
	}
	if (tITEM_INFO->iEquipInfo[0] != 1)
	{
		if ((tITEM_INFO->iEquipInfo[0] - 2) != tTribe)
		{
			return FALSE;
		}
	}
	if ((tEquipIndex >= 0) && (tEquipIndex <= (MAX_EQUIP_SLOT_NUM - 1)))
	{
		if (tITEM_INFO->iEquipInfo[1] != mEquipPart[tEquipIndex])
		{
			return FALSE;
		}
	}
	if ((tITEM_INFO->iLevelLimit + tITEM_INFO->iMartialLevelLimit) > tLevel)
	{
		return FALSE;
	}
	return TRUE;
}

//PROCESS_FOR_EXPERIENCE
void MyUtil::ProcessForExperience(int tUserIndex, int tGainGeneralExperience, int tGainPatExperience, int tGainLifeValue)
{
	if ((tUserIndex < 0) || (tUserIndex > (mSERVER.mMAX_USER_NUM - 1)) || (!mUSER[tUserIndex].mCheckValidState) || (mUSER[tUserIndex].mMoveZoneResult == 1) || (tGainGeneralExperience < 1))
	{
		return;
	}

	int index01;
	float tMaxGeneralExperienceRange;
	int tPresentGeneralExperienceRatio;
	int tNextGeneralExperienceRatio;
	int tPresentAvatarLevel;
	int tNextAvatarLevel;

	/*if (tGainGeneralExperience < 1)
	{
		return;
	}*/

	/*if (mUSER[tUserIndex].mHealthState == 4)
	{
		tGainGeneralExperience /= 2;
		if (tGainGeneralExperience < 1)
		{
			return;
		}
	}*/
	if (mUSER[tUserIndex].mHealthState == 5)
	{
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < MAX_LIMIT_LEVEL_NUM)
	{
		tPresentAvatarLevel = mLEVEL.ReturnLevel(mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1);
		tNextAvatarLevel = mLEVEL.ReturnLevel((mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 + tGainGeneralExperience));

		if (tNextAvatarLevel > tPresentAvatarLevel)
		{
			mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 1, (tNextAvatarLevel - tPresentAvatarLevel), 0, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, tUserIndex, false);
			for (index01 = (tPresentAvatarLevel + 1); index01 <= tNextAvatarLevel; index01++)
			{
				if ((index01 - 1) < 99)
				{
					mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += 5;
				}
				else if ((index01 - 1) < 112)
				{
					mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += 15;
				}
				else
				{
					mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += 30;


				}
				mUTIL.ProcessForLevelBonusSend(tUserIndex, index01);
				//LOG_TO_FILE_2("!Skill point : %d %d\n", mUSER[tUserIndex].mAvatarInfo.aSkillPoint, index01);
				mUSER[tUserIndex].mAvatarInfo.aSkillPoint += mLEVEL.ReturnLevelFactor3(index01);
				//LOG_TO_FILE_1("!Skill point : %d\n", mUSER[tUserIndex].mAvatarInfo.aSkillPoint);
			}
			mUSER[tUserIndex].mAvatarInfo.aLevel1 = tNextAvatarLevel;
			mAVATAR_OBJECT[tUserIndex].mDATA.aLevel1 = tNextAvatarLevel;
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
			mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
		}

		if (tGainGeneralExperience > 0)
		{
			mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 += tGainGeneralExperience;

			//To pass from u32 to u33, for it to be %0.
			if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 > 1074898175)
				mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 = 1074898176;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(13, mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		if ((mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue + tGainLifeValue) > mAVATAR_OBJECT[tUserIndex].GetMaxLife())
		{
			tGainLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife() - mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue;
		}
		if (tGainLifeValue > 0)
		{
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue += tGainLifeValue;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(10, mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}

		//Pet Fix
		if (mUSER[tUserIndex].mAvatarInfo.aEquip[8][1] > 0)
		{
			if ((mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] + tGainPatExperience) > mPAT.ReturnMaxPetExp(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]) * 2)
			{
				tGainPatExperience = (mPAT.ReturnMaxPetExp(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]) * 2) - mUSER[tUserIndex].mAvatarInfo.aEquip[8][2];
			}
		}
		else
		{
			tGainPatExperience = 0;
		}
		if (tGainPatExperience > 0)
		{
			if (mPAT.ReturnGrowStep(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0], (mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] + tGainPatExperience)) > mPAT.ReturnGrowStep(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0], mUSER[tUserIndex].mAvatarInfo.aEquip[8][2]))
			{
				mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 10, 0, 0, 0);
				mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			}
			mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] += tGainPatExperience;
			mAVATAR_OBJECT[tUserIndex].mDATA.aEquipForView[8][1] += tGainPatExperience;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(14, mUSER[tUserIndex].mAvatarInfo.aEquip[8][2]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aLevel1 == MAX_LIMIT_LEVEL_NUM)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 == 2000000000
			&& mUSER[tUserIndex].mAvatarInfo.aLevel2 <= MAX_LIMIT_HIGH_LEVEL_NUM)
		{
			mUTIL.ProcessForLevelBonusSend(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aLevel2);
			switch (mUSER[tUserIndex].mAvatarInfo.aLevel2)
			{
			case 0://for m33 server
				break;
				/*case  0:
					mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += 1;
					mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
					mUSER[tUserIndex].mAvatarInfo.aLevel2 += 1;
					mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = mUSER[tUserIndex].mAvatarInfo.aLevel2;
					mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
					mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
					mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
					mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 11, mUSER[tUserIndex].mAvatarInfo.aLevel2, mUSER[tUserIndex].mAvatarInfo.aSkillPoint, 0);
					mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
					mUTIL.ProcessForLevelBonusSend(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2);
					return;
				case  1:
					if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 == mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
					{
						mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
						mUSER[tUserIndex].mAvatarInfo.aLevel2 += 1;
						mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += 1;
						mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = mUSER[tUserIndex].mAvatarInfo.aLevel2;
						mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
						mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
						mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 11, mUSER[tUserIndex].mAvatarInfo.aLevel2, mUSER[tUserIndex].mAvatarInfo.aSkillPoint, 0);
						mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
						mUTIL.ProcessForLevelBonusSend(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2);
						return;
					}
					break;
				case  2:
					if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 == mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
					{
						mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
						mUSER[tUserIndex].mAvatarInfo.aLevel2 += 1;
						mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += 1;
						mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = mUSER[tUserIndex].mAvatarInfo.aLevel2;
						mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
						mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
						mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 11, mUSER[tUserIndex].mAvatarInfo.aLevel2, mUSER[tUserIndex].mAvatarInfo.aSkillPoint, 0);
						mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
						mUTIL.ProcessForLevelBonusSend(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2);
						return;
					}
					break;
				case  3:
					if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 == mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
					{
						mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
						mUSER[tUserIndex].mAvatarInfo.aLevel2 += 1;
						mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += 1;
						mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = mUSER[tUserIndex].mAvatarInfo.aLevel2;
						mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
						mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
						mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 11, mUSER[tUserIndex].mAvatarInfo.aLevel2, mUSER[tUserIndex].mAvatarInfo.aSkillPoint, 0);
						mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
						mUTIL.ProcessForLevelBonusSend(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2);
						return;
					}
					break;

				case  4:
					if (MAX_LIMIT_HIGH_LEVEL_NUM == mUSER[tUserIndex].mAvatarInfo.aLevel2)
					{
						break;
					}
					if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 == mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
					{
						mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
						mUSER[tUserIndex].mAvatarInfo.aLevel2 += 1;
						mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += 1;
						mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = mUSER[tUserIndex].mAvatarInfo.aLevel2;
						mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
						mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
						mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 11, mUSER[tUserIndex].mAvatarInfo.aLevel2, mUSER[tUserIndex].mAvatarInfo.aSkillPoint, 0);
						mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
						mUTIL.ProcessForLevelBonusSend(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2);
						return;
					}
					break;
				case  5:
					if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 == mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
					{
						mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
						mUSER[tUserIndex].mAvatarInfo.aLevel2 += 1;
						mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += 1;
						mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = mUSER[tUserIndex].mAvatarInfo.aLevel2;
						mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
						mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
						mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 11, mUSER[tUserIndex].mAvatarInfo.aLevel2, mUSER[tUserIndex].mAvatarInfo.aSkillPoint, 0);
						mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
						mUTIL.ProcessForLevelBonusSend(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2);
						return;
					}
					break;
				case  6:
					if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 == mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
					{
						mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
						mUSER[tUserIndex].mAvatarInfo.aLevel2 += 1;
						mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += 1;
						mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = mUSER[tUserIndex].mAvatarInfo.aLevel2;
						mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
						mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
						mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 11, mUSER[tUserIndex].mAvatarInfo.aLevel2, mUSER[tUserIndex].mAvatarInfo.aSkillPoint, 0);
						mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
						mUTIL.ProcessForLevelBonusSend(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2);
						return;
					}
					break;
				case  7:
					if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 == mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
					{
						mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
						mUSER[tUserIndex].mAvatarInfo.aLevel2 += 1;
						mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += 1;
						mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = mUSER[tUserIndex].mAvatarInfo.aLevel2;
						mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
						mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
						mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 11, mUSER[tUserIndex].mAvatarInfo.aLevel2, mUSER[tUserIndex].mAvatarInfo.aSkillPoint, 0);
						mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
						mUTIL.ProcessForLevelBonusSend(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2);
						return;
					}
					break;
				case  8:
					if (MAX_LIMIT_HIGH_LEVEL_NUM == mUSER[tUserIndex].mAvatarInfo.aLevel2)
					{
						break;
					}
					if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 == mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
					{
						mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
						mUSER[tUserIndex].mAvatarInfo.aLevel2 += 1;
						mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += 1;
						mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = mUSER[tUserIndex].mAvatarInfo.aLevel2;
						mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
						mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
						mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 11, mUSER[tUserIndex].mAvatarInfo.aLevel2, mUSER[tUserIndex].mAvatarInfo.aSkillPoint, 0);
						mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
						mUTIL.ProcessForLevelBonusSend(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2);
						return;
					}
					break;
				case  9:
					if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 == mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
					{
						mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
						mUSER[tUserIndex].mAvatarInfo.aLevel2 += 1;
						mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += 1;
						mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = mUSER[tUserIndex].mAvatarInfo.aLevel2;
						mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
						mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
						mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 11, mUSER[tUserIndex].mAvatarInfo.aLevel2, mUSER[tUserIndex].mAvatarInfo.aSkillPoint, 0);
						mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
						mUTIL.ProcessForLevelBonusSend(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2);
						return;
					}
					break;
				case 10:
					if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 == mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
					{
						mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
						mUSER[tUserIndex].mAvatarInfo.aLevel2 += 1;
						mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += 1;
						mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = mUSER[tUserIndex].mAvatarInfo.aLevel2;
						mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
						mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
						mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 11, mUSER[tUserIndex].mAvatarInfo.aLevel2, mUSER[tUserIndex].mAvatarInfo.aSkillPoint, 0);
						mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
						mUTIL.ProcessForLevelBonusSend(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2);
						return;
					}
					break;
				case 11:
					if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 == mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
					{
						mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
						mUSER[tUserIndex].mAvatarInfo.aLevel2 += 1;
						mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += 1;
						mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = mUSER[tUserIndex].mAvatarInfo.aLevel2;
						mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
						mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
						mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 11, mUSER[tUserIndex].mAvatarInfo.aLevel2, mUSER[tUserIndex].mAvatarInfo.aSkillPoint, 0);
						mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
						mUTIL.ProcessForLevelBonusSend(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2);
						return;
					}
					break;
				case 12:
					break;*/
			}
		}

		//for m33
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 == 145)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 != 2000000000)
			{
				if ((mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 + tGainGeneralExperience) > 2000000000)
				{
					tGainGeneralExperience = 2000000000 - mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1;
				}
				if (tGainGeneralExperience > 0)
				{
					if ((mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 + tGainGeneralExperience) < 2000000000)
					{
						tMaxGeneralExperienceRange = (float)2000000000;
						tPresentGeneralExperienceRatio = (int)((float)mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 * 100.0f / tMaxGeneralExperienceRange);
						tNextGeneralExperienceRatio = (int)((float)(mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 + tGainGeneralExperience) * 100.0f / tMaxGeneralExperienceRange);
						if (tPresentGeneralExperienceRatio < tNextGeneralExperienceRatio)
						{
							mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (tNextGeneralExperienceRatio - tPresentGeneralExperienceRatio);
							mTRANSFER.B_AVATAR_CHANGE_INFO_2(2, mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint);
							mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
						}
					}
					else
					{
						mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += 1;
						mTRANSFER.B_AVATAR_CHANGE_INFO_2(2, mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint);
						mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					}
					mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 += tGainGeneralExperience;
					mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
					mTRANSFER.B_AVATAR_CHANGE_INFO_2(13, mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				if ((mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue + tGainLifeValue) > mAVATAR_OBJECT[tUserIndex].GetMaxLife())
				{
					tGainLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife() - mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue;
				}
				if (tGainLifeValue > 0)
				{
					mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue += tGainLifeValue;
					mTRANSFER.B_AVATAR_CHANGE_INFO_2(10, mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				//Pet Fix
				if (mUSER[tUserIndex].mAvatarInfo.aEquip[8][1] > 0)
				{
					if ((mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] + tGainPatExperience) > mPAT.ReturnMaxPetExp(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]) * 2)
					{
						tGainPatExperience = (mPAT.ReturnMaxPetExp(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]) * 2) - mUSER[tUserIndex].mAvatarInfo.aEquip[8][2];
					}
				}
				else
				{
					tGainPatExperience = 0;
				}
				if (tGainPatExperience > 0)
				{
					if (mPAT.ReturnGrowStep(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0], (mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] + tGainPatExperience)) > mPAT.ReturnGrowStep(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0], mUSER[tUserIndex].mAvatarInfo.aEquip[8][2]))
					{
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 10, 0, 0, 0);
						mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
					}


					mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] += tGainPatExperience;
					mAVATAR_OBJECT[tUserIndex].mDATA.aEquipForView[8][1] += tGainPatExperience;

					mTRANSFER.B_AVATAR_CHANGE_INFO_2(14, mUSER[tUserIndex].mAvatarInfo.aEquip[8][2]);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				return;
			}
		}

		//for deity
		if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 < 1481117817)
		{
			if ((mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 + tGainGeneralExperience) > mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
			{
				tGainGeneralExperience = mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2) - mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2;
			}
			if (tGainGeneralExperience > 0)
			{
				tMaxGeneralExperienceRange = (float)mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2);
				tPresentGeneralExperienceRatio = (int)((float)mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 * 100.0f / tMaxGeneralExperienceRange);
				tNextGeneralExperienceRatio = (int)((float)(mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 + tGainGeneralExperience) * 100.0f / tMaxGeneralExperienceRange);
				if (tPresentGeneralExperienceRatio < tNextGeneralExperienceRatio)
				{
					if (tNextGeneralExperienceRatio > 100)
					{
						tNextGeneralExperienceRatio = 100;
					}
					mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (tNextGeneralExperienceRatio - tPresentGeneralExperienceRatio);
					mTRANSFER.B_AVATAR_CHANGE_INFO_2(2, mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 += tGainGeneralExperience;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(24, mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
		}
		if ((mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue + tGainLifeValue) > mAVATAR_OBJECT[tUserIndex].GetMaxLife())
		{
			tGainLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife() - mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue;
		}
		if (tGainLifeValue > 0)
		{
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue += tGainLifeValue;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(10, mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		//Pet Exp Fix
		//Pet Fix
		if (mUSER[tUserIndex].mAvatarInfo.aEquip[8][1] > 0)
		{
			if ((mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] + tGainPatExperience) > mPAT.ReturnMaxPetExp(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]) * 2)
			{
				tGainPatExperience = (mPAT.ReturnMaxPetExp(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]) * 2) - mUSER[tUserIndex].mAvatarInfo.aEquip[8][2];
			}
		}
		else
		{
			tGainPatExperience = 0;
		}
		if (tGainPatExperience > 0)
		{
			if (mPAT.ReturnGrowStep(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0], (mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] + tGainPatExperience)) > mPAT.ReturnGrowStep(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0], mUSER[tUserIndex].mAvatarInfo.aEquip[8][2]))
			{
				mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 10, 0, 0, 0);
				mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			}
			mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] += tGainPatExperience;
			mAVATAR_OBJECT[tUserIndex].mDATA.aEquipForView[8][1] += tGainPatExperience;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(14, mUSER[tUserIndex].mAvatarInfo.aEquip[8][2]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		return;
	}

}


//PROCESS_FOR_DROP_ITEM
BOOL MyUtil::ProcessForDropItem(int tDropSort, int tItemIndex, int tItemQuantity, int tItemValue, int tItemRecognitionNumber, float tLocation[3], char tMaster[MAX_AVATAR_NAME_LENGTH], int tTribe, int Socket[3])
{
	int index01;
	ITEM_INFO* tITEM_INFO;
	ITEM_INFO* tITEM_STACK;

	switch (tDropSort)
	{
	case  1: //[����]
		break;
	case  2: //[������] ����ų.
		break;
	case  3: //[�೶->����]
		break;
	case  4: //[�] ����.
		tITEM_INFO = mITEM.Search(tItemIndex);
		if (tITEM_INFO == NULL)
		{
			return FALSE;
		}
		if (tITEM_INFO->iSort == 2)
		{
			tItemQuantity = MAX_ITEM_DUPLICATION_NUM;
		}
		break;
	case  5: //[����Ʈ] �߰�.
		break;
	case  6: //[����Ʈ] ����.
		break;
	case  7: //[Ư��������] ���.
		break;
	case  8: //[������] ����.
		break;
	case  9: //[����] ����.
		break;
	case 10: //[���¹���] ����.
		break;
	case 11: //[õ�Ẕ́�] ����.
		break;
	case 12: //Change KillOtherTribe to Itme.
		break;
	default:
		return FALSE;
	}
	tITEM_INFO = mITEM.Search(tItemIndex);
	if (tITEM_INFO == NULL)
	{
		return FALSE;
	}
	switch (tITEM_INFO->iType)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	default:
		return FALSE;
	}
	switch (tITEM_INFO->iSort)
	{
	case  1:
		tItemValue = 0;
		if ((tItemQuantity < 1) || (tItemQuantity > MAX_NUMBER_SIZE))
		{
			return FALSE;
		}
		//--------//
		//���±ݰ�//
		//--------//
		if (tDropSort == 1)
		{
			mGAME.AddTribeBankInfo(mGAME.ReturnTribeForSymbol(tTribe), (int)((float)tItemQuantity * 0.1f));
			tItemQuantity -= (int)((float)tItemQuantity * 0.1f);
		}
		//--------//
		//--------//
		//--------//
		break;
	case  2:
		tItemValue = 0;
		if ((tItemQuantity < 1) || (tItemQuantity > MAX_ITEM_DUPLICATION_NUM))
		{
			return FALSE;
		}
		break;
	case  3:
	case  4:
	case  5:
	case  6:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
	case 30:
	case 31:
	case 32:
		tItemQuantity = 0;
		tItemValue = 0;
		break;
	case  7:
	case  8:
	case  9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
		tItemQuantity = 0;
		if ((mUTIL.ReturnISValue(tItemValue) < 0) || (mUTIL.ReturnISValue(tItemValue) > MAX_IMPROVE_ITEM_NUM) || (mUTIL.ReturnIUValue(tItemValue) < 0) || (mUTIL.ReturnIUValue(tItemValue) > MAX_ADD_ITEM_NUM))
		{
			return FALSE;
		}
		break;
	case 22:
		if ((tItemQuantity < 0) || (tItemQuantity > MAX_PAT_ACTIVITY_SIZE) || (tItemValue < 0) || (tItemValue > MAX_NUMBER_SIZE))
		{
			return FALSE;
		}
		break;
	default:
		return FALSE;
	}
	for (index01 = 0; index01 < MAX_ITEM_OBJECT_NUM; index01++)
	{
		if (!mITEM_OBJECT[index01].mCheckValidState)
		{
			break;
		}
	}
	if (index01 == MAX_ITEM_OBJECT_NUM)
	{
		return FALSE;
	}

	//nova - stack box 
	tITEM_STACK = mITEM.Search(44);//Diamond box 
	if (tITEM_INFO->iIndex == 1244 || tITEM_INFO->iIndex == 531) {
		mITEM_OBJECT[index01].mCheckValidState = TRUE;
		mITEM_OBJECT[index01].mUniqueNumber = mGAME.mItemObjectUniqueNumber;
		mGAME.mItemObjectUniqueNumber++;
		mITEM_OBJECT[index01].mDATA.iIndex = tITEM_STACK->iIndex;
		mITEM_OBJECT[index01].mDATA.iQuantity = 1;
		mITEM_OBJECT[index01].mDATA.iValue = tItemValue;
		mITEM_OBJECT[index01].mDATA.iItemRecognitionNumber = tItemRecognitionNumber;
		mITEM_OBJECT[index01].mDATA.iLocation[0] = tLocation[0];
		mITEM_OBJECT[index01].mDATA.iLocation[1] = tLocation[1];
		mITEM_OBJECT[index01].mDATA.iLocation[2] = tLocation[2];
		strncpy(mITEM_OBJECT[index01].mDATA.iMaster, tMaster, MAX_AVATAR_NAME_LENGTH);
		mITEM_OBJECT[index01].mDATA.iCreateTime = GetTickCount();
		mITEM_OBJECT[index01].mDATA.iPresentTime = GetTickCount();
		mITEM_OBJECT[index01].mDATA.iCreateState = 1;
		mITEM_OBJECT[index01].mDATA.Socket[0] = Socket[0];
		mITEM_OBJECT[index01].mDATA.Socket[1] = Socket[1];
		mITEM_OBJECT[index01].mDATA.Socket[2] = Socket[2];
		mITEM_OBJECT[index01].mDATA.bul1 = 0;
		mITEM_OBJECT[index01].mDATA.bul2 = 0;
		mITEM_OBJECT[index01].mDATA.bul3 = 0;
		mITEM_OBJECT[index01].mDATA.bul4 = 0;
		mITEM_OBJECT[index01].SetSpaceIndex();
		mITEM_OBJECT[index01].mITEM_INFO = tITEM_INFO;
		mITEM_OBJECT[index01].mUpdateTimeForBroadcast = GetTickCount();
		mTRANSFER.B_ITEM_ACTION_RECV(index01, mITEM_OBJECT[index01].mUniqueNumber, &mITEM_OBJECT[index01].mDATA, 1);
		mUTIL.Broadcast(TRUE, &tLocation[0], UNIT_SCALE_RADIUS1, false);
		return TRUE;
	}

	tITEM_STACK = mITEM.Search(45);//Tin Box
	if (tITEM_INFO->iIndex == 1019 || tITEM_INFO->iIndex == 410) {
		mITEM_OBJECT[index01].mCheckValidState = TRUE;
		mITEM_OBJECT[index01].mUniqueNumber = mGAME.mItemObjectUniqueNumber;
		mGAME.mItemObjectUniqueNumber++;
		mITEM_OBJECT[index01].mDATA.iIndex = tITEM_STACK->iIndex;
		mITEM_OBJECT[index01].mDATA.iQuantity = 1;
		mITEM_OBJECT[index01].mDATA.iValue = tItemValue;
		mITEM_OBJECT[index01].mDATA.iItemRecognitionNumber = tItemRecognitionNumber;
		mITEM_OBJECT[index01].mDATA.iLocation[0] = tLocation[0];
		mITEM_OBJECT[index01].mDATA.iLocation[1] = tLocation[1];
		mITEM_OBJECT[index01].mDATA.iLocation[2] = tLocation[2];
		strncpy(mITEM_OBJECT[index01].mDATA.iMaster, tMaster, MAX_AVATAR_NAME_LENGTH);
		mITEM_OBJECT[index01].mDATA.iCreateTime = GetTickCount();
		mITEM_OBJECT[index01].mDATA.iPresentTime = GetTickCount();
		mITEM_OBJECT[index01].mDATA.iCreateState = 1;
		mITEM_OBJECT[index01].mDATA.Socket[0] = Socket[0];
		mITEM_OBJECT[index01].mDATA.Socket[1] = Socket[1];
		mITEM_OBJECT[index01].mDATA.Socket[2] = Socket[2];
		mITEM_OBJECT[index01].mDATA.bul1 = 0;
		mITEM_OBJECT[index01].mDATA.bul2 = 0;
		mITEM_OBJECT[index01].mDATA.bul3 = 0;
		mITEM_OBJECT[index01].mDATA.bul4 = 0;
		mITEM_OBJECT[index01].SetSpaceIndex();
		mITEM_OBJECT[index01].mITEM_INFO = tITEM_INFO;
		mITEM_OBJECT[index01].mUpdateTimeForBroadcast = GetTickCount();
		mTRANSFER.B_ITEM_ACTION_RECV(index01, mITEM_OBJECT[index01].mUniqueNumber, &mITEM_OBJECT[index01].mDATA, 1);
		mUTIL.Broadcast(TRUE, &tLocation[0], UNIT_SCALE_RADIUS1, false);
		return TRUE;
	}
	tITEM_STACK = mITEM.Search(46);//Dark Steel Box
	if (tITEM_INFO->iIndex == 1020 || tITEM_INFO->iIndex == 411) {
		mITEM_OBJECT[index01].mCheckValidState = TRUE;
		mITEM_OBJECT[index01].mUniqueNumber = mGAME.mItemObjectUniqueNumber;
		mGAME.mItemObjectUniqueNumber++;
		mITEM_OBJECT[index01].mDATA.iIndex = tITEM_STACK->iIndex;
		mITEM_OBJECT[index01].mDATA.iQuantity = 1;
		mITEM_OBJECT[index01].mDATA.iValue = tItemValue;
		mITEM_OBJECT[index01].mDATA.iItemRecognitionNumber = tItemRecognitionNumber;
		mITEM_OBJECT[index01].mDATA.iLocation[0] = tLocation[0];
		mITEM_OBJECT[index01].mDATA.iLocation[1] = tLocation[1];
		mITEM_OBJECT[index01].mDATA.iLocation[2] = tLocation[2];
		strncpy(mITEM_OBJECT[index01].mDATA.iMaster, tMaster, MAX_AVATAR_NAME_LENGTH);
		mITEM_OBJECT[index01].mDATA.iCreateTime = GetTickCount();
		mITEM_OBJECT[index01].mDATA.iPresentTime = GetTickCount();
		mITEM_OBJECT[index01].mDATA.iCreateState = 1;
		mITEM_OBJECT[index01].mDATA.Socket[0] = Socket[0];
		mITEM_OBJECT[index01].mDATA.Socket[1] = Socket[1];
		mITEM_OBJECT[index01].mDATA.Socket[2] = Socket[2];
		mITEM_OBJECT[index01].mDATA.bul1 = 0;
		mITEM_OBJECT[index01].mDATA.bul2 = 0;
		mITEM_OBJECT[index01].mDATA.bul3 = 0;
		mITEM_OBJECT[index01].mDATA.bul4 = 0;
		mITEM_OBJECT[index01].SetSpaceIndex();
		mITEM_OBJECT[index01].mITEM_INFO = tITEM_INFO;
		mITEM_OBJECT[index01].mUpdateTimeForBroadcast = GetTickCount();
		mTRANSFER.B_ITEM_ACTION_RECV(index01, mITEM_OBJECT[index01].mUniqueNumber, &mITEM_OBJECT[index01].mDATA, 1);
		mUTIL.Broadcast(TRUE, &tLocation[0], UNIT_SCALE_RADIUS1, false);
		return TRUE;
	}
	tITEM_STACK = mITEM.Search(47);//Black Steel Box
	if (tITEM_INFO->iIndex == 1021 || tITEM_INFO->iIndex == 412) {
		mITEM_OBJECT[index01].mCheckValidState = TRUE;
		mITEM_OBJECT[index01].mUniqueNumber = mGAME.mItemObjectUniqueNumber;
		mGAME.mItemObjectUniqueNumber++;
		mITEM_OBJECT[index01].mDATA.iIndex = tITEM_STACK->iIndex;
		mITEM_OBJECT[index01].mDATA.iQuantity = 1;
		mITEM_OBJECT[index01].mDATA.iValue = tItemValue;
		mITEM_OBJECT[index01].mDATA.iItemRecognitionNumber = tItemRecognitionNumber;
		mITEM_OBJECT[index01].mDATA.iLocation[0] = tLocation[0];
		mITEM_OBJECT[index01].mDATA.iLocation[1] = tLocation[1];
		mITEM_OBJECT[index01].mDATA.iLocation[2] = tLocation[2];
		strncpy(mITEM_OBJECT[index01].mDATA.iMaster, tMaster, MAX_AVATAR_NAME_LENGTH);
		mITEM_OBJECT[index01].mDATA.iCreateTime = GetTickCount();
		mITEM_OBJECT[index01].mDATA.iPresentTime = GetTickCount();
		mITEM_OBJECT[index01].mDATA.iCreateState = 1;
		mITEM_OBJECT[index01].mDATA.Socket[0] = Socket[0];
		mITEM_OBJECT[index01].mDATA.Socket[1] = Socket[1];
		mITEM_OBJECT[index01].mDATA.Socket[2] = Socket[2];
		mITEM_OBJECT[index01].mDATA.bul1 = 0;
		mITEM_OBJECT[index01].mDATA.bul2 = 0;
		mITEM_OBJECT[index01].mDATA.bul3 = 0;
		mITEM_OBJECT[index01].mDATA.bul4 = 0;
		mITEM_OBJECT[index01].SetSpaceIndex();
		mITEM_OBJECT[index01].mITEM_INFO = tITEM_INFO;
		mITEM_OBJECT[index01].mUpdateTimeForBroadcast = GetTickCount();
		mTRANSFER.B_ITEM_ACTION_RECV(index01, mITEM_OBJECT[index01].mUniqueNumber, &mITEM_OBJECT[index01].mDATA, 1);
		mUTIL.Broadcast(TRUE, &tLocation[0], UNIT_SCALE_RADIUS1, false);
		return TRUE;
	}
	tITEM_STACK = mITEM.Search(48);//Steel of Eternity Box
	if (tITEM_INFO->iIndex == 1022 || tITEM_INFO->iIndex == 413) {
		mITEM_OBJECT[index01].mCheckValidState = TRUE;
		mITEM_OBJECT[index01].mUniqueNumber = mGAME.mItemObjectUniqueNumber;
		mGAME.mItemObjectUniqueNumber++;
		mITEM_OBJECT[index01].mDATA.iIndex = tITEM_STACK->iIndex;
		mITEM_OBJECT[index01].mDATA.iQuantity = 1;
		mITEM_OBJECT[index01].mDATA.iValue = tItemValue;
		mITEM_OBJECT[index01].mDATA.iItemRecognitionNumber = tItemRecognitionNumber;
		mITEM_OBJECT[index01].mDATA.iLocation[0] = tLocation[0];
		mITEM_OBJECT[index01].mDATA.iLocation[1] = tLocation[1];
		mITEM_OBJECT[index01].mDATA.iLocation[2] = tLocation[2];
		strncpy(mITEM_OBJECT[index01].mDATA.iMaster, tMaster, MAX_AVATAR_NAME_LENGTH);
		mITEM_OBJECT[index01].mDATA.iCreateTime = GetTickCount();
		mITEM_OBJECT[index01].mDATA.iPresentTime = GetTickCount();
		mITEM_OBJECT[index01].mDATA.iCreateState = 1;
		mITEM_OBJECT[index01].mDATA.Socket[0] = Socket[0];
		mITEM_OBJECT[index01].mDATA.Socket[1] = Socket[1];
		mITEM_OBJECT[index01].mDATA.Socket[2] = Socket[2];
		mITEM_OBJECT[index01].mDATA.bul1 = 0;
		mITEM_OBJECT[index01].mDATA.bul2 = 0;
		mITEM_OBJECT[index01].mDATA.bul3 = 0;
		mITEM_OBJECT[index01].mDATA.bul4 = 0;
		mITEM_OBJECT[index01].SetSpaceIndex();
		mITEM_OBJECT[index01].mITEM_INFO = tITEM_INFO;
		mITEM_OBJECT[index01].mUpdateTimeForBroadcast = GetTickCount();
		mTRANSFER.B_ITEM_ACTION_RECV(index01, mITEM_OBJECT[index01].mUniqueNumber, &mITEM_OBJECT[index01].mDATA, 1);
		mUTIL.Broadcast(TRUE, &tLocation[0], UNIT_SCALE_RADIUS1, false);
		return TRUE;
	}
	tITEM_STACK = mITEM.Search(49);//Gold of Eternity Box
	if (tITEM_INFO->iIndex == 1023 || tITEM_INFO->iIndex == 414) {
		mITEM_OBJECT[index01].mCheckValidState = TRUE;
		mITEM_OBJECT[index01].mUniqueNumber = mGAME.mItemObjectUniqueNumber;
		mGAME.mItemObjectUniqueNumber++;
		mITEM_OBJECT[index01].mDATA.iIndex = tITEM_STACK->iIndex;
		mITEM_OBJECT[index01].mDATA.iQuantity = 1;
		mITEM_OBJECT[index01].mDATA.iValue = tItemValue;
		mITEM_OBJECT[index01].mDATA.iItemRecognitionNumber = tItemRecognitionNumber;
		mITEM_OBJECT[index01].mDATA.iLocation[0] = tLocation[0];
		mITEM_OBJECT[index01].mDATA.iLocation[1] = tLocation[1];
		mITEM_OBJECT[index01].mDATA.iLocation[2] = tLocation[2];
		strncpy(mITEM_OBJECT[index01].mDATA.iMaster, tMaster, MAX_AVATAR_NAME_LENGTH);
		mITEM_OBJECT[index01].mDATA.iCreateTime = GetTickCount();
		mITEM_OBJECT[index01].mDATA.iPresentTime = GetTickCount();
		mITEM_OBJECT[index01].mDATA.iCreateState = 1;
		mITEM_OBJECT[index01].mDATA.Socket[0] = Socket[0];
		mITEM_OBJECT[index01].mDATA.Socket[1] = Socket[1];
		mITEM_OBJECT[index01].mDATA.Socket[2] = Socket[2];
		mITEM_OBJECT[index01].mDATA.bul1 = 0;
		mITEM_OBJECT[index01].mDATA.bul2 = 0;
		mITEM_OBJECT[index01].mDATA.bul3 = 0;
		mITEM_OBJECT[index01].mDATA.bul4 = 0;
		mITEM_OBJECT[index01].SetSpaceIndex();
		mITEM_OBJECT[index01].mITEM_INFO = tITEM_INFO;
		mITEM_OBJECT[index01].mUpdateTimeForBroadcast = GetTickCount();
		mTRANSFER.B_ITEM_ACTION_RECV(index01, mITEM_OBJECT[index01].mUniqueNumber, &mITEM_OBJECT[index01].mDATA, 1);
		mUTIL.Broadcast(TRUE, &tLocation[0], UNIT_SCALE_RADIUS1, false);
		return TRUE;
	}
	tITEM_STACK = mITEM.Search(56);//Monster Treasuer Box
	if (tITEM_INFO->iIndex == 17083 || tITEM_INFO->iIndex == 417) {
		mITEM_OBJECT[index01].mCheckValidState = TRUE;
		mITEM_OBJECT[index01].mUniqueNumber = mGAME.mItemObjectUniqueNumber;
		mGAME.mItemObjectUniqueNumber++;
		mITEM_OBJECT[index01].mDATA.iIndex = tITEM_STACK->iIndex;
		mITEM_OBJECT[index01].mDATA.iQuantity = 1;
		mITEM_OBJECT[index01].mDATA.iValue = tItemValue;
		mITEM_OBJECT[index01].mDATA.iItemRecognitionNumber = tItemRecognitionNumber;
		mITEM_OBJECT[index01].mDATA.iLocation[0] = tLocation[0];
		mITEM_OBJECT[index01].mDATA.iLocation[1] = tLocation[1];
		mITEM_OBJECT[index01].mDATA.iLocation[2] = tLocation[2];
		strncpy(mITEM_OBJECT[index01].mDATA.iMaster, tMaster, MAX_AVATAR_NAME_LENGTH);
		mITEM_OBJECT[index01].mDATA.iCreateTime = GetTickCount();
		mITEM_OBJECT[index01].mDATA.iPresentTime = GetTickCount();
		mITEM_OBJECT[index01].mDATA.iCreateState = 1;
		mITEM_OBJECT[index01].mDATA.Socket[0] = Socket[0];
		mITEM_OBJECT[index01].mDATA.Socket[1] = Socket[1];
		mITEM_OBJECT[index01].mDATA.Socket[2] = Socket[2];
		mITEM_OBJECT[index01].mDATA.bul1 = 0;
		mITEM_OBJECT[index01].mDATA.bul2 = 0;
		mITEM_OBJECT[index01].mDATA.bul3 = 0;
		mITEM_OBJECT[index01].mDATA.bul4 = 0;
		mITEM_OBJECT[index01].SetSpaceIndex();
		mITEM_OBJECT[index01].mITEM_INFO = tITEM_INFO;
		mITEM_OBJECT[index01].mUpdateTimeForBroadcast = GetTickCount();
		mTRANSFER.B_ITEM_ACTION_RECV(index01, mITEM_OBJECT[index01].mUniqueNumber, &mITEM_OBJECT[index01].mDATA, 1);
		mUTIL.Broadcast(TRUE, &tLocation[0], UNIT_SCALE_RADIUS1, false);
		return TRUE;
	}
	tITEM_STACK = mITEM.Search(57);//Purple Jade
	if (tITEM_INFO->iIndex == 1024 || tITEM_INFO->iIndex == 415) {
		mITEM_OBJECT[index01].mCheckValidState = TRUE;
		mITEM_OBJECT[index01].mUniqueNumber = mGAME.mItemObjectUniqueNumber;
		mGAME.mItemObjectUniqueNumber++;
		mITEM_OBJECT[index01].mDATA.iIndex = tITEM_STACK->iIndex;
		mITEM_OBJECT[index01].mDATA.iQuantity = 1;
		mITEM_OBJECT[index01].mDATA.iValue = tItemValue;
		mITEM_OBJECT[index01].mDATA.iItemRecognitionNumber = tItemRecognitionNumber;
		mITEM_OBJECT[index01].mDATA.iLocation[0] = tLocation[0];
		mITEM_OBJECT[index01].mDATA.iLocation[1] = tLocation[1];
		mITEM_OBJECT[index01].mDATA.iLocation[2] = tLocation[2];
		strncpy(mITEM_OBJECT[index01].mDATA.iMaster, tMaster, MAX_AVATAR_NAME_LENGTH);
		mITEM_OBJECT[index01].mDATA.iCreateTime = GetTickCount();
		mITEM_OBJECT[index01].mDATA.iPresentTime = GetTickCount();
		mITEM_OBJECT[index01].mDATA.iCreateState = 1;
		mITEM_OBJECT[index01].mDATA.Socket[0] = Socket[0];
		mITEM_OBJECT[index01].mDATA.Socket[1] = Socket[1];
		mITEM_OBJECT[index01].mDATA.Socket[2] = Socket[2];
		mITEM_OBJECT[index01].mDATA.bul1 = 0;
		mITEM_OBJECT[index01].mDATA.bul2 = 0;
		mITEM_OBJECT[index01].mDATA.bul3 = 0;
		mITEM_OBJECT[index01].mDATA.bul4 = 0;
		mITEM_OBJECT[index01].SetSpaceIndex();
		mITEM_OBJECT[index01].mITEM_INFO = tITEM_INFO;
		mITEM_OBJECT[index01].mUpdateTimeForBroadcast = GetTickCount();
		mTRANSFER.B_ITEM_ACTION_RECV(index01, mITEM_OBJECT[index01].mUniqueNumber, &mITEM_OBJECT[index01].mDATA, 1);
		mUTIL.Broadcast(TRUE, &tLocation[0], UNIT_SCALE_RADIUS1, false);
		return TRUE;
	}

	tITEM_STACK = mITEM.Search(58);//Red Jade
	if (tITEM_INFO->iIndex == 1025 || tITEM_INFO->iIndex == 416) {
		mITEM_OBJECT[index01].mCheckValidState = TRUE;
		mITEM_OBJECT[index01].mUniqueNumber = mGAME.mItemObjectUniqueNumber;
		mGAME.mItemObjectUniqueNumber++;
		mITEM_OBJECT[index01].mDATA.iIndex = tITEM_STACK->iIndex;
		mITEM_OBJECT[index01].mDATA.iQuantity = 1;
		mITEM_OBJECT[index01].mDATA.iValue = tItemValue;
		mITEM_OBJECT[index01].mDATA.iItemRecognitionNumber = tItemRecognitionNumber;
		mITEM_OBJECT[index01].mDATA.iLocation[0] = tLocation[0];
		mITEM_OBJECT[index01].mDATA.iLocation[1] = tLocation[1];
		mITEM_OBJECT[index01].mDATA.iLocation[2] = tLocation[2];
		strncpy(mITEM_OBJECT[index01].mDATA.iMaster, tMaster, MAX_AVATAR_NAME_LENGTH);
		mITEM_OBJECT[index01].mDATA.iCreateTime = GetTickCount();
		mITEM_OBJECT[index01].mDATA.iPresentTime = GetTickCount();
		mITEM_OBJECT[index01].mDATA.iCreateState = 1;
		mITEM_OBJECT[index01].mDATA.Socket[0] = Socket[0];
		mITEM_OBJECT[index01].mDATA.Socket[1] = Socket[1];
		mITEM_OBJECT[index01].mDATA.Socket[2] = Socket[2];
		mITEM_OBJECT[index01].mDATA.bul1 = 0;
		mITEM_OBJECT[index01].mDATA.bul2 = 0;
		mITEM_OBJECT[index01].mDATA.bul3 = 0;
		mITEM_OBJECT[index01].mDATA.bul4 = 0;
		mITEM_OBJECT[index01].SetSpaceIndex();
		mITEM_OBJECT[index01].mITEM_INFO = tITEM_INFO;
		mITEM_OBJECT[index01].mUpdateTimeForBroadcast = GetTickCount();
		mTRANSFER.B_ITEM_ACTION_RECV(index01, mITEM_OBJECT[index01].mUniqueNumber, &mITEM_OBJECT[index01].mDATA, 1);
		mUTIL.Broadcast(TRUE, &tLocation[0], UNIT_SCALE_RADIUS1, false);
		return TRUE;
	}

	mITEM_OBJECT[index01].mCheckValidState = TRUE;
	mITEM_OBJECT[index01].mUniqueNumber = mGAME.mItemObjectUniqueNumber;
	mGAME.mItemObjectUniqueNumber++;
	mITEM_OBJECT[index01].mDATA.iIndex = tItemIndex;
	mITEM_OBJECT[index01].mDATA.iQuantity = tItemQuantity;
	mITEM_OBJECT[index01].mDATA.iValue = tItemValue;
	mITEM_OBJECT[index01].mDATA.iItemRecognitionNumber = tItemRecognitionNumber;
	mITEM_OBJECT[index01].mDATA.iLocation[0] = tLocation[0];
	mITEM_OBJECT[index01].mDATA.iLocation[1] = tLocation[1];
	mITEM_OBJECT[index01].mDATA.iLocation[2] = tLocation[2];
	strncpy(mITEM_OBJECT[index01].mDATA.iMaster, tMaster, MAX_AVATAR_NAME_LENGTH);
	mITEM_OBJECT[index01].mDATA.iCreateTime = GetTickCount();
	mITEM_OBJECT[index01].mDATA.iPresentTime = GetTickCount();
	mITEM_OBJECT[index01].mDATA.iCreateState = 1;
	mITEM_OBJECT[index01].mDATA.Socket[0] = Socket[0];
	mITEM_OBJECT[index01].mDATA.Socket[1] = Socket[1];
	mITEM_OBJECT[index01].mDATA.Socket[2] = Socket[2];
	mITEM_OBJECT[index01].mDATA.bul1 = 0;
	mITEM_OBJECT[index01].mDATA.bul2 = 0;
	mITEM_OBJECT[index01].mDATA.bul3 = 0;
	mITEM_OBJECT[index01].mDATA.bul4 = 0;
	mITEM_OBJECT[index01].SetSpaceIndex();
	mITEM_OBJECT[index01].mITEM_INFO = tITEM_INFO;
	mITEM_OBJECT[index01].mUpdateTimeForBroadcast = GetTickCount();
	mTRANSFER.B_ITEM_ACTION_RECV(index01, mITEM_OBJECT[index01].mUniqueNumber, &mITEM_OBJECT[index01].mDATA, 1);
	mUTIL.Broadcast(TRUE, &tLocation[0], UNIT_SCALE_RADIUS1, false);
	return TRUE;
}
//BROADCAST
//MIR
void MyUtil::Broadcast(BOOL tCheckInRange, float tPostLocation[3], int iScale, bool bUDPSend, int type)
{
	int index01;
	int tSpaceIndex[3];
	float tLocation[3];
	float tPostDistance = static_cast<float> (iScale) * mGAME.MAX_RADIUS;

	if (tCheckInRange)
	{
		tSpaceIndex[0] = (int)(tPostLocation[0] / mGAME.MAX_RADIUS);
		tSpaceIndex[1] = (int)(tPostLocation[1] / mGAME.MAX_RADIUS);
		tSpaceIndex[2] = (int)(tPostLocation[2] / mGAME.MAX_RADIUS);

		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if ((abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[0] - tSpaceIndex[0]) > iScale) || (abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[1] - tSpaceIndex[1]) > iScale) || (abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[2] - tSpaceIndex[2]) > iScale))
			{
				continue;
			}
			CopyMemory(&tLocation[0], &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], 12);
			if (((tLocation[0] - tPostLocation[0]) * (tLocation[0] - tPostLocation[0]) + (tLocation[1] - tPostLocation[1]) * (tLocation[1] - tPostLocation[1]) + (tLocation[2] - tPostLocation[2]) * (tLocation[2] - tPostLocation[2])) > (tPostDistance * tPostDistance))
			{
				continue;
			}
			if (type == 0) {
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal2[0], mTRANSFER.mOriginalSize2, bUDPSend);
			}
			else if (type == 1) {
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize, bUDPSend);
			}
			else if (type == 2) {
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal_C[0], mTRANSFER.mOriginalSize_C, bUDPSend);
			}
		}
		return;
	}
	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (mAVATAR_OBJECT[index01].mCheckValidState)
		{
			if (type == 0) {
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal2[0], mTRANSFER.mOriginalSize2, bUDPSend);
			}
			else if (type == 1) {
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize, bUDPSend);
			}
			else if (type == 2) {
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal_C[0], mTRANSFER.mOriginalSize_C, bUDPSend);
			}
		}
	}
}
//BROADCAST
void MyUtil::Broadcast(BOOL tCheckInRange, float tPostLocation[3], int iScale, int tUserIndexForNoSend, bool bUDPSend, int type)
{
	int index01;
	int tSpaceIndex[3];
	float tLocation[3];

	float tPostDistance = static_cast<float> (iScale) * mGAME.MAX_RADIUS;

	if (tCheckInRange)
	{
		tSpaceIndex[0] = (int)(tPostLocation[0] / mGAME.MAX_RADIUS);
		tSpaceIndex[1] = (int)(tPostLocation[1] / mGAME.MAX_RADIUS);
		tSpaceIndex[2] = (int)(tPostLocation[2] / mGAME.MAX_RADIUS);
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (index01 == tUserIndexForNoSend)
			{
				continue;
			}
			if ((abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[0] - tSpaceIndex[0]) > iScale) || (abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[1] - tSpaceIndex[1]) > iScale) || (abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[2] - tSpaceIndex[2]) > iScale))
			{
				continue;
			}
			CopyMemory(&tLocation[0], &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], 12);
			if (((tLocation[0] - tPostLocation[0]) * (tLocation[0] - tPostLocation[0]) + (tLocation[1] - tPostLocation[1]) * (tLocation[1] - tPostLocation[1]) + (tLocation[2] - tPostLocation[2]) * (tLocation[2] - tPostLocation[2])) > (tPostDistance * tPostDistance))
			{
				continue;
			}
			if (type) {
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize, bUDPSend);
			}
			else {
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal2[0], mTRANSFER.mOriginalSize2, bUDPSend);
			}
		}
		return;
	}
	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (mAVATAR_OBJECT[index01].mCheckValidState)
		{
			if (type) {
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize, bUDPSend);
			}
			else {
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal2[0], mTRANSFER.mOriginalSize2, bUDPSend);
			}
		}
	}
}
//RANDOM_NUMBER
float MyUtil::RandomNumber(float tMinValue, float tMaxValue)
{
	unsigned int tRandom = 0;
	tRandom = rand();
	return (tMinValue + (((tMaxValue - tMinValue) * (float)(tRandom % 10001)) / 10000.0f));
}
//RANDOM_NUMBER
int MyUtil::RandomNumber(void)
{
	unsigned int tRandom1 = 0;
	unsigned int tRandom2 = 0;
	tRandom1 = rand();
	tRandom2 = rand();
	return ((1 + (tRandom1 % 1000)) * (1 + (tRandom2 % 1000)));
}
//CHECK_IN_RANGE
BOOL MyUtil::CheckInRange(float tLocation01[3], float tLocation02[3], float tDistance)
{
	if (((tLocation01[0] - tLocation02[0]) * (tLocation01[0] - tLocation02[0]) + (tLocation01[1] - tLocation02[1]) * (tLocation01[1] - tLocation02[1]) + (tLocation01[2] - tLocation02[2]) * (tLocation01[2] - tLocation02[2])) > (tDistance * tDistance))
	{
		return FALSE;
	}
	return TRUE;
}
//GET_LENGTH_XYZ
float MyUtil::GetLengthXYZ(float tLocation01[3], float tLocation02[3])
{
	return sqrtf((tLocation01[0] - tLocation02[0]) * (tLocation01[0] - tLocation02[0]) + (tLocation01[1] - tLocation02[1]) * (tLocation01[1] - tLocation02[1]) + (tLocation01[2] - tLocation02[2]) * (tLocation01[2] - tLocation02[2]));
}
//GET_DOUBLE_XYZ
float MyUtil::GetDoubleXYZ(float tLocation01[3], float tLocation02[3])
{
	return ((tLocation01[0] - tLocation02[0]) * (tLocation01[0] - tLocation02[0]) + (tLocation01[1] - tLocation02[1]) * (tLocation01[1] - tLocation02[1]) + (tLocation01[2] - tLocation02[2]) * (tLocation01[2] - tLocation02[2]));
}
//GET_LENGTH_X_Z
float MyUtil::GetLengthX_Z(float tLocation01[3], float tLocation02[3])
{
	return sqrtf((tLocation01[0] - tLocation02[0]) * (tLocation01[0] - tLocation02[0]) + (tLocation01[2] - tLocation02[2]) * (tLocation01[2] - tLocation02[2]));
}
//GET_DOUBLE_X_Z
float MyUtil::GetDoubleX_Z(float tLocation01[3], float tLocation02[3])
{
	return ((tLocation01[0] - tLocation02[0]) * (tLocation01[0] - tLocation02[0]) + (tLocation01[2] - tLocation02[2]) * (tLocation01[2] - tLocation02[2]));
}
//GET_Y_ANGLE
float MyUtil::GetYAngle(float x1, float z1, float x2, float z2)
{
	if ((x1 == x2) && (z1 == z2))
	{
		return 0.0f;
	}

	float tVector[2];
	float tLength;
	float tAngle;
	float tDegreeAngle;

	tVector[0] = x2 - x1;
	tVector[1] = z2 - z1;
	tLength = sqrtf(tVector[0] * tVector[0] + tVector[1] * tVector[1]);
	if (tLength > 0.0f)
	{
		tVector[0] /= tLength;
		tVector[1] /= tLength;
	}
	tVector[1] -= 1.0f;
	tLength = sqrtf(tVector[0] * tVector[0] + tVector[1] * tVector[1]);
	if ((tLength / 2.0f) > 1.0f)
	{
		tAngle = 2.0f * asinf(1.0f);
	}
	else
	{
		tAngle = 2.0f * asinf(tLength / 2.0f);
	}
	if (x1 > x2)
	{
		tAngle = 2.0f * 3.14159265359f - tAngle;
	}
	tDegreeAngle = ((180.0f * tAngle) / 3.14159265359f) + 180.0f;
	if (tDegreeAngle >= 360.0f)
	{
		tDegreeAngle -= 360.0f;
	}
	return tDegreeAngle;
}
//RETURN_ITEM_RECOGNITION_NUMBER
int MyUtil::ReturnItemRecognitionNumber(int tItemType)
{
	time_t tCountSeconds;
	struct tm* tPresentTime;
	char tempString01[1000];
	char tempString02[1000];

	if ((tItemType != 0) && (tItemType != 3) && (tItemType != 4))
	{
		return 0;
	}
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return 0;
	}

	strcpy(tempString01, "");
	if (tPresentTime->tm_mday < 10)
	{
		tempString02[0] = '0';
		tempString02[1] = tPresentTime->tm_mday + '0';
		tempString02[2] = '\0';
	}
	else
	{
		itoa(tPresentTime->tm_mday, tempString02, 10);
	}
	strcat(tempString01, tempString02);
	if (tPresentTime->tm_hour < 10)
	{
		tempString02[0] = '0';
		tempString02[1] = tPresentTime->tm_hour + '0';
		tempString02[2] = '\0';
	}
	else
	{
		itoa(tPresentTime->tm_hour, tempString02, 10);
	}
	strcat(tempString01, tempString02);
	if (tPresentTime->tm_min < 10)
	{
		tempString02[0] = '0';
		tempString02[1] = tPresentTime->tm_min + '0';
		tempString02[2] = '\0';
	}
	else
	{
		itoa(tPresentTime->tm_min, tempString02, 10);
	}
	strcat(tempString01, tempString02);
	if (tPresentTime->tm_sec < 10)
	{
		tempString02[0] = '0';
		tempString02[1] = tPresentTime->tm_sec + '0';
		tempString02[2] = '\0';
	}
	else
	{
		itoa(tPresentTime->tm_sec, tempString02, 10);
	}
	strcat(tempString01, tempString02);
	return atoi(tempString01);
}
//RETURN_NOW_DATE
int MyUtil::ReturnNowDate(void)
{
	time_t tCountSeconds;
	struct tm* tPresentTime;
	char tempString01[1000];
	char tempString02[1000];

	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return 0;
	}
#ifdef __WIN32__
	strcpy(tempString01, "");
	itoa((tPresentTime->tm_year + 1900), tempString02, 10);
	strcat(tempString01, tempString02);
	if (tPresentTime->tm_mon < 9)
	{
		tempString02[0] = '0';
		tempString02[1] = tPresentTime->tm_mon + 1 + '0';
		tempString02[2] = '\0';
	}
	else
	{
		itoa((tPresentTime->tm_mon + 1), tempString02, 10);
	}
	strcat(tempString01, tempString02);
	if (tPresentTime->tm_mday < 10)
	{
		tempString02[0] = '0';
		tempString02[1] = tPresentTime->tm_mday + '0';
		tempString02[2] = '\0';
	}
	else
	{
		itoa(tPresentTime->tm_mday, tempString02, 10);
	}
	strcat(tempString01, tempString02);
#else
	_snprintf(tempString01, 1000, "%4.4d%2.2d%2.2d"
		, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1
		, tPresentTime->tm_mday);
#endif
	return atoi(tempString01);
}
//RETURN_ADD_DATE
int MyUtil::ReturnAddDate(int tPostDateValue, int tAddDayValue)
{
	if (tAddDayValue < 0)
	{
		return -1;
	}

	time_t tCountSeconds;
	struct tm* tPresentTime;
	char tempString01[1000];
	char tempString02[1000];
	int tPresentDateValue;

	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return -1;
	}

	_snprintf(tempString01, 1000, "%4.4d%2.2d%2.2d"
		, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1
		, tPresentTime->tm_mday);

	tPresentDateValue = atoi(tempString01);
	if (tPostDateValue > tPresentDateValue)
	{
		//tAddDayValue += ReturnSubDate( tPostDateValue, tCountSeconds );
		tAddDayValue += ReturnSubDate(tPostDateValue, tPresentDateValue);
	}
	time(&tCountSeconds);
	tCountSeconds += (tAddDayValue * 24 * 3600);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return -1;
	}

	_snprintf(tempString01, 1000, "%4.4d%2.2d%2.2d"
		, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1
		, tPresentTime->tm_mday);

	return atoi(tempString01);
}
//RETURN_SUB_DATE
int MyUtil::ReturnSubDate(int tPostDateValue, int tSubDayValue)
{
	if (tPostDateValue <= tSubDayValue)
	{
		return 0;
	}

#if 0
	struct tm time_str;
	time_t uPostDataValue;
	char tmpBuffer[8];
	char tempString01[1000];

	::snprintf(tempString01, 1000, "%s", tPostDateValue);
	memcpy(&tmpBuffer, &tempString01[0], 4);
	tmpBuffer[4] = '\0';
	time_str.tm_year = atoi(tmpBuffer) - 1900;
	memcpy(&tmpBuffer, &tempString01[4], 2);
	tmpBuffer[2] = '\0';
	time_str.tm_mon = atoi(tmpBuffer) - 1;
	tmpBuffer[2] = '\0';
	memcpy(&tmpBuffer, &tempString01[6], 2);
	time_str.tm_mday = atoi(tmpBuffer);
	time_str.tm_hour = 0;
	time_str.tm_min = 0;
	time_str.tm_sec = 0;

	if ((uPostDataValue = mktime(&time_str)) == -1) {
		return 0;
	}

	return ((uPostDataValue - tSubDayValue) / (24 * 3600)) + 1;
#endif
#if 1
	int index01;
	char tempString01[1000];
	char tempString02[1000];
	int tMonthDay[12];
	int tYear[2];
	int tMonth[2];
	int tDay[2];

	tMonthDay[0] = 31;
	tMonthDay[1] = 29;
	tMonthDay[2] = 31;
	tMonthDay[3] = 30;
	tMonthDay[4] = 31;
	tMonthDay[5] = 30;
	tMonthDay[6] = 31;
	tMonthDay[7] = 31;
	tMonthDay[8] = 30;
	tMonthDay[9] = 31;
	tMonthDay[10] = 30;
	tMonthDay[11] = 31;
#ifdef __WIN32__
	itoa(tPostDateValue, &tempString01[0], 10);
#else
	sprintf(&tempString01[0], "%d", tPostDateValue);
#endif
	CopyMemory(&tempString02[0], &tempString01[0], 4);
	tempString02[4] = '\0';
	tYear[0] = atoi(tempString02);
	if ((tYear[0] < 1) || (tYear[0] > 9000))
	{
		return 0;
	}
	CopyMemory(&tempString02[0], &tempString01[4], 2);
	tempString02[2] = '\0';
	tMonth[0] = atoi(tempString02);
	if ((tMonth[0] < 1) || (tMonth[0] > 12))
	{
		return 0;
	}
	CopyMemory(&tempString02[0], &tempString01[6], 2);
	tempString02[2] = '\0';
	tDay[0] = atoi(tempString02);
	if ((tDay[0] < 1) || (tDay[0] > 31))
	{
		return 0;
	}
	tDay[0] += (tYear[0] * 365);
	for (index01 = 0; index01 < (tMonth[0] - 1); index01++)
	{
		tDay[0] += tMonthDay[index01];
	}
#ifdef __WIN32__
	itoa(tSubDayValue, &tempString01[0], 10);
#else
	sprintf(&tempString01[0], "%d", tSubDayValue);
#endif
	CopyMemory(&tempString02[0], &tempString01[0], 4);
	tempString02[4] = '\0';
	tYear[1] = atoi(tempString02);
	if ((tYear[1] < 1) || (tYear[1] > 9000))
	{
		return 0;
	}
	CopyMemory(&tempString02[0], &tempString01[4], 2);
	tempString02[2] = '\0';
	tMonth[1] = atoi(tempString02);
	if ((tMonth[1] < 1) || (tMonth[1] > 12))
	{
		return 0;
	}
	CopyMemory(&tempString02[0], &tempString01[6], 2);
	tempString02[2] = '\0';
	tDay[1] = atoi(tempString02);
	if ((tDay[1] < 1) || (tDay[1] > 31))
	{
		return 0;
	}
	tDay[1] += (tYear[1] * 365);
	for (index01 = 0; index01 < (tMonth[1] - 1); index01++)
	{
		tDay[1] += tMonthDay[index01];
	}
	return (tDay[0] - tDay[1]);
#endif
}
//RETURN_VOTE_DATE
int MyUtil::ReturnVoteDate(void)
{
	time_t tCountSeconds;
	struct tm* tPresentTime;
	char tempString01[1000];
	char tempString02[1000];

	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return 0;
	}
#ifdef __WIN32__
	strcpy(tempString01, "");
	itoa((tPresentTime->tm_year + 1900), tempString02, 10);
	strcat(tempString01, tempString02);
	if (tPresentTime->tm_mon < 9)
	{
		tempString02[0] = '0';
		tempString02[1] = tPresentTime->tm_mon + 1 + '0';
		tempString02[2] = '\0';
	}
	else
	{
		itoa((tPresentTime->tm_mon + 1), tempString02, 10);
	}
	strcat(tempString01, tempString02);
	tempString02[0] = '0';
	tempString02[1] = '6';
	tempString02[2] = '\0';
	strcat(tempString01, tempString02);
#else
	_snprintf(tempString01, 1000, "%4.4d%2.2d06", tPresentTime->tm_year + 1900
		, tPresentTime->tm_mon + 1);
#endif
	return atoi(tempString01);
}
//RETURN_I_S_VALUE
int MyUtil::ReturnISValue(int tValue)
{
	char tempValue01[4];

	CopyMemory(&tempValue01[0], &tValue, 4);
	return ((int)tempValue01[0]);
}
//RETURN_I_U_VALUE
int MyUtil::ReturnIUValue(int tValue)
{
	char tempValue01[4];

	CopyMemory(&tempValue01[0], &tValue, 4);
	return ((int)tempValue01[1]);
}
//RETURN_I_B_VALUE
int MyUtil::ReturnIBValue(int tValue)
{
	char tempValue01[4];

	CopyMemory(&tempValue01[0], &tValue, 4);
	return ((int)tempValue01[2]);
}
//RETURN_I_B_VALUE
int MyUtil::ReturnICValue(int tValue)
{
	char tempValue01[4];

	CopyMemory(&tempValue01[0], &tValue, 4);
	return ((int)tempValue01[3]);
}
//CHANGE_I_S_VALUE
int MyUtil::ChangeISValue(int tValue, int tISValue)
{
	char tempValue01[4];
	int tResultIValue;

	CopyMemory(&tempValue01[0], &tValue, 4);
	tempValue01[0] += (char)tISValue;
	CopyMemory(&tResultIValue, &tempValue01[0], 4);
	return tResultIValue;
}
//CHANGE_I_U_VALUE
int MyUtil::ChangeIUValue(int tValue, int tIUValue)
{
	char tempValue01[4];
	int tResultIValue;

	CopyMemory(&tempValue01[0], &tValue, 4);
	tempValue01[1] += (char)tIUValue;
	CopyMemory(&tResultIValue, &tempValue01[0], 4);
	return tResultIValue;
}
//CHANGE_I_B_VALUE
int MyUtil::ChangeIBValue(int tValue, int tIUBalue)
{
	char tempValue01[4];
	int tResultIValue;

	CopyMemory(&tempValue01[0], &tValue, 4);
	tempValue01[2] += (char)tIUBalue;
	CopyMemory(&tResultIValue, &tempValue01[0], 4);
	return tResultIValue;
}

//CHANGE_I_B_VALUE
int MyUtil::ChangeEngraveValue(int tValue, int tEngraveValue)
{
	char tempValue01[4];
	int tResultIValue;

	CopyMemory(&tempValue01[0], &tValue, 4);
	tempValue01[3] += (char)tEngraveValue;
	CopyMemory(&tResultIValue, &tempValue01[0], 4);
	return tResultIValue;
}
//SET_I_S_I_U_VALUE
int MyUtil::SetISIUValue(int tISValue, int tIUValue)
{
	char tempValue01[4];
	int tResultIValue;

	tempValue01[0] = (char)tISValue;
	tempValue01[1] = (char)tIUValue;
	tempValue01[2] = 0;
	tempValue01[3] = 0;
	CopyMemory(&tResultIValue, &tempValue01[0], 4);
	return tResultIValue;
}
//RETURN_I_U_EFFECT_VALUE
int MyUtil::ReturnIUEffectValue(ITEM_INFO* tITEM_INFO, int tEffectSort)
{
	switch (tEffectSort)
	{
	case 1: //[���ݷ�]
		switch (tITEM_INFO->iSort)
		{
		case 13: //[����]
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
			if (tITEM_INFO->iLevel < 100)
			{
				return (int)(14.34f + (0.00f + (float)(tITEM_INFO->iLevel - 45) * 0.10f) * 0.72f);
			}
			if (tITEM_INFO->iLevel < 113)
			{
				return (int)(14.34f + (6.00f + (float)(tITEM_INFO->iLevel - 100) * 0.20f) * 0.72f);
			}
			if (tITEM_INFO->iLevel < 146)
			{
				return (int)(14.34f + (8.00f + (float)(tITEM_INFO->iLevel - 113) * 0.50f) * 0.72f);
			}
			break;
		}
		break;
	case 2: //[����]
		switch (tITEM_INFO->iSort)
		{
		case  8: //[����]
			if (tITEM_INFO->iLevel < 100)
			{
				return (int)(2.00f + (0.00f + (float)(tITEM_INFO->iLevel - 45) * 0.10f) * 0.10f);
			}
			if (tITEM_INFO->iLevel < 113)
			{
				return (int)(2.00f + (6.00f + (float)(tITEM_INFO->iLevel - 100) * 0.20f) * 0.10f);
			}
			if (tITEM_INFO->iLevel < 146)
			{
				return (int)(2.00f + (8.00f + (float)(tITEM_INFO->iLevel - 113) * 0.50f) * 0.10f);
			}
			break;
		case  9: //[����]
			if (tITEM_INFO->iLevel < 100)
			{
				return (int)(6.36f + (0.00f + (float)(tITEM_INFO->iLevel - 45) * 0.10f) * 0.32f);
			}
			if (tITEM_INFO->iLevel < 113)
			{
				return (int)(6.36f + (6.00f + (float)(tITEM_INFO->iLevel - 100) * 0.20f) * 0.32f);
			}
			if (tITEM_INFO->iLevel < 146)
			{
				return (int)(6.36f + (8.00f + (float)(tITEM_INFO->iLevel - 113) * 0.50f) * 0.32f);
			}
			break;
		case 10: //[�尩]
			if (tITEM_INFO->iLevel < 100)
			{
				return (int)(1.82f + (0.00f + (float)(tITEM_INFO->iLevel - 45) * 0.10f) * 0.09f);
			}
			if (tITEM_INFO->iLevel < 113)
			{
				return (int)(1.82f + (6.00f + (float)(tITEM_INFO->iLevel - 100) * 0.20f) * 0.09f);
			}
			if (tITEM_INFO->iLevel < 146)
			{
				return (int)(1.82f + (8.00f + (float)(tITEM_INFO->iLevel - 113) * 0.50f) * 0.09f);
			}
			break;
		case 12: //[�Ź�]
			if (tITEM_INFO->iLevel < 100)
			{
				return (int)(0.91f + (0.00f + (float)(tITEM_INFO->iLevel - 45) * 0.10f) * 0.05f);
			}
			if (tITEM_INFO->iLevel < 113)
			{
				return (int)(0.91f + (6.00f + (float)(tITEM_INFO->iLevel - 100) * 0.20f) * 0.05f);
			}
			if (tITEM_INFO->iLevel < 146)
			{
				return (int)(0.91f + (8.00f + (float)(tITEM_INFO->iLevel - 113) * 0.50f) * 0.05f);
			}
			break;
		}
		break;
	case 3: //[���ݼ���]
		switch (tITEM_INFO->iSort)
		{
		case 10: //[�尩]
			if (tITEM_INFO->iLevel < 100)
			{
				return (int)(13.36f + (0.00f + (float)(tITEM_INFO->iLevel - 45) * 0.10f) * 0.67f);
			}
			if (tITEM_INFO->iLevel < 113)
			{
				return (int)(13.36f + (6.00f + (float)(tITEM_INFO->iLevel - 100) * 0.20f) * 0.67f);
			}
			if (tITEM_INFO->iLevel < 146)
			{
				return (int)(13.36f + (8.00f + (float)(tITEM_INFO->iLevel - 113) * 0.50f) * 0.67f);
			}
			break;
		case 13: //[����]
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
			if (tITEM_INFO->iLevel < 100)
			{
				return (int)(5.73f + (0.00f + (float)(tITEM_INFO->iLevel - 45) * 0.10f) * 0.29f);
			}
			if (tITEM_INFO->iLevel < 113)
			{
				return (int)(5.73f + (6.00f + (float)(tITEM_INFO->iLevel - 100) * 0.20f) * 0.29f);
			}
			if (tITEM_INFO->iLevel < 146)
			{
				return (int)(5.73f + (8.00f + (float)(tITEM_INFO->iLevel - 113) * 0.50f) * 0.29f);
			}
			break;
		}
		break;
	case 4: //[����ȸ��]
		switch (tITEM_INFO->iSort)
		{
		case  9: //[����]
			if (tITEM_INFO->iLevel < 100)
			{
				return (int)(0.95f + (0.00f + (float)(tITEM_INFO->iLevel - 45) * 0.10f) * 0.05f);
			}
			if (tITEM_INFO->iLevel < 113)
			{
				return (int)(0.95f + (6.00f + (float)(tITEM_INFO->iLevel - 100) * 0.20f) * 0.05f);
			}
			if (tITEM_INFO->iLevel < 146)
			{
				return (int)(0.95f + (8.00f + (float)(tITEM_INFO->iLevel - 113) * 0.50f) * 0.05f);
			}
			break;
		case 12: //[�Ź�]
			if (tITEM_INFO->iLevel < 100)
			{
				return (int)(2.23f + (0.00f + (float)(tITEM_INFO->iLevel - 45) * 0.10f) * 0.11f);
			}
			if (tITEM_INFO->iLevel < 113)
			{
				return (int)(2.23f + (6.00f + (float)(tITEM_INFO->iLevel - 100) * 0.20f) * 0.11f);
			}
			if (tITEM_INFO->iLevel < 146)
			{
				return (int)(2.23f + (8.00f + (float)(tITEM_INFO->iLevel - 113) * 0.50f) * 0.11f);
			}
			break;
		}
		break;
	case 5: //[�Ӽ�����]
		switch (tITEM_INFO->iSort)
		{
		case 11: //[����]
			if (tITEM_INFO->iLevel < 100)
			{
				return (int)(2.00f + (0.00f + (float)(tITEM_INFO->iLevel - 45) * 0.10f) * 0.26f);
			}
			if (tITEM_INFO->iLevel < 113)
			{
				return (int)(2.00f + (6.00f + (float)(tITEM_INFO->iLevel - 100) * 0.20f) * 0.26f);
			}
			if (tITEM_INFO->iLevel < 146)
			{
				return (int)(2.00f + (8.00f + (float)(tITEM_INFO->iLevel - 113) * 0.50f) * 0.26f);
			}
			break;
		}
		break;
	case 6: //[�Ӽ����]
		switch (tITEM_INFO->iSort)
		{
		case  7: //[�����]
			if (tITEM_INFO->iLevel < 100)
			{
				return (int)(1.00f + (0.00f + (float)(tITEM_INFO->iLevel - 45) * 0.10f) * 0.13f);
			}
			if (tITEM_INFO->iLevel < 113)
			{
				return (int)(1.00f + (6.00f + (float)(tITEM_INFO->iLevel - 100) * 0.20f) * 0.13f);
			}
			if (tITEM_INFO->iLevel < 146)
			{
				return (int)(1.00f + (8.00f + (float)(tITEM_INFO->iLevel - 113) * 0.50f) * 0.13f);
			}
			break;
		}
		break;
	}
	return 0;
}
//RETURN_IS_VALUE_WITH_LEVEL_LIMIT
int MyUtil::ReturnISValueWithLevelLimit(int tLevel, int tISValue)
{
#ifdef __GOD__
	if ((!mGAME.mCheckZone049TypeServer) && (!mGAME.mCheckZone051TypeServer) && (!mGAME.mCheckZone053TypeServer) && (!mGAME.mCheckZone267TypeServer))
#else
	if ((!mGAME.mCheckZone049TypeServer) && (!mGAME.mCheckZone051TypeServer) && (!mGAME.mCheckZone053TypeServer))
#endif
	{
		if (tISValue < 50)//if (tISValue < 40)
		{
			return tISValue;
		}
		else
		{
			return 50;
		}
	}
	if (tLevel <= 15)
	{
		if (tISValue < 4)
		{
			return tISValue;
		}
		else
		{
			return 4;
		}
	}
	else if (tLevel <= 45)
	{
		if (tISValue < 8)
		{
			return tISValue;
		}
		else
		{
			return 8;
		}
	}
	else if (tLevel <= 55)
	{
		if (tISValue < 12)
		{
			return tISValue;
		}
		else
		{
			return 12;
		}
	}
	else if (tLevel <= 65)
	{
		if (tISValue < 16)
		{
			return tISValue;
		}
		else
		{
			return 16;
		}
	}
	else if (tLevel <= 75)
	{
		if (tISValue < 20)
		{
			return tISValue;
		}
		else
		{
			return 20;
		}
	}
	else if (tLevel <= 85)
	{
		if (tISValue < 24)
		{
			return tISValue;
		}
		else
		{
			return 24;
		}
	}
	else if (tLevel <= 95)
	{
		if (tISValue < 28)
		{
			return tISValue;
		}
		else
		{
			return 28;
		}
	}
	else if (tLevel <= 105)
	{
		if (tISValue < 32)
		{
			return tISValue;
		}
		else
		{
			return 32;
		}
	}
	else if (tLevel <= 112)
	{
		if (tISValue < 36)
		{
			return tISValue;
		}
		else
		{
			return 36;
		}
	}
	else
	{
		if (tISValue < 50)//if (tISValue < 40)
		{
			return tISValue;
		}
		else
		{
			return 50;
		}
	}
	return 0;
}
//RETURN_IU_VALUE_WITH_LEVEL_LIMIT
int MyUtil::ReturnIUValueWithLevelLimit(int tLevel, int tIUValue)
{
#ifdef __GOD__
	if ((!mGAME.mCheckZone049TypeServer) && (!mGAME.mCheckZone051TypeServer) && (!mGAME.mCheckZone053TypeServer) && (!mGAME.mCheckZone267TypeServer))
#else
	if ((!mGAME.mCheckZone049TypeServer) && (!mGAME.mCheckZone051TypeServer) && (!mGAME.mCheckZone053TypeServer))
#endif
	{
		if (tIUValue < 12)
		{
			return tIUValue;
		}
		else
		{
			return 12;
		}
	}
	if (tLevel <= 15)
	{
		if (tIUValue < 1)
		{
			return tIUValue;
		}
		else
		{
			return 1;
		}
	}
	else if (tLevel <= 25)
	{
		if (tIUValue < 2)
		{
			return tIUValue;
		}
		else
		{
			return 2;
		}
	}
	else if (tLevel <= 35)
	{
		if (tIUValue < 3)
		{
			return tIUValue;
		}
		else
		{
			return 3;
		}
	}
	else if (tLevel <= 45)
	{
		if (tIUValue < 4)
		{
			return tIUValue;
		}
		else
		{
			return 4;
		}
	}
	else if (tLevel <= 55)
	{
		if (tIUValue < 5)
		{
			return tIUValue;
		}
		else
		{
			return 5;
		}
	}
	else if (tLevel <= 65)
	{
		if (tIUValue < 6)
		{
			return tIUValue;
		}
		else
		{
			return 6;
		}
	}
	else if (tLevel <= 75)
	{
		if (tIUValue < 7)
		{
			return tIUValue;
		}
		else
		{
			return 7;
		}
	}
	else if (tLevel <= 85)
	{
		if (tIUValue < 8)
		{
			return tIUValue;
		}
		else
		{
			return 8;
		}
	}
	else if (tLevel <= 95)
	{
		if (tIUValue < 9)
		{
			return tIUValue;
		}
		else
		{
			return 9;
		}
	}
	else if (tLevel <= 105)
	{
		if (tIUValue < 10)
		{
			return tIUValue;
		}
		else
		{
			return 10;
		}
	}
	else if (tLevel <= 112)
	{
		if (tIUValue < 11)
		{
			return tIUValue;
		}
		else
		{
			return 11;
		}
	}
	else
	{
		if (tIUValue < 12)
		{
			return tIUValue;
		}
		else
		{
			return 12;
		}
	}
	return 0;
}

#ifdef __GOD__
//RETURN_UPGRADE_VALUE_WITH_LEVEL_LIMIT
int MyUtil::ReturnUpgradeValueWithLevelLimit(int tLevel, int tUpgradeValue)
{
	if ((!mGAME.mCheckZone049TypeServer) && (!mGAME.mCheckZone051TypeServer) && (!mGAME.mCheckZone053TypeServer) && (!mGAME.mCheckZone267TypeServer))
	{
		if (tUpgradeValue < 96)
		{
			return tUpgradeValue;
		}
		else
		{
			return 96;
		}
	}
	if (tLevel <= 19)
	{
		if (tUpgradeValue < 4)
		{
			return tUpgradeValue;
		}
		else
		{
			return 4;
		}
	}
	else if (tLevel <= 29)
	{
		if (tUpgradeValue < 8)
		{
			return tUpgradeValue;
		}
		else
		{
			return 8;
		}
	}
	else if (tLevel <= 39)
	{
		if (tUpgradeValue < 13)
		{
			return tUpgradeValue;
		}
		else
		{
			return 13;
		}
	}
	else if (tLevel <= 45)
	{
		if (tUpgradeValue < 17)
		{
			return tUpgradeValue;
		}
		else
		{
			return 17;
		}
	}
	else if (tLevel <= 55)
	{
		if (tUpgradeValue < 21)
		{
			return tUpgradeValue;
		}
		else
		{
			return 21;
		}
	}
	else if (tLevel <= 65)
	{
		if (tUpgradeValue < 25)
		{
			return tUpgradeValue;
		}
		else
		{
			return 25;
		}
	}
	else if (tLevel <= 75)
	{
		if (tUpgradeValue < 29)
		{
			return tUpgradeValue;
		}
		else
		{
			return 29;
		}
	}
	else if (tLevel <= 85)
	{
		if (tUpgradeValue < 33)
		{
			return tUpgradeValue;
		}
		else
		{
			return 33;
		}
	}
	else if (tLevel <= 95)
	{
		if (tUpgradeValue < 38)
		{
			return tUpgradeValue;
		}
		else
		{
			return 38;
		}
	}
	else if (tLevel <= 105)
	{
		if (tUpgradeValue < 42)
		{
			return tUpgradeValue;
		}
		else
		{
			return 42;
		}
	}
	else if (tLevel <= 112)
	{
		if (tUpgradeValue < 46)
		{
			return tUpgradeValue;
		}
		else
		{
			return 46;
		}
	}
	else if (tLevel <= 115)
	{
		if (tUpgradeValue < 50)
		{
			return tUpgradeValue;
		}
		else
		{
			return 50;
		}
	}
	else if (tLevel <= 118)
	{
		if (tUpgradeValue < 54)
		{
			return tUpgradeValue;
		}
		else
		{
			return 54;
		}
	}
	else if (tLevel <= 121)
	{
		if (tUpgradeValue < 58)
		{
			return tUpgradeValue;
		}
		else
		{
			return 58;
		}
	}
	else if (tLevel <= 124)
	{
		if (tUpgradeValue < 63)
		{
			return tUpgradeValue;
		}
		else
		{
			return 63;
		}
	}
	else if (tLevel <= 127)
	{
		if (tUpgradeValue < 67)
		{
			return tUpgradeValue;
		}
		else
		{
			return 67;
		}
	}
	else if (tLevel <= 130)
	{
		if (tUpgradeValue < 71)
		{
			return tUpgradeValue;
		}
		else
		{
			return 71;
		}
	}
	else if (tLevel <= 133)
	{
		if (tUpgradeValue < 75)
		{
			return tUpgradeValue;
		}
		else
		{
			return 75;
		}
	}
	else if (tLevel <= 136)
	{
		if (tUpgradeValue < 79)
		{
			return tUpgradeValue;
		}
		else
		{
			return 79;
		}
	}
	else if (tLevel <= 139)
	{
		if (tUpgradeValue < 83)
		{
			return tUpgradeValue;
		}
		else
		{
			return 83;
		}
	}
	else if (tLevel <= 142)
	{
		if (tUpgradeValue < 88)
		{
			return tUpgradeValue;
		}
		else
		{
			return 88;
		}
	}
	else if (tLevel <= 145)
	{
		if (tUpgradeValue < 92)
		{
			return tUpgradeValue;
		}
		else
		{
			return 92;
		}
	}
	else
	{
		if (tUpgradeValue < 96)
		{
			return tUpgradeValue;
		}
		else
		{
			return 96;
		}
	}
	return 0;
}
#endif



//PROCESS_ITEM_FOR_KILL_OTHER_TRIBE
void MyUtil::ProcessForKillOtherTribe(int tUserIndex, int tOtherIndex, int tZoneNumber)
{

	if ((!mUSER[tUserIndex].mCheckValidState) || (!mUSER[tOtherIndex].mCheckValidState))
	{
		return;
	}
	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	int BinekExp = mGAME.mBinekExpAddValue;
	int tGainGeneralExperience;
	int index01;
	time_t tCountSeconds;
	struct tm* tPresentTime;
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	int tRandomValue;


	if (((mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2) - (mUSER[tOtherIndex].mAvatarInfo.aLevel1 + mUSER[tOtherIndex].mAvatarInfo.aLevel2)) > 9)
	{
		return;
	}

	if (mGAME.mCheckZone049TypeServer)
	{
		mGAME.mZone049TypeBattleResult[mUSER[tUserIndex].mAvatarInfo.aTribe]++;
	}

	if (mGAME.mCheckZone194Server)
	{
		mGAME.mZone194BattleResult[mUSER[tUserIndex].mAvatarInfo.aTribe]++;
	}

	if (mGAME.mCheckZone267TypeServer)
	{
		mGAME.mZone267TypeBattleResult[mUSER[tUserIndex].mAvatarInfo.aTribe]++;
	}

	mPLAYUSER_COM.U_CHECK_KILL_OTHER_TRIBE_SEND(&mUSER[tUserIndex].mAvatarInfo.aName[0], &mUSER[tOtherIndex].mAvatarInfo.aName[0]);

	if (mPLAYUSER_COM.mRecv_Result != 0)
	{
		return;
	}

	if (mUSER[tUserIndex].mAvatarInfo.PlayerKill < 10)
	{
		mUSER[tUserIndex].mAvatarInfo.PlayerKill++;
	}

	DropItemForKillOtherTribe(tUserIndex, tOtherIndex, tZoneNumber);
	mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += mGAME.mKillOtherTribeAddValue;
	mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += mGAME.mKillOtherTribeAddValue;
	mUSER[tUserIndex].mAvatarInfo.RankPoint += 1;//per kill 1 rank point
	mUSER[tUserIndex].mAvatarInfo.OnlineHour += 2; // Capsul / kill
	// Message for Kill
	//mUSER[tUserIndex].mAvatarInfo.BloodStained += 1; // + Blood Point
	//mTRANSFER.B_AVATAR_CHANGE_INFO_2(121, mUSER[tUserIndex].mAvatarInfo.BloodStained);
	//mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	switch (tZoneNumber) {
	case 38:
	case 49:
	case 51:
	case 53:
	case 196:
	case 199:
		mUSER[tUserIndex].mAvatarInfo.BloodStained += 2; // + Blood Point
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(121, mUSER[tUserIndex].mAvatarInfo.BloodStained);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	default:
		mUSER[tUserIndex].mAvatarInfo.BloodStained += 1; // + Blood Point
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(121, mUSER[tUserIndex].mAvatarInfo.BloodStained);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		break;
	}




	//nova - winner gets extra cp
	if (mGAME.mWorldInfo.mZone038WinTribe == mUSER[tUserIndex].mAvatarInfo.aTribe)
	{
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 10;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 10;
	}

	if (mGAME.mWorldInfo.mMonsterSymbol == mUSER[tUserIndex].mAvatarInfo.aTribe)
	{
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 10;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 10;
	}

	if (mGAME.mWorldInfo.mTribe1Symbol == mUSER[tUserIndex].mAvatarInfo.aTribe)
	{
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 10;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 10;
	}

	if (mGAME.mWorldInfo.mTribe2Symbol == mUSER[tUserIndex].mAvatarInfo.aTribe)
	{
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 10;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 10;
	}

	if (mGAME.mWorldInfo.mTribe3Symbol == mUSER[tUserIndex].mAvatarInfo.aTribe)
	{
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 10;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 10;
	}

	if (mGAME.mWorldInfo.mTribe4Symbol == mUSER[tUserIndex].mAvatarInfo.aTribe)
	{
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 10;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 10;
	}

	//nova - Rank Info during HSB
	if (mGAME.mWorldInfo.mTribeSymbolBattle == 1)
	{
		mUSER[tUserIndex].mAvatarInfo.aRankPoint += 20;
		mAVATAR_OBJECT[tUserIndex].mDATA.aRankPoint += 20;

		if (mUSER[tUserIndex].mAvatarInfo.ScrollofLoyality > 0)
		{
			mUSER[tUserIndex].mAvatarInfo.aRankPoint += 20;
			mAVATAR_OBJECT[tUserIndex].mDATA.aRankPoint += 20;
		}
		/*if (mUSER[tUserIndex].mAvatarInfo.WarriorScroll > 0)
		{
			mUSER[tUserIndex].mAvatarInfo.aRankPoint += 20;
			mAVATAR_OBJECT[tUserIndex].mDATA.aRankPoint += 20;
		}*/

		if (mUSER[tUserIndex].mAvatarInfo.aRankPoint > 3000)
		{
			mUSER[tUserIndex].mAvatarInfo.aRankPoint = 3000;
			mAVATAR_OBJECT[tUserIndex].mDATA.aRankPoint = 3000;
		}

		mTRANSFER.B_AVATAR_CHANGE_INFO_2(66, mUSER[tUserIndex].mAvatarInfo.aRankPoint);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}

	if (mUSER[tUserIndex].mAvatarInfo.ScrollofLoyality > 0)
	{
		mUSER[tUserIndex].mAvatarInfo.ScrollofLoyality--;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(4, mUSER[tUserIndex].mAvatarInfo.ScrollofLoyality);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += mGAME.mKillOtherTribeAddValue;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += mGAME.mKillOtherTribeAddValue;
	}



	tGainGeneralExperience = mLEVEL.ReturnGainExpForKillOtherTribe(mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2, mUSER[tOtherIndex].mAvatarInfo.aLevel1 + mUSER[tOtherIndex].mAvatarInfo.aLevel2);

	/* Mir modified 09.02.27 */
	switch (tZoneNumber) {
	case 38:
	case 196:
	case 199:
		tGainGeneralExperience *= 10;
	case 49:
	case 51:
	case 53:
	case 146:
	case 147:
	case 149:
	case 150:
	case 151:
	case 153:
		tGainGeneralExperience *= 3;
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
		tGainGeneralExperience *= 5;
		break;
	default:
		tGainGeneralExperience *= mGAME.mKillOtherTribeExperienceUpRatio;
		break;
	}
	/* Mir modified 09.02.27 */

	if (mUSER[tUserIndex].mAvatarInfo.ScrollofBattle > 0)
	{
		mUSER[tUserIndex].mAvatarInfo.ScrollofBattle--;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(5, mUSER[tUserIndex].mAvatarInfo.ScrollofBattle);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		/* Mir modified 09.02.27 */
		tGainGeneralExperience *= 5;
		/* Mir modified 09.02.27 */
		mUSER[tUserIndex].mAvatarInfo.BloodStained += 1; // + Blood Point
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(121, mUSER[tUserIndex].mAvatarInfo.BloodStained);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}
	// Warrior Scroll
	/*if (mUSER[tUserIndex].mAvatarInfo.WarriorScroll > 0)
	{
		tGainGeneralExperience *= 2;
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += mGAME.mKillOtherTribeAddValue;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += mGAME.mKillOtherTribeAddValue;
	}*/
	if (mUSER[tUserIndex].mAvatarInfo.TimeEffect == 300)
	{
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 1;
	}

	//nova - per kill mount exp. 
	if (mUSER[tUserIndex].mAvatarInfo.aAnimalIndex > 9)
	{

		if (mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] / 1000000 > 0)
		{
			if ((mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] % 1000000) != 100000)
			{
				int incomingAmount = 500;
				mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] += incomingAmount;
				if (mUSER[tUserIndex].mAvatarInfo.DoubleMouthExp2x > 0)
				{
					mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] += incomingAmount * 2;

				}
				if (mUSER[tUserIndex].mAvatarInfo.TimeEffect == 360)
				{
					mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] += incomingAmount * 2;

				}

				if ((mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] % 1000000) > 100000)
				{
					mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] = 100000;
				}
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(71, mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10]);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
		}
	}
	mTRANSFER.B_AVATAR_CHANGE_INFO_2(3, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	//nova - murdered one gets cp
	if (mGAME.mCheckZone049TypeServer)//for outpost
	{
		mUSER[tOtherIndex].mAvatarInfo.aKillOtherTribe += 2;
		mAVATAR_OBJECT[tOtherIndex].mDATA.aKillOtherTribe += 2;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(3, mUSER[tOtherIndex].mAvatarInfo.aKillOtherTribe);
		mUSER[tOtherIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}

	if (mGAME.mCheckZone267TypeServer)//for ruins
	{
		mUSER[tOtherIndex].mAvatarInfo.aKillOtherTribe += 2;
		mAVATAR_OBJECT[tOtherIndex].mDATA.aKillOtherTribe += 2;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(3, mUSER[tOtherIndex].mAvatarInfo.aKillOtherTribe);
		mUSER[tOtherIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}

	if (mUSER[tOtherIndex].mAvatarInfo.Fury >= 0 && mUSER[tOtherIndex].mAvatarInfo.Fury < 10)
	{
		mUSER[tOtherIndex].mAvatarInfo.Fury += 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(80, mUSER[tOtherIndex].mAvatarInfo.Fury);
		mUSER[tOtherIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	ProcessForExperience(tUserIndex, tGainGeneralExperience, 0, 0);
}
//DROP_ITEM_FOR_KILL_OTHER_TRIBE
void MyUtil::DropItemForKillOtherTribe(int tUserIndex, int tOtherIndex, int tZoneNumber)
{


	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];
	ITEM_INFO* tITEM_INFO;
	int tItemLLevel;
	int tItemHLevel;
	int tTribeItemList[9];
	int tRandomValue;
	int tItemType;
	int tItemSort;
	int tSearchNum;
	unsigned int tRandom = 0;
	int itemindex = 0;


	tRandom = rand() % 10;
	if (tRandom < 5) {
		tRandom = rand() % 1000;
		if (tRandom < 50) {
			tRandom = rand() % 6;
			switch (tRandom) {
			case 0:
				itemindex = 522; // P
				break;
			case 1:
				itemindex = 523; // L
				break;
			case 2:
				itemindex = 524; // A
				break;
			case 3:
				itemindex = 525; // Y
				break;
			case 4:
				itemindex = 614; // Sock
				break;
			case 5: 
				itemindex = 615; // Lamp
				break;
			case 6:
				itemindex = 616; // Star	
				break;
			case 7:
				itemindex = 617; // Snowflake
				break;
			}
		}
		else
		{
			tRandom = rand() % 8;
			switch (tRandom) {
			case 0:
				itemindex = 1216; // Auto Buff Scroll(1d)
				break;
			case 1:
				itemindex = 1145; // SkyLord's Blessed Feed
				break;
			case 2:
				itemindex = 695;  // White Feather
				break;
			case 3:
				itemindex = 696;  // Black Feather
				break;
			case 4:
				itemindex = 1118; // Scroll of Loyality
				break;
			case 5:
				itemindex = 1370; // Silver Plate Scroll
				break;
			case 6:
				itemindex = 1132; // Buff Duration Pill
				break;
			case 7:
				tRandom = rand() % 8;
				switch (tRandom) {
				case 0:
					itemindex = 1301; // White Tiger (5%)
					break;
				case 1:
					itemindex = 1302; // Stalking Boar (5%)
					break;
				case 2:
					itemindex = 1303; // Heaven's Stag (5%)
					break;
				case 3:
					itemindex = 1313; // Feral Bear (5%)
					break;
				case 4:
					itemindex = 1317; // Ferocious Ferret (5%)
					break;
				case 5:
					itemindex = 1320; // Angry Bull (5%)
					break;
				case 6:
					itemindex = 1323; // Snow Wolf (5%)
					break;
				case 7:
					itemindex = 1326; // Gilden HaeChi (5%)
					break;
				}
			}


		}
		string test = "";
		tRandomValue = rand() % 5;
		switch (tRandomValue) {
		case 0:
			test = "dominated  ";
			break;
		case 1:
			test = "just killed ";
			break;
		case 2:
			test = "destroyed ";
			break;
		case 3:
			test = "free cp farm from ";
			break;
		case 4:
			test = "burried ";
			break;

		}
		

		if (itemindex > 0)
		{
			tITEM_INFO = mITEM.Search(itemindex);

			if (tITEM_INFO == NULL)
			{
				return;
			}
			sprintf((char*)&tData[0], "[%s] %s [%s]-[%s] ", &mUSER[tUserIndex].mAvatarInfo.aName[0], test.c_str(), &mUSER[tOtherIndex].mAvatarInfo.aName[0],tITEM_INFO->iName);
			mRELAY_COM.U_DEMAND_BROADCAST_DATA(102, &tData[0]);
			if (!ProcessForDropItem(2, tITEM_INFO->iIndex, 0, 0, ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[tOtherIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], 0, mUSER[tUserIndex].DropItemSocketGmAndBos))
			{
				return;
			}

			mGAMELOG.GL_GAIN_KILLOTHERTRIBE_ITEM(tUserIndex, tOtherIndex, tITEM_INFO->iIndex, tITEM_INFO->iName);
			return;
		}

	}
	if (tZoneNumber == 268 || tZoneNumber == 267) {
		if (tRandom < 5) {
			tRandom = rand() % 1000;
			if (tRandom < 50) {
				tRandom = rand() % 6;
				switch (tRandom) {
				case 0:
					itemindex = 522; // P
					break;
				case 1:
					itemindex = 523; // L
					break;
				case 2:
					itemindex = 524; // A
					break;
				case 3:
					itemindex = 525; // Y
					break;
				case 4:
					itemindex = 617; // Snowflake
					break;
				case 5:
					itemindex = 616; // Star
					break;
				}
			}
			else
			{
				tRandom = rand() % 8;
				switch (tRandom) {
				case 0:
					itemindex = 1216; // Auto Buff Scroll(1d)
					break;
				case 1:
					itemindex = 1145; // SkyLord's Blessed Feed
					break;
				case 2:
					itemindex = 695;  // White Feather
					break;
				case 3:
					itemindex = 696;  // Black Feather
					break;
				case 4:
					itemindex = 1118; // Scroll of Loyality
					break;
				case 5:
					itemindex = 1370; // Gold Plate Scroll
					break;
				case 6:
					itemindex = 1132; // Buff Duration Pill
					break;
				case 7:
					tRandom = rand() % 8;
					switch (tRandom) {
					case 0:
						itemindex = 1301; // White Tiger (5%)
						break;
					case 1:
						itemindex = 1302; // Stalking Boar (5%)
						break;
					case 2:
						itemindex = 1303; // Heaven's Stag (5%)
						break;
					case 3:
						itemindex = 1313; // Feral Bear (5%)
						break;
					case 4:
						itemindex = 1317; // Ferocious Ferret (5%)
						break;
					case 5:
						itemindex = 1320; // Angry Bull (5%)
						break;
					case 6:
						itemindex = 1323; // Snow Wolf (5%)
						break;
					case 7:
						itemindex = 1326; // Gilden HaeChi (5%)
						break;
					}
				}
			}
		}
	}

	/*if (tZoneNumber == 153) {
		tRandom = rand() % 1000;
		if (tRandom <= 30) {
			itemindex = 635;
		}
		else if (tRandom <= 160) {
			itemindex = 813;
		}

		if (itemindex > 0)
		{
			tITEM_INFO = mITEM.Search(itemindex);

			if (tITEM_INFO == NULL)
			{
				return;
			}

			if (!ProcessForDropItem(2, tITEM_INFO->iIndex, 0, 0, ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[tOtherIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], 0, mUSER[tUserIndex].DropItemSocketGmAndBos))
			{
				return;
			}

			mGAMELOG.GL_GAIN_KILLOTHERTRIBE_ITEM(tUserIndex, tOtherIndex, tITEM_INFO->iIndex, tITEM_INFO->iName);
			return;
		}
	}*/




	//nova - outpost r12 killothertribe drop
	/*if (tZoneNumber == 296) {
		tRandom = rand() % 1000;
		if (tRandom <= 30) {
			itemindex = 635;
		}
		else if (tRandom <= 160) {
			itemindex = 813;
		}

		if (itemindex > 0)
		{
			tITEM_INFO = mITEM.Search(itemindex);

			if (tITEM_INFO == NULL)
			{
				return;
			}

			if (!(2, tITEM_INFO->iIndex, 0, 0, ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[tOtherIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], 0, mUSER[tUserIndex].DropItemSocketGmAndBos))
			{
				return;
			}

			mGAMELOG.GL_GAIN_KILLOTHERTRIBE_ITEM(tUserIndex, tOtherIndex, tITEM_INFO->iIndex, tITEM_INFO->iName);
			return;
		}
	}*/

	//nova - ghost valley r12 killothertribe drop
	/*if (tZoneNumber == 38) {
		tRandom = rand() % 1000;
		if (tRandom <= 30) {
			itemindex = 601;
		}
		else if (tRandom <= 70) {
			itemindex = 1301;
		}
		else if (tRandom <= 110) {
			itemindex = 1313;
		}

		if (itemindex > 0) {
			tITEM_INFO = mITEM.Search(itemindex);

			if (tITEM_INFO == NULL) {
				return;
			}

			if (!ProcessForDropItem(2, tITEM_INFO->iIndex, 0, 0, ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[tOtherIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], 0, mUSER[tUserIndex].DropItemSocketGmAndBos)) {
				return;
			}

			mGAMELOG.GL_GAIN_KILLOTHERTRIBE_ITEM(tUserIndex, tOtherIndex, tITEM_INFO->iIndex, tITEM_INFO->iName);
			return;
		}
	}*/

	//nova - HSB killothertribe drop
	/*if (mGAME.mWorldInfo.mTribeSymbolBattle == 1)
	{
		tRandom = rand() % 1000;

		if (tRandom <= 100)
		{
			itemindex = 10;
		}

		if (itemindex > 0)
		{
			tITEM_INFO = mITEM.Search(itemindex);

			if (tITEM_INFO == NULL)
			{
				return;
			}

			if (!ProcessForDropItem(2, tITEM_INFO->iIndex, 0, 0, ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[tOtherIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], 0, mUSER[tUserIndex].DropItemSocketGmAndBos))
			{
				return;
			}

			mGAMELOG.GL_GAIN_KILLOTHERTRIBE_ITEM(tUserIndex, tOtherIndex, tITEM_INFO->iIndex, tITEM_INFO->iName);
			return;
		}
	}*/
}
//////mGAMELOG
int MyUtil::SearchAvatar(char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tInvalidIndex)
{
	int index01;
	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (!mAVATAR_OBJECT[index01].mCheckValidState)
		{
			continue;
		}
		if (index01 == tInvalidIndex)
		{
			continue;
		}
		if (strcmp(mAVATAR_OBJECT[index01].mDATA.aName, tAvatarName) == 0)
		{
			break;
		}
	}
	if (index01 < mSERVER.mMAX_USER_NUM)
	{
		return index01;
	}
	return -1;
}
//////mGAMELOG
int MyUtil::SearchValetShop(int tSort, char tAvatarName[MAX_AVATAR_NAME_LENGTH])
{
	int index01;
	switch (tSort)
	{
	case 1://Bo pazar yeri arama
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mSHOP_OBJECT[index01].mCheckValidState)
			{
				break;
			}
		}
		if (index01 < mSERVER.mMAX_USER_NUM)
		{
			return index01;
		}
		return -2;
	case 2://Olan Pazarı arama
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mSHOP_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (strcmp(mSHOP_OBJECT[index01].mDATA.aName, tAvatarName) == 0)
			{
				break;
			}
		}
		if (index01 < mSERVER.mMAX_USER_NUM)
		{
			return index01;
		}
		return -1;
	default:
		break;
	}
}
// # Defense Hack # {
bool MyUtil::CheckInvenForItem(int* tUserIndex, ITEM_INFO* pItem, int* tPage, int* tIndex, int* tXPost, int* tYPost)
{
	int iCount = 0;
	int iOccupyRange = 1;
	ITEM_INFO* tItemInfo = NULL;

	if (pItem->iSort != 2 && pItem->iSort != 7 && pItem->iSort != 11) {
		iOccupyRange = 2;
	}

	for (iCount = 0; iCount < MAX_INVENTORY_SLOT_NUM; iCount++) {
		if ((mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][1] == (*tXPost - 1)
			&& (mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][2] == (*tYPost - 1)))) {
			if (mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][0] < 1)
				continue;
			tItemInfo = mITEM.Search(mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][0]);
			if (tItemInfo == NULL) {
				mUSER[*tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return false;
			}
			if (pItem->iSort != 2 && pItem->iSort != 7 && pItem->iSort != 11) {
				return false;
			}
		}
		else if ((mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][1] == (*tXPost)
			&& (mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][2] == (*tYPost - 1)))) {
			if (mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][0] < 1)
				continue;
			tItemInfo = mITEM.Search(mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][0]);
			if (tItemInfo == NULL) {
				mUSER[*tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return false;
			}
			if (pItem->iSort != 2 && pItem->iSort != 7 && pItem->iSort != 11) {
				return false;
			}
		}
		else if ((mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][1] == (*tXPost + 1)
			&& (mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][2] == (*tYPost - 1)))) {
			if (mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][0] < 1)
				continue;
			tItemInfo = mITEM.Search(mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][0]);
			if (tItemInfo == NULL) {
				mUSER[*tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return false;
			}
			if (pItem->iSort != 2 && pItem->iSort != 7 && pItem->iSort != 11) {
				return false;
			}

		}
		else if ((mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][1] == (*tXPost - 1)
			&& (mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][2] == (*tYPost)))) {
			if (mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][0] < 1)
				continue;
			tItemInfo = mITEM.Search(mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][0]);
			if (tItemInfo == NULL) {
				mUSER[*tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return false;
			}
			if (pItem->iSort != 2 && pItem->iSort != 7 && pItem->iSort != 11) {
				return false;
			}
		}

		if (iOccupyRange == 2) {
			if ((mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][1] == (*tXPost + 1)
				&& (mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][2] == (*tYPost)))) {
				if (mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][0] > 0) {
					return false;
				}
			}
			else if ((mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][1] == (*tXPost)
				&& (mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][2] == (*tYPost + 1)))) {
				if (mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][0] > 0) {
					return false;
				}
			}
			else if ((mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][1] == (*tXPost + 1)
				&& (mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][2] == (*tYPost + 1)))) {
				if (mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][0] > 0) {
					return false;
				}
			}
		}
	}
	return true;
}
// # }
bool MyUtil::FindEmptyInvenForItem(int iUserIndex, ITEM_INFO* pItem, int& iPage, int& iIndex)
{
	bool bResult = true;
	int iMaxPage = 1, iRange = 8, iOccupyRange = 1;
	AVATAR_INFO* pAvatar = &mUSER[iUserIndex].mAvatarInfo;

	if (pAvatar->aExpandInventoryDate >= mUTIL.ReturnNowDate())
		iMaxPage = 2;

	if (pItem->iSort != 2 && pItem->iSort != 7 && pItem->iSort != 11) {
		iRange = 7;
		iOccupyRange = 2;
	}

	bool bInvenSlots[MAX_INVENTORY_SLOT_NUM];

	for (int i = 0; i < iMaxPage; i++) {
		SetInvenSlotHumanReadable(iUserIndex, i, bInvenSlots);
		for (int j = 0; j < iRange; j++) {
			for (int k = 0; k < iRange; k++) {
				if (bInvenSlots[j * 8 + k] == false) {
					// .. .. .. ....
					bResult = true;
					for (int m = 0; m < iOccupyRange; m++) {
						for (int n = 0; n < iOccupyRange; n++) {
							int iPlus = j * 8 + k + m * 8 + n;
							if (bInvenSlots[iPlus] == true) {
								bResult = false;
								break;
							}
						}

						if (bResult == false) break;
					}

					if (bResult == true) {
						iPage = i;
						iIndex = j * 8 + k;
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool MyUtil::SetInvenSlotHumanReadable(int iUserIndex, int iPage, bool bInvenSlots[MAX_INVENTORY_SLOT_NUM])
{
	AVATAR_INFO* pAvatar = &mUSER[iUserIndex].mAvatarInfo;

	for (int i = 0; i < MAX_INVENTORY_SLOT_NUM; i++)
		bInvenSlots[i] = false;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (pAvatar->aInventory[iPage][i * 8 + j][0] > 0) {
				int iItemIndex = pAvatar->aInventory[iPage][i * 8 + j][0];
				ITEM_INFO* pItem = mITEM.Search(iItemIndex);
				if (pItem != NULL) {
					int iX = pAvatar->aInventory[iPage][i * 8 + j][1];
					int iY = pAvatar->aInventory[iPage][i * 8 + j][2];
					// .. 1 X 1 ... ..... ... 1.. ...
					bInvenSlots[iY * 8 + iX] = true;

					if (pItem->iSort != 2 && pItem->iSort != 7 && pItem->iSort != 11) {
						if (iX < 7) {
							bInvenSlots[iY * 8 + iX + 1] = true;
						}

						if (iY < 7) {
							bInvenSlots[(iY + 1) * 8 + iX] = true;

							if (iX < 7) {
								bInvenSlots[(iY + 1) * 8 + iX + 1] = true;
							}
						}
					}
				}
			}
		}
	}

	return true;
}

int MyUtil::GetEmptyInvenSlotIndex(int iUserIndex, int iPage)
{
	AVATAR_INFO* pAvatar = &mUSER[iUserIndex].mAvatarInfo;

	if (pAvatar == NULL)
		return -1;

	for (int i = 0; i < MAX_INVENTORY_SLOT_NUM; i++) {
		if (pAvatar->aInventory[iPage][i][0] < 1)
			return i;
	}

	return -1;
}

int MyUtil::ReturnHealthState(int tPlayTime)
{
	if (tPlayTime <= 60)
	{
		return 1;
	}
	if (tPlayTime <= 120)
	{
		return 2;
	}
	if (tPlayTime <= 180)
	{
		return 3;
	}
	if (tPlayTime <= 299)
	{
		return 4;
	}
	return 5;
}
//PROCESS_FOR_CHANGE
BOOL MyUtil::ProcessForChange(int tUserIndex)
{
	int tRandomNumber;
	int tSort;
	ITEM_INFO* tITEM_INFO;
	int tItemLLevel;
	int tItemHLevel;
	int tTribeItemList[9];
	int tItemType;
	int tItemSort;
	int tSearchNum;

	tRandomNumber = rand() % 10000;
	if (tRandomNumber < 3000)
	{
		tSort = 1;
	}
	else if (tRandomNumber < 5000)
	{
		tSort = 2;
	}
	else if (tRandomNumber < 6000)
	{
		tSort = 3;
	}
	else if (tRandomNumber < 6400)
	{
		tSort = 4;
	}
	else if (tRandomNumber < 6500)
	{
		tSort = 5;
	}
	else if (tRandomNumber < 6600)
	{
		tSort = 6;
	}
	else if (tRandomNumber < 6700)
	{
		tSort = 7;
	}
	else if (tRandomNumber < 6800)
	{
		tSort = 8;
	}
	else if (tRandomNumber < 9999)
	{
		tSort = 9;
		tItemType = 3;
	}
	else if (tRandomNumber < 9999)
	{
		tSort = 9;
		tItemType = 4;
	}
	switch (tSort)
	{
	case 1:
		tITEM_INFO = mITEM.Search(1022);
		if (tITEM_INFO == NULL)
		{
			return FALSE;
		}
		if (!ProcessForDropItem(12, tITEM_INFO->iIndex, 0, 0, ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], 0, mUSER[tUserIndex].DropItemSocketGmAndBos))
		{
			return FALSE;
		}
		////mGAMELOG.GL_647_KILLOTHERTRIBE_TO_ITEM( tUserIndex, tITEM_INFO->iIndex );
		return TRUE;
	case 2:
		tITEM_INFO = mITEM.Search(1023);
		if (tITEM_INFO == NULL)
		{
			return FALSE;
		}
		if (!ProcessForDropItem(12, tITEM_INFO->iIndex, 0, 0, ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], 0, mUSER[tUserIndex].DropItemSocketGmAndBos))
		{
			return FALSE;
		}
		////mGAMELOG.GL_647_KILLOTHERTRIBE_TO_ITEM( tUserIndex, tITEM_INFO->iIndex );
		return TRUE;
	case 3:
		tITEM_INFO = mITEM.Search(1379);
		if (tITEM_INFO == NULL)
		{
			return FALSE;
		}
		if (!ProcessForDropItem(12, tITEM_INFO->iIndex, 0, 0, ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], 0, mUSER[tUserIndex].DropItemSocketGmAndBos))
		{
			return FALSE;
		}
		////mGAMELOG.GL_647_KILLOTHERTRIBE_TO_ITEM( tUserIndex, tITEM_INFO->iIndex );
		return TRUE;
	case 4:
		tITEM_INFO = mITEM.Search(1041);
		if (tITEM_INFO == NULL)
		{
			return FALSE;
		}
		if (!ProcessForDropItem(12, tITEM_INFO->iIndex, 0, 0, ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], 0, mUSER[tUserIndex].DropItemSocketGmAndBos))
		{
			return FALSE;
		}
		////mGAMELOG.GL_647_KILLOTHERTRIBE_TO_ITEM( tUserIndex, tITEM_INFO->iIndex );
		return TRUE;
	case 5:
		tITEM_INFO = mITEM.Search(1017);
		if (tITEM_INFO == NULL)
		{
			return FALSE;
		}
		if (!ProcessForDropItem(12, tITEM_INFO->iIndex, 0, 0, ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], 0, mUSER[tUserIndex].DropItemSocketGmAndBos))
		{
			return FALSE;
		}
		////mGAMELOG.GL_647_KILLOTHERTRIBE_TO_ITEM( tUserIndex, tITEM_INFO->iIndex );
		return TRUE;
	case 6:
		tITEM_INFO = mITEM.Search(1018);
		if (tITEM_INFO == NULL)
		{
			return FALSE;
		}
		if (!ProcessForDropItem(12, tITEM_INFO->iIndex, 0, 0, ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], 0, mUSER[tUserIndex].DropItemSocketGmAndBos))
		{
			return FALSE;
		}
		////mGAMELOG.GL_647_KILLOTHERTRIBE_TO_ITEM( tUserIndex, tITEM_INFO->iIndex );
		return TRUE;
	case 7:
		tITEM_INFO = mITEM.Search(1092);
		if (tITEM_INFO == NULL)
		{
			return FALSE;
		}
		if (!ProcessForDropItem(12, tITEM_INFO->iIndex, 0, 0, ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], 0, mUSER[tUserIndex].DropItemSocketGmAndBos))
		{
			return FALSE;
		}
		////mGAMELOG.GL_647_KILLOTHERTRIBE_TO_ITEM( tUserIndex, tITEM_INFO->iIndex );
		return TRUE;
	case 8:
		tITEM_INFO = mITEM.Search(1093);
		if (tITEM_INFO == NULL)
		{
			return FALSE;
		}
		if (!ProcessForDropItem(12, tITEM_INFO->iIndex, 0, 0, ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], 0, mUSER[tUserIndex].DropItemSocketGmAndBos))
		{
			return FALSE;
		}
		//mGAMELOG.GL_647_KILLOTHERTRIBE_TO_ITEM( tUserIndex, tITEM_INFO->iIndex );
		return TRUE;
	case 9:
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1)
		{
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
		}
		else
		{
			tItemLLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2;
			tItemHLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2;
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
		tItemSort = tTribeItemList[(rand() % 9)];
		tSearchNum = 0;
		while (tSearchNum < 10)
		{
			tITEM_INFO = mITEM.Return((tItemLLevel + (rand() % (tItemHLevel - tItemLLevel + 1))), tItemType, tItemSort);
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
			return FALSE;
		}
		if (!ProcessForDropItem(12, tITEM_INFO->iIndex, 0, 0, ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], 0, mUSER[tUserIndex].DropItemSocketGmAndBos))
		{
			return FALSE;
		}
		////mGAMELOG.GL_647_KILLOTHERTRIBE_TO_ITEM( tUserIndex, tITEM_INFO->iIndex );
		return TRUE;
	}
	return FALSE;
}
#ifdef __GOD__
//CHECK_CHANGE_TRIBE_TIME
BOOL MyUtil::CheckChangeTribeTime(void)
{
	time_t tCountSeconds;
	struct tm* tPresentTime;

	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return FALSE;
	}
	if (tPresentTime->tm_wday != 6)
	{
		return FALSE;
	}
	if (tPresentTime->tm_hour < 12)
	{
		return FALSE;
	}
	return TRUE;
}
#endif
// # Defense Hack # {
int MyUtil::GetAttackRadius(int tSkillNumber)
{
	switch (tSkillNumber) {
	case   1: return  25;
	case   2: return  25;
	case   3: return  25;
	case   4: return  15;
	case   5: return  15;
	case   6: return   0;
	case   7: return   0;
	case   8: return  20;
	case   9: return  20;
	case  10: return  45;
	case  11: return   0;
	case  12: return  25;
	case  13: return  25;
	case  14: return  50;
	case  15: return   0;
	case  16: return 120;
	case  17: return 120;
	case  18: return  45;
	case  19: return   0;
	case  20: return   0;
	case  21: return   0;
	case  22: return   0;
	case  23: return  15;
	case  24: return  15;
	case  25: return   0;
	case  26: return   0;
	case  27: return  25;
	case  28: return  25;
	case  29: return  50;
	case  30: return   0;
	case  31: return  15;
	case  32: return  15;
	case  33: return  45;
	case  34: return   0;
	case  35: return 120;
	case  36: return 120;
	case  37: return  45;
	case  38: return   0;
	case  39: return   0;
	case  40: return   0;
	case  41: return   0;
	case  42: return  15;
	case  43: return  15;
	case  44: return   0;
	case  45: return   0;
	case  46: return  20;
	case  47: return  20;
	case  48: return  45;
	case  49: return   0;
	case  50: return  25;
	case  51: return  25;
	case  52: return  50;
	case  53: return   0;
	case  54: return 120;
	case  55: return 120;
	case  56: return  45;
	case  57: return   0;
	case  58: return  20;
	case  59: return  20;
	case  60: return  25;
	case  61: return  25;
	case  62: return 120;
	case  63: return 120;
	case  64: return  25;
	case  65: return  25;
	case  66: return  15;
	case  67: return  15;
	case  68: return 120;
	case  69: return 120;
	case  70: return  20;
	case  71: return  20;
	case  72: return  25;
	case  73: return  25;
	case  74: return 120;
	case  75: return 120;
	case  76: return  30;
	case  77: return  30;
	case  78: return  30;
	case  79: return  30;
	case  80: return 150;
	case  81: return  30;
	case  82: return   0;
	case  83: return   0;
	case  84: return   0;
	case  85: return  20;
	case  86: return  20;
	case  87: return  25;
	case  88: return  25;
	case  89: return 120;
	case  90: return 120;
	case  91: return  25;
	case  92: return  25;
	case  93: return  15;
	case  94: return  15;
	case  95: return 120;
	case  96: return 120;
	case  97: return  20;
	case  98: return  20;
	case  99: return  25;
	case 100: return  25;
	case 101: return 120;
	case 102: return 120;
	case 103: return   0;
	case 104: return   0;
	case 105: return   0;
	case 106: return 300;
	case 107: return 300;
	case 108: return 300;
	case 109: return 300;
	case 110: return 300;
	case 111: return 300;
	case 112: return  70;
	case 113: return  70;
	case 114: return  70;
	case 115: return  70;
	case 116: return  70;
	case 117: return  70;
	case 118: return  70;
	case 119: return  70;
	case 120: return  70;
#ifdef __GOD__
	case 121: return  20;
	case 122: return  20;
	case 123: return  25;
	case 124: return  25;
	case 125: return 120;
	case 126: return 120;
	case 127: return  25;
	case 128: return  25;
	case 129: return  15;
	case 130: return  15;
	case 131: return 120;
	case 132: return 120;
	case 133: return  20;
	case 134: return  20;
	case 135: return  25;
	case 136: return  25;
	case 137: return 120;
	case 138: return 120;
#endif
	}
	return 0;
}

float MyUtil::ReturnLengthXYZ(float tLocation01[3], float tLocation02[3])
{
	return ::sqrtf(::powf((tLocation01[0] - tLocation02[0]), 2) + ::powf((tLocation01[1] - tLocation02[1]), 2) + ::powf((tLocation01[2] - tLocation02[2]), 2));
}

bool MyUtil::CheckRAttackRange(int tUserIndex, int tSkillNumber, float tLocation1[3], float tLocation2[3], float tObjectSize)
{
	int iTemp = 0;
	float fTemp = 0.0f;
	fTemp = ReturnLengthXYZ(&tLocation1[0], &tLocation2[0]);
	//iTemp = GetAttackRadius(tSkillNumber) + 40;

	//iTemp = GetAttackRadius(tSkillNumber) + tObjectSize + 40;
	//LOG_TO_FILE_2("GetAttackRadius : %d, %d\n", GetAttackRadius(tSkillNumber), tObjectSize);

	// # Defense Hack Add02 #
#if 0
	if (tObjectSize < 20.0f) {
		tObjectSize = 20.0f;
	}
#endif
	iTemp = GetAttackRadius(tSkillNumber) + (int)(ceilf(tObjectSize));

	if ((int)fTemp <= iTemp)
	{
		return true;
	}
	return false;
}


bool MyUtil::CheckSkillNumber(int tUserIndex)
{
	bool tCheckType1 = false;
	bool tCheckType2 = false;

	switch (mUSER[tUserIndex].mAvatarInfo.AutoHunt.AtakType[0][0]) {
	case   0:
	case   8:
	case   9:
	case  58:
	case  59:
	case  85:
	case  86:
	case 121:
	case 122:
	case  27:
	case  28:
	case  64:
	case  65:
	case  91:
	case  92:
	case 127:
	case 128:
	case  46:
	case  47:
	case  70:
	case  71:
	case  97:
	case  98:
	case 133:
	case 134:
	case  12:
	case  13:
	case  60:
	case  61:
	case  87:
	case  88:
	case 123:
	case 124:
	case  31:
	case  32:
	case  66:
	case  67:
	case  93:
	case  94:
	case 129:
	case 130:
	case  50:
	case  51:
	case  72:
	case  73:
	case  99:
	case 100:
	case 135:
	case 136:
	case  16:
	case  17:
	case  62:
	case  63:
	case  89:
	case  90:
	case 125:
	case 126:
	case  35:
	case  36:
	case  68:
	case  69:
	case  95:
	case  96:
	case 131:
	case 132:
	case  54:
	case  55:
	case  74:
	case  75:
	case 101:
	case 102:
	case 137:
	case 138:
		tCheckType1 = true;
	}

	switch (mUSER[tUserIndex].mAvatarInfo.AutoHunt.AtakType[1][0]) {
	case   0:
	case  10:
	case 112:
	case  29:
	case 115:
	case  48:
	case 118:
	case  14:
	case 113:
	case  33:
	case 116:
	case  52:
	case 119:
	case  18:
	case 114:
	case  37:
	case 117:
	case  56:
	case 120:
		tCheckType2 = true;
	}

	if (tCheckType1 && tCheckType2) {
		return true;
	}

	return false;
}
// # }
// 
//RETURN_I_S_VALUE
int MyUtil::SOCKET1(int tValue)
{
	char tempValue01[4];

	CopyMemory(&tempValue01[0], &tValue, 4);
	return ((int)tempValue01[2]);
}
//CHANGE_I_S_VALUE
int MyUtil::CHANGESOCKET1(int tValue, int tISValue)
{
	char tempValue01[4];
	int tResultIValue;

	CopyMemory(&tempValue01[0], &tValue, 4);
	tempValue01[2] = (char)tISValue;
	CopyMemory(&tResultIValue, &tempValue01[0], 4);
	return tResultIValue;
}
//CHANGE_I_S_VALUE
int MyUtil::CHANGESOCKET1DEGER(int tValue, int tISValue)
{
	char tempValue01[4];
	int tResultIValue;

	CopyMemory(&tempValue01[0], &tValue, 4);
	tempValue01[3] = (char)tISValue;
	CopyMemory(&tResultIValue, &tempValue01[0], 4);
	return tResultIValue;
}
int MyUtil::SOCKET2(int tValue)
{
	char tempValue01[4];

	CopyMemory(&tempValue01[0], &tValue, 4);
	return ((int)tempValue01[0]);
}
//CHANGE_I_S_VALUE
int MyUtil::CHANGESOCKET2(int tValue, int tISValue)
{
	char tempValue01[4];
	int tResultIValue;

	CopyMemory(&tempValue01[0], &tValue, 4);
	tempValue01[0] = (char)tISValue;
	CopyMemory(&tResultIValue, &tempValue01[0], 4);
	return tResultIValue;
}
//CHANGE_I_S_VALUE
int MyUtil::CHANGESOCKET2DEGER(int tValue, int tISValue)
{
	char tempValue01[4];
	int tResultIValue;

	CopyMemory(&tempValue01[0], &tValue, 4);
	tempValue01[1] = (char)tISValue;
	CopyMemory(&tResultIValue, &tempValue01[0], 4);
	return tResultIValue;
}
int MyUtil::SOCKET3(int tValue)
{
	char tempValue01[4];

	CopyMemory(&tempValue01[0], &tValue, 4);
	return ((int)tempValue01[2]);
}
//CHANGE_I_S_VALUE
int MyUtil::CHANGESOCKET3(int tValue, int tISValue)
{
	char tempValue01[4];
	int tResultIValue;

	CopyMemory(&tempValue01[0], &tValue, 4);
	tempValue01[2] = (char)tISValue;
	CopyMemory(&tResultIValue, &tempValue01[0], 4);
	return tResultIValue;
}
//CHANGE_I_S_VALUE
int MyUtil::CHANGESOCKET3DEGER(int tValue, int tISValue)
{
	char tempValue01[4];
	int tResultIValue;

	CopyMemory(&tempValue01[0], &tValue, 4);
	tempValue01[3] = (char)tISValue;
	CopyMemory(&tResultIValue, &tempValue01[0], 4);
	return tResultIValue;
}
int MyUtil::SOCKET4(int tValue)
{
	char tempValue01[4];

	CopyMemory(&tempValue01[0], &tValue, 4);
	return ((int)tempValue01[0]);
}
//CHANGE_I_S_VALUE
int MyUtil::CHANGESOCKET4(int tValue, int tISValue)
{
	char tempValue01[4];
	int tResultIValue;

	CopyMemory(&tempValue01[0], &tValue, 4);
	tempValue01[0] = (char)tISValue;
	CopyMemory(&tResultIValue, &tempValue01[0], 4);
	return tResultIValue;
}
//CHANGE_I_S_VALUE
int MyUtil::CHANGESOCKET4DEGER(int tValue, int tISValue)
{
	char tempValue01[4];
	int tResultIValue;

	CopyMemory(&tempValue01[0], &tValue, 4);
	tempValue01[1] = (char)tISValue;
	CopyMemory(&tResultIValue, &tempValue01[0], 4);
	return tResultIValue;
}
int MyUtil::SOCKET5(int tValue)
{
	char tempValue01[4];

	CopyMemory(&tempValue01[0], &tValue, 4);
	return ((int)tempValue01[2]);
}
//CHANGE_I_S_VALUE
int MyUtil::CHANGESOCKET5(int tValue, int tISValue)
{
	char tempValue01[4];
	int tResultIValue;

	CopyMemory(&tempValue01[0], &tValue, 4);
	tempValue01[2] = (char)tISValue;
	CopyMemory(&tResultIValue, &tempValue01[0], 4);
	return tResultIValue;
}
//CHANGE_I_S_VALUE
int MyUtil::CHANGESOCKET5DEGER(int tValue, int tISValue)
{
	char tempValue01[4];
	int tResultIValue;

	CopyMemory(&tempValue01[0], &tValue, 4);
	tempValue01[3] = (char)tISValue;
	CopyMemory(&tResultIValue, &tempValue01[0], 4);
	return tResultIValue;
}
void MyUtil::ProcessForLevelBonusSend(int tUserIndex, int tLevel)
{

	if (tLevel == 45)//45Level
	{
		mUSER[tUserIndex].mAvatarInfo.BeginnerLevel = tLevel;
		mUSER[tUserIndex].mAvatarInfo.Beginner = 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.Beginner);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else if (tLevel == 75)//75 Level
	{
		mUSER[tUserIndex].mAvatarInfo.BeginnerLevel = tLevel;
		mUSER[tUserIndex].mAvatarInfo.Beginner = 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.Beginner);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else if (tLevel == 105)//105 Level
	{
		mUSER[tUserIndex].mAvatarInfo.BeginnerLevel = tLevel;
		mUSER[tUserIndex].mAvatarInfo.Beginner = 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.Beginner);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else if (tLevel == 114)//U2
	{
		mUSER[tUserIndex].mAvatarInfo.BeginnerLevel = tLevel;
		mUSER[tUserIndex].mAvatarInfo.Beginner = 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.Beginner);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else if (tLevel == 117)//U5
	{
		mUSER[tUserIndex].mAvatarInfo.BeginnerLevel = tLevel;
		mUSER[tUserIndex].mAvatarInfo.Beginner = 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.Beginner);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else if (tLevel == 120)//u8
	{
		mUSER[tUserIndex].mAvatarInfo.BeginnerLevel = tLevel;
		mUSER[tUserIndex].mAvatarInfo.Beginner = 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.Beginner);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else if (tLevel == 123)//u11
	{
		mUSER[tUserIndex].mAvatarInfo.BeginnerLevel = tLevel;
		mUSER[tUserIndex].mAvatarInfo.Beginner = 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.Beginner);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else if (tLevel == 126)//u14
	{
		mUSER[tUserIndex].mAvatarInfo.BeginnerLevel = tLevel;
		mUSER[tUserIndex].mAvatarInfo.Beginner = 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.Beginner);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else if (tLevel == 129)//u17
	{
		mUSER[tUserIndex].mAvatarInfo.BeginnerLevel = tLevel;
		mUSER[tUserIndex].mAvatarInfo.Beginner = 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.Beginner);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else if (tLevel == 132)//u20
	{
		mUSER[tUserIndex].mAvatarInfo.BeginnerLevel = tLevel;
		mUSER[tUserIndex].mAvatarInfo.Beginner = 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.Beginner);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else if (tLevel == 135)//u23
	{
		mUSER[tUserIndex].mAvatarInfo.BeginnerLevel = tLevel;
		mUSER[tUserIndex].mAvatarInfo.Beginner = 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.Beginner);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else if (tLevel == 138)//u26
	{
		mUSER[tUserIndex].mAvatarInfo.BeginnerLevel = tLevel;
		mUSER[tUserIndex].mAvatarInfo.Beginner = 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.Beginner);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else if (tLevel == 141)//u29
	{
		mUSER[tUserIndex].mAvatarInfo.BeginnerLevel = tLevel;
		mUSER[tUserIndex].mAvatarInfo.Beginner = 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.Beginner);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else if (tLevel == 144)//u32
	{
		mUSER[tUserIndex].mAvatarInfo.BeginnerLevel = tLevel;
		mUSER[tUserIndex].mAvatarInfo.Beginner = 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.Beginner);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else if (tLevel == 145)//u33
	{
		mUSER[tUserIndex].mAvatarInfo.BeginnerLevel = tLevel;
		mUSER[tUserIndex].mAvatarInfo.Beginner = 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.Beginner);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else if (tLevel == 146)//u33
	{
		mUSER[tUserIndex].mAvatarInfo.BeginnerLevel = tLevel;
		mUSER[tUserIndex].mAvatarInfo.Beginner = 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.Beginner);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else if (tLevel == 147)//u33
	{
		mUSER[tUserIndex].mAvatarInfo.BeginnerLevel = tLevel;
		mUSER[tUserIndex].mAvatarInfo.Beginner = 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.Beginner);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else if (tLevel == 148)//u33
	{
		mUSER[tUserIndex].mAvatarInfo.BeginnerLevel = tLevel;
		mUSER[tUserIndex].mAvatarInfo.Beginner = 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.Beginner);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else if (tLevel == 149)//u33
	{
		mUSER[tUserIndex].mAvatarInfo.BeginnerLevel = tLevel;
		mUSER[tUserIndex].mAvatarInfo.Beginner = 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.Beginner);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else if (tLevel == 150)//u33
	{
		mUSER[tUserIndex].mAvatarInfo.BeginnerLevel = tLevel;
		mUSER[tUserIndex].mAvatarInfo.Beginner = 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.Beginner);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else if (tLevel == 151)//u33
	{
		mUSER[tUserIndex].mAvatarInfo.BeginnerLevel = tLevel;
		mUSER[tUserIndex].mAvatarInfo.Beginner = 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.Beginner);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else if (tLevel == 152)//u33
	{
		mUSER[tUserIndex].mAvatarInfo.BeginnerLevel = tLevel;
		mUSER[tUserIndex].mAvatarInfo.Beginner = 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.Beginner);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else if (tLevel == 153)//u33
	{
		mUSER[tUserIndex].mAvatarInfo.BeginnerLevel = tLevel;
		mUSER[tUserIndex].mAvatarInfo.Beginner = 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.Beginner);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else if (tLevel == 154)//u33
	{
		mUSER[tUserIndex].mAvatarInfo.BeginnerLevel = tLevel;
		mUSER[tUserIndex].mAvatarInfo.Beginner = 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.Beginner);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else if (tLevel == 155)//u33
	{
		mUSER[tUserIndex].mAvatarInfo.BeginnerLevel = tLevel;
		mUSER[tUserIndex].mAvatarInfo.Beginner = 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.Beginner);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else if (tLevel == 156)//u33
	{
		mUSER[tUserIndex].mAvatarInfo.BeginnerLevel = tLevel;
		mUSER[tUserIndex].mAvatarInfo.Beginner = 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.Beginner);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else if (tLevel == 157)//u33
	{
		mUSER[tUserIndex].mAvatarInfo.BeginnerLevel = tLevel;
		mUSER[tUserIndex].mAvatarInfo.Beginner = 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.Beginner);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	return;
}
//-------------------------------------------------------------------------------------------------

int MyUtil::CheckPVNumber(int tTribe)
{
	int a = 0;

	if (mGAME.mWorldInfo.mProvingGroundsState[0] == (tTribe + 1))
	{
		a++;
	}
	if (mGAME.mWorldInfo.mProvingGroundsState[1] == (tTribe + 1))
	{
		a++;
	}
	if (mGAME.mWorldInfo.mProvingGroundsState[2] == (tTribe + 1))
	{
		a++;
	}
	if (mGAME.mWorldInfo.mProvingGroundsState[3] == (tTribe + 1))
	{
		a++;
	}
	return a;
}