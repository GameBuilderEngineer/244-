//-----------------------------------------------------------------------------
// �g�̃u���b�N�{�[�h���� [BlackBoardBody.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/19
//-----------------------------------------------------------------------------
#pragma once;
#include "BlackBoardBase.h"
#include "Player.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class BodyBB : public BlackBoardBase {
protected:
	//------
	// Data
	//------
	bool aiMove;							// true �ړ�����@false �ړ����Ȃ�
	D3DXVECTOR3* movingDestination;			// �ړ�����W�i�r�w�C�r�A�c���[���Ő؂�ւ��j
	bool isArrived;							// true ���������@false �������Ă��Ȃ�
	float speed;							// �ړ��X�s�[�h
	bool aiJump;							// true �W�����v����@false �W�����v���Ȃ�
	bool onceJumped;						// true �W�����v�ς݁@false�@���W�����v
											// ��Player::jump()���s������true
	bool aiShoot;							// true �o���b�g��ł@false �o���b�g��ł��Ȃ�
	D3DXVECTOR3 target;						// �o���b�g�̃^�[�Q�b�g���W	
	float shootingInterval;					// �o���b�g���˃C���^�[�o��
	bool aiLocatePile;						// true �p�C���ݒu����@false �p�C���ݒu���Ȃ�
	bool isPileReady;						// true �p�C���ݒu�\�@false �p�C���ݒu�s��
	bool aiCutLine;							// true ���C���؂�@false ���C���؂�Ȃ�
	bool onceTriedCut;						// true ���C���ؒf���s�ς݁@false ���C���ؒf���s���Ă��Ȃ�
	bool aiRevivalAction;					// true �_�E�������A�N�V��������@false �_�E�������A�N�V�������Ȃ�
	float revivalPointInterval;				// �����|�C���g�̉��Z�C���^�[�o���^�C��


public:
	//--------
	// Method
	//--------
	BodyBB(void);
	void initialize(void) override;									// ������

	// �ړ�
	bool getMove(void) { return aiMove; }							// �ړ����擾
	void setMove(bool setting) { aiMove = setting; }				// �ړ���ݒ�
	D3DXVECTOR3* getMovingDestination(void) { return movingDestination; }// �ړI�n�̍��W�|�C���^���擾
	void configMovingDestination(D3DXVECTOR3* _destnation);			// �ړI�n���W��V���ɐݒ肵�֘A�t���O���ݒ肷��
	bool getIsArrived(void) { return isArrived; }					// �ړI�n�����������擾
	void setIsArrival(bool setting) { isArrived = setting; }		// �ړI�n������������ݒ�
	float getSpeed(void) { return speed; }							// �ړ��X�s�[�h���擾
	void setSpeed(const float _speed) { speed = _speed; }			// �ړ��X�s�[�h��ݒ�
	const float MOVING_SPEED = playerNS::SPEED;
	const float MOVING_SLOW_SPEED = playerNS::SPEED / 5.0f;

	// �W�����v
	bool getJump(void) { return aiJump; }							// �W�����v���擾
	void setJump(bool setting) { aiJump = setting; }				// �W�����v��ݒ�
	bool whetherJumpedOnce(void) { return onceJumped; }				// �W�����v�����̎擾
	void setJumpedHistory(bool setting) { onceJumped = setting; }	// �W�����v�����̐ݒ�

	// �o���b�g
	bool getShootingBullet(void) { return aiShoot; }				// �o���b�g��ł��擾
	void setShootingBullet(bool setting) { aiShoot = setting; }		// �o���b�g��ł��ݒ�
	D3DXVECTOR3 getTargetCoordValue(void) { return target; }		// �^�[�Q�b�g���W�̎擾		���|�C���^����Ȃ��I
	void setTargetCoordValue(D3DXVECTOR3 setting) { target = setting; }// �^�[�Q�b�g���W�̐ݒ�	���|�C���^��������񂵂��ǂ��C������
	float getShootingInterval(void) { return shootingInterval; }	// �o���b�g���˃C���^�[�o���^�C���̎擾
	void setShootingInterval(float currentValue) { shootingInterval = currentValue; }// �o���b�g���˃C���^�[�o���^�C���̐ݒ�

	// �������[�p�C��
	bool getLocatingPile(void) { return aiLocatePile; }				// �p�C���ݒu���邩�擾
	void setLocatingPile(bool setting) { aiLocatePile = setting; }	// �p�C���ݒu��ݒ�
	bool getIsReadyForPile(void) { return isPileReady; }			// �p�C���ݒu�\���擾
	void setIsReadyForPile(bool setting) { isPileReady = setting; }	// �p�C���ݒu�\���ݒ�

	// �������[���C��
	bool getCuttingLine(void) { return aiCutLine; }					// �������[���C����؂邩�擾
	void setCuttingLine(bool setting) { aiCutLine = setting; }		// �������[���C����؂邩�ݒ�
	bool getOnceTriedCut(void) { return onceTriedCut; }				// �������\���C���ؒf�����s�ς݂��擾
	void setOnceTriedCut(bool setting) { onceTriedCut = setting; }	// �������[���C���ؒf�𖢎��s���擾

	// �_�E������
	bool getRevivalAction(void) { return aiRevivalAction; }			// �_�E�������A�N�V���������邩�擾
	void setRevivalAction(bool setting) { aiRevivalAction = setting; }// �_�E�������A�N�V���������邩�ݒ�
	float getRevivalPointInterval(void) { return revivalPointInterval; }// �����|�C���g�̉��Z�C���^�[�o���^�C�����擾
	void setRevivalPointInterval(float setting) { revivalPointInterval = setting; }// �����|�C���g�̉��Z�C���^�[�o���^�C����ݒ�
};