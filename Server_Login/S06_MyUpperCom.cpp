//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "Shengming.h"
#include <signal.h>
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_PLAYUSER_COM
//-------------------------------------------------------------------------------------------------

//INSTANCE
MyPlayUserCom mPLAYUSER_COM;
//CREATE
MyPlayUserCom::MyPlayUserCom( void )
{
}
//CONNECT
BOOL MyPlayUserCom::Connect( void )
{
	if( mCheckConnectState )
	{
		return TRUE;
	}

	int tConnectRecvCheck;
	char tConnectDataCheck;
	char tSendData[1000];
	int tSendDataSize;
	int tSendValue01;
	int tSendValue02;
	int tSendValue03;
	int tOKRecvCheck;
	char tOKDataCheck;

	WSAData wsaData;
	int err = 0 ; 
	WORD wVersionRequested = MAKEWORD( 2, 2 );
	err = WSAStartup(wVersionRequested, &wsaData); 

	if (err != 0 )
	{
		return FALSE;  
	}  

	mSocket = socket( AF_INET, SOCK_STREAM, 0 );
	if( mSocket < 0 )
	{
		return FALSE;
	}
	mAddress.sin_family = AF_INET;
	mAddress.sin_addr.s_addr = inet_addr( "127.0.0.1" );
	mAddress.sin_port = htons(10050);
	err = connect (mSocket, (sockaddr*) &mAddress, sizeof (sockaddr_in));
	if (err == SOCKET_ERROR )
	{
		closesocket( mSocket );
		return FALSE;
	}
	tConnectRecvCheck = recv( mSocket, &tConnectDataCheck, 1, 0 );
	if( tConnectRecvCheck != 1 )
	{
		closesocket( mSocket );
		return FALSE;
	}
	tSendData[0] = P_LOGIN_FOR_PLAYUSER_SEND;
	tSendDataSize = S_LOGIN_FOR_PLAYUSER_SEND;
	tSendValue01 = tSendDataSize;
	tSendValue02 = 0;
	while( tSendValue01 > 0 )
	{
		tSendValue03 = send( mSocket, &tSendData[tSendValue02], tSendValue01, 0 );
		if( tSendValue03 == SOCKET_ERROR )
		{
			closesocket( mSocket );
			return FALSE;
		}
		tSendValue01 -= tSendValue03;
		tSendValue02 += tSendValue03;
	}
	tOKRecvCheck = recv( mSocket, &tOKDataCheck, 1, 0 );
	if( tOKRecvCheck != 1 )
	{
		closesocket( mSocket );
		return FALSE;
	}
	mCheckConnectState = TRUE;

	return TRUE;
}
//SEND
BOOL MyPlayUserCom::Send( void )
{
	int tSendValue01;
	int tSendValue02;
	int tSendValue03;

	tSendValue01 = mSendDataSize;
	tSendValue02 = 0;
	while( tSendValue01 > 0 )
	{
		tSendValue03 = send( mSocket, &mSendData[tSendValue02], tSendValue01, 0 );
		if( tSendValue03 == SOCKET_ERROR )
		{
			if( WSAGetLastError() == WSAEWOULDBLOCK )
			{
				return FALSE;
			}
			Close();
			return FALSE;
		}
		tSendValue01 -= tSendValue03;
		tSendValue02 += tSendValue03;
	}
	return TRUE;
}
//RECV
BOOL MyPlayUserCom::Recv( void )
{
    fd_set readfds;
    int iResult = 0;
	int tRecvValue01;
	int tRecvValue02;

	if( mRecvDataSize > 0 )
	{
		tRecvValue01 = 0;
		while( TRUE )
		{
#if 0
            FD_ZERO (&readfds);
            FD_SET (mSocket, &readfds);
            struct timeval tv = {2, 0};

            if ((iResult = ::select (mSocket + 1, &readfds, NULL, NULL, &tv)) < 0) {
                if (errno == EINTR) continue;
                Close ();
                return FALSE;
            }

            if (iResult == 0) {
                LOG_TO_FILE ("!Tired of waiting for an answer from the PlayUser server to give up.\n");
                LOG_TO_FILE_2 ("\t\t\tin (%s - %d).\n", __FILE__, __LINE__);
                Close ();
                return FALSE;
            }

            if (FD_ISSET (mSocket, &readfds)) { 
#endif
                tRecvValue02 = ::recv (mSocket, &mRecvData[tRecvValue01], mRecvDataSize - tRecvValue01, 0);
    			if( tRecvValue02 < 0 )
    			{
					if(errno == EINTR)
						continue;
    				//if (errno != EAGAIN && errno != EWOULDBLOCK && errno != EINTR) {
					Close();
					return FALSE;
					//}
                    //continue;
    			} else if (tRecvValue02 == 0) {
                    Close ();
                    return FALSE;
                }
			    tRecvValue01 += tRecvValue02;
			    if( tRecvValue01 == mRecvDataSize )
			    {
			    	break;
			    }
#if 0
		    }
#endif
	    }
    }

	return TRUE;
}
//CLOSE
void MyPlayUserCom::Close( void )
{
	if( !mCheckConnectState )
	{
		return;
	}
	mCheckConnectState = FALSE;
	closesocket( mSocket );
}
//INIT
BOOL MyPlayUserCom::Init( char tIP[16], int tPort )
{
	mCheckConnectState = FALSE;
	strcpy( mIP, tIP );
	mPort = tPort;
	if( !Connect() )
	{
		return FALSE;
	}
	return TRUE;
}
//FREE
void MyPlayUserCom::Free( void )
{
	Close();
}
//PROCESS_FOR_NETWORK
BOOL MyPlayUserCom::ProcessForNetwork( void )
{
	if( !Connect() )
	{
		return FALSE;
	}
	if( !Send() )
	{
		return FALSE;
	}
	if( !Recv() )
	{
		return FALSE;
	}
	return TRUE;
}
//U_LOGIN_OK_FOR_PLAYUSER_SEND
void MyPlayUserCom::U_LOGIN_OK_FOR_PLAYUSER_SEND( void )
{
	mSendData[0] = P_LOGIN_OK_FOR_PLAYUSER_SEND;
	mSendDataSize = S_LOGIN_OK_FOR_PLAYUSER_SEND;
	mRecvDataSize = 0;
	while( TRUE )
	{
		if( ProcessForNetwork() )
		{
			break;
		}
	}
}
//U_REGISTER_USER_FOR_LOGIN_1_SEND
void MyPlayUserCom::U_REGISTER_USER_FOR_LOGIN_1_SEND( char tIP[16], char tID[MAX_USER_ID_LENGTH], int tUserSort, int tGoodFellow, int tUserRandom, int tLoginPremium, int tLoginPremiumPCRoom, int tTraceState, char tBonus100Money, int tPremiumServerExpirationDate, AUTH_INFO *tAuthInfo ) // 함수 선언 변경 - int tPremiumServerExpirationDate 추가. // @_Premium_Server_@
{
	mSendData[0] = P_REGISTER_USER_FOR_LOGIN_1_SEND;
	CopyMemory( &mSendData[1], &tIP[0], 16 );
	CopyMemory( &mSendData[17], &tID[0], MAX_USER_ID_LENGTH );
	CopyMemory( &mSendData[( 17 + MAX_USER_ID_LENGTH )], &tUserSort, 4 );
	CopyMemory( &mSendData[( 21 + MAX_USER_ID_LENGTH )], &tGoodFellow, 4 );
	CopyMemory( &mSendData[( 25 + MAX_USER_ID_LENGTH )], &tUserRandom, 4 );
	CopyMemory( &mSendData[( 29 + MAX_USER_ID_LENGTH )], &tLoginPremium, 4 );
	CopyMemory( &mSendData[( 33 + MAX_USER_ID_LENGTH )], &tLoginPremiumPCRoom, 4 );
	CopyMemory( &mSendData[( 37 + MAX_USER_ID_LENGTH )], &tTraceState, 4 );
	CopyMemory( &mSendData[( 41 + MAX_USER_ID_LENGTH )], &tBonus100Money, 1 );
	CopyMemory( &mSendData[( 42 + MAX_USER_ID_LENGTH )], &tPremiumServerExpirationDate, 4 ); // @_Premium_Server_@
	CopyMemory( &mSendData[( 46 + MAX_USER_ID_LENGTH )], tAuthInfo, sizeof(AUTH_INFO) );
	mSendDataSize = S_REGISTER_USER_FOR_LOGIN_1_SEND;
	mRecvDataSize = S_REGISTER_USER_FOR_LOGIN_RECV;
	while( TRUE )
	{
		if( ProcessForNetwork() )
		{
			break;
		}
	}
	CopyMemory( &mRecv_Result, &mRecvData[1], 4 );
	CopyMemory( &mRecv_PlayUserIndex, &mRecvData[5], 4 );
}
//U_REGISTER_USER_FOR_LOGIN_2_SEND
void MyPlayUserCom::U_REGISTER_USER_FOR_LOGIN_2_SEND( int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH] )
{
	mSendData[0] = P_REGISTER_USER_FOR_LOGIN_2_SEND;
	CopyMemory( &mSendData[1], &tPlayUserIndex, 4 );
	CopyMemory( &mSendData[5], &tID[0], MAX_USER_ID_LENGTH );
	mSendDataSize = S_REGISTER_USER_FOR_LOGIN_2_SEND;
	mRecvDataSize = S_REGISTER_USER_FOR_LOGIN_RECV;
	while( TRUE )
	{
		if( ProcessForNetwork() )
		{
			break;
		}
	}
	CopyMemory( &mRecv_Result, &mRecvData[1], 4 );
	CopyMemory( &mRecv_PlayUserIndex, &mRecvData[5], 4 );
}
//U_REGISTER_USER_FOR_LOGIN_3_SEND
void MyPlayUserCom::U_REGISTER_USER_FOR_LOGIN_3_SEND( int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO *tAvatarInfo )
{
	mSendData[0] = P_REGISTER_USER_FOR_LOGIN_3_SEND;
	CopyMemory( &mSendData[1], &tPlayUserIndex, 4 );
	CopyMemory( &mSendData[5], &tID[0], MAX_USER_ID_LENGTH );
	CopyMemory( &mSendData[( 5 + MAX_USER_ID_LENGTH )], tAvatarInfo, sizeof( AVATAR_INFO ) );
	mSendDataSize = S_REGISTER_USER_FOR_LOGIN_3_SEND;
	mRecvDataSize = S_REGISTER_USER_FOR_LOGIN_RECV;
	while( TRUE )
	{
		if( ProcessForNetwork() )
		{
			break;
		}
	}
	CopyMemory( &mRecv_Result, &mRecvData[1], 4 );
	CopyMemory( &mRecv_PlayUserIndex, &mRecvData[5], 4 );
}
//U_UNREGISTER_USER_FOR_LOGIN_SEND
void MyPlayUserCom::U_UNREGISTER_USER_FOR_LOGIN_SEND( int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH] )
{
	mSendData[0] = P_UNREGISTER_USER_FOR_LOGIN_SEND;
	CopyMemory( &mSendData[1], &tPlayUserIndex, 4 );
	CopyMemory( &mSendData[5], &tID[0], MAX_USER_ID_LENGTH );
	mSendDataSize = S_UNREGISTER_USER_FOR_LOGIN_SEND;
	mRecvDataSize = S_UNREGISTER_USER_FOR_LOGIN_RECV;
	while( TRUE )
	{
		if( ProcessForNetwork() )
		{
			break;
		}
	}
}
//U_GET_PRESENT_USER_NUM_FOR_LOGIN_SEND
void MyPlayUserCom::U_GET_PRESENT_USER_NUM_FOR_LOGIN_SEND( void )
{
	mSendData[0] = P_GET_PRESENT_USER_NUM_FOR_LOGIN_SEND;
	mSendDataSize = S_GET_PRESENT_USER_NUM_FOR_LOGIN_SEND;
	mRecvDataSize = S_GET_PRESENT_USER_NUM_FOR_LOGIN_RECV;
	while( TRUE )
	{
		if( ProcessForNetwork() )
		{
			break;
		}
	}
	CopyMemory( &mRecv_PresentUserNum, &mRecvData[1], 4 );
}
//U_BLOCK_USER_FOR_LOGIN_1_SEND
void MyPlayUserCom::U_BLOCK_USER_FOR_LOGIN_1_SEND( int tSort, char tID[MAX_USER_ID_LENGTH] )
{
	mSendData[0] = P_BLOCK_USER_FOR_LOGIN_1_SEND;
	CopyMemory( &mSendData[1], &tSort, 4 );
	CopyMemory( &mSendData[5], &tID[0], MAX_USER_ID_LENGTH );
	mSendDataSize = S_BLOCK_USER_FOR_LOGIN_1_SEND;
	mRecvDataSize = S_BLOCK_USER_FOR_LOGIN_RECV;
	while( TRUE )
	{
		if( ProcessForNetwork() )
		{
			break;
		}
	}
	CopyMemory( &mRecv_Result, &mRecvData[1], 4 );
}
//U_BLOCK_USER_FOR_LOGIN_2_SEND
void MyPlayUserCom::U_BLOCK_USER_FOR_LOGIN_2_SEND( int tSort, char tID[MAX_USER_ID_LENGTH] )
{
	mSendData[0] = P_BLOCK_USER_FOR_LOGIN_2_SEND;
	CopyMemory( &mSendData[1], &tSort, 4 );
	CopyMemory( &mSendData[5], &tID[0], MAX_USER_ID_LENGTH );
	mSendDataSize = S_BLOCK_USER_FOR_LOGIN_2_SEND;
	mRecvDataSize = S_BLOCK_USER_FOR_LOGIN_RECV;
	while( TRUE )
	{
		if( ProcessForNetwork() )
		{
			break;
		}
	}
	CopyMemory( &mRecv_Result, &mRecvData[1], 4 );
}

