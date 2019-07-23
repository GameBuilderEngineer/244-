//-----------------------------------------------------------------------------
// ビヘイビアツリー アクションノード処理 [ActionNode.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/17
//-----------------------------------------------------------------------------
#pragma once
#include "BehaviorNodeBase.h"
using namespace BehaviorTreeNS;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class ActionNode: public BehaviorNodeBase
{
private:
	
public:
	ActionNode(int treeType, int parent, NODE_TAG);

	// 実行
	NODE_STATUS run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB, std::vector<BehaviorRecord> record);
};

