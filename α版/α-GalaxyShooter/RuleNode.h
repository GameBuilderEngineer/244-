//-----------------------------------------------------------------------------
// ビヘイビアツリー ルールノード処理 [RuleNode.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/17
//-----------------------------------------------------------------------------
#pragma once
#include "BehaviorNodeBase.h"
#include <vector>

struct ResultData
{
	NODE_STATUS status;
	bool isRepetition;
	int executedCount;
};

//*****************************************************************************
// クラス定義
//*****************************************************************************
class RuleNode: public BehaviorNodeBase
{
public:
	RuleNode(int treeType, int parent, NODE_TAG);
	// 実行
	NODE_STATUS run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB, std::vector<BehaviorRecord> record);
};

