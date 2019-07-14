//=============================================================================
// �G�t�F�N�g���� [ScreenEffectBase.h]
//
//=============================================================================

#pragma once
#include "Base.h"
#include <d3dx9.h>
#include "StaticMeshLoader.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �Q�c�|���S�����_�t�H�[�}�b�g( ���_���W[2D] / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// �R�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / �@�� / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_3D		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//*****************************************************************************
// �萔��`
//*****************************************************************************
namespace ScreenEffectNS
{
	const  int	NUM_VERTEX = 4;			// ���_��
	const  int	NUM_POLYGON = 2;		// �|���S����

	// �G�t�F�N�g���_�i��]���j
	enum F_PIVOT {
		F_CENTER,
		F_TOP_LEFT,
		F_PIVOT_MAX
	};
}

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// �Q�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
struct VERTEX_2D_F
{
	D3DXVECTOR3			vtx;		// ���_���W
	float				rhw;		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR			diffuse;	// ���ˌ�
	D3DXVECTOR2			uv;			// �e�N�X�`�����W
};

// ��L�R�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
struct VERTEX_3D_F
{
	D3DXVECTOR3			vtx;		// ���_���W
	D3DXVECTOR3			nor;		// �@���x�N�g��
	D3DCOLOR			diffuse;	// ���ˌ�
	D3DXVECTOR2			tex;		// �e�N�X�`�����W
};

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class ScreenEffectBase
{
protected:
	VERTEX_2D_F			vertexWk[ScreenEffectNS::NUM_VERTEX];	// ���_���i�[���[�N
	VERTEX_3D_F			vertexWk3D[ScreenEffectNS::NUM_VERTEX];	// ���_���i�[���[�N
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
	int					settingFrame;					// �G�t�F�N�g��������
	int					cntFrame;						// �G�t�F�N�g�������ԉ��Z

	//�X�^�e�B�b�N���b�V��
	StaticMesh* staticMesh;
	//�s��i�ʒu�E��]�E���[���h�j�F�X�P�[���ǉ��\��
	D3DXMATRIX matrixPosition;
	D3DXMATRIX matrixRotation;
	D3DXMATRIX matrixWorld;

public:
	ScreenEffectBase();
	~ScreenEffectBase();

	virtual void initialize(LPDIRECT3DDEVICE9 device, LPDIRECT3DTEXTURE9 _texture, int _pivot, int _width, int _height, D3DXVECTOR3 _position, D3DXVECTOR3 _rotation, D3DCOLOR color);
	virtual void uninitialize(void);
	virtual void render2D(LPDIRECT3DDEVICE9 device);
	virtual void render3D(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);
	virtual void activate(int second);
	virtual void inactivate(void);
	HRESULT setTexture(LPDIRECT3DDEVICE9 device, LPSTR fileName);		// �e�N�X�`���̐ݒ�
	void setTexture(LPDIRECT3DTEXTURE9 _texture);						// �e�N�X�`���̐ݒ�@�|�C���^���Ver
	void setUVCoordinates(D3DXVECTOR2 v0, D3DXVECTOR2 v1, D3DXVECTOR2 v2, D3DXVECTOR2 v3);// �e�N�X�`��UV���W�̐ݒ�
	void setSize(int sizeX, int sizeY);									// �T�C�Y�ݒ�
	void setVertex(void);												// ���_���W�̐ݒ�
	void setColor(D3DCOLOR v0, D3DCOLOR v1, D3DCOLOR v2, D3DCOLOR v3);	// �J���[�̐ݒ�
	void setColor(D3DCOLOR color);										// �J���[�̐ݒ�@�S���_�ꊇ�ݒ�Ver
	void setAlpha(D3DCOLOR color);
	void setPosition2(D3DXVECTOR3 _position);

	D3DXVECTOR3 getPosition(void) { return position; }
	D3DXVECTOR3 getRotation(void) { return rotation; }
	D3DXVECTOR3 setPosition(void) { return position; }
	D3DXVECTOR3 setRotation(void) { return rotation; }
	void setPivot(int _pivot) { pivot = _pivot; }
	bool isActive;

};
