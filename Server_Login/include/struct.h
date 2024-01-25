//-------------------------------------------------------------------------------------------------
//DATATYPE_AND_PROTOCOL_H
//-------------------------------------------------------------------------------------------------
#ifndef DATATYPE_AND_PROTOCOL_H
#define DATATYPE_AND_PROTOCOL_H


//-------------------------------------------------------------------------------------------------

#define     PATCH_DEPLOYMENT_PHASE  4   // 0 ~ 4 패치 단계

// @ Cost Info Download @
#define     MAX_CASH_ITEM_INFO_SIZE                 4 * 10 * 10 * 4 * sizeof(int)
// @

// # X-Trap # {
#define XTRAP_CSFILE_NUM                                            3
#define XTRAP_CS4_BUFSIZE_MAP                                       13000
#define XTRAP_SESSION_BUF_SIZE                                      320
#define XTRAP_STEP_1_BUF_SIZE                                       128
// # }

//-------------------------------------------------------------------------------------------------
//DEFINE_CHANGEABLE_VALUE
//-------------------------------------------------------------------------------------------------
//-------------//
//FOR_STRUCTURE//
//-------------//
#define MAX_AVATAR_NAME_LENGTH										13
#define MAX_EQUIP_SLOT_NUM											13
#define MAX_INVENTORY_SLOT_NUM										64
#define MAX_TRADE_SLOT_NUM											8
#define MAX_STORE_ITEM_SLOT_NUM										28
#define MAX_SKILL_SLOT_NUM											30
#define MAX_HOT_KEY_NUM												14
#define MAX_FRIEND_NUM												10
#define MAX_GUILD_NAME_LENGTH										13
#define MAX_CALL_NAME_LENGTH										5
#define MAX_PARTY_NAME_LENGTH										13
#define MAX_TRIBE4_QUEST_NAME_LENGTH								13
#define MAX_SAVE_ITEM_SLOT_NUM										28
#define MAX_TRIBE_VOTE_AVATAR_NUM									10
#define MAX_TRIBE_SUBMASTER_NUM										12
#define MAX_GUILD_AVATAR_NUM										50
#define MAX_GUILD_NOTICE_LENGTH										41
#define MAX_PSHOP_NAME_LENGTH										25
#define MAX_PSHOP_PAGE_NUM											5
#define MAX_PSHOP_SLOT_NUM											5
/** 2009. 10. 26 : DarkAttack Potion add (wolf) */
#define MAX_AVATAR_EFFECT_SORT_NUM									16
/** 2009. 10. 26 : DarkAttack Potion add (wolf) */

/*뉴영수*/
#define MAX_AVATAR_ANIMAL_NUM										10
#define MAX_CORRECT_ANSWER_NUM										5
//------------//
//FOR_PLAYUSER//
//------------//
#define MAX_ZONE_NUMBER_NUM											300
#define MIN_VALID_ZONE_NUMBER										1
#define MAX_VALID_ZONE_NUMBER										300
#define MAX_PLAY_USER_NUM											3000
#define MAX_NUMBER_SIZE												2000000000
#define MAX_TRIBE_BANK_SLOT_NUM										50
#define MAX_HACK_NAME_LENGTH										101
//----------//
//FOR_CENTER//
//----------//
#define MAX_BROADCAST_INFO_SIZE										100
//---------//
//FOR_RELAY//
//---------//
#define MAX_BROADCAST_DATA_SIZE										100
//---------//
//FOR_EXTRA//
//---------//
#define MAX_GUILD_WORK_SIZE											500
//-----------//
//FOR_GAMELOG//
//-----------//
#define MAX_GAMELOG_LENGTH											1000
//---------//
//FOR_LOGIN//
//---------//
#ifdef __CHANNEL__ // pubwin or kugo
#ifdef __SINA__    // sina
#define MAX_USER_ID_LENGTH											512
#else
#define MAX_USER_ID_LENGTH											33
#endif
#else              // original
#define MAX_USER_ID_LENGTH											51
#endif
#ifdef __SINA__
#define MAX_USER_PASSWORD_LENGTH									1024
#else 
#define MAX_USER_PASSWORD_LENGTH									33
#endif
#define MAX_MOUSE_PASSWORD_LENGTH									5
#define MAX_USER_CARD_NUMBER_LENGTH									33
#define MAX_USER_AVATAR_NUM											3
//--------//
//FOR_ZONE//
//--------//
#define MAX_RADIUS_FOR_NETWORK										450.0f
#define MAX_SELL_ITEM_INFO_NUM										500
#define MAX_AVATAR_OBJECT_NUM										2000
#define MAX_NPC_OBJECT_NUM											100

//----------------------------------------------------------------------------------------------------------------
// 2010.01.15 :김성수
// 무신십이경 추가에 따른 소스 수정
#ifdef __GOD__

#define MAX_MONSTER_OBJECT_NUM										3000
#define MAX_MONSTER_OBJECT_BASE_1_NUM								2500	//..-...
#define MAX_MONSTER_OBJECT_BASE_2_NUM								2600	//..-...
#define MAX_MONSTER_OBJECT_BASE_3_NUM								2700	//..
#define MAX_MONSTER_OBJECT_BASE_4_NUM								2800	//..
#define MAX_MONSTER_OBJECT_BASE_5_NUM								2900	//..

#else

#define MAX_MONSTER_OBJECT_NUM										2000
#define MAX_MONSTER_OBJECT_BASE_1_NUM								1500	//..-...
#define MAX_MONSTER_OBJECT_BASE_2_NUM								1600	//..-...
#define MAX_MONSTER_OBJECT_BASE_3_NUM								1700	//..
#define MAX_MONSTER_OBJECT_BASE_4_NUM								1800	//..
#define MAX_MONSTER_OBJECT_BASE_5_NUM								1900	//..

#endif
//----------------------------------------------------------------------------------------------------------------
#define MAX_MONSTER_OBJECT_ATTACK_NUM								10
#define MAX_ITEM_OBJECT_NUM											2000
#define MAX_LIMIT_LEVEL_NUM											145
//----------------------------------------------------------------------------------------------------------------
// 2010.01.15 :김성수
// 무신십이경 추가에 따른 소스 수정
#ifdef __GOD__
#define MAX_LIMIT_HIGH_LEVEL_NUM									4
#endif
//----------------------------------------------------------------------------------------------------------------


#define MAX_CHAT_CONTENT_LENGTH										61
#define MAX_TRIBE_WORK_SIZE											100
#define MAX_PARTY_AVATAR_NUM										5
#define MAX_ITEM_DUPLICATION_NUM									99
#define MAX_PAT_ACTIVITY_SIZE										200
#define MAX_IMPROVE_ITEM_NUM										40
#define MAX_ADD_ITEM_NUM											12


// 2009.11.19 : 김성수
// 영수 시스템의 영수 이이템 번호 및 영수에 해당 하는 능력치 계수값 정의


const float ANIMAL_MOVE_RATE		= 1.10f;
const int ANIMAL_NUM_CRISTMAS		= 1937;


#ifndef __TK__

const int ANIMAL_BAB				= 1409;

const int ANIMAL_NUM_BAKHO			= 1400;
const int ANIMAL_NUM_DONWHOANG		= 1407;
const int ANIMAL_NUM_CHUNLOK		= 1408;
const int ANIMAL_NUM_CHUNGHO		= 1418;
const int ANIMAL_NUM_TWODON			= 1419;
const int ANIMAL_NUM_BAIKLOK		= 1420;
const int ANIMAL_NUM_CHUKHO			= 1421;
const int ANIMAL_NUM_SUNGDON		= 1422;
const int ANIMAL_NUM_SHINLOK		= 1423;

const float ANIMAL_RATE_ONE_GRADE	= 1.05f;
const float ANIMAL_RATE_TWO_GRADE	= 1.1f;
const float ANIMAL_RATE_THREE_GRADE = 1.15f;
#else

const int ANIMAL_BAB				= 1403;

const int ANIMAL_NUM_BAKHO			= 1404;
const int ANIMAL_NUM_DONWHOANG		= 1405;
const int ANIMAL_NUM_CHUNLOK		= 1406;
const int ANIMAL_NUM_CHUNGHO		= 1407;
const int ANIMAL_NUM_TWODON			= 1408;
const int ANIMAL_NUM_BAIKLOK		= 1409;
const int ANIMAL_NUM_CHUKHO			= 1410;
const int ANIMAL_NUM_SUNGDON		= 1411;
const int ANIMAL_NUM_SHINLOK		= 1412;

