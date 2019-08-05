//-----------------------------------------------------------------------------
// �^���������� [MotionGeneration.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/19
//-----------------------------------------------------------------------------
#pragma once
#include "KnowledgeSourceBase.h"

namespace MotionGenerationNS
{
	static const float STOP_MOVE_LENGTH = 3.0f;		// 2.0���Ǝ~�܂�Ȃ�4.0�ȏゾ�ƒ�~�ʒu�̂��ꂪ�傫��
	static const float LANDING_JUDGE_LENGTH = 3.0f;	// �������~���悭�킩��Ȃ�����e�L�g�[
}

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class MotionGeneration:public KnowledgeSourceBase {
private:
	MemoryBB* memoryBB;
	BodyBB* bodyBB;

public:
	// Method
	MotionGeneration(void);
	~MotionGeneration(void);
	void initialize(void) override;		// ����������
	void uninitialize(void) override;	// �I������
	void update(AgentAI* agentAI) override;// �X�V����
	void setBlackBoard(MemoryBB* adr1, BodyBB* adr2) { memoryBB = adr1; bodyBB = adr2; }

	void move(AgentAI* agentAI, D3DXVECTOR3* targetCoordinates);	// �ړ�
	bool autoStop(D3DXVECTOR3* position1, D3DXVECTOR3* position2);	// ������~
	void jumpFlagCycle(AgentAI* agentAI);


};