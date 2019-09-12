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
	// Data
	int	currentTree;										// 現在の選択ツリー

	// Method
	void offense(void);										// オフェンスツリー
	void deffense(void);									// ディフェンスツリー
	void recursion(void);									// リカージョンツリー
	void recursionOpponent(void);							// リカージョンツリー（相手版）
	void down(void);										// ダウンツリー
	void sky(void);											// 上空モードツリー
	void fall(void);										// 落下ツリー

	//void switchTree(int treeType);						// ツリー切り替え
	void addNode(int parentNumber, NODE_TAG tag);			// ノードの追加

public:
	BehaviorTree(void);
	~BehaviorTree();
	// ビヘイビアツリーの実行
	void run(int treeNumber, RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};
