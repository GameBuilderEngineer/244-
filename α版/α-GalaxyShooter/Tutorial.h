#pragma once
#include "AbstractScene.h"
#include "Tutorial2D.h"

namespace tutorialNS
{

}

class Tutorial : public AbstractScene
{
private:

	Tutorial2D tutorial2D;

public:
	Tutorial();
	~Tutorial();
	virtual void initialize(
		Direct3D9* direct3D9,
		Input* _input,
		Sound* _sound,
		TextureLoader* _textureLoader,
		StaticMeshLoader* _staticMeshLoader,
		ShaderLoader* _shaderLoader) override;
	virtual void update(float frameTime) override;
	virtual void render(Direct3D9* direct3D9) override;
	virtual void collisions() override;
	virtual void AI() override;
	virtual void uninitialize() override;

	void render3D(Direct3D9* direct3D9);
	void renderUI(LPDIRECT3DDEVICE9 device);
};
