#include "Tutorial.h"
using namespace tutorialNS;

Tutorial::Tutorial()
{
	sceneName = "Scene -Tutorial-";
	nextScene = SceneList::RESULT;
}

Tutorial::~Tutorial()
{
	//BGMの停止
	audio->stopCue(audioCue::TUTORIAL_BGM);
}

void Tutorial::initialize(
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

	tutorial2D.initialize(direct3D9->device, 0, _textureLoader);

	//BGMの再生
	audio->playCue(audioCue::TUTORIAL_BGM);
}

void Tutorial::update(float frameTime) {

	camera->update();

	tutorial2D.update();

	if (input->wasKeyPressed(VK_RETURN)||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::A)
		)changeScene(nextScene);

}

void Tutorial::render(Direct3D9* direct3D9) {
	//1Pカメラ・ウィンドウ
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera->view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera->projection);
	direct3D9->changeViewportFullWindow();
	render3D(direct3D9);
	//UI
	renderUI(direct3D9->device);
}

void Tutorial::render3D(Direct3D9* direct3D9) {

}

void Tutorial::renderUI(LPDIRECT3DDEVICE9 device) {

	tutorial2D.render(device);
}

void Tutorial::collisions() {

}

void Tutorial::AI() {

}

void Tutorial::uninitialize() {

	tutorial2D.uninitialize();
}
