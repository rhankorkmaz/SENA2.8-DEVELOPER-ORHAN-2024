//-------------------------------------------------------------------------------------------------
//MY_UPPER_COM_H
//-------------------------------------------------------------------------------------------------
#ifndef MY_UPPER_COM_H
#define MY_UPPER_COM_H
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//DEFINE_MACRO_OF_MY_UPPER_COM
//-------------------------------------------------------------------------------------------------
#define MAX_SEND_DATA_SIZE											50000
#define MAX_RECV_DATA_SIZE											50000
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_PLAYUSER_COM
//-------------------------------------------------------------------------------------------------
//DEFINE
class MyPlayUserCom
{

private :

	BOOL mCheckConnectState;

	int mZoneNumber;
	char mIP[16];
	int mPort;

	/*pthread_t m_handle;*/
	CRITICAL_SECTION m_lock;
	//pthread_mutex_t m_lock;

	SOCKET mSocket;
	SOCKADDR_IN mAddress;

	char mSendData[MAX_SEND_DATA_SIZE];
	int mSendDataSize;
	char mRecvData[MAX_RECV_DATA_SIZE];
	int mRecvDataSize;

	BOOL Connect( void );
	BOOL Send( void );
	BOOL Recv( void );
	void Close( void );

public :

	int mRecv_Result;
	int mRecv_PlayUserIndex;
	int mRecv_UserSort;
	int mRecv_GoodFellow;
	int mRecv_ClientRandom;
	int mRecv_LoginPremium;//UserSort Taþýyýcýsý
	int mRecv_LoginPremiumPCRoom;
	int mRecv_TraceState;
	char mRecv_Bonus100Money;
	int mRecv_PremiumServerExpirationDate; // ÇÁ¸®¹Ì¾ö ¼­¹ö(¿ùµå) ÀÔÀå±Ç À¯È¿ ±âÇÑ(YYYYMMDD ÇüÅÂÀÇ Á¤¼ö). // @_Premium_Server_@
	AVATAR_INFO mRecv_AvatarInfo;
	int mRecv_EffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2];
	int mRecv_CheckFirstZone;
	int mRecv_ZoneNumber;
	int mRecv_Tribe;
	int mRecv_TribeBankInfo[MAX_TRIBE_BANK_SLOT_NUM];
	int mRecv_Money;
	AUTH_INFO mRecv_AuthInfo;
    MOVE_ITEM_INFO mRecv_MoveItemInfo; // ÀÌµ¿¼­ »ç¿ë Á¤º¸.
	int mAvatarAnimalOn;

	MyPlayUserCom( void );

	BOOL Init( int tZoneNumber, char tIP[16], int tPort );
	void Free( void );

	BOOL ProcessForNetwork( void );

	void U_ZONE_OK_FOR_PLAYUSER_SEND( void );
	void U_REGISTER_USER_FOR_ZONE_0_SEND( char tID[MAX_USER_ID_LENGTH] );
	void U_REGISTER_USER_FOR_ZONE_1_SEND( int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH], char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tLogoutInfo[6] );
	void U_REGISTER_USER_FOR_ZONE_2_SEND( int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO *tAvatarInfo, int tEffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2], AUTH_INFO *tAuthInfo);
	void U_REGISTER_USER_FOR_ZONE_3_SEND( int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO *tAvatarInfo, int tEffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2], AUTH_INFO *tAuthInfo, int AnimalOn);
	void U_UNREGISTER_USER_FOR_ZONE_SEND( int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO *tAvatarInfo, AUTH_INFO *tAuthInfo);
	void U_DUPEFIX(int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO* tAvatarInfo, AUTH_INFO* tAuthInfo);
	void U_DUPEFIX1(int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO* tAvatarInfo, AUTH_INFO* tAuthInfo);
	void U_FIND_AVATAR_FOR_ZONE_SEND( char tAvatarName[MAX_AVATAR_NAME_LENGTH] );
	void U_TRIBE_BANK_INFO_SAVE_SEND( int tMoney[4] );
	void U_TRIBE_BANK_INFO_VIEW_SEND( int tTribe );
	void U_TRIBE_BANK_INFO_LOAD_SEND( int tTribe, int tTribeBankInfoIndex, int tInventoryMoney );
	void U_HACK_NAME_SEND( char tID[MAX_USER_ID_LENGTH], char tHackName[MAX_HACK_NAME_LENGTH], int tHackSize );
	void U_BLOCK_USER_FOR_ZONE_1_SEND( int tSort, char tID[MAX_USER_ID_LENGTH] );
	void U_BLOCK_USER_FOR_ZONE_2_SEND( int tSort, char tID[MAX_USER_ID_LENGTH] );
	void U_ADD_AUTO_USER_LIST_SEND( char tID[MAX_USER_ID_LENGTH], char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tWorldNumber, int tZoneNumber );
	void U_CHECK_KILL_OTHER_TRIBE_SEND( char tAvatarName1[MAX_AVATAR_NAME_LENGTH], char tAvatarName2[MAX_AVATAR_NAME_LENGTH] );
	void U_EVENT_INFO_SEND( char tID[MAX_USER_ID_LENGTH], int tSort );
	void U_CHECK_AUTH_KEY (char szID[MAX_USER_ID_LENGTH], char szAuthKey[MAX_MOUSE_PASSWORD_LENGTH]);
	void U_UPDATE_AUTH_KEY (char szID[MAX_USER_ID_LENGTH], char szAuthKey[2][MAX_MOUSE_PASSWORD_LENGTH]);
	void U_CHANGE_AVATAR_NAME_FOR_ZONE_SEND(int tPlayUserIndex, char *tChangeAvatarName);
	void U_BONUS_100_MONEY_FOR_ZONE_SEND(int tPlayUserIndex);
	void U_EVENT_FOR_ZONE_SEND(int tPlayUserIndex, int tKillNum);
	void U_EVENT_FOR_ZONE_SEND_PHONE(int tPlayUserIndex);
    void U_SET_MOVE_ITEM_FOR_ZONE_SEND( int tPlayUserIndex, MOVE_ITEM_INFO *tMoveItemInfo); // ÀÌµ¿¼­ »ç¿ë Á¤º¸¸¦ PlayUser¿¡ Àü¼ÛÇÏ´Â ÇÔ¼ö.
	void U_VALET_CHECK_ONLINE(int tPlayUserIndex, char tAvatarName[MAX_AVATAR_NAME_LENGTH]);
};
//INSTANCE
extern MyPlayUserCom mPLAYUSER_COM;
//-------------------------------------------------------------------------------------------------

