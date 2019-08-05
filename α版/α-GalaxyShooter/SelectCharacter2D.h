//=============================================================================
// SelectCharacter�`�揈�� [SelectCharacter.h]
//
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"

#define DEFAULT_COLOR			(D3DCOLOR_RGBA(255, 255, 255, 255))	// �Z���N�g�̐F
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class SelectCharacter2D :public Sprite
{
private:
	// Data
	int playerNumber;									// �v���C���[�ԍ�
	static int cntUI;									// �C���X�^���X�̐��𐔂���
	static LPDIRECT3DTEXTURE9 selectBgTexture;			// �Z���N�gBG�e�N�X�`��
	static LPDIRECT3DTEXTURE9 selectPlayerTexture;		// �Z���N�g�v���C���[�e�N�X�`��
	static LPDIRECT3DTEXTURE9 selectPlayer2Texture;		// �Z���N�g�v���C���[2�e�N�X�`��
	static LPDIRECT3DTEXTURE9 select2PlayerTexture;		// �Z���N�g�v���C���[�e�N�X�`��
	static LPDIRECT3DTEXTURE9 select2Player2Texture;	// �Z���N�g�v���C���[2�e�N�X�`��
	static LPDIRECT3DTEXTURE9 selectPlayerBGTexture;	// �Z���N�g�v���C���[BG�e�N�X�`��

	Sprite selectBG;
	Sprite selectPlayer;
	Sprite selectPlayer2;
	Sprite select2Player;
	Sprite select2Player2;
	Sprite charaSelectBG;

public:
	SelectCharacter2D(void);
	~SelectCharacter2D(void);

	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device, int selectNo, int select2No);

};

