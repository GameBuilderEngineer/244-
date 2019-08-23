//=============================================================================
// ���U���g�`�揈�� [Result2D.cpp]
// ����� �ђˏt�P
////===========================================================================
#include "Result2D.h"
//*****************************************************************************
// �萔
//*****************************************************************************
const static int		WIDTH = WINDOW_WIDTH;												// ���U���g2D���T�C�Y
const static int		HEIGHT = WINDOW_HEIGHT;												// ���U���g2D�c�T�C�Y
const static int		PLAYER_WIDTH = WINDOW_WIDTH / 3;									// ���U���g�L�������T�C�Y
const static int		PLAYER_HEIGHT = WINDOW_HEIGHT;										// ���U���g�L�����c�T�C�Y
const static int		PLAYER_BG_WIDTH = WINDOW_WIDTH;										// �v���C���[BG���T�C�Y
const static int		PLAYER_BG_HEIGHT = WINDOW_HEIGHT /2;								// �v���C���[BG�c�T�C�Y
const static int		PLAYER_NUMBER_WIDTH = WINDOW_WIDTH / 4;								// ���U���g�L�����i���o�[���T�C�Y
const static int		PLAYER_NUMBER_HEIGHT = WINDOW_HEIGHT / 12;							// ���U���g�L�����i���o�[�c�T�C�Y
const static int		JUDGE_WIDTH = WINDOW_WIDTH / 4;										// ���U���g�W���b�W���T�C�Y
const static int		JUDGE_HEIGHT = WINDOW_HEIGHT / 12;									// ���U���g�W���b�W�c�T�C�Y
const static float		POSITION_X_PLAYER1 = 0.0f;											// ���U���g2DX���W
const static float		POSITION_Y = 0.0f;													// ���U���g2DY���W
#ifdef _DEBUG
const static float		POSITION_X_PLAYER = 80.0f;											// ���U���g�L����X���W
const static float		POSITION_Y_PLAYER = -20.0f;											// ���U���g�L����Y���W
const static float		POSITION2_X_PLAYER = POSITION_X_PLAYER + WINDOW_WIDTH / 2;			// ���U���g�L����2X���W
const static float		POSITION2_Y_PLAYER = -20.0f;										// ���U���g�L����Y���W
const static float		POSITION_X_PLAYER_NO = 110.0f;										// ���U���g�L�����i���o�[X���W
const static float		POSITION2_X_PLAYER_NO = POSITION_X_PLAYER_NO + WINDOW_WIDTH / 2;	// ���U���g�L����2�i���o�[X���W
const static float		POSITION_Y_PLAYER_NO = 220.0f;										// ���U���g�L�����i���o�[Y���W
const static float		POSITION_X_JUDGE = 110.0f;											// ���U���g�W���b�WX���W
const static float		POSITION2_X_JUDGE = POSITION_X_JUDGE + WINDOW_WIDTH / 2;			// ���U���g�W���b�W2X���W
const static float		POSITION_Y_JUDGE = 270.0f;											// ���U���g�W���b�WY���W
const static float		PLAYER_BG_POSITION_X = 0.0f;										// �v���C���[BGX���W
const static float		PLAYER_BG_POSITION_Y = 150.0f;										// �v���C���[BGY���W
#else
const static float		POSITION_X_PLAYER = 160.0f;											// �����[�X�����U���g�L����X���W
const static float		POSITION_Y_PLAYER = -40.0f;											// �����[�X�����U���g�L����Y���W
const static float		POSITION2_X_PLAYER = POSITION_X_PLAYER + WINDOW_WIDTH / 2;			// �����[�X�����U���g�L����2X���W
const static float		POSITION2_Y_PLAYER = -40.0f;										// �����[�X�����U���g�L����Y���W
const static float		POSITION_X_PLAYER_NO = 220.0f;										// �����[�X�����U���g�L�����i���o�[X���W
const static float		POSITION2_X_PLAYER_NO = POSITION_X_PLAYER_NO + WINDOW_WIDTH / 2;	// �����[�X�����U���g�L����2�i���o�[X���W
const static float		POSITION_Y_PLAYER_NO = 440.0f;										// �����[�X�����U���g�L�����i���o�[Y���W
const static float		POSITION_X_JUDGE = 220.0f;											// �����[�X�����U���g�W���b�WX���W
const static float		POSITION2_X_JUDGE = POSITION_X_JUDGE + WINDOW_WIDTH / 2;			// �����[�X�����U���g�W���b�W2X���W
const static float		POSITION_Y_JUDGE = 540.0f;											// �����[�X�����U���g�W���b�WY���W
const static float		PLAYER_BG_POSITION_X = 0.0f;										// �����[�X���v���C���[BGX���W
const static float		PLAYER_BG_POSITION_Y = 300.0f;										// �����[�X���v���C���[BGY���W
#endif 
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int Result2D::cntUI = -1;
LPDIRECT3DTEXTURE9 Result2D::result2DTexture = NULL;										// ���U���g2D�e�N�X�`��
LPDIRECT3DTEXTURE9 Result2D::resultPlayerTexture = NULL;									// ���U���g�v���C���[�e�N�X�`��
LPDIRECT3DTEXTURE9 Result2D::resultPlayer2Texture = NULL;									// ���U���g�v���C���[2�e�N�X�`��
LPDIRECT3DTEXTURE9 Result2D::result2PlayerTexture = NULL;									// ���U���g2�v���C���[�e�N�X�`��
LPDIRECT3DTEXTURE9 Result2D::result2Player2Texture = NULL;									// ���U���g2�v���C���[2�e�N�X�`��
LPDIRECT3DTEXTURE9 Result2D::resultPlayerBGTexture = NULL;									// �L�����Z���N�g�v���C���[BG�e�N�X�`��
LPDIRECT3DTEXTURE9 Result2D::resultPlayerNumberTexture = NULL;								// ���U���g�v���C���[�i���o�[�e�N�X�`��
LPDIRECT3DTEXTURE9 Result2D::resultPlayer2NumberTexture = NULL;								// ���U���g�v���C���[2�i���o�[�e�N�X�`��
LPDIRECT3DTEXTURE9 Result2D::resultJadgeTexture = NULL;										// ���U���g�W���b�W�e�N�X�`��
LPDIRECT3DTEXTURE9 Result2D::resultJadge2Texture = NULL;									// ���U���g�W���b�W2�e�N�X�`��
//=============================================================================
// �R���X�g���N�^
//=============================================================================
Result2D::Result2D()
{
	cntUI++;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
Result2D::~Result2D()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT Result2D::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader)
{
	// �v���C���[�i���o�[
	playerNumber = _playerNumber;

	// �e�N�X�`����ǂݍ���
	setVisualDirectory();

	result2DTexture = *textureLoader->getTexture(textureLoaderNS::RESULT);
	resultPlayerTexture = *textureLoader->getTexture(textureLoaderNS::SELECT_PLAYER);
	resultPlayer2Texture = *textureLoader->getTexture(textureLoaderNS::SELECT_PLAYER2);
	result2PlayerTexture = *textureLoader->getTexture(textureLoaderNS::SELECT_PLAYER);
	result2Player2Texture = *textureLoader->getTexture(textureLoaderNS::SELECT_PLAYER2);
	resultPlayerBGTexture = *textureLoader->getTexture(textureLoaderNS::CHARA_RESULT_BG);
	resultPlayerNumberTexture = *textureLoader->getTexture(textureLoaderNS::SELECT_PLAYER_NUMBER);
	resultPlayer2NumberTexture = *textureLoader->getTexture(textureLoaderNS::SELECT_PLAYER2_NUMBER);
	resultJadgeTexture = *textureLoader->getTexture(textureLoaderNS::WIN);
	resultJadge2Texture = *textureLoader->getTexture(textureLoaderNS::LOSE);

	// ���U���g2D������
	Sprite::initialize(device,
		result2DTexture,					// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		WIDTH,								// ����
		HEIGHT,								// ����
		D3DXVECTOR3(POSITION_X_PLAYER1, POSITION_Y, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		RESULT2D_COLOR						// �F
	);
	// ���U���g�L����������
	resultPlayer.initialize(device,
		resultPlayerTexture,				// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_WIDTH,						// ����
		PLAYER_HEIGHT,						// ����
		D3DXVECTOR3(POSITION_X_PLAYER, POSITION_Y_PLAYER, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		RESULT2D_COLOR						// �F
	);
	// ���U���g�L����2������
	resultPlayer2.initialize(device,
		resultPlayer2Texture,				// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_WIDTH,						// ����
		PLAYER_HEIGHT,						// ����
		D3DXVECTOR3(POSITION_X_PLAYER, POSITION_Y_PLAYER, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		RESULT2D_COLOR						// �F
	);
	// ���U���g2�L����������
	result2Player.initialize(device,
		result2PlayerTexture,				// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_WIDTH,						// ����
		PLAYER_HEIGHT,						// ����
		D3DXVECTOR3(POSITION2_X_PLAYER, POSITION2_Y_PLAYER, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		RESULT2D_COLOR						// �F
	);
	// ���U���g2�L����2������
	result2Player2.initialize(device,
		result2Player2Texture,				// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_WIDTH,						// ����
		PLAYER_HEIGHT,						// ����
		D3DXVECTOR3(POSITION2_X_PLAYER, POSITION2_Y_PLAYER, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		RESULT2D_COLOR						// �F
	);
	// �L�����N�^�[BG������
	charaResultBG.initialize(device,
		resultPlayerBGTexture,				// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_BG_WIDTH,					// ����
		PLAYER_BG_HEIGHT,					// ����
		D3DXVECTOR3(PLAYER_BG_POSITION_X, PLAYER_BG_POSITION_Y, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		RESULT2D_COLOR						// �F
	);
	// ���U���g�L�����i���o�[������
	resultPlayerNumber.initialize(device,
		resultPlayerNumberTexture,			// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_NUMBER_WIDTH,				// ����
		PLAYER_NUMBER_HEIGHT,				// ����
		D3DXVECTOR3(POSITION_X_PLAYER_NO, POSITION_Y_PLAYER_NO, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		RESULT2D_COLOR						// �F
	);
	// ���U���g�L����2�i���o�[������
	resultPlayer2Number.initialize(device,
		resultPlayer2NumberTexture,			// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_NUMBER_WIDTH,				// ����
		PLAYER_NUMBER_HEIGHT,				// ����
		D3DXVECTOR3(POSITION2_X_PLAYER_NO, POSITION_Y_PLAYER_NO, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		RESULT2D_COLOR						// �F
	);
	// �W���b�W������
	resultJadge.initialize(device,
		resultJadgeTexture,					// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		JUDGE_WIDTH,						// ����
		JUDGE_HEIGHT,						// ����
		D3DXVECTOR3(POSITION_X_JUDGE, POSITION_Y_JUDGE, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		RESULT2D_COLOR						// �F
	);
	// �W���b�W2������
	resultJadge2.initialize(device,
		resultJadge2Texture,				// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		JUDGE_WIDTH,						// ����
		JUDGE_HEIGHT,						// ����
		D3DXVECTOR3(POSITION2_X_JUDGE, POSITION_Y_JUDGE, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		RESULT2D_COLOR						// �F
	);

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void Result2D::uninitialize(void)
{
	setTexture(NULL);						// ���U���g2D�摜���
	resultPlayer.setTexture(NULL);			// ���U���g�L�����摜���
	resultPlayer2.setTexture(NULL);			// ���U���g�L����2�摜���
	result2Player.setTexture(NULL);			// ���U���g2�L�����摜���
	result2Player2.setTexture(NULL);		// ���U���g2�L����2�摜���
	charaResultBG.setTexture(NULL);			// �L�����N�^�[BG�摜���
	resultPlayerNumber.setTexture(NULL);	// ���U���g�L�����i���o�[�摜���
	resultPlayer2Number.setTexture(NULL);	// ���U���g�L����2�i���o�[�摜���
	resultJadge.setTexture(NULL);			// ���U���g�W���b�W�摜���
	resultJadge2.setTexture(NULL);			// ���U���g�W���b�W2�摜���

	// �C���X�^���X�����݂��Ȃ���΃e�N�X�`�����
	cntUI--;
	if (cntUI < 0)
	{
		SAFE_RELEASE(result2DTexture)
		SAFE_RELEASE(resultPlayerTexture)
		SAFE_RELEASE(resultPlayer2Texture)
		SAFE_RELEASE(result2PlayerTexture)
		SAFE_RELEASE(result2Player2Texture)
		SAFE_RELEASE(resultPlayerBGTexture)
		SAFE_RELEASE(resultPlayerNumberTexture)
		SAFE_RELEASE(resultPlayer2NumberTexture)
		SAFE_RELEASE(resultJadgeTexture)
		SAFE_RELEASE(resultJadge2Texture)
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void Result2D::update(void)
{
}
//=============================================================================
// �`�揈��
//=============================================================================
void Result2D::render(LPDIRECT3DDEVICE9 device, int resultNo, int result2No)
{
	// ���U���g2D�`��
	Sprite::render(device);

	// �L�����N�^�[BG�`��
	charaResultBG.render(device);

	//1P���U���g
	switch (resultNo)
	{
		// �v���C���[
	case 0:

		resultPlayer.render(device);

		break;
		// �v���C���[2
	case 1:

		resultPlayer2.render(device);

		break;
	}

	//2P���U���g
	switch (result2No)
	{
		// �v���C���[
	case 0:

		result2Player.render(device);

		break;
		// �v���C���[2
	case 1:

		result2Player2.render(device);

		break;
	}

	// �L�����N�^�[�i���o�[�`��
	resultPlayerNumber.render(device);

	// �L�����N�^�[�i���o�[2�`��
	resultPlayer2Number.render(device);

	// �W���b�W�`��
	resultJadge.render(device);

	// �W���b�W2�`��
	resultJadge2.render(device);
}
