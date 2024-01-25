#pragma once
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
	void GL_USE_INVENTORY_ITEM();
	void GL_IMPROVE_ITEM(int tUserIndex, int iIndex, char UseItemId[25], int OldValue, int NewValue, char Sonuc[50]);
	void GL_ADD_ITEM(int tUserIndex, int iIndex, char UseItemId[25], int OldValue, int NewValue, int tcost, char Sonuc[50]);
	void GL_EXCHANGE_ITEM(int tUserIndex, int iIndex, char UseItemId[25], int iIndex1, char UseItemId1[25]);
	void GL_MAKE_ITEM(int tUserIndex, int iIndex, char UseItemId[25], int iIndex1, char UseItemId1[25], int iIndex2, char UseItemId2[25], int iIndex3, char UseItemId3[25], int iIndex4, char UseItemId4[25]);
	void GL_BUY_SHOP_ITEM(int tUserIndex, int tOtherUserIndex, int iIndex, char UseItemId[25], int tValue, int soket1, int soket2, int soket3, int tCost);
	void GL_COSTUME_ITEM(int tUserIndex, int iIndex, char UseItemId[25]);
	void GL_CRAFT_ITEM(int tUserIndex, int iIndex, char UseItemId[25], int OldValue, int NewValue, char Sonuc[50]);
	void GL_DAILY_ITEM(int tUserIndex, int iIndex, char UseItemId[25]);
	void GL_PETCOMBINE_ITEM(int tUserIndex, int iIndex, char UseItemId[25], int iIndex1, char UseItemId1[25], int iIndex2, char UseItemId2[25], int iIndex3, char UseItemId3[25], int iIndex4, char UseItemId4[25]);
	void GL_OPEN_SOKET_ITEM(int tUserIndex, int iIndex, char UseItemId[25], int hole);
	void GL_SELL_SOKET_ITEM(int tUserIndex, int iIndex, char UseItemId[25]);
	void GL_RANK_PRIZE(int tUserIndex, int iIndex);
	void GL_CAPSUL_ITEM(int tUserIndex, int iIndex, char UseItemId[25]);
	void GL_BUY_VALET_ITEM(int tUserIndex, int tOtherUserIndex, int iIndex, char UseItemId[25], int tValue, int soket1, int soket2, int soket3, int tCost);
	void GL_GET_VALET_MONEY_ITEM(int tUserIndex, int iIndex, int iIndex1);
	void GL_GAIN_FISH(int tUserIndex, int iIndex, char UseItemId[25]);
	void GL_QUIT_LOG(const char* Id, const char* Name, const char* tFileName, const char* tFuncName, int tLine);
	void GL_GAIN_KILLOTHERTRIBE_ITEM(int tUserIndex, int tOtherUserIndex, int iIndex, char UseItemId[25]);
	void GL_615_TRADE_ITEM(int tUserIndex, int tOtherIndex, int ItemId, const char* ItemName, int iValue, int iQuantity, int Soket1, int Soket2, int Soket3);
	void GL_616_TRADE_MONEY(int tUserIndex, int tOtherIndex, int tValue, int tValue1);
};

//INSTANCE
extern MyGameLog mGAMELOG;