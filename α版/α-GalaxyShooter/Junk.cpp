#include "Junk.h"

using namespace junkNS;

Junk::Junk()
{
	onGravity = true;
	activation();
	changeAxisRotation();
}


Junk::~Junk()
{
}

void Junk::initialize(LPDIRECT3DDEVICE9 device, LPSTR xFileName, D3DXVECTOR3* _position)
{
	Object::initialize(device, xFileName, _position);
	bodyCollide.initialize(device, &position, mesh);
	radius = bodyCollide.getRadius();
}

void Junk::update(float frameTime, LPD3DXMESH fieldMesh, D3DXMATRIX fieldMatrix,D3DXVECTOR3 fieldPosition)
{
	setSpeed(D3DXVECTOR3(0, 0, 0));

	float difference = 1.0f;


	D3DXVECTOR3 gravityDirection;
	D3DXVec3Normalize(&gravityDirection, &(fieldPosition - position));
	betweenField.update(position, gravityDirection);
	


	//�t�B�[���h�␳
	if (betweenField.rayIntersect(fieldMesh, fieldMatrix) &&
		radius >= (betweenField.distance - difference))
	{
		//�߂荞�ݕ␳
		setPosition(position + betweenField.normal*(radius - betweenField.distance));
		//�ړ��x�N�g���̃X���b�v�i�ʕ����ւ̃x�N�g�������̍폜�j
		//setSpeed(reverseAxisY.slip(speed, reverseAxisY.normal));
		//Ray moveRay;//�ړ��x�N�g�����g���ă��C���쐬
		//moveRay.initialize(*bullet[i].getPosition(), bullet[i].getSpeed());
		//if(moveRay.rayIntersect(*field.getMesh(),field.getMatrixWorld()) && bullet[i].getRadius() > moveRay.distance)
		//{//��d�`�F�b�N
		//	bullet[i].setSpeed(moveRay.slip(bullet[i].getSpeed(),moveRay.normal));
		//}
		bound();
	}
	else {
		setGravity(gravityDirection, 80.0f);
	}

	roopRotation();

	if (D3DXVec3Length(&acceleration) > 0.01f)
	{//�����x���������ꍇ�A���Z���Ȃ�
		speed += acceleration;
	}

	//�ʒu�X�V
	position += speed * frameTime;

	//�����x����
	acceleration *= 0.9f;
	Object::update();

}

void Junk::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	Object::render(device, view, projection, cameraPositon);

	bodyCollide.render(device, matrixWorld);
}

void Junk::bound()
{
	changeAxisRotation();
	float rate = rand() % 10;
	rate *= 0.1;
	acceleration += betweenField.normal*(BOUND_FORCE*rate);
}

void Junk::roopRotation()
{
	anyAxisRotation(axisRotation, ROTATION_SPEED);
}

void Junk::changeAxisRotation()
{
	axisRotation = D3DXVECTOR3(rand() % 10, rand() % 10, rand() % 10);
	D3DXVec3Normalize(&axisRotation, &axisRotation);
}

void Junk::headPosition(D3DXVECTOR3 headPosition)
{
	onGravity == false;
	D3DXVECTOR3 headDirection;
	float headDistance = between2VectorDirection(&headDirection,position,headPosition);
	//�����x�̑����ʂ��߂Â��قǏ���������B
	acceleration += headDirection*(HEAD_FORCE/headDistance);
}