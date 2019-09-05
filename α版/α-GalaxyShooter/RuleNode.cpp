//-----------------------------------------------------------------------------
// �r�w�C�r�A�c���[ ���[���m�[�h���� [RuleNode.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/17
//-----------------------------------------------------------------------------
#include "RuleNode.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
RuleNode::RuleNode(int treeType, int parentNumber, NODE_TYPE type, NODE_TAG tag): BehaviorNodeBase(treeType, parentNumber,type, tag)
{
		
}


//=============================================================================
// ���s
//=============================================================================
NODE_STATUS RuleNode::run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	// ���s�\�Ȏq�m�[�h�����W�߂�
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

	// ���s����q�m�[�h��I��
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

	// �q�m�[�h�����s����
	NODE_STATUS result = _NOT_FOUND;
	bool isRepetition = false;
	int executedCount = 0;
	do {
		// �ċA���s
		result = searchNode->run(recognitionBB, memoryBB, bodyBB);
		executedCount++;

		// �q�������m�[�h�Ō��ʂ��U�Ȃ瓯�K�w�m�[�h�͂���ȏ���s���Ȃ�
		if (searchNode->getType() == CONDITIONAL_NODE && result == NODE_STATUS::FAILED) { break; }

		// ���[�����ƂɌ��ʂ���������
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

	// �m�[�h�������Ԃ�
	return result;
}


//=============================================================================
// ON_OFF�m�[�h���q�m�[�h��I��
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
// RANDOM�m�[�h���q�m�[�h��I��
//=============================================================================
BehaviorNodeBase* RuleNode::randomSelect(std::vector<BehaviorNodeBase*>& activeChild)
{
	int select = rand() % activeChild.size();
	return activeChild[select];
}


//=============================================================================
// PRIORITY�m�[�h�̎��s���ʏ���
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
		{// activeChild�̐��ȏ�͎��s���Ȃ�
			searchNode = activeChild[executedCount];
			isRepetition = true;
		}
		if (executedCount == activeChild.size())
		{// ����q�m�[�h�����s�ł��Ă��Ȃ��̂Ŏ��s
			result = NODE_STATUS::FAILED;
			isRepetition = false;
		}
		break;

	case NODE_STATUS::RUNNING:
		result = NODE_STATUS::SUCCESS;
		isRepetition = false;
		break;

	case NODE_STATUS::_NOT_FOUND:
		MessageBox(NULL, TEXT("(PRIORITY)�q�m�[�h��_NOT_FOUND��Ԃ��܂���"), TEXT("Behavior Tree Error"), MB_OK);
		break;
	}

}


//=============================================================================
// ON_OFF�m�[�h�̎��s���ʏ���
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
		{// activeChild�̐��ȏ�͎��s���Ȃ�
			searchNode = onOffSelect(activeChild, memoryBB);
			isRepetition = true;
		}
		if (executedCount == activeChild.size())
		{// ����q�m�[�h�����s�ł��Ă��Ȃ��̂Ŏ��s
			result = NODE_STATUS::FAILED;
			isRepetition = false;
		}
		break;

	case NODE_STATUS::RUNNING:
		result = NODE_STATUS::SUCCESS;
		isRepetition = false;
		break;

	case NODE_STATUS::_NOT_FOUND:
		MessageBox(NULL, TEXT("(ON_OFF)�q�m�[�h��_NOT_FOUND��Ԃ��܂���"), TEXT("Behavior Tree Error"), MB_OK);
		break;
	}
}


//=============================================================================
// RANDOM�m�[�h�̎��s���ʏ���
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
		MessageBox(NULL, TEXT("(RANDOM)�q�m�[�h��_NOT_FOUND��Ԃ��܂���"), TEXT("Behavior Tree Error"), MB_OK);
		break;
	}
}


//=============================================================================
// SEQUENCE�m�[�h�̎��s���ʏ���
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
		{// activeChild�̐��ȏ�͎��s���Ȃ�
			searchNode = activeChild[executedCount];
			isRepetition = true;
		}
		break;

	case NODE_STATUS::FAILED:
		isRepetition = false;
		break;

	case NODE_STATUS::_NOT_FOUND:
		MessageBox(NULL, TEXT("(SEQUENCE)�q�m�[�h��_NOT_FOUND��Ԃ��܂���"), TEXT("Behavior Tree Error"), MB_OK);
		break;
	}

	// �S�Ă̎q�m�[�h�����s���I�����琬��
	if (executedCount == activeChild.size())
	{
		result = NODE_STATUS::SUCCESS;
		isRepetition = false;
	}
}


//=============================================================================
// PARARELL�m�[�h�̎��s���ʏ���
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
		{// activeChild�̐��ȏ�͎��s���Ȃ�
			searchNode = activeChild[executedCount];
			isRepetition = true;
		}
		break;

	case NODE_STATUS::_NOT_FOUND:
		MessageBox(NULL, TEXT("(PARARELL)�q�m�[�h��_NOT_FOUND��Ԃ��܂���"), TEXT("Behavior Tree Error"), MB_OK);
		break;
	}

	// �S�Ă̎q�m�[�h�����s���I�����琬��
	if (executedCount == activeChild.size())
	{
		result = NODE_STATUS::SUCCESS;
		isRepetition = false;
	}
}
