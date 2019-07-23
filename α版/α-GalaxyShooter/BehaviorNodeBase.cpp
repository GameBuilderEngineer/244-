//-----------------------------------------------------------------------------
// ビヘイビアツリー ノード基底処理 [BehaviorNode.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/17
//-----------------------------------------------------------------------------
#include "BehaviorNodeBase.h"
#include "BehaviorTree.h"

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
BehaviorNodeBase* BehaviorNodeBase::root[NUM_TREE];
std::vector<BehaviorNodeBase*> BehaviorNodeBase::list[NUM_TREE];


//=============================================================================
// コンストラクタ
//=============================================================================
BehaviorNodeBase::BehaviorNodeBase(int treeType, int parentNumber, NODE_TAG tag)
{
	this->tag = tag;
	executionJudgement = true;
	childCount = 0;
	child = NULL;

	if (parentNumber == PARENT_IS_NOT_EXIST)
	{// ルートノード
		root[treeType] = this;
		hierarchyNumber = 0;
		siblingCount = 0;
		parent = NULL;
		sibling = NULL;
	}
	else
	{// ルート以外
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
		siblingCount = parent->childCount;// ●
		sibling = parent->child[parent->childCount - 1];
	}

	// リストに接続
	list[treeType].push_back(this);
}
