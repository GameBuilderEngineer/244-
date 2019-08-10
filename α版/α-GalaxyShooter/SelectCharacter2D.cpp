//=============================================================================
// �Z���N�g�L�����N�^�[�`�揈�� [SelectCharacter.cpp]
// ����� �ђˏt�P
////=============================================================================
#include "SelectCharacter2D.h"
//*****************************************************************************
// �萔
//*****************************************************************************
const static int		BG_WIDTH = WINDOW_WIDTH / 2;										// �Z���N�gBG���T�C�Y
const static int		BG_HEIGHT = WINDOW_HEIGHT;											// �Z���N�gBG�c�T�C�Y
const static int		PLAYER_WIDTH = WINDOW_WIDTH / 3;									// �Z���N�g�L�������T�C�Y
const static int		PLAYER_HEIGHT = WINDOW_HEIGHT;										// �Z���N�g�L�����c�T�C�Y
const static int		PLAYER_BG_WIDTH = WINDOW_WIDTH / 2;									// �v���C���[BG���T�C�Y
const static int		PLAYER_BG_HEIGHT = WINDOW_HEIGHT;									// �v���C���[BG�c�T�C�Y
const static float		POSITION_X_BG = 0.0f;												// �Z���N�gBGX���W
const static float		POSITION_X_BG2 = POSITION_X_BG + WINDOW_WIDTH / 2;					// �Z���N�gBG2X���W
const static float		POSITION_Y_BG = 0.0f;												// �Z���N�gBGY���W
const static float		PLAYER_BG_POSITION_X = 0.0f;										// �v���C���[BGX���W
const static float		PLAYER_BG_POSITION2_X = PLAYER_BG_POSITION_X + WINDOW_WIDTH / 2;	// �v���C���[BG2X���W
const static float		PLAYER_BG_POSITION_Y = 0.0f;										// �v���C���[BGY���W
#ifdef _DEBUG
const static float		POSITION_X_PLAYER = 0.0f;											// �Z���N�g�L����X���W
const static float		POSITION_Y_PLAYER = -20.0f;											// �Z���N�g�L����Y���W
const static float		POSITION2_X_PLAYER = POSITION_X_PLAYER + WINDOW_WIDTH / 2;			// �Z���N�g�L����2X���W
const static float		POSITION2_Y_PLAYER = -20.0f;										// �Z���N�g�L����Y���W
#else
const static float		POSITION_X_PLAYER = 0.0f;											// �����[�X���Z���N�g�L����X���W
const static float		POSITION_Y_PLAYER = -40.0f;											// �����[�X���Z���N�g�L����Y���W
const static float		POSITION2_X_PLAYER = POSITION_X_PLAYER + WINDOW_WIDTH / 2;			// �����[�X���Z���N�g�L����2X���W
const static float		POSITION2_Y_PLAYER = -40.0f;										// �����[�X���Z���N�g�L����Y���W
#endif 
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int SelectCharacter2D::cntUI = -1;
LPDIRECT3DTEXTURE9 SelectCharacter2D::selectBgTexture = NULL;								// �Z���N�gBG�e�N�X�`��
LPDIRECT3DTEXTURE9 SelectCharacter2D::selectPlayerTexture = NULL;							// �Z���N�g�v���C���[�e�N�X�`��
LPDIRECT3DTEXTURE9 SelectCharacter2D::selectPlayer2Texture = NULL;							// �Z���N�g�v���C���[2�e�N�X�`��
LPDIRECT3DTEXTURE9 SelectCharacter2D::select2PlayerTexture = NULL;							// �Z���N�g2�v���C���[�e�N�X�`��
LPDIRECT3DTEXTURE9 SelectCharacter2D::select2Player2Texture = NULL;							// �Z���N�g2�v���C���[2�e�N�X�`��
LPDIRECT3DTEXTURE9 SelectCharacter2D::selectPlayerBGTexture = NULL;							// �L�����Z���N�g�v���C���[BG�e�N�X�`��
//=============================================================================
// �R���X�g���N�^
//=============================================================================
SelectCharacter2D::SelectCharacter2D()
{
	cntUI++;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
SelectCharacter2D::~SelectCharacter2D()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT SelectCharacter2D::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader)
{
	// �v���C���[�i���o�[
	playerNumber = _playerNumber;

	// �e�N�X�`����ǂݍ���
	setVisualDirectory();

	selectBgTexture = *textureLoader->getTexture(textureLoaderNS::SELECT);
	selectPlayerTexture = *textureLoader->getTexture(textureLoaderNS::SELECT_PLAYER);
	selectPlayer2Texture = *textureLoader->getTexture(textureLoaderNS::SELECT_PLAYER2);
	select2PlayerTexture = *textureLoader->getTexture(textureLoaderNS::SELECT_PLAYER);
	select2Player2Texture = *textureLoader->getTexture(textureLoaderNS::SELECT_PLAYER2);
	selectPlayerBGTexture = *textureLoader->getTexture(textureLoaderNS::CHARA_SELECT_BG);

	// �Z���N�gBG������
	selectBG.initialize(device,
		selectBgTexture,					// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		BG_WIDTH,							// ����
		BG_HEIGHT,							// ����
		D3DXVECTOR3(playerNumber ? POSITION_X_BG2 : POSITION_X_BG, POSITION_Y_BG, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		SELECT2D_COLOR						// �F
	);
	// �Z���N�g�L����������
	selectPlayer.initialize(device,
		selectPlayerTexture,				// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_WIDTH,						// ����
		PLAYER_HEIGHT,						// ����
		D3DXVECTOR3(POSITION_X_PLAYER, POSITION_Y_PLAYER, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		SELECT2D_COLOR						// �F
	);
	// �Z���N�g�L����2������
	selectPlayer2.initialize(device,
		selectPlayer2Texture,				// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_WIDTH,						// ����
		PLAYER_HEIGHT,						// ����
		D3DXVECTOR3(POSITION_X_PLAYER, POSITION_Y_PLAYER, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		SELECT2D_COLOR						// �F
	);
	// �Z���N�g2�L����������
	select2Player.initialize(device,
		select2PlayerTexture,				// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_WIDTH,						// ����
		PLAYER_HEIGHT,						// ����
		D3DXVECTOR3(POSITION2_X_PLAYER, POSITION2_Y_PLAYER, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		SELECT2D_COLOR						// �F
	);
	// �Z���N�g2�L����2������
	select2Player2.initialize(device,
		select2Player2Texture,				// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_WIDTH,						// ����
		PLAYER_HEIGHT,						// ����
		D3DXVECTOR3(POSITION2_X_PLAYER, POSITION2_Y_PLAYER, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		SELECT2D_COLOR						// �F
	);
	// �L�����N�^�[BG������
	charaSelectBG.initialize(device,
		selectPlayerBGTexture,			// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_BG_WIDTH,					// ����
		PLAYER_BG_HEIGHT,					// ����
		D3DXVECTOR3(playerNumber ? PLAYER_BG_POSITION2_X : PLAYER_BG_POSITION_X, PLAYER_BG_POSITION_Y, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		SELECT2D_COLOR						// �F
	);

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void SelectCharacter2D::uninitialize(void)
{
	selectBG.setTexture(NULL);			// �Z���N�gBG�摜���
	selectPlayer.setTexture(NULL);		// �Z���N�g�L�����摜���
	selectPlayer2.setTexture(NULL);		// �Z���N�g�L����2�摜���
	select2Player.setTexture(NULL);		// �Z���N�g2�L�����摜���
	select2Player2.setTexture(NULL);	// �Z���N�g2�L����2�摜���
	charaSelectBG.setTexture(NULL);		// �L�����N�^�[BG�摜���

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
	// �Z���N�gBG�`��
	selectBG.render(device);

	// �L�����N�^�[BG�`��
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

