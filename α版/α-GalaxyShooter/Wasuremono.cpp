//-----------------------------------------------------------------------------
// �`���M���f�[�^����[Wasuremono.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/7
//-----------------------------------------------------------------------------
#include "Wasuremono.h"

//*****************************************************************************
// �O���[�o���ϐ��@(���ÓI�����o�ϐ�)
//*****************************************************************************
LPDIRECT3DDEVICE9 Wasuremono::device;	// �f�o�C�X
WasuremonoTable* Wasuremono::table;		// ���X�����m�e�[�u�����w���|�C���^


//=============================================================================
// �R���X�g���N�^
//=============================================================================
Wasuremono::Wasuremono(void)
{

}

Wasuremono::Wasuremono(int typeID, D3DXVECTOR3 *position)
{
	initialize(typeID, position);
}


//=============================================================================
// ����������
//=============================================================================
void Wasuremono::initialize(int typeID, D3DXVECTOR3 *position)
{
	this->typeID = typeID;
	Object::initialize(device, table->getStaticMesh(typeID), position);
	bodyCollide.initialize(device, position, staticMesh->mesh);
	radius = bodyCollide.getRadius();
}


//=============================================================================
// �X�V����
//=============================================================================
void Wasuremono::update()
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


//*****************************************************************************
// �e���X�����m�̍X�V����
//*****************************************************************************
//=============================================================================
// �`���[�C���O�K��
//=============================================================================
void ChewingGum::update(void)
{
	Wasuremono::update();
}

//=============================================================================
// ��@
//=============================================================================
void ElectricFan::update(void)
{
	Wasuremono::update();
}


//=============================================================================
// �꒵��
//=============================================================================
void JumpRope::update(void)
{
	Wasuremono::update();
}


//=============================================================================
// �e���r
//=============================================================================
void Television::update(void)
{
	Wasuremono::update();
}


//=============================================================================
// ���񂾂�
//=============================================================================
void Kendama::update(void)
{
	Wasuremono::update();
}


//=============================================================================
// �T�b�J�[�{�[��
//=============================================================================
void SoccerBall::update(void)
{
	Wasuremono::update();
}


//=============================================================================
// �N���X�}�X�c���[
//=============================================================================
void ChristmasTree::update(void)
{
	Wasuremono::update();
}


//=============================================================================
// ���]��
//=============================================================================
void Bicycle::update(void)
{
	Wasuremono::update();
}


//=============================================================================
// ���d�b
//=============================================================================
void DialPhone::update(void)
{
	Wasuremono::update();
}


//=============================================================================
// �E�T�M�̂ʂ������
//=============================================================================
void StuffedBunny::update(void)
{
	Wasuremono::update();
}
