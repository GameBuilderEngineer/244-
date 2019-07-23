//-----------------------------------------------------------------------------
// �r�w�C�r�A�c���[ �m�[�h��ꏈ�� [BehaviorNodeBase.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/17
//-----------------------------------------------------------------------------
#pragma once
#include "BehaviorTree.h"
#include "BlackBoardRecognition.h"
#include "BlackBoardMemory.h"
#include "BlackBoardBody.h"
#include <vector>
using namespace BehaviorTreeNS;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class BehaviorNodeBase
{
protected:
	NODE_TAG tag;					// �m�[�h�^�O
	int	number;						// �m�[�h�ԍ�
	int	hierarchyNumber;			// �c���[�K�w�ԍ�
	bool executionJudgement;		// ���s����
	NODE_STATUS status;				// ���s���

	int siblingCount;				// �Z��m�[�h�̐�
	int	childCount;					// �q�m�[�h�̐�
	
	BehaviorNodeBase* parent;		// �e�m�[�h
	BehaviorNodeBase* sibling;		// �Z��m�[�h�i�擪�j
	BehaviorNodeBase** child;		// �q�m�[�h
	BehaviorNodeBase* next;			// ���X�g�̎��m�[�h

	// Static
	static BehaviorNodeBase* root[NUM_TREE];				// ���[�g
	static std::vector<BehaviorNodeBase*> list[NUM_TREE];	// ���X�g

public:
	// �R���X�g���N�^
	BehaviorNodeBase(int treeType, int parentNumber, NODE_TAG tag);

	// �m�[�h���s
	virtual NODE_STATUS run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB, std::vector<BehaviorRecord> record) = 0;

	//NODE_TAG getTag(void) { return tag; }
	bool getExecutionJudgement(void) { return executionJudgement; }
	//int getChildCount(void) { return childCount; }
	//BehaviorNodeBase** getChild(void) { return child; }

	// Static
	static BehaviorNodeBase* getRoot(int treeType) { return root[treeType]; }
	static std::vector<BehaviorNodeBase*> getList(int treeType) { return list[treeType]; }
};
