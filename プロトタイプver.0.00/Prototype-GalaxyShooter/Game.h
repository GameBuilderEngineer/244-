#pragma once
#include "AbstractScene.h"
#include "Object.h"
#include "HitPointUI.h"
#include "SkillPointUI.h"
#include "ColonyHitPointUI.h"
#include "MissileUI.h"
#include "WeaponUI.h"



namespace gameNS
{
	enum {
		PLAYER1,
		PLAYER2,
		NUM_PLAYER,
	};
}

class Game : public AbstractScene
{
private:	
	Object player[gameNS::NUM_PLAYER];
	HitPointUI hp[gameNS::NUM_PLAYER];
	SkillPointUI sp[gameNS::NUM_PLAYER];
	ColonyHitPointUI colonyHp[gameNS::NUM_PLAYER];
	MissileUI missileInfomation[gameNS::NUM_PLAYER];
	WeaponUI weaponInfomation[gameNS::NUM_PLAYER];
public:
	Game();
	~Game();
	virtual void initialize(Direct3D9* direct3D9,Input* _input) override;
	virtual void update() override;
	virtual void render(Direct3D9* direct3D9) override;
	virtual void collisions() override;
	virtual void AI() override;
	virtual void uninitialize() override;

	void render3D(Direct3D9* direct3D9, Camera currentCamera);
	void renderUI(LPDIRECT3DDEVICE9 device);
};