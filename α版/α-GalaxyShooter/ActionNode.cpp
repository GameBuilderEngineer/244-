//-----------------------------------------------------------------------------
// ビヘイビアツリー アクションノード処理 [ActionNode.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/17
//-----------------------------------------------------------------------------
#include "ActionNode.h"

//=============================================================================
// コンストラクタ
//=============================================================================
ActionNode::ActionNode(int treeType, int parentNumber, NODE_TAG tag): BehaviorNodeBase(treeType, parentNumber, tag)
{

}


//=============================================================================
// 実行
//=============================================================================
NODE_STATUS ActionNode::run(RecognitionBB* recognitionBB,
	MemoryBB* memoryBB, BodyBB* bodyBB, std::vector<BehaviorRecord> record)
{
	return NODE_STATUS::SUCCESS;
}
