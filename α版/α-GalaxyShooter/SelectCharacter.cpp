#include "SelectCharacter.h"

using namespace selectCharacterNS;


SelectCharacter::SelectCharacter()
{
	sceneName = "Scene -SelectCharacter-";
	nextScene = SceneList::GAME;
}


SelectCharacter::~SelectCharacter()
{
	//BGMの停止
	audio->stopCue(audioCue::SELECT_CHARACTER_BGM);
}

void SelectCharacter::initialize(
	Direct3D9* direct3D9,
	Input* _input,
	Audio* _audio,
	TextureLoader* _textureLoader,
	StaticMeshLoader* _staticMeshLoader,
	ShaderLoader* _shaderLoader) {
	//Input
	input = _input;
	//audio
	audio = _audio;
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

	selectCharacter2D.initialize(direct3D9->device, 0, _textureLoader);

	//BGMの再生
	audio->playCue(audioCue::SELECT_CHARACTER_BGM);

}

void SelectCharacter::update(float frameTime) {

	camera->update();

	if (input->anyKeyPressed())changeScene(nextScene);

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

	selectCharacter2D.render(device);
}

void SelectCharacter::collisions() {

}

void SelectCharacter::AI() {

}

void SelectCharacter::uninitialize() {

	selectCharacter2D.uninitialize();
}