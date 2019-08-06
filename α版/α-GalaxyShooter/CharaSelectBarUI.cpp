//=============================================================================
// �L�����Z���N�g�o�[UI���� [CharaSelectBarUI.cpp]
//
//=============================================================================
#include "CharaSelectBarUI.h"
using namespace charaSelectBarUINS;

//*****************************************************************************
// �萔�E�}�N��
//*****************************************************************************
#ifdef _DEBUG
const static int		BAR_WIDTH = WINDOW_WIDTH / 2;					// ���T�C�Y
const static int		BAR_HEIGHT = 250;								// �c�T�C�Y
const static int		NO_WIDTH = 180;									// ���T�C�Y
const static int		NO_HEIGHT = 82;									// �c�T�C�Y
const static int		CURSOR_WIDTH = WINDOW_WIDTH / 2;				// ���T�C�Y
const static int		CURSOR_HEIGHT = 40;								// �c�T�C�Y
const static int		PLAYER_LOGO_WIDTH = 80;							// ���T�C�Y
const static int		PLAYER_LOGO_HEIGHT = 40;						// �c�T�C�Y
const static int		PLAYER_NAME_ENG_WIDTH = 250;					// �v���C���[�l�[���p�ꉡ�T�C�Y
const static int		PLAYER_NAME_ENG_HEIGHT = 82;					// �v���C���[�l�[���p��c�T�C�Y
const static int		PLAYER_NAME_JP_WIDTH = 250;						// �v���C���[�l�[�����{�ꉡ�T�C�Y
const static int		PLAYER_NAME_JP_HEIGHT = 20;						// �v���C���[�l�[�����{��c�T�C�Y
const static float		BAR_LIGHT_POSITION_X = 0.0f;					// X���W
const static float		BAR_LIGHT_POSITION2_X = BAR_LIGHT_POSITION_X + WINDOW_WIDTH / 2;
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
const static float		POSITION_X_NAME_EVE_ENG = 200.0f;				// X���W
const static float		POSITION2_X_NAME_EVE_ENG = POSITION_X_NAME_EVE_ENG + WINDOW_WIDTH / 2;
const static float		POSITION_X_NAME_ADAM_ENG = 200.0f;				// X���W
const static float		POSITION2_X_NAME_ADAM_ENG = POSITION_X_NAME_ADAM_ENG + WINDOW_WIDTH / 2;
const static float		POSITION_Y_NAME_ENG = 304.0f;					// Y���W
const static float		POSITION_X_NAME_EVE_JP = 200.0f;				// X���W
const static float		POSITION2_X_NAME_EVE_JP = POSITION_X_NAME_EVE_JP + WINDOW_WIDTH / 2;
const static float		POSITION_X_NAME_ADAM_JP = 200.0f;				// X���W
const static float		POSITION2_X_NAME_ADAM_JP = POSITION_X_NAME_ADAM_JP + WINDOW_WIDTH / 2;
const static float		POSITION_Y_NAME_JP = 390.0f;					// Y���W

#else

