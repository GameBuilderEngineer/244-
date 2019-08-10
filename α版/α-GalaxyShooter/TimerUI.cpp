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
#else
const static int		WIDTH = 600;						// �����[�X���^�C�}�[UI�T�C�Y
const static int		HEIGHT = 300;						// �����[�X���^�C�}�[UI�c�T�C�Y	
const static float		POSITION_X = 660.0f;				// �����[�X���^�C�}�[UIX���W
const static float		POSITION_Y = 0.0f;					// �����[�X���^�C�}�[UIY���W
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
HRESULT TimerUI::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader)
{
	// �v���C���[�i���o�[
	playerNumber = _playerNumber;

	// �e�N�X�`����ǂݍ���
	setVisualDirectory();

	timerTexture = *textureLoader->getTexture(textureLoaderNS::UI_CHARA_SELECT_TIMER);

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
	// �^�C�}�[UI�摜���
	setTexture(NULL);

	// �C���X�^���X�����݂��Ȃ���΃e�N�X�`�����
	cntUI--;
	if (cntUI < 0)
	{
		SAFE_RELEASE(timerTexture)
	}
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
void TimerUI::render(LPDIRECT3DDEVICE9 device)
{
	// �^�C�}�[UI�`��
	Sprite::render(device);
}