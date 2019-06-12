//=============================================================================
// SP��UI���� [SkillPointUI.h]
//
// Author : HAL�������ԕ� 2�N���Q�[���w�� GP12A332 32 �����a�P
// �쐬�� : 2019/6/9
//=============================================================================
#pragma once
#include "Sprite.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class SkillPointUI {
private:
	// Data
	int playerNumber;								// �v���C���[�ԍ�
	static int cntUI;								// �C���X�^���X�̐��𐔂���
	static LPDIRECT3DTEXTURE9 textureGaugeBase;		// �e�N�X�`���P
	static LPDIRECT3DTEXTURE9 textureGaugeBar;		// �e�N�X�`���Q
	static LPDIRECT3DTEXTURE9 textureGaugeCover;	// �e�N�X�`���R
	Sprite gaugeBase;								// �Q�[�W�x�[�X
	Sprite gaugeBar;								// �Q�[�W�o�[
	Sprite gaugeCover;								// �Q�[�W�J�o�[

public:
	// Method
	SkillPointUI(void);
	~SkillPointUI(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber);	
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
};
