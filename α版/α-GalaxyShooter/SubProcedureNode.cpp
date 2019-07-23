//-----------------------------------------------------------------------------
// ビヘイビアツリー サブプロシージャノード処理 [SubProcedureNode.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/23
//-----------------------------------------------------------------------------
#include "SubProcedureNode.h"
using namespace BehaviorTreeNS;

//=============================================================================
// コンストラクタ
//=============================================================================
SubProcedureNode::SubProcedureNode(int treeType, int parentNumber, NODE_TAG tag): BehaviorNodeBase(treeType, parentNumber, tag)
{

}


//=============================================================================
// 実行
//=============================================================================
NODE_STATUS SubProcedureNode::run(RecognitionBB* recognitionBB,
	MemoryBB* memoryBB, BodyBB* bodyBB, std::vector<BehaviorRecord> record)
{
	return NODE_STATUS::SUCCESS;
}
