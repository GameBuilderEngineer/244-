//-----------------------------------------------------------------------------
// ビヘイビアツリー アクションノード処理 [ActionNode.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/17
//-----------------------------------------------------------------------------
#pragma once
#include "BehaviorNodeBase.h"

//*****************************************************************************
// クラス定義
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

	// 実行
	NODE_STATUS run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};