class MyCenterCom
{

private :

	BOOL *mCheckSocketState;
	BOOL *mCheckConnectState;

	int mZoneNumber;
	int mZonePort;
	char mIP[16];
	int mPort;
	fd_set *m_read_fds;
	HANDLE m_handle;

	SOCKET mSocket;
	SOCKADDR_IN mAddress;

	char mSendData[MAX_SEND_DATA_SIZE];
	int mSendDataSize;
	char mRecvData[MAX_RECV_DATA_SIZE];
	int mRecvDataSize;
	int teksefer;

	BOOL Connect( void );
	BOOL Send( void );
	void Close( void );

public :
	CRITICAL_SECTION m_lock;
	MyCenterCom( void );
	void connect_thread(void);

	static void Start(void *arg);
	BOOL Init( int tZoneNumber, int tZonePort, char tIP[16], int tPort );
	BOOL ReConnect(void);
	void Free( void );

	int PROCESS_FOR_NETWORK( HWND hWnd, WPARAM wPrm, LPARAM lPrm );
	//int PROCESS_FOR_NETWORK(SOCKET cli_fd, UINT fd_status);

	void W_WORLD_INFO( void );
	void W_CPTOWER(void);
	void W_RANKINFO(void);
	void W_OLDRANKINFO(void);
	void W_ZONE_CONNECTION_INFO( void );
	void W_BROADCAST_INFO( void );
	void W_START( void );
	void W_NOTICE( void );
	void W_SET_EVENT( void );
	void W_SHUTDOWN( void );
	void W_TRIBE_CHAT( void );
	void W_SECRET_CHAT( void );
	void W_POLICE_INFO( void );
	void W_SET_GM_ORDER( void );
	void W_SERCH_AVATAR( void );
	void W_SET_GM_ORDER_MOVE_AVATAR( void );

	void W_BAN_PLAYER (void);
	void W_CHECK_EVENT( void );

