//-----------------------------------------------------------------------------
// �t�@�W�[���_ [Fuzzy.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/23
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
struct FuzzyDistance
{
	float	nearSet;
	float	normalSet;
	float	farSet;
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
// �����o�[�V�b�v�֐��u�㏸�ΕӁv�^
float FuzzyGrade(float value, float x0, float x1);

// �����o�[�V�b�v�֐��u���~�ΕӁv�_
float FuzzyReverseGrade(float value, float x0, float x1);

// �����o�[�V�b�v�֐��u�O�p�`�v�Q�^�_�Q
float FuzzyTriangle(float value, float x0, float x1, float x2);

// �����o�[�V�b�v�֐��u��`�v�Q�^�P�_�Q
float FuzzyTrapenoid(float value, float x0, float x1, float x2, float x3);

// �w�b�W�֐��u�ƂĂ������v
float HedgeVery(float a);

// �w�b�W�֐��u�ƂĂ��キ�v
float HedgeNotVery(float a);

// �t�@�W�[AND���Z
float FuzzyAnd(float a, float b);

// �t�@�W�[OR���Z
float FuzzyOr(float a, float b);

// �t�@�W�[NOT���Z
float FuzzyNot(float a);


