#include "Plane.h"



Plane::Plane()
{
}


Plane::~Plane()
{
	delete[] position;
}

HRESULT Plane::initialize(LPDIRECT3DDEVICE9 device)
{
	PlaneVertex vertex[4] = {
		{D3DXVECTOR2( -1.0f,  1.0f),D3DXVECTOR2(0.0f,0.0f)},
		{D3DXVECTOR2(  1.0f,  1.0f),D3DXVECTOR2(1.0f,0.0f)},
		{D3DXVECTOR2( -1.0f, -1.0f),D3DXVECTOR2(0.0f,1.0f)},
		{D3DXVECTOR2(  1.0f, -1.0f),D3DXVECTOR2(1.0f,1.0f)},
	};
	//���_�o�b�t�@�̍쐬
	device->CreateVertexBuffer(sizeof(vertex), 0, 0, D3DPOOL_MANAGED, &vertexBuffer, 0);//�T�C�Y�m��
	copyVertexBuffer(sizeof(vertex), &vertex, vertexBuffer);

	WORD index[6] = { 
		0,1,2,
		2,1,3 
	};

	//�C���f�b�N�X�o�b�t�@�̍쐬
	device->CreateIndexBuffer(sizeof(index), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuffer, 0);
	void *p = 0;
	indexBuffer->Lock(0, 0, &p, 0);
	memcpy(p, index, sizeof(index));
	indexBuffer->Unlock();

	//�ʒu���o�b�t�@�̍쐬
	device->CreateVertexBuffer(sizeof(D3DXVECTOR3)*num, 0, 0, D3DPOOL_MANAGED, &positionBuffer, 0);
	copyVertexBuffer(sizeof(D3DXVECTOR3)*num, position, positionBuffer);

	//���_�錾
	D3DVERTEXELEMENT9 vertexElement[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },	//���_���W
		{ 0, sizeof(D3DXVECTOR2), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },//UV
		{ 1, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD, 1 },	//�ʒu
		D3DDECL_END()
	};
	device->CreateVertexDeclaration(vertexElement, &declation);

	//�V�F�[�_�[��ǂݍ���
	setShaderDirectory();
	HRESULT hr;
	LPD3DXBUFFER err = NULL;
	if (FAILED(hr = D3DXCreateEffectFromFile(device, "PlaneShader.fx", NULL, NULL, 0, NULL, &effect, &err)))
	{
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "ERROR", MB_OK);
	}
	
	//�e�N�X�`����ǂݍ���
	setVisualDirectory();
	D3DXCreateTextureFromFileA(device, "ring.png", &texture);

	return S_OK;
}

void Plane::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	//��]��ł������B
	//D3DXMATRIX cancelRotation = view;
	//cancelRotation._41 = cancelRotation._42 = cancelRotation._43 = 0;
	//D3DXMatrixInverse(&cancelRotation, NULL,&cancelRotation);

	// ���u�����h���s��
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// ���\�[�X�J���[�̎w��
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	// ���f�X�e�B�l�[�V�����J���[�̎w��
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�C���X�^���X�錾
	device->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | num);
	device->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	// ���_�錾��ʒm
	device->SetVertexDeclaration(declation);
	
	//�f�o�C�X�f�[�^�X�g���[���Ƀ��b�V���̒��_�o�b�t�@���o�C���h
	device->SetStreamSource(0, vertexBuffer, 0, sizeof(PlaneVertex));
	device->SetStreamSource(1, positionBuffer, 0, sizeof(D3DXVECTOR3));

	//�C���f�b�N�X�o�b�t�@���Z�b�g
	device->SetIndices(indexBuffer);

	effect->SetTechnique("mainTechnique");
	//effect->SetMatrix("cancelRotation", &cancelRotation);
	effect->SetMatrix("matrixProjection", &projection);
	effect->SetMatrix("matrixView", &view);
	effect->SetTexture("planeTexture", texture);
	effect->Begin(0, 0);
	effect->BeginPass(0);
		
	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	effect->EndPass();
	effect->End();

	//��n��
	device->SetStreamSourceFreq(0, 1);
	device->SetStreamSourceFreq(1, 1);

}

void Plane::createPositionSpherical(int _num ,float radius)
{
	num = _num;
	//�ʒu�o�b�t�@�̍쐬
	position = new D3DXVECTOR3[num];
	for (int i = 0; i < num; i++)
	{
		D3DXVECTOR3 pos((float)(rand() % 100 - 50),(float)(rand() % 100 - 50),(float)(rand() % 100 - 50));
		D3DXVec3Normalize(&pos, &pos);
		pos *= radius;
		position[i] = pos;
	}
}