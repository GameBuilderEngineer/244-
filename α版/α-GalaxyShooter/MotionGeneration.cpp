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
void MotionGeneration::initialize(Input* _input, playerNS::OperationKeyTable _keyTable)
{
	input = _input;
	keyTable = _keyTable;
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
		animationPlayer->setAIAnimFlag(animationPlayerNS::AI_ANIMATION_FALG::MOVE, true);
	}

	// �W�����v
	if (bodyBB->getJump())
	{
		input->keyPress(keyTable.jump);
	}

	// �o���b�g��ł�
	if (bodyBB->getShootingBullet())
	{
		input->keyPress(playerNS::BUTTON_BULLET);
		animationPlayer->setAIAnimFlag(animationPlayerNS::AI_ANIMATION_FALG::SHOOTING, true);
	}

	// �������[�p�C���̐ݒu
	if (bodyBB->getLocatingPile())
	{
		input->keyPress(playerNS::BUTTON_PILE);
		animationPlayer->setAIAnimFlag(animationPlayerNS::AI_ANIMATION_FALG::INSTALLATION, true);
	}

	// �������[���C���̐ؒf
	if (bodyBB->getCuttingLine())
	{
		input->keyPress(playerNS::BUTTON_CUT);
		animationPlayer->setAIAnimFlag(animationPlayerNS::AI_ANIMATION_FALG::SLASH, true);
	}

	// �_�E������
	if (bodyBB->getRevivalAction())
	{
		input->keyPress(keyTable.revival);
	}

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