const float ANIMAL_RATE_ONE_GRADE	= 1.05f;
const float ANIMAL_RATE_TWO_GRADE	= 1.1f;
const float ANIMAL_RATE_THREE_GRADE = 1.15f;
#endif

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//LEVEL_INFO
//-------------------------------------------------------------------------------------------------
typedef struct
{
	int lIndex;
	int lRangeInfo[3];
	int lAttackPower;
	int lDefensePower;
	int lAttackSuccess;
	int lAttackBlock;
	int lElementAttack;
	int lLife;
	int lMana;
}
LEVEL_INFO;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//ITEM_INFO
//-------------------------------------------------------------------------------------------------
typedef struct
{
	int iIndex;
	char iName[25];
	char iDescription[3][51];
	int iType;
	int iSort;
	int iDataNumber2D;
	int iDataNumber3D;
	int iAddDataNumber3D;
	int iLevel;
	//----------------------------------------------------------------------------------------------------------------
	// 2010.01.15 :김성수
	// 무신십이경 추가에 따른 소스 수정
#ifdef __GOD__
	int iMartialLevel;
#endif
	//----------------------------------------------------------------------------------------------------------------
	int iEquipInfo[2];
	int iBuyCost;
	int iSellCost;
	int iLevelLimit;
	//----------------------------------------------------------------------------------------------------------------
	// 2010.01.15 :김성수
	// 무신십이경 추가에 따른 소스 수정
#ifdef __GOD__
	int iMartialLevelLimit;
#endif
	//----------------------------------------------------------------------------------------------------------------
	int iCheckMonsterDrop;
	int iCheckNPCSell;
	int iCheckNPCShop;
	int iCheckAvatarDrop;
	int iCheckAvatarTrade;
	int iCheckAvatarShop;
	int iCheckImprove;
	int iCheckHighImprove;
	int iCheckHighItem;
	int iCheckLowItem;
	int iCheckExchange;
	int iStrength;
	int iWisdom;
	int iVitality;
	int iKi;
	int iLuck;
	int iAttackPower;
	int iDefensePower;
	int iAttackSucess;
	int iAttackBlock;
	int iElementAttackPower;
	int iElementDefensePower;
	int iCritical;
	int iPotionType[2];
	int iGainSkillNumber;
	int iLastAttackBonusInfo[2];
	int iCapeInfo[3];
	//----------------------------------------------------------------------------------------------------------------
	// 2010.01.15 :김성수
	// 무신십이경 추가에 따른 소스 수정
#ifdef __GOD__
	int iBonusSkillInfo[8][2];
#else
	int iBonusSkillInfo[5][2];
#endif
	//----------------------------------------------------------------------------------------------------------------
}
ITEM_INFO;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//GRADE_INFO_FOR_SKILL
//-------------------------------------------------------------------------------------------------
typedef struct
{
	int sManaUse;
	int sRecoverInfo[2];
	int sStunAttack;
	int sStunDefense;
	int sFastRunSpeed;
	int sAttackInfo[3];
	int sRunTime;
	int sChargingDamageUp;
	int sAttackPowerUp;
	int sDefensePowerUp;
	int sAttackSuccessUp;
	int sAttackBlockUp;
	int sElementAttackUp;
	int sElementDefenseUp;
	int sAttackSpeedUp;
	int sRunSpeedUp;
	int sShieldLifeUp;
	int sLuckUp;
	int sCriticalUp;
	int sReturnSuccessUp;
	int sStunDefenseUp;
	int sDestroySuccessUp;
}
GRADE_INFO_FOR_SKILL;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//SKILL_INFO
//-------------------------------------------------------------------------------------------------
typedef struct
{
	int sIndex;
	char sName[25];
	char sDescription[10][51];
	int sType;
	int sAttackType;
	int sDataNumber2D;
	int sTribeInfo[2];
	int sLearnSkillPoint;
	int sMaxUpgradePoint;
	int sTotalHitNumber;
	int sValidRadius;
	GRADE_INFO_FOR_SKILL sGradeInfo[2];
}
SKILL_INFO;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//MONSTER_INFO
//-------------------------------------------------------------------------------------------------
typedef struct
{
	int mIndex;
	char mName[25];
	char mChatInfo[2][101];
	int mType;
	int mSpecialType;
	int mDamageType;
	int mDataSortNumber;
	int mSize[4];
	int mSizeCategory;
	int mCheckCollision;
	int mFrameInfo[6];
	int mTotalHitNum;
	int mHitFrame[3];
	int mTotalSkillHitNum;
	int mSkillHitFrame[3];
	int mBulletInfo[2];
	int mSummonTime[2];
	int mItemLevel;
	//----------------------------------------------------------------------------------------------------------------
	// 2010.01.15 :김성수
	// 무신십이경 추가에 따른 소스 수정
#ifdef __GOD__
	int mMartialItemLevel;
#endif
	//----------------------------------------------------------------------------------------------------------------
	int mRealLevel;
	//----------------------------------------------------------------------------------------------------------------
	// 2010.01.15 :김성수
	// 무신십이경 추가에 따른 소스 수정
#ifdef __GOD__
	int mMartialRealLevel;
#endif
	//----------------------------------------------------------------------------------------------------------------
	int mGeneralExperience;
	int mPatExperience;
	int mLife;
	int mAttackType;
	int mRadiusInfo[2];
	int mWalkSpeed;
	int mRunSpeed;
	int mDeathSpeed;
	int mAttackPower;
	int mDefensePower;
	int mAttackSuccess;
	int mAttackBlock;
	int mElementAttackPower;
	int mElementDefensePower;
	int mCritical;
	int mFollowInfo[2];
	int mDropMoneyInfo[3];
	int mDropPotionInfo[5][2];
	int mDropItemInfo[12];
	int mDropQuestItemInfo[2];
	int mDropExtraItemInfo[50][2];
}
MONSTER_INFO;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//NPC_INFO
//-------------------------------------------------------------------------------------------------
typedef struct
{
	int nIndex;
	char nName[25];
	int nSpeechNum;
	char nSpeech[5][5][51];
	int nTribe;
	int nType;
	int nDataSortNumber2D;
	int nDataSortNumber3D;
	int nSize[3];
	int nMenu[50];
	int nShopInfo[3][28];
	int nSkillInfo1[3][8];
	int nSkillInfo2[3][3][3][8];
	int nGambleCostInfo[145][15];
}
NPC_INFO;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//QUEST_INFO
//-------------------------------------------------------------------------------------------------
typedef struct
{
	int qIndex;
	char qSubject[51];
	int qCategory;
	int qStep;
	int qLevel;
	int qType;
	int qSort;
	int qSummonInfo[4];
	int qStartNPCNumber;
	int qKeyNPCNumber[5];
	int qEndNPCNumber;
	int qSolution[4];
	int qReward[3][2];
	int qNextIndex;
	char qStartSpeech[15][51];
	int qStartSpeechColor[15];
	char qHurrySpeech[15][51];
	int qHurrySpeechColor[15];
	char qProcessSpeech1[15][51];
	int qProcessSpeech1Color[15];
	char qProcessSpeech2[15][51];
	int qProcessSpeech2Color[15];
	char qProcessSpeech3[15][51];
	int qProcessSpeech3Color[15];
	char qProcessSpeech4[15][51];
	int qProcessSpeech4Color[15];
	char qProcessSpeech5[15][51];
	int qProcessSpeech5Color[15];
	char qSuccessSpeech[15][51];
	int qSuccessSpeechColor[15];
	char qFailureSpeech[15][51];
	int qFailureSpeechColor[15];
	char qCallSpeech[15][51];
	int qCallSpeechColor[15];
}
QUEST_INFO;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//HELP_INFO
//-------------------------------------------------------------------------------------------------
typedef struct
{
	int hIndex;
	char hKeyword[5][13];
	int hTribe;
	int hLevel;
	int h2DImage;
}
HELP_INFO;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//AVATAR_INFO
//-------------------------------------------------------------------------------------------------
typedef struct
{
	int aVisibleState; // .... ... 0 .. 1.
	int aSpecialState; // GM .... .. ... .., 0 .. 1.
	int aPlayTime1;
	int aPlayTime2;
	int aPlayTime3;
	int aKillOtherTribe;
	char aName[MAX_AVATAR_NAME_LENGTH];
	int aTribe; // 0 ~ 3, ../../../...
	int aPreviousTribe; // 0 ~ 2, ../../...
	int aGender; // 0 .. 1.
	int aHeadType; // 0 ~ 6.
	int aFaceType; // 0 ~ 2.
	int aLevel1;
	int aLevel2;
	int aGeneralExperience1;
	int aGeneralExperience2;
	int aVitality;
	int aStrength;
	int aKi;
	int aWisdom;
	int aEatLifePotion;
	int aEatManaPotion;
	int aStateBonusPoint;
	int aSkillPoint;
	int aEquip[MAX_EQUIP_SLOT_NUM][4];
	int aExpandInventoryDate;
	int aMoney;
	int aInventory[2][MAX_INVENTORY_SLOT_NUM][6];
	int aTradeMoney;
	int aTrade[MAX_TRADE_SLOT_NUM][4];
	int aExpandStoreDate;
	int aStoreMoney;
	int aStoreItem[2][MAX_STORE_ITEM_SLOT_NUM][4];
	int aSkill[MAX_SKILL_SLOT_NUM][2];
	int aHotKey[3][MAX_HOT_KEY_NUM][3];
	int aQuestInfo[5];
	char aFriend[MAX_FRIEND_NUM][MAX_AVATAR_NAME_LENGTH];
	char aTeacher[MAX_AVATAR_NAME_LENGTH];
	char aStudent[MAX_AVATAR_NAME_LENGTH];
	int aTeacherPoint;
	char aGuildName[MAX_GUILD_NAME_LENGTH];
	int aGuildRole;
	char aCallName[MAX_CALL_NAME_LENGTH];
	int aGuildMarkNum;
	int aGuildMarkEffect;
	int aLogoutInfo[6];
	int aProtectForDeath;
	int aProtectForDestroy;
	int aDoubleExpTime1;	//..._..
	int aDoubleExpTime2;	//..._..
	int aDoubleExpTime3;	//Double Experience for level of low than 30.
	int aDoubleKillNumTime;
	int aDoubleKillExpTime;
	int aNineTowerKeyNum;
	int aZone101TypeTime;
	int aZone125TypeTime;
	int aZone126TypeTime;
	int aKillMonsterNum;
	int aLevelZoneKeyNum;
	int aSearchAndBuyDate;
	int aLifePotionConvertNum;
	int aManaPotionConvertNum;
	int aTribeVoteDate;
	int uSaveMoney;
	int uSaveItem[MAX_SAVE_ITEM_SLOT_NUM][4];
	//Auto potion.
	int aUse_AutoPotion_Date;
	int aUse_AutoPotion_Time;
	int aAutoLifeRatio;
	int aAutoManaRatio;
	/*뉴영수*/
	int aAnimal[MAX_AVATAR_ANIMAL_NUM];
	int aAnimalIndex;
	int aAnimalTime;

	int aDoubleDropTime;

	//----------------------------------------------------------------------------------------------------------------
	// 2010.01.15 :김성수
	// 무신십이경 추가에 따른 소스 수정
#ifdef __GOD__
	int aAddItemValue;
	int aHighItemValue;
	int aDropItemTime;
	int aTribeCallValue;
	int aUpgradeValue;
	int aBonusItemValue;
	int aKillOtherTribeEvent;
	int aTeacherPointEvent;
	int aPlayTimeEvent;
	int aProtectForUpgrade;
#endif
	//----------------------------------------------------------------------------------------------------------------


	char aPartyName[MAX_PARTY_NAME_LENGTH];

	//@{ auto quiz
	int iCriminal_Record;
	int iEnter_The_Prison;
	int iKill_Monster_Count;
	//@}

	int aEatStrengthPotion;
	int aEatWisdomPotion;

	int aPat_Exp_x2_Time;
	int aPat_User_Exp_x2_Time;

	int aFiveExpTime;

	unsigned int aZone84Time;

	/** 2009. 11. 18 : 장식 해방 시스템 (wolf) */
	int iSilverOrnamentRemainsTime; // 은장서 사용 가능 잔여 시간.
	int	iGoldOrnamentRemainsTime;  // 금장서 사용 가능 잔여 시간.
	int iUseOrnament; // 장식 해방 (금장서, 은장서) 시스템 사용 여부.
	/** 2009. 11. 18 : 장식 해방 시스템 (wolf) */

	/** 2009. 11. 23 : 패키지 아이템 개발 (wolf) */
#ifdef __TK__

	int aPackSilverDate;
	int aPackGoldDate;
	int aPackDiamondDate;
	int aPackSilverDateMobile;
	int aPackGoldDateMobile;
	int aPackDiamondDateMobile;

#endif
	/** 2009. 11. 23 : 패키지 아이템 개발 (wolf) */

	/** 2009. 12. 16 : 강화, 조합, 승급부(특) 아이템 개발 (wolf) */
	int aLevelZoneKeyNum2;
	/** 2009. 12. 16 : 강화, 조합, 승급부(특) 아이템 개발 (wolf) */

	/** 2009. 12. 16 : 귀멸부 아이템 개발 (wolf) */
	int aDoubleKillNumTime2;
	/** 2009. 12. 16 : 귀멸부 아이템 개발 (wolf) */

	int aKillMonsterNum2; // 몬스터 사냥 카운트 변수 - 몬스터 사냥 수에 따른 기여도 제공여부 계산을 위한 변수.
}
AVATAR_INFO;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//WORLD_INFO
//-------------------------------------------------------------------------------------------------
typedef struct
{
	int mZone038WinTribe;
	int mTribeSymbolBattle;
	int mTribe1Symbol;
	int mTribe2Symbol;
	int mTribe3Symbol;
	int mTribe4Symbol;
	int mMonsterSymbol;
	int mTribePoint[4];
	int mTribeCloseInfo[2];
	int mPossibleAllianceInfo[4][2];
	int mAllianceState[2][2];
	int mTribeVoteState[4];
	int mCloseVoteState[4];
	int mTribe4QuestDate;
	int mTribe4QuestState;
	char mTribe4QuestName[MAX_TRIBE4_QUEST_NAME_LENGTH];
	//----------------------------------------------------------------------------------------------------------------
	// 2010.01.15 :김성수
	// 무신십이경 추가에 따른 소스 수정
#ifdef __GOD__
	int mZone049TypeState[9];
#else
	int mZone049TypeState[6];
#endif
	//----------------------------------------------------------------------------------------------------------------

	int mZone051TypeState[6];
	int mZone053TypeState[10];
	//----------------------------------------------------------------------------------------------------------------
	// 2010.01.15 :김성수
	// 무신십이경 추가에 따른 소스 수정
#ifdef __GOD__
	int mZone175TypeState[4][8];
#else
	int mZone175TypeState[4][5]; 
#endif
	//----------------------------------------------------------------------------------------------------------------
	int mTribeGuardState[4][4];
	int mTribeMasterCallAbility[4];//세력진법 변수
	//----------------------------------------------------------------------------------------------------------------
	// 2010.01.15 :김성수
	// 무신십이경 추가에 따른 소스 수정
#ifdef __GOD__
	int mZone194State;
	float mTribeGeneralExperienceUpRatioInfo[4];
	float mTribeItemDropUpRatioInfo[4];
	float mTribeItemDropUpRatioForMyoungInfo[4];
	int mTribeKillOtherTribeAddValueInfo[4];
	int mZone267TypeState[3];
#endif
	//----------------------------------------------------------------------------------------------------------------
}
WORLD_INFO;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//TRIBE_INFO
//-------------------------------------------------------------------------------------------------
typedef struct
{
	char mTribeVoteName[4][MAX_TRIBE_VOTE_AVATAR_NUM][MAX_AVATAR_NAME_LENGTH];
	int mTribeVoteLevel[4][MAX_TRIBE_VOTE_AVATAR_NUM];
	int mTribeVoteKillOtherTribe[4][MAX_TRIBE_VOTE_AVATAR_NUM];
	int mTribeVotePoint[4][MAX_TRIBE_VOTE_AVATAR_NUM];
	char mTribeMaster[4][MAX_AVATAR_NAME_LENGTH];
	char mTribeSubMaster[4][MAX_TRIBE_SUBMASTER_NUM][MAX_AVATAR_NAME_LENGTH];
}
TRIBE_INFO;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//GUILD_INFO
//-------------------------------------------------------------------------------------------------
typedef struct
{
	char gName[MAX_GUILD_NAME_LENGTH];
	int gGrade;
	char gMaster01[MAX_AVATAR_NAME_LENGTH];
	char gSubMaster01[MAX_AVATAR_NAME_LENGTH];
	char gSubMaster02[MAX_AVATAR_NAME_LENGTH];
	char gMemberName[MAX_GUILD_AVATAR_NUM][MAX_AVATAR_NAME_LENGTH];
	int gMemberRole[MAX_GUILD_AVATAR_NUM];
	char gMemberCall[MAX_GUILD_AVATAR_NUM][MAX_CALL_NAME_LENGTH];
	char gNotice[4][MAX_GUILD_NOTICE_LENGTH];
}
GUILD_INFO;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//ZONE_CONNECTION_INFO
//-------------------------------------------------------------------------------------------------
typedef struct
{
	char mIP[MAX_ZONE_NUMBER_NUM][16];
	int mPort[MAX_ZONE_NUMBER_NUM];
}
ZONE_CONNECTION_INFO;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//SELL_ITEM_INFO
//-------------------------------------------------------------------------------------------------
typedef struct
{
	int mState;
	char mID[MAX_USER_ID_LENGTH];
	int mItemInfo[5];											//[0]:..,[1]:..,[2]:..,[3]:..,[4]:..
}
SELL_ITEM_INFO;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//PSHOP_INFO
//-------------------------------------------------------------------------------------------------
typedef struct
{
	DWORD mUniqueNumber;
	char mName[MAX_PSHOP_NAME_LENGTH];
	int mItemInfo[MAX_PSHOP_PAGE_NUM][MAX_PSHOP_SLOT_NUM][9];	//[0]:..,[1]:..,[2]:..,[3]:..,[4]:..,[5]:mPage,[6]:mIndex,[7]:mXPost,[8]:mYPost
}
PSHOP_INFO;
//-------------------------------------------------------------------------------------------------

#pragma pack (push, 1)

//-------------------------------------------------------------------------------------------------
//ACTION_INFO
//-------------------------------------------------------------------------------------------------
typedef struct
{
	BYTE        aType               :   3;
	BYTE        aTargetObjectSort   :   3;
	BYTE        aSort;;
	short       aSkillValue;        ///< .. ... ..... .. ..?.

	float aFrame;
	float aLocation[3];
	float aTargetLocation[3];
	float aFront;
	float aTargetFront;
	int aTargetObjectIndex;
	DWORD aTargetObjectUniqueNumber;
	short       aSkillNumber;   ///< .. .. 300.
	BYTE        aSkillGradeNum1;    ///< .. ....
	BYTE        aSkillGradeNum2;    ///< ..(... ..?) ....
}
ACTION_INFO;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//OBJECT_FOR_AVATAR
//-------------------------------------------------------------------------------------------------
typedef struct
{
	BYTE    aVisibleState       :   1;
	BYTE    aSpecialState       :   1;
	BYTE    aGuildRole          :   2;
	BYTE    aGuildMarkEffect    :   1;
	BYTE    aGender             :   1;
	BYTE    aTribe              :   2;

	BYTE    aPreviousTribe      :   2;
	BYTE    aHeadType           :   3;
	BYTE    aPShopState         :   1;
	BYTE    aFaceType           :   2;

	BYTE    aLevel1;
	BYTE    aLevel2;

	int     aKillOtherTribe;
	int     uGoodFellow;

	char aGuildName[MAX_GUILD_NAME_LENGTH];
	char aCallName[MAX_CALL_NAME_LENGTH];
	char aName[MAX_AVATAR_NAME_LENGTH];
	int aEquipForView[MAX_EQUIP_SLOT_NUM][2];

	/** 2009. 10. 26 : DarkAttack Potion add (wolf)*/
	bool bStateDarkAttack;
	/** 2009. 10. 26 : DarkAttack Potion add (wolf)*/

	/*뉴영수*/
	int aAnimalNumber;

	ACTION_INFO aAction;
	int aMaxLifeValue;
	int aLifeValue;
	int aMaxManaValue;
	int aManaValue;
	//-------------//
	//[ 0]:....//
	//[ 1]:....//
	//[ 2]:....//
	//[ 3]:....//
	//[ 4]:....//
	//[ 5]:....//
	//[ 6]:....//
	//[ 7]:....//
	//[ 8]:..    //
	//[ 9]:....//
	//[10]:....//
	//[11]:.      //
	//[12]:....//
	//[13]:....//
	//[14]:....//
	//-------------//
	int aEffectValueForView[MAX_AVATAR_EFFECT_SORT_NUM];
	//-------------//
	//-------------//
	//-------------//
	char aPartyName[MAX_PARTY_NAME_LENGTH];
	int aDuelState[3];
	char aPShopName[MAX_PSHOP_NAME_LENGTH];
}
OBJECT_FOR_AVATAR;
//-------------------------------------------------------------------------------------------------

typedef struct{
	BYTE AuthType;
	BYTE FindFlag;
	BYTE MoveFlag;
	BYTE MoveZoneFlag;
	BYTE CallFlag;
	BYTE HideFlag;
	BYTE ShowFlag;
	BYTE KickFlag;
	BYTE BlockFlag;
	BYTE MonCallFlag;
	BYTE EquipFlag;
	BYTE UnequipFlag;
	BYTE YchatFlag;
	BYTE NchatFlag;
	BYTE NoticeFlag;
	BYTE ItemFlag;
	BYTE MoneyFlag;
	BYTE ExpFlag;
	BYTE DieFlag;
	BYTE GodFlag;
	BYTE ChatFlag;
	BYTE TradeFlag;
	BYTE ShopFlag;
	BYTE PShopFlag;
	BYTE GItemFlag;
	BYTE DItemFlag;
	BYTE AttackFlag;
	BYTE UZonemoveFlag;
}
AUTH_INFO;

// 이동서 사용 정보.
typedef struct _MOVE_ITEM_INFO { // 멤버 값들이 -1이면 사용하지 않은 것입니다.
	int mZoneNumber;        // 이동할 존 번호.
	int mInvenPage;         // 이동서 아이템이 위치한 인벤토리 페이지.
	int mInvenIndex;        // 이동서 아이템이 위치한 배열 index.
	int mInvenX;            // 이동서 아이템 x좌표.
	int mInvenY;            // 이동서 아이템 y좌표.
} MOVE_ITEM_INFO;
#pragma pack (pop)

//-------------------------------------------------------------------------------------------------
//OBJECT_FOR_MONSTER
//-------------------------------------------------------------------------------------------------
typedef struct
{
	int mIndex;
	ACTION_INFO mAction;
	int mLifeValue;
}
OBJECT_FOR_MONSTER;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//OBJECT_FOR_ITEM
//-------------------------------------------------------------------------------------------------
typedef struct
{
	int iIndex;
	int iQuantity;
	int iValue;
	int iItemRecognitionNumber;
	float iLocation[3];
	char iMaster[MAX_AVATAR_NAME_LENGTH];
	DWORD iCreateTime;
	DWORD iPresentTime;
	int iCreateState;
}
OBJECT_FOR_ITEM;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//ATTACK_FOR_PROTOCOL
//-------------------------------------------------------------------------------------------------
typedef struct
{
	int mCase;					//[....]::1.[...->...(..)],2.[...->...(..)],3.[...->...],4.[...->...],5.[..],6.[..]
	int mServerIndex1;
	DWORD mUniqueNumber1;
	int mServerIndex2;
	DWORD mUniqueNumber2;
	// # Defense Hack # {
	DWORD mUniqueNumber3;
	// # }
	float mSenderLocation[3];
	int mAttackActionValue1;	//[....]::1.[....],2[....]
	int mAttackActionValue2;	//[....] OR [....]
	int mAttackActionValue3;	//[....]
	int mAttackActionValue4;	//[....]
	int mAttackResultValue;		//[....]::0.[..],1.[..]
	int mAttackCriticalExist;	//[....]::0.[..],1.[..]
	int mAttackElementDamage;	//[....]
	int mAttackViewDamageValue;	//[....]
	int mAttackRealDamageValue;	//[....]
}
ATTACK_FOR_PROTOCOL;

