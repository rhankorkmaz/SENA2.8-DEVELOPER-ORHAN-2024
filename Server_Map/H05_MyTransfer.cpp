//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "Shengming.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_TRANSFER
//-------------------------------------------------------------------------------------------------
//INSTANCE
MyTransfer mTRANSFER;
//CREATE
MyTransfer::MyTransfer(void)
{
}
//INIT
BOOL MyTransfer::Init(void)
{
	return TRUE;
}

//FREE
void MyTransfer::Free(void)
{
}
//B_CONNECT_OK
void MyTransfer::B_CONNECT_OK(int tRandomNumber)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = 0;
	memcpy(&mOriginal[1], &tRandomNumber, 4);
	mOriginalSize = 5;
}
//B_TEMP_REGISTER_RECV
void MyTransfer::B_TEMP_REGISTER_RECV(int tResult)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TEMP_REGISTER_RECV;
	memcpy(&mOriginal[1], &tResult, 4);
	mOriginalSize = S_TEMP_REGISTER_RECV;
}
//B_REGISTER_AVATAR_RECV
void MyTransfer::B_REGISTER_AVATAR_RECV(AVATAR_INFO* tAvatarInfo, int tEffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2], int tPremiumServerExpirationDate) // ÇÔ¼ö ¼±¾ð ¼öÁ¤ - int tPremiumServerExpirationDate Ãß°¡. // @_Premium_Server_@
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_REGISTER_AVATAR_RECV;
	memcpy(&mOriginal[1], tAvatarInfo, sizeof(AVATAR_INFO));
	memcpy(&mOriginal[(1 + sizeof(AVATAR_INFO))], tEffectValue, (MAX_AVATAR_EFFECT_SORT_NUM * 8));
	memcpy(&mOriginal[(1 + sizeof(AVATAR_INFO) + (MAX_AVATAR_EFFECT_SORT_NUM * 8))], &tPremiumServerExpirationDate, 4); // @_Premium_Server_@
	mOriginalSize = S_REGISTER_AVATAR_RECV;
}
//B_BROADCAST_WORLD_INFO
void MyTransfer::B_BROADCAST_WORLD_INFO(WORLD_INFO* tWorldInfo, TRIBE_INFO* tTribeInfo)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_BROADCAST_WORLD_INFO;
	memcpy(&mOriginal[1], tWorldInfo, sizeof(WORLD_INFO));
	memcpy(&mOriginal[(1 + sizeof(WORLD_INFO))], tTribeInfo, sizeof(TRIBE_INFO));
	mOriginalSize = S_BROADCAST_WORLD_INFO;
}
void MyTransfer::B_BROADCAST_WORLD_INFO2(WORLD_INFO* tWorldInfo, TRIBE_INFO* tTribeInfo)
{
	memset(mOriginal_C, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal_C[0] = P_BROADCAST_WORLD_INFO;
	memcpy(&mOriginal_C[1], tWorldInfo, sizeof(WORLD_INFO));
	memcpy(&mOriginal_C[(1 + sizeof(WORLD_INFO))], tTribeInfo, sizeof(TRIBE_INFO));
	mOriginalSize_C = S_BROADCAST_WORLD_INFO;
}

//B_AUTO_CHECK_ASK_SEND
void MyTransfer::B_AUTO_CHECK_ASK_SEND(int tDataSize, BYTE tData[1000])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_AUTO_CHECK_ASK_SEND;
	memcpy(&mOriginal[1], &tDataSize, 4);
	memcpy(&mOriginal[5], &tData[0], 1000);
	mOriginalSize = S_AUTO_CHECK_ASK_SEND;
}
//B_AVATAR_ACTION_RECV
void MyTransfer::B_AVATAR_ACTION_RECV(int tServerIndex, DWORD tUniqueNumber, OBJECT_FOR_AVATAR* tAvatar, int tCheckChangeActionState)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mAVATAR_OBJECT[tServerIndex].mUpdateTimeForBroadcast = GetTickCount();
	mOriginal[0] = P_AVATAR_ACTION_RECV;
	memcpy(&mOriginal[1], &tServerIndex, 4);
	memcpy(&mOriginal[5], &tUniqueNumber, 4);
	memcpy(&mOriginal[9], tAvatar, sizeof(OBJECT_FOR_AVATAR));
	memcpy(&mOriginal[(9 + sizeof(OBJECT_FOR_AVATAR))], &tCheckChangeActionState, 4);
	mOriginalSize = S_AVATAR_ACTION_RECV;
}
void MyTransfer::B_AVATAR_ACTION_RECV2(int tServerIndex, DWORD tUniqueNumber, OBJECT_FOR_AVATAR* tAvatar, int tCheckChangeActionState)
{
	memset(mOriginal2, 0, MAX_TRANSFER_BUFFER_SIZE);
	mAVATAR_OBJECT[tServerIndex].mUpdateTimeForBroadcast = GetTickCount();
	mOriginal2[0] = P_AVATAR_ACTION_RECV;
	memcpy(&mOriginal2[1], &tServerIndex, 4);
	memcpy(&mOriginal2[5], &tUniqueNumber, 4);
	memcpy(&mOriginal2[9], tAvatar, sizeof(OBJECT_FOR_AVATAR));
	memcpy(&mOriginal2[(9 + sizeof(OBJECT_FOR_AVATAR))], &tCheckChangeActionState, 4);
	mOriginalSize2 = S_AVATAR_ACTION_RECV;
}

