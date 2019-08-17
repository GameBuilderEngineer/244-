//-----------------------------------------------------------------------------
// センサー処理 [Sensor.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/15
//-----------------------------------------------------------------------------
#pragma once
#include "KnowledgeSourceBase.h"
#include "Ray.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Sensor:public KnowledgeSourceBase {
private:
	RecognitionBB* recognitionBB;			// 環境認識ブラックボード
	D3DXVECTOR3* cameraPosition;			// カメラの位置
	float cameraFieldOfView;				// カメラの視野角情報
	float fieldRadius;						// フィールドの半径
	Ray ray;								// レイ

public:
	// Method
	Sensor(D3DXVECTOR3* _cameraPosition, float _cameraFieldOfView);
	~Sensor(void);
	void initialize(void) override;			// 初期化処理
	void uninitialize(void) override;		// 終了処理
	void update(AgentAI* agentAI) override;	// 更新処理
	void setBlackBoard(RecognitionBB* adr) { recognitionBB = adr; }

	D3DXVECTOR3* getCameraPosition(void) { return cameraPosition; }
};
