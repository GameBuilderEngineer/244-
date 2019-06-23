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

enum AI_LEVEL
{
	NORMAL_LEVEL,				// �m�[�}��
	HARD_LEVEL,					// �n�[�h
	VERY_HARD_LEVEL				// �x���[�n�[�h
};

enum MODULE_TYPE
{
	SENSOR,						// �Z���T�[
	ENVIRONMENT_ANSLYSIS,		// �����
	PATH_PLANNING,				// �o�H�T��
	DECISION_MAKING,			// �ӎv����
	MOTION_GENERATION,			// �^������
	NUM_KNOWLEDGE_SOURCE		// ���W���[���̐�
};

enum BLACK_BOARD_TYPE
{
	ENVIRONMENT_RECOGNITION,	// ���F��
	BODY,						// �g��
	MEMORY,						// �L��
	NUM_BLACK_BOARD				// �u���b�N�{�[�h�̐�
};

enum TARGET_OF_RECOGNITION
{
	OPPONENT,					// �ΐ푊��
	MISSILE,					// �~�T�C��
	ETC,						// �Ƃ�
	NUM_TARGET					// �Ώۂ̐�
};

enum PATH_TYPE {
	PATH_TO_OPPONENT,			// ����ւ̌o�H
	PATH_TO_JUNK,				// �K���N�^�ւ̌o�H
	NUM_PATH_TYPE,				// �o�H�̐�
	INVALID_PATH = -1			// �������[�g
};