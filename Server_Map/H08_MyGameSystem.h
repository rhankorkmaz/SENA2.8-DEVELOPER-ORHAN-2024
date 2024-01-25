//-------------------------------------------------------------------------------------------------
//MY_GAMESYSTEM_H
//-------------------------------------------------------------------------------------------------
#ifndef MY_GAMESYSTEM_H
#define MY_GAMESYSTEM_H
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_LEVELSYSTEM-ARRAY[145]
//-------------------------------------------------------------------------------------------------
//DEFINE
class LEVELSYSTEM
{

private :

#ifdef __GOD__
	float mGainExpInfoForKillOtherTribe[MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM ];
	int mRangeForHigh[MAX_LIMIT_HIGH_LEVEL_NUM];
#else
	float mGainExpInfoForKillOtherTribe[MAX_LIMIT_LEVEL_NUM];
#endif

	LEVEL_INFO mDATA[MAX_LIMIT_LEVEL_NUM];

	BOOL CheckValidElement( int tArrayIndex );

public :

	LEVELSYSTEM( void );

	BOOL Init( char *tFileName );
	void Free( void );

	int ReturnLevel( int tGeneralExperience );
	int ReturnLevelFactor1( int tLevel );
	int ReturnLevelFactor2( int tLevel );
	int ReturnLevelFactor3( int tLevel );
	int ReturnLevelFactorAttackPower( int tLevel );
	int ReturnLevelFactorDefensePower( int tLevel );
	int ReturnLevelFactorAttackSuccess( int tLevel );
	int ReturnLevelFactorAttackBlock( int tLevel );
	int ReturnLevelFactorElementAttack( int tLevel );
	int ReturnLevelFactorLife( int tLevel );
	int ReturnLevelFactorMana( int tLevel );

	int ReturnGainExpForKillOtherTribe( int tAttackLevel, int tDefenseLevel );
	
#ifdef __GOD__
	int ReturnHighExpValue( int tLevel );
#endif

};
//INSTANCE
extern LEVELSYSTEM mLEVEL;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_ITEMSYSTEM-ARRAY[99999]
//-------------------------------------------------------------------------------------------------
//STRUCTURE-[SHARED_ITEMSYSTEM]
typedef struct
{
	int mDataNum;
	ITEM_INFO *mDATA;
	int mPartNum[157][6][32];
	int *mPART[157][6][32];
}
SHARED_ITEMSYSTEM;
//DEFINE
class ITEMSYSTEM
{

private :

	int mDataNum;
	ITEM_INFO *mDATA;
	int mPartNum[157][6][32];
	int *mPART[157][6][32];

	DWORD mSharedMemSize;
	DWORD mSharedMemSizeForCheck;
	HANDLE mSharedMemMap;

	BYTE *mSharedPostMem;
	SHARED_ITEMSYSTEM mSharedItemData;

	BOOL CheckValidElement( int tArrayIndex );

public :

	ITEMSYSTEM( void );

	BOOL Init( char *tFileName );
	void Free( void );

	ITEM_INFO * Search( int iIndex );
	ITEM_INFO * Return( int iLevel, int iType, int iSort );
	ITEM_INFO *	Return31(int iLevel, int iType, int iSort);
	ITEM_INFO* GetSkillByTribeInfo(int iLevel, int iType, int iSort, int tribe);
	ITEM_INFO * Return( int iLevel, int iType, int iSort, ITEM_INFO *tITEM_INFO );
	ITEM_INFO*  ReturnTalih(int iLevel, int iType, int iSort, int iSetBonus);


#ifdef __GOD__
	ITEM_INFO * Return_1( int iLevel, ITEM_INFO *tITEM_INFO );
	ITEM_INFO * Return_2( int iLevel, ITEM_INFO *tITEM_INFO );
#else
	ITEM_INFO * Return( int iLevel, ITEM_INFO *tITEM_INFO );
#endif

