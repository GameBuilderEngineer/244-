//============================================================================================================================================
// Document
//============================================================================================================================================
// Gun.h
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/09/11
//============================================================================================================================================
#pragma once
#include "Object.h"
//============================================================================================================================================
// NameSpace
// 名前空間
//============================================================================================================================================
namespace gunNS
{
	const float EXISTENCE_TIME = (5.0f);	//	存在時間
	const float GRAVITY_FORCE = (80.0f);	//	重力
	const float SPEED = (80.0f);			//	速度
}
//============================================================================================================================================
// Class
// クラス
//============================================================================================================================================
class Gun : public Object
{
public:
	Gun(void);
	~Gun(void);
	void initialize(LPDIRECT3DDEVICE9 _device, StaticMesh* _staticMesh, D3DXVECTOR3* _position);
	void release(void);
	void update(float _frameTime, D3DXVECTOR3 _position);
	void render(LPDIRECT3DDEVICE9 _device, D3DXMATRIX _view, D3DXMATRIX _projection, D3DXVECTOR3 _cameraPositon, D3DXMATRIX _matrixPlayer, D3DXMATRIX _matrixAnimation);
	//void render(LPDIRECT3DDEVICE9 _device, D3DXMATRIX _view, D3DXMATRIX _projection, D3DXVECTOR3 _cameraPositon, LPD3DXMESHCONTAINER _baseMeshContainer);
};