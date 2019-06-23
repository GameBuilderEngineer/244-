//-----------------------------------------------------------------------------
// �G�[�W�F���gAI���� [AgentAI.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/15
//-----------------------------------------------------------------------------
#include "AgentAI.h"

//=============================================================================
// �R���X�g���N�^
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

	// �A�[�r�^�[�Ƀ��W���[����ڑ�
	arbiter->setModule(SENSOR, sensor);
	arbiter->setModule(ENVIRONMENT_ANSLYSIS, environmentAnalysis);
	arbiter->setModule(PATH_PLANNING, pathPlanning);
	arbiter->setModule(DECISION_MAKING, decisionMaking);
	arbiter->setModule(MOTION_GENERATION, motionGeneration);

	// ���W���[���Ƀu���b�N�{�[�h��ڑ�
	// �Z���T�[�@���F��
	// ����́@���F��
	// �o�H�T���@���F���@�L��
	// �ӎv����@���F���@�L��
	// �^�������@�g�̏�ԁ@�L��
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
AgentAI::~AgentAI(void)
{

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
