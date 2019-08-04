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
	bodyBB->setJump(true);

	memoryBB->tempRandomNode = 0;
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

	std::vector<MapNode*> mapNode = Map::getMapNode();
	D3DXVECTOR3 target = mapNode[memoryBB->tempRandomNode]->getPosition();

	// �ړ�
	if (bodyBB->getIsMoving())
	{
		move(agentAI, &target);
	}

	// �W�����v
	jumpFlagCycle(agentAI);
}


//=============================================================================
// �ړ�
//=============================================================================
void MotionGeneration::move(AgentAI* agentAI, D3DXVECTOR3* targetCoord)
{
	// �^�[�Q�b�g���W�ւ̃x�N�g������v���C���[Y�������̐������폜����
	// �i�s�������w���x�N�g�������
	D3DXVECTOR3 targetDirection = *targetCoord - *agentAI->getPosition();
	D3DXVECTOR3 adjustDirection = agentAI->getAxisY()->direction;

	float adjustScale = D3DXVec3Length(&targetDirection);
	D3DXVec3Scale(&adjustDirection, &adjustDirection, adjustScale);

	D3DXVECTOR3 moveDirection = agentAI->slip(targetDirection, adjustDirection);
	D3DXVec3Normalize(&moveDirection, &moveDirection);

	//------------------------------
	// �O�ςƂ��Ŋ撣�낤�Ƃ����c�[
	//------------------------------
	//// �d�͕����ƖړI�n���W�����]�����쐬
	//D3DXVECTOR3 moveDirection = agentAI->getGravity();
	//D3DXVECTOR3 targetDirection = targetCoord - *agentAI->getPosition();
	//D3DXVECTOR3 rotationAxis;
	//D3DXVec3Cross(&rotationAxis, &moveDirection, &targetDirection);

	//// �ړI�n���W���^���΂̂Ƃ��̋��E����


	//// �d�͕����̈ړ��x�N�g��������90�x��]������
	//D3DXQUATERNION quaternion = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	//D3DXMATRIX rotationMatrix;
	//D3DXQuaternionRotationAxis(&quaternion, &rotationAxis, D3DX_PI / 2.0f);
	//D3DXMatrixRotationQuaternion(&rotationMatrix, &quaternion);
	//D3DXVec3TransformCoord(&moveDirection, &moveDirection, &rotationMatrix);

	// �ړ�������
	D3DXVec3Normalize(&moveDirection, &moveDirection);
	agentAI->addSpeed(moveDirection * playerNS::SPEED);
	agentAI->postureControl(agentAI->getAxisZ()->direction, moveDirection, 0.1f);

	// �ړI�n�ɒ������玩����~
	if (autoStop(agentAI->getPosition(), targetCoord))
	{
		bodyBB->setIsMoving(false);
	}
}


//=============================================================================
// ������~
//=============================================================================
bool MotionGeneration::autoStop(D3DXVECTOR3* position1, D3DXVECTOR3* position2)
{
	// ��Ԃ܂�
	float length = D3DXVec3Length(&(*position2 - *position1));
	if (length < STOP_MOVE_LENGTH)
	{
		return true;
	}
	else
	{
		return false;
	}

	//if (	(position2->x - ADJUST < position1->x && position1->x < position2->x + ADJUST)
	//	&&	(position2->y - ADJUST < position1->y && position1->y < position2->y + ADJUST)
	//	&&	(position2->z - ADJUST < position1->z && position1->z < position2->z + ADJUST))
	//{
	//	return  true;
	//}
	//else
	//{
	//	return false;
	//}

	//int x1 = (int)position1.x;
	//int y1 = (int)position1.y;
	//int z1 = (int)position1.z;

	//int x2 = (int)position2.x;
	//int y2 = (int)position2.y;
	//int z2 = (int)position2.z;

	//if (x1 == x2 && y1 == y2 && z1 == z2)
	//{
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}
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
			*Map::getField()->getMesh(), Map::getField()->getMatrixWorld()))
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
