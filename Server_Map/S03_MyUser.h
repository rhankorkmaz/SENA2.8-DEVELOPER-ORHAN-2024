//-------------------------------------------------------------------------------------------------
//MY_USER_H
//-------------------------------------------------------------------------------------------------
#ifndef MY_USER_H
#define MY_USER_H
//-------------------------------------------------------------------------------------------------
#define MAX_TRANSFER_BUFFER_SIZE									10000
//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_USER
//-------------------------------------------------------------------------------------------------
//DEFINE
class MyUser
{

public :
	// # X-Trap # {
	char mXTrapSessionBuf[XTRAP_SESSION_BUF_SIZE];
	char mXTrapStep1_SendBuf[XTRAP_STEP_1_BUF_SIZE];
	unsigned long mXTrapTick;
	// # }

	int mEPFD;
	int *mCliFd;
	int mUserIndex;

	BOOL mCheckConnectState;
	BOOL mCheckValidState;

	DWORD mConnectTime;
	SOCKET mSocket;
	char mIP[16];

	char mPacketEncryptionValue[2];

	char *mBUFFER_FOR_SEND;
	int mTotalSendSize;
	char *mBUFFER_FOR_RECV;
	int mTotalRecvSize;

	//------------------------//
	//VARIABLE_FOR_THIS_SERVER//
	//------------------------//
	time_t mCheckTime;
	BOOL mCheckTempRegister;
	int mTempRegisterTribe;
	DWORD mRegisterTime;
	int mPlayUserIndex;
	char uID[MAX_USER_ID_LENGTH];
	int uUserSort;
	int uGoodFellow;
	int UserRandomNumber;
	int uLoginPremium;
	int uLoginPremiumPCRoom;

	int DropItemSocketGmAndBos[3];
	int AutoHunt;
	int ClientKontrol;
	int GainFish;
	int WinFish;

	int uTraceState;
	char uBonus100Money;
	int uPremiumServerExpirationDate; // 프리미엄 서버(월드) 입장권 유효 기한(YYYYMMDD 형태의 정수) 설정. // @_Premium_Server_@
	AVATAR_INFO mAvatarInfo;
	int mEffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2];
	float mGeneralExperienceUpRatio;
	float mItemDropUpRatio;
	float mGeneralExperienceDownRatio;
	/** 2009. 11. 23 : 패키지 아이템개발 (wolf) */
	float mSelfPatExperienceUpRatio; // 펫경험치 상승률 조정
	/** 2009. 11. 23 : 패키지 아이템개발 (wolf) */
	int mSupportSkillTimeUpRatio;
	BOOL mCheckHealthState;
	int mHealthState;
	int AnimalOn;
	int AutoBuff1;
	DWORD AutoBuffTick;

	/** 2009. 10. 26 : DarkAttack Potion add (wolf) */
	DWORD mTickCountForDarkAttack;
	int iKindDarkAttack;
	/** 2009. 10. 26 : DarkAttack Potion add (wolf) */

	DWORD mTickCountFor01Second;
	DWORD mTickCountFor01SecondForProtect;
	DWORD mTickCountFor30Second;
	DWORD mTickCountFor01MinuteForHealth;
	DWORD mTickCountFor01Minute;

	DWORD mTickCountFor01Minute_2;
	DWORD mTickCountFor03Second;
	// # Defense Hack # {
	int mAutoCheckCount;
	DWORD mUniqueNumber;
	DWORD mAttackTickCount;
	unsigned int mSpeedTickCount;
	// # }
	int mCheckMaxAttackPacketNum;
	int mMaxAttackPacketNum;
	int mNowAttackPacketNum;
	int mAutoCheckState;
	int mAutoCheckAnswer;
	DWORD mAutoCheckTime;
	DWORD mHackCheckTime;
	int mMoveZoneResult;
	AUTH_INFO mAuthInfo;
#ifdef __LOCK__
	pthread_mutex_t m_user_lock;
	pthread_mutex_t m_user_quit_lock; // MyUser::Quit 함수 동기화 처리용.
