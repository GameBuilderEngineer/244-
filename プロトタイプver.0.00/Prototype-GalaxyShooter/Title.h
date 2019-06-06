#pragma once
#include "AbstractScene.h"
#include "Object.h"

namespace titleNS
{
	enum {
		PLAYER1,
		PLAYER2,
		NUM_PLAYER,
	};
}

class Title : public AbstractScene
{
private:
	Object player[titleNS::NUM_PLAYER];
public:
	Title();
	~Title();
	virtual void initialize(Direct3D9* direct3D9) override;
	virtual void update() override;
	virtual void render(Direct3D9* direct3D9) override;
	virtual void collisions() override;
	virtual void AI() override;
	virtual void uninitialize() override;

	void render3D(Direct3D9* direct3D9);
	void renderUI();
};