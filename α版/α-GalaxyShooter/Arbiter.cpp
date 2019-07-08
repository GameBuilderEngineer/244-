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
	for (int i = 0; i < Module::NUM_MAX; i++)
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
		module[Module::SENSOR]->setUpdatePermission(true);
	}

	// �����
	if (frameCount- sensorLastFrame > sensoryTransmissionTime)
	{
		module[Module::ENVIRONMENT_ANSLYSIS]->setUpdatePermission(true);
	}

	// �o�H�T��
	if (frameCount - pathPlanningLastFrame > pathPanningInterval)
	{
		pathPlanningLastFrame = frameCount;
		module[Module::PATH_PLANNING]->setUpdatePermission(true);
	}

	// �ӎv����
	if (frameCount - decisionMakingLastFrame > decisionMakingInterval)
	{
		decisionMakingLastFrame = frameCount;
		module[Module::DECISION_MAKING]->setUpdatePermission(true);
	}

	// �^������
	if (frameCount - motionGenerationLastFrame > motionInterval)
	{
		decisionMakingLastFrame = frameCount;
		module[Module::MOTION_GENERATION]->setUpdatePermission(true);
	}
}
