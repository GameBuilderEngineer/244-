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
	bool isMoving;
public:
	D3DXVECTOR3* movingDestination;				// �ړ�����W�i�r�w�C�r�A�c���[���Ő؂�ւ��j

	bool jump;
	bool isJumping;
	bool isAir;


public:
	BodyBB(void);
	~BodyBB(void);
	void initialize(void) override;				// ����������
	void uninitialize(void) override;			// �I������


	bool getJump(void) { return jump; }
	bool getIsJumping(void) { return isJumping; }
	bool getIsAir(void) { return isAir; }

	void setJump(bool _jump) { jump = _jump; }
	void setIsJumping(bool _isJumping) { isJumping = _isJumping; }
	void setIsAir(bool _isAir) { isAir = _isAir; }


	// �ړ���Ԃ��擾
	bool getMove(void) { return isMoving; }
	// �ړ���Ԃ�ݒ�
	void setMove(bool setting) { isMoving = setting; }
	// �ړ��^�[�Q�b�g�̍��W�|�C���^���擾
	D3DXVECTOR3* getMovingDestination(void)
	{
		return movingDestination;
	}
	// �ړ��^�[�Q�b�g�̍��W�|�C���^��ݒ�
	void setMovingDestination(D3DXVECTOR3* _destnation) 
	{ 
		movingDestination = _destnation;
	}
};