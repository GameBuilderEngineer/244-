//-----------------------------------------------------------------------------
// 環境認識ブラックボード処理 [BlackBoardRecognition.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/19
//-----------------------------------------------------------------------------
#pragma once
#include "BlackBoardBase.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************

class RecognitionBB : public BlackBoardBase
{
private:
	// Data
	float distanceOpponent;

public:
	// Accessor
	float getDistanceOpponent(void) { return distanceOpponent; }
	void setDistanceOpponent(float value) { distanceOpponent = value; }

	// Method
	RecognitionBB(void);
	~RecognitionBB(void);
	void initialize(void) override;				// 初期化処理
	void uninitialize(void) override;			// 終了処理
};