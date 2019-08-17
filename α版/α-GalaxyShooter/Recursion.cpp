//===================================================================================================================================
//�yRecursion.cpp�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/07/17
// [�X�V��]2019/08/05
//===================================================================================================================================
#include "Recursion.h"
using namespace recursionNS;

//===================================================================================================================================
//�y�R���X�g���N�^�z
//===================================================================================================================================
Recursion::Recursion()
{
	weightCenter = D3DXVECTOR3(0, 0, 0);
	existenceTimer = EXISTENCE_TIME;
}

//===================================================================================================================================
//�y�f�X�g���N�^�z
//===================================================================================================================================
Recursion::~Recursion()
{

}

//===================================================================================================================================
//�y�������z
//===================================================================================================================================
HRESULT Recursion::initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR3* _vertexArray, LPDIRECT3DTEXTURE9 _texture, LPD3DXEFFECT _effect)
{
	//�e�N�X�`�����Z�b�g
	texture = _texture;

	//�V�F�[�_�[���Z�b�g
	effect = _effect;

	//���_���\�����郁�����[�p�C���ʒu�����Z�b�g
	vertexArray = new D3DXVECTOR3[5];
	for (int i = 0; i < 5; i++)
		vertexArray[i] = _vertexArray[i];

	//���_���W�̍쐬
	Vertex3D vertex[5];
	for (int i = 0; i < 5; i++)
	{
		vertex[i].coord = _vertexArray[i];
	}
	//UV���W�̍쐬
	UV uv[5] = {
		D3DXVECTOR2(0.0f,0.5f),
		D3DXVECTOR2(0.375f,0.0f),
		D3DXVECTOR2(1.0f,0.1875f),
		D3DXVECTOR2(1.0f,0.8125f),
		D3DXVECTOR2(0.375f,1.0f),
	};

	//�C���f�b�N�X�̍쐬
	WORD index[3 * 3] = {
		4,0,1,
		1,3,4,
		1,2,3
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

	//�d�S�����߂�
	calculationCenter(vertexArray,5);

	//���R���W�����̔��a���쐬����
	float radius = D3DXVec3Length(&(vertexArray[0]-weightCenter));
	for (int i = 1; i < 5; i++)
	{
		radius = max(radius, D3DXVec3Length(&(vertexArray[i] - weightCenter)));
	}
	//���R���W�����𔼌a�ƒ��S�ʒu�ŏ�����
	boundingSphere.initialize(device, radius);

	onRender = true;

	return S_OK;
}

//===================================================================================================================================
//�y�`��z
//===================================================================================================================================
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

	//�d�S�ʒu���Փ˔���͈͕`��
	worldMatrix = {
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		weightCenter.x,weightCenter.y,weightCenter.z,1.0f
	};
#ifdef _DEBUG
	boundingSphere.render(device, worldMatrix);
#endif // _DEBUG
}

//===================================================================================================================================
//�y�X�V�����z
//===================================================================================================================================
void Recursion::update(float frameTime)
{
	existenceTimer -= frameTime;
}

//===================================================================================================================================
//�y�d�S�ʒu�̎Z�o�z
//[����]
//vertex	�F�������[�p�C���̒��_�ʒu�z��|�C���^
//vertexNum	�F���_�̐�
//===================================================================================================================================
void Recursion::calculationCenter(D3DXVECTOR3* vertex, int vertexNum)
{
	//�O�p�`�̏d�S�����߂�B
	D3DXVECTOR3* eachWeightCenter = new D3DXVECTOR3[vertexNum-2];
	for (int i = 0; i < vertexNum-2;i++)
	{
		eachWeightCenter[i] = (vertex[vertexNum-1] + vertex[i] + vertex[i + 1])/3;
	}
	//���d���ςɗv����d�݁i�ʐρj���O�ςɂ��Z�o�F�O�p�`�Ȃ̂ŁA�{����1/2���邪�ȗ�
	float* eachWeight = new float[vertexNum-2];
	float sumWeight = 0;
	for (int i = 0; i < vertexNum - 2; i++)
	{
		D3DXVECTOR3 v1 = vertex[i] - vertex[vertexNum - 1];
		D3DXVECTOR3 v2 = vertex[i+1] - vertex[vertexNum - 1];
		D3DXVECTOR3 cross;
		D3DXVec3Cross(&cross, &v1, &v2);
		eachWeight[i] = D3DXVec3Length(&cross);
		sumWeight += eachWeight[i];
	}
	//���d���ςɂ��d�S�����߂�B
	weightCenter = D3DXVECTOR3(0, 0, 0);
	for (int i = 0; i < vertexNum - 2; i++)
	{
		weightCenter += eachWeightCenter[i] * eachWeight[i];
	}
	weightCenter /= sumWeight;

	delete[] eachWeight;
	delete[] eachWeightCenter;
}

