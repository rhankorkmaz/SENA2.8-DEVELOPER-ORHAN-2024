//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "Shengming.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//WORKER_FUNCTION
//-------------------------------------------------------------------------------------------------
//INSTANCE
//W_SOCKETSYSTEM
void W_SOCKETSYSTEM(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	unsigned int tRandom = 0;
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
	ITEM_INFO* tITEM_INFO1;
	ITEM_INFO* tITEM_INFO2;
	int tSort;
	int tSort2;
	int PageDeger;
	int tPage1;
	int tPage2;
	int IndexDeger;
	int tIndex1;
	int tIndex2;
	int tCost;
	int iValue;
	int Deger;
	int tSortDeger;


	CopyMemory(&tSortDeger, &tPacket[1], 4);
	CopyMemory(&PageDeger, &tPacket[5], 4);
	CopyMemory(&IndexDeger, &tPacket[9], 4);


	tIndex1 = IndexDeger % 100;
	tIndex2 = IndexDeger / 100;
	tPage1 = PageDeger % 100;
	tPage2 = PageDeger / 100;
	tSort = tSortDeger % 100;
	tSort2 = tSortDeger / 100;

	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	switch (tSort)
	{
	case 1:
		
		if ((tPage1 == 1) || (tPage1 == 2))
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
		if ((tITEM_INFO1->iSort != 6) && (tITEM_INFO1->iSort != 7) && (tITEM_INFO1->iSort != 8) && (tITEM_INFO1->iSort != 9) && (tITEM_INFO1->iSort != 10) && (tITEM_INFO1->iSort != 11) && (tITEM_INFO1->iSort != 12) && (tITEM_INFO1->iSort != 13) && (tITEM_INFO1->iSort != 14) && (tITEM_INFO1->iSort != 15) && (tITEM_INFO1->iSort != 16) && (tITEM_INFO1->iSort != 17) && (tITEM_INFO1->iSort != 18) && (tITEM_INFO1->iSort != 19) && (tITEM_INFO1->iSort != 20) && (tITEM_INFO1->iSort != 21) && (tITEM_INFO1->iSort != 1422))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tITEM_INFO1->iType != 3) && (tITEM_INFO1->iType != 4) && (tITEM_INFO1->iType != 5) && (tITEM_INFO1->iType != 6))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0] != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aMoney -= 100000000;
		
		tRandom = rand();
		switch (tRandom % 6)
		{
		case 0:
		case 1:
		case 2:
			iValue = 1;
			break;
		case 3:
		case 4:
			iValue = 2;
			break;
		case 5:
			iValue = 3;
			break;
		}
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0] = mUTIL.ChangeIUValue(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0], iValue);
		mTRANSFER.B_SOCKET(0, ((100 * iValue) + 1), mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1], mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2]);
		mGAMELOG.GL_OPEN_SOKET_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName, iValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 2:
		//Socket Kapatma
		if ((tPage1 == 1) || (tPage1 == 2))
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
		if ((tITEM_INFO1->iSort != 6) && (tITEM_INFO1->iSort != 7) && (tITEM_INFO1->iSort != 8) && (tITEM_INFO1->iSort != 9) && (tITEM_INFO1->iSort != 10) && (tITEM_INFO1->iSort != 11) && (tITEM_INFO1->iSort != 12) && (tITEM_INFO1->iSort != 13) && (tITEM_INFO1->iSort != 14) && (tITEM_INFO1->iSort != 15) && (tITEM_INFO1->iSort != 16) && (tITEM_INFO1->iSort != 17) && (tITEM_INFO1->iSort != 18) && (tITEM_INFO1->iSort != 19) && (tITEM_INFO1->iSort != 20) && (tITEM_INFO1->iSort != 21) && (tITEM_INFO1->iSort != 1422))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tITEM_INFO1->iType != 3) && (tITEM_INFO1->iType != 4) && (tITEM_INFO1->iType != 5) && (tITEM_INFO1->iType != 6))
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
		if ((tITEM_INFO2->iIndex != 1212))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		//Undrill Itemi silme
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][0] = 0;
		//Ýtemin Socketler
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0] = 0;
		mGAMELOG.GL_SELL_SOKET_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName);
		mTRANSFER.B_SOCKET(0, 2, mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1], mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 3:
		//Socket Yükleme
		if ((tPage1 == 1) || (tPage1 == 2))
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
		if ((tITEM_INFO1->iSort != 6) && (tITEM_INFO1->iSort != 7) && (tITEM_INFO1->iSort != 8) && (tITEM_INFO1->iSort != 9) && (tITEM_INFO1->iSort != 10) && (tITEM_INFO1->iSort != 11) && (tITEM_INFO1->iSort != 12) && (tITEM_INFO1->iSort != 13) && (tITEM_INFO1->iSort != 14) && (tITEM_INFO1->iSort != 15) && (tITEM_INFO1->iSort != 16) && (tITEM_INFO1->iSort != 17) && (tITEM_INFO1->iSort != 18) && (tITEM_INFO1->iSort != 19) && (tITEM_INFO1->iSort != 20) && (tITEM_INFO1->iSort != 21) && (tITEM_INFO1->iSort != 1422))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tITEM_INFO1->iType != 3) && (tITEM_INFO1->iType != 4) && (tITEM_INFO1->iType != 5) && (tITEM_INFO1->iType != 6))
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
		if (tITEM_INFO2->iIndex != 1244 && tITEM_INFO2->iIndex != 531)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		int tSocketDegeri;
		tRandom = rand();
		tSocketDegeri = ((tRandom % 33) + 1);
		//1.SOKET
		if (mUTIL.SOCKET1(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0]) == 0)
		{
			mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0] = mUTIL.CHANGESOCKET1(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0], 1);
			mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0] = mUTIL.CHANGESOCKET1DEGER(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0], tSocketDegeri);
		}
		//2.SOKET
		else if (mUTIL.SOCKET2(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1]) == 0)
		{
			mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1] = mUTIL.CHANGESOCKET2(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1], 1);
			mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1] = mUTIL.CHANGESOCKET2DEGER(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1], tSocketDegeri);
		}
		//3.SOKET
		else if (mUTIL.SOCKET3(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1]) == 0)
		{
			mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1] = mUTIL.CHANGESOCKET3(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1], 1);
			mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1] = mUTIL.CHANGESOCKET3DEGER(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1], tSocketDegeri);
		}
		//4.SOKET
		else if (mUTIL.SOCKET4(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2]) == 0)
		{
			mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2] = mUTIL.CHANGESOCKET4(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2], 1);
			mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2] = mUTIL.CHANGESOCKET4DEGER(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2], tSocketDegeri);
		}
		//5.SOKET	
		else if (mUTIL.SOCKET5(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2]) == 0)
		{
			mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2] = mUTIL.CHANGESOCKET5(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2], 1);
			mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2] = mUTIL.CHANGESOCKET5DEGER(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2], tSocketDegeri);
		}

		//Diamond Silme
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][0] = 0;
		mTRANSFER.B_SOCKET(0, 3, mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1], mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		break;
	case 4:
		//Socket Silme
		if ((tPage1 == 1) || (tPage1 == 2))
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
		if ((tITEM_INFO1->iSort != 6) && (tITEM_INFO1->iSort != 7) && (tITEM_INFO1->iSort != 8) && (tITEM_INFO1->iSort != 9) && (tITEM_INFO1->iSort != 10) && (tITEM_INFO1->iSort != 11) && (tITEM_INFO1->iSort != 12) && (tITEM_INFO1->iSort != 13) && (tITEM_INFO1->iSort != 14) && (tITEM_INFO1->iSort != 15) && (tITEM_INFO1->iSort != 16) && (tITEM_INFO1->iSort != 17) && (tITEM_INFO1->iSort != 18) && (tITEM_INFO1->iSort != 19) && (tITEM_INFO1->iSort != 20) && (tITEM_INFO1->iSort != 21) && (tITEM_INFO1->iSort != 1422))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tITEM_INFO1->iType != 3) && (tITEM_INFO1->iType != 4) && (tITEM_INFO1->iType != 5) && (tITEM_INFO1->iType != 6))
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
		if ((tITEM_INFO2->iIndex != 1213))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}


		switch (tSort2)
		{
		case 1:
			mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0] = mUTIL.CHANGESOCKET1(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0], 0);
			mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0] = mUTIL.CHANGESOCKET1DEGER(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0], 0);
			break;
		case 2:
			mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1] = mUTIL.CHANGESOCKET2(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1], 0);
			mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1] = mUTIL.CHANGESOCKET2DEGER(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1], 0);
			break;
		case 3:
			mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1] = mUTIL.CHANGESOCKET3(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1], 0);
			mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1] = mUTIL.CHANGESOCKET3DEGER(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1], 0);
			break;
		case 4:
			mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2] = mUTIL.CHANGESOCKET4(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2], 0);
			mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2] = mUTIL.CHANGESOCKET4DEGER(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2], 0);
			break;
		case 5:
			mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2] = mUTIL.CHANGESOCKET5(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2], 0);
			mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2] = mUTIL.CHANGESOCKET5DEGER(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2], 0);
			break;
		}

		//Diamond Silme
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][0] = 0;
		mTRANSFER.B_SOCKET(0, 4, mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1], mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		break;
	default:
		break;
	}
	return;

}
//W_ADDSOCKETSYSTEM
void W_ADDSOCKETSYSTEM(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	unsigned int tRandom = 0;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
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
	int iValue;
	int tProbability1;
	int tProbability2;
	int tSort;
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
	if (tITEM_INFO1->iType != 3 && tITEM_INFO1->iType != 4 && tITEM_INFO1->iType != 5 && tITEM_INFO1->iType != 6)
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
	if ((tITEM_INFO2->iIndex != 690))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0]) == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tProbability1 = 10;
	tRandom = rand() % 1000;

	if (mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0]) == 1)
		tProbability1 = mSERVER_INFO.WORLD_2_SOCKET_RATE;
	if (mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0]) == 2)
		tProbability1 = mSERVER_INFO.WORLD_3_SOCKET_RATE;
	if (mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0]) == 3)
		tProbability1 = mSERVER_INFO.WORLD_4_SOCKET_RATE;
	if (mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0]) == 4)
		tProbability1 = mSERVER_INFO.WORLD_5_SOCKET_RATE;

	//Success rate 
	if (tRandom < 75)
	{
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0] = mUTIL.ChangeIUValue(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0], 1);
		tSort = ((mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0])) * 100);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][2] = 0;
		mTRANSFER.B_ADDSOCKET(tSort, mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1], mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);


		int soket = mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0]);
		if (mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0]) == 4 || soket == 5) {
			tBroadcastInfoSort = 676;
			CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
			CopyMemory(&tBroadcastInfoData[4], &soket, 4);
			CopyMemory(&tBroadcastInfoData[8], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		}
		return;
	}
	//failure
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
	mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][0] = 0;
	mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][1] = 0;
	mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage2][tIndex2][2] = 0;
	mTRANSFER.B_ADDSOCKET(1, mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][1], mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage1][tIndex1][2]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	return;



}
//W_RANK
void W_RANK(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	mTRANSFER.B_RANKINFO(&mGAME.mRankInfo);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	return;
}
//W_UPRADGETOWER
void W_UPRADGETOWER(int tUserIndex)
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
	int tMapCode;
	int tTowerType;
	int tTowerRank;
	CopyMemory(&tMapCode, &tPacket[1], 4);
	CopyMemory(&tTowerType, &tPacket[5], 4);
	CopyMemory(&tTowerRank, &tPacket[9], 4);

	int tPage = -1;
	int tIndex = -1;
	int dur;
	int MapIndex;
	int CpTowerMobCodeOld;
	int CpTowerMobCodeNew;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	int index01;
	int index02;
	int forBreak = 0;


	if (mSERVER_INFO.mServerNumber != tMapCode)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mGAME.CpTowerServer != TRUE)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (((mGAME.mCpTower.CpTowers[mGAME.CpTowerZoneIndex] / 100) != tTowerRank) || ((mGAME.mCpTower.CpTowers[mGAME.CpTowerZoneIndex] % 100) != tTowerType))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	switch (tTowerType)
	{
	case 1://Silvr Tower
		switch (tTowerRank)
		{
		case 2:
			CpTowerMobCodeOld = 589;
			CpTowerMobCodeNew = 590;
			break;
		case 4:
			CpTowerMobCodeOld = 590;
			CpTowerMobCodeNew = 591;
			break;
		case 6:
			CpTowerMobCodeOld = 591;
			CpTowerMobCodeNew = 592;
			break;
		}
		break;
	case 2:
		switch (tTowerRank)
		{
		case 2:
			CpTowerMobCodeOld = 593;
			CpTowerMobCodeNew = 594;
			break;
		case 4:
			CpTowerMobCodeOld = 594;
			CpTowerMobCodeNew = 595;
			break;
		case 6:
			CpTowerMobCodeOld = 595;
			CpTowerMobCodeNew = 596;
			break;
		}
		break;
	case 3:
		switch (tTowerRank)
		{
		case 2:
			CpTowerMobCodeOld = 597;
			CpTowerMobCodeNew = 598;
			break;
		case 4:
			CpTowerMobCodeOld = 598;
			CpTowerMobCodeNew = 599;
			break;
		case 6:
			CpTowerMobCodeOld = 599;
			CpTowerMobCodeNew = 600;
			break;
		}
		break;
	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		break;
	}
	for (index01 = 0; index01 < 2; ++index01)
	{
		for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; ++index02)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aInventory[index01][index02][0] == 666) 
			{
				tPage = index01;
				tIndex = index02;
				dur++;
				break;
			}
		}
		if (dur == 1)
		{
			break;
		}
	}
	if (index01 == 2 && index02 == 64)
	{
		mTRANSFER.B_KuleUpradge(1, tPage, tIndex, 0, 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (!mSUMMON.CHANGECPTower(CpTowerMobCodeOld, CpTowerMobCodeNew, &mGAME.CpTowerYeri[0]))
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
	mTRANSFER.B_KuleUpradge(0, tPage, tIndex, 0, 0, 0);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	mGAME.mCpTower.CpTowers[mGAME.CpTowerZoneIndex] += 200;
	tBroadcastInfoSort = 752;
	CopyMemory(&tBroadcastInfoData[0], &mGAME.CpTowerZoneIndex, 4);
	CopyMemory(&tBroadcastInfoData[4], &mGAME.mCpTower.CpTowers[mGAME.CpTowerZoneIndex], 4);
	mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
	return;
}

//d
void W_RANKPRIZE(int tUserIndex)
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
	int iCount;
	int CpOdulu;
	int KanOdulu;
	int tValue[8];
	for (int index01 = 0; index01 < 8; index01++)
	{
		tValue[index01] = 0;
	}

	for (iCount = 0; iCount < MAX_TRIBE_SUBMASTER_NUM; ++iCount) {
		if (::strcmp(mGAME.mOldRankInfo.OldRank[mUSER[tUserIndex].mAvatarInfo.aTribe][iCount], mUSER[tUserIndex].mAvatarInfo.aName) == 0) {
			break;
		}
	}
	if (iCount == 10)
	{
		mTRANSFER.B_RANKPRIZE(1, 0, 0, 0, 0, 0, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	if (mGAME.mOldRankInfo.OldRankPoint[mUSER[tUserIndex].mAvatarInfo.aTribe][iCount] == 0)
	{
		mTRANSFER.B_RANKPRIZE(1, 0, 0, 0, 0, 0, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.RankPrize == 1)
	{
		mTRANSFER.B_RANKPRIZE(3, 0, 0, 0, 0, 0, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	switch (iCount)
	{
	case 0:
		CpOdulu = 10000;//1.
		KanOdulu = 1000;//1.
		break;
	case 1:
		CpOdulu = 9000;//2.
		KanOdulu = 900;//2.
		break;
	case 2:
		CpOdulu = 8000;//3.
		KanOdulu = 800;//3.
		break;
	case 3:
		CpOdulu = 7000;//4.
		KanOdulu = 700;//4.
		break;
	case 4:
		CpOdulu = 6000;//5.
		KanOdulu = 600;//5.
		break;
	case 5:
		CpOdulu = 5000;//6.
		KanOdulu = 500;//6.
		break;
	case 6:
		CpOdulu = 4000;//7.
		KanOdulu = 400;//7.
		break;
	case 7:
		CpOdulu = 3000;//8.
		KanOdulu = 300;//8.
		break;
	case 8:
		CpOdulu = 2000;//9.
		KanOdulu = 200;//9.
		break;
	case 9:
		CpOdulu = 1000;//10.
		KanOdulu = 100;//10.
		break;
	default:
		CpOdulu = 0;
		KanOdulu = 0;
		break;
	}
	mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += CpOdulu;
	mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += CpOdulu;

	mUSER[tUserIndex].mAvatarInfo.BloodStained += KanOdulu;
	mTRANSFER.B_AVATAR_CHANGE_INFO_2(121, mUSER[tUserIndex].mAvatarInfo.BloodStained);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	mUSER[tUserIndex].mAvatarInfo.RankPrize = 1;
	mTRANSFER.B_AVATAR_CHANGE_INFO_2(3, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	mGAMELOG.GL_RANK_PRIZE(tUserIndex, iCount);
	mTRANSFER.B_RANKPRIZE(0, 0, 0, 0, 0, 0, &tValue[0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	return;
}
//W_RANKSYSTEM HSB RANK
void W_RANKSYSTEM(int tUserIndex)
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
	if (mGAME.mWorldInfo.HollyBattleRank == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	int tSort;
	CopyMemory(&tSort, &tPacket[1], 4);

	switch (tSort)
	{
	case 1:
		if (mUSER[tUserIndex].mAvatarInfo.aRankPoint < 100)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aRankPoint < 100)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aRank = tSort;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(68, tSort);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 2:
		if (mUSER[tUserIndex].mAvatarInfo.aRankPoint < 300)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aRankPoint < 300)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aRank = tSort;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(68, tSort);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 3:
		if (mUSER[tUserIndex].mAvatarInfo.aRankPoint < 600)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aRankPoint < 600)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aRank = tSort;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(68, tSort);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 4:
		if (mUSER[tUserIndex].mAvatarInfo.aRankPoint < 1000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aRankPoint < 1000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aRank = tSort;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(68, tSort);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 5:
		if (mUSER[tUserIndex].mAvatarInfo.aRankPoint < 1500)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aRankPoint < 1500)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aRank = tSort;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(68, tSort);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 6:
		if (mUSER[tUserIndex].mAvatarInfo.aRankPoint < 2100)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aRankPoint < 2100)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aRank = tSort;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(68, tSort);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 7:
		if (mUSER[tUserIndex].mAvatarInfo.aRankPoint < 3000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aRankPoint < 3000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aRank = tSort;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(68, tSort);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	default:
		break;
	}

}
//W_KAPSUL
// CAPSULE
void W_KAPSUL(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	unsigned int tRandom = 0;
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
	int tValue;
	int tSort;
	int tCount;
	CopyMemory(&tValue, &tPacket[1], 4);
	CopyMemory(&tSort, &tPacket[5], 4);
	CopyMemory(&tCount, &tPacket[9], 4);


	int ItemID[8];
	int iPage[8];
	int iIndex[8];
	int iInvenPage[8];
	int	iInvenIndex[8];
	int	iInvenSlot[8];
	int Paralar[3];
	int index01;
	int index02;
	ITEM_INFO* pItemInfo[8];
	iPage[0] = 1;
	iPage[1] = 10;
	iPage[2] = 100;
	iPage[3] = 1000;
	iPage[4] = 10000;
	iPage[5] = 100000;
	iPage[6] = 1000000;
	iPage[7] = 10000000;
	iIndex[0] = 1; //64
	iIndex[1] = 100;//6400
	iIndex[2] = 10000;
	iIndex[3] = 1000000;
	iIndex[4] = 1;
	iIndex[5] = 100;
	iIndex[6] = 10000;
	iIndex[7] = 1000000;
	int ItemPage = 0;
	int ItemIndex1 = 0;
	int ItemIndex2 = 0;
	int ItemSlot1 = 0;
	int ItemSlot2 = 0;
	Paralar[1] = 360;
	Paralar[2] = 720;
	Paralar[3] = 99999;

	
	switch (tSort)
	{
	case 1:
		Paralar[1] = 360 * tCount;
		break;
	case 2:
		Paralar[2] = 720 * tCount;
		break;
	case 3:
		Paralar[3] = 99999 * tCount;
		break;
	}
								   // KapsulPuan
	if (mUSER[tUserIndex].mAvatarInfo.KapsulPuan < Paralar[1] && tSort == 1)
	{
		mTRANSFER.B_KAPSUL(12, 0, 0, 0, 0, 0, 0, 0, &ItemID[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	if (mUSER[tUserIndex].mAvatarInfo.OnlineHour < Paralar[2] && tSort == 2)
	{
		mTRANSFER.B_KAPSUL(4, 0, 0, 0, 0, 0, 0, 0, &ItemID[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	for (index01 = 0; index01 < 8; index01++)
	{
		iInvenSlot[index01] = 0;
		iInvenIndex[index01] = 0;
		iInvenPage[index01] = 0;
		ItemID[index01] = 0;
	}
	for (index01 = 0; index01 < tCount; index01++)
	{
		tRandom = rand() % 1000;
		
		if (tRandom < 90) { // 9% Chance
			tRandom = rand() % 5; 
			switch (tRandom) {
			case 0:
				ItemID[index01] = 1448; // 500 CP Charm
				break;
			case 1 :
				ItemID[index01] = 1124; // Scroll of Seeker
				break;
			case 2:
				ItemID[index01] = 1166; // CP PC
				break;
			case 3:
				ItemID[index01] = 1237; // Wing PC
				break;
			case 4:
				ItemID[index01] = 686; // AHS 7 Days
				break;
			}
		}
		else {
			tRandom = rand() % 13;
			switch (tRandom) {
			case 0:
				ItemID[index01] = 601;  // 5% Mount Box
				break;
			case 1:
				ItemID[index01] = 602; // Pet Box
				break;
			case 2:
				ItemID[index01] = 1047; // Odawa Ticket 180 min
				break;
			case 3:
				ItemID[index01] = 1041; // Sup Pill
				break;
			case 4:
				ItemID[index01] = 1449; // CP Charm (S)
				break;
			case 5:
				ItemID[index01] = 506; // HP Elix
				break;
			case 6:
				ItemID[index01] = 507; // Chi Elix
				break;
			case 7:
				ItemID[index01] = 508; // Str Elix
				break;
			case 8:
				ItemID[index01] = 509; // Dex Elix
				break;
			case 9:
				ItemID[index01] = 698; // Gold Feather F
				break;
			case 10:
				ItemID[index01] = 1190; // x2 Pet EXP
				break;
			case 11:
				ItemID[index01] = 1438; //Green Pill(M) 
				break;
			case 12:
				ItemID[index01] = 1439; //Green Pill(S) 
				break;
			}
		}
		pItemInfo[index01] = mITEM.Search(ItemID[index01]);
		if (pItemInfo[index01] == NULL)
		{
			char tContent[MAX_CHAT_CONTENT_LENGTH];
			snprintf(tContent, 61, "Capsule Item was empty... Time was restored");
			mTRANSFER.B_SECRET_CHAT_RECV(3, mSERVER_INFO.mServerNumber, "SYSTEM", &tContent[0], 1);
			break;
		}
		if (mUTIL.FindEmptyInvenForItem(tUserIndex, pItemInfo[index01], iInvenPage[index01], iInvenIndex[index01]) == false)
		{
			break;
		}
		iInvenSlot[index01] = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, iInvenPage[index01]);
		if (iInvenSlot[index01] == -1)
		{
			break;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage[index01]][iInvenSlot[index01]][0] = pItemInfo[index01]->iIndex;
		mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage[index01]][iInvenSlot[index01]][1] = iInvenIndex[index01] % 8;
		mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage[index01]][iInvenSlot[index01]][2] = iInvenIndex[index01] / 8;
		mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage[index01]][iInvenSlot[index01]][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage[index01]][iInvenSlot[index01]][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage[index01]][iInvenSlot[index01]][5] = 0;
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

	if (index01 != tCount)
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
		mTRANSFER.B_KAPSUL(8, 0, 0, 0, 0, 0, 0, 0, &ItemID[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	for (index01 = 0; index01 < tCount; index01++)
	{
		mGAMELOG.GL_CAPSUL_ITEM(tUserIndex, pItemInfo[index01]->iIndex, pItemInfo[index01]->iName);
		//GameLogger(413, "<CAPSUL RECEIVED>(%s),(%s)[ITEM]%d,[%s],[[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, pItemInfo[index01]->iIndex, pItemInfo[index01]->iName, mSERVER_INFO.mServerNumber);
	}

	Paralar[1] = 360 * tCount;
	Paralar[2] = 720 * tCount;
	Paralar[3] = 99999 * tCount;
	switch (tSort)
	{
	case 1:
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= Paralar[tSort];
		break;
	case 2:
		mUSER[tUserIndex].mAvatarInfo.OnlineHour -= Paralar[tSort];
		break;
	}

	mTRANSFER.B_KAPSUL((1000 * tCount), ItemPage, ItemSlot1, ItemSlot2, ItemIndex1, ItemIndex2, tSort, Paralar[tSort], &ItemID[0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	return;
}
void W_HIDECOSTUME(int tUserIndex)
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

	int tValue;
	CopyMemory(&tValue, &tPacket[1], 4);
	if (mAVATAR_OBJECT[tUserIndex].mDATA.aHideCostume == 0)
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aHideCostume = 1;
		mUSER[tUserIndex].mAvatarInfo.HideCostumeRegister = 1;
	}
	else
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aHideCostume = 0;
		mUSER[tUserIndex].mAvatarInfo.HideCostumeRegister = 0;
	}
	mTRANSFER.B_HIDECOSTUME(mAVATAR_OBJECT[tUserIndex].mDATA.aHideCostume, 0, 0);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	return;
}

//Lotus Alliance - Bottle
void W_BOTTLE(int tUserIndex)
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
	int tValue;
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tValue, &tPacket[5], 4);

	switch (tSort)
	{
	case 0:
		if (mUSER[tUserIndex].mAvatarInfo.Bottle[tValue] != 878
			&& mUSER[tUserIndex].mAvatarInfo.Bottle[tValue] != 879
			&& mUSER[tUserIndex].mAvatarInfo.Bottle[tValue] != 880
			&& mUSER[tUserIndex].mAvatarInfo.Bottle[tValue] != 881
			&& mUSER[tUserIndex].mAvatarInfo.Bottle[tValue] != 882)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.BottlePrice[tValue] < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		if (mUSER[tUserIndex].mAvatarInfo.BottleIndex != tValue && mUSER[tUserIndex].mAvatarInfo.BottleTime >= 0)
		{
			if (mUSER[tUserIndex].mAvatarInfo.BottlePrice[mUSER[tUserIndex].mAvatarInfo.BottleIndex] < 1)
			{
				mUSER[tUserIndex].mAvatarInfo.Bottle[mUSER[tUserIndex].mAvatarInfo.BottleIndex] = 0;
			}
		}
		mUSER[tUserIndex].mAvatarInfo.BottleIndex = tValue;
		mUSER[tUserIndex].mAvatarInfo.BottlePrice[tValue] -= 1;
		mUSER[tUserIndex].mAvatarInfo.BottleTime = 60;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_BOTTLE(0, 0, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		break;
	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}

//d
void W_LEGENDERYIMPROVE(int tUserIndex)
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

	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || 
		(tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	ITEM_INFO* tITEM_INFO1;
	ITEM_INFO* tITEM_INFO2;
	int tCost;
	int iValue;
	int kalan;
	int eger;
	int step;
	int tProbability1;
	int tProbability2;
	int tProtectIS = 0;
	int tRandomValue;
	int refinedegeri;
	char text[61];
	AVATAR_INFO* tAvatarInfo = &mUSER[tUserIndex].mAvatarInfo;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];
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
	tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
	if (tITEM_INFO2 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tITEM_INFO2->iIndex != 1831)
		&& (tITEM_INFO2->iIndex != 1832)
		&& (tITEM_INFO2->iIndex != 2332)
		&& (tITEM_INFO2->iIndex != 2383)
		&& (tITEM_INFO2->iIndex != 2373)
		&& (tITEM_INFO2->iIndex != 1948)
		&& (tITEM_INFO2->iIndex != 1952)
		&& (tITEM_INFO2->iIndex != 1949)
		&& (tITEM_INFO2->iIndex != 1950)
		&& (tITEM_INFO2->iIndex != 1951)
		&& (tITEM_INFO2->iIndex != 2400))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	switch (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0])
	{
	case 1831:
	case 1832:
		tCost = 50;
		tRandom = rand();
		switch (tRandom % 3)
		{
		case 0:
			iValue = 1;
			break;
		case 1:
			iValue = 2;
			break;
		case 2:
			iValue = 3;
			break;
		default:
			break;
		}
		break;
	case 2332:
	case 2383:
		tCost = 50;
		iValue = 1;
		break;
	case 2373:
	case 2400:
		tCost = 50;
		iValue = 1;
		break;
	}

	switch (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0])
	{
	case 1831:
	case 1832:
	case 2332:
	case 2383:
		tRandomValue = rand() % 100;
		if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == 15)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 50) 
		{
			char tContent[MAX_CHAT_CONTENT_LENGTH];
			snprintf(tContent, 61, "Not enough CP.");
			mTRANSFER.B_SECRET_CHAT_RECV(3, mSERVER_INFO.mServerNumber, "SYSTEM", &tContent[0], 1);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize, false);
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tRandomValue < 30)//%30 
		//if (tRandomValue < 100)//%100 
		{
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + iValue > 15)
			{
				iValue = 15 - mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
			}

			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 50;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 50;

			mUSER[tUserIndex].mAvatarInfo.aMoney -= 1000000;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(19, mUSER[tUserIndex].mAvatarInfo.aMoney);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] += iValue;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;

			//Step notice.
			switch (mAVATAR_OBJECT[tUserIndex].mDATA.aTribe)
			{
			case 0:
				strcpy(text, "[Dragon] ");
				break;
			case 1:
				strcpy(text, "[Snake] ");
				break;
			case 2:
				strcpy(text, "[Tiger] ");
				break;
			case 3:
				strcpy(text, "[Sky] ");
				break;
			default:
				break;
			}
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == 13) {
				strcat(text, mAVATAR_OBJECT[tUserIndex].mDATA.aName);
				strcat(text, " has reached 13 at step stage.");
				CopyMemory(&tData[0], text, MAX_CHAT_CONTENT_LENGTH);
				mRELAY_COM.U_DEMAND_BROADCAST_DATA(102, &tData[0]);

			}

			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == 14) {
				strcat(text, mAVATAR_OBJECT[tUserIndex].mDATA.aName);
				strcat(text, " has reached 14 at step stage.");
				CopyMemory(&tData[0], text, MAX_CHAT_CONTENT_LENGTH);
				mRELAY_COM.U_DEMAND_BROADCAST_DATA(102, &tData[0]);

			}

			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == 15) {
				strcat(text, mAVATAR_OBJECT[tUserIndex].mDATA.aName);
				strcat(text, " has reached 15 at step stage.");
				CopyMemory(&tData[0], text, MAX_CHAT_CONTENT_LENGTH);
				mRELAY_COM.U_DEMAND_BROADCAST_DATA(102, &tData[0]);

			}
			mTRANSFER.B_LEGANDARYIMPROVE(0, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;

		}
		else if (tRandomValue < 90) {
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + iValue < 0)
			{
				iValue = 0;
			}
			iValue = 0;
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 50;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 50;

			mUSER[tUserIndex].mAvatarInfo.aMoney -= 1000000;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(19, mUSER[tUserIndex].mAvatarInfo.aMoney);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] += iValue;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			mTRANSFER.B_LEGANDARYIMPROVE(1, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		else {
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + iValue > 15)
			{
				iValue = 15 - mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
			}

			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 50;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 50;

			mUSER[tUserIndex].mAvatarInfo.aMoney -= 1000000;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(19, mUSER[tUserIndex].mAvatarInfo.aMoney);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] += 100;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			mTRANSFER.B_LEGANDARYIMPROVE(5, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		return;

	case 2373:
	case 2400:
		tRandom = rand();
		tProbability1 = 50;
		if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == 15)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (0 < (unsigned int)tProbability1)
		{
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + iValue > 15)
			{
				iValue = 15 - mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
			}
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 50;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] += iValue;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			mTRANSFER.B_LEGANDARYIMPROVE(0, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			return;
		}
		
		iValue = -1;
		if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + iValue < 0)
		{
			iValue = 0;
		}
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 50;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] += iValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_LEGANDARYIMPROVE(1, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1948:
	case 1952:
		tRandom = rand();
		tProbability1 = 50;
		if (0 < (unsigned int)tProbability1)
		{
			step = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] % 256;
			kalan = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4];
			eger = (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] / 256) - step;

			iValue = 20;
			if (eger >= 20 && eger < 30)
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] -= eger * 256;
			}
			goto LABEL_13;
		}
		goto LABEL_12;

	case 1949:
		tRandom = rand();
		tProbability1 = 50;

		if (0 < (unsigned int)tProbability1)
		{
			step = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] % 256;
			kalan = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4];
			eger = (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] / 256) - step;

			iValue = 30;
			if (eger >= 30 && eger < 40)
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] -= eger * 256;
			}
			goto LABEL_13;
		}
		goto LABEL_12;

	case 1950:
		tRandom = rand();
		tProbability1 = 50;

		if (0 < (unsigned int)tProbability1)
		{
			step = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] % 256;
			kalan = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4];
			eger = (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] / 256) - step;
			iValue = 40;
			if (eger >= 40 && eger < 50)
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] -= eger * 256;
			}
			goto LABEL_13;
		}
		goto LABEL_12;

	case 1951:
		tRandom = rand();
		tProbability1 = 50;

		if (0 < (unsigned int)tProbability1)
		{
			step = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] % 256;
			kalan = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4];
			eger = (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] / 256) - step;
			iValue = 50;
			if (eger >= 50 && eger < 60)
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] -= eger * 256;
			}
			goto LABEL_13;
		}
		goto LABEL_12;

	LABEL_13:
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 50;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = iValue * 256 + step;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_LEGANDARYIMPROVE(0, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	LABEL_14:
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 50;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = kalan + 256;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_LEGANDARYIMPROVE(0, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	LABEL_12:
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 50;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_LEGANDARYIMPROVE(1, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	return;

}
//W_VALETSHOPSEND
void W_VALETSHOPSEND(int tUserIndex)
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
	if (mSERVER_INFO.mServerNumber != 1 && 
		mSERVER_INFO.mServerNumber != 6 && 
		mSERVER_INFO.mServerNumber != 11 && 
		mSERVER_INFO.mServerNumber != 140 && 
		mSERVER_INFO.mServerNumber != 37)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	int tSort;
	int unk2;
	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&unk2, &tPacket[5], 4);
	CopyMemory(&tAvatarName[0], &tPacket[9], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
	int ValutShopIndex;

	switch (tSort)
	{
	case 1://What comes when you press the button
		ValutShopIndex = mUTIL.SearchValetShop(2, mUSER[tUserIndex].mAvatarInfo.aName);
		//Checking whether the market is open or closed and if it's open, sending it closed
		if (mSHOP_OBJECT[ValutShopIndex].mCheckValidState || ValutShopIndex != -1)
		{
			mTRANSFER.B_VALETSHOPSEND(1, 1, &mVALETINFO.mRecv_ValetInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mVALETINFO.U_VALET_INFO(tSort, tAvatarName);
		if (mVALETINFO.mRecv_Result != 0)
		{
			mTRANSFER.B_VALETSHOPSEND(100, 0, &mVALETINFO.mRecv_ValetInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_VALETSHOPSEND(tSort, 0, &mVALETINFO.mRecv_ValetInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 2://to look at one's own market
		ValutShopIndex = mUTIL.SearchValetShop(2, mUSER[tUserIndex].mAvatarInfo.aName);
		//Checking whether the market is open or closed
		if (ValutShopIndex == -1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (!mSHOP_OBJECT[ValutShopIndex].mCheckValidState)
		{
			mTRANSFER.B_VALETSHOPSEND(100, 0, &mVALETINFO.mRecv_ValetInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mVALETINFO.U_VALET_INFO(tSort, mUSER[tUserIndex].mAvatarInfo.aName);
		if (mVALETINFO.mRecv_Result != 0)
		{
			mTRANSFER.B_VALETSHOPSEND(100, 0, &mVALETINFO.mRecv_ValetInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_VALETSHOPSEND(tSort, 0, &mVALETINFO.mRecv_ValetInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 3://to check someone's market
		ValutShopIndex = mUTIL.SearchValetShop(2, tAvatarName);

		if (ValutShopIndex == -1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (!mSHOP_OBJECT[ValutShopIndex].mCheckValidState)
		{
			mTRANSFER.B_VALETSHOPSEND(100, 0, &mVALETINFO.mRecv_ValetInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		mVALETINFO.U_VALET_INFO(tSort, tAvatarName);
		if (mVALETINFO.mRecv_Result != 0)
		{
			mTRANSFER.B_VALETSHOPSEND(100, 0, &mVALETINFO.mRecv_ValetInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_VALETSHOPSEND(tSort, 0, &mVALETINFO.mRecv_ValetInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}
void W_VALETSHOPITEMDEL(int tUserIndex)
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
	int ValutShopIndex;
	int tValetPage;
	int tValetSlot;
	int tItemId;
	int tPage;
	int tIndex;
	int mX;
	int mY;
	int tSort;
	int mItem[4];
	int mItemSoket[3];
	int tValue[9];
	int tCost;
	VALETSHOP_INFO tValetShop;

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory(&tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
	CopyMemory(&tValetPage, &tPacket[1 + MAX_AVATAR_NAME_LENGTH], 4);
	CopyMemory(&tValetSlot, &tPacket[5 + MAX_AVATAR_NAME_LENGTH], 4);
	CopyMemory(&tItemId, &tPacket[9 + MAX_AVATAR_NAME_LENGTH], 4);
	CopyMemory(&tPage, &tPacket[13 + MAX_AVATAR_NAME_LENGTH], 4);
	CopyMemory(&tIndex, &tPacket[17 + MAX_AVATAR_NAME_LENGTH], 4);
	CopyMemory(&mX, &tPacket[21 + MAX_AVATAR_NAME_LENGTH], 4);
	CopyMemory(&mY, &tPacket[25 + MAX_AVATAR_NAME_LENGTH], 4);
	CopyMemory(&tSort, &tPacket[29 + MAX_AVATAR_NAME_LENGTH], 4);
	CopyMemory(&mItem[0], &tPacket[33 + MAX_AVATAR_NAME_LENGTH], 16);
	CopyMemory(&mItemSoket[0], &tPacket[49 + MAX_AVATAR_NAME_LENGTH], 12);

	for (int index01 = 0; index01 < 9; index01++)
	{
		tValue[0] = 0;
	}


	//tResult
	// 0 Purchase
	// 1-2-3-4 Failed
	// 5 Inventory Spaces in use
	// 1000 Purchases non-purchases
	// 100 No Longer Available
	// 101 Can't Buy
	// 102 Silver Coin Limit Exceeded
	// 103 Silver Limit Exceeded
	// 104 Empty

	switch (tSort)
	{
	case 1://Removing items from your own market
		mVALETINFO.U_VALET_INFO(tSort, tAvatarName);
		if (mVALETINFO.mRecv_Result != 0)
		{
			mTRANSFER.B_VALETSHOPSEND1(1, &mVALETINFO.mRecv_ValetInfo, tPage, tIndex, &tValue[0], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		CopyMemory(&tValetShop, &mVALETINFO.mRecv_ValetInfo, sizeof(VALETSHOP_INFO));
		if (mVALETINFO.mRecv_ValetInfo.mItemInfo[tValetPage][tValetSlot][0] != tItemId)
		{
			mTRANSFER.B_VALETSHOPSEND1(1, &mVALETINFO.mRecv_ValetInfo, tPage, tIndex, &tValue[0], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mVALETINFO.mRecv_ValetInfo.mItemInfo[tValetPage][tValetSlot][1] != mItem[0])
		{
			mTRANSFER.B_VALETSHOPSEND1(1, &mVALETINFO.mRecv_ValetInfo, tPage, tIndex, &tValue[0], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mVALETINFO.mRecv_ValetInfo.mItemInfo[tValetPage][tValetSlot][2] != mItem[1])
		{
			mTRANSFER.B_VALETSHOPSEND1(1, &mVALETINFO.mRecv_ValetInfo, tPage, tIndex, &tValue[0], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mVALETINFO.mRecv_ValetInfo.mItemInfo[tValetPage][tValetSlot][3] != mItem[2])
		{
			mTRANSFER.B_VALETSHOPSEND1(1, &mVALETINFO.mRecv_ValetInfo, tPage, tIndex, &tValue[0], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mVALETINFO.mRecv_ValetInfo.mSoketInfo[tValetPage][tValetSlot][0] != mItemSoket[0])
		{
			mTRANSFER.B_VALETSHOPSEND1(1, &mVALETINFO.mRecv_ValetInfo, tPage, tIndex, &tValue[0], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mVALETINFO.mRecv_ValetInfo.mSoketInfo[tValetPage][tValetSlot][1] != mItemSoket[1])
		{
			mTRANSFER.B_VALETSHOPSEND1(1, &mVALETINFO.mRecv_ValetInfo, tPage, tIndex, &tValue[0], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mVALETINFO.mRecv_ValetInfo.mSoketInfo[tValetPage][tValetSlot][2] != mItemSoket[2])
		{
			mTRANSFER.B_VALETSHOPSEND1(1, &mVALETINFO.mRecv_ValetInfo, tPage, tIndex, &tValue[0], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mVALETINFO.U_VALET_BUY(1, tAvatarName, tValetPage, tValetSlot, tItemId);
		if (mVALETINFO.mRecv_Result != 0)
		{
			mTRANSFER.B_VALETSHOPSEND1(1, &mVALETINFO.mRecv_ValetInfo, tPage, tIndex, &tValue[0], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tValue[0] = tItemId;
		tValue[1] = mX;
		tValue[2] = mY;
		tValue[3] = mItem[0];
		tValue[4] = mItem[1];
		tValue[5] = mItem[2];
		tValue[6] = mItemSoket[0];
		tValue[7] = mItemSoket[1];
		tValue[8] = mItemSoket[2];
		tCost = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = tValue[5];
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage][tIndex][0] = tValue[6];
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage][tIndex][1] = tValue[7];
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage][tIndex][2] = tValue[8];

		tValetShop.mItemInfo[tValetPage][tValetSlot][0] = 0;
		tValetShop.mItemInfo[tValetPage][tValetSlot][1] = 0;
		tValetShop.mItemInfo[tValetPage][tValetSlot][2] = 0;
		tValetShop.mItemInfo[tValetPage][tValetSlot][3] = 0;
		tValetShop.mItemInfo[tValetPage][tValetSlot][4] = 0;
		tValetShop.mSoketInfo[tValetPage][tValetSlot][0] = 0;
		tValetShop.mSoketInfo[tValetPage][tValetSlot][1] = 0;
		tValetShop.mSoketInfo[tValetPage][tValetSlot][2] = 0;
		mTRANSFER.B_VALETSHOPSEND1(0, &tValetShop, tPage, tIndex, &tValue[0], tCost);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 2:
		ValutShopIndex = mUTIL.SearchValetShop(2, tAvatarName);
		if (ValutShopIndex == -1)
		{
			mTRANSFER.B_VALETSHOPSEND1(1, &mSHOP_OBJECT[1999].mValetShopInfo, tPage, tIndex, &tValue[0], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (!mSHOP_OBJECT[ValutShopIndex].mCheckValidState)
		{
			mTRANSFER.B_VALETSHOPSEND1(1, &mSHOP_OBJECT[ValutShopIndex].mValetShopInfo, tPage, tIndex, &tValue[0], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mSHOP_OBJECT[ValutShopIndex].mValetShopInfo.mItemInfo[tValetPage][tValetSlot][0] != tItemId)
		{
			mTRANSFER.B_VALETSHOPSEND1(1, &mSHOP_OBJECT[ValutShopIndex].mValetShopInfo, tPage, tIndex, &tValue[0], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mSHOP_OBJECT[ValutShopIndex].mValetShopInfo.mItemInfo[tValetPage][tValetSlot][1] != mItem[0])
		{
			mTRANSFER.B_VALETSHOPSEND1(1, &mSHOP_OBJECT[ValutShopIndex].mValetShopInfo, tPage, tIndex, &tValue[0], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mSHOP_OBJECT[ValutShopIndex].mValetShopInfo.mItemInfo[tValetPage][tValetSlot][2] != mItem[1])
		{
			mTRANSFER.B_VALETSHOPSEND1(1, &mSHOP_OBJECT[ValutShopIndex].mValetShopInfo, tPage, tIndex, &tValue[0], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mSHOP_OBJECT[ValutShopIndex].mValetShopInfo.mItemInfo[tValetPage][tValetSlot][3] != mItem[2])
		{
			mTRANSFER.B_VALETSHOPSEND1(1, &mSHOP_OBJECT[ValutShopIndex].mValetShopInfo, tPage, tIndex, &tValue[0], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mSHOP_OBJECT[ValutShopIndex].mValetShopInfo.mSoketInfo[tValetPage][tValetSlot][0] != mItemSoket[0])
		{
			mTRANSFER.B_VALETSHOPSEND1(1, &mSHOP_OBJECT[ValutShopIndex].mValetShopInfo, tPage, tIndex, &tValue[0], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mSHOP_OBJECT[ValutShopIndex].mValetShopInfo.mSoketInfo[tValetPage][tValetSlot][1] != mItemSoket[1])
		{
			mTRANSFER.B_VALETSHOPSEND1(1, &mSHOP_OBJECT[ValutShopIndex].mValetShopInfo, tPage, tIndex, &tValue[0], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mSHOP_OBJECT[ValutShopIndex].mValetShopInfo.mSoketInfo[tValetPage][tValetSlot][2] != mItemSoket[2])
		{
			mTRANSFER.B_VALETSHOPSEND1(1, &mSHOP_OBJECT[ValutShopIndex].mValetShopInfo, tPage, tIndex, &tValue[0], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aMoney < mSHOP_OBJECT[ValutShopIndex].mValetShopInfo.mItemInfo[tValetPage][tValetSlot][4])
		{
			mTRANSFER.B_VALETSHOPSEND1(1, &mSHOP_OBJECT[ValutShopIndex].mValetShopInfo, tPage, tIndex, &tValue[0], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] > 0)
		{
			mTRANSFER.B_VALETSHOPSEND1(5, &mSHOP_OBJECT[ValutShopIndex].mValetShopInfo, tPage, tIndex, &tValue[0], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mVALETINFO.U_VALET_BUY(2, tAvatarName, tValetPage, tValetSlot, tItemId);
		if (mVALETINFO.mRecv_Result != 0)
		{
			mTRANSFER.B_VALETSHOPSEND1(1, &mSHOP_OBJECT[ValutShopIndex].mValetShopInfo, tPage, tIndex, &tValue[0], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		ITEM_INFO* iItem;
		iItem = mITEM.Search(tItemId);
		tValue[0] = tItemId;
		tValue[1] = mX;
		tValue[2] = mY;
		tValue[3] = mItem[0];
		tValue[4] = mItem[1];
		tValue[5] = mItem[2];
		tValue[6] = mItemSoket[0];
		tValue[7] = mItemSoket[1];
		tValue[8] = mItemSoket[2];
		tCost = mSHOP_OBJECT[ValutShopIndex].mValetShopInfo.mItemInfo[tValetPage][tValetSlot][4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = tValue[5];
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage][tIndex][0] = tValue[6];
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage][tIndex][1] = tValue[7];
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage][tIndex][2] = tValue[8];
		mUSER[tUserIndex].mAvatarInfo.aMoney -= mSHOP_OBJECT[ValutShopIndex].mValetShopInfo.mItemInfo[tValetPage][tValetSlot][4];
		mSHOP_OBJECT[ValutShopIndex].mValetShopInfo.mShopMoney += mSHOP_OBJECT[ValutShopIndex].mValetShopInfo.mItemInfo[tValetPage][tValetSlot][4];
		if (mSHOP_OBJECT[ValutShopIndex].mValetShopInfo.mShopMoney > 999999999)
		{
			mSHOP_OBJECT[ValutShopIndex].mValetShopInfo.mShopMoney -= 1000000000;
			mSHOP_OBJECT[ValutShopIndex].mValetShopInfo.mShopBar += 1;
		}
		mSHOP_OBJECT[ValutShopIndex].mValetShopInfo.mItemInfo[tValetPage][tValetSlot][0] = 0;
		mSHOP_OBJECT[ValutShopIndex].mValetShopInfo.mItemInfo[tValetPage][tValetSlot][1] = 0;
		mSHOP_OBJECT[ValutShopIndex].mValetShopInfo.mItemInfo[tValetPage][tValetSlot][2] = 0;
		mSHOP_OBJECT[ValutShopIndex].mValetShopInfo.mItemInfo[tValetPage][tValetSlot][3] = 0;
		mSHOP_OBJECT[ValutShopIndex].mValetShopInfo.mItemInfo[tValetPage][tValetSlot][4] = 0;
		mSHOP_OBJECT[ValutShopIndex].mValetShopInfo.mSoketInfo[tValetPage][tValetSlot][0] = 0;
		mSHOP_OBJECT[ValutShopIndex].mValetShopInfo.mSoketInfo[tValetPage][tValetSlot][1] = 0;
		mSHOP_OBJECT[ValutShopIndex].mValetShopInfo.mSoketInfo[tValetPage][tValetSlot][2] = 0;

		mGAMELOG.GL_BUY_VALET_ITEM(tUserIndex, ValutShopIndex, iItem->iIndex, iItem->iName, tValue[4], tValue[6], tValue[7], tValue[8], mSHOP_OBJECT[ValutShopIndex].mValetShopInfo.mItemInfo[tValetPage][tValetSlot][4]);
		mTRANSFER.B_VALETSHOPSEND1(1000, &mSHOP_OBJECT[ValutShopIndex].mValetShopInfo, tPage, tIndex, &tValue[0], tCost);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	default:
		break;
	}
}

//W_VALETSHOPSEND
void W_VALET_SHOP_GET_ITEM(int tUserIndex)
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
	if (mSERVER_INFO.mServerNumber != 1 && mSERVER_INFO.mServerNumber != 6 && mSERVER_INFO.mServerNumber != 11 && mSERVER_INFO.mServerNumber != 140 && mSERVER_INFO.mServerNumber != 37)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	int tValetMoney;
	int tValetBar;
	CopyMemory(&tValetMoney, &tPacket[1], 4);
	CopyMemory(&tValetBar, &tPacket[5], 4);

	int ValutShopIndex;
	VALETSHOP_INFO tValetShop;

	ValutShopIndex = mUTIL.SearchValetShop(2, mUSER[tUserIndex].mAvatarInfo.aName);
	if (ValutShopIndex != -1)
	{
		mTRANSFER.B_VALETSHOPGETMONEY(3, tValetMoney, tValetBar);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	mVALETINFO.U_VALET_INFO(1, mUSER[tUserIndex].mAvatarInfo.aName);
	if (mVALETINFO.mRecv_Result != 0)
	{
		mTRANSFER.B_VALETSHOPGETMONEY(3, tValetMoney, tValetBar);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	CopyMemory(&tValetShop, &mVALETINFO.mRecv_ValetInfo, sizeof(VALETSHOP_INFO));
	if (tValetShop.mShopMoney != tValetMoney)
	{
		mTRANSFER.B_VALETSHOPGETMONEY(3, tValetMoney, tValetBar);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (tValetShop.mShopBar != tValetBar)
	{
		mTRANSFER.B_VALETSHOPGETMONEY(3, tValetMoney, tValetBar);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mUTIL.CheckOverMaximum(mUSER[tUserIndex].mAvatarInfo.aMoney, tValetMoney))
	{
		mTRANSFER.B_VALETSHOPGETMONEY(1, tValetMoney, tValetBar);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.Inventorybar + tValetBar > 500)
	{
		mTRANSFER.B_VALETSHOPGETMONEY(2, tValetMoney, tValetBar);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}


	tValetShop.mShopMoney -= tValetMoney;
	mUSER[tUserIndex].mAvatarInfo.aMoney += tValetMoney;
	tValetShop.mShopBar -= tValetBar;
	mUSER[tUserIndex].mAvatarInfo.Inventorybar += tValetBar;

	mGAMELOG.GL_GET_VALET_MONEY_ITEM(tUserIndex, tValetBar, tValetMoney);
	mVALETINFO.U_VALET_UPDATE(mUSER[tUserIndex].mAvatarInfo.aName, &tValetShop);
	mTRANSFER.B_VALETSHOPGETMONEY(0, tValetMoney, tValetBar);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	return;
}

// Lotus Alliance - Fishing


void W_FISHING(int tUserIndex)
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
	if (mSERVER_INFO.mServerNumber != 170)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.FishingTime < 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mUSER[tUserIndex].GainFish = 3;
	int tSort;
	float unk1[2];
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&unk1[0], &tPacket[5], 4);
	CopyMemory(&unk1[1], &tPacket[9], 4);
	switch (tSort)
	{
	case 1://Starting
		mAVATAR_OBJECT[tUserIndex].mDATA.mFishingState = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.mFishingStep = 1;
		mUSER[tUserIndex].WinFish = 0;
		mTRANSFER.B_FISHING(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, tSort, 1, 2);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, tUserIndex, false);
		return;
	case 2://Finishing
		mAVATAR_OBJECT[tUserIndex].mDATA.mFishingState = 0;
		mAVATAR_OBJECT[tUserIndex].mDATA.mFishingStep = 0;
		mTRANSFER.B_FISHING(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, tSort, 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, tUserIndex, false);
		return;
	default:
		break;
	}
}
void W_FISHING2(int tUserIndex)
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
	if (mSERVER_INFO.mServerNumber != 170)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.FishingTime < 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	int tSort;
	int unk1;
	int unk2;
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&unk1, &tPacket[5], 4);
	int tRandomValue;

	///Map control will be placed
	//IvyHall will be checked haalofevergreen
	//mFishingStep
	//0 stops
	//1 started
	//2 hold rows
	//draw 3 fish
	//pulled 4 fish
	//5 fail

	switch (tSort)
	{
	case 1:
		// If she catches fish
		if (mUSER[tUserIndex].GainFish != 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.mFishingStep != 3)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tRandomValue = myrand(0, 100);
		// fish drop rate - WILL CHANGE
		if (tRandomValue < 40)
		{
			mAVATAR_OBJECT[tUserIndex].mDATA.mFishingState = 1;
			mAVATAR_OBJECT[tUserIndex].mDATA.mFishingStep = 4;
			mUSER[tUserIndex].WinFish = 1;
			mUSER[tUserIndex].GainFish = 0;
			mTRANSFER.B_FISHING2(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, tSort, mAVATAR_OBJECT[tUserIndex].mDATA.mFishingState, mAVATAR_OBJECT[tUserIndex].mDATA.mFishingStep);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, tUserIndex, false);
			return;
		}
		else
		{
			mAVATAR_OBJECT[tUserIndex].mDATA.mFishingState = 1;
			mAVATAR_OBJECT[tUserIndex].mDATA.mFishingStep = 5;
			mUSER[tUserIndex].WinFish = 0;
			mUSER[tUserIndex].GainFish = 0;
			mTRANSFER.B_FISHING2(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, tSort, mAVATAR_OBJECT[tUserIndex].mDATA.mFishingState, mAVATAR_OBJECT[tUserIndex].mDATA.mFishingStep);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, tUserIndex, false);
			return;
		}
	case 2:
		mAVATAR_OBJECT[tUserIndex].mDATA.mFishingState = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.mFishingStep = 2;
		mTRANSFER.B_FISHING2(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, tSort, mAVATAR_OBJECT[tUserIndex].mDATA.mFishingState, mAVATAR_OBJECT[tUserIndex].mDATA.mFishingStep);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, tUserIndex, false);
		return;
	case 3:
		switch (unk1)
		{
		case 0:
			mAVATAR_OBJECT[tUserIndex].mDATA.mFishingState = 0;
			mAVATAR_OBJECT[tUserIndex].mDATA.mFishingStep = 0;
			mTRANSFER.B_FISHING2(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, tSort, mAVATAR_OBJECT[tUserIndex].mDATA.mFishingState, mAVATAR_OBJECT[tUserIndex].mDATA.mFishingStep);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, tUserIndex, false);
			return;
		case 1:
			mAVATAR_OBJECT[tUserIndex].mDATA.mFishingState = 1;
			mAVATAR_OBJECT[tUserIndex].mDATA.mFishingStep = 1;
			mTRANSFER.B_FISHING2(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, tSort, mAVATAR_OBJECT[tUserIndex].mDATA.mFishingState, mAVATAR_OBJECT[tUserIndex].mDATA.mFishingStep);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, tUserIndex, false);
			return;
		case 2:
			mAVATAR_OBJECT[tUserIndex].mDATA.mFishingState = 1;
			mAVATAR_OBJECT[tUserIndex].mDATA.mFishingStep = 2;
			mTRANSFER.B_FISHING2(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, tSort, mAVATAR_OBJECT[tUserIndex].mDATA.mFishingState, mAVATAR_OBJECT[tUserIndex].mDATA.mFishingStep);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, tUserIndex, false);
			return;
		}
	default:
		break;
	}

}
void W_FISHINGWINITEM(int tUserIndex)
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
	if (mSERVER_INFO.mServerNumber != 170)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].WinFish != 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].GainFish != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mAVATAR_OBJECT[tUserIndex].mDATA.mFishingStep != 4)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.FishingTime < 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}


	int ItemID;
	int iPage;
	int iIndex;
	int iInvenPage;
	int	iInvenIndex;
	int	iInvenSlot;
	ITEM_INFO* pItemInfo = NULL;
	int tRandom = 0;
	tRandom = rand() % 100;
	//Lotus Alliance - fish drop
	if (tRandom < 10)
	{
		ItemID = 585; // Blue Topaz Koi
	}
	else if (tRandom < 20) {
		ItemID = 584; // Amethyst Koi
	}
	else if (tRandom < 30)
	{
		ItemID = 583; // Saphire Koi
	}
	else if (tRandom < 50 ){
		ItemID = 582; // Emerald Koi
	}
	else if (tRandom < 60) {
		ItemID = 580; // 
	}
	else {
		ItemID = 581; // Citrine Koi
	}



	// 581 = Citrine Koi - unique
	// 580 = Ruby Koi
	pItemInfo = mITEM.Search(ItemID);
	if (pItemInfo == NULL)
	{
		mTRANSFER.B_FISHINGITEMSEND(2, 0, 0, 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mUTIL.FindEmptyInvenForItem(tUserIndex, pItemInfo, iPage, iInvenSlot) == false)
	{
		mTRANSFER.B_FISHINGITEMSEND(2, 0, 0, 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	iInvenIndex = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, iPage);
	if (iInvenIndex == -1)
	{
		mTRANSFER.B_FISHINGITEMSEND(2, 0, 0, 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	mGAMELOG.GL_GAIN_FISH(tUserIndex, pItemInfo->iIndex, pItemInfo->iName);
	mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenIndex][0] = pItemInfo->iIndex;
	mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenIndex][1] = iInvenSlot % 8;
	mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenIndex][2] = iInvenSlot / 8;
	mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenIndex][3] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenIndex][4] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenIndex][5] = 0;
	mUSER[tUserIndex].mAvatarInfo.InventorySocket[iPage][iInvenIndex][0] = 0;
	mUSER[tUserIndex].mAvatarInfo.InventorySocket[iPage][iInvenIndex][1] = 0;
	mUSER[tUserIndex].mAvatarInfo.InventorySocket[iPage][iInvenIndex][2] = 0;
	mUSER[tUserIndex].mAvatarInfo.InventorySocket[iPage][iInvenIndex][3] = 0;
	mUSER[tUserIndex].mAvatarInfo.InventorySocket[iPage][iInvenIndex][4] = 0;
	mUSER[tUserIndex].WinFish = 0;
	mTRANSFER.B_FISHINGITEMSEND(1, pItemInfo->iIndex, iPage, iInvenIndex, iInvenSlot);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	return;
}
//W_BLOODMAERKET
void W_BLOODMAERKET(int tUserIndex)
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
	int tMarket[50][3];
	//0 itemýd
	//item price
	//item cout


	mTRANSFER.B_BLOODMARKET(40, mEXTRA_COM.mBloodItemInfo[mUSER[tUserIndex].mAvatarInfo.aTribe]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

}
void W_BLOODMAERKETBUY(int tUserIndex)
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

	int tItemIndex;
	int tPage;
	int tIndex;
	int tValue[6];
	CopyMemory(&tItemIndex, &tPacket[1], 4);
	CopyMemory(&tPage, &tPacket[5], 4);
	CopyMemory(&tIndex, &tPacket[9], 4);
	CopyMemory(&tValue[0], &tPacket[13], 24);



	if (mEXTRA_COM.mBloodItemInfo[mUSER[tUserIndex].mAvatarInfo.aTribe][tItemIndex][0] != tValue[0])
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mEXTRA_COM.mBloodItemInfo[mUSER[tUserIndex].mAvatarInfo.aTribe][tItemIndex][1] > mUSER[tUserIndex].mAvatarInfo.BloodStained)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mUSER[tUserIndex].mAvatarInfo.BloodStained -= mEXTRA_COM.mBloodItemInfo[mUSER[tUserIndex].mAvatarInfo.aTribe][tItemIndex][1];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue[0];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = tValue[1];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = tValue[2];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = tValue[3];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = tValue[4];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = tValue[5];

	mTRANSFER.B_BLOODMARKETBUY(0, mUSER[tUserIndex].mAvatarInfo.BloodStained, tPage, tIndex, &tValue[0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	return;
}
void W_SKILLCOMBINE(int tUserIndex)
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
	return;
}

//d
void W_TIMEEFFECT(int tUserIndex)
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
	int Effect;
	CopyMemory(&Effect, &tPacket[1], 4);

	switch (Effect)
	{
	case 1:
		mUSER[tUserIndex].mAvatarInfo.TimeEffectMin = 120;
		mUSER[tUserIndex].mAvatarInfo.TimeEffect = 120;
		mUSER[tUserIndex].mAvatarInfo.OnlineHourTimeEffect = Effect;
		break;
	case 2:
		mUSER[tUserIndex].mAvatarInfo.TimeEffectMin = 240;
		mUSER[tUserIndex].mAvatarInfo.TimeEffect = 180;
		mUSER[tUserIndex].mAvatarInfo.OnlineHourTimeEffect = Effect;
		break;
	case 3:
		mUSER[tUserIndex].mAvatarInfo.TimeEffectMin = 360;
		mUSER[tUserIndex].mAvatarInfo.TimeEffect = 240;
		mUSER[tUserIndex].mAvatarInfo.OnlineHourTimeEffect = Effect;
		break;
	case 4:
		mUSER[tUserIndex].mAvatarInfo.TimeEffectMin = 480;
		mUSER[tUserIndex].mAvatarInfo.TimeEffect = 300;
		mUSER[tUserIndex].mAvatarInfo.OnlineHourTimeEffect = Effect;
		break;
	case 5:
		mUSER[tUserIndex].mAvatarInfo.TimeEffectMin = 600;
		mUSER[tUserIndex].mAvatarInfo.TimeEffect = 360;
		mUSER[tUserIndex].mAvatarInfo.OnlineHourTimeEffect = Effect;
		break;
	}
	mTRANSFER.B_AVATAR_CHANGE_INFO_2(55, mUSER[tUserIndex].mAvatarInfo.TimeEffect);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	return;
}
//W_GEAR_BREAK_SEND
void W_DESTROY_ITEM(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
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

	int tPage1;
	int tIndex1;
	CopyMemory(&tPage1, &tPacket[1], 4);
	CopyMemory(&tIndex1, &tPacket[5], 4);

	int tMoney;
	int tValue[6];
	ITEM_INFO* tITEM_INFO1;
	int EquipPercent = mUTIL.ReturnISValue(mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]));


	tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
	if (tITEM_INFO1 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tITEM_INFO1->iType != 3)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tITEM_INFO1->iSort < 7)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (EquipPercent - 1 > 9)
	{
		if (EquipPercent - 11 > 9)
		{
			if (EquipPercent - 21 > 9)
			{
				if (EquipPercent - 31 > 8)
				{
					if (EquipPercent != 40)
					{
						mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
						return;
					}
					tValue[0] = 1437;
					tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
					tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
					tValue[3] = 0;
					tValue[4] = 0;
					tValue[5] = 0;
					tMoney = 10000000;
				}
				else
				{
					tValue[0] = 1023;
					tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
					tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
					tValue[3] = 0;
					tValue[4] = 0;
					tValue[5] = 0;
					tMoney = 5000000;
				}
			}
			else
			{
				tValue[0] = 1022;
				tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
				tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
				tValue[3] = 0;
				tValue[4] = 0;
				tValue[5] = 0;
				tMoney = 3000000;
			}
		}
		else
		{
			tValue[0] = 1021;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;
			tMoney = 2000000;
		}
	}
	else
	{
		tValue[0] = 1021;
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		tValue[3] = 0;
		tValue[4] = 0;
		tValue[5] = 0;
		tMoney = 1000000;
	}

	// Protection
	if (tValue[0] == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
	mUSER[tUserIndex].mAvatarInfo.aMoney += tMoney;

	mTRANSFER.B_DESTROY_ITEM(0, tMoney, &tValue[0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	return;
}

//d
void W_CAPE_UPGRADE(int tUserIndex)
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
	if ((tITEM_INFO1->iSort != 8))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tITEM_INFO1->iType == 6) && (tITEM_INFO1->iType != 4))
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
	cout << tITEM_INFO2->iIndex << endl;
	if ((tITEM_INFO2->iIndex != 984))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aMoney < 100000000)
	{
		char tContent[MAX_CHAT_CONTENT_LENGTH];
		snprintf(tContent, 61, "Not enough Silver.");
		mTRANSFER.B_SECRET_CHAT_RECV(3, mSERVER_INFO.mServerNumber, "SYSTEM", &tContent[0], 1);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize, false);
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tCost = 100000000;
	switch (tITEM_INFO1->iIndex)
	{
	case 1401:
		tValue[0] = 1403;
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		tValue[3] = 0;
		tValue[4] = 0;
		tValue[5] = 0;	
		tProbability1 = 1000;//success rate
		break;
	case 1403:
		tValue[0] = 1404;
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		tValue[3] = 0;
		tValue[4] = 0;
		tValue[5] = 0;
		tProbability1 = 150;
		break;
	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
	mTRANSFER.B_AVATAR_CHANGE_INFO_2(19, mUSER[tUserIndex].mAvatarInfo.aMoney);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	tRandom = rand() % 10000;

	if (tRandom < (unsigned int)tProbability1)
	{
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
		mTRANSFER.B_CAPE_UPGRADE(0, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mGAMELOG.GL_IMPROVE_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], "CAPE YÜKSELDÝ");
		return;
	}
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
	mTRANSFER.B_CAPE_UPGRADE(1, &tValue[0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	mGAMELOG.GL_IMPROVE_ITEM(tUserIndex, tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], "CAPE YÜKSELMEDÝ");
	return;
}

void W_BEGGARADDABILITY(int tUserIndex) 
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

	ITEM_INFO* tITEM_INFO1;
	ITEM_INFO* tITEM_INFO2;
	int tCost;
	int iValue;
	int basari;
	int randomözellik;
	int kalan;
	int mammon;
	char tContent[MAX_CHAT_CONTENT_LENGTH];

	tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
	if (tITEM_INFO1 == NULL)
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

	if (tITEM_INFO2->iIndex != 2155
		&& tITEM_INFO2->iIndex != 2156
		&& tITEM_INFO2->iIndex != 2157
		&& tITEM_INFO2->iIndex != 2190
		&& tITEM_INFO2->iIndex != 2324
		&& tITEM_INFO2->iIndex != 2325)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}


	switch (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0])
	{
	case 2155:// Mammon
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] % 256 >= 10 && mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] % 256 < 20) { 
			if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] % 256 == 19) {
				goto LABEL_323;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] += 1;
			goto LABEL_311;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] % 256 >= 20 && mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] % 256 < 30) { 
			if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] % 256 == 29) {
				goto LABEL_323;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] += 1;
			goto LABEL_311;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] % 256 >= 30 && mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] % 256 < 40) { 
			if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] % 256 == 39) {
				goto LABEL_323;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] += 1;
			goto LABEL_311;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] % 256 >= 40 && mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] % 256 < 50) { 
			if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] % 256 == 49) {
				goto LABEL_323;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] += 1;
			goto LABEL_311;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] % 256 >= 50 && mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] % 256 < 60) { 
			if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] % 256 == 59) {
				goto LABEL_323;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] += 1;
			goto LABEL_311;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] % 256 >= 60 && mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] % 256 < 70) { 
			if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] % 256 == 69) {
				goto LABEL_323;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] += 1;
			goto LABEL_311;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] % 256 < 10) { 
			tRandom = rand() % 5;
			switch (tRandom) {
			case 0:
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] + 10;
				goto LABEL_322;
			case 1:
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] + 20;
				goto LABEL_322;
			case 2:
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] + 30;
				goto LABEL_322;
			case 3:
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] + 40;
				goto LABEL_322;
			case 4:
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] + 50;
				goto LABEL_322;
			default:
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] + 60;
				goto LABEL_322;
			}
		LABEL_322:
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			mTRANSFER.B_ENGRAVERECV(0, mUSER[tUserIndex].mAvatarInfo.aMoney, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, mUSER[tUserIndex].mAvatarInfo.ProtectionCharm, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);  // tresult,money,cp,charm,step?
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

	LABEL_323:
		snprintf(tContent, 61, "Max value reached.");
		mTRANSFER.B_SECRET_CHAT_RECV(3, mSERVER_INFO.mServerNumber, "SYSTEM", &tContent[0], 1);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize, false);
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;

	LABEL_311:
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_ENGRAVERECV(0, mUSER[tUserIndex].mAvatarInfo.aMoney, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, mUSER[tUserIndex].mAvatarInfo.ProtectionCharm, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);  // tresult,money,cp,charm,step?
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2156:// Cat eye -- Skillere veren /item 2156
		return;

	case 2157:// Deletes all attributes.
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_ENGRAVERECV(0, mUSER[tUserIndex].mAvatarInfo.aMoney, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, mUSER[tUserIndex].mAvatarInfo.ProtectionCharm, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2324://2156(Cat's Eye) deletes attributes.
		kalan = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] % 256;
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - kalan == 0) {
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = kalan;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_ENGRAVERECV(0, mUSER[tUserIndex].mAvatarInfo.aMoney, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, mUSER[tUserIndex].mAvatarInfo.ProtectionCharm, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2325://2155(Diopside) deletes attributes.
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] % 256 == 0) {
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		kalan = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] % 256;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - kalan;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_ENGRAVERECV(0, mUSER[tUserIndex].mAvatarInfo.aMoney, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, mUSER[tUserIndex].mAvatarInfo.ProtectionCharm, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2150://Fahrenheit Jade
		return;
	case 2168://Elite Pet
		return;
	case 2190://Shiny Stone
		return;
	}
	return;
}

