#include "Recursion.h"

namespace recursionNS
{

}

Recursion::Recursion()
{
}


Recursion::~Recursion()
{
}

HRESULT Recursion::initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR3* vertexArray, LPDIRECT3DTEXTURE9 _texture, LPD3DXEFFECT _effect)
{
	//�e�N�X�`�����Z�b�g
	texture = _texture;

	//�V�F�[�_�[���Z�b�g
	effect = _effect;

	//���_���W�̍쐬
	Vertex3D vertex[5];
	for (int i = 0; i < 5; i++)
	{
		vertex[i].coord = vertexArray[i];
	}
	//UV���W�̍쐬
	UV uv[5] = {
		D3DXVECTOR2(0.0f,0.5f),
		D3DXVECTOR2(0.375f,0.0f),
		D3DXVECTOR2(1.0f,0.1875f),
		D3DXVECTOR2(1.0f,0.8125f),
		D3DXVECTOR2(0.375f,1.0f)
	};

	//�C���f�b�N�X�̍쐬
	WORD index[3 * 3] = {
		1,2,5,
		2,4,5,
		2,3,4
	};

	//���_�o�b�t�@�̍쐬
	device->CreateVertexBuffer(sizeof(vertex), 0, 0, D3DPOOL_MANAGED, &vertexBuffer, 0);
	copyVertexBuffer(sizeof(vertex), &vertex, vertexBuffer);
	//UV�o�b�t�@�̍쐬
	device->CreateVertexBuffer(sizeof(uv), 0, 0, D3DPOOL_MANAGED, &uvBuffer, 0);
	copyVertexBuffer(sizeof(uv), &uv, uvBuffer);

	//�C���f�b�N�X�o�b�t�@�̍쐬
	device->CreateIndexBuffer(sizeof(index), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuffer, 0);
	void* p = 0;
	indexBuffer->Lock(0, 0, &p, 0);
	memcpy(p, index, sizeof(index));
	indexBuffer->Unlock();

	//���_�錾
	D3DVERTEXELEMENT9 vertexElement[] = {
		{0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},//���_���W
		{1,0,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0},//UV
		D3DDECL_END()
	};
	device->CreateVertexDeclaration(vertexElement, &declation);

	onRender = true;

	return S_OK;
}


void Recursion::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	if (onRender == false)return;
	// ���u�����h���s��
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// ���\�[�X�J���[�̎w��
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	// ���f�X�e�B�l�[�V�����J���[�̎w��
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	// �J�����O�͂��Ȃ�
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	
	//���_�錾��ǉ�
	device->SetVertexDeclaration(declation);

	//�f�o�C�X�f�[�^�X�g���[���Ƀ��b�V���̒��_�o�b�t�@���o�C���h
	device->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex3D));
	device->SetStreamSource(1, uvBuffer, sizeof(Vertex3D), sizeof(UV));
	
	//�C���f�b�N�X�o�b�t�@���Z�b�g
	device->SetIndices(indexBuffer);
	
	//�V�F�[�_�[����
	effect->SetTechnique("main");
	effect->SetMatrix("matrixProjection", &projection);
	effect->SetMatrix("matrixView", &view);
	effect->SetTexture("textureDecal", texture);

	effect->Begin(0, 0);
	effect->BeginPass(0);

	//�`��
	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 5, 0, 3);

	effect->EndPass();
	effect->End();

	//��n��
	// �J�����O��L���ɂ���
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

}


void Recursion::calculationCenter()
{

}