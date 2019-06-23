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
namespace RecognitionNS
{
	enum INDEX_RECOBNITION_BLACK_BOARD
	{
		// from Sensor
		DISTANCE_TO_OPPONENT_CRISP_DATA,
		DISTANCE_TO_XXXXXXX1_CRISP_DATA,
		DISTANCE_TO_XXXXXXX2_CRISP_DATA,
		DISTANCE_TO_XXXXXXX3_CRISP_DATA,
		DISTANCE_TO_XXXXXXX4_CRISP_DATA,

		// from EnvironmentAnalysis
		DISTANCE_TO_OPPONENT_FUZZY_DATA,
		DISTANCE_TO_XXXXXXX1_FUZZY_DATA,
		DISTANCE_TO_XXXXXXX2_FUZZY_DATA,
		DISTANCE_TO_XXXXXXX3_FUZZY_DATA,
		DISTANCE_TO_XXXXXXX4_FUZZY_DATA,

		NUM_PAGE
	};
};



//*****************************************************************************
// クラス定義
//*****************************************************************************
class RecognitionBB : public BlackBoardBase {
protected:
	// Data
	float vecLength[NUM_TARGET];
	FuzzyDistance fuzzyDistance[NUM_TARGET];

public:
	// Method
	RecognitionBB(void);
	~RecognitionBB(void);
	void initialize(void) override;				// 初期化処理
	void uninitialize(void) override;			// 終了処理
};