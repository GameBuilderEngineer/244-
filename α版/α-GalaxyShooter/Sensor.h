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
class Sensor:public KnowledgeSourceBase
{
private:
	RecognitionBB* recognitionBB;			// 環境認識ブラックボード
	Camera* camera;							// カメラ
	float fieldRadius;						// フィールドの半径
	Ray ray;								// レイ

	// センサー
	void mapSensor(AgentAI* agentAI, D3DXVECTOR3 vecCameraToGaze, float radius2);
	void opponentSensor(AgentAI* agentAI, D3DXVECTOR3 vecCameraToGaze);
	void bulletSensor(AgentAI* agentAI, D3DXVECTOR3 vecCameraToGaze, float radius2);

public:
	// Method
	Sensor(Camera *camera);
	~Sensor(void);
	void initialize(void) override;			// 初期化処理
	void uninitialize(void) override;		// 終了処理
	void update(AgentAI* agentAI) override;	// 更新処理
	void setBlackBoard(RecognitionBB* adr) { recognitionBB = adr; }
};
