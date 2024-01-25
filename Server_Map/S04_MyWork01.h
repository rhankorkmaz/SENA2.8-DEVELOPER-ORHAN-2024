//-------------------------------------------------------------------------------------------------
//MY_WORK_H
//-------------------------------------------------------------------------------------------------
#ifndef MY_WORK_H
#define MY_WORK_H
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//WORKER_FUNCTION
//-------------------------------------------------------------------------------------------------
//DEFINE
typedef struct
{
	void (*PROC)( int tUserIndex );
}
WORKER_FUNCTION;
//INSTANCE
extern WORKER_FUNCTION W_FUNCTION[256];
//W_TEMP_REGISTER_SEND
void W_TEMP_REGISTER_SEND( int tUserIndex );
//W_REGISTER_AVATAR_SEND
void W_REGISTER_AVATAR_SEND( int tUserIndex );
//W_CLIENT_OK_FOR_ZONE_SEND
void W_CLIENT_OK_FOR_ZONE_SEND( int tUserIndex );
//W_AUTO_CHECK_ASK_RECV
void W_AUTO_CHECK_ASK_RECV( int tUserIndex );
//W_AVATAR_ACTION_SEND
void W_AVATAR_ACTION_SEND( int tUserIndex );
//W_UPDATE_AVATAR_ACTION
void W_UPDATE_AVATAR_ACTION( int tUserIndex );
//W_GENERAL_NOTICE_SEND
void W_GENERAL_NOTICE_SEND( int tUserIndex );
//W_PROCESS_ATTACK_SEND
void W_PROCESS_ATTACK_SEND( int tUserIndex );
//W_PROCESS_DATA_SEND
void W_PROCESS_DATA_SEND( int tUserIndex );
//W_DEMAND_ZONE_SERVER_INFO_2
void W_DEMAND_ZONE_SERVER_INFO_2( int tUserIndex );
//W_FAIL_MOVE_ZONE_2_SEND
void W_FAIL_MOVE_ZONE_2_SEND( int tUserIndex );
//W_USE_HOTKEY_ITEM_SEND
void W_USE_HOTKEY_ITEM_SEND( int tUserIndex );
//W_USE_INVENTORY_ITEM_SEND
void W_USE_INVENTORY_ITEM_SEND( int tUserIndex );
//W_IMPROVE_ITEM_SEND
void W_IMPROVE_ITEM_SEND( int tUserIndex );
//W_ADD_ITEM_SEND
void W_ADD_ITEM_SEND( int tUserIndex );
//W_EXCHANGE_ITEM_SEND
void W_EXCHANGE_ITEM_SEND( int tUserIndex );
//W_HIGH_ITEM_SEND
void W_HIGH_ITEM_SEND( int tUserIndex );
//W_LOW_ITEM_SEND
void W_LOW_ITEM_SEND( int tUserIndex );
//W_MAKE_ITEM_SEND
void W_MAKE_ITEM_SEND( int tUserIndex );
//W_MAKE_SKILL_SEND
void W_MAKE_SKILL_SEND( int tUserIndex );
//W_START_PSHOP_SEND
void W_START_PSHOP_SEND( int tUserIndex );
//W_END_PSHOP_SEND
void W_END_PSHOP_SEND( int tUserIndex );
//W_DEMAND_PSHOP_SEND
void W_DEMAND_PSHOP_SEND( int tUserIndex );
//W_PSHOP_ITEM_INFO_SEND
void W_PSHOP_ITEM_INFO_SEND( int tUserIndex );
//W_BUY_PSHOP_SEND
void W_BUY_PSHOP_SEND( int tUserIndex );
//W_PROCESS_QUEST_SEND
void W_PROCESS_QUEST_SEND( int tUserIndex );
//W_CHANGE_TO_TRIBE4_SEND
void W_CHANGE_TO_TRIBE4_SEND( int tUserIndex );
//W_GENERAL_CHAT_SEND
void W_GENERAL_CHAT_SEND( int tUserIndex );
//W_SECRET_CHAT_SEND
void W_SECRET_CHAT_SEND( int tUserIndex );
//W_GENERAL_SHOUT_SEND
void W_GENERAL_SHOUT_SEND( int tUserIndex );
//W_GET_CASH_SIZE_SEND
void W_GET_CASH_SIZE_SEND( int tUserIndex );
//W_BUY_CASH_ITEM_SEND
void W_BUY_CASH_ITEM_SEND( int tUserIndex );
//W_DUEL_ASK_SEND
void W_DUEL_ASK_SEND( int tUserIndex );
//W_DUEL_CANCEL_SEND
void W_DUEL_CANCEL_SEND( int tUserIndex );
//W_DUEL_ANSWER_SEND
void W_DUEL_ANSWER_SEND( int tUserIndex );
//W_DUEL_START_SEND
void W_DUEL_START_SEND( int tUserIndex );
//W_TRADE_ASK_SEND
void W_TRADE_ASK_SEND( int tUserIndex );
//W_TRADE_CANCEL_SEND
void W_TRADE_CANCEL_SEND( int tUserIndex );
//W_TRADE_ANSWER_SEND
void W_TRADE_ANSWER_SEND( int tUserIndex );
//W_TRADE_START_SEND
void W_TRADE_START_SEND( int tUserIndex );
//W_TRADE_MENU_SEND
void W_TRADE_MENU_SEND( int tUserIndex );
//W_TRADE_END_SEND
void W_TRADE_END_SEND( int tUserIndex );
//W_FRIEND_ASK_SEND
void W_FRIEND_ASK_SEND( int tUserIndex );
//W_FRIEND_CANCEL_SEND
void W_FRIEND_CANCEL_SEND( int tUserIndex );
//W_FRIEND_ANSWER_SEND
void W_FRIEND_ANSWER_SEND( int tUserIndex );
//W_FRIEND_MAKE_SEND
void W_FRIEND_MAKE_SEND( int tUserIndex );
//W_FRIEND_FIND_SEND
void W_FRIEND_FIND_SEND( int tUserIndex );
//W_FRIEND_DELETE_SEND
void W_FRIEND_DELETE_SEND( int tUserIndex );
//W_TEACHER_ASK_SEND
void W_TEACHER_ASK_SEND( int tUserIndex );
//W_TEACHER_CANCEL_SEND
void W_TEACHER_CANCEL_SEND( int tUserIndex );
//W_TEACHER_ANSWER_SEND
void W_TEACHER_ANSWER_SEND( int tUserIndex );
//W_TEACHER_START_SEND
void W_TEACHER_START_SEND( int tUserIndex );
//W_TEACHER_END_SEND
void W_TEACHER_END_SEND( int tUserIndex );
//W_TEACHER_STATE_SEND
void W_TEACHER_STATE_SEND( int tUserIndex );
//W_PARTY_ASK_SEND
void W_PARTY_ASK_SEND( int tUserIndex );
//W_PARTY_CANCEL_SEND
void W_PARTY_CANCEL_SEND( int tUserIndex );
//W_PARTY_ANSWER_SEND
void W_PARTY_ANSWER_SEND( int tUserIndex );
//W_PARTY_MAKE_SEND
void W_PARTY_MAKE_SEND( int tUserIndex );
//W_PARTY_JOIN_SEND
void W_PARTY_JOIN_SEND( int tUserIndex );
//W_PARTY_CHAT_SEND
void W_PARTY_CHAT_SEND( int tUserIndex );
//W_PARTY_LEAVE_SEND
void W_PARTY_LEAVE_SEND( int tUserIndex );
//W_PARTY_EXILE_SEND
void W_PARTY_EXILE_SEND( int tUserIndex );
//W_PARTY_INFO_SEND
void W_PARTY_INFO_SEND( int tUserIndex );
//W_PARTY_BREAK_SEND
void W_PARTY_BREAK_SEND( int tUserIndex );
//W_GUILD_ASK_SEND
void W_GUILD_ASK_SEND( int tUserIndex );
//W_GUILD_CANCEL_SEND
void W_GUILD_CANCEL_SEND( int tUserIndex );
//W_GUILD_ANSWER_SEND
void W_GUILD_ANSWER_SEND( int tUserIndex );
//W_GUILD_WORK_SEND
void W_GUILD_WORK_SEND( int tUserIndex );
//W_GUILD_NOTICE_SEND
void W_GUILD_NOTICE_SEND( int tUserIndex );
//W_GUILD_CHAT_SEND
void W_GUILD_CHAT_SEND( int tUserIndex );
//W_GUILD_FIND_SEND
void W_GUILD_FIND_SEND( int tUserIndex );
//W_TRIBE_WORK_SEND
void W_TRIBE_WORK_SEND( int tUserIndex );
//W_TRIBE_NOTICE_SEND
void W_TRIBE_NOTICE_SEND( int tUserIndex );
//W_TRIBE_CHAT_SEND
void W_TRIBE_CHAT_SEND( int tUserIndex );
//W_TRIBE_BANK_SEND
void W_TRIBE_BANK_SEND( int tUserIndex );
//W_TRIBE_VOTE_SEND
void W_TRIBE_VOTE_SEND( int tUserIndex );
//W_CHECK_HACK_INFO
void W_CHECK_HACK_INFO( int tUserIndex );
//W_CHECK_N_PROTECT_2
void W_CHECK_N_PROTECT_2( int tUserIndex );
//w_MOUT_ABSORB
void w_MOUT_ABSORB(int tUserIndex);
//W_AUTO_POT
void W_AUTO_POT(int tUserIndex);
//W_COSTUME
void W_COSTUME(int tUserIndex);
//W_AUTOBUFF
void W_AUTOBUFF(int tUserIndex);
void W_AUTOBUFF1(int tUserIndex);
//W_CRAFT
void W_CRAFT(int tUserIndex);
//W_MUHAFIZ
void W_MUHAFIZ(int tUserIndex);
//W_FUNCITON_NOTICE
void W_FUNCITON_NOTICE(int tUserIndex);
//W_AUTOBUFF
void W_AUTOHUNT(int tUserIndex);
//W_DAILY_MISSION
void W_DAILY_MISSION(int tUserIndex);
//W_RANK
void W_RANK(int tUserIndex);
//W_RANKPRÝZE
//void W_RANKPRIZE(int tUserIndex)
void W_RANKPRIZE(int tUserIndex);
//W_SOCKETSYSTEM
void W_SOCKETSYSTEM(int tUserIndex);
//W_ADDSOCKETSYSTEM
void W_ADDSOCKETSYSTEM(int tUserIndex);
//W_UPRADGETOWER
void W_UPRADGETOWER(int tUserIndex);
//W_RANKSYSTEM SINIF SÝSTEMÝ
void W_RANKSYSTEM(int tUserIndex);
//W_RANKSYSTEM SINIF SÝSTEMÝ
void W_KAPSUL(int tUserIndex);
//W_HIDECOSTUME
void W_HIDECOSTUME(int tUserIndex);
//W_BOTTLE
void W_BOTTLE(int tUserIndex);
//W_LEGENDERYIMPROVE
void W_LEGENDERYIMPROVE(int tUserIndex);
//W_CHECK_AUTH_KEY
void W_CHECK_AUTH_KEY (int tUserIndex);
//W_UPDATE_AUTH_KEY
void W_UPDATE_AUTH_KEY (int tUserIndex);
//W_ACK_INCOMING_UDP
void W_ACK_INCOMING_UDP (int tUserIndex);
//W_REQUEST_PRESENT
void W_REQUEST_PRESENT (int tUserIndex);
//W_CHANGE_PLAYTIMETOTEACHERPOINT
void W_CHANGE_PLAYTIMETOTEACHERPOINT (int tUserIndex);
//W_CHECK_EVENT_INFO
void W_CHECK_EVENT_INFO(int tUserIndex);
//W_GET_RANK_INFO
void W_GET_RANK_INFO(int tUserIndex);
//W_CHANGE_AUTO_INFO
void W_CHANGE_AUTO_INFO(int tUserIndex);
//W_ANIMAL_STATE_SEND
void W_ANIMAL_STATE_SEND( int tUserIndex );
//W_MEDAL_EXCHANGE_SEND
void W_MEDAL_EXCHANGE_SEND( int tUserIndex );
//W_CORRECT_ANSWER
void W_CORRECT_ANSWER( int tUserIndex );
//W_GET_CASH_ITEM_INFO_SEND
void W_GET_CASH_ITEM_INFO_SEND( int tUserIndex );

