#include "Camera.h"

Camera::Camera()
{
	ZeroMemory(this, sizeof(Camera));
}

Camera::~Camera()
{

}

HRESULT Camera::initialize(DWORD _windowWidth, DWORD _windowHeight)
{
	setAspect(_windowWidth,_windowHeight);
	return S_OK;
}

void Camera::update()
{
	setViewProjection();
}

void Camera::setAspect(DWORD _windowWidth, DWORD _windowHeight)
{
	windowWidth = _windowWidth;
	windowHeight = _windowHeight;
	aspect = (FLOAT)windowWidth / (FLOAT)windowHeight;

}

HRESULT Camera::setViewProjection()
{
	D3DXMatrixLookAtLH(&view, &position, &gazePosition, &upVector);

	// プロジェクション
	D3DXMatrixPerspectiveFovLH(&projection, D3DX_PI / 4, aspect, 0.1f, 1000.0f);

	return S_OK;
}