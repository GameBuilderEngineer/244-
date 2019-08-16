//-----------------------------------------------------------------------------
// ビヘイビアツリー処理[BehaviorTree.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/18
//-----------------------------------------------------------------------------
#pragma once
#include <vector>
#include "Base.h"
#include "SubProcedureNode.h"
#include "RuleNode.h"
#include "ActionNode.h"
#include "ConditionalNode.h"

//*****************************************************************************
// 定数定義
//*****************************************************************************


//*****************************************************************************
// クラス定義
//*****************************************************************************
class BehaviorTree
{
private:
	void offense(void);												// サンプルツリー1
	void deffense(void);											// サンプルツリー2
	void addNode(int treeType, int parentNumber, NODE_TAG tag);		// ノードの追加

public:
	BehaviorTree(void);
	~BehaviorTree();
	// ビヘイビアツリーの実行
	void run(int treeNumber, RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};
