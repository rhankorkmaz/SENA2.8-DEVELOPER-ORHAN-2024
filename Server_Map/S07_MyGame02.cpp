//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "Shengming.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_GAME
//-------------------------------------------------------------------------------------------------
//VARIABLE_FOR_ATTACK_FUNCTION
#define PROTECT_TICK                  20
static int tMinDamageValueWithAvatar = 5;
static AVATAR_OBJECT *tAVATAR_OBJECT1;
static AVATAR_OBJECT *tAVATAR_OBJECT2;
static MONSTER_OBJECT *tMONSTER_OBJECT;
static int tChargingValue;//Albız
static int tAttackSuccessValue;
static int tAttackBlockValue;
static int tAttackDetermineValue;
static int tAttackPowerValue;
static float tAttackPowerUpRatio;
static int tDefensePowerValue;
static int tDamageValue;
static int tReturnDamageProbability;
static int tReturnDamageValue;
static int tShieldDamageValue;
static int tElementAttackPower;
static float tElementAttackPowerUpRatio;
static int tElementDefensePower;
static float tDeathDirection[3];
static float tDeathLength;
//CHECK_POSSIBLE_ATTACK_TARGET
BOOL MyGame::CheckPossibleAttackTarget(int tTargetSort, int tActionSort)
{
	switch (tTargetSort)
	{
	case 1:
		switch (tActionSort)
		{
		case  0:
		case 12:
			return FALSE;
		}
		return TRUE;
	case 2:
		switch (tActionSort)
		{
		case  0:
		case 12:
		case 19:
			return FALSE;
		}
		return TRUE;
	default:
		return FALSE;
	}
	return TRUE;
}


unsigned int MyGame::getCriticalAttackDefValue(AVATAR_OBJECT *_attacker, AVATAR_OBJECT *_defenser)
{
	unsigned int t_cmp_critical;
	int t_critical;
	int t_critical_defense;

	t_cmp_critical = 0;
	t_critical = _attacker->GetCritical();
	t_critical_defense = _defenser->GetCriticalDefense();

	if (t_critical > t_critical_defense)
	{
		t_cmp_critical = (unsigned int)(t_critical - t_critical_defense);
	}

	return t_cmp_critical;
}

