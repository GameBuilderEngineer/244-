//-----------------------------------------------------------------------------
// 身体ブラックボード処理 [BlackBoardBody.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/19
//-----------------------------------------------------------------------------
#pragma once;
#include "BlackBoardBase.h"

//*****************************************************************************
// クラス定義
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
	void initialize(void) override;				// 初期化処理
	void uninitialize(void) override;			// 終了処理

	bool getIsMoving(void) { return isMoving; }
	bool getJump(void) { return jump; }
	bool getIsJumping(void) { return isJumping; }

	void setJump(bool _jump) { jump = _jump; }
	void setIsJumping(bool _isJumping) { isJumping = _isJumping; }
};