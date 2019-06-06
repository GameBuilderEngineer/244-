//=============================================================================
// 2D��`���� [quad.cpp]
//
// Author : HAL�������ԕ� 2�N���Q�[���w�� GP12A332 32 �����a�P
// �쐬�� : 2019/6/1
//=============================================================================
//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "Main.h"
#include "Quad.h"


//=============================================================================
// 2D��`�̃T�C�Y�ݒ�
//=============================================================================
void Quad::setSize(int sizeX, int sizeY)
{
	centralAngle = atan2f((float)sizeY / 2, (float)sizeX / 2);				// ���S���W���璸�_�ւ̊p�x��������
	D3DXVECTOR2 vec = D3DXVECTOR2((float)sizeX / 2, (float)sizeY / 2);		// ���S���W���璸�_�ւ̃x�N�g�������߂�
	originalRadius = radius = D3DXVec2Length(&vec);							// ���a�̏�����
}


//=============================================================================
// 2D��`�̒��_���W�̐ݒ�
//=============================================================================
void Quad::setVertex(void)
{
	// �A�t�B���ϊ�
	vertexWk[0].vtx.x = position.x - cosf(centralAngle + rotation.z) * radius;
	vertexWk[0].vtx.y = position.y - sinf(centralAngle + rotation.z) * radius;
	vertexWk[1].vtx.x = position.x + cosf(centralAngle - rotation.z) * radius;
	vertexWk[1].vtx.y = position.y - sinf(centralAngle - rotation.z) * radius;
	vertexWk[2].vtx.x = position.x - cosf(centralAngle - rotation.z) * radius;
	vertexWk[2].vtx.y = position.y + sinf(centralAngle - rotation.z) * radius;
	vertexWk[3].vtx.x = position.x + cosf(centralAngle + rotation.z) * radius;
	vertexWk[3].vtx.y = position.y + sinf(centralAngle + rotation.z) * radius;
}


//=============================================================================
// 2D��`�̒��_�J���[�̐ݒ�
//=============================================================================
void Quad::setColor(D3DCOLOR setColor)
{
	// �ꊇ�ݒ�
	vertexWk[0].diffuse = setColor;
	vertexWk[1].diffuse = setColor;
	vertexWk[2].diffuse = setColor;
	vertexWk[3].diffuse = setColor;
}


//=============================================================================
// �e�N�X�`��UV���W�̐ݒ�
//=============================================================================
void Quad::setTexture(D3DXVECTOR2 v0, D3DXVECTOR2 v1, D3DXVECTOR2 v2, D3DXVECTOR2 v3)
{
	vertexWk[0].tex = v0;
	vertexWk[1].tex = v1;
	vertexWk[2].tex = v2;
	vertexWk[3].tex = v3;
}


//=============================================================================
// 2D��`�̏�����
//=============================================================================
void Quad::initQuad(int sizeX, int sizeY, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DCOLOR color)
{
	setSize(sizeX, sizeY);		// �T�C�Y
	this->position = position;	// ���W
	this->rotation = rotation;	// ���W
	setVertex();				// ���_���W�̐ݒ�
	setColor(color);			// ���_�J���[�̐ݒ�

	// �e�N�X�`��UV���W�̐ݒ�
	setTexture(D3DXVECTOR2(0.0, 0.0), D3DXVECTOR2(1.0, 0.0), D3DXVECTOR2(0.0, 1.0), D3DXVECTOR2(1.0, 1.0));

	// rhw�̐ݒ�
	vertexWk[0].rhw = vertexWk[1].rhw = vertexWk[2].rhw = vertexWk[3].rhw = 1.0f;
}


//=============================================================================
// �R���X�g���N�^
//=============================================================================
Quad::Quad(void)
{
}

Quad::Quad(int sizeX, int sizeY, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DCOLOR color)
{
	// �錾�Ɠ����ɏ������ł���
	initQuad(sizeX, sizeY, position, rotation, color);
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
Quad::~Quad(void)
{
}
