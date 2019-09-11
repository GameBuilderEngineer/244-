//=============================================================================
// チュートリアルヘッダー [Tutorial.h]
// 制作者 飯塚春輝
//=============================================================================
#pragma once
#include "AbstractScene.h"
#include "Tutorial2D.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NEXT_MAX	(4)	// チュートリアルマックス値
//=============================================================================
// 名前空間
//=============================================================================
namespace tutorialNS
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
class Tutorial : public AbstractScene
{
private:
	// チュートリアル2D
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
