//-----------------------------------------------------------------------------
// ビヘイビアツリー ルールノード処理 [RuleNode.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/17
//-----------------------------------------------------------------------------
#include "RuleNode.h"

//=============================================================================
// コンストラクタ
//=============================================================================
RuleNode::RuleNode(int treeType, int parentNumber, NODE_TYPE type, NODE_TAG tag): BehaviorNodeBase(treeType, parentNumber,type, tag)
{
		
}


//=============================================================================
// 実行
//=============================================================================
NODE_STATUS RuleNode::run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	// 実行可能な子ノードだけ集める
	std::vector<BehaviorNodeBase*> activeChild;
	for (int i = 0; i < child.size(); i++)
	{
		if (child[i]->getExecutionJudgement() == false) { continue; }
		activeChild.push_back(child[i]);
	}
	if (activeChild.size() == 0)
	{
		return NODE_STATUS::_NOT_FOUND;
	}

	// 実行する子ノードを選ぶ
	BehaviorNodeBase* searchNode = NULL;
	switch (tag)
	{
	case PRIORITY:
		searchNode = activeChild[0];
		break;

	case ON_OFF:
		searchNode = onOffSelect(activeChild, memoryBB);
		break;

	case RANDOM:
		searchNode = randomSelect(activeChild);
		break;

	case SEQUENCE:
		searchNode = activeChild[0];
		break;

	case PARARELL:
		searchNode = activeChild[0];
		break;
	}

	// 子ノードを実行する
	NODE_STATUS result = _NOT_FOUND;
	bool isRepetition = false;
	int executedCount = 0;
	do {
		// 再帰実行
		result = searchNode->run(recognitionBB, memoryBB, bodyBB);
		executedCount++;

		// 子が条件ノードで結果が偽なら同階層ノードはこれ以上実行しない
		if (searchNode->getType() == CONDITIONAL_NODE && result == NODE_STATUS::FAILED) { break; }

		// ルールごとに結果を処理する
		switch (tag)
		{
		case PRIORITY:
			priorityWork(result, isRepetition, executedCount, searchNode, activeChild);
			break;

		case ON_OFF:
			onOffWork(result, isRepetition, executedCount, searchNode, activeChild, memoryBB);
			break;

		case RANDOM:
			randomWork(result, isRepetition, executedCount, searchNode, activeChild);
			break;

		case SEQUENCE:
			sequenceWork(result, isRepetition, executedCount, searchNode, activeChild);
			break;

		case PARARELL:
			pararellWork(result, isRepetition, executedCount, searchNode, activeChild);
			break;
		}
	} while (isRepetition);

	// ノードを引き返す
	return result;
}


//=============================================================================
// ON_OFFノードが子ノードを選択
//=============================================================================
BehaviorNodeBase* RuleNode::onOffSelect(std::vector<BehaviorNodeBase*>& activeChild, MemoryBB* memoryBB)
{
	if (memoryBB->getOnOffRecord()[this] > activeChild.size() - 1)
	{
		memoryBB->getOnOffRecord()[this] = 0;
	}
	return activeChild[memoryBB->getOnOffRecord()[this]++];
}


//=============================================================================
// RANDOMノードが子ノードを選択
//=============================================================================
BehaviorNodeBase* RuleNode::randomSelect(std::vector<BehaviorNodeBase*>& activeChild)
{
	int select = rand() % activeChild.size();
	return activeChild[select];
}


//=============================================================================
// PRIORITYノードの実行結果処理
//=============================================================================
void RuleNode::priorityWork(NODE_STATUS& result, bool& isRepetition, int& executedCount,
	BehaviorNodeBase*& searchNode, std::vector<BehaviorNodeBase*>& activeChild)
{
	switch (result)
	{
	case NODE_STATUS::SUCCESS:
		isRepetition = false;
		break;

	case NODE_STATUS::FAILED:
		if (executedCount < activeChild.size())
		{// activeChildの数以上は実行しない
			searchNode = activeChild[executedCount];
			isRepetition = true;
		}
		if (executedCount == activeChild.size())
		{// 一つも子ノードを実行できていないので失敗
			result = NODE_STATUS::FAILED;
			isRepetition = false;
		}
		break;

	case NODE_STATUS::RUNNING:
		result = NODE_STATUS::SUCCESS;
		isRepetition = false;
		break;

	case NODE_STATUS::_NOT_FOUND:
		MessageBox(NULL, TEXT("(PRIORITY)子ノードが_NOT_FOUNDを返しました"), TEXT("Behavior Tree Error"), MB_OK);
		break;
	}
}


