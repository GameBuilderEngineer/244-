//-----------------------------------------------------------------------------
// �Z���T�[���� [Sensor.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/15
//-----------------------------------------------------------------------------
#pragma once
#include "KnowledgeSourceBase.h"
#include "Ray.h"


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Sensor:public KnowledgeSourceBase
{
private:
	RecognitionBB* recognitionBB;			// ���F���u���b�N�{�[�h
	Camera* camera;							// �J����
	float fieldRadius;						// �t�B�[���h�̔��a
	Ray ray;								// ���C

	// �Z���T�[
	void mapSensor(AgentAI* agentAI, D3DXVECTOR3 vecCameraToGaze, float radius2);
	void mapSensorSky(void);
	void opponentSensor(AgentAI* agentAI, D3DXVECTOR3 vecCameraToGaze);
	void bulletSensor(AgentAI* agentAI, D3DXVECTOR3 vecCameraToGaze, float radius2);

public:
	// Method
	Sensor(Camera *camera);
	~Sensor(void);
	void initialize(void) override;			// ����������
	void uninitialize(void) override;		// �I������
	void update(AgentAI* agentAI) override;	// �X�V����
	void setBlackBoard(RecognitionBB* adr) { recognitionBB = adr; }
};
