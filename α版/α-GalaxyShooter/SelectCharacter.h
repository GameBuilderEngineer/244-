#pragma once
#include "AbstractScene.h"
#include "SelectCharacter2D.h"
#include "CharaSelectBarUI.h"
#include "TimerUI.h"

namespace selectCharacterNS
{
	enum {
		PLAYER1,
		PLAYER2,
		NUM_PLAYER,
	};
}

class SelectCharacter :public AbstractScene
{
private:
	SelectCharacter2D selectCharacter2D[selectCharacterNS::NUM_PLAYER];
	CharaSelectBarUI charaSelectBar[selectCharacterNS::NUM_PLAYER];
	TimerUI timerUI;

public:
	SelectCharacter();
	~SelectCharacter();
	virtual void initialize(
		Direct3D9* direct3D9,
		Input* _input,
		Audio* _audio,
		TextureLoader* _textureLoader,
		StaticMeshLoader* _staticMeshLoader,
		ShaderLoader* _shaderLoader) override;
	virtual void update(float frameTime) override;
	virtual void render(Direct3D9* direct3D9) override;
	virtual void collisions() override;
	virtual void AI() override;
	virtual void uninitialize() override;

	void render3D(Direct3D9* direct3D9);
	void renderUI(LPDIRECT3DDEVICE9 device);

	int selectTransition;	// �Z���N�g�摜����ւ�
	int select2Transition;	// �Z���N�g2�摜����ւ�

};