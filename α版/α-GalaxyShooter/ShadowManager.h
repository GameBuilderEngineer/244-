//-----------------------------------------------------------------------------
// 影処理 [ShadowManager.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/9/9
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "InstancingBillboard.h"
#include "TextureLoader.h"

static const int INITIAL_NUM_SHADOW = 200;	// ポインタ配列要素数の妥当そうな初期値

//----------
// 影クラス
//----------
class Shadow
{
private:
	D3DXVECTOR3 *ownerPositionPointer;		// 持ち主の座標のポインタ
	D3DXVECTOR3 position;					// 位置
	D3DXVECTOR3 scale;						// スケール
	float alpha;							// 透過値
	D3DXMATRIX matrixWorld;					// ワールド座標

public:
	D3DXVECTOR3* getPosition() { return &position; }
	D3DXMATRIX* getMatrixWorld() { return &matrixWorld; }
	void setPosition(D3DXVECTOR3 _position) { position = _position; }
};


//----------------------------
// インスタンシング描画クラス
//----------------------------
class InstancingShadowRender :public InstancingBillboard
{
public:
	HRESULT initialize(LPDIRECT3DDEVICE9 device, LPD3DXEFFECT effect, LPDIRECT3DTEXTURE9 texture);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);
};


//--------------
// 影管理クラス
//--------------
class ShadowManager :public Base
{
private:
	Shadow **shadow;							// 影ポインタ配列
	InstancingShadowRender instancingProcedure;	// ビルボードのインスタンシング描画処理クラス
	D3DXVECTOR3* renderList;					// インスタンシング描画する影の座標
	LPD3DXMESH sphere;							// バウンディングスフィア用球形メッシュ
	int shadowMax;								// 影ポインタ配列の要素数
	int numOfUse;								// 使用中(配列にポインタがセットされている)数

	// Method
	D3DXVECTOR3 moveSpeed(D3DXVECTOR3 position, D3DXVECTOR3 targetPosition);// 影の移動を設定

public:
	void initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect);
	void uninitialize(void);
	void update(Sound* _sound, float frameTime);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);
	void generateShadow(int num, D3DXVECTOR3 setPosition, Player* target);	// 影を発生させる
};

