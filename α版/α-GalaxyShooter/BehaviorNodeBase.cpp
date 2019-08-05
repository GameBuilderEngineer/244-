//-----------------------------------------------------------------------------
// ビヘイビアツリー ノード基底処理 [BehaviorNode.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/17
//-----------------------------------------------------------------------------
#include "BehaviorNodeBase.h"

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
int BehaviorNodeBase::instanceCount[NUM_TREE] = { 0 };
BehaviorNodeBase* BehaviorNodeBase::root[NUM_TREE];
std::vector<BehaviorNodeBase*> BehaviorNodeBase::list[NUM_TREE];


//=============================================================================
// コンストラクタ
//=============================================================================
BehaviorNodeBase::BehaviorNodeBase(int treeType, int parentNumber, NODE_TYPE _type, NODE_TAG _tag)
{
	number = instanceCount[treeType]++;
	type = _type;
	tag = _tag;
	executionJudgement = true;
	list[treeType].push_back(this);

	// ルートノード
	if (parentNumber == PARENT_IS_NOT_EXIST)
	{
		root[treeType] = this;
		hierarchyNumber = 0;
		parent = NULL;
		sibling = NULL;
		return;
	}

	// ルート以外
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
