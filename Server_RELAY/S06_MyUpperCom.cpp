#include "Shengming.h"
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_GAMELOG
//-------------------------------------------------------------------------------------------------
//INSTANCE
MyGameLog mGAMELOG;
//CREATE
MyGameLog::MyGameLog(void)
{
}
//INIT
BOOL MyGameLog::Init(char tIP[16], int tPort)
{
	if (DISCORD_NOTIFICATION_BOT_ACTIVE != 1)
	{
		return TRUE;
	}

	mCheckConnectState = FALSE;

	mSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (mSocket == INVALID_SOCKET)
	{
		return FALSE;
	}
	ZeroMemory(&mAddress, sizeof(mAddress));
	mAddress.sin_family = AF_INET;
	mAddress.sin_addr.s_addr = inet_addr(tIP);
	mAddress.sin_port = htons(10065);
	if (connect(mSocket, (LPSOCKADDR)&mAddress, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		closesocket(mSocket);
		return FALSE;
	}
	mCheckConnectState = TRUE;
	return TRUE;
}
//FREE
void MyGameLog::SendToLogServer(int LogSort)
{
	if (mCheckConnectState != TRUE)
	{
		return;
	}
	CopyMemory(&mSendBuffer[0], &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	send(mSocket, &mSendBuffer[0], mTRANSFER.mOriginalSize, 0);
}

