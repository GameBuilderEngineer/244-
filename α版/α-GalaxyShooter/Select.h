#pragma once
#include "AbstractScene.h"
#include "Player.h"

namespace selectNS
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
	};

}

class Select : public AbstractScene
{
private:
	Player selectPlayer[selectNS::NUM_PLAYER];

public:
	Select();
	~Select();
	virtual void initialize(Direct3D9* _direct3D9,
		Input* _input,
		Audio* _audio,
		TextureLoader* _textureLoader,
		StaticMeshLoader* _staticMeshLoader,
		ShaderLoader* _shaderLoader) override;
	virtual void update(float frameTime) override;
	virtual void render(Direct3D9* direct3D9) override;
	virtual void collisions() override;
	virtual void AI() override;
	virtual void uninitialize() override;

	void render3D(Direct3D9* direct3D9, Camera currentCamera);
	void renderUI(LPDIRECT3DDEVICE9 device);

};