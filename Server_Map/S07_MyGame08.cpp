//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "Shengming.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MONSTER_OBJECT
//-------------------------------------------------------------------------------------------------
//INSTANCE
SHOP_OBJECT mSHOP_OBJECT[MAX_AVATAR_OBJECT_NUM];
//SET_SPACE_INDEX
void SHOP_OBJECT::SetSpaceIndex(void)
{
	mSPACE_INDEX[0] = (int)(mDATA.aLocation[0] / mGAME.MAX_RADIUS);
	mSPACE_INDEX[1] = (int)(mDATA.aLocation[1] / mGAME.MAX_RADIUS);
	mSPACE_INDEX[2] = (int)(mDATA.aLocation[2] / mGAME.MAX_RADIUS);
}
//UPDATE
void SHOP_OBJECT::Update(int tObjectIndex)
{
	int index01;
	int index02;
	int index03 = 0;;
	if (!mCheckValidState)
	{
		return;
	}
	mPresentTime = GetTickCount();
	for (index01 = 0; index01 < 5; index01++)
	{
		for (index02 = 0; index02 < 5; index02++)
		{
			if (mValetShopInfo.mItemInfo[index01][index02][0] == 0)
			{
				index03++;
			}
		}
	}
	if (index03 == 25)
	{
		mTRANSFER.B_VALETSHOPUPDATE(tObjectIndex, mUniqueNumber, &mDATA, 3);
		mUTIL.Broadcast(TRUE, &mDATA.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mCheckValidState = FALSE;
		return;
	}
	if ((mPresentTime - mCheckTime) < 50000)
	{
		return;
	}
	mCheckTime = GetTickCount();
	mPLAYUSER_COM.U_VALET_CHECK_ONLINE(ValetPlayerUserIndex, mDATA.aName);
	if (mPLAYUSER_COM.mRecv_Result != 0)
	{
		mTRANSFER.B_VALETSHOPUPDATE(tObjectIndex, mUniqueNumber, &mDATA, 3);
		mUTIL.Broadcast(TRUE, &mDATA.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mCheckValidState = TRUE;
	}
}