//-----------------------------------------------------------------------------
// センサー処理 [Sensor.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/15
//-----------------------------------------------------------------------------
#pragma once
#include "KnowledgeSourceBase.h"
#include "BlackBoardRecognition.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Sensor:public KnowledgeSourceBase {
private:
	RecognitionBB* recognitionBB;		// 環境認識ブラックボード

public:
	// Method
	Sensor(void);
	~Sensor(void);
	void initialize(void) override;		// 初期化処理
	void uninitialize(void) override;	// 終了処理
	void update(void) override;			// 更新処理
	void setBlackBoard(RecognitionBB* adr) { recognitionBB = adr; }
};
