//=============================================================================
// 2D���� [Sprite.cpp]
//
// Author : HAL�������ԕ� 2�N���Q�[���w�� GP12A332 32 �����a�P
// �쐬�� : 2019/6/8
//=============================================================================
#include "Sprite.h"
#include "Base.h"
using namespace spriteNS;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Sprite::Sprite(void)
{
	texture = NULL;
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
Sprite::~Sprite(void)
{
}


//=============================================================================
// ����������
//=============================================================================
void Sprite::initialize(LPDIRECT3DDEVICE9 device, LPSTR fileName, int _pivot,
	int _width, int _height, D3DXVECTOR3 _position, D3DXVECTOR3 _rotation, D3DCOLOR color)
{
	if (fileName)
	{
		setTexture(device, fileName);
	}

	setUVCoordinates(D3DXVECTOR2(0.0, 0.0), D3DXVECTOR2(1.0, 0.0), D3DXVECTOR2(0.0, 1.0), D3DXVECTOR2(1.0, 1.0));
	setPivot(_pivot);
	setSize(_width, _height);
	position = _position;
	rotation = _rotation;
	setVertex();
	setColor(color);
	vertexWk[0].rhw = vertexWk[1].rhw = vertexWk[2].rhw = vertexWk[3].rhw = 1.0f;
}

// �e�N�X�`���̐ݒ肾��������
void Sprite::initialize(LPDIRECT3DDEVICE9 device, LPDIRECT3DTEXTURE9 _texture, int _pivot,
	int _width, int _height, D3DXVECTOR3 _position, D3DXVECTOR3 _rotation, D3DCOLOR color)
{
	if (_texture)
	{
		setTexture(_texture);
	}

	setUVCoordinates(D3DXVECTOR2(0.0, 0.0), D3DXVECTOR2(1.0, 0.0), D3DXVECTOR2(0.0, 1.0), D3DXVECTOR2(1.0, 1.0));
	setPivot(_pivot);
	setSize(_width, _height);
	position = _position;
	rotation = _rotation;
	setVertex();
	setColor(color);
	vertexWk[0].rhw = vertexWk[1].rhw = vertexWk[2].rhw = vertexWk[3].rhw = 1.0f;
}


//=============================================================================
// �I������
//=============================================================================
void Sprite::uninitialize(void)
{
	SAFE_RELEASE(texture)
}


//=============================================================================
// �`�揈��
//=============================================================================
void Sprite::render(LPDIRECT3DDEVICE9 device)
{
	// ���_�t�H�[�}�b�g�̐ݒ�
	device->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	device->SetTexture(0, texture);
	// �|���S���̕`��
	device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(VERTEX_2D));
}


//=============================================================================
// �e�N�X�`���̐ݒ�
//=============================================================================
HRESULT Sprite::setTexture(LPDIRECT3DDEVICE9 device, LPSTR fileName)
{
	setVisualDirectory();	// �J�����g�f�B���N�g���̕ύX

	if (FAILED(D3DXCreateTextureFromFile(device, fileName, &texture)))
	{
		MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", fileName, MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

// �|�C���^���Ver
void Sprite::setTexture(LPDIRECT3DTEXTURE9 _texture)
{
	texture = _texture;
}



//=============================================================================
// UV���W�̐ݒ�
//=============================================================================
void Sprite::setUVCoordinates(D3DXVECTOR2 v0, D3DXVECTOR2 v1, D3DXVECTOR2 v2, D3DXVECTOR2 v3)
{
	vertexWk[0].uv = v0;
	vertexWk[1].uv = v1;
	vertexWk[2].uv = v2;
	vertexWk[3].uv = v3;
}


//=============================================================================
// �T�C�Y�ݒ�
//=============================================================================
void Sprite::setSize(int _width, int _height)
{
	width = _width;
	height = _height;

	if (pivot == CENTER)
	{
		centralAngle = atan2f((float)height / 2, (float)width / 2);				// ���S���W���璸�_�ւ̊p�x��������
		D3DXVECTOR2 vec = D3DXVECTOR2((float) width/ 2, (float)height / 2);		// ���S���W���璸�_�ւ̃x�N�g�������߂�
		originalRadius = radius = D3DXVec2Length(&vec);							// ���a�̏�����
	}
	else
	{
	}
}


//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void Sprite::setVertex(void)
{
	switch (pivot)
	{
	case CENTER:
		vertexWk[0].vtx.x = position.x - cosf(centralAngle + rotation.z) * radius;
		vertexWk[0].vtx.y = position.y - sinf(centralAngle + rotation.z) * radius;
		vertexWk[1].vtx.x = position.x + cosf(centralAngle - rotation.z) * radius;
		vertexWk[1].vtx.y = position.y - sinf(centralAngle - rotation.z) * radius;
		vertexWk[2].vtx.x = position.x - cosf(centralAngle - rotation.z) * radius;
		vertexWk[2].vtx.y = position.y + sinf(centralAngle - rotation.z) * radius;
		vertexWk[3].vtx.x = position.x + cosf(centralAngle + rotation.z) * radius;
		vertexWk[3].vtx.y = position.y + sinf(centralAngle + rotation.z) * radius;
		break;

	case TOP_LEFT:
		vertexWk[0].vtx.x = position.x;
		vertexWk[0].vtx.y = position.y;
		vertexWk[1].vtx.x = position.x + cosf(rotation.z) * width;
		vertexWk[1].vtx.y = position.y + sinf(rotation.z) * width;
		vertexWk[2].vtx.x = position.x - sin(rotation.z) * height;
		vertexWk[2].vtx.y = position.y + cos(rotation.z) * height;
		vertexWk[3].vtx.x = position.x + cosf(rotation.z) * width - sin(rotation.z) * height;
		vertexWk[3].vtx.y = position.y + sinf(rotation.z) * width + cos(rotation.z) * height;
		break;
	}
	vertexWk[0].vtx.z = 0.0f;
	vertexWk[1].vtx.z = 0.0f;
	vertexWk[2].vtx.z = 0.0f;
	vertexWk[3].vtx.z = 0.0f;
}


//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void Sprite::setColor(D3DCOLOR v0, D3DCOLOR v1, D3DCOLOR v2, D3DCOLOR v3)
{
	vertexWk[0].diffuse = v0;
	vertexWk[1].diffuse = v1;
	vertexWk[2].diffuse = v2;
	vertexWk[3].diffuse = v3;
}

// �S���_�ꊇ�ݒ�Ver
void Sprite::setColor(D3DCOLOR color)
{
	vertexWk[0].diffuse =
	vertexWk[1].diffuse =
	vertexWk[2].diffuse =
	vertexWk[3].diffuse = color;
}
