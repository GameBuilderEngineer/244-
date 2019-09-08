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
	float *skyHeight;							// ��󃂁[�h�̍����ւ̃|�C���^
	bool inAir;									// true �󒆂ɂ���  false �n��ɂ���
	float distanceBetweenPlayers;				// �v���C���[�Ԃ̋���
	D3DXVECTOR3 lineCutCoord;					// �������[���C���ؒf���W
	bool isFallingDestinationDecided;			// �����ړI�n�����܂�����

	// �v���C���[�X�e�[�g
	int playerState;							// �v���C���[�N���X�̏��

	//-----------------------
	// Data - �o�g���󋵊֌W
	//-----------------------
	bool isOpponentNear;						// �G���Ⴂ
	bool isOpponentOffensive;					// �G���U���I�ł���
	bool isBulletNear;							// �o���b�g���߂�
	bool isChinginLow;							// �`���M�����Ⴂ

	//-----------------------------
	// Data - ���J�[�W�����F���֌W
	//-----------------------------
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

	bool isStartRecursion;						// ���J�[�W�������J�n���邩�H
	bool isRecursionRunnning;					// ���J�[�W���������s���ł��邩�ǂ���
	int pileCount;								// �������[�p�C���ł����݂��J�E���g

public:
	//--------
	// Method
	//--------
	RecognitionBB(Player* _opponentPlayer);
	void initialize(void) override;									// ����������
	void setMemoryBB(MemoryBB* _memoryBB) { memoryBB = _memoryBB; }	// �u���b�N�{�[�h���Z�b�g
	float getFrameTime(void) { return *frameTime; }					// �t���[�����Ԃ��擾
	void setFrameTimePointer(float* adr) { frameTime = adr; }		// �t���[�����Ԃփ|�C���^�ݒ�
	float getSkyHeight(void) { return *skyHeight; }					// ��󃂁[�h�̍������擾
	void setSkyHeightPointer(float* adr) { skyHeight = adr; }		// ��󃂁[�h�̍����փ|�C���^�ݒ�

	// �����̏��
	D3DXVECTOR3* getMyPosition(void) { return myPosition; }			// �����̍��W���擾
	void setMyPosition(D3DXVECTOR3* _position) { myPosition = _position; }// �����̍��W��ݒ�
	bool getWhetherInAir(void) { return inAir; }					// �������󒆂ɂ��邩�擾
	void setWhetherInAir(bool setting) { inAir = setting; }			// �������󒆂ɂ��邩�ݒ�
	int getPlayerState(void) { return playerState; }				// �v���C���[�X�e�[�g���擾
	void setPlayerState(int setting) { playerState = setting; }		// �v�����[�X�e�[�g��ݒ�

	D3DXVECTOR3 getLineCutCoord(void) { return lineCutCoord; }				// �������[���C���ؒf���W���擾
	void setLineCutCoord(D3DXVECTOR3 setting) { lineCutCoord = setting; }	// �������[���C���ؒf���W��ݒ�

	bool whetherFallingDestinationDecided(void) { return isFallingDestinationDecided; }// ������ړI�n�����܂������擾
	void setWhetherFallingDestinationDecided(bool setting) { isFallingDestinationDecided = setting; }// ������ړI�n�����܂������ݒ�

	// ���J�[�W����
	RecursionRecognition* getRecursionRecognition(void) { return recursionRecognition; }// ���J�[�W�����F�����擾
	bool getIsActiveRecursionRecognition(int i) { return isActiveRecursionRecognition[i]; }// ���J�[�W�����F���̊�����Ԃ��擾
	void setIsActiveRecursionRecognition(int i, bool setting) { isActiveRecursionRecognition[i] = setting; }// ���J�[�W�����F���̊�����Ԃ�ݒ�
	bool getIsStartRecursion(void) { return isStartRecursion; }				// ���J�[�W�������J�n���邩�擾
	void setIsStartRecursion(bool setting) { isStartRecursion = setting; }	// ���J�[�W�������J�n���邩�ݒ�
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

	// �o�g���󋵊֌W
	bool getIsOpponentNear(void) { return isOpponentNear; };					// �G���Ⴂ���擾
	void setIsOpponentNear(bool setting) { isOpponentNear = setting; }			// �G���߂����ݒ�
	bool getIsOpponentOffensive(void) { return isOpponentOffensive; }			// �G���U���I�ł��邩�擾
	void setIsOpponentOffensive(bool setting) { isOpponentOffensive = setting; }// �G���U���I�ł��邩�ݒ�
	bool getIsBulletNear(void) { return isBulletNear; }							// �o���b�g���߂����擾
	void setIsBuletNear(bool setting) { isBulletNear = setting; }				// �o���b�g���߂����ݒ�
	bool getIsChinginLow(void) { return isChinginLow; }							// �`���M�����Ⴂ���擾
	void setIsChinginLow(bool setting) { isChinginLow = setting; }				// �`���M�����Ⴂ���ݒ�
};