const static int		BAR_WIDTH = WINDOW_WIDTH / 2;					// ���T�C�Y
const static int		BAR_HEIGHT = 500;								// �c�T�C�Y
const static int		NO_WIDTH = 360;									// ���T�C�Y
const static int		NO_HEIGHT = 164;								// �c�T�C�Y
const static int		CURSOR_WIDTH = WINDOW_WIDTH / 2;				// ���T�C�Y
const static int		CURSOR_HEIGHT = 80;								// �c�T�C�Y
const static int		PLAYER_LOGO_WIDTH = 160;						// ���T�C�Y
const static int		PLAYER_LOGO_HEIGHT = 80;						// �c�T�C�Y
const static int		PLAYER_NAME_ENG_WIDTH = 500;					// �v���C���[�l�[���p�ꉡ�T�C�Y
const static int		PLAYER_NAME_ENG_HEIGHT = 164;					// �v���C���[�l�[���p��c�T�C�Y
const static int		PLAYER_NAME_JP_WIDTH = 500;						// �v���C���[�l�[�����{�ꉡ�T�C�Y
const static int		PLAYER_NAME_JP_HEIGHT = 40;						// �v���C���[�l�[�����{��c�T�C�Y
const static float		BAR_LIGHT_POSITION_X = 0.0f;					// X���W
const static float		BAR_LIGHT_POSITION2_X = BAR_LIGHT_POSITION_X + WINDOW_WIDTH / 2;
const static float		BAR_LIGHT_POSITION_Y = 440.0f;					// Y���W
const static float		NO_POSITION_X = 0.0f;							// X���W
const static float		NO_POSITION2_X = NO_POSITION_X + WINDOW_WIDTH / 2;
const static float		NO_POSITION_Y = 608.0f;							// Y���W
const static float		CURSOR_POSITION_X = 0.0f;						// X���W
const static float		CURSOR_POSITION2_X = CURSOR_POSITION_X + WINDOW_WIDTH / 2;
const static float		CURSOR_POSITION_Y = 500.0f;						// Y���W
const static float		PLAYER_LOGO_POSITION_X = 0.0f;					// X���W
const static float		PLAYER_LOGO_POSITION2_X = PLAYER_LOGO_POSITION_X + WINDOW_WIDTH / 2;
const static float		PLAYER_LOGO_POSITION_Y = 780.0f;				// Y���W
const static float		POSITION_X_NAME_EVE_ENG = 400.0f;				// X���W
const static float		POSITION2_X_NAME_EVE_ENG = POSITION_X_NAME_EVE_ENG + WINDOW_WIDTH / 2;
const static float		POSITION_X_NAME_ADAM_ENG = 400.0f;				// X���W
const static float		POSITION2_X_NAME_ADAM_ENG = POSITION_X_NAME_ADAM_ENG + WINDOW_WIDTH / 2;
const static float		POSITION_Y_NAME_ENG = 608.0f;					// Y���W
const static float		POSITION_X_NAME_EVE_JP = 400.0f;				// X���W
const static float		POSITION2_X_NAME_EVE_JP = POSITION_X_NAME_EVE_JP + WINDOW_WIDTH / 2;
const static float		POSITION_X_NAME_ADAM_JP = 400.0f;				// X���W
const static float		POSITION2_X_NAME_ADAM_JP = POSITION_X_NAME_ADAM_JP + WINDOW_WIDTH / 2;
const static float		POSITION_Y_NAME_JP = 780.0f;					// Y���W

#endif 

