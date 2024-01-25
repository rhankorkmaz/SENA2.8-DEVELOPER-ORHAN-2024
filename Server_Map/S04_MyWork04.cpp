//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "Shengming.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_WORK
//-------------------------------------------------------------------------------------------------
//PROCESS_FOR_GET_ITEM
BOOL MyWork::ProcessForGetItem(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if ((tPage1 < 0) || (tPage1 > (MAX_ITEM_OBJECT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tXPost2 < 0) || (tXPost2 > 7) || (tYPost2 < 0) || (tYPost2 > 7))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	ITEM_OBJECT* tITEM_OBJECT;
	ITEM_INFO* tITEM_INFO;
	int index01 = 0, index02 = 0, tMax = 0;

	tITEM_OBJECT = &mITEM_OBJECT[tPage1];
	if ((!tITEM_OBJECT->mCheckValidState) || ((int)tITEM_OBJECT->mUniqueNumber != tIndex1))
	{
		*tResult = 1;
		return TRUE;
	}
	if (!tITEM_OBJECT->CheckPossibleGetItem(tUserIndex))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	tITEM_INFO = mITEM.Search(tITEM_OBJECT->mDATA.iIndex);
	if (tITEM_INFO == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	// ÀÌº¥Æ® ºžœº žóœºÅÍ(·¹ÀÌµå žóœºÅÍ)°¡ µå¶øÇÏŽÂ ŸÆÀÌÅÛÀÎ 1417Àº
	// ÇÑ °³žž È¹µæ °¡ŽÉÇÏµµ·Ï ŒöÁ€.


	switch (tITEM_INFO->iSort)
	{
	case  1:
		if (mUTIL.CheckOverMaximum(mUSER[tUserIndex].mAvatarInfo.aMoney, tITEM_OBJECT->mDATA.iQuantity))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		mUSER[tUserIndex].mAvatarInfo.aMoney += tITEM_OBJECT->mDATA.iQuantity;
		*tResult = 0;
		return TRUE;
	case  2:
		if (tPage2 == 1)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
		}
		if ((tITEM_OBJECT->mDATA.iQuantity < 1) || (tITEM_OBJECT->mDATA.iQuantity > MAX_ITEM_DUPLICATION_NUM))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] > 0)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != tITEM_OBJECT->mDATA.iIndex)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
			if ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] + tITEM_OBJECT->mDATA.iQuantity) > MAX_ITEM_DUPLICATION_NUM)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = tITEM_OBJECT->mDATA.iIndex;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = tXPost2;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = tYPost2;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] += tITEM_OBJECT->mDATA.iQuantity;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		
		*tResult = 0;
		return TRUE;
	default:
		if (tPage2 == 1)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] > 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		// # Defense Hack # {
		if (!mUTIL.CheckInvenForItem(&tUserIndex, tITEM_INFO, &tPage2, &tIndex2, &tXPost2, &tYPost2)) {
			//mGAMELOG.GL_659_AUTO_CHECK(tUserIndex, 7, tIndex2, tXPost2, tYPost2);
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		// # }
		
		mGAMELOG.GL_GAIN_ITEM(tUserIndex, tITEM_OBJECT->mDATA.iIndex, tITEM_OBJECT->mDATA.iQuantity, tITEM_OBJECT->mDATA.iValue, tITEM_OBJECT->mDATA.iItemRecognitionNumber,tITEM_INFO->iName);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = tITEM_OBJECT->mDATA.iIndex;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = tXPost2;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = tYPost2;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = tITEM_OBJECT->mDATA.iQuantity;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = tITEM_OBJECT->mDATA.iValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = tITEM_OBJECT->mDATA.iItemRecognitionNumber;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][0] = tITEM_OBJECT->mDATA.Socket[0];
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][1] = tITEM_OBJECT->mDATA.Socket[1];
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][2] = tITEM_OBJECT->mDATA.Socket[2];
		
		*tResult = 0;
		return TRUE;
	}
	mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
	return FALSE;
}
//PROCESS_FOR_LEARN_SKILL_1
BOOL MyWork::ProcessForLearnSkill1(int tUserIndex, int nIndex, int sIndex, int* tResult)
{
	int index01;
	int index02;
	NPC_INFO* tNPC_INFO;
	BOOL tCheckExistSkill;
	SKILL_INFO* tSKILL_INFO;

	tNPC_INFO = mNPC.Search(nIndex);
	if (tNPC_INFO == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	tCheckExistSkill = FALSE;
	for (index01 = 0; index01 < 3; index01++)
	{
		for (index02 = 0; index02 < 8; index02++)
		{
			if (tNPC_INFO->nSkillInfo1[index01][index02] == sIndex)
			{
				tCheckExistSkill = TRUE;
			}
		}
	}
	if (!tCheckExistSkill)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	tSKILL_INFO = mSKILL.Search(sIndex);
	if (tSKILL_INFO == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aSkillPoint < tSKILL_INFO->sLearnSkillPoint)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	for (index01 = 0; index01 < MAX_SKILL_SLOT_NUM; index01++)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] == tSKILL_INFO->sIndex)
		{
			break;
		}
	}
	if (index01 < MAX_SKILL_SLOT_NUM)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
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
			return FALSE;
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
			return FALSE;
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
				return FALSE;
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
				return FALSE;
			}
		}
		break;
	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	mUSER[tUserIndex].mAvatarInfo.aSkillPoint -= tSKILL_INFO->sLearnSkillPoint;
	mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] = tSKILL_INFO->sIndex;
	mUSER[tUserIndex].mAvatarInfo.aSkill[index01][1] = tSKILL_INFO->sLearnSkillPoint;
	
	*tResult = 0;
	return TRUE;
}
//PROCESS_FOR_SKILL_UPGRADE
BOOL MyWork::ProcessForSkillUpgrade(int tUserIndex, int tSkillIndex, int* tResult)
{
	if ((tSkillIndex < 0) || (tSkillIndex > (MAX_SKILL_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	SKILL_INFO* tSKILL_INFO;

	tSKILL_INFO = mSKILL.Search(mUSER[tUserIndex].mAvatarInfo.aSkill[tSkillIndex][0]);
	if (tSKILL_INFO == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aSkillPoint < 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aSkill[tSkillIndex][1] >= tSKILL_INFO->sMaxUpgradePoint)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	mUSER[tUserIndex].mAvatarInfo.aSkillPoint--;
	mUSER[tUserIndex].mAvatarInfo.aSkill[tSkillIndex][1]++;
	
	*tResult = 0;
	return TRUE;
}
//PROCESS_FOR_SKILL_TO_HOTKEY
BOOL MyWork::ProcessForSkillToHotKey(int tUserIndex, int tSkillSort, int tSkillIndex, int tSkillGrade, int tHotKeyPage, int tHotKeyIndex, int* tResult)
{
	switch (tSkillSort)
	{
	case 1:
		if ((tSkillIndex < 0) || (tSkillIndex > (MAX_SKILL_SLOT_NUM - 1)) || (tSkillGrade < 1) || (tHotKeyPage < 0) || (tHotKeyPage > 2) || (tHotKeyIndex < 0) || (tHotKeyIndex > (MAX_HOT_KEY_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aSkill[tSkillIndex][0] < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (tSkillGrade > mUSER[tUserIndex].mAvatarInfo.aSkill[tSkillIndex][1])
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tHotKeyPage][tHotKeyIndex][0] > 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		mUSER[tUserIndex].mAvatarInfo.aHotKey[tHotKeyPage][tHotKeyIndex][0] = mUSER[tUserIndex].mAvatarInfo.aSkill[tSkillIndex][0];
		mUSER[tUserIndex].mAvatarInfo.aHotKey[tHotKeyPage][tHotKeyIndex][1] = tSkillGrade;
		mUSER[tUserIndex].mAvatarInfo.aHotKey[tHotKeyPage][tHotKeyIndex][2] = 1;
		*tResult = 0;
		
		return TRUE;
	case 2:
		if ((tSkillIndex < 1) || (tSkillIndex > 9) || (tHotKeyPage < 0) || (tHotKeyPage > 2) || (tHotKeyIndex < 0) || (tHotKeyIndex > (MAX_HOT_KEY_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tHotKeyPage][tHotKeyIndex][0] > 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		mUSER[tUserIndex].mAvatarInfo.aHotKey[tHotKeyPage][tHotKeyIndex][0] = tSkillIndex;
		mUSER[tUserIndex].mAvatarInfo.aHotKey[tHotKeyPage][tHotKeyIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aHotKey[tHotKeyPage][tHotKeyIndex][2] = 2;
		*tResult = 0;
		
		return TRUE;
	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
	return FALSE;
}
//PROCESS_FOR_HOTKEY_TO_NO
BOOL MyWork::ProcessForHotKeyToNo(int tUserIndex, int tHotKeyPage, int tHotKeyIndex, int* tResult)
{
	if ((tHotKeyPage < 0) || (tHotKeyPage > 2) || (tHotKeyIndex < 0) || (tHotKeyIndex > (MAX_HOT_KEY_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tHotKeyPage][tHotKeyIndex][0] < 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mUSER[tUserIndex].mAvatarInfo.aHotKey[tHotKeyPage][tHotKeyIndex][2] != 1) && (mUSER[tUserIndex].mAvatarInfo.aHotKey[tHotKeyPage][tHotKeyIndex][2] != 2))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	mUSER[tUserIndex].mAvatarInfo.aHotKey[tHotKeyPage][tHotKeyIndex][0] = 0;
	mUSER[tUserIndex].mAvatarInfo.aHotKey[tHotKeyPage][tHotKeyIndex][1] = 0;
	mUSER[tUserIndex].mAvatarInfo.aHotKey[tHotKeyPage][tHotKeyIndex][2] = 0;
	
	*tResult = 0;
	return TRUE;
}
//PROCESS_FOR_STAT_PLUS
BOOL MyWork::ProcessForStatPlus(int tUserIndex, int tStatSort, int* tResult)
{
	
	if (mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint < 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (tStatSort == 5 || tStatSort == 6 || tStatSort == 7 || tStatSort == 8)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint < 5)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	switch (tStatSort)
	{
	case 1:
		mUSER[tUserIndex].mAvatarInfo.aStrength++;
		break;
	case 5:
		mUSER[tUserIndex].mAvatarInfo.aStrength++;
		mUSER[tUserIndex].mAvatarInfo.aStrength++;
		mUSER[tUserIndex].mAvatarInfo.aStrength++;
		mUSER[tUserIndex].mAvatarInfo.aStrength++;
		mUSER[tUserIndex].mAvatarInfo.aStrength++;
		break;
	case 2:
		mUSER[tUserIndex].mAvatarInfo.aWisdom++;
		break;
	case 6:
		mUSER[tUserIndex].mAvatarInfo.aWisdom++;
		mUSER[tUserIndex].mAvatarInfo.aWisdom++;
		mUSER[tUserIndex].mAvatarInfo.aWisdom++;
		mUSER[tUserIndex].mAvatarInfo.aWisdom++;
		mUSER[tUserIndex].mAvatarInfo.aWisdom++;
		break;
	case 3:
		mUSER[tUserIndex].mAvatarInfo.aVitality++;
		break;
	case 7:
		mUSER[tUserIndex].mAvatarInfo.aVitality++;
		mUSER[tUserIndex].mAvatarInfo.aVitality++;
		mUSER[tUserIndex].mAvatarInfo.aVitality++;
		mUSER[tUserIndex].mAvatarInfo.aVitality++;
		mUSER[tUserIndex].mAvatarInfo.aVitality++;
		break;
	case 4:
		mUSER[tUserIndex].mAvatarInfo.aKi++;
		break;
	case 8:
		mUSER[tUserIndex].mAvatarInfo.aKi++;
		mUSER[tUserIndex].mAvatarInfo.aKi++;
		mUSER[tUserIndex].mAvatarInfo.aKi++;
		mUSER[tUserIndex].mAvatarInfo.aKi++;
		mUSER[tUserIndex].mAvatarInfo.aKi++;
		break;
	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (tStatSort == 5 || tStatSort == 6 || tStatSort == 7 || tStatSort == 8) {
		mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint--;
		mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint--;
		mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint--;
		mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint--;
		mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint--;
	}
	else {
		mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint--;
	}
	mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
	
	*tResult = 0;
	return TRUE;
}
//PROCESS_FOR_INVENTORY_TO_INVENTORY
BOOL MyWork::ProcessForInventoryToInventory(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tXPost2 < 0) || (tXPost2 > 7) || (tYPost2 < 0) || (tYPost2 > 7))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	ITEM_INFO* tITEM_INFO;

	if ((tPage1 == 1) || (tPage2 == 1))
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	tITEM_INFO = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
	if (tITEM_INFO == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	switch (tITEM_INFO->iSort)
	{
	case  2:
		if ((tQuantity1 < 0) || (tQuantity1 > MAX_ITEM_DUPLICATION_NUM))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] < tQuantity1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] > 0)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0])
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
			if ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] + tQuantity1) > MAX_ITEM_DUPLICATION_NUM)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = tXPost2;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = tYPost2;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] += tQuantity1;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] -= tQuantity1;
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] < 1)
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = 0;
		}
		
		*tResult = 0;
		return TRUE;
	default:
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] > 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = tXPost2;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = tYPost2;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5];
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][1] = mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1];
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][2] = mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2] = 0;


		*tResult = 0;
		
		return TRUE;
	}
	mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
	return FALSE;
}
//PROCESS_FOR_INVENTORY_TO_WORLD
BOOL MyWork::ProcessForInventoryToWorld(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	ITEM_INFO* tITEM_INFO;

	if (tPage1 == 1)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	tITEM_INFO = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
	if (tITEM_INFO == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (tITEM_INFO->iCheckAvatarDrop == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	switch (tITEM_INFO->iSort)
	{
	case  2:
		if ((tQuantity1 < 0) || (tQuantity1 > MAX_ITEM_DUPLICATION_NUM))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] < tQuantity1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		// 2009.08.05
		if (!mUTIL.ProcessForDropItem(3, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], tQuantity1, 0, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], 0, mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1]))
		{
			*tResult = 1;
			return TRUE;
		} //
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] -= tQuantity1;
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] < 1)
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = 0;
		}
		
		*tResult = 0;
		
		return TRUE;
	default:
		// 2009.08.05
		if (!mUTIL.ProcessForDropItem(3, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], 0, &mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0]))
		{
			*tResult = 1;
			return TRUE;
		} //
		//mGAMELOG.GL_620_DROP_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5]);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2] = 0;
		*tResult = 0;
		
		return TRUE;
	}
	mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
	return FALSE;
}
//PROCESS_FOR_INVENTORY_TO_EQUIP
BOOL MyWork::ProcessForInventoryToEquip(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tIndex2 < 0) || (tIndex2 > (MAX_EQUIP_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (tPage1 == 1)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	if (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort != 1)
	{
		*tResult = 1;
		return TRUE;
	}
	if (!mUTIL.CheckPossibleEquipItem(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, tIndex2, (mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aEquip[tIndex2][0] > 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	mUSER[tUserIndex].mAvatarInfo.aEquip[tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0];
	mUSER[tUserIndex].mAvatarInfo.aEquip[tIndex2][1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3];
	mUSER[tUserIndex].mAvatarInfo.aEquip[tIndex2][2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4];
	mUSER[tUserIndex].mAvatarInfo.aEquip[tIndex2][3] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5];
	mUSER[tUserIndex].mAvatarInfo.EquipSocket[tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0];
	mUSER[tUserIndex].mAvatarInfo.EquipSocket[tIndex2][1] = mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1];
	mUSER[tUserIndex].mAvatarInfo.EquipSocket[tIndex2][2] = mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2];
	mAVATAR_OBJECT[tUserIndex].mDATA.aEquipForView[tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.aEquip[tIndex2][0];
	mAVATAR_OBJECT[tUserIndex].mDATA.aEquipForView[tIndex2][1] = mUSER[tUserIndex].mAvatarInfo.aEquip[tIndex2][2];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = 0;
	mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0] = 0;
	mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1] = 0;
	mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2] = 0;
	mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aType = mAVATAR_OBJECT[tUserIndex].GetWeaponClass() * 2;
	mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort = 1;
	mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aFrame = 0.0f;
	mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
	*tResult = 0;
	
	return TRUE;
}
//PROCESS_FOR_INVENTORY_TO_HOTKEY
BOOL MyWork::ProcessForInventoryToHotKey(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 2) || (tIndex2 < 0) || (tIndex2 > (MAX_HOT_KEY_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	ITEM_INFO* tITEM_INFO;

	if (tPage1 == 1)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	tITEM_INFO = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
	if (tITEM_INFO == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	switch (tITEM_INFO->iSort)
	{
	case  2:
		if ((tITEM_INFO->iPotionType[0] == 7) || (tITEM_INFO->iPotionType[0] == 8))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((tQuantity1 < 1) || (tQuantity1 > MAX_ITEM_DUPLICATION_NUM))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] < tQuantity1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage2][tIndex2][2] == 3)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage2][tIndex2][0] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0])
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
			if ((mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage2][tIndex2][1] + tQuantity1) > MAX_ITEM_DUPLICATION_NUM)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
		}
		mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage2][tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage2][tIndex2][1] += tQuantity1;
		mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage2][tIndex2][2] = 3;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] -= tQuantity1;
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] < 1)
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = 0;
		}
		*tResult = 0;
		
		return TRUE;
	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
	return FALSE;
}
BOOL MyWork::ProcessForInventoryToPetInventory(int tUserIndex, int tPage1, int tIndex1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	ITEM_INFO* tITEM_INFO;

	if (tPage1 == 1)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	tITEM_INFO = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);

	if (tITEM_INFO == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_PET_INVENTORY_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUSER[tUserIndex].mAvatarInfo.PetInventoryTick[tPage2][tIndex2] > 0)
	{
		//mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	mUSER[tUserIndex].mAvatarInfo.PetInventoryTick[tPage2][tIndex2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = 0;
	
	*tResult = 0;
	return TRUE;
}
BOOL MyWork::ProcessForPetInventoryToInventory(int tUserIndex, int tPage1, int tIndex1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_PET_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tXPost2 < 0) || (tXPost2 > 7) || (tYPost2 < 0) || (tYPost2 > 7))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	ITEM_INFO* tITEM_INFO;

	if (tPage2 == 1)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
	}

	tITEM_INFO = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.PetInventoryTick[tPage1][tIndex1]);

	if (tITEM_INFO == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] > 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.PetInventoryTick[tPage1][tIndex1];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = tXPost2;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = tYPost2;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
	mUSER[tUserIndex].mAvatarInfo.PetInventoryTick[tPage1][tIndex1] = 0;
	
	*tResult = 0;
	return TRUE;
}
BOOL MyWork::ProcessForPetInventoryToPetInventory(int tUserIndex, int tPage1, int tIndex1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_PET_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_PET_INVENTORY_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	ITEM_INFO* tITEM_INFO;

	tITEM_INFO = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.PetInventoryTick[tPage1][tIndex1]);

	if (tITEM_INFO == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	mUSER[tUserIndex].mAvatarInfo.PetInventoryTick[tPage2][tIndex2] = mUSER[tUserIndex].mAvatarInfo.PetInventoryTick[tPage1][tIndex1];
	mUSER[tUserIndex].mAvatarInfo.PetInventoryTick[tPage1][tIndex1] = 0;
	
	*tResult = 0;
	return TRUE;
}
//PROCESS_FOR_INVENTORY_TO_NPCSHOP
BOOL MyWork::ProcessForInventoryToNPCShop(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	ITEM_INFO* tITEM_INFO;

	if (tPage1 == 1)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	tITEM_INFO = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
	if (tITEM_INFO == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (tITEM_INFO->iCheckNPCSell == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	switch (tITEM_INFO->iSort)
	{
	case  2:
		if ((tQuantity1 < 1) || (tQuantity1 > MAX_ITEM_DUPLICATION_NUM))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] < tQuantity1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUTIL.CheckOverMaximum(mUSER[tUserIndex].mAvatarInfo.aMoney, (tITEM_INFO->iSellCost * tQuantity1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		mUSER[tUserIndex].mAvatarInfo.aMoney += (tITEM_INFO->iSellCost * tQuantity1);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] -= tQuantity1;
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] < 1)
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = 0;
		}
		*tResult = 0;
		
		return TRUE;
	default:
		if (mUTIL.CheckOverMaximum(mUSER[tUserIndex].mAvatarInfo.aMoney, tITEM_INFO->iSellCost))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		//mGAMELOG.GL_621_NSHOP_ITEM(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tITEM_INFO->iSellCost);
		mUSER[tUserIndex].mAvatarInfo.aMoney += tITEM_INFO->iSellCost;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = 0;
		*tResult = 0;
		
		return TRUE;
	}
	mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
	return FALSE;
}
//PROCESS_FOR_EQUIP_TO_INVENTORY
BOOL MyWork::ProcessForEquipToInventory(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if ((tIndex1 < 0) || (tIndex1 > (MAX_EQUIP_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tXPost2 < 0) || (tXPost2 > 7) || (tYPost2 < 0) || (tYPost2 > 7))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (tPage2 == 1)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	if (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort != 1)
	{
		*tResult = 1;
		return TRUE;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aEquip[tIndex1][0] < 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] > 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.aEquip[tIndex1][0];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = tXPost2;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = tYPost2;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = mUSER[tUserIndex].mAvatarInfo.aEquip[tIndex1][1];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = mUSER[tUserIndex].mAvatarInfo.aEquip[tIndex1][2];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = mUSER[tUserIndex].mAvatarInfo.aEquip[tIndex1][3];
	mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.EquipSocket[tIndex1][0];
	mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][1] = mUSER[tUserIndex].mAvatarInfo.EquipSocket[tIndex1][1];
	mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][2] = mUSER[tUserIndex].mAvatarInfo.EquipSocket[tIndex1][2];
	mUSER[tUserIndex].mAvatarInfo.aEquip[tIndex1][0] = 0;
	mUSER[tUserIndex].mAvatarInfo.aEquip[tIndex1][1] = 0;
	mUSER[tUserIndex].mAvatarInfo.aEquip[tIndex1][2] = 0;
	mUSER[tUserIndex].mAvatarInfo.aEquip[tIndex1][3] = 0;
	mUSER[tUserIndex].mAvatarInfo.EquipSocket[tIndex1][0] = 0;
	mUSER[tUserIndex].mAvatarInfo.EquipSocket[tIndex1][1] = 0;
	mUSER[tUserIndex].mAvatarInfo.EquipSocket[tIndex1][2] = 0;
	mAVATAR_OBJECT[tUserIndex].mDATA.aEquipForView[tIndex1][0] = 0;
	mAVATAR_OBJECT[tUserIndex].mDATA.aEquipForView[tIndex1][1] = 0;
	mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aType = mAVATAR_OBJECT[tUserIndex].GetWeaponClass() * 2;
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
	if (tIndex1 == 7)
	{
		mAVATAR_OBJECT[tUserIndex].ProcessForDeleteEffectValue();
	}
	*tResult = 0;
	
	return TRUE;
}
//PROCESS_FOR_HOTKEY_TO_INVENTORY
BOOL MyWork::ProcessForHotKeyToInventory(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if ((tPage1 < 0) || (tPage1 > 2) || (tIndex1 < 0) || (tIndex1 > (MAX_HOT_KEY_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tXPost2 < 0) || (tXPost2 > 7) || (tYPost2 < 0) || (tYPost2 > 7))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	ITEM_INFO* tITEM_INFO;

	if (tPage2 == 1)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage1][tIndex1][2] != 3)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	tITEM_INFO = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage1][tIndex1][0]);
	if (tITEM_INFO == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (tITEM_INFO->iSort != 2)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((tQuantity1 < 1) || (tQuantity1 > MAX_ITEM_DUPLICATION_NUM))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage1][tIndex1][1] < tQuantity1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] > 0)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage1][tIndex1][0])
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] + tQuantity1) > MAX_ITEM_DUPLICATION_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage1][tIndex1][0];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = tXPost2;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = tYPost2;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] += tQuantity1;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
	mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage1][tIndex1][1] -= tQuantity1;
	if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage1][tIndex1][1] < 1)
	{
		mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage1][tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage1][tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage1][tIndex1][2] = 0;
	}
	*tResult = 0;
	
	return TRUE;
}
//PROCESS_FOR_NPCSHOP_TO_INVENTORY
BOOL MyWork::ProcessForNPCShopToInventory(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if ((tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tXPost2 < 0) || (tXPost2 > 7) || (tYPost2 < 0) || (tYPost2 > 7))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	int index01;
	int index02;
	NPC_INFO* tNPC_INFO;
	ITEM_INFO* tITEM_INFO;

	if (tPage2 == 1)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	tNPC_INFO = mNPC.Search(tPage1);
	if (tNPC_INFO == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	for (index01 = 0; index01 < 3; index01++)
	{
		for (index02 = 0; index02 < 28; index02++)
		{
			if (tNPC_INFO->nShopInfo[index01][index02] == tIndex1)
			{
				break;
			}
		}
		if (index02 < 28)
		{
			break;
		}
	}
	if (index01 == 3)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	tITEM_INFO = mITEM.Search(tIndex1);
	if (tITEM_INFO == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (tITEM_INFO->iIndex == 1047)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 113)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	switch (tITEM_INFO->iSort)
	{
	case  2:
		if ((tQuantity1 < 1) || (tQuantity1 > MAX_ITEM_DUPLICATION_NUM))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] > 0)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != tIndex1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
			if ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] + tQuantity1) > MAX_ITEM_DUPLICATION_NUM)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
		}
		if (mUSER[tUserIndex].mAvatarInfo.aMoney < (tITEM_INFO->iBuyCost * tQuantity1))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < (tITEM_INFO->iBuyCPCost * tQuantity1))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -=( tITEM_INFO->iBuyCPCost * tQuantity1);
		mUSER[tUserIndex].mAvatarInfo.aMoney -= (tITEM_INFO->iBuyCost * tQuantity1);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = tIndex1;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = tXPost2;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = tYPost2;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] += tQuantity1;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		*tResult = 0;
		
		return TRUE;
	default:
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] > 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aMoney < tITEM_INFO->iBuyCost)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < tITEM_INFO->iBuyCPCost)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= tITEM_INFO->iBuyCPCost;
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tITEM_INFO->iBuyCost;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = tIndex1;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = tXPost2;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = tYPost2;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		*tResult = 0;
		
		return TRUE;
	}
	mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
	return FALSE;
}
//PROCESS_FOR_HOTKEY_TO_HOTKEY
BOOL MyWork::ProcessForHotKeyToHotKey(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if ((tPage1 < 0) || (tPage1 > 2) || (tIndex1 < 0) || (tIndex1 > (MAX_HOT_KEY_NUM - 1)) || (tPage2 < 0) || (tPage2 > 2) || (tIndex2 < 0) || (tIndex2 > (MAX_HOT_KEY_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	ITEM_INFO* tITEM_INFO;

	switch (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage1][tIndex1][2])
	{
	case 1:
	case 2:
		if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage1][tIndex1][0] < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage2][tIndex2][0] > 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage2][tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage1][tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage2][tIndex2][1] = mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage1][tIndex1][1];
		mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage2][tIndex2][2] = mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage1][tIndex1][2];
		mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage1][tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage1][tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage1][tIndex1][2] = 0;
		*tResult = 0;
		
		return TRUE;
	case 3:
		tITEM_INFO = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage1][tIndex1][0]);
		if (tITEM_INFO == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (tITEM_INFO->iSort != 2)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((tQuantity1 < 1) || (tQuantity1 > MAX_ITEM_DUPLICATION_NUM))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage1][tIndex1][1] < tQuantity1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage2][tIndex2][2] == 3)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage2][tIndex2][0] != mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage1][tIndex1][0])
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
			if ((mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage2][tIndex2][1] + tQuantity1) > MAX_ITEM_DUPLICATION_NUM)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
		}
		mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage2][tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage1][tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage2][tIndex2][1] += tQuantity1;
		mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage2][tIndex2][2] = 3;
		mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage1][tIndex1][1] -= tQuantity1;
		if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage1][tIndex1][1] < 1)
		{
			mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage1][tIndex1][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage1][tIndex1][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage1][tIndex1][2] = 0;
		}
		*tResult = 0;
		
		return TRUE;
	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
	return FALSE;
}
//PROCESS_FOR_INVENTORY_MONEY_TO_WORLD
BOOL MyWork::ProcessForInventoryMoneyToWorld(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if (tQuantity1 < 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aMoney < tQuantity1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (!mUTIL.ProcessForDropItem(3, 1, tQuantity1, 0, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], 0, mUSER[tUserIndex].DropItemSocketGmAndBos))
	{
		*tResult = 1;
		return TRUE;
	}
	mUSER[tUserIndex].mAvatarInfo.aMoney -= tQuantity1;
	
	*tResult = 0;
	return TRUE;
}
//PROCESS_FOR_INVENTORY_TO_TRADE
BOOL MyWork::ProcessForInventoryToTrade(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tIndex2 < 0) || (tIndex2 > (MAX_TRADE_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	ITEM_INFO* tITEM_INFO;

	if (tPage1 == 1)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	if ((mAVATAR_OBJECT[tUserIndex].mTradeProcessState == 4) && (mAVATAR_OBJECT[tUserIndex].mTradeProcessMenu != 0))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	tITEM_INFO = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
	if (tITEM_INFO == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (tITEM_INFO->iCheckAvatarTrade == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	switch (tITEM_INFO->iSort)
	{
	case  2:
		if ((tQuantity1 < 1) || (tQuantity1 > MAX_ITEM_DUPLICATION_NUM))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] < tQuantity1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex2][0] > 0)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex2][0] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0])
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
			if ((mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex2][1] + tQuantity1) > MAX_ITEM_DUPLICATION_NUM)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
		}
		mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex2][1] += tQuantity1;
		mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] -= tQuantity1;
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] < 1)
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = 0;
		}
		mAVATAR_OBJECT[tUserIndex].ProcessForTradeInfo();
		*tResult = 0;
		
		return TRUE;
	default:
		if (mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex2][0] > 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		//mGAMELOG.GL_622_TRADESLOT_ITEM(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5]);
		mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex2][1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3];
		mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex2][2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4];
		mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex2][3] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5];
		mUSER[tUserIndex].mAvatarInfo.TradeSocket[tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.TradeSocket[tIndex2][1] = mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1];
		mUSER[tUserIndex].mAvatarInfo.TradeSocket[tIndex2][2] = mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2];


		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2] = 0;
		mAVATAR_OBJECT[tUserIndex].ProcessForTradeInfo();
		*tResult = 0;
		
		return TRUE;
	}
	mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
	return FALSE;
}
//PROCESS_FOR_TRADE_TO_INVENTORY
BOOL MyWork::ProcessForTradeToInventory(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if ((tIndex1 < 0) || (tIndex1 > (MAX_TRADE_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tXPost2 < 0) || (tXPost2 > 7) || (tYPost2 < 0) || (tYPost2 > 7))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	ITEM_INFO* tITEM_INFO;

	if (tPage2 == 1)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	if ((mAVATAR_OBJECT[tUserIndex].mTradeProcessState == 4) && (mAVATAR_OBJECT[tUserIndex].mTradeProcessMenu != 0))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	tITEM_INFO = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][0]);
	if (tITEM_INFO == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	switch (tITEM_INFO->iSort)
	{
	case  2:
		if ((tQuantity1 < 1) || (tQuantity1 > MAX_ITEM_DUPLICATION_NUM))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][1] < tQuantity1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] > 0)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][0])
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
			if ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] + tQuantity1) > MAX_ITEM_DUPLICATION_NUM)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = tXPost2;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = tYPost2;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] += tQuantity1;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][1] -= tQuantity1;
		if (mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][1] < 1)
		{
			mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][3] = 0;
		}
		mAVATAR_OBJECT[tUserIndex].ProcessForTradeInfo();
		
		*tResult = 0;
		return TRUE;
	default:
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] > 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		//mGAMELOG.GL_622_TRADESLOT_ITEM(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][1], mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][2], mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][3]);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = tXPost2;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = tYPost2;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][3];
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.TradeSocket[tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][1] = mUSER[tUserIndex].mAvatarInfo.TradeSocket[tIndex1][1];
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][2] = mUSER[tUserIndex].mAvatarInfo.TradeSocket[tIndex1][2];
		mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.TradeSocket[tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.TradeSocket[tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.TradeSocket[tIndex1][2] = 0;
		mAVATAR_OBJECT[tUserIndex].ProcessForTradeInfo();
		
		*tResult = 0;
		return TRUE;
	}
	mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
	return FALSE;
}
//PROCESS_FOR_TRADE_TO_TRADE
BOOL MyWork::ProcessForTradeToTrade(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if ((tIndex1 < 0) || (tIndex1 > (MAX_TRADE_SLOT_NUM - 1)) || (tIndex2 < 0) || (tIndex2 > (MAX_TRADE_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	ITEM_INFO* tITEM_INFO;

	if ((mAVATAR_OBJECT[tUserIndex].mTradeProcessState == 4) && (mAVATAR_OBJECT[tUserIndex].mTradeProcessMenu != 0))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	tITEM_INFO = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][0]);
	if (tITEM_INFO == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	switch (tITEM_INFO->iSort)
	{
	case  2:
		if ((tQuantity1 < 1) || (tQuantity1 > MAX_ITEM_DUPLICATION_NUM))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][1] < tQuantity1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex2][0] > 0)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex2][0] != mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][0])
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
			if ((mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex2][1] + tQuantity1) > MAX_ITEM_DUPLICATION_NUM)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
		}
		mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex2][1] += tQuantity1;
		mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][1] -= tQuantity1;
		if (mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][1] < 1)
		{
			mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][3] = 0;
		}
		mAVATAR_OBJECT[tUserIndex].ProcessForTradeInfo();
		*tResult = 0;
		
		return TRUE;
	default:
		if (mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex2][0] > 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex2][1] = mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][1];
		mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex2][2] = mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][2];
		mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex2][3] = mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][3];
		mUSER[tUserIndex].mAvatarInfo.TradeSocket[tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.TradeSocket[tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.TradeSocket[tIndex2][1] = mUSER[tUserIndex].mAvatarInfo.TradeSocket[tIndex1][1];
		mUSER[tUserIndex].mAvatarInfo.TradeSocket[tIndex2][2] = mUSER[tUserIndex].mAvatarInfo.TradeSocket[tIndex1][2];
		mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aTrade[tIndex1][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.TradeSocket[tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.TradeSocket[tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.TradeSocket[tIndex1][2] = 0;
		mAVATAR_OBJECT[tUserIndex].ProcessForTradeInfo();
		*tResult = 0;
		
		return TRUE;
	}
	mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
	return FALSE;
}
//PROCESS_FOR_INVENTORY_MONEY_TO_TRADE_MONEY
BOOL MyWork::ProcessForInventoryMoneyToTradeMoney(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if (tQuantity1 < 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mAVATAR_OBJECT[tUserIndex].mTradeProcessState == 4) && (mAVATAR_OBJECT[tUserIndex].mTradeProcessMenu != 0))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aMoney < tQuantity1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUTIL.CheckOverMaximum(mUSER[tUserIndex].mAvatarInfo.aTradeMoney, tQuantity1))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	//mGAMELOG.GL_623_TRADESLOT_MONEY(tUserIndex, 1, tQuantity1);
	mUSER[tUserIndex].mAvatarInfo.aTradeMoney += tQuantity1;
	mUSER[tUserIndex].mAvatarInfo.aMoney -= tQuantity1;
	
	mAVATAR_OBJECT[tUserIndex].ProcessForTradeInfo();
	*tResult = 0;
	return TRUE;
}
//PROCESS_FOR_TRADE_MONEY_TO_INVENTORY_MONEY
BOOL MyWork::ProcessForTradeMoneyToInventoryMoney(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if (tQuantity1 < 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mAVATAR_OBJECT[tUserIndex].mTradeProcessState == 4) && (mAVATAR_OBJECT[tUserIndex].mTradeProcessMenu != 0))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aTradeMoney < tQuantity1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUTIL.CheckOverMaximum(mUSER[tUserIndex].mAvatarInfo.aMoney, tQuantity1))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	//mGAMELOG.GL_623_TRADESLOT_MONEY(tUserIndex, 2, tQuantity1);
	mUSER[tUserIndex].mAvatarInfo.aMoney += tQuantity1;
	mUSER[tUserIndex].mAvatarInfo.aTradeMoney -= tQuantity1;
	
	mAVATAR_OBJECT[tUserIndex].ProcessForTradeInfo();
	*tResult = 0;
	return TRUE;
}
//PROCESS_FOR_INVENTORY_TO_STORE
BOOL MyWork::ProcessForInventoryToStore(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_STORE_ITEM_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	ITEM_INFO* tITEM_INFO;

	if (tPage1 == 1)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	if (tPage2 == 1)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandStoreDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	tITEM_INFO = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
	if (tITEM_INFO == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	switch (tITEM_INFO->iSort)
	{
	case  2:
		if ((tQuantity1 < 1) || (tQuantity1 > MAX_ITEM_DUPLICATION_NUM))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] < tQuantity1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage2][tIndex2][0] > 0)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage2][tIndex2][0] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0])
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
			if ((mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage2][tIndex2][1] + tQuantity1) > MAX_ITEM_DUPLICATION_NUM)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
		}
		mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage2][tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage2][tIndex2][1] += tQuantity1;
		mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] -= tQuantity1;
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] < 1)
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = 0;
		}
		*tResult = 0;
		
		return TRUE;
	default:
		if (mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage2][tIndex2][0] > 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		mGAMELOG.GL_STROESLOT_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][1], mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][2], mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][3], tITEM_INFO->iName, "Bankaya Koyuldu");
		mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage2][tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage2][tIndex2][1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3];
		mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage2][tIndex2][2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4];
		mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage2][tIndex2][3] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5];
		mUSER[tUserIndex].mAvatarInfo.StoreSocket[tPage2][tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.StoreSocket[tPage2][tIndex2][1] = mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1];
		mUSER[tUserIndex].mAvatarInfo.StoreSocket[tPage2][tIndex2][2] = mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2] = 0;
		*tResult = 0;
		
		return TRUE;
	}
	mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
	return FALSE;
}
//PROCESS_FOR_STORE_TO_INVENTORY
BOOL MyWork::ProcessForStoreToInventory(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_STORE_ITEM_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tXPost2 < 0) || (tXPost2 > 7) || (tYPost2 < 0) || (tYPost2 > 7))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	ITEM_INFO* tITEM_INFO;

	if (tPage1 == 1)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandStoreDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	if (tPage2 == 1)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	tITEM_INFO = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][0]);
	if (tITEM_INFO == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	switch (tITEM_INFO->iSort)
	{
	case  2:
		if ((tQuantity1 < 1) || (tQuantity1 > MAX_ITEM_DUPLICATION_NUM))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][1] < tQuantity1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] > 0)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][0])
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
			if ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] + tQuantity1) > MAX_ITEM_DUPLICATION_NUM)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = tXPost2;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = tYPost2;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] += tQuantity1;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][1] -= tQuantity1;
		if (mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][1] < 1)
		{
			mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][3] = 0;
		}
		*tResult = 0;
		
		return TRUE;
	default:
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] > 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		mGAMELOG.GL_STROESLOT_ITEM(tUserIndex,mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][1], mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][2], mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][3],tITEM_INFO->iName,"Envantere Alındı");
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = tXPost2;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = tYPost2;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][3];
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.StoreSocket[tPage1][tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][1] = mUSER[tUserIndex].mAvatarInfo.StoreSocket[tPage1][tIndex1][1];
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][2] = mUSER[tUserIndex].mAvatarInfo.StoreSocket[tPage1][tIndex1][2];
		mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.StoreSocket[tPage1][tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.StoreSocket[tPage1][tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.StoreSocket[tPage1][tIndex1][2] = 0;
		*tResult = 0;
		
		return TRUE;
	}
	mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
	return FALSE;
}
//PROCESS_FOR_STORE_TO_STORE
BOOL MyWork::ProcessForStoreToStore(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_STORE_ITEM_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_STORE_ITEM_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	ITEM_INFO* tITEM_INFO;

	if ((tPage1 == 1) || (tPage2 == 1))
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandStoreDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	tITEM_INFO = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][0]);
	if (tITEM_INFO == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	switch (tITEM_INFO->iSort)
	{
	case  2:
		if ((tQuantity1 < 1) || (tQuantity1 > MAX_ITEM_DUPLICATION_NUM))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][1] < tQuantity1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage2][tIndex2][0] > 0)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage2][tIndex2][0] != mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][0])
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
			if ((mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage2][tIndex2][1] + tQuantity1) > MAX_ITEM_DUPLICATION_NUM)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
		}
		mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage2][tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage2][tIndex2][1] += tQuantity1;
		mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][1] -= tQuantity1;
		if (mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][1] < 1)
		{
			mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][3] = 0;
		}
		*tResult = 0;
		
		return TRUE;
	default:
		if (mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage2][tIndex2][0] > 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage2][tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage2][tIndex2][1] = mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][1];
		mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage2][tIndex2][2] = mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][2];
		mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage2][tIndex2][3] = mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][3];
		mUSER[tUserIndex].mAvatarInfo.StoreSocket[tPage2][tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.StoreSocket[tPage1][tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.StoreSocket[tPage2][tIndex2][1] = mUSER[tUserIndex].mAvatarInfo.StoreSocket[tPage1][tIndex1][1];
		mUSER[tUserIndex].mAvatarInfo.StoreSocket[tPage2][tIndex2][2] = mUSER[tUserIndex].mAvatarInfo.StoreSocket[tPage1][tIndex1][2];
		mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.StoreSocket[tPage1][tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.StoreSocket[tPage1][tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.StoreSocket[tPage1][tIndex1][2] = 0;
		*tResult = 0;
		
		return TRUE;
	}
	mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
	return FALSE;
}
//PROCESS_FOR_INVENTORY_MONEY_TO_STORE_MONEY
BOOL MyWork::ProcessForInventoryMoneyToStoreMoney(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if (tQuantity1 < 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aMoney < tQuantity1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUTIL.CheckOverMaximum(mUSER[tUserIndex].mAvatarInfo.aStoreMoney, tQuantity1))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	//mGAMELOG.GL_625_STORESLOT_MONEY(tUserIndex, 1, tQuantity1);
	mUSER[tUserIndex].mAvatarInfo.aStoreMoney += tQuantity1;
	mUSER[tUserIndex].mAvatarInfo.aMoney -= tQuantity1;
	
	*tResult = 0;
	return TRUE;
}
//PROCESS_FOR_STORE_MONEY_TO_INVENTORY_MONEY
BOOL MyWork::ProcessForStoreMoneyToInventoryMoney(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if (tQuantity1 < 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aStoreMoney < tQuantity1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUTIL.CheckOverMaximum(mUSER[tUserIndex].mAvatarInfo.aMoney, tQuantity1))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	//mGAMELOG.GL_625_STORESLOT_MONEY(tUserIndex, 2, tQuantity1);
	mUSER[tUserIndex].mAvatarInfo.aMoney += tQuantity1;
	mUSER[tUserIndex].mAvatarInfo.aStoreMoney -= tQuantity1;
	
	*tResult = 0;
	return TRUE;
}
//PROCESS_FOR_INVENTORY_TO_SAVE
BOOL MyWork::ProcessForInventoryToSave(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tIndex2 < 0) || (tIndex2 > (MAX_SAVE_ITEM_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	ITEM_INFO* tITEM_INFO;

	if (tPage1 == 1)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	tITEM_INFO = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
	if (tITEM_INFO == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	switch (tITEM_INFO->iSort)
	{
	case  2:
		if ((tQuantity1 < 1) || (tQuantity1 > MAX_ITEM_DUPLICATION_NUM))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] < tQuantity1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex2][0] > 0)
		{
			if (mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex2][0] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0])
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
			if ((mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex2][1] + tQuantity1) > MAX_ITEM_DUPLICATION_NUM)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
		}
		mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex2][1] += tQuantity1;
		mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] -= tQuantity1;
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] < 1)
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = 0;
		}
		*tResult = 0;
		
		return TRUE;
	default:
		if (mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex2][0] > 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		mGAMELOG.GL_SAVESLOT_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][1], mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][2], mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][3], tITEM_INFO->iName, "Işınlayıcıya Koyuldu"); mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex2][1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3];
		mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex2][2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4];
		mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex2][3] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5];
		mUSER[tUserIndex].mAvatarInfo.SaveSocket[tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.SaveSocket[tIndex2][1] = mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1];
		mUSER[tUserIndex].mAvatarInfo.SaveSocket[tIndex2][2] = mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2] = 0;
		
		*tResult = 0;
		return TRUE;
	}
	mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
	return FALSE;
}
//PROCESS_FOR_SAVE_TO_INVENTORY
BOOL MyWork::ProcessForSaveToInventory(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if ((tIndex1 < 0) || (tIndex1 > (MAX_SAVE_ITEM_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tXPost2 < 0) || (tXPost2 > 7) || (tYPost2 < 0) || (tYPost2 > 7))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	ITEM_INFO* tITEM_INFO;

	if (tPage2 == 1)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	tITEM_INFO = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][0]);
	if (tITEM_INFO == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	switch (tITEM_INFO->iSort)
	{
	case  2:
		if ((tQuantity1 < 1) || (tQuantity1 > MAX_ITEM_DUPLICATION_NUM))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][1] < tQuantity1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] > 0)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][0])
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
			if ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] + tQuantity1) > MAX_ITEM_DUPLICATION_NUM)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = tXPost2;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = tYPost2;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] += tQuantity1;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][1] -= tQuantity1;
		if (mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][1] < 1)
		{
			mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][3] = 0;
		}
		
		*tResult = 0;
		return TRUE;
	default:
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] > 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		mGAMELOG.GL_SAVESLOT_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][1], mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][2], mUSER[tUserIndex].mAvatarInfo.aStoreItem[tPage1][tIndex1][3], tITEM_INFO->iName, "Envantere Koyuldu");
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = tXPost2;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = tYPost2;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][3];
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.SaveSocket[tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][1] = mUSER[tUserIndex].mAvatarInfo.SaveSocket[tIndex1][1];
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][2] = mUSER[tUserIndex].mAvatarInfo.SaveSocket[tIndex1][2];
		mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.SaveSocket[tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.SaveSocket[tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.SaveSocket[tIndex1][2] = 0;
		*tResult = 0;
		
		return TRUE;
	}
	mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
	return FALSE;
}
//PROCESS_FOR_SAVE_TO_SAVE
BOOL MyWork::ProcessForSaveToSave(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if ((tIndex1 < 0) || (tIndex1 > (MAX_SAVE_ITEM_SLOT_NUM - 1)) || (tIndex2 < 0) || (tIndex2 > (MAX_SAVE_ITEM_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	ITEM_INFO* tITEM_INFO;

	tITEM_INFO = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][0]);
	if (tITEM_INFO == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	switch (tITEM_INFO->iSort)
	{
	case  2:
		if ((tQuantity1 < 1) || (tQuantity1 > MAX_ITEM_DUPLICATION_NUM))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][1] < tQuantity1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		if (mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex2][0] > 0)
		{
			if (mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex2][0] != mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][0])
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
			if ((mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex2][1] + tQuantity1) > MAX_ITEM_DUPLICATION_NUM)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return FALSE;
			}
		}
		mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex2][1] += tQuantity1;
		mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][1] -= tQuantity1;
		if (mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][1] < 1)
		{
			mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][3] = 0;
		}
		
		*tResult = 0;
		return TRUE;
	default:
		if (mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex2][0] > 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex2][1] = mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][1];
		mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex2][2] = mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][2];
		mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex2][3] = mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][3];
		mUSER[tUserIndex].mAvatarInfo.SaveSocket[tIndex2][0] = mUSER[tUserIndex].mAvatarInfo.SaveSocket[tIndex1][0];
		mUSER[tUserIndex].mAvatarInfo.SaveSocket[tIndex2][1] = mUSER[tUserIndex].mAvatarInfo.SaveSocket[tIndex1][1];
		mUSER[tUserIndex].mAvatarInfo.SaveSocket[tIndex2][2] = mUSER[tUserIndex].mAvatarInfo.SaveSocket[tIndex1][2];
		mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.uSaveItem[tIndex1][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.SaveSocket[tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.SaveSocket[tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.SaveSocket[tIndex1][2] = 0;
		*tResult = 0;
		
		return TRUE;
	}
	mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
	return FALSE;
}
//PROCESS_FOR_INVENTORY_MONEY_TO_SAVE_MONEY
BOOL MyWork::ProcessForInventoryMoneyToSaveMoney(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if (tQuantity1 < 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aMoney < tQuantity1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUTIL.CheckOverMaximum(mUSER[tUserIndex].mAvatarInfo.uSaveMoney, tQuantity1))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	//mGAMELOG.GL_627_SAVESLOT_MONEY(tUserIndex, 1, tQuantity1);
	mUSER[tUserIndex].mAvatarInfo.uSaveMoney += tQuantity1;
	mUSER[tUserIndex].mAvatarInfo.aMoney -= tQuantity1;
	
	*tResult = 0;
	return TRUE;
}
//PROCESS_FOR_SAVE_MONEY_TO_INVENTORY_MONEY
BOOL MyWork::ProcessForSaveMoneyToInventoryMoney(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if (tQuantity1 < 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUSER[tUserIndex].mAvatarInfo.uSaveMoney < tQuantity1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUTIL.CheckOverMaximum(mUSER[tUserIndex].mAvatarInfo.aMoney, tQuantity1))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	//mGAMELOG.GL_627_SAVESLOT_MONEY(tUserIndex, 2, tQuantity1);
	mUSER[tUserIndex].mAvatarInfo.aMoney += tQuantity1;
	mUSER[tUserIndex].mAvatarInfo.uSaveMoney -= tQuantity1;
	
	*tResult = 0;
	return TRUE;
}
//PROCESS_FOR_LEARN_SKILL_2
BOOL MyWork::ProcessForLearnSkill2(int tUserIndex, int nIndex, int sIndex, int* tResult)
{
	int index01;
	int index02;
	int index03;
	int index04;
	NPC_INFO* tNPC_INFO;
	BOOL tCheckExistSkill;
	SKILL_INFO* tSKILL_INFO;

	tNPC_INFO = mNPC.Search(nIndex);
	if (tNPC_INFO == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	tCheckExistSkill = FALSE;
	for (index01 = 0; index01 < 3; index01++)
	{
		for (index02 = 0; index02 < 3; index02++)
		{
			for (index03 = 0; index03 < 3; index03++)
			{
				for (index04 = 0; index04 < 8; index04++)
				{
					if (tNPC_INFO->nSkillInfo2[index01][index02][index03][index04] == sIndex)
					{
						tCheckExistSkill = TRUE;
					}
				}
			}
		}
	}
	if (!tCheckExistSkill)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	tSKILL_INFO = mSKILL.Search(sIndex);
	if (tSKILL_INFO == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aSkillPoint < tSKILL_INFO->sLearnSkillPoint)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	for (index01 = 0; index01 < MAX_SKILL_SLOT_NUM; index01++)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] == tSKILL_INFO->sIndex)
		{
			break;
		}
	}
	if (index01 < MAX_SKILL_SLOT_NUM)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
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
			return FALSE;
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
			return FALSE;
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
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
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
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return FALSE;
		}
		break;
	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	mUSER[tUserIndex].mAvatarInfo.aSkillPoint -= tSKILL_INFO->sLearnSkillPoint;
	mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] = tSKILL_INFO->sIndex;
	mUSER[tUserIndex].mAvatarInfo.aSkill[index01][1] = tSKILL_INFO->sLearnSkillPoint;
	
	*tResult = 0;
	return TRUE;
}
//ProcessForInventoryBarToInventoryMoney
BOOL MyWork::ProcessForInventoryBarToInventoryMoney(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if (tQuantity1 < 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUSER[tUserIndex].mAvatarInfo.Inventorybar < tQuantity1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUTIL.CheckOverMaximum(mUSER[tUserIndex].mAvatarInfo.aMoney, 1000000000 * tQuantity1))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	//mGAMELOG.GL_623_TRADESLOT_MONEY(tUserIndex, 1, tQuantity1);
	mUSER[tUserIndex].mAvatarInfo.Inventorybar -= tQuantity1;
	mUSER[tUserIndex].mAvatarInfo.aMoney += 1000000000 * tQuantity1;
	
	*tResult = 0;
	return TRUE;
}
//ProcessForInventoryBarToInventoryMoney
BOOL MyWork::ProcessForInventoryMoneyToInventoryBar(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if (tQuantity1 != 1000000000)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aMoney < tQuantity1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	//mGAMELOG.GL_623_TRADESLOT_MONEY(tUserIndex, 1, tQuantity1);
	mUSER[tUserIndex].mAvatarInfo.Inventorybar += 1;
	mUSER[tUserIndex].mAvatarInfo.aMoney -= 1000000000;
	
	*tResult = 0;
	return TRUE;
}
//ProcessForInventoryBarToInventoryMoney
BOOL MyWork::ProcessForInventoryBarToTradeBar(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if (tQuantity1 < 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mAVATAR_OBJECT[tUserIndex].mTradeProcessState == 4) && (mAVATAR_OBJECT[tUserIndex].mTradeProcessMenu != 0))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUSER[tUserIndex].mAvatarInfo.Inventorybar < tQuantity1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	//mGAMELOG.GL_623_TRADESLOT_MONEY(tUserIndex, 1, tQuantity1);
	mUSER[tUserIndex].mAvatarInfo.Inventorybar -= tQuantity1;
	mUSER[tUserIndex].mAvatarInfo.TradeBar += tQuantity1;
	
	mAVATAR_OBJECT[tUserIndex].ProcessForTradeInfo();
	*tResult = 0;
	return TRUE;
}
//ProcessForInventoryBarToInventoryMoney
BOOL MyWork::ProcessForTradeBarToInventoryBar(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if (tQuantity1 < 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mAVATAR_OBJECT[tUserIndex].mTradeProcessState == 4) && (mAVATAR_OBJECT[tUserIndex].mTradeProcessMenu != 0))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUSER[tUserIndex].mAvatarInfo.TradeBar < tQuantity1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	//mGAMELOG.GL_623_TRADESLOT_MONEY(tUserIndex, 1, tQuantity1);
	mUSER[tUserIndex].mAvatarInfo.Inventorybar += tQuantity1;
	mUSER[tUserIndex].mAvatarInfo.TradeBar -= tQuantity1;
	
	mAVATAR_OBJECT[tUserIndex].ProcessForTradeInfo();
	*tResult = 0;
	return TRUE;
}
//ProcessForInventoryBarToInventoryMoney
BOOL MyWork::ProcessForInventoryBarToBankBar(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if (tQuantity1 < 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUSER[tUserIndex].mAvatarInfo.Inventorybar < tQuantity1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	//mGAMELOG.GL_623_TRADESLOT_MONEY(tUserIndex, 1, tQuantity1);
	mUSER[tUserIndex].mAvatarInfo.Inventorybar -= tQuantity1;
	mUSER[tUserIndex].mAvatarInfo.BankBar += tQuantity1;
	
	*tResult = 0;
	return TRUE;
}
//ProcessForInventoryBarToInventoryMoney
BOOL MyWork::ProcessForBankBarToInventoryBar(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if (tQuantity1 < 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUSER[tUserIndex].mAvatarInfo.BankBar < tQuantity1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	//mGAMELOG.GL_623_TRADESLOT_MONEY(tUserIndex, 1, tQuantity1);
	mUSER[tUserIndex].mAvatarInfo.Inventorybar += tQuantity1;
	mUSER[tUserIndex].mAvatarInfo.BankBar -= tQuantity1;
	
	*tResult = 0;
	return TRUE;
}
//ProcessForInventoryBarToInventoryMoney
BOOL MyWork::ProcessForInventoryBarToSeyisBar(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if (tQuantity1 < 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUSER[tUserIndex].mAvatarInfo.Inventorybar < tQuantity1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	//mGAMELOG.GL_623_TRADESLOT_MONEY(tUserIndex, 1, tQuantity1);
	mUSER[tUserIndex].mAvatarInfo.Inventorybar -= tQuantity1;
	mUSER[tUserIndex].mAvatarInfo.SeyisBar += tQuantity1;
	
	*tResult = 0;
	return TRUE;
}
//ProcessForInventoryBarToInventoryMoney
BOOL MyWork::ProcessForSeyisBarToInventoryBar(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult)
{
	if (tQuantity1 < 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mUSER[tUserIndex].mAvatarInfo.SeyisBar < tQuantity1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return FALSE;
	}

	//mGAMELOG.GL_623_TRADESLOT_MONEY(tUserIndex, 1, tQuantity1);
	mUSER[tUserIndex].mAvatarInfo.Inventorybar += tQuantity1;
	mUSER[tUserIndex].mAvatarInfo.SeyisBar -= tQuantity1;
	
	*tResult = 0;
	return TRUE;
}
//-------------------------------------------------------------------------------------------------