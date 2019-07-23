//-----------------------------------------------------------------------------
// �r�w�C�r�A�c���[ �A�N�V�����m�[�h���� [ActionNode.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/17
//-----------------------------------------------------------------------------
#pragma once
#include "BehaviorNodeBase.h"
using namespace BehaviorTreeNS;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class ActionNode: public BehaviorNodeBase
{
private:
	
public:
	ActionNode(int treeType, int parent, NODE_TAG);

	// ���s
	NODE_STATUS run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB, std::vector<BehaviorRecord> record);
};

