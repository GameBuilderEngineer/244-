//-----------------------------------------------------------------------------
// �G�[�W�F���gAI���� [AgentAI.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/15
//-----------------------------------------------------------------------------
#include "AgentAI.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int AgentAI::numAgent = 0;


//=============================================================================
// �R���X�g���N�^
//=============================================================================
AgentAI::AgentAI(void)
{
	aiID = numAgent++;

	// ���W���[���ƃu���b�N�{�[�h����
	arbiter = new Arbiter;
	sensor = new Sensor;
	environmentAnalysis = new EnvironmentAnalysis;
	pathPlanning = new PathPlanning;
	decisionMaking = new DecisionMaking;
	motionGeneration = new MotionGeneration;
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
    setBlackBoard(BB::ENVIRONMENT_RECOGNITION, recognitionBB);
	setBlackBoard(BB::BODY, bodyBB);
	setBlackBoard(BB::MEMORY, memoryBB);
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
AgentAI::~AgentAI(void)
{
	// ���W���[���ƃu���b�N�{�[�h�j��
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
