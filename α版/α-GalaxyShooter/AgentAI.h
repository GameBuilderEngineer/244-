//-----------------------------------------------------------------------------
// �G�[�W�F���gAI���� [AgentAI.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/15
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "Camera.h"
#include "Player.h"
#include "arbiter.h"
#include "Sensor.h"
#include "EnvironmentAnalysis.h"
#include "PathPlanning.h"
#include "DecisionMaking.h"
#include "MotionGeneration.h"
#include "BlackBoardRecognition.h"
#include "BlackBoardBody.h"
#include "BlackBoardMemory.h"
#include "StateMachine.h"
#include "BehaviorTree.h"
#include "Sound.h"

//*****************************************************************************
// �G�[�W�F���gAI
//*****************************************************************************
class AgentAI: public Player
{
private:
	//------
	// Data
	//------
	static int				numAgent;				// AI�̐�  
	int						aiID;					// AI�̌ŗL���ʔԍ�
	float					frameTime;				// 1�t���[��������̎���
	float					virticalTime;			// �I�[�g�J�����̏c��U�莞��
	float					horizontalTime;			// �I�[�g�J�����̉���U�莞��

	// �A�[�r�^�[�F			�e���W���[���̃^�C�~���O��؂�ւ��𐧌�
	Arbiter					*arbiter;

	// �i���b�W�\�[�X�F		�u���b�N�{�[�h��ǂݏ������Ȃ���AI�𓮂���
	Sensor					*sensor; 				// �Z���T�[ *�}�b�v�⑊��̏������W
	EnvironmentAnalysis		*environmentAnalysis; 	// ����� *���J�[�W�������W���߂Ȃ�
	PathPlanning			*pathPlanning;			// �o�H�T�� *�قڏ����Ȃ�
	DecisionMaking			*decisionMaking;		// �ӎv���� *�r�w�C�r�A�c���[�ɂ��s������
	MotionGeneration		*motionGeneration;		// �^������ *�e�A�N�V�����̃t���O�Ǘ�

	// �u���b�N�{�[�h�F		AI�̋L����g�̏�Ԃ��L�^���鍕�I�T�O
	RecognitionBB			*recognitionBB; 		// ���F��
	MemoryBB				*memoryBB; 				// �L��
	BodyBB					*bodyBB; 				// �g�̏��


	//--------
	// Method
	//--------
	// �v���C���[�����̎��O�X�V
	void updatePlayerBefore(float frameTime);
	// �v���C���[�����̎���X�V
	void updatePlayerAfter(float frameTime);
	// �v���C���[���ȏ��AI�ɑ��M 
	void updateAgentSelfData(void);
	// �I�[�g�J��������
	void autoCamera(void);
	// �������b�N�I��
	void lockOnHorizontally(D3DXVECTOR3 lockOnTarget, float frameTime);
	// 3�������b�N�I���i�����j
	void lockOn3D(D3DXVECTOR3 lockOnTarget, float frameTime);

public:
	AgentAI(Player* opponentPlayer, Camera* camera, std::vector<Wasuremono*>* wasuremono);
	~AgentAI(void);
	// ����������
	void initialize(int playerType, int modelType, PDIRECT3DDEVICE9 device, StaticMeshLoader* staticMeshLoader,
		TextureLoader* textureLoader, ShaderLoader* shaderLoader) override;
	// �I������
	void uninitialize(void);
	// �X�V����
	void update(float frameTime) override;
	// �`�揈��
	void debugRender(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);
	// �o���b�g�̔���
	void shootBullet(D3DXVECTOR3 targetDirection);
	// �������[�p�C���̐ݒu
	void locateMemoryPile(void);
	// �������[���C���ؒf
	void cutMemoryLine(void);
	// �����|�C���g����
	void increaseRevivalPoint(void);
};