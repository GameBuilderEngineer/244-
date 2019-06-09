//=============================================================================
// ���݂̕���UI���� [WeaponUI.h]
//
// Author : HAL�������ԕ� 2�N���Q�[���w�� GP12A332 32 �����a�P
// �쐬�� : 2019/6/9
//=============================================================================
#pragma once
#include "Sprite.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class WeaponUI :public Sprite{
	// �ǂ�����UI�ɂȂ邩������Ȃ����獡�͂����̃X�v���C�g

private:
	// Data
	int playerNumber;								// �v���C���[�ԍ�
	static int cntUI;								// �C���X�^���X�̐��𐔂���
	static LPDIRECT3DTEXTURE9 buffTexture;			// �e�N�X�`��

public:
	// Method
	WeaponUI(void);
	~WeaponUI(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber);	
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
};
