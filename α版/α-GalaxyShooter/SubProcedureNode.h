//-----------------------------------------------------------------------------
// ビヘイビアツリー サブプロシージャノード処理 [SubProcedureNode.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/23
//-----------------------------------------------------------------------------
#pragma once
#include "BehaviorNodeBase.h"
using namespace BehaviorTreeNS;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class SubProcedureNode: public BehaviorNodeBase
{
private:
	
public:
	SubProcedureNode(int treeType, int parent, NODE_TAG);
	// 実行
	NODE_STATUS run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB, std::vector<BehaviorRecord> record);
};

