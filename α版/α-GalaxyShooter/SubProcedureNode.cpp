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
	case SET_DESTINATION_OPPONENT:				return setMovingDestinationOpponent(recognitionBB, memoryBB, bodyBB);
	case SET_DESTINATION_RANDOM:				return setMovingDestinationRandom(recognitionBB, memoryBB, bodyBB);
	case SET_DESTINATION_NEXT_PILE:				return setMovingDestinationNextPile(recognitionBB, memoryBB, bodyBB);
	case SET_DESTINATION_TO_RECUASION:			return setMovingDestinationToRecuasion(recognitionBB, memoryBB, bodyBB);
	case SET_DESTINATION_TO_CUT_LINE:			return setMovingDestinationToCutLine(recognitionBB, memoryBB, bodyBB);
	case SET_TARGET_OPPONENT:					return setShootingTargetOpponent(recognitionBB, memoryBB, bodyBB);
	case SET_RECURSION_RECOGNITION:				return setRecursionRecognition(recognitionBB, memoryBB, bodyBB);
	case SET_RECURSION_RECOGNITION_FOR_OPPONENT:return setRecursionRecognitionForOpponent(recognitionBB, memoryBB, bodyBB);
	case SET_RECUASION_STATE:					return setRecursionState(recognitionBB, memoryBB, bodyBB);
	case SET_RECUASION_OPPONENT_STATE:			return setRecursionStateForOpponent(recognitionBB, memoryBB, bodyBB);
	case SET_BULLET_SWITCH:						return setBulletSwith(recognitionBB, memoryBB, bodyBB);
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
	//if (recognitionBB->getWhetherDestinationDecided()) { return NODE_STATUS::RUNNING; }

	int number = rand() % Map::getMapNode().size();
	D3DXVECTOR3* newDestination = Map::getMapNode()[number]->getPosition();
	bodyBB->configMovingDestination(Map::getMapNode()[number]->getPosition());

	recognitionBB->setWhetherDestinationDecided(true);
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
		&recognitionBB->getRunningRecursion()->pilePosition[recognitionBB->getElementMemoryPile()]);

	return NODE_STATUS::SUCCESS;
}


//=============================================================================
// 副処理：リカージョンするための目的地を設定する
//=============================================================================
NODE_STATUS SubProcedureNode::setMovingDestinationToRecuasion(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	//if (recognitionBB->getWhetherDestinationDecided()) { return NODE_STATUS::RUNNING; }

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
		recognitionBB->setWhetherDestinationDecided(true);
		return NODE_STATUS::SUCCESS;
	}
	else
	{
		return NODE_STATUS::FAILED;
	}
}


//=============================================================================
// 副処理：メモリーラインを切る座標を目的地に設定する
//=============================================================================
NODE_STATUS SubProcedureNode::setMovingDestinationToCutLine(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	bodyBB->setIsArrival(false);
	bodyBB->configMovingDestination(recognitionBB->getLineCutCoordPointer());
	return NODE_STATUS::SUCCESS;
}


//=============================================================================
// 副処理：実行するリカージョン認識を設定する
//=============================================================================
NODE_STATUS SubProcedureNode::setRecursionRecognition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	// リカージョンが実行中ならRUNNING
	if (recognitionBB->getIsRecursionRunning()) { return NODE_STATUS::RUNNING; }

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

	recognitionBB->setIsRecursionRunning(true);						// リカージョン実行中にセット
	setMovingDestinationNextPile(recognitionBB, memoryBB, bodyBB);	// 最初の目的地を入れる
	return NODE_STATUS::SUCCESS;									// 成功
}


//=============================================================================
// 副処理：実行するリカージョン認識（相手）を設定する
//=============================================================================
NODE_STATUS SubProcedureNode::setRecursionRecognitionForOpponent(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	// リカージョンが実行中ならRUNNING
	if (recognitionBB->getIsRecursionRunning()) { return NODE_STATUS::RUNNING; }

	*recognitionBB->getRunningRecursion() = *recognitionBB->getRecursionRecognitionForOpponent();
	recognitionBB->setIsRecursionRunning(true);						// リカージョン実行中にセット
	setMovingDestinationNextPile(recognitionBB, memoryBB, bodyBB);	// 最初の目的地を入れる
	return NODE_STATUS::SUCCESS;									// 成功
}


//=============================================================================
// 副処理：リカージョンステートをセット（遷移）
//=============================================================================
NODE_STATUS SubProcedureNode::setRecursionState(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	recognitionBB->setIsStartRecursion(true);
	return NODE_STATUS::SUCCESS;
}


//=============================================================================
// 副処理：リカージョンステートをセット（遷移）
//=============================================================================
NODE_STATUS SubProcedureNode::setRecursionStateForOpponent(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
 	recognitionBB->setIsStartRecursionForOpponent(true);
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


//=============================================================================
// 副処理：バレットの発射切り替え
//=============================================================================
NODE_STATUS SubProcedureNode::setBulletSwith(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	recognitionBB->changeBulletSwitch();
	return NODE_STATUS::SUCCESS;
}
