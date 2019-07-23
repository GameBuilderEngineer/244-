//-----------------------------------------------------------------------------
// アービター処理 [Arbiter.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/15
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "AICommon.h"
#include "KnowledgeSourceBase.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Arbiter{
private:
	// Data
	int sensorInterval;				// センサーの更新間隔
	int sensoryTransmissionTime;	// センサ→環境認識の伝達速度（感覚神経の伝達速度を表現）
	int pathPanningInterval;		// 経路探索の更新間隔
	int decisionMakingInterval;		// 意思決定の更新間隔
	int motionInterval;				// 運動生成の更新間隔

	DWORD frameCount;				// AI稼働後のフレーム数をカウント
	DWORD sensorLastFrame;			// センサーを最後に更新したのが何フレーム目か記録
	DWORD pathPlanningLastFrame;	// 経路探索を最後に更新したのが何フレーム目か記録
	DWORD decisionMakingLastFrame;	// 意思決定を最後に更新したのが何フレーム目か記録
	DWORD motionGenerationLastFrame;// 運動生成を最後に更新したのが何フレーム目か記録

	KnowledgeSourceBase *module[Module::NUM_MAX];// 各モジュールのアドレス

public:
	// Method
	Arbiter(void);
	~Arbiter(void);
	void initialize(void);			// 初期化処理
	void uninitialize(void);		// 終了処理
	void update(void);				// 更新処理
	void setModule(int number, KnowledgeSourceBase *adr) { module[number] = adr; }// モジュールを接続
};