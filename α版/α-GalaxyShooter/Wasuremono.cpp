//-----------------------------------------------------------------------------
// ���X�����m����[Wasuremono.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/7
//-----------------------------------------------------------------------------
#include "Wasuremono.h"
#include "Map.h"
using namespace wasuremonoNS;
//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
WasuremonoTable* Wasuremono::table;		// ���X�����m�e�[�u�����w���|�C���^


//=============================================================================
// �R���X�g���N�^
//=============================================================================
Wasuremono::Wasuremono(void)
{
	onRecursion = false;
}

Wasuremono::Wasuremono(LPDIRECT3DDEVICE9 device, int typeID, D3DXVECTOR3 *position)
{
	onRecursion = false;
	this->typeID = typeID;
	Object::initialize(device, table->getStaticMesh(typeID), position);
	bodyCollide.initialize(device, position, staticMesh->mesh);
	radius = bodyCollide.getRadius();
	onGravity = true;
	activation();
	difference = DIFFERENCE_FIELD;
	configurationGravity(Map::getField()->getPosition(), Map::getField()->getRadius());
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

	//===========
	//�y�ڒn�����z
	//===========
	//�d�͐����쐬
	D3DXVECTOR3 gravityDirection;
	between2VectorDirection(&gravityDirection, position, *attractorPosition);		//�d�͕������Z�o
	gravityRay.initialize(position, gravityDirection);								//�d�̓��C�̏�����
	float distanceToAttractor = between2VectorLength(position, *attractorPosition);	//�d�͔������Ƃ̋���
	if (!onRecursion) {
		if (radius + attractorRadius >= distanceToAttractor - difference)
		{
			//���ݔ��a���v�l�����͔������Ƃ̋������Z���Ɛڒn
			onGround = true;
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
			onGround = false;
			onGravity = true;
		}
		setGravity(gravityDirection, GRAVITY_FORCE*frameTime);//�d�͏���
	}

	recursionProcessing();

	if (D3DXVec3Length(&acceleration) > 0.05f)
	{//�����x���������ꍇ�A���Z���Ȃ�
		speed += acceleration;
	}

	//�ʒu�X�V
	position += speed * frameTime;


	// �p������c�c�d�͕������C�𓖂Ă��t�B�[���h�̖@���Ǝ���Y�����g�p
	postureControl(axisY.direction, -gravityRay.direction, 3.0f * frameTime);


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

//===================================================================================================================================
//�y�d�͐ݒ�z
//[���e]�d�͌��̈ʒu���ŏd�͂�ݒ肷��
//[����]
//D3DXVECTOR3* attractorPosition�F���͔����n�_
//===================================================================================================================================
void Wasuremono::configurationGravity(D3DXVECTOR3* _attractorPosition, float _attractorRadius)
{
	//�d�͏������s�����߂ɕK�v�ȗv�f���Z�b�g
	attractorPosition = _attractorPosition;
	attractorRadius = _attractorRadius;
	//�d�͐����쐬
	D3DXVECTOR3 gravityDirection;
	between2VectorDirection(&gravityDirection, position, *attractorPosition);
	gravityRay.initialize(position, gravityDirection);//�d�̓��C�̏�����
	setGravity(gravityDirection, GRAVITY_FORCE);
	postureControl(axisY.direction, gravityDirection, 1.0f);
}

//===================================================================================================================================
//�y���J�[�W�����ւ̋z�������z
//===================================================================================================================================
void Wasuremono::recursionProcessing()
{
	if (!onRecursion)return;
	D3DXVECTOR3 centerDirection;	//���J�[�W�����̒��S�i�d�S�j�����x�N�g��

	//���J�[�W�����̒��S�i�d�S�j�ʒu�����x�N�g���̍쐬
	Base::between2VectorDirection(&centerDirection, position, recursionCenter);

	//���J�[�W�����̉��������̃x�N�g�����폜����i�d�S�֌��������Ƃ�h���j
	centerDirection = slip(centerDirection, recursionVertical);
	acceleration += centerDirection*INHALE_FORCE+recursionVertical;
}

//===================================================================================================================================
//�y���J�[�W���������N���z
//===================================================================================================================================
void Wasuremono::startUpRecursion(D3DXVECTOR3 _recursionCenter, D3DXVECTOR3 fieldCenter)
{

	recursionCenter = _recursionCenter;
	onRecursion = true;

	//���J�[�W�����̒��S�i�d�S�j���������x�N�g���̍쐬
	Base::between2VectorDirection(&recursionVertical, fieldCenter, recursionCenter);

	//���J�[�W�����̒��S�i�d�S�j�ʒu�����x�N�g���̍쐬
	D3DXVECTOR3 centerDirection;
	Base::between2VectorDirection(&centerDirection, position, recursionCenter);
	//���J�[�W�����̉��������̃x�N�g�����폜����i�d�S�֌��������Ƃ�h���j
	centerDirection = slip(centerDirection, recursionVertical);
	D3DXVec3Normalize(&centerDirection, &centerDirection);

	//�������쐬
	D3DXVECTOR3 initialSpeed;
	D3DXVec3Cross(&initialSpeed, &centerDirection,&recursionVertical);
	D3DXVec3Normalize(&initialSpeed, &initialSpeed);
	initialSpeed += centerDirection;
	D3DXVec3Normalize(&initialSpeed, &initialSpeed);

	acceleration += initialSpeed*INHALE_FORCE;


	//���J�[�W�����̉��������̃x�N�g�����폜����i�d�S�֌��������Ƃ�h���j
	centerDirection = slip(centerDirection, recursionVertical);


}