//===================================================================================================================================
//�y���J�[�W�����Ƃ̏Փˌ��m�֐��z
//[����]
//targetPosition�F���J�[�W�������\������|���S���Ƃ̏Փ˔��肷��ʒu
//targetCenter	�F�ΏۃI�u�W�F�N�g�̋��R���W�����̒��S�ʒu
//targetRadius	�F�ΏۃI�u�W�F�N�g�̋��R���W�����̔��a
//targetMatrix	�F�ΏۃI�u�W�F�N�g�̃��[���h�s��
//===================================================================================================================================
bool Recursion::collide(D3DXVECTOR3 targetPosition,D3DXVECTOR3 targetCenter, float targetRadius, D3DXMATRIX targetMatrix)
{
	//�y����1�z
	//���Ƃ̏Փ˔���F�����悻�̏Փˌ��m
	if (boundingSphere.collide(targetCenter, targetRadius, worldMatrix, targetMatrix) == false)
		return false;

	//�y����2�z
	//���J�[�W�����̃|���S���ƏՓ˂��Ă��邩���m
	//�d�S�����Ƃɍ\�������O�p�|���S���T���Ƃ̏Փˌ��m���s��
	//�^�[�Q�b�g�̈ʒu�����O�p�|���S���Ɠ��ꕽ�ʏ�ɕ␳���������ŁA
	//�O�p�|���S���Ƃ̓��O������s��
	bool collide = false;
	for (int i = 0; i < 5; i++)
	{
		if (collide)continue;//�����ꂩ�ŏՓ˂����m�ł��Ă���ꍇ�͔��肵�Ȃ�
		int j;
		if( i+1 >= 5)j = 0;
		else j = i+1;
		//�y�Ӄx�N�g���z�O�p�|���S�����\������Ӄx�N�g�����쐬
		D3DXVECTOR3 side[3];
		side[0] = vertexArray[i] - weightCenter;
		side[1] = vertexArray[j] - vertexArray[i];
		side[2] = weightCenter - vertexArray[j];

		//�y�@���x�N�g���z�O�p�|���S���̖@���̍쐬
		D3DXVECTOR3 normal = D3DXVECTOR3(0,0,0);
		D3DXVec3Cross(&normal, &side[0],&side[1]);
		D3DXVec3Normalize(&normal, &normal);//���K��

		//�y���ʓ_�z�Ώۂ̈ʒu�����O�p�|���S���������镽�ʏ�֕␳����
		D3DXVECTOR3 correctionVector = normal * D3DXVec3Dot(&normal,&(targetPosition-weightCenter));
		D3DXVECTOR3 pointOnPlane = targetPosition - correctionVector;

		//�y�Ώۃx�N�g���z�O�p�|���S���̂R���_������O������s���_�i�ʒu���j�ւ̃x�N�g�����쐬����
		D3DXVECTOR3 toTarget[3];
		toTarget[0] = pointOnPlane - vertexArray[i];
		toTarget[1] = pointOnPlane - vertexArray[j];
		toTarget[2] = pointOnPlane - weightCenter;

		//�y�O�σx�N�g���z�Ӄx�N�g���ƑΏۃx�N�g���̊O�ς��Z�o����
		D3DXVECTOR3 cross[3];
		for (int k = 0; k < 3; k++)
		{
			D3DXVec3Cross(&cross[k], &side[k], &toTarget[k]);
			D3DXVec3Normalize(&cross[k], &cross[k]);//���ςɂ�������r�̂��ߐ��K��
		}

		//�y���ςɂ�������r�z
		//TRUE�F�O�σx�N�g�������ׂē��������̏ꍇ(���ς��P(�덷�h�~�̂���0.99f�Ƃ̔�r))
		//FALSE�F�O�σx�N�g���̂����ꂩ���ʂ̕����̏ꍇ(���ς��|�P�i�P�ȊO�̏ꍇ�͂��ׂāj)
		if (D3DXVec3Dot(&cross[0],&cross[1]) < 0.99f)
		{
			//�ʕ���
		}
		else if (D3DXVec3Dot(&cross[1], &cross[2]) < 0.99f)
		{
			//�ʕ���
		}
		else
		{
			//�������
			collide = true;
		}
	}

	return collide;

}