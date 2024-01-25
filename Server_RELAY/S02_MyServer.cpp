//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "Shengming.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_SERVER
//-------------------------------------------------------------------------------------------------
//INSTANCE
MyServer mSERVER;
//CREATE
MyServer::MyServer( void )
{
}
//INIT
BOOL MyServer::Init( int *tResult )
{
	int index01;
	if( !SetTimer( hMainWindow, 1, 10000, NULL ) )
	{
		*tResult = 1;
		return FALSE;
	}
	ZeroMemory( &mWsaData, sizeof( WSADATA ) );
	if( WSAStartup( MAKEWORD( 2, 2 ), &mWsaData ) != 0 )
	{
		*tResult = 2;
		return FALSE;
	}
	mSocket = socket( AF_INET, SOCK_STREAM, 0 );
	if( mSocket == INVALID_SOCKET )
	{
		*tResult = 3;
		return FALSE;
	}
	mAddress.sin_family = AF_INET;
	mAddress.sin_addr.s_addr = htonl( INADDR_ANY );
	mAddress.sin_port = htons( mSERVER_INFO.mServerPort );
	if( bind( mSocket, (LPSOCKADDR) &mAddress, sizeof( mAddress ) ) == SOCKET_ERROR )
	{
		*tResult = 4;
		return FALSE;
	}
	if( listen( mSocket, SOMAXCONN ) == SOCKET_ERROR )
	{
		*tResult = 5;
		return FALSE;
	}
	if( WSAAsyncSelect( mSocket, hMainWindow, WM_NETWORK_MESSAGE_1, FD_ACCEPT|FD_CLOSE|FD_READ|FD_WRITE ) == SOCKET_ERROR )
	{
		*tResult = 6;
		return FALSE;
	}

	mUSER = (MyUser *) GlobalAlloc( GMEM_FIXED, ( MAX_USER_NUM * sizeof( MyUser ) ) );
	if( mUSER == NULL )
	{
		*tResult = 7;
		return FALSE;
	}
	for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
	{
		mUSER[index01].mBUFFER_FOR_SEND = NULL;
		mUSER[index01].mBUFFER_FOR_RECV = NULL;
	}
	for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
	{
		if( !mUSER[index01].Init( MAX_SEND_BUFFER_SIZE, MAX_RECV_BUFFER_SIZE ) )
		{
			*tResult = 8;
			return FALSE;
		}
	}
	if (!mGAMELOG.Init("127.0.0.1", 25021))
	{
		*tResult = 236;
		printf("![%s] : Player server start\n", __FUNCTION__);
		return FALSE;
	}
	if( !mWORK.Init() )
	{
		*tResult = 9;
		return FALSE;
	}
	__LogMgr()->Log( "![%s] : Work start \n", __FUNCTION__ );
	if( !mTRANSFER.Init() )
	{
		*tResult = 10;
		return FALSE;
	}
	__LogMgr()->Log( "![%s] : Transfer start \n", __FUNCTION__ );
	return TRUE;
}
//FREE
void MyServer::Free( void )
{
	int index01;

	mTRANSFER.Free();
	mWORK.Free();
	if( mUSER )
	{
		for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
		{
			mUSER[index01].Quit( 0 );
		}
		for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
		{
			mUSER[index01].Free();
		}
		GlobalFree( mUSER );
		mUSER = NULL;
	}
	closesocket( mSocket );
	WSACleanup();
}
//PROCESS_FOR_NETWORK
int MyServer::PROCESS_FOR_NETWORK( HWND hWnd, WPARAM wPrm, LPARAM lPrm )
{
	int index01;
	int tAddressLength;
	SOCKET tSocket;
	SOCKADDR_IN	tAddress;
	int tempUserIndex;
	int tRecvSizeFromUser;
	BYTE tProtocol;

	tSocket = (SOCKET) wPrm;
	switch( WSAGETSELECTEVENT( lPrm ))
	{
	case FD_READ :
		for( tempUserIndex = 0 ; tempUserIndex < MAX_USER_NUM ; tempUserIndex++ )
		{
			if( !mUSER[tempUserIndex].mCheckConnectState )
			{				
				continue;
			}		
			if( mUSER[tempUserIndex].mSocket == tSocket )
			{
				break;
			}
		}
		if( tempUserIndex == MAX_USER_NUM )
		{
			return -1;
		}	
		//AGAIN:
		while(1) 
		{
			tRecvSizeFromUser = recv( tSocket, &mUSER[tempUserIndex].mBUFFER_FOR_RECV[mUSER[tempUserIndex].mTotalRecvSize], ( MAX_RECV_BUFFER_SIZE - mUSER[tempUserIndex].mTotalRecvSize ), 0 );	
			if( tRecvSizeFromUser <= 0 )
			{
				if( tRecvSizeFromUser == SOCKET_ERROR )
				{
					if( WSAGetLastError() == WSAEWOULDBLOCK )
					{
						return 0;
					}
				}
				mUSER[tempUserIndex].Quit(10002);
				return 0;
			}

			mUSER[tempUserIndex].mTotalRecvSize += tRecvSizeFromUser;
			break;
		}
			while( TRUE )
			{

				if( mUSER[tempUserIndex].mTotalRecvSize < 1 )
				{
				mUSER[tempUserIndex].Quit(10003);
				return 0;
				}
				tProtocol = (BYTE) mUSER[tempUserIndex].mBUFFER_FOR_RECV[0];
				if( W_FUNCTION[tProtocol].PROC == NULL )
				{
					mUSER[tempUserIndex].Quit( 1002 );
					return 0;
				}
				if( mUSER[tempUserIndex].mTotalRecvSize < mWORK.mWorkerPacketSize[tProtocol] )
				{
				return -1;
				}
				W_FUNCTION[tProtocol].PROC( tempUserIndex );
				if( mUSER[tempUserIndex].mCheckConnectState )
				{
					MoveMemory( &mUSER[tempUserIndex].mBUFFER_FOR_RECV[0], &mUSER[tempUserIndex].mBUFFER_FOR_RECV[mWORK.mWorkerPacketSize[tProtocol]], ( mUSER[tempUserIndex].mTotalRecvSize - mWORK.mWorkerPacketSize[tProtocol] ) );
					mUSER[tempUserIndex].mTotalRecvSize -= mWORK.mWorkerPacketSize[tProtocol];
				}
				if(mUSER[tempUserIndex].mTotalRecvSize == 0)
					break;
			}
			return tRecvSizeFromUser;
	case FD_WRITE :
			for( tempUserIndex = 0 ; tempUserIndex < MAX_USER_NUM ; tempUserIndex++ )
			{
				if( !mUSER[tempUserIndex].mCheckConnectState )
				{
					continue;
				}			
				if( mUSER[tempUserIndex].mSocket == tSocket )
				{
				break;
			}
		}
		if( tempUserIndex == MAX_USER_NUM )
		{
			return -1;
		}
		mUSER[tempUserIndex].Send( FALSE, NULL, 0 );
		return 1;

	case FD_ACCEPT :
		tAddressLength = sizeof( tAddress );
		tSocket = accept( mSocket, (LPSOCKADDR) &tAddress, &tAddressLength );
		for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
		{
			if( !mUSER[index01].mCheckConnectState )
			{
				break;
			}
		}
		if( index01 == MAX_USER_NUM )
		{
			return 0;
		}

		mUSER[index01].mCheckConnectState = TRUE;
		mUSER[index01].mUsedTime = GetTickCount();
		mUSER[index01].mSocket = tSocket;	
		sprintf( mUSER[index01].mIP, "%s", inet_ntoa(tAddress.sin_addr));
		mUSER[index01].mTotalSendSize = 0;
		mUSER[index01].mTotalRecvSize = 0;
		mUSER[index01].mCheckServerType = 0;
		mTRANSFER.B_CONNECT_OK();
		mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return 1;
	case FD_CLOSE :
		for( tempUserIndex = 0 ; tempUserIndex < MAX_USER_NUM ; tempUserIndex++ )
		{
			if( !mUSER[tempUserIndex].mCheckConnectState )
			{
				continue;
			}
			
			if( mUSER[tempUserIndex].mSocket == tSocket )
			{
				break;
			}
		}
		if( tempUserIndex == MAX_USER_NUM )
		{
			return 0;
		}
		mUSER[tempUserIndex].Quit( 0 );
		return 0;
	}
}
//PROCESS_FOR_TIMER
void MyServer::PROCESS_FOR_TIMER( void )
{
	int index01;
	DWORD tPresentTime;

	tPresentTime = GetTickCount();
	for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
	{
		if( !mUSER[index01].mCheckConnectState )
		{
			continue;
		}
		if( ( tPresentTime - mUSER[index01].mUsedTime ) > 1800000 )
		{
			__LogMgr()->Log("![%s] : %u %u\n", __FUNCTION__, tPresentTime, mUSER[index01].mUsedTime);
			mUSER[index01].Quit( 1003 );
		}
	}
}
#ifdef __WIN32__
//WRITE_FOR_ERROR
void MyServer::WRITE_FOR_ERROR( char *tErrorData )
{

	char tempString01[10000];
	char tempString02[10000];
	time_t tCountSeconds;
	struct tm *tPresentTime;
	HANDLE hFile;
	DWORD nWriteByte;

	time( &tCountSeconds );
	tPresentTime = localtime( &tCountSeconds );
	if( tPresentTime == NULL )
	{
		return;
	}
	strcpy( tempString01, "LOG\\ERROR_" );
	itoa( ( tPresentTime->tm_year + 1900 ), tempString02, 10 );
	strcat( tempString01, tempString02 );
	strcat( tempString01, "-" );
	if( tPresentTime->tm_mon < 9 )
	{
		tempString02[0] = '0';
		tempString02[1] = tPresentTime->tm_mon + 1 + '0';
		tempString02[2] = '\0';
	}
	else
	{
		itoa( ( tPresentTime->tm_mon + 1 ), tempString02, 10 );
	}
	strcat( tempString01, tempString02 );
	strcat( tempString01, "-" );
	if( tPresentTime->tm_mday < 10 )
	{
		tempString02[0] = '0';
		tempString02[1] = tPresentTime->tm_mday + '0';
		tempString02[2] = '\0';
	}
	else
	{
		itoa( tPresentTime->tm_mday, tempString02, 10 );
	}
	strcat( tempString01, tempString02 );
	strcat( tempString01, ".TXT" );
	sprintf( tempString02, "[%d:%d:%d] %s\r\n", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec, tErrorData );
	hFile = CreateFile(	tempString01, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
	if( hFile == INVALID_HANDLE_VALUE )
	{
		return;
	}
	if( SetFilePointer( hFile, 0, 0, FILE_END ) == 0xFFFFFFFF )
	{
		CloseHandle( hFile );
		return;
	}
	if( !WriteFile( hFile, tempString02, strlen( tempString02 ), &nWriteByte, NULL ) )
	{
		CloseHandle( hFile );
		return;
	}
	if( nWriteByte != strlen( tempString02 ) )
	{
		CloseHandle( hFile );
		return;
	}
	if( !CloseHandle( hFile ) )
	{
		return;
	}

}
#endif
//-------------------------------------------------------------------------------------------------

