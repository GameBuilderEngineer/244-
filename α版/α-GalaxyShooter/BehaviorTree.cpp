//-----------------------------------------------------------------------------
// ビヘイビアツリー処理[BehaviorTree.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/18
//-----------------------------------------------------------------------------
#include "BehaviorTree.h"

//=============================================================================
// オフェンスツリー
//=============================================================================
void BehaviorTree::offense(void)
{
	currentTree = OFFENSE_TREE;

	addNode(PARENT_IS_NOT_EXIST, PARARELL);
	//addNode(0, SET_DESTINATION_OPPONENT);
	//addNode(0, SET_TARGET_OPPONENT);
	//addNode(0, SEQUENCE);
	//addNode(3, ACTION_MOVE);
	//addNode(3, ACTION_SHOOT);
}


//=============================================================================
// ディフェンスツリー
//=============================================================================
void BehaviorTree::deffense(void)
{
	currentTree = DEFFENSE_TREE;


	addNode(PARENT_IS_NOT_EXIST, PARARELL);

	addNode(0, IF_BULLET_NEAR);
	addNode(0, ACTION_JUMP);

	//addNode(0, SEQUENCE);
	//addNode(1, IF_FIVE_SECONDS_LATER);
	//addNode(1, SET_DESTINATION_RANDOM);
	//addNode(1, SET_TARGET_OPPONENT);
	//addNode(1, ACTION_SHOOT);

	//addNode(0, SEQUENCE);
	//addNode(6, IF_THREE_SECONDS_LATER);
	//addNode(6, ACTION_JUMP);

	//addNode(0, ACTION_MOVE);
}


//=============================================================================
// リカージョンツリー
//=============================================================================
void BehaviorTree::recursion(void)
{
	currentTree = RECURSION_TREE;

	addNode(PARENT_IS_NOT_EXIST, PARARELL);
	addNode(0, SEQUENCE);
	addNode(0, IF_RECURSION_IS_RUNNING);
	addNode(0, PRIORITY);
	addNode(1, SET_RECURSION_RECOGNITION);
	addNode(1, SET_DESTINATION_NEXT_PILE);
	addNode(3, ACTION_MOVE);
	addNode(3, SEQUENCE);
	addNode(7, ACTION_PILE);
	addNode(7, SET_DESTINATION_NEXT_PILE);
}

//=============================================================================
// ダウンツリー
//=============================================================================
void BehaviorTree::down(void)
{
	currentTree = DOWN_TREE;

	addNode(PARENT_IS_NOT_EXIST, PARARELL);
	addNode(0, ACTION_REVIVAL);
}


//=============================================================================
// 上空モードツリー
//=============================================================================
void BehaviorTree::sky(void)
{
	currentTree = SKY_TREE;

	addNode(PARENT_IS_NOT_EXIST, PRIORITY);
	addNode(0, SEQUENCE);
	addNode(0, SEQUENCE);

	addNode(1, IF_FALLING_DEST_DECIDED);
	addNode(1, ACTION_MOVE);

	addNode(2, IF_ONE_SECOND_LATER);
	addNode(2, SET_DESTINATION_TO_FALL);
}


//=============================================================================
// 落下中ツリー
//=============================================================================
void BehaviorTree::fall(void)
{
	currentTree = FALL_TREE;
	addNode(PARENT_IS_NOT_EXIST, PARARELL);
}


//=============================================================================
// コンストラクタ
//=============================================================================
BehaviorTree::BehaviorTree(void)
{
	currentTree = -1;// 未選択

	offense();
	deffense();
	recursion();
	down();
	sky();
	fall();
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
void BehaviorTree::addNode(int parentNumber, NODE_TAG tag)
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
		if (new RuleNode(currentTree, parentNumber, nodeType, tag) == NULL)
		{
			MessageBox(NULL, TEXT("メモリの確保に失敗しました。\nアプリケーションを終了します。"), TEXT("SystemError"), MB_OK);
			PostQuitMessage(0);
		}
		break;

	case CONDITIONAL_NODE:
		if (new ConditionalNode(currentTree, parentNumber, nodeType, tag) == NULL)
		{
			MessageBox(NULL, TEXT("メモリの確保に失敗しました。\nアプリケーションを終了します。"), TEXT("SystemError"), MB_OK);
			PostQuitMessage(0);
		}
		break;

	case ACTION_NODE:
		if (new ActionNode(currentTree, parentNumber, nodeType, tag) == NULL)
		{
			MessageBox(NULL, TEXT("メモリの確保に失敗しました。\nアプリケーションを終了します。"), TEXT("SystemError"), MB_OK);
			PostQuitMessage(0);
		}
		break;

	case SUBPROCEDURE_NODE:
		if (new SubProcedureNode(currentTree, parentNumber, nodeType, tag) == NULL)
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