#include "Result.h"

using namespace resultNS;

Result::Result()
{
	sceneName = "Scene -Result-";
	nextScene = SceneList::TITLE;
}

Result::~Result()
{
}

void Result::initialize(
	Direct3D9* direct3D9,
	Input* _input,
	Sound* _sound,
	TextureLoader* _textureLoader,
	StaticMeshLoader* _staticMeshLoader,
	ShaderLoader* _shaderLoader) {
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

	result2D.initialize(direct3D9->device, 0, _textureLoader);
}

void Result::update(float frameTime) {

	camera->update();

	if (input->anyKeyPressed())changeScene(nextScene);

}

void Result::render(Direct3D9* direct3D9) {
	//1Pカメラ・ウィンドウ
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera->view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera->projection);
	direct3D9->changeViewportFullWindow();
	render3D(direct3D9);
	//UI
	renderUI(direct3D9->device);
}

void Result::render3D(Direct3D9* direct3D9) {

}

void Result::renderUI(LPDIRECT3DDEVICE9 device) {

	result2D.render(device);
}

void Result::collisions() {

}

void Result::AI() {

}

void Result::uninitialize() {

	result2D.uninitialize();
}