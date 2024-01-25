//-------------------------------------------------------------------------------------------------
//MY_GAME_H
//-------------------------------------------------------------------------------------------------
#ifndef MY_GAME_H
#define MY_GAME_H
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_GAME
//-------------------------------------------------------------------------------------------------
//THREAD-[THREAD_FOR_DB_WORKER]
#ifdef __WIN32__
DWORD WINAPI THREAD_FOR_DB_WORKER( PVOID pParam );
#endif
//DEFINE
class MyGame
{

public :

	int mTribeBankInfo[4][MAX_TRIBE_BANK_SLOT_NUM];

	DWORD mTickCount;

	BOOL mCheckValidState[MAX_PLAY_USER_NUM];
	int mRegisterSort[MAX_PLAY_USER_NUM];
	DWORD mSaveTime[MAX_PLAY_USER_NUM];
	DWORD mPostTime[MAX_PLAY_USER_NUM];
	DWORD mPlayTime[MAX_PLAY_USER_NUM];
	int mZoneNumber[MAX_PLAY_USER_NUM];
	char mIP[MAX_PLAY_USER_NUM][16];
	char mID[MAX_PLAY_USER_NUM][MAX_USER_ID_LENGTH];
	int mUserSort[MAX_PLAY_USER_NUM];
	int mGoodFellow[MAX_PLAY_USER_NUM];
	int mUserRandom[MAX_PLAY_USER_NUM];
	int mLoginPremium[MAX_PLAY_USER_NUM];
	int mLoginPremiumPCRoom[MAX_PLAY_USER_NUM];
	int mTraceState[MAX_PLAY_USER_NUM];
	char mBonus100Money[MAX_PLAY_USER_NUM];
	int mPremiumServerExpirationDate[MAX_PLAY_USER_NUM]; // 프리미엄 서버(월드) 입장권 유효 기한(YYYYMMDD 형태의 정수). // @_Premium_Server_@
	AVATAR_INFO mAvatarInfo[MAX_PLAY_USER_NUM];
	int mEffectValue[MAX_PLAY_USER_NUM][MAX_AVATAR_EFFECT_SORT_NUM][2];
	BOOL mFirstEnterZone[MAX_PLAY_USER_NUM];
	AUTH_INFO mAuthInfo[MAX_PLAY_USER_NUM];
	int mAnimalOn[MAX_PLAY_USER_NUM];
	int mTotalSave1Num;
	int mSave1Sort[MAX_PLAY_USER_NUM];
	char mSave1ID[MAX_PLAY_USER_NUM][MAX_USER_ID_LENGTH];
	AVATAR_INFO mSave1AvatarInfo[MAX_PLAY_USER_NUM];
	AUTH_INFO mSave1AuthInfo[MAX_PLAY_USER_NUM];
	int mSave1LoginPremiumPCRoom[MAX_PLAY_USER_NUM];
	int mTotalSave2Num;
	int mSave2Sort[MAX_PLAY_USER_NUM];
	char mSave2ID[MAX_PLAY_USER_NUM][MAX_USER_ID_LENGTH];
	AVATAR_INFO mSave2AvatarInfo[MAX_PLAY_USER_NUM];
	AUTH_INFO mSave2AuthInfo[MAX_PLAY_USER_NUM];
	int mSave2LoginPremiumPCRoom[MAX_PLAY_USER_NUM];
	CRITICAL_SECTION mCriticalSection;
	HANDLE mEHandle;
	HANDLE mTHandle;
	BOOL mCheckKillOtherTribe[MAX_PLAY_USER_NUM];
	char mKillOtherTribeAvatarName1[MAX_PLAY_USER_NUM][MAX_AVATAR_NAME_LENGTH];
	char mKillOtherTribeAvatarName2[MAX_PLAY_USER_NUM][MAX_AVATAR_NAME_LENGTH];
	DWORD mKillOtherTribeTime[MAX_PLAY_USER_NUM];
	MOVE_ITEM_INFO mMoveItemInfo[MAX_PLAY_USER_NUM]; // 이동서 사용 정보.
	VALETSHOP_INFO mValetShopInfo;

	MyGame( void );

	BOOL Init( void );
	void Free( void );

	BOOL CheckOverMaximum( int tValue1, int tValue2 );

	BOOL LoadForTribeBankInfo( void );
	void SaveForTribeBankInfo( void );

	void ProcessForPlayUser( void );

	void ProcessForSave_1( int tSort, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO *tAvatarInfo, AUTH_INFO *tAuthInfo, int tLoginPremiumPCRoom );
	void ProcessForSave_2( void );

	void SafeAvatarInfoData( AVATAR_INFO *tAvatarInfo );

	int ReturnPresentUserNum( int tZoneNumber );
	void ReturnPresentUserNum(char *tBuffer);

	int ReturnExistZoneNumberForAvatarName( char tAvatarName[MAX_AVATAR_NAME_LENGTH], int *tTribe );
	int ReturnExistZoneNumberForUserID( char tID[MAX_USER_ID_LENGTH] );

	int RegisterUserForLogin_01( char tIP[16], char tID[MAX_USER_ID_LENGTH], int tUserSort, int tGoodFellow, int tUserRandom, int tLoginPremium, int tLoginPremiumPCRoom, int tTraceState, char tBonus100Money, int tPremiumServerExpirationDate, int *tPlayUserIndex, AUTH_INFO *tAuthInfo ); // 함수 선언 수정 - int tPremiumServerExpirationDate 추가. // @_Premium_Server_@
	int RegisterUserForLogin_02( int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH] );
	int RegisterUserForLogin_03( int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO *tAvatarInfo);
	void UnRegisterUserForLogin( int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH] );

	int RegisterUserForZone_00( int tZoneNumber, char tID[MAX_USER_ID_LENGTH], int *tPlayUserIndex );
	int RegisterUserForZone_01(int tZoneNumber, int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH], char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tLogoutInfo[6], int* tUserSort, int* tGoodFellow, int* tUserRandom, int* tLoginPremium, int* tLoginPremiumPCRoom, int* tTraceState, char* tBonus100Money, int* tPremiumServerExpirationDate, AVATAR_INFO* tAvatarInfo, int tEffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2], int* tCheckFirstZone, AUTH_INFO* tAuthInfo, int *AnimalOn); // 함수 선언 수정 - int *tPremiumServerExpirationDate 추가. // @_Premium_Server_@
	int RegisterUserForZone_02( int tZoneNumber, int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO *tAvatarInfo, int tEffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2], AUTH_INFO *tAuthInfo);
	int RegisterUserForZone_03( int tZoneNumber, int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO *tAvatarInfo, int tEffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2], AUTH_INFO *tAuthInfo, int AnimalOn);
	void UnRegisterUserForZone( int tZoneNumber, int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO *tAvatarInfo, AUTH_INFO *tAuthInfo);
	void DUPEFIX(int tZoneNumber, int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO* tAvatarInfo, AUTH_INFO* tAuthInfo);

	int ProcessKillOtherTribe( char tAvatarName1[MAX_AVATAR_NAME_LENGTH], char tAvatarName2[MAX_AVATAR_NAME_LENGTH] );
	int ChangeAvatarNameForZone(int tPlayUserIndex, char *tChangeAvatarName);
	BOOL CheckNameString(char *tString);
	int ReturnTribeRole( TRIBE_INFO *tTribeInfo, char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tTribe );
	int Bonus100Money(int tPlayUserIndex);
	int ProccesForFindAvatar(int PlayerUserIndex, char aName[MAX_AVATAR_NAME_LENGTH]);

};
//INSTANCE
extern MyGame mGAME;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
