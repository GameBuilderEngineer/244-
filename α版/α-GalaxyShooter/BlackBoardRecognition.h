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
	float distanceBetweenPlayers;

public:
	RecognitionBB(Player* _opponentPlayer);
	void setMemoryBB(MemoryBB* _memoryBB) { memoryBB = _memoryBB; }
	void initialize(void) override;				// ����������
	// �ΐ푊����擾
	Player* getOpponentPlayer(void) { return opponentPlayer; }

	D3DXVECTOR3* getMyPosition(void) { return myPosition; }
	void setMyPosition(D3DXVECTOR3* _position) { myPosition = _position; }
	bool getWhetherInAir(void) { return inAir; }
	void setWhetherInAir(bool setting) { inAir = setting; }
	bool getIsDown(void) { return isDown; }
	void setIsDown(bool setting) { isDown = setting; }
	std::vector<MapNode*>& getMemorizedMap(void) { return memoryBB->getMemorizedMap(); }
	void setDistanceBetweenPlayers(float setting) { distanceBetweenPlayers = setting; }
};