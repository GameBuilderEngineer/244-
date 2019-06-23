//-----------------------------------------------------------------------------
// エージェントAI処理 [AgentAI.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/15
//-----------------------------------------------------------------------------
#include "AgentAI.h"

//=============================================================================
// コンストラクタ
//=============================================================================
AgentAI::AgentAI(void)
{
	arbiter = new Arbiter;
	sensor = new Sensor;
	environmentAnalysis = new EnvironmentAnalysis;
	pathPlanning = new PathPlanning;
	decisionMaking = new DecisionMaking;
	motionGeneration = new MotionGeneration;
	recognitionBB = new RecognitionBB;
	bodyBB = new BodyBB;
	memoryBB = new MemoryBB;

	// アービターにモジュールを接続
	arbiter->setModule(SENSOR, sensor);
	arbiter->setModule(ENVIRONMENT_ANSLYSIS, environmentAnalysis);
	arbiter->setModule(PATH_PLANNING, pathPlanning);
	arbiter->setModule(DECISION_MAKING, decisionMaking);
	arbiter->setModule(MOTION_GENERATION, motionGeneration);

	// モジュールにブラックボードを接続
	// センサー　環境認識
	// 環境解析　環境認識
	// 経路探索　環境認識　記憶
	// 意思決定　環境認識　記憶
	// 運動生成　身体状態　記憶
}


//=============================================================================
// デストラクタ
//=============================================================================
AgentAI::~AgentAI(void)
{

}


//=============================================================================
// 初期化処理
//=============================================================================
void AgentAI::initialize(void)
{

}


//=============================================================================
// 終了処理
//=============================================================================
void AgentAI::uninitialize(void)
{

}


//=============================================================================
// 実行
//=============================================================================
void AgentAI::run(void)
{
	arbiter->update();

	if (sensor->getUpdatePermission())
	{
		sensor->update();
	}

	if (environmentAnalysis->getUpdatePermission())
	{
		environmentAnalysis->update();
	}

	if (pathPlanning->getUpdatePermission())
	{
		pathPlanning->update();
	}

	if (decisionMaking->getUpdatePermission())
	{
		decisionMaking->update();
	}

	if (motionGeneration->getUpdatePermission())
	{
		motionGeneration->update();
	}
}
