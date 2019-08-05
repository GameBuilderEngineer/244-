//===================================================================================================================================
//yResult.hz
// [ì¬Ò]HAL“Œ‹GP12A332 11 ›–ì ÷
// [ì¬“ú]2019/05/16
// [XV“ú]2019/08/04
//===================================================================================================================================
#pragma once
#include "AbstractScene.h"
#include "Result2D.h"

namespace resultNS
{

}

class Result :
	public AbstractScene
{

private:
	Result2D result2D;

public:
	Result();
	~Result();
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

