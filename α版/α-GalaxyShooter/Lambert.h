//===================================================================================================================================
//�yLambert.h�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/05/16
// [�X�V��]2019/09/03
//===================================================================================================================================
#pragma once
#include "Base.h"
class Lambert :public Base
{
private:
	LPD3DXEFFECT effect;
	D3DXHANDLE technique, WVP, lightDirection, ambient, farZ;
	D3DXMATRIX matrixView, matrixProjection;
	LPDIRECT3DDEVICE9 device;

public:
	//Method
	Lambert(LPDIRECT3DDEVICE9 _device);
	~Lambert();

	//processing
	void invalidate();			//������
	void restore();				//����
	
	HRESULT load(LPD3DXEFFECT effect);				//shader�̓ǂݍ���
	
	//shader���s�֐�
	void begin();
	void beginPass();
	void commitChanges();
	void endPass();
	void end();

	//setter
	void setAmbient(float ambient);
	void setAmbient(D3DXVECTOR4* ambient);
	void setMatrix(D3DXMATRIX* matrixWorld, D3DXVECTOR4* lightDirection, float farZ);
	//getter
	BOOL isOK();
	LPD3DXEFFECT getEffect() {	return effect;}


};