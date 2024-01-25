//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "Shengming.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_AVATAR_OBJECT
//-------------------------------------------------------------------------------------------------
//INSTANCE
AVATAR_OBJECT mAVATAR_OBJECT[MAX_AVATAR_OBJECT_NUM];
//SET_SPACE_INDEX
void AVATAR_OBJECT::Init(void)
{
	mLuck = 0;
	mIndex = 0;
	mMaxLife = 0;
	mMaxMana = 0;
	mCritical = 0;
	mAttackBlock = 0;
	mAttackPower = 0;
	mUniqueNumber = 0;
	mDefensePower = 0;
	mAttackSuccess = 0;
	//Soketler
	SpritEruption = 0;
	InternalWound = 0;
	BloodSucking = 0;
	InnerBleeding = 0;
	ShadowStrike = 0;
	PoisonAttack = 0;
	StrongBlow = 0;
	Glaciation = 0;
	TouchOfDeath = 0;
	SoketDayanik = 0;
	//Soketler
	mSPACE_INDEX[0] = 0;
	mSPACE_INDEX[1] = 0;
	mSPACE_INDEX[2] = 0;
	mCriticalDefense = 0;
	mDuelProcessSort = 0;
	mTradeProcessMenu = 0;
	mDuelProcessState = 0;
	mPartyProcessState = 0;
	mGuildProcessState = 0;
	mTradeProcessState = 0;
	mElementAttackPower = 0;
	mFriendProcessState = 0;
	mElementDefensePower = 0;
	mTeacherProcessState = 0;
	mCheckValidState = false;
	mDuelProcessRemainTime = 0;
	mLastAttackBonusValue = 0.0f;
	mLastAttackBonusProbability = 0;
	mCheckPossibleEatPotion = false;
	::memset(&mPShopInfo, 0x00, sizeof(PSHOP_INFO));
	::memset(&mDATA, 0x00, sizeof(OBJECT_FOR_AVATAR));
	::memset(mDuelProcessAvatarName, 0x00, MAX_AVATAR_NAME_LENGTH);
	::memset(mTradeProcessAvatarName, 0x00, MAX_AVATAR_NAME_LENGTH);
	::memset(mPartyProcessAvatarName, 0x00, MAX_AVATAR_NAME_LENGTH);
	::memset(mGuildProcessAvatarName, 0x00, MAX_AVATAR_NAME_LENGTH);
	::memset(mFriendProcessAvatarName, 0x00, MAX_AVATAR_NAME_LENGTH);
	::memset(mTeacherProcessAvatarName, 0x00, MAX_AVATAR_NAME_LENGTH);
}
void AVATAR_OBJECT::SetSpaceIndex(void)
{
	mSPACE_INDEX[0] = (int)(mAVATAR_OBJECT[mIndex].mDATA.aAction.aLocation[0] / mGAME.MAX_RADIUS);
	mSPACE_INDEX[1] = (int)(mAVATAR_OBJECT[mIndex].mDATA.aAction.aLocation[1] / mGAME.MAX_RADIUS);
	mSPACE_INDEX[2] = (int)(mAVATAR_OBJECT[mIndex].mDATA.aAction.aLocation[2] / mGAME.MAX_RADIUS);
}
//SET_BASIC_ABILITY_FROM_EQUIP
void AVATAR_OBJECT::SetBasicAbilityFromEquip(void)
{
	if (!mCheckValidState)
	{
		return;
	}

	int index01;
	AVATAR_INFO* tAvatarInfo = &mUSER[mIndex].mAvatarInfo;
	int tVitality;
	int tKi;
	int tStrength;
	int tWisdom;
	int tISValue;
	int tIUValue;
	int tIUEffectValue;
	//Soketler
	SpritEruption = 0;
	InternalWound = 0;
	BloodSucking = 0;
	InnerBleeding = 0;
	ShadowStrike = 0;
	PoisonAttack = 0;
	StrongBlow = 0;
	Glaciation = 0;
	TouchOfDeath = 0;
	SoketDayanik = 0;

	for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM; index01++)
	{
		mEquipItem[index01] = mITEM.Search(tAvatarInfo->aEquip[index01][0]);
		mEquipValue[index01] = tAvatarInfo->aEquip[index01][2];
		mItemType[index01] = ItemType(tAvatarInfo->aEquip[index01][0]);
		mEquipSocketValue[index01][0] = tAvatarInfo->EquipSocket[index01][0];
		mEquipSocketValue[index01][1] = tAvatarInfo->EquipSocket[index01][1];
		mEquipSocketValue[index01][2] = tAvatarInfo->EquipSocket[index01][2];
		ShadowStrike += Socket(11, mEquipSocketValue[index01][0], mEquipSocketValue[index01][1], mEquipSocketValue[index01][2]);
		TouchOfDeath += Socket(12, mEquipSocketValue[index01][0], mEquipSocketValue[index01][1], mEquipSocketValue[index01][2]);
		SpritEruption += Socket(13, mEquipSocketValue[index01][0], mEquipSocketValue[index01][1], mEquipSocketValue[index01][2]);
		StrongBlow += Socket(14, mEquipSocketValue[index01][0], mEquipSocketValue[index01][1], mEquipSocketValue[index01][2]);
		BloodSucking += Socket(15, mEquipSocketValue[index01][0], mEquipSocketValue[index01][1], mEquipSocketValue[index01][2]);
		InnerBleeding += Socket(16, mEquipSocketValue[index01][0], mEquipSocketValue[index01][1], mEquipSocketValue[index01][2]);
		Glaciation += Socket(17, mEquipSocketValue[index01][0], mEquipSocketValue[index01][1], mEquipSocketValue[index01][2]);
		InternalWound += Socket(18, mEquipSocketValue[index01][0], mEquipSocketValue[index01][1], mEquipSocketValue[index01][2]);
		PoisonAttack += Socket(19, mEquipSocketValue[index01][0], mEquipSocketValue[index01][1], mEquipSocketValue[index01][2]);
	}

	SoketDayanik = mUTIL.ReturnIBValue(mEquipValue[4]);
	ItemTypeSetBonusu = ItemTypeSetBonus();
	KarakterCani();
	KarakterManasi();
	KarakterAtak();
	KarakterDefence();
	KarakterAtakSucces();
	AttackBlock();
	ElementPower();
	ElementDef();
	Criticial();

	mCriticalDefense = 0;
	for (index01 = 0; index01 < 13; ++index01)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		mCriticalDefense += mEquipItem[index01]->iCapeInfo[1];
		if (index01 != 8)
		{
			switch (ItemTypeSetBonusu)
			{
			case 5:
			case 10:
			case 21:
				mCriticalDefense += (int)((float)mEquipItem[index01]->iCapeInfo[1] * 0.05f);
				break;
			case 22:
				mCriticalDefense += (int)((float)mEquipItem[index01]->iCapeInfo[1] * 0.04f);
				break;
			default:
				continue;
			}
		}
	}
	for (index01 = 0; index01 < 13; ++index01)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		if (index01 != 8)
		{
			if (index01 == 1)
			{
				if (mItemType[index01] == 8)
				{
					mCriticalDefense += YuzdelikOzellikler2(mItemType[index01], index01, mEquipValue[index01], 80);
					if (mCriticalDefense < 1)
						mCriticalDefense = 1;
				}
			}
			else if ((!index01 || index01 == 2 || index01 == 3 || index01 == 4 || index01 == 5 || index01 == 7) && (mItemType[index01] == 1 || mItemType[index01] == 4))
			{
				mCriticalDefense += YuzdelikOzellikler2(mItemType[index01], index01, mEquipValue[index01], 80);
				if (mCriticalDefense < 1)
					mCriticalDefense = 1;
			}
		}
	}

	switch (ItemTypeSetBonusu)
	{
	case 15:
		mCriticalDefense += 2;
		break;
	case 20:
	case 30:
	case 50:
		mCriticalDefense += 7;
		break;
	default:
		mCriticalDefense += 0;
		break;
	}

	switch (tAvatarInfo->SkillIncreaseCritHit)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		mCriticalDefense += tAvatarInfo->SkillIncreaseCritHit;
		break;
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
		mCriticalDefense += 6;
		break;
	default:
		mCriticalDefense += 0;
		break;
	}

	mCriticalDefense += (int)((float)((LegandaryBinekOzellikleri(4, mDATA.aAnimalNumber) / 100.0) * mCriticalDefense));
	mCriticalDefense += (int)((float)(RefineSystem(7) * 0.016f * mCriticalDefense));

	if (tAvatarInfo->aUpradgeValue == 96)
		mCriticalDefense += 10;
	else
		mCriticalDefense += tAvatarInfo->aUpradgeValue / 10;

	if (tAvatarInfo->Bottle[tAvatarInfo->BottleIndex] == 880 && tAvatarInfo->BottleTime > 0)
	{
		mCriticalDefense += (int)((float)mCriticalDefense * 0.05);
	}

	mCriticalDefense += (int)(LedandaryCapeUpradge(tAvatarInfo->aEquip[2][0], tAvatarInfo->aEquip[2][2], 8));
	if (tAvatarInfo->VigilanteScroll > 0)
		mCriticalDefense += 1;

	mLastAttackBonusProbability = 0;
	for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM; index01++)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		mLastAttackBonusProbability += mEquipItem[index01]->iLastAttackBonusInfo[0];
	}
	mLastAttackBonusValue = 0.0f;
	for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM; index01++)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		mLastAttackBonusValue += (float)mEquipItem[index01]->iLastAttackBonusInfo[1];
	}
	mLastAttackBonusValue *= 0.01f;
	mLuck = 0;
	for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM; index01++)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		mLuck += mEquipItem[index01]->iLuck;
		switch (index01)
		{
		case 0:
			tISValue = mUTIL.ReturnISValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnISValue(mEquipValue[index01]));
			if (tISValue > 0)
			{
				mLuck += (tISValue * 12);
			}
			break;
		}
	}
	// Critical Boost Scrolls
	if (mUSER[mIndex].mAvatarInfo.CritBoostScroll > 0)
	{
		mCritical += 5;
	}
}
//GET_WEAPON_CLASS
int AVATAR_OBJECT::GetWeaponClass(void)
{
	if (mEquipItem[7] == NULL)
	{
		return 0;
	}
	switch (mEquipItem[7]->iSort)
	{
	case 13: return 1;
	case 14: return 2;
	case 15: return 3;
	case 16: return 1;
	case 17: return 2;
	case 18: return 3;
	case 19: return 1;
	case 20: return 2;
	case 21: return 3;
	}
	return 0;
}
//GET_MAX_LIFE
int AVATAR_OBJECT::GetMaxLife(void)
{
	return mMaxLife;
}
//GET_MAX_MANA
int AVATAR_OBJECT::GetMaxMana(void)
{
	return mMaxMana;
}
//GET_ATTACK_POWER
int AVATAR_OBJECT::GetAttackPower(void)
{
	int tValue = mAttackPower;
	if (tValue < (int)mPAT.ReturnAttackPower(mUSER[mIndex].mAvatarInfo.aEquip[8][0], mUSER[mIndex].mAvatarInfo.aEquip[8][2], mUSER[mIndex].mAvatarInfo.aEquip[8][1]))
	{
		tValue += tValue;
	}
	else
	{
		tValue += ((int)mPAT.ReturnAttackPower(mUSER[mIndex].mAvatarInfo.aEquip[8][0], mUSER[mIndex].mAvatarInfo.aEquip[8][2], mUSER[mIndex].mAvatarInfo.aEquip[8][1]));
	}
	tValue += mPAT.PetExp200(mUSER[mIndex].mAvatarInfo.aEquip[8][0], mUSER[mIndex].mAvatarInfo.aEquip[8][2], mUSER[mIndex].mAvatarInfo.aEquip[8][1]);
	// Proving Ground Bonus Damage
	if ((mGAME.mWorldInfo.mProvingGroundsPoint[0] > 0) && (mUSER[mIndex].mAvatarInfo.aTribe == 0))
	{
		tValue += mGAME.mWorldInfo.mProvingGroundsPoint[0] * 100;
	}
	if ((mGAME.mWorldInfo.mProvingGroundsPoint[1] > 0) && (mUSER[mIndex].mAvatarInfo.aTribe == 1))
	{
		tValue += mGAME.mWorldInfo.mProvingGroundsPoint[1] * 100;
	}
	if ((mGAME.mWorldInfo.mProvingGroundsPoint[2] > 0) && (mUSER[mIndex].mAvatarInfo.aTribe == 2))
	{
		tValue += mGAME.mWorldInfo.mProvingGroundsPoint[2] * 100;
	}
	if ((mGAME.mWorldInfo.mProvingGroundsPoint[3] > 0) && (mUSER[mIndex].mAvatarInfo.aTribe == 3))
	{
		tValue += mGAME.mWorldInfo.mProvingGroundsPoint[3] * 100;
	}


	if (mUSER[mIndex].mAuthInfo.AuthType != 1)
	{
		if (tValue > 100000)
		{
			return 0;
		}
	}
	return tValue;
}
//GET_DEFENSE_POWER
int AVATAR_OBJECT::GetDefensePower(void)
{
	int tValue = mDefensePower;
	if (tValue < (int)mPAT.ReturnDefensePower(mUSER[mIndex].mAvatarInfo.aEquip[8][0], mUSER[mIndex].mAvatarInfo.aEquip[8][2], mUSER[mIndex].mAvatarInfo.aEquip[8][1]))
	{
		tValue += tValue;
	}
	else
	{
		tValue += ((int)mPAT.ReturnDefensePower(mUSER[mIndex].mAvatarInfo.aEquip[8][0], mUSER[mIndex].mAvatarInfo.aEquip[8][2], mUSER[mIndex].mAvatarInfo.aEquip[8][1]));
	}


	if (mUSER[mIndex].mAuthInfo.AuthType != 1)
	{
		if (tValue > 75000)
		{
			return 0;
		}
	}
	return tValue;
}