//VALET SHOP
//W_VALETSHOPSEND
//void W_VALETSHOPSEND(int tUserIndex);
//W_VALETSHOPITEMDEL
//void W_VALETSHOPITEMDEL(int tUserIndex);
//W_VALET_SHOP_GET_ITEM
//void W_VALET_SHOP_GET_ITEM(int tUserIndex);
//W_FISHING
void W_FISHING(int tUserIndex);
//W_FISHING2
void W_FISHING2(int tUserIndex);
//W_FISHINGWINITEM
void W_FISHINGWINITEM(int tUserIndex);
//W_BLOODMAERKET
void W_BLOODMAERKET(int tUserIndex);
//W_BLOODMAERKETBUY
void W_BLOODMAERKETBUY(int tUserIndex);
// W_SKILLCOMBINE
void W_SKILLCOMBINE(int tUserIndex);
//W_TIMEEFFECT
void W_TIMEEFFECT(int tUserIndex);
//W_DESTROY_ITEM
void W_DESTROY_ITEM(int tUserIndex);
//W_PET_COMBINE_SEND
void W_PET_COMBINE_SEND(int tUserIndex);
//W_CAPE_UPGRADE
void W_CAPE_UPGRADE(int tUserIndex);
//W_FURY
void W_FURY(int tUserIndex);
//W_TRADER_WARLORD_UPGRADE
void W_TRADER_WARLORD_UPGRADE(int tUserIndex);
//W_ENGRAVE
void W_ENGRAVE(int tUserIndex);
//W_BEGGARADDABILITY
void W_BEGGARADDABILITY(int tUserIndex);
//W_BEGGARREQUIEM
void W_BEGGARREQUIEM(int tUserIndex);
//W_TERZI_ITEM_YUKSELTME
void W_TERZI_ITEM_YUKSELTME(int tUserIndex);
//W_TAILOR_SEAL
void W_TAILOR_SEAL(int tUserIndex);
//W_TAILOR_ITEM_UPGRADE
void W_TAILOR_ITEM_UPGRADE(int tUserIndex);

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_WORK
//-------------------------------------------------------------------------------------------------
//DEFINE
class MyWork
{

public :

