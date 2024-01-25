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
	//---------//
	//N-PROTECT//
	//---------//
#ifdef __N_PROTECT__	
	mNPROTECT = NULL;
#endif
	//---------//
	//---------//
	//---------//
}
//INIT
BOOL MyUser::Init( int tUserIndex, int tSendBufferSize, int tRecvBufferSize )
{
    m_bUDPActivated = false;
#ifndef __ORG__
	m_bUDPArrivedAtClient = false;
#endif
	m_iTryCountForAuth = 0;
	mUserIndex = tUserIndex;
#ifdef __GOD__
	mCheckConnectState = FALSE;
#endif
	mBUFFER_FOR_SEND = (char *) GlobalAlloc( GMEM_FIXED, tSendBufferSize );
	if( mBUFFER_FOR_SEND == NULL )
	{
		return FALSE;
	}
	mBUFFER_FOR_RECV = (char *) GlobalAlloc( GMEM_FIXED, tRecvBufferSize );
	if( mBUFFER_FOR_RECV == NULL )
	{
		return FALSE;
	}

	//@{ auto quize
	m_bIsBonusRecv = FALSE;
	m_bIsSend_Question = FALSE;			
	::ZeroMemory( m_tSphinx_Question, sizeof(m_tSphinx_Question) );
	m_dSend_Time = 0;
	m_iWrong_Count = 0;
	return TRUE;
}
//FREE
void MyUser::Free( void )
{
    m_bUDPActivated = false;
	if( mBUFFER_FOR_SEND != NULL )
	{
		free( mBUFFER_FOR_SEND );
		mBUFFER_FOR_SEND = NULL;
	}
	if( mBUFFER_FOR_RECV != NULL )
	{
		free( mBUFFER_FOR_RECV );
		mBUFFER_FOR_RECV = NULL;
	}
	m_bIsSend_Question = FALSE;			
	::ZeroMemory( m_tSphinx_Question, sizeof(m_tSphinx_Question) );
	m_dSend_Time = 0;
	m_iWrong_Count = 0;
	bUsePackItem = false;
}
//SEND
void MyUser::Send( BOOL tCheckValidBuffer, char *tBuffer, int tBufferSize, bool bUDPSend)
{ 
	if( !mCheckConnectState )
	{
		return;
	}

	int nResult = 0;
	int tSendValue01 = 0;
	if( tCheckValidBuffer )
	{
		if( ( mSERVER.mMAX_SEND_BUFFER_SIZE - mTotalSendSize ) < tBufferSize )
		{
			__LogMgr()->Log("![%s] : Send buffer full!(%d, %d) - %s\n", __FUNCTION__
					, ( mSERVER.mMAX_SEND_BUFFER_SIZE - mTotalSendSize )
					, tBufferSize, mAvatarInfo.aName);
			Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if(mTotalSendSize < 0) 
			mTotalSendSize = 0;
		::memcpy(mBUFFER_FOR_SEND + mTotalSendSize, tBuffer, tBufferSize);
		mTotalSendSize += tBufferSize;
	}

	while( mTotalSendSize > 0 )
	{
		tSendValue01 = send( mSocket, &mBUFFER_FOR_SEND[0], mTotalSendSize, 0 );
		if( tSendValue01 == SOCKET_ERROR )
		{
			if( WSAGetLastError() == WSAEWOULDBLOCK )
			{
				return;
			}
			Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		if((mTotalSendSize - tSendValue01) > 0) 
		{
			::memmove(mBUFFER_FOR_SEND, mBUFFER_FOR_SEND + tSendValue01,
				( mTotalSendSize - tSendValue01 ) );
		} 
		mTotalSendSize -= tSendValue01;
		if(mTotalSendSize < 0) 
		{
			mTotalSendSize = 0;
		}
	}
}
//QUIT
//void MyUser::Quit( void )
void MyUser::Quit(const char *tFileName, const char *tFuncName, int tLine)
{
	if( !mCheckConnectState )
	{
		return;
	}

	if (mUSER[mUserIndex].mAvatarInfo.FuryState == 1 && mUSER[mUserIndex].mAvatarInfo.Fury > 0) 
	{
		mUSER[mUserIndex].mAvatarInfo.Fury = 0;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(80, mUSER[mUserIndex].mAvatarInfo.Fury);
		mUSER[mUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}

	closesocket( mSocket );
	mSocket = -1;
	mCheckConnectState = FALSE;

	mTotalSendSize = 0;
	mTotalRecvSize = 0;

	m_iTryCountForAuth = 0;

	/** 2009. 11. 25 : 패키지 아이템 개발(wolf) */
	bUsePackItem = false;
	/** 2009. 11. 25 : 패키지 아이템 개발(wolf) */

  
	m_bUDPActivated = false;
   // g_BroadCastMgr.Delete (mAvatarInfo.aName);


	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	if( ( mCheckValidState ) && ( mMoveZoneResult == 0 ) )
	{
		//AÇILACAK DUPE
		mPLAYUSER_COM.U_DUPEFIX(mPlayUserIndex, &uID[0], &mAvatarInfo, &mAuthInfo);

		mCheckValidState = FALSE;

		if( strcmp(mAvatarInfo.aPartyName[0], "" ) != 0 )
		{
			if( strcmp(mAvatarInfo.aPartyName[0], mAvatarInfo.aName ) != 0 )
			{
				tSort = 106;
				CopyMemory( &tData[0], &mAvatarInfo.aPartyName[0], MAX_PARTY_NAME_LENGTH );
				CopyMemory( &tData[MAX_PARTY_NAME_LENGTH], &mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH );
				mRELAY_COM.U_DEMAND_BROADCAST_DATA( tSort, &tData[0] );
			}
			else
			{
				tSort = 109;
				CopyMemory( &tData[0], &mAvatarInfo.aPartyName[0], MAX_PARTY_NAME_LENGTH );
				tData[MAX_PARTY_NAME_LENGTH] = '\0';
				mRELAY_COM.U_DEMAND_BROADCAST_DATA( tSort, &tData[0] );
			}
		}
		mAvatarInfo.aLogoutInfo[0] = mSERVER_INFO.mServerNumber;
		mAvatarInfo.aLogoutInfo[1] = (int) mAVATAR_OBJECT[mUserIndex].mDATA.aAction.aLocation[0];
		mAvatarInfo.aLogoutInfo[2] = (int) mAVATAR_OBJECT[mUserIndex].mDATA.aAction.aLocation[1];
		mAvatarInfo.aLogoutInfo[3] = (int) mAVATAR_OBJECT[mUserIndex].mDATA.aAction.aLocation[2];
		mAvatarInfo.aLogoutInfo[4] = mAVATAR_OBJECT[mUserIndex].mDATA.aLifeValue;
		mAvatarInfo.aLogoutInfo[5] = mAVATAR_OBJECT[mUserIndex].mDATA.aManaValue;
		mPLAYUSER_COM.U_UNREGISTER_USER_FOR_ZONE_SEND( mPlayUserIndex, &uID[0], &mAvatarInfo, &mAuthInfo );
	}

	mCheckValidState = FALSE;
	mAVATAR_OBJECT[mUserIndex].mCheckValidState = false;
	mGAMELOG.GL_QUIT_LOG(uID, mAvatarInfo.aName, tFileName, tFuncName, tLine);
	::memset(&mAvatarInfo, 0x00, sizeof(AVATAR_INFO));
	mUSER[mUserIndex].AutoBuff1 = 0;
	//@{ auto quiz
	m_bIsBonusRecv = FALSE;
	m_bIsSend_Question = FALSE;			
	::ZeroMemory( m_tSphinx_Question, sizeof(m_tSphinx_Question) );
	m_dSend_Time = 0;
	m_iWrong_Count = 0;
	//@}	
}

BOOL MyUser::IsSend_TimeOver( void )
{
	if ( FALSE == IsSend_Question() ) return FALSE; 
	else;

	if ( ( ( GetTickCount() - m_dSend_Time ) / 1000 ) > (  LIMIT_SEND_TIME_MINUTE * 60 )  )
	{
		return TRUE;
	}
	else;

	return FALSE;
}
BOOL MyUser::IsWrong_CountOver( void )
{
	m_iWrong_Count++;

	if ( MAX_WRONG_ANSWER_COUNT <= m_iWrong_Count )
	{
		m_iWrong_Count = 0;
		return TRUE;
	}
	else;

	return FALSE;
}
bool MyUser::IsValidSkillNumber(int skillNumber)
{
    for (int index = 0; index < MAX_SKILL_SLOT_NUM; ++index) {
        if (mAvatarInfo.aSkill[index][0] == skillNumber) {
            return true;
        }
    }
    return false;
}
int MyUser::GetMaxSkillGradeNum(int skillNumber)
{
    for (int index = 0; index < MAX_SKILL_SLOT_NUM; ++index) {
        if (mAvatarInfo.aSkill[index][0] == skillNumber) {
            return mAvatarInfo.aSkill[index][1];
        }
    }
    return 1;
}
//-------------------------------------------------------------------------------------------------
