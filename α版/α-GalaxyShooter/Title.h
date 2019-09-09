//============================================================================================================================================
// Document
//============================================================================================================================================
// Title.h
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/08/29
//============================================================================================================================================
#pragma once
#include "AbstractScene.h"
#include "UITitle.h"
#include "EffectDew.h"
//============================================================================================================================================
// NameSpace
// 名前空間
//============================================================================================================================================
namespace titleNS
{
	enum PLAYER_TYPE
	{
		PLAYER_1,
		PLAYER_2,
		PLAYER_TYPE_MAX
	};

	// プレイヤー座標
	const D3DXVECTOR3 PLAYER_POSITION[titleNS::PLAYER_TYPE::PLAYER_TYPE_MAX] =
	{
		D3DXVECTOR3(-10.0f, 90.0f, 25.0f),
		D3DXVECTOR3(60,100,0)
	};
	// カメラ角度
	const D3DXQUATERNION CAMERA_RELATIVE_QUATERNION[titleNS::PLAYER_TYPE::PLAYER_TYPE_MAX] =
	{
		D3DXQUATERNION(0.0f,20.0f,-40.0f,0.0f),
		D3DXQUATERNION(0.0f,20.0f,-400,0.0f)
	};
}
//============================================================================================================================================
// Class
// クラス
//============================================================================================================================================
class Title : public AbstractScene
{
private:
	Player player[titleNS::PLAYER_TYPE::PLAYER_TYPE_MAX];	//	プレイヤー
	UITitle uiTitle;										//	タイトルUI
	InstancingBillboard plane;								//	インスタンシングビルボード
	EffectDewManager effectDewManager;						//	露エフェクト
public:
	Title(void);
	~Title(void);
	virtual void initialize(Direct3D9* _direct3D9, Input* _input, Sound* _sound, TextureLoader* _textureLoader, StaticMeshLoader* _staticMeshLoader, ShaderLoader* _shaderLoader, TextManager* _textManager) override;
	virtual void uninitialize(void) override;
	virtual void update(float _frameTime) override;
	void updateInput(void);
	virtual void render(Direct3D9* _direct3D9) override;
	void render3D(Direct3D9* _direct3D9, Camera _currentCamera);
	void render2D(LPDIRECT3DDEVICE9 _device);
	// None
	virtual void collisions(void) override;
	virtual void AI(void) override;
};