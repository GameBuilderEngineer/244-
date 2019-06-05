#pragma once
#include "Base.h"

class Window : public Celement
{
public:
	//Data
	HWND wnd;

	//Method
	HRESULT initialize(HINSTANCE, INT, INT, INT, INT, LPSTR);
	LRESULT msgProc(HWND, UINT, WPARAM, LPARAM);
};