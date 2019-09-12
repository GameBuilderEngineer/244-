//============================================================================================================================================
// Document
//============================================================================================================================================
// CharacterSelect.h
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/08/25
//============================================================================================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
#include "UICharacterSelect.h"
#include "UIScreenSplitLine.h"
#include "SceneEffect.h"

//============================================================================================================================================
// NameSpace
// 名前空間
//============================================================================================================================================
namespace characterSelectNS
{
	static const float EFFECT_MAX = 1500;	// エフェクト上限

	const float SELECT_TIME = (60.0f);
	const float POSITION_TIME_X = ((uiCharacterSelectNS::POSITION_X_TIME) - 38.0f);
	const float POSITION_TIME_Y = ((uiCharacterSelectNS::POSITION_Y_TIME) - 125.0f);

	enum PLAYER_TYPE
	{
		PLAYER_1,
		PLAYER_2,
		PLAYER_TYPE_MAX
	};
	const D3DXQUATERNION CAMERA_RELATIVE_QUATERNION[characterSelectNS::PLAYER_TYPE::PLAYER_TYPE_MAX] =
	{
		D3DXQUATERNION(0.0f,20.0f,-40.0f,0.0f),
#ifdef _DEBUG
		D3DXQUATERNION(0.0f,20.0f,-40.0f,0.0f)
#else
		D3DXQUATERNION(0.0f,20.0f,-40.0f,0.0f)
#endif // _DEBUG
	};

}
//============================================================================================================================================
// Class
// クラス
//============================================================================================================================================
class CharacterSelect :public AbstractScene
{
private:
	UICharacterSelect uiCharacterSelect;	//	キャラクターセレクトUI
	UIScreenSplitLine uiScreenSplitLine;	//	画面分割線UI
	float selectTime;						//	選択時間
	TextManager* textManager;				//	テキストマネージャ
	SceneEffect sceneEffect;				//	シーンエフェクト

public:
	CharacterSelect(void);
	~CharacterSelect(void);
	virtual void initialize(Direct3D9* _direct3D9, Input* _input, Sound* _sound, TextureLoader* _textureLoader, StaticMeshLoader* _staticMeshLoader, ShaderLoader* _shaderLoader, TextManager* _textManager) override;
	virtual void uninitialize(void) override;
	virtual void update(float _frameTime) override;
	void updateScene(void);
	void updateSceneBack(void);
	void updateSceneNext(void);
	void updateTime(float _frameTime);
	virtual void render(Direct3D9* _direct3D9) override;
	void render3D(Direct3D9* _direct3D9, Camera _currentCamera);
	void render2D(LPDIRECT3DDEVICE9 _device);
	void renderTime(void);
	// None
	virtual void collisions(void) override;
	virtual void AI(void) override;
};