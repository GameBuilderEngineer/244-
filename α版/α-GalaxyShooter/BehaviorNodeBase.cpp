//-----------------------------------------------------------------------------
// �r�w�C�r�A�c���[ �m�[�h��ꏈ�� [BehaviorNode.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/17
//-----------------------------------------------------------------------------
#include "BehaviorNodeBase.h"

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
int BehaviorNodeBase::instanceCount[NUM_TREE] = { 0 };
BehaviorNodeBase* BehaviorNodeBase::root[NUM_TREE];
std::vector<BehaviorNodeBase*> BehaviorNodeBase::list[NUM_TREE];


//=============================================================================
// �R���X�g���N�^
//=============================================================================
BehaviorNodeBase::BehaviorNodeBase(int treeType, int parentNumber, NODE_TYPE _type, NODE_TAG _tag)
{
	number = instanceCount[treeType]++;
	type = _type;
	tag = _tag;
	executionJudgement = true;
	list[treeType].push_back(this);

	// ���[�g�m�[�h
	if (parentNumber == PARENT_IS_NOT_EXIST)
	{
		root[treeType] = this;
		hierarchyNumber = 0;
		parent = NULL;
		sibling = NULL;
		return;
	}

	// ���[�g�ȊO
	for (size_t i = 0; i < list[treeType].size(); i++)
	{
		if (list[treeType][i]->number == parentNumber)
		{
			parent = list[treeType][i];
			break;
		}
		else
			parent = NULL;
	}
	hierarchyNumber = parent->hierarchyNumber + 1;
	parent->child.push_back(this);
	sibling = parent->child.front();
}
