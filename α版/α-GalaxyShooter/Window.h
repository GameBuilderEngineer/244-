#pragma once
#include "Base.h"
#include "Input.h"

class Window : public Base
{
public:
	//Data
	HWND wnd;
	Input* input;

	bool windowActivate;
	bool initialized;
	//Method
	Window();
	HRESULT initialize(HINSTANCE, INT, INT, INT, INT, LPSTR);
	LRESULT msgProc(HWND, UINT, WPARAM, LPARAM);
	void setInput(Input* _input) { input = _input; }
};