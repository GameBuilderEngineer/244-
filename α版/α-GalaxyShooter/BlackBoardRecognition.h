//-----------------------------------------------------------------------------
// ���F���u���b�N�{�[�h���� [BlackBoardRecognition.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/19
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "AICommon.h"
#include "BlackBoardBase.h"
#include "BlackBoardMemory.h"
#include "Player.h"
#include "Map.h"
#include "RecursionRecognition.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class RecognitionBB : public BlackBoardBase
{
private:
	//-------------
	// Data - ���
	//-------------
	MemoryBB* memoryBB;							// �L���̈�u���b�N�{�[�h
	Player* opponentPlayer;						// �ΐ푊��
	D3DXVECTOR3 *myPosition;					// �����̍��W
	float *frameTime;							// �t���[�����Ԃւ̃|�C���^
	bool inAir;									// true �󒆂ɂ���  false �n��ɂ���
	bool isDown;								// �_�E������
	float distanceBetweenPlayers;				// �v���C���[�Ԃ̋���
	D3DXVECTOR3 lineCutCoord;					// �������[���C���ؒf���W

public://��
	//-----------------------------
	// Data - ���J�[�W�����F���֌W
	//-----------------------------
	bool flag = false;

	// ���J�[�W�����F���i���F�����W���[���Œ��ׂ����J�[�W�����ꏊ���j
	RecursionRecognition recursionRecognition[NUM_RECURSION_RECOGNITION];

	// ���J�[�W�����F���̊�����ԁi��L���J�[�W�����F�������ۂɎg�p�ł��邩�ۂ����t���O�Ǘ��j
	bool isActiveRecursionRecognition[NUM_RECURSION_RECOGNITION];

	// ���s���J�[�W�����F��
	//�i��L���J�[�W�����F���͊��F�����W���[�����s���ɏ��������j
	//�i���̂��ߎ��ۂɎ��s���郊�J�[�W�����͎��s���ɏ��������Ȃ��悤�ʂɕۊǂ���j
	RecursionRecognition runningRecursion;

	// ���J�[�W�����̕��j
	//�i��L���J�[�W�����F��������s���J�[�W�����F��������ɑI�肷�邽�߂̕��j�j
	//�i�E�F�C�g�d��, �`���M���z�d��, ���a�T�C�Y�d���̂R���j�j
	int recursionPolicy;

	bool isRecursionRunnning;					// ���J�[�W���������s���ł��邩�ǂ���
	int pileCount;								// �������[�p�C���ł����݂��J�E���g

public:
	//--------
	// Method
	//--------
	RecognitionBB(Player* _opponentPlayer);
	void initialize(void) override;								// ����������
	void setMemoryBB(MemoryBB* _memoryBB) { memoryBB = _memoryBB; }

	// frameTime
	float getFrameTime(void) { return *frameTime; }				// �t���[�����Ԃ��擾
	void setFrameTimePointer(float* adr) { frameTime = adr; }	// �t���[�����Ԃփ|�C���^�ݒ�

	// �����̏��
	D3DXVECTOR3* getMyPosition(void) { return myPosition; }		// �����̍��W
	void setMyPosition(D3DXVECTOR3* _position) { myPosition = _position; }
	bool getWhetherInAir(void) { return inAir; }				// �������󒆂ɂ��邩�H
	void setWhetherInAir(bool setting) { inAir = setting; }
	bool getIsDown(void) { return isDown; }						// �������_�E�������H
	void setIsDown(bool setting) { isDown = setting; }
	D3DXVECTOR3 getLineCutCoord(void) { return lineCutCoord; }				// �������[���C���ؒf���W���擾
	void setLineCutCoord(D3DXVECTOR3 setting) { lineCutCoord = setting; }	// �������[���C���ؒf���W��ݒ�
	RecursionRecognition* getRecursionRecognition(void) { return recursionRecognition; }// ���J�[�W�����F�����擾
	bool getIsActiveRecursionRecognition(int i) { return isActiveRecursionRecognition[i]; }// ���J�[�W�����F���̊�����Ԃ��擾
	void setIsActiveRecursionRecognition(int i, bool setting) { isActiveRecursionRecognition[i] = setting; }// ���J�[�W�����F���̊�����Ԃ�ݒ�
	bool getIsRecursionRunning(void) { return isRecursionRunnning; }
	void setIsRecursionRunning(bool setting) { isRecursionRunnning = setting; }
	int getRecursionPolicy(void) { return recursionPolicy; }
	void setRecursionPolicy(int setting) { recursionPolicy = setting; }
	RecursionRecognition* getRunningRecursion(void) { return &runningRecursion; }
	int* getPileCount(void) { return &pileCount; }

	// ����̏��
	Player* getOpponentPlayer(void) { return opponentPlayer; }							// �ΐ푊����擾
	bool getIsOpponentFall(void) { return opponentPlayer->whetherFall(); }				// ���������H
	bool getIsOpponentSky(void) { return opponentPlayer->whetherSky(); }				// ��󃂁[�h���H
	bool getIsOpponentDown(void) { return opponentPlayer->whetherDown(); }				// �_�E�������H
	void setDistanceBetweenPlayers(float setting) { distanceBetweenPlayers = setting; }	// �����ݒ�
	float getDistanceBetweenPlayers(void) { return distanceBetweenPlayers; }			// �����擾

	// �}�b�v���
	std::list<MapNode*>& getMemorizedMap(void) { return memoryBB->getMemorizedMap(); }

	// �o���b�g�̏��
	std::list<Bullet*>& getMemorizedBullet(void) { return memoryBB->getMemorizedBullet(); }
};