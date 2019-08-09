//-----------------------------------------------------------------------------
// �r�w�C�r�A�c���[ �A�N�V�����m�[�h���� [ActionNode.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/17
//-----------------------------------------------------------------------------
#include "ActionNode.h"

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
	default:			return NODE_STATUS::_NOT_FOUND;
	}
}


//=============================================================================
// �A�N�V�����F�ړ�
//=============================================================================
NODE_STATUS ActionNode::actionMove(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	bodyBB->setMove(true);
	return NODE_STATUS::RUNNING;
}


//=============================================================================
// �A�N�V�����F�W�����v
//=============================================================================
NODE_STATUS ActionNode::actionJump(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	//if (bodyBB->getIsJumping() == true)
	//{
	//	return NODE_STATUS::RUNNING;
	//}
	//if (bodyBB->getIsJumping() == false)
	//{
	//	bodyBB->setJump(true);
		return NODE_STATUS::SUCCESS;
	//}
}