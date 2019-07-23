//-----------------------------------------------------------------------------
// �r�w�C�r�A�c���[����[BehaviorTree.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/18
//-----------------------------------------------------------------------------
#pragma once
#include <vector>
#include "Base.h"
#include "BehaviorRecord.h"
#include "StateMachine.h"

//*****************************************************************************
// �萔��`
//*****************************************************************************
namespace BehaviorTreeNS
{
	// �r�w�C�r�A�c���[
	enum TREE
	{
		TREE_INDEX,					// 0
		SAMPLE = 0,					// �T���v���c���[
		NUM_TREE					// �r�w�C�r�A�c���[�̐�
	};

	// �m�[�h�̃^�O
	enum NODE_TAG
	{
		_RULE_NODE,					// ���[���m�[�h
		PRIORITY,					// �D�揇�ʃ��X�g�@
		ON_OFF,						// �I���E�I�t�@
		RANDOM,						// �����_���@
		SEQUENCE,					// �V�[�N�G���X�@
		PARARELL,					// �p�������@
		CONDITIONAL,				// �����m�[�h

		_ACTION_NODE,				// �A�N�V�����m�[�h
		D,
		E,
		F,

		_SUBPROCEDURE_NODE,			// �������m�[�h
		G,
		H,
		I,

		NUM_NODE_TAG				// �^�O�̐�
	};

	// �m�[�h�̎��s����
	enum NODE_STATUS
	{
		SUCCESS,					// ���s����
		FAILED,						// ���s���s
		RUNNING,					// ���s��
		_NOT_FOUND = -1				// �m�[�h�����݂��Ȃ�
	};

	const int PARENT_IS_NOT_EXIST = -1;
}


using namespace BehaviorTreeNS;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class BehaviorTree
{
private:
	// Data
	static BehaviorTree* instance;	// �C���X�^���X�ւ̃|�C���^

	// Method
	BehaviorTree(void);
	~BehaviorTree();
	void sample(void);														// �T���v���c���[
	void addNode(int treeType, int parentNumber, NODE_TAG tag);				// �m�[�h�̒ǉ�

public:
	static void create(void) { if (!instance)instance = new BehaviorTree; }	// �C���X�^���X����
	static void destroy(void) { SAFE_DELETE(instance) }						// �C���X�^���X�j��
	static BehaviorTree* getInstance(void) { return instance; }				// �C���X�^���X�擾
	// �r�w�C�r�A�c���[�̎��s
	void run(int treeNumber, RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB, std::vector<BehaviorRecord> record);
};
