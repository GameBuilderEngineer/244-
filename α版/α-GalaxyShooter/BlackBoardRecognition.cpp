//-----------------------------------------------------------------------------
// ���F���u���b�N�{�[�h���� [BlackBoardRecognition.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/19
//-----------------------------------------------------------------------------
#include "BlackBoardRecognition.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
RecognitionBB::RecognitionBB(void)
{
	index = new void*[RecognitionNS::NUM_PAGE];
	index[RecognitionNS::DISTANCE_TO_OPPONENT_CRISP_DATA] = &vecLength[0];
	index[RecognitionNS::DISTANCE_TO_XXXXXXX1_CRISP_DATA] = &vecLength[1];
	index[RecognitionNS::DISTANCE_TO_XXXXXXX2_CRISP_DATA] = &vecLength[2];
	index[RecognitionNS::DISTANCE_TO_XXXXXXX3_CRISP_DATA] = &vecLength[3];
	index[RecognitionNS::DISTANCE_TO_XXXXXXX4_CRISP_DATA] = &vecLength[4];
	index[RecognitionNS::DISTANCE_TO_OPPONENT_FUZZY_DATA] = &fuzzyDistance[0];
	index[RecognitionNS::DISTANCE_TO_XXXXXXX1_FUZZY_DATA] = &fuzzyDistance[1];
	index[RecognitionNS::DISTANCE_TO_XXXXXXX2_FUZZY_DATA] = &fuzzyDistance[2];
	index[RecognitionNS::DISTANCE_TO_XXXXXXX3_FUZZY_DATA] = &fuzzyDistance[3];
	index[RecognitionNS::DISTANCE_TO_XXXXXXX4_FUZZY_DATA] = &fuzzyDistance[4];

	// �H����
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
RecognitionBB::~RecognitionBB(void)
{
	delete[] index;
}


//=============================================================================
// ����������
//=============================================================================
void RecognitionBB::initialize(void)
{

}


//=============================================================================
// �I������
//=============================================================================
void RecognitionBB::uninitialize(void)
{

}

