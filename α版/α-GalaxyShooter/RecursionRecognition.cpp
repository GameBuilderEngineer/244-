//-----------------------------------------------------------------------------
// ���J�[�W������AI�F�� [RecursionRecognition.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/8/22
//-----------------------------------------------------------------------------
#include "RecursionRecognition.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
RecursionRecognition::RecursionRecognition(void)
{
	totalHit = 0;
	totalAmount = 0;
	center = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	radius = 0.0f;
	wasuremonoInArea.reserve(15);	// �K�x�ɃL���p�V�e�B�[�𑝂₵�Ă���
	ZeroMemory(pilePosition, sizeof(D3DXVECTOR3) * 5);
	fuzzySelectionWeight = 0.0f;
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
RecursionRecognition::~RecursionRecognition()
{
	// �x�N�^�[�͎����ŉ�������
}
