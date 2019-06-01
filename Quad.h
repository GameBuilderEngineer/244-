//=============================================================================
// 2D��`���� [quad.h]
//
// Author : HAL�������ԕ� 2�N���Q�[���w�� GP12A332 32 �����a�P
// �쐬�� : 2019/6/1
//=============================================================================
//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#pragma once
#include "Main.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �Q�c�|���S�����_�t�H�[�}�b�g( ���_���W[2D] / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define	NUM_VERTEX		(4)			// ���_��
#define	NUM_POLYGON		(2)			// �|���S����


//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// �Q�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3			vtx;		// ���_���W
	float				rhw;		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR			diffuse;	// ���ˌ�
	D3DXVECTOR2			tex;		// �e�N�X�`�����W
} VERTEX_2D;


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Quad {
protected:
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N
	D3DXVECTOR3		position;					// �ʒu
	D3DXVECTOR3		rotation;					// ��]
	float			centralAngle;				// ���S���W����S���_�ւ̊p�x
	float			radius;						// ���a
	float			originalRadius;				// ���̔��a

public:
	void setSize(int sizeX, int sizeY);			// 2D��`�̃T�C�Y�ݒ�
	void setVertex(void);						// 2D��`�̒��_���W�̐ݒ�
	void setColor(D3DCOLOR setColor);			// 2D��`���_�J���[�̐ݒ�
												// �e�N�X�`��UV���W�̐ݒ�
	void setTexture(D3DXVECTOR2 v0, D3DXVECTOR2 v1, D3DXVECTOR2 v2, D3DXVECTOR2 v3);
												// 2D��`�̏�����
	void initQuad(int sizeX, int sizeY, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DCOLOR color);

	// �R���X�g���N�^�E�f�X�g���N�^
	Quad(void);
	Quad(int sizeX, int sizeY, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DCOLOR color);
	~Quad(void);

	// �A�N�Z�T
	D3DXVECTOR3 getPosition(void) { return position; }
	D3DXVECTOR3 getRotation(void) { return rotation; }
	D3DXVECTOR3 setPosition(void) { return position; }
	D3DXVECTOR3 setRotation(void) { return rotation; }
};
