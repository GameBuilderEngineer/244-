//=============================================================================
// �R���j�[HP���� [ColonyHp.h]
//
// Author : HAL�������ԕ� 2�N���Q�[���w�� GP12A332 32 �����a�P
// �쐬�� : 2019/6/1
//=============================================================================
//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#pragma once
#include "Main.h"
#include "Quad.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COLONY_HP_SIZE_X		(150)				// �R���j�[HP����
#define COLONY_HP_SIZE_Y		(200)				// �R���j�[HP����


//*****************************************************************************
// �N���X��`
//*****************************************************************************

class ColonyHp :public Quad {
private:
	LPDIRECT3DTEXTURE9		pTexture;				// �e�N�X�`���ւ̃|�C���^
	void release(void);								// �e�N�X�`�����

public:
	HRESULT initialize(int type);					// ����������
	void uninitialize(void);						// �I������
	void update(void);								// �X�V����
	void draw(void);								// �`�揈��

	// �R���X�g���N�^�E�f�X�g���N�^
	ColonyHp(void);
	ColonyHp(int sizeX, int sizeY, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DCOLOR color);
	~ColonyHp(void);

	// �A�N�Z�T
	LPDIRECT3DTEXTURE9 ColonyHp::getTexture(void) { return pTexture; }		// �e�N�X�`�����擾
	LPDIRECT3DTEXTURE9* ColonyHp::getAdrTexture(void) { return &pTexture; }	// �e�N�X�`���ւ̃|�C���^�̃A�h���X���擾
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
// �R���j�[HP���擾
ColonyHp *getColonyHp(void);