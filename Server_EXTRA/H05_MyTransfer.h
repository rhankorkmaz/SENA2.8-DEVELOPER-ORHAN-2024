//-------------------------------------------------------------------------------------------------
//MY_TRANSFER_H
//-------------------------------------------------------------------------------------------------
#ifndef MY_TRANSFER_H
#define MY_TRANSFER_H
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_TRANSFER
//-------------------------------------------------------------------------------------------------
//MACRO
#define MAX_TRANSFER_BUFFER_SIZE									10000
//DEFINE
class MyTransfer
{

public :

	BYTE mOriginal[MAX_TRANSFER_BUFFER_SIZE];
	DWORD mOriginalSize;

	MyTransfer( void );

	BOOL Init( void );
	void Free( void );

	void B_CONNECT_OK( void );
    // @ Cost Info Download @
    void B_ZONE_FOR_EXTRA_RECV(int tVersion, const int tCashItemInfo[4][14][10][4]);
    // @
	void B_GUILD_WORK_FOR_EXTRA_RECV( int tResult, GUILD_INFO *tGuildInfo );
	void B_GET_CASH_SIZE_FOR_EXTRA_RECV( int tCashSize, int tBonusCashSize );
	void B_BUY_CASH_ITEM_FOR_EXTRA_RECV( int tResult, int tCashSize, int tBonusCashSize, int tCostSize, int tBonusCostSize );
    // @ Cost Info Download @
    void B_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_RECV( int tResult );
    void B_GET_CASH_ITEM_INFO_FOR_EXTRA_RECV( int tResult, int tVersion, const int tCashItemInfo[4][14][10][4] );
    // @
    void B_USE_PACKAGE_ITEM_FOR_EXTRA_SEND( int tResult );
	void B_BLOOD_ITEM_FOR_EXTRA_SEND(int tResult, const int mBloodItemInfo[4][50][3]);
};
//INSTANCE
extern MyTransfer mTRANSFER;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
