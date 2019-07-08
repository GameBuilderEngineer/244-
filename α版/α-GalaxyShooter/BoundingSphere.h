#pragma once
#include "Base.h"
class BoundingSphere : public Base
{
	D3DXVECTOR3*	position;	//位置
	float			radius;		//半径
	D3DXVECTOR3		center;		//中心
	LPD3DXMESH		mesh;		//メッシュ
public:
	BoundingSphere();
	~BoundingSphere();
	void initialize(LPDIRECT3DDEVICE9 device,D3DXVECTOR3* position, LPD3DXMESH ownerMesh);
	void render(LPDIRECT3DDEVICE9 device,D3DXMATRIX owner);
	bool collide(D3DXVECTOR3 targetCenter,float targetRadius, D3DXMATRIX ownerMatrix, D3DXMATRIX targetMatrix);

	float getRadius() { return radius; }
	D3DXVECTOR3 getCenter() { return center; }

};