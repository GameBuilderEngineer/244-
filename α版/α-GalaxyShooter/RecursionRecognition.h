//-----------------------------------------------------------------------------
// ���J�[�W������AI�F�� [RecursionRecognition.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/8/22
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "AICommon.h"
#include "Wasuremono.h"
#include <vector>

//*****************************************************************************
// ���J�[�W�����F���N���X
//*****************************************************************************
struct RecursionRecognition
{
	// Data
	float totalHit;								// �F���͈͓��̃��X�����m��
	float totalAmount;							// �F���͈͂̑��`���M���z
	D3DXVECTOR3 center;							// �F���͈͂̒��S���W
	float radius;								// �F���͈͂̔��a
	std::vector<Wasuremono*> wasuremonoInArea;	// ���X�����m�ւ̃|�C���^
	D3DXVECTOR3 pilePosition[5];				// �������[�p�C���̐ݒu���W
	float fuzzySelectionWeight;					// ���̔F�������J�[�W�����ɍ̗p���邩�ǂ����̏d�݂Â� 

	// Method
	RecursionRecognition();
	~RecursionRecognition();
};
