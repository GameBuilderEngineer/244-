//-----------------------------------------------------------------------------
// �r�w�C�r�A�c���[ �����m�[�h���� [ConditionalNode.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/23
//-----------------------------------------------------------------------------
#pragma once
#include "BehaviorNodeBase.h"
#include <vector>

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class ConditionalNode: public BehaviorNodeBase
{
private:

	// �������X�g
	bool conditionList(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	// ����
	bool ifOpponentNear(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);	// �����F���肪�߂��ɂ�����
	bool ifBulletNear(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	bool if5secondsLater(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	bool if3secondsLater(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	bool if1secondLater(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	bool ifRecursionIsRunning(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	bool ifFallDestinationDecided(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);


public:
	ConditionalNode(int treeType, int parent, NODE_TYPE type, NODE_TAG tag);
	// ���s
	NODE_STATUS run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};

