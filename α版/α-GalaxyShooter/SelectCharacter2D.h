//=============================================================================
// �Z���N�g�L�����N�^�[�`��w�b�_�[ [SelectCharacter.h]
// ����� �ђˏt�P
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SELECT2D_COLOR			(D3DCOLOR_RGBA(255, 255, 255, 255))	// �Z���N�g2D�̐F
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
	static LPDIRECT3DTEXTURE9 select2PlayerTexture;		// �Z���N�g2�v���C���[�e�N�X�`��
	static LPDIRECT3DTEXTURE9 select2Player2Texture;	// �Z���N�g2�v���C���[2�e�N�X�`��
	static LPDIRECT3DTEXTURE9 selectPlayerBGTexture;	// �Z���N�g�v���C���[BG�e�N�X�`��

	Sprite selectBG;									// �Z���N�gBG
	Sprite selectPlayer;								// �Z���N�g�v���C���[
	Sprite selectPlayer2;								// �Z���N�g�v���C���[2
	Sprite select2Player;								// �Z���N�g2�v���C���[
	Sprite select2Player2;								// �Z���N�g2�v���C���[2
	Sprite charaSelectBG;								// �L�����N�^�[�Z���N�gBG

public:
	SelectCharacter2D(void);
	~SelectCharacter2D(void);

	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device, int selectNo, int select2No);

};

