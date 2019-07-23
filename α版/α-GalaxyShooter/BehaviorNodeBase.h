//-----------------------------------------------------------------------------
// ビヘイビアツリー ノード基底処理 [BehaviorNodeBase.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/17
//-----------------------------------------------------------------------------
#pragma once
#include "BehaviorTree.h"
#include "BlackBoardRecognition.h"
#include "BlackBoardMemory.h"
#include "BlackBoardBody.h"
#include <vector>
using namespace BehaviorTreeNS;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class BehaviorNodeBase
{
protected:
	NODE_TAG tag;					// ノードタグ
	int	number;						// ノード番号
	int	hierarchyNumber;			// ツリー階層番号
	bool executionJudgement;		// 実行判定
	NODE_STATUS status;				// 実行状態

	int siblingCount;				// 兄弟ノードの数
	int	childCount;					// 子ノードの数
	
	BehaviorNodeBase* parent;		// 親ノード
	BehaviorNodeBase* sibling;		// 兄弟ノード（先頭）
	BehaviorNodeBase** child;		// 子ノード
	BehaviorNodeBase* next;			// リストの次ノード

	// Static
	static BehaviorNodeBase* root[NUM_TREE];				// ルート
	static std::vector<BehaviorNodeBase*> list[NUM_TREE];	// リスト

public:
	// コンストラクタ
	BehaviorNodeBase(int treeType, int parentNumber, NODE_TAG tag);

	// ノード実行
	virtual NODE_STATUS run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB, std::vector<BehaviorRecord> record) = 0;

	//NODE_TAG getTag(void) { return tag; }
	bool getExecutionJudgement(void) { return executionJudgement; }
	//int getChildCount(void) { return childCount; }
	//BehaviorNodeBase** getChild(void) { return child; }

	// Static
	static BehaviorNodeBase* getRoot(int treeType) { return root[treeType]; }
	static std::vector<BehaviorNodeBase*> getList(int treeType) { return list[treeType]; }
};
