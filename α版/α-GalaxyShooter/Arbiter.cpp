//-----------------------------------------------------------------------------
// �A�[�r�^�[���� [Arbiter.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/15
//-----------------------------------------------------------------------------
#include "Arbiter.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Arbiter::Arbiter(void)
{

}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
Arbiter::~Arbiter(void)
{

}


//=============================================================================
// ����������
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

	// �S�Ẵ��W���[���̍X�V��L���ɂ���
	for (int i = 0; i < NUM_KNOWLEDGE_SOURCE; i++)
	{
		module[i]->setUpdatePermission(true);
	}
}


//=============================================================================
// �I������
//=============================================================================
void Arbiter::uninitialize(void)
{

}


//=============================================================================
// �X�V����
//=============================================================================
void Arbiter::update(void)
{
	// �e���W���[���̍X�V���Ǘ����Ă���

	frameCount++;

	// �Z���T�[
	if (frameCount - sensorLastFrame > sensorInterval)
	{
		sensorLastFrame = frameCount;
		module[SENSOR]->setUpdatePermission(true);
	}

	// �����
	if (frameCount- sensorLastFrame > sensoryTransmissionTime)
	{
		module[ENVIRONMENT_ANSLYSIS]->setUpdatePermission(true);
	}

	// �o�H�T��
	if (frameCount - pathPlanningLastFrame > pathPanningInterval)
	{
		pathPlanningLastFrame = frameCount;
		module[PATH_PLANNING]->setUpdatePermission(true);
	}

	// �ӎv����
	if (frameCount - decisionMakingLastFrame > decisionMakingInterval)
	{
		decisionMakingLastFrame = frameCount;
		module[DECISION_MAKING]->setUpdatePermission(true);
	}

	// �^������
	if (frameCount - motionGenerationLastFrame > motionInterval)
	{
		decisionMakingLastFrame = frameCount;
		module[MOTION_GENERATION]->setUpdatePermission(true);
	}
}