	void W_RANK_TOTAL_SEND(void);
	void W_RANK_TOTAL_INFO_SEND(int TotalSize);
	// @ Cost Info Download @
	bool mIsUpdateCashItemInfo;
	bool IsUpdateCashItemInfo();
	void SetUpdateCashItemInfo(bool isUpdate);
	void W_UPDATE_CASH_ITEM_INFO_FOR_CENTER(int updateResult);  // ¸ðµç Zone¿¡°Ô Ä³½¬ ¾ÆÀÌÅÛ Á¤º¸°¡ ¾÷µ¥ÀÌÆ® µÇ¾úÀ½À» ¾Ë¸°´Ù.
	void W_UPDATE_CASH_ITEM_INFO_FOR_ZONE();
	// @

	// # X-Trap # {
	void W_XTRAP_MAP_FILE_CHANGE_FOR_ZONE( void );
	// # }

	BOOL ProcessForSend( void );

	void U_ZONE_OK_FOR_CENTER_SEND( void );
	void U_DEMAND_BROADCAST_INFO( int tInfoSort, BYTE tInfoData[MAX_BROADCAST_INFO_SIZE] );

	//int SearchAvatarforGM( char tAvatarName[MAX_AVATAR_NAME_LENGTH] );
	int SearchAvatarforGM(const char *tAvatarName);
	void MoveZone(int tUserIndex, int tZoneNumber);
	void W_RANK_INFO_SEND(void);
	void W_CENTER_GET_RANK_INFO(const char *aName, int tUserIndex);
	void W_ZONE_OTHER_CONNECTION_INFO(int tZoneNumber);
};
//INSTANCE
extern MyCenterCom mCENTER_COM;

class MyExtraCom
{

private :

	BOOL mCheckConnectState;

	int mZoneNumber;
	char mIP[16];
	int mPort;
	HANDLE m_handle;

	SOCKET mSocket;
	SOCKADDR_IN mAddress;

	char mSendData[MAX_SEND_DATA_SIZE];
	int mSendDataSize;
	char mRecvData[MAX_RECV_DATA_SIZE];
	int mRecvDataSize;

	BOOL Connect( void );
	BOOL Send( void );
	BOOL Recv( void );
	void Close( void );

public :

	int mRecv_Result;
	GUILD_INFO mRecv_GuildInfo;

	int mRecv_CashSize;
	int mRecv_BonusCashSize;
	int mRecv_CostSize;
	int mRecv_BonusCostSize;

	// @ Cost Info Download @
	bool mIsValidCashItemInfo;              // ÇöÀç °¡Áö°í ÀÖ´Â Ä³½¬ ¾ÆÀÌÅÛ Á¤º¸°¡ ÃÖ½ÅÀÎÁö ¿©ºÎ.
	int mCashItemInfoVersion;               // COST_INFO.TXTÀÇ ¹öÀü
	int mCashItemInfo[4][14][10][4];        // Å¬¶óÀÌ¾ðÆ®¿¡¼­ »ç¿ëÇÏ´Â Ä³½¬ ¾ÆÀÌÅÛ Áø¿­ Á¤º¸

	BOOL U_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_SEND();  // UpdateÇÒ ÇÊ¿ä°¡ ÀÖ´Â Áö °Ë»ç. - 37¹ø Á¸¿¡¼­¸¸ »ç¿ë
	BOOL U_GET_CASH_ITEM_INFO_FOR_EXTRA_SEND();     // Ä³½¬ ¾ÆÀÌÅÛ Á¤º¸¸¦ »õ·Î ¹Þ¾Æ ¿Â´Ù.
	// @

	int mBloodItemInfo[4][50][3];

	CRITICAL_SECTION m_lock;

	MyExtraCom( void );

	BOOL Init( int tZoneNumber, char tIP[16], int tPort );
	void Free( void );

	BOOL ProcessForNetwork( void );

	BOOL U_ZONE_OK_FOR_EXTRA_SEND( void );
	BOOL U_GUILD_WORK_FOR_EXTRA_SEND( int tSort, BYTE tData[MAX_GUILD_WORK_SIZE] );
	BOOL U_GET_CASH_SIZE_FOR_EXTRA_SEND(char tID[MAX_USER_ID_LENGTH], int* tCash, int* tBonusCash);
	// @ Cost Info Download @
	//BOOL U_BUY_CASH_ITEM_FOR_EXTRA_SEND( char tID[MAX_USER_ID_LENGTH], int tCostInfoIndex, int iIndex, int iQuantity, char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tTribe, int tLevel );
	BOOL U_BUY_CASH_ITEM_FOR_EXTRA_SEND( char tID[MAX_USER_ID_LENGTH], int tCostInfoIndex, int iIndex, int iQuantity, char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tTribe, int tLevel, int tVersion );
	// @
	BOOL U_BUY_BLOOD_ITEM_FOR_EXTRA_SEND(int index);

