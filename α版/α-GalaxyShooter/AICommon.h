//-----------------------------------------------------------------------------
// AI���p�w�b�_ [AICommon.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/23
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "Player.h"

//*****************************************************************************
// AI���
//*****************************************************************************
namespace STDAI
{
#define opponent					(recognitionBB->getOpponentPlayer())

	const D3DXQUATERNION SKY_RELATIVE_QUATERNION =	// ��󃂁[�h�J�����̃N�I�[�^�j�I��
		D3DXQUATERNION(-2.51793313, 44.6412468, -0.916452408, 3.55765224e-07);

	static const int NUM_RECURSION_RECOGNITION = 3;	// ���J�[�W�����F���̐�
	enum RECURSION_PERSONALITY						// ���J�[�W�����̐��i
	{
		LARGEST_WEIGHT,	// �E�F�C�g�̏d���D��
		MOST_EXPENSIVE,	// �`���M���z��D��
		LEAST_RADIUS	// �T�C�Y�̏�������D��
	};
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
		//--------------
		// ���[���m�[�h
		//--------------
		_RULE_NODE_,
		PRIORITY,					// �D�揇�ʃ��X�g�@
		ON_OFF,						// �I���E�I�t�@
		RANDOM,						// �����_���@
		SEQUENCE,					// �V�[�N�G���X�@
		PARARELL,					// �p�������@

		//------------
		// �����m�[�h
		//------------
		_CONDITIONAL_NODE_,
		IF_OPPONENT_NEAR,
		IF_BULLET_NEAR,
		IF_SHOCK_WAVE_MAY_BE_HAPPEN,
		IF_FIVE_SECONDS_LATER,
		IF_THREE_SECONDS_LATER,
		IF_ONE_SECOND_LATER,
		IF_RECURSION_IS_RUNNING,	// ���J�[�W�������s���Ȃ�
		IF_DESTINATION_DECIDED,

		//------------------
		// �A�N�V�����m�[�h
		//------------------
		_ACTION_NODE_,
		ACTION_MOVE,
		ACTION_JUMP,
		ACTION_SHOOT,
		ACTION_PILE,
		ACTION_CUT,
		ACTION_REVIVAL,
		ACTION_FALL,

		//--------------
		// �������m�[�h
		//--------------
		_SUBPROCEDURE_NODE_,
		SET_DESTINATION_OPPONENT,
		SET_DESTINATION_RANDOM,
		SET_DESTINATION_NEXT_PILE,
		SET_DESTINATION_TO_RECUASION,
		SET_RECURSION_RECOGNITION,
		SET_RECUASION_STATE,
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
		OFFENSE_TREE = 0,			// �I�t�F���X��ԃc���[
		DEFFENSE_TREE,				// �f�B�t�F���X��ԃc���[
		RECURSION_TREE,				// ���J�[�W������ԃc���[
		DOWN_TREE,					// �_�E����ԃc���[
		SKY_TREE,					// �X�J�C��ԃc���[
		FALL_TREE,					// ������ԃc���[
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