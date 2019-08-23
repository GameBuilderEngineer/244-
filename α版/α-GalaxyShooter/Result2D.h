//=============================================================================
// ���U���g�`��w�b�_�[ [Result2D.h]
// ����� �ђˏt�P
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define RESULT2D_COLOR	(D3DCOLOR_RGBA(255, 255, 255, 255))	// ���U���g2D�̐F
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Result2D :public Sprite
{
private:
	// Data
	int playerNumber;											// �v���C���[�ԍ�
	static int cntUI;											// �C���X�^���X�̐��𐔂���
	static LPDIRECT3DTEXTURE9 result2DTexture;					// ���U���g2D�e�N�X�`��
	static LPDIRECT3DTEXTURE9 resultPlayerTexture;				// ���U���g�v���C���[�e�N�X�`��
	static LPDIRECT3DTEXTURE9 resultPlayer2Texture;				// ���U���g�v���C���[2�e�N�X�`��
	static LPDIRECT3DTEXTURE9 result2PlayerTexture;				// ���U���g2�v���C���[�e�N�X�`��
	static LPDIRECT3DTEXTURE9 result2Player2Texture;			// ���U���g2�v���C���[2�e�N�X�`��
	static LPDIRECT3DTEXTURE9 resultPlayerBGTexture;			// ���U���g�v���C���[BG�e�N�X�`��
	static LPDIRECT3DTEXTURE9 resultPlayerNumberTexture;		// ���U���g�v���C���[�i���o�[�e�N�X�`��
	static LPDIRECT3DTEXTURE9 resultPlayer2NumberTexture;		// ���U���g�v���C���[2�i���o�[�e�N�X�`��
	static LPDIRECT3DTEXTURE9 resultJadgeTexture;				// ���U���g�W���b�W�e�N�X�`��
	static LPDIRECT3DTEXTURE9 resultJadge2Texture;				// ���U���g�W���b�W2�e�N�X�`��
public:
	Result2D(void);
	~Result2D(void);
	Sprite resultPlayer;										// ���U���g�v���C���[
	Sprite resultPlayer2;										// ���U���g�v���C���[2
	Sprite result2Player;										// ���U���g2�v���C���[
	Sprite result2Player2;										// ���U���g2�v���C���[2
	Sprite charaResultBG;										// �L�����N�^�[���U���gBG
	Sprite resultPlayerNumber;									// ���U���g�v���C���[�i���o�[
	Sprite resultPlayer2Number;									// ���U���g�v���C���[2�i���o�[
	Sprite resultJadge;											// ���U���g�W���b�W
	Sprite resultJadge2;										// ���U���g�W���b�W2

	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device, int resultNo, int result2No);
};

