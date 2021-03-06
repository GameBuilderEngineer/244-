#pragma once
#include "Base.h"
#include "Window.h"
#include "Direct3D9.h"

class Camera : public Base
{
private:
public:
	//Data
	Direct3D9* d3d;

	float fieldOfView;					//視野角
	float aspect;						//画面縦横比
	DWORD windowWidth;
	DWORD windowHeight;
	bool onGaze;						//=true 注視ありモード
	D3DXVECTOR3 position;				//カメラ位置
	D3DXVECTOR3 gazePosition;			//注視
	D3DXVECTOR3 upVector;				//上方ベクトル
	D3DXQUATERNION posture;				//姿勢クォータニオン
	D3DXMATRIX world;					//姿勢制御用行列
	D3DXQUATERNION relativeQuaternion;	//ターゲットに対する相対位置ベクトル
	D3DXVECTOR3* target;				//注視ターゲット位置ポインタ
	D3DXVECTOR3* targetX;				//注視ターゲットX方向ポインタ
	D3DXVECTOR3* targetY;				//注視ターゲットY方向ポインタ
	D3DXVECTOR3* targetZ;				//注視ターゲットZ方向ポインタ
	D3DXMATRIX view;					//ビューマトリックス
	D3DXMATRIX projection;				//プロジェクションマトリックス


	//Method
	Camera();
	~Camera();
	HRESULT initialize(DWORD _windowWidth, DWORD _windowHeight);
	void update();

	void rotation(D3DXVECTOR3 axis, float angle);

	D3DXVECTOR3 getDirectionX() { 
		D3DXVECTOR3 result;
		D3DXVec3Normalize(&result, &(gazePosition- position));
		D3DXVec3Cross(&result, &upVector,&result);
		D3DXVec3Normalize(&result, &result);
		return result;}
	D3DXVECTOR3 getDirectionY() {
		return upVector;}
	D3DXVECTOR3 getDirectionZ() {
		D3DXVECTOR3 result;
		D3DXVec3Normalize(&result, &(gazePosition- position));
		return result;}

	void setAspect(DWORD _windowWidth, DWORD _windowHeight);
	void setPosition(D3DXVECTOR3 _position) { position = _position; };
	void setGaze(D3DXVECTOR3 _gazePosition) { gazePosition = _gazePosition; };
	void setUpVector(D3DXVECTOR3 _upVector) { upVector = _upVector; };
	void setRelative(D3DXQUATERNION _relativeQuaternion) {relativeQuaternion = _relativeQuaternion; };
	void setTarget(D3DXVECTOR3* _target) { target = _target; }
	void setTargetX(D3DXVECTOR3* targetAxisX) { targetX = targetAxisX; }
	void setTargetY(D3DXVECTOR3* targetAxisY) { targetY = targetAxisY; }
	void setTargetZ(D3DXVECTOR3* targetAxisZ) { targetZ = targetAxisZ; }
	HRESULT setViewProjection();
};