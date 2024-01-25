//-------------------------------------------------------------------------------------------------
//MY_TRANSFER_H
//-------------------------------------------------------------------------------------------------
#ifndef MY_TRANSFER_H
#define MY_TRANSFER_H
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_TRANSFER
//-------------------------------------------------------------------------------------------------
//MACRO
#define MAX_TRANSFER_BUFFER_SIZE									10000
//DEFINE
class MyTransfer
{

public:

	DWORD mOriginalSize;
	BYTE mOriginal[MAX_TRANSFER_BUFFER_SIZE];
	DWORD mOriginalSize2;
	BYTE mOriginal2[MAX_TRANSFER_BUFFER_SIZE];
	DWORD mOriginalSize_C;
	BYTE mOriginal_C[MAX_TRANSFER_BUFFER_SIZE];
	DWORD mOriginalSize_R;
	BYTE mOriginal_R[MAX_TRANSFER_BUFFER_SIZE];

	MyTransfer(void);

	BOOL Init(void);
	void Free(void);

	void B_CONNECT_OK(int tRandomNumber);
	void B_TEMP_REGISTER_RECV(int tResult);
	void B_REGISTER_AVATAR_RECV(AVATAR_INFO* tAvatarInfo, int tEffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2], int tPremiumServerExpirationDate); // ÇÔ¼ö ¼±¾ð ¼öÁ¤ - int tPremiumServerExpirationDate Ãß°¡. // @_Premium_Server_@
	void B_BROADCAST_WORLD_INFO(WORLD_INFO* tWorldInfo, TRIBE_INFO* tTribeInfo);
	void B_BROADCAST_WORLD_INFO2(WORLD_INFO* tWorldInfo, TRIBE_INFO* tTribeInfo);
	void B_AUTO_CHECK_ASK_SEND(int tDataSize, BYTE tData[1000]);
	void B_AVATAR_ACTION_RECV(int tServerIndex, DWORD tUniqueNumber, OBJECT_FOR_AVATAR* tAvatar, int tCheckChangeActionState);
	void B_AVATAR_ACTION_RECV2(int tServerIndex, DWORD tUniqueNumber, OBJECT_FOR_AVATAR* tAvatar, int tCheckChangeActionState);
	void B_AVATAR_EFFECT_VALUE_INFO(int tServerIndex, DWORD tUniqueNumber, int tEffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2], int tEffectValueState[MAX_AVATAR_EFFECT_SORT_NUM]);
	void B_AVATAR_CHANGE_INFO_1(int tServerIndex, DWORD tUniqueNumber, int tSort, int tValue01, int tValue02, int tValue03);
	void B_MONSTER_ACTION_RECV(int tServerIndex, DWORD tUniqueNumber, OBJECT_FOR_MONSTER* tMonster, int tCheckChangeActionState);
	void B_ITEM_ACTION_RECV(int tServerIndex, DWORD tUniqueNumber, OBJECT_FOR_ITEM* tItem, int tCheckChangeActionState);
	void B_ITEM_ACTION_RECV2(int tServerIndex, DWORD tUniqueNumber, OBJECT_FOR_ITEM* tItem, int tCheckChangeActionState);
	void B_GENERAL_NOTICE_RECV(char tContent[MAX_CHAT_CONTENT_LENGTH], int type = 0);
	void B_PROCESS_ATTACK_RECV(ATTACK_FOR_PROTOCOL* tAttackInfo);
	void B_AVATAR_CHANGE_INFO_2(int tSort, int tValue);
	void B_PROCESS_DATA_RECV(int tResult, int tSort, BYTE tData[MAX_BROADCAST_DATA_SIZE]);
	void B_DEMAND_ZONE_SERVER_INFO_2_RESULT(int tResult, char tIp[16], int tPort);
	void B_USE_HOTKEY_ITEM_RECV(int tResult, int tPage, int tIndex);
	void B_USE_INVENTORY_ITEM_RECV(int tResult, int tPage, int tIndex, int tValue);
	void B_IMPROVE_ITEM_RECV(int tResult, int tCost, int iValue);
	void B_CRAFT_ITEM_RECV(int tResult, int tCost, int iValue);
	void B_ADD_ITEM_RECV(int tResult, int tCost);
	void B_EXCHANGE_ITEM_RECV(int tResult, int tCost, int tValue[6]);
	void B_HIGH_ITEM_RECV(int tResult, int tCost, int tValue[6]);
	void B_LOW_ITEM_RECV(int tResult, int tCost, int tValue[6]);
	void B_MAKE_ITEM_RECV(int tResult, int tValue[6]);
	void B_TAILORUPGRADE(int tResult, int tSort, int killothertribe, int tValue[6]);
	void B_MAKE_SKILL_RECV(int tResult, int tValue[6]);
	void B_START_PSHOP_RECV(int tResult, PSHOP_INFO* tPShopInfo);
	void B_END_PSHOP_RECV(int tResult);
	void B_DEMAND_PSHOP_RECV(int tResult, PSHOP_INFO* tPShopInfo);
	void B_PSHOP_ITEM_INFO_RECV(int tUniqueNumber, char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tPage, int tIndex, int tPShopItemInfo[9], int tPShopSocketInfo[3], int Unk);
	void B_BUY_PSHOP_RECV(int tResult, int tCost, int tPage, int tIndex, int tValue[6], int tSocketValue[3]);
	void B_PROCESS_QUEST_RECV(int tResult, int tSort, int tPage, int tIndex, int  tXPost, int tYPost);
	void B_CHANGE_TO_TRIBE4_RECV(int tResult);
	void B_GENERAL_CHAT_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], BYTE tAuthType, char tContent[MAX_CHAT_CONTENT_LENGTH]);
	void B_SECRET_CHAT_RECV(int tResult, int tZoneNumber, char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tContent[MAX_CHAT_CONTENT_LENGTH], int tAuthType, int type = 0);
	void B_GENERAL_SHOUT_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], BYTE tAuthType, char tContent[MAX_CHAT_CONTENT_LENGTH]);
	void B_GET_CASH_SIZE_RECV(int tCashSize, int tBonusCashSize);
	void B_BUY_CASH_ITEM_RECV(int tResult, int tCashSize, int tBonusCashSize, int tPage, int tIndex, int tValue[6]);
	void B_DUEL_ASK_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tSort);
	void B_DUEL_CANCEL_RECV(void);
	void B_DUEL_ANSWER_RECV(int tAnswer);
	void B_DUEL_START_RECV(int tDuelState[3], int tRemainTime, int DuelSort);
	void B_DUEL_TIME_INFO(int tRemainTime);
	void B_DUEL_END_RECV(int tResult);
	void B_TRADE_ASK_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tLevel);
	void B_TRADE_CANCEL_RECV(void);
	void B_TRADE_ANSWER_RECV(int tAnswer);
	void B_TRADE_START_RECV(int tTradeMoney, int tTrade[MAX_TRADE_SLOT_NUM][4], int tradeSocket[MAX_TRADE_SLOT_NUM][3], int TradeBar);
	void B_TRADE_STATE_RECV(int tTradeMoney, int tTrade[MAX_TRADE_SLOT_NUM][4], int tradeSocket[MAX_TRADE_SLOT_NUM][3], int TradeBar);
	void B_TRADE_MENU_RECV(int tCheckMe);
	void B_TRADE_END_RECV(int tResult);
	void B_FRIEND_ASK_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH]);
	void B_FRIEND_CANCEL_RECV(void);
	void B_FRIEND_ANSWER_RECV(int tAnswer);
	void B_FRIEND_MAKE_RECV(int tIndex, char tAvatarName[MAX_AVATAR_NAME_LENGTH]);
	void B_FRIEND_FIND_RECV(int tIndex, int tZoneNumber);
	void B_FRIEND_DELETE_RECV(int tIndex);
	void B_TEACHER_ASK_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH]);
	void B_TEACHER_CANCEL_RECV(void);
	void B_TEACHER_ANSWER_RECV(int tAnswer);
	void B_TEACHER_START_RECV(int tSort, char tAvatarName[MAX_AVATAR_NAME_LENGTH]);
	void B_TEACHER_END_RECV(void);
	void B_TEACHER_STATE_RECV(int tResult);
	void B_PARTY_ASK_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH]);
	void B_PARTY_CANCEL_RECV(void);
	void B_PARTY_ANSWER_RECV(int tAnswer);
	void B_PARTY_MAKE_RECV(int tAnswer, char tAvatarName[5][MAX_AVATAR_NAME_LENGTH]);
	void B_PARTY_JOIN_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], int type = 0);
	void B_PARTY_CHAT_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tContent[MAX_CHAT_CONTENT_LENGTH], int type = 0);
	void B_PARTY_LEAVE_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], int type = 0);
	void B_PARTY_EXILE_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], int type = 0);
	void B_PARTY_BREAK_RECV(int state, char tAvatarName[MAX_AVATAR_NAME_LENGTH], int type = 0);
	void B_GUILD_ASK_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH]);
	void B_GUILD_CANCEL_RECV(void);
	void B_GUILD_ANSWER_RECV(int tAnswer);
	void B_GUILD_WORK_RECV(int tResult, int tSort, GUILD_INFO* tGuildInfo);
	void B_GUILD_NOTICE_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tContent[MAX_CHAT_CONTENT_LENGTH], int type = 0);
	void B_GUILD_CHAT_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tContent[MAX_CHAT_CONTENT_LENGTH], int type = 0);
	void B_GUILD_FIND_RECV(int tResult);
	void B_GUILD_LOGIN_INFO(char tAvatarName[MAX_AVATAR_NAME_LENGTH], int type = 0);
	void B_TRIBE_WORK_RECV(int tResult, int tSort, BYTE tData[MAX_TRIBE_WORK_SIZE]);
	void B_TRIBE_NOTICE_RECV(int tSort, char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tContent[MAX_CHAT_CONTENT_LENGTH], int type = 0);
	void B_TRIBE_CHAT_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], BYTE tAuthType, char tContent[MAX_CHAT_CONTENT_LENGTH]);
	void B_TRIBE_CHAT_RECV2(char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tContent[MAX_CHAT_CONTENT_LENGTH]);
	void B_TRIBE_BANK_RECV(int tResult, int tSort, int tTribeBankInfo[MAX_TRIBE_BANK_SLOT_NUM], int tMoney);
	void B_TRIBE_VOTE_RECV(int tResult, int tSort, int tValue);
	void B_TRIBE_ALLIANCE_INFO(int tSort, int tValue);
	void B_BROADCAST_INFO_RECV(int tInfoSort, BYTE tInfoData[MAX_BROADCAST_INFO_SIZE]);
	void B_BROADCAST_INFO_RECV2(int tInfoSort, BYTE tInfoData[MAX_BROADCAST_INFO_SIZE]);
	void B_049_TYPE_BATTLE_INFO(int tTribeUserNum[4], int tRemainTime);
	void B_051_TYPE_BATTLE_INFO(int tExistStone[4]);
	void B_053_TYPE_BATTLE_INFO(int tRemainTime);
	void B_194_BATTLE_INFO(int tTribeUserNum[4]);
	void B_194_BATTLE_COUNTDOWN(int tTime);
	void B_267_TYPE_BATTLE_INFO(int tTribeUserNum[4], int tRemainTime);
	void B_GM_COMMAND_INFO(int tSort, BYTE tData[MAX_TRIBE_WORK_SIZE]);
	void B_GM_COMMAND_INFO2(int tSort, BYTE tData[MAX_TRIBE_WORK_SIZE]);
	void B_RETURN_TO_AUTO_ZONE(void);
	void B_CHECK_AUTH_KEY(BYTE bResult);
	void B_UPDATE_AUTH_KEY(BYTE bResult);
	void B_ANIMAL_STATE_RECV(int tValue01, int tValue02);
	void B_COSTUME(int unk1, int unk2, int unk3, int unk4, int unk5, int unk6, int unk7);
	void B_AUTOBUFF(int tResult);
	void B_AUTOBUFF1(int tResult);
	void B_FUNCITON_NOTICE(int Tribe, char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tContent[MAX_CHAT_CONTENT_LENGTH]);
	void B_DAILY_MISSION(int tSort, int tResult, int JoinWar, int PlayerKill, int MonsterKill, int PlayTimeDay);
	void B_AUTOHUNT(int tResult, int unk1, int unk2);
	void B_SOCKET(int tResult, int tSort, int Socket0, int Socket1, int Socket2);
	void B_ADDSOCKET(int tSort, int Socket0, int Socket1, int Socket2);
	void B_TamirKule(char tAvatarName[MAX_AVATAR_NAME_LENGTH]);
	void B_KuleUpradge(int tResult, int tPage, int tPage1, int tIndex, int tIndex1, int tCount);
	void B_GERISAYIM(int tResult);
	void B_RANKPRIZE(int tResult, int unk, int unk1, int unk2, int unk3, int unk4, int unk5[8]);
	void B_HIDECOSTUME(int tResult, int unk1, int unk2);
	void B_KAPSUL(int tResult, int iPage, int ItemSlot1, int ItemSlot2, int ItemIndex1, int ItemIndex2, int ItemSayýsý, int ItemFiyati, int ItemNumber[8]);
	void B_BOTTLE(int tResult, int State1, int State2);
	void B_AVLANMABONUSU(int tResult, int iPage, int ItemSlot1, int ItemSlot2, int ItemIndex1, int ItemIndex2, int ItemNumber[8], int ItemYuzde);
	void B_LEGANDARYIMPROVE(int tResult, int Cost, int Improve, int GuclendirmeSiniri);
	void B_ITEM_SEND(int tResult, int tItemId, int tPage, int tIndex, int tIvenIndex);
	void B_GET_CASH_ITEM_INFO_RECV(int tResult, int tVersion, const int tCashItemInfo[4][14][10][4]);
	void B_UPDATE_CASH_ITEM_INFO();
	void B_CPTOWER(CP_TOWERS* tCpTower);
	void B_CPTOWER2(CP_TOWERS* tCpTower);
	void B_RANKINFO(RANK_INFO* tRankInfo);
	void B_RANKINFO2(RANK_INFO* tRankInfo);
	void B_OLDRANKINFO(OLD_RANK_INFO* tOldRankInfo);
	void B_OLDRANKINFO2(OLD_RANK_INFO* tOldRankInfo);
	void B_200_BATTLE_INFO(int tTribeUserNum[4]);
	void B_200_BATTLE_COUNTDOWN(int tSort, int TimeSort, int Time);

	void B_VALETSHOPUPDATE(int tServerIndex, DWORD tUniqueNumber, OBJECT_FOR_SHOP* tShop, int tCheckChangeActionState);
	void B_VALETSHOPUPDATE2(int tServerIndex, DWORD tUniqueNumber, OBJECT_FOR_SHOP* tShop, int tCheckChangeActionState);
	void B_VALETSHOPSEND(int tSort, int tResult, VALETSHOP_INFO* tValetShopInfo);
	void B_VALETSHOPSEND1(int tResult, VALETSHOP_INFO* tValetShopInfo, int tPage, int tIndex, int tValue[9], int tCost);

	void B_VALETSHOPGETMONEY(int tResult, int ValetMoney, int ValetBar);


	void B_FISHING(int tServerIndex, DWORD tUniqueNumber, int tResult, int tState, int unk);
	void B_FISHING2(int tServerIndex, DWORD tUniqueNumber, int tResult, int tState, int unk);
	void B_FISHINGITEMSEND(int tResult, int ItemId, int tPage, int tIndex, int tIvenSlot);
	void B_BLOODMARKET(int tResult, int Market[50][3]);
	void B_BLOODMARKETBUY(int tResult, int BloodCoin, int tPage, int tIndex, int tValue[6]);
	void B_DESTROY_ITEM(int tResult, int tMoney, int tValue[6]);
	void B_PET_COMBINE(int tResult, int tValue[6]);
	void B_CAPE_UPGRADE(int tResult, int tValue[6]);


	void B_ITEM_UPGRADE_RECV(int tResult, int tCost, int tValue[6]);
	void B_ENGRAVERECV(int tResult, int tCost, int tKillOtherTribe, int tUnk3, int tImprove);
	void B_MUHURLEGEND(int tResult, int tCost, int tValue[6]);
};
//INSTANCE
extern MyTransfer mTRANSFER;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
