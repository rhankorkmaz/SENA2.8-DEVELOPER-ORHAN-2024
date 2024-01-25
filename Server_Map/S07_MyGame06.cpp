//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "Shengming.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_ITEM_OBJECT
//-------------------------------------------------------------------------------------------------
//INSTANCE
ITEM_OBJECT mITEM_OBJECT[MAX_ITEM_OBJECT_NUM];
//SET_SPACE_INDEX
void ITEM_OBJECT::SetSpaceIndex(void)
{
	mSPACE_INDEX[0] = (int)(mDATA.iLocation[0] / mGAME.MAX_RADIUS);
	mSPACE_INDEX[1] = (int)(mDATA.iLocation[1] / mGAME.MAX_RADIUS);
	mSPACE_INDEX[2] = (int)(mDATA.iLocation[2] / mGAME.MAX_RADIUS);
}
//UPDATE
void ITEM_OBJECT::Update(int tObjectIndex)
{
	if (!mCheckValidState)
	{
		return;
	}
	mDATA.iPresentTime = GetTickCount();
	if (mDATA.iCreateState == 1)
	{
		if ((mDATA.iPresentTime - mDATA.iCreateTime) < 1000)
		{
			return;
		}
		mDATA.iCreateState = 0;
	}
	else
	{
		if ((mDATA.iPresentTime - mDATA.iCreateTime) < 60000)
		{
			return;
		}
		mTRANSFER.B_ITEM_ACTION_RECV(tObjectIndex, mUniqueNumber, &mDATA, 3);
		mUTIL.Broadcast(TRUE, &mDATA.iLocation[0], UNIT_SCALE_RADIUS1, false);
		mCheckValidState = FALSE;
	}
}
//CHECK_POSSIBLE_GET_ITEM
BOOL ITEM_OBJECT::CheckPossibleGetItem(int tUserIndex)
{
	if (!mCheckValidState)
	{
		return FALSE;
	}
	if (mUTIL.GetLengthXYZ(&mDATA.iLocation[0], &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0]) > 450.0f)
	{
		return FALSE;
	}
	if ((mDATA.iPresentTime - mDATA.iCreateTime) > 30000)
	{
		return TRUE;
	}
	if (strcmp(mDATA.iMaster, "") == 0)
	{
		return TRUE;
	}
	if (strcmp(mDATA.iMaster, mUSER[tUserIndex].mAvatarInfo.aName) == 0)
	{
		return TRUE;
	}
	return FALSE;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_ZONEMAININFO
