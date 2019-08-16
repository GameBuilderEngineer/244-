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
	case SET_DESTINATION_OPPONENT:	return setMovingDestinationOpponent(recognitionBB, memoryBB, bodyBB);
	case SET_DESTINATION_RANDOM:	return setMovingDestinationRandom(recognitionBB, memoryBB, bodyBB);
	case SET_TARGET_OPPONENT:		return setShootingTargetOpponent(recognitionBB, memoryBB, bodyBB);
	default:						return NODE_STATUS::_NOT_FOUND;
	}
}


//=============================================================================
// �������F�ړI�n�𑊎�ɐݒ�
//=============================================================================
NODE_STATUS SubProcedureNode::setMovingDestinationOpponent(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	bodyBB->configMovingDestination(opponent->getPosition());
	return NODE_STATUS::SUCCESS;
}


//=============================================================================
// �������F�����_���Ƀm�[�h��ړI�n�ɐݒ肷��
//=============================================================================
NODE_STATUS SubProcedureNode::setMovingDestinationRandom(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	int number = rand() % Map::getMapNode().size();
	D3DXVECTOR3* newDestination = Map::getMapNode()[number]->getPosition();
	bodyBB->configMovingDestination(Map::getMapNode()[number]->getPosition());
	return NODE_STATUS::SUCCESS;
}


//=============================================================================
// �������F�V���b�g�^�[�Q�b�g�𑊎�ɐݒ�
//=============================================================================
NODE_STATUS SubProcedureNode::setShootingTargetOpponent(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	bodyBB->setTargetCoordValue(*opponent->getPosition());
	return NODE_STATUS::SUCCESS;
}


