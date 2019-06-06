#pragma once
#include "Base.h"

class Direct3D9:public Celement
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