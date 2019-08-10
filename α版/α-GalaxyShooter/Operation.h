//=============================================================================
// オペレーションヘッダー [Operation.h]
// 制作者 飯塚春輝
//=============================================================================
#pragma once
#include "AbstractScene.h"
#include "KeyOpe.h"
#include "PadOpe.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define OPE_MAX (1)		// オペレーション移動限界
//=============================================================================
// 名前空間
//=============================================================================
namespace operationNS
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
class Operation : public AbstractScene
{
private:
	// キーボード説明
	KeyOpe keyOpe;
	// パッド説明
	PadOpe padOpe;

public:
	Operation();
	~Operation();
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
	int opeTransition;	// オペレーション画像入れ替え
};