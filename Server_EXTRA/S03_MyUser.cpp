//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "Shengming.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_USER
//-------------------------------------------------------------------------------------------------
//INSTANCE
MyUser *mUSER = NULL;
//CREATE
MyUser::MyUser( void )
{
	mBUFFER_FOR_SEND = NULL;
	mBUFFER_FOR_RECV = NULL;
}
//INIT
BOOL MyUser::Init( int tSendBufferSize, int tRecvBufferSize )
{
	mCheckConnectState = FALSE;

	//--------------------------------------------------------------------------------------------------
	// 2008.11.18 Kim SungSoo
	// Intro : 1. Modify win32 api to c++ for linux
	//--------------------------------------------------------------------------------------------------	
	mBUFFER_FOR_SEND = (char *) GlobalAlloc( GMEM_FIXED, tSendBufferSize );
	//--------------------------------------------------------------------------------------------------	
	if( mBUFFER_FOR_SEND == NULL )
	{
		return FALSE;
	}

	//--------------------------------------------------------------------------------------------------
	// 2008.11.18 Kim SungSoo
	// Intro : 1. Modify win32 api to c++ for linux
	//--------------------------------------------------------------------------------------------------			
	mBUFFER_FOR_RECV = (char *) GlobalAlloc( GMEM_FIXED, tRecvBufferSize );
	//--------------------------------------------------------------------------------------------------	
	if( mBUFFER_FOR_RECV == NULL )
	{
		return FALSE;
	}
	return TRUE;
}
//FREE
void MyUser::Free( void )
{
	if( mBUFFER_FOR_SEND != NULL )
	{
		//--------------------------------------------------------------------------------------------------
		// 2008.11.18 Kim SungSoo
		// Intro : 1. Modify win32 api to c++ for linux
		//--------------------------------------------------------------------------------------------------	
		GlobalFree( mBUFFER_FOR_SEND );
		//--------------------------------------------------------------------------------------------------	

		mBUFFER_FOR_SEND = NULL;
	}
	if( mBUFFER_FOR_RECV != NULL )
	{
		//--------------------------------------------------------------------------------------------------
		// 2008.11.18 Kim SungSoo
		// Intro : 1. Modify win32 api to c++ for linux
		//--------------------------------------------------------------------------------------------------	
		GlobalFree( mBUFFER_FOR_RECV );
		//--------------------------------------------------------------------------------------------------	
		mBUFFER_FOR_RECV = NULL;
	}
}
//SEND
void MyUser::Send( BOOL tCheckValidBuffer, char *tBuffer, int tBufferSize , bool bUDPSend )
{
	int nResult = 0;
	fd_set write_fds;
	int tSendValue01;

	if( !mCheckConnectState )
	{
		return;
	}

	if( tCheckValidBuffer )
	{
		if( ( MAX_SEND_BUFFER_SIZE - mTotalSendSize ) < tBufferSize )
		{
			Quit( 2001 );
			return;
		}
		CopyMemory( &mBUFFER_FOR_SEND[mTotalSendSize], &tBuffer[0], tBufferSize );
		mTotalSendSize += tBufferSize;
	}
	while( mTotalSendSize > 0 )
	{
		FD_ZERO(&write_fds);
		FD_SET(mSocket, &write_fds);
		struct timeval tv = {5, 0};

		if((nResult = select(mSocket + 1, NULL, &write_fds, NULL, &tv)) < 0) {
			continue;
		}
		if(nResult == 0) {
			MoveMemory( &mBUFFER_FOR_SEND[0], &mBUFFER_FOR_SEND[tSendValue01], ( mTotalSendSize - tSendValue01 ) );
			mTotalSendSize -= tSendValue01;
			__LogMgr()->Log("![%s] : Player user send buffer full[%d]\n", __FUNCTION__, mTotalSendSize);
			return;
		}

		if(FD_ISSET(mSocket, &write_fds)) 
		{
			tSendValue01 = send( mSocket, &mBUFFER_FOR_SEND[0], mTotalSendSize, 0 );

			if( tSendValue01 == SOCKET_ERROR )
			{
				if( WSAGetLastError() == WSAEWOULDBLOCK )
				{
					return;
				}
				Quit(2002);
				return;
			}

			MoveMemory( &mBUFFER_FOR_SEND[0], &mBUFFER_FOR_SEND[tSendValue01], ( mTotalSendSize - tSendValue01 ) );
			mTotalSendSize -= tSendValue01;
		}
	}
}
//QUIT
void MyUser::Quit( int tSort )
{
	if( !mCheckConnectState )
	{
		return;
	}

	char tempString01[1000];

	//-------------//
	//ABNORMAL_FREE//
	//-------------//
	if( tSort != 0 )
	{
		if( mCheckServerType != 3 )
		{
			sprintf( tempString01, "[ABNORMAL_FREE-(%d)]::[SERVER_IP](%s),[SERVER_TYPE](%d),[SERVER_NUMBER](%d)", tSort, &mIP[0], mCheckServerType, mZoneServerNumber );
			__LogMgr()->Log("![%s] : error(%s)\n", __FUNCTION__, tempString01);
			// 2008.11.20 KimSungSoo : Log finction change
			//mSERVER.WRITE_FOR_ERROR( &tempString01[0] );
		}
	}
	//-------------//
	//-------------//
	//-------------//
	mTotalRecvSize = 0;
	mTotalSendSize = 0;
	mCheckServerType = -1;
	mZoneServerNumber = -1;
	mCheckConnectState = FALSE;
	closesocket( mSocket );
}
//-------------------------------------------------------------------------------------------------
