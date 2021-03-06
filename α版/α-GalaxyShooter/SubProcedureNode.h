//-----------------------------------------------------------------------------
// ビヘイビアツリー サブプロシージャノード処理 [SubProcedureNode.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/23
//-----------------------------------------------------------------------------
#pragma once
#include "BehaviorNodeBase.h"
#include "Map.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class SubProcedureNode: public BehaviorNodeBase
{
private:
	NODE_STATUS subProcedureList(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	NODE_STATUS setMovingDestinationOpponent(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	NODE_STATUS setMovingDestinationRandom(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	NODE_STATUS setMovingDestinationNextPile(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	NODE_STATUS setMovingDestinationToRecuasion(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	NODE_STATUS setMovingDestinationToCutLine(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	NODE_STATUS setRecursionRecognition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	NODE_STATUS setRecursionRecognitionForOpponent(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	NODE_STATUS setRecursionState(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	NODE_STATUS setRecursionStateForOpponent(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	NODE_STATUS setShootingTargetOpponent(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
	NODE_STATUS setBulletSwith(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);



public:
	SubProcedureNode(int treeType, int parent, NODE_TYPE type, NODE_TAG tag);

	// 実行
	NODE_STATUS run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};
