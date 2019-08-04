//-----------------------------------------------------------------------------
// チンギン処理 [Chingin.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/8/1
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "InstancingChingin.h"
#include "TextureLoader.h"
#include "BoundingSphere.h"
#include "Player.h"

static const int NUM_CHINGIN = 100;	// 同時に表示するうえで妥当そうな数

//----------
// チンギン
//----------
class Chingin	// 2人分で200個も出るなら重いかと思ってObjectを使っていない
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
	D3DXVECTOR3* getSpeed() { return &speed; }
	D3DXMATRIX* getMatrixWorld() { return &matrixWorld; }
	BoundingSphere* getCollider() { return &bodyCollide; }
	bool getUse() { return use; }

	void setPosition(D3DXVECTOR3 _position) { position = _position; }
	void setSpeed(D3DXVECTOR3 _speed) { speed = _speed; }
	void setUse(bool _use) { use = _use; }
};


//--------------------
// チンギン管理クラス
//--------------------
class ChinginManager :public Base
{
private:
	InstancingChingin instancingProcedure;	// ビルボードのインスタンシング描画処理クラス
	Chingin chingin[NUM_CHINGIN];			// チンギン配列
	int numOfUse;							// 使用中の数
	D3DXVECTOR3* renderList;				// インスタンシング描画するチンギンの座標
	LPD3DXMESH sphere;						// バウンディングスフィア用球形メッシュ
	D3DXVECTOR3 moveSpeed(D3DXVECTOR3 position, D3DXVECTOR3 targetPosition);// 移動速度

	// マグネット関係は今は触らない（理解していない）
	//int type;
	//float amount;	//磁気量
	//void reverseAmount();

public:
	void initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect);
	void update(float frameTime, Player* player);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);

	// チンギンを発生させる
	void generateChingin(int num, D3DXVECTOR3 positionToGenerate);
};

