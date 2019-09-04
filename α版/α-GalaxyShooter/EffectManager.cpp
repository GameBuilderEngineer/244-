//-----------------------------------------------------------------------------
// エフェクトマネージャー処理 [EffectManager.cpp]
// 製作者 飯塚春輝
//-----------------------------------------------------------------------------
#include "EffectManager.h"
//=============================================================================
// 初期化処理
//=============================================================================
void EffectManager::initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect)
{
	D3DXCreateSphere(device, 3.0f, 9, 9, &sphere, NULL);	// 当たり判定用にスフィアを作る

	for (int i = 0; i < NUM_EFFECT; i++)
	{
		effectIns[i].setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		effectIns[i].setSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		D3DXMatrixIdentity(effectIns[i].getMatrixWorld());
		effectIns[i].getCollider()->initialize(device, effectIns[i].getPosition(), sphere);
		effectIns[i].setUse(false);
	}

	numOfUse = 0;
	renderList = NULL;

	instancingProcedure.initialize(device, effect, *_textureLoader->getTexture(textureLoaderNS::HP_EFFECT));
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