#define DEFAULT_COLOR	(D3DCOLOR_RGBA(255, 255, 255, 255))				// �L�����Z���N�g�̐F
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
LPDIRECT3DTEXTURE9 CharaSelectBarUI::nameEveEngTexture = NULL;			// �C�����O�p��e�N�X�`��
LPDIRECT3DTEXTURE9 CharaSelectBarUI::nameEveEngTexture2 = NULL;			// �C�����O�p��e�N�X�`��2
LPDIRECT3DTEXTURE9 CharaSelectBarUI::nameAdamEngTexture = NULL;			// �A�_�����O�p��e�N�X�`��
LPDIRECT3DTEXTURE9 CharaSelectBarUI::nameAdamEngTexture2 = NULL;		// �A�_�����O�p��e�N�X�`��2
LPDIRECT3DTEXTURE9 CharaSelectBarUI::nameEveJpTexture = NULL;			// �C�����O���{��e�N�X�`��
LPDIRECT3DTEXTURE9 CharaSelectBarUI::nameEveJpTexture2 = NULL;			// �C�����O���{��e�N�X�`��2
LPDIRECT3DTEXTURE9 CharaSelectBarUI::nameAdamJpTexture = NULL;			// �A�_�����O���{��e�N�X�`��
LPDIRECT3DTEXTURE9 CharaSelectBarUI::nameAdamJpTexture2 = NULL;			// �A�_�����O���{��e�N�X�`��2
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
	nameEveEngTexture = *textureLoader->getTexture(textureLoaderNS::EVE_NAME_ENG);
	nameAdamEngTexture = *textureLoader->getTexture(textureLoaderNS::ADAM_NAME_ENG);
	nameEveJpTexture = *textureLoader->getTexture(textureLoaderNS::EVE_NAME_JP);
	nameAdamJpTexture = *textureLoader->getTexture(textureLoaderNS::ADAM_NAME_JP);

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

	nameEveEng.initialize(device,
		nameEveEngTexture,					// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_NAME_ENG_WIDTH,				// ����
		PLAYER_NAME_ENG_HEIGHT,				// ����
		D3DXVECTOR3(POSITION_X_NAME_EVE_ENG, POSITION_Y_NAME_ENG, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);

	nameEveEng2.initialize(device,
		nameEveEngTexture,					// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_NAME_ENG_WIDTH,				// ����
		PLAYER_NAME_ENG_HEIGHT,				// ����
		D3DXVECTOR3(POSITION2_X_NAME_EVE_ENG, POSITION_Y_NAME_ENG, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);

	nameAdamEng.initialize(device,
		nameAdamEngTexture,					// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_NAME_ENG_WIDTH,				// ����
		PLAYER_NAME_ENG_HEIGHT,				// ����
		D3DXVECTOR3(POSITION_X_NAME_ADAM_ENG, POSITION_Y_NAME_ENG, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);

	nameAdamEng2.initialize(device,
		nameAdamEngTexture,					// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_NAME_ENG_WIDTH,				// ����
		PLAYER_NAME_ENG_HEIGHT,				// ����
		D3DXVECTOR3(POSITION2_X_NAME_ADAM_ENG, POSITION_Y_NAME_ENG, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);

	nameEveJp.initialize(device,
		nameEveJpTexture,					// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_NAME_JP_WIDTH,				// ����
		PLAYER_NAME_JP_HEIGHT,				// ����
		D3DXVECTOR3(POSITION_X_NAME_EVE_JP, POSITION_Y_NAME_JP, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);

	nameEveJp2.initialize(device,
		nameEveJpTexture,					// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_NAME_JP_WIDTH,				// ����
		PLAYER_NAME_JP_HEIGHT,				// ����
		D3DXVECTOR3(POSITION2_X_NAME_EVE_JP, POSITION_Y_NAME_JP, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);

	nameAdamJp.initialize(device,
		nameAdamJpTexture,					// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_NAME_JP_WIDTH,				// ����
		PLAYER_NAME_JP_HEIGHT,				// ����
		D3DXVECTOR3(POSITION_X_NAME_ADAM_JP, POSITION_Y_NAME_JP, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);

	nameAdamJp2.initialize(device,
		nameAdamJpTexture,					// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_NAME_JP_WIDTH,				// ����
		PLAYER_NAME_JP_HEIGHT,				// ����
		D3DXVECTOR3(POSITION2_X_NAME_ADAM_JP, POSITION_Y_NAME_JP, 0.0f),// ���W
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
	nameEveEng.setTexture(NULL);
	nameAdamEng.setTexture(NULL);
	nameEveJp.setTexture(NULL);
	nameAdamJp.setTexture(NULL);

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
		SAFE_RELEASE(nameEveEngTexture)
		SAFE_RELEASE(nameAdamEngTexture)
		SAFE_RELEASE(nameEveJpTexture)
		SAFE_RELEASE(nameAdamJpTexture)
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
void CharaSelectBarUI::render(LPDIRECT3DDEVICE9 device, int selectNo, int select2No)
{
	charaSelectBar.render(device);
	charaSelectBar2.render(device);
	charaSelectNo.render(device);
	charaSelectNo2.render(device);
	charaSelectCursor.render(device);
	charaSelectCursor2.render(device);
	charaSelectLogo.render(device);

	//1P�Z���N�g
	switch (selectNo)
	{
		// �v���C���[
	case 0:

		nameEveEng.render(device);
		nameEveJp.render(device);

		break;
		// �v���C���[2
	case 1:

		nameAdamEng.render(device);
		nameAdamJp.render(device);

		break;
	}

	//2P�Z���N�g
	switch (select2No)
	{
		// �v���C���[
	case 0:

		nameEveEng2.render(device);
		nameEveJp2.render(device);

		break;
		// �v���C���[2
	case 1:

		nameAdamEng2.render(device);
		nameAdamJp2.render(device);

		break;
	}

}


