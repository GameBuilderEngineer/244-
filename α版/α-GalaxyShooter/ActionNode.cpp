//-----------------------------------------------------------------------------
// ビヘイビアツリー アクションノード処理 [ActionNode.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/17
//-----------------------------------------------------------------------------
#include "ActionNode.h"

//=============================================================================
// コンストラクタ
//=============================================================================
ActionNode::ActionNode(int treeType, int parentNumber, NODE_TYPE type, NODE_TAG tag) : BehaviorNodeBase(treeType, parentNumber, type, tag)
{

}


//=============================================================================
// 実行
//=============================================================================
NODE_STATUS ActionNode::run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	return actionList(recognitionBB, memoryBB, bodyBB);
}


//=============================================================================
// アクションリスト
//=============================================================================
NODE_STATUS ActionNode::actionList(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	switch (tag)
	{
	case ACTION_MOVE:	return actionMove(recognitionBB, memoryBB, bodyBB);
	case ACTION_JUMP:	return actionJump(recognitionBB, memoryBB, bodyBB);
	default:			return NODE_STATUS::_NOT_FOUND;
	}
}


//=============================================================================
// アクション：移動
//=============================================================================
NODE_STATUS ActionNode::actionMove(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	bodyBB->setMove(true);
	return NODE_STATUS::RUNNING;
}


//=============================================================================
// アクション：ジャンプ
//=============================================================================
NODE_STATUS ActionNode::actionJump(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	//if (bodyBB->getIsJumping() == true)
	//{
	//	return NODE_STATUS::RUNNING;
	//}
	//if (bodyBB->getIsJumping() == false)
	//{
	//	bodyBB->setJump(true);
		return NODE_STATUS::SUCCESS;
	//}
}