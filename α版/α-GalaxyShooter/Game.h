//===================================================================================================================================
//【Game.h】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/05/16
// [更新日]2019/09/03
//===================================================================================================================================
#pragma once
#include <vector>
#include "AbstractScene.h"
#include "Object.h"
#include "Player.h"
#include "Text.h"
#include "Magnet.h"
#include "Colony.h"
#include "Junk.h"
#include "GameMaster.h"
#include "Bullet.h"
#include "Planet.h"
#include "PointSprite.h"
#include "InstancingBillboard.h"
#include "MemoryPile.h"
#include "MemoryLine.h"
#include "Recursion.h"
#include "Wasuremono.h"
#include "WasuremonoManager.h"
#include "HpEffect.h"
#include "TargetDisplayEffect.h"
#include "UIPause.h"
#include "UIPlayTime.h"
#include "UIChingin.h"
#include "Map.h"
#include "AgentAI.h"
#include "ChinginManager.h"
#include "UIScreenSplitLine.h"
#include "UIRevival.h"
#include "UICutMemoryLine.h"
#include "LineEffect.h"
#include "EffectManager.h"
#include "Lambert.h"
#include "UICountDown.h"

#define JUNK_MAX (100) //ガラクタの数

namespace gameNS
{
	enum {
		PLAYER1,
		PLAYER2,
		NUM_PLAYER,
	};

	const int NUM_BULLET = 30;
	const int NUM_MAGNET = 30;
	const int NUM_CUBE = 1000;
	const int NUM_MEMORY_PILE = 5;

	const D3DXVECTOR3 PLANET_POSITION(0.0f,0.0f,0.0f);

	const D3DXVECTOR3 PLAYER_POSITION[NUM_PLAYER] =
	{
		D3DXVECTOR3(0,100,0),
		D3DXVECTOR3(0,-100,0)
	};
	const D3DXQUATERNION CAMERA_RELATIVE_QUATERNION[NUM_PLAYER] =
	{
		D3DXQUATERNION(0.0f,20.0f,-40.0f,0.0f),
#ifdef _DEBUG
		D3DXQUATERNION(0.0f,20.0f,-40.0f,0.0f)
#else
		D3DXQUATERNION(0.0f,20.0f,-40.0f,0.0f)
#endif // _DEBUG
	};
	
	const D3DXVECTOR3 CAMERA_RELATIVE_GAZE = D3DXVECTOR3(0,10,0);
		const BYTE BUTTON_BULLET = virtualControllerNS::R1;
		const BYTE BUTTON_REVIVAL = virtualControllerNS::A;

	const int NUM_COLONY = 4;
	const int NUM_STAR_X100 = 3;
	const int NUM_STAR_X10 = 5;
	const D3DXVECTOR3 COLONY_POSITION[NUM_COLONY] =
	{
		D3DXVECTOR3(200,100,80),
		D3DXVECTOR3(-80,-100,150),
		D3DXVECTOR3(-400,300,-350),
		D3DXVECTOR3(480,-200,-550)
	};
	const D3DXVECTOR3 STAR_X100_POSITION[NUM_STAR_X100] =
	{
		D3DXVECTOR3(70,400,60),
		D3DXVECTOR3(-180,10,-250),
		D3DXVECTOR3(-300,220,150)
	};
	const D3DXVECTOR3 STAR_X10_POSITION[NUM_STAR_X10] =
	{
		D3DXVECTOR3(70,200,60),
		D3DXVECTOR3(-180,10,-250),
		D3DXVECTOR3(-380,60,50),
		D3DXVECTOR3(-10,120,50),
		D3DXVECTOR3(-30,-20,-40)
	};


	const int NUM_1P_MEMORY_PILE = 5;
	const int NUM_2P_MEMORY_PILE = 5;
	const float INTERVAL_TIME_BULLET1 = 0.2f;
	const float INTERVAL_TIME_BULLET2 = 0.2f;

}

class Game : public AbstractScene
{
private:
	Planet field;
	Magnet magnet[gameNS::NUM_MAGNET];
	Text text;
	Text text2;

	UIPlayTime uiPlayTime[gameNS::NUM_PLAYER];
	UIChingin uiChingin[gameNS::NUM_PLAYER];
	UICutMemoryLine uiCutMemoryLine[gameNS::NUM_PLAYER];
	UIRevival uiRevival[gameNS::NUM_PLAYER];
	UIScreenSplitLine uiScreenSplitLine;
	UICountDown uiCountDown[gameNS::NUM_PLAYER];
	LineEffect lineEffect;		//ラインエフェクト

	Colony colony[gameNS::NUM_COLONY];
	Colony star100[gameNS::NUM_STAR_X100];
	Colony star10[gameNS::NUM_STAR_X10];

	Junk junk[JUNK_MAX];
	PointSprite pointSprite;
	InstancingBillboard plane;
	//Object testObject;//仮
	//Object testCube;//仮
#ifdef _DEBUG
	//極座標動作テスト用
	Object polarTest;//仮
	utility::Polar3D polarPosition;
	D3DXVECTOR3 transPosition;
#endif // _DEBUG


	//プレイヤー
	Player *player[gameNS::NUM_PLAYER];
	//プレイヤークラスへ統合
	Map map;// 仮

	std::vector<Wasuremono*> wasuremono;
	WasuremonoManager wasuremonoManager;
	ChinginManager chinginManager;
	HpEffect hpEffect[gameNS::NUM_PLAYER];
	TargetDisplayEffect target;
	UIPause uiPause;

	bool startCountFlag;
	bool endCountFlag;
	bool onUI = true;
	float frameTime = 0.0f;//フレームタイム保存変数


	//シーンのカラー情報とZ値情報を取得するクラス
	Lambert* lambert;

	//シーンのカラー情報を格納するサーフェイス
	LPDIRECT3DTEXTURE9 colorTexture = NULL;
	LPDIRECT3DSURFACE9 colorSurface = NULL;

	//シーンのZ値を格納するサーフェイス
	LPDIRECT3DTEXTURE9 zMapTexture = NULL;
	LPDIRECT3DSURFACE9 zMapSurface = NULL;

public:
	Game();
	~Game();
	virtual void initialize(
		Direct3D9* _direct3D9,
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

	void render3D(Direct3D9* direct3D9, Camera currentCamera);
	void renderUI(LPDIRECT3DDEVICE9 device);

};

