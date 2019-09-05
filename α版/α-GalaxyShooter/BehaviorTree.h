//-----------------------------------------------------------------------------
// �r�w�C�r�A�c���[����[BehaviorTree.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/18
//-----------------------------------------------------------------------------
#pragma once
#include <vector>
#include "Base.h"
#include "SubProcedureNode.h"
#include "RuleNode.h"
#include "ActionNode.h"
#include "ConditionalNode.h"

//*****************************************************************************
// �萔��`
//*****************************************************************************


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class BehaviorTree
{
private:
	// Data
	int	currentTree;										// ���݂̑I���c���[

	// Method
	void offense(void);										// �T���v���c���[1
	void deffense(void);									// �T���v���c���[2
	void recursion(void);									// ���J�[�W����
	//void switchTree(int treeType);						// �c���[�؂�ւ�
	void addNode(int parentNumber, NODE_TAG tag);			// �m�[�h�̒ǉ�

public:
	BehaviorTree(void);
	~BehaviorTree();
	// �r�w�C�r�A�c���[�̎��s
	void run(int treeNumber, RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};