//RANK_FOR_PROTOCOL
typedef struct _s_rank_level {
	char aName[MAX_AVATAR_NAME_LENGTH];
	int level;
	int tribe;
} rank_level_t;

typedef struct _s_rank_kill {
	char aName[MAX_AVATAR_NAME_LENGTH];
	int kill;
	int tribe;
} rank_kill_t;

typedef struct _s_rank_info {
	char aName[MAX_AVATAR_NAME_LENGTH];
	int level;
	int kill;
	int tribe;
	int rank;
} rank_info_t;

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//PROTOCOL
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//DEFINITION_FOR_PLAYUSER
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//[RECV_PROTOCOL]
//-------------------------------------------------------------------------------------------------
//---------------------//
//[LOGIN] -> [PLAYUSER]//
//---------------------//
//protocol(1)
#define P_LOGIN_FOR_PLAYUSER_SEND									11
#define S_LOGIN_FOR_PLAYUSER_SEND									1
//protocol(1)
#define P_LOGIN_OK_FOR_PLAYUSER_SEND								12
#define S_LOGIN_OK_FOR_PLAYUSER_SEND								1
//protocol(1) + tIP(16) + tID(MAX_USER_ID_LENGTH) + tUserSort(4) + tGoodFellow(4) + tLoginPlace(4) + tLoginPremium(4) + tPremiumPCRoom(4) + tTraceState(4) + tBonus100Money + sizeof (AUTH_INFO) + tPremiumServerExpirationDate(4)
#define P_REGISTER_USER_FOR_LOGIN_1_SEND							13
#define S_REGISTER_USER_FOR_LOGIN_1_SEND							46 + MAX_USER_ID_LENGTH + sizeof (AUTH_INFO) // + tPremiumServerExpirationDate(4) // @_Premium_Server_@
//protocol(1) + tPlayUserIndex(4) + tID(MAX_USER_ID_LENGTH)
#define P_REGISTER_USER_FOR_LOGIN_2_SEND							14
#define S_REGISTER_USER_FOR_LOGIN_2_SEND							5 + MAX_USER_ID_LENGTH
//protocol(1) + tPlayUserIndex(4) + tID(MAX_USER_ID_LENGTH) + tAvatarInfo( sizeof( AVATAR_INFO ) )
#define P_REGISTER_USER_FOR_LOGIN_3_SEND							15
#define S_REGISTER_USER_FOR_LOGIN_3_SEND							5 + MAX_USER_ID_LENGTH + sizeof( AVATAR_INFO )
//protocol(1) + tPlayUserIndex(4) + tID(MAX_USER_ID_LENGTH)
#define P_UNREGISTER_USER_FOR_LOGIN_SEND							16
#define S_UNREGISTER_USER_FOR_LOGIN_SEND							5 + MAX_USER_ID_LENGTH
//protocol(1)
#define P_GET_PRESENT_USER_NUM_FOR_LOGIN_SEND						17
#define S_GET_PRESENT_USER_NUM_FOR_LOGIN_SEND						1
//protocol(1) + tSort(4) + tID(MAX_USER_ID_LENGTH)
#define P_BLOCK_USER_FOR_LOGIN_1_SEND								18
#define S_BLOCK_USER_FOR_LOGIN_1_SEND								5 + MAX_USER_ID_LENGTH
//protocol(1) + tSort(4) + tID(MAX_USER_ID_LENGTH)
#define P_BLOCK_USER_FOR_LOGIN_2_SEND								19
#define S_BLOCK_USER_FOR_LOGIN_2_SEND								5 + MAX_USER_ID_LENGTH
//--------------------//
//[ZONE] -> [PLAYUSER]//
//--------------------//
//protocol(1) + tZoneNumber(4)
#define P_ZONE_FOR_PLAYUSER_SEND									31
#define S_ZONE_FOR_PLAYUSER_SEND									5
//protocol(1)
#define P_ZONE_OK_FOR_PLAYUSER_SEND									32
#define S_ZONE_OK_FOR_PLAYUSER_SEND									1
//protocol(1) + tID(MAX_USER_ID_LENGTH)
#define P_REGISTER_USER_FOR_ZONE_0_SEND								33
#define S_REGISTER_USER_FOR_ZONE_0_SEND								1 + MAX_USER_ID_LENGTH
//protocol(1) + tPlayUserIndex(4) + tID(MAX_USER_ID_LENGTH) + tAvatarName(MAX_AVATAR_NAME_LENGTH) + tLogoutInfo(24)
#define P_REGISTER_USER_FOR_ZONE_1_SEND								34
#define S_REGISTER_USER_FOR_ZONE_1_SEND								29 + MAX_USER_ID_LENGTH + MAX_AVATAR_NAME_LENGTH
//protocol(1) + tPlayUserIndex(4) + tID(MAX_USER_ID_LENGTH) + tAvatarInfo( sizeof( AVATAR_INFO ) ) + tEffectValue(MAX_AVATAR_EFFECT_SORT_NUM * 8)
#define P_REGISTER_USER_FOR_ZONE_2_SEND								35
#define S_REGISTER_USER_FOR_ZONE_2_SEND								5 + MAX_USER_ID_LENGTH + sizeof( AVATAR_INFO ) + (MAX_AVATAR_EFFECT_SORT_NUM * 8) + sizeof (AUTH_INFO)
//protocol(1) + tPlayUserIndex(4) + tID(MAX_USER_ID_LENGTH) + tAvatarInfo( sizeof( AVATAR_INFO ) ) + tEffectValue(MAX_AVATAR_EFFECT_SORT_NUM * 8)
#define P_REGISTER_USER_FOR_ZONE_3_SEND								36
#define S_REGISTER_USER_FOR_ZONE_3_SEND								5 + MAX_USER_ID_LENGTH + sizeof( AVATAR_INFO ) + (MAX_AVATAR_EFFECT_SORT_NUM * 8) + sizeof (AUTH_INFO)
//protocol(1) + tPlayUserIndex(4) + tID(MAX_USER_ID_LENGTH) + tAvatarInfo( sizeof( AVATAR_INFO ) )
#define P_UNREGISTER_USER_FOR_ZONE_SEND								37
#define S_UNREGISTER_USER_FOR_ZONE_SEND								5 + MAX_USER_ID_LENGTH + sizeof( AVATAR_INFO ) + sizeof (AUTH_INFO)
//protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH)
#define P_FIND_AVATAR_FOR_ZONE_SEND									38
#define S_FIND_AVATAR_FOR_ZONE_SEND									1 + MAX_AVATAR_NAME_LENGTH
//protocol(1) + tMoney(16)
#define P_TRIBE_BANK_INFO_SAVE_SEND									39
#define S_TRIBE_BANK_INFO_SAVE_SEND									17
//protocol(1) + tTribe(4)
#define P_TRIBE_BANK_INFO_VIEW_SEND									40
#define S_TRIBE_BANK_INFO_VIEW_SEND									5
//protocol(1) + tTribe(4) + tTribeBankInfoIndex(4) + tInventoryMoney(4)
#define P_TRIBE_BANK_INFO_LOAD_SEND									41
#define S_TRIBE_BANK_INFO_LOAD_SEND									13
//protocol(1) + tID(MAX_USER_ID_LENGTH) + tHackName(MAX_HACK_NAME_LENGTH) + tHackSize(4)
#define P_HACK_NAME_SEND											42
#define S_HACK_NAME_SEND											5 + MAX_USER_ID_LENGTH + MAX_HACK_NAME_LENGTH
//protocol(1) + tSort(4) + tID(MAX_USER_ID_LENGTH)
#define P_BLOCK_USER_FOR_ZONE_1_SEND								43
#define S_BLOCK_USER_FOR_ZONE_1_SEND								5 + MAX_USER_ID_LENGTH
//protocol(1) + tSort(4) + tID(MAX_USER_ID_LENGTH)
#define P_BLOCK_USER_FOR_ZONE_2_SEND								44
#define S_BLOCK_USER_FOR_ZONE_2_SEND								5 + MAX_USER_ID_LENGTH
//protocol(1) + tID(MAX_USER_ID_LENGTH) + tAvatarName(MAX_AVATAR_NAME_LENGTH) + tWorldNumber(4) + tZoneNumber(4)
#define P_ADD_AUTO_USER_LIST_SEND									45
#define S_ADD_AUTO_USER_LIST_SEND									9 + MAX_USER_ID_LENGTH + MAX_AVATAR_NAME_LENGTH
//protocol(1) + tAvatarName1(MAX_AVATAR_NAME_LENGTH) + tAvatarName2(MAX_AVATAR_NAME_LENGTH)
#define P_CHECK_KILL_OTHER_TRIBE_SEND								46
#define S_CHECK_KILL_OTHER_TRIBE_SEND								1 + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH
//protocol(1) + tID(MAX_USER_ID_LENGTH) + tSort(4)
#define P_EVENT_INFO_SEND											47
#define S_EVENT_INFO_SEND											5 + MAX_USER_ID_LENGTH

#pragma pack (push, 1)

#define ZTOP_CHECK_AUTH_KEY_TYPE     48
struct ZTOP_CHECK_AUTH_KEY {
	ZTOP_CHECK_AUTH_KEY (void) {
		m_bMagic =  ZTOP_CHECK_AUTH_KEY_TYPE;
		::ZeroMemory (m_szUserID, sizeof (m_szUserID));
		::ZeroMemory (m_szAuthKey, sizeof (m_szAuthKey));
	}

	BYTE    m_bMagic;
	char    m_szUserID[MAX_USER_ID_LENGTH];
	char    m_szAuthKey[MAX_MOUSE_PASSWORD_LENGTH];
};
#define ZTOP_CHECK_AUTH_KEY_SIZE                    sizeof (ZTOP_CHECK_AUTH_KEY)

#define ZTOP_UPDATE_AUTH_KEY_TYPE       49
struct ZTOP_UPDATE_AUTH_KEY {
	ZTOP_UPDATE_AUTH_KEY (void) {
		m_bMagic = ZTOP_UPDATE_AUTH_KEY_TYPE;
		::ZeroMemory (m_szUserID, sizeof (m_szUserID));
		::ZeroMemory (m_szAuthKey, sizeof (m_szAuthKey));
	}

	BYTE    m_bMagic;
	char    m_szUserID[MAX_USER_ID_LENGTH];
	char    m_szAuthKey[2][MAX_MOUSE_PASSWORD_LENGTH];
};
#define ZTOP_UPDATE_AUTH_KEY_SIZE                   sizeof (ZTOP_UPDATE_AUTH_KEY)

#pragma pack (pop)
//protocol(1) + tPlayUserIndex(4) + tChangeAvatarName(MAX_AVATAR_NAME_LENGTH) 
#define P_CHANGE_AVATAR_NAME_FOR_ZONE_SEND							50
#define S_CHANGE_AVATAR_NAME_FOR_ZONE_SEND							5 + MAX_AVATAR_NAME_LENGTH 
//protocol(1) + tPlayUserIndex(4)
#define P_BONUS_100_MONEY_FOR_ZONE_SEND								51
#define S_BONUS_100_MONEY_FOR_ZONE_SEND								5

#ifdef __EVENT_KILL__
//protocol(1) + tPlayUserIndex(4) + tKillNum(4)
#define P_EVENT_FOR_ZONE_SEND										63
#define S_EVENT_FOR_ZONE_SEND										9
#elif __EVENT_GOLD_PHONE__
//protocol(1) + tPlayUserIndex(4)
#define P_EVENT_FOR_ZONE_SEND										63
#define S_EVENT_FOR_ZONE_SEND										5
#endif
//protocol(1) + tPlayUserIndex(4) + tMoveItemInfo(sizeof(MOVE_ITEM_INFO))
#define P_SET_MOVE_ITEM_FOR_ZONE_SEND                               64
#define S_SET_MOVE_ITEM_FOR_ZONE_SEND                               5 + sizeof(MOVE_ITEM_INFO)

//--------------------//
//[TOOL] -> [PLAYUSER]//
//--------------------//
//protocol(1)
#define P_TOOL_FOR_PLAYUSER_SEND									51
#define S_TOOL_FOR_PLAYUSER_SEND									1
//protocol(1)
#define P_TOOL_OK_FOR_PLAYUSER_SEND									52
#define S_TOOL_OK_FOR_PLAYUSER_SEND									1
//protocol(1) + tUserNum(4)
#define P_CHANGE_LOGIN_USER_NUM_SEND								53
#define S_CHANGE_LOGIN_USER_NUM_SEND								5
//protocol(1) + tZoneNumber(4)
#define P_CHECK_ZONE_FOR_TOOL_SEND									54
#define S_CHECK_ZONE_FOR_TOOL_SEND									5
//protocol(1) + tZoneNumber(4)
#define P_GET_PRESENT_USER_NUM_FOR_TOOL_SEND						55
#define S_GET_PRESENT_USER_NUM_FOR_TOOL_SEND						5
//protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH)
#define P_FIND_AVATAR_FOR_TOOL_SEND									56
#define S_FIND_AVATAR_FOR_TOOL_SEND									1 + MAX_AVATAR_NAME_LENGTH
//protocol(1) + tID(MAX_USER_ID_LENGTH)
#define P_FIND_USER_FOR_TOOL_SEND									57
#define S_FIND_USER_FOR_TOOL_SEND									1 + MAX_USER_ID_LENGTH
//protocol(1) + tSort(4) + tID(MAX_USER_ID_LENGTH)
#define P_BLOCK_USER_FOR_TOOL_1_SEND								58
#define S_BLOCK_USER_FOR_TOOL_1_SEND								5 + MAX_USER_ID_LENGTH
//protocol(1) + tSort(4) + tID(MAX_USER_ID_LENGTH)
#define P_BLOCK_USER_FOR_TOOL_2_SEND								59
#define S_BLOCK_USER_FOR_TOOL_2_SEND								5 + MAX_USER_ID_LENGTH
//protocol(1)
#define P_GET_PRESENT_USER_NUM_2_FOR_TOOL_SEND						60		
#define S_GET_PRESENT_USER_NUM_2_FOR_TOOL_SEND						1		
//----------------------//
//[POLICE] -> [PLAYUSER]//
//----------------------//
//protocol(1)
#define P_POLICE_FOR_PLAYUSER_SEND									61
#define S_POLICE_FOR_PLAYUSER_SEND									1
//protocol(1)
#define P_POLICE_OK_FOR_PLAYUSER_SEND								62
#define S_POLICE_OK_FOR_PLAYUSER_SEND								1
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//[SEND_PROTOCOL]
//-------------------------------------------------------------------------------------------------
//---------------------//
//[PLAYUSER] -> [LOGIN]//
//---------------------//
//protocol(1)
#define P_LOGIN_FOR_PLAYUSER_RECV									11
#define S_LOGIN_FOR_PLAYUSER_RECV									1
//protocol(1) + tResult(4) + tPlayUserIndex(4)
#define P_REGISTER_USER_FOR_LOGIN_RECV								12
#define S_REGISTER_USER_FOR_LOGIN_RECV								9
//protocol(1)
#define P_UNREGISTER_USER_FOR_LOGIN_RECV							13
#define S_UNREGISTER_USER_FOR_LOGIN_RECV							1
//protocol(1) + tPresentUserNum(4)
#define P_GET_PRESENT_USER_NUM_FOR_LOGIN_RECV						14
#define S_GET_PRESENT_USER_NUM_FOR_LOGIN_RECV						5
//protocol(1) + tResult(4)
#define P_BLOCK_USER_FOR_LOGIN_RECV									15
#define S_BLOCK_USER_FOR_LOGIN_RECV									5
//--------------------//
//[PLAYUSER] -> [ZONE]//
//--------------------//
//protocol(1)
#define P_ZONE_FOR_PLAYUSER_RECV									11
#define S_ZONE_FOR_PLAYUSER_RECV									1
//protocol(1) + tResult(4) + tPlayUserIndex(4)
#define P_REGISTER_USER_FOR_ZONE_0_RECV								12
#define S_REGISTER_USER_FOR_ZONE_0_RECV								9
//protocol(1) + tResult(4) + tUserSort(4) + tGoodFellow(4) + tLoginPlace(4) + tLoginPremium(4) + tLoginPremiumPCRoom(4) + tTraceState(4) + tBonus100Money(1) + tPremiumServerExpirationDate(4) + tAvatarInfo( sizeof( AVATAR_INFO ) ) + tEffectValue(MAX_AVATAR_EFFECT_SORT_NUM * 8) + tCheckFirstZone(4)
#define P_REGISTER_USER_FOR_ZONE_1_RECV								13
#define S_REGISTER_USER_FOR_ZONE_1_RECV								38 + sizeof( AVATAR_INFO ) + (MAX_AVATAR_EFFECT_SORT_NUM * 8) + sizeof (AUTH_INFO) + sizeof(MOVE_ITEM_INFO) // + tPremiumServerExpirationDate(4) // @_Premium_Server_@ // + sizeof(MOVE_ITEM_INFO)
//protocol(1) + tResult(4)
#define P_REGISTER_USER_FOR_ZONE_2_RECV								14
#define S_REGISTER_USER_FOR_ZONE_2_RECV								5
//protocol(1) + tResult(4)
#define P_REGISTER_USER_FOR_ZONE_3_RECV								15
#define S_REGISTER_USER_FOR_ZONE_3_RECV								5
//protocol(1)
#define P_UNREGISTER_USER_FOR_ZONE_RECV								16
#define S_UNREGISTER_USER_FOR_ZONE_RECV								1
//protocol(1) + tZoneNumber(4) + tTribe(4)
#define P_FIND_AVATAR_FOR_ZONE_RECV									17
#define S_FIND_AVATAR_FOR_ZONE_RECV									9
//protocol(1)
#define P_TRIBE_BANK_INFO_SAVE_RECV									18
#define S_TRIBE_BANK_INFO_SAVE_RECV									1
//protocol(1) + tResult(4) + tTribeBankInfo( MAX_TRIBE_BANK_SLOT_NUM * 4 )
#define P_TRIBE_BANK_INFO_VIEW_RECV									19
#define S_TRIBE_BANK_INFO_VIEW_RECV									5 + MAX_TRIBE_BANK_SLOT_NUM * 4
//protocol(1) + tResult(4) + tMoney(4)
#define P_TRIBE_BANK_INFO_LOAD_RECV									20
#define S_TRIBE_BANK_INFO_LOAD_RECV									9
//protocol(1) + tResult(4)
#define P_HACK_NAME_RECV											21
#define S_HACK_NAME_RECV											5
//protocol(1) + tResult(4)
#define P_BLOCK_USER_FOR_ZONE_RECV									22
#define S_BLOCK_USER_FOR_ZONE_RECV									5
//protocol(1) + tResult(4)
#define P_ADD_AUTO_USER_LIST_RECV									23
#define S_ADD_AUTO_USER_LIST_RECV									5
//protocol(1) + tResult(4)
#define P_CHECK_KILL_OTHER_TRIBE_RECV								24
#define S_CHECK_KILL_OTHER_TRIBE_RECV								5
//protocol(1)
#define P_EVENT_INFO_RECV											25
#define S_EVENT_INFO_RECV											1

