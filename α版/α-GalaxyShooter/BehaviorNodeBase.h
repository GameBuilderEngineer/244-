//-----------------------------------------------------------------------------
// �r�w�C�r�A�c���[ �m�[�h��ꏈ�� [BehaviorNodeBase.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/17
//-----------------------------------------------------------------------------
#pragma once
#include "AICommon.h"
#include <vector>
#include "BlackBoardRecognition.h"
#include "BlackBoardMemory.h"
#include "BlackBoardBody.h"
using namespace BehaviorTreeNS;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class BehaviorNodeBase
{
protected:
	NODE_TYPE type;							// �m�[�h�^�C�v
	NODE_TAG tag;							// �m�[�h�^�O
	int	number;								// �m�[�h�ԍ�
	int	hierarchyNumber;					// �c���[�K�w�ԍ�
	bool executionJudgement;				// ���s����
	NODE_STATUS status;						// ���s���
	
	BehaviorNodeBase* parent;				// �e�m�[�h
	BehaviorNodeBase* sibling;				// �Z��m�[�h�i�擪�j
	std::vector<BehaviorNodeBase*> child;	// �q�m�[�h
	BehaviorNodeBase* next;					// ���X�g�̎��m�[�h

	// Static
	static int instanceCount[NUM_TREE];						// �C���X�^���X�̐�
	static BehaviorNodeBase* root[NUM_TREE];				// ���[�g
	static std::vector<BehaviorNodeBase*> list[NUM_TREE];	// ���X�g

public:
	// �R���X�g���N�^
	BehaviorNodeBase(int treeType, int parentNumber, NODE_TYPE _type, NODE_TAG _tag);

	// �m�[�h���s
	virtual NODE_STATUS run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB) = 0;
	NODE_TYPE getType(void) { return type; }
	bool getExecutionJudgement(void) { return executionJudgement; }

	// Static
	static BehaviorNodeBase* getRoot(int treeType) { return root[treeType]; }
	static std::vector<BehaviorNodeBase*> getList(int treeType) { return list[treeType]; }
};