//GET_ATTACK_SUCCESS
int AVATAR_OBJECT::GetAttackSuccess(void)
{
	int tValue = mAttackSuccess;
	if (mUSER[mIndex].mAvatarInfo.HideCostumeRegister == 1)
	{
		tValue += 1000000;
	}
	if (mUSER[mIndex].mAuthInfo.AuthType != 1)
	{
		if (tValue > 50000)//50000

		{
			return 0;
		}
	}
	return tValue;
}
//GET_ATTACK_BLOCK
int AVATAR_OBJECT::GetAttackBlock(void)
{
	int tValue = mAttackBlock;
	if (mUSER[mIndex].mAuthInfo.AuthType != 1)
	{
		if (tValue > 75000)//75000
		{
			return 0;
		}
	}
	return tValue;
}
//GET_ELEMENT_ATTACK_POWER
int AVATAR_OBJECT::GetElementAttackPower(void)
{
	int tValue = mElementAttackPower;
	if (mUSER[mIndex].mAuthInfo.AuthType != 1)
	{
		if (tValue > 50000)//50000
		{
			return 0;
		}
	}
	return tValue;
}
//GET_ELEMENT_DEFENSE_POWER
int AVATAR_OBJECT::GetElementDefensePower(void)
{
	int tValue = mElementDefensePower;
	if (mUSER[mIndex].mAuthInfo.AuthType != 1)
	{
		if (tValue > 50000)//50000
		{
			return 0;
		}
	}
	return tValue;
}
//GET_CRITICAL
int AVATAR_OBJECT::GetCritical(void)
{
	int tValue = mCritical;

	if (mUSER[mIndex].mAuthInfo.AuthType != 1)
	{
		if (tValue > 150)
		{
			return 0;
		}
	}
	return tValue;
}
//GET_CRITICAL_DEFENSE
int AVATAR_OBJECT::GetCriticalDefense(void)
{
	return mCriticalDefense;
}
//GET_LAST_ATTACK_BONUS_PROBABILITY
int AVATAR_OBJECT::GetLastAttackBonusProbability(void)
{
	return mLastAttackBonusProbability;
}
//GET_LAST_ATTACK_BONUS_VALUE
float AVATAR_OBJECT::GetLastAttackBonusValue(void)
{
	return mLastAttackBonusValue;
}
//GET_LUCK
int AVATAR_OBJECT::GetLuck(void)
{
	int tValue = mLuck;
	//Defanse Hack
	if (mUSER[mIndex].mEffectValue[11][0] > 0)
	{
		tValue = (int)((float)(tValue * (mUSER[mIndex].mEffectValue[11][0] + 100)) * 0.01f);
	}
	if (mUSER[mIndex].mAuthInfo.AuthType != 1)
	{
		if (tValue > 4500)//4500
		{
			return 0;
		}
	}

	if (mUSER[mIndex].mAuthInfo.AuthType == 1)
	{
		tValue = 3000000;
	}
	return tValue;
}
//GET_BONUS_SKILL_VALUE
int AVATAR_OBJECT::GetBonusSkillValue(int sIndex)
{
	int index01;
	int tValue = 0;

	for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM; index01++)
	{

		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		if (mEquipItem[index01]->iBonusSkillInfo[0][0] == sIndex)
		{
			tValue += mEquipItem[index01]->iBonusSkillInfo[0][1];
		}
		if (mEquipItem[index01]->iBonusSkillInfo[1][0] == sIndex)
		{
			tValue += mEquipItem[index01]->iBonusSkillInfo[1][1];
		}
		if (mEquipItem[index01]->iBonusSkillInfo[2][0] == sIndex)
		{
			tValue += mEquipItem[index01]->iBonusSkillInfo[2][1];
		}
		if (mEquipItem[index01]->iBonusSkillInfo[3][0] == sIndex)
		{
			tValue += mEquipItem[index01]->iBonusSkillInfo[3][1];
		}
		if (mEquipItem[index01]->iBonusSkillInfo[4][0] == sIndex)
		{
			tValue += mEquipItem[index01]->iBonusSkillInfo[4][1];
		}
		if (mEquipItem[index01]->iBonusSkillInfo[5][0] == sIndex)
		{
			tValue += mEquipItem[index01]->iBonusSkillInfo[5][1];
		}
		if (mEquipItem[index01]->iBonusSkillInfo[6][0] == sIndex)
		{
			tValue += mEquipItem[index01]->iBonusSkillInfo[6][1];
		}
		if (mEquipItem[index01]->iBonusSkillInfo[7][0] == sIndex)
		{
			tValue += mEquipItem[index01]->iBonusSkillInfo[7][1];
		}
		tValue += mEquipItem[index01]->iCapeInfo[2];
	}
	return tValue;
}
//GET_REDUCE_MANA_RATIO
int AVATAR_OBJECT::GetReduceManaRatio(void)
{
	int index01;
	int tValue = 0;

	for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM; index01++)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		tValue += mEquipItem[index01]->iCapeInfo[0];
	}
	return tValue;
}
//CHECK_COMMUNITY_WORK
BOOL AVATAR_OBJECT::CheckCommunityWork(void)
{
	if (mDATA.aPShopState != 0)
	{
		return TRUE;
	}
	if (mDuelProcessState != 0)
	{
		return TRUE;
	}
	if (mTradeProcessState != 0)
	{
		return TRUE;
	}
	if (mFriendProcessState != 0)
	{
		return TRUE;
	}
	if (mPartyProcessState != 0)
	{
		return TRUE;
	}
	if (mGuildProcessState != 0)
	{
		return TRUE;
	}
	if (mTeacherProcessState != 0)
	{
		return TRUE;
	}
	return FALSE;
}
//UPDATE
void AVATAR_OBJECT::Update(float tPostTime)
{
	
	if (!mCheckValidState) {
		return;
	}
	if ((mUSER[mIndex].mMoveZoneResult == 1)) {
		mUSER[mIndex].mHeartCheckCount = 0;
		mUSER[mIndex].mHeartCheckTime = ::time(NULL);
		return;
	}
	
	int index01;
	int tMaxAvatarLife;
	int tRecoverAvatarLife;
	int tMaxAvatarMana;
	int tRecoverAvatarMana;
	float tLifeRecoverTime;
	float tManaRecoverTime;
	int tEffectValueState[MAX_AVATAR_EFFECT_SORT_NUM];
	BOOL tCheckChangeEffectValue;
	int tOtherAvatarIndex;
	int iTemp_Auto_time;

	time_t tCountSeconds;
	struct tm* tPresentTime;
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);


	if (mUSER[mIndex].mAuthInfo.AuthType == 0)
	{
		if ((mGAME.mCheckZone049TypeServer) || (mGAME.mCheckZone051TypeServer) || (mGAME.mCheckZone053TypeServer))
		{
			if ((mDATA.aAction.aLocation[0] < mWORLD.mQuadtree[0].mBoxMin[0]) || (mDATA.aAction.aLocation[0] > mWORLD.mQuadtree[0].mBoxMax[0]) || (mDATA.aAction.aLocation[1] < mWORLD.mQuadtree[0].mBoxMin[1]) || (mDATA.aAction.aLocation[1] > mWORLD.mQuadtree[0].mBoxMax[1]) || (mDATA.aAction.aLocation[2] < mWORLD.mQuadtree[0].mBoxMin[2]) || (mDATA.aAction.aLocation[2] > mWORLD.mQuadtree[0].mBoxMax[2]))
			{

				//mUSER[mIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				//return;
			}
		}
	}

	if (mDATA.aPShopState == 1)
	{
		if (!mWORK.CheckPossiblePShopRegion(mDATA.aTribe, mSERVER_INFO.mServerNumber, &mDATA.aAction.aLocation[0]))
		{
			mUSER[mIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}

	SummonQuestBoss();

	if ((mGAME.mTickCount - mUSER[mIndex].mTickCountFor01Second) == 2)
	{
		mUSER[mIndex].mTickCountFor01Second = mGAME.mTickCount;
		//LOG_TO_FILE_1("mUSER[mIndex].uUserSortp2 : %d\n", mUSER[mIndex].mAutoCheckState);
#ifdef __HACKINFO__
		if ((GetTickCount() - mUSER[mIndex].mHackCheckTime) > 300000)
		{
			mUSER[mIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
#endif

		if (mDATA.aAction.aSort == 11)
		{
			mDATA.aAction.aSkillValue--;
			if (mDATA.aAction.aSkillValue < 1)
			{
				mDATA.aAction.aType = GetWeaponClass() * 2;
				mDATA.aAction.aSort = 1;
				mDATA.aAction.aFrame = 0.0f;
				mTRANSFER.B_AVATAR_ACTION_RECV(mIndex, mUniqueNumber, &mDATA, 1);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			}
		}

		tMaxAvatarLife = GetMaxLife();
		tRecoverAvatarLife = 0;

		if (mDATA.aAction.aSort == 31)
		{
			if (mDATA.aLifeValue < tMaxAvatarLife)
			{
				tLifeRecoverTime = mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 2);
				if (tLifeRecoverTime > 0.0f)
				{
					tRecoverAvatarLife = (int)((float)tMaxAvatarLife / tLifeRecoverTime);
					if (tRecoverAvatarLife < 1)
					{
						tRecoverAvatarLife = 1;
					}
					else
					{
						if ((mDATA.aLifeValue + tRecoverAvatarLife) > tMaxAvatarLife)
						{
							tRecoverAvatarLife = tMaxAvatarLife - mDATA.aLifeValue;
						}
					}
				}
			}
		}

		if (tRecoverAvatarLife > 0)
		{
			mDATA.aLifeValue += tRecoverAvatarLife;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(10, mDATA.aLifeValue);
			mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}

		tMaxAvatarMana = GetMaxMana();
		tRecoverAvatarMana = 0;

		if (mDATA.aAction.aSort == 31)
		{
			if (mDATA.aManaValue < tMaxAvatarMana)
			{
				tManaRecoverTime = mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 3);
				if (tManaRecoverTime > 0.0f)
				{
					tRecoverAvatarMana = (int)((float)tMaxAvatarMana / tManaRecoverTime);
					if (tRecoverAvatarMana < 1)
					{
						tRecoverAvatarMana = 1;
					}
					else
					{
						if ((mDATA.aManaValue + tRecoverAvatarMana) > tMaxAvatarMana)
						{
							tRecoverAvatarMana = tMaxAvatarMana - mDATA.aManaValue;
						}
					}
				}
			}

		}

		if (tRecoverAvatarMana > 0)
		{
			mDATA.aManaValue += tRecoverAvatarMana;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(11, mDATA.aManaValue);
			mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}

		//Kanama
		if (mUSER[mIndex].mEffectValue[28][1] > 0)
		{
			mDATA.aLifeValue = (int)((float)mDATA.aLifeValue * 0.95f);
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(10, mDATA.aLifeValue);
			mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}

		tCheckChangeEffectValue = FALSE;

		for (index01 = 0; index01 < MAX_AVATAR_EFFECT_SORT_NUM; index01++)
		{
			tEffectValueState[index01] = 0;
		}

		for (index01 = 0; index01 < MAX_AVATAR_EFFECT_SORT_NUM; index01++)
		{
			if (mUSER[mIndex].mEffectValue[index01][0] < 1)
			{
				continue;
			}
			mUSER[mIndex].mEffectValue[index01][1]--;
			if (mUSER[mIndex].mEffectValue[index01][1] <= 0)
			{
				tCheckChangeEffectValue = TRUE;
				mUSER[mIndex].mEffectValue[index01][0] = 0;
				mUSER[mIndex].mEffectValue[index01][1] = 0;
				mDATA.aEffectValueForView[index01] = 0;
				tEffectValueState[index01] = 2;

				if (index01 == 15)
				{
					mUSER[mIndex].iKindDarkAttack = 0;
				}

				
				if (index01 == 19)
				{
					mAVATAR_OBJECT[mIndex].mCheckPossibleEatPotion = TRUE;
				}
			}
		}
		if (tCheckChangeEffectValue)
		{
			mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
			mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);

			if (mAVATAR_OBJECT[mIndex].mDATA.BotOn == 1)
				AutoBuff();
		}
		
		if (mDuelProcessState == 3)
		{
			if (mUTIL.SearchAvatar(mDuelProcessAvatarName, mIndex) == -1)
			{
				mDuelProcessState = 0;
			}
		}
		if (124 != mSERVER_INFO.mServerNumber) {
			if (mDATA.aDuelState[0] == 1)
			{
				switch (mDATA.aDuelState[2])
				{
				case 1:
					tOtherAvatarIndex = mUTIL.SearchAvatar(mDuelProcessAvatarName, mIndex);
					if (tOtherAvatarIndex == -1)
					{
						mTRANSFER.B_DUEL_END_RECV(3);
						mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
						mDATA.aDuelState[0] = 0;
						mDATA.aDuelState[1] = 0;
						mDATA.aDuelState[2] = 0;
						mCheckPossibleEatPotion = TRUE;
						mDuelProcessState = 0;
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(mIndex, mUniqueNumber, 7, mDATA.aDuelState[0], mDATA.aDuelState[1], mDATA.aDuelState[2]);
						mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
						break;
					}
					if (mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aLifeValue < 1)
					{
						mTRANSFER.B_DUEL_END_RECV(1);
						mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
						mTRANSFER.B_DUEL_END_RECV(1);
						mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
						mDATA.aDuelState[0] = 0;
						mDATA.aDuelState[1] = 0;
						mDATA.aDuelState[2] = 0;
						mCheckPossibleEatPotion = TRUE;
						mDuelProcessState = 0;
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(mIndex, mUniqueNumber, 7, mDATA.aDuelState[0], mDATA.aDuelState[1], mDATA.aDuelState[2]);
						mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
						mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[0] = 0;
						mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[1] = 0;
						mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[2] = 0;
						mAVATAR_OBJECT[tOtherAvatarIndex].mCheckPossibleEatPotion = TRUE;
						mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState = 0;
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(tOtherAvatarIndex, mAVATAR_OBJECT[tOtherAvatarIndex].mUniqueNumber, 7, mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[0], mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[1], mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[2]);
						mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
						break;
					}
					if (mDATA.aLifeValue < 1)
					{
						mTRANSFER.B_DUEL_END_RECV(2);
						mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
						mTRANSFER.B_DUEL_END_RECV(2);
						mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
						mDATA.aDuelState[0] = 0;
						mDATA.aDuelState[1] = 0;
						mDATA.aDuelState[2] = 0;
						mCheckPossibleEatPotion = TRUE;
						mDuelProcessState = 0;
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(mIndex, mUniqueNumber, 7, mDATA.aDuelState[0], mDATA.aDuelState[1], mDATA.aDuelState[2]);
						mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
						mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[0] = 0;
						mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[1] = 0;
						mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[2] = 0;
						mAVATAR_OBJECT[tOtherAvatarIndex].mCheckPossibleEatPotion = TRUE;
						mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState = 0;
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(tOtherAvatarIndex, mAVATAR_OBJECT[tOtherAvatarIndex].mUniqueNumber, 7, mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[0], mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[1], mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[2]);
						mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
						break;
					}
					if (mDuelProcessRemainTime == 1)
					{
						mTRANSFER.B_DUEL_END_RECV(0);
						mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
						mTRANSFER.B_DUEL_END_RECV(0);
						mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
						mDATA.aDuelState[0] = 0;
						mDATA.aDuelState[1] = 0;
						mDATA.aDuelState[2] = 0;
						mCheckPossibleEatPotion = TRUE;
						mDuelProcessState = 0;
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(mIndex, mUniqueNumber, 7, mDATA.aDuelState[0], mDATA.aDuelState[1], mDATA.aDuelState[2]);
						mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
						mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[0] = 0;
						mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[1] = 0;
						mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[2] = 0;
						mAVATAR_OBJECT[tOtherAvatarIndex].mCheckPossibleEatPotion = TRUE;
						mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState = 0;
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(tOtherAvatarIndex, mAVATAR_OBJECT[tOtherAvatarIndex].mUniqueNumber, 7, mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[0], mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[1], mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[2]);
						mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
						break;
					}
					mDuelProcessRemainTime--;
					mTRANSFER.B_DUEL_TIME_INFO(mDuelProcessRemainTime);
					mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					break;
				case 2:
					tOtherAvatarIndex = mUTIL.SearchAvatar(mDuelProcessAvatarName, mIndex);
					if (tOtherAvatarIndex == -1)
					{
						mTRANSFER.B_DUEL_END_RECV(3);
						mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
						mDATA.aDuelState[0] = 0;
						mDATA.aDuelState[1] = 0;
						mDATA.aDuelState[2] = 0;
						mCheckPossibleEatPotion = TRUE;
						mDuelProcessState = 0;
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(mIndex, mUniqueNumber, 7, mDATA.aDuelState[0], mDATA.aDuelState[1], mDATA.aDuelState[2]);
						mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
					}
					break;
				}
			}
		}
		else {
			if (mDATA.aLifeValue < 1) {
				if (1 == mDATA.aDuelState[0]) {
					mGAME.mDuel_124_Pvp = TRUE;
					if (mDATA.aDuelState[2] == 1) {
						mGAME.mDuel_124_AvatarNum[0]--;
						mDATA.aAction.aLocation[0] = -157.0f;
						mDATA.aAction.aLocation[1] = 5.0f;
						mDATA.aAction.aLocation[2] = 1.0f;
					}
					else if (mDATA.aDuelState[2] == 2) {
						mGAME.mDuel_124_AvatarNum[1]--;
						mDATA.aAction.aLocation[0] = 157.0f;
						mDATA.aAction.aLocation[1] = 5.0f;
						mDATA.aAction.aLocation[2] = 1.0f;
					}

					mDATA.aDuelState[0] = 0;
					mDATA.aDuelState[1] = 0;
					mDATA.aDuelState[2] = 0;
					mCheckPossibleEatPotion = TRUE;
					mDuelProcessState = 0;
					mTRANSFER.B_AVATAR_CHANGE_INFO_1(mIndex, mUniqueNumber, 7, mDATA.aDuelState[0], mDATA.aDuelState[1], mDATA.aDuelState[2]);
					mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
			}
		}

		if (mTradeProcessState == 3)
		{
			if (mUTIL.SearchAvatar(mTradeProcessAvatarName, mIndex) == -1)
			{
				mTradeProcessState = 0;
			}
		}
		if (mFriendProcessState == 3)
		{
			if (mUTIL.SearchAvatar(mFriendProcessAvatarName, mIndex) == -1)
			{
				mFriendProcessState = 0;
			}
		}
		if (mTeacherProcessState == 3)
		{
			if (mUTIL.SearchAvatar(mTeacherProcessAvatarName, mIndex) == -1)
			{
				mTeacherProcessState = 0;
			}
		}
		if (mPartyProcessState == 3)
		{
			if (mUTIL.SearchAvatar(mPartyProcessAvatarName, mIndex) == -1)
			{
				mPartyProcessState = 0;
			}
		}
		if (mGuildProcessState == 3)
		{
			if (mUTIL.SearchAvatar(mGuildProcessAvatarName, mIndex) == -1)
			{
				mGuildProcessState = 0;
			}
		}

		if (mUSER[mIndex].mAvatarInfo.BottleTime > 0)
		{
			mUSER[mIndex].mAvatarInfo.BottleTime--;
			if (mUSER[mIndex].mAvatarInfo.BottleTime == 0)
			{
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(112, mUSER[mIndex].mAvatarInfo.BottleTime);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				SetBasicAbilityFromEquip();
				if (mUSER[mIndex].mAvatarInfo.BottlePrice[mUSER[mIndex].mAvatarInfo.BottleIndex] < 1)
				{
					mUSER[mIndex].mAvatarInfo.Bottle[mUSER[mIndex].mAvatarInfo.BottleIndex] = 0;
				}
			}
		}
		
		if (mUSER[mIndex].mAvatarInfo.FuryTime > 0)
		{
			mUSER[mIndex].mAvatarInfo.FuryTime--;
			
			if (mUSER[mIndex].mAvatarInfo.FuryTime == 0)
			{
				mUSER[mIndex].mAvatarInfo.FuryState = 0;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(81, mUSER[mIndex].mAvatarInfo.FuryState);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

				mUSER[mIndex].mAvatarInfo.Fury = 0;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(80, mUSER[mIndex].mAvatarInfo.Fury);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

				mTRANSFER.B_AVATAR_CHANGE_INFO_2(82, mUSER[mIndex].mAvatarInfo.FuryTime);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
		}
		if (mUSER[mIndex].mAvatarInfo.Fury > 10) {
			mUSER[mIndex].mAvatarInfo.Fury = 10;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(80, mUSER[mIndex].mAvatarInfo.Fury);
			mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}

	}

	

	//pet yemi
	if ((mGAME.mTickCount - mUSER[mIndex].mTickCountFor30Second) == 120)
	{
		mUSER[mIndex].mTickCountFor30Second = mGAME.mTickCount;
		if (mUSER[mIndex].mAvatarInfo.PetExpBoost < 1)
		{
			if (mUSER[mIndex].mAvatarInfo.aEquip[8][1] > 0)
			{
				mUSER[mIndex].mAvatarInfo.aEquip[8][1]--;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(12, mUSER[mIndex].mAvatarInfo.aEquip[8][1]);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
		}
	}

	if ((mGAME.mTickCount - mUSER[mIndex].mTickCountFor01MinuteForHealth) == 110)
	{
		mUSER[mIndex].mTickCountFor01MinuteForHealth = mGAME.mTickCount;
		if (mUSER[mIndex].mCheckHealthState)
		{
			mUSER[mIndex].mAvatarInfo.aPlayTime2++;
			if (mUSER[mIndex].mAvatarInfo.aPlayTime2 > 300)
			{
				mUSER[mIndex].mAvatarInfo.aPlayTime2 = 300;
			}
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(16, mUSER[mIndex].mAvatarInfo.aPlayTime2);
			mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mUSER[mIndex].mHealthState = mUTIL.ReturnHealthState(mUSER[mIndex].mAvatarInfo.aPlayTime2);
		}
	}

	if ((mGAME.mTickCount - mUSER[mIndex].mTickCountFor01Minute) == 120)
	{
		mUSER[mIndex].mTickCountFor01Minute = mGAME.mTickCount;
		mUSER[mIndex].mAvatarInfo.aPlayTime1++;
		mUSER[mIndex].mAvatarInfo.OnlineHour++;
		if (mUSER[mIndex].mAvatarInfo.PlayTimeDay < 60)
			mUSER[mIndex].mAvatarInfo.PlayTimeDay++;

		mTRANSFER.B_AVATAR_CHANGE_INFO_2(16, mUSER[mIndex].mAvatarInfo.aPlayTime2);
		mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		if (mUSER[mIndex].mAvatarInfo.DoubleMouthExp2x < 1)
		{
			if (mUSER[mIndex].mAvatarInfo.aAnimalIndex > 9)
			{
				if (mUSER[mIndex].mAvatarInfo.AnimalExp[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10] / 1000000 > 0)
				{
					mUSER[mIndex].mAvatarInfo.AnimalExp[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10] -= 1000000;
					mTRANSFER.B_AVATAR_CHANGE_INFO_2(71, mUSER[mIndex].mAvatarInfo.AnimalExp[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10]);
					mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
			}
		}

		if (mAVATAR_OBJECT[mIndex].mDATA.mFishingState == 1 && mAVATAR_OBJECT[mIndex].mDATA.mFishingStep == 2)
		{
			mAVATAR_OBJECT[mIndex].mDATA.mFishingState = 1;
			mAVATAR_OBJECT[mIndex].mDATA.mFishingStep = 3;
			mUSER[mIndex].GainFish = 1;
			mTRANSFER.B_FISHING2(mIndex, mAVATAR_OBJECT[mIndex].mUniqueNumber, 1, mAVATAR_OBJECT[mIndex].mDATA.mFishingState, mAVATAR_OBJECT[mIndex].mDATA.mFishingStep);
			mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}

		if (mGAME.mCheckZone170Server)
		{
			mUSER[mIndex].mAvatarInfo.FishingTime--;
			if (mUSER[mIndex].mAvatarInfo.FishingTime < 0)
			{
				mUSER[mIndex].mAvatarInfo.FishingTime = 0;
				mTRANSFER.B_RETURN_TO_AUTO_ZONE();
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(65, mUSER[mIndex].mAvatarInfo.FishingTime);
			mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}

		if (mUSER[mIndex].mAvatarInfo.BuffDurationPill > 0)
		{
			mUSER[mIndex].mAvatarInfo.BuffDurationPill--;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(42, mUSER[mIndex].mAvatarInfo.BuffDurationPill);
			mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}

		if (mGAME.mCheckZone118Server)
		{
			mUSER[mIndex].mAvatarInfo.RebirtHall--;
			if (mUSER[mIndex].mAvatarInfo.RebirtHall < 0)
			{
				mUSER[mIndex].mAvatarInfo.RebirtHall = 0;
				mTRANSFER.B_RETURN_TO_AUTO_ZONE();
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(64, mUSER[mIndex].mAvatarInfo.RebirtHall);
			mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}

		if (((mSERVER_INFO.mServerNumber != 1)  //town dragon 
			&& (mSERVER_INFO.mServerNumber != 6)  //town snake
			&& (mSERVER_INFO.mServerNumber != 11) //town tiger 
			&& (mSERVER_INFO.mServerNumber != 140)//town sky
			&& (mSERVER_INFO.mServerNumber != 37) //saigo
			&& (mSERVER_INFO.mServerNumber != 119)
			&& (mSERVER_INFO.mServerNumber != 124)) || mGAME.mWorldInfo.mTribeSymbolBattle == 1)
		{
			// Deduct Boost Scrolls Time
			if (mUSER[mIndex].mAvatarInfo.DamegeBoostScroll > 0)
			{
				mUSER[mIndex].mAvatarInfo.DamegeBoostScroll--;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(46, mUSER[mIndex].mAvatarInfo.DamegeBoostScroll);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				if (mUSER[mIndex].mAvatarInfo.DamegeBoostScroll == 0)
				{
					SetBasicAbilityFromEquip();
				}
			}

			if (mUSER[mIndex].mAvatarInfo.HealtBoostScroll > 0)
			{
				mUSER[mIndex].mAvatarInfo.HealtBoostScroll--;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(47, mUSER[mIndex].mAvatarInfo.HealtBoostScroll);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				if (mUSER[mIndex].mAvatarInfo.HealtBoostScroll == 0)
				{
					SetBasicAbilityFromEquip();
				}
			}

			if (mUSER[mIndex].mAvatarInfo.CritBoostScroll > 0)
			{
				mUSER[mIndex].mAvatarInfo.CritBoostScroll--;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(48, mUSER[mIndex].mAvatarInfo.CritBoostScroll);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				if (mUSER[mIndex].mAvatarInfo.CritBoostScroll == 0)
				{
					SetBasicAbilityFromEquip();
				}
			}

			//LuckyDrop
			if (mUSER[mIndex].mAvatarInfo.LuckyDrop > 0)
			{
				mUSER[mIndex].mAvatarInfo.LuckyDrop--;
				if (mUSER[mIndex].mAvatarInfo.LuckyDrop < 0)
				{
					mUSER[mIndex].mAvatarInfo.LuckyDrop = 0;
				}
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(27, mUSER[mIndex].mAvatarInfo.LuckyDrop);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}

			//Sup Pill Deduct
		
			if (mUSER[mIndex].mAvatarInfo.SuperiorPill > 0)
			{
				mUSER[mIndex].mAvatarInfo.SuperiorPill--;
				if (mUSER[mIndex].mAvatarInfo.SuperiorPill < 0)
				{
					mUSER[mIndex].mAvatarInfo.SuperiorPill = 0;
				}
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(17, mUSER[mIndex].mAvatarInfo.SuperiorPill);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}


			//Exp Pill
			if (mUSER[mIndex].mAvatarInfo.ExpPill > 0)
			{
				mUSER[mIndex].mAvatarInfo.ExpPill--;
				if (mUSER[mIndex].mAvatarInfo.ExpPill < 0)
				{
					mUSER[mIndex].mAvatarInfo.ExpPill = 0;
				}
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(43, mUSER[mIndex].mAvatarInfo.ExpPill);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}



			//2x Pet Pill
			if (mUSER[mIndex].mAvatarInfo.PetExpBoost > 0)
			{
				mUSER[mIndex].mAvatarInfo.PetExpBoost--;
				if (mUSER[mIndex].mAvatarInfo.PetExpBoost < 0)
				{
					mUSER[mIndex].mAvatarInfo.PetExpBoost = 0;
				}
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(44, mUSER[mIndex].mAvatarInfo.PetExpBoost);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}

			//Hormone Pill
			if (mUSER[mIndex].mAvatarInfo.DoubleMouthExp2x > 0)
			{
				mUSER[mIndex].mAvatarInfo.DoubleMouthExp2x--;
				if (mUSER[mIndex].mAvatarInfo.DoubleMouthExp2x < 0)
				{
					mUSER[mIndex].mAvatarInfo.DoubleMouthExp2x = 0;
				}
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(75, mUSER[mIndex].mAvatarInfo.DoubleMouthExp2x);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}

			//if (!mGAME.mCheckZone101TypeServer && !mGAME.mCheckZone126TypeServer)
			//{
			//	//Warrior Scroll
			//	if (mUSER[mIndex].mAvatarInfo.WarriorScroll > 0)
			//	{
			//		
			//	}
			//}

			//Binek hormonu
			if ((mUSER[mIndex].mAvatarInfo.aAnimalIndex >= 0)
				&& (mUSER[mIndex].mAvatarInfo.aAnimalIndex <= (MAX_AVATAR_ANIMAL_NUM + MAX_AVATAR_ANIMAL_NUM - 1))
				&& (mAVATAR_OBJECT[mIndex].mDATA.aAnimalNumber != 0))
			{
				if (mUSER[mIndex].mAvatarInfo.aAnimalTime > 0)
				{
					mUSER[mIndex].mAvatarInfo.aAnimalTime--;
				}
				else
				{
					mUSER[mIndex].mAvatarInfo.aAnimalTime = 0;
				}
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(26, mUSER[mIndex].mAvatarInfo.aAnimalTime);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				if (mDATA.aAnimalOn == 1)
				{
					mUSER[mIndex].mAvatarInfo.MountAbsorb--;
					if (mUSER[mIndex].mAvatarInfo.MountAbsorb < 0)
					{
						mUSER[mIndex].mAvatarInfo.MountAbsorb = 0;
					}
					if (mUSER[mIndex].mAvatarInfo.MountAbsorb == 0)
					{
						mDATA.aAnimalOn = 0;
						mUSER[mIndex].mAvatarInfo.MountAbsorbe = 0;
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(mIndex, mAVATAR_OBJECT[mIndex].mUniqueNumber, 26, mUSER[mIndex].mAvatarInfo.MountAbsorbe, 0, 0);
						mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[mIndex].mDATA.aAction.aLocation[0], 1);
						SetBasicAbilityFromEquip();
					}
					mTRANSFER.B_AVATAR_CHANGE_INFO_2(78, mUSER[mIndex].mAvatarInfo.MountAbsorb);
					mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
			}

			if (mUSER[mIndex].mAvatarInfo.iUseOrnament == 1)
			{
				if (IsUsedOrnament() == 1)
				{
					mUSER[mIndex].mAvatarInfo.iGoldOrnamentRemainsTime--;
					mTRANSFER.B_AVATAR_CHANGE_INFO_2(40, mUSER[mIndex].mAvatarInfo.iGoldOrnamentRemainsTime);
				}
				else if (IsUsedOrnament() == 2)
				{
					mUSER[mIndex].mAvatarInfo.iSilverOrnamentRemainsTime--;
					mTRANSFER.B_AVATAR_CHANGE_INFO_2(32, mUSER[mIndex].mAvatarInfo.iSilverOrnamentRemainsTime);
				}
				if (mUSER[mIndex].mAvatarInfo.iSilverOrnamentRemainsTime <= 0 && mUSER[mIndex].mAvatarInfo.iGoldOrnamentRemainsTime <= 0)
				{
					mUSER[mIndex].mAvatarInfo.iUseOrnament = 0;
				}
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				SetBasicAbilityFromEquip();
			}
		}


		if (mUSER[mIndex].mAuthInfo.AuthType == 0)
		{
			if (mGAME.mCheckZone101TypeServer)
			{
				//mUSER[mIndex].mAvatarInfo.SolemGrounds--;
				if (mUSER[mIndex].mAvatarInfo.SolemGrounds < 0)
				{
					mUSER[mIndex].mAvatarInfo.SolemGrounds = 0;
					mTRANSFER.B_RETURN_TO_AUTO_ZONE();
					mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(18, mUSER[mIndex].mAvatarInfo.SolemGrounds);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}

			if (mGAME.mCheckZone125Server)
			{
				mUSER[mIndex].mAvatarInfo.EdgeOfTaiyan--;
				if (mUSER[mIndex].mAvatarInfo.EdgeOfTaiyan < 0)
				{
					mUSER[mIndex].mAvatarInfo.EdgeOfTaiyan = 0;
					mTRANSFER.B_RETURN_TO_AUTO_ZONE();
					mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(21, mUSER[mIndex].mAvatarInfo.EdgeOfTaiyan);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}

			if (mGAME.mCheckZone126TypeServer)
			{
				mUSER[mIndex].mAvatarInfo.ScrollOfSeekers--;
				if (mUSER[mIndex].mAvatarInfo.ScrollOfSeekers < 0)
				{
					mUSER[mIndex].mAvatarInfo.ScrollOfSeekers = 0;
					mTRANSFER.B_RETURN_TO_AUTO_ZONE();
					mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(22, mUSER[mIndex].mAvatarInfo.ScrollOfSeekers);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}

			if (mGAME.mCheckZone234TypeServer)
			{
				mUSER[mIndex].mAvatarInfo.IslandOfBlood--;
				if (mUSER[mIndex].mAvatarInfo.IslandOfBlood < 0)
				{
					mUSER[mIndex].mAvatarInfo.IslandOfBlood = 0;
					mTRANSFER.B_RETURN_TO_AUTO_ZONE();
					mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(33, mUSER[mIndex].mAvatarInfo.IslandOfBlood);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}

			if (mGAME.mCheckZone235TypeServer)
			{
				mUSER[mIndex].mAvatarInfo.IslandOfSoulMReal1--;
				if (mUSER[mIndex].mAvatarInfo.IslandOfSoulMReal1 < 0)
				{
					mUSER[mIndex].mAvatarInfo.IslandOfSoulMReal1 = 0;
					mTRANSFER.B_RETURN_TO_AUTO_ZONE();
					mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(34, mUSER[mIndex].mAvatarInfo.IslandOfSoulMReal1);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}

			if (mGAME.mCheckZone236TypeServer)
			{
				mUSER[mIndex].mAvatarInfo.IslandOfSoulMReal2--;
				if (mUSER[mIndex].mAvatarInfo.IslandOfSoulMReal2 < 0)
				{
					mUSER[mIndex].mAvatarInfo.IslandOfSoulMReal2 = 0;
					mTRANSFER.B_RETURN_TO_AUTO_ZONE();
					mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(35, mUSER[mIndex].mAvatarInfo.IslandOfSoulMReal2);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}

			if (mGAME.mCheckZone237TypeServer)
			{
				mUSER[mIndex].mAvatarInfo.IslandOfSoulMReal3--;
				if (mUSER[mIndex].mAvatarInfo.IslandOfSoulMReal3 < 0)
				{
					mUSER[mIndex].mAvatarInfo.IslandOfSoulMReal3 = 0;
					mTRANSFER.B_RETURN_TO_AUTO_ZONE();
					mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(36, mUSER[mIndex].mAvatarInfo.IslandOfSoulMReal3);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}

			if (mGAME.mCheckZone238TypeServer)
			{
				mUSER[mIndex].mAvatarInfo.IslandOfSoulMReal4--;
				if (mUSER[mIndex].mAvatarInfo.IslandOfSoulMReal4 < 0)
				{
					mUSER[mIndex].mAvatarInfo.IslandOfSoulMReal4 = 0;
					mTRANSFER.B_RETURN_TO_AUTO_ZONE();
					mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(37, mUSER[mIndex].mAvatarInfo.IslandOfSoulMReal4);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}

			if (mGAME.mCheckZone239TypeServer)
			{
				mUSER[mIndex].mAvatarInfo.IslandOfSoulMReal5--;
				if (mUSER[mIndex].mAvatarInfo.IslandOfSoulMReal5 < 0)
				{
					mUSER[mIndex].mAvatarInfo.IslandOfSoulMReal5 = 0;
					mTRANSFER.B_RETURN_TO_AUTO_ZONE();
					mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(38, mUSER[mIndex].mAvatarInfo.IslandOfSoulMReal5);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}

			if (mGAME.mCheckZone240TypeServer)
			{
				mUSER[mIndex].mAvatarInfo.IslandOfSoulMReal6--;
				if (mUSER[mIndex].mAvatarInfo.IslandOfSoulMReal6 < 0)
				{
					mUSER[mIndex].mAvatarInfo.IslandOfSoulMReal6 = 0;
					mTRANSFER.B_RETURN_TO_AUTO_ZONE();
					mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(39, mUSER[mIndex].mAvatarInfo.IslandOfSoulMReal6);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
		}
	}


	if ((mGAME.mTickCount - mUSER[mIndex].mTickCountFor01Minute_2) == 120)
	{
		mUSER[mIndex].mTickCountFor01Minute_2 = mGAME.mTickCount;

		/** 2009. 11. 18 : ��� �ع� �ý��� (wolf) */
	}


}
//PROCESS_FOR_CREATE_EFFECT_VALUE
void AVATAR_OBJECT::ProcessForCreateEffectValue(ACTION_INFO* tAction)
{
	if ((mDATA.aAction.aSkillNumber != tAction->aSkillNumber) || (mDATA.aAction.aSkillGradeNum1 != tAction->aSkillGradeNum1) || (mDATA.aAction.aSkillGradeNum2 != tAction->aSkillGradeNum2))
	{
		return;
	}
	if (tAction->aSkillNumber != 0)
	{
		// µ¿Çà¹«°øÀº °Ë»ç¿¡Œ­ ÁŠ¿Ü.
		if ((tAction->aSkillNumber != 76) && (tAction->aSkillNumber != 77) && (tAction->aSkillNumber != 78) && (tAction->aSkillNumber != 79) && (tAction->aSkillNumber != 80) && (tAction->aSkillNumber != 81))
		{
			if ((tAction->aSkillGradeNum1 > mUSER[mIndex].GetMaxSkillGradeNum(tAction->aSkillNumber)) || (tAction->aSkillGradeNum2 > this->GetBonusSkillValue(tAction->aSkillNumber)))
			{
				return;
			}
		}
	}

	int index01;

	AVATAR_OBJECT* tAVATAR_OBJECT;
	int tRecoverLifeValue;
	int tRecoverManaValue;
	mUSER[mIndex].mSupportSkillTimeUpRatio = 1;
	int tEffectValueState[MAX_AVATAR_EFFECT_SORT_NUM];
	for (index01 = 0; index01 < MAX_AVATAR_EFFECT_SORT_NUM; index01++)
	{
		tEffectValueState[index01] = 0;
	}

	if (mUSER[mIndex].mAvatarInfo.BuffDurationPill > 0)
	{
		mUSER[mIndex].mSupportSkillTimeUpRatio = 2;
	}
	else
	{
		mUSER[mIndex].mSupportSkillTimeUpRatio = 1;
	}

	switch (mDATA.aAction.aSkillNumber)
	{
	case   6: //Albız
	case  25:
	case  44:
		mUSER[mIndex].mEffectValue[8][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 11);
		mUSER[mIndex].mEffectValue[8][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
		mDATA.aEffectValueForView[8] = mUSER[mIndex].mEffectValue[8][0];
		tEffectValueState[8] = 1;
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case   7: //Elemental Atak ve Saldırı hızı
	case  26:
	case  45:
		mUSER[mIndex].mEffectValue[4][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 16);
		mUSER[mIndex].mEffectValue[4][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
		mDATA.aEffectValueForView[4] = mUSER[mIndex].mEffectValue[4][0];
		tEffectValueState[4] = 1;
		mUSER[mIndex].mEffectValue[6][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 18);
		mUSER[mIndex].mEffectValue[6][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
		mDATA.aEffectValueForView[6] = mUSER[mIndex].mEffectValue[6][0];
		tEffectValueState[6] = 1;
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case  11: //Defans Buff
	case  34:
	case  49:
		if ((mEquipItem[7] == NULL) || ((mEquipItem[7]->iSort != 13) && (mEquipItem[7]->iSort != 17) && (mEquipItem[7]->iSort != 19)))
		{
			return;
		}
		mUSER[mIndex].mEffectValue[1][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 13);
		mUSER[mIndex].mEffectValue[1][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
		mDATA.aEffectValueForView[1] = mUSER[mIndex].mEffectValue[1][0];
		tEffectValueState[1] = 1;
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case  15: //Atak Power Buff
	case  30:
	case  53:
		if ((mEquipItem[7] == NULL) || ((mEquipItem[7]->iSort != 14) && (mEquipItem[7]->iSort != 16) && (mEquipItem[7]->iSort != 20)))
		{
			return;
		}
		mUSER[mIndex].mEffectValue[0][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 12);
		mUSER[mIndex].mEffectValue[0][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
		mDATA.aEffectValueForView[0] = mUSER[mIndex].mEffectValue[0][0];
		tEffectValueState[0] = 1;
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case  19: //Dodge ve hareket hızı buff
	case  38:
	case  57:
		if ((mEquipItem[7] == NULL) || ((mEquipItem[7]->iSort != 15) && (mEquipItem[7]->iSort != 18) && (mEquipItem[7]->iSort != 21)))
		{
			return;
		}
		mUSER[mIndex].mEffectValue[3][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 15);
		mUSER[mIndex].mEffectValue[3][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
		mDATA.aEffectValueForView[3] = mUSER[mIndex].mEffectValue[3][0];
		tEffectValueState[3] = 1;
		mUSER[mIndex].mEffectValue[7][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 19);
		mUSER[mIndex].mEffectValue[7][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
		mDATA.aEffectValueForView[7] = mUSER[mIndex].mEffectValue[7][0];
		tEffectValueState[7] = 1;
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case  82:
		//Normal d.t
		mUSER[mIndex].mEffectValue[9][0] = 0;
		mUSER[mIndex].mEffectValue[9][1] = 0;
		mDATA.aEffectValueForView[9] = 0;
		// EffectValue = 34 beyaz
		mUSER[mIndex].mEffectValue[34][0] = 0;
		mUSER[mIndex].mEffectValue[34][1] = 0;
		mDATA.aEffectValueForView[34] = 0;
		// EffectValue = 33 Siyah
		mUSER[mIndex].mEffectValue[33][0] = 0;
		mUSER[mIndex].mEffectValue[33][1] = 0;
		mDATA.aEffectValueForView[33] = 0;
		// EffectValue = 32 Yeşil
		mUSER[mIndex].mEffectValue[32][0] = 0;
		mUSER[mIndex].mEffectValue[32][1] = 0;
		mDATA.aEffectValueForView[32] = 0;
		// EffectValue = 31 Mor
		mUSER[mIndex].mEffectValue[31][0] = 0;
		mUSER[mIndex].mEffectValue[31][1] = 0;
		mDATA.aEffectValueForView[31] = 0;
		// EffectValue = 30 Mavi
		mUSER[mIndex].mEffectValue[30][0] = 0;
		mUSER[mIndex].mEffectValue[30][1] = 0;
		mDATA.aEffectValueForView[30] = 0;
		// EffectValue = 29 Turuncu Kırmızı
		mUSER[mIndex].mEffectValue[29][0] = 0;
		mUSER[mIndex].mEffectValue[29][1] = 0;
		mDATA.aEffectValueForView[29] = 0;

		if (mAVATAR_OBJECT[mIndex].mDATA.aAnimalNumber > 2265 && mAVATAR_OBJECT[mIndex].mDATA.aAnimalNumber < 2276 ||
			mUTIL.ReturnIUValueWithLevelLimit(145, mUTIL.ReturnIUValue(mEquipValue[1])) >= 30 &&
			mUTIL.ReturnIUValueWithLevelLimit(145, mUTIL.ReturnIUValue(mEquipValue[1])) < 40)
		{
			mUSER[mIndex].mEffectValue[29][0] = (int)(mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 20) * (float)GetMaxLife() * 0.01f);
			mUSER[mIndex].mEffectValue[29][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
			mDATA.aEffectValueForView[29] = mUSER[mIndex].mEffectValue[29][0];
			tEffectValueState[29] = 1;
			mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
			mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		else if (mAVATAR_OBJECT[mIndex].mDATA.aAnimalNumber > 2275 && mAVATAR_OBJECT[mIndex].mDATA.aAnimalNumber < 2286 ||
			mUTIL.ReturnIUValueWithLevelLimit(145, mUTIL.ReturnIUValue(mEquipValue[1])) >= 50 &&
			mUTIL.ReturnIUValueWithLevelLimit(145, mUTIL.ReturnIUValue(mEquipValue[1])) < 60)
		{
			mUSER[mIndex].mEffectValue[30][0] = (int)(mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 20) * (float)GetMaxLife() * 0.01f);
			mUSER[mIndex].mEffectValue[30][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
			mDATA.aEffectValueForView[30] = mUSER[mIndex].mEffectValue[30][0];
			tEffectValueState[30] = 1;
			mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
			mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		else if (mAVATAR_OBJECT[mIndex].mDATA.aAnimalNumber == 2316)
		{
			mUSER[mIndex].mEffectValue[31][0] = (int)(mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 20) * (float)GetMaxLife() * 0.01f);
			mUSER[mIndex].mEffectValue[31][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
			mDATA.aEffectValueForView[31] = mUSER[mIndex].mEffectValue[31][0];
			tEffectValueState[31] = 1;
			mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
			mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		else if (mAVATAR_OBJECT[mIndex].mDATA.aAnimalNumber == 2317)
		{
			mUSER[mIndex].mEffectValue[32][0] = (int)(mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 20) * (float)GetMaxLife() * 0.01f);
			mUSER[mIndex].mEffectValue[32][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
			mDATA.aEffectValueForView[32] = mUSER[mIndex].mEffectValue[32][0];
			tEffectValueState[32] = 1;
			mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
			mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		else if (mAVATAR_OBJECT[mIndex].mDATA.aAnimalNumber > 1916 && mAVATAR_OBJECT[mIndex].mDATA.aAnimalNumber < 1927 ||
			mUTIL.ReturnIUValueWithLevelLimit(145, mUTIL.ReturnIUValue(mEquipValue[1])) >= 40 &&
			mUTIL.ReturnIUValueWithLevelLimit(145, mUTIL.ReturnIUValue(mEquipValue[1])) < 50)
		{
			mUSER[mIndex].mEffectValue[32][0] = (int)(mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 20) * (float)GetMaxLife() * 0.01f);
			mUSER[mIndex].mEffectValue[32][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
			mDATA.aEffectValueForView[32] = mUSER[mIndex].mEffectValue[32][0];
			tEffectValueState[32] = 1;
			mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
			mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		else if (mAVATAR_OBJECT[mIndex].mDATA.aAnimalNumber > 2421 && mAVATAR_OBJECT[mIndex].mDATA.aAnimalNumber < 2432)
		{
			mUSER[mIndex].mEffectValue[33][0] = (int)(mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 20) * (float)GetMaxLife() * 0.01f);
			mUSER[mIndex].mEffectValue[33][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
			mDATA.aEffectValueForView[33] = mUSER[mIndex].mEffectValue[33][0];
			tEffectValueState[33] = 1;
			mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
			mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		else if (mAVATAR_OBJECT[mIndex].mDATA.aAnimalNumber > 1926 && mAVATAR_OBJECT[mIndex].mDATA.aAnimalNumber < 1937 ||
			mUTIL.ReturnIUValueWithLevelLimit(145, mUTIL.ReturnIUValue(mEquipValue[1])) >= 20 &&
			mUTIL.ReturnIUValueWithLevelLimit(145, mUTIL.ReturnIUValue(mEquipValue[1])) < 30)
		{
			mUSER[mIndex].mEffectValue[34][0] = (int)(mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 20) * (float)GetMaxLife() * 0.01f);
			mUSER[mIndex].mEffectValue[34][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
			mDATA.aEffectValueForView[34] = mUSER[mIndex].mEffectValue[34][0];
			tEffectValueState[34] = 1;
			mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
			mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		else if (mAVATAR_OBJECT[mIndex].mDATA.aAnimalNumber > 2431 && mAVATAR_OBJECT[mIndex].mDATA.aAnimalNumber < 2442)
		{
			mUSER[mIndex].mEffectValue[34][0] = (int)(mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 20) * (float)GetMaxLife() * 0.01f);
			mUSER[mIndex].mEffectValue[34][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
			mDATA.aEffectValueForView[34] = mUSER[mIndex].mEffectValue[34][0];
			tEffectValueState[34] = 1;
			mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
			mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		else
		{
			mUSER[mIndex].mEffectValue[9][0] = (int)(mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 20) * (float)GetMaxLife() * 0.01f);
			mUSER[mIndex].mEffectValue[9][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
			mDATA.aEffectValueForView[9] = mUSER[mIndex].mEffectValue[9][0];
			tEffectValueState[9] = 1;
			mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
			mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		return;
	case  83: //Kritik Buffı
		mUSER[mIndex].mEffectValue[10][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 22);
		mUSER[mIndex].mEffectValue[10][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
		mDATA.aEffectValueForView[10] = mUSER[mIndex].mEffectValue[10][0];
		tEffectValueState[10] = 1;
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case  84: 
		mUSER[mIndex].mEffectValue[11][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 21);
		mUSER[mIndex].mEffectValue[11][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
		mDATA.aEffectValueForView[11] = mUSER[mIndex].mEffectValue[11][0];
		tEffectValueState[11] = 1;
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case 106: //Can Yenileme
	case 108:
	case 110:
		if ((mIndex == mDATA.aAction.aTargetObjectIndex) && (mUniqueNumber == mDATA.aAction.aTargetObjectUniqueNumber))
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		if ((mDATA.aAction.aTargetObjectIndex < 0) || (mDATA.aAction.aTargetObjectIndex > (mSERVER.mMAX_USER_NUM - 1)))
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		tAVATAR_OBJECT = &mAVATAR_OBJECT[mDATA.aAction.aTargetObjectIndex];
		if ((!tAVATAR_OBJECT->mCheckValidState) || (tAVATAR_OBJECT->mUniqueNumber != mDATA.aAction.aTargetObjectUniqueNumber))
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		if (tAVATAR_OBJECT->mDATA.aLifeValue < 1)
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		if (tAVATAR_OBJECT->mDATA.aPShopState == 1)
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		if (!mGAME.CheckPossibleAttackTarget(1, tAVATAR_OBJECT->mDATA.aAction.aSort))
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		if (tAVATAR_OBJECT->mDATA.aLifeValue >= tAVATAR_OBJECT->GetMaxLife())
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		tRecoverLifeValue = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 2);
		if ((tAVATAR_OBJECT->mDATA.aLifeValue + tRecoverLifeValue) > tAVATAR_OBJECT->GetMaxLife())
		{
			tRecoverLifeValue = tAVATAR_OBJECT->GetMaxLife() - tAVATAR_OBJECT->mDATA.aLifeValue;
		}
		if (tRecoverLifeValue < 1)
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		tAVATAR_OBJECT->mDATA.aLifeValue += tRecoverLifeValue;
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(mDATA.aAction.aTargetObjectIndex, mDATA.aAction.aTargetObjectUniqueNumber, 8, tRecoverLifeValue, 0, 0);
		mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case 107: //Mana yenileme
	case 109:
	case 111:
		if ((mIndex == mDATA.aAction.aTargetObjectIndex) && (mUniqueNumber == mDATA.aAction.aTargetObjectUniqueNumber))
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		if ((mDATA.aAction.aTargetObjectIndex < 0) || (mDATA.aAction.aTargetObjectIndex > (mSERVER.mMAX_USER_NUM - 1)))
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		tAVATAR_OBJECT = &mAVATAR_OBJECT[mDATA.aAction.aTargetObjectIndex];
		if ((!tAVATAR_OBJECT->mCheckValidState) || (tAVATAR_OBJECT->mUniqueNumber != mDATA.aAction.aTargetObjectUniqueNumber))
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		if (tAVATAR_OBJECT->mDATA.aLifeValue < 1)
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		if (tAVATAR_OBJECT->mDATA.aPShopState == 1)
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		if (!mGAME.CheckPossibleAttackTarget(1, tAVATAR_OBJECT->mDATA.aAction.aSort))
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		if (tAVATAR_OBJECT->mDATA.aManaValue >= tAVATAR_OBJECT->GetMaxMana())
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		tRecoverManaValue = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 3);
		if ((tAVATAR_OBJECT->mDATA.aManaValue + tRecoverManaValue) > tAVATAR_OBJECT->GetMaxMana())
		{
			tRecoverManaValue = tAVATAR_OBJECT->GetMaxMana() - tAVATAR_OBJECT->mDATA.aManaValue;
		}
		if (tRecoverManaValue < 1)
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		tAVATAR_OBJECT->mDATA.aManaValue += tRecoverManaValue;
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(mDATA.aAction.aTargetObjectIndex, mDATA.aAction.aTargetObjectUniqueNumber, 9, tRecoverManaValue, 0, 0);
		mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case 103: //Yansıma
		mUSER[mIndex].mEffectValue[12][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 23);
		mUSER[mIndex].mEffectValue[12][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
		mDATA.aEffectValueForView[12] = mUSER[mIndex].mEffectValue[12][0];
		tEffectValueState[12] = 1;
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case 104: //Mistik
		mUSER[mIndex].mEffectValue[13][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 24);
		mUSER[mIndex].mEffectValue[13][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
		mDATA.aEffectValueForView[13] = mUSER[mIndex].mEffectValue[13][0];
		tEffectValueState[13] = 1;
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case 105: //Zihin Yayma
		mUSER[mIndex].mEffectValue[14][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 25);
		mUSER[mIndex].mEffectValue[14][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
		mDATA.aEffectValueForView[14] = mUSER[mIndex].mEffectValue[14][0];
		tEffectValueState[14] = 1;
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case  76: //Atak Rate Parti Buffı
		//Parti kişi sayısı kontrol
		if (strcmp(mUSER[mIndex].mAvatarInfo.aPartyName[4], "") == 0)
		{
			return;
		}
		mUSER[mIndex].mEffectValue[2][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 14);
		mUSER[mIndex].mEffectValue[2][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10);
		mDATA.aEffectValueForView[2] = mUSER[mIndex].mEffectValue[2][0];
		tEffectValueState[2] = 1;
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case  77: //Dodge Dodge Buffı
		//Parti kişi sayısı kontrol
		if (strcmp(mUSER[mIndex].mAvatarInfo.aPartyName[4], "") == 0)
		{
			return;
		}
		mUSER[mIndex].mEffectValue[3][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 15);
		mUSER[mIndex].mEffectValue[3][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10);
		mDATA.aEffectValueForView[3] = mUSER[mIndex].mEffectValue[3][0];
		tEffectValueState[3] = 1;
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case  79: //Demir Ten Parti Buffı
		//Parti kişi sayısı kontrol
		if (strcmp(mUSER[mIndex].mAvatarInfo.aPartyName[4], "") == 0)
		{
			return;
		}
		mUSER[mIndex].mEffectValue[9][0] = (int)(mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 20) * (float)GetMaxLife() * 0.01f);
		mUSER[mIndex].mEffectValue[9][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10);
		mDATA.aEffectValueForView[9] = mUSER[mIndex].mEffectValue[9][0];
		tEffectValueState[9] = 1;
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case  81: //Increase Critik 
		//Parti kişi sayısı kontrol
		if (strcmp(mUSER[mIndex].mAvatarInfo.aPartyName[4], "") == 0)
		{
			return;
		}
		mUSER[mIndex].mEffectValue[10][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 22);
		mUSER[mIndex].mEffectValue[10][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10);
		mDATA.aEffectValueForView[10] = mUSER[mIndex].mEffectValue[10][0];
		tEffectValueState[10] = 1;
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	}
}
//PROCESS_FOR_DELETE_EFFECT_VALUE
void AVATAR_OBJECT::ProcessForDeleteEffectValue(void)
{
	int index01;
	BOOL tCheckChangeEffectValueState;
	int tEffectValueState[MAX_AVATAR_EFFECT_SORT_NUM];

	tCheckChangeEffectValueState = FALSE;
	for (index01 = 0; index01 < MAX_AVATAR_EFFECT_SORT_NUM; index01++)
	{
		tEffectValueState[index01] = 0;
	}
	for (index01 = 0; index01 < MAX_AVATAR_EFFECT_SORT_NUM; index01++)
	{
		if (mUSER[mIndex].mEffectValue[index01][0] < 1)
		{
			continue;
		}
		tCheckChangeEffectValueState = TRUE;
		mUSER[mIndex].mEffectValue[index01][0] = 0;
		mUSER[mIndex].mEffectValue[index01][1] = 0;
		mDATA.aEffectValueForView[index01] = 0;
		mUSER[mIndex].iKindDarkAttack = 0;
		tEffectValueState[index01] = 2;
	}
	if (tCheckChangeEffectValueState)
	{
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
	}
}
//PROCESS_FOR_DEATH
void AVATAR_OBJECT::ProcessForDeath(void)
{
	int index01;
	// # Defense Hack # {
	mCheckDeath = true;
	mCheckCount = 9;
	// # }
	BOOL tCheckChangeEffectValueState;
	int tEffectValueState[MAX_AVATAR_EFFECT_SORT_NUM];

	tCheckChangeEffectValueState = FALSE;
	for (index01 = 0; index01 < MAX_AVATAR_EFFECT_SORT_NUM; index01++)
	{
		tEffectValueState[index01] = 0;
	}
	for (index01 = 0; index01 < MAX_AVATAR_EFFECT_SORT_NUM; index01++)
	{
		//if (mUSER[mIndex].mEffectValue[index01][0] < 1)
		//{
		//	continue;
		//}
		tCheckChangeEffectValueState = TRUE;
		mUSER[mIndex].mEffectValue[index01][0] = 0;
		mUSER[mIndex].mEffectValue[index01][1] = 0;
		mDATA.aEffectValueForView[index01] = 0;
		tEffectValueState[index01] = 2;
	}
	if (tCheckChangeEffectValueState)
	{
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
	}
	mAVATAR_OBJECT[mIndex].mCheckPossibleEatPotion = TRUE;
}
//PROCESS_FOR_TRADE_INFO
void AVATAR_OBJECT::ProcessForTradeInfo(void)
{
	int tOtherAvatarIndex;

	if (mTradeProcessState != 4)
	{
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(mTradeProcessAvatarName, mIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState != 4)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessAvatarName, mDATA.aName) != 0)
	{
		return;
	}
	mTRANSFER.B_TRADE_STATE_RECV(mUSER[mIndex].mAvatarInfo.aTradeMoney, mUSER[mIndex].mAvatarInfo.aTrade, mUSER[mIndex].mAvatarInfo.TradeSocket, mUSER[mIndex].mAvatarInfo.TradeBar);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//RETURN_QUEST_PRESENT_STATE
int AVATAR_OBJECT::ReturnQuestPresentState(void)
{
	int index01;
	int index02;
	QUEST_INFO* tQUEST_INFO;

	if ((mUSER[mIndex].mAvatarInfo.aQuestInfo[1] == 0) && (mUSER[mIndex].mAvatarInfo.aQuestInfo[2] == 0) && (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] == 0) && (mUSER[mIndex].mAvatarInfo.aQuestInfo[4] == 0))
	{
		tQUEST_INFO = mQUEST.Search(mUSER[mIndex].mAvatarInfo.aTribe, (mUSER[mIndex].mAvatarInfo.aQuestInfo[0] + 1));
		if (tQUEST_INFO == NULL)
		{
			return 0;
		}
		if (mUSER[mIndex].mAvatarInfo.aLevel1 < tQUEST_INFO->qLevel)
		{
			return 0;
		}
		return 1;
	}
	if (mUSER[mIndex].mAvatarInfo.aQuestInfo[1] == 1)
	{
		tQUEST_INFO = mQUEST.Search(mUSER[mIndex].mAvatarInfo.aTribe, mUSER[mIndex].mAvatarInfo.aQuestInfo[0]);
		if (tQUEST_INFO == NULL)
		{
			return 0;
		}
		switch (mUSER[mIndex].mAvatarInfo.aQuestInfo[2])
		{
		case 1: //[žóœºÅÍ Á×ÀÌ±â]
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] != tQUEST_INFO->qSolution[0])
			{
				return 0;
			}
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[4] < tQUEST_INFO->qSolution[1])
			{
				return 2;
			}
			return 3;
		case 2: //[ŸÆÀÌÅÛ ÀÔŒö]
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] != tQUEST_INFO->qSolution[0])
			{
				return 0;
			}
			for (index01 = 0; index01 < 2; index01++)
			{
				for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
				{
					if (mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][0] == tQUEST_INFO->qSolution[0])
					{
						break;
					}
				}
				if (index02 < MAX_INVENTORY_SLOT_NUM)
				{
					break;
				}
			}
			if (index01 == 2)
			{
				return 2;
			}
			return 3;
		case 3: //[ŸÆÀÌÅÛ ÀüŽÞ]
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] != tQUEST_INFO->qSolution[0])
			{
				return 0;
			}
			for (index01 = 0; index01 < 2; index01++)
			{
				for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
				{
					if (mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][0] == tQUEST_INFO->qSolution[0])
					{
						break;
					}
				}
				if (index02 < MAX_INVENTORY_SLOT_NUM)
				{
					break;
				}
			}
			if (index01 == 2)
			{
				return 2;
			}
			return 3;
		case 4: //[ŸÆÀÌÅÛ ¹ÞŸÆ¿À±â]
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] != tQUEST_INFO->qSolution[0])
			{
				return 0;
			}
			for (index01 = 0; index01 < 2; index01++)
			{
				for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
				{
					if (mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][0] == tQUEST_INFO->qSolution[0])
					{
						break;
					}
				}
				if (index02 < MAX_INVENTORY_SLOT_NUM)
				{
					break;
				}
			}
			if (index01 == 2)
			{
				return 2;
			}
			return 3;
		case 5: //[ŽëÀå Á×ÀÌ±â]
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] != tQUEST_INFO->qSolution[0])
			{
				return 0;
			}
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[4] < 1)
			{
				return 2;
			}
			return 3;
		case 6: //[ŸÆÀÌÅÛ ±³È¯ÇÏ±â]
			switch (mUSER[mIndex].mAvatarInfo.aQuestInfo[3])
			{
			case 1: //[±³È¯ Àü]
				if (mUSER[mIndex].mAvatarInfo.aQuestInfo[4] != tQUEST_INFO->qSolution[0])
				{
					return 0;
				}
				for (index01 = 0; index01 < 2; index01++)
				{
					for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
					{
						if (mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][0] == tQUEST_INFO->qSolution[0])
						{
							break;
						}
					}
					if (index02 < MAX_INVENTORY_SLOT_NUM)
					{
						break;
					}
				}
				if (index01 == 2)
				{
					return 2;
				}
				return 3;
			case 2: //[±³È¯ ÈÄ]
				if (mUSER[mIndex].mAvatarInfo.aQuestInfo[4] != tQUEST_INFO->qSolution[1])
				{
					return 0;
				}
				for (index01 = 0; index01 < 2; index01++)
				{
					for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
					{
						if (mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][0] == tQUEST_INFO->qSolution[1])
						{
							break;
						}
					}
					if (index02 < MAX_INVENTORY_SLOT_NUM)
					{
						break;
					}
				}
				if (index01 == 2)
				{
					return 4;
				}
				return 5;
			}
			break;
		case 7: //[NPC žž³ª±â]
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] != tQUEST_INFO->qSolution[0])
			{
				return 0;
			}
			return 2;
		case 8: //[Áø Á¡·É Âü¿©]
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] != tQUEST_INFO->qSolution[0])
			{
				return 0;
			}
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[4] < 1)
			{
				return 2;
			}
			return 3;
		}
	}
	return 0;
}
//RETURN_QUEST_END_CONDITION_STATE
int AVATAR_OBJECT::ReturnQuestEndConditionState(void)
{
	switch (mUSER[mIndex].mAvatarInfo.aQuestInfo[2])
	{
	case 1:
		if (ReturnQuestPresentState() == 3)
		{
			return 1;
		}
		return 0;
	case 2:
		if (ReturnQuestPresentState() == 3)
		{
			return 1;
		}
		return 0;
	case 3:
		if (ReturnQuestPresentState() == 3)
		{
			return 1;
		}
		return 0;
	case 4:
		if (ReturnQuestPresentState() == 3)
		{
			return 1;
		}
		return 0;
	case 5:
		if (ReturnQuestPresentState() == 3)
		{
			return 1;
		}
		return 0;
	case 6:
		if (ReturnQuestPresentState() == 5)
		{
			return 1;
		}
		return 0;
	case 7:
		if (ReturnQuestPresentState() == 2)
		{
			return 1;
		}
		return 0;
	case 8:
		if (ReturnQuestPresentState() == 3)
		{
			return 1;
		}
		return 0;
	}
	return 0;
}
//RETURN_QUEST_NEXT_NPC_NUMBER
int AVATAR_OBJECT::ReturnQuestNextNPCNumber(void)
{
	int index01;
	int index02;
	QUEST_INFO* tQUEST_INFO;

	if ((mUSER[mIndex].mAvatarInfo.aQuestInfo[1] == 0) && (mUSER[mIndex].mAvatarInfo.aQuestInfo[2] == 0) && (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] == 0) && (mUSER[mIndex].mAvatarInfo.aQuestInfo[4] == 0))
	{
		tQUEST_INFO = mQUEST.Search(mUSER[mIndex].mAvatarInfo.aTribe, (mUSER[mIndex].mAvatarInfo.aQuestInfo[0] + 1));
		if (tQUEST_INFO == NULL)
		{
			return 0;
		}
		if (mUSER[mIndex].mAvatarInfo.aLevel1 < tQUEST_INFO->qLevel)
		{
			return 0;
		}
		return tQUEST_INFO->qStartNPCNumber;
	}
	if (mUSER[mIndex].mAvatarInfo.aQuestInfo[1] == 1)
	{
		tQUEST_INFO = mQUEST.Search(mUSER[mIndex].mAvatarInfo.aTribe, mUSER[mIndex].mAvatarInfo.aQuestInfo[0]);
		if (tQUEST_INFO == NULL)
		{
			return 0;
		}
		switch (mUSER[mIndex].mAvatarInfo.aQuestInfo[2])
		{
		case 1: //[žóœºÅÍ Á×ÀÌ±â]
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] != tQUEST_INFO->qSolution[0])
			{
				return 0;
			}
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[4] < tQUEST_INFO->qSolution[1])
			{
				return tQUEST_INFO->qStartNPCNumber;
			}
			return tQUEST_INFO->qEndNPCNumber;
		case 2: //[ŸÆÀÌÅÛ ÀÔŒö]
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] != tQUEST_INFO->qSolution[0])
			{
				return 0;
			}
			for (index01 = 0; index01 < 2; index01++)
			{
				for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
				{
					if (mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][0] == tQUEST_INFO->qSolution[0])
					{
						break;
					}
				}
				if (index02 < MAX_INVENTORY_SLOT_NUM)
				{
					break;
				}
			}
			if (index01 == 2)
			{
				return tQUEST_INFO->qStartNPCNumber;
			}
			return tQUEST_INFO->qEndNPCNumber;
		case 3: //[ŸÆÀÌÅÛ ÀüŽÞ]
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] != tQUEST_INFO->qSolution[0])
			{
				return 0;
			}
			for (index01 = 0; index01 < 2; index01++)
			{
				for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
				{
					if (mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][0] == tQUEST_INFO->qSolution[0])
					{
						break;
					}
				}
				if (index02 < MAX_INVENTORY_SLOT_NUM)
				{
					break;
				}
			}
			if (index01 == 2)
			{
				return tQUEST_INFO->qStartNPCNumber;
			}
			return tQUEST_INFO->qEndNPCNumber;
		case 4: //[ŸÆÀÌÅÛ ¹ÞŸÆ¿À±â]
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] != tQUEST_INFO->qSolution[0])
			{
				return 0;
			}
			for (index01 = 0; index01 < 2; index01++)
			{
				for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
				{
					if (mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][0] == tQUEST_INFO->qSolution[0])
					{
						break;
					}
				}
				if (index02 < MAX_INVENTORY_SLOT_NUM)
				{
					break;
				}
			}
			if (index01 == 2)
			{
				return tQUEST_INFO->qKeyNPCNumber[0];
			}
			return tQUEST_INFO->qEndNPCNumber;
		case 5: //[ŽëÀå Á×ÀÌ±â]
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] != tQUEST_INFO->qSolution[0])
			{
				return 0;
			}
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[4] < 1)
			{
				return tQUEST_INFO->qStartNPCNumber;
			}
			return tQUEST_INFO->qEndNPCNumber;
		case 6: //[ŸÆÀÌÅÛ ±³È¯ÇÏ±â]
			switch (mUSER[mIndex].mAvatarInfo.aQuestInfo[3])
			{
			case 1: //[±³È¯ Àü]
				if (mUSER[mIndex].mAvatarInfo.aQuestInfo[4] != tQUEST_INFO->qSolution[0])
				{
					return 0;
				}
				for (index01 = 0; index01 < 2; index01++)
				{
					for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
					{
						if (mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][0] == tQUEST_INFO->qSolution[0])
						{
							break;
						}
					}
					if (index02 < MAX_INVENTORY_SLOT_NUM)
					{
						break;
					}
				}
				if (index01 == 2)
				{
					return tQUEST_INFO->qStartNPCNumber;
				}
				return tQUEST_INFO->qKeyNPCNumber[0];
			case 2: //[±³È¯ ÈÄ]
				if (mUSER[mIndex].mAvatarInfo.aQuestInfo[4] != tQUEST_INFO->qSolution[1])
				{
					return 0;
				}
				for (index01 = 0; index01 < 2; index01++)
				{
					for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
					{
						if (mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][0] == tQUEST_INFO->qSolution[1])
						{
							break;
						}
					}
					if (index02 < MAX_INVENTORY_SLOT_NUM)
					{
						break;
					}
				}
				if (index01 == 2)
				{
					return tQUEST_INFO->qStartNPCNumber;
				}
				return tQUEST_INFO->qEndNPCNumber;
			}
			break;
		case 7: //[NPC žž³ª±â]
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] != tQUEST_INFO->qSolution[0])
			{
				return 0;
			}
			return tQUEST_INFO->qEndNPCNumber;
		case 8: //[Áø Á¡·É Âü¿©]
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] != tQUEST_INFO->qSolution[0])
			{
				return 0;
			}
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[4] < 1)
			{
				return tQUEST_INFO->qStartNPCNumber;
			}
			return tQUEST_INFO->qEndNPCNumber;
		}
	}
	return 0;
}
//RETURN_ITEM_NUMBER_FOR_QUEST_REWARD
int AVATAR_OBJECT::ReturnItemNumberForQuestReward(void)
{
	int index01;
	QUEST_INFO* tQUEST_INFO;

	tQUEST_INFO = mQUEST.Search(mUSER[mIndex].mAvatarInfo.aTribe, mUSER[mIndex].mAvatarInfo.aQuestInfo[0]);
	if (tQUEST_INFO == NULL)
	{
		return 0;
	}
	for (index01 = 0; index01 < 3; index01++)
	{
		if (tQUEST_INFO->qReward[index01][0] == 6)
		{
			return tQUEST_INFO->qReward[index01][1];
		}
	}
	return 0;
}
//RETURN_ITEM_QUANTITY_FOR_QUEST_REWARD
int AVATAR_OBJECT::ReturnItemQuantityForQuestReward(void)
{
	int index01;
	QUEST_INFO* tQUEST_INFO;
	ITEM_INFO* tITEM_INFO;

	tQUEST_INFO = mQUEST.Search(mUSER[mIndex].mAvatarInfo.aTribe, mUSER[mIndex].mAvatarInfo.aQuestInfo[0]);
	if (tQUEST_INFO == NULL)
	{
		return 0;
	}
	for (index01 = 0; index01 < 3; index01++)
	{
		if (tQUEST_INFO->qReward[index01][0] != 6)
		{
			continue;
		}
		tITEM_INFO = mITEM.Search(tQUEST_INFO->qReward[index01][1]);
		if (tITEM_INFO == NULL)
		{
			return 0;
		}
		if (tITEM_INFO->iSort == 2)
		{
			return 1;
		}
		return 0;
	}
	return 0;
}
//SUMMON_QUEST_BOSS
int AVATAR_OBJECT::SummonQuestBoss(void)
{
	QUEST_INFO* tQUEST_INFO;
	float tCoord[3];

	if ((mUSER[mIndex].mAvatarInfo.aQuestInfo[2] != 5) || (ReturnQuestPresentState() != 2))
	{
		return 0;
	}
	tQUEST_INFO = mQUEST.Search(mUSER[mIndex].mAvatarInfo.aTribe, mUSER[mIndex].mAvatarInfo.aQuestInfo[0]);
	if (tQUEST_INFO == NULL)
	{
		return 0;
	}
	if (mSERVER_INFO.mServerNumber != tQUEST_INFO->qSummonInfo[0])
	{
		return 0;
	}
	tCoord[0] = (float)tQUEST_INFO->qSummonInfo[1];
	tCoord[1] = (float)tQUEST_INFO->qSummonInfo[2];
	tCoord[2] = (float)tQUEST_INFO->qSummonInfo[3];
	if (mUTIL.GetLengthXYZ(&mDATA.aAction.aLocation[0], &tCoord[0]) > 300.0f)
	{
		return 0;
	}
	mSUMMON.SummonMonsterForSpecial(tQUEST_INFO->qSolution[0], &tCoord[0], TRUE);
	return 0;
}
//CHANGE_QUEST_ITEM
int AVATAR_OBJECT::ChangeQuestItem(int tItemNumber1, int tItemNumber2)
{
	int index01;
	int index02;

	for (index01 = 0; index01 < 2; index01++)
	{
		for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
		{
			if (mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][0] == tItemNumber1)
			{
				mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][0] = tItemNumber2;
				mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][3] = 0;
				mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][4] = 0;
				mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][5] = 0;
				return index01;
			}
		}
	}
	return -1;
}
//DELETE_QUEST_ITEM
int AVATAR_OBJECT::DeleteQuestItem(int tItemNumber)
{
	int index01;
	int index02;

	for (index01 = 0; index01 < 2; index01++)
	{
		for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
		{
			if (mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][0] == tItemNumber)
			{
				mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][0] = 0;
				mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][1] = 0;
				mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][2] = 0;
				mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][3] = 0;
				mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][4] = 0;
				mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][5] = 0;
				return index01;
			}
		}
	}
	return -1;
}

