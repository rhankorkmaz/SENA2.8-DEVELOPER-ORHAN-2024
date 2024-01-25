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
    mBUFFER_FOR_SEND = static_cast<char*> (::calloc (1, tSendBufferSize));
	if( mBUFFER_FOR_SEND == NULL )
	{
		return FALSE;
	}
    mBUFFER_FOR_RECV = static_cast<char*> (::calloc (1, tRecvBufferSize));
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
		::free (mBUFFER_FOR_SEND);
		mBUFFER_FOR_SEND = NULL;
	}
	if( mBUFFER_FOR_RECV != NULL )
	{
		::free (mBUFFER_FOR_RECV);
		mBUFFER_FOR_RECV = NULL;
	}
}
//SEND
void MyUser::Send( BOOL tCheckValidBuffer, char *tBuffer, int tBufferSize )
{
	int nResult = 0;
	fd_set write_fds;
	if( !mCheckConnectState )
	{
		return;
	}

	int tSendValue01;

	if( tCheckValidBuffer )
	{
		if( ( MAX_SEND_BUFFER_SIZE - mTotalSendSize ) < tBufferSize )
		{
			Quit(  );
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

		if(nResult == 0) 
		{
			MoveMemory( &mBUFFER_FOR_SEND[0], &mBUFFER_FOR_SEND[tSendValue01], ( mTotalSendSize - tSendValue01 ) );
			mTotalSendSize -= tSendValue01;
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
				Quit();
				return;
			}
			MoveMemory( &mBUFFER_FOR_SEND[0], &mBUFFER_FOR_SEND[tSendValue01], ( mTotalSendSize - tSendValue01 ) );
			mTotalSendSize -= tSendValue01;
		}
	}
}
//QUIT
void MyUser::Quit( void )
{
	if( !mCheckConnectState )
	{
		return;
	}
	mCheckConnectState = FALSE;
	if( ( mCheckValidState ) && ( mMoveZoneResult == 0 ) )
	{
		mPLAYUSER_COM.U_UNREGISTER_USER_FOR_LOGIN_SEND( mPlayUserIndex, &uID[0] );
	}
	mTotalRecvSize = 0;
	mTotalSendSize = 0;
	mCheckValidState = FALSE;
	closesocket( mSocket );

	__LogMgr()->Log("Quit ");

}
//-------------------------------------------------------------------------------------------------
