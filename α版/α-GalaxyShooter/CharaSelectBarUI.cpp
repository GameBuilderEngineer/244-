//=============================================================================
// �L�����Z���N�g�o�[UI���� [CharaSelectBarUI.cpp]
//
//=============================================================================
#include "CharaSelectBarUI.h"
using namespace charaSelectBarUINS;

//*****************************************************************************
// �萔�E�}�N��
//*****************************************************************************
const static int		BAR_WIDTH = WINDOW_WIDTH/2;						// ���T�C�Y
const static int		BAR_HEIGHT = 250;								// �c�T�C�Y
const static int		NO_WIDTH = 180;									// ���T�C�Y
const static int		NO_HEIGHT = 82;									// �c�T�C�Y
const static int		CURSOR_WIDTH = WINDOW_WIDTH / 2;				// ���T�C�Y
const static int		CURSOR_HEIGHT = 40;								// �c�T�C�Y
const static int		PLAYER_LOGO_WIDTH = 80;							// ���T�C�Y
const static int		PLAYER_LOGO_HEIGHT = 40;						// �c�T�C�Y
const static float		BAR_LIGHT_POSITION_X = 0.0f;					// X���W
const static float		BAR_LIGHT_POSITION2_X = BAR_LIGHT_POSITION_X+ WINDOW_WIDTH / 2;
const static float		BAR_LIGHT_POSITION_Y = 220.0f;					// Y���W
const static float		NO_POSITION_X = 0.0f;							// X���W
const static float		NO_POSITION2_X = NO_POSITION_X + WINDOW_WIDTH / 2;
const static float		NO_POSITION_Y = 304.0f;							// Y���W
const static float		CURSOR_POSITION_X = 0.0f;						// X���W
const static float		CURSOR_POSITION2_X = CURSOR_POSITION_X + WINDOW_WIDTH / 2;
const static float		CURSOR_POSITION_Y = 250.0f;						// Y���W
const static float		PLAYER_LOGO_POSITION_X = 0.0f;					// X���W
const static float		PLAYER_LOGO_POSITION2_X = PLAYER_LOGO_POSITION_X + WINDOW_WIDTH / 2;
const static float		PLAYER_LOGO_POSITION_Y = 390.0f;				// Y���W
#define DEFAULT_COLOR	(D3DCOLOR_RGBA(255, 255, 255, 255))				// �L�����Z���N�g�o�[�̐F
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int CharaSelectBarUI::cntUI = -1;
LPDIRECT3DTEXTURE9 CharaSelectBarUI::selectBarLightTexture = NULL;		// �L�����Z���N�g�o�[�e�N�X�`��
LPDIRECT3DTEXTURE9 CharaSelectBarUI::selectBarLightTexture2 = NULL;		// �L�����Z���N�g�o�[�e�N�X�`��2
LPDIRECT3DTEXTURE9 CharaSelectBarUI::selectNoTexture = NULL;			// �L�����Z���N�g�i���o�[�e�N�X�`��
LPDIRECT3DTEXTURE9 CharaSelectBarUI::selectNoTexture2 = NULL;			// �L�����Z���N�g�i���o�[�e�N�X�`��2
LPDIRECT3DTEXTURE9 CharaSelectBarUI::selectCursorTexture = NULL;		// �L�����Z���N�g�J�[�\���e�N�X�`��
LPDIRECT3DTEXTURE9 CharaSelectBarUI::selectCursorTexture2 = NULL;		// �L�����Z���N�g�J�[�\���e�N�X�`��2
LPDIRECT3DTEXTURE9 CharaSelectBarUI::selectPlayerLogoTexture = NULL;	// �L�����Z���N�g�v���C���[���S�e�N�X�`��
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CharaSelectBarUI::CharaSelectBarUI(void)
{
	cntUI++;
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
CharaSelectBarUI::~CharaSelectBarUI(void)
{
}


//=============================================================================
// ����������
//=============================================================================
HRESULT CharaSelectBarUI::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader)
{
	playerNumber = _playerNumber;

	// �e�N�X�`����ǂݍ���
	setVisualDirectory();

	selectBarLightTexture = *textureLoader->getTexture(textureLoaderNS::UI_CHARA_SELECT_BAR);
	selectBarLightTexture2 = *textureLoader->getTexture(textureLoaderNS::UI_CHARA_SELECT_BAR2);
	selectNoTexture = *textureLoader->getTexture(textureLoaderNS::UI_CHARA_SELECT_NO);
	selectNoTexture2 = *textureLoader->getTexture(textureLoaderNS::UI_CHARA_SELECT_NO2);
	selectCursorTexture = *textureLoader->getTexture(textureLoaderNS::UI_CHARA_SELECT_CURSOR);
	selectCursorTexture2 = *textureLoader->getTexture(textureLoaderNS::UI_CHARA_SELECT_CURSOR2);
	selectPlayerLogoTexture = *textureLoader->getTexture(textureLoaderNS::UI_CHARA_SELECT_LOGO);

	charaSelectBar.initialize(device,
		selectBarLightTexture,				// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		BAR_WIDTH,							// ����
		BAR_HEIGHT,							// ����
		D3DXVECTOR3(BAR_LIGHT_POSITION_X, BAR_LIGHT_POSITION_Y, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);

	charaSelectBar2.initialize(device,
		selectBarLightTexture2,				// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		BAR_WIDTH,							// ����
		BAR_HEIGHT,							// ����
		D3DXVECTOR3(BAR_LIGHT_POSITION2_X, BAR_LIGHT_POSITION_Y, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);

	charaSelectNo.initialize(device,
		selectNoTexture,					// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		NO_WIDTH,							// ����
		NO_HEIGHT,							// ����
		D3DXVECTOR3(NO_POSITION_X, NO_POSITION_Y, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);

	charaSelectNo2.initialize(device,
		selectNoTexture2,					// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		NO_WIDTH,							// ����
		NO_HEIGHT,							// ����
		D3DXVECTOR3(NO_POSITION2_X, NO_POSITION_Y, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);

	charaSelectCursor.initialize(device,
		selectCursorTexture,				// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		CURSOR_WIDTH,						// ����
		CURSOR_HEIGHT,						// ����
		D3DXVECTOR3(CURSOR_POSITION_X, CURSOR_POSITION_Y, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);

	charaSelectCursor2.initialize(device,
		selectCursorTexture2,				// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		CURSOR_WIDTH,						// ����
		CURSOR_HEIGHT,						// ����
		D3DXVECTOR3(CURSOR_POSITION2_X, CURSOR_POSITION_Y, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);

	charaSelectLogo.initialize(device,
		selectPlayerLogoTexture,			// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_LOGO_WIDTH,					// ����
		PLAYER_LOGO_HEIGHT,					// ����
		D3DXVECTOR3(playerNumber ? PLAYER_LOGO_POSITION2_X : PLAYER_LOGO_POSITION_X, PLAYER_LOGO_POSITION_Y, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);

	return S_OK;
}


//=============================================================================
// �I������
//=============================================================================
void CharaSelectBarUI::uninitialize(void)
{
	charaSelectBar.setTexture(NULL);
	charaSelectBar2.setTexture(NULL);
	charaSelectNo.setTexture(NULL);
	charaSelectNo2.setTexture(NULL);
	charaSelectCursor.setTexture(NULL);
	charaSelectCursor2.setTexture(NULL);
	charaSelectLogo.setTexture(NULL);
	// �C���X�^���X�����݂��Ȃ���΃e�N�X�`�����
	cntUI--;
	if (cntUI < 0)
	{
		SAFE_RELEASE(selectBarLightTexture)
		SAFE_RELEASE(selectBarLightTexture2)
		SAFE_RELEASE(selectNoTexture)
		SAFE_RELEASE(selectNoTexture2)
		SAFE_RELEASE(selectCursorTexture)
		SAFE_RELEASE(selectCursorTexture2)
		SAFE_RELEASE(selectPlayerLogoTexture)
	}
}


//=============================================================================
// �X�V����
//=============================================================================
void CharaSelectBarUI::update(void)
{
}


//=============================================================================
// �`�揈��
//=============================================================================
void CharaSelectBarUI::render(LPDIRECT3DDEVICE9 device)
{
	charaSelectBar.render(device);
	charaSelectBar2.render(device);
	charaSelectNo.render(device);
	charaSelectNo2.render(device);
	charaSelectCursor.render(device);
	charaSelectCursor2.render(device);
	charaSelectLogo.render(device);
}


