//-----------------------------------------------------------------------------
// 身体ブラックボード処理 [BlackBoardBody.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/19
//-----------------------------------------------------------------------------
#include "AIcommon.h"
#include "BlackBoardBody.h"

//=============================================================================
// コンストラクタ
//=============================================================================
BodyBB::BodyBB(void)
{
	// No Process
}


//=============================================================================
// 初期化処理
//=============================================================================
void BodyBB::initialize(void)
{
	aiMove = false;
	movingDestination = NULL;
	isArrived = false;
	speed = MOVING_SPEED;

	aiJump = false;
	onceJumped = false;
	
	aiShoot = false;
	target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	shootingInterval = 0.0f;

	aiLocatePile = false;
	isPileReady = false;
}

//=============================================================================
// 移動ターゲットの座標を新たに設定し関連フラグも設定する
//=============================================================================
void BodyBB::configMovingDestination(D3DXVECTOR3* _destnation)
{
	if (movingDestination == _destnation)	return;

	movingDestination = _destnation;
	isArrived = false;
}