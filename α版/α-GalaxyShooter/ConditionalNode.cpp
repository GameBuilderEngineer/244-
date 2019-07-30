//-----------------------------------------------------------------------------
// ビヘイビアツリー 条件ノード処理 [ConditionalNode.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/23
//-----------------------------------------------------------------------------
#include "ConditionalNode.h"

//=============================================================================
// コンストラクタ
//=============================================================================
ConditionalNode::ConditionalNode(int treeType, int parentNumber, NODE_TYPE type, NODE_TAG tag): BehaviorNodeBase(treeType, parentNumber,type, tag)
{
		
}


//=============================================================================
// 実行
//=============================================================================
NODE_STATUS ConditionalNode::run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	if (conditionList(recognitionBB, memoryBB, bodyBB))
	{
		return NODE_STATUS::SUCCESS;
	}
	else
	{
		return  NODE_STATUS::FAILED;
	}
}


//=============================================================================
// 条件リスト
//=============================================================================
bool ConditionalNode::conditionList(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	switch (tag)
	{
	case IF_OPPONENT_NEAR: return ifOpponentNear(recognitionBB, memoryBB, bodyBB);
	default: return false;
	}
}


//=============================================================================
// 条件：相手が近くにいたら
//=============================================================================
bool ConditionalNode::ifOpponentNear(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	return true;
}