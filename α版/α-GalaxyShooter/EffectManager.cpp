//-----------------------------------------------------------------------------
// エフェクトマネージャー処理 [EffectManager.cpp]
// 製作者 飯塚春輝
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
// 初期化処理
//=============================================================================
void EffectManager::initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect)
{
}
//=============================================================================
// 更新処理
//=============================================================================
void EffectManager::update(float frameTime)
{
}
//=============================================================================
// 描画処理
//=============================================================================
void EffectManager::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
}
