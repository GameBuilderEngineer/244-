//===================================================================================================================================
//�yShockWave.h�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/05/16
// [�X�V��]2019/09/02
//===================================================================================================================================
#pragma once
#include "Base.h"
#include "UtilityFunction.h"

namespace shockWaveNS
{
	const int VERTEX_NUM = 24;
	const int POLYGON_NUM = VERTEX_NUM*2;
	const float EXISTENCE_TIME = 2.0f;
	const float HEIGHT = 3.0f;
	const float WIDTH = 1.0f;
}

class ShockWave :public Base
{
private:
	LPDIRECT3DDEVICE9 device;								//directX9�f�o�C�X
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;					//���_�o�b�t�@
	LPDIRECT3DVERTEXBUFFER9 uvBuffer;						//�t�u�o�b�t�@
	LPDIRECT3DINDEXBUFFER9 indexBuffer;						//�C���f�b�N�X�o�b�t�@
	IDirect3DVertexDeclaration9* declation;					//���_�錾
	LPDIRECT3DTEXTURE9 texture;								//�e�N�X�`��
	LPD3DXEFFECT effect;									//�V�F�[�_�[�G�t�F�N�g

	utility::Polar3D initialPolar;							//�����ɍ��W
	utility::Polar3D topPolar[shockWaveNS::VERTEX_NUM];		//�㕔�ɍ��W
	utility::Polar3D bottomPolar[shockWaveNS::VERTEX_NUM];	//�����ɍ��W

	D3DXVECTOR3 topVertex[shockWaveNS::VERTEX_NUM];			//�㕔���_���W
	D3DXVECTOR3 bottomVertex[shockWaveNS::VERTEX_NUM];		//�������_���W
	D3DXVECTOR2 topUV[shockWaveNS::VERTEX_NUM+1];			//�㕔�t�u���W
	D3DXVECTOR2 bottomUV[shockWaveNS::VERTEX_NUM+1];		//�����t�u���W

	float height[shockWaveNS::VERTEX_NUM];					//��������㕔�ւ̍���
	float existenceTimer;									//���ݎ���
	float deltaTheta;										//�Ƒ�����



public:
	//Method
	ShockWave();
	~ShockWave();

	//processing
	void initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR3 initialPosition, float radius, LPDIRECT3DTEXTURE9 _texture, LPD3DXEFFECT _effect);
	void createUVBuffer();
	void createVertexBuffer();
	void createIndexBuffer();
	void updateVertexCoord();
	void update(float frameTime);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);
	float calculationDistance(D3DXVECTOR3 point);		//(���Z)����_�ƃ��C���Ƃ̋�����߂�
	bool collision(D3DXVECTOR3 position, float radius);	//�Փˌ��m

	//getter
	bool whetherActive();
};