void MyGame::ProcessAttack01(int tUserIndex, ATTACK_FOR_PROTOCOL *tAttackInfo)
{
#ifdef __GOD__
	int index01;
	int index02;
	int tBonusSkillGrade;
#endif
	int tShieldSort = 9;
	int tShieldType = 5;
	unsigned int tRandom = 0;
	if ((tAttackInfo->mServerIndex1 != tUserIndex) || (tAttackInfo->mUniqueNumber1 != mAVATAR_OBJECT[tUserIndex].mUniqueNumber))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);


		return;
	}
	tAVATAR_OBJECT1 = &mAVATAR_OBJECT[tAttackInfo->mServerIndex1];
	tAVATAR_OBJECT1->mDATA.aAction.aLocation[0] = tAttackInfo->mSenderLocation[0];
	tAVATAR_OBJECT1->mDATA.aAction.aLocation[1] = tAttackInfo->mSenderLocation[1];
	tAVATAR_OBJECT1->mDATA.aAction.aLocation[2] = tAttackInfo->mSenderLocation[2];
	tAVATAR_OBJECT1->SetSpaceIndex();
	if ((tAttackInfo->mServerIndex2 < 0) || (tAttackInfo->mServerIndex2 > (mSERVER.mMAX_USER_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tAVATAR_OBJECT2 = &mAVATAR_OBJECT[tAttackInfo->mServerIndex2];
	if ((!tAVATAR_OBJECT2->mCheckValidState) || (tAVATAR_OBJECT2->mUniqueNumber != tAttackInfo->mUniqueNumber2))
	{
		return;
	}
	if (tAVATAR_OBJECT1->mDATA.aLifeValue < 1)
	{
		return;
	}
	if ((mTickCount - mUSER[tAttackInfo->mServerIndex1].mTickCountFor01SecondForProtect) < PROTECT_TICK)
	{
		return;
	}
	if (mUSER[tAttackInfo->mServerIndex2].mMoveZoneResult == 1)
	{
		return;
	}
	if (tAVATAR_OBJECT2->mDATA.aLifeValue < 1)
	{
		return;
	}
	if (tAVATAR_OBJECT2->mDATA.aPShopState == 1)
	{
		return;
	}
	if (!CheckPossibleAttackTarget(1, tAVATAR_OBJECT2->mDATA.aAction.aSort))
	{
		return;
	}
	if ((mTickCount - mUSER[tAttackInfo->mServerIndex2].mTickCountFor01SecondForProtect) < PROTECT_TICK)
	{
		return;
	}
	if ((tAVATAR_OBJECT1->mDATA.aDuelState[0] != 1) || (tAVATAR_OBJECT2->mDATA.aDuelState[0] != 1) || (tAVATAR_OBJECT1->mDATA.aDuelState[1] != tAVATAR_OBJECT2->mDATA.aDuelState[1]) || (tAVATAR_OBJECT1->mDATA.aDuelState[2] == tAVATAR_OBJECT2->mDATA.aDuelState[2]))
	{
		return;
	}
	mAVATAR_OBJECT[tAttackInfo->mServerIndex2].SetBasicAbilityFromEquip();
	mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();

	//Albız
	tChargingValue = mUSER[tAttackInfo->mServerIndex1].mEffectValue[8][0];
	if (mUSER[tAttackInfo->mServerIndex1].mEffectValue[8][0] > 0)
	{
		mUSER[tAttackInfo->mServerIndex1].mEffectValue[8][0] = 0;
		mUSER[tAttackInfo->mServerIndex1].mEffectValue[8][1] = 0;
		tAVATAR_OBJECT1->mDATA.aEffectValueForView[8] = 0;
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(tAttackInfo->mServerIndex1, tAttackInfo->mUniqueNumber1, 2, 0, 0, 0);
		mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
	}

	switch (tAttackInfo->mAttackActionValue1)
	{
	case 1:
		tAttackSuccessValue = tAVATAR_OBJECT1->GetAttackSuccess();
		break;
	case 2:
		if (mUSER[tUserIndex].mCheckMaxAttackPacketNum == 1)
		{
			if ((tAVATAR_OBJECT1->mDATA.aAction.aSkillNumber != tAttackInfo->mAttackActionValue2) || ((tAVATAR_OBJECT1->mDATA.aAction.aSkillGradeNum1 + tAVATAR_OBJECT1->mDATA.aAction.aSkillGradeNum2) != tAttackInfo->mAttackActionValue3))
			{
				return;
			}
		}
		tAttackSuccessValue = tAVATAR_OBJECT1->GetAttackSuccess();
		break;
	default:
		return;
	}
	if (tAttackSuccessValue < 1)
	{
		return;
	}
	tAttackBlockValue = tAVATAR_OBJECT2->GetAttackBlock();
	if (tAttackBlockValue > 0)
	{
		if (tAttackSuccessValue > tAttackBlockValue)
		{
			tAttackDetermineValue = (int)(70.0f + (((float)tAttackSuccessValue / (float)tAttackBlockValue) - 1.0f) * 25.0f);
			
			if (tAttackDetermineValue > 99)
			{
				tAttackDetermineValue = 99;
			}
		}
		else
		{
			tAttackDetermineValue = (int)(70.0f - (((float)tAttackBlockValue / (float)tAttackSuccessValue) - 1.0f) * 25.0f);
			if (tAttackDetermineValue < 1)
			{
				tAttackDetermineValue = 1;
			}
		}
	
		tRandom = rand();
		if ((tRandom % 100) >= (unsigned int)tAttackDetermineValue)
		{
			tAttackInfo->mAttackResultValue = 0;
			mTRANSFER.B_PROCESS_ATTACK_RECV(tAttackInfo);
			mUSER[tAttackInfo->mServerIndex1].Send(TRUE, (char *)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
	}

	switch (tAttackInfo->mAttackActionValue1)
	{
	case 1:
		tAttackPowerValue = tAVATAR_OBJECT1->GetAttackPower();
		break;
	case 2:
		tAttackPowerValue = tAVATAR_OBJECT1->GetAttackPower();
		tAttackPowerUpRatio = mSKILL.ReturnSkillValue(tAttackInfo->mAttackActionValue2, tAttackInfo->mAttackActionValue3, 7);
		if (tAttackPowerUpRatio > 0.0f)
		{
			tAttackPowerValue = (int)((float)tAttackPowerValue * (tAttackPowerUpRatio + 100.0f) * 0.01f);
		}
		break;
	}
	tDefensePowerValue = tAVATAR_OBJECT2->GetDefensePower();
	tDamageValue = tAttackPowerValue - tDefensePowerValue;
	//100

	if (tDamageValue < 1)
	{
		tDamageValue = 1;
	}
	//Albız
	if (tChargingValue > 0)
	{
		tDamageValue = (int)((float)(tDamageValue * (tChargingValue + 100)) * 0.01f);
	}

	tRandom = rand();
	if ((tRandom % 2) == 0)
	{
		tRandom = rand();
		tDamageValue += (int)((float)(tDamageValue * (tRandom % 11)) * 0.01f);
	}
	else
	{
		tRandom = rand();
		tDamageValue -= (int)((float)(tDamageValue * (tRandom % 11)) * 0.01f);
	}

	
	if (tDamageValue < tMinDamageValueWithAvatar)
	{
		tDamageValue = tMinDamageValueWithAvatar;
	}

	tAttackInfo->mAttackCriticalExist = 0;
	switch (tAttackInfo->mAttackActionValue1)
	{
	case 1:
		tRandom = (rand() % 100);
		if (tRandom < getCriticalAttackDefValue(tAVATAR_OBJECT1, tAVATAR_OBJECT2))
		{
			tDamageValue *= 2;
			tAttackInfo->mAttackCriticalExist = 1;
		}
		break;
	case 2:
		if (tAttackInfo->mAttackActionValue2 == 78)
		{
			break;
		}
		switch (mSKILL.ReturnAttackType(tAttackInfo->mAttackActionValue2))
		{
		case 2:
		case 5:
			tRandom = (rand() % 100);
			if (tRandom < getCriticalAttackDefValue(tAVATAR_OBJECT1, tAVATAR_OBJECT2))
			{
				tDamageValue *= 2;
				tAttackInfo->mAttackCriticalExist = 1;
			}
			break;
		}
		break;
	}
	
	tDamageValue /= tMinDamageValueWithAvatar;

	

	//Demir Ten Seçilimi
	if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[9][0] > 0)
	{
		tShieldSort = 9;
		tShieldType = 5;
	}
	else if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[29][0] > 0)
	{
		tShieldSort = 29;
		tShieldType = 31;
	}
	else if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[30][0] > 0)
	{
		tShieldSort = 30;
		tShieldType = 32;
	}
	else if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[31][0] > 0)
	{
		tShieldSort = 31;
		tShieldType = 33;
	}
	else if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[32][0] > 0)
	{
		tShieldSort = 32;
		tShieldType = 34;
	}
	else if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[33][0] > 0)
	{
		tShieldSort = 33;
		tShieldType = 35;
	}
	else if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[34][0] > 0)
	{
		tShieldSort = 34;
		tShieldType = 36;
	}
	//Zihin Yayma
	if (mUSER[tAttackInfo->mServerIndex1].mEffectValue[14][0] > 0)
	{
		tRandom = rand();
		
		if ((tRandom % 2000) < (unsigned int)mUSER[tAttackInfo->mServerIndex1].mEffectValue[14][0])
		{
			mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0] = 0;
			mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][1] = 0;
			tAVATAR_OBJECT2->mDATA.aEffectValueForView[tShieldSort] = 0;
			mTRANSFER.B_AVATAR_CHANGE_INFO_1(tAttackInfo->mServerIndex2, tAttackInfo->mUniqueNumber2, 3, 0, 0, 0);
			mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT2->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		}
	}
	//Yansıma
	if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[12][0] > 0)
	{
		tReturnDamageProbability = mUSER[tAttackInfo->mServerIndex2].mEffectValue[12][0];
		if (tAVATAR_OBJECT1->mDATA.aLevel1 > tAVATAR_OBJECT2->mDATA.aLevel1)
		{
			tReturnDamageProbability -= ((tAVATAR_OBJECT1->mDATA.aLevel1 - tAVATAR_OBJECT2->mDATA.aLevel1) * 3);
		}
		tRandom = rand();
		if (tReturnDamageProbability < 0) {
			tReturnDamageProbability = 0;
		}
		if ((tRandom % 1000) < tReturnDamageProbability)
		{
			tRandom = rand();
			tReturnDamageValue = (int)((float)(tDamageValue * (100 + tRandom % 51)) * 0.01f);
			mTRANSFER.B_AVATAR_CHANGE_INFO_1(tAttackInfo->mServerIndex1, tAttackInfo->mUniqueNumber1, 4, tReturnDamageValue, 0, 0);
			mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			tAVATAR_OBJECT1->mDATA.aLifeValue -= tReturnDamageValue;
			if (tAVATAR_OBJECT1->mDATA.aLifeValue < 1)
			{
				tAVATAR_OBJECT1->mDATA.aLifeValue = 0;
				//------------------------//
				//PROCESS_FOR_AVATAR_DEATH//
				//------------------------//
				tDeathDirection[0] = tAVATAR_OBJECT1->mDATA.aAction.aLocation[0] - tAVATAR_OBJECT2->mDATA.aAction.aLocation[0];
				tDeathDirection[2] = tAVATAR_OBJECT1->mDATA.aAction.aLocation[2] - tAVATAR_OBJECT2->mDATA.aAction.aLocation[2];
				tDeathLength = sqrtf(tDeathDirection[0] * tDeathDirection[0] + tDeathDirection[2] * tDeathDirection[2]);
				if (tDeathLength < 1.0f)
				{
					tDeathDirection[0] = 0.0f;
					tDeathDirection[2] = 0.0f;
				}
				else
				{
					tDeathDirection[0] /= tDeathLength;
					tDeathDirection[2] /= tDeathLength;
				}
				tAVATAR_OBJECT1->mDATA.aAction.aType = 0;
				tAVATAR_OBJECT1->mDATA.aAction.aSort = 12;
				tAVATAR_OBJECT1->mDATA.aAction.aFrame = 0.0f;
				tAVATAR_OBJECT1->mDATA.aAction.aTargetLocation[0] = tDeathDirection[0];
				tAVATAR_OBJECT1->mDATA.aAction.aTargetLocation[1] = 0.0f;
				tAVATAR_OBJECT1->mDATA.aAction.aTargetLocation[2] = tDeathDirection[2];
				tAVATAR_OBJECT1->mDATA.aAction.aFront = mUTIL.GetYAngle(tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], tAVATAR_OBJECT1->mDATA.aAction.aLocation[2], tAVATAR_OBJECT2->mDATA.aAction.aLocation[0], tAVATAR_OBJECT2->mDATA.aAction.aLocation[2]);
				tAVATAR_OBJECT1->mDATA.aAction.aTargetFront = tAVATAR_OBJECT1->mDATA.aAction.aFront;
				tAVATAR_OBJECT1->mDATA.aAction.aSkillNumber = 1;
				mTRANSFER.B_AVATAR_ACTION_RECV(tAttackInfo->mServerIndex1, tAVATAR_OBJECT1->mUniqueNumber, &tAVATAR_OBJECT1->mDATA, 1);
				mUSER[tAttackInfo->mServerIndex1].Send(TRUE, (char *)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, tAttackInfo->mServerIndex1, false);
				tAVATAR_OBJECT1->ProcessForDeath();
				//------------------------//
				//------------------------//
				//------------------------//
			}
			return;
		}
	}
	
	if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0] > 0 && tShieldSort != 0)
	{
		if (tDamageValue > mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0])
		{
			tShieldDamageValue = mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0];
		}
		else
		{
			tShieldDamageValue = tDamageValue;
		}
		mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0] -= tShieldDamageValue;
		if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0] < 1)
		{
			mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0] = 0;
			mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][1] = 0;
		}
		tAVATAR_OBJECT2->mDATA.aEffectValueForView[tShieldSort] -= tShieldDamageValue;
		if (tAVATAR_OBJECT2->mDATA.aEffectValueForView[tShieldSort] < 1)
		{
			tAVATAR_OBJECT2->mDATA.aEffectValueForView[tShieldSort] = 0;
		}
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(tAttackInfo->mServerIndex2, tAttackInfo->mUniqueNumber2, tShieldType, tShieldDamageValue, 0, 0);
		mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT2->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		tDamageValue -= tShieldDamageValue;
	}
	
	tElementAttackPower = tAVATAR_OBJECT1->GetElementAttackPower();
	switch (tAttackInfo->mAttackActionValue1)
	{
	case 3:
		tElementAttackPowerUpRatio = mSKILL.ReturnSkillValue(tAttackInfo->mAttackActionValue2, tAttackInfo->mAttackActionValue3, 8);
		if (tElementAttackPowerUpRatio > 0.0f)
		{
			tElementAttackPower = (int)((float)tElementAttackPower * (tElementAttackPowerUpRatio + 100.0f) * 0.01f);
		}
		break;
	}

	tElementDefensePower = tAVATAR_OBJECT2->GetElementDefensePower();
	if (tElementAttackPower > tElementDefensePower)
	{
		tDamageValue += (tElementAttackPower - tElementDefensePower);
		tAttackInfo->mAttackElementDamage = tElementAttackPower - tElementDefensePower;
	}
	else
	{
		tAttackInfo->mAttackElementDamage = 0;
	}
	tAttackInfo->mAttackResultValue = 1 + mUSER[tAttackInfo->mServerIndex1].mAvatarInfo.aEquip[7][0];
	tAttackInfo->mAttackViewDamageValue = tDamageValue;
	if (tAVATAR_OBJECT2->mDATA.aLifeValue < tDamageValue)
	{
		tDamageValue = tAVATAR_OBJECT2->mDATA.aLifeValue;
	}
	tAttackInfo->mAttackRealDamageValue = tDamageValue;

	mTRANSFER.B_PROCESS_ATTACK_RECV(tAttackInfo);
	mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
	tAVATAR_OBJECT2->mDATA.aLifeValue -= tDamageValue;
	if (tAVATAR_OBJECT2->mDATA.aLifeValue > 0)
	{
		return;
	}
	//------------------------//
	//PROCESS_FOR_AVATAR_DEATH//
	//------------------------//
	tDeathDirection[0] = tAVATAR_OBJECT2->mDATA.aAction.aLocation[0] - tAVATAR_OBJECT1->mDATA.aAction.aLocation[0];
	tDeathDirection[2] = tAVATAR_OBJECT2->mDATA.aAction.aLocation[2] - tAVATAR_OBJECT1->mDATA.aAction.aLocation[2];
	tDeathLength = sqrtf(tDeathDirection[0] * tDeathDirection[0] + tDeathDirection[2] * tDeathDirection[2]);
	if (tDeathLength < 1.0f)
	{
		tDeathDirection[0] = 0.0f;
		tDeathDirection[2] = 0.0f;
	}
	else
	{
		tDeathDirection[0] /= tDeathLength;
		tDeathDirection[2] /= tDeathLength;
	}
	tAVATAR_OBJECT2->mDATA.aAction.aType = 0;
	tAVATAR_OBJECT2->mDATA.aAction.aSort = 12;
	tAVATAR_OBJECT2->mDATA.aAction.aFrame = 0.0f;
	tAVATAR_OBJECT2->mDATA.aAction.aTargetLocation[0] = tDeathDirection[0];
	tAVATAR_OBJECT2->mDATA.aAction.aTargetLocation[1] = 0.0f;
	tAVATAR_OBJECT2->mDATA.aAction.aTargetLocation[2] = tDeathDirection[2];
	tAVATAR_OBJECT2->mDATA.aAction.aFront = mUTIL.GetYAngle(tAVATAR_OBJECT2->mDATA.aAction.aLocation[0], tAVATAR_OBJECT2->mDATA.aAction.aLocation[2], tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], tAVATAR_OBJECT1->mDATA.aAction.aLocation[2]);
	tAVATAR_OBJECT2->mDATA.aAction.aTargetFront = tAVATAR_OBJECT2->mDATA.aAction.aFront;
	tAVATAR_OBJECT2->mDATA.aAction.aSkillNumber = 2;
	mTRANSFER.B_AVATAR_ACTION_RECV(tAttackInfo->mServerIndex2, tAVATAR_OBJECT2->mUniqueNumber, &tAVATAR_OBJECT2->mDATA, 1);
	mUSER[tAttackInfo->mServerIndex2].Send(TRUE, (char *)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT2->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, tAttackInfo->mServerIndex2, false);
	tAVATAR_OBJECT2->ProcessForDeath();
	//------------------------//
	//------------------------//
	//------------------------//
}
//PROCESS_ATTACK_02
void MyGame::ProcessAttack02(int tUserIndex, ATTACK_FOR_PROTOCOL *tAttackInfo)
{
	unsigned int tRandom = 0;
	int index01;
	int tShieldSort = 9;
	int tShieldType = 5;
	int tEffectValueState[MAX_AVATAR_EFFECT_SORT_NUM];
	if ((tAttackInfo->mServerIndex1 != tUserIndex) || (tAttackInfo->mUniqueNumber1 != mAVATAR_OBJECT[tUserIndex].mUniqueNumber))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

		return;
	}
	tAVATAR_OBJECT1 = &mAVATAR_OBJECT[tAttackInfo->mServerIndex1];
	tAVATAR_OBJECT1->mDATA.aAction.aLocation[0] = tAttackInfo->mSenderLocation[0];
	tAVATAR_OBJECT1->mDATA.aAction.aLocation[1] = tAttackInfo->mSenderLocation[1];
	tAVATAR_OBJECT1->mDATA.aAction.aLocation[2] = tAttackInfo->mSenderLocation[2];
	tAVATAR_OBJECT1->SetSpaceIndex();
	if ((tAttackInfo->mServerIndex2 < 0) || (tAttackInfo->mServerIndex2 > (mSERVER.mMAX_USER_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tAVATAR_OBJECT2 = &mAVATAR_OBJECT[tAttackInfo->mServerIndex2];
	if ((!tAVATAR_OBJECT2->mCheckValidState) || (tAVATAR_OBJECT2->mUniqueNumber != tAttackInfo->mUniqueNumber2))
	{
		return;
	}
	if (tAVATAR_OBJECT1->mDATA.aLifeValue < 1)
	{
		return;
	}
	if ((mTickCount - mUSER[tAttackInfo->mServerIndex1].mTickCountFor01SecondForProtect) < PROTECT_TICK)
	{
		return;
	}
	if (mUSER[tAttackInfo->mServerIndex2].mMoveZoneResult == 1)
	{
		return;
	}
	if (tAVATAR_OBJECT2->mDATA.aLifeValue < 1)
	{
		return;
	}
	if (tAVATAR_OBJECT2->mDATA.aPShopState == 1)
	{
		return;
	}
	if (!CheckPossibleAttackTarget(1, tAVATAR_OBJECT2->mDATA.aAction.aSort))
	{
		return;
	}
	if ((mTickCount - mUSER[tAttackInfo->mServerIndex2].mTickCountFor01SecondForProtect) < PROTECT_TICK)
	{
		return;
	}
	if ((mZONEMAININFO.ReturnZoneTribeInfo2(mSERVER_INFO.mServerNumber) == 0) || (tAVATAR_OBJECT1->mDATA.aTribe == tAVATAR_OBJECT2->mDATA.aTribe) || (tAVATAR_OBJECT2->mDATA.aTribe == ReturnAllianceTribe(tAVATAR_OBJECT1->mDATA.aTribe)))
	{
		return;
	}
	if (1 == tAVATAR_OBJECT2->mGod) {
		return;
	}
	if (1 == mUSER[tUserIndex].mAuthInfo.AttackFlag) {
		return;
	}
	if (1 == mUSER[tAttackInfo->mServerIndex2].mAuthInfo.AttackFlag) {
		return;
	}
	mAVATAR_OBJECT[tAttackInfo->mServerIndex2].SetBasicAbilityFromEquip();
	mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
	//Albız
	tChargingValue = mUSER[tAttackInfo->mServerIndex1].mEffectValue[8][0];
	if (mUSER[tAttackInfo->mServerIndex1].mEffectValue[8][0] > 0)
	{
		mUSER[tAttackInfo->mServerIndex1].mEffectValue[8][0] = 0;
		mUSER[tAttackInfo->mServerIndex1].mEffectValue[8][1] = 0;
		tAVATAR_OBJECT1->mDATA.aEffectValueForView[8] = 0;
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(tAttackInfo->mServerIndex1, tAttackInfo->mUniqueNumber1, 2, 0, 0, 0);
		mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
	}

	switch (tAttackInfo->mAttackActionValue1)
	{
	case 1:
		tAttackSuccessValue = tAVATAR_OBJECT1->GetAttackSuccess();
		break;
	case 2:
		if (mUSER[tUserIndex].mCheckMaxAttackPacketNum == 1)
		{
			if ((tAVATAR_OBJECT1->mDATA.aAction.aSkillNumber != tAttackInfo->mAttackActionValue2) || ((tAVATAR_OBJECT1->mDATA.aAction.aSkillGradeNum1 + tAVATAR_OBJECT1->mDATA.aAction.aSkillGradeNum2) != tAttackInfo->mAttackActionValue3))
			{
				return;
			}
		}
		tAttackSuccessValue = tAVATAR_OBJECT1->GetAttackSuccess();
		break;
	default:
		return;
	}
	if (tAttackSuccessValue < 1)
	{
		return;
	}
	tAttackBlockValue = tAVATAR_OBJECT2->GetAttackBlock();
	if (tAttackBlockValue > 0)
	{
		if (tAttackSuccessValue > tAttackBlockValue)
		{
			tAttackDetermineValue = (int)(70.0f + (((float)tAttackSuccessValue / (float)tAttackBlockValue) - 1.0f) * 25.0f);
			if (tAttackDetermineValue > 99)
			{
				tAttackDetermineValue = 99;
			}
		}
		else
		{
			tAttackDetermineValue = (int)(70.0f - (((float)tAttackBlockValue / (float)tAttackSuccessValue) - 1.0f) * 25.0f);
			if (tAttackDetermineValue < 1)
			{
				tAttackDetermineValue = 1;
			}
		}
		tRandom = rand();
		if ((tRandom % 100) >= tAttackDetermineValue)
		{
			tAttackInfo->mAttackResultValue = 0;
			mTRANSFER.B_PROCESS_ATTACK_RECV(tAttackInfo);
			mUSER[tAttackInfo->mServerIndex1].Send(TRUE, (char *)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
	}

	//Buf Silme
	
	if (tAVATAR_OBJECT1->SpritEruption > 0)
	{

		for (index01 = 0; index01 < MAX_AVATAR_EFFECT_SORT_NUM; index01++)
		{
			tEffectValueState[index01] = 0;
			if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[index01][0] > 0)
			{
				tRandom = rand() % 2;
				if (tRandom != 1)
					continue;
			}
			tRandom = rand() % 10000;

			if (tRandom < (tAVATAR_OBJECT1->SpritEruption - tAVATAR_OBJECT2->SoketDayanik))
			{
				mUSER[tAttackInfo->mServerIndex2].mEffectValue[index01][0] = 0;
				mUSER[tAttackInfo->mServerIndex2].mEffectValue[index01][1] = 0;
				tAVATAR_OBJECT2->mDATA.aEffectValueForView[index01] = 0;
				tEffectValueState[index01] = 2;
				mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(tAttackInfo->mServerIndex2, tAttackInfo->mUniqueNumber2, mUSER[tAttackInfo->mServerIndex2].mEffectValue, &tEffectValueState[0]);
				mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT2->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
				goto LABEL_ATAK;
				return;
			}
		}
	}
	//Saldırı Hızı ve Hareket Hızı Azaltma 
	
	if (tAVATAR_OBJECT1->Glaciation > 0)
	{
		tRandom = rand();

		if ((tRandom % 10000) < (tAVATAR_OBJECT1->Glaciation - tAVATAR_OBJECT2->SoketDayanik))
		{
			mUSER[tAttackInfo->mServerIndex2].mEffectValue[25][0] = 50;
			mUSER[tAttackInfo->mServerIndex2].mEffectValue[25][1] = 3;
			tAVATAR_OBJECT2->mDATA.aEffectValueForView[25] = 50;
			mTRANSFER.B_AVATAR_CHANGE_INFO_1(tAttackInfo->mServerIndex2, tAttackInfo->mUniqueNumber2, 2, 0, 0, 0);
			mUSER[tAttackInfo->mServerIndex2].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT2->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			goto LABEL_ATAK;
			return;
		}
	}
	//Kanama
	
	if (tAVATAR_OBJECT1->PoisonAttack > 0)
	{
		tRandom = rand();

		if ((tRandom % 10000) < (tAVATAR_OBJECT1->PoisonAttack - tAVATAR_OBJECT2->SoketDayanik))
		{
			mUSER[tAttackInfo->mServerIndex2].mEffectValue[28][0] = 5;
			mUSER[tAttackInfo->mServerIndex2].mEffectValue[28][1] = 10;
			tAVATAR_OBJECT2->mDATA.aEffectValueForView[28] = 5;
			mTRANSFER.B_AVATAR_CHANGE_INFO_1(tAttackInfo->mServerIndex2, tAttackInfo->mUniqueNumber2, 2, 0, 0, 0);
			mUSER[tAttackInfo->mServerIndex2].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT2->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			goto LABEL_ATAK;
			return;
		}
	}
	//ShadowStrike
	
	if (tAVATAR_OBJECT1->ShadowStrike > 0)
	{
		tRandom = rand();

		if ((tRandom % 20000) < (tAVATAR_OBJECT1->ShadowStrike - tAVATAR_OBJECT2->SoketDayanik))
		{
			mUSER[tAttackInfo->mServerIndex2].mEffectValue[19][0] = 5;
			mUSER[tAttackInfo->mServerIndex2].mEffectValue[19][1] = 3;
			tAVATAR_OBJECT2->mDATA.aEffectValueForView[19] = 5;
			mTRANSFER.B_AVATAR_CHANGE_INFO_1(tAttackInfo->mServerIndex2, tAttackInfo->mUniqueNumber2, 2, 0, 0, 0);
			mUSER[tAttackInfo->mServerIndex2].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT2->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			mAVATAR_OBJECT[tAttackInfo->mServerIndex2].mCheckPossibleEatPotion = FALSE;
			goto LABEL_ATAK;
			return;
		}
	}
	
	//Stun Atma
	if (tAVATAR_OBJECT1->TouchOfDeath > 0)
	{
		tRandom = rand();

		if ((tRandom % 10000) < (tAVATAR_OBJECT1->TouchOfDeath - tAVATAR_OBJECT2->SoketDayanik))
		{
			tAVATAR_OBJECT2->mDATA.aAction.aType = 0;
			tAVATAR_OBJECT2->mDATA.aAction.aSort = 11;
			tAVATAR_OBJECT2->mDATA.aAction.aFrame = 0.0f;
			tAVATAR_OBJECT2->mDATA.aAction.aSkillValue = 3;
			mTRANSFER.B_AVATAR_ACTION_RECV(tAttackInfo->mServerIndex2, tAttackInfo->mUniqueNumber2, &tAVATAR_OBJECT2->mDATA, 1);
			mUSER[tAttackInfo->mServerIndex2].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT2->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			goto LABEL_ATAK;
			return;
		}
	}

LABEL_ATAK:
	switch (tAttackInfo->mAttackActionValue1)
	{
	case 1:
		tAttackPowerValue = tAVATAR_OBJECT1->GetAttackPower();
		break;
	case 2:
		tAttackPowerValue = tAVATAR_OBJECT1->GetAttackPower();
		tAttackPowerUpRatio = mSKILL.ReturnSkillValue(tAttackInfo->mAttackActionValue2, tAttackInfo->mAttackActionValue3, 7);
		if (tAttackPowerUpRatio > 0.0f)
		{
			tAttackPowerValue = (int)((float)tAttackPowerValue * (tAttackPowerUpRatio + 100.0f) * 0.01f);
		}
		break;
	}
	// @ Tribe Formation Skill @
	//--------//
	//žÍ°øÁø¹ý//
	//--------//
	
	if (mWorldInfo.mTribeMasterCallAbility[tAVATAR_OBJECT1->mDATA.aTribe] == 1)
	{
		tAttackPowerValue = (int)((float)tAttackPowerValue * 1.1f);
	}
	//--------//
	//--------//
	//--------//
	// @
	tDefensePowerValue = tAVATAR_OBJECT2->GetDefensePower();
	// @ Tribe Formation Skill @
	//--------//
	//Ã¶º®Áø¹ý//
	//--------//
	
	if (mWorldInfo.mTribeMasterCallAbility[tAVATAR_OBJECT2->mDATA.aTribe] == 2)
	{
		tDefensePowerValue = (int)((float)tDefensePowerValue * 1.1f);
	}
	//Defans Azaltan Soket
	tRandom = rand();
	if ((tRandom % 10000) < (tAVATAR_OBJECT1->StrongBlow - tAVATAR_OBJECT2->SoketDayanik))
	{
		tDefensePowerValue = (int)((float)tDefensePowerValue * 0.5f);
	}
	//--------//
	//--------//
	//--------//
	// @
	tDamageValue = tAttackPowerValue - tDefensePowerValue;
	if (tDamageValue < 1)
	{
		tDamageValue = 1;
	}
	if (tChargingValue > 0)
	{
		tDamageValue = (int)((float)(tDamageValue * (tChargingValue + 100)) * 0.01f);
	}
	tRandom = rand();
	if ((tRandom % 2) == 0)
	{
		tRandom = rand();
		tDamageValue += (int)((float)(tDamageValue * (tRandom % 11)) * 0.01f);
	}
	else
	{
		tRandom = rand();
		tDamageValue -= (int)((float)(tDamageValue * (tRandom % 11)) * 0.01f);
	}
	if (tDamageValue < tMinDamageValueWithAvatar)
	{
		tDamageValue = tMinDamageValueWithAvatar;
	}
	tAttackInfo->mAttackCriticalExist = 0;


	switch (tAttackInfo->mAttackActionValue1)
	{
	case 1:
		// @ Tribe Formation Skill @
		//-----------------//
		//ÀÏ°ÝÁø¹ý_°­º®Áø¹ý//
		//-----------------//
		if ((mWorldInfo.mTribeMasterCallAbility[tAVATAR_OBJECT1->mDATA.aTribe] != 3) && (mWorldInfo.mTribeMasterCallAbility[tAVATAR_OBJECT2->mDATA.aTribe] != 4))
		{
			tRandom = rand();
			if ((tRandom % 100) < getCriticalAttackDefValue(tAVATAR_OBJECT1, tAVATAR_OBJECT2))
			{
				tDamageValue *= 2;
				tAttackInfo->mAttackCriticalExist = 1;
			}
		}
		else if ((mWorldInfo.mTribeMasterCallAbility[tAVATAR_OBJECT1->mDATA.aTribe] == 3) && (mWorldInfo.mTribeMasterCallAbility[tAVATAR_OBJECT2->mDATA.aTribe] != 4))
		{
			tRandom = rand();
			if ((tRandom % 100) < (getCriticalAttackDefValue(tAVATAR_OBJECT1, tAVATAR_OBJECT2) + 5))
			{
				tDamageValue *= 2;
				tAttackInfo->mAttackCriticalExist = 1;
			}
		}
		else if ((mWorldInfo.mTribeMasterCallAbility[tAVATAR_OBJECT1->mDATA.aTribe] != 3) && (mWorldInfo.mTribeMasterCallAbility[tAVATAR_OBJECT2->mDATA.aTribe] == 4))
		{
			tRandom = rand();
			if ((tRandom % 100) < (getCriticalAttackDefValue(tAVATAR_OBJECT1, tAVATAR_OBJECT2) - 5))
			{
				tDamageValue *= 2;
				tAttackInfo->mAttackCriticalExist = 1;
			}
		}
		else if ((mWorldInfo.mTribeMasterCallAbility[tAVATAR_OBJECT1->mDATA.aTribe] == 3) && (mWorldInfo.mTribeMasterCallAbility[tAVATAR_OBJECT2->mDATA.aTribe] == 4))
		{
			tRandom = rand();
			if ((tRandom % 100) < getCriticalAttackDefValue(tAVATAR_OBJECT1, tAVATAR_OBJECT2))
			{
				tDamageValue *= 2;
				tAttackInfo->mAttackCriticalExist = 1;
			}
		}
		else;
		//-----------------//
		//-----------------//
		//-----------------//
		// @
		break;
	case 2:
		if (tAttackInfo->mAttackActionValue2 == 78)
		{
			break;
		}
		switch (mSKILL.ReturnAttackType(tAttackInfo->mAttackActionValue2))
		{
		case 2:
		case 5:
			// @ Tribe Formation Skill @
			//-----------------//
			//ÀÏ°ÝÁø¹ý_°­º®Áø¹ý//
			//-----------------//
		
			if ((mWorldInfo.mTribeMasterCallAbility[tAVATAR_OBJECT1->mDATA.aTribe] != 3) && (mWorldInfo.mTribeMasterCallAbility[tAVATAR_OBJECT2->mDATA.aTribe] != 4))
			{
				tRandom = rand();
				if ((tRandom % 100) < getCriticalAttackDefValue(tAVATAR_OBJECT1, tAVATAR_OBJECT2))
				{
					tDamageValue *= 2;
					tAttackInfo->mAttackCriticalExist = 1;
				}
			}
			else if ((mWorldInfo.mTribeMasterCallAbility[tAVATAR_OBJECT1->mDATA.aTribe] == 3) && (mWorldInfo.mTribeMasterCallAbility[tAVATAR_OBJECT2->mDATA.aTribe] != 4))
			{
				tRandom = rand();
				if ((tRandom % 100) < (getCriticalAttackDefValue(tAVATAR_OBJECT1, tAVATAR_OBJECT2) + 5))
				{
					tDamageValue *= 2;
					tAttackInfo->mAttackCriticalExist = 1;
				}
			}
			else if ((mWorldInfo.mTribeMasterCallAbility[tAVATAR_OBJECT1->mDATA.aTribe] != 3) && (mWorldInfo.mTribeMasterCallAbility[tAVATAR_OBJECT2->mDATA.aTribe] == 4))
			{
				tRandom = rand();
				if ((tRandom % 100) < (getCriticalAttackDefValue(tAVATAR_OBJECT1, tAVATAR_OBJECT2) - 5))
				{
					tDamageValue *= 2;
					tAttackInfo->mAttackCriticalExist = 1;
				}
			}
			else if ((mWorldInfo.mTribeMasterCallAbility[tAVATAR_OBJECT1->mDATA.aTribe] == 3) && (mWorldInfo.mTribeMasterCallAbility[tAVATAR_OBJECT2->mDATA.aTribe] == 4))
			{
				tRandom = rand();
				if ((tRandom % 100) < getCriticalAttackDefValue(tAVATAR_OBJECT1, tAVATAR_OBJECT2))
				{
					tDamageValue *= 2;
					tAttackInfo->mAttackCriticalExist = 1;
				}
			}
			else;
			//-----------------//
			//-----------------//
			//-----------------//
			// @
			break;
		}
		break;
	}
	tDamageValue /= tMinDamageValueWithAvatar;

	//Demir Ten Seçilimi
	if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[9][0] > 0)
	{
		tShieldSort = 9;
		tShieldType = 5;
	}
	else if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[29][0] > 0)
	{
		tShieldSort = 29;
		tShieldType = 31;
	}
	else if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[30][0] > 0)
	{
		tShieldSort = 30;
		tShieldType = 32;
	}
	else if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[31][0] > 0)
	{
		tShieldSort = 31;
		tShieldType = 33;
	}
	else if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[32][0] > 0)
	{
		tShieldSort = 32;
		tShieldType = 34;
	}
	else if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[33][0] > 0)
	{
		tShieldSort = 33;
		tShieldType = 35;
	}
	else if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[34][0] > 0)
	{
		tShieldSort = 34;
		tShieldType = 36;
	}

	//Zihin Yayma
	if (mUSER[tAttackInfo->mServerIndex1].mEffectValue[14][0] > 0)
	{
		tRandom = rand();
		if ((tRandom % 2000) < mUSER[tAttackInfo->mServerIndex1].mEffectValue[14][0])
		{
			mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0] = 0;
			mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][1] = 0;
			tAVATAR_OBJECT2->mDATA.aEffectValueForView[tShieldSort] = 0;
			mTRANSFER.B_AVATAR_CHANGE_INFO_1(tAttackInfo->mServerIndex2, tAttackInfo->mUniqueNumber2, 3, 0, 0, 0);
			mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT2->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		}
	}
	//Yansıma
	if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[12][0] > 0)
	{
		tReturnDamageProbability = mUSER[tAttackInfo->mServerIndex2].mEffectValue[12][0] * 2;//50
		if (tAVATAR_OBJECT1->mDATA.aLevel1 > tAVATAR_OBJECT2->mDATA.aLevel1)
		{
			tReturnDamageProbability -= ((tAVATAR_OBJECT1->mDATA.aLevel1 - tAVATAR_OBJECT2->mDATA.aLevel1) * 3);
		}
		tRandom = rand();
		if (tReturnDamageProbability < 0) {
			tReturnDamageProbability = 0;
		}
		if ((tRandom % 5000) < tReturnDamageProbability)
		{
			tRandom = rand();
			tReturnDamageValue = (int)((float)(tDamageValue * (100 + tRandom % 31)) * 0.01f);
			mTRANSFER.B_AVATAR_CHANGE_INFO_1(tAttackInfo->mServerIndex1, tAttackInfo->mUniqueNumber1, 4, tReturnDamageValue, 0, 0);
			mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			tAVATAR_OBJECT1->mDATA.aLifeValue -= tReturnDamageValue;
			if (tAVATAR_OBJECT1->mDATA.aLifeValue < 1)
			{
				tAVATAR_OBJECT1->mDATA.aLifeValue = 0;
				//------------------------//
				//PROCESS_FOR_AVATAR_DEATH//
				//------------------------//
				tDeathDirection[0] = tAVATAR_OBJECT1->mDATA.aAction.aLocation[0] - tAVATAR_OBJECT2->mDATA.aAction.aLocation[0];
				tDeathDirection[2] = tAVATAR_OBJECT1->mDATA.aAction.aLocation[2] - tAVATAR_OBJECT2->mDATA.aAction.aLocation[2];
				tDeathLength = sqrtf(tDeathDirection[0] * tDeathDirection[0] + tDeathDirection[2] * tDeathDirection[2]);
				if (tDeathLength < 1.0f)
				{
					tDeathDirection[0] = 0.0f;
					tDeathDirection[2] = 0.0f;
				}
				else
				{
					tDeathDirection[0] /= tDeathLength;
					tDeathDirection[2] /= tDeathLength;
				}
				tAVATAR_OBJECT1->mDATA.aAction.aType = 0;
				tAVATAR_OBJECT1->mDATA.aAction.aSort = 12;
				tAVATAR_OBJECT1->mDATA.aAction.aFrame = 0.0f;
				tAVATAR_OBJECT1->mDATA.aAction.aTargetLocation[0] = tDeathDirection[0];
				tAVATAR_OBJECT1->mDATA.aAction.aTargetLocation[1] = 0.0f;
				tAVATAR_OBJECT1->mDATA.aAction.aTargetLocation[2] = tDeathDirection[2];
				tAVATAR_OBJECT1->mDATA.aAction.aFront = mUTIL.GetYAngle(tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], tAVATAR_OBJECT1->mDATA.aAction.aLocation[2], tAVATAR_OBJECT2->mDATA.aAction.aLocation[0], tAVATAR_OBJECT2->mDATA.aAction.aLocation[2]);
				tAVATAR_OBJECT1->mDATA.aAction.aTargetFront = tAVATAR_OBJECT1->mDATA.aAction.aFront;
				tAVATAR_OBJECT1->mDATA.aAction.aSkillNumber = 3;
				mTRANSFER.B_AVATAR_ACTION_RECV(tAttackInfo->mServerIndex1, tAVATAR_OBJECT1->mUniqueNumber, &tAVATAR_OBJECT1->mDATA, 1);
				mUSER[tAttackInfo->mServerIndex1].Send(TRUE, (char *)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, tAttackInfo->mServerIndex1, false);
				tAVATAR_OBJECT1->ProcessForDeath();
				//------------------------//
				//------------------------//
				//------------------------//
				mUTIL.ProcessForKillOtherTribe(tAttackInfo->mServerIndex2, tAttackInfo->mServerIndex1, mSERVER_INFO.mServerNumber);
			}
			return;
		}
	}
	//Demir Ten
	if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0] > 0 && tShieldSort !=0)
	{
		if (tDamageValue > mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0])
		{
			tShieldDamageValue = mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0];
		}
		else
		{
			tShieldDamageValue = tDamageValue;
		}
		mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0] -= tShieldDamageValue;
		if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0] < 1)
		{
			mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0] = 0;
			mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][1] = 0;
		}
		tAVATAR_OBJECT2->mDATA.aEffectValueForView[tShieldSort] -= tShieldDamageValue;
		if (tAVATAR_OBJECT2->mDATA.aEffectValueForView[tShieldSort] < 1)
		{
			tAVATAR_OBJECT2->mDATA.aEffectValueForView[tShieldSort] = 0;
		}
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(tAttackInfo->mServerIndex2, tAttackInfo->mUniqueNumber2, tShieldType, tShieldDamageValue, 0, 0);
		mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT2->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		tDamageValue -= tShieldDamageValue;
	}
	//Element Atak
	tElementAttackPower = tAVATAR_OBJECT1->GetElementAttackPower();
	switch (tAttackInfo->mAttackActionValue1)
	{
	case 2:
		tElementAttackPowerUpRatio = mSKILL.ReturnSkillValue(tAttackInfo->mAttackActionValue2, tAttackInfo->mAttackActionValue3, 8);
		if (tElementAttackPowerUpRatio > 0.0f)
		{
			tElementAttackPower = (int)((float)tElementAttackPower * (tElementAttackPowerUpRatio + 100.0f) * 0.01f);
		}
		break;
	}
	//Elemen Defans
	tElementDefensePower = tAVATAR_OBJECT2->GetElementDefensePower();
	if (tElementAttackPower > tElementDefensePower)
	{
		tDamageValue += (tElementAttackPower - tElementDefensePower);
		tAttackInfo->mAttackElementDamage = tElementAttackPower - tElementDefensePower;
	}
	else
	{
		tAttackInfo->mAttackElementDamage = 0;
	}
	tAttackInfo->mAttackResultValue = 1 + mUSER[tAttackInfo->mServerIndex1].mAvatarInfo.aEquip[7][0];
	tAttackInfo->mAttackViewDamageValue = tDamageValue;
	if (tAVATAR_OBJECT2->mDATA.aLifeValue < tDamageValue)
	{
		tDamageValue = tAVATAR_OBJECT2->mDATA.aLifeValue;
	}
	tAttackInfo->mAttackRealDamageValue = tDamageValue;

	mTRANSFER.B_PROCESS_ATTACK_RECV(tAttackInfo);
	mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
	tAVATAR_OBJECT2->mDATA.aLifeValue -= tDamageValue;
	if (tAVATAR_OBJECT2->mDATA.aLifeValue > 0)
	{
		return;
	}
	//------------------------//
	//PROCESS_FOR_AVATAR_DEATH//
	//------------------------//
	tDeathDirection[0] = tAVATAR_OBJECT2->mDATA.aAction.aLocation[0] - tAVATAR_OBJECT1->mDATA.aAction.aLocation[0];
	tDeathDirection[2] = tAVATAR_OBJECT2->mDATA.aAction.aLocation[2] - tAVATAR_OBJECT1->mDATA.aAction.aLocation[2];
	tDeathLength = sqrtf(tDeathDirection[0] * tDeathDirection[0] + tDeathDirection[2] * tDeathDirection[2]);
	if (tDeathLength < 1.0f)
	{
		tDeathDirection[0] = 0.0f;
		tDeathDirection[2] = 0.0f;
	}
	else
	{
		tDeathDirection[0] /= tDeathLength;
		tDeathDirection[2] /= tDeathLength;
	}
	tAVATAR_OBJECT2->mDATA.aAction.aType = 0;
	tAVATAR_OBJECT2->mDATA.aAction.aSort = 12;
	tAVATAR_OBJECT2->mDATA.aAction.aFrame = 0.0f;
	tAVATAR_OBJECT2->mDATA.aAction.aTargetLocation[0] = tDeathDirection[0];
	tAVATAR_OBJECT2->mDATA.aAction.aTargetLocation[1] = 0.0f;
	tAVATAR_OBJECT2->mDATA.aAction.aTargetLocation[2] = tDeathDirection[2];
	tAVATAR_OBJECT2->mDATA.aAction.aFront = mUTIL.GetYAngle(tAVATAR_OBJECT2->mDATA.aAction.aLocation[0], tAVATAR_OBJECT2->mDATA.aAction.aLocation[2], tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], tAVATAR_OBJECT1->mDATA.aAction.aLocation[2]);
	tAVATAR_OBJECT2->mDATA.aAction.aTargetFront = tAVATAR_OBJECT2->mDATA.aAction.aFront;
	tAVATAR_OBJECT2->mDATA.aAction.aSkillNumber = 4;
	mTRANSFER.B_AVATAR_ACTION_RECV(tAttackInfo->mServerIndex2, tAVATAR_OBJECT2->mUniqueNumber, &tAVATAR_OBJECT2->mDATA, 1);
	mUSER[tAttackInfo->mServerIndex2].Send(TRUE, (char *)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT2->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, tAttackInfo->mServerIndex2, false);
	tAVATAR_OBJECT2->ProcessForDeath();
	//------------------------//
	//------------------------//
	//------------------------//
	mUTIL.ProcessForKillOtherTribe(tAttackInfo->mServerIndex1, tAttackInfo->mServerIndex2, mSERVER_INFO.mServerNumber);
}
//PROCESS_ATTACK_03
void MyGame::ProcessAttack03(int tUserIndex, ATTACK_FOR_PROTOCOL *tAttackInfo)
{
	//-----------------------------------------------------------------//
	//[01].ÀÏ¹Ý,[02].ŒºŒ®,[03].ŒöÈ£ºñ,[04].µ¿žÍŒ®,[05].ŒöÈ£Œ®,[06].Œ®Â÷//
	//-----------------------------------------------------------------//

	int index01;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	int tAllianceTribe;
	int tTribeSymbolIndex;
	int tAllianceStoneIndex;
	int tWhoAttackMonster;
	int tSelectAvatarIndex;
	int tGainValue;
	int tTotalPartyNum, iTribe = 0;;
	int tPartyUserIndex[MAX_PARTY_AVATAR_NUM];
	int tBonusGainGeneralExperience;
	int tPatExperience;
	unsigned int tRandom = 0;


	if ((tAttackInfo->mServerIndex1 != tUserIndex) || (tAttackInfo->mUniqueNumber1 != mAVATAR_OBJECT[tUserIndex].mUniqueNumber))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

		return;
	}
	tAVATAR_OBJECT1 = &mAVATAR_OBJECT[tAttackInfo->mServerIndex1];
	tAVATAR_OBJECT1->mDATA.aAction.aLocation[0] = tAttackInfo->mSenderLocation[0];
	tAVATAR_OBJECT1->mDATA.aAction.aLocation[1] = tAttackInfo->mSenderLocation[1];
	tAVATAR_OBJECT1->mDATA.aAction.aLocation[2] = tAttackInfo->mSenderLocation[2];
	tAVATAR_OBJECT1->SetSpaceIndex();
	if ((tAttackInfo->mServerIndex2 < 0) || (tAttackInfo->mServerIndex2 > (MAX_MONSTER_OBJECT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (1 == mUSER[tUserIndex].mAuthInfo.AttackFlag) {
		return;
	}
	tMONSTER_OBJECT = &mMONSTER_OBJECT[tAttackInfo->mServerIndex2];
	if ((!tMONSTER_OBJECT->mCheckValidState) || (tMONSTER_OBJECT->mUniqueNumber != tAttackInfo->mUniqueNumber2))
	{
		return;
	}
	//------
	//Event monster
	if (890 == tMONSTER_OBJECT->mMONSTER_INFO->mIndex) {
		if (tAVATAR_OBJECT1->mDATA.aLevel1 > 112)
			return;
	}
	if (891 == tMONSTER_OBJECT->mMONSTER_INFO->mIndex) {
		if (tAVATAR_OBJECT1->mDATA.aLevel1 < 113)
			return;
	}
	if (1052 == tMONSTER_OBJECT->mMONSTER_INFO->mIndex) {
		if (tAVATAR_OBJECT1->mDATA.aLevel1 >= 15)
			return;
	}
	if (1053 == tMONSTER_OBJECT->mMONSTER_INFO->mIndex) {
		if (tAVATAR_OBJECT1->mDATA.aLevel1 >= 25)
			return;
	}
	//------
	if (tAVATAR_OBJECT1->mDATA.aLifeValue < 1)
	{
		return;
	}
	/* Mir */
	if ((mTickCount - mUSER[tAttackInfo->mServerIndex1].mTickCountFor01SecondForProtect) < PROTECT_TICK)
	{
		return;
	}
	/* Mir */
	if (tMONSTER_OBJECT->mDATA.mLifeValue < 1)
	{
		return;
	}
	if (!CheckPossibleAttackTarget(2, tMONSTER_OBJECT->mDATA.mAction.aSort))
	{
		return;
	}
	if ((::strlen(tMONSTER_OBJECT->mAvatarName) > 0) && (::strncmp(tMONSTER_OBJECT->mAvatarName, mUSER[tUserIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH) != 0))
	{
		// žóœºÅÍ ŒÒÀ¯ÀÚ°¡ ÁöÁ€µÇŸî ÀÖÀžžé ŒÒÀ¯ÀÚžž Åž°Ý °¡ŽÉ.
		return;
	}

	

	mUSER[tUserIndex].mAutoCheckCount = 0;
	float fHeight = ::abs((int)(tAVATAR_OBJECT1->mDATA.aAction.aLocation[1] - tMONSTER_OBJECT->mDATA.mAction.aLocation[1]));
	if (fHeight > 40) {
		//mGAMELOG.GL_659_AUTO_CHECK(tUserIndex, 1, fHeight);
		return;
	}

	//if(!mUTIL.CheckRAttackRange(tUserIndex, tAVATAR_OBJECT1->mDATA.aAction.aSkillNumber, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0]
	//__LogMgr()->Log("Monster Size : %3.3f\n", tMONSTER_OBJECT->mRadiusForSize); // ..... .... .. ..
#if 0
	if (!mUTIL.CheckRAttackRange(tUserIndex, tAttackInfo->mAttackActionValue2, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0]
		, &tMONSTER_OBJECT->mDATA.mAction.aLocation[0], 0.0f)) {
		return;
	}
#endif
	// # }
	if (!mUTIL.CheckRAttackRange(tUserIndex, tAttackInfo->mAttackActionValue2, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0]
		, &tMONSTER_OBJECT->mDATA.mAction.aLocation[0], tMONSTER_OBJECT->mRadiusForSize)) { // 0.0f)) {
		return;
	}

	//nova - to disable auto hunt on the map. currently set only for Ghost Valley.	
	if (mSERVER_INFO.mServerNumber == 38)
	{
		if (mAVATAR_OBJECT[tUserIndex].mDATA.BotOn == 1)
		{
			//sleep(1000);
			return;
		}
	}


	if (mSERVER_INFO.mServerNumber == 234 || mSERVER_INFO.mServerNumber == 235 || mSERVER_INFO.mServerNumber == 236 ||
		mSERVER_INFO.mServerNumber == 237 || mSERVER_INFO.mServerNumber == 238 || mSERVER_INFO.mServerNumber == 239 || mSERVER_INFO.mServerNumber == 240)
	{
		if (mSERVER_INFO.mServerNumber == 234)
		{
			if (mAVATAR_OBJECT[tUserIndex].mDATA.BotOn == 1)
			{
				return;
			}	
		}
		if (tAttackInfo->mAttackActionValue2 >= 112 && tAttackInfo->mAttackActionValue2 <= 120)//8th skilss
		{
			char tContent[MAX_CHAT_CONTENT_LENGTH];
			snprintf(tContent, 61, "You cannot use this skill in IoS Maps !");
			mTRANSFER.B_SECRET_CHAT_RECV(3, mSERVER_INFO.mServerNumber, "SYSTEM", &tContent[0], 1);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize, false);
			return;
		}
	}

	mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
	tChargingValue = mUSER[tAttackInfo->mServerIndex1].mEffectValue[8][0];
	if (mUSER[tAttackInfo->mServerIndex1].mEffectValue[8][0] > 0)
	{
		mUSER[tAttackInfo->mServerIndex1].mEffectValue[8][0] = 0;
		mUSER[tAttackInfo->mServerIndex1].mEffectValue[8][1] = 0;
		tAVATAR_OBJECT1->mDATA.aEffectValueForView[8] = 0;
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(tAttackInfo->mServerIndex1, tAttackInfo->mUniqueNumber1, 2, 0, 0, 0);
		mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
	}
	//-------------//
	//°ø°ÝÇã¿ë_°Ë»ç//
	//-------------//


	switch (tMONSTER_OBJECT->mSpecialSortNumber)
	{
	case 1:
		break;
	case 2:
		tAllianceTribe = ReturnAllianceTribe(tAVATAR_OBJECT1->mDATA.aTribe);
		switch (tMONSTER_OBJECT->mMONSTER_INFO->mSpecialType)
		{
		case 10:
			if (mGAME.CpTowerTribe == tAVATAR_OBJECT1->mDATA.aTribe)
			{
				return;
			}				
			if (mGAME.mCpTower.CpTowersAtakType[mGAME.CpTowerZoneIndex] == -1 )
			{
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				//Saldırıyor Duyurusu
				tTribeSymbolIndex = (mCpTower.CpTowers[CpTowerZoneIndex] % 100);
				tBroadcastInfoSort = 754;
				CopyMemory(&tBroadcastInfoData[0], &tTribeSymbolIndex, 4);
				CopyMemory(&tBroadcastInfoData[4], &tAVATAR_OBJECT1->mDATA.aTribe, 4);
				CopyMemory(&tBroadcastInfoData[8], &mSERVER_INFO.mServerNumber, 4);
				CopyMemory(&tBroadcastInfoData[12], &tAVATAR_OBJECT1->mDATA.aName[0], MAX_AVATAR_NAME_LENGTH);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				mGAME.CPTowerTypeBattleState = 3;
				//--------------//
			}
			break;
		case 11:
			if ((mWorldInfo.mTribeSymbolBattle == 0) || (mWorldInfo.mTribe1Symbol == tAVATAR_OBJECT1->mDATA.aTribe) || (mWorldInfo.mTribe1Symbol == tAllianceTribe))
			{
				return;
			}
			if (!tMONSTER_OBJECT->mCheckFirstAttackForTribeSymbol)
			{
				tMONSTER_OBJECT->mCheckFirstAttackForTribeSymbol = TRUE;
				tMONSTER_OBJECT->mFirstAttackTimeForTribeSymbol = GetTickCount();
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tTribeSymbolIndex = 0;
				tBroadcastInfoSort = 41;
				CopyMemory(&tBroadcastInfoData[0], &tTribeSymbolIndex, 4);
				iTribe = static_cast<int> (tAVATAR_OBJECT1->mDATA.aTribe);
				CopyMemory(&tBroadcastInfoData[4], &iTribe, 4);
				CopyMemory(&tBroadcastInfoData[8], &tAVATAR_OBJECT1->mDATA.aName[0], MAX_AVATAR_NAME_LENGTH);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
			}
			break;
		case 12:
			if ((mWorldInfo.mTribeSymbolBattle == 0) || (mWorldInfo.mTribe2Symbol == tAVATAR_OBJECT1->mDATA.aTribe) || (mWorldInfo.mTribe2Symbol == tAllianceTribe))
			{
				return;
			}
			if (!tMONSTER_OBJECT->mCheckFirstAttackForTribeSymbol)
			{
				tMONSTER_OBJECT->mCheckFirstAttackForTribeSymbol = TRUE;
				tMONSTER_OBJECT->mFirstAttackTimeForTribeSymbol = GetTickCount();
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tTribeSymbolIndex = 1;
				tBroadcastInfoSort = 41;
				CopyMemory(&tBroadcastInfoData[0], &tTribeSymbolIndex, 4);
				iTribe = static_cast<int> (tAVATAR_OBJECT1->mDATA.aTribe);
				CopyMemory(&tBroadcastInfoData[4], &iTribe, 4);
				CopyMemory(&tBroadcastInfoData[8], &tAVATAR_OBJECT1->mDATA.aName[0], MAX_AVATAR_NAME_LENGTH);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
			}
			break;
		case 13:
			if ((mWorldInfo.mTribeSymbolBattle == 0) || (mWorldInfo.mTribe3Symbol == tAVATAR_OBJECT1->mDATA.aTribe) || (mWorldInfo.mTribe3Symbol == tAllianceTribe))
			{
				return;
			}
			if (!tMONSTER_OBJECT->mCheckFirstAttackForTribeSymbol)
			{
				tMONSTER_OBJECT->mCheckFirstAttackForTribeSymbol = TRUE;
				tMONSTER_OBJECT->mFirstAttackTimeForTribeSymbol = GetTickCount();
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tTribeSymbolIndex = 2;
				tBroadcastInfoSort = 41;
				CopyMemory(&tBroadcastInfoData[0], &tTribeSymbolIndex, 4);
				iTribe = static_cast<int> (tAVATAR_OBJECT1->mDATA.aTribe);
				CopyMemory(&tBroadcastInfoData[4], &iTribe, 4);
				CopyMemory(&tBroadcastInfoData[8], &tAVATAR_OBJECT1->mDATA.aName[0], MAX_AVATAR_NAME_LENGTH);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
			}
			break;
		case 28:
			if ((mWorldInfo.mTribeSymbolBattle == 0) || (mWorldInfo.mTribe4Symbol == tAVATAR_OBJECT1->mDATA.aTribe) || (mWorldInfo.mTribe4Symbol == tAllianceTribe))
			{
				return;
			}
			if (!tMONSTER_OBJECT->mCheckFirstAttackForTribeSymbol)
			{
				tMONSTER_OBJECT->mCheckFirstAttackForTribeSymbol = TRUE;
				tMONSTER_OBJECT->mFirstAttackTimeForTribeSymbol = GetTickCount();
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tTribeSymbolIndex = 3;
				tBroadcastInfoSort = 41;
				CopyMemory(&tBroadcastInfoData[0], &tTribeSymbolIndex, 4);
				iTribe = static_cast<int> (tAVATAR_OBJECT1->mDATA.aTribe);
				CopyMemory(&tBroadcastInfoData[4], &iTribe, 4);
				CopyMemory(&tBroadcastInfoData[8], &tAVATAR_OBJECT1->mDATA.aName[0], MAX_AVATAR_NAME_LENGTH);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
			}
			break;
		case 14:
			if (mWorldInfo.mMonsterSymbol == tAVATAR_OBJECT1->mDATA.aTribe)
			{
				return;
			}
			if (tAllianceTribe != -1)
			{
				if (mWorldInfo.mMonsterSymbol == tAllianceTribe)
				{
					return;
				}
			}
			/** 2009. 10. 27 : Monster Symbol edit (wolf) */
			if (!bAttackMonsterSymbol)
			{
				return;
			}
			/** 2009. 10. 27 : Monster Symbol edit (wolf) */
			if (!tMONSTER_OBJECT->mCheckFirstAttackForTribeSymbol)
			{
				tMONSTER_OBJECT->mCheckFirstAttackForTribeSymbol = TRUE;
				tMONSTER_OBJECT->mFirstAttackTimeForTribeSymbol = GetTickCount();
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tTribeSymbolIndex = 4;
				tBroadcastInfoSort = 41;
				CopyMemory(&tBroadcastInfoData[0], &tTribeSymbolIndex, 4);
				iTribe = static_cast<int> (tAVATAR_OBJECT1->mDATA.aTribe);
				CopyMemory(&tBroadcastInfoData[4], &iTribe, 4);
				CopyMemory(&tBroadcastInfoData[8], &tAVATAR_OBJECT1->mDATA.aName[0], MAX_AVATAR_NAME_LENGTH);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
			}
			break;
		case 15:
			break;
		}
		break;
	case 3:
		switch (tMONSTER_OBJECT->mMONSTER_INFO->mSpecialType)
		{
		case 21:
			if ((tAVATAR_OBJECT1->mDATA.aTribe == 0) || (tAVATAR_OBJECT1->mDATA.aTribe == ReturnAllianceTribe(0)))
			{
				return;
			}
			break;
		case 22:
			if ((tAVATAR_OBJECT1->mDATA.aTribe == 1) || (tAVATAR_OBJECT1->mDATA.aTribe == ReturnAllianceTribe(1)))
			{
				return;
			}
			break;
		case 23:
			if ((tAVATAR_OBJECT1->mDATA.aTribe == 2) || (tAVATAR_OBJECT1->mDATA.aTribe == ReturnAllianceTribe(2)))
			{
				return;
			}
			break;
		case 29:
			if ((tAVATAR_OBJECT1->mDATA.aTribe == 3) || (tAVATAR_OBJECT1->mDATA.aTribe == ReturnAllianceTribe(3)))
			{
				return;
			}
			break;
		}
		break;
	case 4:
		switch (tMONSTER_OBJECT->mMONSTER_INFO->mSpecialType)
		{
		case 31:
			tAllianceTribe = ReturnAllianceTribe(0);
			if ((tAVATAR_OBJECT1->mDATA.aTribe == 0) || (tAVATAR_OBJECT1->mDATA.aTribe == tAllianceTribe))
			{
				return;
			}
			if (!tMONSTER_OBJECT->mCheckFirstAttackForAllianceStone)
			{
				tMONSTER_OBJECT->mCheckFirstAttackForAllianceStone = TRUE;
				tMONSTER_OBJECT->mFirstAttackTimeForAllianceStone = GetTickCount();
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tAllianceStoneIndex = 0;
				tBroadcastInfoSort = 48;
				CopyMemory(&tBroadcastInfoData[0], &tAllianceStoneIndex, 4);
				iTribe = static_cast<int> (tAVATAR_OBJECT1->mDATA.aTribe);
				CopyMemory(&tBroadcastInfoData[4], &iTribe, 4);
				CopyMemory(&tBroadcastInfoData[8], &tAVATAR_OBJECT1->mDATA.aName[0], MAX_AVATAR_NAME_LENGTH);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
			}
			break;
		case 32:
			tAllianceTribe = ReturnAllianceTribe(1);
			if ((tAVATAR_OBJECT1->mDATA.aTribe == 1) || (tAVATAR_OBJECT1->mDATA.aTribe == tAllianceTribe))
			{
				return;
			}
			if (!tMONSTER_OBJECT->mCheckFirstAttackForAllianceStone)
			{
				tMONSTER_OBJECT->mCheckFirstAttackForAllianceStone = TRUE;
				tMONSTER_OBJECT->mFirstAttackTimeForAllianceStone = GetTickCount();
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tAllianceStoneIndex = 1;
				tBroadcastInfoSort = 48;
				CopyMemory(&tBroadcastInfoData[0], &tAllianceStoneIndex, 4);
				iTribe = static_cast<int> (tAVATAR_OBJECT1->mDATA.aTribe);
				CopyMemory(&tBroadcastInfoData[4], &iTribe, 4);
				CopyMemory(&tBroadcastInfoData[8], &tAVATAR_OBJECT1->mDATA.aName[0], MAX_AVATAR_NAME_LENGTH);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
			}
			break;
		case 33:
			tAllianceTribe = ReturnAllianceTribe(2);
			if ((tAVATAR_OBJECT1->mDATA.aTribe == 2) || (tAVATAR_OBJECT1->mDATA.aTribe == tAllianceTribe))
			{
				return;
			}
			if (!tMONSTER_OBJECT->mCheckFirstAttackForAllianceStone)
			{
				tMONSTER_OBJECT->mCheckFirstAttackForAllianceStone = TRUE;
				tMONSTER_OBJECT->mFirstAttackTimeForAllianceStone = GetTickCount();
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tAllianceStoneIndex = 2;
				tBroadcastInfoSort = 48;
				CopyMemory(&tBroadcastInfoData[0], &tAllianceStoneIndex, 4);
				iTribe = static_cast<int> (tAVATAR_OBJECT1->mDATA.aTribe);
				CopyMemory(&tBroadcastInfoData[4], &iTribe, 4);
				CopyMemory(&tBroadcastInfoData[8], &tAVATAR_OBJECT1->mDATA.aName[0], MAX_AVATAR_NAME_LENGTH);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
			}
			break;
		case 34:
			tAllianceTribe = ReturnAllianceTribe(3);
			if ((tAVATAR_OBJECT1->mDATA.aTribe == 3) || (tAVATAR_OBJECT1->mDATA.aTribe == tAllianceTribe))
			{
				return;
			}
			if (!tMONSTER_OBJECT->mCheckFirstAttackForAllianceStone)
			{
				tMONSTER_OBJECT->mCheckFirstAttackForAllianceStone = TRUE;
				tMONSTER_OBJECT->mFirstAttackTimeForAllianceStone = GetTickCount();
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tAllianceStoneIndex = 3;
				tBroadcastInfoSort = 48;
				CopyMemory(&tBroadcastInfoData[0], &tAllianceStoneIndex, 4);
				iTribe = static_cast<int> (tAVATAR_OBJECT1->mDATA.aTribe);
				CopyMemory(&tBroadcastInfoData[4], &iTribe, 4);
				CopyMemory(&tBroadcastInfoData[8], &tAVATAR_OBJECT1->mDATA.aName[0], MAX_AVATAR_NAME_LENGTH);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
			}
			break;
		}
		break;
	case 5:
		tAllianceTribe = ReturnAllianceTribe(tAVATAR_OBJECT1->mDATA.aTribe);
		switch (tMONSTER_OBJECT->mMONSTER_INFO->mType)
		{
		case 6:
			tAllianceTribe = ReturnAllianceTribe(0);
			if ((tAVATAR_OBJECT1->mDATA.aTribe == 0) || (tAVATAR_OBJECT1->mDATA.aTribe == tAllianceTribe))
			{
				return;
			}
			break;
		case 7:
			tAllianceTribe = ReturnAllianceTribe(1);
			if ((tAVATAR_OBJECT1->mDATA.aTribe == 1) || (tAVATAR_OBJECT1->mDATA.aTribe == tAllianceTribe))
			{
				return;
			}
			break;
		case 8:
			tAllianceTribe = ReturnAllianceTribe(2);
			if ((tAVATAR_OBJECT1->mDATA.aTribe == 2) || (tAVATAR_OBJECT1->mDATA.aTribe == tAllianceTribe))
			{
				return;
			}
			break;
		case 9:
			tAllianceTribe = ReturnAllianceTribe(3);
			if ((tAVATAR_OBJECT1->mDATA.aTribe == 3) || (tAVATAR_OBJECT1->mDATA.aTribe == tAllianceTribe))
			{
				return;
			}
			break;
		}
		break;
	case 6:
		switch (tMONSTER_OBJECT->mMONSTER_INFO->mSpecialType)
		{
		case 35:
			tAllianceTribe = ReturnAllianceTribe(0);
			if ((tAVATAR_OBJECT1->mDATA.aTribe == 0) || (tAVATAR_OBJECT1->mDATA.aTribe == tAllianceTribe))
			{
				return;
			}
			break;
		case 36:
			tAllianceTribe = ReturnAllianceTribe(1);
			if ((tAVATAR_OBJECT1->mDATA.aTribe == 1) || (tAVATAR_OBJECT1->mDATA.aTribe == tAllianceTribe))
			{
				return;
			}
			break;
		case 37:
			tAllianceTribe = ReturnAllianceTribe(2);
			if ((tAVATAR_OBJECT1->mDATA.aTribe == 2) || (tAVATAR_OBJECT1->mDATA.aTribe == tAllianceTribe))
			{
				return;
			}
			break;
		case 38:
			tAllianceTribe = ReturnAllianceTribe(3);
			if ((tAVATAR_OBJECT1->mDATA.aTribe == 3) || (tAVATAR_OBJECT1->mDATA.aTribe == tAllianceTribe))
			{
				return;
			}
			break;
		case 18:
			break;
		}
		break;
	default:
		return;
	}
	//-------------//
	//-------------//
	//-------------//
	//-------------//
	//°ø°ÝÁ€ºž_ÁöÁ€//
	//-------------//
	switch (tMONSTER_OBJECT->mSpecialSortNumber)
	{
	case 1:
	case 6:
		tMONSTER_OBJECT->SetAttackInfoWithAvatar(tAttackInfo->mServerIndex1, tAttackInfo->mUniqueNumber1, &tWhoAttackMonster);
		break;
	}
	//-------------//
	//-------------//
	//-------------//
	switch (tAttackInfo->mAttackActionValue1)
	{
	case 1:
		tAttackSuccessValue = tAVATAR_OBJECT1->GetAttackSuccess();
		break;
	case 2:
		if (mUSER[tUserIndex].mCheckMaxAttackPacketNum == 1)
		{
			if ((tAVATAR_OBJECT1->mDATA.aAction.aSkillNumber != tAttackInfo->mAttackActionValue2) || ((tAVATAR_OBJECT1->mDATA.aAction.aSkillGradeNum1 + tAVATAR_OBJECT1->mDATA.aAction.aSkillGradeNum2) != tAttackInfo->mAttackActionValue3))
			{
				return;
			}
		}
		tAttackSuccessValue = tAVATAR_OBJECT1->GetAttackSuccess();
		break;
	default:
		return;
	}
	if (tAttackSuccessValue < 1)
	{
		return;
	}
	tAttackBlockValue = tMONSTER_OBJECT->mMONSTER_INFO->mAttackBlock;
	if (tAttackBlockValue > 0)
	{
		if (tAttackSuccessValue > tAttackBlockValue)
		{
			tAttackDetermineValue = (int)(70.0f + (((float)tAttackSuccessValue / (float)tAttackBlockValue) - 1.0f) * 25.0f);
			if (tAttackDetermineValue > 99)
			{
				tAttackDetermineValue = 99;
			}
		}
		else
		{
			tAttackDetermineValue = (int)(70.0f - (((float)tAttackBlockValue / (float)tAttackSuccessValue) - 1.0f) * 25.0f);
			if (tAttackDetermineValue < 1)
			{
				tAttackDetermineValue = 1;
			}
		}
		tRandom = rand();
		if ((tRandom % 100) >= tAttackDetermineValue)
		{
			tAttackInfo->mAttackResultValue = 0;
			mTRANSFER.B_PROCESS_ATTACK_RECV(tAttackInfo);
			mUSER[tAttackInfo->mServerIndex1].Send(TRUE, (char *)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
	}

	switch (tAttackInfo->mAttackActionValue1)
	{
	case 1:
		tAttackPowerValue = tAVATAR_OBJECT1->GetAttackPower();
		break;
	case 2:
		tAttackPowerValue = tAVATAR_OBJECT1->GetAttackPower();
		tAttackPowerUpRatio = mSKILL.ReturnSkillValue(tAttackInfo->mAttackActionValue2, tAttackInfo->mAttackActionValue3, 7);
		if (tAttackPowerUpRatio > 0.0f)
		{
			tAttackPowerValue = (int)((float)tAttackPowerValue * (tAttackPowerUpRatio + 100.0f) * 0.01f);
		}
		break;
	}
	tDefensePowerValue = tMONSTER_OBJECT->mMONSTER_INFO->mDefensePower;
	tDamageValue = tAttackPowerValue - tDefensePowerValue;

	if (tDamageValue < 1)
	{
		tDamageValue = 1;
	}
	if (tChargingValue > 0)
	{
		tDamageValue = (int)((float)(tDamageValue * (tChargingValue + 100)) * 0.01f);
	}
	tRandom = rand();
	if ((tRandom % 2) == 0)
	{
		tRandom = rand();
		tDamageValue += (int)((float)(tDamageValue * (tRandom % 11)) * 0.01f);
	}
	else
	{
		tRandom = rand();
		tDamageValue -= (int)((float)(tDamageValue * (tRandom % 11)) * 0.01f);
	}
	if (tDamageValue < 1)
	{
		tDamageValue = 1;
	}
	tAttackInfo->mAttackCriticalExist = 0;
	/* Mir Check  critical attack*/

	switch (tAttackInfo->mAttackActionValue1)
	{
	case 1:
		tRandom = rand();
		if ((tRandom % 100) < tAVATAR_OBJECT1->GetCritical())
		{
			tDamageValue *= 2;
			tAttackInfo->mAttackCriticalExist = 1;
		}
		break;
	case 2:
		if (tAttackInfo->mAttackActionValue2 == 78)
		{
			break;
		}
		switch (mSKILL.ReturnAttackType(tAttackInfo->mAttackActionValue2))
		{
		case 2:
		case 5:
			tRandom = rand();
			if ((tRandom % 100) < tAVATAR_OBJECT1->GetCritical())
			{
				tDamageValue *= 2;
				tAttackInfo->mAttackCriticalExist = 1;
			}
			break;
		}
		break;
	}
	tElementAttackPower = tAVATAR_OBJECT1->GetElementAttackPower();

	switch (tAttackInfo->mAttackActionValue1)
	{
	case 3:
		tElementAttackPowerUpRatio = mSKILL.ReturnSkillValue(tAttackInfo->mAttackActionValue2, tAttackInfo->mAttackActionValue3, 8);
		if (tElementAttackPowerUpRatio > 0.0f)
		{
			tElementAttackPower = (int)((float)tElementAttackPower * (tElementAttackPowerUpRatio + 100.0f) * 0.01f);
		}
		break;
	}
	tElementDefensePower = tMONSTER_OBJECT->mMONSTER_INFO->mElementDefensePower;
	if (tElementAttackPower > tElementDefensePower)
	{
		tDamageValue += (tElementAttackPower - tElementDefensePower);
		tAttackInfo->mAttackElementDamage = tElementAttackPower - tElementDefensePower;
	}
	else
	{
		tAttackInfo->mAttackElementDamage = 0;
	}
	//-------------//
	//ŒºŒ®ŒÒÀ¯_¹Ý¿µ//
	//-------------//
	if (ReturnSymbolDamageUp(tAVATAR_OBJECT1->mDATA.aTribe) > 0)
	{
		tDamageValue += (ReturnSymbolDamageUp(tAVATAR_OBJECT1->mDATA.aTribe));
	}

	if (tAVATAR_OBJECT1->mDATA.aLevel1 > 112)
	{
		if (ReturnSymbolDamageDown(tAVATAR_OBJECT1->mDATA.aTribe) > 0.0f)
		{
			tDamageValue -= (int)((float)tDamageValue * ReturnSymbolDamageDown(tAVATAR_OBJECT1->mDATA.aTribe));
		}
	}
	//-------------//
	//-------------//
	//-------------//
	tAttackInfo->mAttackResultValue = 1 + mUSER[tAttackInfo->mServerIndex1].mAvatarInfo.aEquip[7][0];
	tAttackInfo->mAttackViewDamageValue = tDamageValue;
	if (tMONSTER_OBJECT->mDATA.mLifeValue < tDamageValue)
	{
		tDamageValue = tMONSTER_OBJECT->mDATA.mLifeValue;
	}
	tAttackInfo->mAttackRealDamageValue = tDamageValue;
	mTRANSFER.B_PROCESS_ATTACK_RECV(tAttackInfo);
	mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
	tMONSTER_OBJECT->mDATA.mLifeValue -= tDamageValue;
	//-------------//
	//°ø°ÝÁ€ºž_ÁöÁ€//
	//-------------//
	switch (tMONSTER_OBJECT->mSpecialSortNumber)
	{
	case 1:
	case 6:
		tMONSTER_OBJECT->mAttackDamage[tWhoAttackMonster] += tDamageValue;
		break;
	case 2:
		tMONSTER_OBJECT->mTribeDamageForTribeSymbol[tAVATAR_OBJECT1->mDATA.aTribe] += tDamageValue;
		break;
	}
	//-------------//
	//-------------//
	//-------------//
	if (tMONSTER_OBJECT->mDATA.mLifeValue > 0)
	{
		tRandom = rand();
		if ((tMONSTER_OBJECT->mMONSTER_INFO->mDamageType != 1) && ((tRandom % 2) == 0) && (tDamageValue > (int)((float)tMONSTER_OBJECT->mMONSTER_INFO->mLife * 0.10f)) && (tMONSTER_OBJECT->mDATA.mAction.aSort != 8))
		{
			tMONSTER_OBJECT->mDATA.mAction.aSort = 8;
			tMONSTER_OBJECT->mDATA.mAction.aFrame = 0.0f;
			tMONSTER_OBJECT->mDATA.mAction.aFront = mUTIL.GetYAngle(tMONSTER_OBJECT->mDATA.mAction.aLocation[0], tMONSTER_OBJECT->mDATA.mAction.aLocation[2], tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], tAVATAR_OBJECT1->mDATA.aAction.aLocation[2]);
			//------------------------//
			//BROADCAST_MONSTER_ACTION//
			//------------------------//
			mTRANSFER.B_MONSTER_ACTION_RECV(tAttackInfo->mServerIndex2, tMONSTER_OBJECT->mUniqueNumber, &tMONSTER_OBJECT->mDATA, 1);
			//-----------------------------------------------------------------//
			//[01].ÀÏ¹Ý,[02].ŒºŒ®,[03].ŒöÈ£ºñ,[04].µ¿žÍŒ®,[05].ŒöÈ£Œ®,[06].Œ®Â÷//
			//-----------------------------------------------------------------//
			switch (tMONSTER_OBJECT->mSpecialSortNumber)
			{
			case 1:
				mUTIL.Broadcast(TRUE, &tMONSTER_OBJECT->mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS1, false, 0);
				break;
			case 2:
				mUTIL.Broadcast(TRUE, &tMONSTER_OBJECT->mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
				break;
			case 3:
				mUTIL.Broadcast(TRUE, &tMONSTER_OBJECT->mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
				break;
			case 4:
				mUTIL.Broadcast(TRUE, &tMONSTER_OBJECT->mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
				break;
			case 5:
				mUTIL.Broadcast(TRUE, &tMONSTER_OBJECT->mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS2, false, 0);
				break;
			case 6:
				mUTIL.Broadcast(TRUE, &tMONSTER_OBJECT->mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
				break;
			}
			//------------------------//
			//------------------------//
			//------------------------//
		}
		return;
	}
	//-----//
	//QUEST//
	//-----//
	switch (mUSER[tUserIndex].mAvatarInfo.aQuestInfo[2])
	{
	case 1:
		if (mAVATAR_OBJECT[tUserIndex].ReturnQuestPresentState() != 2)
		{
			break;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aQuestInfo[3] != tMONSTER_OBJECT->mMONSTER_INFO->mIndex)
		{
			break;
		}
		if (mUSER[tUserIndex].mHealthState == 5)
		{
			break;
		}
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[4]++;
		mTRANSFER.B_PROCESS_QUEST_RECV(0, 6, 0, 0, 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char *)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		break;
	case 5:
		if (mAVATAR_OBJECT[tUserIndex].ReturnQuestPresentState() != 2)
		{
			break;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aQuestInfo[3] != tMONSTER_OBJECT->mMONSTER_INFO->mIndex)
		{
			break;
		}
		if (mUSER[tUserIndex].mHealthState == 5)
		{
			break;
		}
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[4]++;
		mTRANSFER.B_PROCESS_QUEST_RECV(0, 8, 0, 0, 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char *)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		break;
	}
	//-----//
	//-----//
	//-----//
	//-------------//
	//ÃÖÁŸÀ¯Àú_ÁöÁ€//
	//-------------//

	tMONSTER_OBJECT->mLastAttackUserIndex = tUserIndex;
	tMONSTER_OBJECT->mLastAttackUniqueNumber = mAVATAR_OBJECT[tUserIndex].mUniqueNumber;
	tMONSTER_OBJECT->mLastAttackUserTribe = mAVATAR_OBJECT[tUserIndex].mDATA.aTribe;
	strncpy(tMONSTER_OBJECT->mLastAttackUserName, mAVATAR_OBJECT[tUserIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH);

	/** 2009. 10. 27 : MonsterSymbol edit (wolf) */
	if (tMONSTER_OBJECT->mMONSTER_INFO->mSpecialType == 14)
	{
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 10;
		//mUSER[tUserIndex].mAvatarInfo.BloodStained += 2 ;
		//mTRANSFER.B_AVATAR_CHANGE_INFO_2(121, mUSER[tUserIndex].mAvatarInfo.BloodStained);
		//mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(3, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}
	/** 2009. 10. 27 : MonsterSymbol edit (wolf) */


	//-------------//
	//±ÇÇÑÁ€ºž_ÁöÁ€//
	//-------------//
	switch (tMONSTER_OBJECT->mSpecialSortNumber)
	{
	case 1:
	case 6:
		tSelectAvatarIndex = tMONSTER_OBJECT->SelectAvatarIndexForMaxAttackDamage();
		break;
	case 2:
	case 3:
	case 4:
	case 5:
		tSelectAvatarIndex = -1;
		break;
	}
	//-------------//
	//-------------//
	//-------------//
	if (tSelectAvatarIndex != -1)
	{
		::memset(tMONSTER_OBJECT->mAvatarName, 0, MAX_AVATAR_NAME_LENGTH);
		tMONSTER_OBJECT->ProcessForDropItem(tSelectAvatarIndex);
	}
	if (tMONSTER_OBJECT->mMONSTER_INFO->mDamageType != 1)
	{
		tDeathDirection[0] = tMONSTER_OBJECT->mDATA.mAction.aLocation[0] - tAVATAR_OBJECT1->mDATA.aAction.aLocation[0];
		tDeathDirection[2] = tMONSTER_OBJECT->mDATA.mAction.aLocation[2] - tAVATAR_OBJECT1->mDATA.aAction.aLocation[2];

		tDeathLength = sqrtf(tDeathDirection[0] * tDeathDirection[0] + tDeathDirection[2] * tDeathDirection[2]);
		if (tDeathLength < 1.0f)
		{
			tDeathDirection[0] = 0.0f;
			tDeathDirection[2] = 0.0f;
		}
		else
		{
			tRandom = rand() % 4;
			if (tRandom == 0 || tRandom == 1 || tAttackInfo->mAttackCriticalExist) {
				tDeathDirection[0] /= tDeathLength;
				tDeathDirection[2] /= tDeathLength;

			}
			else if (tRandom == 2) {
				tDeathDirection[0] /= (tDeathLength / 4.0f);
				tDeathDirection[2] /= (tDeathLength / 4.0f);

			}
			else {
				tDeathDirection[0] /= (tDeathLength / 3.7f);
				tDeathDirection[2] /= (tDeathLength / 3.7f);

			}
		}
	}
	else
	{
		tDeathDirection[0] = 0.0f;
		tDeathDirection[2] = 0.0f;
	}
	/* Mir */


	if (mGAME.mCheckZone200TypeServer == true)
	{
		if (mGAME.mZone200TypeBattleResult[mUSER[tUserIndex].mAvatarInfo.aTribe] > 0)
		{
			mGAME.mZone200TypeBattleResult[mUSER[tUserIndex].mAvatarInfo.aTribe]--;
			if (mGAME.mZone200TypeBattleResult[mUSER[tUserIndex].mAvatarInfo.aTribe] < 0)
			{
				mGAME.mZone200TypeBattleResult[mUSER[tUserIndex].mAvatarInfo.aTribe] = 0;
			}
		}
	}

	tMONSTER_OBJECT->mDATA.mAction.aSort = 12;
	tMONSTER_OBJECT->mDATA.mAction.aFrame = 0.0f;
	tMONSTER_OBJECT->mDATA.mAction.aTargetLocation[0] = tDeathDirection[0];
	tMONSTER_OBJECT->mDATA.mAction.aTargetLocation[1] = 0.0f;
	tMONSTER_OBJECT->mDATA.mAction.aTargetLocation[2] = tDeathDirection[2];
	tMONSTER_OBJECT->mDATA.mAction.aFront = mUTIL.GetYAngle(tMONSTER_OBJECT->mDATA.mAction.aLocation[0], tMONSTER_OBJECT->mDATA.mAction.aLocation[2], tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], tAVATAR_OBJECT1->mDATA.aAction.aLocation[2]);
	tMONSTER_OBJECT->mDATA.mAction.aSkillNumber = 0;
	if ((tMONSTER_OBJECT->mMONSTER_INFO->mDamageType != 1) && (tMONSTER_OBJECT->mMONSTER_INFO->mType != 2))
	{
		switch (tAttackInfo->mAttackActionValue1)
		{
		case 1:
			tRandom = rand();
			if ((tAttackInfo->mAttackActionValue2 == 1) && ((tRandom % 2) == 0))
			{
				tMONSTER_OBJECT->mDATA.mAction.aSkillNumber = 1;
			}
			break;
		case 2:
			tRandom = rand();
			if ((tRandom % 5) == 0)
			{
				tMONSTER_OBJECT->mDATA.mAction.aSkillNumber = 1;
			}
			break;
		}
	}
	//------------------------//
	//BROADCAST_MONSTER_ACTION//
	//------------------------//
	mTRANSFER.B_MONSTER_ACTION_RECV(tAttackInfo->mServerIndex2, tMONSTER_OBJECT->mUniqueNumber, &tMONSTER_OBJECT->mDATA, 1);
	//-----------------------------------------------------------------//
	//[01].ÀÏ¹Ý,[02].ŒºŒ®,[03].ŒöÈ£ºñ,[04].µ¿žÍŒ®,[05].ŒöÈ£Œ®,[06].Œ®Â÷//
	//-----------------------------------------------------------------//
	//__LogMgr()->Log("tMONSTER_OBJECT->mSpecialSortNumber : %d %d\n", tMONSTER_OBJECT->mSpecialSortNumber, tMONSTER_OBJECT->mDATA.mAction.aSort);
	switch (tMONSTER_OBJECT->mSpecialSortNumber)
	{
	case 1:
		mUTIL.Broadcast(TRUE, &tMONSTER_OBJECT->mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS1, false, 0);
		break;
	case 2:
		mUTIL.Broadcast(TRUE, &tMONSTER_OBJECT->mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
		break;
	case 3:
		mUTIL.Broadcast(TRUE, &tMONSTER_OBJECT->mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
		break;
	case 4:
		mUTIL.Broadcast(TRUE, &tMONSTER_OBJECT->mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
		break;
	case 5:
		mUTIL.Broadcast(TRUE, &tMONSTER_OBJECT->mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS2, false, 0);
		break;
	case 6:
		mUTIL.Broadcast(TRUE, &tMONSTER_OBJECT->mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
		break;
	}
	//------------------------//
	//------------------------//
	//------------------------//
	if ((tSelectAvatarIndex == -1) || (tMONSTER_OBJECT->mMONSTER_INFO->mGeneralExperience < 1) || ((mUTIL.ReturnFixedLevel(mUSER[tSelectAvatarIndex].mAvatarInfo.aLevel1) - tMONSTER_OBJECT->mMONSTER_INFO->mRealLevel) > 9))
	{
		return;
	}
	//EXP LOCK
	if (mUSER[tUserIndex].mAuthInfo.Explock == 1)
	{
		return;
	}
	//------//
	//žóœºÅÍ//
	//------//
	if (tMONSTER_OBJECT->mMONSTER_INFO->mRealLevel > mUTIL.ReturnFixedLevel(mUSER[tSelectAvatarIndex].mAvatarInfo.aLevel1))
	{
		if ((tMONSTER_OBJECT->mMONSTER_INFO->mRealLevel - mUTIL.ReturnFixedLevel(mUSER[tSelectAvatarIndex].mAvatarInfo.aLevel1)) > 20)
		{
			tGainValue = (int)((float)tMONSTER_OBJECT->mMONSTER_INFO->mGeneralExperience * (3.0f + mUSER[tSelectAvatarIndex].mGeneralExperienceUpRatio));
		}
		else
		{
			tGainValue = (int)((float)tMONSTER_OBJECT->mMONSTER_INFO->mGeneralExperience * ((1.0f + mUSER[tSelectAvatarIndex].mGeneralExperienceUpRatio) + (float)(tMONSTER_OBJECT->mMONSTER_INFO->mRealLevel - mUTIL.ReturnFixedLevel(mUSER[tSelectAvatarIndex].mAvatarInfo.aLevel1)) * 0.1f));
		}
	}
	else
	{
		tGainValue = (int)((float)tMONSTER_OBJECT->mMONSTER_INFO->mGeneralExperience * ((1.0f + mUSER[tSelectAvatarIndex].mGeneralExperienceUpRatio) - (float)(mUTIL.ReturnFixedLevel(mUSER[tSelectAvatarIndex].mAvatarInfo.aLevel1) - tMONSTER_OBJECT->mMONSTER_INFO->mRealLevel) * 0.1f));
	}
	//------//
	//------//
	//------//
	//-------------//
	//ž·ÅžÁ€ºž_¹Ý¿µ//
	//-------------//


	//-------------//
	//-------------//
	//-------------//

	if (mUSER[tSelectAvatarIndex].mAvatarInfo.SuperiorPill > 0)
	{
		tGainValue *= 2;
	}
	if (mUSER[tSelectAvatarIndex].mAvatarInfo.ExpPill > 0)
	{
		tGainValue += 2;
	}
	//------//
	//¿ëÆøÁø//
	//------//
	if ((mUSER[tSelectAvatarIndex].mAvatarInfo.aTribe == mWorldInfo.mZone038WinTribe) || (mUSER[tSelectAvatarIndex].mAvatarInfo.aTribe == ReturnAllianceTribe(mGAME.mWorldInfo.mZone038WinTribe)))
	{
		tGainValue += (int)((float)tMONSTER_OBJECT->mMONSTER_INFO->mGeneralExperience * 0.1f);
	}
	//------//
	//------//
	//------//
	//------//
	//---------//
	//»çÁŠ_¹Ý¿µ//
	//---------//

	//---------//
	//---------//
	//---------//
	//------//
	//ÀÌº¥Æ®//
	//------//


	// Double EXP in maps


	if (mGeneralExperienceUpRatio >= 1.0f)
	{
		if (mSERVER_INFO.mServerNumber == 127 ||
			mSERVER_INFO.mServerNumber == 128 ||
			mSERVER_INFO.mServerNumber == 129 ||
			mSERVER_INFO.mServerNumber == 130 ||
			mSERVER_INFO.mServerNumber == 131 ||
			mSERVER_INFO.mServerNumber == 132 ||
			mSERVER_INFO.mServerNumber == 133 ||
			mSERVER_INFO.mServerNumber == 134 ||
			mSERVER_INFO.mServerNumber == 135 ||
			mSERVER_INFO.mServerNumber == 136 ||
			mSERVER_INFO.mServerNumber == 137 ||
			mSERVER_INFO.mServerNumber == 171 ||
			mSERVER_INFO.mServerNumber == 172 ||
			mSERVER_INFO.mServerNumber == 173 ||
			mSERVER_INFO.mServerNumber == 174
			) 
		{

			tGainValue = (int)((float)tGainValue * mGeneralExperienceUpRatio * 2);
			//tPatExperience = (int)((float)tMONSTER_OBJECT->mMONSTER_INFO->mPatExperience * mPatExperienceUpRatio * 2);//sos 2x pet exp
		}
		else
		{
			tGainValue = (int)((float)tGainValue * mGeneralExperienceUpRatio);
		}
	}
	if (mPatExperienceUpRatio > 1.0f)
	{
		if (mSERVER_INFO.mServerNumber == 127 ||
			mSERVER_INFO.mServerNumber == 128 ||
			mSERVER_INFO.mServerNumber == 129 ||
			mSERVER_INFO.mServerNumber == 130 ||
			mSERVER_INFO.mServerNumber == 131 ||
			mSERVER_INFO.mServerNumber == 132 ||
			mSERVER_INFO.mServerNumber == 133 ||
			mSERVER_INFO.mServerNumber == 134 ||
			mSERVER_INFO.mServerNumber == 135 ||
			mSERVER_INFO.mServerNumber == 136 ||
			mSERVER_INFO.mServerNumber == 137 ||
			mSERVER_INFO.mServerNumber == 171 ||
			mSERVER_INFO.mServerNumber == 172 ||
			mSERVER_INFO.mServerNumber == 173 ||
			mSERVER_INFO.mServerNumber == 174
			)
		{
			tPatExperience = (int)((float)tMONSTER_OBJECT->mMONSTER_INFO->mPatExperience * mPatExperienceUpRatio * 2);//sos 2x pet exp
		}
		else {
			tPatExperience = (int)((float)tMONSTER_OBJECT->mMONSTER_INFO->mPatExperience * mPatExperienceUpRatio);
		}

		//tPatExperience = (int)((float)tMONSTER_OBJECT->mMONSTER_INFO->mPatExperience * mPatExperienceUpRatio);
	}

	else {
		tPatExperience = tMONSTER_OBJECT->mMONSTER_INFO->mPatExperience;
	}

	if (mUSER[tSelectAvatarIndex].mAvatarInfo.PetExpBoost > 0)
	{
		tPatExperience *= 2;
	}

	//------//
	//------//
	//------//
	//mUTIL.ProcessForExperience( tSelectAvatarIndex, tGainValue, tMONSTER_OBJECT->mMONSTER_INFO->mPatExperience, ( tMONSTER_OBJECT->mMONSTER_INFO->mLife / 100 ) );
	mUTIL.ProcessForExperience(tSelectAvatarIndex, tGainValue, tPatExperience, (tMONSTER_OBJECT->mMONSTER_INFO->mLife / 100));
	//---------//
	//µ¿Çà_¹Ý¿µ//
	//---------//
	tTotalPartyNum = 0;
	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (!mAVATAR_OBJECT[index01].mCheckValidState)
		{
			continue;
		}
		if (mUSER[index01].mMoveZoneResult == 1)
		{
			continue;
		}
		if (mUSER[index01].mAvatarInfo.aVisibleState == 0)
		{
			continue;
		}
		if (mAVATAR_OBJECT[index01].mDATA.aLifeValue < 1)
		{
			continue;
		}

		tPartyUserIndex[tTotalPartyNum] = index01;
		tTotalPartyNum++;
		if (tTotalPartyNum == MAX_PARTY_AVATAR_NUM)
		{
			break;
		}
	}
	if (tTotalPartyNum < 2)
	{
		return;
	}
	tBonusGainGeneralExperience = 0;
	switch (tTotalPartyNum)
	{
	case 2: tBonusGainGeneralExperience = (int)((float)tMONSTER_OBJECT->mMONSTER_INFO->mGeneralExperience * 0.1f); break;
	case 3: tBonusGainGeneralExperience = (int)((float)tMONSTER_OBJECT->mMONSTER_INFO->mGeneralExperience * 0.2f); break;
	case 4: tBonusGainGeneralExperience = (int)((float)tMONSTER_OBJECT->mMONSTER_INFO->mGeneralExperience * 0.3f); break;
	case 5: tBonusGainGeneralExperience = (int)((float)tMONSTER_OBJECT->mMONSTER_INFO->mGeneralExperience * 0.5f); break;
	}
	if (mBonusGainGeneralExperienceUpRatio > 1.0f)
	{
		tBonusGainGeneralExperience = (int)((float)tBonusGainGeneralExperience * mBonusGainGeneralExperienceUpRatio);
	}

	if (tBonusGainGeneralExperience < 1)
	{
		return;
	}
	for (index01 = 0; index01 < tTotalPartyNum; index01++)
	{
		mUTIL.ProcessForExperience(tPartyUserIndex[index01], tBonusGainGeneralExperience, 0, 0);
	}
	//---------//
	//---------//
	//---------//
}
//PROCESS_ATTACK_04
void MyGame::ProcessAttack04(int tUserIndex, ATTACK_FOR_PROTOCOL *tAttackInfo)
{
	//-----------------------------------------------------------------//
	//[01].ÀÏ¹Ý,[02].ŒºŒ®,[03].ŒöÈ£ºñ,[04].µ¿žÍŒ®,[05].ŒöÈ£Œ®,[06].Œ®Â÷//
	//-----------------------------------------------------------------//

	int tMinusGeneralExperience;
	unsigned int tRandom = 0;
	int tShieldSort = 9;
	int tShieldType = 6;
	if ((tAttackInfo->mServerIndex2 != tUserIndex) || (tAttackInfo->mUniqueNumber2 != mAVATAR_OBJECT[tUserIndex].mUniqueNumber))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tAVATAR_OBJECT1 = &mAVATAR_OBJECT[tAttackInfo->mServerIndex2];
	tAVATAR_OBJECT1->mDATA.aAction.aLocation[0] = tAttackInfo->mSenderLocation[0];
	tAVATAR_OBJECT1->mDATA.aAction.aLocation[1] = tAttackInfo->mSenderLocation[1];
	tAVATAR_OBJECT1->mDATA.aAction.aLocation[2] = tAttackInfo->mSenderLocation[2];
	tAVATAR_OBJECT1->SetSpaceIndex();
	if ((tAttackInfo->mServerIndex1 < 0) || (tAttackInfo->mServerIndex1 > (MAX_MONSTER_OBJECT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tMONSTER_OBJECT = &mMONSTER_OBJECT[tAttackInfo->mServerIndex1];
	if ((!tMONSTER_OBJECT->mCheckValidState) || (tMONSTER_OBJECT->mUniqueNumber != tAttackInfo->mUniqueNumber1))
	{
		return;
	}
	tMONSTER_OBJECT->mCheckAttackPacketRecv = FALSE;
	if (mUSER[tAttackInfo->mServerIndex2].mMoveZoneResult == 1)
	{
		return;
	}
	if (tAVATAR_OBJECT1->mDATA.aLifeValue < 1)
	{
		return;
	}
	if (tAVATAR_OBJECT1->mDATA.aPShopState == 1)
	{
		return;
	}
	if (!CheckPossibleAttackTarget(1, tAVATAR_OBJECT1->mDATA.aAction.aSort))
	{
		return;
	}
	if ((mTickCount - mUSER[tAttackInfo->mServerIndex2].mTickCountFor01SecondForProtect) < PROTECT_TICK)
	{
		return;
	}
	if (tMONSTER_OBJECT->mDATA.mLifeValue < 1)
	{
		return;
	}
	if (mUTIL.GetDoubleX_Z(&tMONSTER_OBJECT->mDATA.mAction.aLocation[0], &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0]) > (float) (tMONSTER_OBJECT->mMONSTER_INFO->mRadiusInfo[1] * tMONSTER_OBJECT->mMONSTER_INFO->mRadiusInfo[1]))
	{
		return;
	}
	tAttackSuccessValue = tMONSTER_OBJECT->mMONSTER_INFO->mAttackSuccess;
	if (tAttackSuccessValue < 1)
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();


	tAttackBlockValue = tAVATAR_OBJECT1->GetAttackBlock();
	if (tAttackBlockValue > 0)
	{
		if (tAttackSuccessValue > tAttackBlockValue)
		{
			tAttackDetermineValue = (int)(70.0f + (((float)tAttackSuccessValue / (float)tAttackBlockValue) - 1.0f) * 25.0f);
			if (tAttackDetermineValue > 99)
			{
				tAttackDetermineValue = 99;
			}
		}
		else
		{
			tAttackDetermineValue = (int)(70.0f - (((float)tAttackBlockValue / (float)tAttackSuccessValue) - 1.0f) * 25.0f);
			if (tAttackDetermineValue < 1)
			{
				tAttackDetermineValue = 1;
			}
		}
		tRandom = rand();
		if ((tRandom % 100) >= tAttackDetermineValue)
		{
			tAttackInfo->mAttackResultValue = 0;
			mTRANSFER.B_PROCESS_ATTACK_RECV(tAttackInfo);
			mUSER[tAttackInfo->mServerIndex2].Send(TRUE, (char *)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
	}
	tAttackPowerValue = tMONSTER_OBJECT->mMONSTER_INFO->mAttackPower;
	tDefensePowerValue = tAVATAR_OBJECT1->GetDefensePower();
	tDamageValue = tAttackPowerValue - tDefensePowerValue;
	if (tDamageValue < 1)
	{
		tDamageValue = 1;
	}
	tRandom = rand();
	if ((tRandom % 2) == 0)
	{
		tRandom = rand();
		tDamageValue += (int)((float)(tDamageValue * (tRandom % 11)) * 0.01f);
	}
	else
	{
		tRandom = rand();
		tDamageValue -= (int)((float)(tDamageValue * (tRandom % 11)) * 0.01f);
	}
	if (tDamageValue < 1)
	{
		tDamageValue = 1;
	}
	tAttackInfo->mAttackCriticalExist = 0;
	if (tMONSTER_OBJECT->mMONSTER_INFO->mCritical > tAVATAR_OBJECT1->GetCriticalDefense())
	{
		tRandom = rand();
		if ((tRandom % 100) < (tMONSTER_OBJECT->mMONSTER_INFO->mCritical - tAVATAR_OBJECT1->GetCriticalDefense()))
		{
			tDamageValue *= 2;
			tAttackInfo->mAttackCriticalExist = 1;
		}
	}
	else
	{
		tRandom = rand();
		if ((tRandom % 100) < 1)
		{
			tDamageValue *= 2;
			tAttackInfo->mAttackCriticalExist = 1;
		}
	}
	//------------------//
	//ÃµœÅ¹Ì±Ã_ºžœº_Ã³ž®//
	//------------------//

	if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[9][0] > 0)
	{
		tShieldSort = 9;
		tShieldType = 6;
	}
	else if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[29][0] > 0)
	{
		tShieldSort = 29;
		tShieldType = 31;
	}
	else if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[30][0] > 0)
	{
		tShieldSort = 30;
		tShieldType = 32;
	}
	else if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[31][0] > 0)
	{
		tShieldSort = 31;
		tShieldType = 33;
	}
	else if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[32][0] > 0)
	{
		tShieldSort = 32;
		tShieldType = 34;
	}
	else if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[33][0] > 0)
	{
		tShieldSort = 33;
		tShieldType = 35;
	}
	else if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[34][0] > 0)
	{
		tShieldSort = 34;
		tShieldType = 36;
	}

	if (tAttackInfo->mAttackActionValue4 == 0)
	{
		switch (tMONSTER_OBJECT->mMONSTER_INFO->mSpecialType)
		{
		case 40:
			tRandom = rand();
			if ((tRandom % 100) < 10)
			{
				mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0] = 0;
				mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][1] = 0;
				tAVATAR_OBJECT1->mDATA.aEffectValueForView[tShieldSort] = 0;
				mTRANSFER.B_AVATAR_CHANGE_INFO_1(tAttackInfo->mServerIndex2, tAttackInfo->mUniqueNumber2, 3, 0, 0, 0);
				mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			}
			tRandom = rand();
			if ((tRandom % 100) < 10)
			{
				tAVATAR_OBJECT1->mDATA.aAction.aType = 0;
				tAVATAR_OBJECT1->mDATA.aAction.aSort = 11;
				tAVATAR_OBJECT1->mDATA.aAction.aFrame = 0.0f;
				tAVATAR_OBJECT1->mDATA.aAction.aSkillValue = 10;
				mTRANSFER.B_AVATAR_ACTION_RECV(tAttackInfo->mServerIndex2, tAVATAR_OBJECT1->mUniqueNumber, &tAVATAR_OBJECT1->mDATA, 1);
				mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			}
			break;
		case 41:
			tRandom = rand();
			if ((tRandom % 100) < 0)
			{
				mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0] = 0;
				mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][1] = 0;
				tAVATAR_OBJECT1->mDATA.aEffectValueForView[tShieldSort] = 0;
				mTRANSFER.B_AVATAR_CHANGE_INFO_1(tAttackInfo->mServerIndex2, tAttackInfo->mUniqueNumber2, 3, 0, 0, 0);
				mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			}
			tRandom = rand();
			if ((tRandom % 100) < 0)
			{
				tAVATAR_OBJECT1->mDATA.aAction.aType = 0;
				tAVATAR_OBJECT1->mDATA.aAction.aSort = 11;
				tAVATAR_OBJECT1->mDATA.aAction.aFrame = 0.0f;
				tAVATAR_OBJECT1->mDATA.aAction.aSkillValue = 10;
				mTRANSFER.B_AVATAR_ACTION_RECV(tAttackInfo->mServerIndex2, tAVATAR_OBJECT1->mUniqueNumber, &tAVATAR_OBJECT1->mDATA, 1);
				mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			}
			break;
		case 42:
			tRandom = rand();
			if ((tRandom % 100) < 10)
			{
				mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0] = 0;
				mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][1] = 0;
				tAVATAR_OBJECT1->mDATA.aEffectValueForView[tShieldSort] = 0;
				mTRANSFER.B_AVATAR_CHANGE_INFO_1(tAttackInfo->mServerIndex2, tAttackInfo->mUniqueNumber2, 3, 0, 0, 0);
				mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			}
			tRandom = rand();
			if ((tRandom % 100) < 10)
			{
				tAVATAR_OBJECT1->mDATA.aAction.aType = 0;
				tAVATAR_OBJECT1->mDATA.aAction.aSort = 11;
				tAVATAR_OBJECT1->mDATA.aAction.aFrame = 0.0f;
				tAVATAR_OBJECT1->mDATA.aAction.aSkillValue = 10;
				mTRANSFER.B_AVATAR_ACTION_RECV(tAttackInfo->mServerIndex2, tAVATAR_OBJECT1->mUniqueNumber, &tAVATAR_OBJECT1->mDATA, 1);
				mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			}
			break;
		case 43:
			tRandom = rand();
			if ((tRandom % 100) < 5)
			{
				mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0] = 0;
				mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][1] = 0;
				tAVATAR_OBJECT1->mDATA.aEffectValueForView[tShieldSort] = 0;
				mTRANSFER.B_AVATAR_CHANGE_INFO_1(tAttackInfo->mServerIndex2, tAttackInfo->mUniqueNumber2, 3, 0, 0, 0);
				mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			}
			tRandom = rand();
			if ((tRandom % 100) < 5)
			{
				tAVATAR_OBJECT1->mDATA.aAction.aType = 0;
				tAVATAR_OBJECT1->mDATA.aAction.aSort = 11;
				tAVATAR_OBJECT1->mDATA.aAction.aFrame = 0.0f;
				tAVATAR_OBJECT1->mDATA.aAction.aSkillValue = 10;
				mTRANSFER.B_AVATAR_ACTION_RECV(tAttackInfo->mServerIndex2, tAVATAR_OBJECT1->mUniqueNumber, &tAVATAR_OBJECT1->mDATA, 1);
				mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			}
			break;
		case 44:
			tRandom = rand();
			if ((tRandom % 100) < 10)
			{
				mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0] = 0;
				mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][1] = 0;
				tAVATAR_OBJECT1->mDATA.aEffectValueForView[tShieldSort] = 0;
				mTRANSFER.B_AVATAR_CHANGE_INFO_1(tAttackInfo->mServerIndex2, tAttackInfo->mUniqueNumber2, 3, 0, 0, 0);
				mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			}
			tRandom = rand();
			if ((tRandom % 100) < 10)
			{
				tAVATAR_OBJECT1->mDATA.aAction.aType = 0;
				tAVATAR_OBJECT1->mDATA.aAction.aSort = 11;
				tAVATAR_OBJECT1->mDATA.aAction.aFrame = 0.0f;
				tAVATAR_OBJECT1->mDATA.aAction.aSkillValue = 10;
				mTRANSFER.B_AVATAR_ACTION_RECV(tAttackInfo->mServerIndex2, tAVATAR_OBJECT1->mUniqueNumber, &tAVATAR_OBJECT1->mDATA, 1);
				mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			}
			break;
		}
	}
	else if (tAttackInfo->mAttackActionValue4 == 1)
	{
		switch (tMONSTER_OBJECT->mMONSTER_INFO->mSpecialType)
		{
		case 40:
			tRandom = rand();
			if ((tRandom % 100) < 50)
			{
				mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0] = 0;
				mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][1] = 0;
				tAVATAR_OBJECT1->mDATA.aEffectValueForView[tShieldSort] = 0;
				mTRANSFER.B_AVATAR_CHANGE_INFO_1(tAttackInfo->mServerIndex2, tAttackInfo->mUniqueNumber2, 3, 0, 0, 0);
				mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			}
			tRandom = rand();
			if ((tRandom % 100) < 50)
			{
				tAVATAR_OBJECT1->mDATA.aAction.aType = 0;
				tAVATAR_OBJECT1->mDATA.aAction.aSort = 11;
				tAVATAR_OBJECT1->mDATA.aAction.aFrame = 0.0f;
				tAVATAR_OBJECT1->mDATA.aAction.aSkillValue = 10;
				mTRANSFER.B_AVATAR_ACTION_RECV(tAttackInfo->mServerIndex2, tAVATAR_OBJECT1->mUniqueNumber, &tAVATAR_OBJECT1->mDATA, 1);
				mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			}
			break;
		case 41:
			tRandom = rand();
			if ((tRandom % 100) < 60)
			{
				mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0] = 0;
				mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][1] = 0;
				tAVATAR_OBJECT1->mDATA.aEffectValueForView[tShieldSort] = 0;
				mTRANSFER.B_AVATAR_CHANGE_INFO_1(tAttackInfo->mServerIndex2, tAttackInfo->mUniqueNumber2, 3, 0, 0, 0);
				mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			}
			tRandom = rand();
			if ((tRandom % 100) < 60)
			{
				tAVATAR_OBJECT1->mDATA.aAction.aType = 0;
				tAVATAR_OBJECT1->mDATA.aAction.aSort = 11;
				tAVATAR_OBJECT1->mDATA.aAction.aFrame = 0.0f;
				tAVATAR_OBJECT1->mDATA.aAction.aSkillValue = 10;
				mTRANSFER.B_AVATAR_ACTION_RECV(tAttackInfo->mServerIndex2, tAVATAR_OBJECT1->mUniqueNumber, &tAVATAR_OBJECT1->mDATA, 1);
				mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			}
			break;
		case 42:
			tRandom = rand();
			if ((tRandom % 100) < 70)
			{
				mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0] = 0;
				mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][1] = 0;
				tAVATAR_OBJECT1->mDATA.aEffectValueForView[tShieldSort] = 0;
				mTRANSFER.B_AVATAR_CHANGE_INFO_1(tAttackInfo->mServerIndex2, tAttackInfo->mUniqueNumber2, 3, 0, 0, 0);
				mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			}
			tRandom = rand();
			if ((tRandom % 100) < 70)
			{
				tAVATAR_OBJECT1->mDATA.aAction.aType = 0;
				tAVATAR_OBJECT1->mDATA.aAction.aSort = 11;
				tAVATAR_OBJECT1->mDATA.aAction.aFrame = 0.0f;
				tAVATAR_OBJECT1->mDATA.aAction.aSkillValue = 10;
				mTRANSFER.B_AVATAR_ACTION_RECV(tAttackInfo->mServerIndex2, tAVATAR_OBJECT1->mUniqueNumber, &tAVATAR_OBJECT1->mDATA, 1);
				mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			}
			break;
		case 43:
			tRandom = rand();
			if ((tRandom % 100) < 80)
			{
				mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0] = 0;
				mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][1] = 0;
				tAVATAR_OBJECT1->mDATA.aEffectValueForView[tShieldSort] = 0;
				mTRANSFER.B_AVATAR_CHANGE_INFO_1(tAttackInfo->mServerIndex2, tAttackInfo->mUniqueNumber2, 3, 0, 0, 0);
				mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			}
			tRandom = rand();
			if ((tRandom % 100) < 80)
			{
				tAVATAR_OBJECT1->mDATA.aAction.aType = 0;
				tAVATAR_OBJECT1->mDATA.aAction.aSort = 11;
				tAVATAR_OBJECT1->mDATA.aAction.aFrame = 0.0f;
				tAVATAR_OBJECT1->mDATA.aAction.aSkillValue = 10;
				mTRANSFER.B_AVATAR_ACTION_RECV(tAttackInfo->mServerIndex2, tAVATAR_OBJECT1->mUniqueNumber, &tAVATAR_OBJECT1->mDATA, 1);
				mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			}
			break;
		case 44:
			tRandom = rand();
			if ((tRandom % 100) < 90)
			{
				mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0] = 0;
				mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][1] = 0;
				tAVATAR_OBJECT1->mDATA.aEffectValueForView[tShieldSort] = 0;
				mTRANSFER.B_AVATAR_CHANGE_INFO_1(tAttackInfo->mServerIndex2, tAttackInfo->mUniqueNumber2, 3, 0, 0, 0);
				mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			}
			tRandom = rand();
			if ((tRandom % 100) < 90)
			{
				tAVATAR_OBJECT1->mDATA.aAction.aType = 0;
				tAVATAR_OBJECT1->mDATA.aAction.aSort = 11;
				tAVATAR_OBJECT1->mDATA.aAction.aFrame = 0.0f;
				tAVATAR_OBJECT1->mDATA.aAction.aSkillValue = 10;
				mTRANSFER.B_AVATAR_ACTION_RECV(tAttackInfo->mServerIndex2, tAVATAR_OBJECT1->mUniqueNumber, &tAVATAR_OBJECT1->mDATA, 1);
				mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			}
			break;
		}
	}
	else;
	//------------------//
	//------------------//
	//------------------//
	if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0] > 0)
	{
		if (tDamageValue > mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0])
		{
			tShieldDamageValue = mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0];
		}
		else
		{
			tShieldDamageValue = tDamageValue;
		}
		mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0] -= tShieldDamageValue;
		if (mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0] < 1)
		{
			mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][0] = 0;
			mUSER[tAttackInfo->mServerIndex2].mEffectValue[tShieldSort][1] = 0;
		}
		tAVATAR_OBJECT1->mDATA.aEffectValueForView[tShieldSort] -= tShieldDamageValue;
		if (tAVATAR_OBJECT1->mDATA.aEffectValueForView[tShieldSort] < 1)
		{
			tAVATAR_OBJECT1->mDATA.aEffectValueForView[tShieldSort] = 0;
		}
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(tAttackInfo->mServerIndex2, tAttackInfo->mUniqueNumber2, tShieldType, tShieldDamageValue, 0, 0);
		mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		tDamageValue -= tShieldDamageValue;
	}
	tElementAttackPower = tMONSTER_OBJECT->mMONSTER_INFO->mElementAttackPower;
	tElementDefensePower = tAVATAR_OBJECT1->GetElementDefensePower();
	if (tElementAttackPower > tElementDefensePower)
	{
		tDamageValue += (tElementAttackPower - tElementDefensePower);
		tAttackInfo->mAttackElementDamage = tElementAttackPower - tElementDefensePower;
	}
	else
	{
		tAttackInfo->mAttackElementDamage = 0;
	}
	tAttackInfo->mAttackResultValue = 1;
	tAttackInfo->mAttackViewDamageValue = tDamageValue;
	if (tAVATAR_OBJECT1->mDATA.aLifeValue < tDamageValue)
	{
		tDamageValue = tAVATAR_OBJECT1->mDATA.aLifeValue;
	}
	tAttackInfo->mAttackRealDamageValue = tDamageValue;
	mTRANSFER.B_PROCESS_ATTACK_RECV(tAttackInfo);
	mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
	tAVATAR_OBJECT1->mDATA.aLifeValue -= tDamageValue;
	if (tAVATAR_OBJECT1->mDATA.aLifeValue > 0)
	{
		return;
	}
	//------------------------//
	//PROCESS_FOR_AVATAR_DEATH//
	//------------------------//
	tDeathDirection[0] = tAVATAR_OBJECT1->mDATA.aAction.aLocation[0] - tMONSTER_OBJECT->mDATA.mAction.aLocation[0];
	tDeathDirection[2] = tAVATAR_OBJECT1->mDATA.aAction.aLocation[2] - tMONSTER_OBJECT->mDATA.mAction.aLocation[2];
	tDeathLength = sqrtf(tDeathDirection[0] * tDeathDirection[0] + tDeathDirection[2] * tDeathDirection[2]);
	if (tDeathLength < 1.0f)
	{
		tDeathDirection[0] = 0.0f;
		tDeathDirection[2] = 0.0f;
	}
	else
	{
		tDeathDirection[0] /= tDeathLength;
		tDeathDirection[2] /= tDeathLength;
	}
	tAVATAR_OBJECT1->mDATA.aAction.aType = 0;
	tAVATAR_OBJECT1->mDATA.aAction.aSort = 12;
	tAVATAR_OBJECT1->mDATA.aAction.aFrame = 0.0f;
	tAVATAR_OBJECT1->mDATA.aAction.aTargetLocation[0] = tDeathDirection[0];
	tAVATAR_OBJECT1->mDATA.aAction.aTargetLocation[1] = 0.0f;
	tAVATAR_OBJECT1->mDATA.aAction.aTargetLocation[2] = tDeathDirection[2];
	tAVATAR_OBJECT1->mDATA.aAction.aFront = mUTIL.GetYAngle(tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], tAVATAR_OBJECT1->mDATA.aAction.aLocation[2], tMONSTER_OBJECT->mDATA.mAction.aLocation[0], tMONSTER_OBJECT->mDATA.mAction.aLocation[2]);
	tAVATAR_OBJECT1->mDATA.aAction.aTargetFront = tAVATAR_OBJECT1->mDATA.aAction.aFront;
	tAVATAR_OBJECT1->mDATA.aAction.aSkillNumber = 5;
	mTRANSFER.B_AVATAR_ACTION_RECV(tAttackInfo->mServerIndex2, tAVATAR_OBJECT1->mUniqueNumber, &tAVATAR_OBJECT1->mDATA, 1);
	mUSER[tAttackInfo->mServerIndex2].Send(TRUE, (char *)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT1->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, tAttackInfo->mServerIndex1, false);
	tAVATAR_OBJECT1->ProcessForDeath();
	if ((890 == tMONSTER_OBJECT->mMONSTER_INFO->mIndex) ||
		(891 == tMONSTER_OBJECT->mMONSTER_INFO->mIndex)) {
		return;
	}
	//------------------------//
	//------------------------//
	//------------------------//
	//-----------------------------------------------------------------//
	//[01] General,[02] Sacred Stone,[03] Guardian Stone,[04] Alliance Stone,[05] Guardian Stone,[06] Ranking.//
	//-----------------------------------------------------------------//
	switch (tMONSTER_OBJECT->mSpecialSortNumber)
	{
	case 1:
		if ((mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aLevel1 < 10) || (mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aLevel1 >= 145))
		{
			// 2009.12.29 - 33rd Guardian Division Function - Modified per request to decrease Guardian Division by 1 when using it once.
			if (mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aLevel1 >= 145)
			{
				if (mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.ProtectionScroll > 0)
				{
					// Guardian Division decrease processing.
					mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.ProtectionScroll--;
					mTRANSFER.B_AVATAR_CHANGE_INFO_2(8, mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.ProtectionScroll);
					mUSER[tAttackInfo->mServerIndex2].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				else
				{
					mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aKillOtherTribe -= 10;
					if (mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aKillOtherTribe < 0)
					{
						mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aKillOtherTribe = 0;
					}
					tAVATAR_OBJECT1->mDATA.aKillOtherTribe -= 10;
					if (tAVATAR_OBJECT1->mDATA.aKillOtherTribe < 0)
					{
						tAVATAR_OBJECT1->mDATA.aKillOtherTribe = 0;
					}
				}
			}
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(3, mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aKillOtherTribe);
			mUSER[tAttackInfo->mServerIndex2].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tMinusGeneralExperience = (int)((float)(mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aGeneralExperience1 - mLEVEL.ReturnLevelFactor1(mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aLevel1)) * (0.05f * mUSER[tAttackInfo->mServerIndex2].mGeneralExperienceDownRatio));
#if 0
		if (mGeneralExperienceDownRatio > 1 || mGeneralExperienceDownRatio < 10) {
			mGeneralExperienceDownRatio = mGeneralExperienceDownRatio;
		}
		else {
			mGeneralExperienceDownRatio = 1;
		}
		LOG_TO_FILE_3("aName 

			, % d, % d, \n", mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aName, mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aGeneralExperience1, tMinusGeneralExperience);
#endif
			tMinusGeneralExperience = tMinusGeneralExperience * mGeneralExperienceDownRatio;

		if (tMinusGeneralExperience < 1)
		{
			return;
		}
		/* Mir added */
		if (mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aGeneralExperience1 <= tMinusGeneralExperience)
			tMinusGeneralExperience = mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aGeneralExperience1;
		/* Mir */

		if (mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.ProtectionScroll < 1)
		{
			//mGAMELOG.GL_633_MINUS_EXP_WITH_DIE(tAttackInfo->mServerIndex2, mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aGeneralExperience1, (mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aGeneralExperience1 - tMinusGeneralExperience));
			mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aGeneralExperience1 -= tMinusGeneralExperience;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(7, mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aGeneralExperience1);
			mUSER[tAttackInfo->mServerIndex2].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		else
		{
			mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.ProtectionScroll--;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(8, mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.ProtectionScroll);
			mUSER[tAttackInfo->mServerIndex2].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		return;
	}
//	case 1:
//		if ((mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aLevel1 < 10) || (mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aLevel1 >= 145))
//		{
//			// 2009.12.29 - 33°© ŒöÈ£ºÎ ±âŽÉ - ŒöÈ£ºÎ 1Èž °šŒÒœÃÄÑ ŽÞ¶óŽÂ ¿äÃ»Àž·Î ŒöÁ€ÇÕŽÏŽÙ.
//			if (mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aLevel1 >= 145)
//			{
//
//				mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aKillOtherTribe -= 10;
//				if (mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aKillOtherTribe < 0)
//				{
//					mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aKillOtherTribe = 0;
//				}
//				tAVATAR_OBJECT1->mDATA.aKillOtherTribe -= 10;
//				if (tAVATAR_OBJECT1->mDATA.aKillOtherTribe < 0)
//				{
//					tAVATAR_OBJECT1->mDATA.aKillOtherTribe = 0;
//				}
//
//			}
//			mTRANSFER.B_AVATAR_CHANGE_INFO_2(3, mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aKillOtherTribe);
//			mUSER[tAttackInfo->mServerIndex2].Send(TRUE, (char *)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
//			return;
//		}
//
//#if 0
//		if (mGeneralExperienceDownRatio > 1 || mGeneralExperienceDownRatio < 10) {
//			mGeneralExperienceDownRatio = mGeneralExperienceDownRatio;
//		}
//		else {
//			mGeneralExperienceDownRatio = 1;
//		}
//		__LogMgr()->Log("aName %s, %d, %d, \n", mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aName, mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aGeneralExperience1, tMinusGeneralExperience);
//#endif
//		tMinusGeneralExperience = tMinusGeneralExperience * mGeneralExperienceDownRatio;
//
//		if (tMinusGeneralExperience < 1)
//		{
//			return;
//		}
//		/* Mir added */
//		if (mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aGeneralExperience1 <= tMinusGeneralExperience)
//			tMinusGeneralExperience = mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aGeneralExperience1;
//		/* Mir */
//
//		if (mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.ProtectionScroll < 1)
//		{
//			//mGAMELOG.GL_633_MINUS_EXP_WITH_DIE(tAttackInfo->mServerIndex2, mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aGeneralExperience1, (mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aGeneralExperience1 - tMinusGeneralExperience));
//			mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aGeneralExperience1 -= tMinusGeneralExperience;
//			mTRANSFER.B_AVATAR_CHANGE_INFO_2(7, mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aGeneralExperience1);
//			mUSER[tAttackInfo->mServerIndex2].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
//		}
//		else
//		{
//			mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.ProtectionScroll--;
//			mTRANSFER.B_AVATAR_CHANGE_INFO_2(8, mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.ProtectionScroll);
//			mUSER[tAttackInfo->mServerIndex2].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
//		}
//		return;
//	}
}
//PROCESS_ATTACK_05
void MyGame::ProcessAttack05(int tUserIndex, ATTACK_FOR_PROTOCOL *tAttackInfo)
{
	int index01;
	unsigned int tRandom = 0;

	if ((tAttackInfo->mServerIndex1 != tUserIndex) || (tAttackInfo->mUniqueNumber1 != mAVATAR_OBJECT[tUserIndex].mUniqueNumber))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);

		return;
	}
	tAVATAR_OBJECT1 = &mAVATAR_OBJECT[tAttackInfo->mServerIndex1];
	tAVATAR_OBJECT1->mDATA.aAction.aLocation[0] = tAttackInfo->mSenderLocation[0];
	tAVATAR_OBJECT1->mDATA.aAction.aLocation[1] = tAttackInfo->mSenderLocation[1];
	tAVATAR_OBJECT1->mDATA.aAction.aLocation[2] = tAttackInfo->mSenderLocation[2];
	tAVATAR_OBJECT1->SetSpaceIndex();
	if ((tAttackInfo->mServerIndex2 < 0) || (tAttackInfo->mServerIndex2 > (mSERVER.mMAX_USER_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (1 == mUSER[tUserIndex].mAuthInfo.AttackFlag) {
		return;
	}
	tAVATAR_OBJECT2 = &mAVATAR_OBJECT[tAttackInfo->mServerIndex2];
	if ((!tAVATAR_OBJECT2->mCheckValidState) || (tAVATAR_OBJECT2->mUniqueNumber != tAttackInfo->mUniqueNumber2))
	{
		return;
	}
	if (tAVATAR_OBJECT1->mDATA.aLifeValue < 1)
	{
		return;
	}
	if ((mTickCount - mUSER[tAttackInfo->mServerIndex1].mTickCountFor01SecondForProtect) < PROTECT_TICK)
	{
		return;
	}
	if (mUSER[tAttackInfo->mServerIndex2].mMoveZoneResult == 1)
	{
		return;
	}
	if (tAVATAR_OBJECT2->mDATA.aLifeValue < 1)
	{
		return;
	}
	if (1 == tAVATAR_OBJECT2->mGod) {
		return;
	}
	if (1 == mUSER[tAttackInfo->mServerIndex2].mAuthInfo.AttackFlag) {
		return;
	}
	if (tAVATAR_OBJECT2->mDATA.aPShopState == 1)
	{
		return;
	}
	if (!CheckPossibleAttackTarget(1, tAVATAR_OBJECT2->mDATA.aAction.aSort))
	{
		return;
	}
	if ((mTickCount - mUSER[tAttackInfo->mServerIndex2].mTickCountFor01SecondForProtect) < PROTECT_TICK)
	{
		return;
	}
	if ((mZONEMAININFO.ReturnZoneTribeInfo2(mSERVER_INFO.mServerNumber) == 0) || (tAVATAR_OBJECT1->mDATA.aTribe == tAVATAR_OBJECT2->mDATA.aTribe) || (tAVATAR_OBJECT2->mDATA.aTribe == ReturnAllianceTribe(tAVATAR_OBJECT1->mDATA.aTribe)))
	{
		if ((tAVATAR_OBJECT1->mDATA.aDuelState[0] != 1) || (tAVATAR_OBJECT2->mDATA.aDuelState[0] != 1) || (tAVATAR_OBJECT1->mDATA.aDuelState[1] != tAVATAR_OBJECT2->mDATA.aDuelState[1]) || (tAVATAR_OBJECT1->mDATA.aDuelState[2] == tAVATAR_OBJECT2->mDATA.aDuelState[2]))
		{
			return;
		}
	}

	if (mUSER[tUserIndex].mCheckMaxAttackPacketNum == 1)
	{
		if ((tAVATAR_OBJECT1->mDATA.aAction.aSkillNumber != tAttackInfo->mAttackActionValue2) || ((tAVATAR_OBJECT1->mDATA.aAction.aSkillGradeNum1 + tAVATAR_OBJECT1->mDATA.aAction.aSkillGradeNum2) != tAttackInfo->mAttackActionValue3))
		{
			return;
		}
	}
	tAttackSuccessValue = (int)mSKILL.ReturnSkillValue(tAttackInfo->mAttackActionValue2, tAttackInfo->mAttackActionValue3, 4);

	if (tAttackSuccessValue < 1)
	{
		return;
	}

	if (tAttackInfo->mAttackActionValue2 != 80)
	{
		for (index01 = 0; index01 < MAX_SKILL_SLOT_NUM; index01++)
		{
			if ((mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aSkill[index01][0] == 5) || (mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aSkill[index01][0] == 24) || (mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aSkill[index01][0] == 43))
			{
				break;
			}
		}
		if (index01 < MAX_SKILL_SLOT_NUM)
		{
			tAttackBlockValue = (int)mSKILL.ReturnSkillValue(mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aSkill[index01][0], (mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aSkill[index01][1] + tAVATAR_OBJECT2->GetBonusSkillValue(mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aSkill[index01][0])), 5);
			//__LogMgr()->Log("tAttackBlockValue : %d, %d, %d, %d\n", mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aSkill[index01][1], tAVATAR_OBJECT2->GetBonusSkillValue( mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aSkill[index01][0] ), mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aSkill[index01][0], ( mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aSkill[index01][1] + tAVATAR_OBJECT2->GetBonusSkillValue( mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aSkill[index01][0] ) ));
		}
		else
		{
			tAttackBlockValue = 0;
		}

		if (mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aLevel1 > 99)
		{
			tAttackBlockValue += (1 + (mUSER[tAttackInfo->mServerIndex2].mAvatarInfo.aLevel1 - 100) / 2);
		}

		if (tAVATAR_OBJECT2->mDATA.aEffectValueForView[13] > 0)
		{
			tAttackBlockValue = (int)((float)(tAttackBlockValue * (tAVATAR_OBJECT2->mDATA.aEffectValueForView[13] + 100)) * 0.01f);
			
		}
	}
	else
	{
		tAttackBlockValue = 0;
	}

	tRandom = rand() % 100;

	if ((int)tRandom > (int)(tAttackSuccessValue - tAttackBlockValue - 1))
	{
		return;
	}
	tAVATAR_OBJECT2->mDATA.aAction.aType = 0;
	tAVATAR_OBJECT2->mDATA.aAction.aSort = 11;
	tAVATAR_OBJECT2->mDATA.aAction.aFrame = 0.0f;
	tAVATAR_OBJECT2->mDATA.aAction.aSkillValue = (int)mSKILL.ReturnSkillValue(tAttackInfo->mAttackActionValue2, tAttackInfo->mAttackActionValue3, 10);
	mTRANSFER.B_AVATAR_ACTION_RECV(tAttackInfo->mServerIndex2, tAVATAR_OBJECT2->mUniqueNumber, &tAVATAR_OBJECT2->mDATA, 1);
	mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT2->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
}
//PROCESS_ATTACK_06
void MyGame::ProcessAttack06(int tUserIndex, ATTACK_FOR_PROTOCOL *tAttackInfo)
{
	unsigned int tRandom = 0;
	if ((tAttackInfo->mServerIndex1 != tUserIndex) || (tAttackInfo->mUniqueNumber1 != mAVATAR_OBJECT[tUserIndex].mUniqueNumber))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tAVATAR_OBJECT1 = &mAVATAR_OBJECT[tAttackInfo->mServerIndex1];
	tAVATAR_OBJECT1->mDATA.aAction.aLocation[0] = tAttackInfo->mSenderLocation[0];
	tAVATAR_OBJECT1->mDATA.aAction.aLocation[1] = tAttackInfo->mSenderLocation[1];
	tAVATAR_OBJECT1->mDATA.aAction.aLocation[2] = tAttackInfo->mSenderLocation[2];
	tAVATAR_OBJECT1->SetSpaceIndex();
	if ((tAttackInfo->mServerIndex2 < 0) || (tAttackInfo->mServerIndex2 > (mSERVER.mMAX_USER_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (1 == mUSER[tUserIndex].mAuthInfo.AttackFlag) {
		return;
	}
	tAVATAR_OBJECT2 = &mAVATAR_OBJECT[tAttackInfo->mServerIndex2];
	if ((!tAVATAR_OBJECT2->mCheckValidState) || (tAVATAR_OBJECT2->mUniqueNumber != tAttackInfo->mUniqueNumber2))
	{
		return;
	}
	if (1 == mUSER[tAttackInfo->mServerIndex2].mAuthInfo.AttackFlag) {
		return;
	}
	if (tAVATAR_OBJECT1->mDATA.aLifeValue < 1)
	{
		return;
	}
	if (mUSER[tAttackInfo->mServerIndex2].mMoveZoneResult == 1)
	{
		return;
	}
	if (tAVATAR_OBJECT2->mDATA.aLifeValue < 1)
	{
		return;
	}
	if (tAVATAR_OBJECT2->mDATA.aPShopState == 1)
	{
		return;
	}
	if (tAVATAR_OBJECT2->mDATA.aAction.aSort != 11)
	{
		return;
	}
	if ((tAVATAR_OBJECT1->mDATA.aTribe != tAVATAR_OBJECT2->mDATA.aTribe) && (tAVATAR_OBJECT1->mDATA.aTribe != ReturnAllianceTribe(tAVATAR_OBJECT2->mDATA.aTribe)))
	{
		return;
	}
	if (mUSER[tUserIndex].mCheckMaxAttackPacketNum == 1)
	{
		if ((tAVATAR_OBJECT1->mDATA.aAction.aSkillNumber != tAttackInfo->mAttackActionValue2) || ((tAVATAR_OBJECT1->mDATA.aAction.aSkillGradeNum1 + tAVATAR_OBJECT1->mDATA.aAction.aSkillGradeNum2) != tAttackInfo->mAttackActionValue3))
		{
			return;
		}
	}
	tAttackSuccessValue = (int)mSKILL.ReturnSkillValue(tAttackInfo->mAttackActionValue2, tAttackInfo->mAttackActionValue3, 5);
	if (tAttackSuccessValue < 1)
	{
		return;
	}
	tRandom = rand();
	if ((tRandom % 100) > ((tAttackSuccessValue * 2) - 1))
	{
		return;
	}
	tAVATAR_OBJECT2->mDATA.aAction.aType = mAVATAR_OBJECT[tAttackInfo->mServerIndex2].GetWeaponClass() * 2;
	tAVATAR_OBJECT2->mDATA.aAction.aSort = 1;
	tAVATAR_OBJECT2->mDATA.aAction.aFrame = 0.0f;
	mTRANSFER.B_AVATAR_ACTION_RECV(tAttackInfo->mServerIndex2, tAVATAR_OBJECT2->mUniqueNumber, &tAVATAR_OBJECT2->mDATA, 1);
	mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT2->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
}
//-------------------------------------------------------------------------------------------------