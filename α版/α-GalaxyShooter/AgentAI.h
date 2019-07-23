//-----------------------------------------------------------------------------
// �G�[�W�F���gAI���� [AgentAI.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/15
//-----------------------------------------------------------------------------
#pragma once
#include "arbiter.h"
#include "Sensor.h"
#include "EnvironmentAnalysis.h"
#include "PathPlanning.h"
#include "DecisionMaking.h"
#include "MotionGeneration.h"
#include "BlackBoardRecognition.h"
#include "BlackBoardBody.h"
#include "BlackBoardMemory.h"


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class AgentAI {
private:
	// Data
	static int	numAgent;	// AI�̐�  
	int			aiID;		// AI�̌ŗL���ʔԍ�
	// Player�N���X�ɕK�v���Ǝv����
	//bool isNPC;
	//int characterID;

	// �A�[�r�^�[�F�e���W���[���̃^�C�~���O��؂�ւ��𐧌�
	Arbiter *arbiter;								// ����ҁiArbiter�j

	// AI���W���[���i�i���b�W�\�[�X�j�F�u���b�N�{�[�h��ǂݏ������Ȃ���AI�𓮂���
	Sensor					*sensor; 				// �Z���T�[ 
	EnvironmentAnalysis		*environmentAnalysis; 	// �����
	PathPlanning			*pathPlanning;			// �o�H�T��
	DecisionMaking			*decisionMaking;		// �ӎv����@
	MotionGeneration		*motionGeneration;		// �^������

	// �u���b�N�{�[�h�FAI�̋L����g�̏�Ԃ��L�^���鍕�I�T�O
	RecognitionBB			*recognitionBB; 		// ���F��
	BodyBB					*bodyBB; 				// �g�̏��
	MemoryBB				*memoryBB; 				// �L��

public:
	// Method
	AgentAI(void);
	~AgentAI(void);
	void initialize(void);				// ����������
	void uninitialize(void);			// �I������
	void run(void);						// ���s
};