//-----------------------------------------------------------------------------
// �A�[�r�^�[���� [Arbiter.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/15
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "AICommon.h"
#include "KnowledgeSourceBase.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Arbiter{
private:
	// Data
	int sensorInterval;				// �Z���T�[�̍X�V�Ԋu
	int sensoryTransmissionTime;	// �Z���T�����F���̓`�B���x�i���o�_�o�̓`�B���x��\���j
	int pathPanningInterval;		// �o�H�T���̍X�V�Ԋu
	int decisionMakingInterval;		// �ӎv����̍X�V�Ԋu
	int motionInterval;				// �^�������̍X�V�Ԋu

	DWORD frameCount;				// AI�ғ���̃t���[�������J�E���g
	DWORD sensorLastFrame;			// �Z���T�[���Ō�ɍX�V�����̂����t���[���ڂ��L�^
	DWORD pathPlanningLastFrame;	// �o�H�T�����Ō�ɍX�V�����̂����t���[���ڂ��L�^
	DWORD decisionMakingLastFrame;	// �ӎv������Ō�ɍX�V�����̂����t���[���ڂ��L�^
	DWORD motionGenerationLastFrame;// �^���������Ō�ɍX�V�����̂����t���[���ڂ��L�^

	KnowledgeSourceBase *module[Module::NUM_MAX];// �e���W���[���̃A�h���X

public:
	// Method
	Arbiter(void);
	~Arbiter(void);
	void initialize(void);			// ����������
	void uninitialize(void);		// �I������
	void update(void);				// �X�V����
	void setModule(int number, KnowledgeSourceBase *adr) { module[number] = adr; }// ���W���[����ڑ�
};