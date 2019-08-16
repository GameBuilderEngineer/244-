//===================================================================================================================================
//【Window.h】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/05/16
// [更新日]2019/08/16
//===================================================================================================================================
#pragma once
#include "Base.h"
#include "Input.h"

class Window : public Base
{
public:
	//Data
	HWND wnd;
	Input* input;
	RECT rect;

	bool windowActivate;
	bool initialized;
	//Method
	Window();
	HRESULT initialize(HINSTANCE, INT, INT, INT, INT, LPSTR);
	LRESULT msgProc(HWND, UINT, WPARAM, LPARAM);
	void setInput(Input* _input) { input = _input; }
	D3DXVECTOR2 getCenter();
	RECT getRect();
	void update();
};