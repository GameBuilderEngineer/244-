//-----------------------------------------------------------------------------
// 環境認識ブラックボード処理 [BlackBoardRecognition.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/19
//-----------------------------------------------------------------------------
#include "BlackBoardRecognition.h"

//=============================================================================
// コンストラクタ
//=============================================================================
RecognitionBB::RecognitionBB(void)
{
	// インデックスに変数を登録
	index = new void*[Page::NUM_PAGE_RECOGNITION_BB];
	index[Page::DISTANCE_TO_OPPONENT_CRISP_DATA] = &vecLength[0];
	index[Page::DISTANCE_TO_XXXXXXX1_CRISP_DATA] = &vecLength[1];
	index[Page::DISTANCE_TO_XXXXXXX2_CRISP_DATA] = &vecLength[2];
	index[Page::DISTANCE_TO_XXXXXXX3_CRISP_DATA] = &vecLength[3];
	index[Page::DISTANCE_TO_XXXXXXX4_CRISP_DATA] = &vecLength[4];
	index[Page::DISTANCE_TO_OPPONENT_FUZZY_DATA] = &fuzzyDistance[0];
	index[Page::DISTANCE_TO_XXXXXXX1_FUZZY_DATA] = &fuzzyDistance[1];
	index[Page::DISTANCE_TO_XXXXXXX2_FUZZY_DATA] = &fuzzyDistance[2];
	index[Page::DISTANCE_TO_XXXXXXX3_FUZZY_DATA] = &fuzzyDistance[3];

	// 工事中
}


//=============================================================================
// デストラクタ
//=============================================================================
RecognitionBB::~RecognitionBB(void)
{
	delete[] index;
}


//=============================================================================
// 初期化処理
//=============================================================================
void RecognitionBB::initialize(void)
{

}


//=============================================================================
// 終了処理
//=============================================================================
void RecognitionBB::uninitialize(void)
{

}


//=============================================================================
// モジュールにアクセス許可を返す
//=============================================================================
bool RecognitionBB::getAccessPermission(int tag)
{
	switch (tag)
	{
	case Module::SENSOR:
	case Module::ENVIRONMENT_ANSLYSIS:
	case Module::PATH_PLANNING:
	case Module::DECISION_MAKING:
		return true;

	default:
		return false;
	}
}