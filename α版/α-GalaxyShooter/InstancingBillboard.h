//===================================================================================================================================
//�yInstancingBillboard.h�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/08/07
// [�X�V��]2019/08/07
//===================================================================================================================================
#pragma once
#include "Base.h"

struct InstancingBillboardVertex
{
	D3DXVECTOR2 coord;
	D3DXVECTOR2 uv;
};

class InstancingBillboard : public Base
{
protected:
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
	LPDIRECT3DINDEXBUFFER9 indexBuffer;
	LPDIRECT3DVERTEXBUFFER9 positionBuffer;
	IDirect3DVertexDeclaration9* declation;
	LPD3DXEFFECT effect;
	D3DXVECTOR3* position;
	LPDIRECT3DTEXTURE9 texture;
	int renderNum;
	bool onRender;

public:
	InstancingBillboard();
	~InstancingBillboard();

	virtual HRESULT initialize(LPDIRECT3DDEVICE9 device,LPD3DXEFFECT effect,LPDIRECT3DTEXTURE9 texture);
	virtual void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);

	void offRender();

	//����Ƀ����_���z�u�\������
	void createPositionSpherical(LPDIRECT3DDEVICE9 device, int num, float radius);

	//�`�搔���Z�b�g����
	void setNumOfRender(LPDIRECT3DDEVICE9 device, int num, D3DXVECTOR3* positionList);
};