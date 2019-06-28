#pragma once
#include "AbstractScene.h"
#include "Object.h"
#include "Player.h"
#include "Text.h"
#include "Magnet.h"
#include "HitPointUI.h"
#include "SkillPointUI.h"
#include "ColonyHitPointUI.h"
#include "MissileUI.h"
#include "WeaponUI.h"
#include "Colony.h"
#include "Junk.h"
#include "GameMaster.h"
#include "Bullet.h"
#include "Planet.h"
#include "PointSprite.h"
#include "Plane.h"


#define JUNK_MAX (100) //ÉKÉâÉNÉ^ÇÃêî

namespace gameNS
{
	enum {
		PLAYER1,
		PLAYER2,
		NUM_PLAYER,
	};

	const int NUM_BULLET = 30;
	const int NUM_MAGNET = 30;
	const D3DXVECTOR3 PLANET_POSITION(0.0f,0.0f,0.0f);

	const D3DXVECTOR3 PLAYER_POSITION[NUM_PLAYER] =
	{
		D3DXVECTOR3(0,100,0),
		D3DXVECTOR3(0,-100,0)
	};
	const D3DXQUATERNION CAMERA_RELATIVE_QUATERNION[NUM_PLAYER] =
	{
		D3DXQUATERNION(0,20.0f,-40,0.0f),
		D3DXQUATERNION(0,100,-500,0.0f)
	};
	
	const D3DXVECTOR3 CAMERA_RELATIVE_GAZE = D3DXVECTOR3(0,10,0);
	
	enum {
		COLONY1,
		COLONY2,
		NUM_COLONY,
	};

}

class Game : public AbstractScene
{
private:	
	Player player[gameNS::NUM_PLAYER];
	Bullet bullet1[gameNS::NUM_BULLET];
	Bullet bullet2[gameNS::NUM_BULLET];
	Planet field;
	Magnet magnet[gameNS::NUM_MAGNET];
	Text text;
	Text text2;
	HitPointUI hp[gameNS::NUM_PLAYER];
	SkillPointUI sp[gameNS::NUM_PLAYER];
	ColonyHitPointUI colonyHp[gameNS::NUM_PLAYER];
	MissileUI missileInfomation[gameNS::NUM_PLAYER];
	WeaponUI weaponInfomation[gameNS::NUM_PLAYER];
	Colony colony[gameNS::NUM_COLONY];
	Junk junk[JUNK_MAX];
	GameMaster gameMaster;
	PointSprite pointSprite;
	Plane plane;
	
	bool onUI = true;

public:
	Game();
	~Game();
	virtual void initialize(Direct3D9* direct3D9,Input* _input, TextureLoader* _textureLoader, StaticMeshLoader* _staticMeshLoader) override;
	virtual void update(float frameTime) override;
	virtual void render(Direct3D9* direct3D9) override;
	virtual void collisions() override;
	virtual void AI() override;
	virtual void uninitialize() override;

	void render3D(Direct3D9* direct3D9, Camera currentCamera);
	void renderUI(LPDIRECT3DDEVICE9 device);
};