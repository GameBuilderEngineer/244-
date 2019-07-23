//-----------------------------------------------------------------------------
// ビヘイビアツリー処理[BehaviorTree.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/18
//-----------------------------------------------------------------------------
#pragma once
#include <vector>
#include "Base.h"
#include "BehaviorRecord.h"
#include "StateMachine.h"

//*****************************************************************************
// 定数定義
//*****************************************************************************
namespace BehaviorTreeNS
{
	// ビヘイビアツリー
	enum TREE
	{
		TREE_INDEX,					// 0
		SAMPLE = 0,					// サンプルツリー
		NUM_TREE					// ビヘイビアツリーの数
	};

	// ノードのタグ
	enum NODE_TAG
	{
		_RULE_NODE,					// ルールノード
		PRIORITY,					// 優先順位リスト法
		ON_OFF,						// オン・オフ法
		RANDOM,						// ランダム法
		SEQUENCE,					// シークエンス法
		PARARELL,					// パラレル法
		CONDITIONAL,				// 条件ノード

		_ACTION_NODE,				// アクションノード
		D,
		E,
		F,

		_SUBPROCEDURE_NODE,			// 副処理ノード
		G,
		H,
		I,

		NUM_NODE_TAG				// タグの数
	};

	// ノードの実行結果
	enum NODE_STATUS
	{
		SUCCESS,					// 実行成功
		FAILED,						// 実行失敗
		RUNNING,					// 実行中
		_NOT_FOUND = -1				// ノードが存在しない
	};

	const int PARENT_IS_NOT_EXIST = -1;
}


using namespace BehaviorTreeNS;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class BehaviorTree
{
private:
	// Data
	static BehaviorTree* instance;	// インスタンスへのポインタ

	// Method
	BehaviorTree(void);
	~BehaviorTree();
	void sample(void);														// サンプルツリー
	void addNode(int treeType, int parentNumber, NODE_TAG tag);				// ノードの追加

public:
	static void create(void) { if (!instance)instance = new BehaviorTree; }	// インスタンス生成
	static void destroy(void) { SAFE_DELETE(instance) }						// インスタンス破棄
	static BehaviorTree* getInstance(void) { return instance; }				// インスタンス取得
	// ビヘイビアツリーの実行
	void run(int treeNumber, RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB, std::vector<BehaviorRecord> record);
};
