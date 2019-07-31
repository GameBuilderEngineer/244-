#include "Tutorial.h"
using namespace tutorialNS;

Tutorial::Tutorial()
{
	sceneName = "Scene -Tutorial-";
	nextScene = SceneList::RESULT;
}

Tutorial::~Tutorial()
{
}

void Tutorial::initialize(
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

	tutorial2D.initialize(direct3D9->device, 0, _textureLoader);
}

void Tutorial::update(float frameTime) {

	camera->update();

	tutorial2D.update();

	if (input->wasKeyPressed(VK_RETURN))changeScene(nextScene);

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
