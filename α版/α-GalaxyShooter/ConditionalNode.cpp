//-----------------------------------------------------------------------------
// �r�w�C�r�A�c���[ �����m�[�h���� [ConditionalNode.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/23
//-----------------------------------------------------------------------------
#include "ConditionalNode.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
ConditionalNode::ConditionalNode(int treeType, int parentNumber, NODE_TYPE type, NODE_TAG tag): BehaviorNodeBase(treeType, parentNumber,type, tag)
{
		
}


//=============================================================================
// ���s
//=============================================================================
NODE_STATUS ConditionalNode::run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	if (conditionList(recognitionBB, memoryBB, bodyBB))
	{
		return NODE_STATUS::SUCCESS;
	}
	else
	{
		return  NODE_STATUS::FAILED;
	}
}


//=============================================================================
// �������X�g
//=============================================================================
bool ConditionalNode::conditionList(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	switch (tag)
	{
	case IF_OPPONENT_NEAR: return ifOpponentNear(recognitionBB, memoryBB, bodyBB);
	default: return false;
	}
}


//=============================================================================
// �����F���肪�߂��ɂ�����
//=============================================================================
bool ConditionalNode::ifOpponentNear(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	return true;
}