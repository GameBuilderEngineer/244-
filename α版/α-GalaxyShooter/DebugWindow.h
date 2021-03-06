//===================================================================================================================================
//【DebugWindow.h】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/05/16
// [更新日]2019/08/07
//===================================================================================================================================
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
	TCHAR strCount[30][2048];
	int iCount;

	bool windowActivate;
	bool initialized;
	//Method
	DebugWindow();
	HRESULT initialize(HINSTANCE, INT, INT, INT, INT, LPSTR);
	void update();
	LRESULT msgProc(HWND, UINT, WPARAM, LPARAM);
	void setInput(Input* _input) { input = _input; }
};

#endif // _DEBUG