#ifdef _DEBUG
#include "DebugWindow.h"

DebugWindow* debugWindow0 = NULL;
DebugWindow* debugWindow1 = NULL;
DebugWindow* debugWindow2 = NULL;
DebugWindow* debugWindow3 = NULL;
LRESULT CALLBACK debugWndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK debugWndProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	return debugWindow0->msgProc(wnd, msg, wparam, lparam);
}

DebugWindow::DebugWindow()
{
	input = NULL;
	initialized = false;
	windowActivate = true;
}

HRESULT DebugWindow::initialize(HINSTANCE instance, INT x, INT y, INT width, INT height, LPSTR windowName) {
	if(debugWindow0 == NULL)debugWindow0 = this;
	else if(debugWindow1 == NULL)
		debugWindow1 = this;
	else if(debugWindow2 == NULL)debugWindow2 = this;
	else if(debugWindow3 == NULL)debugWindow3 = this;
	//ウィンドウの定義
	WNDCLASSEX wndClass;
	ZeroMemory(&wndClass, sizeof(wndClass));
	wndClass.cbSize = sizeof(wndClass);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = debugWndProc;
	wndClass.hInstance = instance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wndClass.lpszClassName = windowName;
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wndClass);
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
	if (input == NULL)	return DefWindowProc(wnd, msg, wParam, lParam);
	HDC hdc;
	switch (msg)
	{
	case WM_ACTIVATE:
		windowActivate = wParam != WA_INACTIVE;
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		hdc = GetDC(wnd);

		ReleaseDC(wnd, hdc);

	case WM_KEYDOWN:case WM_SYSKEYDOWN: // キーが押された
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		return 0;

	}
	return DefWindowProc(wnd, msg, wParam, lParam);
}

#endif // _DEBUG