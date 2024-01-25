//-------------------------------------------------------------------------------------------------
//MY_SERVER_H
//-------------------------------------------------------------------------------------------------
#ifndef MY_SERVER_H
#define MY_SERVER_H
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_SERVER
//-------------------------------------------------------------------------------------------------
//MACRO
#define MAX_USER_NUM												MAX_ZONE_NUMBER_NUM
#define MAX_SEND_BUFFER_SIZE										1000000
#define MAX_RECV_BUFFER_SIZE										100000


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

	int PROCESS_FOR_NETWORK( HWND hWnd, WPARAM wPrm, LPARAM lPrm );

	//int PROCESS_FOR_NETWORK(SOCKET *cli_fd, UINT fd_status, void *arg);
	
	void PROCESS_FOR_TIMER( void );

	void WRITE_FOR_ERROR( char *tErrorData );

};
//INSTANCE
extern MyServer mSERVER;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
