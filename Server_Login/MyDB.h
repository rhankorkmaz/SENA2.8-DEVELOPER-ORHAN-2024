//-------------------------------------------------------------------------------------------------
//MY_DB_H
//-------------------------------------------------------------------------------------------------
#ifndef MY_DB_H
#define MY_DB_H
//-------------------------------------------------------------------------------------------------
#include "..\include\cts_mysql.h"

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_DB
//-------------------------------------------------------------------------------------------------
//MACRO
#define MAX_QUERY_BUFFER_SIZE										100000
//DEFINE
class MyDB
{

private :

	char mQUERY[MAX_QUERY_BUFFER_SIZE];

    CMySQL mDB01;
    CMySQL mDB02;

	BOOL RECONNECT_TO_DATABASE01( void );
	BOOL RECONNECT_TO_DATABASE02( void );

	void MakeQueryForInsert( int tSort, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO *tAvatarInfo );

public :

	MyDB( void );

	BOOL Init( void );
	void Free( void );

	BOOL DB_PROCESS_01( void );

	void MyDB::DB_PROCESS_02(char tIP[16], char tID[MAX_USER_ID_LENGTH], char tPassword[MAX_USER_PASSWORD_LENGTH], char uID[MAX_USER_ID_LENGTH], int* tCheckMOTP,
		char tMousePassword[MAX_MOUSE_PASSWORD_LENGTH], int* tSecretCard, int* tUserSort, int* tGoodFellow, int* tUserRandom, int* tLoginPremium, int* tTraceState,
		char* tBonus100Money, int* tPremiumServerExpirationDate, int* tSaveMoney, int tSaveItem[MAX_SAVE_ITEM_SLOT_NUM][4], AVATAR_INFO tAvatarInfo[MAX_USER_AVATAR_NUM],
		AUTH_INFO* tAuthInfo, int* tResult, char* tFirstLogin, int* tSeyisbar, int tSaveSocket[MAX_SAVE_ITEM_SLOT_NUM][3]);
	BOOL DB_PROCESS_03( char tID[MAX_USER_ID_LENGTH], char tMousePassword[MAX_MOUSE_PASSWORD_LENGTH] );
	BOOL DB_PROCESS_04( int tSecretCardNumber, int tSecretCardIndex, char tSecretCardContent[5] );
	void DB_PROCESS_05( int tUserIndex, int tAvatarPost, AVATAR_INFO *tAvatarInfo, int *tResult );
	BOOL DB_PROCESS_06( int tUserIndex, int tAvatarPost );
	void DB_PROCESS_07( char tID[MAX_USER_ID_LENGTH], int tAvatarPost, char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tChangeAvatarName[MAX_AVATAR_NAME_LENGTH], int *tResult );
	BOOL DB_PROCESS_08( char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tInventory[2][MAX_INVENTORY_SLOT_NUM][6] );
	BOOL DB_PROCESS_09( char tCardNumber[MAX_USER_CARD_NUMBER_LENGTH], char tID[MAX_USER_ID_LENGTH], int tGiftInfo[10] );
	BOOL DB_PROCESS_10( char tCardNumber[MAX_USER_CARD_NUMBER_LENGTH], int tGiftInfo[10] );
	BOOL DB_PROCESS_11( char tID[MAX_USER_ID_LENGTH], int tSaveItem[MAX_SAVE_ITEM_SLOT_NUM][4] );
	BOOL DB_PROCESS_12( WORLD_INFO *tWorldInfo );
	BOOL DB_PROCESS_13( TRIBE_INFO *tTribeInfo );
	int DB_PROCESS_14(const char *ip_addr, const char *user_id);
	bool DB_PROCESS_15(int aTribe);
    // @ __WEB_MALL__
    BOOL DB_PROCESS_18(char *tID, int tLimit, int *tList, int &tCount, WEBMALL_INFO *tGiftInfo);
    BOOL DB_PROCESS_19(char *tID, int tItemSetNumber, int tUsedCnt, int tWebMallSeq);
    // __WEB_MALL__ @
	int DB_PROCESS_21(char* aName);
};
//INSTANCE
extern MyDB mDB;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
