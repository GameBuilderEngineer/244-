//=============================================================================
// �������\������ [ChinginCnt.cpp]
// ����� �ђˏt�P
//=============================================================================
#include "ChinginCnt.h"
//*****************************************************************************
// �萔
//*****************************************************************************
#ifdef _DEBUG
const static float		CHINGIN_CNT_POSITION_X = 150.0f;		// ������X���W
const static float		CHINGIN_CNT_POSITION_Y = 300.0f;		// ������Y���W
const static float		CHINGIN2_CNT_POSITION_X = 620.0f;		// ������X���W2
const static float		CHINGIN2_CNT_POSITION_Y = 300.0f;		// ������Y���W2
#else
const static float		CHINGIN_CNT_POSITION_X = 300.0f;	// �����[�X��������X���W
const static float		CHINGIN_CNT_POSITION_Y = 600.0f;	// �����[�X��������Y���W
const static float		CHINGIN2_CNT_POSITION_X = 1240.0f;	// �����[�X��������X���W2
const static float		CHINGIN2_CNT_POSITION_Y = 600.0f;	// �����[�X��������Y���W2
#endif 
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//=============================================================================
// �R���X�g���N�^
//=============================================================================
ChinginCnt::ChinginCnt(void)
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
ChinginCnt::~ChinginCnt(void)
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT ChinginCnt::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader, TextManager* _textManager)
{
	// �e�L�X�g�}�l�[�W��
	textManager = _textManager;
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void ChinginCnt::uninitialize(void)
{
}
//=============================================================================
// �X�V����
//=============================================================================
void ChinginCnt::update(void)
{
}
//=============================================================================
// �`�揈��
//=============================================================================
void ChinginCnt::render(LPDIRECT3DDEVICE9 device, float _chinginCnt, float _chinginCnt2)
{
	// �������`��
	textManager->text[textManagerNS::TYPE::NEW_RODIN_GAME_TIME]->print(CHINGIN_CNT_POSITION_X, CHINGIN_CNT_POSITION_Y, "�� %.0f", _chinginCnt);

	// �������`��2
	textManager->text[textManagerNS::TYPE::NEW_RODIN_GAME_TIME]->print(CHINGIN2_CNT_POSITION_X, CHINGIN2_CNT_POSITION_Y, "�� %.0f", _chinginCnt2);

}