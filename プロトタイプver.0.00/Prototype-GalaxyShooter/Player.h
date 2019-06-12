#pragma once
#include "Object.h"
#include "BoudingSphere.h"

class Player : public Object
{
public:
	BoudingSphere bodyCollide;

	Player();
	~Player();

	void initialize(LPDIRECT3DDEVICE9 device, LPSTR xFileName, D3DXVECTOR3* _position);
	void update();
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);
	void move(D3DXVECTOR2 moveDirection);
	void jump();
};

