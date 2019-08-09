//-----------------------------------------------------------------------------
// �^���������� [MotionGeneration.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/19
//-----------------------------------------------------------------------------
#include "MotionGeneration.h"
#include "AbstractScene.h"
#include "AgentAI.h"
#include "Map.h"// ��
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
	bodyBB->setMovingDestination(&D3DXVECTOR3(100.0f, 0.0f, 0.0f));
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
	bodyBB->movingDestination = Map::getMapNode()[20]->getPosition();
	bodyBB->setMove(true);

	// �ړ�
	if (bodyBB->getMove())
	{
		move(agentAI, bodyBB->getMovingDestination());
	}

	//// �W�����v
	//jumpFlagCycle(agentAI);
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
	agentAI->addSpeed(moveDirection * playerNS::SPEED);
	agentAI->postureControl(agentAI->getAxisZ()->direction, moveDirection, 0.1f);

	//// �ړI�n�ɒ������玩����~
	//if (autoStop(agentAI->getPosition(), movingDestination))
	//{
	//	bodyBB->setMove(false);
	//}
}


//=============================================================================
// ������~
//=============================================================================
bool MotionGeneration::autoStop(D3DXVECTOR3* position1, D3DXVECTOR3* position2)
{
	float length = D3DXVec3Length(&(*position2 - *position1));
	if (length < STOP_MOVE_LENGTH)
	{
		return true;
	}
	else
	{
		return false;
	}
}


//=============================================================================
// �W�����v�̃t���O�z��
//=============================================================================
void MotionGeneration::jumpFlagCycle(AgentAI* agentAI)
{
	// �W�����v���łȂ���΃W�����v���߂��󂯕t����
	if (bodyBB->getIsJumping() == false)
	{
		if (bodyBB->getJump())
		{
			bodyBB->setJump(false);
			bodyBB->setIsJumping(true);
			agentAI->jump();// �����ŃA�N�V����
		}
	}

	// �W�����v���̏ꍇ�n��ɐڂ����^�C�~���O�ŃW�����v����Ԃ���������
	else
	{
		// ���܋󒆁H
		if (agentAI->getReverseAxisY()->rayIntersect(
			*Map::getField()->getMesh(), *Map::getField()->getMatrixWorld()))
		{

		}
		else
		{
			bodyBB->setIsAir(true);
		}

		// �󒆂���Ȃ��Ȃ�
		if (bodyBB->getIsAir() == false) return;

		// �󒆂Ȃ�n�ʂɋ߂��ƃW�����v�I���Ƃ݂Ȃ�
		if (agentAI->getReverseAxisY()->distance < 3.0f)
		{
			bodyBB->setIsAir(false);
			bodyBB->setIsJumping(false);
		}
	}
}
