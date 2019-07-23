//-----------------------------------------------------------------------------
// ���F���u���b�N�{�[�h���� [BlackBoardRecognition.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/19
//-----------------------------------------------------------------------------
#pragma once
#include "BlackBoardBase.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************

class RecognitionBB : public BlackBoardBase
{
private:
	// Data
	float distanceOpponent;

public:
	// Accessor
	float getDistanceOpponent(void) { return distanceOpponent; }
	void setDistanceOpponent(float value) { distanceOpponent = value; }

	// Method
	RecognitionBB(void);
	~RecognitionBB(void);
	void initialize(void) override;				// ����������
	void uninitialize(void) override;			// �I������
};