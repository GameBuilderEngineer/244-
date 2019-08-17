//=============================================================================
// �L�����Z���N�g�o�[UI���� [CharaSelectBarUI.cpp]
// ����� �ђˏt�P
//=============================================================================
#include "CharaSelectBarUI.h"
// �L�����N�^�[�Z���N�g�o�[���O��ԗL��
using namespace charaSelectBarUINS;
//*****************************************************************************
// �萔
//*****************************************************************************
#ifdef _DEBUG
const static int		BAR_WIDTH = WINDOW_WIDTH / 2;											// �Z���N�g�o�[���C�g���T�C�Y
const static int		BAR_HEIGHT = 250;														// �Z���N�g�o�[���C�g�T�C�Y
const static int		NO_WIDTH = 180;															// �Z���N�g�i���o�[���T�C�Y
const static int		NO_HEIGHT = 82;															// �Z���N�g�i���o�[�c�T�C�Y
const static int		CURSOR_WIDTH = WINDOW_WIDTH / 2;										// �Z���N�g�J�[�\�����T�C�Y
const static int		CURSOR_HEIGHT = 40;														// �Z���N�g�J�[�\���c�T�C�Y
const static int		PLAYER_LOGO_WIDTH = 80;													// �Z���N�g�v���C���[���S���T�C�Y
const static int		PLAYER_LOGO_HEIGHT = 40;												// �Z���N�g�v���C���[���S�c�T�C�Y
const static int		PLAYER_NAME_ENG_WIDTH = 250;											// �v���C���[�l�[���p�ꉡ�T�C�Y
const static int		PLAYER_NAME_ENG_HEIGHT = 82;											// �v���C���[�l�[���p��c�T�C�Y
const static int		PLAYER_NAME_JP_WIDTH = 250;												// �v���C���[�l�[�����{�ꉡ�T�C�Y
const static int		PLAYER_NAME_JP_HEIGHT = 20;												// �v���C���[�l�[�����{��c�T�C�Y
const static float		BAR_LIGHT_POSITION_X = 0.0f;											// �Z���N�g�o�[���C�gX���W
const static float		BAR_LIGHT_POSITION2_X = BAR_LIGHT_POSITION_X + WINDOW_WIDTH / 2;		// �Z���N�g�o�[���C�g2X���W
const static float		BAR_LIGHT_POSITION_Y = 220.0f;											// �Z���N�g�o�[���C�gY���W
const static float		NO_POSITION_X = 0.0f;													// �Z���N�g�i���o�[X���W
const static float		NO_POSITION2_X = NO_POSITION_X + WINDOW_WIDTH / 2;						// �Z���N�g�i���o�[2X���W
const static float		NO_POSITION_Y = 304.0f;													// �Z���N�g�i���o�[Y���W
const static float		CURSOR_POSITION_X = 0.0f;												// �Z���N�g�J�[�\��X���W
const static float		CURSOR_POSITION2_X = CURSOR_POSITION_X + WINDOW_WIDTH / 2;				// �Z���N�g�J�[�\��2X���W
const static float		CURSOR_POSITION_Y = 250.0f;												// �Z���N�g�J�[�\��Y���W
const static float		PLAYER_LOGO_POSITION_X = 0.0f;											// �Z���N�g�v���C���[���SX���W
const static float		PLAYER_LOGO_POSITION2_X = PLAYER_LOGO_POSITION_X + WINDOW_WIDTH / 2;	// �Z���N�g�v���C���[���S2X���W
const static float		PLAYER_LOGO_POSITION_Y = 390.0f;										// �Z���N�g�v���C���[���SY���W
const static float		POSITION_X_NAME_EVE_ENG = 200.0f;										// �C�����O�p��e�N�X�`��X���W
const static float		POSITION2_X_NAME_EVE_ENG = POSITION_X_NAME_EVE_ENG + WINDOW_WIDTH / 2;	// �C�����O�p��e�N�X�`��2X���W
const static float		POSITION_X_NAME_ADAM_ENG = 200.0f;										// �A�_�����O�p��e�N�X�`��X���W
const static float		POSITION2_X_NAME_ADAM_ENG = POSITION_X_NAME_ADAM_ENG + WINDOW_WIDTH / 2;// �A�_�����O�p��e�N�X�`��2X���W
const static float		POSITION_Y_NAME_ENG = 304.0f;											// ���O�p��e�N�X�`��Y���W
const static float		POSITION_X_NAME_EVE_JP = 200.0f;										// �C�����O���{��e�N�X�`��X���W
const static float		POSITION2_X_NAME_EVE_JP = POSITION_X_NAME_EVE_JP + WINDOW_WIDTH / 2;	// �C�����O���{��e�N�X�`��2X���W
const static float		POSITION_X_NAME_ADAM_JP = 200.0f;										// �A�_�����O���{��e�N�X�`��X���W
const static float		POSITION2_X_NAME_ADAM_JP = POSITION_X_NAME_ADAM_JP + WINDOW_WIDTH / 2;	// �A�_�����O���{��e�N�X�`��2X���W
const static float		POSITION_Y_NAME_JP = 390.0f;											// ���O���{��e�N�X�`��Y���W
#else
const static int		BAR_WIDTH = WINDOW_WIDTH / 2;											// �����[�X���Z���N�g�o�[���C�g���T�C�Y
const static int		BAR_HEIGHT = 500;														// �����[�X���Z���N�g�o�[���C�g�c�T�C�Y
const static int		NO_WIDTH = 360;															// �����[�X���Z���N�g�i���o�[���T�C�Y
const static int		NO_HEIGHT = 164;														// �����[�X���Z���N�g�i���o�[�c�T�C�Y
const static int		CURSOR_WIDTH = WINDOW_WIDTH / 2;										// �����[�X���Z���N�g�J�[�\�����T�C�Y
const static int		CURSOR_HEIGHT = 80;														// �����[�X���Z���N�g�J�[�\���c�T�C�Y
const static int		PLAYER_LOGO_WIDTH = 160;												// �����[�X���Z���N�g�v���C���[���S���T�C�Y
const static int		PLAYER_LOGO_HEIGHT = 80;												// �����[�X���Z���N�g�v���C���[���S�c�T�C�Y
const static int		PLAYER_NAME_ENG_WIDTH = 500;											// �����[�X���v���C���[�l�[���p�ꉡ�T�C�Y
const static int		PLAYER_NAME_ENG_HEIGHT = 164;											// �����[�X���v���C���[�l�[���p��c�T�C�Y
const static int		PLAYER_NAME_JP_WIDTH = 500;												// �����[�X���v���C���[�l�[�����{�ꉡ�T�C�Y
const static int		PLAYER_NAME_JP_HEIGHT = 40;												// �����[�X���v���C���[�l�[�����{��c�T�C�Y
const static float		BAR_LIGHT_POSITION_X = 0.0f;											// �����[�X���Z���N�g�o�[���C�gX���W
const static float		BAR_LIGHT_POSITION2_X = BAR_LIGHT_POSITION_X + WINDOW_WIDTH / 2;		// �����[�X���Z���N�g�o�[���C�g2X���W
const static float		BAR_LIGHT_POSITION_Y = 440.0f;											// �����[�X���Z���N�g�o�[���C�gY���W
const static float		NO_POSITION_X = 0.0f;													// �����[�X���Z���N�g�i���o�[X���W
const static float		NO_POSITION2_X = NO_POSITION_X + WINDOW_WIDTH / 2;						// �����[�X���Z���N�g�i���o�[2X���W
const static float		NO_POSITION_Y = 608.0f;													// �����[�X���Z���N�g�i���o�[Y���W
const static float		CURSOR_POSITION_X = 0.0f;												// �����[�X���Z���N�g�J�[�\��X���W
const static float		CURSOR_POSITION2_X = CURSOR_POSITION_X + WINDOW_WIDTH / 2;				// �����[�X���Z���N�g�J�[�\��2X���W
const static float		CURSOR_POSITION_Y = 500.0f;												// �����[�X���Z���N�g�J�[�\��Y���W
const static float		PLAYER_LOGO_POSITION_X = 0.0f;											// �����[�X���Z���N�g�v���C���[���SX���W
const static float		PLAYER_LOGO_POSITION2_X = PLAYER_LOGO_POSITION_X + WINDOW_WIDTH / 2;	// �����[�X���Z���N�g�v���C���[���S2X���W
const static float		PLAYER_LOGO_POSITION_Y = 780.0f;										// �����[�X���Z���N�g�v���C���[���SY���W
const static float		POSITION_X_NAME_EVE_ENG = 400.0f;										// �����[�X���C�����O�p��e�N�X�`��X���W
const static float		POSITION2_X_NAME_EVE_ENG = POSITION_X_NAME_EVE_ENG + WINDOW_WIDTH / 2;	// �����[�X���C�����O�p��e�N�X�`��2X���W
const static float		POSITION_X_NAME_ADAM_ENG = 400.0f;										// �����[�X���A�_�����O�p��e�N�X�`��X���W
const static float		POSITION2_X_NAME_ADAM_ENG = POSITION_X_NAME_ADAM_ENG + WINDOW_WIDTH / 2;// �����[�X���A�_�����O�p��e�N�X�`��2X���W
const static float		POSITION_Y_NAME_ENG = 608.0f;											// �����[�X�����O�p��e�N�X�`��Y���W
const static float		POSITION_X_NAME_EVE_JP = 400.0f;										// �����[�X���C�����O���{��e�N�X�`��X���W
const static float		POSITION2_X_NAME_EVE_JP = POSITION_X_NAME_EVE_JP + WINDOW_WIDTH / 2;	// �����[�X���C�����O���{��e�N�X�`��2X���W
const static float		POSITION_X_NAME_ADAM_JP = 400.0f;										// �����[�X���A�_�����O���{��e�N�X�`��X���W
const static float		POSITION2_X_NAME_ADAM_JP = POSITION_X_NAME_ADAM_JP + WINDOW_WIDTH / 2;	// �����[�X���A�_�����O���{��e�N�X�`��2X���W
const static float		POSITION_Y_NAME_JP = 780.0f;											// �����[�X�����O���{��e�N�X�`��Y���W
#endif 
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
	// �v���C���[�i���o�[
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

	// �Z���N�g�o�[���C�g������
	charaSelectBar.initialize(device,
		selectBarLightTexture,				// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		BAR_WIDTH,							// ����
		BAR_HEIGHT,							// ����
		D3DXVECTOR3(BAR_LIGHT_POSITION_X, BAR_LIGHT_POSITION_Y, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);
	// �Z���N�g�o�[���C�g2������
	charaSelectBar2.initialize(device,
		selectBarLightTexture2,				// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		BAR_WIDTH,							// ����
		BAR_HEIGHT,							// ����
		D3DXVECTOR3(BAR_LIGHT_POSITION2_X, BAR_LIGHT_POSITION_Y, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);
	// �Z���N�g�i���o�[������
	charaSelectNo.initialize(device,
		selectNoTexture,					// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		NO_WIDTH,							// ����
		NO_HEIGHT,							// ����
		D3DXVECTOR3(NO_POSITION_X, NO_POSITION_Y, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);
	// �Z���N�g�i���o�[2������
	charaSelectNo2.initialize(device,
		selectNoTexture2,					// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		NO_WIDTH,							// ����
		NO_HEIGHT,							// ����
		D3DXVECTOR3(NO_POSITION2_X, NO_POSITION_Y, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);
	// �Z���N�g�J�[�\��������
	charaSelectCursor.initialize(device,
		selectCursorTexture,				// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		CURSOR_WIDTH,						// ����
		CURSOR_HEIGHT,						// ����
		D3DXVECTOR3(CURSOR_POSITION_X, CURSOR_POSITION_Y, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);
	// �Z���N�g�J�[�\��2������
	charaSelectCursor2.initialize(device,
		selectCursorTexture2,				// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		CURSOR_WIDTH,						// ����
		CURSOR_HEIGHT,						// ����
		D3DXVECTOR3(CURSOR_POSITION2_X, CURSOR_POSITION_Y, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);
	// �Z���N�g�v���C���[���S������
	charaSelectLogo.initialize(device,
		selectPlayerLogoTexture,			// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_LOGO_WIDTH,					// ����
		PLAYER_LOGO_HEIGHT,					// ����
		D3DXVECTOR3(playerNumber ? PLAYER_LOGO_POSITION2_X : PLAYER_LOGO_POSITION_X, PLAYER_LOGO_POSITION_Y, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);
	// �C�����O�p��e�N�X�`��������
	nameEveEng.initialize(device,
		nameEveEngTexture,					// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_NAME_ENG_WIDTH,				// ����
		PLAYER_NAME_ENG_HEIGHT,				// ����
		D3DXVECTOR3(POSITION_X_NAME_EVE_ENG, POSITION_Y_NAME_ENG, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);
	// �C�����O�p��e�N�X�`��2������
	nameEveEng2.initialize(device,
		nameEveEngTexture,					// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_NAME_ENG_WIDTH,				// ����
		PLAYER_NAME_ENG_HEIGHT,				// ����
		D3DXVECTOR3(POSITION2_X_NAME_EVE_ENG, POSITION_Y_NAME_ENG, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);
	// �A�_�����O�p��e�N�X�`��������
	nameAdamEng.initialize(device,
		nameAdamEngTexture,					// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_NAME_ENG_WIDTH,				// ����
		PLAYER_NAME_ENG_HEIGHT,				// ����
		D3DXVECTOR3(POSITION_X_NAME_ADAM_ENG, POSITION_Y_NAME_ENG, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);
	// �A�_�����O�p��e�N�X�`��2������
	nameAdamEng2.initialize(device,
		nameAdamEngTexture,					// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_NAME_ENG_WIDTH,				// ����
		PLAYER_NAME_ENG_HEIGHT,				// ����
		D3DXVECTOR3(POSITION2_X_NAME_ADAM_ENG, POSITION_Y_NAME_ENG, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);
	// �C�����O���{��e�N�X�`��������
	nameEveJp.initialize(device,
		nameEveJpTexture,					// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_NAME_JP_WIDTH,				// ����
		PLAYER_NAME_JP_HEIGHT,				// ����
		D3DXVECTOR3(POSITION_X_NAME_EVE_JP, POSITION_Y_NAME_JP, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);
	// �C�����O���{��e�N�X�`��2������
	nameEveJp2.initialize(device,
		nameEveJpTexture,					// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_NAME_JP_WIDTH,				// ����
		PLAYER_NAME_JP_HEIGHT,				// ����
		D3DXVECTOR3(POSITION2_X_NAME_EVE_JP, POSITION_Y_NAME_JP, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);
	// �A�_�����O���{��e�N�X�`��������
	nameAdamJp.initialize(device,
		nameAdamJpTexture,					// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		PLAYER_NAME_JP_WIDTH,				// ����
		PLAYER_NAME_JP_HEIGHT,				// ����
		D3DXVECTOR3(POSITION_X_NAME_ADAM_JP, POSITION_Y_NAME_JP, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);
	// �A�_�����O���{��e�N�X�`��2������
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
	charaSelectBar.setTexture(NULL);			// �Z���N�g�o�[���C�g�e�N�X�`�����
	charaSelectBar2.setTexture(NULL);			// �Z���N�g�o�[���C�g�e�N�X�`��2���
	charaSelectNo.setTexture(NULL);				// �Z���N�g�i���o�[�e�N�X�`�����
	charaSelectNo2.setTexture(NULL);			// �Z���N�g�i���o�[�e�N�X�`��2���
	charaSelectCursor.setTexture(NULL);			// �Z���N�g�J�[�\���e�N�X�`�����
	charaSelectCursor2.setTexture(NULL);		// �Z���N�g�J�[�\���e�N�X�`��2���
	charaSelectLogo.setTexture(NULL);			// �Z���N�g�v���C���[���S�e�N�X�`�����
	nameEveEng.setTexture(NULL);				// �C�����O�p��e�N�X�`�����
	nameAdamEng.setTexture(NULL);				// �A�_�����O�p��e�N�X�`�����
	nameEveJp.setTexture(NULL);					// �C�����O���{��e�N�X�`�����
	nameAdamJp.setTexture(NULL);				// �A�_�����O���{��e�N�X�`�����

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
	charaSelectBar.render(device);			// �Z���N�g�o�[���C�g�e�N�X�`���`��
	charaSelectBar2.render(device);			// �Z���N�g�o�[���C�g�e�N�X�`��2�`��
	charaSelectNo.render(device);			// �Z���N�g�i���o�[�e�N�X�`���`��
	charaSelectNo2.render(device);			// �Z���N�g�i���o�[�e�N�X�`��2�`��
	charaSelectCursor.render(device);		// �Z���N�g�J�[�\���e�N�X�`���`��
	charaSelectCursor2.render(device);		// �Z���N�g�J�[�\���e�N�X�`��2�`��
	charaSelectLogo.render(device);			// �Z���N�g�v���C���[���S�e�N�X�`���`��

	//1P�Z���N�g
	switch (selectNo)
	{
		// �v���C���[1
	case 0:

		nameEveEng.render(device);			// �C�����O�p��e�N�X�`���`��
		nameEveJp.render(device);			// �C�����O���{��e�N�X�`���`��

		break;
		// �v���C���[2
	case 1:

		nameAdamEng.render(device);			// �A�_�����O�p��e�N�X�`���`��
		nameAdamJp.render(device);			// �A�_�����O���{��e�N�X�`���`��

		break;
	}

	//2P�Z���N�g
	switch (select2No)
	{
		// �v���C���[1
	case 0:

		nameEveEng2.render(device);			// �C�����O�p��e�N�X�`��2�`��
		nameEveJp2.render(device);			// �C�����O���{��e�N�X�`��2�`��

		break;
		// �v���C���[2
	case 1:

		nameAdamEng2.render(device);		// �A�_�����O�p��e�N�X�`��2�`��
		nameAdamJp2.render(device);			// �A�_�����O���{��e�N�X�`��2�`��

		break;
	}
}