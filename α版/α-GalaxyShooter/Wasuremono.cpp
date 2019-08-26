//-----------------------------------------------------------------------------
// ���X�����m����[Wasuremono.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/7
//-----------------------------------------------------------------------------
#include "Wasuremono.h"
#include "Map.h"

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
WasuremonoTable* Wasuremono::table;		// ���X�����m�e�[�u�����w���|�C���^


//=============================================================================
// �R���X�g���N�^
//=============================================================================
Wasuremono::Wasuremono(void)
{

}

Wasuremono::Wasuremono(LPDIRECT3DDEVICE9 device, int typeID, D3DXVECTOR3 *position)
{
	this->typeID = typeID;
	Object::initialize(device, table->getStaticMesh(typeID), position);
	bodyCollide.initialize(device, position, staticMesh->mesh);
	radius = bodyCollide.getRadius();
	onGravity = true;
	activation();
}


//=============================================================================
// ����������
//=============================================================================
void Wasuremono::initialize(LPDIRECT3DDEVICE9 device, int typeID, D3DXVECTOR3 *position)
{
	Wasuremono(device, typeID, position);
}


//=============================================================================
// �X�V����
//=============================================================================
void Wasuremono::update(float frameTime, LPD3DXMESH fieldMesh, D3DXMATRIX matrix, D3DXVECTOR3 fieldPosition)
{
	if (!onActive) { return; }

	setSpeed(D3DXVECTOR3(0, 0, 0));

	float difference = 1.0f;

	//// �d�͕����̃x�N�g��&���C���쐬�i�O�����B�e�B���C�ɂ��������ł���H�j
	//D3DXVECTOR3 gravityDirection;
	//D3DXVec3Normalize(&gravityDirection, &(fieldPosition - position));
	//betweenField.update(position, gravityDirection);

	////�t�B�[���h�␳
	//if (betweenField.rayIntersect(fieldMesh, matrix) &&
	//	radius >= (betweenField.distance - difference))
	//{
	//	//�߂荞�ݕ␳
	//	setPosition(position + betweenField.normal*(radius - betweenField.distance));
	//	//�ړ��x�N�g���̃X���b�v�i�ʕ����ւ̃x�N�g�������̍폜�j
	//	//setSpeed(reverseAxisY.slip(speed, reverseAxisY.normal));
	//	//Ray moveRay;//�ړ��x�N�g�����g���ă��C���쐬
	//	//moveRay.initialize(*bullet[i].getPosition(), bullet[i].getSpeed());
	//	//if(moveRay.rayIntersect(*field.getMesh(),field.getMatrixWorld()) && bullet[i].getRadius() > moveRay.distance)
	//	//{//��d�`�F�b�N
	//	//	bullet[i].setSpeed(moveRay.slip(bullet[i].getSpeed(),moveRay.normal));
	//	//}
	//	//bound();

	//}
	//else {
	//	setGravity(gravityDirection, 80.0f);
	//}

	//===========
	//�y�ڒn�����z
	//===========
	D3DXVECTOR3 *attractorPosition = Map::getField()->getPosition();
	float attractorRadius = Map::getField()->getRadius();
	//�d�͐����쐬
	D3DXVECTOR3 gravityDirection;
	between2VectorDirection(&gravityDirection, position, *attractorPosition);		//�d�͕������Z�o
	gravityRay.initialize(position, gravityDirection);								//�d�̓��C�̏�����
	float distanceToAttractor = between2VectorLength(position, *attractorPosition);	//�d�͔������Ƃ̋���
	if (radius + attractorRadius >= distanceToAttractor - difference)
	{
		//���ݔ��a���v�l�����͔������Ƃ̋������Z���Ɛڒn
		onGravity = false;
		//�߂荞�ݕ␳
		//���݈ʒu+ ��������*(�߂荞�݋���)
		setPosition(position + axisY.direction * (radius + attractorRadius - distanceToAttractor));
		//�ړ��x�N�g���̃X���b�v�i�ʕ����ւ̃x�N�g�������̍폜�j
		setSpeed(reverseAxisY.slip(speed, axisY.direction));
		acceleration *= 0;
	}
	else {
		//��
		onGravity = true;
	}
	setGravity(gravityDirection, 80.0f);//�d�͏���


	if (D3DXVec3Length(&acceleration) > 0.01f)
	{//�����x���������ꍇ�A���Z���Ȃ�
		speed += acceleration;
	}

	//�ʒu�X�V
	position += speed * frameTime;

	//�����x����
	acceleration *= 0.9f;

	// �p������c�c�d�͕������C�𓖂Ă��t�B�[���h�̖@���Ǝ���Y�����g�p
	postureControl(axisY.direction, betweenField.normal, 3.0f * frameTime);

	Object::update();
}


//=============================================================================
// �`�揈��
//=============================================================================
void Wasuremono::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	Object::render(device, view, projection, cameraPositon);
#ifdef _DEBUG
	bodyCollide.render(device, matrixWorld);
#endif
}