	// 2009.12.16 ÅÍÅ°¿¡¼­¸¸ »ç¿ëÇÕ´Ï´Ù.
	// ÆÐÅ°Áö ¾ÆÀÌÅÛ(1418 ~ 1423) »ç¿ë ½Ã º¸³Ê½º Ä³½¬ Áö±Þ ¿äÃ» ÇÔ¼ö.
	BOOL U_USE_PACKAGE_ITEM_FOR_EXTRA_SEND( char tID[MAX_USER_ID_LENGTH], int iIndex, char tAvatarName[MAX_AVATAR_NAME_LENGTH] );
};
//INSTANCE
extern MyExtraCom mEXTRA_COM;
//-------------------------------------------------------------------------------------------------

//CLASS_OF_MY_RELAY_COM
//-------------------------------------------------------------------------------------------------
//DEFINE
class MyRelayCom
{

private :

	BOOL *mCheckSocketState;
	BOOL *mCheckConnectState;

	int mZoneNumber;
	char mIP[16];
	int mPort;
	fd_set *m_read_fds;
	HANDLE m_handle;

	SOCKET mSocket;
	SOCKADDR_IN mAddress;

	char mSendData[MAX_SEND_DATA_SIZE];
	int mSendDataSize;
	char mRecvData[MAX_RECV_DATA_SIZE];
	int mRecvDataSize;

	BOOL Connect( void );
	BOOL Send( void );
	void Close( void );

public :

	CRITICAL_SECTION m_lock;
	MyRelayCom( void );
	void connect_thread(void);

	static void *Start(void *arg);
	BOOL Init( int tZoneNumber, char tIP[16], int tPort );
	void Free( void );

	int PROCESS_FOR_NETWORK( HWND hWnd, WPARAM wPrm, LPARAM lPrm );
	//int PROCESS_FOR_NETWORK(SOCKET cli_fd, UINT fd_status);


	void W_BROADCAST_DATA( void );

	BOOL ProcessForSend( void );

	void U_ZONE_OK_FOR_RELAY_SEND( void );
	void U_DEMAND_BROADCAST_DATA( int tSort, BYTE tData[MAX_BROADCAST_DATA_SIZE] );

};
//INSTANCE
extern MyRelayCom mRELAY_COM;
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_GAMELOG
//-------------------------------------------------------------------------------------------------
//DEFINE
class MyGameLog
{

private:

	BOOL mCheckConnectState;

	SOCKET mSocket;
	SOCKADDR_IN mAddress;

	int mLogSort;
	char mGameLogData[10000];
	char mSendBuffer[(10000 * 2)];

	BOOL CheckValidState(int tUserIndex);

public:

	MyGameLog(void);

	BOOL Init(char tIP[16], int tPort);
	void Free(void);

