//===================================================================================================================================
//【Planet.h】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/06/05
// [更新日]2019/08/03
//===================================================================================================================================
#pragma once
#include "Object.h"
#include "BoundingSphere.h"
class Planet :public Object
{
private:
public:
	//Data
	BoundingSphere sphereCollide;

	//Method
	Planet();
	~Planet();

	//processing
	void initilaize(LPDIRECT3DDEVICE9 device, StaticMesh*_staticMesh, D3DXVECTOR3* _position);
	void update();
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);


	//setter


	//getter
	LPD3DXMESH getSphereMesh();
};

