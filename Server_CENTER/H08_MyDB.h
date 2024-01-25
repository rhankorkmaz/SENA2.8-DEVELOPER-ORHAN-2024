//-------------------------------------------------------------------------------------------------
//MY_DB_H
//-------------------------------------------------------------------------------------------------
#ifndef MY_DB_H
#define MY_DB_H
#include <list>
#include "..\include\cts_mysql.h"

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_DB
//-------------------------------------------------------------------------------------------------
//MACRO
#define MAX_QUERY_BUFFER_SIZE										10000
//DEFINE
class MyDB
{

	private :

		char mQUERY[MAX_QUERY_BUFFER_SIZE];


		CMySQL mDB01;
		CMySQL mDB02;

		BOOL RECONNECT_TO_DATABASE01( void );
		BOOL RECONNECT_TO_DATABASE02( void );

	public :

		/*
		int m_rank_kill_size;
		int m_rank_level_size;
		*/
		list<rank_kill_t> list_rank_kill;
		list<rank_level_t> list_rank_level;


		MyDB( void );

		BOOL Init( void );
		void Free( void );

		BOOL DB_PROCESS_01( WORLD_INFO *tWorldInfo );
		BOOL DB_PROCESS_02( WORLD_INFO *tWorldInfo );
		BOOL DB_PROCESS_03( int tTribe );
		BOOL DB_PROCESS_04(int zeroRank, int tSort, int tTribe );
		BOOL DB_PROCESS_05( int tDate, int tTribe );
		BOOL DB_PROCESS_06( int tSort, int tDate, int tValue );
		BOOL DB_PROCESS_07( int tSort, int tAlliance01, int tAlliance02 );
		BOOL DB_PROCESS_08( int tSort, int tValue );
		BOOL DB_PROCESS_09( int tSort, int tValue );
		BOOL DB_PROCESS_10( TRIBE_INFO *tTribeInfo );
		BOOL DB_PROCESS_11( TRIBE_INFO *tTribeInfo );
		BOOL DB_PROCESS_12(int up_check);
		BOOL DB_PROCESS_13(const char *aName, rank_info_t *rank_info);
		BOOL DB_PROCESS_14(int tTribe);
		BOOL DB_PROCESS_15(int tTribe);
		BOOL DB_PROCESS_16(int tTribe);
};
//INSTANCE
extern MyDB mDB;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
