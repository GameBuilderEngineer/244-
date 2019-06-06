#pragma once
#include "Base.h"
#include "Window.h"
#include "Direct3D9.h"

class Camera : public Celement
{
private:
public:
	//Data
	Direct3D9* d3d;

	float fieldOfView;//視野角
	float aspect;//画面縦横比
	DWORD windowWidth;
	DWORD windowHeight;
	bool onGaze;//=true 注視ありモード
	D3DXVECTOR3 position;//カメラ位置
	D3DXVECTOR3 gazePosition;//注視
	D3DXVECTOR3 upVector;//上方ベクトル
	D3DXMATRIX view;//ビューマトリックス
	D3DXMATRIX projection;//プロジェクションマトリックス


	//Method
	Camera();
	~Camera();
	HRESULT initialize(DWORD _windowWidth, DWORD _windowHeight);
	void update();

	void setPosition(D3DXVECTOR3 _position) { position = _position; };
	void setGaze(D3DXVECTOR3 _gazePosition) { gazePosition = _gazePosition; };
	void setUpVector(D3DXVECTOR3 _upVector) { upVector = _upVector; };
	void setAspect(DWORD _windowWidth, DWORD _windowHeight);
	HRESULT setViewProjection();
};

