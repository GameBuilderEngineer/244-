#include "SelectCharacter.h"

using namespace selectCharacterNS;


SelectCharacter::SelectCharacter()
{
	sceneName = "Scene -SelectCharacter-";
	nextScene = SceneList::GAME;
}


SelectCharacter::~SelectCharacter()
{
}

void SelectCharacter::initialize(
	Direct3D9* direct3D9,
	Input* _input,
	Sound* _sound,
	TextureLoader* _textureLoader,
	StaticMeshLoader* _staticMeshLoader,
	ShaderLoader* _shaderLoader,
	TextManager* _textManager) {
	//Input
	input = _input;
	//sound
	sound = _sound;
	//textureLoader
	textureLoader = _textureLoader;
	//staticMeshLoader
	staticMeshLoader = _staticMeshLoader;
	//shaderLoader
	shaderLoader = _shaderLoader;

	//camera
	camera = new Camera;
	camera->initialize(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
	camera->setGaze(D3DXVECTOR3(0, 0, 0));
	camera->setPosition(D3DXVECTOR3(0, 0, -1));
	camera->setUpVector(D3DXVECTOR3(0, 1, 0));

	for (int i = 0; i < NUM_PLAYER; i++)
	{
		selectCharacter2D[i].initialize(direct3D9->device, i, _textureLoader);
		charaSelectBar[i].initialize(direct3D9->device, i, _textureLoader);
	}

	timerUI.initialize(direct3D9->device, 0, _textureLoader);


	selectTransition = 0; // セレクト画像入れ替え
	select2Transition = 0; // セレクト2画像入れ替え

}

void SelectCharacter::update(float frameTime) {

	camera->update();

	// キーを押したら選択UI移動
	if (input->wasKeyPressed('D') ||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::RIGHT))
	{
		selectTransition++;
	}
	else if (input->wasKeyPressed('A') ||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::LEFT))
	{
		selectTransition--;
	}

	// キーを押したら選択UI2移動
	if (input->wasKeyPressed(VK_RIGHT)||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::RIGHT))
	{
		select2Transition++;
	}
	else if (input->wasKeyPressed(VK_LEFT)||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::LEFT))
	{
		select2Transition--;
	}

	// 選択UI限界
	if (selectTransition > 1)
	{
		selectTransition = 0;
	}
	// 選択UI上限
	else if (selectTransition < 0)
	{
		selectTransition = 1;
	}

	// 選択UI2限界
	if (select2Transition > 1)
	{
		select2Transition = 0;
	}
	// 選択UI2上限
	else if (select2Transition < 0)
	{
		select2Transition = 1;
	}

	int selectModel1P = 0;
	int selectModel2P = 0;
	//モデル選択
	switch (selectTransition)
	{
	case 0:	selectModel1P = gameMasterNS::MODEL_ADAM; break;
	case 1:	selectModel1P = gameMasterNS::MODEL_EVE; break;
	} 
	switch (select2Transition)
	{
	case 0:	selectModel2P = gameMasterNS::MODEL_ADAM; break;
	case 1:	selectModel2P = gameMasterNS::MODEL_EVE; break;
	} 

	if (input->wasKeyPressed(VK_RETURN) ||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::A)
		)
	{
		gameMaster->setPlayerCharacter(playerNS::PLAYER1, gameMasterNS::PLAYER_CHARACTER, selectModel1P);
		gameMaster->setPlayerCharacter(playerNS::PLAYER1, gameMasterNS::PLAYER_CHARACTER, selectModel2P);
		changeScene(nextScene);
	}
}

void SelectCharacter::render(Direct3D9* direct3D9) {
	//1Pカメラ・ウィンドウ
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera->view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera->projection);
	direct3D9->changeViewportFullWindow();
	render3D(direct3D9);
	//UI
	renderUI(direct3D9->device);
}

void SelectCharacter::render3D(Direct3D9* direct3D9) {

}

void SelectCharacter::renderUI(LPDIRECT3DDEVICE9 device) {

	for (int i = 0; i < NUM_PLAYER; i++)
	{
		selectCharacter2D[i].render(device, selectTransition, select2Transition);
		charaSelectBar[i].render(device, selectTransition, select2Transition);
	}

	timerUI.render(device);
}

void SelectCharacter::collisions() {

}

void SelectCharacter::AI() {

}

void SelectCharacter::uninitialize() {

	for (int i = 0; i < NUM_PLAYER; i++)
	{
		selectCharacter2D[i].uninitialize();
		charaSelectBar[i].uninitialize();
	}

	timerUI.uninitialize();
}