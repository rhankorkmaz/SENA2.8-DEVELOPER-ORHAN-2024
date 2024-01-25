//-------------------------------------------------------------------------------------------------
//MY_GAME_H
//-------------------------------------------------------------------------------------------------
#ifndef MY_GAME_H
#define MY_GAME_H
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_GAME
//-------------------------------------------------------------------------------------------------
//MACRO
#define MAX_SIZE_OF_RCMD                                            4
#define MAX_GIFT_ITEM_NUM											10
#define MAX_GIFT_SORT_NUM											1000
#define MAX_BLOCK_IP_INFO_NUM										10000
//STRUCTURE-[GIFT_INFO]
typedef struct
{
	int mTotalGiftNum;
	int mGiftData[MAX_GIFT_ITEM_NUM][2];
}
GIFT_INFO;

typedef struct
{
    int mTotalGiftNum;
    int mGiftData[MAX_GIFT_ITEM_NUM][2];
    int mWebMallSeq;            //2009.10.20 : 김성수 : 웹몰에서 구매한 일련번호를 저장하기 위한 필드
}
WEBMALL_INFO;

class CIPInfoList
{
	public :
		BOOL LoadIPInfo( const char * ipInfoFilePath );
		BOOL GetOneValueFromFile( FILE* fp, int tBufferSize, char *tBuffer );
		BOOL CompareIPInfo( int tIP1, int tIP2, int tIP3, int tIP4 );

		CIPInfoList();
		~CIPInfoList();

	private :
		int mTotalIPInfoNum;
		int mIPInfoList[MAX_BLOCK_IP_INFO_NUM][2][4];
};

//DEFINE
class MyGame
{

public :

	DWORD mTickCount;
	
	int mMaxPlayerNum;
	int mAddPlayerNum;
	int mGagePlayerNum;
	int mPresentPlayerNum;

	int mTotalBlockIPInfo;
	unsigned char mRcmdIld[MAX_SIZE_OF_RCMD];
	unsigned char mRcmdPtt[MAX_SIZE_OF_RCMD];
	unsigned char mRcmdWrd[MAX_SIZE_OF_RCMD];
	int mBlockIPInfo[MAX_BLOCK_IP_INFO_NUM][2][4];

	CIPInfoList mGMEnableLoginIPList;

	GIFT_INFO mGiftInfo[MAX_GIFT_SORT_NUM];

	MyGame( void );

	BOOL Init( void );
	void Free( void );

	BOOL CheckNameString( char *tString );

	int ReturnNowDate( void );
	void SafeAvatarInfoData( AVATAR_INFO *tAvatarInfo );
	int ReturnTribeRole( TRIBE_INFO *tTribeInfo, char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tTribe );

	BOOL LoadBlockIPInfo( void );
	BOOL GetOneValueFromFile( FILE* fp, int tBufferSize, char *tBuffer );
	BOOL CompareBlockIPInfo( int tIP1, int tIP2, int tIP3, int tIP4 );

	BOOL LoadGiftInfo( void );

	BOOL CheckDeleteItem( int iIndex );
	
//-------------------------------------------------------------------------------------------------
// 2010.01.15 : KimSungSoo
// musin
	int ReturnNowTime( void );
	int ReturnAddDate( int tPostDateValue, int tAddDayValue );
	int ReturnSubDate( int tPostDateValue, int tSubDayValue );
	BOOL CheckSinItem( int iIndex );

//-------------------------------------------------------------------------------------------------
};
//INSTANCE
extern MyGame mGAME;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_ZONEMAININFO
//-------------------------------------------------------------------------------------------------
//DEFINE
class ZONEMAININFO
{

private :

	int mZoneLevelInfo[MAX_ZONE_NUMBER_NUM][2];
	int mZoneTribeInfo[MAX_ZONE_NUMBER_NUM][2];

public :

	ZONEMAININFO( void );

	BOOL Init( void );
	void Free( void );

	int ReturnMinZoneLevelInfo( int tZoneNumber );
	int ReturnMaxZoneLevelInfo( int tZoneNumber );
	int ReturnZoneTribeInfo1( int tZoneNumber );
	int ReturnZoneTribeInfo2( int tZoneNumber );

};
//INSTANCE
extern ZONEMAININFO mZONEMAININFO;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