#pragma pack (push, 1)

#define PTOZ_CHECK_AUTH_KEY_TYPE     26
struct PTOZ_CHECK_AUTH_KEY {
	PTOZ_CHECK_AUTH_KEY (void) {
		m_bMagic =  PTOZ_CHECK_AUTH_KEY_TYPE;
	}

	BYTE    m_bMagic;
	BYTE    m_bResult;
};
#define PTOZ_CHECK_AUTH_KEY_SIZE                    sizeof (PTOZ_CHECK_AUTH_KEY)

#define PTOZ_UPDATE_AUTH_KEY_TYPE       27
struct PTOZ_UPDATE_AUTH_KEY {
	PTOZ_UPDATE_AUTH_KEY (void) {
		m_bMagic = PTOZ_UPDATE_AUTH_KEY_TYPE;
	}

	BYTE        m_bMagic;
	BYTE        m_bResult;
};
#define PTOZ_UPDATE_AUTH_KEY_SIZE                   sizeof (PTOZ_UPDATE_AUTH_KEY)

#pragma pack (pop)

//protocol(1) + tResult(4)
#define P_CHANGE_AVATAR_NAME_FOR_ZONE_RECV							28
#define S_CHANGE_AVATAR_NAME_FOR_ZONE_RECV							5
//protocol(1) + tResult(4)
#define P_BONUS_100_MONEY_FOR_ZONE_RECV								29
#define S_BONUS_100_MONEY_FOR_ZONE_RECV								5

//--------------------//
//[PLAYUSER] -> [TOOL]//
//--------------------//
//protocol(1)
#define P_TOOL_FOR_PLAYUSER_RECV									11
#define S_TOOL_FOR_PLAYUSER_RECV									1
//protocol(1) + tResult(4)
#define P_CHANGE_LOGIN_USER_NUM_RECV								12
#define S_CHANGE_LOGIN_USER_NUM_RECV								5
//protocol(1) + tResult(4)
#define P_CHECK_ZONE_FOR_TOOL_RECV									13
#define S_CHECK_ZONE_FOR_TOOL_RECV									5
//protocol(1) + tPresentUserNum(4)
#define P_GET_PRESENT_USER_NUM_FOR_TOOL_RECV						14
#define S_GET_PRESENT_USER_NUM_FOR_TOOL_RECV						5
//protocol(1) + tZoneNumber(4)
#define P_FIND_AVATAR_FOR_TOOL_RECV									15
#define S_FIND_AVATAR_FOR_TOOL_RECV									5
//protocol(1) + tZoneNumber(4)
#define P_FIND_USER_FOR_TOOL_RECV									16
#define S_FIND_USER_FOR_TOOL_RECV									5
//protocol(1) + tResult(4)
#define P_BLOCK_USER_FOR_TOOL_RECV									17
#define S_BLOCK_USER_FOR_TOOL_RECV									5
//protocol(1) + tLength(4) + tBuffer(2048)
#define P_GET_PRESENT_USER_NUM_2_FOR_TOOL_RECV						18
#define S_GET_PRESENT_USER_NUM_2_FOR_TOOL_RECV						5 + 2048
//----------------------//
//[PLAYUSER] -> [POLICE]//
//----------------------//
//protocol(1)
#define P_POLICE_FOR_PLAYUSER_RECV									11
#define S_POLICE_FOR_PLAYUSER_RECV									1
//protocol(1) + tID(33) + tIP(16)
#define P_USER_INFO_FOR_POLICE										12
#define S_USER_INFO_FOR_POLICE										51
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//DEFINITION_FOR_CENTER
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//[RECV_PROTOCOL]
//-------------------------------------------------------------------------------------------------
//-------------------//
//[LOGIN] -> [CENTER]//
//-------------------//
//protocol(1)
#define P_LOGIN_FOR_CENTER_SEND										11
#define S_LOGIN_FOR_CENTER_SEND										1
//protocol(1)
#define P_LOGIN_OK_FOR_CENTER_SEND									12
#define S_LOGIN_OK_FOR_CENTER_SEND									1
//protocol(1) + tZoneNumber(4)
#define P_GET_ZONE_SERVER_INFO_1									13
#define S_GET_ZONE_SERVER_INFO_1									5

#pragma pack (push, 1)

#define LTOG_BAN_PLAYER_TYPE                                        18
struct LTOG_BAN_PLAYER {
	LTOG_BAN_PLAYER (void) {
		::ZeroMemory (this, sizeof (LTOG_BAN_PLAYER));
		m_bMagic = LTOG_BAN_PLAYER_TYPE;
	}

	BYTE        m_bMagic;
	char        m_szID[MAX_USER_ID_LENGTH];
};
#define LTOG_BAN_PLAYER_SIZE                    sizeof (LTOG_BAN_PLAYER)

#pragma pack (pop)
//------------------//
//[ZONE] -> [CENTER]//
//------------------//
//protocol(1) + tZoneNumber(4) + tPort(4)
#define P_ZONE_FOR_CENTER_SEND										31
#define S_ZONE_FOR_CENTER_SEND										9
//protocol(1)
#define P_ZONE_OK_FOR_CENTER_SEND									32
#define S_ZONE_OK_FOR_CENTER_SEND									1
//protocol(1) + tInfoSort(4) + tInfoData(MAX_BROADCAST_INFO_SIZE)
#define P_DEMAND_BROADCAST_INFO										33
#define S_DEMAND_BROADCAST_INFO										5 + MAX_BROADCAST_INFO_SIZE
//protocol(1) + tZoneNumber(4) + tResult(4) + tUserIndex(4) + tGmIndex(4)
#define P_SERCH_AVATAR_SEND											34
#define S_SERCH_AVATAR_SEND											17
//protocol(1) +tSort(4) + tResult(4) + tUserIndex(4) + tGmIndex(4)
#define P_CHECK_EVENT_SEND											35
#define S_CHECK_EVENT_SEND											17
//protocol(1)
#define P_GET_TOTAL_RANK_INFO_SEND                                  36
#define S_GET_TOTAL_RANK_INFO_SEND                                   1
//protocol(1) + aName(13) + tUserIndex(4)
#define P_GET_RANK_INFO_SEND                                        37
#define S_GET_RANK_INFO_SEND                                        1 + MAX_AVATAR_NAME_LENGTH + 4
//protocol(1) + ZoneNumber(4)
#define P_ZONE_CONNECTION_INFO_SEND                                 38
#define S_ZONE_CONNECTION_INFO_SEND                                 5
// @ Cost Info Download @
//protocol(1) + tResult(4)
#define P_UPDATE_CASH_ITEM_INFO_FOR_CENTER                          39
#define S_UPDATE_CASH_ITEM_INFO_FOR_CENTER                          5
// @

//------------------//
//[TOOL] -> [CENTER]//
//------------------//
//protocol(1)
#define P_TOOL_FOR_CENTER_SEND										51
#define S_TOOL_FOR_CENTER_SEND										1
//protocol(1)
#define P_TOOL_OK_FOR_CENTER_SEND									52
#define S_TOOL_OK_FOR_CENTER_SEND									1
//protocol(1)
#define P_DEMAND_START_FOR_TOOL										53
#define S_DEMAND_START_FOR_TOOL										1
//protocol(1) + tContent(MAX_CHAT_CONTENT_LENGTH) + tZoneNumber(4) + tTribe(4)
#define P_DEMAND_NOTICE_FOR_TOOL									54
#define S_DEMAND_NOTICE_FOR_TOOL									9 + MAX_CHAT_CONTENT_LENGTH
//protocol(1) + tEventSort(4) + tEventValue(4) + tZoneNumber(4)
#define P_DEMAND_SET_EVENT_FOR_TOOL									55
#define S_DEMAND_SET_EVENT_FOR_TOOL									13
//protocol(1)
#define P_DEMAND_SHUTDOWN_FOR_TOOL									56
#define S_DEMAND_SHUTDOWN_FOR_TOOL									1
//protocol(1) + tEventSort(4) + tZoneNumber(4) + tMoveZoneNumber(4) + tAvatarName01(13)
#define P_DEMAND_SET_GM_ORDER_FOR_GMTOOL							57
#define S_DEMAND_SET_GM_ORDER_FOR_GMTOOL							25
//protocol(1) + tAvatarName01(13) + tGmIndex(4)
#define P_DEMAND_SERCH_AVATAR_FOR_GMTOOL							58
#define S_DEMAND_SERCH_AVATAR_FOR_GMTOOL							18
//protocol(1) + tZoneNumber(4) + AvatarName01(13) + tPosX(4) + tPosY(4) + tPosZ(4)
#define P_DEMAND_SET_GM_ORDER_FOR_GMTOOL_MOVE_AVATAR				59
#define S_DEMAND_SET_GM_ORDER_FOR_GMTOOL_MOVE_AVATAR				30
//protocol(1) + tEventSort(4) + tGmIndex(4)
#define P_DEMAND_CHECK_EVENT_FOR_TOOL									60
#define S_DEMAND_CHECK_EVENT_FOR_TOOL									9
// # X-Trap # {
//protocol(1)
#define P_XTRAP_MAP_FILE_CHANGE_FOR_CENTER                           64
#define S_XTRAP_MAP_FILE_CHANGE_FOR_CENTER                           1
// # }

//-----------------------//
//[CHAT_TOOL] -> [CENTER]//
//-----------------------//
//protocol(1)
#define P_CHAT_TOOL_FOR_CENTER_SEND									14
#define S_CHAT_TOOL_FOR_CENTER_SEND									1
//protocol(1)
#define P_CHAT_TOOL_OK_FOR_CENTER_SEND								15
#define S_CHAT_TOOL_OK_FOR_CENTER_SEND								1
//protocol(1) + tZoneNumber(4) + tTribe(4) + tAvatarName01(13) + tAvatarName02(13) + tContent(51)
#define P_TRIBE_CHAT_FOR_CHAT_TOOL_SEND								16
#define S_TRIBE_CHAT_FOR_CHAT_TOOL_SEND								86
//protocol(1) + tZoneNumber(4) + tTribe(4) + tAvatarName01(13) + tAvatarName02(13) + tContent(51)
#define P_SECRET_CHAT_FOR_CHAT_TOOL_SEND							17
#define S_SECRET_CHAT_FOR_CHAT_TOOL_SEND							86
//--------------------//
//[POLICE] -> [CENTER]//
//--------------------//
//protocol(1)
#define P_POLICE_FOR_CENTER_SEND									61
#define S_POLICE_FOR_CENTER_SEND									1
//protocol(1)
#define P_POLICE_OK_FOR_CENTER_SEND									62
#define S_POLICE_OK_FOR_CENTER_SEND									1
//protocol(1) + tID(33) + tLoginTime(4) + tLogoutTime(4)
#define P_POLICE_INFO_FOR_CENTER_SEND								63
#define S_POLICE_INFO_FOR_CENTER_SEND								42
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//[SEND_PROTOCOL]
//-------------------------------------------------------------------------------------------------
//-------------------//
//[CENTER] -> [LOGIN]//
//-------------------//
//protocol(1)
#define P_LOGIN_FOR_CENTER_RECV										11
#define S_LOGIN_FOR_CENTER_RECV										1
//protocol(1) + tResult(4) + tIP(16) + tPort(4)
#define P_GET_ZONE_SERVER_INFO_1_RESULT								12
#define S_GET_ZONE_SERVER_INFO_1_RESULT								25

#pragma pack (push, 1)

#define GTOL_BAN_PLAYER_TYPE                    13
struct GTOL_BAN_PLAYER {
	GTOL_BAN_PLAYER (void) {
		::ZeroMemory (this, sizeof (GTOL_BAN_PLAYER));
		m_bMagic = GTOL_BAN_PLAYER_TYPE;
	}

	BYTE            m_bMagic;
	char            m_szID[MAX_USER_ID_LENGTH];
};
#define GTOL_BAN_PLAYER_SIZE                    sizeof (GTOL_BAN_PLAYER)

