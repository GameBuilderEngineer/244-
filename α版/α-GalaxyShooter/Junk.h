//===================================================================================================================================
//yJunk.hz
// [ì¬Ò]HALGP12A332 11 ì ÷
// [ì¬ú]2019/05/16
// [XVú]2019/08/07
//===================================================================================================================================
#pragma once
#include "Object.h"
#include "BoundingSphere.h"

namespace junkNS
{
	const float BOUND_FORCE = 300.0f;
	const float ROTATION_SPEED = 6.0f;
	const float HEAD_FORCE = 100.0f;
	const float HEAD_DISTANCE = 50.0f;
}

class Junk :public Object
{
	D3DXVECTOR3 axisRotation;//ñ]²
public:
	BoundingSphere bodyCollide;
	Ray betweenField;
	Junk();
	~Junk();
	void initialize(LPDIRECT3DDEVICE9 device, StaticMesh* _staticMesh, D3DXVECTOR3* _position);

	void update(float frameTime, LPD3DXMESH fieldMesh, D3DXMATRIX fieldMatrix, D3DXVECTOR3 fieldPosition);
	void bound();
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);
	void roopRotation();
	void changeAxisRotation();
	void headPosition(D3DXVECTOR3 headPosition);

};