   /** .. ... .. (.. ...). ......
     *
     *  @return     ... .... ....
     *  @param      iTribe  .. (0 - .., 1 - .., 2 - ..)
     *  @param      iLevel  .. ... .. .. (.. ..).
     *  @warning    .. .... .... .. .... .... . .... 
     *              ... .... .... .. . .. .. ..... 
     *              .. ..... ... ... ..... ... ....
     *              .... ... .. .. .... ... .... ...
     *              . .....
     */
	ITEM_INFO*  ReturnRareItem2(int iTribe, int iLevel);
    ITEM_INFO*  ReturnRareItem1 (int iTribe, int iLevel, int iSort);
    ITEM_INFO*  ReturnRareItem (int iTribe, int iType, int iLevel);

    /** ..... (Gigabyte) .... .... . .. . .. .... ......
     *
     *  @return     ... .. ... ... .... ....
     *  @note       ... (.) - 45.00%
     *              ... (.) - 25.00%
     *              ... (.) - 10.00%
     *              ... (.) -  6.00%
     *              ... (.) -  4.00%
     *              ... (.) -  3.00%
     *              ... (.) -  2.50%
     *              ... (.) -  2.00%
     *              ... (.) -  1.50%
     *              ... (.) -  1.00%
     */
    ITEM_INFO*  GetResultItemPtrByGigabyteItem (void);

    /** 1. .... .... .... . .. . .. .... ......
     *
     *  @return     ... .. ... ... .... ....
     *  @param      iCounts     .... .. (OUTPUT).
     *  @warning    iCounts ..... .. ... ....... .., 1. 
     *              ..... .. ... ... ... .. . ... ..
     *              ... ... ... .. ... ... .... ....
     *              .. .... ... ......
     */
    ITEM_INFO*  GetMoneyBy1WonLuckyBag (void);

    /** .. .. NPC. .. .. .. ..... .. . .. .... ......
     *
     *  @return     ... .. ... ... .... ....
     *  @param      iCounts     .... .. (OUTPUT).
     *  @note       ... (.)     - 50%
     *              ... (.)     - 42%
     *              ... 9%       -  6%
     *              1. ....    -  1%
     *              . ...       -  1%
     */
    ITEM_INFO*  GetPresentItemPtrByGoodwillAmbassador (int& iCounts);

};
//INSTANCE
extern ITEMSYSTEM mITEM;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_SKILLSYSTEM-ARRAY[300]
//-------------------------------------------------------------------------------------------------
//DEFINE
class SKILLSYSTEM
{

private :

	int mDataNum;
	SKILL_INFO *mDATA;

	BOOL CheckValidElement( int tArrayIndex );

public :

	SKILLSYSTEM( void );

	BOOL Init( char *tFileName );
	void Free( void );

	SKILL_INFO * Search( int sIndex );

	int ReturnAttackType( int sIndex );
	int ReturnTotalHitNumber( int sIndex );

	float ReturnSkillValue( int sIndex, int sPoint, int sFactor );

};
//INSTANCE
extern SKILLSYSTEM mSKILL;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MONSTERSYSTEM-ARRAY[10000]
//-------------------------------------------------------------------------------------------------
//STRUCTURE-[SHARED_MONSTERSYSTEM]
typedef struct
{
	int mDataNum;
	MONSTER_INFO *mDATA;
}
SHARED_MONSTERSYSTEM;
//DEFINE
class MONSTERSYSTEM
{

private :

	int mDataNum;
	MONSTER_INFO *mDATA;

	DWORD mSharedMemSize;
	DWORD mSharedMemSizeForCheck;
	HANDLE mSharedMemMap;
	BYTE *mSharedPostMem;
	SHARED_MONSTERSYSTEM mSharedMonsterData;

	BOOL CheckValidElement( int tArrayIndex );

public :

	MONSTERSYSTEM( void );

	BOOL Init( char *tFileName );
	void Free( void );

