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

	float fieldOfView;//����p
	float aspect;//��ʏc����
	DWORD windowWidth;
	DWORD windowHeight;
	bool onGaze;//=true �������胂�[�h
	D3DXVECTOR3 position;//�J�����ʒu
	D3DXVECTOR3 gazePosition;//����
	D3DXVECTOR3 upVector;//����x�N�g��
	D3DXMATRIX view;//�r���[�}�g���b�N�X
	D3DXMATRIX projection;//�v���W�F�N�V�����}�g���b�N�X


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

