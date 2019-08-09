//-----------------------------------------------------------------------------
// エージェントAI処理 [AgentAI.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/15
//-----------------------------------------------------------------------------
#include "AgentAI.h"

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
int AgentAI::numAgent = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
AgentAI::AgentAI(void)
{
	aiID = numAgent++;

	// アービター
	arbiter = new Arbiter;

	// モジュール
	sensor = new Sensor;
	environmentAnalysis = new EnvironmentAnalysis;
	pathPlanning = new PathPlanning;
	decisionMaking = new DecisionMaking;
	motionGeneration = new MotionGeneration;

	// ブラックボード
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
	sensor->setBlackBoard(recognitionBB);
	environmentAnalysis->setBlackBoard(recognitionBB);
	pathPlanning->setBlackBoard(recognitionBB, memoryBB);
	decisionMaking->setBlackBoard(recognitionBB, memoryBB, bodyBB);
	motionGeneration->setBlackBoard(memoryBB, bodyBB);
}


//=============================================================================
// デストラクタ
//=============================================================================
AgentAI::~AgentAI(void)
{
	// モジュールとブラックボード破棄
	SAFE_DELETE(arbiter)
	SAFE_DELETE(sensor)
	SAFE_DELETE(environmentAnalysis)
	SAFE_DELETE(pathPlanning)
	SAFE_DELETE(decisionMaking)
	SAFE_DELETE(motionGeneration)
	SAFE_DELETE(recognitionBB)
	SAFE_DELETE(bodyBB)
	SAFE_DELETE(memoryBB)

	--numAgent;
}


//=============================================================================
// 初期化処理
//=============================================================================
void AgentAI::initialize(int playerType, 
	PDIRECT3DDEVICE9 device,
	StaticMeshLoader* staticMeshLoader,
	TextureLoader* textureLoader,
	ShaderLoader* shaderLoader)
{
	sensor->initialize();
	environmentAnalysis->initialize();
	decisionMaking->initialize();
	pathPlanning->initialize();
	motionGeneration->initialize();
	Player::initialize(playerType, device, staticMeshLoader, textureLoader, shaderLoader);
}


//=============================================================================
// 終了処理
//=============================================================================
void AgentAI::uninitialize(void)
{

}


//=============================================================================
// 更新処理
//=============================================================================
void AgentAI::update(float frameTime)
{
	arbiter->update();

	if (sensor->getUpdatePermission())
	{
		sensor->update(this);
	}

	if (environmentAnalysis->getUpdatePermission())
	{
		environmentAnalysis->update(this);
	}

	if (pathPlanning->getUpdatePermission())
	{
		pathPlanning->update(this);
	}

	if (decisionMaking->getUpdatePermission())
	{
		decisionMaking->update(this);
	}

	if (motionGeneration->getUpdatePermission())
	{
		motionGeneration->update(this);
	}

	Player::update(frameTime);
}
