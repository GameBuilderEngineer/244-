#pragma once
#ifdef _DEBUG
#include "Base.h"
#include "Input.h"

class DebugWindow : public Base
{
public:
	//Data
	HWND wnd;
	Input* input;
	LPRECT rect;


	bool windowActivate;
	bool initialized;
	//Method
	DebugWindow();
	HRESULT initialize(HINSTANCE, INT, INT, INT, INT, LPSTR);
	LRESULT msgProc(HWND, UINT, WPARAM, LPARAM);
	void setInput(Input* _input) { input = _input; }
};

#endif // _DEBUG