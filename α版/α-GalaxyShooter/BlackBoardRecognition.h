//-----------------------------------------------------------------------------
// 環境認識ブラックボード処理 [BlackBoardRecognition.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/19
//-----------------------------------------------------------------------------
#pragma once
#include "AICommon.h"
#include "BlackBoardBase.h"
#include "Fuzzy.h"

//*****************************************************************************
// 定数定義
//*****************************************************************************
namespace Page
{
	enum PAGE
	{
		// from Sensor
		DISTANCE_TO_OPPONENT_CRISP_DATA,
		DISTANCE_TO_XXXXXXX1_CRISP_DATA,
		DISTANCE_TO_XXXXXXX2_CRISP_DATA,
		DISTANCE_TO_XXXXXXX3_CRISP_DATA,
		DISTANCE_TO_XXXXXXX4_CRISP_DATA,
		_DUMMY_COUNT_DISTANCE_CRISP_DATA,

		// from EnvironmentAnalysis
		DISTANCE_TO_OPPONENT_FUZZY_DATA,
		DISTANCE_TO_XXXXXXX1_FUZZY_DATA,
		DISTANCE_TO_XXXXXXX2_FUZZY_DATA,
		DISTANCE_TO_XXXXXXX3_FUZZY_DATA,
		_DUMMY_COUNT_DISTANCE_FUZZY_DATA,
	};

	// 各種類ごとのページ数（ページが増えたらここに追加する）
	const static int NUM_DISTANCE_CRISP_DATA = _DUMMY_COUNT_DISTANCE_CRISP_DATA;
	const static int NUM_DISTANCE_FUZZY_DATA = _DUMMY_COUNT_DISTANCE_FUZZY_DATA - _DUMMY_COUNT_DISTANCE_CRISP_DATA + 1;

	// ページ総数（ページが増えたらここに追加する）
	const static int NUM_PAGE_RECOGNITION_BB = NUM_DISTANCE_CRISP_DATA + NUM_DISTANCE_FUZZY_DATA;
};


//*****************************************************************************
// クラス定義
//*****************************************************************************
class RecognitionBB : public BlackBoardBase
{
protected:
	// Data
	float vecLength[Target::NUM_MAX];
	FuzzyDistance fuzzyDistance[Target::NUM_MAX];

public:
	// Method
	RecognitionBB(void);
	~RecognitionBB(void);
	void initialize(void) override;				// 初期化処理
	void uninitialize(void) override;			// 終了処理
	bool getAccessPermission(int tag) override;	// モジュールにアクセス許可を返す
};