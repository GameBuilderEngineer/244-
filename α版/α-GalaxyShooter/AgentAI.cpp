//-----------------------------------------------------------------------------
// エージェントAI処理 [AgentAI.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/15
//-----------------------------------------------------------------------------
#include "AgentAI.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
int AgentAI::numAgent = 0;


//=============================================================================
// コンストラクタ
//=============================================================================
AgentAI::AgentAI(void)
{
	aiID = numAgent++;

	// モジュールとブラックボード生成
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
	arbiter->setModule(Module::SENSOR, sensor);
	arbiter->setModule(Module::ENVIRONMENT_ANSLYSIS, environmentAnalysis);
	arbiter->setModule(Module::PATH_PLANNING, pathPlanning);
	arbiter->setModule(Module::DECISION_MAKING, decisionMaking);
	arbiter->setModule(Module::MOTION_GENERATION, motionGeneration);

	// モジュールにブラックボードを接続
    setBlackBoard(BB::ENVIRONMENT_RECOGNITION, recognitionBB);
	setBlackBoard(BB::BODY, bodyBB);
	setBlackBoard(BB::MEMORY, memoryBB);
}


//=============================================================================
// デストラクタ
//=============================================================================
AgentAI::~AgentAI(void)
{
	// モジュールとブラックボード破棄
	delete arbiter;
	delete sensor;
	delete environmentAnalysis;
	delete pathPlanning;
	delete decisionMaking;
	delete motionGeneration;
	delete recognitionBB;
	delete bodyBB;
	delete memoryBB;

	--numAgent;
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