	MONSTER_INFO * Search( int mIndex );
	MONSTER_INFO * Search( int tMonsterType, int tMonsterSpecialType );

};
//INSTANCE
extern MONSTERSYSTEM mMONSTER;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_NPCSYSTEM-ARRAY[500]
//-------------------------------------------------------------------------------------------------
//STRUCTURE-[SHARED_NPCSYSTEM]
typedef struct
{
	int mDataNum;
	NPC_INFO *mDATA;
}
SHARED_NPCSYSTEM;
//DEFINE
class NPCSYSTEM
{

private :

	int mDataNum;
	NPC_INFO *mDATA;

	DWORD mSharedMemSize;
	DWORD mSharedMemSizeForCheck;

	HANDLE mSharedMemMap;

	BYTE *mSharedPostMem;
	SHARED_NPCSYSTEM mSharedNPCData;

	BOOL CheckValidElement( int tArrayIndex );

public :

	NPCSYSTEM( void );

	BOOL Init( char *tFileName );
	void Free( void );

	NPC_INFO * Search( int nIndex );

};
//INSTANCE
extern NPCSYSTEM mNPC;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_QUESTSYSTEM-ARRAY[1000]
//-------------------------------------------------------------------------------------------------
//STRUCTURE-[SHARED_QUESTSYSTEM]
typedef struct
{
	int mDataNum;
	QUEST_INFO *mDATA;
}
SHARED_QUESTSYSTEM;
//DEFINE
class QUESTSYSTEM
{

private :

	int mDataNum;
	QUEST_INFO *mDATA;

	DWORD mSharedMemSize;
	DWORD mSharedMemSizeForCheck;

	HANDLE mSharedMemMap;

	BYTE *mSharedPostMem;
	SHARED_QUESTSYSTEM mSharedQuestData;

	BOOL CheckValidElement( int tArrayIndex );

public :

	QUESTSYSTEM( void );

	BOOL Init( char *tFileName );
	void Free( void );

	QUEST_INFO * Search( int qTribe, int qStep );

};
//INSTANCE
extern QUESTSYSTEM mQUEST;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_PATSYSTEM
//-------------------------------------------------------------------------------------------------
//DEFINE
class PATSYSTEM
{

public :

	int mMaxRangeValue[8];

	PATSYSTEM( void );

	BOOL Init( void );
	void Free( void );

	float ReturnGrowStep( int pIndex, int pGrowUpValue );
	float ReturnGrowPercent( int pIndex, int pGrowUpValue );
	float ReturnAttackPower( int pIndex, int pGrowUpValue, int pActivityValue );
	float ReturnDefensePower( int pIndex, int pGrowUpValue, int pActivityValue );
	float ReturnLifeValue( int pIndex, int pGrowUpValue );
	float ReturnManaValue( int pIndex, int pGrowUpValue );
	int   PetExp200(int pIndex, int pGrowUpValue, int pActivityValue);
	int   ReturnNewPets(int PetKodu, int PetExp, int tSort);
	float ReturnNewPetCombine(int PetKodu, int PetExp, int tSort);
	float ReturnLegandryPets(int PetKodu);
	float ReturnEpicPets(int PetKodu);
	int ReturnMaxPetExp(int pIndex);

};
//INSTANCE
extern PATSYSTEM mPAT;
//-------------------------------------------------------------------------------------------------
typedef struct
{
	int mDataNum;
	SOCKET_INFO* mDATA;
}
SHARED_SOCKETSYSTEM;
//DEFINE
class SOCKETSYSTEM
{

private:

	int mDataNum;
	SOCKET_INFO* mDATA;

	DWORD mSharedMemSize;
	DWORD mSharedMemSizeForCheck;

	HANDLE mSharedMemMap;

	BYTE* mSharedPostMem;
	SHARED_SOCKETSYSTEM mSharedSocketData;

	BOOL CheckValidElement(int tArrayIndex);

public:

	SOCKETSYSTEM(void);

	BOOL Init(char* tFileName);
	void Free(void);

	SOCKET_INFO* Search(int a2, int a3);


};
//INSTANCE
extern SOCKETSYSTEM mSocket;

//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
