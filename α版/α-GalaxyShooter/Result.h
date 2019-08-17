//=============================================================================
// リザルトヘッダー [Result.h]
// 制作者 飯塚春輝
//=============================================================================
#pragma once
#include "AbstractScene.h"
#include "Result2D.h"
//=============================================================================
// 名前空間
//=============================================================================
namespace resultNS
{
	// プレイヤー人数
	enum {
		PLAYER1,
		PLAYER2,
		NUM_PLAYER,
	};
}
//*****************************************************************************
// クラス定義
//*****************************************************************************
class Result : public AbstractScene
{
private:
	// リザルト2D
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

