//-----------------------------------------------------------------------------
// �Z���T�[���� [Sensor.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/15
//-----------------------------------------------------------------------------
#pragma once
#include "KnowledgeSourceBase.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Sensor:public KnowledgeSourceBase {
private:
	RecognitionBB* recognitionBB;			// ���F���u���b�N�{�[�h
	D3DXVECTOR3* cameraPosition;				// �J�����̈ʒu
	float cameraFieldOfView;				// �J�����̎���p���

public:
	// Method
	Sensor(D3DXVECTOR3* _cameraPosition, float _cameraFieldOfView);
	~Sensor(void);
	void initialize(void) override;			// ����������
	void uninitialize(void) override;		// �I������
	void update(AgentAI* agentAI) override;	// �X�V����
	void setBlackBoard(RecognitionBB* adr) { recognitionBB = adr; }

};
