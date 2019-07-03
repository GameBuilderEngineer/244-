//=============================================================================
// SelectCharacter�`�揈�� [SelectCharacter.h]
//
//=============================================================================
#pragma once
#include "Sprite.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class SelectCharacter2D :public Sprite
{
private:
	// Data
	int playerNumber;								// �v���C���[�ԍ�
	static int cntUI;								// �C���X�^���X�̐��𐔂���
	static LPDIRECT3DTEXTURE9 buffTexture;			// �e�N�X�`��

public:
	SelectCharacter2D(void);
	~SelectCharacter2D(void);

	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);

};

