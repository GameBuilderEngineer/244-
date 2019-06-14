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

void Player::move(D3DXVECTOR2 operationDirection,D3DXVECTOR3 cameraAxisX,D3DXVECTOR3 cameraAxisZ)
{
	if (operationDirection.x == 0 && operationDirection.y == 0)return;//���͒l��0�ȉ��Ȃ�Έړ����Ȃ�
	//Y�������ւ̐������폜����
	D3DXVECTOR3 front = slip(cameraAxisZ, axisY.direction);
	D3DXVECTOR3 right = slip(cameraAxisX, axisY.direction);
	D3DXVec3Normalize(&front, &front);//���K��
	D3DXVec3Normalize(&right, &right);//���K��

	//����������J������XZ�����ɏ��������ړ��x�N�g���֕ϊ�����
	D3DXVECTOR3 moveDirection = operationDirection.x*right + -operationDirection.y*front;
	addSpeed(moveDirection*0.0007);
	postureControl(getAxisZ()->direction, moveDirection, 0.1f);
}