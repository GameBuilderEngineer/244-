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
	case ACTION_MOVE:		return actionMove(recognitionBB, memoryBB, bodyBB);
	case ACTION_JUMP:		return actionJump(recognitionBB, memoryBB, bodyBB);
	case ACTION_SHOOT:		return actionShoot(recognitionBB, memoryBB, bodyBB);
	case ACTION_PILE:		return actionPile(recognitionBB, memoryBB, bodyBB);
	case ACTION_CUT:		return actionCut(recognitionBB, memoryBB, bodyBB);
	case ACTION_REVIVAL:	return actionRevival(recognitionBB, memoryBB, bodyBB);
	case ACTION_SKY_MOVE:	return actionSkyMove(recognitionBB, memoryBB, bodyBB);
	case ACTION_FALL:		return actionFall(recognitionBB, memoryBB, bodyBB);

	default:
		MessageBox(NULL, TEXT("アクションリストにないノードです"), TEXT("Behavior Tree Error"), MB_OK);
		return NODE_STATUS::_NOT_FOUND;
	}
}


//=============================================================================
// アクション：移動
//=============================================================================
NODE_STATUS ActionNode::actionMove(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	static const float STOP_MOVE_LENGTH = 6.0f;
	static const float STOP_MOVE_LENGTH_STRICT = 5.5f;

	// 到着していたら停止で失敗
	if (bodyBB->getIsArrived())
	{
		bodyBB->setMove(false);
		return NODE_STATUS::FAILED;
	}

	// 到着していない場合実行中↓

	// 到着座標との距離を測る
	D3DXVECTOR3 vecToDestination;
	if (recognitionBB->getPlayerState() == playerNS::SKY)
	{// 上空モード
		D3DXVECTOR3 destAxisY;
		destAxisY = *bodyBB->getMovingDestination() - *Map::getField()->getPosition();
		D3DXVec3Normalize(&destAxisY, &destAxisY);
		D3DXVECTOR3 skyDest = *bodyBB->getMovingDestination() + destAxisY * recognitionBB->getSkyHeight();
		vecToDestination = skyDest - *recognitionBB->getMyPosition();
	}
	else
	{// 地上
		vecToDestination = *bodyBB->getMovingDestination() - *recognitionBB->getMyPosition();
	}
	float length = D3DXVec3Length(&vecToDestination);

	// 距離に応じて到着を判断する
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



//=============================================================================
// アクション：ジャンプ
//=============================================================================
NODE_STATUS ActionNode::actionJump(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	// 初速を与えるのを1フレームに限定するためのチェックをしたのち
	// 地上にいればジャンプをさせる


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

	//if (bodyBB->whetherJumpedOnce())
	//{// 過去フレームにジャンプをさせている場合
	//	if (recognitionBB->getWhetherInAir())
	//	{

	//	}
	//	else
	//	{
	//		bodyBB->setJumpedHistory(false);
	//	}
	//	bodyBB->setJump(false);
	//	return NODE_STATUS::RUNNING;	// ジャンプ実行中
	//}

	//else
	//{
	//}
}


//=============================================================================
// アクション：ショット
//=============================================================================
NODE_STATUS ActionNode::actionShoot(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	if (recognitionBB->getPlayerState() == playerNS::DOWN)
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

		// パイルの5つめを打ち込みしたらリカージョン実行中フラグをオフにする
		if (*recognitionBB->getPileCount() == 5)
		{
			recognitionBB->setIsRecursionRunning(false);
			recognitionBB->setIsStartRecursion(false);
			*recognitionBB->getPileCount() = 0;
		}

		return NODE_STATUS::SUCCESS;
	}
}


//=============================================================================
// アクション：メモリーライン切断
//=============================================================================
NODE_STATUS ActionNode::actionCut(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	//----------------------------------------------------------------
	// 切断を実行後切れたかどうか取得できるのが1フレーム後になるので
	// 初回は必ずFAILEDが返る
	// 切れていればSUCCESSではなく「切断」の実行があればSUCCESSとする
	//----------------------------------------------------------------
	if (opponent->getMemoryLine()->getDisconnected())
	{// メモリーラインが切れている
		if (bodyBB->getOnceTriedCut())
		{// 切断アクションを実行済み
			return NODE_STATUS::SUCCESS;// 切断に成功
		}
		else
		{
			return NODE_STATUS::FAILED;	// 切断に失敗（切れていても自分で切断していない）
		}
		bodyBB->setOnceTriedCut(false);
	}
	else
	{// メモリーラインは切れていない
		bodyBB->setCuttingLine(true);
		bodyBB->setOnceTriedCut(true);
		return NODE_STATUS::FAILED;		// 切断に失敗
	}
}


//=============================================================================
// アクション：ダウン復活
//=============================================================================
NODE_STATUS ActionNode::actionRevival(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	static const float INCREASE_INTERVAL = 0.2f;//（秒）ボタン連打の間隔を表現

	if (bodyBB->getRevivalPointInterval() < INCREASE_INTERVAL)
	{
		bodyBB->setRevivalPointInterval(bodyBB->getRevivalPointInterval() + recognitionBB->getFrameTime());
		return NODE_STATUS::FAILED;		// ダウン復活アクション失敗
	}
	else
	{
		bodyBB->setRevivalAction(true);
		bodyBB->setRevivalPointInterval(0.0f);
		return NODE_STATUS::SUCCESS;	// ダウン復活アクション成功
	}
}


//=============================================================================
// アクション：上空モード移動
//=============================================================================
NODE_STATUS ActionNode::actionSkyMove(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	return NODE_STATUS::SUCCESS;
}


//=============================================================================
// アクション：落下
//=============================================================================
NODE_STATUS ActionNode::actionFall(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	return NODE_STATUS::SUCCESS;
}
