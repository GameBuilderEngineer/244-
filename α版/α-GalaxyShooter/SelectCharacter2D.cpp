//=============================================================================
// SelecCharacter�̕`�揈�� [SelectCharacter.cpp]
////=============================================================================
#include "SelectCharacter2D.h"

//*****************************************************************************
// �萔�E�}�N��
//*****************************************************************************
const static int		BG_WIDTH = WINDOW_WIDTH / 2;			// �Z���N�gBG���T�C�Y
const static int		BG_HEIGHT = WINDOW_HEIGHT;				// �Z���N�gBG�c�T�C�Y
const static int		PLAYER_WIDTH = WINDOW_WIDTH / 3;		// �Z���N�g�L�������T�C�Y
const static int		PLAYER_HEIGHT = WINDOW_HEIGHT;			// �Z���N�g�L�����c�T�C�Y
const static int		PLAYER_BG_WIDTH = WINDOW_WIDTH / 2;		// �v���C���[BG���T�C�Y
const static int		PLAYER_BG_HEIGHT = WINDOW_HEIGHT;		// �v���C���[BG�c�T�C�Y
const static float		POSITION_X_BG = 0.0f;					// X���W
const static float		POSITION_X_BG2 = POSITION_X_BG + WINDOW_WIDTH / 2;
const static float		POSITION_Y_BG = 0.0f;					// Y���W
const static float		POSITION_X_PLAYER = 0.0f;				// X���W
const static float		POSITION_Y_PLAYER = -20.0f;				// Y���W
const static float		POSITION2_X_PLAYER = POSITION_X_PLAYER + WINDOW_WIDTH / 2;
const static float		POSITION2_Y_PLAYER = -20.0f;			// Y���W
const static float		PLAYER_BG_POSITION_X = 0.0f;			// X���W
const static float		PLAYER_BG_POSITION2_X = PLAYER_BG_POSITION_X + WINDOW_WIDTH / 2;
const static float		PLAYER_BG_POSITION_Y = 0.0f;			// Y���W
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int SelectCharacter2D::cntUI = -1;
LPDIRECT3DTEXTURE9 SelectCharacter2D::selectBgTexture = NULL;		// �Z���N�gBG�e�N�X�`��
LPDIRECT3DTEXTURE9 SelectCharacter2D::selectPlayerTexture = NULL;	// �Z���N�g�v���C���[�e�N�X�`��
LPDIRECT3DTEXTURE9 SelectCharacter2D::selectPlayer2Texture = NULL;	// �Z���N�g�v���C���[2�e�N�X�`��
LPDIRECT3DTEXTURE9 SelectCharacter2D::select2PlayerTexture = NULL;	// �Z���N�g2�v���C���[�e�N�X�`��
LPDIRECT3DTEXTURE9 SelectCharacter2D::select2Player2Texture = NULL;	// �Z���N�g2�v���C���[2�e�N�X�`��
LPDIRECT3DTEXTURE9 SelectCharacter2D::selectPlayerBGTexture = NULL;	// �L�����Z���N�g�v���C���[BG�e�N�X�`��
//=============================================================================
// �R���X�g���N�^
//=============================================================================
SelectCharacter2D::SelectCharacter2D()
{
	cntUI++;
}


SelectCharacter2D::~SelectCharacter2D()
{
}


//=============================================================================
// ����������
//=============================================================================
HRESULT SelectCharacter2D::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader)
{
	playerNumber = _playerNumber;

	// �e�N�X�`����ǂݍ���
	setVisualDirectory();

	selectBgTexture = *textureLoader->getTexture(textureLoaderNS::SELECT);
	selectPlayerTexture = *textureLoader->getTexture(textureLoaderNS::SELECT_PLAYER);
	selectPlayer2Texture = *textureLoader->getTexture(textureLoaderNS::SELECT_PLAYER2);
	select2PlayerTexture = *textureLoader->getTexture(textureLoaderNS::SELECT_PLAYER);
	select2Player2Texture = *textureLoader->getTexture(textureLoaderNS::SELECT_PLAYER2);
	selectPlayerBGTexture = *textureLoader->getTexture(textureLoaderNS::CHARA_SELECT_BG);

	selectBG.initialize(device,
		selectBgTexture,					// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		BG_WIDTH,							// ����
		BG_HEIGHT,							// ����
		D3DXVECTOR3(playerNumber ? POSITION_X_BG2 : POSITION_X_BG, POSITION_Y_BG, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);

	selectPlayer.initialize(device,
		selectPlayerTexture,				// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_WIDTH,						// ����
		PLAYER_HEIGHT,						// ����
		D3DXVECTOR3(POSITION_X_PLAYER, POSITION_Y_PLAYER, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);

	selectPlayer2.initialize(device,
		selectPlayer2Texture,				// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_WIDTH,						// ����
		PLAYER_HEIGHT,						// ����
		D3DXVECTOR3(POSITION_X_PLAYER, POSITION_Y_PLAYER, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);

	select2Player.initialize(device,
		select2PlayerTexture,				// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_WIDTH,						// ����
		PLAYER_HEIGHT,						// ����
		D3DXVECTOR3(POSITION2_X_PLAYER, POSITION2_Y_PLAYER, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);

	select2Player2.initialize(device,
		select2Player2Texture,				// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_WIDTH,						// ����
		PLAYER_HEIGHT,						// ����
		D3DXVECTOR3(POSITION2_X_PLAYER, POSITION2_Y_PLAYER, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);

	charaSelectBG.initialize(device,
		selectPlayerBGTexture,			// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_BG_WIDTH,					// ����
		PLAYER_BG_HEIGHT,					// ����
		D3DXVECTOR3(playerNumber ? PLAYER_BG_POSITION2_X : PLAYER_BG_POSITION_X, PLAYER_BG_POSITION_Y, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void SelectCharacter2D::uninitialize(void)
{
	selectBG.setTexture(NULL);
	selectPlayer.setTexture(NULL);
	selectPlayer2.setTexture(NULL);
	select2Player.setTexture(NULL);
	select2Player2.setTexture(NULL);
	charaSelectBG.setTexture(NULL);

	// �C���X�^���X�����݂��Ȃ���΃e�N�X�`�����
	cntUI--;
	if (cntUI < 0)
	{
		SAFE_RELEASE(selectBgTexture)
		SAFE_RELEASE(selectPlayerTexture)
		SAFE_RELEASE(selectPlayer2Texture)
		SAFE_RELEASE(select2PlayerTexture)
		SAFE_RELEASE(select2Player2Texture)
		SAFE_RELEASE(selectPlayerBGTexture)
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void SelectCharacter2D::update(void)
{

}


//=============================================================================
// �`�揈��
//=============================================================================
void SelectCharacter2D::render(LPDIRECT3DDEVICE9 device,int selectNo, int select2No)
{
	selectBG.render(device);
	charaSelectBG.render(device);

	//1P�Z���N�g
	switch (selectNo)
	{
		// �v���C���[
	case 0:

		selectPlayer.render(device);

		break;
		// �v���C���[2
	case 1:

		selectPlayer2.render(device);

		break;
	}

	//2P�Z���N�g
	switch (select2No)
	{
		// �v���C���[
	case 0:

		select2Player.render(device);

		break;
		// �v���C���[2
	case 1:

		select2Player2.render(device);

		break;
	}

}

