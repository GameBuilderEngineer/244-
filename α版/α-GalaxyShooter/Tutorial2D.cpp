//=============================================================================
// �`���[�g���A���̕`�揈�� [Tutorial2D.cpp]
// ����� �ђˏt�P
////===========================================================================
#include "Tutorial2D.h"
//*****************************************************************************
// �萔
//*****************************************************************************
const static int		WIDTH = ((3840 / 2) - 16);					// �`���[�g���A��2D���T�C�Y
const static int		HEIGHT = ((2160 / 2) - 9);					// �`���[�g���A��2D�c�T�C�Y
const static float		POSITION_X = ((WINDOW_WIDTH / 2) - 8.5f);	// �`���[�g���A��2DX���W
const static float		POSITION_Y = ((WINDOW_HEIGHT / 2) - 10.0f);	// �`���[�g���A��2DY���W
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int Tutorial2D::cntUI = -1;
LPDIRECT3DTEXTURE9 Tutorial2D::textureTutorial2D = NULL;			// �`���[�g���A��2D�e�N�X�`��
LPDIRECT3DTEXTURE9 Tutorial2D::textureTutorial2D2 = NULL;			// �`���[�g���A��2D2�e�N�X�`��
LPDIRECT3DTEXTURE9 Tutorial2D::textureTutorial2D3 = NULL;			// �`���[�g���A��2D3�e�N�X�`��
LPDIRECT3DTEXTURE9 Tutorial2D::textureTutorial2D4 = NULL;			// �`���[�g���A��2D4�e�N�X�`��
//=============================================================================
// �R���X�g���N�^
//=============================================================================
Tutorial2D::Tutorial2D()
{
	cntUI++;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
Tutorial2D::~Tutorial2D()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT Tutorial2D::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader)
{
	// �v���C���[�i���o�[
	playerNumber = _playerNumber;

	// �e�N�X�`����ǂݍ���
	setVisualDirectory();

	textureTutorial2D = *textureLoader->getTexture(textureLoaderNS::TUTORIAL);
	textureTutorial2D2 = *textureLoader->getTexture(textureLoaderNS::TUTORIAL2);
	textureTutorial2D3 = *textureLoader->getTexture(textureLoaderNS::TUTORIAL3);
	textureTutorial2D4 = *textureLoader->getTexture(textureLoaderNS::TUTORIAL4);

	// �`���[�g���A���̃y�[�W
	next = 0;

	// �`���[�g���A��2D������
	Sprite::initialize(device,
		textureTutorial2D,							// �e�N�X�`��
		spriteNS::CENTER,							// ���_
		WIDTH,										// ����
		HEIGHT,										// ����
		D3DXVECTOR3(POSITION_X, POSITION_Y, 0.0f),	// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// ��]
		TUTORIAL2D_COLOR							// �F
	);

	// �`���[�g���A��2D2������
	tuto2.initialize(device,
		textureTutorial2D2,							// �e�N�X�`��
		spriteNS::CENTER,							// ���_
		WIDTH,										// ����
		HEIGHT,										// ����
		D3DXVECTOR3(POSITION_X, POSITION_Y, 0.0f),	// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// ��]
		TUTORIAL2D_COLOR							// �F
	);

	// �`���[�g���A��2D3������
	tuto3.initialize(device,
		textureTutorial2D3,							// �e�N�X�`��
		spriteNS::CENTER,							// ���_
		WIDTH,										// ����
		HEIGHT,										// ����
		D3DXVECTOR3(POSITION_X, POSITION_Y, 0.0f),	// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// ��]
		TUTORIAL2D_COLOR							// �F
	);

	// �`���[�g���A��2D4������
	tuto4.initialize(device,
		textureTutorial2D4,							// �e�N�X�`��
		spriteNS::CENTER,							// ���_
		WIDTH,										// ����
		HEIGHT,										// ����
		D3DXVECTOR3(POSITION_X, POSITION_Y, 0.0f),	// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// ��]
		TUTORIAL2D_COLOR							// �F
	);

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void Tutorial2D::uninitialize(void)
{
}
//=============================================================================
// �X�V����
//=============================================================================
void Tutorial2D::update(void)
{

}
//=============================================================================
// �`�揈��
//=============================================================================
void Tutorial2D::render(LPDIRECT3DDEVICE9 device)
{
	switch (next)
	{
	case 0:
		// �`���[�g���A��2D�`��
		Sprite::render(device);

		break;
	case 1:
		// �`���[�g���A��2D2�`��
		tuto2.render(device);

		break;
	case 2:
		// �`���[�g���A��2D4�`��
		tuto4.render(device);

		break;
	case 3:
		// �`���[�g���A��2D3�`��
		tuto3.render(device);

		break;

	}

}
