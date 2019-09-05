//-----------------------------------------------------------------------------
// �r�w�C�r�A�c���[ �A�N�V�����m�[�h���� [ActionNode.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/17
//-----------------------------------------------------------------------------
#pragma once
#include "BehaviorNodeBase.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class ActionNode: public BehaviorNodeBase
{
private:
	NODE_STATUS actionList(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	NODE_STATUS actionMove(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	NODE_STATUS actionJump(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	NODE_STATUS actionShoot(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	NODE_STATUS actionPile(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	NODE_STATUS actionCut(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	NODE_STATUS actionRevival(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	NODE_STATUS actionSkyMove(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	NODE_STATUS actionFall(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);


public:
	ActionNode(int treeType, int parent, NODE_TYPE type, NODE_TAG tag);

	// ���s
	NODE_STATUS run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};

