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
	MemoryBB* memoryBB;							// �L���̈�u���b�N�{�[�h
	Player* opponentPlayer;						// �ΐ푊��
	D3DXVECTOR3 *myPosition;					// �����̍��W
	bool inAir;									// true �󒆂ɂ���  false �n��ɂ���
	bool isDown;								// �_�E������

	float distanceBetweenPlayers;				// �v���C���[�Ԃ̋���

	RecursionRecognition recursionRecognition[NUM_RECURSION_RECOGNITION];// ���J�[�W�����F��

public:
	RecognitionBB(Player* _opponentPlayer);
	void setMemoryBB(MemoryBB* _memoryBB) { memoryBB = _memoryBB; }
	void initialize(void) override;								// ����������
	Player* getOpponentPlayer(void) { return opponentPlayer; }	// �ΐ푊����擾

	D3DXVECTOR3* getMyPosition(void) { return myPosition; }		// �����̍��W
	void setMyPosition(D3DXVECTOR3* _position) { myPosition = _position; }
	bool getWhetherInAir(void) { return inAir; }				// �������󒆂ɂ��邩�H
	void setWhetherInAir(bool setting) { inAir = setting; }
	bool getIsDown(void) { return isDown; }						// �������_�E�������H
	void setIsDown(bool setting) { isDown = setting; }
	RecursionRecognition* getRecursionRecognition(void) { return recursionRecognition; }// ���J�[�W�����F�����擾

	// ����̏��
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