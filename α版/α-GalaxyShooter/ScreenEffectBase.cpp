//=============================================================================
// �G�t�F�N�g���� [ScreenEffectBase.cpp]
//
//=============================================================================
#include "ScreenEffectBase.h"
using namespace ScreenEffectNS;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
ScreenEffectBase::ScreenEffectBase()
{
	texture = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
ScreenEffectBase::~ScreenEffectBase()
{
}

// �֐�
void ScreenEffectBase::initialize(LPDIRECT3DDEVICE9 device, LPDIRECT3DTEXTURE9 _texture, int _pivot,
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

	isActive = false;
	settingFrame = 0;
}

//=============================================================================
// �I������
//=============================================================================
void ScreenEffectBase::uninitialize(void)
{
	SAFE_RELEASE(texture)
}

//=============================================================================
// �`�揈��
//=============================================================================
void ScreenEffectBase::render2D(LPDIRECT3DDEVICE9 device)
{
	// ���_�t�H�[�}�b�g�̐ݒ�
	device->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	device->SetTexture(0, texture);
	// �|���S���̕`��
	device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(VERTEX_2D_F));
}

VOID ScreenEffectBase::render3D(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	device->SetTransform(D3DTS_WORLD, &matrixWorld);
	device->SetRenderState(D3DRS_LIGHTING, true);

	D3DMATERIAL9 matDef;
	device->GetMaterial(&matDef);

	// �����_�����O			
	for (DWORD i = 0; i < staticMesh->attributeTableSize; i++)
	{
		device->SetMaterial(&staticMesh->materials[i]);
		device->SetTexture(0, staticMesh->textures[i]);


		staticMesh->mesh->DrawSubset(i);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	device->SetMaterial(&matDef);
	// �e�N�X�`���̐ݒ��NULL�ɂ���
	device->SetTexture(0, NULL);

}

void ScreenEffectBase::activate(int second)
{
	isActive = true;

	settingFrame = second;
}

void ScreenEffectBase::inactivate(void)
{
	isActive = false;
}

//=============================================================================
// �e�N�X�`���̐ݒ�
//=============================================================================
HRESULT ScreenEffectBase::setTexture(LPDIRECT3DDEVICE9 device, LPSTR fileName)
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
void ScreenEffectBase::setTexture(LPDIRECT3DTEXTURE9 _texture)
{
	texture = _texture;
}

//=============================================================================
// UV���W�̐ݒ�
//=============================================================================
void ScreenEffectBase::setUVCoordinates(D3DXVECTOR2 v0, D3DXVECTOR2 v1, D3DXVECTOR2 v2, D3DXVECTOR2 v3)
{
	vertexWk[0].uv = v0;
	vertexWk[1].uv = v1;
	vertexWk[2].uv = v2;
	vertexWk[3].uv = v3;
}


//=============================================================================
// �T�C�Y�ݒ�
//=============================================================================
void ScreenEffectBase::setSize(int _width, int _height)
{
	width = _width;
	height = _height;

	if (pivot == F_CENTER)
	{
		centralAngle = atan2f((float)height / 2, (float)width / 2);				// ���S���W���璸�_�ւ̊p�x��������
		D3DXVECTOR2 vec = D3DXVECTOR2((float)width / 2, (float)height / 2);		// ���S���W���璸�_�ւ̃x�N�g�������߂�
		originalRadius = radius = D3DXVec2Length(&vec);							// ���a�̏�����
	}
	else
	{
	}
}

//=============================================================================
// �ʒu�ݒ�
//=============================================================================
void ScreenEffectBase::setPosition2(D3DXVECTOR3 _position)
{
	position = _position;

}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void ScreenEffectBase::setVertex(void)
{
	switch (pivot)
	{
	case F_CENTER:
		vertexWk[0].vtx.x = position.x - cosf(centralAngle + rotation.z) * radius;
		vertexWk[0].vtx.y = position.y - sinf(centralAngle + rotation.z) * radius;
		vertexWk[1].vtx.x = position.x + cosf(centralAngle - rotation.z) * radius;
		vertexWk[1].vtx.y = position.y - sinf(centralAngle - rotation.z) * radius;
		vertexWk[2].vtx.x = position.x - cosf(centralAngle - rotation.z) * radius;
		vertexWk[2].vtx.y = position.y + sinf(centralAngle - rotation.z) * radius;
		vertexWk[3].vtx.x = position.x + cosf(centralAngle + rotation.z) * radius;
		vertexWk[3].vtx.y = position.y + sinf(centralAngle + rotation.z) * radius;
		break;

	case F_TOP_LEFT:
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
void ScreenEffectBase::setColor(D3DCOLOR v0, D3DCOLOR v1, D3DCOLOR v2, D3DCOLOR v3)
{
	vertexWk[0].diffuse = v0;
	vertexWk[1].diffuse = v1;
	vertexWk[2].diffuse = v2;
	vertexWk[3].diffuse = v3;
}

// �S���_�ꊇ�ݒ�Ver
void ScreenEffectBase::setColor(D3DCOLOR color)
{
	vertexWk[0].diffuse =
		vertexWk[1].diffuse =
		vertexWk[2].diffuse =
		vertexWk[3].diffuse = color;
}

void ScreenEffectBase::setAlpha(D3DCOLOR color)
{
	vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, color);
	vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, color);
	vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, color);
	vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, color);
}
