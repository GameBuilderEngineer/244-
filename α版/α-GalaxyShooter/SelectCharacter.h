//=============================================================================
// セレクトキャラクターヘッダー [SelectCharacter.h]
// 制作者 飯塚春輝
//=============================================================================
#pragma once
#include "AbstractScene.h"
#include "SelectCharacter2D.h"
#include "CharaSelectBarUI.h"
#include "TimerUI.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SELECT_TRANS_MAX (1)	// セレクト移動限界
#define SELECT_TIME_MAX (99)	// セレクト時間
#define SELECT_FLAME_MAX (60)	// セレクトフレーム
//=============================================================================
// 名前空間
//=============================================================================
namespace selectCharacterNS
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
class SelectCharacter :public AbstractScene
{
private:
	// セレクトキャラクター2D
	SelectCharacter2D selectCharacter2D[selectCharacterNS::NUM_PLAYER];
	// キャラクターセレクトバー
	CharaSelectBarUI charaSelectBar[selectCharacterNS::NUM_PLAYER];
	// タイマーUI
	TimerUI timerUI;
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

	int selectTransition;	// セレクト画像入れ替え
	int select2Transition;	// セレクト2画像入れ替え
	float selectTime;		// セレクト時間
	int selectFlameTime;	// ゲーム内時間
};