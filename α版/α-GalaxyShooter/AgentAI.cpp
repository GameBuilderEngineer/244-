//-----------------------------------------------------------------------------
// �G�[�W�F���gAI���� [AgentAI.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/15
//-----------------------------------------------------------------------------
#include "AgentAI.h"

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
int AgentAI::numAgent = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
AgentAI::AgentAI(void)
{
	aiID = numAgent++;

	// �A�[�r�^�[
	arbiter = new Arbiter;

	// ���W���[��
	sensor = new Sensor;
	environmentAnalysis = new EnvironmentAnalysis;
	pathPlanning = new PathPlanning;
	decisionMaking = new DecisionMaking;
	motionGeneration = new MotionGeneration;

	// �u���b�N�{�[�h
	recognitionBB = new RecognitionBB;
	bodyBB = new BodyBB;
	memoryBB = new MemoryBB;

	// �A�[�r�^�[�Ƀ��W���[����ڑ�
	arbiter->setModule(Module::SENSOR, sensor);
	arbiter->setModule(Module::ENVIRONMENT_ANSLYSIS, environmentAnalysis);
	arbiter->setModule(Module::PATH_PLANNING, pathPlanning);
	arbiter->setModule(Module::DECISION_MAKING, decisionMaking);
	arbiter->setModule(Module::MOTION_GENERATION, motionGeneration);

	// ���W���[���Ƀu���b�N�{�[�h��ڑ�
	sensor->setBlackBoard(recognitionBB);
	environmentAnalysis->setBlackBoard(recognitionBB);
	pathPlanning->setBlackBoard(recognitionBB, memoryBB);
	decisionMaking->setBlackBoard(recognitionBB, memoryBB, bodyBB);
	motionGeneration->setBlackBoard(memoryBB, bodyBB);
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
AgentAI::~AgentAI(void)
{
	// ���W���[���ƃu���b�N�{�[�h�j��
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
// ����������
//=============================================================================
void AgentAI::initialize(LPDIRECT3DDEVICE9 device, StaticMeshLoader* staticMeshLoader, TextureLoader* textureLoader, ShaderLoader* shaderLoader)
{
	sensor->initialize();
	environmentAnalysis->initialize();
	decisionMaking->initialize();
	pathPlanning->initialize();
	motionGeneration->initialize();
	Player::initialize(playerNS::PLAYER2,device, staticMeshLoader, textureLoader, shaderLoader);
}


//=============================================================================
// �I������
//=============================================================================
void AgentAI::uninitialize(void)
{

}


//=============================================================================
// �X�V����
//=============================================================================
void AgentAI::update(Sound* _sound, float frameTime)
{
#if 0
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
#endif

	Player::update(_sound, frameTime);
}
