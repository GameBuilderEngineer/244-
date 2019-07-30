//-----------------------------------------------------------------------------
// �r�w�C�r�A�c���[ ���[���m�[�h���� [RuleNode.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/17
//-----------------------------------------------------------------------------
#pragma once
#include "BehaviorNodeBase.h"
#include <vector>

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class RuleNode: public BehaviorNodeBase
{
private:
	BehaviorNodeBase* onOffSelect(std::vector<BehaviorNodeBase*>& activeChild, MemoryBB* memoryBB);
	BehaviorNodeBase* randomSelect(std::vector<BehaviorNodeBase*>& activeChild);
	void priorityWork(NODE_STATUS& result, bool& isRepetition, int& executedCount, BehaviorNodeBase*& searchNode, std::vector<BehaviorNodeBase*>& activeChild);
	void onOffWork(NODE_STATUS& result, bool& isRepetition, int& executedCount, BehaviorNodeBase*& searchNode, std::vector<BehaviorNodeBase*>& activeChild, MemoryBB* memoryBB);
	void randomWork(NODE_STATUS& result, bool& isRepetition, int& executedCount, BehaviorNodeBase*& searchNode, std::vector<BehaviorNodeBase*>& activeChild);
	void sequenceWork(NODE_STATUS& result, bool& isRepetition, int& executedCount, BehaviorNodeBase*& searchNode, std::vector<BehaviorNodeBase*>& activeChild);
	void pararellWork(NODE_STATUS& result, bool& isRepetition, int& executedCount, BehaviorNodeBase*& searchNode, std::vector<BehaviorNodeBase*>& activeChild);

public:
	RuleNode(int treeType, int parent, NODE_TYPE type, NODE_TAG tag);
	// ���s
	NODE_STATUS run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};