	int mWorkerPacketSize[256];

	MyWork( void );

	BOOL Init( void );
	void Free( void );
#ifdef __GOD__
	BOOL CheckValidCharacterMotionForSend( int tType, int tSort, int tSkillNumber, int *tSkillSort, int *tCheckMaxAttackPacketNum, int *tAttackPacketSort, int *tMaxAttackPacketNum );
#else
	BOOL CheckValidCharacterMotionForSend( int tType, int tSort, int tSkillNumber, int *tSkillSort, int *tCheckMaxAttackPacketNum, int *tMaxAttackPacketNum );
#endif
	BOOL CheckPossiblePShopRegion( int tTribe, int tZoneNumber, float tCoord[3] );

	void ProcessForRelay( int tSort, BYTE tData[MAX_BROADCAST_DATA_SIZE], int type = 0 );

	void ProcessForData( int tUserIndex, int tSort, BYTE tData[MAX_BROADCAST_DATA_SIZE] );

	BOOL ProcessForGetItem( int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int *tResult );
	BOOL ProcessForLearnSkill1( int tUserIndex, int nIndex, int sIndex, int *tResult );
	BOOL ProcessForSkillUpgrade( int tUserIndex, int tSkillIndex, int *tResult );
	BOOL ProcessForSkillToHotKey( int tUserIndex, int tSkillSort, int tSkillIndex, int tSkillGrade, int tHotKeyPage, int tHotKeyIndex, int *tResult );
	BOOL ProcessForHotKeyToNo( int tUserIndex, int tHotKeyPage, int tHotKeyIndex, int *tResult );
	BOOL ProcessForStatPlus( int tUserIndex, int tStatSort, int *tResult );
	BOOL ProcessForInventoryToInventory( int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int *tResult );
	BOOL ProcessForInventoryToWorld( int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int *tResult );
	BOOL ProcessForInventoryToEquip( int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int *tResult );
	BOOL ProcessForInventoryToHotKey( int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int *tResult );
	BOOL ProcessForInventoryToPetInventory( int tUserIndex, int tPage1, int tIndex1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int *tResult );
	BOOL ProcessForPetInventoryToInventory(int tUserIndex, int tPage1, int tIndex1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult);
	BOOL ProcessForPetInventoryToPetInventory(int tUserIndex, int tPage1, int tIndex1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult);
	BOOL ProcessForInventoryToNPCShop( int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int *tResult );
	BOOL ProcessForEquipToInventory( int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int *tResult );
	BOOL ProcessForHotKeyToInventory( int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int *tResult );
	BOOL ProcessForNPCShopToInventory( int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int *tResult );
	BOOL ProcessForHotKeyToHotKey( int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int *tResult );
	BOOL ProcessForInventoryMoneyToWorld( int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int *tResult );
	BOOL ProcessForInventoryToTrade( int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int *tResult );
	BOOL ProcessForTradeToInventory( int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int *tResult );
	BOOL ProcessForTradeToTrade( int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int *tResult );
	BOOL ProcessForInventoryMoneyToTradeMoney( int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int *tResult );
	BOOL ProcessForTradeMoneyToInventoryMoney( int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int *tResult );
	BOOL ProcessForInventoryToStore( int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int *tResult );
	BOOL ProcessForStoreToInventory( int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int *tResult );
	BOOL ProcessForStoreToStore( int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int *tResult );
	BOOL ProcessForInventoryMoneyToStoreMoney( int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int *tResult );
	BOOL ProcessForStoreMoneyToInventoryMoney( int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int *tResult );
	BOOL ProcessForInventoryToSave( int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int *tResult );
	BOOL ProcessForSaveToInventory( int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int *tResult );
	BOOL ProcessForSaveToSave( int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int *tResult );
	BOOL ProcessForInventoryMoneyToSaveMoney( int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int *tResult );
	BOOL ProcessForSaveMoneyToInventoryMoney( int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int *tResult );
	BOOL ProcessForLearnSkill2( int tUserIndex, int nIndex, int sIndex, int *tResult );
	BOOL ProcessForInventoryBarToInventoryMoney(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult);
	BOOL ProcessForInventoryMoneyToInventoryBar(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult);
	BOOL ProcessForInventoryBarToTradeBar(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult);
	BOOL ProcessForTradeBarToInventoryBar(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult);
	BOOL ProcessForInventoryBarToBankBar(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult);
	BOOL ProcessForBankBarToInventoryBar(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult);
	BOOL ProcessForInventoryBarToSeyisBar(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult);
	BOOL ProcessForSeyisBarToInventoryBar(int tUserIndex, int tPage1, int tIndex1, int tQuantity1, int tPage2, int tIndex2, int tXPost2, int tYPost2, int* tResult);

	void Sphinx_Question_Control(  int iIndex  );
	void Sphinx_Question_TimeCheck( int iIndex );
	void Sphinx_Punishment( int iIndex );
	void Sphinx_Requital( int iIndex );

	bool SkillForMotion(int tUserIdnex, ACTION_INFO* pAction, int tCheckMotion);
	bool ReturnEffectState(int tUserIndex, int tSkillNumber);
};
//INSTANCE
extern MyWork mWORK;
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
