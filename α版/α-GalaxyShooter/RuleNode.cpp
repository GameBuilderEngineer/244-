//-----------------------------------------------------------------------------
// �r�w�C�r�A�c���[ ���[���m�[�h���� [RuleNode.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/17
//-----------------------------------------------------------------------------
#include "RuleNode.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
RuleNode::RuleNode(int treeType, int parentNumber, NODE_TAG tag): BehaviorNodeBase(treeType, parentNumber, tag)
{
		
}


//=============================================================================
// ���s
//=============================================================================
NODE_STATUS RuleNode::run(RecognitionBB* recognitionBB, 
	MemoryBB* memoryBB, BodyBB* bodyBB, std::vector<BehaviorRecord> record)
{
	// ���s�\�Ȏq�m�[�h�����W�߂�
	std::vector<BehaviorNodeBase*> activeChild;
	for (int i = 0; i < childCount; i++)
	{
		if (child[i]->getExecutionJudgement() == false) continue;
		activeChild.push_back(child[i]);
	}

	// ���s����q�m�[�h��I��
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

	// �q�m�[�h�����s����
	NODE_STATUS result = _NOT_FOUND;
	bool isRepetition = false;
	int executedCount = 0;
	do {
		result = searchNode->run(recognitionBB, memoryBB, bodyBB, record);// �ċA����
		executedCount++;

		// ���[�����ƂɌ��ʂ���������
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

	// �m�[�h�������Ԃ�
	return result;
}


//
//BehaviorNodeBase* setNode(std::vector<BehaviorNodeBase*>& activeNode, int number)
//{
//	activeNode[0].nu
//	// ��ԗD�揇�ʂ������m�[�h��T��
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
//		// ���̗D��q�m�[�h�����s
//		re
//		(*data)[dataNo].step++;
//		*nextNode = *(++executedNode);
//		isRepetition = true;
//	}
//	else if (*result == NODE_RUNNING)
//	{
//		// ����
//		*result = NODE_SUCCESS;
//	}
//
//	// ����q�m�[�h�����s�ł��Ă��Ȃ��̂Ŏ��s
//	if ((*data)[dataNo].step == cntChild)
//	{
//		*result = NODE_FAILED;
//		isSameNodeRestart = FALSE;
//	}
//	break;
//}