#pragma pack (pop)
//------------------//
//[CENTER] -> [ZONE]//
//------------------//
//protocol(1)
#define P_ZONE_FOR_CENTER_RECV										11
#define S_ZONE_FOR_CENTER_RECV										1
//protocol(1) + tZoneConnectionInfo( sizeof( ZONE_CONNECTION_INFO ) )
#define P_TOTAL_ZONE_CONNECTION_INFO								12
#define S_TOTAL_ZONE_CONNECTION_INFO								1 + sizeof( ZONE_CONNECTION_INFO )
//protocol(1) + tWorldInfo( sizeof( WORLD_INFO ) ) + tTribeInfo( sizeof( TRIBE_INFO ) )
#define P_WORLD_INFO												13
#define S_WORLD_INFO												1 + sizeof( WORLD_INFO ) + sizeof( TRIBE_INFO )
//protocol(1) + tZoneNumber(4) + tIP(16) + tPort(4)
#define P_ZONE_CONNECTION_INFO										14
#define S_ZONE_CONNECTION_INFO										25
//protocol(1) + tInfoSort(4) + tInfoData(MAX_BROADCAST_INFO_SIZE)
#define P_BROADCAST_INFO											15
#define S_BROADCAST_INFO											5 + MAX_BROADCAST_INFO_SIZE
//protocol(1)
#define P_START														16
#define S_START														1
//protocol(1) + tContent(MAX_CHAT_CONTENT_LENGTH) + tTribe(4)
#define P_NOTICE													17
#define S_NOTICE													5 + MAX_CHAT_CONTENT_LENGTH
//protocol(1) + tEventSort(4) + tEventValue(4)
#define P_SET_EVENT													18
#define S_SET_EVENT													9
//protocol(1)
#define P_SHUTDOWN													19
#define S_SHUTDOWN													1
//protocol(1) + tZoneNumber(4) + tTribe(4) + tAvatarName01(13) + tAvatarName02(13) + tContent(51)
#define P_TRIBE_CHAT												20
#define S_TRIBE_CHAT												86
//protocol(1) + tZoneNumber(4) + tTribe(4) + tAvatarName01(13) + tAvatarName02(13) + tContent(51)
#define P_SECRET_CHAT												21
#define S_SECRET_CHAT												86
//protocol(1) + tID(33) + tLoginTime(4) + tLogoutTime(4)
#define P_POLICE_INFO												22
#define S_POLICE_INFO												42
//protocol(1) + tEventSort(4) + tMoveZoneNumber(4) + tAvatarName01(13)
#define P_SET_GM_ORDER												23
#define S_SET_GM_ORDER												21		
//protocol(1) + tAvatarName01(13) + tUserIndex(4) + tGmIndex(4)
#define P_SERCH_AVATAR												24
#define S_SERCH_AVATAR												22
//protocol(1) + tAvatarName01(13) + tPosX(4) + tPosY(4) + tPosZ(4) +
#define P_SET_GM_ORDER_MOVE_AVATAR									25
#define S_SET_GM_ORDER_MOVE_AVATAR									26

#pragma pack (push, 1)

#define GTOZ_BAN_PLAYER_TYPE                    26
struct GTOZ_BAN_PLAYER {
	GTOZ_BAN_PLAYER (void) {
		::ZeroMemory (this, sizeof (GTOZ_BAN_PLAYER));
		m_bMagic = GTOZ_BAN_PLAYER_TYPE;
	}

	BYTE                m_bMagic;
	char                m_szID[MAX_USER_ID_LENGTH];
};
#define GTOZ_BAN_PLAYER_SIZE                    sizeof (GTOZ_BAN_PLAYER)

#pragma pack (pop)

//protocol(1) + tEventSort(4) + tUserIndex(4) + tGmIndex(4)
#define P_CHECK_EVENT											    27
#define S_CHECK_EVENT											    13
#define P_TOTAL_RANK_INFO_RECV                                      28
#define S_TOTAL_RANK_INFO_RECV                                      0
//protocol(1) + sizeof(rank_info_t) + tUserIndex(4) 
#define P_RANK_INFO_RECV                                            29
#define S_RANK_INFO_RECV                                            1 + sizeof(rank_info_t) + 4
// # X-Trap # {
//protocol(1)
#define P_XTRAP_MAP_FILE_CHANGE_FOR_ZONE                            30
#define S_XTRAP_MAP_FILE_CHANGE_FOR_ZONE                            1
// # }
// @ Cost Info Download @
//protocol(1) + tResult(4)
#define P_UPDATE_CASH_ITEM_INFO_FOR_ZONE                            31
#define S_UPDATE_CASH_ITEM_INFO_FOR_ZONE                            5
// @


