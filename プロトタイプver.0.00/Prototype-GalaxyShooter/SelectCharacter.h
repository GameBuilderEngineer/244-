#pragma once
#include "AbstractScene.h"

namespace selectCharacterNS
{

}

class SelectCharacter :public AbstractScene
{
private:
public:
	SelectCharacter();
	~SelectCharacter();
	virtual void initialize(Direct3D9* direct3D9, Input* _input) override;
	virtual void update() override;
	virtual void render(Direct3D9* direct3D9) override;
	virtual void collisions() override;
	virtual void AI() override;
	virtual void uninitialize() override;

	void render3D(Direct3D9* direct3D9);
	void renderUI();
};