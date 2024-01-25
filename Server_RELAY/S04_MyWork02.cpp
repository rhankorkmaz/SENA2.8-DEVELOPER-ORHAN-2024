//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "Shengming.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//WORKER_FUNCTION
//-------------------------------------------------------------------------------------------------
//INSTANCE
WORKER_FUNCTION W_FUNCTION[256];
//W_ZONE_FOR_RELAY_SEND
void W_ZONE_FOR_RELAY_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 0 )
	{
		mUSER[tUserIndex].Quit( 4001 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tZoneNumber;
	CopyMemory( &tZoneNumber, &tPacket[1], 4 );

	if( ( tZoneNumber < MIN_VALID_ZONE_NUMBER ) || ( tZoneNumber > MAX_VALID_ZONE_NUMBER ) )
	{
		mUSER[tUserIndex].Quit( 4002 );
		return;
	}

	int index01;

	for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
	{
		if( ( mUSER[index01].mCheckServerType == 2 ) && ( mUSER[index01].mZoneServerNumber == tZoneNumber ) )
		{
			mUSER[index01].Quit( 4003 );
		}
	}
	mUSER[tUserIndex].mCheckServerType = 2;
	mUSER[tUserIndex].mZoneServerNumber = tZoneNumber;
	mTRANSFER.B_ZONE_FOR_RELAY_RECV();
	mUSER[tUserIndex].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
}
//W_ZONE_OK_FOR_RELAY_SEND
void W_ZONE_OK_FOR_RELAY_SEND( int tUserIndex )
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 2 )
	{
		mUSER[tUserIndex].Quit( 4004 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();
}
//W_DEMAND_BROADCAST_DATA
void W_DEMAND_BROADCAST_DATA( int tUserIndex )
{
	
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[0];
	if( mUSER[tUserIndex].mCheckServerType != 2 )
	{
		mUSER[tUserIndex].Quit( 4005 );
		return;
	}
	mUSER[tUserIndex].mUsedTime = GetTickCount();

	int tSort = 0;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];
	CopyMemory( &tSort, &tPacket[1], 4 );
	CopyMemory( &tData[0], &tPacket[5], MAX_BROADCAST_DATA_SIZE );

	int index01 = 0;

	mTRANSFER.B_BROADCAST_DATA( tSort, &tData[0] );
	for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
	{
		if( mUSER[index01].mCheckServerType == 2 )
		{
			mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
		}
	}
	if(tSort == 102)
	mGAMELOG.SendToLogServer(31);
	char tPartyName[MAX_PARTY_NAME_LENGTH];
	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	party_list tParty_list;
	map<string, party_list>::iterator iter;

	::memset(tPartyName, 0, MAX_PARTY_NAME_LENGTH);
	::memset(tAvatarName, 0, MAX_AVATAR_NAME_LENGTH);
	::memset(&tParty_list, 0, sizeof(party_list));


	switch(tSort)
	{
		case 104://PARTY_JOIN
			CopyMemory(tPartyName, tData, MAX_PARTY_NAME_LENGTH);
			CopyMemory(tAvatarName, &tData[MAX_PARTY_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);

			iter = mWORK.map_party_list.find(tPartyName);

			if(mWORK.map_party_list.end() == iter)
			{
				CopyMemory(tParty_list.mPartyAvatarName[0], tPartyName, MAX_PARTY_NAME_LENGTH);
				CopyMemory(tParty_list.mPartyAvatarName[1], tAvatarName, MAX_AVATAR_NAME_LENGTH);
				mWORK.map_party_list.insert(make_pair(tPartyName, tParty_list));

				CopyMemory(&tData[MAX_PARTY_NAME_LENGTH], tParty_list.mPartyAvatarName[0], MAX_AVATAR_NAME_LENGTH);
				CopyMemory(&tData[MAX_PARTY_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH],tParty_list.mPartyAvatarName[1], MAX_AVATAR_NAME_LENGTH);
				CopyMemory(&tData[( MAX_PARTY_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH )],tParty_list.mPartyAvatarName[2],MAX_AVATAR_NAME_LENGTH );
				CopyMemory(&tData[( MAX_PARTY_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH )], tParty_list.mPartyAvatarName[3],MAX_AVATAR_NAME_LENGTH );
				CopyMemory(&tData[( MAX_PARTY_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH )], tParty_list.mPartyAvatarName[4],MAX_AVATAR_NAME_LENGTH );
			}
			else
			{
				for (index01 = 0; index01 < 5; ++index01)
				{
					if(0 != strcmp(iter->second.mPartyAvatarName[index01], ""))
						continue;

					CopyMemory(iter->second.mPartyAvatarName[index01], tAvatarName, MAX_AVATAR_NAME_LENGTH);
					break;
				}
				for (index01 = 0; index01 < 5; ++index01)
				{
					CopyMemory(&tData[MAX_PARTY_NAME_LENGTH + (index01 * MAX_AVATAR_NAME_LENGTH)],
						iter->second.mPartyAvatarName[index01], MAX_AVATAR_NAME_LENGTH);
				}
			}
			tSort = 108;
			mTRANSFER.B_BROADCAST_DATA( tSort, &tData[0] );
			for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
			{
				if( mUSER[index01].mCheckServerType == 2 )
				{
					mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
				}
			}
			break;
		case 106://PARTY_LEAVE
		case 107://PARTY_EXILE
			CopyMemory(tPartyName, tData, MAX_PARTY_NAME_LENGTH);
			CopyMemory(tAvatarName, &tData[MAX_PARTY_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
			iter = mWORK.map_party_list.find(tPartyName);
			if(mWORK.map_party_list.end() != iter)
			{
				for (index01 = 0; index01 < 5; ++index01)
				{
					if(0 != ::strcmp(iter->second.mPartyAvatarName[index01], tAvatarName))
					{
						continue;
					}

					strncpy(iter->second.mPartyAvatarName[index01], "", MAX_AVATAR_NAME_LENGTH);

					for(; index01 < 4; ++index01)
					{
						strncpy(iter->second.mPartyAvatarName[index01], iter->second.mPartyAvatarName[index01 + 1], MAX_AVATAR_NAME_LENGTH);
						strncpy(iter->second.mPartyAvatarName[index01 + 1], "", MAX_AVATAR_NAME_LENGTH);
					}
					break;
				}
			}
			break;
		case 108://PARTY_INFO
			CopyMemory(tPartyName, tData, MAX_PARTY_NAME_LENGTH);
			CopyMemory(tAvatarName, &tData[MAX_PARTY_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);

			iter = mWORK.map_party_list.find(tPartyName);

			if(mWORK.map_party_list.end() != iter)
			{
				for (index01 = 0; index01 < 5; ++index01)
				{
					CopyMemory(&tData[MAX_PARTY_NAME_LENGTH + (index01 * MAX_AVATAR_NAME_LENGTH)],
						iter->second.mPartyAvatarName[index01], MAX_AVATAR_NAME_LENGTH);
				}
				tSort = 108;
				mTRANSFER.B_BROADCAST_DATA( tSort, &tData[0] );
				for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
				{
					if( mUSER[index01].mCheckServerType == 2 )
					{
						mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
					}
				}
			}
			else
			{
				iter = mWORK.map_party_list.begin();
				while(iter != mWORK.map_party_list.end())
				{
					for(index01 = 0; index01 < 5; ++index01)
					{
						if(0 != strcmp(tAvatarName, iter->second.mPartyAvatarName[index01]))
							continue;
						tSort = 109;
						CopyMemory(&tData[MAX_PARTY_NAME_LENGTH], iter->second.mPartyAvatarName[0], MAX_AVATAR_NAME_LENGTH);
						mTRANSFER.B_BROADCAST_DATA( tSort, &tData[0] );
						for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
						{
							if( mUSER[index01].mCheckServerType == 2 )
							{
								mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
							}
						}
						return;
					}
					iter++;
				}
				tSort = 109;
				CopyMemory(&tData[MAX_PARTY_NAME_LENGTH], "", MAX_AVATAR_NAME_LENGTH);
				mTRANSFER.B_BROADCAST_DATA( tSort, &tData[0] );
				for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
				{
					if( mUSER[index01].mCheckServerType == 2 )
					{
						mUSER[index01].Send( TRUE, (char *) &mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize );
					}
				}
				return;
			}
			break;
		case 109://PARTY_BREAK
			CopyMemory(tPartyName, tData, MAX_PARTY_NAME_LENGTH);
			CopyMemory(tAvatarName, &tData[MAX_PARTY_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);

			iter = mWORK.map_party_list.find(tPartyName);

			if(mWORK.map_party_list.end() != iter){
				CopyMemory(&tParty_list, &(iter->second), sizeof(party_list));
				mWORK.map_party_list.erase(iter);

				if(0 == ::strcmp("", tAvatarName))
					return;

				for(index01 = 1; index01 < 5; ++index01){
					strncpy(tParty_list.mPartyAvatarName[index01 - 1], tParty_list.mPartyAvatarName[index01], MAX_AVATAR_NAME_LENGTH);
					strncpy(tParty_list.mPartyAvatarName[index01], "", MAX_AVATAR_NAME_LENGTH);
				}
				mWORK.map_party_list.insert(make_pair(tAvatarName, tParty_list));
			}
			break;
		default:
			break;
	}
}
//-------------------------------------------------------------------------------------------------
