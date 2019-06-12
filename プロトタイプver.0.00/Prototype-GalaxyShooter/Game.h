#pragma once
#include "AbstractScene.h"
#include "Object.h"
#include "Planet.h"
#include "Player.h"
#include "Colony.h"
#include "Junk.h"

#define JUNK_MAX (10) //ÉKÉâÉNÉ^ÇÃêî
#define DELTA_ANGLE 0.05f

namespace gameNS
{
	enum {
		PLAYER1,
		PLAYER2,
		NUM_PLAYER,
	};

	enum {
		COLONY1,
		COLONY2,
		NUM_COLONY,
	};
}

class Game : public AbstractScene
{
private:
	
	Planet planet;
	Player player[gameNS::NUM_PLAYER];
	Colony colony[gameNS::NUM_COLONY];
	Junk junk[JUNK_MAX];

public:
	Game();
	~Game();
	virtual void initialize(Direct3D9* direct3D9) override;
	virtual void update() override;
	virtual void render(Direct3D9* direct3D9) override;
	virtual void collisions() override;
	virtual void AI() override;
	virtual void uninitialize() override;

	void render3D(Direct3D9* direct3D9);
	void renderUI();
};