//===================================================================================================================================
//ÅyDirect3D9.hÅz
// [çÏê¨é“]HALìåãûGP12A332 11 êõñÏ é˜
// [çÏê¨ì˙]2019/05/16
// [çXêVì˙]2019/08/07
//===================================================================================================================================
#pragma once
#include "Base.h"

class Direct3D9:public Base
{
public:
	//Data
	HWND wnd;
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 device;
	D3DVIEWPORT9 viewPort;
	//Method
	Direct3D9();
	~Direct3D9();

	HRESULT initialize(HWND targetWnd);
	void showFPS();
	void clear();
	HRESULT present();
	HRESULT beginScene();
	HRESULT endScene();
	HRESULT changeViewport(DWORD x, DWORD y, DWORD width, DWORD height);
	HRESULT changeViewportFullWindow();
	HRESULT changeViewport1PWindow();
	HRESULT changeViewport2PWindow();
	//HRESULT initShader();
};