//d
void W_FURY(int tUserIndex) {
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
	if (mUSER[tUserIndex].mAvatarInfo.BurstPill < 1) {
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.Fury > 10 || mUSER[tUserIndex].mAvatarInfo.Fury < 0) {
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.FuryTime > 30 || mUSER[tUserIndex].mAvatarInfo.FuryTime < 0) {
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	mUSER[tUserIndex].mAvatarInfo.BurstPill -= 1;
	mTRANSFER.B_AVATAR_CHANGE_INFO_2(84, mUSER[tUserIndex].mAvatarInfo.BurstPill);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);


	mUSER[tUserIndex].mAvatarInfo.FuryState = 1;
	mAVATAR_OBJECT[tUserIndex].mDATA.FuryState = 1;
	mTRANSFER.B_AVATAR_CHANGE_INFO_2(81, mUSER[tUserIndex].mAvatarInfo.FuryState);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	mUSER[tUserIndex].mAvatarInfo.FuryTime = 30;
	mTRANSFER.B_AVATAR_CHANGE_INFO_2(82, mUSER[tUserIndex].mAvatarInfo.FuryTime);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	return;
}
//d
void W_TRADER_WARLORD_UPGRADE(int tUserIndex) {
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
	int tV2;
	int tEnchantLoss;
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
	tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
	if (tITEM_INFO2 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tITEM_INFO2->iIndex != 501) && (tITEM_INFO2->iIndex != 502) && (tITEM_INFO2->iIndex != 503) && (tITEM_INFO2->iIndex != 504))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	tV2 = tITEM_INFO1->iIndex + 129;

	switch (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0])
	{
	case 501:
		tCost = 30000000;
		tProbability = 40;
		tEnchantLoss = -8;
		break;
	case 502:
		tCost = 30000000;
		tProbability = 30;
		tEnchantLoss = -6;
		break;
	case 503:
		tCost = 30000000;
		tProbability = 20;
		tEnchantLoss = -4;
		break;
	case 504:
		tCost = 30000000;
		tProbability = 10;
		tEnchantLoss = 0;
		break;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aMoney < tCost)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) < 30)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tRandom = rand();
	if ((tRandom % 100) < tProbability)
	{
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
		tValue[0] = tV2;
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		tValue[3] = 0;
		tValue[4] = mUTIL.ChangeISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], tEnchantLoss);
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
		mTRANSFER.B_ITEM_UPGRADE_RECV(0, tCost, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else
	{
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
		tValue[0] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0];
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		tValue[3] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3];
		tValue[4] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4];
		tValue[5] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5];
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
		mTRANSFER.B_ITEM_UPGRADE_RECV(1, tCost, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
}

