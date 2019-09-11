//============================================================================================================================================
// Document
//============================================================================================================================================
// EffectDew.h
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/08/30
//============================================================================================================================================
#pragma once
#include "Base.h"
#include "InstancingEffect.h"
#include "TextureLoader.h"
#include "BoundingSphere.h"
#include "Player.h"
#include "EffectManager.h"
//============================================================================================================================================
// NameSpace
// 名前空間
//============================================================================================================================================
namespace effectDewNS
{
	const int EFFECT_MAX = (100);	//	同時描画数
}
//============================================================================================================================================
// Class
// クラス
//============================================================================================================================================
class EffectDew
{
private:
	BoundingSphere bodyCollide;	//	バウンディングスフィア
	D3DXMATRIX matrixWorld;		//	ワールド座標
	D3DXVECTOR3 position;		//	位置
	D3DXVECTOR3 scale;			//	スケール
	D3DXVECTOR3 speed;			//	速度
	D3DXVECTOR3 acceleration;	//	加速度
	D3DXVECTOR3 gravity;		//	重力
	float collisionRadius;		//	衝突半径
	float alpha;				//	アルファ値
	bool existenceFlag;			//	存在フラグ
public:
	D3DXVECTOR3* getPosition(void) { return &position; }
	D3DXVECTOR3* getSpeed(void) { return &speed; }
	D3DXMATRIX* getMatrixWorld(void) { return &matrixWorld; }
	BoundingSphere* getCollider(void) { return &bodyCollide; }
	bool getExistenceFlag(void) { return existenceFlag; }
	void setPosition(D3DXVECTOR3 _position) { position = _position; }
	void setSpeed(D3DXVECTOR3 _speed) { speed = _speed; }
	void setExistenceFlag(bool _flag) { existenceFlag = _flag; }
};

class EffectDewManager :public Base
{
private:
	InstancingEffect instancingProcedure;										//	ビルボードのインスタンシング描画処理クラス
	EffectDew effectDew[effectDewNS::EFFECT_MAX];								//	エフェクト配列
	int existence;																//	使用中の数
	D3DXVECTOR3* renderList;													//	インスタンシング描画するエフェクトの座標
	LPD3DXMESH sphere;															//	バウンディングスフィア用球形メッシュ
	D3DXVECTOR3 moveSpeed(D3DXVECTOR3 _position, D3DXVECTOR3 _targetPosition);	// 移動速度
public:
	void initialize(LPDIRECT3DDEVICE9 _device, TextureLoader* _textureLoader, LPD3DXEFFECT _effect);
	~EffectDewManager();
	void update(float _frameTime, Player* _player);
	void render(LPDIRECT3DDEVICE9 _device, D3DXMATRIX _view, D3DXMATRIX _projection, D3DXVECTOR3 _cameraPosition);
	void generateEffect(int _index, D3DXVECTOR3 _positionToGenerate);
};