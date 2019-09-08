//-----------------------------------------------------------------------------
// ビヘイビアツリー 条件ノード処理 [ConditionalNode.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/23
//-----------------------------------------------------------------------------
#pragma once
#include "BehaviorNodeBase.h"
#include <vector>

//*****************************************************************************
// クラス定義
//*****************************************************************************
class ConditionalNode: public BehaviorNodeBase
{
private:

	// 条件リスト
	bool conditionList(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	// 条件
	bool ifOpponentNear(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);	// 条件：相手が近くにいたら
	bool ifBulletNear(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	bool if5secondsLater(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	bool if3secondsLater(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	bool if1secondLater(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	bool ifRecursionIsRunning(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	bool ifFallDestinationDecided(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);


public:
	ConditionalNode(int treeType, int parent, NODE_TYPE type, NODE_TAG tag);
	// 実行
	NODE_STATUS run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};

