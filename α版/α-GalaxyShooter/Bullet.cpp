//===================================================================================================================================
//�yBullet.cpp�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/07/31
// [�X�V��]2019/08/04
//===================================================================================================================================
#include "Bullet.h"
using namespace bulletNS;

Bullet::Bullet()
{
	onLighting = false;
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

void Bullet::update(float frameTime)
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
	addSpeed(getAxisZ()->direction*SPEED);//�����ړ�

	//===========
	//�y�ڒn�����z
	//===========
	//�d�͐����쐬
	D3DXVECTOR3 gravityDirection;
	between2VectorDirection(&gravityDirection, position, *attractorPosition);
	gravityRay.initialize(position, gravityDirection);//�d�̓��C�̏�����
	if (radius + attractorRadius >= (between2VectorLength(position, *attractorPosition) - difference))
	{
		//�߂荞�ݕ␳
		//���݈ʒu+ ��������*(�߂荞�݋���)
		setPosition(position + -gravityDirection * (radius + attractorRadius - between2VectorLength(position, *attractorPosition)));
		//�ړ��x�N�g���̃X���b�v�i�ʕ����ւ̃x�N�g�������̍폜�j
		setSpeed(reverseAxisY.slip(speed, -gravityDirection));
	}
	else {
		setGravity(gravityDirection, GRAVITY_FORCE);
	}

	if (D3DXVec3Length(&acceleration) > 0.01f)
	{//�����x���������ꍇ�A���Z���Ȃ�
		speed += acceleration;
	}

	//�ʒu�X�V
	position += speed * frameTime;

	//�����x����
	acceleration *= 0.9f;

	//�p������
	postureControl(axisY.direction, -gravityRay.direction, 3.0f * frameTime);

	Object::update();
}

void Bullet::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	Object::render(device, view, projection, cameraPositon);
#ifdef _DEBUG
	bodyCollide.render(device, matrixWorld);
#endif // _DEBUG
}

//===================================================================================================================================
//�y�d�͐ݒ�z
//[���e]�d�͌��̈ʒu���ŏd�͂�ݒ肷��
//[����]
//D3DXVECTOR3* attractorPosition�F���͔����n�_
//===================================================================================================================================
void Bullet::configurationGravity(D3DXVECTOR3* _attractorPosition, float _attractorRadius)
{
	//�d�͏������s�����߂ɕK�v�ȗv�f���Z�b�g
	attractorPosition = _attractorPosition;
	attractorRadius = _attractorRadius;
	//�d�͐����쐬
	D3DXVECTOR3 gravityDirection;
	between2VectorDirection(&gravityDirection, position, *attractorPosition);
	gravityRay.initialize(position, gravityDirection);//�d�̓��C�̏�����
	setGravity(gravityDirection, GRAVITY_FORCE);
	//postureControl(axisY.direction, gravityDirection, 1.0f);
}
