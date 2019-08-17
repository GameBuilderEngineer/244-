//===================================================================================================================================
//�yShockWave.cpp�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/08/07
// [�X�V��]2019/08/07
//===================================================================================================================================
#include "ShockWave.h"
using namespace shockWaveNS;
//===================================================================================================================================
//�y�R���X�g���N�^�z
//===================================================================================================================================
ShockWave::ShockWave()
{
	ZeroMemory(this, sizeof(ShockWave));
	existenceTimer = 0.0f;
}

//===================================================================================================================================
//�y�f�X�g���N�^�z
//===================================================================================================================================
ShockWave::~ShockWave()
{

}

//===================================================================================================================================
//�y�������z
//===================================================================================================================================
void ShockWave::initialize(LPDIRECT3DDEVICE9 device,D3DXVECTOR3 initialPosition,float radius, LPDIRECT3DTEXTURE9 _texture, LPD3DXEFFECT _effect)
{
	//�e�N�X�`�����Z�b�g
	texture = _texture;

	//�V�F�[�_�[���Z�b�g
	effect = _effect;

	this->device = device;
	existenceTimer = 0.0f;
	//�����ɍ��W�������������W����Z�o
	initialPolar = UtilityFunction::fromRectangular3D(initialPosition);
	D3DXVECTOR3 p = UtilityFunction::fromTransformationPolar3D(initialPolar.radius, initialPolar.theta, initialPolar.phi);
	initialPolar.radius = radius;
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		float rate = (float)i / (float)VERTEX_NUM;
		height[i] = HEIGHT;
		//���a�̐ݒ�
		topPolar[i].radius = radius + height[i];
		bottomPolar[i].radius = radius;
		//�Ɋp�̐ݒ�
		topPolar[i].theta =
		bottomPolar[i].theta = 0.0f;
		//�Ίp�̐ݒ�
		topPolar[i].phi =
		bottomPolar[i].phi = UtilityFunction::lerp(0,2.0f*D3DX_PI,rate);
	}
	updateVertexCoord();	//�ɍ��W���璸�_���W���Z�o
	createVertexBuffer();	//���_�o�b�t�@���쐬
	createUVBuffer();		//�t�u�o�b�t�@���쐬
	createIndexBuffer();	//�C���f�b�N�X�o�b�t�@���쐬

	//���_�錾
	D3DVERTEXELEMENT9 vertexElement[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },	//���_���W
		{ 1, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },	//UV
		D3DDECL_END()
	};
	device->CreateVertexDeclaration(vertexElement, &declation);
}

//===================================================================================================================================
//�y���_�o�b�t�@�̍쐬�z
//===================================================================================================================================
void ShockWave::createVertexBuffer()
{
	D3DXVECTOR3 vertex[VERTEX_NUM * 2];
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		vertex[i] = bottomVertex[i];
		vertex[i+VERTEX_NUM] = topVertex[i];
	}
	//���_�o�b�t�@�̍쐬
	device->CreateVertexBuffer(sizeof(vertex), 0, 0, D3DPOOL_MANAGED, &vertexBuffer, 0);//�T�C�Y�m��
	copyVertexBuffer(sizeof(vertex), &vertex, vertexBuffer);

}

//===================================================================================================================================
//�yUV�o�b�t�@�̍쐬�z
//===================================================================================================================================
void ShockWave::createUVBuffer()
{
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		float rate = (float)i / (float)VERTEX_NUM;
		topUV[i].x =
		bottomUV[i].x = rate;
		topUV[i].y = 0.0f;
		bottomUV[i].y = 1.0f;
	}
	topUV[VERTEX_NUM].x =
	bottomUV[VERTEX_NUM].x = 1.0f;
	topUV[VERTEX_NUM].y = 0.0f;
	bottomUV[VERTEX_NUM].y = 1.0f;
	D3DXVECTOR2 uv[(VERTEX_NUM+1)*2];
	for (int i = 0; i < VERTEX_NUM+1; i++)
	{
		uv[i] = bottomUV[i];
		uv[i + VERTEX_NUM+1] = topUV[i];
	}
	//UV�o�b�t�@�̍쐬
	device->CreateVertexBuffer(sizeof(uv), 0, 0, D3DPOOL_MANAGED, &uvBuffer, 0);
	copyVertexBuffer(sizeof(uv), &uv, uvBuffer);

}

