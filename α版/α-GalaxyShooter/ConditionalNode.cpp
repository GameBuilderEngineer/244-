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
	case IF_OPPONENT_NEAR:				return ifOpponentNear(recognitionBB, memoryBB, bodyBB);
	case IF_BULLET_NEAR:				return ifBulletNear(recognitionBB, memoryBB, bodyBB);
	case IF_SHOCK_WAVE_MAY_BE_HAPPEN:	return ifShockWaveMayBeHappen(recognitionBB, memoryBB, bodyBB);
	case IF_FIVE_SECONDS_LATER:			return if5secondsLater(recognitionBB, memoryBB, bodyBB);
	case IF_THREE_SECONDS_LATER:		return if3secondsLater(recognitionBB, memoryBB, bodyBB);
	case IF_ONE_SECOND_LATER:			return if1secondLater(recognitionBB, memoryBB, bodyBB);
	case IF_RECURSION_IS_RUNNING:		return ifRecursionIsRunning(recognitionBB, memoryBB, bodyBB);
	case IF_DESTINATION_DECIDED:		return ifDestinationDecided(recognitionBB, memoryBB, bodyBB);
	case IF_OPPONENT_DOES_RECURSION:	return ifOpponentDoesRecursion(recognitionBB, memoryBB, bodyBB);
	case IF_OPPONENT_IS_DOWN:			return ifOpponentIsDown(recognitionBB, memoryBB, bodyBB);
	case IF_BULLET_SWITCH_IS_ON:		return ifBulletSwitchIsOn(recognitionBB, memoryBB, bodyBB);
	default:
		MessageBox(NULL, TEXT("条件リストにないノードです"), TEXT("Behavior Tree Error"), MB_OK);
		return false;
	}
}


//=============================================================================
// 条件：相手が近くにいたら
//=============================================================================
bool ConditionalNode::ifOpponentNear(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	return true;
}


//=============================================================================
// 条件：バレットが近いなら
//=============================================================================
bool ConditionalNode::ifBulletNear(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
 	if (recognitionBB->getIsBulletNear())
	{
		return true;
	}
	else
	{
		return false;
	}
}


//=============================================================================
// 条件：衝撃波が発生しそうなら
//=============================================================================
bool ConditionalNode::ifShockWaveMayBeHappen(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	return recognitionBB->getMayHappenShockWave();
}


//=============================================================================
// 条件：5秒経ったら
//=============================================================================
bool ConditionalNode::if5secondsLater(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	if (memoryBB->getTimer()[this]++ > 5 * 60/*1sec = 60fps*/)
	{
		memoryBB->getTimer()[this] = 0;
		return true;
	}
	
	return false;
}


//=============================================================================
// 条件：3秒経ったら
//=============================================================================
bool ConditionalNode::if3secondsLater(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	if (memoryBB->getTimer()[this]++ > 3 * 60/*1sec = 60fps*/)
	{
		memoryBB->getTimer()[this] = 0;
		return true;
	}

	return false;
}


//=============================================================================
// 条件：1秒経ったら
//=============================================================================
bool ConditionalNode::if1secondLater(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	if (memoryBB->getTimer()[this]++ > 60/*1sec = 60fps*/)
	{
		memoryBB->getTimer()[this] = 0;
		return true;
	}

	return false;
}


//=============================================================================
// 条件：リカージョン実行中なら
//=============================================================================
bool ConditionalNode::ifRecursionIsRunning(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	return recognitionBB->getIsRecursionRunning();
}


//=============================================================================
// 条件：移動先座標決定済なら
//=============================================================================
bool ConditionalNode::ifDestinationDecided(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	return recognitionBB->getWhetherDestinationDecided();
}


//=============================================================================
// 条件：相手がリカージョン中なら
//=============================================================================
bool ConditionalNode::ifOpponentDoesRecursion(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
 	if (opponent->getElementMemoryPile() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


//=============================================================================
// 条件：相手がダウン中なら
//=============================================================================
bool ConditionalNode::ifOpponentIsDown(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	if (opponent->getState() == playerNS::DOWN)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//=============================================================================
// 条件：相手がダウン中なら
//=============================================================================
bool ConditionalNode::ifBulletSwitchIsOn(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	return recognitionBB->getBulletSwitch();
}