//d
void W_ENGRAVE(int tUserIndex)
{
	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	unsigned int tRandom = 0;
	unsigned int tRandom2 = 0;
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
	int deger;
	int kalan;

	CopyMemory(&tPage1, &tPacket[1], 4);
	CopyMemory(&tIndex1, &tPacket[5], 4);
	CopyMemory(&tPage2, &tPacket[9], 4);
	CopyMemory(&tIndex2, &tPacket[13], 4);
	CopyMemory(&deger, &tPacket[17], 4);
	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	ITEM_INFO* tITEM_INFO1;
	ITEM_INFO* tITEM_INFO2;
	int tCost;
	int iValue;
	int iValue2;
	int tProbability1;
	int tProbability2;
	int tProtectIS = 0;
	int k = 16777216;
	int eskideger;
	int yenideger;

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
	tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
	if (tITEM_INFO2 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tRandom = rand() % 100;
	switch (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0])
	{
	case 17216:
	case 17217:
	case 17218:
	case 17219:
	case 17220:
	case 17221:
	case 17222:
	case 17223:
	case 17224:
	case 17225:
	case 17226:
	case 17227:
	case 17228:
	case 17229:
	case 17230:
	case 17231:
	case 17232:
	case 17233:
	case 17234:
	case 17235:
	case 17236:
	case 17237:
	case 17238:
	case 17239:
	case 17240:
	case 17241:
	case 17242:
	case 17243:
	case 17244:
	case 17245:
	case 17246:
	case 17247:
	case 17248:
	case 17249:
	case 17250:
	case 17251:
	case 17252:
	case 17253:
	case 17254:
	case 17255:
	case 17256:
	case 17257:
	case 17258:
	case 17259:
	case 17260:
	case 17261:
	case 17262:
	case 17263:
	case 17264:
	case 17265:
	case 17266:
	case 17267:
	case 17268:
	case 17269:
	case 17270:
	case 17271:
	case 17272:
	case 17273:
	case 17274:

		if (tRandom < 50)
		{

			if (mUTIL.ReturnICValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) > 0)
			{
				deger = mUTIL.ReturnICValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]); 

				iValue = tITEM_INFO2->iIndex - 17215;

				eskideger = mUTIL.ChangeEngraveValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], deger);
				yenideger = mUTIL.ChangeEngraveValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], iValue);

				mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 1000;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] -= eskideger;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] += yenideger;

				goto LABEL_312;
			}
			iValue = tITEM_INFO2->iIndex - 17215;
			goto LABEL_311;
		}

		if (mUSER[tUserIndex].mAvatarInfo.ProtectionCharm > 0) {
			goto LABEL_33;
		}
		tRandom2 = rand() % 100;
		if (tRandom2 < 10)
		{
			goto LABEL_32;
		}
		else {
			goto LABEL_31;
		}

	LABEL_33:
		--mUSER[tUserIndex].mAvatarInfo.ProtectionCharm;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(15, mUSER[tUserIndex].mAvatarInfo.ProtectionCharm);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 1000;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_ENGRAVERECV(2, mUSER[tUserIndex].mAvatarInfo.aMoney, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, mUSER[tUserIndex].mAvatarInfo.ProtectionCharm, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	LABEL_31:
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 1000;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_ENGRAVERECV(1, mUSER[tUserIndex].mAvatarInfo.aMoney, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, mUSER[tUserIndex].mAvatarInfo.ProtectionCharm, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	LABEL_32:
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 1000;
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
		mTRANSFER.B_ENGRAVERECV(3, mUSER[tUserIndex].mAvatarInfo.aMoney, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, mUSER[tUserIndex].mAvatarInfo.ProtectionCharm, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	LABEL_312:
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_ENGRAVERECV(0, mUSER[tUserIndex].mAvatarInfo.aMoney, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, mUSER[tUserIndex].mAvatarInfo.ProtectionCharm, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	LABEL_311:
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 1000;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeEngraveValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], iValue);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_ENGRAVERECV(0, mUSER[tUserIndex].mAvatarInfo.aMoney, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, mUSER[tUserIndex].mAvatarInfo.ProtectionCharm, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
}

//d
void W_TAILOR_SEAL(int tUserIndex) 
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


	ITEM_INFO* item1;
	ITEM_INFO* item2;
	ITEM_INFO* item3;
	ITEM_INFO* item4;
	ITEM_INFO* item5;

	int tRandomNumber;
	int tValue[6];
	int ivenindex[3];
	int tRandom;
	int tcost;
	switch (tSort)
	{
	case  1:

		if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) ||
			(tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)))
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
		if ((mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] < 88101) &&
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] > 88172) ||
			(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != 1422))
		{

			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 8000) {
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tcost = 8000;
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= tcost;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= tcost;


		tValue[0] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0];
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		tValue[3] = 0;
		tValue[4] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] - 100;
		tValue[5] = 0;

		item1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
		item2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
		item5 = mITEM.Search(tValue[0]);
		mGAMELOG.GL_MAKE_ITEM(tUserIndex, item1->iIndex, item1->iName, item2->iIndex, item2->iName, 0, 0, 0, 0, item5->iIndex, item5->iName);

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
		mTRANSFER.B_MUHURLEGEND(0, tcost, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
}