void AVATAR_OBJECT::AutoBuff(int tCheckMotion)
{
	int tCount = 0;
	int OtoBuffControl = 8;
	ACTION_INFO tAction;
	mUSER[mIndex].mAvatarInfo.AutoHunt.HuntSabit = 0;
	if (mUSER[mIndex].mAvatarInfo.AutoBuffScroll < mUTIL.ReturnNowDate()) {
		OtoBuffControl = 2;
	}
	if ((mUSER[mIndex].mAvatarInfo.HunstStart)) {
		for (tCount = 0; tCount < OtoBuffControl; tCount++)
		{
			if ((mUSER[mIndex].mAvatarInfo.AutoHunt.HuntBuff[tCount][0] == 0))
				continue;
			mUSER[mIndex].mAvatarInfo.AutoHunt.HuntSabit++;			
			if ((mUSER[mIndex].mAvatarInfo.AutoHunt.HuntBuff[tCount][0] == 0))
			{
				continue;
			}
			if (!mWORK.ReturnEffectState(mIndex, mUSER[mIndex].mAvatarInfo.AutoHunt.HuntBuff[tCount][0]))
			{
				continue;
			}
			::memset(&tAction, 0, sizeof(ACTION_INFO));
			tAction.aSkillNumber = mUSER[mIndex].mAvatarInfo.AutoHunt.HuntBuff[tCount][0];
			tAction.aSkillGradeNum1 = mUSER[mIndex].mAvatarInfo.AutoHunt.HuntBuff[tCount][1];
			tAction.aSkillGradeNum2 = mAVATAR_OBJECT[mIndex].GetBonusSkillValue(tAction.aSkillNumber);
			mWORK.SkillForMotion(mIndex, &tAction, 0);
			AutoBuffStart(&tAction);
		}
		mAVATAR_OBJECT[mIndex].mDATA.BotOn = 1;
	}
	else if (mUSER[mIndex].mAvatarInfo.AutoHunt.BuffType == 0 && tCheckMotion == 0) {
		mAVATAR_OBJECT[mIndex].mDATA.BotOn = 0;
		ProcessForDeleteEffectValue();
	}
	return;
}