//===================================================================================================================================
//�y�C���f�b�N�X�o�b�t�@�̍쐬�z
//===================================================================================================================================
void ShockWave::createIndexBuffer()
{
	WORD index[POLYGON_NUM*3];
	WORD topNumber[VERTEX_NUM];
	WORD bottomNumber[VERTEX_NUM];
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		topNumber[i] = i+VERTEX_NUM;
		bottomNumber[i] = i;
	}

	for (int i = 0; i < POLYGON_NUM; i++)
	{
		int j = (int)i / 2;
		int k = UtilityFunction::wrap(j + 1, 0, VERTEX_NUM);
		switch (i % 2)
		{
		case 0:
			index[i * 3 + 0] = bottomNumber[k];
			index[i * 3 + 1] = bottomNumber[j];
			index[i * 3 + 2] = topNumber[j];
			break;
		case 1:
			index[i * 3 + 0] = topNumber[j];
			index[i * 3 + 1] = topNumber[k];
			index[i * 3 + 2] = bottomNumber[k];
			break;
		}
	}
	//�C���f�b�N�X�o�b�t�@�̍쐬
	device->CreateIndexBuffer(sizeof(index), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuffer, 0);
	void* p = 0;
	indexBuffer->Lock(0, 0, &p, 0);
	memcpy(p, index, sizeof(index));
	indexBuffer->Unlock();
}

//===================================================================================================================================
//�y���_���W�̍X�V�z
//===================================================================================================================================
void ShockWave::updateVertexCoord()
{
	D3DXMATRIX xRotation;
	D3DXMATRIX yRotation;
	D3DXMATRIX rotation;
	D3DXMatrixRotationX(&xRotation, initialPolar.theta);
	D3DXMatrixRotationY(&yRotation, -initialPolar.phi+D3DX_PI/2);
	D3DXMatrixMultiply(&rotation, &xRotation, &yRotation);
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		topVertex[i] = UtilityFunction::fromTransformationPolar3D(topPolar[i].radius,topPolar[i].theta,topPolar[i].phi);
		D3DXVec3TransformCoord(&topVertex[i], &topVertex[i], &rotation);
		bottomVertex[i] = UtilityFunction::fromTransformationPolar3D(bottomPolar[i].radius,bottomPolar[i].theta,bottomPolar[i].phi);
		D3DXVec3TransformCoord(&bottomVertex[i], &bottomVertex[i], &rotation);
	}
}
//===================================================================================================================================
//�y�X�V�z
//===================================================================================================================================
void ShockWave::update(float frameTime)
{
	if (!whetherActive())return;
	existenceTimer = min(existenceTimer + frameTime,EXISTENCE_TIME);
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		float rate = existenceTimer / EXISTENCE_TIME;
		topPolar[i].theta = 
		bottomPolar[i].theta = UtilityFunction::lerp(0.0f, D3DX_PI, rate);
	}
	updateVertexCoord();
	createVertexBuffer();
}

//===================================================================================================================================
//�y�`��z
//===================================================================================================================================
void ShockWave::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	// ���u�����h���s��
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
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
	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, VERTEX_NUM, 0, POLYGON_NUM);

	effect->EndPass();
	effect->End();

	//��n��
	// �J�����O��L���ɂ���
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

}

//===================================================================================================================================
//�ygetter�z
//===================================================================================================================================
bool ShockWave::whetherActive(){return existenceTimer < EXISTENCE_TIME;}
