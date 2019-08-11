//-----------------------------------------------------------------------------
// ���F���u���b�N�{�[�h���� [BlackBoardRecognition.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/19
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "AICommon.h"
#include "BlackBoardBase.h"
#include "Player.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************

class RecognitionBB : public BlackBoardBase
{
private:
	Player* opponentPlayer;						// �ΐ푊��
	D3DXVECTOR3 *myPosition;					// �����̍��W
	bool inAir;									// true �󒆂ɂ���  false �n��ɂ���
	bool isDown;								// �_�E������

public:
	RecognitionBB(void);
	void initialize(void) override;				// ����������

	// �ΐ푊����Z�b�g
	void setOpponentPlayer(Player* _opponentPlayer) { opponentPlayer = _opponentPlayer; }
	// �ΐ푊����擾
	Player* getOpponentPlayer(void) { return opponentPlayer; }

	D3DXVECTOR3* getMyPosition(void) { return myPosition; }
	void setMyPosition(D3DXVECTOR3* _position) { myPosition = _position; }
	bool getWhetherInAir(void) { return inAir; }
	void setWhetherInAir(bool setting) { inAir = setting; }
	bool getIsDown(void) { return isDown; }
	void setIsDown(bool setting) { isDown = setting; }
};