//-----------------------------------------------------------------------------
// �r�w�C�r�A�c���[ �A�N�V�����m�[�h���� [ActionNode.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/17
//-----------------------------------------------------------------------------
#include "ActionNode.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
ActionNode::ActionNode(int treeType, int parentNumber, NODE_TAG tag): BehaviorNodeBase(treeType, parentNumber, tag)
{

}


//=============================================================================
// ���s
//=============================================================================
NODE_STATUS ActionNode::run(RecognitionBB* recognitionBB,
	MemoryBB* memoryBB, BodyBB* bodyBB, std::vector<BehaviorRecord> record)
{
	return NODE_STATUS::SUCCESS;
}
