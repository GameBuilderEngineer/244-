//=============================================================================
// 2D���� [Sprite.h]
//
// Author : HAL�������ԕ� 2�N���Q�[���w�� GP12A332 32 �����a�P
// �쐬�� : 2019/6/8
//=============================================================================
#pragma once
#include <d3dx9.h>
#include "Base.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �Q�c�|���S�����_�t�H�[�}�b�g( ���_���W[2D] / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)


//*****************************************************************************
// �萔��`
//*****************************************************************************
namespace spriteNS
{
	const  int	NUM_VERTEX = 4;			// ���_��
	const  int	NUM_POLYGON = 2;		// �|���S����

	// ���_�i��]���j
	enum PIVOT {
		CENTER,
		TOP_LEFT,
		// ���͖��Ή�
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_RIGHT,
		PIVOT_MAX
	};
}


//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// �Q�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
struct VERTEX_2D
{
	D3DXVECTOR3			vtx;		// ���_���W
	float				rhw;		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR			diffuse;	// ���ˌ�
	D3DXVECTOR2			uv;			// �e�N�X�`�����W
};


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Sprite {

private:
	// Data
	VERTEX_2D			vertexWk[spriteNS::NUM_VERTEX];	// ���_���i�[���[�N
	LPDIRECT3DTEXTURE9	texture;						// �e�N�X�`���ւ̃|�C���^
	int					pivot;							// ���_�i��]���j
	int					width;							// ����
	int					height;							// ����
	D3DXVECTOR3			position;						// �ʒu
	D3DXVECTOR3			rotation;						// ��]
	float				centralAngle;					// ���S���W����S���_�ւ̊p�x
	float				radius;							// ���a
	float				originalRadius;					// ���̔��a
	float				alpha;							// �A���t�@�l

public:
	// Method
	Sprite(void);
	~Sprite(void);
	virtual void initialize(LPDIRECT3DDEVICE9 device, LPSTR fileName, int _pivot, int sizeX, int sizeY, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DCOLOR color);
	virtual void initialize(LPDIRECT3DDEVICE9 device, LPDIRECT3DTEXTURE9 _texture, int _pivot, int _width, int _height, D3DXVECTOR3 _position, D3DXVECTOR3 _rotation, D3DCOLOR color);
	virtual void uninitialize(void);
	virtual void render(LPDIRECT3DDEVICE9 device);

	HRESULT setTexture(LPDIRECT3DDEVICE9 device, LPSTR fileName);		// �e�N�X�`���̐ݒ�
	void setTexture(LPDIRECT3DTEXTURE9 _texture);						// �e�N�X�`���̐ݒ�@�|�C���^���Ver
	void setUVCoordinates(D3DXVECTOR2 v0, D3DXVECTOR2 v1,D3DXVECTOR2 v2, D3DXVECTOR2 v3);// �e�N�X�`��UV���W�̐ݒ�
	void setSize(int sizeX, int sizeY);									// �T�C�Y�ݒ�
	void setVertex(void);												// ���_���W�̐ݒ�
	void setColor(D3DCOLOR v0, D3DCOLOR v1, D3DCOLOR v2, D3DCOLOR v3);	// �J���[�̐ݒ�
	void setColor(D3DCOLOR color);										// �J���[�̐ݒ�@�S���_�ꊇ�ݒ�Ver
	void setAlpha(D3DCOLOR color);
	void setPosition2(D3DXVECTOR3 _position);

	D3DXVECTOR3 getPosition(void) { return position; }
	D3DXVECTOR3 getRotation(void) { return rotation; }
	void setPosition(D3DXVECTOR3 _position) { position = _position; }
	void setRotation(D3DXVECTOR3 _position) { position = _position; }
	void setPivot(int _pivot) { pivot = _pivot; }
};