//------------------//
//[CENTER] -> [TOOL]//
//------------------//
//protocol(1)
#define P_TOOL_FOR_CENTER_RECV										11
#define S_TOOL_FOR_CENTER_RECV										1
//protocol(1)
#define P_TOOL_DEMAND_RESULT										12
#define S_TOOL_DEMAND_RESULT										1
//protocol(1) + tZoneNumber(4) + tGmIndex(4)
#define P_TOOL_SERCH_AVATAR_RESULT									13
#define S_TOOL_SERCH_AVATAR_RESULT									9
//protocol(1) + tGmIndex(4) + tEventSort(4) + tResult(4) + tWorldNumber(4) + tZoneNumber(4)
#define P_TOOL_CHECK_EVENT_RESULT									14
#define S_TOOL_CHECK_EVENT_RESULT									21
//-----------------------//
//[CENTER] -> [CHAT_TOOL]//
//-----------------------//
//protocol(1)
#define P_CHAT_TOOL_FOR_CENTER_RECV									11
#define S_CHAT_TOOL_FOR_CENTER_RECV									1
//--------------------//
//[CENTER] -> [POLICE]//
//--------------------//
//protocol(1)
#define P_POLICE_FOR_CENTER_RECV									11
#define S_POLICE_FOR_CENTER_RECV									1
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//DEFINITION_FOR_RELAY
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//[RECV_PROTOCOL]
//-------------------------------------------------------------------------------------------------
//-----------------//
//[ZONE] -> [RELAY]//
//-----------------//
//protocol(1) + tZoneNumber(4)
#define P_ZONE_FOR_RELAY_SEND										31
#define S_ZONE_FOR_RELAY_SEND										5
//protocol(1)
#define P_ZONE_OK_FOR_RELAY_SEND									32
#define S_ZONE_OK_FOR_RELAY_SEND									1
//protocol(1) + tSort(4) + tData(MAX_BROADCAST_DATA_SIZE)
#define P_DEMAND_BROADCAST_DATA										33
#define S_DEMAND_BROADCAST_DATA										5 + MAX_BROADCAST_DATA_SIZE
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//[SEND_PROTOCOL]
//-------------------------------------------------------------------------------------------------
//-----------------//
//[RELAY] -> [ZONE]//
//-----------------//
//protocol(1)
#define P_ZONE_FOR_RELAY_RECV										11
#define S_ZONE_FOR_RELAY_RECV										1
//protocol(1) + tSort(4) + tData(MAX_BROADCAST_DATA_SIZE)
#define P_BROADCAST_DATA											12
#define S_BROADCAST_DATA											5 + MAX_BROADCAST_DATA_SIZE
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//DEFINITION_FOR_EXTRA
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//[RECV_PROTOCOL]
//-------------------------------------------------------------------------------------------------
//-----------------//
//[ZONE] -> [EXTRA]//
//-----------------//
//protocol(1) + tZoneNumber(4)
#define P_ZONE_FOR_EXTRA_SEND										31
#define S_ZONE_FOR_EXTRA_SEND										5
//protocol(1)
#define P_ZONE_OK_FOR_EXTRA_SEND									32
#define S_ZONE_OK_FOR_EXTRA_SEND									1
//protocol(1) + tSort(4) + tData(MAX_GUILD_WORK_SIZE)
#define P_GUILD_WORK_FOR_EXTRA_SEND									33
#define S_GUILD_WORK_FOR_EXTRA_SEND									5 + MAX_GUILD_WORK_SIZE
//protocol(1) + tID(MAX_USER_ID_LENGTH)
#define P_GET_CASH_SIZE_FOR_EXTRA_SEND								34
#define S_GET_CASH_SIZE_FOR_EXTRA_SEND								1 + MAX_USER_ID_LENGTH
// @ Cost Info Download @
//S_BUY_CASH_ITEM_FOR_EXTRA_SEND 사이즈 변경 - tVersion(4) 추가.
//protocol(1) + tID(MAX_USER_ID_LENGTH) + tCostInfoIndex(4) + iIndex(4) + iQuantity(4) + tAvatarName(MAX_AVATAR_NAME_LENGTH) + tTribe(4) + tLevel(4) + tZoneNumber(4) + tVersion(4)
#define P_BUY_CASH_ITEM_FOR_EXTRA_SEND								35
#define S_BUY_CASH_ITEM_FOR_EXTRA_SEND								21 + MAX_USER_ID_LENGTH + MAX_AVATAR_NAME_LENGTH + 4 + 4
//protocol(1)
#define P_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_SEND                      36
#define S_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_SEND                      1
//protocol(1) + tZoneNumber(4)
#define P_GET_CASH_ITEM_INFO_FOR_EXTRA_SEND                         37
#define S_GET_CASH_ITEM_INFO_FOR_EXTRA_SEND                         5
// @
//protocol(1) + tID(MAX_USER_ID_LENGTH) + iIndex(4) + tAvatarName(MAX_AVATAR_NAME_LENGTH) + tZoneNumber(4)
#define P_USE_PACKAGE_ITEM_FOR_EXTRA_SEND                           38
#define S_USE_PACKAGE_ITEM_FOR_EXTRA_SEND                           9 + MAX_USER_ID_LENGTH + MAX_AVATAR_NAME_LENGTH
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//[SEND_PROTOCOL]
//-------------------------------------------------------------------------------------------------
//-----------------//
//[EXTRA] -> [ZONE]//
//-----------------//
// @ Cost Info Download @
// S_ZONE_FOR_EXTRA_RECV 사이즈 변경 1 --> 5 + MAX_CASH_ITEM_INFO_SIZE
//protocol(1) + tVersion(4) + MAX_CASH_ITEM_INFO_SIZE
#define P_ZONE_FOR_EXTRA_RECV										11
#define S_ZONE_FOR_EXTRA_RECV										5 + MAX_CASH_ITEM_INFO_SIZE
// @
//protocol(1) + tResult(4) + tGuildInfo( sizeof( GUILD_INFO ) )
#define P_GUILD_WORK_FOR_EXTRA_RECV									12
#define S_GUILD_WORK_FOR_EXTRA_RECV									5 + sizeof( GUILD_INFO )
//protocol(1) + tCashSize(4) + tBonusCashSize(4)
#define P_GET_CASH_SIZE_FOR_EXTRA_RECV								13
#define S_GET_CASH_SIZE_FOR_EXTRA_RECV								9
//protocol(1) + tResult(4) + tCashSize(4) + tBonusCashSize(4)
#define P_BUY_CASH_ITEM_FOR_EXTRA_RECV								14
#define S_BUY_CASH_ITEM_FOR_EXTRA_RECV								9 + 4 + 4 + 4
// @ Cost Info Download @
//protocol(1) + tResult(4)
#define P_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_RECV                      15
#define S_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_RECV                      5
//protocol(1) + tResult(4) + tVersion(4) + tCashItemInfo(MAX_CASH_ITEM_INFO_SIZE)
#define P_GET_CASH_ITEM_INFO_FOR_EXTRA_RECV                         16
#define S_GET_CASH_ITEM_INFO_FOR_EXTRA_RECV                         9 + MAX_CASH_ITEM_INFO_SIZE
// @
//protocol(1) + tResult(4)
#define P_USE_PACKAGE_ITEM_FOR_EXTRA_RECV                           17
#define S_USE_PACKAGE_ITEM_FOR_EXTRA_RECV                           5
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//DEFINITION_FOR_LOGIN
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//[RECV_PROTOCOL]
//-------------------------------------------------------------------------------------------------
//-------------------//
//[CLIENT] -> [LOGIN]//
//-------------------//
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tID(MAX_USER_ID_LENGTH) + tPassword(MAX_USER_PASSWORD_LENGTH) + tVersion(4)
#define P_LOGIN_SEND												11
#define S_LOGIN_SEND												13 + MAX_USER_ID_LENGTH + MAX_USER_PASSWORD_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1)
#define P_CLIENT_OK_FOR_LOGIN_SEND									12
#define S_CLIENT_OK_FOR_LOGIN_SEND									9
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tMousePassword(MAX_MOUSE_PASSWORD_LENGTH)
#define P_CREATE_MOUSE_PASSWORD_SEND								13
#define S_CREATE_MOUSE_PASSWORD_SEND								9 + MAX_MOUSE_PASSWORD_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tMousePassword(MAX_MOUSE_PASSWORD_LENGTH) + tChangeMousePassword(MAX_MOUSE_PASSWORD_LENGTH)
#define P_CHANGE_MOUSE_PASSWORD_SEND								14
#define S_CHANGE_MOUSE_PASSWORD_SEND								9 + MAX_MOUSE_PASSWORD_LENGTH + MAX_MOUSE_PASSWORD_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tMousePasswordInput(MAX_MOUSE_PASSWORD_LENGTH)
#define P_LOGIN_MOUSE_PASSWORD_SEND									15
#define S_LOGIN_MOUSE_PASSWORD_SEND									9 + MAX_MOUSE_PASSWORD_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tSecretCardInput01(3) + tSecretCardInput02(3)
#define P_LOGIN_SECRET_CARD_SEND									16
#define S_LOGIN_SECRET_CARD_SEND									15
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tAvatarPost(4) + tAvatarInfo( sizeof( AVATAR_INFO ) )
#define P_CREATE_AVATAR_SEND										17
#define S_CREATE_AVATAR_SEND										13 + sizeof( AVATAR_INFO )
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tAvatarPost(4)
#define P_DELETE_AVATAR_SEND										18
#define S_DELETE_AVATAR_SEND										13
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tAvatarPost(4) + tChangeAvatarName(MAX_AVATAR_NAME_LENGTH) + tPage(4) + tIndex(4)
#define P_CHANGE_AVATAR_NAME_SEND									19
#define S_CHANGE_AVATAR_NAME_SEND									21 + MAX_AVATAR_NAME_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tCardNumber(MAX_USER_CARD_NUMBER_LENGTH)
#define P_DEMAND_GIFT_SEND											20
#define S_DEMAND_GIFT_SEND											9 + MAX_USER_CARD_NUMBER_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tGiftInfoindex(4)
#define P_WANT_GIFT_SEND											21
#define S_WANT_GIFT_SEND											13
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tAvatarPost(4)
#define P_DEMAND_ZONE_SERVER_INFO_1									22
#define S_DEMAND_ZONE_SERVER_INFO_1									13
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1)
#define P_FAIL_MOVE_ZONE_1_SEND										23
#define S_FAIL_MOVE_ZONE_1_SEND										9
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1)
#define P_RECOMMAND_WORLD_SEND                                      24
#define S_RECOMMAND_WORLD_SEND                                      9                
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//[SEND_PROTOCOL]
//-------------------------------------------------------------------------------------------------
//-------------------//
//[LOGIN] -> [CLIENT]//
//-------------------//
//protocol(1) + tResult(4) + tID(MAX_USER_ID_LENGTH) + tUserSort(4) + tGoodFellow(4) + tLoginPlace(4) + tLoginPremium(4) + tLoginPremiumPCRoom(4) + tSecondLoginSort(4) + tMousePassword(MAX_MOUSE_PASSWORD_LENGTH) + tSecretCardIndex01(4) + tSecretCardIndex02(4) + tFirstLogin(1)
#define P_LOGIN_RECV												11
#define S_LOGIN_RECV												37 + MAX_USER_ID_LENGTH + MAX_MOUSE_PASSWORD_LENGTH
//protocol(1) + tAvatarInfo( sizeof( AVATAR_INFO ) )
#define P_USER_AVATAR_INFO											12
#define S_USER_AVATAR_INFO											1 + sizeof( AVATAR_INFO )
//protocol(1) + tResult(4) + tMousePassword(MAX_MOUSE_PASSWORD_LENGTH)
#define P_CREATE_MOUSE_PASSWORD_RECV								13
#define S_CREATE_MOUSE_PASSWORD_RECV								5 + MAX_MOUSE_PASSWORD_LENGTH
//protocol(1) + tResult(4) + tMousePassword(MAX_MOUSE_PASSWORD_LENGTH)
#define P_CHANGE_MOUSE_PASSWORD_RECV								14
#define S_CHANGE_MOUSE_PASSWORD_RECV								5 + MAX_MOUSE_PASSWORD_LENGTH
//protocol(1) + tResult(4)
#define P_LOGIN_MOUSE_PASSWORD_RECV									15
#define S_LOGIN_MOUSE_PASSWORD_RECV									5
//protocol(1) + tResult(4)
#define P_LOGIN_SECRET_CARD_RECV									16
#define S_LOGIN_SECRET_CARD_RECV									5
//protocol(1) + tResult(4) + tAvatarInfo( sizeof( AVATAR_INFO ) )
#define P_CREATE_AVATAR_RECV										17
#define S_CREATE_AVATAR_RECV										5 + sizeof( AVATAR_INFO )
//protocol(1) + tResult(4)
#define P_DELETE_AVATAR_RECV										18
#define S_DELETE_AVATAR_RECV										5
//protocol(1) + tResult(4)
#define P_CHANGE_AVATAR_NAME_RECV									19
#define S_CHANGE_AVATAR_NAME_RECV									5
//protocol(1) + tResult(4) + tGiftInfo(40)
#define P_DEMAND_GIFT_RECV											20
#define S_DEMAND_GIFT_RECV											45
//protocol(1) + tResult(4)
#define P_WANT_GIFT_RECV											21
#define S_WANT_GIFT_RECV											5
//protocol(1) + tResult(4) + tIP(16) + tPort(4)
#define P_DEMAND_ZONE_SERVER_INFO_1_RESULT							22
#define S_DEMAND_ZONE_SERVER_INFO_1_RESULT							25
//protocol(1) + island_1(1) + partition_1(1) + world_1(1) + island_2(1) + partition_2(1) + world_2(1) + island_3(1) + partition_3(1) + world_3(1) + island_4(1) + partition_4(1) + world_4(1)
#define P_RECOMMAND_WORLD_RECV                                      23
#define S_RECOMMAND_WORLD_RECV                                      13               
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//DEFINITION_FOR_ZONE
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//[RECV_PROTOCOL]
//-------------------------------------------------------------------------------------------------
//------------------//
//[CLIENT] -> [ZONE]//
//------------------//
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tID(MAX_USER_ID_LENGTH) + tribe(4)
#define P_TEMP_REGISTER_SEND										11
#define S_TEMP_REGISTER_SEND										13 + MAX_USER_ID_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tID(MAX_USER_ID_LENGTH) + tAvatarName(MAX_AVATAR_NAME_LENGTH) + tAction( sizeof( ACTION_INFO ) )
#define P_REGISTER_AVATAR_SEND										12
#define S_REGISTER_AVATAR_SEND										9 + MAX_USER_ID_LENGTH + MAX_AVATAR_NAME_LENGTH + sizeof( ACTION_INFO )
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tTribe(4)
#define P_CLIENT_OK_FOR_ZONE_SEND									13
#define S_CLIENT_OK_FOR_ZONE_SEND									13
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tAnswer(4)
#define P_AUTO_CHECK_ASK_RECV										14
#define S_AUTO_CHECK_ASK_RECV										13
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tAction( sizeof( ACTION_INFO ) )
#define P_AVATAR_ACTION_SEND										15
#define S_AVATAR_ACTION_SEND										9 + sizeof( ACTION_INFO )
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tAction( sizeof( ACTION_INFO ) )
#define P_UPDATE_AVATAR_ACTION										16
#define S_UPDATE_AVATAR_ACTION										9 + sizeof( ACTION_INFO )
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tContent(MAX_CHAT_CONTENT_LENGTH)
#define P_GENERAL_NOTICE_SEND										17
#define S_GENERAL_NOTICE_SEND										9 + MAX_CHAT_CONTENT_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tAttackInfo( sizeof( ATTACK_FOR_PROTOCOL ) )
#define P_PROCESS_ATTACK_SEND										18
#define S_PROCESS_ATTACK_SEND										9 + sizeof( ATTACK_FOR_PROTOCOL )
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tSort(4) + tData(MAX_BROADCAST_DATA_SIZE)
#define P_PROCESS_DATA_SEND											19
#define S_PROCESS_DATA_SEND											13 + MAX_BROADCAST_DATA_SIZE
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tSort(4) + tZoneNumber(4)
#define P_DEMAND_ZONE_SERVER_INFO_2									20
#define S_DEMAND_ZONE_SERVER_INFO_2									17
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1)
#define P_FAIL_MOVE_ZONE_2_SEND										21
#define S_FAIL_MOVE_ZONE_2_SEND										9
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tPage(4) + tIndex(4)
#define P_USE_HOTKEY_ITEM_SEND										22
#define S_USE_HOTKEY_ITEM_SEND										17
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tPage(4) + tIndex(4) + tValue(4) +bParam_1(1)+bParam_2(1)
#define P_USE_INVENTORY_ITEM_SEND									23
#define S_USE_INVENTORY_ITEM_SEND									23
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tPage1(4) + tIndex1(4) + tPage2(4) + tIndex2(4)
#define P_IMPROVE_ITEM_SEND											24
#define S_IMPROVE_ITEM_SEND											25
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tPage1(4) + tIndex1(4) + tPage2(4) + tIndex2(4)
#define P_ADD_ITEM_SEND												25
#define S_ADD_ITEM_SEND												25
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tPage(4) + tIndex(4)
#define P_EXCHANGE_ITEM_SEND										26
#define S_EXCHANGE_ITEM_SEND										17
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tPage1(4) + tIndex1(4) + tPage2(4) + tIndex2(4)
#define P_HIGH_ITEM_SEND											27
#define S_HIGH_ITEM_SEND											25
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tPage1(4) + tIndex1(4) + tPage2(4) + tIndex2(4)
#define P_LOW_ITEM_SEND												28
#define S_LOW_ITEM_SEND												25
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tSort(4) + tPage1(4) + tIndex1(4) + tPage2(4) + tIndex2(4) + tPage3(4) + tIndex3(4) + tPage4(4) + tIndex4(4)
#define P_MAKE_ITEM_SEND											29
#define S_MAKE_ITEM_SEND											45
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tSort(4) + tPage1(4) + tIndex1(4) + tPage2(4) + tIndex2(4) + tPage3(4) + tIndex3(4) + tPage4(4) + tIndex4(4)
#define P_MAKE_SKILL_SEND											30
#define S_MAKE_SKILL_SEND											45
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tPShopInfo( sizeof( PSHOP_INFO ) )
#define P_START_PSHOP_SEND											31
#define S_START_PSHOP_SEND											9 + sizeof( PSHOP_INFO )
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1)
#define P_END_PSHOP_SEND											32
#define S_END_PSHOP_SEND											9
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH)
#define P_DEMAND_PSHOP_SEND											33
#define S_DEMAND_PSHOP_SEND											9 + MAX_AVATAR_NAME_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tSort1(4) + tSort2(4)
#define P_PSHOP_ITEM_INFO_SEND										34
#define S_PSHOP_ITEM_INFO_SEND										17
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tUniqueNumber(4) + tAvatarName(MAX_AVATAR_NAME_LENGTH) + tPage1(4) + tIndex1(4) + tQuantity1(4) + tPage2(4) + tIndex2(4) + tXPost2(4) + tYPost2(4)
#define P_BUY_PSHOP_SEND											35
#define S_BUY_PSHOP_SEND											41 + MAX_AVATAR_NAME_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tSort(4) + tPage(4) + tIndex(4) + tXPost(4) + tYPost(4)
#define P_PROCESS_QUEST_SEND										36
#define S_PROCESS_QUEST_SEND										29
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1)
#define P_CHANGE_TO_TRIBE4_SEND										37
#define S_CHANGE_TO_TRIBE4_SEND										9
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tContent(MAX_CHAT_CONTENT_LENGTH)
#define P_GENERAL_CHAT_SEND											38
#define S_GENERAL_CHAT_SEND											9 + MAX_CHAT_CONTENT_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH) + tContent(MAX_CHAT_CONTENT_LENGTH)
#define P_SECRET_CHAT_SEND											39
#define S_SECRET_CHAT_SEND											9 + MAX_AVATAR_NAME_LENGTH + MAX_CHAT_CONTENT_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tContent(MAX_CHAT_CONTENT_LENGTH)
#define P_GENERAL_SHOUT_SEND										40
#define S_GENERAL_SHOUT_SEND										9 + MAX_CHAT_CONTENT_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1)
#define P_GET_CASH_SIZE_SEND										41
#define S_GET_CASH_SIZE_SEND										9
// @ Cost Info Download @
// S_BUY_CASH_ITEM_SEND 사이즈 변경 45 --> 49 (tVersion 포함)
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tCostInfoIndex(4) + tPage(4) + tIndex(4) + tValue(24) + tVersion(4)
#define P_BUY_CASH_ITEM_SEND										42
#define S_BUY_CASH_ITEM_SEND										49
// @
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH) + tSort(4)
#define P_DUEL_ASK_SEND												43
#define S_DUEL_ASK_SEND												13 + MAX_AVATAR_NAME_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1)
#define P_DUEL_CANCEL_SEND											44
#define S_DUEL_CANCEL_SEND											9
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tAnswer(4)
#define P_DUEL_ANSWER_SEND											45
#define S_DUEL_ANSWER_SEND											13
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1)
#define P_DUEL_START_SEND											46
#define S_DUEL_START_SEND											9
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH)
#define P_TRADE_ASK_SEND											47
#define S_TRADE_ASK_SEND											9 + MAX_AVATAR_NAME_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1)
#define P_TRADE_CANCEL_SEND											48
#define S_TRADE_CANCEL_SEND											9
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tAnswer(4)
#define P_TRADE_ANSWER_SEND											49
#define S_TRADE_ANSWER_SEND											13
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1)
#define P_TRADE_START_SEND											50
#define S_TRADE_START_SEND											9
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1)
#define P_TRADE_MENU_SEND											51
#define S_TRADE_MENU_SEND											9
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1)
#define P_TRADE_END_SEND											52
#define S_TRADE_END_SEND											9
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH)
#define P_FRIEND_ASK_SEND											53
#define S_FRIEND_ASK_SEND											9 + MAX_AVATAR_NAME_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1)
#define P_FRIEND_CANCEL_SEND										54
#define S_FRIEND_CANCEL_SEND										9
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tAnswer(4)
#define P_FRIEND_ANSWER_SEND										55
#define S_FRIEND_ANSWER_SEND										13
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tIndex(4)
#define P_FRIEND_MAKE_SEND											56
#define S_FRIEND_MAKE_SEND											13
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tIndex(4)
#define P_FRIEND_FIND_SEND											57
#define S_FRIEND_FIND_SEND											13 
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tIndex(4)
#define P_FRIEND_DELETE_SEND										58
#define S_FRIEND_DELETE_SEND										13
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH)
#define P_TEACHER_ASK_SEND											59
#define S_TEACHER_ASK_SEND											9 + MAX_AVATAR_NAME_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1)
#define P_TEACHER_CANCEL_SEND										60
#define S_TEACHER_CANCEL_SEND										9
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tAnswer(4)
#define P_TEACHER_ANSWER_SEND										61
#define S_TEACHER_ANSWER_SEND										13
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1)
#define P_TEACHER_START_SEND										62
#define S_TEACHER_START_SEND										9
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1)
#define P_TEACHER_END_SEND											63
#define S_TEACHER_END_SEND											9
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1)
#define P_TEACHER_STATE_SEND										64
#define S_TEACHER_STATE_SEND										9
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH)
#define P_PARTY_ASK_SEND											65
#define S_PARTY_ASK_SEND											9 + MAX_AVATAR_NAME_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1)
#define P_PARTY_CANCEL_SEND											66
#define S_PARTY_CANCEL_SEND											9
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tAnswer(4)
#define P_PARTY_ANSWER_SEND											67
#define S_PARTY_ANSWER_SEND											13
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1)
#define P_PARTY_MAKE_SEND											68
#define S_PARTY_MAKE_SEND											9
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1)
#define P_PARTY_JOIN_SEND											69
#define S_PARTY_JOIN_SEND											9
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tContent(MAX_CHAT_CONTENT_LENGTH)
#define P_PARTY_CHAT_SEND											70
#define S_PARTY_CHAT_SEND											9 + MAX_CHAT_CONTENT_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1)
#define P_PARTY_LEAVE_SEND											71
#define S_PARTY_LEAVE_SEND											9
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH)
#define P_PARTY_EXILE_SEND											72
#define S_PARTY_EXILE_SEND											9 + MAX_AVATAR_NAME_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tValue(4) + tPartyName(MAX_PARTY_NAME_LENGTH) + tAvatarName(MAX_AVATAR_NAME_LENGTH)
//#define P_PARTY_OUT_INFO_SEND										73
//#define S_PARTY_OUT_INFO_SEND										13 + MAX_PARTY_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tAvatarName01(MAX_AVATAR_NAME_LENGTH) + tAvatarName02(MAX_AVATAR_NAME_LENGTH) + tAvatarName03(MAX_AVATAR_NAME_LENGTH) + tAvatarName04(MAX_AVATAR_NAME_LENGTH) + tAvatarName05(MAX_AVATAR_NAME_LENGTH)
#define P_PARTY_INFO_SEND											73
#define S_PARTY_INFO_SEND											9 + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH)
#define P_PARTY_BREAK_SEND											74
#define S_PARTY_BREAK_SEND											9 + MAX_AVATAR_NAME_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH)
#define P_GUILD_ASK_SEND											75
#define S_GUILD_ASK_SEND											9 + MAX_AVATAR_NAME_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1)
#define P_GUILD_CANCEL_SEND											76
#define S_GUILD_CANCEL_SEND											9
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tAnswer(4)
#define P_GUILD_ANSWER_SEND											77
#define S_GUILD_ANSWER_SEND											13
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tSort(4) + tData(MAX_GUILD_WORK_SIZE)
#define P_GUILD_WORK_SEND											78
#define S_GUILD_WORK_SEND											13 + MAX_GUILD_WORK_SIZE
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tContent(MAX_CHAT_CONTENT_LENGTH)
#define P_GUILD_NOTICE_SEND											79
#define S_GUILD_NOTICE_SEND											9 + MAX_CHAT_CONTENT_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tContent(MAX_CHAT_CONTENT_LENGTH)
#define P_GUILD_CHAT_SEND											80
#define S_GUILD_CHAT_SEND											9 + MAX_CHAT_CONTENT_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH)
#define P_GUILD_FIND_SEND											81
#define S_GUILD_FIND_SEND											9 + MAX_AVATAR_NAME_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tSort(4) + tData(MAX_TRIBE_WORK_SIZE)
#define P_TRIBE_WORK_SEND											82
#define S_TRIBE_WORK_SEND											13 + MAX_TRIBE_WORK_SIZE
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tContent(MAX_CHAT_CONTENT_LENGTH)
#define P_TRIBE_NOTICE_SEND											83
#define S_TRIBE_NOTICE_SEND											9 + MAX_CHAT_CONTENT_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tContent(MAX_CHAT_CONTENT_LENGTH)
#define P_TRIBE_CHAT_SEND											84
#define S_TRIBE_CHAT_SEND											9 + MAX_CHAT_CONTENT_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tSort(4) + tValue(4)
#define P_TRIBE_BANK_SEND											85
#define S_TRIBE_BANK_SEND											17
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tSort(4) + tValue(4)
#define P_TRIBE_VOTE_SEND											86
#define S_TRIBE_VOTE_SEND											17
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tHackName(MAX_HACK_NAME_LENGTH) + tHackSize(4)
#define P_CHECK_HACK_INFO											87
#define S_CHECK_HACK_INFO											13 + MAX_HACK_NAME_LENGTH
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tValue( sizeof( GG_AUTH_DATA ) )
#define P_CHECK_N_PROTECT_2											88
#define S_CHECK_N_PROTECT_2											9 + sizeof( GG_AUTH_DATA )


#pragma pack (push, 1)

union U_RANDOM_AND_ENCRYPT_MAGIC {
	int     m_iRandom;
	char    m_iEncrypt[4];
} ;

#define CTOZ_CHECK_AUTH_KEY_TYPE            89
struct CTOZ_CHECK_AUTH_KEY {
	CTOZ_CHECK_AUTH_KEY (void) {
		m_bMagic =  CTOZ_CHECK_AUTH_KEY_TYPE;
	}

	int                         m_iRandom1;
	U_RANDOM_AND_ENCRYPT_MAGIC  m_iRandom2;
	BYTE                        m_bMagic;
	short                       m_wAuthKey;
};
#define CTOZ_CHECK_AUTH_KEY_SIZE                    sizeof (CTOZ_CHECK_AUTH_KEY)

#define CTOZ_UPDATE_AUTH_KEY_TYPE           90
struct CTOZ_UPDATE_AUTH_KEY {
	CTOZ_UPDATE_AUTH_KEY (void) {
		m_bMagic = CTOZ_UPDATE_AUTH_KEY_TYPE;
	}

