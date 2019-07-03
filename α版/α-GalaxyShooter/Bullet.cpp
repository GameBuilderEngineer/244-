#include "Bullet.h"
using namespace bulletNS;

Bullet::Bullet()
{
	onGravity = true;
	inActivation();
	existenceTimer = 0.0f;
}


Bullet::~Bullet()
{
}

void Bullet::initialize(LPDIRECT3DDEVICE9 device, StaticMesh* _staticMesh, D3DXVECTOR3* _position)
{
	Object::initialize(device, _staticMesh, _position);
	bodyCollide.initialize(device, &position, staticMesh->mesh);
	radius = bodyCollide.getRadius();
}

void Bullet::update(float frameTime, LPD3DXMESH fieldMesh,D3DXMATRIX matrix)
{
	if (onActive == false)return;

	existenceTimer += frameTime;
	if (existenceTimer >= EXISTENCE_TIME)
	{
		existenceTimer = 0.0f;
		inActivation();
		return;
	}
	float difference = 1.0f;

	setSpeed(D3DXVECTOR3(0, 0, 0));
	addSpeed(getAxisZ()->direction*50.0);//�����ړ�

	//anyAxisRotation(axisY.direction, (rand() % 10) - 5);

	//�t�B�[���h�␳
	if (reverseAxisY.rayIntersect(fieldMesh, matrix) &&
		radius+2.0f >= (reverseAxisY.distance - difference))
	{
		//�߂荞�ݕ␳
		setPosition(position + axisY.direction*(radius + 2.0f - reverseAxisY.distance));
		//�ړ��x�N�g���̃X���b�v�i�ʕ����ւ̃x�N�g�������̍폜�j
		setSpeed(reverseAxisY.slip(speed, reverseAxisY.normal));
		//Ray moveRay;//�ړ��x�N�g�����g���ă��C���쐬
		//moveRay.initialize(*bullet[i].getPosition(), bullet[i].getSpeed());
		//if(moveRay.rayIntersect(*field.getMesh(),field.getMatrixWorld()) && bullet[i].getRadius() > moveRay.distance)
		//{//��d�`�F�b�N
		//	bullet[i].setSpeed(moveRay.slip(bullet[i].getSpeed(),moveRay.normal));
		//}
		
	}
	else {
		setGravity(-axisY.direction, 80.0f);
	}

	D3DXVECTOR3 moveDirection;

	if (D3DXVec3Length(&acceleration) > 0.01f)
	{//�����x���������ꍇ�A���Z���Ȃ�
		speed += acceleration;
	}

	//�ʒu�X�V
	position += speed * frameTime;

	//�����x����
	acceleration *= 0.9f;

	//�p������
	postureControl(axisY.direction, reverseAxisY.normal, 3.0f * frameTime);


	Object::update();
}

void Bullet::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	Object::render(device, view, projection, cameraPositon);
#ifdef _DEBUG
	bodyCollide.render(device, matrixWorld);
#endif // _DEBUG
}
