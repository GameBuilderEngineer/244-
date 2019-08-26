//=============================================================================
// �^�C�}�[UI���� [TimerUI.cpp]
// ����� �ђˏt�P
//=============================================================================
#include "TimerUI.h"
//*****************************************************************************
// �萔
//*****************************************************************************
#ifdef _DEBUG
const static int		WIDTH = 300;						// �^�C�}�[UI���T�C�Y
const static int		HEIGHT = 150;						// �^�C�}�[UI�c�T�C�Y
const static float		POSITION_X = 330.0f;				// �^�C�}�[UIX���W
const static float		POSITION_Y = 0.0f;					// �^�C�}�[UIY���W
const static float		TIMER_ONE_POSITION_X = 480.0f;		// 1���^�C�}�[X���W
const static float		TIMER_ONE_POSITION_Y = -20.0f;		// 1���^�C�}�[Y���W
const static float		TIMER_TEN_POSITION_X = 440.0f;		// 10���^�C�}�[X���W
const static float		TIMER_TEN_POSITION_Y = -20.0f;		// 10���^�C�}�[Y���W
#else
const static int		WIDTH = 600;						// �����[�X���^�C�}�[UI�T�C�Y
const static int		HEIGHT = 300;						// �����[�X���^�C�}�[UI�c�T�C�Y	
const static float		POSITION_X = 660.0f;				// �����[�X���^�C�}�[UIX���W
const static float		POSITION_Y = 0.0f;					// �����[�X���^�C�}�[UIY���W
const static float		TIMER_ONE_POSITION_X = 970.0f;		// �����[�X��1���^�C�}�[X���W
const static float		TIMER_ONE_POSITION_Y = 10.0f;		// �����[�X��1���^�C�}�[Y���W
const static float		TIMER_TEN_POSITION_X = 910.0f;		// �����[�X��10���^�C�}�[X���W
const static float		TIMER_TEN_POSITION_Y = 10.0f;		// �����[�X��10���^�C�}�[Y���W
#endif 
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int TimerUI::cntUI = -1;
LPDIRECT3DTEXTURE9 TimerUI::timerTexture = NULL;			// �^�C�}�[�e�N�X�`��
//=============================================================================
// �R���X�g���N�^
//=============================================================================
TimerUI::TimerUI(void)
{
	cntUI++;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
TimerUI::~TimerUI(void)
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT TimerUI::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader, TextManager* _textManager)
{
	// �v���C���[�i���o�[
	playerNumber = _playerNumber;

	// �e�L�X�g�}�l�[�W��
	textManager = _textManager;

	// �e�N�X�`����ǂݍ���
	setVisualDirectory();

	timerTexture = *textureLoader->getTexture(textureLoaderNS::UI_CHARACTER_SELECT_TIME);

	// �^�C�}�[UI������
	Sprite::initialize(device,
		timerTexture,						// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		WIDTH,								// ����
		HEIGHT,								// ����
		D3DXVECTOR3(POSITION_X, POSITION_Y, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		TIMER_UI_COLOR						// �F
	);

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void TimerUI::uninitialize(void)
{
}
//=============================================================================
// �X�V����
//=============================================================================
void TimerUI::update(void)
{
}
//=============================================================================
// �`�揈��
//=============================================================================
void TimerUI::render(LPDIRECT3DDEVICE9 device, float _uiOneTimer, float _uiTenTimer)
{
	// �^�C�}�[UI�`��
	Sprite::render(device);

	// �^�C���`��
	textManager->text[textManagerNS::TYPE::NEW_RODIN_CHARACTER_SELECT_TIME]->print(TIMER_ONE_POSITION_X, TIMER_ONE_POSITION_Y, "%.0f", _uiOneTimer);
	textManager->text[textManagerNS::TYPE::NEW_RODIN_CHARACTER_SELECT_TIME]->print(TIMER_TEN_POSITION_X, TIMER_TEN_POSITION_Y, "%.0f", _uiTenTimer);
}