//B_AVATAR_EFFECT_VALUE_INFO
void MyTransfer::B_AVATAR_EFFECT_VALUE_INFO(int tServerIndex, DWORD tUniqueNumber, int tEffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2], int tEffectValueState[MAX_AVATAR_EFFECT_SORT_NUM])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_AVATAR_EFFECT_VALUE_INFO;
	memcpy(&mOriginal[1], &tServerIndex, 4);
	memcpy(&mOriginal[5], &tUniqueNumber, 4);
	memcpy(&mOriginal[9], tEffectValue, (MAX_AVATAR_EFFECT_SORT_NUM * 8));
	memcpy(&mOriginal[(9 + MAX_AVATAR_EFFECT_SORT_NUM * 8)], &tEffectValueState[0], (MAX_AVATAR_EFFECT_SORT_NUM * 4));
	mOriginalSize = S_AVATAR_EFFECT_VALUE_INFO;
}
//B_AVATAR_CHANGE_INFO_1
void MyTransfer::B_AVATAR_CHANGE_INFO_1(int tServerIndex, DWORD tUniqueNumber, int tSort, int tValue01, int tValue02, int tValue03)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_AVATAR_CHANGE_INFO_1;
	memcpy(&mOriginal[1], &tServerIndex, 4);
	memcpy(&mOriginal[5], &tUniqueNumber, 4);
	memcpy(&mOriginal[9], &tSort, 4);
	memcpy(&mOriginal[13], &tValue01, 4);
	memcpy(&mOriginal[17], &tValue02, 4);
	memcpy(&mOriginal[21], &tValue03, 4);
	mOriginalSize = S_AVATAR_CHANGE_INFO_1;
}
//B_MONSTER_ACTION_RECV
void MyTransfer::B_MONSTER_ACTION_RECV(int tServerIndex, DWORD tUniqueNumber, OBJECT_FOR_MONSTER* tMonster, int tCheckChangeActionState)
{
	memset(mOriginal2, 0, MAX_TRANSFER_BUFFER_SIZE);
	mMONSTER_OBJECT[tServerIndex].mUpdateTimeForBroadcast = GetTickCount();
	mOriginal2[0] = P_MONSTER_ACTION_RECV;
	memcpy(&mOriginal2[1], &tServerIndex, 4);
	memcpy(&mOriginal2[5], &tUniqueNumber, 4);
	memcpy(&mOriginal2[9], tMonster, sizeof(OBJECT_FOR_MONSTER));
	memcpy(&mOriginal2[(9 + sizeof(OBJECT_FOR_MONSTER))], &tCheckChangeActionState, 4);
	mOriginalSize2 = S_MONSTER_ACTION_RECV;
}
//B_ITEM_ACTION_RECV
void MyTransfer::B_ITEM_ACTION_RECV(int tServerIndex, DWORD tUniqueNumber, OBJECT_FOR_ITEM* tItem, int tCheckChangeActionState)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mITEM_OBJECT[tServerIndex].mUpdateTimeForBroadcast = GetTickCount();
	mOriginal[0] = P_ITEM_ACTION_RECV;
	memcpy(&mOriginal[1], &tServerIndex, 4);
	memcpy(&mOriginal[5], &tUniqueNumber, 4);
	memcpy(&mOriginal[9], tItem, sizeof(OBJECT_FOR_ITEM));
	memcpy(&mOriginal[(9 + sizeof(OBJECT_FOR_ITEM))], &tCheckChangeActionState, 4);
	mOriginalSize = S_ITEM_ACTION_RECV;
}
void MyTransfer::B_ITEM_ACTION_RECV2(int tServerIndex, DWORD tUniqueNumber, OBJECT_FOR_ITEM* tItem, int tCheckChangeActionState)
{
	memset(mOriginal2, 0, MAX_TRANSFER_BUFFER_SIZE);
	mITEM_OBJECT[tServerIndex].mUpdateTimeForBroadcast = GetTickCount();
	mOriginal2[0] = P_ITEM_ACTION_RECV;
	memcpy(&mOriginal2[1], &tServerIndex, 4);
	memcpy(&mOriginal2[5], &tUniqueNumber, 4);
	memcpy(&mOriginal2[9], tItem, sizeof(OBJECT_FOR_ITEM));
	memcpy(&mOriginal2[(9 + sizeof(OBJECT_FOR_ITEM))], &tCheckChangeActionState, 4);
	mOriginalSize2 = S_ITEM_ACTION_RECV;
}
//B_GENERAL_NOTICE_RECV
void MyTransfer::B_GENERAL_NOTICE_RECV(char tContent[MAX_CHAT_CONTENT_LENGTH], int type)
{
	if (type == 1) {
		memset(mOriginal_C, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal_C[0] = P_GENERAL_NOTICE_RECV;
		memcpy(&mOriginal_C[1], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize_C = S_GENERAL_NOTICE_RECV;
	}
	else if (type == 2) {
		memset(mOriginal_R, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal_R[0] = P_GENERAL_NOTICE_RECV;
		memcpy(&mOriginal_R[1], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize_R = S_GENERAL_NOTICE_RECV;
	}
	else {
		memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal[0] = P_GENERAL_NOTICE_RECV;
		memcpy(&mOriginal[1], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize = S_GENERAL_NOTICE_RECV;
	}
}
//B_PROCESS_ATTACK_RECV
void MyTransfer::B_PROCESS_ATTACK_RECV(ATTACK_FOR_PROTOCOL* tAttackInfo)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_PROCESS_ATTACK_RECV;
	memcpy(&mOriginal[1], tAttackInfo, sizeof(ATTACK_FOR_PROTOCOL));
	mOriginalSize = S_PROCESS_ATTACK_RECV;
}
//B_AVATAR_CHANGE_INFO_2
void MyTransfer::B_AVATAR_CHANGE_INFO_2(int tSort, int tValue)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_AVATAR_CHANGE_INFO_2;
	memcpy(&mOriginal[1], &tSort, 4);
	memcpy(&mOriginal[5], &tValue, 4);
	mOriginalSize = S_AVATAR_CHANGE_INFO_2;
}
//B_PROCESS_DATA_RECV
void MyTransfer::B_PROCESS_DATA_RECV(int tResult, int tSort, BYTE tData[MAX_BROADCAST_DATA_SIZE])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_PROCESS_DATA_RECV;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &tSort, 4);
	memcpy(&mOriginal[9], &tData[0], MAX_BROADCAST_DATA_SIZE);
	mOriginalSize = S_PROCESS_DATA_RECV;
}
//B_DEMAND_ZONE_SERVER_INFO_2_RESULT
void MyTransfer::B_DEMAND_ZONE_SERVER_INFO_2_RESULT(int tResult, char tIp[16], int tPort)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_DEMAND_ZONE_SERVER_INFO_2_RESULT;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &tIp[0], 16);
	memcpy(&mOriginal[21], &tPort, 4);
	mOriginalSize = S_DEMAND_ZONE_SERVER_INFO_2_RESULT;
}
//B_USE_HOTKEY_ITEM_RECV
void MyTransfer::B_USE_HOTKEY_ITEM_RECV(int tResult, int tPage, int tIndex)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_USE_HOTKEY_ITEM_RECV;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &tPage, 4);
	memcpy(&mOriginal[9], &tIndex, 4);
	mOriginalSize = S_USE_HOTKEY_ITEM_RECV;
}
//B_USE_INVENTORY_ITEM_RECV
void MyTransfer::B_USE_INVENTORY_ITEM_RECV(int tResult, int tPage, int tIndex, int tValue)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_USE_INVENTORY_ITEM_RECV;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &tPage, 4);
	memcpy(&mOriginal[9], &tIndex, 4);
	memcpy(&mOriginal[13], &tValue, 4);
	mOriginalSize = S_USE_INVENTORY_ITEM_RECV;
}
//B_IMPROVE_ITEM_RECV
void MyTransfer::B_IMPROVE_ITEM_RECV(int tResult, int tCost, int iValue)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_IMPROVE_ITEM_RECV;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &tCost, 4);
	memcpy(&mOriginal[9], &iValue, 4);
	mOriginalSize = S_IMPROVE_ITEM_RECV;
}
//B_ADD_ITEM_RECV
void MyTransfer::B_ADD_ITEM_RECV(int tResult, int tCost)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_ADD_ITEM_RECV;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &tCost, 4);
	mOriginalSize = S_ADD_ITEM_RECV;
}
//B_EXCHANGE_ITEM_RECV
void MyTransfer::B_EXCHANGE_ITEM_RECV(int tResult, int tCost, int tValue[6])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_EXCHANGE_ITEM_RECV;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &tCost, 4);
	memcpy(&mOriginal[9], &tValue[0], 24);
	mOriginalSize = S_EXCHANGE_ITEM_RECV;
}
//B_HIGH_ITEM_RECV
void MyTransfer::B_HIGH_ITEM_RECV(int tResult, int tCost, int tValue[6])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_HIGH_ITEM_RECV;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &tCost, 4);
	memcpy(&mOriginal[9], &tValue[0], 24);
	mOriginalSize = S_HIGH_ITEM_RECV;
}
//B_LOW_ITEM_RECV
void MyTransfer::B_LOW_ITEM_RECV(int tResult, int tCost, int tValue[6])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_LOW_ITEM_RECV;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &tCost, 4);
	memcpy(&mOriginal[9], &tValue[0], 24);
	mOriginalSize = S_LOW_ITEM_RECV;
}
//B_MAKE_ITEM_RECV
void MyTransfer::B_MAKE_ITEM_RECV(int tResult, int tValue[6])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_MAKE_ITEM_RECV;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &tValue[0], 24);
	mOriginalSize = S_MAKE_ITEM_RECV;
}
//B_TAILORUPGRADE
void MyTransfer::B_TAILORUPGRADE(int tResult, int tSort, int killothertribe, int tValue[6])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TAILORUPGRADE;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[9], &tSort, 4);
	memcpy(&mOriginal[13], &killothertribe, 4);
	memcpy(&mOriginal[17], &tValue[0], 24);
	mOriginalSize = S_TAILORUPGRADE;
}
//B_MAKE_SKILL_RECV
void MyTransfer::B_MAKE_SKILL_RECV(int tResult, int tValue[6])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_MAKE_SKILL_RECV;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &tValue[0], 24);
	mOriginalSize = S_MAKE_SKILL_RECV;
}
//B_START_PSHOP_RECV
void MyTransfer::B_START_PSHOP_RECV(int tResult, PSHOP_INFO* tPShopInfo)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_START_PSHOP_RECV;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], tPShopInfo, sizeof(PSHOP_INFO));
	mOriginalSize = S_START_PSHOP_RECV;
}
//B_END_PSHOP_RECV
void MyTransfer::B_END_PSHOP_RECV(int tResult)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_END_PSHOP_RECV;
	memcpy(&mOriginal[1], &tResult, 4);
	mOriginalSize = S_END_PSHOP_RECV;
}
//B_DEMAND_PSHOP_RECV
void MyTransfer::B_DEMAND_PSHOP_RECV(int tResult, PSHOP_INFO* tPShopInfo)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_DEMAND_PSHOP_RECV;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], tPShopInfo, sizeof(PSHOP_INFO));
	mOriginalSize = S_DEMAND_PSHOP_RECV;
}
//B_PSHOP_ITEM_INFO_RECV
void MyTransfer::B_PSHOP_ITEM_INFO_RECV(int tUniqueNumber, char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tPage, int tIndex, int tPShopItemInfo[9], int tPShopSocketInfo[3], int Unk)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_PSHOP_ITEM_INFO_RECV;
	memcpy(&mOriginal[1], &tUniqueNumber, 4);
	memcpy(&mOriginal[5], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	memcpy(&mOriginal[(5 + MAX_AVATAR_NAME_LENGTH)], &tPage, 4);
	memcpy(&mOriginal[(9 + MAX_AVATAR_NAME_LENGTH)], &tIndex, 4);
	memcpy(&mOriginal[(13 + MAX_AVATAR_NAME_LENGTH)], &tPShopItemInfo[0], 36);
	memcpy(&mOriginal[(49 + MAX_AVATAR_NAME_LENGTH)], &tPShopSocketInfo[0], 12);
	memcpy(&mOriginal[(61 + MAX_AVATAR_NAME_LENGTH)], &Unk, 4);
	mOriginalSize = S_PSHOP_ITEM_INFO_RECV;
}
//B_BUY_PSHOP_RECV
void MyTransfer::B_BUY_PSHOP_RECV(int tResult, int tCost, int tPage, int tIndex, int tValue[6], int tSocketValue[3])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_BUY_PSHOP_RECV;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &tCost, 4);
	memcpy(&mOriginal[9], &tPage, 4);
	memcpy(&mOriginal[13], &tIndex, 4);
	memcpy(&mOriginal[17], &tValue[0], 24);
	memcpy(&mOriginal[41], &tSocketValue[0], 12);
	mOriginalSize = S_BUY_PSHOP_RECV;
}
//B_PROCESS_QUEST_RECV
void MyTransfer::B_PROCESS_QUEST_RECV(int tResult, int tSort, int tPage, int tIndex, int  tXPost, int tYPost)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	//Tresult Kullanýlmýyor
	mOriginal[0] = P_PROCESS_QUEST_RECV;
	memcpy(&mOriginal[1], &tSort, 4);
	memcpy(&mOriginal[5], &tPage, 4);
	memcpy(&mOriginal[9], &tIndex, 4);
	memcpy(&mOriginal[13], &tXPost, 4);
	memcpy(&mOriginal[17], &tYPost, 4);
	mOriginalSize = S_PROCESS_QUEST_RECV;
}
//B_CHANGE_TO_TRIBE4_RECV
void MyTransfer::B_CHANGE_TO_TRIBE4_RECV(int tResult)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_CHANGE_TO_TRIBE4_RECV;
	memcpy(&mOriginal[1], &tResult, 4);
	mOriginalSize = S_CHANGE_TO_TRIBE4_RECV;
}
//B_GENERAL_CHAT_RECV
void MyTransfer::B_GENERAL_CHAT_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], BYTE tAuthType, char tContent[MAX_CHAT_CONTENT_LENGTH])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_GENERAL_CHAT_RECV;
	memcpy(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	memcpy(&mOriginal[(1 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
	mOriginalSize = S_GENERAL_CHAT_RECV;
}
//B_SECRET_CHAT_RECV
void MyTransfer::B_SECRET_CHAT_RECV(int tResult, int tZoneNumber, char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tContent[MAX_CHAT_CONTENT_LENGTH], int tAuthType, int type)
{

	if (type == 0) {
		memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal[0] = P_SECRET_CHAT_RECV;
		memcpy(&mOriginal[1], &tResult, 4);
		memcpy(&mOriginal[5], &tZoneNumber, 4);
		memcpy(&mOriginal[9], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		memcpy(&mOriginal[(9 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		memcpy(&mOriginal[(9 + MAX_AVATAR_NAME_LENGTH + MAX_CHAT_CONTENT_LENGTH)], &tAuthType, 4);
		mOriginalSize = S_SECRET_CHAT_RECV;
	}
	else if (type == 1) {
		memset(mOriginal_C, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal_C[0] = P_SECRET_CHAT_RECV;
		memcpy(&mOriginal_C[1], &tResult, 4);
		memcpy(&mOriginal_C[5], &tZoneNumber, 4);
		memcpy(&mOriginal_C[9], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		memcpy(&mOriginal_C[(9 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		memcpy(&mOriginal_C[(9 + MAX_AVATAR_NAME_LENGTH + MAX_CHAT_CONTENT_LENGTH)], &tAuthType, 4);
		mOriginalSize_C = S_SECRET_CHAT_RECV;
	}
	else if (type == 2) {
		memset(mOriginal_R, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal_R[0] = P_SECRET_CHAT_RECV;
		memcpy(&mOriginal_R[1], &tResult, 4);
		memcpy(&mOriginal_R[5], &tZoneNumber, 4);
		memcpy(&mOriginal_R[9], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		memcpy(&mOriginal_R[(9 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		memcpy(&mOriginal_R[(9 + MAX_AVATAR_NAME_LENGTH + MAX_CHAT_CONTENT_LENGTH)], &tAuthType, 4);
		mOriginalSize_R = S_SECRET_CHAT_RECV;
	}
}
//B_GENERAL_SHOUT_RECV
void MyTransfer::B_GENERAL_SHOUT_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], BYTE tAuthType, char tContent[MAX_CHAT_CONTENT_LENGTH])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_GENERAL_SHOUT_RECV;
	memcpy(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	memcpy(&mOriginal[(1 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
	mOriginalSize = S_GENERAL_SHOUT_RECV;
}
//B_GET_CASH_SIZE_RECV
void MyTransfer::B_GET_CASH_SIZE_RECV(int tCashSize, int tBonusCashSize)
{
	mOriginal[0] = P_GET_CASH_SIZE_RECV;
	tCashSize = 1;
	CopyMemory(&mOriginal[1], &tBonusCashSize, 4);
	CopyMemory(&mOriginal[5], &tCashSize, 4);

	mOriginalSize = S_GET_CASH_SIZE_RECV;
}
//B_BUY_CASH_ITEM_RECV
void MyTransfer::B_BUY_CASH_ITEM_RECV(int tResult, int tCashSize, int tBonusCashSize, int tPage, int tIndex, int tValue[6])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_BUY_CASH_ITEM_RECV;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &tBonusCashSize, 4);
	memcpy(&mOriginal[9], &tPage, 4);
	memcpy(&mOriginal[13], &tIndex, 4);
	memcpy(&mOriginal[17], &tValue[0], 24);
	mOriginalSize = S_BUY_CASH_ITEM_RECV;
}
//B_DUEL_ASK_RECV
void MyTransfer::B_DUEL_ASK_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tSort)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_DUEL_ASK_RECV;
	memcpy(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	memcpy(&mOriginal[(1 + MAX_AVATAR_NAME_LENGTH)], &tSort, 4);
	mOriginalSize = S_DUEL_ASK_RECV;
}
//B_DUEL_CANCEL_RECV
void MyTransfer::B_DUEL_CANCEL_RECV(void)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_DUEL_CANCEL_RECV;
	mOriginalSize = S_DUEL_CANCEL_RECV;
}
//B_DUEL_ANSWER_RECV
void MyTransfer::B_DUEL_ANSWER_RECV(int tAnswer)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_DUEL_ANSWER_RECV;
	memcpy(&mOriginal[1], &tAnswer, 4);
	mOriginalSize = S_DUEL_ANSWER_RECV;
}
//B_DUEL_START_RECV
void MyTransfer::B_DUEL_START_RECV(int tDuelState[3], int tRemainTime, int DuelSort)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_DUEL_START_RECV;
	memcpy(&mOriginal[1], &tDuelState[0], 12);
	memcpy(&mOriginal[13], &tRemainTime, 4);
	memcpy(&mOriginal[17], &DuelSort, 4);
	mOriginalSize = S_DUEL_START_RECV;
}
//B_DUEL_TIME_INFO
void MyTransfer::B_DUEL_TIME_INFO(int tRemainTime)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_DUEL_TIME_INFO;
	memcpy(&mOriginal[1], &tRemainTime, 4);
	mOriginalSize = S_DUEL_TIME_INFO;
}
//B_DUEL_END_RECV
void MyTransfer::B_DUEL_END_RECV(int tResult)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_DUEL_END_RECV;
	memcpy(&mOriginal[1], &tResult, 4);
	mOriginalSize = S_DUEL_END_RECV;
}
//B_TRADE_ASK_RECV
void MyTransfer::B_TRADE_ASK_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tLevel)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TRADE_ASK_RECV;
	memcpy(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	memcpy(&mOriginal[(1 + MAX_AVATAR_NAME_LENGTH)], &tLevel, 4);
	mOriginalSize = S_TRADE_ASK_RECV;
}
//B_TRADE_CANCEL_RECV
void MyTransfer::B_TRADE_CANCEL_RECV(void)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TRADE_CANCEL_RECV;
	mOriginalSize = S_TRADE_CANCEL_RECV;
}
//B_TRADE_ANSWER_RECV
void MyTransfer::B_TRADE_ANSWER_RECV(int tAnswer)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TRADE_ANSWER_RECV;
	memcpy(&mOriginal[1], &tAnswer, 4);
	mOriginalSize = S_TRADE_ANSWER_RECV;
}
//B_TRADE_START_RECV
void MyTransfer::B_TRADE_START_RECV(int tTradeMoney, int tTrade[MAX_TRADE_SLOT_NUM][4], int tradeSocket[MAX_TRADE_SLOT_NUM][3], int TradeBar)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TRADE_START_RECV;
	memcpy(&mOriginal[1], &tTradeMoney, 4);
	memcpy(&mOriginal[5], tTrade, (MAX_TRADE_SLOT_NUM * 16));
	memcpy(&mOriginal[5 + (MAX_TRADE_SLOT_NUM * 16)], tradeSocket, MAX_TRADE_SLOT_NUM * 12);
	memcpy(&mOriginal[5 + (MAX_TRADE_SLOT_NUM * 16) + (MAX_TRADE_SLOT_NUM * 12)], &TradeBar, 4);
	mOriginalSize = S_TRADE_START_RECV;
}
//B_TRADE_STATE_RECV
void MyTransfer::B_TRADE_STATE_RECV(int tTradeMoney, int tTrade[MAX_TRADE_SLOT_NUM][4], int tradeSocket[MAX_TRADE_SLOT_NUM][3], int TradeBar)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TRADE_STATE_RECV;
	memcpy(&mOriginal[1], &tTradeMoney, 4);
	memcpy(&mOriginal[5], tTrade, (MAX_TRADE_SLOT_NUM * 16));
	memcpy(&mOriginal[5 + (MAX_TRADE_SLOT_NUM * 16)], tradeSocket, MAX_TRADE_SLOT_NUM * 12);
	memcpy(&mOriginal[5 + (MAX_TRADE_SLOT_NUM * 16) + (MAX_TRADE_SLOT_NUM * 12)], &TradeBar, 4);
	mOriginalSize = S_TRADE_STATE_RECV;
}
//B_TRADE_MENU_RECV
void MyTransfer::B_TRADE_MENU_RECV(int tCheckMe)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TRADE_MENU_RECV;
	memcpy(&mOriginal[1], &tCheckMe, 4);
	mOriginalSize = S_TRADE_MENU_RECV;
}
//B_TRADE_END_RECV
void MyTransfer::B_TRADE_END_RECV(int tResult)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TRADE_END_RECV;
	memcpy(&mOriginal[1], &tResult, 4);
	mOriginalSize = S_TRADE_END_RECV;
}
//B_FRIEND_ASK_RECV
void MyTransfer::B_FRIEND_ASK_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_FRIEND_ASK_RECV;
	memcpy(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	mOriginalSize = S_FRIEND_ASK_RECV;
}
//B_FRIEND_CANCEL_RECV
void MyTransfer::B_FRIEND_CANCEL_RECV(void)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_FRIEND_CANCEL_RECV;
	mOriginalSize = S_FRIEND_CANCEL_RECV;
}
//B_FRIEND_ANSWER_RECV
void MyTransfer::B_FRIEND_ANSWER_RECV(int tAnswer)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_FRIEND_ANSWER_RECV;
	memcpy(&mOriginal[1], &tAnswer, 4);
	mOriginalSize = S_FRIEND_ANSWER_RECV;
}
//B_FRIEND_MAKE_RECV
void MyTransfer::B_FRIEND_MAKE_RECV(int tIndex, char tAvatarName[MAX_AVATAR_NAME_LENGTH])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_FRIEND_MAKE_RECV;
	memcpy(&mOriginal[1], &tIndex, 4);
	memcpy(&mOriginal[5], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	mOriginalSize = S_FRIEND_MAKE_RECV;
}
//B_FRIEND_FIND_RECV
void MyTransfer::B_FRIEND_FIND_RECV(int tIndex, int tZoneNumber)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_FRIEND_FIND_RECV;
	memcpy(&mOriginal[1], &tIndex, 4);
	memcpy(&mOriginal[5], &tZoneNumber, 4);
	mOriginalSize = S_FRIEND_FIND_RECV;
}
//B_FRIEND_DELETE_RECV
void MyTransfer::B_FRIEND_DELETE_RECV(int tIndex)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_FRIEND_DELETE_RECV;
	memcpy(&mOriginal[1], &tIndex, 4);
	mOriginalSize = S_FRIEND_DELETE_RECV;
}
//B_TEACHER_ASK_RECV
void MyTransfer::B_TEACHER_ASK_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TEACHER_ASK_RECV;
	memcpy(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	mOriginalSize = S_TEACHER_ASK_RECV;
}
//B_TEACHER_CANCEL_RECV
void MyTransfer::B_TEACHER_CANCEL_RECV(void)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TEACHER_CANCEL_RECV;
	mOriginalSize = S_TEACHER_CANCEL_RECV;
}
//B_TEACHER_ANSWER_RECV
void MyTransfer::B_TEACHER_ANSWER_RECV(int tAnswer)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TEACHER_ANSWER_RECV;
	memcpy(&mOriginal[1], &tAnswer, 4);
	mOriginalSize = S_TEACHER_ANSWER_RECV;
}
//B_TEACHER_START_RECV
void MyTransfer::B_TEACHER_START_RECV(int tSort, char tAvatarName[MAX_AVATAR_NAME_LENGTH])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TEACHER_START_RECV;
	memcpy(&mOriginal[1], &tSort, 4);
	memcpy(&mOriginal[5], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	mOriginalSize = S_TEACHER_START_RECV;
}
//B_TEACHER_END_RECV
void MyTransfer::B_TEACHER_END_RECV(void)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TEACHER_END_RECV;
	mOriginalSize = S_TEACHER_END_RECV;
}
//B_TEACHER_STATE_RECV
void MyTransfer::B_TEACHER_STATE_RECV(int tResult)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TEACHER_STATE_RECV;
	memcpy(&mOriginal[1], &tResult, 4);
	mOriginalSize = S_TEACHER_STATE_RECV;
}
//B_PARTY_ASK_RECV
void MyTransfer::B_PARTY_ASK_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_PARTY_ASK_RECV;
	memcpy(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	mOriginalSize = S_PARTY_ASK_RECV;
}
//B_PARTY_CANCEL_RECV
void MyTransfer::B_PARTY_CANCEL_RECV(void)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_PARTY_CANCEL_RECV;
	mOriginalSize = S_PARTY_CANCEL_RECV;
}
//B_PARTY_ANSWER_RECV
void MyTransfer::B_PARTY_ANSWER_RECV(int tAnswer)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_PARTY_ANSWER_RECV;
	memcpy(&mOriginal[1], &tAnswer, 4);
	mOriginalSize = S_PARTY_ANSWER_RECV;
}
//B_PARTY_MAKE_RECV
void MyTransfer::B_PARTY_MAKE_RECV(int tAnswer, char tAvatarName[5][MAX_AVATAR_NAME_LENGTH])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_PARTY_MAKE_RECV;
	memcpy(&mOriginal[1], &tAnswer, 4);
	memcpy(&mOriginal[5], &tAvatarName[0][0], MAX_AVATAR_NAME_LENGTH);
	memcpy(&mOriginal[5 + MAX_AVATAR_NAME_LENGTH], &tAvatarName[1][0], MAX_AVATAR_NAME_LENGTH);
	memcpy(&mOriginal[5 + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH], &tAvatarName[2][0], MAX_AVATAR_NAME_LENGTH);
	memcpy(&mOriginal[5 + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH], &tAvatarName[3][0], MAX_AVATAR_NAME_LENGTH);
	memcpy(&mOriginal[5 + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH], &tAvatarName[4][0], MAX_AVATAR_NAME_LENGTH);
	mOriginalSize = S_PARTY_MAKE_RECV;
}
//B_PARTY_JOIN_RECV
void MyTransfer::B_PARTY_JOIN_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], int type)
{
	if (type == 0) {
		memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal[0] = P_PARTY_JOIN_RECV;
		memcpy(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize = S_PARTY_JOIN_RECV;
	}
	else if (type == 1) {
		memset(mOriginal_C, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal_C[0] = P_PARTY_JOIN_RECV;
		memcpy(&mOriginal_C[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize_C = S_PARTY_JOIN_RECV;
	}
	else if (type == 2) {
		memset(mOriginal_R, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal_R[0] = P_PARTY_JOIN_RECV;
		memcpy(&mOriginal_R[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize_R = S_PARTY_JOIN_RECV;
	}
}
//B_PARTY_CHAT_RECV
void MyTransfer::B_PARTY_CHAT_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tContent[MAX_CHAT_CONTENT_LENGTH], int type)
{
	if (type == 0) {
		memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal[0] = P_PARTY_CHAT_RECV;
		memcpy(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		memcpy(&mOriginal[(1 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize = S_PARTY_CHAT_RECV;
	}
	else if (type == 1) {
		memset(mOriginal_C, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal_C[0] = P_PARTY_CHAT_RECV;
		memcpy(&mOriginal_C[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		memcpy(&mOriginal_C[(1 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize_C = S_PARTY_CHAT_RECV;
	}
	else if (type == 2) {
		memset(mOriginal_R, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal_R[0] = P_PARTY_CHAT_RECV;
		memcpy(&mOriginal_R[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		memcpy(&mOriginal_R[(1 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize_R = S_PARTY_CHAT_RECV;
	}
}
//B_PARTY_LEAVE_RECV
void MyTransfer::B_PARTY_LEAVE_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], int type)
{
	if (type == 0) {
		memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal[0] = P_PARTY_LEAVE_RECV;
		memcpy(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize = S_PARTY_LEAVE_RECV;
	}
	else if (type == 1) {
		memset(mOriginal_C, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal_C[0] = P_PARTY_LEAVE_RECV;
		memcpy(&mOriginal_C[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize_C = S_PARTY_LEAVE_RECV;
	}
	else if (type == 2) {
		memset(mOriginal_R, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal_R[0] = P_PARTY_LEAVE_RECV;
		memcpy(&mOriginal_R[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize_R = S_PARTY_LEAVE_RECV;
	}
}
//B_PARTY_EXILE_RECV
void MyTransfer::B_PARTY_EXILE_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], int type)
{
	if (type == 0) {
		memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal[0] = P_PARTY_EXILE_RECV;
		memcpy(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize = S_PARTY_EXILE_RECV;
	}
	else if (type == 1) {
		memset(mOriginal_C, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal_C[0] = P_PARTY_EXILE_RECV;
		memcpy(&mOriginal_C[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize_C = S_PARTY_EXILE_RECV;
	}
	else if (type == 2) {
		memset(mOriginal_R, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal_R[0] = P_PARTY_EXILE_RECV;
		memcpy(&mOriginal_R[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize_R = S_PARTY_EXILE_RECV;
	}
}
//B_PARTY_BREAK_RECV
void MyTransfer::B_PARTY_BREAK_RECV(int state, char tAvatarName[MAX_AVATAR_NAME_LENGTH], int type)
{
	if (type == 0) {
		memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal[0] = P_PARTY_BREAK_RECV;
		memcpy(&mOriginal[1], &state, 4);
		memcpy(&mOriginal[5], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize = S_PARTY_BREAK_RECV;
	}
	else if (type == 1) {
		memset(mOriginal_C, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal_C[0] = P_PARTY_BREAK_RECV;
		memcpy(&mOriginal_C[1], &state, 4);
		memcpy(&mOriginal_C[5], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize_C = S_PARTY_BREAK_RECV;
	}
	else if (type == 2) {
		memset(mOriginal_R, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal_R[0] = P_PARTY_BREAK_RECV;
		memcpy(&mOriginal_R[1], &state, 4);
		memcpy(&mOriginal_R[5], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize_R = S_PARTY_BREAK_RECV;
	}
}
//B_GUILD_ASK_RECV
void MyTransfer::B_GUILD_ASK_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_GUILD_ASK_RECV;
	memcpy(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	mOriginalSize = S_GUILD_ASK_RECV;
}
//B_GUILD_CANCEL_RECV
void MyTransfer::B_GUILD_CANCEL_RECV(void)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_GUILD_CANCEL_RECV;
	mOriginalSize = S_GUILD_CANCEL_RECV;
}
//B_GUILD_ANSWER_RECV
void MyTransfer::B_GUILD_ANSWER_RECV(int tAnswer)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_GUILD_ANSWER_RECV;
	memcpy(&mOriginal[1], &tAnswer, 4);
	mOriginalSize = S_GUILD_ANSWER_RECV;
}
//B_GUILD_WORK_RECV
void MyTransfer::B_GUILD_WORK_RECV(int tResult, int tSort, GUILD_INFO* tGuildInfo)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_GUILD_WORK_RECV;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &tSort, 4);
	memcpy(&mOriginal[9], tGuildInfo, sizeof(GUILD_INFO));
	mOriginalSize = S_GUILD_WORK_RECV;
}
//B_GUILD_NOTICE_RECV
void MyTransfer::B_GUILD_NOTICE_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tContent[MAX_CHAT_CONTENT_LENGTH], int type)
{

	if (type == 0) {
		memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal[0] = P_GUILD_NOTICE_RECV;
		memcpy(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		memcpy(&mOriginal[(1 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize = S_GUILD_NOTICE_RECV;
	}
	else if (type == 1) {
		memset(mOriginal_C, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal_C[0] = P_GUILD_NOTICE_RECV;
		memcpy(&mOriginal_C[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		memcpy(&mOriginal_C[(1 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize_C = S_GUILD_NOTICE_RECV;
	}
	else if (type == 2) {
		memset(mOriginal_R, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal_R[0] = P_GUILD_NOTICE_RECV;
		memcpy(&mOriginal_R[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		memcpy(&mOriginal_R[(1 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize_R = S_GUILD_NOTICE_RECV;
	}
}
//B_GUILD_CHAT_RECV
void MyTransfer::B_GUILD_CHAT_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tContent[MAX_CHAT_CONTENT_LENGTH], int type)
{

	if (type == 0) {
		memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal[0] = P_GUILD_CHAT_RECV;
		memcpy(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		memcpy(&mOriginal[(1 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize = S_GUILD_CHAT_RECV;
	}
	else if (type == 1) {
		memset(mOriginal_C, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal_C[0] = P_GUILD_CHAT_RECV;
		memcpy(&mOriginal_C[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		memcpy(&mOriginal_C[(1 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize_C = S_GUILD_CHAT_RECV;
	}
	else if (type == 2) {
		memset(mOriginal_R, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal_R[0] = P_GUILD_CHAT_RECV;
		memcpy(&mOriginal_R[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		memcpy(&mOriginal_R[(1 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize_R = S_GUILD_CHAT_RECV;
	}
}
//B_GUILD_FIND_RECV
void MyTransfer::B_GUILD_FIND_RECV(int tResult)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_GUILD_FIND_RECV;
	memcpy(&mOriginal[1], &tResult, 4);
	mOriginalSize = S_GUILD_FIND_RECV;
}
//B_GUILD_LOGIN_INFO
void MyTransfer::B_GUILD_LOGIN_INFO(char tAvatarName[MAX_AVATAR_NAME_LENGTH], int type)
{
	if (type == 0) {
		memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal[0] = P_GUILD_LOGIN_INFO;
		memcpy(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize = S_GUILD_LOGIN_INFO;
	}
	else if (type == 1) {
		memset(mOriginal_C, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal_C[0] = P_GUILD_LOGIN_INFO;
		memcpy(&mOriginal_C[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize_C = S_GUILD_LOGIN_INFO;
	}
	else if (type == 2) {
		memset(mOriginal_R, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal_R[0] = P_GUILD_LOGIN_INFO;
		memcpy(&mOriginal_R[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize_R = S_GUILD_LOGIN_INFO;
	}
}
//B_TRIBE_WORK_RECV
void MyTransfer::B_TRIBE_WORK_RECV(int tResult, int tSort, BYTE tData[MAX_TRIBE_WORK_SIZE])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TRIBE_WORK_RECV;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &tSort, 4);
	memcpy(&mOriginal[9], &tData[0], MAX_TRIBE_WORK_SIZE);
	mOriginalSize = S_TRIBE_WORK_RECV;
}
//B_TRIBE_NOTICE_RECV
void MyTransfer::B_TRIBE_NOTICE_RECV(int tSort, char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tContent[MAX_CHAT_CONTENT_LENGTH], int type)
{
		memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
		mOriginal[0] = P_TRIBE_NOTICE_RECV;
		memcpy(&mOriginal[1], &tSort, 4);
		memcpy(&mOriginal[5], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		memcpy(&mOriginal[(5 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize = S_TRIBE_NOTICE_RECV;
}
//B_TRIBE_CHAT_RECV
void MyTransfer::B_TRIBE_CHAT_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], BYTE tAuthType, char tContent[MAX_CHAT_CONTENT_LENGTH])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TRIBE_CHAT_RECV;
	memcpy(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	memcpy(&mOriginal[(1 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
	mOriginalSize = S_TRIBE_CHAT_RECV;
}
void MyTransfer::B_TRIBE_CHAT_RECV2(char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tContent[MAX_CHAT_CONTENT_LENGTH])
{
	memset(mOriginal_C, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal_C[0] = P_TRIBE_CHAT_RECV;
	memcpy(&mOriginal_C[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	memcpy(&mOriginal_C[(1 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
	mOriginalSize_C = S_TRIBE_CHAT_RECV;
}
//B_TRIBE_BANK_RECV
void MyTransfer::B_TRIBE_BANK_RECV(int tResult, int tSort, int tTribeBankInfo[MAX_TRIBE_BANK_SLOT_NUM], int tMoney)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TRIBE_BANK_RECV;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &tSort, 4);
	memcpy(&mOriginal[9], &tTribeBankInfo[0], (MAX_TRIBE_BANK_SLOT_NUM * 4));
	memcpy(&mOriginal[(9 + MAX_TRIBE_BANK_SLOT_NUM * 4)], &tMoney, 4);
	mOriginalSize = S_TRIBE_BANK_RECV;
}
//B_TRIBE_VOTE_RECV
void MyTransfer::B_TRIBE_VOTE_RECV(int tResult, int tSort, int tValue)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TRIBE_VOTE_RECV;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &tSort, 4);
	memcpy(&mOriginal[9], &tValue, 4);
	mOriginalSize = S_TRIBE_VOTE_RECV;
}
//B_TRIBE_ALLIANCE_INFO
void MyTransfer::B_TRIBE_ALLIANCE_INFO(int tSort, int tValue)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TRIBE_ALLIANCE_INFO;
	memcpy(&mOriginal[1], &tSort, 4);
	memcpy(&mOriginal[5], &tValue, 4);
	mOriginalSize = S_TRIBE_ALLIANCE_INFO;
}
//B_BROADCAST_INFO_RECV
void MyTransfer::B_BROADCAST_INFO_RECV(int tInfoSort, BYTE tInfoData[MAX_BROADCAST_INFO_SIZE])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_BROADCAST_INFO_RECV;
	memcpy(&mOriginal[1], &tInfoSort, 4);
	memcpy(&mOriginal[5], &tInfoData[0], MAX_BROADCAST_INFO_SIZE);
	mOriginalSize = S_BROADCAST_INFO_RECV;
}
void MyTransfer::B_BROADCAST_INFO_RECV2(int tInfoSort, BYTE tInfoData[MAX_BROADCAST_INFO_SIZE])
{
	memset(mOriginal_C, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal_C[0] = P_BROADCAST_INFO_RECV;
	memcpy(&mOriginal_C[1], &tInfoSort, 4);
	memcpy(&mOriginal_C[5], &tInfoData[0], MAX_BROADCAST_INFO_SIZE);
	mOriginalSize_C = S_BROADCAST_INFO_RECV;
}
//B_049_TYPE_BATTLE_INFO
void MyTransfer::B_049_TYPE_BATTLE_INFO(int tTribeUserNum[4], int tRemainTime)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_049_TYPE_BATTLE_INFO;
	memcpy(&mOriginal[1], &tTribeUserNum[0], 16);
	memcpy(&mOriginal[17], &tRemainTime, 4);
	mOriginalSize = S_049_TYPE_BATTLE_INFO;
}
//B_051_TYPE_BATTLE_INFO
void MyTransfer::B_051_TYPE_BATTLE_INFO(int tExistStone[4])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_051_TYPE_BATTLE_INFO;
	memcpy(&mOriginal[1], &tExistStone[0], 16);
	mOriginalSize = S_051_TYPE_BATTLE_INFO;
}
//B_053_TYPE_BATTLE_INFO
void MyTransfer::B_053_TYPE_BATTLE_INFO(int tRemainTime)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_053_TYPE_BATTLE_INFO;
	memcpy(&mOriginal[1], &tRemainTime, 4);
	mOriginalSize = S_053_TYPE_BATTLE_INFO;
}
//B_GM_COMMAND_INFO
void MyTransfer::B_GM_COMMAND_INFO(int tSort, BYTE tData[MAX_TRIBE_WORK_SIZE])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_GM_COMMAND_INFO;
	memcpy(&mOriginal[1], &tSort, 4);
	memcpy(&mOriginal[5], &tData[0], MAX_TRIBE_WORK_SIZE);
	mOriginalSize = S_GM_COMMAND_INFO;
}
void MyTransfer::B_GM_COMMAND_INFO2(int tSort, BYTE tData[MAX_TRIBE_WORK_SIZE])
{
	memset(mOriginal_C, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal_C[0] = P_GM_COMMAND_INFO;
	memcpy(&mOriginal_C[1], &tSort, 4);
	memcpy(&mOriginal_C[5], &tData[0], MAX_TRIBE_WORK_SIZE);
	mOriginalSize_C = S_GM_COMMAND_INFO;
}
//B_RETURN_TO_AUTO_ZONE
void MyTransfer::B_RETURN_TO_AUTO_ZONE(void)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_RETURN_TO_AUTO_ZONE;
	mOriginalSize = S_RETURN_TO_AUTO_ZONE;
}
//B_194_BATTLE_INFO
void MyTransfer::B_194_BATTLE_INFO(int tTribeUserNum[4])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_194_BATTLE_INFO;
	memcpy(&mOriginal[1], &tTribeUserNum[0], 16);
	mOriginalSize = S_194_BATTLE_INFO;
}
//B_194_BATTLE_COUNTDOWN
void MyTransfer::B_194_BATTLE_COUNTDOWN(int tTime)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_194_BATTLE_COUNTDOWN;
	memcpy(&mOriginal[1], &tTime, 4);
	mOriginalSize = S_194_BATTLE_COUNTDOWN;
}
//B_267_TYPE_BATTLE_INFO
void MyTransfer::B_267_TYPE_BATTLE_INFO(int tTribeUserNum[4], int tRemainTime)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_267_TYPE_BATTLE_INFO;
	memcpy(&mOriginal[1], &tTribeUserNum[0], 16);
	memcpy(&mOriginal[17], &tRemainTime, 4);
	mOriginalSize = S_267_TYPE_BATTLE_INFO;
}
void MyTransfer::B_ANIMAL_STATE_RECV(int tValue01, int tValue02)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_ANIMAL_STATE_RECV;
	memcpy(&mOriginal[1], &tValue01, 4);
	memcpy(&mOriginal[5], &tValue02, 4);
	mOriginalSize = S_ANIMAL_STATE_RECV;
}
//B_GET_CASH_ITEM_INFO_RECV
void MyTransfer::B_GET_CASH_ITEM_INFO_RECV(int tResult, int tVersion, const int tCashItemInfo[4][14][10][4])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_GET_CASH_ITEM_INFO_RECV;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &tVersion, 4);
	memcpy(&mOriginal[9], tCashItemInfo, MAX_CASH_ITEM_INFO_SIZE);
	mOriginalSize = S_GET_CASH_ITEM_INFO_RECV;
}
//B_UPDATE_CASH_ITEM_INFO
void MyTransfer::B_UPDATE_CASH_ITEM_INFO()
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_UPDATE_CASH_ITEM_INFO;
	mOriginalSize = S_UPDATE_CASH_ITEM_INFO;
}
//B_COSTUME
void MyTransfer::B_COSTUME(int unk1, int unk2, int unk3, int unk4, int unk5, int unk6, int unk7)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_COSTUME_RECV;
	::memcpy(&mOriginal[1], &unk1, 4);
	::memcpy(&mOriginal[5], &unk2, 4);
	::memcpy(&mOriginal[9], &unk3, 4);
	::memcpy(&mOriginal[13], &unk4, 4);
	::memcpy(&mOriginal[17], &unk5, 4);
	::memcpy(&mOriginal[21], &unk6, 4);
	::memcpy(&mOriginal[25], &unk7, 4);
	mOriginalSize = S_COSTUME_RECV;
}
//B_CRAFT_ITEM_RECV
void MyTransfer::B_CRAFT_ITEM_RECV(int tResult, int tCost, int iValue)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_CRAFT_ITEM_RECV;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &tCost, 4);
	memcpy(&mOriginal[9], &iValue, 4);
	mOriginalSize = S_CRAFT_ITEM_RECV;
}
//B_AUTOBUFF
void MyTransfer::B_AUTOBUFF(int tResult)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_AutoBuff1;
	memcpy(&mOriginal[1], &tResult, 4);
	mOriginalSize = S_AutoBuff1;
}
//B_AUTOBUFF1
void MyTransfer::B_AUTOBUFF1(int tResult)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_AutoBuff2;
	memcpy(&mOriginal[1], &tResult, 4);
	mOriginalSize = S_AutoBuff2;
}
//B_GENERAL_CHAT_RECV
void MyTransfer::B_FUNCITON_NOTICE(int Tribe, char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tContent[MAX_CHAT_CONTENT_LENGTH])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_FUNCITON_NOTICE_RECV;
	memcpy(&mOriginal[1], &Tribe, 4);
	memcpy(&mOriginal[5], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	memcpy(&mOriginal[(5 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
	mOriginalSize = S_FUNCITON_NOTICE_RECV;
}
//B_GERISAYIM
void MyTransfer::B_GERISAYIM(int tResult)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_053_TYPE_BATTLE_INFO;
	memcpy(&mOriginal[1], &tResult, 4);
	mOriginalSize = S_053_TYPE_BATTLE_INFO;
}
//B_DAILY_MISSION
void MyTransfer::B_DAILY_MISSION(int tSort, int tResult, int JoinWar, int PlayerKill, int MonsterKill, int PlayTimeDay)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_DAILY_MISSION_SEND;
	memcpy(&mOriginal[1], &tSort, 4);
	memcpy(&mOriginal[5], &tResult, 4);
	memcpy(&mOriginal[9], &JoinWar, 4);
	memcpy(&mOriginal[13], &PlayerKill, 4);
	memcpy(&mOriginal[17], &MonsterKill, 4);
	memcpy(&mOriginal[21], &PlayTimeDay, 4);
	mOriginalSize = S_DAILY_MISSION_SEND;
}
//B_AUTOHUNT
void MyTransfer::B_AUTOHUNT(int tResult, int unk1, int unk2)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_AUTOHUNTSEND;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &unk1, 4);
	memcpy(&mOriginal[9], &unk2, 4);
	mOriginalSize = S_AUTOHUNTSEND;
}
//B_SOCKET
void MyTransfer::B_SOCKET(int tResult, int tSort, int Socket0, int Socket1, int Socket2)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_Socket;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &tSort, 4);
	memcpy(&mOriginal[9], &Socket0, 4);
	memcpy(&mOriginal[13], &Socket1, 4);
	memcpy(&mOriginal[17], &Socket2, 4);
	mOriginalSize = S_Socket;
}
//B_ADDSOCKET
void MyTransfer::B_ADDSOCKET(int tSort, int Socket0, int Socket1, int Socket2)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_ADDSOCKET;
	memcpy(&mOriginal[1], &tSort, 4);
	memcpy(&mOriginal[5], &Socket0, 4);
	memcpy(&mOriginal[9], &Socket1, 4);
	memcpy(&mOriginal[13], &Socket2, 4);
	mOriginalSize = S_ADDSOCKET;
}
//B_CPTOWER
void MyTransfer::B_CPTOWER(CP_TOWERS* tCpTower)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_CPTOWERZONE;
	memcpy(&mOriginal[1], tCpTower, sizeof(CP_TOWERS));
	mOriginalSize = S_CPTOWERZONE;
}
//B_CPTOWER2
void MyTransfer::B_CPTOWER2(CP_TOWERS* tCpTower)
{
	memset(mOriginal_C, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal_C[0] = P_CPTOWERZONE;
	memcpy(&mOriginal_C[1], tCpTower, sizeof(CP_TOWERS));
	mOriginalSize_C = S_CPTOWERZONE;
}
//B_TamirKule
void MyTransfer::B_TamirKule(char tAvatarName[MAX_AVATAR_NAME_LENGTH])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TamirKule;
	memcpy(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	mOriginalSize = S_TamirKule;
}
//B_KuleUpradge
void MyTransfer::B_KuleUpradge(int tResult, int tPage, int tPage1, int tIndex, int tIndex1, int tCount)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_UpradgeKule;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &tPage, 4);
	memcpy(&mOriginal[9], &tPage1, 4);
	memcpy(&mOriginal[13], &tIndex, 4);
	memcpy(&mOriginal[17], &tIndex1, 4);
	memcpy(&mOriginal[21], &tCount, 4);
	mOriginalSize = S_UpradgeKule;
}
//B_RANKINFO
void MyTransfer::B_RANKINFO(RANK_INFO* tRankInfo)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	int tResult = 0;
	mOriginal[0] = P_NEWRANKINFO;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], tRankInfo, sizeof(RANK_INFO));
	mOriginalSize = S_NEWRANKINFO;
}
//B_RANKINFO2
void MyTransfer::B_RANKINFO2(RANK_INFO* tRankInfo)
{
	memset(mOriginal_C, 0, MAX_TRANSFER_BUFFER_SIZE);
	int tResult = 0;
	mOriginal_C[0] = P_NEWRANKINFO;
	memcpy(&mOriginal_C[1], &tResult, 4);
	memcpy(&mOriginal_C[5], tRankInfo, sizeof(RANK_INFO));
	mOriginalSize_C = S_NEWRANKINFO;
}
//B_OLDRANKINFO
void MyTransfer::B_OLDRANKINFO(OLD_RANK_INFO* tOldRankInfo)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	int tResult = 0;
	mOriginal[0] = P_OLDRANKINFO;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], tOldRankInfo, sizeof(OLD_RANK_INFO));
	mOriginalSize = S_OLDRANKINFO;
}
//B_OLDRANKINFO2
void MyTransfer::B_OLDRANKINFO2(OLD_RANK_INFO* tOldRankInfo)
{
	memset(mOriginal_C, 0, MAX_TRANSFER_BUFFER_SIZE);
	int tResult = 0;
	mOriginal_C[0] = P_OLDRANKINFO;
	memcpy(&mOriginal_C[1], &tResult, 4);
	memcpy(&mOriginal_C[5], tOldRankInfo, sizeof(OLD_RANK_INFO));
	mOriginalSize_C = S_OLDRANKINFO;
}
//B_RANKPRIZE
void MyTransfer::B_RANKPRIZE(int tResult, int unk, int unk1, int unk2, int unk3, int unk4, int unk5[8])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_RANKPRIZE;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &unk, 4);
	memcpy(&mOriginal[9], &unk1, 4);
	memcpy(&mOriginal[13], &unk2, 4);
	memcpy(&mOriginal[17], &unk3, 4);
	memcpy(&mOriginal[21], &unk4, 4);
	memcpy(&mOriginal[25], unk5, 32);
	mOriginalSize = S_RANKPRIZE;
}
//B_HIDECOSTUME
void MyTransfer::B_HIDECOSTUME(int tResult, int unk1, int unk2)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_HIDECOSTUME;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &unk1, 4);
	memcpy(&mOriginal[9], &unk2, 4);
	mOriginalSize = S_HIDECOSTUME;
}
//B_KAPSUL
void MyTransfer::B_KAPSUL(int tResult, int iPage, int ItemSlot1, int ItemSlot2, int ItemIndex1, int ItemIndex2, int ItemSayýsý, int ItemFiyati, int ItemNumber[8])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_KAPSULSEND;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &iPage, 4);
	memcpy(&mOriginal[9], &ItemSlot1, 4);
	memcpy(&mOriginal[13], &ItemSlot2, 4);
	memcpy(&mOriginal[17], &ItemIndex1, 4);
	memcpy(&mOriginal[21], &ItemIndex2, 4);
	memcpy(&mOriginal[25], &ItemSayýsý, 4);
	memcpy(&mOriginal[29], &ItemFiyati, 4);
	memcpy(&mOriginal[33], ItemNumber, 32);
	mOriginalSize = S_KAPSULSEND;
}
//B_AVLANMABONUSU
void MyTransfer::B_AVLANMABONUSU(int tResult, int iPage, int ItemSlot1, int ItemSlot2, int ItemIndex1, int ItemIndex2, int ItemNumber[8], int ItemYuzdesi)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_AVLANMABONUSU;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &iPage, 4);
	memcpy(&mOriginal[9], &ItemSlot1, 4);
	memcpy(&mOriginal[13], &ItemSlot2, 4);
	memcpy(&mOriginal[17], &ItemIndex1, 4);
	memcpy(&mOriginal[21], &ItemIndex2, 4);
	memcpy(&mOriginal[25], ItemNumber, 32);
	memcpy(&mOriginal[57], &ItemYuzdesi, 4);
	mOriginalSize = S_AVLANMABONUSU;
}
//B_BOTTLE
void MyTransfer::B_BOTTLE(int tResult, int State1, int Index)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_BOTTLESEND;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &State1, 4);
	memcpy(&mOriginal[9], &Index, 4);
	mOriginalSize = S_BOTTLESEND;
}
//B_LEGANDARYIMPROVE
void MyTransfer::B_LEGANDARYIMPROVE(int tResult, int Cost, int Improve, int GuclendirmeSiniri)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_LEGANDARYIMP;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &Cost, 4);
	memcpy(&mOriginal[9], &Improve, 4);
	memcpy(&mOriginal[13], &GuclendirmeSiniri, 4);
	mOriginalSize = S_LEGANDARYIMP;
}

//B_200_BATTLE_INFO
void MyTransfer::B_200_BATTLE_INFO(int tTribeUserNum[4])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_CemberVadiMobInfo;
	memcpy(&mOriginal[1], &tTribeUserNum[0], 16);
	mOriginalSize = S_CemberVadiMobInfo;
}
//B_200_BATTLE_COUNTDOWN
void MyTransfer::B_200_BATTLE_COUNTDOWN(int tSort, int TimeSort, int Time)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_CemberVadiZamani;
	memcpy(&mOriginal[1], &tSort, 4);
	memcpy(&mOriginal[4], &TimeSort, 4);
	memcpy(&mOriginal[9], &Time, 4);
	mOriginalSize = S_CemberVadiZamani;
}
//B_ITEM_SEND
void MyTransfer::B_ITEM_SEND(int tResult, int tItemId, int tPage, int tIndex, int tIvenIndex)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_ITEMSEND;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &tItemId, 4);
	memcpy(&mOriginal[9], &tPage, 4);
	memcpy(&mOriginal[13], &tIndex, 4);
	memcpy(&mOriginal[17], &tIvenIndex, 4);
	mOriginalSize = S_ITEMSEND;
}

void MyTransfer::B_VALETSHOPUPDATE(int tServerIndex, DWORD tUniqueNumber, OBJECT_FOR_SHOP* tShop, int tCheckChangeActionState)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mSHOP_OBJECT[tServerIndex].mUpdateTimeForBroadcast = GetTickCount();
	mOriginal[0] = 134;
	memcpy(&mOriginal[1], &tServerIndex, 4);
	memcpy(&mOriginal[5], &tUniqueNumber, 4);
	memcpy(&mOriginal[9], tShop, sizeof(OBJECT_FOR_SHOP));
	memcpy(&mOriginal[9 + sizeof(OBJECT_FOR_SHOP)], &tCheckChangeActionState, 4);
	mOriginalSize = S_VALETSHOPUPDATE;
}
void MyTransfer::B_VALETSHOPUPDATE2(int tServerIndex, DWORD tUniqueNumber, OBJECT_FOR_SHOP* tShop, int tCheckChangeActionState)
{
	memset(mOriginal2, 0, MAX_TRANSFER_BUFFER_SIZE);
	mSHOP_OBJECT[tServerIndex].mUpdateTimeForBroadcast = GetTickCount();
	mOriginal2[0] = 134;
	memcpy(&mOriginal2[1], &tServerIndex, 4);
	memcpy(&mOriginal2[5], &tUniqueNumber, 4);
	memcpy(&mOriginal2[9], tShop, sizeof(OBJECT_FOR_SHOP));
	memcpy(&mOriginal2[9 + sizeof(OBJECT_FOR_SHOP)], &tCheckChangeActionState, 4);
	mOriginalSize2 = S_VALETSHOPUPDATE;
}

void MyTransfer::B_VALETSHOPSEND(int tSort, int tResult, VALETSHOP_INFO* tValetShopInfo)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_VALETSHOP;
	memcpy(&mOriginal[1], &tSort, 4);
	memcpy(&mOriginal[5], &tResult, 4);
	memcpy(&mOriginal[9], tValetShopInfo, sizeof(VALETSHOP_INFO));
	mOriginalSize = S_VALETSHOP;
}
void MyTransfer::B_VALETSHOPSEND1(int tResult, VALETSHOP_INFO* tValetShopInfo, int tPage, int tIndex, int tValue[9], int tCost)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_VALETSHOP1;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], tValetShopInfo, sizeof(VALETSHOP_INFO));
	memcpy(&mOriginal[5 + sizeof(VALETSHOP_INFO)], &tPage, 4);
	memcpy(&mOriginal[9 + sizeof(VALETSHOP_INFO)], &tIndex, 4);
	memcpy(&mOriginal[13 + sizeof(VALETSHOP_INFO)], &tValue[0], 36);
	memcpy(&mOriginal[49 + sizeof(VALETSHOP_INFO)], &tCost, 4);
	mOriginalSize = S_VALETSHOP1;
}
void MyTransfer::B_VALETSHOPGETMONEY(int tResult, int ValetMoney, int ValetBar)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_VALETGETMONEY;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &ValetMoney, 4);
	memcpy(&mOriginal[9], &ValetBar, 4);
	mOriginalSize = S_VALETGETMONEY;
}

void MyTransfer::B_FISHING(int tServerIndex, DWORD tUniqueNumber, int tResult, int tState, int unk)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_FISHINGSEND;
	memcpy(&mOriginal[1], &tServerIndex, 4);
	memcpy(&mOriginal[5], &tUniqueNumber, 4);
	memcpy(&mOriginal[9], &tResult, 4);
	memcpy(&mOriginal[13], &tState, 4);
	memcpy(&mOriginal[17], &unk, 4);
	mOriginalSize = S_FISHINGSEND;
}
void MyTransfer::B_FISHING2(int tServerIndex, DWORD tUniqueNumber, int tResult, int tState, int unk)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_FISHINGSEND2;
	memcpy(&mOriginal[1], &tServerIndex, 4);
	memcpy(&mOriginal[5], &tUniqueNumber, 4);
	memcpy(&mOriginal[9], &tResult, 4);
	memcpy(&mOriginal[13], &tState, 4);
	memcpy(&mOriginal[17], &unk, 4);
	mOriginalSize = S_FISHINGSEND2;
}
void MyTransfer::B_FISHINGITEMSEND(int tResult, int ItemId, int tPage, int tIndex, int tIvenSlot)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_FISHINGITEMSEND;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &ItemId, 4);
	memcpy(&mOriginal[9], &tPage, 4);
	memcpy(&mOriginal[13], &tIndex, 4);
	memcpy(&mOriginal[17], &tIvenSlot, 4);
	mOriginalSize = S_FISHINGITEMSEND;
}
void MyTransfer::B_BLOODMARKET(int tResult, int Market[50][3])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_BLOODMARKETSEND;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], Market, 600);
	mOriginalSize = S_BLOODMARKETSEND;
}
void MyTransfer::B_BLOODMARKETBUY(int tResult, int BloodCoin, int tPage, int tIndex, int tValue[6])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_BLOODMARKETBUYSEND;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &BloodCoin, 4);
	memcpy(&mOriginal[9], &tPage, 4);
	memcpy(&mOriginal[13], &tIndex, 4);
	memcpy(&mOriginal[17], &tValue[0], 24);
	mOriginalSize = S_BLOODMARKETBUYSEND;
}
//B_GEAR_BREAK_RECV
void MyTransfer::B_DESTROY_ITEM(int tResult, int tMoney, int tValue[6])
{
	//memset(mOriginal, 0, P_DESTROY_ITEM_SEND);
	mOriginal[0] = P_DESTROY_ITEM_SEND;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &tMoney, 4);
	memcpy(&mOriginal[9], &tValue[0], 24);
	mOriginalSize = S_DESTROY_ITEM_SEND;
}
//B_MAKE_ITEM_RECV
void MyTransfer::B_PET_COMBINE(int tResult, int tValue[6])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_PET_COMBINE_SEND;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &tValue[0], 24);
	mOriginalSize = S_PET_COMBINE_SEND;
}
//-------------------------------------------------------------------------------------------------
//B_HIGH_ITEM_RECV
void MyTransfer::B_CAPE_UPGRADE(int tResult,int tValue[6])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_Cape_Upgrade;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &tValue[0], 24);
	mOriginalSize = S_Cape_Upgrade;
}



//B_LEGANDARYIMPROVE
void MyTransfer::B_MUHURLEGEND(int tResult, int tCost, int tValue[6])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_MUHURLEGEND;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &tCost, 4);
	memcpy(&mOriginal[9], &tValue[0], 24);
	mOriginalSize = S_MUHURLEGEND;
}


void MyTransfer::B_ENGRAVERECV(int tResult, int tCost, int tKillOtherTribe, int tUnk3, int tImprove)
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_ENGRAVERECV;
	memcpy(&mOriginal[1], &tResult, 4);
	memcpy(&mOriginal[5], &tCost, 4);
	memcpy(&mOriginal[9], &tKillOtherTribe, 4);
	memcpy(&mOriginal[13], &tUnk3, 4);
	memcpy(&mOriginal[17], &tImprove, 4);
	mOriginalSize = S_ENGRAVERECV;
}

void MyTransfer::B_ITEM_UPGRADE_RECV(int tResult, int tCost, int tValue[6])
{
	memset(mOriginal, 0, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_ITEM_UPGRADE_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tCost, 4);
	CopyMemory(&mOriginal[9], &tValue[0], 24);
	mOriginalSize = S_ITEM_UPGRADE_RECV;
}