//-------------------------------------------------------------------------------------------------
//INSTANCE
ZONEMAININFO mZONEMAININFO;
//CREATE
ZONEMAININFO::ZONEMAININFO(void)
{
}
//INIT
BOOL ZONEMAININFO::Init(void)
{
	int index01;

	for (index01 = 0; index01 < MAX_ZONE_NUMBER_NUM; index01++)
	{
		mZoneLevelInfo[index01][0] = 0;
		mZoneLevelInfo[index01][1] = 0;
		mZoneTribeInfo[index01][0] = -1;
		mZoneTribeInfo[index01][1] = 0;
		switch ((index01 + 1))
		{
		case   1: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 1; break;
		case   2: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 1; break;
		case   3: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 1; break;
		case   4: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 1; break;
		case   6: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 1; break;
		case   7: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 1; break;
		case   8: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 1; break;
		case   9: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 1; break;
		case  11: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 1; break;
		case  12: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 1; break;
		case  13: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 1; break;
		case  14: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 1; break;
		case  16: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 0; break;
		case  17: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 0; break;
		case  18: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 0; break;
		case  19: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case  20: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case  21: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case  22: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 0; break;
		case  23: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 0; break;
		case  24: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 0; break;
		case  25: mZoneLevelInfo[index01][0] = 150; mZoneLevelInfo[index01][1] = 153; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case  26: mZoneLevelInfo[index01][0] = 150; mZoneLevelInfo[index01][1] = 153; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case  27: mZoneLevelInfo[index01][0] = 150; mZoneLevelInfo[index01][1] = 153; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case  28: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 0; break;
		case  29: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 0; break;
		case  30: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 0; break;
		case  31: mZoneLevelInfo[index01][0] = 154; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case  32: mZoneLevelInfo[index01][0] = 154; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case  33: mZoneLevelInfo[index01][0] = 154; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case  34: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 149; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case  35: mZoneLevelInfo[index01][0] = 150; mZoneLevelInfo[index01][1] = 153; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case  36: mZoneLevelInfo[index01][0] = 154; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case  37: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 0; break;
		case  38: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case  39: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 99; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 0; break;
		case  40: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 0; break;
		case  41: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 0; break;
		case  42: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 0; break;
		case  43: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 0; break;
		case  44: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 0; break;
		case  45: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 0; break;
		case  46: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 0; break;
		case  47: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 0; break;
		case  48: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 0; break;
		case  49: mZoneLevelInfo[index01][0] = 10; mZoneLevelInfo[index01][1] = 19; mZoneTribeInfo[index01][0] = 11; mZoneTribeInfo[index01][1] = 1; break;
		case  51: mZoneLevelInfo[index01][0] = 20; mZoneLevelInfo[index01][1] = 29; mZoneTribeInfo[index01][0] = 12; mZoneTribeInfo[index01][1] = 1; break;
		case  53: mZoneLevelInfo[index01][0] = 30; mZoneLevelInfo[index01][1] = 39; mZoneTribeInfo[index01][0] = 13; mZoneTribeInfo[index01][1] = 1; break;
		case  55: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case  56: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 0; break;
		case  57: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 0; break;
		case  58: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 0; break;
		case  59: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 0; break;
		case  60: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 0; break;
		case  61: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 0; break;
		case  62: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 0; break;
		case  63: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 0; break;
		case  64: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 0; break;
		case  65: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 0; break;
		case  66: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 0; break;
		case  67: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 0; break;
		case  68: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 0; break;
		case  69: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 0; break;
		case  70: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 0; break;
		case  71: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 0; mZoneTribeInfo[index01][1] = 0; break;
		case  72: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 1; mZoneTribeInfo[index01][1] = 0; break;
		case  73: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 2; mZoneTribeInfo[index01][1] = 0; break;
		case  74: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 0; break;
		case  75: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case  76: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case  77: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case  78: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case  79: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case  80: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case  81: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case  82: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case  83: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case  84: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 0; break;
		case  85: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case  86: mZoneLevelInfo[index01][0] = 150; mZoneLevelInfo[index01][1] = 153; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case  87: mZoneLevelInfo[index01][0] = 154; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case  88: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 0; break;
		case  89: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case  90: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case  91: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case  92: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case  93: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case  94: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case  95: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case  96: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case  97: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case  98: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 101: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 102: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 103: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 104: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 105: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 106: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 107: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 108: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 109: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 110: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 111: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 112: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 113: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 114: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 115: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 116: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 117: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 120: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 149; mZoneTribeInfo[index01][0] = 11; mZoneTribeInfo[index01][1] = 1; break;
		case 121: mZoneLevelInfo[index01][0] = 150; mZoneLevelInfo[index01][1] = 153; mZoneTribeInfo[index01][0] = 11; mZoneTribeInfo[index01][1] = 1; break;
		case 122: mZoneLevelInfo[index01][0] = 154; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 11; mZoneTribeInfo[index01][1] = 1; break;
		case 124: mZoneLevelInfo[index01][0] = 1; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 0; break;
		case 125: mZoneLevelInfo[index01][0] = 145; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case 126: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 127: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 128: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 129: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 130: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 131: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 132: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 133: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 134: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 135: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 136: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 137: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 140: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 3; mZoneTribeInfo[index01][1] = 1; break;
		case 141: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 3; mZoneTribeInfo[index01][1] = 1; break;
		case 142: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 3; mZoneTribeInfo[index01][1] = 1; break;
		case 143: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 3; mZoneTribeInfo[index01][1] = 1; break;
		case 144: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 112; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 0; break;
		case 145: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 0; break;
		case 146: mZoneLevelInfo[index01][0] = 40; mZoneLevelInfo[index01][1] = 49; mZoneTribeInfo[index01][0] = 11; mZoneTribeInfo[index01][1] = 1; break;
		case 147: mZoneLevelInfo[index01][0] = 50; mZoneLevelInfo[index01][1] = 59; mZoneTribeInfo[index01][0] = 12; mZoneTribeInfo[index01][1] = 1; break;
		case 148: mZoneLevelInfo[index01][0] = 60; mZoneLevelInfo[index01][1] = 69; mZoneTribeInfo[index01][0] = 13; mZoneTribeInfo[index01][1] = 1; break;
		case 149: mZoneLevelInfo[index01][0] = 70; mZoneLevelInfo[index01][1] = 79; mZoneTribeInfo[index01][0] = 11; mZoneTribeInfo[index01][1] = 1; break;
		case 150: mZoneLevelInfo[index01][0] = 80; mZoneLevelInfo[index01][1] = 89; mZoneTribeInfo[index01][0] = 12; mZoneTribeInfo[index01][1] = 1; break;
		case 151: mZoneLevelInfo[index01][0] = 90; mZoneLevelInfo[index01][1] = 99; mZoneTribeInfo[index01][0] = 13; mZoneTribeInfo[index01][1] = 1; break;
		case 152: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 105; mZoneTribeInfo[index01][0] = 13; mZoneTribeInfo[index01][1] = 1; break;
		case 153: mZoneLevelInfo[index01][0] = 106; mZoneLevelInfo[index01][1] = 112; mZoneTribeInfo[index01][0] = 13; mZoneTribeInfo[index01][1] = 1; break;
		case 154: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 115; mZoneTribeInfo[index01][0] = 11; mZoneTribeInfo[index01][1] = 1; break;
		case 155: mZoneLevelInfo[index01][0] = 116; mZoneLevelInfo[index01][1] = 118; mZoneTribeInfo[index01][0] = 12; mZoneTribeInfo[index01][1] = 1; break;
		case 156: mZoneLevelInfo[index01][0] = 119; mZoneLevelInfo[index01][1] = 121; mZoneTribeInfo[index01][0] = 13; mZoneTribeInfo[index01][1] = 1; break;
		case 157: mZoneLevelInfo[index01][0] = 122; mZoneLevelInfo[index01][1] = 124; mZoneTribeInfo[index01][0] = 11; mZoneTribeInfo[index01][1] = 1; break;
		case 158: mZoneLevelInfo[index01][0] = 125; mZoneLevelInfo[index01][1] = 127; mZoneTribeInfo[index01][0] = 12; mZoneTribeInfo[index01][1] = 1; break;
		case 159: mZoneLevelInfo[index01][0] = 128; mZoneLevelInfo[index01][1] = 130; mZoneTribeInfo[index01][0] = 13; mZoneTribeInfo[index01][1] = 1; break;
		case 160: mZoneLevelInfo[index01][0] = 131; mZoneLevelInfo[index01][1] = 133; mZoneTribeInfo[index01][0] = 11; mZoneTribeInfo[index01][1] = 1; break;
		case 161: mZoneLevelInfo[index01][0] = 134; mZoneLevelInfo[index01][1] = 136; mZoneTribeInfo[index01][0] = 12; mZoneTribeInfo[index01][1] = 1; break;
		case 162: mZoneLevelInfo[index01][0] = 137; mZoneLevelInfo[index01][1] = 139; mZoneTribeInfo[index01][0] = 13; mZoneTribeInfo[index01][1] = 1; break;
		case 163: mZoneLevelInfo[index01][0] = 140; mZoneLevelInfo[index01][1] = 142; mZoneTribeInfo[index01][0] = 13; mZoneTribeInfo[index01][1] = 1; break;
		case 164: mZoneLevelInfo[index01][0] = 143; mZoneLevelInfo[index01][1] = 145; mZoneTribeInfo[index01][0] = 13; mZoneTribeInfo[index01][1] = 1; break;
		case 167: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 168: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 169: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 170: mZoneLevelInfo[index01][0] = 145; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 171: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 172: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 173: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 174: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 175: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 112; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 176: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 112; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 177: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 112; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 178: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 122; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 179: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 122; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 180: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 122; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 181: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 122; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 182: mZoneLevelInfo[index01][0] = 123; mZoneLevelInfo[index01][1] = 132; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 183: mZoneLevelInfo[index01][0] = 123; mZoneLevelInfo[index01][1] = 132; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 184: mZoneLevelInfo[index01][0] = 123; mZoneLevelInfo[index01][1] = 132; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 185: mZoneLevelInfo[index01][0] = 123; mZoneLevelInfo[index01][1] = 132; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 186: mZoneLevelInfo[index01][0] = 133; mZoneLevelInfo[index01][1] = 142; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 187: mZoneLevelInfo[index01][0] = 133; mZoneLevelInfo[index01][1] = 142; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 188: mZoneLevelInfo[index01][0] = 133; mZoneLevelInfo[index01][1] = 142; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 189: mZoneLevelInfo[index01][0] = 133; mZoneLevelInfo[index01][1] = 142; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 190: mZoneLevelInfo[index01][0] = 143; mZoneLevelInfo[index01][1] = 145; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 191: mZoneLevelInfo[index01][0] = 143; mZoneLevelInfo[index01][1] = 145; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 192: mZoneLevelInfo[index01][0] = 143; mZoneLevelInfo[index01][1] = 145; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 193: mZoneLevelInfo[index01][0] = 143; mZoneLevelInfo[index01][1] = 145; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 194: mZoneLevelInfo[index01][0] = 157; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 14; mZoneTribeInfo[index01][1] = 2; break;
		case 195: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 112; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case 196: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 122; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case 197: mZoneLevelInfo[index01][0] = 123; mZoneLevelInfo[index01][1] = 132; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case 198: mZoneLevelInfo[index01][0] = 133; mZoneLevelInfo[index01][1] = 142; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case 199: mZoneLevelInfo[index01][0] = 143; mZoneLevelInfo[index01][1] = 145; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case 200: mZoneLevelInfo[index01][0] = 145; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 201: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = -1; mZoneTribeInfo[index01][1] = 1; break;
		case 202: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 203: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 204: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 205: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 206: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 207: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 208: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 209: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 210: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 211: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 212: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 213: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 214: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 215: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 216: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 217: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 218: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 219: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 220: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 221: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 222: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 223: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 224: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 225: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 226: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 227: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 228: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 229: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 230: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 231: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 232: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 233: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 234: mZoneLevelInfo[index01][0] = 157; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 11; mZoneTribeInfo[index01][1] = 1; break;
		case 235: mZoneLevelInfo[index01][0] = 157; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 11; mZoneTribeInfo[index01][1] = 1; break;
		case 236: mZoneLevelInfo[index01][0] = 157; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 11; mZoneTribeInfo[index01][1] = 1; break;
		case 237: mZoneLevelInfo[index01][0] = 157; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 11; mZoneTribeInfo[index01][1] = 1; break;
		case 238: mZoneLevelInfo[index01][0] = 157; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 11; mZoneTribeInfo[index01][1] = 1; break;
		case 239: mZoneLevelInfo[index01][0] = 157; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 11; mZoneTribeInfo[index01][1] = 1; break;
		case 240: mZoneLevelInfo[index01][0] = 157; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 11; mZoneTribeInfo[index01][1] = 1; break;
		case 241: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 242: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 243: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 244: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 245: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 246: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 247: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 248: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 249: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 250: mZoneLevelInfo[index01][0] = 157; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 15; mZoneTribeInfo[index01][1] = 1; break;
		case 251: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 252: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 253: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 254: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 255: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 256: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 257: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 258: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 259: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 260: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 4; mZoneTribeInfo[index01][1] = 0; break;
		case 261: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 262: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 5; mZoneTribeInfo[index01][1] = 0; break;
		case 263: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 264: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 265: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 266: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 7; mZoneTribeInfo[index01][1] = 0; break;
		case 267: mZoneLevelInfo[index01][0] = 70; mZoneLevelInfo[index01][1] = 112; mZoneTribeInfo[index01][0] = 15; mZoneTribeInfo[index01][1] = 1; break;
		case 268: mZoneLevelInfo[index01][0] = 113; mZoneLevelInfo[index01][1] = 145; mZoneTribeInfo[index01][0] = 15; mZoneTribeInfo[index01][1] = 1; break;
		case 269: mZoneLevelInfo[index01][0] = 146; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 15; mZoneTribeInfo[index01][1] = 1; break;
		case 295: mZoneLevelInfo[index01][0] = 157; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 11; mZoneTribeInfo[index01][1] = 1; break;
		case 296: mZoneLevelInfo[index01][0] = 157; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 11; mZoneTribeInfo[index01][1] = 1; break;
		case 292: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 293: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		case 294: mZoneLevelInfo[index01][0] = 100; mZoneLevelInfo[index01][1] = 157; mZoneTribeInfo[index01][0] = 6; mZoneTribeInfo[index01][1] = 0; break;
		}
	}
	return TRUE;
}
//FREE
void ZONEMAININFO::Free(void)
{
}
//RETURN_MIN_ZONE_LEVEL_INFO
int ZONEMAININFO::ReturnMinZoneLevelInfo(int tZoneNumber)
{
	
	if ((tZoneNumber < MIN_VALID_ZONE_NUMBER) || (tZoneNumber > MAX_VALID_ZONE_NUMBER))
	{
		
		return 0;
	}
	return mZoneLevelInfo[(tZoneNumber - 1)][0];
}
//RETURN_MAX_ZONE_LEVEL_INFO
int ZONEMAININFO::ReturnMaxZoneLevelInfo(int tZoneNumber)
{

	if ((tZoneNumber < MIN_VALID_ZONE_NUMBER) || (tZoneNumber > MAX_VALID_ZONE_NUMBER))
	{
	
		return 0;
	}
	return mZoneLevelInfo[(tZoneNumber - 1)][1];
}
//RETURN_ZONE_TRIBE_INFO_1
int ZONEMAININFO::ReturnZoneTribeInfo1(int tZoneNumber)
{
	if ((tZoneNumber < MIN_VALID_ZONE_NUMBER) || (tZoneNumber > MAX_VALID_ZONE_NUMBER))
	{
		return -1;
	}
	return mZoneTribeInfo[(tZoneNumber - 1)][0];
}
//RETURN_ZONE_TRIBE_INFO_2
int ZONEMAININFO::ReturnZoneTribeInfo2(int tZoneNumber)
{
	if ((tZoneNumber < MIN_VALID_ZONE_NUMBER) || (tZoneNumber > MAX_VALID_ZONE_NUMBER))
	{
		return -1;
	}
	return mZoneTribeInfo[(tZoneNumber - 1)][1];
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_ZONENPCINFO
//-------------------------------------------------------------------------------------------------
//INSTANCE
ZONENPCINFO mZONENPCINFO;
//CREATE
ZONENPCINFO::ZONENPCINFO(void)
{
}
//INIT
BOOL ZONENPCINFO::Init(void)
{
	DWORD nReadByte = 0;

	int nRead = 0;
	FILE* r_fp = NULL;

	HANDLE hFile = CreateFile("DATA\\002.BIN", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	if (!ReadFile(hFile, &mDATA[0], (MAX_ZONE_NUMBER_NUM * sizeof(ZONENPCINFODATA)), &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != (MAX_ZONE_NUMBER_NUM * sizeof(ZONENPCINFODATA)))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!CloseHandle(hFile))
	{
		return FALSE;
	}

	return TRUE;
}
//FREE
void ZONENPCINFO::Free(void)
{
}
//RETURN_ZONE_NUMBER
int ZONENPCINFO::ReturnZoneNumber(int tNPCNumber)
{
	int index01;
	int index02;

	for (index01 = 0; index01 < MAX_ZONE_NUMBER_NUM; index01++)
	{
		for (index02 = 0; index02 < mDATA[index01].mTotalNPCNum; index02++)
		{
			if (mDATA[index01].mNPCNumber[index02] == tNPCNumber)
			{
				return (index01 + 1);
			}
		}
	}
	return 0;
}
//RETURN_ZONE_COORD
int ZONENPCINFO::ReturnZoneCoord(int tNPCNumber, float tCoord[3])
{
	int index01;
	int index02;

	for (index01 = 0; index01 < MAX_ZONE_NUMBER_NUM; index01++)
	{
		for (index02 = 0; index02 < mDATA[index01].mTotalNPCNum; index02++)
		{
			if (mDATA[index01].mNPCNumber[index02] == tNPCNumber)
			{
				tCoord[0] = mDATA[index01].mNPCCoord[index02][0];
				tCoord[1] = mDATA[index01].mNPCCoord[index02][1];
				tCoord[2] = mDATA[index01].mNPCCoord[index02][2];
				return 1;
			}
		}
	}
	return 0;
}
//CHECK_NPC_FUNCTION
BOOL ZONENPCINFO::CheckNPCFunction(float tCoord[3], int tMenuIndex)
{
	if ((tMenuIndex < 0) || (tMenuIndex > 99))
	{
		return FALSE;
	}

	int index01;
	NPC_INFO* tNPC_INFO;

	for (index01 = 0; index01 < mDATA[(mSERVER_INFO.mServerNumber - 1)].mTotalNPCNum; index01++)
	{
		tNPC_INFO = mNPC.Search(mDATA[(mSERVER_INFO.mServerNumber - 1)].mNPCNumber[index01]);
		if (tNPC_INFO == NULL)
		{
			continue;
		}
		if (tNPC_INFO->nMenu[tMenuIndex] != 2)
		{
			continue;
		}
		if (mUTIL.GetDoubleXYZ(&mDATA[(mSERVER_INFO.mServerNumber - 1)].mNPCCoord[index01][0], &tCoord[0]) < 10000.0f)
		{
			return TRUE;
		}
	}
	return TRUE;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_HACKINFO
//-------------------------------------------------------------------------------------------------
//INSTANCE
HACKINFO mHACKINFO;
//CREATE
HACKINFO::HACKINFO(void)
{
}
//INIT
BOOL HACKINFO::Init(void)
{
	char tempString01[1000];
	FILE* r_fp = NULL;

	if (!(r_fp = fopen("DATA/HACKINFO.TXT", "r")))
	{
		return FALSE;
	}

	mTotalHackInfoNum = 0;

	while (fgets(tempString01, 1000, r_fp) != NULL) {
		if (mTotalHackInfoNum == 0) {
			mTotalHackInfoNum++;
			continue;
		}
		//LOG_TO_FILE_1("--> %s\n",  tempString01);
		mHackSize[(mTotalHackInfoNum - 1)] = GetOneValueFromFile(tempString01);
		mTotalHackInfoNum++;
	}
	fclose(r_fp);
	return TRUE;
}
//FREE
void HACKINFO::Free(void)
{
}
//GET_ONE_VALUE_FROM_FILE
//BOOL HACKINFO::GetOneValueFromFile( HANDLE hFile, int tBufferSize, char *tBuffer )
//int HACKINFO::GetOneValueFromFile(FILE *hFile, int tBufferSize, char *tBuffer )
int HACKINFO::GetOneValueFromFile(const char* pBuffer)
{
	int i = 0;
	int chk = 0;
	char tbuf[20];
	int chk_cnt = 0;
	char* ptr_tmp = (char*)pBuffer;

	while (*ptr_tmp != '\0') {
		if (!chk) {
			if (*ptr_tmp == '[') {
				ptr_tmp++;
				chk_cnt++;
				if (chk_cnt == 2)
					chk = 1;
			}
			else {
				ptr_tmp++;
				continue;
			}
		}
		else {
			if (chk_cnt == 2) {
				tbuf[i++] = *ptr_tmp;
				if (*ptr_tmp == ']') {
					tbuf[--i] = '\0';
					break;
				}
			}
			ptr_tmp++;
		}
	}
	//LOG_TO_FILE_1("---> %s\n", tbuf);

	return atoi(tbuf);
}
//CHECK
BOOL HACKINFO::Check(int tHackSize)
{
	int index01;

	for (index01 = 0; index01 < mTotalHackInfoNum; index01++)
	{
		if (mHackSize[index01] == tHackSize)
		{
			return TRUE;
		}
	}
	return FALSE;
}
//-------------------------------------------------------------------------------------------------