	int                         m_iRandom1;
	U_RANDOM_AND_ENCRYPT_MAGIC  m_iRandom2;
	BYTE                        m_bMagic;
	short                       m_wAuthKey[2];
};
#define CTOZ_UPDATE_AUTH_KEY_SIZE                   sizeof (CTOZ_UPDATE_AUTH_KEY)

#define CTOZ_UDP_UPDATE_TYPE                91
struct CTOZ_UDP_UPDATE {
	CTOZ_UDP_UPDATE (void) {
		m_bMagic = CTOZ_UDP_UPDATE_TYPE;
	}

	BYTE                        m_bMagic;
	char                        m_szName[MAX_AVATAR_NAME_LENGTH];
};
#define CTOZ_UDP_UPDATE_SIZE                        sizeof (CTOZ_UDP_UPDATE)

#define CTOZ_ACK_INCOMING_UDP_TYPE          92
struct CTOZ_ACK_INCOMING_UDP {
	CTOZ_ACK_INCOMING_UDP (void) {
		m_bMagic = CTOZ_ACK_INCOMING_UDP_TYPE;
		::ZeroMemory (m_szName, sizeof (m_szName));
	}

	int                         m_iRandom1;
	U_RANDOM_AND_ENCRYPT_MAGIC  m_iRandom2;
	BYTE                        m_bMagic;
	char                        m_szName[MAX_AVATAR_NAME_LENGTH];
};
#define CTOZ_ACK_INCOMING_UDP_SIZE                  sizeof (CTOZ_ACK_INCOMING_UDP)

#define CTOZ_REQUEST_PRESENT_TYPE           93
struct CTOZ_REQUEST_PRESENT {
	CTOZ_REQUEST_PRESENT (void) {
		m_bMagic = CTOZ_REQUEST_PRESENT_TYPE;
	}

	int                         m_iRandom1;
	U_RANDOM_AND_ENCRYPT_MAGIC  m_iRandom2;
	BYTE                        m_bMagic;
};
#define CTOZ_REQUEST_PRESENT_SIZE                   sizeof (CTOZ_REQUEST_PRESENT)

#define CTOZ_CHANGE_PLAYTIMETOTEACHERPOINT_TYPE     94
struct CTOZ_CHANGE_PLAYTIMETOTEACHERPOINT {
	CTOZ_CHANGE_PLAYTIMETOTEACHERPOINT (void) {
		m_bMagic = CTOZ_CHANGE_PLAYTIMETOTEACHERPOINT_TYPE;
	}

	int                         m_iRandom1;
	U_RANDOM_AND_ENCRYPT_MAGIC  m_iRandom2;
	BYTE                        m_bMagic;
};
#define CTOZ_CHANGE_PLAYTIMETOTEACHERPOINT_SIZE     sizeof (CTOZ_CHANGE_PLAYTIMETOTEACHERPOINT)

#pragma pack (pop)

/* Mir added 08.12.12 */
#define P_CHECK_EVENT_INFO_RECV                                     95
#define S_CHECK_EVENT_INFO_RECV                                      9
/* Mir end */
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH)
#define P_PTOZ_GET_RANK_INFO                                        96
#define S_PTOZ_GET_RANK_INFO                                        9 + MAX_AVATAR_NAME_LENGTH

//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tValue01(4) + tValue02(4)
#define P_CHANGE_AUTO_INFO											97
#define S_CHANGE_AUTO_INFO                                          17
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tValue01(4) + tValue02(4)

/*뉴영수*/
#define P_ANIMAL_STATE_SEND											98	
#define S_ANIMAL_STATE_SEND                                         17

//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tPage(4) + tIndex(4) + tValue(4)
#define P_MEDAL_EXCHANGE_SEND										99
#define S_MEDAL_EXCHANGE_SEND										21

//@{ auto quiz
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) + tValue( sizeof( char ) * 5 ) 
#define P_CORRECT_ANSWER											100
#define S_CORRECT_ANSWER											9 + ( sizeof( char ) * 5 )
//@}
// # Defense Hack # {
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1) 
#define P_SPEED_HACK_SEND                                           101
#define S_SPEED_HACK_SEND                                           9 + MAX_AVATAR_NAME_LENGTH
// # }
// # X-Trap # { // X-Trap Step2
#define P_XTRAP_STEP_2                                              102
#define S_XTRAP_STEP_2                                              9 + 128
// # }
// @ Cost Info Download @
//tPacketNumber1(4) + tPacketNumber2(4) + protocol(1)
#define P_GET_CASH_ITEM_INFO_SEND                                   103
#define S_GET_CASH_ITEM_INFO_SEND                                   9
// @

/** 2009. 11. 18 : 장식 해방 시스템 (wolf) */
#pragma pack (push, 1)

#define CTOZ_TOGGLE_STOPWATCH_TYPE    105 
struct CTOZ_TOGGLE_STOPWATCH {
	CTOZ_TOGGLE_STOPWATCH (void) {
		m_bMagic = CTOZ_TOGGLE_STOPWATCH_TYPE;
	}

	int                         m_iRandom1;
	U_RANDOM_AND_ENCRYPT_MAGIC  m_iRandom2;
	BYTE                        m_bMagic;
	// Kind -   0 : 장식 해방 시스템 사용.
	BYTE                        m_bKind;
	BYTE                        m_bUse; // 0 - 끄기, 1 - 켜기.
};
#define CTOZ_TOGGLE_STOPWATCH_TYPESIZE     sizeof (CTOZ_TOGGLE_STOPWATCH)

#pragma pack (pop)
/** 2009. 11. 18 : 장식 해방 시스템 (wolf) */
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//[SEND_PROTOCOL]
//-------------------------------------------------------------------------------------------------
//------------------//
//[ZONE] -> [CLIENT]//
//------------------//
//protocol(1) + tResult(4)
#define P_TEMP_REGISTER_RECV										11
#define S_TEMP_REGISTER_RECV										5
//protocol(1) + tAvatarInfo( sizeof( AVATAR_INFO ) ) + tEffectValue(MAX_AVATAR_EFFECT_SORT_NUM * 8) + tPremiumServerExpirationDate(4)
#define P_REGISTER_AVATAR_RECV										12
#define S_REGISTER_AVATAR_RECV										5 + sizeof( AVATAR_INFO ) + MAX_AVATAR_EFFECT_SORT_NUM * 8 // + tPremiumServerExpirationDate(4) // @_Premium_Server_@
//protocol(1) + tWorldInfo( sizeof( WORLD_INFO ) ) + tTribeInfo( sizeof( TRIBE_INFO ) )
#define P_BROADCAST_WORLD_INFO										13
#define S_BROADCAST_WORLD_INFO										1 + sizeof( WORLD_INFO ) + sizeof( TRIBE_INFO )
//protocol(1) + tDataSize(4) + tData(1000)
#define P_AUTO_CHECK_ASK_SEND										14
#define S_AUTO_CHECK_ASK_SEND										1005
//protocol(1) + tServerIndex(4) + tUniqueNumber(4) + tAvatar( sizeof( OBJECT_FOR_AVATAR ) ) + tCheckChangeActionState(4)
#define P_AVATAR_ACTION_RECV										15
#define S_AVATAR_ACTION_RECV										13 + sizeof( OBJECT_FOR_AVATAR )
//protocol(1) + tServerIndex(4) + tUniqueNumber(4) + tEffectValue(MAX_AVATAR_EFFECT_SORT_NUM * 8) + tEffectValueState(MAX_AVATAR_EFFECT_SORT_NUM * 4 )
#define P_AVATAR_EFFECT_VALUE_INFO									16
#define S_AVATAR_EFFECT_VALUE_INFO									9 + MAX_AVATAR_EFFECT_SORT_NUM * 8 + MAX_AVATAR_EFFECT_SORT_NUM * 4
//protocol(1) + tServerIndex(4) + tUniqueNumber(4) + tSort(4) + tValue01(4) + tValue02(4) + tValue03(4)
#define P_AVATAR_CHANGE_INFO_1										17
#define S_AVATAR_CHANGE_INFO_1										25
//protocol(1) + tServerIndex(4) + tUniqueNumber(4) + tMonster( sizeof( OBJECT_FOR_MONSTER ) ) + tCheckChangeActionState(4)
#define P_MONSTER_ACTION_RECV										18
#define S_MONSTER_ACTION_RECV										13 + sizeof( OBJECT_FOR_MONSTER )
//protocol(1) + tServerIndex(4) + tUniqueNumber(4) + tItem( sizeof( OBJECT_FOR_ITEM ) ) + tCheckChangeActionState(4)
#define P_ITEM_ACTION_RECV											19
#define S_ITEM_ACTION_RECV											13 + sizeof( OBJECT_FOR_ITEM )
//protocol(1) + tContent(MAX_CHAT_CONTENT_LENGTH)
#define P_GENERAL_NOTICE_RECV										20
#define S_GENERAL_NOTICE_RECV										1 + MAX_CHAT_CONTENT_LENGTH
//protocol(1) + tAttackInfo( sizeof( ATTACK_FOR_PROTOCOL ) )
#define P_PROCESS_ATTACK_RECV										21
#define S_PROCESS_ATTACK_RECV										1 + sizeof( ATTACK_FOR_PROTOCOL )
//protocol(1) + tSort(4) + tValue(4)
#define P_AVATAR_CHANGE_INFO_2										22
#define S_AVATAR_CHANGE_INFO_2										9
//protocol(1) + tResult(4) + tSort(4) + tData(MAX_BROADCAST_DATA_SIZE)
#define P_PROCESS_DATA_RECV											23
#define S_PROCESS_DATA_RECV											9 + MAX_BROADCAST_DATA_SIZE
//protocol(1) + tResult(4) + tIp(16) + tPort(4)
#define P_DEMAND_ZONE_SERVER_INFO_2_RESULT							24
#define S_DEMAND_ZONE_SERVER_INFO_2_RESULT							25
//protocol(1) + tResult(4) + tPage(4) + tIndex(4)
#define P_USE_HOTKEY_ITEM_RECV										25
#define S_USE_HOTKEY_ITEM_RECV										13
//protocol(1) + tResult(4) + tPage(4) + tIndex(4) + tValue(4)
#define P_USE_INVENTORY_ITEM_RECV									26
#define S_USE_INVENTORY_ITEM_RECV									17
//protocol(1) + tResult(4) + tCost(4) + iValue(4)
#define P_IMPROVE_ITEM_RECV											27
#define S_IMPROVE_ITEM_RECV											13
//protocol(1) + tResult(4) + tCost(4)
#define P_ADD_ITEM_RECV												28
#define S_ADD_ITEM_RECV												9
//protocol(1) + tResult(4) + tCost(4) + tValue(24)
#define P_EXCHANGE_ITEM_RECV										29
#define S_EXCHANGE_ITEM_RECV										33
//protocol(1) + tResult(4) + tCost(4) + tValue(24)
#define P_HIGH_ITEM_RECV											30
#define S_HIGH_ITEM_RECV											33
//protocol(1) + tResult(4) + tCost(4) + tValue(24)
#define P_LOW_ITEM_RECV												31
#define S_LOW_ITEM_RECV												33
//protocol(1) + tResult(4) + tValue(24)
#define P_MAKE_ITEM_RECV											32
#define S_MAKE_ITEM_RECV											29
//protocol(1) + tResult(4) + tValue(24)
#define P_MAKE_SKILL_RECV											33
#define S_MAKE_SKILL_RECV											29
//protocol(1) + tResult(4) + tPShopInfo( sizeof( PSHOP_INFO ) )
#define P_START_PSHOP_RECV											34
#define S_START_PSHOP_RECV											5 + sizeof( PSHOP_INFO )
//protocol(1)
#define P_END_PSHOP_RECV											35
#define S_END_PSHOP_RECV											1
//protocol(1) + tResult(4) + tPShopInfo( sizeof( PSHOP_INFO ) )
#define P_DEMAND_PSHOP_RECV											36
#define S_DEMAND_PSHOP_RECV											5 + sizeof( PSHOP_INFO )
//protocol(1) + tUniqueNumber(4) + tAvatarName(MAX_AVATAR_NAME_LENGTH) + tPage(4) + tIndex(4) + tPShopItemInfo(36)
#define P_PSHOP_ITEM_INFO_RECV										37
#define S_PSHOP_ITEM_INFO_RECV										49 + MAX_AVATAR_NAME_LENGTH
//protocol(1) + tResult(4) + tCost(4) + tPage(4) + tIndex(4) + tValue(24)
#define P_BUY_PSHOP_RECV											38
#define S_BUY_PSHOP_RECV											41
//protocol(1) + tSort(4) + tPage(4) + tIndex(4) + tXPost(4) + tYPost(4)
#define P_PROCESS_QUEST_RECV										39
#define S_PROCESS_QUEST_RECV										25
//protocol(1) + tResult(4)
#define P_CHANGE_TO_TRIBE4_RECV										40
#define S_CHANGE_TO_TRIBE4_RECV										5
//protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH) + tAuthType(1) + tContent(MAX_CHAT_CONTENT_LENGTH)
#define P_GENERAL_CHAT_RECV											41
#define S_GENERAL_CHAT_RECV											1 + MAX_AVATAR_NAME_LENGTH + 1 +MAX_CHAT_CONTENT_LENGTH
//protocol(1) + tResult(4) + tZoneNumber(4) + tAvatarName(MAX_AVATAR_NAME_LENGTH) + tContent(MAX_CHAT_CONTENT_LENGTH) + tAuthType(1)
#define P_SECRET_CHAT_RECV											42
#define S_SECRET_CHAT_RECV											10 + MAX_AVATAR_NAME_LENGTH + MAX_CHAT_CONTENT_LENGTH
//protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH) + tAuthType(1) + tContent(MAX_CHAT_CONTENT_LENGTH)
#define P_GENERAL_SHOUT_RECV										43
#define S_GENERAL_SHOUT_RECV										1 + MAX_AVATAR_NAME_LENGTH + 1 + MAX_CHAT_CONTENT_LENGTH
//protocol(1) + tCashSize(4) + tBonusCashSize(4)
#define P_GET_CASH_SIZE_RECV										44
#define S_GET_CASH_SIZE_RECV										9
//protocol(1) + tResult(4) + tCashSize(4) + tBonusCashSize(4) + tPage(4) + tIndex(4) + tValue(24)
#define P_BUY_CASH_ITEM_RECV										45
#define S_BUY_CASH_ITEM_RECV										45
//protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH) + tSort(4)
#define P_DUEL_ASK_RECV												46
#define S_DUEL_ASK_RECV												5 + MAX_AVATAR_NAME_LENGTH
//protocol(1)
#define P_DUEL_CANCEL_RECV											47
#define S_DUEL_CANCEL_RECV											1
//protocol(1) + tAnswer(4)
#define P_DUEL_ANSWER_RECV											48
#define S_DUEL_ANSWER_RECV											5

