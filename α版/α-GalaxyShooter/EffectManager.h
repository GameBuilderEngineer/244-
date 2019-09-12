//-----------------------------------------------------------------------------
// インスタンシングエフェクトヘッダー [InstancingEffect.h]
// 製作者 飯塚春輝
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "InstancingEffect.h"
#include "TextureLoader.h"
#include "BoundingSphere.h"
#include "Bullet.h"

//----------
// エフェクト
//----------
class EffectIns	// 2人分で200個も出るなら重いかと思ってObjectを使っていない
{
private:
	D3DXVECTOR3 position;		// 位置
	D3DXVECTOR3 scale;			// スケール
	float radius;				// 衝突半径
	float alpha;				// 透過値
	D3DXVECTOR3 speed;			// 速度
	D3DXVECTOR3 acceleration;	// 加速度
	D3DXVECTOR3 gravity;		// 重力
	D3DXMATRIX matrixWorld;		// ワールド座標
	BoundingSphere bodyCollide;	// バウンディングスフィア
	bool use;					// 使用中か
public:
	D3DXVECTOR3* getPosition() { return &position; }
	D3DXVECTOR3* getScale() { return &scale; }
	D3DXVECTOR3* getSpeed() { return &speed; }
	D3DXMATRIX* getMatrixWorld() { return &matrixWorld; }
	BoundingSphere* getCollider() { return &bodyCollide; }
	bool getUse() { return use; }

	void setPosition(D3DXVECTOR3 _position) { position = _position; }
	void setSpeed(D3DXVECTOR3 _speed) { speed = _speed; }
	void setScale(D3DXVECTOR3 _scale) { speed = _scale; }
	void addSpeed(D3DXVECTOR3 add) { speed += add; }
	void setUse(bool _use) { use = _use; }
	float time;

};
//--------------------
// エフェクト管理クラス
//--------------------
class EffectManager :public Base
{
protected:
	InstancingEffect instancingProcedure;	// ビルボードのインスタンシング描画処理クラス
	int numOfUse;							// 使用中の数
	D3DXVECTOR3* renderList;				// インスタンシング描画するエフェクトの座標
	LPD3DXMESH sphere;						// バウンディングスフィア用球形メッシュ
public:
	EffectManager();
	~EffectManager();
	virtual void initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect);
	virtual void update(float frameTime);
	virtual void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);
};

