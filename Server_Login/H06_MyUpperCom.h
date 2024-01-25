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

	char mIP[16];
	int mPort;

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
	int mRecv_PresentUserNum;

	MyPlayUserCom( void );

	BOOL Init( char tIP[16], int tPort );
	void Free( void );

	BOOL ProcessForNetwork( void );

	void U_LOGIN_OK_FOR_PLAYUSER_SEND( void );
	void U_REGISTER_USER_FOR_LOGIN_1_SEND( char tIP[16], char tID[MAX_USER_ID_LENGTH], int tUserSort, int tGoodFellow, int tUserRandom, int tLoginPremium, int tLoginPremiumPCRoom, int tTraceState, char tBonus100Money, int tPremiumServerExpirationDate, AUTH_INFO *tAuthInfo ); // 함수 선언 수정 - int tPremiumServerExpirationDate 추가. // @_Premium_Server_@
	void U_REGISTER_USER_FOR_LOGIN_2_SEND( int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH] );
	void U_REGISTER_USER_FOR_LOGIN_3_SEND( int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO *tAvatarInfo );
	void U_UNREGISTER_USER_FOR_LOGIN_SEND( int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH] );
	void U_GET_PRESENT_USER_NUM_FOR_LOGIN_SEND( void );
	void U_BLOCK_USER_FOR_LOGIN_1_SEND( int tSort, char tID[MAX_USER_ID_LENGTH] );
	void U_BLOCK_USER_FOR_LOGIN_2_SEND( int tSort, char tID[MAX_USER_ID_LENGTH] );

	void U_USER_EXT_SEND( int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH] );

};
//INSTANCE
extern MyPlayUserCom mPLAYUSER_COM;


//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_CENTER_COM
//-------------------------------------------------------------------------------------------------
//DEFINE
class MyCenterCom
{

private :

	BOOL mCheckConnectState;

	char mIP[16];
	int mPort;

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
	char mRecv_IP[16];
	int mRecv_Port;

	MyCenterCom( void );

	BOOL Init( char tIP[16], int tPort );
	void Free( void );

	BOOL ProcessForNetwork( void );

	void U_LOGIN_OK_FOR_CENTER_SEND( void );
	void U_GET_ZONE_SERVER_INFO_1( int tZoneNumber );

};
//INSTANCE
extern MyCenterCom mCENTER_COM;

#endif
//-------------------------------------------------------------------------------------------------