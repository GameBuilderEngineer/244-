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
	case SET_DESTINATION_NEXT_PILE: return setMovingDestinationNextPile(recognitionBB, memoryBB, bodyBB);
	case SET_DESTINATION_TO_FALL:	return setMovingDestinationToFall(recognitionBB, memoryBB, bodyBB);
	case SET_TARGET_OPPONENT:		return setShootingTargetOpponent(recognitionBB, memoryBB, bodyBB);
	case SET_RECURSION_RECOGNITION: return setRecursionRecognition(recognitionBB, memoryBB, bodyBB);
	default:
		MessageBox(NULL, TEXT("副処理リストにないノードです"), TEXT("Behavior Tree Error"), MB_OK);
		return NODE_STATUS::_NOT_FOUND;
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
// 副処理：次のパイル設置座標を目的地に設定する
//=============================================================================
NODE_STATUS SubProcedureNode::setMovingDestinationNextPile(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	// リカージョン実行中でないならreturn
	if (recognitionBB->getIsRecursionRunning() == false) { return NODE_STATUS::FAILED; }

	bodyBB->configMovingDestination(
		&recognitionBB->getRunningRecursion()->pilePosition[(*recognitionBB->getPileCount())++]);

	return NODE_STATUS::SUCCESS;
}


//=============================================================================
// 副処理：上空から落下するための目的を設定する
//=============================================================================
NODE_STATUS SubProcedureNode::setMovingDestinationToFall(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	std::list<MapNode*> memorizedMap = recognitionBB->getMemorizedMap();
	std::list<MapNode*>::iterator itr;
	std::list<MapNode*>::iterator dest;
	int numMaxWasuremono = 0;

	for (itr = memorizedMap.begin(); itr != memorizedMap.end(); itr++)
	{
		if ((*itr)->getWasuremonoCount() > numMaxWasuremono)
		{
			numMaxWasuremono = (*itr)->getWasuremonoCount();
			dest = itr;
		}
	}

	if (numMaxWasuremono != 0)
	{
		bodyBB->configMovingDestination((*dest)->getPosition());	// ワスレモノの多いノード
		recognitionBB->setWhetherFallingDestinationDecided(true);	// 落下時にステートマシンでfalseになる
		return NODE_STATUS::SUCCESS;
	}
	else
	{
		bodyBB->configMovingDestination(opponent->getPosition());	// 相手
		recognitionBB->setWhetherFallingDestinationDecided(true);	// 落下時にステートマシンでfalseになる
		return NODE_STATUS::FAILED;
	}
}


//=============================================================================
// 副処理：実行するリカージョン認識を設定する
//=============================================================================
NODE_STATUS SubProcedureNode::setRecursionRecognition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	// リカージョンが実行中なら失敗
	if (recognitionBB->getIsRecursionRunning()) { return NODE_STATUS::FAILED; }

	float largestWeight = 0.0f;				// 重み最大値
	float mostExpensiveAmout = 0.0f;		// 最大チンギン額 
	float leastRadius = 1000.0f;			// 最小半径
	int cntActiveRecursionRecognition = 0;	// 環境認識ブラックボードのリカージョン認識のうち有効なデータが入っている数
	int largestWeightRecognition = -1;		// 認識している中で最も採用ウェイトの思いリカージョン認識を示す
	int mostExpensiveRecognition = -1;		// 認識している中で最もチンギン額の多いリカージョン認識を示す
	int	leastRadiusRecognition = -1;		// 認識している中で最も半径の小さいリカージョン認識を示す

	// リカージョン方針ごとに認識をさがす
	for (int i = 0; i < NUM_RECURSION_RECOGNITION; i++)
	{
		// 非活性はパス
		if (recognitionBB->getIsActiveRecursionRecognition(i) == false) { continue; }

		cntActiveRecursionRecognition++;
		if (largestWeight < recognitionBB->getRecursionRecognition()[i].fuzzySelectionWeight)
		{
			largestWeight = recognitionBB->getRecursionRecognition()[i].fuzzySelectionWeight;
			largestWeightRecognition = i;
		}
		if (mostExpensiveAmout < recognitionBB->getRecursionRecognition()[i].totalAmount)
		{
			mostExpensiveAmout = recognitionBB->getRecursionRecognition()[i].totalAmount;
			mostExpensiveRecognition = i;
		}
		if (leastRadius > recognitionBB->getRecursionRecognition()[i].radius)
		{
			leastRadius = recognitionBB->getRecursionRecognition()[i].radius;
			leastRadiusRecognition = i;
		}
	}

	// 有効なリカージョン認識がない場合は失敗
	if (cntActiveRecursionRecognition == 0)
	{
		return NODE_STATUS::FAILED;
	}

	// 実行リカージョン認識として選ぶ
	switch (recognitionBB->getRecursionPolicy())
	{
	case LARGEST_WEIGHT:
		*recognitionBB->getRunningRecursion() = recognitionBB->getRecursionRecognition()[largestWeightRecognition];
		break;
	case MOST_EXPENSIVE:
		*recognitionBB->getRunningRecursion() = recognitionBB->getRecursionRecognition()[mostExpensiveRecognition];
		break;
	case LEAST_RADIUS:
		*recognitionBB->getRunningRecursion() = recognitionBB->getRecursionRecognition()[leastRadiusRecognition];
		break;
	}

	recognitionBB->setIsRecursionRunning(true);	// リカージョン実行中にセット
	return NODE_STATUS::SUCCESS;				// 成功
}


//=============================================================================
// 副処理：ショットターゲットを相手に設定
//=============================================================================
NODE_STATUS SubProcedureNode::setShootingTargetOpponent(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	bodyBB->setTargetCoordValue(*opponent->getPosition());
	return NODE_STATUS::SUCCESS;
}
