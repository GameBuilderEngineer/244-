//============================================================================================================================================
// Document
//============================================================================================================================================
// Gun.h
// HAL���� GP-12A-332 09 �T���v��
// 2019/09/11
//============================================================================================================================================
#pragma once
#include "Object.h"
//============================================================================================================================================
// NameSpace
// ���O���
//============================================================================================================================================
namespace gunNS
{
	const float EXISTENCE_TIME = (5.0f);	//	���ݎ���
	const float GRAVITY_FORCE = (80.0f);	//	�d��
	const float SPEED = (80.0f);			//	���x
}
//============================================================================================================================================
// Class
// �N���X
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