//=============================================================================
// ON_OFFノードの実行結果処理
//=============================================================================
void RuleNode::onOffWork(NODE_STATUS& result, bool& isRepetition, int& executedCount,
	BehaviorNodeBase*& searchNode, std::vector<BehaviorNodeBase*>& activeChild, MemoryBB* memoryBB)
{
	switch (result)
	{
	case NODE_STATUS::SUCCESS:
		isRepetition = false;
		break;

	case NODE_STATUS::FAILED:
		if (executedCount < activeChild.size())
		{// activeChildの数以上は実行しない
			searchNode = onOffSelect(activeChild, memoryBB);
			isRepetition = true;
		}
		if (executedCount == activeChild.size())
		{// 一つも子ノードを実行できていないので失敗
			result = NODE_STATUS::FAILED;
			isRepetition = false;
		}
		break;

	case NODE_STATUS::RUNNING:
		result = NODE_STATUS::SUCCESS;
		isRepetition = false;
		break;

	case NODE_STATUS::_NOT_FOUND:
		MessageBox(NULL, TEXT("(ON_OFF)子ノードが_NOT_FOUNDを返しました"), TEXT("Behavior Tree Error"), MB_OK);
		break;
	}
}


//=============================================================================
// RANDOMノードの実行結果処理
//=============================================================================
void RuleNode::randomWork(NODE_STATUS& result, bool& isRepetition, int& executedCount,
	BehaviorNodeBase*& searchNode, std::vector<BehaviorNodeBase*>& activeChild)
{
	switch (result)
	{
	case NODE_STATUS::SUCCESS:
		isRepetition = false;
		break;

	case NODE_STATUS::FAILED:
		isRepetition = false;
		break;

	case NODE_STATUS::RUNNING:
		result = NODE_STATUS::SUCCESS;
		isRepetition = false;
		break;

	case NODE_STATUS::_NOT_FOUND:
		MessageBox(NULL, TEXT("(RANDOM)子ノードが_NOT_FOUNDを返しました"), TEXT("Behavior Tree Error"), MB_OK);
		break;
	}
}


//=============================================================================
// SEQUENCEノードの実行結果処理
//=============================================================================
void RuleNode::sequenceWork(NODE_STATUS& result, bool& isRepetition, int& executedCount,
	BehaviorNodeBase*& searchNode, std::vector<BehaviorNodeBase*>& activeChild)
{
	switch (result)
	{
	case NODE_STATUS::SUCCESS:
	case NODE_STATUS::RUNNING:
		result = NODE_STATUS::RUNNING;
		if (executedCount < activeChild.size())
		{// activeChildの数以上は実行しない
			searchNode = activeChild[executedCount];
			isRepetition = true;
		}
		break;

	case NODE_STATUS::FAILED:
		isRepetition = false;
		break;

	case NODE_STATUS::_NOT_FOUND:
		MessageBox(NULL, TEXT("(SEQUENCE)子ノードが_NOT_FOUNDを返しました"), TEXT("Behavior Tree Error"), MB_OK);
		break;
	}

	// 全ての子ノードを実行し終えたら成功
	if (executedCount == activeChild.size())
	{
		result = NODE_STATUS::SUCCESS;
		isRepetition = false;
	}
}


//=============================================================================
// PARARELLノードの実行結果処理
//=============================================================================
void RuleNode::pararellWork(NODE_STATUS& result, bool& isRepetition, int& executedCount,
	BehaviorNodeBase*& searchNode, std::vector<BehaviorNodeBase*>& activeChild)
{
	switch (result)
	{
	case NODE_STATUS::SUCCESS:
	case NODE_STATUS::FAILED:
	case NODE_STATUS::RUNNING:
		result = NODE_STATUS::RUNNING;
		if (executedCount < activeChild.size())
		{// activeChildの数以上は実行しない
			searchNode = activeChild[executedCount];
			isRepetition = true;
		}
		break;

	case NODE_STATUS::_NOT_FOUND:
		MessageBox(NULL, TEXT("(PARARELL)子ノードが_NOT_FOUNDを返しました"), TEXT("Behavior Tree Error"), MB_OK);
		break;
	}

	// 全ての子ノードを実行し終えたら成功
	if (executedCount == activeChild.size())
	{
		result = NODE_STATUS::SUCCESS;
		isRepetition = false;
	}
}
