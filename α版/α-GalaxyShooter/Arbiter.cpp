//-----------------------------------------------------------------------------
// アービター処理 [Arbiter.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/15
//-----------------------------------------------------------------------------
#include "Arbiter.h"

//=============================================================================
// コンストラクタ
//=============================================================================
Arbiter::Arbiter(void)
{

}


//=============================================================================
// デストラクタ
//=============================================================================
Arbiter::~Arbiter(void)
{

}


//=============================================================================
// 初期化処理
//=============================================================================
void Arbiter::initialize(void)
{
	sensorInterval = 0;
	sensoryTransmissionTime = 0;
	pathPanningInterval = 0;
	decisionMakingInterval = 0;

	frameCount = 0;
	sensorLastFrame = 0;
	pathPlanningLastFrame = 0;
	decisionMakingLastFrame = 0;
	motionGenerationLastFrame = 0;

	// 全てのモジュールの更新を有効にする
	for (int i = 0; i < NUM_KNOWLEDGE_SOURCE; i++)
	{
		module[i]->setUpdatePermission(true);
	}
}


//=============================================================================
// 終了処理
//=============================================================================
void Arbiter::uninitialize(void)
{

}


//=============================================================================
// 更新処理
//=============================================================================
void Arbiter::update(void)
{
	// 各モジュールの更新を管理している

	frameCount++;

	// センサー
	if (frameCount - sensorLastFrame > sensorInterval)
	{
		sensorLastFrame = frameCount;
		module[SENSOR]->setUpdatePermission(true);
	}

	// 環境解析
	if (frameCount- sensorLastFrame > sensoryTransmissionTime)
	{
		module[ENVIRONMENT_ANSLYSIS]->setUpdatePermission(true);
	}

	// 経路探索
	if (frameCount - pathPlanningLastFrame > pathPanningInterval)
	{
		pathPlanningLastFrame = frameCount;
		module[PATH_PLANNING]->setUpdatePermission(true);
	}

	// 意思決定
	if (frameCount - decisionMakingLastFrame > decisionMakingInterval)
	{
		decisionMakingLastFrame = frameCount;
		module[DECISION_MAKING]->setUpdatePermission(true);
	}

	// 運動生成
	if (frameCount - motionGenerationLastFrame > motionInterval)
	{
		decisionMakingLastFrame = frameCount;
		module[MOTION_GENERATION]->setUpdatePermission(true);
	}
}
