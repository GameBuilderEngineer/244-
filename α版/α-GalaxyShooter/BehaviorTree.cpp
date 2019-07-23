//-----------------------------------------------------------------------------
// �r�w�C�r�A�c���[����[BehaviorTree.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/18
//-----------------------------------------------------------------------------
#include "BehaviorTree.h"
#include "BehaviorNodeBase.h"
#include "RuleNode.h"
#include "ActionNode.h"
#include "SubProcedureNode.h"

//*****************************************************************************
// �ÓI�����o
//*****************************************************************************
BehaviorTree* BehaviorTree::instance;


//=============================================================================
// �T���v���c���[
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
// �R���X�g���N�^
//=============================================================================
BehaviorTree::BehaviorTree(void)
{
	sample();
}


//=============================================================================
// �f�X�g���N�^
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
// �m�[�h��ǉ�
//=============================================================================
void BehaviorTree::addNode(int treeType, int parentNumber, NODE_TAG tag)
{
	int nodeType;

	// �ǉ��m�[�h�^�C�v�𔻒�
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

	// �m�[�h����
	switch (nodeType)
	{
	case _RULE_NODE:
		if (new RuleNode(treeType, parentNumber, tag) == NULL)
		{
			MessageBox(NULL, TEXT("�������̊m�ۂɎ��s���܂����B\n�A�v���P�[�V�������I�����܂��B"), TEXT("SystemError"), MB_OK);
			PostQuitMessage(0);
		}
		break;

	case _ACTION_NODE:
		if (new ActionNode(treeType, parentNumber, tag) == NULL)
		{
			MessageBox(NULL, TEXT("�������̊m�ۂɎ��s���܂����B\n�A�v���P�[�V�������I�����܂��B"), TEXT("SystemError"), MB_OK);
			PostQuitMessage(0);
		}
		break;

	case _SUBPROCEDURE_NODE:
		if (new SubProcedureNode(treeType, parentNumber, tag) == NULL)
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
void BehaviorTree::run(int treeNumber, RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB, std::vector<BehaviorRecord> record)
{
	BehaviorNodeBase::getRoot(treeNumber)->run(recognitionBB, memoryBB, bodyBB, record);

	for (size_t i = 0; i < record.size(); i++)
	{
		record[i].setStep(0);
	}
}
