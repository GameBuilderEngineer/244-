//-----------------------------------------------------------------------------
// �g�̃u���b�N�{�[�h���� [BlackBoardBody.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/19
//-----------------------------------------------------------------------------
#pragma once;
#include "BlackBoardBase.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class BodyBB : public BlackBoardBase {
protected:
	// Data
	bool isMoving;
	bool jump;
	bool isJumping;
	bool isAir;

public:
	// Method
	BodyBB(void);
	~BodyBB(void);
	void initialize(void) override;				// ����������
	void uninitialize(void) override;			// �I������

	bool getIsMoving(void) { return isMoving; }
	bool getJump(void) { return jump; }
	bool getIsJumping(void) { return isJumping; }

	void setJump(bool _jump) { jump = _jump; }
	void setIsJumping(bool _isJumping) { isJumping = _isJumping; }
};