//----------------------------------------------------------------------------------------------------------------
// 2010.01.15 :김성수
// 무신십이경 추가에 따른 소스 수정
#ifdef __GOD__
//protocol(1) + tDuelState(12) + tRemainTime(4) + tEatDrugState(4)
#define P_DUEL_START_RECV											49
#define S_DUEL_START_RECV											21
#else
//protocol(1) + tDuelState(12) + tRemainTime(4)
#define P_DUEL_START_RECV											49
#define S_DUEL_START_RECV											17
#endif
//----------------------------------------------------------------------------------------------------------------
//protocol(1) + tRemainTime(4)
#define P_DUEL_TIME_INFO											50
#define S_DUEL_TIME_INFO											5
//protocol(1) + tResult(4)
#define P_DUEL_END_RECV												51
#define S_DUEL_END_RECV												5
//protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH) + tLevel(4)
#define P_TRADE_ASK_RECV											52
#define S_TRADE_ASK_RECV											5 + MAX_AVATAR_NAME_LENGTH
//protocol(1)
#define P_TRADE_CANCEL_RECV											53
#define S_TRADE_CANCEL_RECV											1
//protocol(1) + tAnswer(4)
#define P_TRADE_ANSWER_RECV											54
#define S_TRADE_ANSWER_RECV											5
//protocol(1) + tTradeMoney(4) + tTrade(MAX_TRADE_SLOT_NUM * 16)
#define P_TRADE_START_RECV											55
#define S_TRADE_START_RECV											5 + MAX_TRADE_SLOT_NUM * 16
//protocol(1) + tTradeMoney(4) + tTrade(MAX_TRADE_SLOT_NUM * 16)
#define P_TRADE_STATE_RECV											56
#define S_TRADE_STATE_RECV											5 + MAX_TRADE_SLOT_NUM * 16
//protocol(1) + tCheckMe(4)
#define P_TRADE_MENU_RECV											57
#define S_TRADE_MENU_RECV											5
//protocol(1) + tResult(4)
#define P_TRADE_END_RECV											58
#define S_TRADE_END_RECV											5
//protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH)
#define P_FRIEND_ASK_RECV											59
#define S_FRIEND_ASK_RECV											1 + MAX_AVATAR_NAME_LENGTH
//protocol(1)
#define P_FRIEND_CANCEL_RECV										60
#define S_FRIEND_CANCEL_RECV										1
//protocol(1) + tAnswer(4)
#define P_FRIEND_ANSWER_RECV										61
#define S_FRIEND_ANSWER_RECV										5
//protocol(1) + tIndex(4) + tAvatarName(MAX_AVATAR_NAME_LENGTH)
#define P_FRIEND_MAKE_RECV											62
#define S_FRIEND_MAKE_RECV											5 + MAX_AVATAR_NAME_LENGTH
//protocol(1) + tIndex(4) + tZoneNumber(4)
#define P_FRIEND_FIND_RECV											63
#define S_FRIEND_FIND_RECV											9
//protocol(1) + tIndex(4)
#define P_FRIEND_DELETE_RECV										64
#define S_FRIEND_DELETE_RECV										5
//protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH)
#define P_TEACHER_ASK_RECV											65
#define S_TEACHER_ASK_RECV											1 + MAX_AVATAR_NAME_LENGTH
//protocol(1)
#define P_TEACHER_CANCEL_RECV										66
#define S_TEACHER_CANCEL_RECV										1
//protocol(1) + tAnswer(4)
#define P_TEACHER_ANSWER_RECV										67
#define S_TEACHER_ANSWER_RECV										5
//protocol(1) + tSort(4) + tAvatarName(MAX_AVATAR_NAME_LENGTH)
#define P_TEACHER_START_RECV										68
#define S_TEACHER_START_RECV										5 + MAX_AVATAR_NAME_LENGTH
//protocol(1)
#define P_TEACHER_END_RECV											69
#define S_TEACHER_END_RECV											1
//protocol(1) + tResult(4)
#define P_TEACHER_STATE_RECV										70
#define S_TEACHER_STATE_RECV										5
//protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH)
#define P_PARTY_ASK_RECV											71
#define S_PARTY_ASK_RECV											1 + MAX_AVATAR_NAME_LENGTH
//protocol(1)
#define P_PARTY_CANCEL_RECV											72
#define S_PARTY_CANCEL_RECV											1
//protocol(1) + tAnswer(4)
#define P_PARTY_ANSWER_RECV											73
#define S_PARTY_ANSWER_RECV											5
//protocol(1)
#define P_PARTY_MAKE_RECV											74
#define S_PARTY_MAKE_RECV											1
//protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH)
#define P_PARTY_JOIN_RECV											75
#define S_PARTY_JOIN_RECV											1 + MAX_AVATAR_NAME_LENGTH
//protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH) + tContent(MAX_CHAT_CONTENT_LENGTH)
#define P_PARTY_CHAT_RECV											76
#define S_PARTY_CHAT_RECV											1 + MAX_AVATAR_NAME_LENGTH + MAX_CHAT_CONTENT_LENGTH
//protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH)
#define P_PARTY_LEAVE_RECV											77
#define S_PARTY_LEAVE_RECV											1 + MAX_AVATAR_NAME_LENGTH
//protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH)
#define P_PARTY_EXILE_RECV											78
#define S_PARTY_EXILE_RECV											1 + MAX_AVATAR_NAME_LENGTH
//protocol(1) + tAvatarName01(MAX_AVATAR_NAME_LENGTH) + tAvatarName02(MAX_AVATAR_NAME_LENGTH) + tAvatarName03(MAX_AVATAR_NAME_LENGTH) + tAvatarName04(MAX_AVATAR_NAME_LENGTH) + tAvatarName05(MAX_AVATAR_NAME_LENGTH)
#define P_PARTY_INFO_RECV											79
#define S_PARTY_INFO_RECV											1 + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH
//protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH)
#define P_PARTY_BREAK_RECV											80
#define S_PARTY_BREAK_RECV											1 + MAX_AVATAR_NAME_LENGTH
//protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH)
#define P_GUILD_ASK_RECV											81
#define S_GUILD_ASK_RECV											1 + MAX_AVATAR_NAME_LENGTH
//protocol(1)
#define P_GUILD_CANCEL_RECV											82
#define S_GUILD_CANCEL_RECV											1
//protocol(1) + tAnswer(4)
#define P_GUILD_ANSWER_RECV											83
#define S_GUILD_ANSWER_RECV											5
//protocol(1) + tResult(4) + tSort(4) + tGuildInfo( sizeof( GUILD_INFO ) )
#define P_GUILD_WORK_RECV											84
#define S_GUILD_WORK_RECV											9 + sizeof( GUILD_INFO )
//protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH) + tContent(MAX_CHAT_CONTENT_LENGTH)
#define P_GUILD_NOTICE_RECV											85
#define S_GUILD_NOTICE_RECV											1 + MAX_AVATAR_NAME_LENGTH + MAX_CHAT_CONTENT_LENGTH
//protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH) + tContent(MAX_CHAT_CONTENT_LENGTH)
#define P_GUILD_CHAT_RECV											86
#define S_GUILD_CHAT_RECV											1 + MAX_AVATAR_NAME_LENGTH + MAX_CHAT_CONTENT_LENGTH
//protocol(1) + tResult(4)
#define P_GUILD_FIND_RECV											87
#define S_GUILD_FIND_RECV											5
//protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH)
#define P_GUILD_LOGIN_INFO											88
#define S_GUILD_LOGIN_INFO											1 + MAX_AVATAR_NAME_LENGTH
//protocol(1) + tResult(4) + tSort(4) + tData(MAX_TRIBE_WORK_SIZE)
#define P_TRIBE_WORK_RECV											89
#define S_TRIBE_WORK_RECV											9 + MAX_TRIBE_WORK_SIZE
//protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH) + tContent(MAX_CHAT_CONTENT_LENGTH)
#define P_TRIBE_NOTICE_RECV											90
#define S_TRIBE_NOTICE_RECV											1 + MAX_AVATAR_NAME_LENGTH + MAX_CHAT_CONTENT_LENGTH
//protocol(1) + tAvatarName(MAX_AVATAR_NAME_LENGTH) + tAuthType(1) + tContent(MAX_CHAT_CONTENT_LENGTH)
#define P_TRIBE_CHAT_RECV											91
#define S_TRIBE_CHAT_RECV											1 + MAX_AVATAR_NAME_LENGTH + 1 + MAX_CHAT_CONTENT_LENGTH
//protocol(1) + tResult(4) + tSort(4) + tTribeBankInfo( MAX_TRIBE_BANK_SLOT_NUM * 4 ) + tMoney(4)
#define P_TRIBE_BANK_RECV											92
#define S_TRIBE_BANK_RECV											13 + MAX_TRIBE_BANK_SLOT_NUM * 4
//protocol(1) + tResult(4) + tSort(4) + tValue(4)
#define P_TRIBE_VOTE_RECV											93
#define S_TRIBE_VOTE_RECV											13
//protocol(1) + tSort(4) + tValue(4)
#define P_TRIBE_ALLIANCE_INFO										94
#define S_TRIBE_ALLIANCE_INFO										9
//protocol(1) + tInfoSort(4) + tInfoData(MAX_BROADCAST_INFO_SIZE)
#define P_BROADCAST_INFO_RECV										95
#define S_BROADCAST_INFO_RECV										5 + MAX_BROADCAST_INFO_SIZE
//protocol(1) + tTribeUserNum(16) + tRemainTime(4)
#define P_049_TYPE_BATTLE_INFO										96
#define S_049_TYPE_BATTLE_INFO										21
//protocol(1) + tExistStone(16) + tRemainTime(4)
#define P_051_TYPE_BATTLE_INFO										97
#define S_051_TYPE_BATTLE_INFO										21
//protocol(1) + tSort(4) + tData(MAX_TRIBE_WORK_SIZE)
#define P_GM_COMMAND_INFO											98
#define S_GM_COMMAND_INFO											5 + MAX_TRIBE_WORK_SIZE
//protocol(1)
#define P_RETURN_TO_AUTO_ZONE										99
#define S_RETURN_TO_AUTO_ZONE										1
//protocol(1) + tValue( sizeof( GG_AUTH_DATA ) )
#define P_CHECK_N_PROTECT_1											100
#define S_CHECK_N_PROTECT_1											1 + sizeof( GG_AUTH_DATA )

#pragma pack (push, 1)

#define ZTOC_CHECK_AUTH_KEY_TYPE            101
struct ZTOC_CHECK_AUTH_KEY {
	ZTOC_CHECK_AUTH_KEY (void) {
		m_bMagic =  ZTOC_CHECK_AUTH_KEY_TYPE;
	}

	BYTE    m_bMagic;
	BYTE    m_bResult;
};
#define ZTOC_CHECK_AUTH_KEY_SIZE                    sizeof (ZTOC_CHECK_AUTH_KEY)

#define ZTOC_UPDATE_AUTH_KEY_TYPE           102
struct ZTOC_UPDATE_AUTH_KEY {
	ZTOC_UPDATE_AUTH_KEY (void) {
		m_bMagic = ZTOC_UPDATE_AUTH_KEY_TYPE;
	}

	BYTE    m_bMagic;
	BYTE    m_bResult;
};
#define ZTOC_UPDATE_AUTH_KEY_SIZE                   sizeof (ZTOC_UPDATE_AUTH_KEY)

#define ZTOC_REQUEST_INCOMING_UDP_TYPE      103
struct ZTOC_REQUEST_INCOMING_UDP {
	ZTOC_REQUEST_INCOMING_UDP (void) {
		m_bMagic = ZTOC_REQUEST_INCOMING_UDP_TYPE;
	}

	BYTE    m_bMagic;
};
#define ZTOC_REQUEST_INCOMING_UDP_SIZE              sizeof (ZTOC_REQUEST_INCOMING_UDP)

#define ZTOC_REQUEST_PRESENT_TYPE           104
struct ZTOC_REQUEST_PRESENT {
	ZTOC_REQUEST_PRESENT (void) {
		m_bMagic = ZTOC_REQUEST_PRESENT_TYPE;
	}

	BYTE    m_bMagic;
	BYTE    m_bResult;
	BYTE    m_bPage;
	BYTE    m_bInvenIndex;
	int     m_iInvenSlot;
	int     m_iItemIndex;
};
#define ZTOC_REQUEST_PRESENT_SIZE                   sizeof (ZTOC_REQUEST_PRESENT)

#define ZTOC_CHANGE_PLAYTIMETOTEACHERPOINT_TYPE     105
struct ZTOC_CHANGE_PLAYTIMETOTEACHERPOINT {
	ZTOC_CHANGE_PLAYTIMETOTEACHERPOINT (void) {
		m_bMagic = ZTOC_CHANGE_PLAYTIMETOTEACHERPOINT_TYPE;
	}

	BYTE    m_bMagic;
	BYTE    m_bResult;
	int     m_iAddTeacherPoints;
};
#define ZTOC_CHANGE_PLAYTIMETOTEACHERPOINT_SIZE     sizeof (ZTOC_CHANGE_PLAYTIMETOTEACHERPOINT)

#pragma pack (pop)
/* Mir added 08.12.12 */
#define P_CHECK_EVENT_INFO_SEND                                    106
#define S_CHECK_EVENT_INFO_SEND                                      9
/* Mir end */
#define P_ZTOP_RANK_INFO_SEND                                      107
#define S_ZTOP_RANK_INFO_SEND                                      1 + sizeof(rank_info_t)

//protocol(1) + tValue01(4) + tValue02(4)
/*뉴영수*/
#define P_ANIMAL_STATE_RECV											108
#define S_ANIMAL_STATE_RECV											9

//protocol(1) + tCount(4) + {tPage(4) + tInvenSlot(4) + tInvenIndex(4) + tItemNum(4) + tItemCount(4) + tItemValue(4) + tItemRecognitionNum(4)} * 5
#define P_ITEM_LIKE_1336_RECV										109
#define S_ITEM_LIKE_1336_RECV										145
//protocol(1) + tResult(4) + tPage(4) + tSlot(4) + tIndex(4) + tValue(4)
#define P_MEDAL_EXCHANGE_RECV										110
#define S_MEDAL_EXCHANGE_RECV										21
//protocol(1) + tRemainTime(4)
#define P_053_TYPE_BATTLE_INFO										111
#define S_053_TYPE_BATTLE_INFO										5

//@{ auto quiz
//protocol(1) + ( sizof( TCHAR ) *( ( 32 * 32 * 4 ) + 44  ) )
#define P_QUESTION_OF_SPHINX										112
#define S_QUESTION_OF_SPHINX										1 + 4 + ( sizeof( char ) * 4140 )	

#define P_CORRECT_ANSWER_RESULT										113
#define S_CORRECT_ANSWER_RESULT										1 + ( sizeof (int) )
//@}
// # Defense Hack # {
//protocol(1) + tValue(4)                                           
#define P_SPEED_CHECK_RECV                                          114
#define S_SPEED_CHECK_RECV                                          5
// # }
// # X-Trap # { // X-Trap Step1
#define P_XTRAP_STEP_1                                              115
#define S_XTRAP_STEP_1                                              1 + 128
// # }
// @ Cost Info Download @
//protocol(1) + tResult(4) + tVersion(4) + tCashItemInfo(MAX_CASH_ITEM_INFO_SIZE)
#define P_GET_CASH_ITEM_INFO_RECV                                   116
#define S_GET_CASH_ITEM_INFO_RECV                                   9 + MAX_CASH_ITEM_INFO_SIZE
//protocol(1)
#define P_UPDATE_CASH_ITEM_INFO                                     117
#define S_UPDATE_CASH_ITEM_INFO                                     1
// @
//-------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------
// 2010.01.15 :김성수
// 무신십이경 추가에 따른 소스 수정
#ifdef __GOD__
//protocol(1) + tTribeUserNum(16)
#define P_194_BATTLE_INFO											120
#define S_194_BATTLE_INFO											17
//protocol(1) + tTime(4)
#define P_194_BATTLE_COUNTDOWN										121
#define S_194_BATTLE_COUNTDOWN										5

//protocol(1) + tTribeUserNum(16) + tRemainTime(4)
#define P_267_TYPE_BATTLE_INFO										122
#define S_267_TYPE_BATTLE_INFO										21
#endif
//----------------------------------------------------------------------------------------------------------------

//발사체 원거리
#define TRAIL_USE  1
//세력진법
#define SMALL_LEVEL_PROTECTION 1

/** 2009. 11. 18 : 장식 해방 시스템 (wolf) */
#pragma pack (push, 1)

#define ZTOC_TOGGLE_STOPWATCH_TYPE    123
struct ZTOC_TOGGLE_STOPWATCH {
	ZTOC_TOGGLE_STOPWATCH (void) {
		m_bMagic = ZTOC_TOGGLE_STOPWATCH_TYPE;
	}

	BYTE                        m_bMagic;
	BYTE                        m_bResult;
	// Kind -   0 : 장식 해방 시스템 사용.
	BYTE                        m_bKind; // 요청한 값.
	BYTE                        m_bUse; // 0 - 끄기, 1 - 켜기.
};
#define ZTOC_TOGGLE_STOPWATCH_TYPESIZE     sizeof (ZTOC_TOGGLE_STOPWATCH)


#define P_EVENT_FOR_ZONE_SEND_PHONE										63
#define S_EVENT_FOR_ZONE_SEND_PHONE										5


#define P_USER_EXT_SEND								63
#define S_USER_EXT_SEND								5 + MAX_USER_ID_LENGTH

#pragma pack (pop)
/** 2009. 11. 18 : 장식 해방 시스템 (wolf) */
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