void MyPlayUserCom::U_USER_EXT_SEND(int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH])
{
	
	mSendData[0] = P_USER_EXT_SEND;
	CopyMemory(&mSendData[1], &tPlayUserIndex, 4);
	CopyMemory(&mSendData[5], &tID[0], MAX_USER_ID_LENGTH);
	mSendDataSize = S_USER_EXT_SEND;
	mRecvDataSize = S_REGISTER_USER_FOR_LOGIN_RECV;
	while (TRUE)
	{
		if (ProcessForNetwork())
		{
			break;
		}
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	CopyMemory(&mRecv_PlayUserIndex, &mRecvData[5], 4);
}
//-------------------------------------------------------------------------------------------------

MyCenterCom mCENTER_COM;
//CREATE
MyCenterCom::MyCenterCom( void )
{
}
//CONNECT
BOOL MyCenterCom::Connect( void )
{
	if( mCheckConnectState )
	{
		return TRUE;
	}

	int tConnectRecvCheck;
	char tConnectDataCheck;
	char tSendData[1000];
	int tSendDataSize;
	int tSendValue01;
	int tSendValue02;
	int tSendValue03;
	int tOKRecvCheck;
	char tOKDataCheck;

	mSocket = socket( AF_INET, SOCK_STREAM, 0 );
	if( mSocket < 0 )
	{
		return FALSE;
	}
	mAddress.sin_family = AF_INET;
	mAddress.sin_addr.s_addr = inet_addr( mIP );
	mAddress.sin_port = htons( mPort );
	if (connect (mSocket, (sockaddr*) &mAddress, sizeof (sockaddr_in)) < 0) 
	{
		closesocket( mSocket );
		return FALSE;
	}
	tConnectRecvCheck = recv( mSocket, &tConnectDataCheck, 1, 0 );
	if( tConnectRecvCheck != 1 )
	{
		closesocket( mSocket );
		return FALSE;
	}
	tSendData[0] = P_LOGIN_FOR_CENTER_SEND;
	tSendDataSize = S_LOGIN_FOR_CENTER_SEND;
	tSendValue01 = tSendDataSize;
	tSendValue02 = 0;
	while( tSendValue01 > 0 )
	{
		tSendValue03 = send( mSocket, &tSendData[tSendValue02], tSendValue01, 0 );
		if (tSendValue03 <= 0) {
			if(errno == EINTR)
				continue;
			closesocket (mSocket);
			return FALSE;
		}
		tSendValue01 -= tSendValue03;
		tSendValue02 += tSendValue03;
	}
	tOKRecvCheck = recv( mSocket, &tOKDataCheck, 1, 0 );
	if( tOKRecvCheck != 1 )
	{
		closesocket( mSocket );
		return FALSE;
	}
	mCheckConnectState = TRUE;
	return TRUE;
}
//SEND
BOOL MyCenterCom::Send( void )
{
	int tSendValue01;
	int tSendValue02;
	int tSendValue03;

	tSendValue01 = mSendDataSize;
	tSendValue02 = 0;
	while( tSendValue01 > 0 )
	{
		tSendValue03 = send( mSocket, &mSendData[tSendValue02], tSendValue01, 0 );
		if (tSendValue03 <= 0) 
		{
			if(errno == EINTR)
				continue;
			Close ();
			return FALSE;
		}
		tSendValue01 -= tSendValue03;
		tSendValue02 += tSendValue03;
	}
	return TRUE;
}
//RECV
BOOL MyCenterCom::Recv( void )
{
	fd_set readfds;
	int iResult = 0;
	int tRecvValue01;
	int tRecvValue02;

	if( mRecvDataSize > 0 )
	{
		tRecvValue01 = 0;
		while( TRUE )
		{
#if 0
			FD_ZERO (&readfds);
			FD_SET (mSocket, &readfds);
			struct timeval tv = {2, 0};

			if ((iResult = ::select (mSocket + 1, &readfds, NULL, NULL, &tv)) < 0) {
				if (errno == EINTR) continue;
				Close ();
				return FALSE;
			}

			if (iResult == 0) {
				LOG_TO_FILE ("!Tired of waiting for an answer from the PlayUser server to give up.\n");
				LOG_TO_FILE_2 ("\t\t\tin (%s - %d).\n", __FILE__, __LINE__);
				Close ();
				return FALSE;
			}

			if (FD_ISSET (mSocket, &readfds)) {
#endif
				tRecvValue02 = ::recv (mSocket, &mRecvData[tRecvValue01], mRecvDataSize - tRecvValue01, 0);
				if( tRecvValue02 <= 0 )
				{
					if(errno == EINTR)
						continue;
					//if (errno != EAGAIN && errno != EWOULDBLOCK && errno != EINTR) {
					Close();
					return FALSE;
					//}
				}
				tRecvValue01 += tRecvValue02;
				if( tRecvValue01 == mRecvDataSize )
				{
					break;
				}
#if 0
			}
#endif
		}
	}

	return TRUE;
}
//CLOSE
void MyCenterCom::Close( void )
{
	if( !mCheckConnectState )
	{
		return;
	}
	mCheckConnectState = FALSE;
	closesocket( mSocket );
}
//INIT
BOOL MyCenterCom::Init( char tIP[16], int tPort )
{
	mCheckConnectState = FALSE;
	strcpy( mIP, tIP );
	mPort = tPort;
	if( !Connect() )
	{
		return FALSE;
	}
	return TRUE;
}
//FREE
void MyCenterCom::Free( void )
{
	Close();
}
//PROCESS_FOR_NETWORK
BOOL MyCenterCom::ProcessForNetwork( void )
{
	if( !Connect() )
	{
		
		return FALSE;
	}
	if( !Send() )
	{
		
		return FALSE;
	}
	if( !Recv() )
	{
		
		return FALSE;
	}

	return TRUE;
}
//U_LOGIN_OK_FOR_CENTER_SEND
void MyCenterCom::U_LOGIN_OK_FOR_CENTER_SEND( void )
{
	mSendData[0] = P_LOGIN_OK_FOR_CENTER_SEND;
	mSendDataSize = S_LOGIN_OK_FOR_CENTER_SEND;
	mRecvDataSize = 0;
	while( TRUE )
	{
		if( ProcessForNetwork() )
		{
			break;
		}
	}
}
//U_GET_ZONE_SERVER_INFO_1
void MyCenterCom::U_GET_ZONE_SERVER_INFO_1( int tZoneNumber )
{
	mSendData[0] = P_GET_ZONE_SERVER_INFO_1;
	CopyMemory( &mSendData[1], &tZoneNumber, 4 );
	mSendDataSize = S_GET_ZONE_SERVER_INFO_1;
	mRecvDataSize = S_GET_ZONE_SERVER_INFO_1_RESULT;
	while( TRUE )
	{
		if( ProcessForNetwork() )
		{
			break;
		}
	}
	CopyMemory( &mRecv_Result, &mRecvData[1], 4 );
	CopyMemory( &mRecv_IP[0], &mRecvData[5], 16 );
	CopyMemory( &mRecv_Port, &mRecvData[21], 4 );
}