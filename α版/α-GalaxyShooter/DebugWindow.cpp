//===================================================================================================================================
//【DebugWindow.cpp】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/05/16
// [更新日]2019/08/07
//===================================================================================================================================
#ifdef _DEBUG
#include "DebugWindow.h"

DebugWindow* debugWindow0 = NULL;
DebugWindow* debugWindow1 = NULL;
DebugWindow* debugWindow2 = NULL;
DebugWindow* debugWindow3 = NULL;
LRESULT CALLBACK debugWndProc0(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	return debugWindow0->msgProc(wnd, msg, wparam, lparam);
}
LRESULT CALLBACK debugWndProc1(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	return debugWindow1->msgProc(wnd, msg, wparam, lparam);
}
LRESULT CALLBACK debugWndProc2(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	return debugWindow2->msgProc(wnd, msg, wparam, lparam);
}

DebugWindow::DebugWindow()
{
	input = NULL;
	iCount = 0;
	initialized = false;
	windowActivate = true;
}

HRESULT DebugWindow::initialize(HINSTANCE instance, INT x, INT y, INT width, INT height, LPSTR windowName) {
	//ウィンドウの定義
	WNDCLASSEX wndClass;
	ZeroMemory(&wndClass, sizeof(wndClass));
	wndClass.cbSize = sizeof(wndClass);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	if(debugWindow0 == NULL)
		wndClass.lpfnWndProc = debugWndProc0;
	else if(debugWindow1 == NULL)
		wndClass.lpfnWndProc = debugWndProc1;
	else if(debugWindow2 == NULL)
		wndClass.lpfnWndProc = debugWndProc2;
	wndClass.hInstance = instance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wndClass.lpszClassName = windowName;
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wndClass);

	if(debugWindow0 == NULL)
		debugWindow0 = this;
	else if(debugWindow1 == NULL)
		debugWindow1 = this;
	else if(debugWindow2 == NULL)debugWindow2 = this;
	else if(debugWindow3 == NULL)debugWindow3 = this;
	//ウィンドウの作成
	wnd = CreateWindowEx(WS_EX_WINDOWEDGE
		,windowName, windowName,
		WS_OVERLAPPEDWINDOW
		, x, y, width, height, 0, 0, instance, 0);
	if (!wnd)
		return E_FAIL;
	//ウィンドウの表示
	ShowWindow(wnd, SW_SHOW);
	UpdateWindow(wnd);

	initialized = true;
	return S_OK;
}
LRESULT DebugWindow::msgProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (!initialized)	return DefWindowProc(wnd, msg, wParam, lParam);
	switch (msg)
	{
	case WM_ACTIVATE:
		windowActivate = wParam != WA_INACTIVE;
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:

		break;
	case WM_KEYDOWN:case WM_SYSKEYDOWN: // キーが押された
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		return 0;

	}
	return DefWindowProc(wnd, msg, wParam, lParam);
}

void DebugWindow::update()
{
	//iCount++;
	//HDC hdc;
	//hdc = GetDC(wnd);
	//wsprintf(strCount[0], "%d", iCount);
	//wsprintf(strCount[1], "%d", iCount);
	//TextOut(hdc, 0, 0, strCount[0], lstrlen(strCount[0]));
	//TextOut(hdc, 0, 20, strCount[1], lstrlen(strCount[1]));
	//ReleaseDC(wnd, hdc);
}

#endif // _DEBUG