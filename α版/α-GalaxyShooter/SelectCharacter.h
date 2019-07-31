#pragma once
#include "AbstractScene.h"
#include "SelectCharacter2D.h"

namespace selectCharacterNS
{

}

class SelectCharacter :public AbstractScene
{
private:
	SelectCharacter2D selectCharacter2D;

public:
	SelectCharacter();
	~SelectCharacter();
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

	void render3D(Direct3D9* direct3D9);
	void renderUI(LPDIRECT3DDEVICE9 device);
};