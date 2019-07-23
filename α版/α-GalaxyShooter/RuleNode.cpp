//-----------------------------------------------------------------------------
// ビヘイビアツリー ルールノード処理 [RuleNode.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/17
//-----------------------------------------------------------------------------
#include "RuleNode.h"

//=============================================================================
// コンストラクタ
//=============================================================================
RuleNode::RuleNode(int treeType, int parentNumber, NODE_TAG tag): BehaviorNodeBase(treeType, parentNumber, tag)
{
		
}


//=============================================================================
// 実行
//=============================================================================
NODE_STATUS RuleNode::run(RecognitionBB* recognitionBB, 
	MemoryBB* memoryBB, BodyBB* bodyBB, std::vector<BehaviorRecord> record)
{
	// 実行可能な子ノードだけ集める
	std::vector<BehaviorNodeBase*> activeChild;
	for (int i = 0; i < childCount; i++)
	{
		if (child[i]->getExecutionJudgement() == false) continue;
		activeChild.push_back(child[i]);
	}

	// 実行する子ノードを選ぶ
	BehaviorNodeBase* searchNode = NULL;
	switch (tag)
	{
	case PRIORITY:
		searchNode = activeChild[0];
		break;

	case ON_OFF:
		break;

	case RANDOM:
		break;

	case SEQUENCE:
		searchNode = activeChild[0];
		break;

	case PARARELL:
		searchNode = activeChild[0];
		break;

	case CONDITIONAL:
		break;

	default:
		break;
	}

	// 子ノードを実行する
	NODE_STATUS result = _NOT_FOUND;
	bool isRepetition = false;
	int executedCount = 0;
	do {
		result = searchNode->run(recognitionBB, memoryBB, bodyBB, record);// 再帰処理
		executedCount++;

		// ルールごとに結果を処理する
		switch (tag)
		{
		case PRIORITY:
			searchNode = activeChild[executedCount];
			break;

		case ON_OFF:
			break;

		case RANDOM:
			break;

		case SEQUENCE:
			searchNode = activeChild[executedCount];
			break;

		case PARARELL:
			searchNode = activeChild[executedCount];
			break;

		case CONDITIONAL:
			break;

		default:
			break;
		}
	} while (isRepetition);

	// ノードを引き返す
	return result;
}


//
//BehaviorNodeBase* setNode(std::vector<BehaviorNodeBase*>& activeNode, int number)
//{
//	activeNode[0].nu
//	// 一番優先順位が高いノードを探す
//	for (int i = 0; i < activeChildCount; i++)
//	{
//		if(i < )
//
//	}
//}
//
//bool priority(NODE_STATUS& result, bool& isRepetition, std::vector<BehaviorNodeBase*>& activeNode)
//{
//	if (result == NODE_STATUS::SUCCESS)
//	{
//
//	}
//	else if (result == NODE_STATUS::FAILED)
//	{
//		// 次の優先子ノードを実行
//		re
//		(*data)[dataNo].step++;
//		*nextNode = *(++executedNode);
//		isRepetition = true;
//	}
//	else if (*result == NODE_RUNNING)
//	{
//		// 成功
//		*result = NODE_SUCCESS;
//	}
//
//	// 一つも子ノードを実行できていないので失敗
//	if ((*data)[dataNo].step == cntChild)
//	{
//		*result = NODE_FAILED;
//		isSameNodeRestart = FALSE;
//	}
//	break;
//}