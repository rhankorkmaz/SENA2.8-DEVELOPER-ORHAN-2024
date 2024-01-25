#ifndef MY_SERVER_H
#define MY_SERVER_H

class MyServer
{
public :

	WSADATA mWsaData;
	SOCKET mSocket;
	SOCKADDR_IN mAddress;

	bool mRankCheck;
	int mMAX_USER_NUM;
	int mMAX_SEND_BUFFER_SIZE;
	int mMAX_RECV_BUFFER_SIZE;

	MyServer( void );

	BOOL Init( int *tResult );
	//void Free( void );

	int set_nodelay(int cli_fd);
	int set_nonblock(int cli_fd);

	int PROCESS_FOR_NETWORK( HWND hWnd, WPARAM wPrm, LPARAM lPrm );
	void HexDump(char *buf,int len,int addr);//¥Ú”°
	void Free(void);
};
//INSTANCE
extern MyServer mSERVER;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
