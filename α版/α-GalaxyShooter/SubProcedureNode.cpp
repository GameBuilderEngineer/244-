//-----------------------------------------------------------------------------
// ビヘイビアツリー サブプロシージャノード処理 [SubProcedureNode.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/23
//-----------------------------------------------------------------------------
#include "SubProcedureNode.h"

//=============================================================================
// コンストラクタ
//=============================================================================
SubProcedureNode::SubProcedureNode(int treeType, int parentNumber, NODE_TYPE type, NODE_TAG tag) : BehaviorNodeBase(treeType, parentNumber, type, tag)
{

}


//=============================================================================
// 実行
//=============================================================================
NODE_STATUS SubProcedureNode::run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	return NODE_STATUS::SUCCESS;
}


//=============================================================================
// 副処理リスト
//=============================================================================
NODE_STATUS SubProcedureNode::subProcedureList(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	switch (tag)
	{
	case SET_TARGET_OPPONENT: return setTargetOpponent(recognitionBB, memoryBB, bodyBB);
	default: return NODE_STATUS::_NOT_FOUND;
	}
}


//=============================================================================
// 副処理：移動ターゲットを相手に設定
//=============================================================================
NODE_STATUS SubProcedureNode::setTargetOpponent(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	return NODE_STATUS::SUCCESS;
}