#endif

#ifdef __GOD__
	time_t mEffectCheckTime;
	int mAttackPacketSort;
#endif
	//------------------------//
	//------------------------//
	//------------------------//

	//---------//
	//N-PROTECT//
	//---------//
#ifdef __N_PROTECT__
	CCSAuth2 *mNPROTECT;
	BOOL mCheckNPROTECT;
	int mNumberForNPROTECT;
	DWORD mTickCountForNPROTECT;
#endif
	//---------//
	//---------//
	//---------//

	int mHeartCheckCount;
	time_t mHeartCheckTime;

	bool            m_bUDPActivated; /// UDP 주소 확인 여부.
	SOCKADDR_IN     m_AddrFrom; ///< Address Info to broadcast by UDP.
	int             m_iTryCountForAuth;
#ifndef __ORG__
	bool            m_bUDPArrivedAtClient;
#endif

	MOVE_ITEM_INFO mMoveItemInfo; // 이동서 사용 정보.


	int aPackSilverDate;
	int aPackGoldDate;
	int aPackDiamondDate;
	int aPackSilverDateMobile;
	int aPackGoldDateMobile;
	int aPackDiamondDateMobile;


	DWORD mSendOriginalSize;
	BYTE mSendOriginal[MAX_TRANSFER_BUFFER_SIZE];
	DWORD mSendOriginalSize2;
	BYTE mSendOriginal2[MAX_TRANSFER_BUFFER_SIZE];
	DWORD mSendOriginalSize_C;
	BYTE mSendOriginal_C[MAX_TRANSFER_BUFFER_SIZE];
	DWORD mSendOriginalSize_R;
	BYTE mSendOriginal_R[MAX_TRANSFER_BUFFER_SIZE];



	MyUser( void );

	BOOL Init( int tUserIndex, int tSendBufferSize, int tRecvBufferSize );
	void Free( void );

	void Send( BOOL tCheckValidBuffer, char *tBuffer, int tBufferSize, bool bUDPSend = false);

	void Quit(const char *tFileName = __FILE__, const char *tFuncName = NULL , int tLine = __LINE__);



	//@{ auto quize
	enum { TEMP_BUFF_SIZE=10, };
	enum { RST_OK, RST_WRONG_ANSWER_0, RST_WRONG_ANSWER_1, RST_TIME_OVER, };
	BOOL		m_bIsBonusRecv;
	BOOL		m_bIsSend_Question;			
	char		m_tSphinx_Question[ TEMP_BUFF_SIZE ];
	DWORD		m_dSend_Time;
	int			m_iWrong_Count;
	inline void Set_BonusRecv( BOOL bIsCheck )
	{
		m_bIsBonusRecv = bIsCheck;
	}
	inline BOOL Get_BonusRecv( void )
	{
		return m_bIsBonusRecv;
	}
	inline void Set_Send_Question( BOOL bisSend )
	{
		m_bIsSend_Question = bisSend;
	}
	inline BOOL IsSend_Question( void )
	{
		return m_bIsSend_Question;
	}
	inline void Set_Sphinx_Question( char const * tStr )
	{
		memcpy( m_tSphinx_Question, tStr, 5 );
	}
	inline char* Get_Sphinx_Question( void )
	{
		return m_tSphinx_Question;
	}
	inline void Set_Send_Question_Time( DWORD dTime )
	{
		m_dSend_Time = dTime;
	}
	BOOL IsSend_TimeOver( void );
	BOOL IsWrong_CountOver( void );
	//@}

	// @ Cost Info Download @
	bool mIsValidCashItemInfo;
	// @

	/** 2009. 11. 23 : 패키지 아이템 개발 (wolf) */
	bool bUsePackItem;
	/** 2009. 11. 23 : 패키지 아이템 개발 (wolf) */

	bool IsValidSkillNumber(int skillNumber);
	int GetMaxSkillGradeNum(int skillNumber);
};
//INSTANCE
extern MyUser *mUSER;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
