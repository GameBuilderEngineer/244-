#include "Player.h"

Player::Player()
{
	onGravity = true;
	radius = 5.0f;
}

Player::~Player()
{

}

void Player::initialize(LPDIRECT3DDEVICE9 device, LPSTR xFileName, D3DXVECTOR3* _position)
{
	Object::initialize(device, xFileName, _position);
	bodyCollide.initialize(device, &position, mesh);
}

void Player::update()
{
	if (D3DXVec3Length(&acceleration) > 0.01f)
	{
		speed += acceleration;
	}
	position += speed;

	acceleration *= 0.9f;
	

	postureControl(axisY.direction, reverseAxisY.normal,0.05f);

	Object::update();
}

void Player::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	Object::render(device,view,projection,cameraPositon);
	bodyCollide.render(device, matrixWorld);

}

void Player::jump()
{
	acceleration += axisY.direction;
}

void Player::move(D3DXVECTOR2 moveDirection)
{
	//D3DXVec3Normalize(&moveDirection, &slip(camera[i].getDirectionZ(), player[i].getAxisY()->direction));
	//player[i].addSpeed(moveDirection*0.1);
	//player[i].postureControl(player[i].getAxisZ()->direction, moveDirection, 0.1f);

}