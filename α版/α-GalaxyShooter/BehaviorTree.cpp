//-----------------------------------------------------------------------------
// ビヘイビアツリー処理[BehaviorTree.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/18
//-----------------------------------------------------------------------------
#include "BehaviorTree.h"

//=============================================================================
// サンプルツリー1　オフェンス
//=============================================================================
void BehaviorTree::offense(void)
{
	addNode(OFFENSE, PARENT_IS_NOT_EXIST, PARARELL);
	addNode(OFFENSE, 0, SET_DESTINATION_OPPONENT);
	addNode(OFFENSE, 0, SEQUENCE);
	addNode(OFFENSE, 2, IF_THREE_SECONDS_LATER);
	addNode(OFFENSE, 2, ACTION_PILE);
	addNode(OFFENSE, 0, ACTION_MOVE);
}


//=============================================================================
// サンプルツリー1　ディフェンス
//=============================================================================
void BehaviorTree::deffense(void)
{
	addNode(DEFFENSE, PARENT_IS_NOT_EXIST, PARARELL);

	addNode(DEFFENSE, 0, SEQUENCE);
	addNode(DEFFENSE, 1, IF_FIVE_SECONDS_LATER);
	addNode(DEFFENSE, 1, SET_DESTINATION_RANDOM);
	addNode(DEFFENSE, 1, SET_TARGET_OPPONENT);
	addNode(DEFFENSE, 1, ACTION_SHOOT);

	addNode(DEFFENSE, 0, SEQUENCE);
	addNode(DEFFENSE, 6, IF_THREE_SECONDS_LATER);
	addNode(DEFFENSE, 6, ACTION_JUMP);

	addNode(DEFFENSE, 0, ACTION_MOVE);
}


//=============================================================================
// コンストラクタ
//=============================================================================
BehaviorTree::BehaviorTree(void)
{
	offense();
	deffense();
}


//=============================================================================
// デストラクタ
//=============================================================================
BehaviorTree::~BehaviorTree(void)
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
	NODE_TYPE nodeType;

	// 追加ノードタイプを判定
	if (_RULE_NODE_ < tag && tag < _CONDITIONAL_NODE_)
	{
		nodeType = RULE_NODE;
	}
	else if (_CONDITIONAL_NODE_ < tag && tag < _ACTION_NODE_)
	{
		nodeType = CONDITIONAL_NODE;
	}
	else if (_ACTION_NODE_ < tag && tag < _SUBPROCEDURE_NODE_)
	{
		nodeType = ACTION_NODE;
	}
	else
	{
		nodeType = SUBPROCEDURE_NODE;
	}

	// ノード生成
	switch (nodeType)
	{
	case RULE_NODE:
		if (new RuleNode(treeType, parentNumber, nodeType, tag) == NULL)
		{
			MessageBox(NULL, TEXT("メモリの確保に失敗しました。\nアプリケーションを終了します。"), TEXT("SystemError"), MB_OK);
			PostQuitMessage(0);
		}
		break;

	case CONDITIONAL_NODE:
		if (new ConditionalNode(treeType, parentNumber, nodeType, tag) == NULL)
		{
			MessageBox(NULL, TEXT("メモリの確保に失敗しました。\nアプリケーションを終了します。"), TEXT("SystemError"), MB_OK);
			PostQuitMessage(0);
		}
		break;

	case ACTION_NODE:
		if (new ActionNode(treeType, parentNumber, nodeType, tag) == NULL)
		{
			MessageBox(NULL, TEXT("メモリの確保に失敗しました。\nアプリケーションを終了します。"), TEXT("SystemError"), MB_OK);
			PostQuitMessage(0);
		}
		break;

	case SUBPROCEDURE_NODE:
		if (new SubProcedureNode(treeType, parentNumber, nodeType, tag) == NULL)
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
void BehaviorTree::run(int treeNumber, RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	BehaviorNodeBase::getRoot(treeNumber)->run(recognitionBB, memoryBB, bodyBB);
}