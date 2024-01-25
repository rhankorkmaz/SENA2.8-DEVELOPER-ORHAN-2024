//-------------------------------------------------------------------------------------------------
//MY_WORLD_H
//-------------------------------------------------------------------------------------------------
#ifndef MY_WORLD_H
#define MY_WORLD_H
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_WORLD_FOR_GXD
//-------------------------------------------------------------------------------------------------
//STRUCTURE-[WORLDVERTEX_FOR_GXD]
typedef struct
{
	float mV[3];
	float mN[3];
	float mT1[2];
	float mT2[2];
}
WORLDVERTEX_FOR_GXD;
//STRUCTURE-[WORLDTRIS_FOR_GXD]
typedef struct
{
	int mTextureIndex;
	WORLDVERTEX_FOR_GXD mVertex[3];
	float mPlaneInfo[4];
	float mSphereInfo[4];
}
WORLDTRIS_FOR_GXD;
//STRUCTURE-[QUADTREENODE_FOR_GXD]
typedef struct
{
	float mBoxMin[3];
	float mBoxMax[3];
	int mTrisNum;
	int *mTrisIndex;
	int mChildNodeIndex[4];
}
QUADTREENODE_FOR_GXD;
//DEFINE
class WORLD_FOR_GXD
{

private :

	BOOL GetYCoordWithTris( int tTrisIndex, float x, float z, float *y );
	BOOL CheckPointInTris( int tTrisIndex, float tPoint[3] );
	BOOL CheckPointInTrisWithoutYCoord( int tTrisIndex, float tPoint[3] );
	BOOL CheckPointInWorldWithoutYCoord( float tPoint[3] );

public :

	BOOL mCheckValidState;
	int mWorldTrisNum;
	WORLDTRIS_FOR_GXD *mWorldTris;
	int mTotalQuadtreeNodeNum;
	int mMaxQuadtreeNodeLeafNum;
	QUADTREENODE_FOR_GXD *mQuadtree;

	WORLD_FOR_GXD( void );

	void Init( void );
	void Free( void );

	BOOL LoadWM( void );

	BOOL GetYCoord( float x, float z, float *y, BOOL tCheckExistPostYCoord, float tPostYCoord, BOOL tCheckTwoSide, BOOL tCheckOnlyOne );
	void Path( float tSCoord[3], float tECoord[3], float tSpeed, float tPostTime, float tResult[3] );
	BOOL PathForMonsterAttack( float tSCoord[3], float tECoord[3], float tSpeed, float tPostTime, float tLimitCoord[3], float tLimitLength, float tResult[3] );
	BOOL Move( float tSCoord[3], float tECoord[3], float tSpeed, float tPostTime, BOOL *tCheckArrival );

};
//INSTANCE
extern WORLD_FOR_GXD mWORLD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
