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
namespace RecognitionNS
{
	enum INDEX_RECOBNITION_BLACK_BOARD
	{
		// from Sensor
		DISTANCE_TO_OPPONENT_CRISP_DATA,
		DISTANCE_TO_XXXXXXX1_CRISP_DATA,
		DISTANCE_TO_XXXXXXX2_CRISP_DATA,
		DISTANCE_TO_XXXXXXX3_CRISP_DATA,
		DISTANCE_TO_XXXXXXX4_CRISP_DATA,

		// from EnvironmentAnalysis
		DISTANCE_TO_OPPONENT_FUZZY_DATA,
		DISTANCE_TO_XXXXXXX1_FUZZY_DATA,
		DISTANCE_TO_XXXXXXX2_FUZZY_DATA,
		DISTANCE_TO_XXXXXXX3_FUZZY_DATA,
		DISTANCE_TO_XXXXXXX4_FUZZY_DATA,

		NUM_PAGE
	};
};



//*****************************************************************************
// �N���X��`
//*****************************************************************************
class RecognitionBB : public BlackBoardBase {
protected:
	// Data
	float vecLength[NUM_TARGET];
	FuzzyDistance fuzzyDistance[NUM_TARGET];

public:
	// Method
	RecognitionBB(void);
	~RecognitionBB(void);
	void initialize(void) override;				// ����������
	void uninitialize(void) override;			// �I������
};