
#include "Shengming.h"

MyServer mSERVER;
#define MAX_RECV_BUFFER_SIZE 10240
MyServer::MyServer( void )
{
}

BOOL SetSocket(SOCKET tSocket, BOOL tServer)
{


	int optval = 1;
	u_long iMode = 1;
	if (ioctlsocket(tSocket, FIONBIO, &iMode) != 0)
	{
		return FALSE;
	}
	if (setsockopt(tSocket, IPPROTO_TCP, TCP_NODELAY, (const char*)&optval, 4) != 0)
	{
		return FALSE;
	}
	return TRUE;
}


BOOL MyServer::Init( int *tResult)
{
	int index01 =0;
	int tPort =0;
	mMAX_USER_NUM = mSERVER_INFO.mServerMaxUserNum;
    srand( (unsigned int) time( NULL ) );
	ZeroMemory( &mWsaData, sizeof( WSADATA ) );
	if( WSAStartup( MAKEWORD( 2, 2 ), &mWsaData ) != 0 )
	{
		*tResult = 3;
		return FALSE;
	}
	mSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (mSocket == INVALID_SOCKET)
	{
		*tResult = 4;
		return FALSE;
	}
	if (!SetSocket(mSocket, TRUE))
	{
		*tResult = 31;
		return FALSE;
	}
	ZeroMemory(&mAddress, sizeof(SOCKADDR_IN));
	mAddress.sin_family = AF_INET;
	mAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	mAddress.sin_port = htons(mSERVER_INFO.mServerPort);
	if (bind(mSocket, (LPSOCKADDR)&mAddress, sizeof(mAddress)) == SOCKET_ERROR)
	{
		*tResult = 5;
		return FALSE;
	}
	if (listen(mSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		*tResult = 6;
		return FALSE;
	}
	if (WSAAsyncSelect(mSocket, hMainWindow, WM_NETWORK_MESSAGE_1, FD_ACCEPT) == SOCKET_ERROR)
	{
		*tResult = 7;
		return FALSE;
	}

	mMAX_SEND_BUFFER_SIZE = 900000;
	mMAX_RECV_BUFFER_SIZE = 10500;
	mRankCheck = false;
    printf("![%s] : Main server start\n", __FUNCTION__);

	mUSER = (MyUser *) GlobalAlloc( GMEM_FIXED, ( mMAX_USER_NUM * sizeof( MyUser ) ) );
	if( mUSER == NULL )
	{
		*tResult = 13;
		return FALSE;
	}
	for( index01 = 0 ; index01 < mMAX_USER_NUM ; index01++ )
	{
		mUSER[index01].mBUFFER_FOR_SEND = NULL;
		mUSER[index01].mBUFFER_FOR_RECV = NULL;
	}

	for( index01 = 0 ; index01 < mMAX_USER_NUM ; index01++ )
	{
		if( !mUSER[index01].Init( index01, mMAX_SEND_BUFFER_SIZE, mMAX_RECV_BUFFER_SIZE ) )
		{
			*tResult = 14;
			return FALSE;
		}
	}
	if (!mGAME.Init())
	{
		*tResult = 17;
		printf("![%s] : Game start\n", __FUNCTION__);
		return FALSE;
	}
	if( !mPLAYUSER_COM.Init( mSERVER_INFO.mServerNumber, mSERVER_INFO.mUpperServer_1_IP, mSERVER_INFO.mUpperServer_1_Port ) )
	{
		*tResult = 77;
		printf("![%s] : Player server start\n", __FUNCTION__);
		return FALSE;
	}
	printf("[%s] : Player server start\n", __FUNCTION__);

	if( !mCENTER_COM.Init( mSERVER_INFO.mServerNumber, mSERVER_INFO.mServerPort, mSERVER_INFO.mUpperServer_2_IP, mSERVER_INFO.mUpperServer_2_Port ) )
	{
		*tResult = 88;
		printf("![%s] : Center server start\n", __FUNCTION__);
		return FALSE;
	}
	printf("[%s] : Center server start\n", __FUNCTION__);

	if( !mRELAY_COM.Init( mSERVER_INFO.mServerNumber, mSERVER_INFO.mUpperServer_4_IP, mSERVER_INFO.mUpperServer_4_Port ) )
	{
		*tResult = 998;
		printf("![%s] : RELAY server start\n", __FUNCTION__);
		return FALSE;
	}
	printf("[%s] : RELAY server start\n", __FUNCTION__);

	if( !mEXTRA_COM.Init( mSERVER_INFO.mServerNumber, mSERVER_INFO.mUpperServer_3_IP, mSERVER_INFO.mUpperServer_3_Port ) )
	{
		*tResult = 990;
		printf("![%s] : EXTRA server start\n", __FUNCTION__);
		return FALSE;
	}
	printf("[%s] : EXTRA server start\n", __FUNCTION__);

	if (!mGAMELOG.Init(mSERVER_INFO.mGameLogIp, mSERVER_INFO.mGameLogPort))
	{
		*tResult = 236;
		printf("![%s] : Player server start\n", __FUNCTION__);
		return FALSE;
	}
	if (!mVALETINFO.Init(mSERVER_INFO.mServerNumber, mSERVER_INFO.mValet_Ip, mSERVER_INFO.mValet_Port))
	{
		*tResult = 237;
		printf("![%s] : Valet server start\n", __FUNCTION__);
		return FALSE;
	}
	printf("[%s] : Valet server start\n", __FUNCTION__);


	if( !mWORK.Init() )
	{
		*tResult = 15;
		printf("![%s] : Work start\n", __FUNCTION__);
		return FALSE;
	}
	printf("[%s] : Work start\n", __FUNCTION__);

	if( !mTRANSFER.Init() )
	{
		*tResult = 16;
		printf("![%s] : Transfer start\n", __FUNCTION__);
		return FALSE;
	}
	printf("[%s] : Transfer start\n", __FUNCTION__);
	if (mEXTRA_COM.U_BUY_BLOOD_ITEM_FOR_EXTRA_SEND(0) == FALSE)
	{
		*tResult = 18;
		printf("![%s] : Kan Market Yüklenemedi\n", __FUNCTION__);
		return FALSE;
	}

	printf("[%s] : Game start\n", __FUNCTION__);
	mGAME.mCheckActiveBattleLogic = TRUE;
	return TRUE;
}



int MyServer::PROCESS_FOR_NETWORK( HWND hWnd, WPARAM wPrm, LPARAM lPrm )
{
	int index01;	
	SOCKET tSocket;
	BYTE tProtocol;
	int tRandomNumber;
	int tRandomNumber1;
	int tempUserIndex;
	int tAddressLength;
	SOCKADDR_IN	tAddress;
	int tRecvSizeFromUser;
	char tPacketEncryptionValue;	
	unsigned char tServerState = 0;
	tRandomNumber = 0;
	tRandomNumber1 = 0;
	tPacketEncryptionValue = 0;
	tSocket = (SOCKET) wPrm;
	switch( WSAGETSELECTEVENT( lPrm ) )
	{
	case FD_READ :
		for( tempUserIndex = 0 ; tempUserIndex < mMAX_USER_NUM ; tempUserIndex++ )
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

		if( tempUserIndex == mMAX_USER_NUM )
		{

			return -1;
		}
		while(1) 
		{
			tRecvSizeFromUser = recv( (SOCKET) wPrm, &mUSER[tempUserIndex].mBUFFER_FOR_RECV[mUSER[tempUserIndex].mTotalRecvSize], ( MAX_RECV_BUFFER_SIZE - mUSER[tempUserIndex].mTotalRecvSize ), 0 );
			if( tRecvSizeFromUser <= 0 )
			{
				if( tRecvSizeFromUser == SOCKET_ERROR )
				{
					if( WSAGetLastError() == WSAEWOULDBLOCK )
					{
						return 0;
					}
				}
				mUSER[tempUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return 0;
			}
			else if(tRecvSizeFromUser == 0) 
			{
				mUSER[tempUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return 0;
			} 

			for( index01 = mUSER[tempUserIndex].mTotalRecvSize ; index01 < ( mUSER[tempUserIndex].mTotalRecvSize + tRecvSizeFromUser ) ; index01++ )
			{
				mUSER[tempUserIndex].mBUFFER_FOR_RECV[index01] = (char)(mUSER[tempUserIndex].mBUFFER_FOR_RECV[index01] ^ mUSER[tempUserIndex].mPacketEncryptionValue[0]);
			}
			mUSER[tempUserIndex].mTotalRecvSize += tRecvSizeFromUser;
			break;
		}
		while( TRUE )
		{
			if( mUSER[tempUserIndex].mTotalRecvSize < 9 )
			{
				return -1;
			}	
			tProtocol = (BYTE) mUSER[tempUserIndex].mBUFFER_FOR_RECV[8];
			printf("PACKET OPCODE = %d FOUND LENGTH = %d\n", tProtocol, tRecvSizeFromUser);
			
			if( W_FUNCTION[tProtocol].PROC == NULL )
			{
				//if( mUSER[tempUserIndex].mCheckValidState )a
				//{
				//	mPLAYUSER_COM.U_BLOCK_USER_FOR_ZONE_2_SEND( 601, &mUSER[tempUserIndex].uID[0] );
				//}
				mUSER[tempUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				printf("PACKET OPCODE = %d NOT FOUND LENGTH = %d\n", tProtocol, tRecvSizeFromUser);
				printf("Wrong packet. This user ======= %s\n", mUSER[tempUserIndex].mAvatarInfo.aName);
				HexDump(mUSER[tempUserIndex].mBUFFER_FOR_RECV, tRecvSizeFromUser, 0);
				return tRecvSizeFromUser;
			}
			if( mUSER[tempUserIndex].mTotalRecvSize < mWORK.mWorkerPacketSize[tProtocol] )
			{
				return -1;
			}
			tPacketEncryptionValue = mUSER[tempUserIndex].mBUFFER_FOR_RECV[7];
			if( tPacketEncryptionValue != mUSER[tempUserIndex].mPacketEncryptionValue[1])
			{
				if( mUSER[tempUserIndex].mCheckValidState )
				{
					//mPLAYUSER_COM.U_BLOCK_USER_FOR_ZONE_2_SEND( 602, &mUSER[tempUserIndex].uID[0] );
				}
				mUSER[tempUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return 0;
			}
			mUSER[tempUserIndex].mPacketEncryptionValue[1]++;
			mUSER[tempUserIndex].mCheckTime = ::time(NULL);
			W_FUNCTION[tProtocol].PROC( tempUserIndex );
			if (mUSER[tempUserIndex].mCheckConnectState) {
				memmove(mUSER[tempUserIndex].mBUFFER_FOR_RECV, mUSER[tempUserIndex].mBUFFER_FOR_RECV + mWORK.mWorkerPacketSize[tProtocol]
					, (mUSER[tempUserIndex].mTotalRecvSize - mWORK.mWorkerPacketSize[tProtocol]));
				mUSER[tempUserIndex].mTotalRecvSize -= mWORK.mWorkerPacketSize[tProtocol];
			}
			if(mUSER[tempUserIndex].mTotalRecvSize == 0)
				break;
		}
		return tRecvSizeFromUser;
	case FD_WRITE :
		for( tempUserIndex = 0 ; tempUserIndex < mMAX_USER_NUM ; tempUserIndex++ )
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
		if( tempUserIndex == mMAX_USER_NUM )
		{
			return -1;
		}
		mUSER[tempUserIndex].Send( FALSE, NULL, 0 );
		return 0;
	case FD_ACCEPT :
		tAddressLength = sizeof( tAddress );
		tSocket = accept( mSocket, (LPSOCKADDR) &tAddress, &tAddressLength );
		if( tSocket == INVALID_SOCKET )
		{
			return 0;
		}
		for( index01 = 0 ; index01 < mMAX_USER_NUM ; index01++ )
		{
			if( !mUSER[index01].mCheckConnectState )
			{
				break;
			}
		}
		if( index01 == mMAX_USER_NUM )
		{
			closesocket( tSocket );
			return 0;
		}
		if( WSAAsyncSelect( tSocket, hWnd, WM_NETWORK_MESSAGE_1, ( FD_READ | FD_WRITE | FD_CLOSE ) ) == SOCKET_ERROR )
		{
			closesocket( tSocket );
			return 0;
		}
		mUSER[index01].mCheckConnectState = TRUE;
		mUSER[index01].mCheckValidState = FALSE;
		mUSER[index01].mConnectTime = GetTickCount();
		mUSER[index01].mSocket = tSocket;
		sprintf( mUSER[index01].mIP, "%d.%d.%d.%d", tAddress.sin_addr.S_un.S_un_b.s_b1, tAddress.sin_addr.S_un.S_un_b.s_b2, tAddress.sin_addr.S_un.S_un_b.s_b3, tAddress.sin_addr.S_un.S_un_b.s_b4 );
		tRandomNumber = (rand() % 10000) * (rand() % 10000);
		CopyMemory(&mUSER[index01].mPacketEncryptionValue[0], &tRandomNumber, 1);
		CopyMemory(&mUSER[index01].mPacketEncryptionValue[1], &tRandomNumber, 1);
		mUSER[index01].mPacketEncryptionValue[1] += 127;
		mUSER[index01].mTotalSendSize = 0;
		mUSER[index01].mTotalRecvSize = 0;
		mUSER[index01].mUniqueNumber = 0;
		mUSER[index01].mAttackTickCount = 0;
		mUSER[index01].mAutoCheckCount = 0;
		mUSER[index01].mSpeedTickCount = 0;
		mUSER[index01].mCheckTempRegister = FALSE;
		ZeroMemory(&mAVATAR_OBJECT[index01].mDATA,sizeof(OBJECT_FOR_AVATAR));
		ZeroMemory(&mUSER[index01].mAvatarInfo, sizeof(AVATAR_INFO));
		mUSER[index01].mIsValidCashItemInfo = false;
		mUSER[index01].Set_Send_Question( FALSE );
#ifdef __GOD__
		mUSER[index01].mEffectCheckTime = ::time(NULL);
		mUSER[index01].mCheckTempRegister = FALSE;
#endif

		mUSER[index01].mXTrapTick = 0;

		mTRANSFER.B_CONNECT_OK( tRandomNumber );
		mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		return 0;
	case FD_CLOSE :
		for( tempUserIndex = 0 ; tempUserIndex < mMAX_USER_NUM ; tempUserIndex++ )
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
		if( tempUserIndex == mMAX_USER_NUM )
		{
			return 0;
		}
		//mUSER[tempUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return 0;
	}
}

void MyServer::HexDump(char *buf,int len,int addr) 
{
	int i,j,k;
	char binstr[80];

	for (i=0;i<len;i++) {
		if (0==(i%16)) {
			sprintf(binstr,"%08x -",i+addr);
			sprintf(binstr,"%s %02x",binstr,(unsigned char)buf[i]);
		} else if (15==(i%16)) {
			sprintf(binstr,"%s %02x",binstr,(unsigned char)buf[i]);
			sprintf(binstr,"%s  ",binstr);
			for (j=i-15;j<=i;j++) {
				sprintf(binstr,"%s%c",binstr,('!'<buf[j]&&buf[j]<='~')?buf[j]:'.');
			}
			printf("%s\n",binstr);
		} else {
			sprintf(binstr,"%s %02x",binstr,(unsigned char)buf[i]);
		}
	}
	if (0!=(i%16)) {
		k=16-(i%16);
		for (j=0;j<k;j++) {
			sprintf(binstr,"%s   ",binstr);
		}
		sprintf(binstr,"%s  ",binstr);
		k=16-k;
		for (j=i-k;j<i;j++) {
			sprintf(binstr,"%s%c",binstr,('!'<buf[j]&&buf[j]<='~')?buf[j]:'.');
		}
		printf("%s\n",binstr);
	}
}