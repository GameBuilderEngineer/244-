#pragma once
#include "AbstractScene.h"
#include "KeyOpe.h"
#include "PadOpe.h"

namespace operationNS
{

}

class Operation : public AbstractScene
{
private:

	KeyOpe keyOpe;
	PadOpe padOpe;

public:
	Operation();
	~Operation();
	virtual void initialize(
		Direct3D9* direct3D9,
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

	void render3D(Direct3D9* direct3D9);
	void renderUI(LPDIRECT3DDEVICE9 device);
	int opeTransition; // オペレーション画像入れ替え
};