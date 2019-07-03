//=============================================================================
// Title�`�揈�� [Title2D.h]
//
//=============================================================================
#pragma once
#include "Sprite.h"
#include "Input.h"


#define TITLE2D_COLOR		(D3DCOLOR_RGBA(255, 255, 255, 255))	// �^�C�g���̐F
#define CNT_TITLE_MAX		(4)									// �I��UI����l
#define CNT_TITLE_START		(322)								// �I��UI�X�^�[�g�l
#define CNT_TITLE_TUTORIAL	(390)								// �I��UI�`���[�g���A���l
#define CNT_TITLE_OPERATION	(458)								// �I��UI������@�l
#define CNT_TITLE_CREDIT	(522)								// �I��UI�N���W�b�g�l
#define CNT_TITLE_END		(590)								// �I��UI�I���l

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Title2D :public Sprite
{
private:
	// Data
	int playerNumber;											// �v���C���[�ԍ�
	static int cntUI;											// �C���X�^���X�̐��𐔂���
	static LPDIRECT3DTEXTURE9 titleTexture2D;					// �^�C�g��2D�e�N�X�`��
	static LPDIRECT3DTEXTURE9 choiceTexture;					// �I���摜
	Sprite title2D;												// �^�C�g��2D
	Sprite choice;												// �I���摜
public:
	Title2D(void);
	~Title2D(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
	void titleUImove(void);										// �I��UI�ړ�����
	int	cntTitle;												// �I��UI�ʒu
};

