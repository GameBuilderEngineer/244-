//=============================================================================
// �^�C�}�[UI�w�b�_�[ [TimerUI.h]
// ����� �ђˏt�P
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TIMER_UI_COLOR	(D3DCOLOR_RGBA(255, 255, 255, 255))	// �^�C�}�[�̐F
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class TimerUI :public Sprite
{
private:
	// Data
	int playerNumber;								// �v���C���[�ԍ�
	static int cntUI;								// �C���X�^���X�̐��𐔂���
	static LPDIRECT3DTEXTURE9 timerTexture;			// �^�C�}�[�e�N�X�`��

public:
	// Method
	TimerUI(void);
	~TimerUI(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
};