	void SendToLogServer(int Sort);
	void SendToLogServerForDB(void);
	void GL_USE_INVENTORY_ITEM(int tUserIndex, int iIndex, char UseItemId[25],int iQuantity, int iValue, int GainItemtIndex,char ItemId[25], int tQuantity, int tValue);
	void GL_IMPROVE_ITEM(int tUserIndex, int iIndex, char UseItemId[25], int OldValue, int NewValue, char Sonuc[50]);
	void GL_ADD_ITEM(int tUserIndex, int iIndex, char UseItemId[25], int OldValue, int NewValue, int tcost,char Sonuc[50], int iIndex2, char UseItemId2[25]);
	void GL_EXCHANGE_ITEM(int tUserIndex, int iIndex, char UseItemId[25], int iIndex1, char UseItemId1[25]);
	void GL_MAKE_ITEM(int tUserIndex, int iIndex, char UseItemId[25], int iIndex1, char UseItemId1[25], int iIndex2, char UseItemId2[25], int iIndex3, char UseItemId3[25], int iIndex4, char UseItemId4[25]);
	void GL_BUY_SHOP_ITEM(int tUserIndex,int tOtherUserIndex,int iIndex, char UseItemId[25],int tValue, int soket1,int soket2,int soket3, int tCost);
	void GL_COSTUME_ITEM(int tUserIndex, int iIndex, char UseItemId[25]);
	void GL_CRAFT_ITEM(int tUserIndex, int iIndex, char UseItemId[25], int OldValue, int NewValue, char Sonuc[50]);
	void GL_DAILY_ITEM(int tUserIndex, int iIndex, char UseItemId[25]);
	void GL_PETCOMBINE_ITEM(int tUserIndex, int iIndex, char UseItemId[25], int iIndex1, char UseItemId1[25], int iIndex2, char UseItemId2[25], int iIndex3, char UseItemId3[25], int iIndex4, char UseItemId4[25]);
	void GL_OPEN_SOKET_ITEM(int tUserIndex, int iIndex, char UseItemId[25],int hole);
	void GL_SELL_SOKET_ITEM(int tUserIndex, int iIndex, char UseItemId[25]);
	void GL_RANK_PRIZE(int tUserIndex, int iIndex);
	void GL_CAPSUL_ITEM(int tUserIndex, int iIndex, char UseItemId[25]);
	void GL_BUY_VALET_ITEM(int tUserIndex, int tOtherUserIndex, int iIndex, char UseItemId[25], int tValue, int soket1, int soket2, int soket3, int tCost);
	void GL_GET_VALET_MONEY_ITEM(int tUserIndex,int iIndex, int iIndex1);
	void GL_GAIN_FISH(int tUserIndex, int iIndex, char UseItemId[25]);
	void GL_QUIT_LOG(const char* Id, const char* Name, const char* tFileName, const char* tFuncName, int tLine);
	void GL_GAIN_KILLOTHERTRIBE_ITEM(int tUserIndex, int tOtherUserIndex,int iIndex, char UseItemId[25]);
	void GL_615_TRADE_ITEM(int tUserIndex, int tOtherIndex, int ItemId, const char* ItemName, int iValue, int iQuantity, int Soket1, int Soket2, int Soket3);
	void GL_616_TRADE_MONEY(int tUserIndex, int tOtherIndex, int tValue, int tValue1);
	void GL_BAN_SEND(int tUserIndex, const char* tFileName = __FILE__, const char* tFuncName = NULL, int tLine = __LINE__);
	void GL_DIFFERENT_CLIENT_LOGIN(int tUserIndex, int clientControl, int clientRandom, const char* tFileName, const char* tFuncName, int tLine);
	void GL_MAKE_SKILL(int tUserIndex, int iIndex);
	void GL_PLUSS_STATE(int tUserIndex, int tSort, int state , int vitality , int strenght, int aKi, int winsdom);
	void GL_BUY_CASH_ITEM(int tUserIndex, int item, const char* aName, int CashItemFiyat, int CostFiyat);
	void GL_GAIN_ITEM(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, const char* aName);
	void GL_STROESLOT_ITEM(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, const char* aName, const char* Action);
	void GL_SAVESLOT_ITEM(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, const char* aName, const char* Action);
};

//INSTANCE
extern MyGameLog mGAMELOG;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_PLAYUSER_COM
//-------------------------------------------------------------------------------------------------
//DEFINE
class MyValetInfo
{

private:

	BOOL mCheckConnectState;

	int mZoneNumber;
	char mIP[16];
	int mPort;

	/*pthread_t m_handle;*/
	CRITICAL_SECTION m_lock;
	//pthread_mutex_t m_lock;

	SOCKET mSocket;
	SOCKADDR_IN mAddress;

	char mSendData[MAX_SEND_DATA_SIZE];
	int mSendDataSize;
	char mRecvData[MAX_RECV_DATA_SIZE];
	int mRecvDataSize;

	BOOL Connect(void);
	BOOL Send(void);
	BOOL Recv(void);
	void Close(void);

public:

	int mRecv_Result;
	VALETSHOP_INFO mRecv_ValetInfo;

	MyValetInfo(void);
	BOOL Init(int tZoneNumber, char tIP[16], int tPort);
	void Free(void);
	BOOL ProcessForNetwork(void);
	void U_ZONE_OK_FOR_VALET_SEND(void);
	void U_VALET_INFO(int tPlayUserIndex, char tAvatarName[MAX_AVATAR_NAME_LENGTH]);
	void U_VALET_UPDATE(char tAvatarName[MAX_AVATAR_NAME_LENGTH], VALETSHOP_INFO* tValetShop);
	void U_VALET_BUY(int tSort, char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tPage, int tSlot, int ItemNumber);
};
//INSTANCE
extern MyValetInfo mVALETINFO;
//-------------------------------------------------------------------------------------------------
#endif