//===================================================================================================================================
//�yBullet.h�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/07/31
// [�X�V��]2019/08/04
//===================================================================================================================================
#pragma once
#include "Object.h"
#include "BoundingSphere.h"

namespace bulletNS
{
	const float EXISTENCE_TIME = 3.0f;		//���ݎ���
	const float GRAVITY_FORCE = 60.0f;		//�d��
	const float SPEED = 70.0f;

}

class Bullet :	public Object
{
private:
	float existenceTimer;
	D3DXVECTOR3* attractorPosition;						//�d�́i���́j�����ʒu
	float attractorRadius;								//�d�́i���́j�����I�u�W�F�N�g���a

public:
	BoundingSphere bodyCollide;

	//Method
	Bullet();
	~Bullet();
	
	//processing
	void initialize(LPDIRECT3DDEVICE9 device, StaticMesh* _staticMesh, D3DXVECTOR3* _position);
	void update(float frameTime);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);
	
	//operation
	void configurationGravity(D3DXVECTOR3* attractorPosition, float _attractorRadius);
	
	//setter

	//getter
};

