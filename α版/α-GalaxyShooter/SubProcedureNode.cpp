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
	return subProcedureList(recognitionBB, memoryBB, bodyBB);
}


//=============================================================================
// 副処理リスト
//=============================================================================
NODE_STATUS SubProcedureNode::subProcedureList(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	switch (tag)
	{
	case SET_DESTINATION_OPPONENT:	return setMovingDestinationOpponent(recognitionBB, memoryBB, bodyBB);
	case SET_DESTINATION_RANDOM:	return setMovingDestinationRandom(recognitionBB, memoryBB, bodyBB);
	case SET_TARGET_OPPONENT:		return setShootingTargetOpponent(recognitionBB, memoryBB, bodyBB);
	default:						return NODE_STATUS::_NOT_FOUND;
	}
}


//=============================================================================
// 副処理：目的地を相手に設定
//=============================================================================
NODE_STATUS SubProcedureNode::setMovingDestinationOpponent(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	bodyBB->configMovingDestination(opponent->getPosition());
	return NODE_STATUS::SUCCESS;
}


//=============================================================================
// 副処理：ランダムにノードを目的地に設定する
//=============================================================================
NODE_STATUS SubProcedureNode::setMovingDestinationRandom(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	int number = rand() % Map::getMapNode().size();
	D3DXVECTOR3* newDestination = Map::getMapNode()[number]->getPosition();
	bodyBB->configMovingDestination(Map::getMapNode()[number]->getPosition());
	return NODE_STATUS::SUCCESS;
}


//=============================================================================
// 副処理：ショットターゲットを相手に設定
//=============================================================================
NODE_STATUS SubProcedureNode::setShootingTargetOpponent(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	bodyBB->setTargetCoordValue(*opponent->getPosition());
	return NODE_STATUS::SUCCESS;
}


