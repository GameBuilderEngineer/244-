//-----------------------------------------------------------------------------
// �g�̃u���b�N�{�[�h���� [BlackBoardBody.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/19
//-----------------------------------------------------------------------------
#include "AIcommon.h"
#include "BlackBoardBody.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
BodyBB::BodyBB(void)
{
	// No Process
}


//=============================================================================
// ����������
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

	aiCutLine = false;
	onceTriedCut = false;

	aiRevivalAction = false;
	revivalPointInterval = 0.0f;
	
}

//=============================================================================
// �ړ��^�[�Q�b�g�̍��W��V���ɐݒ肵�֘A�t���O���ݒ肷��
//=============================================================================
void BodyBB::configMovingDestination(D3DXVECTOR3* _destnation)
{
	if (movingDestination == _destnation)	return;

	movingDestination = _destnation;
	isArrived = false;
}