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
#include "Sound.h"

static const int INITIAL_NUM_CHINGIN = 300;	// ポインタ配列要素数の妥当そうな初期値

//----------
// チンギン
//----------
class Chingin	// 重いと思ってObjectを使っていない
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
	Player* target;				// ターゲットプレイヤー

public:
	D3DXVECTOR3* getPosition() { return &position; }
	D3DXVECTOR3* getSpeed() { return &speed; }
	D3DXMATRIX* getMatrixWorld() { return &matrixWorld; }
	BoundingSphere* getCollider() { return &bodyCollide; }
	Player* getTarget(void) { return target; }

	void setPosition(D3DXVECTOR3 _position) { position = _position; }
	void setSpeed(D3DXVECTOR3 _speed) { speed = _speed; }
	void setTarget(Player* _target) { target = _target; }
};


//--------------------
// チンギン管理クラス
//--------------------
class ChinginManager :public Base
{
private:
	Chingin **chingin;						// チンギンポインタ配列
	InstancingChingin instancingProcedure;	// ビルボードのインスタンシング描画処理クラス
	D3DXVECTOR3* renderList;				// インスタンシング描画するチンギンの座標
	LPD3DXMESH sphere;						// バウンディングスフィア用球形メッシュ
	int chinginMax;							// チンギンポインタ配列の要素数
	int numOfUse;							// 使用中(配列にポインタがセットされている)数

	// マグネット関係は今は触らない（理解していない）
	//int type;
	//float amount;	//磁気量
	//void reverseAmount();

	// Method
	D3DXVECTOR3 moveSpeed(D3DXVECTOR3 position, D3DXVECTOR3 targetPosition);// チンギンの移動を設定

public:
	void initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect);
	void uninitialize(void);
	void update(Sound* _sound, float frameTime);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);
	void generateChingin(int num, D3DXVECTOR3 setPosition, Player* target);	// チンギンを発生させる
};

