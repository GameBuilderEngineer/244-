#pragma once
#include "AbstractScene.h"
namespace splashNS
{

}

class Splash :
	public AbstractScene
{
public:
	Splash();
	~Splash();
	virtual void initialize(Direct3D9* direct3D9, Input* _input,TextureLoader* _textureLoader,StaticMeshLoader* _staticMeshLoader) override;
	virtual void update(float frameTime) override;
	virtual void render(Direct3D9* direct3D9) override;
	virtual void collisions() override;
	virtual void AI() override;
	virtual void uninitialize() override;

	void render3D(Direct3D9* direct3D9);
	void renderUI();

};

