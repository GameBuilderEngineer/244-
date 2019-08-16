//-----------------------------------------------------------------------------
// �r�w�C�r�A�c���[����[BehaviorTree.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/18
//-----------------------------------------------------------------------------
#include "BehaviorTree.h"

//=============================================================================
// �T���v���c���[1�@�I�t�F���X
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
// �T���v���c���[1�@�f�B�t�F���X
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
// �R���X�g���N�^
//=============================================================================
BehaviorTree::BehaviorTree(void)
{
	offense();
	deffense();
}


//=============================================================================
// �f�X�g���N�^
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
// �m�[�h��ǉ�
//=============================================================================
void BehaviorTree::addNode(int treeType, int parentNumber, NODE_TAG tag)
{
	NODE_TYPE nodeType;

	// �ǉ��m�[�h�^�C�v�𔻒�
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

	// �m�[�h����
	switch (nodeType)
	{
	case RULE_NODE:
		if (new RuleNode(treeType, parentNumber, nodeType, tag) == NULL)
		{
			MessageBox(NULL, TEXT("�������̊m�ۂɎ��s���܂����B\n�A�v���P�[�V�������I�����܂��B"), TEXT("SystemError"), MB_OK);
			PostQuitMessage(0);
		}
		break;

	case CONDITIONAL_NODE:
		if (new ConditionalNode(treeType, parentNumber, nodeType, tag) == NULL)
		{
			MessageBox(NULL, TEXT("�������̊m�ۂɎ��s���܂����B\n�A�v���P�[�V�������I�����܂��B"), TEXT("SystemError"), MB_OK);
			PostQuitMessage(0);
		}
		break;

	case ACTION_NODE:
		if (new ActionNode(treeType, parentNumber, nodeType, tag) == NULL)
		{
			MessageBox(NULL, TEXT("�������̊m�ۂɎ��s���܂����B\n�A�v���P�[�V�������I�����܂��B"), TEXT("SystemError"), MB_OK);
			PostQuitMessage(0);
		}
		break;

	case SUBPROCEDURE_NODE:
		if (new SubProcedureNode(treeType, parentNumber, nodeType, tag) == NULL)
		{
			MessageBox(NULL, TEXT("�������̊m�ۂɎ��s���܂����B\n�A�v���P�[�V�������I�����܂��B"), TEXT("SystemError"), MB_OK);
			PostQuitMessage(0);
		}
		break;
	}
}


//=============================================================================
// �r�w�C�r�A�c���[�̎��s
//=============================================================================
void BehaviorTree::run(int treeNumber, RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	BehaviorNodeBase::getRoot(treeNumber)->run(recognitionBB, memoryBB, bodyBB);
}