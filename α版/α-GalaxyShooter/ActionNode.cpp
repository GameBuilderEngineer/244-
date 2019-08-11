//-----------------------------------------------------------------------------
// �r�w�C�r�A�c���[ �A�N�V�����m�[�h���� [ActionNode.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/17
//-----------------------------------------------------------------------------
#include "ActionNode.h"

static const float STOP_MOVE_LENGTH = 5.0f;
static const float STOP_MOVE_LENGTH_STRICT = 3.5f;


//=============================================================================
// �R���X�g���N�^
//=============================================================================
ActionNode::ActionNode(int treeType, int parentNumber, NODE_TYPE type, NODE_TAG tag) : BehaviorNodeBase(treeType, parentNumber, type, tag)
{

}


//=============================================================================
// ���s
//=============================================================================
NODE_STATUS ActionNode::run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	return actionList(recognitionBB, memoryBB, bodyBB);
}


//=============================================================================
// �A�N�V�������X�g
//=============================================================================
NODE_STATUS ActionNode::actionList(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	switch (tag)
	{
	case ACTION_MOVE:	return actionMove(recognitionBB, memoryBB, bodyBB);
	case ACTION_JUMP:	return actionJump(recognitionBB, memoryBB, bodyBB);
	case ACTION_SHOOT:	return actionShoot(recognitionBB, memoryBB, bodyBB);
	case ACTION_PILE:	return actionPile(recognitionBB, memoryBB, bodyBB);
	default:			return NODE_STATUS::_NOT_FOUND;
	}
}


//=============================================================================
// �A�N�V�����F�ړ�
//=============================================================================
NODE_STATUS ActionNode::actionMove(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	// �������Ă������~���Đ���
	if (bodyBB->getIsArrived())
	{
		bodyBB->setMove(false);
		return NODE_STATUS::SUCCESS;
	}

	// �������Ă��Ȃ��ꍇ���s��
	{
		D3DXVECTOR3 temp = *bodyBB->getMovingDestination() - *recognitionBB->getMyPosition();
		float length = D3DXVec3Length(&temp);

		// �������@�v����ɂ҂�������W�ɂƂ߂���
		if (length < STOP_MOVE_LENGTH_STRICT)
		{
			bodyBB->setIsArrival(true);
		}
		if (length < STOP_MOVE_LENGTH)
		{
			bodyBB->setSpeed(bodyBB->MOVING_SLOW_SPEED);
		}
		else
		{
			bodyBB->setSpeed(bodyBB->MOVING_SPEED);
		}

		bodyBB->setMove(true);
		return NODE_STATUS::RUNNING;
	}
}


//=============================================================================
// �A�N�V�����F�W�����v
//=============================================================================
NODE_STATUS ActionNode::actionJump(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	// ������^����̂�1�t���[���Ɍ��肷�邽�߂̃`�F�b�N�������̂�
	// �n��ɂ���΃W�����v��������

	if (bodyBB->whetherJumpedOnce())
	{// �ߋ��t���[���ɃW�����v�������Ă���ꍇ
		if (recognitionBB->getWhetherInAir())
		{

		}
		else
		{
			bodyBB->setJumpedHistory(false);
		}
		bodyBB->setJump(false);
		return NODE_STATUS::RUNNING;	// �W�����v���s��
	}

	else
	{
		if (recognitionBB->getWhetherInAir())
		{
			return NODE_STATUS::FAILED;	// �󒆂ł̓W�����v���s

		}
		else
		{
			bodyBB->setJump(true);
			bodyBB->setJumpedHistory(true);
			return NODE_STATUS::SUCCESS;// �W�����v����
		}
	}
}


//=============================================================================
// �A�N�V�����F�V���b�g
//=============================================================================
NODE_STATUS ActionNode::actionShoot(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	if (recognitionBB->getIsDown())
	{
		return NODE_STATUS::FAILED;		// �_�E�����V���b�g���s
	}
	else if (bodyBB->getShootingInterval() != 0)
	{
		return NODE_STATUS::RUNNING;	// �C���^�[�o���^�C�����c���Ă���Ȃ���s��
	}
	else
	{
		bodyBB->setShootingBullet(true);
		return NODE_STATUS::SUCCESS;	// �V���b�g����
	}
}


//=============================================================================
// �A�N�V�����F�������[�p�C���z�u
//=============================================================================
NODE_STATUS ActionNode::actionPile(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	if (recognitionBB->getWhetherInAir() || bodyBB->getIsReadyForPile() == false)
	{
		return NODE_STATUS::FAILED;
	}
	else
	{
		bodyBB->setLocatingPile(true);
		return NODE_STATUS::SUCCESS;
	}
}
