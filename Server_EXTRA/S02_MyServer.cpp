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

	srand( (unsigned int) time( NULL ) );
	if( !SetTimer( hMainWindow, 1, 10000, NULL ) )
	{
		*tResult = 1;
		return FALSE;
	}

	if( !mDB.Init() )
	{
		*tResult = 1;
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
	mUSER = (MyUser *)calloc(1, ( MAX_USER_NUM * sizeof( MyUser ) ) );
	if( mUSER == NULL )
	{
		*tResult = 8;
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
			*tResult = 9;
			return FALSE;
		}
	}
	__LogMgr()->Log("![%s] : User mempry set OK\n", __FUNCTION__);

	if( !mWORK.Init() )
	{
		*tResult = 10;
		return FALSE;
	}
	__LogMgr()->Log("![%s] : Work start\n", __FUNCTION__);
	if( !mTRANSFER.Init() )
	{
		*tResult = 11;
		return FALSE;
	}
	__LogMgr()->Log("![%s] : Transfer start\n", __FUNCTION__);
	if( !mGAME.Init() )
	{
		*tResult = 12;
		return FALSE;
	}
	__LogMgr()->Log("![%s] : Game start\n", __FUNCTION__);
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
		//-------------------------------------------------------------------------------------------------
		// 2008.11.18 Kim SungSoo
		// Intro : 1.  win32 api to linux c++
		//-------------------------------------------------------------------------------------------------		
		GlobalFree( mUSER );
		//-------------------------------------------------------------------------------------------------		

		mUSER = NULL;
	}

//	mGAMELOG.Free();
	closesocket( mSocket );
	mDB.Free();

	//-------------------------------------------------------------------------------------------------
	// 2008.11.18 Kim SungSoo
	// Intro : 1.  Delete win32 api 
	//-------------------------------------------------------------------------------------------------	
	//	WSACleanup();
	//	KillTimer( hMainWindow, 1 );
	//-------------------------------------------------------------------------------------------------	

}
//PROCESS_FOR_NETWORK
int MyServer::PROCESS_FOR_NETWORK(HWND hWnd, WPARAM wPrm, LPARAM lPrm )
{
	int index01;
	int tAddressLength; //2008.11.18 Kim SungSoo
	SOCKET tSocket;
	SOCKADDR_IN	tAddress; //2008.11.18 Kim SungSoo
	int tempUserIndex;
	int tRecvSizeFromUser;
	BYTE tProtocol;

	tSocket = (SOCKET) wPrm;

	//-------------------------------------------------------------------------------------------------
	// 2008.11.18 Kim SungSoo
	// Intro : 1.  Change switch flog ( 'WSAGETSELECTEVENT( lPrm )' to 'fd_status')
	//-------------------------------------------------------------------------------------------------	
	switch( WSAGETSELECTEVENT( lPrm ) )
		//-------------------------------------------------------------------------------------------------	
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
				// 2009.10.26 : 辫己荐
				// 力芭 郴侩 :mUSER[tempUserIndex].Quit( 10001 );
				return -1;
			}

