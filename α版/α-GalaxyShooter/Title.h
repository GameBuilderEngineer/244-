#pragma once
#include "AbstractScene.h"
#include "Object.h"
#include "TitleTransition.h"
#include "TitleTransPos.h"
#include "Player.h"

namespace titleNS
{
	enum {
		PLAYER1,
		PLAYER2,
		NUM_PLAYER,
	};
	const D3DXVECTOR3 PLAYER_POSITION[NUM_PLAYER] =
	{
		D3DXVECTOR3(0,100,0),
		D3DXVECTOR3(60,100,0)
	};
	const D3DXQUATERNION CAMERA_RELATIVE_QUATERNION[NUM_PLAYER] =
	{
		D3DXQUATERNION(0.0f,20.0f,-40.0f,0.0f),
#ifdef _DEBUG
		D3DXQUATERNION(0.0f,100.0f,-500,0.0f)
#else
		D3DXQUATERNION(0.0f,20.0f,-400,0.0f)
#endif // _DEBUG
	};

}

class Title : public AbstractScene
{
private:
	TitleTransition titleTrans;
	TitleTransPos titleTransPos;
	Player titlePlayer[titleNS::NUM_PLAYER];

public:
	Title();
	~Title();
	virtual void initialize(
		Direct3D9* direct3D9,
		Input* _input,
		Sound* _sound,
		TextureLoader* _textureLoader,
		StaticMeshLoader* _staticMeshLoader,
		ShaderLoader* _shaderLoader,
		TextManager* _textManager) override;
	virtual void update(float frameTime) override;
	virtual void render(Direct3D9* direct3D9) override;
	virtual void collisions() override;
	virtual void AI() override;
	virtual void uninitialize() override;

	void render3D(Direct3D9* direct3D9, Camera currentCamera);
	void renderUI(LPDIRECT3DDEVICE9 device);

	void titleTransition(void);								// ëIëUIëJà⁄èàóù

};