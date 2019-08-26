//===================================================================================================================================
//【Window.cpp】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/05/16
// [更新日]2019/08/20
//===================================================================================================================================
#include "Window.h"

Window* window = NULL;
LRESULT CALLBACK wndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK wndProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	return window->msgProc(wnd, msg, wparam, lparam);
}
Window::Window()
{
	input = NULL;
	initialized = false;
	windowActivate = true;
	
}
HRESULT Window::initialize(HINSTANCE instance, INT x, INT y, INT width, INT height, LPSTR windowName) {
	window = this;
	//ウィンドウの定義
	WNDCLASSEX wndClass;
	ZeroMemory(&wndClass, sizeof(wndClass));
	wndClass.cbSize = sizeof(wndClass);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = wndProc;
	wndClass.hInstance = instance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wndClass.lpszClassName = windowName;
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wndClass);
	//ウィンドウの作成
	wnd = CreateWindow(windowName, windowName, WS_OVERLAPPEDWINDOW, 0, 0, width, height, 0, 0, instance, 0);
	if (!wnd)
		return E_FAIL;
	//ウィンドウの表示
	ShowWindow(wnd, SW_SHOW);
	UpdateWindow(wnd);
	initialized = true;
	return S_OK;
}
void Window::update()
{
	ShowWindow(wnd, SW_SHOW);
	UpdateWindow(wnd);
}
LRESULT Window::msgProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if(!initialized)	return DefWindowProc(wnd, msg, wParam, lParam);
	if(input == NULL)	return DefWindowProc(wnd, msg, wParam, lParam);
	switch (msg)
	{
	case WM_ACTIVATE:
		windowActivate = wParam != WA_INACTIVE;
		input->clearWheelFraction();
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:case WM_SYSKEYDOWN: // キーが押された
		if(wParam == VK_ESCAPE)
			PostQuitMessage(0);
		input->keyDown(wParam);
		return 0;
	case WM_KEYUP:case WM_SYSKEYUP: // キーが離された
		input->keyUp(wParam);
		return 0;
	case WM_CHAR:					// 文字が入力された
		input->keyIn(wParam);
		return 0;
	case WM_MOUSEMOVE:				// マウスが移動された
		input->mouseIn(lParam);
		return 0;
	case WM_INPUT:					// マウスからのローデータ入力
		input->mouseRawIn(lParam);
		return 0;
	case WM_LBUTTONDOWN:			// 左マウスボタンが押された
		input->setMouseLButton(true);
		SetCapture(wnd);
		input->mouseIn(lParam);
		return 0;
	case WM_LBUTTONUP:				// 左マウスボタンが離された
		input->setMouseLButton(false);
		ReleaseCapture();
		input->mouseIn(lParam);
		return 0;
	case WM_MBUTTONDOWN:			// 中央マウスボタンが押された
		input->setMouseMButton(true);
		SetCapture(wnd);
		input->mouseIn(lParam);
		return 0;
	case WM_MBUTTONUP:				// 中央マウスボタンが離された
		input->setMouseMButton(false);
		ReleaseCapture();
		input->mouseIn(lParam);
		return 0;
	case WM_RBUTTONDOWN:			// 右マウスボタンが押された
		input->setMouseRButton(true);
		SetCapture(wnd);
		input->mouseIn(lParam);
		return 0;
	case WM_RBUTTONUP:				// 右マウスボタンが離された
		input->setMouseRButton(false);
		ReleaseCapture();
		input->mouseIn(lParam);
		return 0;
	case WM_XBUTTONDOWN:case WM_XBUTTONUP:// マウスのXボタンが押された/離された
		input->setMouseXButton(wParam);
		input->mouseIn(lParam);
		return 0;
	case WM_MOUSEWHEEL://マウスのホイールが回転した
		input->mouseWheelIn(wParam);
		return 0;
	case WM_DEVICECHANGE:			// コントローラをチェック
		input->resetController();
		return 0;
	}
	return DefWindowProc(wnd, msg, wParam, lParam);
}

D3DXVECTOR2 Window::getCenter()
{
	GetWindowRect(wnd, &rect);//現在のウィンドウの矩形情報を取得
	D3DXVECTOR2 center((float)(rect.right - rect.left)/2, (float)(rect.bottom - rect.top)/2);//ウィンドウ左上からの中央位置への差を計算
	center += D3DXVECTOR2(rect.left, rect.top);//0,0位置からウィンドウ左上位置を加算	
	return center;
}
RECT Window::getRect()
{
	GetWindowRect(wnd, &rect);//現在のウィンドウの矩形情報を取得
	return rect;
}

