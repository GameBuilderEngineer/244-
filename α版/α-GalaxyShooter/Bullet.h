#pragma once
#include "Object.h"
#include "BoundingSphere.h"

namespace bulletNS
{
	const float EXISTENCE_TIME = 5.0f;
}

class Bullet :	public Object
{
private:
	float existenceTimer;

public:
	BoundingSphere bodyCollide;

	Bullet();
	~Bullet();

	void initialize(LPDIRECT3DDEVICE9 device, LPSTR xFileName, D3DXVECTOR3* _position);
	void update(float frameTime, LPD3DXMESH fieldMesh, D3DXMATRIX matrix);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);

};

