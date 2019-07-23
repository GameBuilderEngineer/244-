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
		BODY,						// �g��
		MEMORY,						// �L��
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
