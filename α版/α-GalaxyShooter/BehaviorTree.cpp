//-----------------------------------------------------------------------------
// �r�w�C�r�A�c���[����[BehaviorTree.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/18
//-----------------------------------------------------------------------------
#include "BehaviorTree.h"

//=============================================================================
// �I�t�F���X�c���[
//=============================================================================
void BehaviorTree::offense(void)
{
	currentTree = OFFENSE_TREE;

	addNode(PARENT_IS_NOT_EXIST, PARARELL);

	addNode(0, SEQUENCE);
	addNode(0, SEQUENCE);
	addNode(0, SET_DESTINATION_OPPONENT);
	addNode(0, SET_TARGET_OPPONENT);


	addNode(1, IF_SHOCK_WAVE_MAY_BE_HAPPEN);
	addNode(1, ACTION_JUMP);

	addNode(2, IF_BULLET_NEAR);
	addNode(2, ACTION_JUMP);

	addNode(0, ACTION_MOVE);
	addNode(0, ACTION_SHOOT);
}


//=============================================================================
// �f�B�t�F���X�c���[
//=============================================================================
void BehaviorTree::deffense(void)
{
	currentTree = DEFFENSE_TREE;


	addNode(PARENT_IS_NOT_EXIST, PARARELL);
	addNode(0, SEQUENCE);
	addNode(0, SEQUENCE);
	addNode(0, SEQUENCE);
	addNode(0, SEQUENCE);

	addNode(1, SET_DESTINATION_TO_RECUASION);
	addNode(1, SET_DESTINATION_RANDOM);
	addNode(2, IF_DESTINATION_DECIDED);
	addNode(2, PRIORITY);

	addNode(3, IF_BULLET_NEAR);
	addNode(3, ACTION_JUMP);

	addNode(4, IF_SHOCK_WAVE_MAY_BE_HAPPEN);
	addNode(4, ACTION_JUMP);

	addNode(8, ACTION_MOVE);
	addNode(8, SET_RECUASION_STATE);
}


//=============================================================================
// ���J�[�W�����c���[
//=============================================================================
void BehaviorTree::recursion(void)
{
	currentTree = RECURSION_TREE;

	addNode(PARENT_IS_NOT_EXIST, SEQUENCE);
	addNode(0, SET_RECURSION_RECOGNITION);
	addNode(0, IF_RECURSION_IS_RUNNING);
	addNode(0, PRIORITY);
	addNode(3, ACTION_MOVE);
	addNode(3, SEQUENCE);
	addNode(5, ACTION_PILE);
	addNode(5, SET_DESTINATION_NEXT_PILE);
}

//=============================================================================
// �_�E���c���[
//=============================================================================
void BehaviorTree::down(void)
{
	currentTree = DOWN_TREE;

	addNode(PARENT_IS_NOT_EXIST, PARARELL);
	addNode(0, ACTION_REVIVAL);
}


//=============================================================================
// ��󃂁[�h�c���[
//=============================================================================
void BehaviorTree::sky(void)
{
	currentTree = SKY_TREE;

	addNode(PARENT_IS_NOT_EXIST, PRIORITY);
	addNode(0, SEQUENCE);
	addNode(0, SEQUENCE);

	addNode(1, IF_DESTINATION_DECIDED);
	addNode(1, ACTION_MOVE);

	addNode(2, IF_ONE_SECOND_LATER);
	addNode(2, SET_DESTINATION_TO_RECUASION);
}


//=============================================================================
// �������c���[
//=============================================================================
void BehaviorTree::fall(void)
{
	currentTree = FALL_TREE;
	addNode(PARENT_IS_NOT_EXIST, PARARELL);
}


//=============================================================================
// �R���X�g���N�^
//=============================================================================
BehaviorTree::BehaviorTree(void)
{
	currentTree = -1;// ���I��

	offense();
	deffense();
	recursion();
	down();
	sky();
	fall();
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
void BehaviorTree::addNode(int parentNumber, NODE_TAG tag)
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
		if (new RuleNode(currentTree, parentNumber, nodeType, tag) == NULL)
		{
			MessageBox(NULL, TEXT("�������̊m�ۂɎ��s���܂����B\n�A�v���P�[�V�������I�����܂��B"), TEXT("SystemError"), MB_OK);
			PostQuitMessage(0);
		}
		break;

	case CONDITIONAL_NODE:
		if (new ConditionalNode(currentTree, parentNumber, nodeType, tag) == NULL)
		{
			MessageBox(NULL, TEXT("�������̊m�ۂɎ��s���܂����B\n�A�v���P�[�V�������I�����܂��B"), TEXT("SystemError"), MB_OK);
			PostQuitMessage(0);
		}
		break;

	case ACTION_NODE:
		if (new ActionNode(currentTree, parentNumber, nodeType, tag) == NULL)
		{
			MessageBox(NULL, TEXT("�������̊m�ۂɎ��s���܂����B\n�A�v���P�[�V�������I�����܂��B"), TEXT("SystemError"), MB_OK);
			PostQuitMessage(0);
		}
		break;

	case SUBPROCEDURE_NODE:
		if (new SubProcedureNode(currentTree, parentNumber, nodeType, tag) == NULL)
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