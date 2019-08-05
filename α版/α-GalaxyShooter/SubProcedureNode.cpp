//-----------------------------------------------------------------------------
// �r�w�C�r�A�c���[ �T�u�v���V�[�W���m�[�h���� [SubProcedureNode.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/23
//-----------------------------------------------------------------------------
#include "SubProcedureNode.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
SubProcedureNode::SubProcedureNode(int treeType, int parentNumber, NODE_TYPE type, NODE_TAG tag) : BehaviorNodeBase(treeType, parentNumber, type, tag)
{

}


//=============================================================================
// ���s
//=============================================================================
NODE_STATUS SubProcedureNode::run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	return subProcedureList(recognitionBB, memoryBB, bodyBB);
}


//=============================================================================
// ���������X�g
//=============================================================================
NODE_STATUS SubProcedureNode::subProcedureList(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	switch (tag)
	{
	case SET_TARGET_OPPONENT: return setTargetOpponent(recognitionBB, memoryBB, bodyBB);
	case SET_TARGET_RANDOM_NODE: return setTargetRandomNode(recognitionBB, memoryBB, bodyBB);
	default: return NODE_STATUS::_NOT_FOUND;
	}
}


//=============================================================================
// �������F�ړ��^�[�Q�b�g�𑊎�ɐݒ�
//=============================================================================
NODE_STATUS SubProcedureNode::setTargetOpponent(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	return NODE_STATUS::SUCCESS;
}


//=============================================================================
// �������F�����_���Ƀm�[�h��ړI�n�ɐݒ肷��
//=============================================================================
NODE_STATUS SubProcedureNode::setTargetRandomNode(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	memoryBB->secondCount += 0.0166f;
	if (memoryBB->secondCount > 3.0f)
	{
		memoryBB->secondCount= 0.0f;
		memoryBB->tempRandomNode = rand() % Map::getMapNode().size();
		bodyBB->setIsMoving(true);
		return NODE_STATUS::SUCCESS;
	}
	else
	{
		return NODE_STATUS::FAILED;
	}
}