//-----------------------------------------------------------------------------
// �^���������� [MotionGeneration.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/19
//-----------------------------------------------------------------------------
#include "MotionGeneration.h"
#include "AbstractScene.h"
#include "AgentAI.h"
#include "input.h"
using namespace MotionGenerationNS;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
MotionGeneration::MotionGeneration(void)
{

}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
MotionGeneration::~MotionGeneration(void)
{

}


//=============================================================================
// ����������
//=============================================================================
void MotionGeneration::initialize(void)
{

}


//=============================================================================
// �I������
//=============================================================================
void MotionGeneration::uninitialize(void)
{

}


//=============================================================================
// �X�V����
//=============================================================================
void MotionGeneration::update(AgentAI* agentAI)
{
	// �ړ�
	if (bodyBB->getMove())
	{
		move(agentAI, bodyBB->getMovingDestination());
	}

	// �W�����v
	if (bodyBB->getJump())
	{
		agentAI->jump();
	}

	// �o���b�g��ł�
	if (bodyBB->getShootingBullet())
	{
		agentAI->shootBullet(bodyBB->getTargetCoordValue());
	}

	// �������[�p�C���̐ݒu
	if (bodyBB->getLocatingPile())
	{
		agentAI->locateMemoryPile();
	}

	// �������[���C���̐ؒf
	if (bodyBB->getCuttingLine())
	{
		agentAI->cutMemoryLine();
	}

	// �_�E������
	if (bodyBB->getRevivalAction())
	{
		agentAI->increaseRevivalPoint();
	}

	// ��󃂁[�h�ړ�

	// ����

	// �t���O�̃��Z�b�g
	bodyBB->setMove(false);
	bodyBB->setJump(false);				//�i���ꂪ�����Ă��ʃt���O�Ŏ~�܂�j
	bodyBB->setShootingBullet(false);
	bodyBB->setLocatingPile(false);
	bodyBB->setCuttingLine(false);
	bodyBB->setRevivalAction(false);
}


//=============================================================================
// �ړ�
//=============================================================================
void MotionGeneration::move(AgentAI* agentAI, D3DXVECTOR3* movingDestination)
{
	// �^�[�Q�b�g���W�ւ̃x�N�g������v���C���[Y�������̐������폜����
	// �i�s�������w���x�N�g�������
	D3DXVECTOR3 targetDirection = *movingDestination - *agentAI->getPosition();
	D3DXVECTOR3 adjustDirection = agentAI->getAxisY()->direction;

	float adjustScale = D3DXVec3Length(&targetDirection);
	D3DXVec3Scale(&adjustDirection, &adjustDirection, adjustScale);

	D3DXVECTOR3 moveDirection = agentAI->slip(targetDirection, adjustDirection);
	D3DXVec3Normalize(&moveDirection, &moveDirection);

	// �ړ�������
	agentAI->addSpeed(moveDirection * bodyBB->getSpeed());
	agentAI->postureControl(agentAI->getAxisZ()->direction, moveDirection, 0.1f);
}
