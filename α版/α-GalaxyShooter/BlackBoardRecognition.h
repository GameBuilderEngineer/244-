//-----------------------------------------------------------------------------
// ���F���u���b�N�{�[�h���� [BlackBoardRecognition.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/19
//-----------------------------------------------------------------------------
#pragma once
#include "AICommon.h"
#include "BlackBoardBase.h"
#include "Fuzzy.h"

//*****************************************************************************
// �萔��`
//*****************************************************************************
namespace Page
{
	enum PAGE
	{
		// from Sensor
		DISTANCE_TO_OPPONENT_CRISP_DATA,
		DISTANCE_TO_XXXXXXX1_CRISP_DATA,
		DISTANCE_TO_XXXXXXX2_CRISP_DATA,
		DISTANCE_TO_XXXXXXX3_CRISP_DATA,
		DISTANCE_TO_XXXXXXX4_CRISP_DATA,
		_DUMMY_COUNT_DISTANCE_CRISP_DATA,

		// from EnvironmentAnalysis
		DISTANCE_TO_OPPONENT_FUZZY_DATA,
		DISTANCE_TO_XXXXXXX1_FUZZY_DATA,
		DISTANCE_TO_XXXXXXX2_FUZZY_DATA,
		DISTANCE_TO_XXXXXXX3_FUZZY_DATA,
		_DUMMY_COUNT_DISTANCE_FUZZY_DATA,
	};

	// �e��ނ��Ƃ̃y�[�W���i�y�[�W���������炱���ɒǉ�����j
	const static int NUM_DISTANCE_CRISP_DATA = _DUMMY_COUNT_DISTANCE_CRISP_DATA;
	const static int NUM_DISTANCE_FUZZY_DATA = _DUMMY_COUNT_DISTANCE_FUZZY_DATA - _DUMMY_COUNT_DISTANCE_CRISP_DATA + 1;

	// �y�[�W�����i�y�[�W���������炱���ɒǉ�����j
	const static int NUM_PAGE_RECOGNITION_BB = NUM_DISTANCE_CRISP_DATA + NUM_DISTANCE_FUZZY_DATA;
};


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class RecognitionBB : public BlackBoardBase
{
protected:
	// Data
	float vecLength[Target::NUM_MAX];
	FuzzyDistance fuzzyDistance[Target::NUM_MAX];

public:
	// Method
	RecognitionBB(void);
	~RecognitionBB(void);
	void initialize(void) override;				// ����������
	void uninitialize(void) override;			// �I������
	bool getAccessPermission(int tag) override;	// ���W���[���ɃA�N�Z�X����Ԃ�
};