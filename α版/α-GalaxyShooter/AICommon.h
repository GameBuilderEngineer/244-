//-----------------------------------------------------------------------------
// AI���p�w�b�_ [AICommon.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/23
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"

//*****************************************************************************
// �萔��`
//*****************************************************************************
#define OPPONENT(p)				()

namespace Agent
{
	enum LEVEL
	{
		NORMAL_LEVEL,				// �m�[�}��
		HARD_LEVEL,					// �n�[�h
		VERY_HARD_LEVEL				// �x���[�n�[�h
	};
}

namespace Module
{
	enum TYPE
	{
		SENSOR,						// �Z���T�[
		ENVIRONMENT_ANSLYSIS,		// �����
		PATH_PLANNING,				// �o�H�T��
		DECISION_MAKING,			// �ӎv����
		MOTION_GENERATION,			// �^������
		NUM_MAX						// ���W���[���̐�
	};
}

namespace BB
{
	enum TYPE
	{
		ENVIRONMENT_RECOGNITION,	// ���F��
		MEMORY,						// �L��
		BODY,						// �g��
		NUM_MAX						// �u���b�N�{�[�h�̐�
	};
}

namespace Target
{
	enum TYPE
	{
		OPPONENT,					// �ΐ푊��
		MISSILE,					// �~�T�C��
		ETC,						// �Ƃ�
		NUM_MAX						// �Ώۂ̐�
	};
}

namespace Path
{
	enum TYPE
	{
		TO_OPPONENT,				// ����ւ̌o�H
		TO_JUNK,					// �K���N�^�ւ̌o�H
		NUM_MAX,					// �o�H�̐�
		INVALID = -1				// �������[�g
	};
}

namespace StateTransition
{
	enum
	{
		OFFENSE,
		DEFFENSE,
		STATE_MAX,
		INVALID = -1
	};

}

namespace BehaviorTreeNS
{
	// �r�w�C�r�A�c���[
	enum TREE
	{
		TREE_INDEX,					// 0
		SAMPLE = 0,					// �T���v���c���[
		NUM_TREE					// �r�w�C�r�A�c���[�̐�
	};

	// �m�[�h�^�C�v
	enum NODE_TYPE
	{
		RULE_NODE,					// ���[���m�[�h
		CONDITIONAL_NODE,			// �����m�[�h
		ACTION_NODE,				// �A�N�V�����m�[�h
		SUBPROCEDURE_NODE,			// �������m�[�h
	};

	// �m�[�h�̃^�O
	enum NODE_TAG
	{
		// ���[���m�[�h
		_RULE_NODE_,
		PRIORITY,					// �D�揇�ʃ��X�g�@
		ON_OFF,						// �I���E�I�t�@
		RANDOM,						// �����_���@
		SEQUENCE,					// �V�[�N�G���X�@
		PARARELL,					// �p�������@

		// �����m�[�h
		_CONDITIONAL_NODE_,	
		IF_OPPONENT_NEAR,

		// �A�N�V�����m�[�h
		_ACTION_NODE_,
		ACTION_MOVE,
		ACTION_JUMP,

		// �������m�[�h
		_SUBPROCEDURE_NODE_,
		SET_TARGET_OPPONENT,
		SET_TARGET_RANDOM_NODE,

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

