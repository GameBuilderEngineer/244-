#pragma once
#include "AbstractScene.h"
#include "Object.h"

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