//AGAIN:
			while(1) 
			{
			        tRecvSizeFromUser = recv(tSocket, &mUSER[tempUserIndex].mBUFFER_FOR_RECV[mUSER[tempUserIndex].mTotalRecvSize]
					        , ( MAX_RECV_BUFFER_SIZE - mUSER[tempUserIndex].mTotalRecvSize ), 0 );

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
			        else if(tRecvSizeFromUser == 0) 
			        {
				        mUSER[tempUserIndex].Quit( 1001 );
				        return 0;
			        }
			        //-------------------------------------------------------------------------------------------------		
			        mUSER[tempUserIndex].mTotalRecvSize += tRecvSizeFromUser;
				break;
			}

			while( TRUE )
			{

				if( mUSER[tempUserIndex].mTotalRecvSize < 1 )
				{
					mUSER[tempUserIndex].Quit( 10003 );
					return 0;
				}
				tProtocol = (BYTE) mUSER[tempUserIndex].mBUFFER_FOR_RECV[0];
				//__LogMgr()->Log("///tProtocol[%d]",tProtocol);
				if( W_FUNCTION[tProtocol].PROC == NULL )
				{
					mUSER[tempUserIndex].Quit( 1002 );
					return 0;
				}

				//LOG_TO_FILE_2("mUSER[tempUserIndex].mTotalRecvSize : %d, mWORK.mWorkerPacketSize[tProtocol] : %d\n" ,  mUSER[tempUserIndex].mTotalRecvSize, mWORK.mWorkerPacketSize[tProtocol]);

				if( mUSER[tempUserIndex].mTotalRecvSize < mWORK.mWorkerPacketSize[tProtocol] )
				{
					return -1;
					//goto AGAIN;
					//return 0;
				}

				W_FUNCTION[tProtocol].PROC( tempUserIndex );

				if( mUSER[tempUserIndex].mCheckConnectState )
				{
					//-------------------------------------------------------------------------------------------------
					// 2008.11.18 Kim SungSoo
					// Intro : 1. Modify win32 api to linuc c++ (MoveMemory - > memmove)
					//-------------------------------------------------------------------------------------------------				
					//memmove(mUSER[tempUserIndex].mBUFFER_FOR_RECV, mUSER[tempUserIndex].mBUFFER_FOR_RECV + mWORK.mWorkerPacketSize[tProtocol]
					//		, ( mUSER[tempUserIndex].mTotalRecvSize - mWORK.mWorkerPacketSize[tProtocol] ));
					MoveMemory( &mUSER[tempUserIndex].mBUFFER_FOR_RECV[0], &mUSER[tempUserIndex].mBUFFER_FOR_RECV[mWORK.mWorkerPacketSize[tProtocol]]
							, ( mUSER[tempUserIndex].mTotalRecvSize - mWORK.mWorkerPacketSize[tProtocol] ) );
					//-------------------------------------------------------------------------------------------------				

					mUSER[tempUserIndex].mTotalRecvSize -= mWORK.mWorkerPacketSize[tProtocol];
				}

				if (0 == mUSER[tempUserIndex].mTotalRecvSize)
				{
					//LOG_TO_FILE_1("MIR 4(%d)\n", tRecvSizeFromUser);
					return tRecvSizeFromUser;
				}
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

			//-------------------------------------------------------------------------------------------------
			// 2008.11.18 Kim SungSoo
			// Intro : 1. Delete winsocket 
			//-------------------------------------------------------------------------------------------------	
			//		tAddressLength = sizeof( tAddress );
			//		tSocket = accept( mSocket, (LPSOCKADDR) &tAddress, &tAddressLength );
			//		if( tSocket == INVALID_SOCKET )
			//		{
			//			return;
			//		}		
			//-------------------------------------------------------------------------------------------------	


			tAddressLength = sizeof( tAddress );
			tSocket = accept( mSocket, (LPSOCKADDR) &tAddress, &tAddressLength );

			if( tSocket == INVALID_SOCKET )
			{
				return 0;
			}
			for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
			{
				if( !mUSER[index01].mCheckConnectState )
				{
					//LOG_TO_FILE_1("!User index  = %d \n" ,index01 );
					break;
				}
			}
			if( index01 == MAX_USER_NUM )
			{
				//-------------------------------------------------------------------------------------------------
				// 2008.11.18 Kim SungSoo
				// Intro : 1. Change winsocket to fd
				//-------------------------------------------------------------------------------------------------	
				closesocket( tSocket );
				//-------------------------------------------------------------------------------------------------	
				return 0;
			}

			//-------------------------------------------------------------------------------------------------
			// 2008.11.18 Kim SungSoo
			// Intro : 1. Delete winsocket 
			//-------------------------------------------------------------------------------------------------	
			//		if( WSAAsyncSelect( tSocket, hWnd, WM_NETWORK_MESSAGE_1, ( FD_READ | FD_WRITE | FD_CLOSE ) ) == SOCKET_ERROR )
			//		{
			//			closesocket( tSocket );
			//			return;
			//		}
			//-------------------------------------------------------------------------------------------------	

			mUSER[index01].mCheckConnectState = TRUE;
			mUSER[index01].mUsedTime = GetTickCount();
			mUSER[index01].mSocket = tSocket;
			__LogMgr()->Log("客户进入:%s:%d",inet_ntoa(tAddress.sin_addr),tAddress.sin_port);
			sprintf( mUSER[index01].mIP, "%s", inet_ntoa(tAddress.sin_addr));
			mUSER[index01].mTotalSendSize = 0;
			mUSER[index01].mTotalRecvSize = 0;
			mUSER[index01].mCheckServerType = 0;
			mTRANSFER.B_CONNECT_OK();
			//LOG_TO_BOTH("accept data ok! no send \n" );
			mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			//LOG_TO_FILE_2("!accept data send : data = %s , size = %d\n" , mTRANSFER.mOriginal , mTRANSFER.mOriginalSize  );
			return 1;
		case FD_CLOSE :
			for( tempUserIndex = 0 ; tempUserIndex < MAX_USER_NUM ; tempUserIndex++ )
			{
				if( !mUSER[tempUserIndex].mCheckConnectState )
				{
					continue;
				}
				//-------------------------------------------------------------------------------------------------
				// 2008.11.18 Kim SungSoo
				// Intro : 1. Delete winsocket 
				//-------------------------------------------------------------------------------------------------	
				if( mUSER[tempUserIndex].mSocket == (SOCKET) wPrm )
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
//-------------------------------------------------------------------------------------------------
// 2008.11.18 Kim SungSoo
// Intro : 1. Delete timer function (this job is runing CWorkerProcess::check_time())
//				 2. reuse
//-------------------------------------------------------------------------------------------------

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
#if 0
	if( ( mGAME.mTickCount % 6 ) == 0 )
	{
	}
#endif
}

//-------------------------------------------------------------------------------------------------

//WRITE_FOR_ERROR

   void MyServer::WRITE_FOR_ERROR( char *tErrorData )
   {
//-------------------------------------------------------------------------------------------------
// 2008.11.18 Kim SungSoo
// Intro : 1. Don't use error logger function (this job is runing LOG_TO_FILE*())
//-------------------------------------------------------------------------------------------------

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

//-------------------------------------------------------------------------------------------------

}
//-------------------------------------------------------------------------------------------------
