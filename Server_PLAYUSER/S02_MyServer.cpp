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

	//srand( (unsigned int) time( NULL ) );

	if( !SetTimer( hMainWindow, 1, 1000, NULL ) )
	{
		*tResult = 1;
		return FALSE;
	}

	if( !mDB.Init() )
	{
		*tResult = 2;
		return FALSE;
	}

	ZeroMemory( &mWsaData, sizeof( WSADATA ) );
	if( WSAStartup( MAKEWORD( 2, 2 ), &mWsaData ) != 0 )
	{
		*tResult = 3;
		return FALSE;
	}
	mSocket = socket( AF_INET, SOCK_STREAM, 0 );
	if( mSocket == INVALID_SOCKET )
	{
		*tResult = 4;
		return FALSE;
	}
	mAddress.sin_family = AF_INET;
	mAddress.sin_addr.s_addr = htonl( INADDR_ANY );
	mAddress.sin_port = htons( mSERVER_INFO.mServerPort );
	if( bind( mSocket, (LPSOCKADDR) &mAddress, sizeof( mAddress ) ) == SOCKET_ERROR )
	{
		*tResult = 5;
		return FALSE;
	}
	if( listen( mSocket, SOMAXCONN ) == SOCKET_ERROR )
	{
		*tResult = 6;
		return FALSE;
	}
	if( WSAAsyncSelect( mSocket, hMainWindow, WM_NETWORK_MESSAGE_1, FD_ACCEPT|FD_CLOSE|FD_READ|FD_WRITE ) == SOCKET_ERROR )
	{
		*tResult = 7;
		return FALSE;
	}

	mUSER = (MyUser *) GlobalAlloc(GMEM_FIXED, ( MAX_USER_NUM * sizeof(MyUser)));
	if( mUSER == NULL )
	{
		*tResult = 9;
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
			*tResult = 10;
			return FALSE;
		}
	}
	if( !mWORK.Init() )
	{
		*tResult = 11;
		return FALSE;
	}
	if( !mTRANSFER.Init() )
	{
		*tResult = 12;
		return FALSE;
	}
	if( !mGAME.Init() )
	{
		*tResult = 13;
		return FALSE;
	}
	return TRUE;
}
//FREE
void MyServer::Free( void )
{
	int index01;

	mGAME.Free();
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
	mDB.Free();
}
//PROCESS_FOR_NETWORK
int MyServer::PROCESS_FOR_NETWORK(HWND hWnd, WPARAM wPrm, LPARAM lPrm)
{
	int index01;
	int tAddressLength;
	SOCKET tSocket;
	int tempUserIndex;
	int tRecvSizeFromUser;
	BYTE tProtocol;
	in_addr     tAddress ;
	struct sockaddr_in ClientAddr;

	tSocket = (SOCKET) wPrm;
	switch(WSAGETSELECTEVENT( lPrm ))
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
			tRecvSizeFromUser = recv(tSocket, &mUSER[tempUserIndex].mBUFFER_FOR_RECV[mUSER[tempUserIndex].mTotalRecvSize],( MAX_RECV_BUFFER_SIZE - mUSER[tempUserIndex].mTotalRecvSize ), 0 );
			if( tRecvSizeFromUser <= 0 )
			{
				if( tRecvSizeFromUser == SOCKET_ERROR )
				{
					if( WSAGetLastError() == WSAEWOULDBLOCK )
					{
						return 0;
					}
				}
				mUSER[tempUserIndex].Quit(1001);
				return 0;
			}
			mUSER[tempUserIndex].mTotalRecvSize += tRecvSizeFromUser;
			while(TRUE) 
			{
				if( mUSER[tempUserIndex].mTotalRecvSize < 1 ) 
				{
					mUSER[tempUserIndex].Quit( 10002 );
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
					MoveMemory( &mUSER[tempUserIndex].mBUFFER_FOR_RECV[0], &mUSER[tempUserIndex].mBUFFER_FOR_RECV[mWORK.mWorkerPacketSize[tProtocol]], ( mUSER[tempUserIndex].mTotalRecvSize - mWORK.mWorkerPacketSize[tProtocol]));
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
				if(mUSER[tempUserIndex].mSocket == tSocket)
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
			tAddressLength = sizeof(ClientAddr);
			tSocket = accept(tSocket, (struct sockaddr*)&ClientAddr, &tAddressLength); 
			for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
			{
				if( !mUSER[index01].mCheckConnectState )
				{
					break;
				}
			}
			//LOG_TO_FILE_2("!!!!!!!!!!!!!!!!!!!!!!! %d %d\n", index01, MAX_USER_NUM);
			if( index01 == MAX_USER_NUM )
			{
				closesocket( tSocket );
				return 0;
			}

			mUSER[index01].mCheckConnectState = TRUE;
			mUSER[index01].mUsedTime = GetTickCount();
			mUSER[index01].mSocket = tSocket;
			//mUSER[index01].mEPFD = *(((arg_t *)arg)->epfd);
			__LogMgr()->Log("客户进入:%s:%d",inet_ntoa(ClientAddr.sin_addr),ClientAddr.sin_port);
			strncpy (mUSER[index01].mIP, inet_ntoa(ClientAddr.sin_addr), 15);
			//sprintf( mUSER[index01].mIP, "%s", inet_ntoa(((struct in_addr)((arg_t *)arg)->cli_addr->sin_addr)));
			mUSER[index01].mTotalSendSize = 0;
			mUSER[index01].mTotalRecvSize = 0;
			mUSER[index01].mCheckServerType = 0;
			mTRANSFER.B_CONNECT_OK();
			mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			//LOG_TO_FILE_3("MAX_USER_NUM : %d %d %d\n", MAX_USER_NUM, index01, mTRANSFER.mOriginalSize);
			return 1;
		case FD_CLOSE :
			for( tempUserIndex = 0 ; tempUserIndex < MAX_USER_NUM ; tempUserIndex++ )
			{
				if( !mUSER[tempUserIndex].mCheckConnectState )
				{
					continue;
				}
				if( mUSER[tempUserIndex].mSocket == tSocket)
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
	mGAME.mTickCount++;
	if( ( mGAME.mTickCount % 6 ) == 0 )
	{
		mGAME.ProcessForPlayUser();
	}
	char buffer[111];
	snprintf(buffer,111, "Current user num : %d", mGAME.ReturnPresentUserNum(0));
	SetConsoleTitleA(buffer);
}
//-------------------------------------------------------------------------------------------------
