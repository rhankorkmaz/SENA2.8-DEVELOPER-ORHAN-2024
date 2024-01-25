//-------------------------------------------------------------------------------------------------
//MY_SERVER_H
//-------------------------------------------------------------------------------------------------
#include <WinSock2.h>
#ifndef MY_SERVER_H
#define MY_SERVER_H
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_SERVER
//-------------------------------------------------------------------------------------------------
//DEFINE
class MyServer
{

private :

	WSADATA mWsaData;

	SOCKET mSocket;
	SOCKADDR_IN mAddress;

public :

	MyServer( void );

	BOOL Init( int *tResult );
	void Free( void );

	void PROCESS_FOR_NETWORK( HWND hWnd, WPARAM wPrm, LPARAM lPrm );

	void WRITE_FOR_LOG( char *tLogData );
	void WRITE_FOR_GENERAL_CHAT_LOG( char *tLogData );
	void WRITE_FOR_SECRET_CHAT_LOG(char* tLogData);
	void WRITE_FOR_GENERAL_SHOUT_CHAT_LOG(char* tLogData);
	void WRITE_FOR_PARTY_CHAT_LOG(char* tLogData);
	void WRITE_FOR_GUILD_CHAT_LOG(char* tLogData);
	void WRITE_FOR_TRIBE_CHAT_LOG(char* tLogData);
	void WRITE_FOR_FUNCTION_CHAT_LOG(char* tLogData);



	void WRITE_FOR_USE_ITEM_LOG(int Map ,char* tLogData);
	void WRITE_FOR_IMPROVE_ITEM_LOG(int Map, char* tLogData);
	void WRITE_FOR_ADD_ITEM_LOG(int Map, char* tLogData);
	void WRITE_FOR_EXCHANGE_ITEM_LOG(int Map, char* tLogData);
	void WRITE_FOR_HIGH_ITEM_LOG(int Map, char* tLogData);
	void WRITE_FOR_LOW_ITEM_LOG(int Map, char* tLogData);
	void WRITE_FOR_MAKE_ITEM_LOG(int Map, char* tLogData);
	void WRITE_FOR_MAKE_SKILL_LOG(int Map, char* tLogData);
	void WRITE_FOR_SHOP_BUY_ITEM_LOG(int Map, char* tLogData);
	void WRITE_FOR_BUY_CASH_ITEM_LOG(int Map, char* tLogData);
	void WRITE_FOR_TRADE_ITEM_LOG(int Map, char* tLogData);
	void WRITE_FOR_COSTUME_ITEM_LOG(int Map, char* tLogData);
	void WRITE_FOR_CRAFT_ITEM_LOG(int Map, char* tLogData);
	void WRITE_FOR_DAILY_ITEM_LOG(int Map, char* tLogData);
	void WRITE_FOR_PET_COMBINE_LOG(int Map, char* tLogData);
	void WRITE_FOR_OPEN_HOLE_SOKET_ITEM_LOG(int Map, char* tLogData);
	void WRITE_FOR_ADD_HOLE_SOKET_ITEM_LOG(int Map, char* tLogData);
	void WRITE_FOR_ADD_SOKET_ITEM_LOG(int Map, char* tLogData);
	void WRITE_FOR_DELETE_SOKET_ITEM_LOG(int Map, char* tLogData);
	void WRITE_FOR_RANK_REWARDS_LOG(int Map, char* tLogData);
	void WRITE_FOR_BUY_CAPSULE_ITEM_LOG(int Map, char* tLogData);
	void WRITE_FOR_BUY_VALET_SHOP_ITEM_LOG(int Map, char* tLogData);
	void WRITE_FOR_FISHING_ITEM_LOG(int Map, char* tLogData);
	void WRITE_FOR_BUY_BLOOD_ITEM_LOG(int Map, char* tLogData);
	void WRITE_FOR_QUIT_LOG(int Map, char* tLogData);
	void WRITE_FOR_KILL_OTHER_TRIBE(int Map, char* tLogData);
	void WRITE_FOR_TRADE_LOG(int Map, char* tLogData);
	void WRITE_FOR_BAN(int Map, char* tLogData);
	void WRITE_SKILL_PLUSS(int Map, char* tLogData);
	void WRITE_BUY_CASH_ITEM(int Map, char* tLogData);
	void WRITE_BUY_GET_ITEM(int Map, char* tLogData);
	void WRITE_BUY_STORE_ITEM(int Map, char* tLogData);
	void WRITE_BUY_SAVE_ITEM(int Map, char* tLogData);
};
//INSTANCE
extern MyServer mSERVER;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_DB
//-------------------------------------------------------------------------------------------------
//DEFINE
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
