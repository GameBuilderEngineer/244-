//-----------------------------------------------------------------------------
// �r�w�C�r�A�c���[ �m�[�h��ꏈ�� [BehaviorNode.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/17
//-----------------------------------------------------------------------------
#include "BehaviorNodeBase.h"
#include "BehaviorTree.h"

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
BehaviorNodeBase* BehaviorNodeBase::root[NUM_TREE];
std::vector<BehaviorNodeBase*> BehaviorNodeBase::list[NUM_TREE];


//=============================================================================
// �R���X�g���N�^
//=============================================================================
BehaviorNodeBase::BehaviorNodeBase(int treeType, int parentNumber, NODE_TAG tag)
{
	this->tag = tag;
	executionJudgement = true;
	childCount = 0;
	child = NULL;

	if (parentNumber == PARENT_IS_NOT_EXIST)
	{// ���[�g�m�[�h
		root[treeType] = this;
		hierarchyNumber = 0;
		siblingCount = 0;
		parent = NULL;
		sibling = NULL;
	}
	else
	{// ���[�g�ȊO
		for (size_t i = 0; i < list[treeType].size(); i++)
		{
			if (list[treeType][i]->number == parentNumber)
				parent = list[treeType][i];
			else
				parent = NULL;
		}
		hierarchyNumber = parent->hierarchyNumber + 1;
		parent->childCount++;
		parent->child[parent->childCount - 1] = this;
		siblingCount = parent->childCount;// ��
		sibling = parent->child[parent->childCount - 1];
	}

	// ���X�g�ɐڑ�
	list[treeType].push_back(this);
}
