//-----------------------------------------------------------------------------
// �r�w�C�r�A�c���[ �T�u�v���V�[�W���m�[�h���� [SubProcedureNode.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/23
//-----------------------------------------------------------------------------
#pragma once
#include "BehaviorNodeBase.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class SubProcedureNode: public BehaviorNodeBase
{
private:
	NODE_STATUS subProcedureList(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	NODE_STATUS setTargetOpponent(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	
public:
	SubProcedureNode(int treeType, int parent, NODE_TYPE type, NODE_TAG tag);

	// ���s
	NODE_STATUS run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};
