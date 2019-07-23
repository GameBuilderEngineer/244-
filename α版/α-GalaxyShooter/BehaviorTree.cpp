//-----------------------------------------------------------------------------
// ビヘイビアツリー処理[BehaviorTree.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/18
//-----------------------------------------------------------------------------
#include "BehaviorTree.h"
#include "BehaviorNodeBase.h"
#include "RuleNode.h"
#include "ActionNode.h"
#include "SubProcedureNode.h"

//*****************************************************************************
// 静的メンバ
//*****************************************************************************
BehaviorTree* BehaviorTree::instance;


//=============================================================================
// サンプルツリー
//=============================================================================
void BehaviorTree::sample(void)
{
	addNode(SAMPLE, -1, PRIORITY);

	addNode(SAMPLE, 0, PRIORITY);
	addNode(SAMPLE, 0, PRIORITY);
	addNode(SAMPLE, 0, PRIORITY);
	addNode(SAMPLE, 0, PRIORITY);


	addNode(SAMPLE, 4, PRIORITY);
	addNode(SAMPLE, 4, PRIORITY);
	addNode(SAMPLE, 0, PRIORITY);
	addNode(SAMPLE, 0, PRIORITY);
	addNode(SAMPLE, 0, PRIORITY);
	addNode(SAMPLE, 0, PRIORITY);
	addNode(SAMPLE, 0, PRIORITY);
	addNode(SAMPLE, 0, PRIORITY);
	addNode(SAMPLE, 0, PRIORITY);
	addNode(SAMPLE, 0, PRIORITY);
	addNode(SAMPLE, 0, PRIORITY);
	addNode(SAMPLE, 0, PRIORITY);
	addNode(SAMPLE, 0, PRIORITY);
	addNode(SAMPLE, 0, PRIORITY);
	addNode(SAMPLE, 0, PRIORITY);
	addNode(SAMPLE, 0, PRIORITY);
	addNode(SAMPLE, 0, PRIORITY);
	addNode(SAMPLE, 0, PRIORITY);
	addNode(SAMPLE, 0, PRIORITY);
	addNode(SAMPLE, 0, PRIORITY);
	addNode(SAMPLE, 0, PRIORITY);
	addNode(SAMPLE, 0, PRIORITY);
	addNode(SAMPLE, 0, PRIORITY);
	addNode(SAMPLE, 0, PRIORITY);
	addNode(SAMPLE, 0, PRIORITY);

}


//=============================================================================
// コンストラクタ
//=============================================================================
BehaviorTree::BehaviorTree(void)
{
	sample();
}


//=============================================================================
// デストラクタ
//=============================================================================
BehaviorTree::~BehaviorTree()
{
	for (int treeNumber = 0; treeNumber < NUM_TREE; treeNumber++)
	{
		std::vector<BehaviorNodeBase*> list = BehaviorNodeBase::getList(treeNumber);

		for (size_t i = 0; i < list.size(); i++)
		{
			delete list[i];
		}

		list.clear();
	}
}


//=============================================================================
// ノードを追加
//=============================================================================
void BehaviorTree::addNode(int treeType, int parentNumber, NODE_TAG tag)
{
	int nodeType;

	// 追加ノードタイプを判定
	if (_RULE_NODE < tag && _ACTION_NODE)
	{
		nodeType = _RULE_NODE;
	}
	else if (_ACTION_NODE < tag && _SUBPROCEDURE_NODE)
	{
		nodeType = _ACTION_NODE;
	}
	else
	{
		nodeType = _SUBPROCEDURE_NODE;
	}

	// ノード生成
	switch (nodeType)
	{
	case _RULE_NODE:
		if (new RuleNode(treeType, parentNumber, tag) == NULL)
		{
			MessageBox(NULL, TEXT("メモリの確保に失敗しました。\nアプリケーションを終了します。"), TEXT("SystemError"), MB_OK);
			PostQuitMessage(0);
		}
		break;

	case _ACTION_NODE:
		if (new ActionNode(treeType, parentNumber, tag) == NULL)
		{
			MessageBox(NULL, TEXT("メモリの確保に失敗しました。\nアプリケーションを終了します。"), TEXT("SystemError"), MB_OK);
			PostQuitMessage(0);
		}
		break;

	case _SUBPROCEDURE_NODE:
		if (new SubProcedureNode(treeType, parentNumber, tag) == NULL)
		{
			MessageBox(NULL, TEXT("メモリの確保に失敗しました。\nアプリケーションを終了します。"), TEXT("SystemError"), MB_OK);
			PostQuitMessage(0);
		}
		break;
	}
}


//=============================================================================
// ビヘイビアツリーの実行
//=============================================================================
void BehaviorTree::run(int treeNumber, RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB, std::vector<BehaviorRecord> record)
{
	BehaviorNodeBase::getRoot(treeNumber)->run(recognitionBB, memoryBB, bodyBB, record);

	for (size_t i = 0; i < record.size(); i++)
	{
		record[i].setStep(0);
	}
}
