//-----------------------------------------------------------------------------
// ����͏��� [EnvironmentAnalysis.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/19
//-----------------------------------------------------------------------------
#pragma once
#include "KnowledgeSourceBase.h"
#include "Fuzzy.h"
#include "BoundingSphere.h"
#include "RecursionRecognition.h"
#include "Ray.h"

//----------
// �萔��`
//----------
namespace EnvilonmentAnalysisNs
{
	// �o�g���󋵉��
	const float	LENGTH_OPPONENT_IS_NEAR = 70.0f;		// ���肪�߂����f����x�N�g���̒���
	const int	BULLET_TWO_VECTOR_ANGLE_DEGREE = 10;	// �o���b�g�̎����x�N�g���ƃo���b�g�X�s�[�h�x�N�g���̊p�x��
	const float LENGHT_BULLET_IS_NEAR = 40.0f;			// �o���b�g���߂��Ɣ��f����x�N�g���̒���
	const float LOSING_WAGE_DEFFERENSE = -600;			// �`���M���z�ō��������Ă���ƌ��Ȃ��`���M���̑���Ƃ̍��z

	const int	BATTLE_ANALYSIS_FPS = 20;				// �o�g���󋵉�͍X�VFPS
	const int	VIRTUAL_RECURSION_FPS = 20;				// ���z���J�[�W�����X�VFPS

	// ���z���J�[�W�������s�񐔊֌W
	const int	NUM_NEARLEST_NODE = 3;					// ���J�[�W�����͈͂𒲂ׂ�}�b�v�m�[�h�̌�␔
	const int	NUM_TEST_SIZE = 3;						// ���J�[�W�����̑傫���iBS�̃T�C�Y�j�̐�
	const int	NUM_TEST_ARROUND = 5;					// �P�̃m�[�h�̎��͂�BS�𓖂Ă�ӏ��̐�
	const int	NUM_TEST_ZONE = NUM_TEST_ARROUND + 1;	// �m�[�h���̂̍��W���܂߂�BS�𓖂Ă�ӏ��̑���
	const int	NUM_TEST_CASES_PER_NODE = NUM_TEST_SIZE * NUM_TEST_ZONE;// ��̃m�[�h�ɂ��ďՓˌ��m�̎��s��

	// ���J�[�W�����G���A����p�o�E���f�B���O�X�t�B�A
	const float	TEST_SIZE_RADIUS_BASE = 13.0f;			// ��{���a
	const float	TEST_SIZE_RADIUS_ADD = 5.0f;			// �ǉ����a
	const float  TEST_SIZE_RADIUS_FUZZY_ADJUST = 1.0f;	// �T�C�Y�W�����e1.0�̂Ƃ��Ɋ܂ގ��ۂ�BS���a�̍ŏ��ő�Ƃ̍�
	const float  AXIS_TILT_ANGLE_FOR_SMALL_BS = 0.22f;	// �T�C�Y�ɉ������z�u���a����邽�߃��C���X����p�x
	const float  AXIS_TILT_ANGLE_FOR_MIDDLE_BS = 0.3f;	// �T�C�Y�ɉ������z�u���a����邽�߃��C���X����p�x
	const float  AXIS_TILT_ANGLE_FOR_BIG_BS = 0.42f;	// �T�C�Y�ɉ������z�u���a����邽�߃��C���X����p�x

	// ��������J�[�W��������ۂ̔��a
	const float  SIZE_RADIUS_OPPONENT_RECURSION = 11.5f;

	// ���t�@�W�[���͒l�Z�o�ɂ������Ă̒萔�͒���selectRecursionArea()����������������̂ł����ɂ͋L�ڂ��Ȃ�
}


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class EnvironmentAnalysis:public KnowledgeSourceBase {
private:
	//------
	// Data
	//------
	RecognitionBB* recognitionBB;			// ���F���u���b�N�{�[�h
	std::vector<Wasuremono*>* wasuremono;	// ���X�����m
	Fuzzy fuzzy;							// �t�@�W�[���_����
	Ray ray;								// �ėp���C

	// �o�g���󋵉��
	int battleAnalysisFrameCount;			// �X�V�J�E���g

	// ���z���J�[�W�����֌W
	int vRecursionFrameCount;				// �X�V�J�E���g
	BoundingSphere* recursionSphere;		// ���J�[�W���������W�Z�o�pBS�|�C���^

	// �L�������֌W
	int mapTimeCount;						// �}�b�v�L���t���[���J�E���^
	int forgettingTimeMap;					// �}�b�v�L���ێ��t���[����
	int bulletTimeCount;					// �o���b�g�L���t���[���J�E���^
	int forgettingTimeBullet;				// �o���b�g�L���ێ��t���[����

	//--------
	// Method
	//--------
	// �o�g���󋵂����
	void analyzeBattle(AgentAI* agentAI);
	// �������[���C���ؒf���W���Z�o
	void makeCoordForCut(AgentAI* agentAI);
	// ���z���J�[�W����
	void virtualRecursion(AgentAI* agentAI);
	//�i���z���J�[�W�����X�e�b�v���̂P�j�߂��}�b�v�m�[�h�Ō����i��
	void selectMapNode(MapNode* nearestNode[], int* numNearestNode, AgentAI* agentAI);
	//�i���z���J�[�W�����X�e�b�v���̂Q�j���J�[�W�����ꏊ�̔F�����X�g�b�N����
	void recognizeRecursionArea(RecursionRecognition recursionRecognition[], MapNode* nearestNode[],
		int numNearestNode, AgentAI* agentAI);
	//�i���z���J�[�W�����X�e�b�v���̂R�j���J�[�W�����F���̐����i��
	void selectRecursionArea(int selectionRecognition[], RecursionRecognition recursionRecognition[],
		MapNode* nearestNode[], int numNearestNode, AgentAI* agentAI);
	//�i���z���J�[�W�����X�e�b�v���̂S�j�������[�p�C����ł����ލ��W�����
	void makeCoordForPile(int selectionRecognition[], RecursionRecognition recursionRecognition[], AgentAI* agentAI);
	// ���J�[�W�����F���ւ̑�������i�X�t�B�A�ƃ��X�����m�̏Փ˔���j
	void hitCheckAndAssign(AgentAI* agentAI, D3DXVECTOR3* checkPosition,
		RecursionRecognition* recursionRecognition, int index, float circumscribedRadius);
	// ���z���J�[�W����for����
	void virtualRecursionForOpponent(AgentAI* agentAI);
	// �L��������Y�p
	void forgetMemorizedMatter(void);

public:
	EnvironmentAnalysis(std::vector<Wasuremono*>* _wasuremono);
	~EnvironmentAnalysis(void);
	void setBlackBoard(RecognitionBB* adr) { recognitionBB = adr; }
	void initialize(void) override;			// ����������
	void uninitialize(void) override;		// �I������
	void update(AgentAI* agentAI) override;	// �X�V����
	void debugRender(AgentAI* agentAI);		// �f�o�b�O�`�揈��
};