void AVATAR_OBJECT::AutoBuffStart(ACTION_INFO* pAction)
{
	mDATA.aAction.aSkillNumber = pAction->aSkillNumber;
	mDATA.aAction.aSkillGradeNum1 = pAction->aSkillGradeNum1;
	mDATA.aAction.aSkillGradeNum2 = pAction->aSkillGradeNum2;
	mDATA.aAction.aSort = pAction->aSort;
	mDATA.aAction.aType = pAction->aType;
	mDATA.aAction.aFrame = pAction->aFrame;
	mDATA.aAction.aTargetLocation[0] = pAction->aTargetLocation[0];
	mDATA.aAction.aTargetLocation[1] = pAction->aTargetLocation[1];
	mDATA.aAction.aTargetLocation[2] = pAction->aTargetLocation[2];
	mDATA.aAction.aTargetObjectSort = pAction->aTargetObjectSort;
	mDATA.aAction.aTargetObjectIndex = pAction->aTargetObjectIndex;
	mDATA.aAction.aTargetObjectUniqueNumber = pAction->aTargetObjectUniqueNumber;
	mDATA.aAction.aSkillValue = pAction->aSkillValue;
	if (mUSER[mIndex].mAvatarInfo.AutoHunt.HuntSabit == 1)
	{
		mTRANSFER.B_AVATAR_ACTION_RECV(mIndex, mAVATAR_OBJECT[mIndex].mUniqueNumber, &mDATA, 1);
		if (mUSER[mIndex].mAvatarInfo.aVisibleState == 0) {
			mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		else {
			mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[mIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, mIndex, false);
		}
	}
	ProcessForCreateEffectValue(pAction);
}

int AVATAR_OBJECT::IsUsedOrnament(void)
{
	if (mUSER[mIndex].mAvatarInfo.iUseOrnament == true && mUSER[mIndex].mAvatarInfo.aLevel1 > 112)
	{
		if (mUSER[mIndex].mAvatarInfo.aEquip[9][0] > 0 &&
			mUSER[mIndex].mAvatarInfo.aEquip[10][0] > 0 &&
			mUSER[mIndex].mAvatarInfo.aEquip[11][0] > 0 &&
			mUSER[mIndex].mAvatarInfo.aEquip[12][0] > 0) {
			if (mUSER[mIndex].mAvatarInfo.iGoldOrnamentRemainsTime > 0)
			{
				return 1;
			}
			else if (mUSER[mIndex].mAvatarInfo.iSilverOrnamentRemainsTime > 0)
			{
				return 2;
			}
			return 0;
		}
	}
	return 0;
}
//-------------------------------------------------------------------------------------------------

int AVATAR_OBJECT::CheckSkillForWeapon(int SkillNumber)
{
	SKILL_INFO* mSkill;
	ITEM_INFO* mItem;

	mSkill = mSKILL.Search(SkillNumber);
	if (mSkill == NULL)
	{
		return 0;
	}
	switch (mSkill->sIndex)
	{
		
	case 58:
	case 59:
	case 85:
	case 86:
	case 121:
	case 122:
	case 112:
		mItem = mITEM.Search(mUSER[mIndex].mAvatarInfo.aEquip[7][0]);
		if (mItem == NULL)
		{
			return 2;
		}
		if (mItem->iSort != 13)
		{
			return 2;
		}
		return 0;
		
	case 60:
	case 61:
	case 87:
	case 88:
	case 123:
	case 124:
	case 113:
		mItem = mITEM.Search(mUSER[mIndex].mAvatarInfo.aEquip[7][0]);
		if (mItem == NULL)
		{
			return 2;
		}
		if (mItem->iSort != 14)
		{
			return 2;
		}
		return 0;
		
	case 62:
	case 63:
	case 89:
	case 90:
	case 125:
	case 126:
	case 114:
		mItem = mITEM.Search(mUSER[mIndex].mAvatarInfo.aEquip[7][0]);
		if (mItem == NULL)
		{
			return 2;
		}
		if (mItem->iSort != 15)
		{
			return 2;
		}
		return 0;
		
	case 64:
	case 65:
	case 91:
	case 92:
	case 127:
	case 128:
	case 115:
		mItem = mITEM.Search(mUSER[mIndex].mAvatarInfo.aEquip[7][0]);
		if (mItem == NULL)
		{
			return 2;
		}
		if (mItem->iSort != 16)
		{
			return 2;
		}
		return 0;
		
	case 66:
	case 67:
	case 93:
	case 94:
	case 129:
	case 130:
	case 116:
		mItem = mITEM.Search(mUSER[mIndex].mAvatarInfo.aEquip[7][0]);
		if (mItem == NULL)
		{
			return 2;
		}
		if (mItem->iSort != 17)
		{
			return 2;
		}
		return 0;
		
	case 68:
	case 69:
	case 95:
	case 96:
	case 131:
	case 132:
	case 117:
		mItem = mITEM.Search(mUSER[mIndex].mAvatarInfo.aEquip[7][0]);
		if (mItem == NULL)
		{
			return 2;
		}
		if (mItem->iSort != 18)
		{
			return 2;
		}
		return 0;
		
	case 70:
	case 71:
	case 97:
	case 98:
	case 133:
	case 134:
	case 118:
		mItem = mITEM.Search(mUSER[mIndex].mAvatarInfo.aEquip[7][0]);
		if (mItem == NULL)
		{
			return 2;
		}
		if (mItem->iSort != 19)
		{
			return 2;
		}
		return 0;
		
	case 72:
	case 73:
	case 99:
	case 100:
	case 135:
	case 136:
	case 119:
		mItem = mITEM.Search(mUSER[mIndex].mAvatarInfo.aEquip[7][0]);
		if (mItem == NULL)
		{
			return 2;
		}
		if (mItem->iSort != 20)
		{
			return 2;
		}
		return 0;
		
	case 74:
	case 75:
	case 101:
	case 102:
	case 137:
	case 138:
	case 120:
		mItem = mITEM.Search(mUSER[mIndex].mAvatarInfo.aEquip[7][0]);
		if (mItem == NULL)
		{
			return 2;
		}
		if (mItem->iSort != 21)
		{
			return 2;
		}
		return 0;
	default:
		return 0;
	}
}