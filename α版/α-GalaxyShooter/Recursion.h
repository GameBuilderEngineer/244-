//===================================================================================================================================
//�yRecursion.h�z
// �쐬�ҁFHAL����GP12A332 11 ���� ��
// �쐬���F2019/07/17
// �X�V���F2019/08/05
//===================================================================================================================================
#pragma once
#include "Base.h"
#include "BoundingSphere.h"

namespace recursionNS
{
	const float EXISTENCE_TIME = 3.0f;
}

class Recursion:public Base
{
private:
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;		//���_�o�b�t�@
	LPDIRECT3DVERTEXBUFFER9 uvBuffer;			//�t�u�o�b�t�@
	LPDIRECT3DINDEXBUFFER9 indexBuffer;			//�C���f�b�N�X�o�b�t�@
	LPDIRECT3DVERTEXDECLARATION9 declation;		//���_�錾
	LPDIRECT3DTEXTURE9 texture;					//�e�N�X�`��
	LPD3DXEFFECT effect;						//�V�F�[�_�[�G�t�F�N�g

	D3DXVECTOR3 weightCenter;					//�d�S
	BoundingSphere boundingSphere;				//�����悻�̏Փˌ��m�p�͈́i��������������Փˌ��m�h�~�j
	D3DMATRIX worldMatrix;						//�d�S�����Ƃɂ������[���h�s��
	D3DXVECTOR3* vertexArray;					//���J�[�W�������\������郁�����[�p�C���ʒu

	bool onRender;								//�`��t���O
	float existenceTimer;						//���ݎ���

public:
	Recursion();
	~Recursion();

	//processing
	HRESULT initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR3* vertexArray,LPDIRECT3DTEXTURE9 _texture, LPD3DXEFFECT _effect);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);
	void update(float frameTime);

	//================================================================
	//�y�d�S�ʒu�̎Z�o�z
	//vertex	�F�������[�p�C���̒��_�ʒu�z��|�C���^
	//vertexNum	�F���_�̐�
	//================================================================
	void calculationCenter(D3DXVECTOR3* vertex, int vertexNum);

	//================================================================
	//�y���J�[�W�����Ƃ̏Փˌ��m�֐��z
	//targetPosition�F���J�[�W�������\������|���S���Ƃ̏Փ˔��肷��ʒu
	//targetCenter	�F�ΏۃI�u�W�F�N�g�̋��R���W�����̒��S�ʒu
	//targetRadius	�F�ΏۃI�u�W�F�N�g�̋��R���W�����̔��a
	//targetMatrix	�F�ΏۃI�u�W�F�N�g�̃��[���h�s��
	//================================================================
	bool collide(D3DXVECTOR3 targetPosition, D3DXVECTOR3 targetCenter, float targetRadius, D3DXMATRIX targetMatrix);


};