//-----------------------------------------------------------------------------
// �G�t�F�N�g�}�l�[�W���[���� [EffectManager.cpp]
// ����� �ђˏt�P
//-----------------------------------------------------------------------------
#include "EffectManager.h"


EffectManager::EffectManager()
{
	sphere = NULL;
}

EffectManager::~EffectManager()
{

 	SAFE_RELEASE(sphere)
}

//=============================================================================
// ����������
//=============================================================================
void EffectManager::initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect)
{
}
//=============================================================================
// �X�V����
//=============================================================================
void EffectManager::update(float frameTime)
{
}
//=============================================================================
// �`�揈��
//=============================================================================
void EffectManager::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
}
