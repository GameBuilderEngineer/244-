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
	if (input->wasKeyPressed('D'))
	{
		selectTransition++;
	}
	else if (input->wasKeyPressed('A'))
	{
		selectTransition--;
	}

	// キーを押したら選択UI2移動
	if (input->wasKeyPressed(VK_RIGHT))
	{
		select2Transition++;
	}
	else if (input->wasKeyPressed(VK_LEFT))
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

	if (input->wasKeyPressed(VK_RETURN))changeScene(nextScene);

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
		charaSelectBar[i].render(device);
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