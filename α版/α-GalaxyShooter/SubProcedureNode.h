//-----------------------------------------------------------------------------
// �r�w�C�r�A�c���[ �T�u�v���V�[�W���m�[�h���� [SubProcedureNode.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/23
//-----------------------------------------------------------------------------
#pragma once
#include "BehaviorNodeBase.h"
using namespace BehaviorTreeNS;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class SubProcedureNode: public BehaviorNodeBase
{
private:
	
public:
	SubProcedureNode(int treeType, int parent, NODE_TAG);
	// ���s
	NODE_STATUS run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB, std::vector<BehaviorRecord> record);
};

