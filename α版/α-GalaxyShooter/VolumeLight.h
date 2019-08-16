//===================================================================================================================================
//ÅyVolumeLight.hÅz
// [çÏê¨é“]HALìåãûGP12A332 11 êõñÏ é˜
// [çÏê¨ì˙]2019/05/16
// [çXêVì˙]2019/08/06
//===================================================================================================================================
#pragma once
#include "Base.h"
class VolumeLight :public Base
{
private:
	LPD3DXEFFECT effect;
	D3DXHANDLE technique, WVP, color, farZ;
	D3DXMATRIX matrixView, matrixProjection;

	LPDIRECT3DDEVICE9 device;
	D3DPRESENT_PARAMETERS* parameters;
public:
	VolumeLight(LPDIRECT3DDEVICE9 _device, D3DPRESENT_PARAMETERS* _parameters);
	~VolumeLight();
	void invalidate();
	void restore();
	HRESULT load();

	void step1Begin();
	void step1BeginPass();
	void step1SetMatrix(D3DXMATRIX* _matrixWorld, float _farZ);
	void step1EndPass();
	void step1End();

	void step2Begin();
	void step2BeginPass();
	void step2SetMatrix(D3DXMATRIX* _matrixWorld, float _farZ);
	void step2EndPass();
	void step2End();

	void step3Render(D3DXVECTOR4* _color);

	void commitChanges();
	BOOL isOK();
	LPD3DXEFFECT getEffect() { return effect; };
};

