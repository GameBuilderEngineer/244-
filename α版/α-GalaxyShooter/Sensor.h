//-----------------------------------------------------------------------------
// �Z���T�[���� [Sensor.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/15
//-----------------------------------------------------------------------------
#pragma once
#include "KnowledgeSourceBase.h"
#include "BlackBoardBase.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Sensor:public KnowledgeSourceBase {
private:

public:
	// Method
	Sensor(void);
	~Sensor(void);
	void initialize(void) override;		// ����������
	void uninitialize(void) override;	// �I������
	void update(void) override;			// �X�V����
};
