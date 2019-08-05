//===================================================================================================================================
//【BoudingSphere.h】
// 作成者：HAL東京GP12A332 11 菅野 樹
// 作成日：2019/06/12
// 更新日：2019/08/03
//===================================================================================================================================
#pragma once
#include "Base.h"
class BoundingSphere : public Base
{
private:
	//Data
	D3DXVECTOR3*	position;	//位置
	float			radius;		//半径
	D3DXVECTOR3		center;		//中心
	LPD3DXMESH		mesh;		//メッシュ
public:
	//Method
	BoundingSphere();
	~BoundingSphere();

	//processing
	void initialize(LPDIRECT3DDEVICE9 device,D3DXVECTOR3* position, LPD3DXMESH ownerMesh);
	void initialize(LPDIRECT3DDEVICE9 device, float _raidus);
	void render(LPDIRECT3DDEVICE9 device,D3DXMATRIX owner);
	bool collide(D3DXVECTOR3 targetCenter,float targetRadius, D3DXMATRIX ownerMatrix, D3DXMATRIX targetMatrix);

	//getter
	float getRadius();
	D3DXVECTOR3 getCenter();
	LPD3DXMESH	getMesh();
};