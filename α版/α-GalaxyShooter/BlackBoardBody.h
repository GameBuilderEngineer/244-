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
	bool isMoving;
public:
	D3DXVECTOR3* movingDestination;				// 移動先座標（ビヘイビアツリー中で切り替わる）

	bool jump;
	bool isJumping;
	bool isAir;


public:
	BodyBB(void);
	~BodyBB(void);
	void initialize(void) override;				// 初期化処理
	void uninitialize(void) override;			// 終了処理


	bool getJump(void) { return jump; }
	bool getIsJumping(void) { return isJumping; }
	bool getIsAir(void) { return isAir; }

	void setJump(bool _jump) { jump = _jump; }
	void setIsJumping(bool _isJumping) { isJumping = _isJumping; }
	void setIsAir(bool _isAir) { isAir = _isAir; }


	// 移動状態を取得
	bool getMove(void) { return isMoving; }
	// 移動状態を設定
	void setMove(bool setting) { isMoving = setting; }
	// 移動ターゲットの座標ポインタを取得
	D3DXVECTOR3* getMovingDestination(void)
	{
		return movingDestination;
	}
	// 移動ターゲットの座標ポインタを設定
	void setMovingDestination(D3DXVECTOR3* _destnation) 
	{ 
		movingDestination = _destnation;
	}
};