//-----------------------------------------------------------------------------
// ビヘイビアツリー アクションノード処理 [ActionNode.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/17
//-----------------------------------------------------------------------------
#include "ActionNode.h"

static const float STOP_MOVE_LENGTH = 5.0f;
static const float STOP_MOVE_LENGTH_STRICT = 3.5f;


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
	case ACTION_SHOOT:	return actionShoot(recognitionBB, memoryBB, bodyBB);
	case ACTION_PILE:	return actionPile(recognitionBB, memoryBB, bodyBB);
	default:			return NODE_STATUS::_NOT_FOUND;
	}
}


//=============================================================================
// アクション：移動
//=============================================================================
NODE_STATUS ActionNode::actionMove(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	// 到着していたら停止して成功
	if (bodyBB->getIsArrived())
	{
		bodyBB->setMove(false);
		return NODE_STATUS::SUCCESS;
	}

	// 到着していない場合実行中
	{
		D3DXVECTOR3 temp = *bodyBB->getMovingDestination() - *recognitionBB->getMyPosition();
		float length = D3DXVec3Length(&temp);

		// 調整中　要するにぴったり座標にとめたい
		if (length < STOP_MOVE_LENGTH_STRICT)
		{
			bodyBB->setIsArrival(true);
		}
		if (length < STOP_MOVE_LENGTH)
		{
			bodyBB->setSpeed(bodyBB->MOVING_SLOW_SPEED);
		}
		else
		{
			bodyBB->setSpeed(bodyBB->MOVING_SPEED);
		}

		bodyBB->setMove(true);
		return NODE_STATUS::RUNNING;
	}
}


//=============================================================================
// アクション：ジャンプ
//=============================================================================
NODE_STATUS ActionNode::actionJump(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	// 初速を与えるのを1フレームに限定するためのチェックをしたのち
	// 地上にいればジャンプをさせる

	if (bodyBB->whetherJumpedOnce())
	{// 過去フレームにジャンプをさせている場合
		if (recognitionBB->getWhetherInAir())
		{

		}
		else
		{
			bodyBB->setJumpedHistory(false);
		}
		bodyBB->setJump(false);
		return NODE_STATUS::RUNNING;	// ジャンプ実行中
	}

	else
	{
		if (recognitionBB->getWhetherInAir())
		{
			return NODE_STATUS::FAILED;	// 空中ではジャンプ失敗

		}
		else
		{
			bodyBB->setJump(true);
			bodyBB->setJumpedHistory(true);
			return NODE_STATUS::SUCCESS;// ジャンプ成功
		}
	}
}


//=============================================================================
// アクション：ショット
//=============================================================================
NODE_STATUS ActionNode::actionShoot(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	if (recognitionBB->getIsDown())
	{
		return NODE_STATUS::FAILED;		// ダウン時ショット失敗
	}
	else if (bodyBB->getShootingInterval() != 0)
	{
		return NODE_STATUS::RUNNING;	// インターバルタイムが残っているなら実行中
	}
	else
	{
		bodyBB->setShootingBullet(true);
		return NODE_STATUS::SUCCESS;	// ショット成功
	}
}


//=============================================================================
// アクション：メモリーパイル配置
//=============================================================================
NODE_STATUS ActionNode::actionPile(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	if (recognitionBB->getWhetherInAir() || bodyBB->getIsReadyForPile() == false)
	{
		return NODE_STATUS::FAILED;
	}
	else
	{
		bodyBB->setLocatingPile(true);
		return NODE_STATUS::SUCCESS;
	}
}
