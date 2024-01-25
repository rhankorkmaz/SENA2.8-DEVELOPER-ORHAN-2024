//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "Shengming.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_GAME
//-------------------------------------------------------------------------------------------------
//THREAD_FOR_DB_WORKER
DWORD WINAPI THREAD_FOR_DB_WORKER( PVOID pParam )
//void *THREAD_FOR_DB_WORKER(void *arg)
{
	while( TRUE )
	{
		WaitForSingleObject( mGAME.mEHandle, 100 );
		mGAME.ProcessForSave_2();
	}
	return NULL;
}
//INSTANCE
MyGame mGAME;
//CREATE
MyGame::MyGame( void ) { }
//INIT
BOOL MyGame::Init( void )
{
	int index01;

	if( !LoadForTribeBankInfo() )
	{
		__LogMgr()->Log("![%s] : %s\n", __FUNCTION__,  "[Error::( !LoadForTribeBankInfo() )]");
		return FALSE;
	}
	mTickCount = 0;
	for( index01 = 0 ; index01 < MAX_PLAY_USER_NUM ; index01++ )
	{
		mCheckValidState[index01] = FALSE;
	}
	mTotalSave1Num = 0;
	mTotalSave2Num = 0;
	DWORD tID = NULL;
	InitializeCriticalSection( &mCriticalSection );
	mEHandle = CreateEvent( NULL, FALSE, FALSE, NULL );
	if( mEHandle == NULL )
	{
		return FALSE;
	}
	mTHandle = CreateThread( NULL, 0, THREAD_FOR_DB_WORKER, NULL, 0, &tID );
	if( mTHandle == NULL )
	{
		return FALSE;
	}
	for( index01 = 0 ; index01 < MAX_PLAY_USER_NUM ; index01++ )
	{
		mCheckKillOtherTribe[index01] = FALSE;
	}
	return TRUE;
}
//FREE
void MyGame::Free( void )
{
	if( mTHandle != NULL )
	{
		TerminateThread( mTHandle, 0 );
		CloseHandle( mTHandle );
		mTHandle = NULL;
	}
	if( mEHandle != NULL )
	{
		CloseHandle( mEHandle );
		mEHandle = NULL;
	}
	DeleteCriticalSection( &mCriticalSection );
}
//CHECK_OVER_MAXIMUM
BOOL MyGame::CheckOverMaximum( int tValue1, int tValue2 )
{
	LONGLONG tCheckValue = (LONGLONG) tValue1 + (LONGLONG) tValue2;

	if( tCheckValue > MAX_NUMBER_SIZE )
	{
		return TRUE;
	}
	return FALSE;
}
//LOAD_FOR_TRIBE_BANK_INFO
BOOL MyGame::LoadForTribeBankInfo( void )
{
	int index01;
	int index02;
	HANDLE hFile;
	DWORD nReadByte;

	hFile = CreateFile( "TRIBE_BANK_INFO.DAT", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if( hFile == INVALID_HANDLE_VALUE )
	{
		for( index01 = 0 ; index01 < 4 ; index01++ )
		{
			for( index02 = 0 ; index02 < MAX_TRIBE_BANK_SLOT_NUM ; index02++ )
			{
				mTribeBankInfo[index01][index02] = 0;
			}
		}
		return TRUE;
	}
	if( !ReadFile( hFile, &mTribeBankInfo[0][0], ( 16 * MAX_TRIBE_BANK_SLOT_NUM ), &nReadByte, NULL ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( nReadByte != ( 16 * MAX_TRIBE_BANK_SLOT_NUM ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( !CloseHandle( hFile ) )
	{
		return FALSE;
	}
	return TRUE;

}
//SAVE_FOR_TRIBE_BANK_INFO
void MyGame::SaveForTribeBankInfo( void )
{
	HANDLE hFile;
	DWORD nWriteByte;

	hFile = CreateFile(	"TRIBE_BANK_INFO.DAT", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
	if( hFile == INVALID_HANDLE_VALUE )
	{
		return;
	}
	if( !WriteFile( hFile, &mTribeBankInfo[0][0], ( 16 * MAX_TRIBE_BANK_SLOT_NUM ), &nWriteByte, NULL ) )
	{
		CloseHandle( hFile );
		return;
	}
	if( nWriteByte != ( 16 * MAX_TRIBE_BANK_SLOT_NUM ) )
	{
		CloseHandle( hFile );
		return;
	}
	if( !CloseHandle( hFile ) )
	{
		return;
	}
}
//PROCESS_FOR_PLAY_USER
void MyGame::ProcessForPlayUser( void )
{
	int index01;
	int index02;
	DWORD tPresentTime;

	tPresentTime = GetTickCount();
	for( index01 = 0 ; index01 < MAX_PLAY_USER_NUM ; index01++ )
	{
		if( !mCheckValidState[index01] )
		{
			continue;
		}
		if( mRegisterSort[index01] == 1 )
		{
			if( ( tPresentTime - mPostTime[index01] ) < 360000 )
			{
				continue;
			}
		}
		else if( mRegisterSort[index01] == 2 )
		{
			if( ( tPresentTime - mPostTime[index01] ) < 360000 )
			{
				continue;
			}
		}
		else if( mRegisterSort[index01] == 3 )
		{
			if( ( tPresentTime - mPostTime[index01] ) < 180000 )
			{
				continue;
			}
		}
		else if( mRegisterSort[index01] == 4 )
		{
			if( ( tPresentTime - mPostTime[index01] ) < 180000 )
			{
				continue;
			}
		}
		else if( mRegisterSort[index01] == 5 )
		{
			if( ( tPresentTime - mPostTime[index01] ) < 360000 )
			{
				continue;
			}
		}
		else if( mRegisterSort[index01] == 6 )
		{
			if( ( tPresentTime - mPostTime[index01] ) < 360000 )
			{
				continue;
			}
		}
		else
		{
			if( ( tPresentTime - mPostTime[index01] ) < 360000 )
			{
				continue;
			}
		}
		mCheckValidState[index01] = FALSE;
		if( mZoneNumber[index01] == 0 )
		{
			mDB.DB_PROCESS_02( &mID[index01][0]);
//			mGAMELOG.GL_103_WAIT_LOGOUT_1( &mID[index01][0] );
			continue;
		}
		ProcessForSave_1( 1, &mID[index01][0], &mAvatarInfo[index01], &mAuthInfo[index01], mLoginPremiumPCRoom[index01] );
		mPlayTime[index01] = ( GetTickCount() - mPlayTime[index01] ) / 1000;
//		mGAMELOG.GL_107_WAIT_LOGOUT_2( &mID[index01][0], &mAvatarInfo[index01].aName[0], mZoneNumber[index01] );
		for( index02 = 0 ; index02 < MAX_USER_NUM ; index02++ )
		{
			if( mUSER[index02].mCheckServerType == 4 )
			{
				mTRANSFER.B_USER_INFO_FOR_POLICE2( &mID[index01][0], &mIP[index01][0], '1' );
				mUSER[index02].Send( TRUE, (char *) &mTRANSFER.mOriginal2[0], mTRANSFER.mOriginalSize2 );
			}
		}
	}
}
//PROCESS_FOR_SAVE_1
void MyGame::ProcessForSave_1( int tSort, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO *tAvatarInfo, AUTH_INFO *tAuthInfo, int tLoginPremiumPCRoom )
{

	while( TRUE )
	{
		if( mTotalSave1Num == MAX_PLAY_USER_NUM )
		{
			Sleep( 100 );
		}
		else
		{
			EnterCriticalSection(&mCriticalSection);
			mSave1Sort[mTotalSave1Num] = tSort;
			strcpy( mSave1ID[mTotalSave1Num], tID );
			CopyMemory( &mSave1AvatarInfo[mTotalSave1Num], tAvatarInfo, sizeof( AVATAR_INFO ) );
			CopyMemory( &mSave1AuthInfo[mTotalSave1Num], tAuthInfo, sizeof( AUTH_INFO ) );
			mSave1LoginPremiumPCRoom[mTotalSave1Num] = tLoginPremiumPCRoom;
			mTotalSave1Num++;
			LeaveCriticalSection(&mCriticalSection);
			return;
		}
	}
}
//PROCESS_FOR_SAVE_2
void MyGame::ProcessForSave_2( void )
{
	int index01;

	mTotalSave2Num = mTotalSave1Num;
	for( index01 = 0 ; index01 < mTotalSave1Num ; index01++ )
	{
		mSave2Sort[index01] = mSave1Sort[index01];
		strcpy( mSave2ID[index01], mSave1ID[index01] ); 
		CopyMemory( &mSave2AvatarInfo[index01], &mSave1AvatarInfo[index01], sizeof( AVATAR_INFO ) );
		CopyMemory( &mSave2AuthInfo[index01], &mSave1AuthInfo[index01], sizeof( AUTH_INFO ) );
		mSave2LoginPremiumPCRoom[index01] = mSave1LoginPremiumPCRoom[index01];
	}
	mTotalSave1Num = 0;
	for( index01 = 0 ; index01 < mTotalSave2Num ; index01++ )
	{
		mDB.DB_PROCESS_03( mSave2Sort[index01], &mSave2ID[index01][0], &mSave2AvatarInfo[index01], &mSave2AuthInfo[index01], mSave2LoginPremiumPCRoom[index01] );
	}
}
//SAFE_AVATAR_INFO_DATA
void MyGame::SafeAvatarInfoData( AVATAR_INFO *tAvatarInfo )
{
	int index01;

	tAvatarInfo->aName[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';
	for( index01 = 0 ; index01 < MAX_FRIEND_NUM ; index01++ )
	{
		tAvatarInfo->aFriend[index01][( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';
	}
	tAvatarInfo->aTeacher[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';
	tAvatarInfo->aStudent[( MAX_AVATAR_NAME_LENGTH - 1 )] = '\0';
	tAvatarInfo->aGuildName[( MAX_GUILD_NAME_LENGTH - 1 )] = '\0';
	tAvatarInfo->aCallName[( MAX_CALL_NAME_LENGTH - 1 )] = '\0';
	tAvatarInfo->aPartyName[0][(MAX_PARTY_NAME_LENGTH - 1 )] = '\0';
	tAvatarInfo->aPartyName[1][(MAX_PARTY_NAME_LENGTH - 1)] = '\0';
	tAvatarInfo->aPartyName[2][(MAX_PARTY_NAME_LENGTH - 1)] = '\0';
	tAvatarInfo->aPartyName[3][(MAX_PARTY_NAME_LENGTH - 1)] = '\0';
	tAvatarInfo->aPartyName[4][(MAX_PARTY_NAME_LENGTH - 1)] = '\0';
}
//RETURN_PRESENT_USER_NUM
int MyGame::ReturnPresentUserNum( int tZoneNumber )
{
	int index01;
	int tPresentUserNum;

	tPresentUserNum = 0;
	for( index01 = 0 ; index01 < MAX_PLAY_USER_NUM ; index01++ )
	{
		if( !mCheckValidState[index01] )
		{
			continue;
		}
		if( tZoneNumber == 0 )
		{
			tPresentUserNum++;
		}
		else
		{
			if( mZoneNumber[index01] == tZoneNumber )
			{
				tPresentUserNum++;
			}
		}
	}
	return tPresentUserNum;
}

void MyGame::ReturnPresentUserNum(char *tBuffer)
{
	int index01;
	char tmp_buffer[16];
	map<int, int> mapZoneUser;
	map<int, int>::iterator it;

	for(index01 = 0; index01 < MAX_PLAY_USER_NUM; index01++) {
		if((!mCheckValidState[index01]) || (mZoneNumber[index01] <= 0)) {
			continue;
		}
		it = mapZoneUser.find(mZoneNumber[index01]);
		if(it == mapZoneUser.end()) {
			mapZoneUser[mZoneNumber[index01]] = 1;
		} else {
			(it->second)++;
		}
	}

	for(it = mapZoneUser.begin(); it != mapZoneUser.end(); ++it) {
		_snprintf(tmp_buffer, 16, "%d:%d|", it->first, it->second);
		strncat(tBuffer, tmp_buffer, strlen(tmp_buffer));
		//__LogMgr()->Log("tmp_buffer : %s %s\n", tBuffer, tmp_buffer);
	}
	//tBuffer[strlen(tBuffer) - 1] = '\0';
	mapZoneUser.clear();
}
//RETURN_EXIST_ZONE_NUMBER_FOR_AVATAR_NAME
int MyGame::ReturnExistZoneNumberForAvatarName( char tAvatarName[MAX_AVATAR_NAME_LENGTH], int *tTribe )
{
	int index01;

	for( index01 = 0 ; index01 < MAX_PLAY_USER_NUM ; index01++ )
	{
		if( !mCheckValidState[index01] )
		{
			continue;
		}
		if( mZoneNumber[index01] == 0 )
		{
			continue;
		}
		if( strcmp( mAvatarInfo[index01].aName, tAvatarName ) == 0 )
		{
			break;
		}
	}
	if( index01 < MAX_PLAY_USER_NUM )
	{
		*tTribe = mAvatarInfo[index01].aTribe;
		return mZoneNumber[index01];
	}
	*tTribe = -1;
	return -1;
}
//RETURN_EXIST_ZONE_NUMBER_FOR_USER_ID
int MyGame::ReturnExistZoneNumberForUserID( char tID[MAX_USER_ID_LENGTH] )
{
	int index01;

	for( index01 = 0 ; index01 < MAX_PLAY_USER_NUM ; index01++ )
	{
		if( !mCheckValidState[index01] )
		{
			continue;
		}
		if( strcmp( mID[index01], tID ) == 0 )
		{
			break;
		}
	}
	if( index01 < MAX_PLAY_USER_NUM )
	{
		return mZoneNumber[index01];
	}
	return -1;
}
//REGISTER_USER_FOR_LOGIN_01
int MyGame::RegisterUserForLogin_01( char tIP[16], char tID[MAX_USER_ID_LENGTH], int tUserSort, int tGoodFellow, int tUserRandom, int tLoginPremium, int tLoginPremiumPCRoom, int tTraceState, char tBonus100Money, int tPremiumServerExpirationDate, int *tPlayUserIndex, AUTH_INFO *tAuthInfo ) // 함수 선언 수정 - int tPremiumServerExpirationDate 추가. // @_Premium_Server_@
{
	int index01;

	for( index01 = 0 ; index01 < MAX_PLAY_USER_NUM ; index01++ )
	{
		if( !mCheckValidState[index01] )
		{
			continue;
		}
		if( strcmp( mID[index01], tID ) == 0 )
		{
			break;
		}
	}

	if( index01 < MAX_PLAY_USER_NUM )
	{
		return 1;
	}
	//--------------------//
	//...._.._...//
	//--------------------//
	//--------------------//
	//--------------------//
	//--------------------//

	for( index01 = 0 ; index01 < MAX_PLAY_USER_NUM ; index01++ )
	{
		if( !mCheckValidState[index01] )
		{
			break;
		}
	}
	if( index01 == MAX_PLAY_USER_NUM )
	{
		return 2;
	}
	if( !mDB.DB_PROCESS_01( &tID[0], tIP ) )
	{
		return 3;
	}
	mCheckValidState[index01] = TRUE;
	mRegisterSort[index01] = 1;
	mSaveTime[index01] = GetTickCount();
	mPostTime[index01] = GetTickCount();
	mPlayTime[index01] = GetTickCount();
	mZoneNumber[index01] = 0;
	strcpy( mIP[index01], tIP );
	strcpy( mID[index01], tID );
	mUserSort[index01] = tUserSort;
	mGoodFellow[index01] = tGoodFellow;
	mUserRandom[index01] = tUserRandom;
	mLoginPremium[index01] = tLoginPremium;
	mLoginPremiumPCRoom[index01] = tLoginPremiumPCRoom;
	mTraceState[index01] = tTraceState;
	mBonus100Money[index01] = tBonus100Money;
	mPremiumServerExpirationDate[index01] = tPremiumServerExpirationDate; // @_Premium_Server_@
	strcpy( mAvatarInfo[index01].aName, "" );
	mFirstEnterZone[index01] = TRUE;
	memset(&mGAME.mMoveItemInfo[index01], -1, sizeof(MOVE_ITEM_INFO)); // 이동서 아이템 정보 초기화
	*tPlayUserIndex = index01;
	CopyMemory(&mAuthInfo[index01], tAuthInfo, sizeof(AUTH_INFO));
//	mGAMELOG.GL_101_LOGIN( &mID[index01][0], &mIP[index01][0] );
	return 0;
}
//REGISTER_USER_FOR_LOGIN_02
int MyGame::RegisterUserForLogin_02( int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH] )
{
	if( ( tPlayUserIndex < 0 ) || ( tPlayUserIndex > ( MAX_PLAY_USER_NUM - 1 ) ) || ( !mCheckValidState[tPlayUserIndex] ) || ( mZoneNumber[tPlayUserIndex] != 0 ) || ( strcmp( mID[tPlayUserIndex], tID ) != 0 ) )
	{
		return 1;
	}
	mRegisterSort[tPlayUserIndex] = 2;
	mSaveTime[tPlayUserIndex] = GetTickCount();
	mPostTime[tPlayUserIndex] = GetTickCount();
	return 0;
}
//REGISTER_USER_FOR_LOGIN_03
int MyGame::RegisterUserForLogin_03( int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO *tAvatarInfo )
{
	if( ( tPlayUserIndex < 0 ) || ( tPlayUserIndex > ( MAX_PLAY_USER_NUM - 1 ) ) || ( !mCheckValidState[tPlayUserIndex] ) || ( mZoneNumber[tPlayUserIndex] != 0 ) || ( strcmp( mID[tPlayUserIndex], tID ) != 0 ) )
	{
		return 1;
	}

	int index01;

	mRegisterSort[tPlayUserIndex] = 3;
	mSaveTime[tPlayUserIndex] = GetTickCount();
	mPostTime[tPlayUserIndex] = GetTickCount();
	CopyMemory( &mAvatarInfo[tPlayUserIndex], tAvatarInfo, sizeof( AVATAR_INFO ) );
	mAnimalOn[tPlayUserIndex] = 0;
	for( index01 = 0 ; index01 < MAX_AVATAR_EFFECT_SORT_NUM ; index01++ )
	{
		mEffectValue[tPlayUserIndex][index01][0] = 0;
		mEffectValue[tPlayUserIndex][index01][1] = 0;
	}
	return 0;
}
//UNREGISTER_USER_FOR_LOGIN
void MyGame::UnRegisterUserForLogin( int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH] )
{
	if( ( tPlayUserIndex < 0 ) || ( tPlayUserIndex > ( MAX_PLAY_USER_NUM - 1 ) ) || ( !mCheckValidState[tPlayUserIndex] ) || ( mZoneNumber[tPlayUserIndex] != 0 ) || ( strcmp( mID[tPlayUserIndex], tID ) != 0 ) )
	{
		return;
	}
	mCheckValidState[tPlayUserIndex] = FALSE;
	mDB.DB_PROCESS_02( &mID[tPlayUserIndex][0]);
//	mGAMELOG.GL_102_LOGOUT_1( &mID[tPlayUserIndex][0] );
}
//REGISTER_USER_FOR_ZONE_00
int MyGame::RegisterUserForZone_00( int tZoneNumber, char tID[MAX_USER_ID_LENGTH], int *tPlayUserIndex )
{
	int index01;

	for( index01 = 0 ; index01 < MAX_PLAY_USER_NUM ; index01++ )
	{
		if( !mCheckValidState[index01] )
		{
			continue;
		}
		if( strncmp( mID[index01], tID, MAX_USER_ID_LENGTH ) == 0 )
		{
			break;
		}
	}
	if( index01 == MAX_PLAY_USER_NUM )
	{
		__LogMgr()->Log("![%s] : index01(%d), MAX_PLAY_USER_NUM(%d)\n"
			, __FUNCTION__, index01, MAX_PLAY_USER_NUM);
		return 1;
	}
	if( ( mRegisterSort[index01] != 3 ) && ( mRegisterSort[index01] != 7 ) )
	{
		__LogMgr()->Log("![%s] : mRegisterSort[index01](%d)\n" , __FUNCTION__
			, mRegisterSort[index01]);
		mCheckValidState[index01] = false;
		return 2;
	}
	mRegisterSort[index01] = 4;
	mPostTime[index01] = GetTickCount();
	if( mFirstEnterZone[index01] )
	{
		mPlayTime[index01] = GetTickCount();
	}
	mZoneNumber[index01] = tZoneNumber;
	*tPlayUserIndex = index01;
	return 0;
}
//REGISTER_USER_FOR_ZONE_01
int MyGame::RegisterUserForZone_01( int tZoneNumber, int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH], char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tLogoutInfo[6], int *tUserSort, int *tGoodFellow, int * tUserRandom, int *tLoginPremium, int *tLoginPremiumPCRoom, int *tTraceState, char *tBonus100Money, int *tPremiumServerExpirationDate, AVATAR_INFO *tAvatarInfo, int tEffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2], int *tCheckFirstZone, AUTH_INFO *tAuthInfo, int *AnimalOn ) // 함수 선언 수정 - int *tPremiumServerExpirationDate 추가. // @_Premium_Server_@
{
	if( ( tPlayUserIndex < 0 ) || ( tPlayUserIndex > ( MAX_PLAY_USER_NUM - 1 ) ) || ( !mCheckValidState[tPlayUserIndex] ) || ( mZoneNumber[tPlayUserIndex] != tZoneNumber ) || ( strcmp( mID[tPlayUserIndex], tID ) != 0 ) || ( strcmp( mAvatarInfo[tPlayUserIndex].aName, tAvatarName ) != 0 ) )
	{
		if(tPlayUserIndex >= 0) {
			mCheckValidState[tPlayUserIndex] = false;
		}
		return 1;
	}

	int index01;

	mRegisterSort[tPlayUserIndex] = 5;
	mPostTime[tPlayUserIndex] = GetTickCount();
	if( mFirstEnterZone[tPlayUserIndex] )
	{
		mPlayTime[tPlayUserIndex] = GetTickCount();
		//mGAMELOG.GL_000_PLAY_LOG( 0, 0, &mID[tPlayUserIndex][0], &mIP[tPlayUserIndex][0], mLoginPremium[tPlayUserIndex], mSERVER_INFO.mWorldNumber, &mAvatarInfo[tPlayUserIndex].aName[0], mAvatarInfo[tPlayUserIndex].aTribe, mAvatarInfo[tPlayUserIndex].aLevel1, mAvatarInfo[tPlayUserIndex].aGeneralExperience1, mAvatarInfo[tPlayUserIndex].aKillOtherTribe, mAvatarInfo[tPlayUserIndex].aMoney, mAvatarInfo[tPlayUserIndex].aStoreMoney, mZoneNumber[tPlayUserIndex] );
///		mGAMELOG.GL_104_ENTER_ZONE( &mID[tPlayUserIndex][0], &mAvatarInfo[tPlayUserIndex].aName[0], mZoneNumber[tPlayUserIndex] );
		for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
		{
			if( mUSER[index01].mCheckServerType == 4 )
			{
				mTRANSFER.B_USER_INFO_FOR_POLICE( &mID[tPlayUserIndex][0], &mIP[tPlayUserIndex][0], '1' );
				mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
			}
		}
	}
	else
	{
//		mGAMELOG.GL_105_MOVE_ZONE( &mID[tPlayUserIndex][0], &mAvatarInfo[tPlayUserIndex].aName[0], mZoneNumber[tPlayUserIndex] );
	}
	mAvatarInfo[tPlayUserIndex].aLogoutInfo[0] = tLogoutInfo[0];
	mAvatarInfo[tPlayUserIndex].aLogoutInfo[1] = tLogoutInfo[1];
	mAvatarInfo[tPlayUserIndex].aLogoutInfo[2] = tLogoutInfo[2];
	mAvatarInfo[tPlayUserIndex].aLogoutInfo[3] = tLogoutInfo[3];
	*tUserSort = mUserSort[tPlayUserIndex];
	*tGoodFellow = mGoodFellow[tPlayUserIndex];
	*tUserRandom = mUserRandom[tPlayUserIndex];
	*tLoginPremium = mLoginPremium[tPlayUserIndex];
	*tLoginPremiumPCRoom = mLoginPremiumPCRoom[tPlayUserIndex];
	*tTraceState = mTraceState[tPlayUserIndex];
	*tBonus100Money = mBonus100Money[tPlayUserIndex];
	*tPremiumServerExpirationDate = mPremiumServerExpirationDate[tPlayUserIndex]; // @_Premium_Server_@
	*AnimalOn = mAnimalOn[tPlayUserIndex];
	CopyMemory( tAvatarInfo, &mAvatarInfo[tPlayUserIndex], sizeof( AVATAR_INFO ) );
	CopyMemory( tAuthInfo, &mAuthInfo[tPlayUserIndex], sizeof(AUTH_INFO ) );
	for( index01 = 0 ; index01 < MAX_AVATAR_EFFECT_SORT_NUM ; index01++ )
	{
		tEffectValue[index01][0] = mEffectValue[tPlayUserIndex][index01][0];
		tEffectValue[index01][1] = mEffectValue[tPlayUserIndex][index01][1];
	}
	if( mFirstEnterZone[tPlayUserIndex] )
	{
		*tCheckFirstZone = 1;
	}
	else
	{
		*tCheckFirstZone = 0;
	}
	
	mFirstEnterZone[tPlayUserIndex] = FALSE;
	return 0;
}
//REGISTER_USER_FOR_ZONE_02
int MyGame::RegisterUserForZone_02( int tZoneNumber, int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO *tAvatarInfo, int tEffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2],\
								   AUTH_INFO *tAuthInfo)
{
	if( ( tPlayUserIndex < 0 ) || ( tPlayUserIndex > ( MAX_PLAY_USER_NUM - 1 ) ) || ( !mCheckValidState[tPlayUserIndex] ) || ( mZoneNumber[tPlayUserIndex] != tZoneNumber ) || ( strcmp( mID[tPlayUserIndex], tID ) != 0 ) || ( strcmp( mAvatarInfo[tPlayUserIndex].aName, tAvatarInfo->aName ) != 0 ) )
	{
		if(tPlayUserIndex >= 0) 
		{
			mCheckValidState[tPlayUserIndex] = false;
		}
		//__LogMgr()->Log("呵겨!!!");
		return 1;
	}

	//__LogMgr()->Log("냥묘!");
	int index01;
	DWORD tTickCount;

	tTickCount = GetTickCount();
	mRegisterSort[tPlayUserIndex] = 6;
	mPostTime[tPlayUserIndex] = tTickCount;
	CopyMemory( &mAvatarInfo[tPlayUserIndex], tAvatarInfo, sizeof( AVATAR_INFO ) );
	CopyMemory( &mAuthInfo[tPlayUserIndex], tAuthInfo, sizeof( AUTH_INFO ) );
	for( index01 = 0 ; index01 < MAX_AVATAR_EFFECT_SORT_NUM ; index01++ )
	{
		mEffectValue[tPlayUserIndex][index01][0] = tEffectValue[index01][0];
		mEffectValue[tPlayUserIndex][index01][1] = tEffectValue[index01][1];
	}
	if( ( tTickCount - mSaveTime[tPlayUserIndex] ) >= 170000 )
	{
		mSaveTime[tPlayUserIndex] = tTickCount;
		ProcessForSave_1( 2, &mID[tPlayUserIndex][0], &mAvatarInfo[tPlayUserIndex], &mAuthInfo[tPlayUserIndex], mLoginPremiumPCRoom[tPlayUserIndex] );
	}
	return 0;
}
//REGISTER_USER_FOR_ZONE_03
int MyGame::RegisterUserForZone_03( int tZoneNumber, int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO *tAvatarInfo, int tEffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2], AUTH_INFO *tAuthInfo, int AnimalOn)
{
	if( ( tPlayUserIndex < 0 ) || ( tPlayUserIndex > ( MAX_PLAY_USER_NUM - 1 ) ) || ( !mCheckValidState[tPlayUserIndex] ) || ( mZoneNumber[tPlayUserIndex] != tZoneNumber ) || ( strcmp( mID[tPlayUserIndex], tID ) != 0 ) || ( strcmp( mAvatarInfo[tPlayUserIndex].aName, tAvatarInfo->aName ) != 0 ) )
	{
		if(tPlayUserIndex >= 0) {
			mCheckValidState[tPlayUserIndex] = false;
		}
		return 1;
	}

	int index01;
	DWORD tTickCount;

	tTickCount = GetTickCount();
	mRegisterSort[tPlayUserIndex] = 7;
	mPostTime[tPlayUserIndex] = tTickCount;
	CopyMemory( &mAvatarInfo[tPlayUserIndex], tAvatarInfo, sizeof( AVATAR_INFO ) );
	CopyMemory( &mAuthInfo[tPlayUserIndex], tAuthInfo, sizeof( AUTH_INFO ) );
	for( index01 = 0 ; index01 < MAX_AVATAR_EFFECT_SORT_NUM ; index01++ )
	{
		mEffectValue[tPlayUserIndex][index01][0] = tEffectValue[index01][0];
		mEffectValue[tPlayUserIndex][index01][1] = tEffectValue[index01][1];

	}
	mAnimalOn[tPlayUserIndex] = AnimalOn;
	if( ( tTickCount - mSaveTime[tPlayUserIndex] ) >= 170000 )
	{
		mSaveTime[tPlayUserIndex] = tTickCount;
		ProcessForSave_1( 2, &mID[tPlayUserIndex][0], &mAvatarInfo[tPlayUserIndex], &mAuthInfo[tPlayUserIndex], mLoginPremiumPCRoom[tPlayUserIndex] );
	}


	return 0;
}
//UNREGISTER_USER_FOR_ZONE
void MyGame::UnRegisterUserForZone( int tZoneNumber, int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO *tAvatarInfo, AUTH_INFO *tAuthInfo )
{
	if( ( tPlayUserIndex < 0 ) || ( tPlayUserIndex > ( MAX_PLAY_USER_NUM - 1 ) ) || ( !mCheckValidState[tPlayUserIndex] ) || ( mZoneNumber[tPlayUserIndex] != tZoneNumber ) || ( strcmp( mID[tPlayUserIndex], tID ) != 0 ) || ( strcmp( mAvatarInfo[tPlayUserIndex].aName, tAvatarInfo->aName ) != 0 ) )
	{
		if(tPlayUserIndex >= 0) {
			mCheckValidState[tPlayUserIndex] = false;
		}
		return;
	}

	int index01;

	mCheckValidState[tPlayUserIndex] = FALSE;
	CopyMemory( &mAvatarInfo[tPlayUserIndex], tAvatarInfo, sizeof( AVATAR_INFO ) );
	CopyMemory( &mAuthInfo[tPlayUserIndex], tAuthInfo, sizeof( AUTH_INFO ) );
	ProcessForSave_1( 1, &mID[tPlayUserIndex][0], &mAvatarInfo[tPlayUserIndex], &mAuthInfo[tPlayUserIndex], mLoginPremiumPCRoom[tPlayUserIndex] );
	mPlayTime[tPlayUserIndex] = ( GetTickCount() - mPlayTime[tPlayUserIndex] ) / 1000;
#ifdef __GOD__


	if( mAvatarInfo[tPlayUserIndex].aLevel2 < 1 )
	{
//		mGAMELOG.GL_000_PLAY_LOG( 1, mPlayTime[tPlayUserIndex], &mID[tPlayUserIndex][0], &mIP[tPlayUserIndex][0], mLoginPremiumPCRoom[tPlayUserIndex], mSERVER_INFO.mWorldNumber, &mAvatarInfo[tPlayUserIndex].aName[0], mAvatarInfo[tPlayUserIndex].aTribe, ( mAvatarInfo[tPlayUserIndex].aLevel1 + mAvatarInfo[tPlayUserIndex].aLevel2 ), mAvatarInfo[tPlayUserIndex].aGeneralExperience1, mAvatarInfo[tPlayUserIndex].aKillOtherTribe, mAvatarInfo[tPlayUserIndex].aMoney, mAvatarInfo[tPlayUserIndex].aStoreMoney, mZoneNumber[tPlayUserIndex] );
	}
	else
	{
//		mGAMELOG.GL_000_PLAY_LOG( 1, mPlayTime[tPlayUserIndex], &mID[tPlayUserIndex][0], &mIP[tPlayUserIndex][0], mLoginPremiumPCRoom[tPlayUserIndex], mSERVER_INFO.mWorldNumber, &mAvatarInfo[tPlayUserIndex].aName[0], mAvatarInfo[tPlayUserIndex].aTribe, ( mAvatarInfo[tPlayUserIndex].aLevel1 + mAvatarInfo[tPlayUserIndex].aLevel2 ), mAvatarInfo[tPlayUserIndex].aGeneralExperience2, mAvatarInfo[tPlayUserIndex].aKillOtherTribe, mAvatarInfo[tPlayUserIndex].aMoney, mAvatarInfo[tPlayUserIndex].aStoreMoney, mZoneNumber[tPlayUserIndex] );
	}

#else
	mGAMELOG.GL_000_PLAY_LOG( 1, mPlayTime[tPlayUserIndex], &mID[tPlayUserIndex][0], &mIP[tPlayUserIndex][0], mLoginPremiumPCRoom[tPlayUserIndex], mSERVER_INFO.mWorldNumber, &mAvatarInfo[tPlayUserIndex].aName[0], mAvatarInfo[tPlayUserIndex].aTribe, mAvatarInfo[tPlayUserIndex].aLevel1, mAvatarInfo[tPlayUserIndex].aGeneralExperience1, mAvatarInfo[tPlayUserIndex].aKillOtherTribe, mAvatarInfo[tPlayUserIndex].aMoney, mAvatarInfo[tPlayUserIndex].aStoreMoney, mZoneNumber[tPlayUserIndex] );
#endif
//	mGAMELOG.GL_106_LOGOUT_2( &mID[tPlayUserIndex][0], &mAvatarInfo[tPlayUserIndex].aName[0], mZoneNumber[tPlayUserIndex] );
	for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
	{
		if( mUSER[index01].mCheckServerType == 4 )
		{
			mTRANSFER.B_USER_INFO_FOR_POLICE( &mID[tPlayUserIndex][0], &mIP[tPlayUserIndex][0], '0' );
			mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		}
	}
}
//UNREGISTER_USER_FOR_ZONE
void MyGame::DUPEFIX(int tZoneNumber, int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO* tAvatarInfo, AUTH_INFO* tAuthInfo)
{
	CopyMemory(&mAvatarInfo[tPlayUserIndex], tAvatarInfo, sizeof(AVATAR_INFO));
	CopyMemory(&mAuthInfo[tPlayUserIndex], tAuthInfo, sizeof(AUTH_INFO));
	ProcessForSave_1(1, &mID[tPlayUserIndex][0], &mAvatarInfo[tPlayUserIndex], &mAuthInfo[tPlayUserIndex], mLoginPremiumPCRoom[tPlayUserIndex]);
	mPlayTime[tPlayUserIndex] = (GetTickCount() - mPlayTime[tPlayUserIndex]) / 1000;
}
//PROCESS_KILL_OTHER_TRIBE
int MyGame::ProcessKillOtherTribe( char tAvatarName1[MAX_AVATAR_NAME_LENGTH], char tAvatarName2[MAX_AVATAR_NAME_LENGTH] )
{
	int index01;
	DWORD tTickCount;

	tTickCount = GetTickCount();
	for( index01 = 0 ; index01 < MAX_PLAY_USER_NUM ; index01++ )
	{
		if( !mCheckKillOtherTribe[index01] )
		{
			continue;
		}
		if( ( strcmp( mKillOtherTribeAvatarName1[index01], tAvatarName1 ) == 0 ) && ( strcmp( mKillOtherTribeAvatarName2[index01], tAvatarName2 ) == 0 ) )
		{
			if( ( tTickCount - mKillOtherTribeTime[index01] ) < 1000 )
			{
				return 1;
			}
			else
			{
				mKillOtherTribeTime[index01] = tTickCount;
				return 0;
			}
		}
	}
	for( index01 = 0 ; index01 < MAX_PLAY_USER_NUM ; index01++ )
	{
		if( !mCheckKillOtherTribe[index01] )
		{
			mCheckKillOtherTribe[index01] = TRUE;
			strcpy( mKillOtherTribeAvatarName1[index01], tAvatarName1 );
			strcpy( mKillOtherTribeAvatarName2[index01], tAvatarName2 );
			mKillOtherTribeTime[index01] = tTickCount;
			return 0;
		}
		if( ( tTickCount - mKillOtherTribeTime[index01] ) >= 1000)
		{
			strcpy( mKillOtherTribeAvatarName1[index01], tAvatarName1 );
			strcpy( mKillOtherTribeAvatarName2[index01], tAvatarName2 );
			mKillOtherTribeTime[index01] = tTickCount;
			return 0;
		}
	}
	return 1;
}
//CHANGE_AVATAR_NAME_FOR_ZONE
int MyGame::ChangeAvatarNameForZone(int tPlayUserIndex, char *tChangeAvatarName)
{
	int tResult;
	if( ( tPlayUserIndex < 0 ) || ( tPlayUserIndex > ( MAX_PLAY_USER_NUM - 1 ) ) || ( !mCheckValidState[tPlayUserIndex] ) || (strcmp(mAvatarInfo[tPlayUserIndex].aName, "") == 0) || (strcmp(mAvatarInfo[tPlayUserIndex].aGuildName, "") != 0 ) || ( strcmp( tChangeAvatarName, "" ) == 0 ) || ( strcmp( mAvatarInfo[tPlayUserIndex].aName, tChangeAvatarName) == 0 ) )
	{
		__LogMgr()->Log("!fail name:%s, guild:%s\n", mAvatarInfo[tPlayUserIndex].aName, mAvatarInfo[tPlayUserIndex].aGuildName);
		return 1;
	}
	if(!CheckNameString(tChangeAvatarName)){
		return 2;
	}
	TRIBE_INFO tTribeInfo;
	if(!mDB.DB_PROCESS_10(&tTribeInfo)){
		return 3;
	}
	if(0 != ReturnTribeRole(&tTribeInfo, mAvatarInfo[tPlayUserIndex].aName, mAvatarInfo[tPlayUserIndex].aTribe)){
		return 4;
	}
	mDB.DB_PROCESS_11(mID[tPlayUserIndex], mAvatarInfo[tPlayUserIndex].aName, tChangeAvatarName, &tResult);
	if(0 != tResult){
		return tResult + 4;
	}
	CopyMemory(mAvatarInfo[tPlayUserIndex].aName, tChangeAvatarName, MAX_AVATAR_NAME_LENGTH);
	return 0;
}

//CHECK_NAME_STRING
BOOL MyGame::CheckNameString( char *tString )
{
	int index01;
	WORD tUnicode;

	for( index01 = 0 ; index01 < (int) strlen( tString ) ; index01++ )
	{
		if( (BYTE) tString[index01] < 128 )
		{
			if(
				( tString[index01] == '0' ) ||
				( tString[index01] == '1' ) ||
				( tString[index01] == '2' ) ||
				( tString[index01] == '3' ) ||
				( tString[index01] == '4' ) ||
				( tString[index01] == '5' ) ||
				( tString[index01] == '6' ) ||
				( tString[index01] == '7' ) ||
				( tString[index01] == '8' ) ||
				( tString[index01] == '9' ) ||
				( tString[index01] == 'A' ) ||
				( tString[index01] == 'B' ) ||
				( tString[index01] == 'C' ) ||
				( tString[index01] == 'D' ) ||
				( tString[index01] == 'E' ) ||
				( tString[index01] == 'F' ) ||
				( tString[index01] == 'G' ) ||
				( tString[index01] == 'H' ) ||
				( tString[index01] == 'I' ) ||
				( tString[index01] == 'J' ) ||
				( tString[index01] == 'K' ) ||
				( tString[index01] == 'L' ) ||
				( tString[index01] == 'M' ) ||
				( tString[index01] == 'N' ) ||
				( tString[index01] == 'O' ) ||
				( tString[index01] == 'P' ) ||
				( tString[index01] == 'Q' ) ||
				( tString[index01] == 'R' ) ||
				( tString[index01] == 'S' ) ||
				( tString[index01] == 'T' ) ||
				( tString[index01] == 'U' ) ||
				( tString[index01] == 'V' ) ||
				( tString[index01] == 'W' ) ||
				( tString[index01] == 'X' ) ||
				( tString[index01] == 'Y' ) ||
				( tString[index01] == 'Z' ) ||
				( tString[index01] == 'a' ) ||
				( tString[index01] == 'b' ) ||
				( tString[index01] == 'c' ) ||
				( tString[index01] == 'd' ) ||
				( tString[index01] == 'e' ) ||
				( tString[index01] == 'f' ) ||
				( tString[index01] == 'g' ) ||
				( tString[index01] == 'h' ) ||
				( tString[index01] == 'i' ) ||
				( tString[index01] == 'j' ) ||
				( tString[index01] == 'k' ) ||
				( tString[index01] == 'l' ) ||
				( tString[index01] == 'm' ) ||
				( tString[index01] == 'n' ) ||
				( tString[index01] == 'o' ) ||
				( tString[index01] == 'p' ) ||
				( tString[index01] == 'q' ) ||
				( tString[index01] == 'r' ) ||
				( tString[index01] == 's' ) ||
				( tString[index01] == 't' ) ||
				( tString[index01] == 'u' ) ||
				( tString[index01] == 'v' ) ||
				( tString[index01] == 'w' ) ||
				( tString[index01] == 'x' ) ||
				( tString[index01] == 'y' ) ||
				( tString[index01] == 'z' )
				){
					continue;
				}
				return FALSE;
				}
		}
		/*else
		{
#ifdef __TK__
			index01++;
#else
			return FALSE;
#endif
		}*/
	}
#if 0
	for( index01 = 0 ; index01 < (int) strlen( tString ) ; index01++ )
	{
		if( (BYTE) tString[index01] < 128 )
		{
			continue;
		}
		index01++;
		if(mbstowcs((wchar_t *)&tUnicode, &tString[(index01 - 1)], 1) < 0 ) {
			return FALSE;
		}

		if( ( tUnicode >= 0x4E00 ) && ( tUnicode <= 0x9FFF ) )
		{
			continue;
		}
		return FALSE;
	}
	return TRUE;
#endif
//RETURN_TRIBE_ROLE
int MyGame::ReturnTribeRole( TRIBE_INFO *tTribeInfo, char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tTribe )
{
	int index01;

	if( strcmp( tAvatarName, tTribeInfo->mTribeMaster[tTribe] ) == 0 )
	{
		return 1;
	}
	for( index01 = 0 ; index01 < MAX_TRIBE_SUBMASTER_NUM ; index01++ )
	{
		if( strcmp( tAvatarName, tTribeInfo->mTribeSubMaster[tTribe][index01] ) == 0 )
		{
			return 2;
		}
	}
	return 0;
}
//Bonus100Money
int MyGame::Bonus100Money(int tPlayUserIndex){
	int tResult;
	if( ( tPlayUserIndex < 0 ) || ( tPlayUserIndex > ( MAX_PLAY_USER_NUM - 1 ) ) || ( !mCheckValidState[tPlayUserIndex] ))
	{
		return 1;
	}

	mDB.DB_PROCESS_14(mID[tPlayUserIndex], &tResult);
	if(0 != tResult){
		return 1 + tResult;
	}
	return 0;
}
//-------------------------------------------------------------------------------------------------

//PROCESS_FOR_SAVE_1
int MyGame::ProccesForFindAvatar(int PlayerUserIndex, char aName[MAX_AVATAR_NAME_LENGTH])
{
	int index01;

	for (index01 = 0; index01 < MAX_PLAY_USER_NUM; index01++)
	{
		if (!mCheckValidState[index01])
		{
			continue;
		}
		if (strcmp(mAvatarInfo[index01].aName, aName) == 0)
		{
			break;
		}
	}
	if (PlayerUserIndex == index01)
	{
		return 0;
	}
	return 1;
}
