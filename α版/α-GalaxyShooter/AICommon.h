//-----------------------------------------------------------------------------
// AI���p�w�b�_ [AICommon.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/23
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"

//*****************************************************************************
// AI���
//*****************************************************************************
namespace STDAI
{
#define opponent					(recognitionBB->getOpponentPlayer())
}
using namespace STDAI;


//*****************************************************************************
// �r�w�C�r�A�c���[
//*****************************************************************************
// BehaviorNodeBase.h�ɋL�q���Ă�include����OK��������J���̂��ʓ|�Ȃ̂ł�����
namespace BehaviorTreeNS
{
	// �m�[�h�^�O��`
	enum NODE_TAG
	{
		//---------------------------------------------------------------------
		// ���[���m�[�h
		//---------------------------------------------------------------------
		_RULE_NODE_,
		PRIORITY,					// �D�揇�ʃ��X�g�@
		ON_OFF,						// �I���E�I�t�@
		RANDOM,						// �����_���@
		SEQUENCE,					// �V�[�N�G���X�@
		PARARELL,					// �p�������@

		//---------------------------------------------------------------------
		// �����m�[�h
		//---------------------------------------------------------------------
		_CONDITIONAL_NODE_,
		IF_OPPONENT_NEAR,
		IF_FIVE_SECONDS_LATER,
		IF_THREE_SECONDS_LATER,

		//---------------------------------------------------------------------
		// �A�N�V�����m�[�h
		//---------------------------------------------------------------------
		_ACTION_NODE_,
		ACTION_MOVE,
		ACTION_JUMP,
		ACTION_SHOOT,
		ACTION_PILE,

		//---------------------------------------------------------------------
		// �������m�[�h
		//---------------------------------------------------------------------
		_SUBPROCEDURE_NODE_,
		SET_DESTINATION_OPPONENT,
		SET_DESTINATION_RANDOM,
		SET_TARGET_OPPONENT,

		// �^�O�̐�
		NUM_NODE_TAG
	};

	// �m�[�h�^�C�v��`
	enum NODE_TYPE
	{
		RULE_NODE,					// ���[���m�[�h
		CONDITIONAL_NODE,			// �����m�[�h
		ACTION_NODE,				// �A�N�V�����m�[�h
		SUBPROCEDURE_NODE,			// �������m�[�h
	};

	// �c���[�^�C�v��`
	enum TREE
	{
		TREE_INDEX,					//  = 0
		OFFENSE = 0,				// �T���v���c���[1
		DEFFENSE,					// �T���v���c���[2
		NUM_TREE					// �r�w�C�r�A�c���[�̐�
	};

	// �m�[�h�̎��s����
	enum NODE_STATUS
	{
		SUCCESS,					// ���s����
		FAILED,						// ���s���s
		RUNNING,					// ���s��
		_NOT_FOUND = -1				// �m�[�h�����݂��Ȃ�
	};

	const int PARENT_IS_NOT_EXIST = -1;		// �e�m�[�h�����݂��Ȃ����Ƃ������i���[�g�̂݁j
}


//*****************************************************************************
// �X�e�[�g�}�V��
//*****************************************************************************
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


//*****************************************************************************
// �u���b�N�{�[�h�A�[�L�e�N�`��
//*****************************************************************************
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