#include "Window.h"

Window* window = NULL;
LRESULT CALLBACK wndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK wndProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	return window->msgProc(wnd, msg, wparam, lparam);
}
Window::Window()
{
	//input = NULL;
	initialized = false;
	windowActivate = true;
	
}
HRESULT Window::initialize(HINSTANCE instance, INT x, INT y, INT width, INT height, LPSTR windowName) {
	window = this;
	//�E�B���h�E�̒�`
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
	//�E�B���h�E�̍쐬
	wnd = CreateWindow(windowName, windowName, WS_OVERLAPPEDWINDOW, 0, 0, width, height, 0, 0, instance, 0);
	if (!wnd)
		return E_FAIL;
	//�E�B���h�E�̕\��
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
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:case WM_SYSKEYDOWN: // �L�[�������ꂽ
		if(wParam == VK_ESCAPE)
			PostQuitMessage(0);
		input->keyDown(wParam);
		return 0;
	case WM_KEYUP:case WM_SYSKEYUP: // �L�[�������ꂽ
		input->keyUp(wParam);
		return 0;
	case WM_CHAR:					// ���������͂��ꂽ
		input->keyIn(wParam);
		return 0;
	case WM_MOUSEMOVE:				// �}�E�X���ړ����ꂽ
		input->mouseIn(lParam);
		return 0;
	case WM_INPUT:					// �}�E�X����̃��[�f�[�^����
		input->mouseRawIn(lParam);
		return 0;
	case WM_LBUTTONDOWN:			// ���}�E�X�{�^���������ꂽ
		input->setMouseLButton(true);
		SetCapture(wnd);
		input->mouseIn(lParam);
		return 0;
	case WM_LBUTTONUP:				// ���}�E�X�{�^���������ꂽ
		input->setMouseLButton(false);
		ReleaseCapture();
		input->mouseIn(lParam);
		return 0;
	case WM_MBUTTONDOWN:			// �����}�E�X�{�^���������ꂽ
		input->setMouseMButton(true);
		SetCapture(wnd);
		input->mouseIn(lParam);
		return 0;
	case WM_MBUTTONUP:				// �����}�E�X�{�^���������ꂽ
		input->setMouseMButton(false);
		ReleaseCapture();
		input->mouseIn(lParam);
		return 0;
	case WM_RBUTTONDOWN:			// �E�}�E�X�{�^���������ꂽ
		input->setMouseRButton(true);
		SetCapture(wnd);
		input->mouseIn(lParam);
		return 0;
	case WM_RBUTTONUP:				// �E�}�E�X�{�^���������ꂽ
		input->setMouseRButton(false);
		ReleaseCapture();
		input->mouseIn(lParam);
		return 0;
		// �}�E�X��X�{�^���������ꂽ/�����ꂽ
	case WM_XBUTTONDOWN:case WM_XBUTTONUP:
		input->setMouseXButton(wParam);
		input->mouseIn(lParam);
		return 0;
	case WM_DEVICECHANGE:			// �R���g���[�����`�F�b�N
		return 0;
	}
	return DefWindowProc(wnd, msg, wParam, lParam);
}

D3DXVECTOR2 Window::getCenter()
{
	GetWindowRect(wnd, &rect);//���݂̃E�B���h�E�̋�`�����擾
	D3DXVECTOR2 center((rect.right - rect.left)/2, (rect.bottom - rect.top)/2);//�E�B���h�E���ォ��̒����ʒu�ւ̍����v�Z
	center += D3DXVECTOR2(rect.left, rect.top);//0,0�ʒu����E�B���h�E����ʒu�����Z	
	return center;
}
RECT Window::getRect()
{
	GetWindowRect(wnd, &rect);//���݂̃E�B���h�E�̋�`�����擾
	return rect;
}