//d
void W_TAILOR_ITEM_UPGRADE(int tUserIndex) {

	//__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
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


	ITEM_INFO* tITEM_INFO1;
	ITEM_INFO* tITEM_INFO2;
	int tCost;
	int iValue;
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
	tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
	if (tITEM_INFO2 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	int tV2;
	int tRandom;
	int tValue[6];
	switch (tSort)
	{
	case 0:
		if ((tITEM_INFO1->iType != 4))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		if ((tITEM_INFO1->iSort != 7) && (tITEM_INFO1->iSort != 8) && (tITEM_INFO1->iSort != 9) && (tITEM_INFO1->iSort != 10) && (tITEM_INFO1->iSort != 11) && (tITEM_INFO1->iSort != 12) && (tITEM_INFO1->iSort != 13) && (tITEM_INFO1->iSort != 14) && (tITEM_INFO1->iSort != 15) && (tITEM_INFO1->iSort != 16) && (tITEM_INFO1->iSort != 17) && (tITEM_INFO1->iSort != 18) && (tITEM_INFO1->iSort != 19) && (tITEM_INFO1->iSort != 20) && (tITEM_INFO1->iSort != 21))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		if (tITEM_INFO2->iIndex != 984)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		tV2 = tITEM_INFO1->iIndex + 895;
		tCost = 1000;

		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < tCost)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) < 50 &&
			mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) < 12)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		tRandom = rand() % 100;
		if (tRandom < 50)//Success
		{
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= tCost;
			tValue[0] = tV2;
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
			mTRANSFER.B_ITEM_UPGRADE_RECV(0, tCost, &tValue[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			return;
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= tCost;
			tValue[0] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0];
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3];
			tValue[4] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4];
			tValue[5] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5];
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
			mTRANSFER.B_ITEM_UPGRADE_RECV(1, tCost, &tValue[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		return;
	}
}