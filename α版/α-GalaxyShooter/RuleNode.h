//-----------------------------------------------------------------------------
// �r�w�C�r�A�c���[ ���[���m�[�h���� [RuleNode.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/17
//-----------------------------------------------------------------------------
#pragma once
#include "BehaviorNodeBase.h"
#include <vector>

struct ResultData
{
	NODE_STATUS status;
	bool isRepetition;
	int executedCount;
};

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class RuleNode: public BehaviorNodeBase
{
public:
	RuleNode(int treeType, int parent, NODE_TAG);
	// ���s
	NODE_STATUS run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB, std::vector<BehaviorRecord> record);
};

