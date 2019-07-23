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

	// �X�e�[�g�}�V����ڑ�
	decisionMaking->setStateMachine(StateMachine::getInstance());

	// �r�w�C�r�A�c���[��ڑ�
	decisionMaking->setBehaviorTree(BehaviorTree::getInstance());
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
void AgentAI::initialize(void)
{

}


//=============================================================================
// �I������
//=============================================================================
void AgentAI::uninitialize(void)
{

}


//=============================================================================
// ���s
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
