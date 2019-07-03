#include "Operation.h"
using namespace operationNS;

Operation::Operation()
{
	sceneName = "Scene -Operation-";
	nextScene = SceneList::TITLE;
}

Operation::~Operation()
{
}

void Operation::initialize(Direct3D9* direct3D9, Input* _input) {
	//Input
	input = _input;
	//camera
	camera = new Camera;
	camera->initialize(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
	camera->setGaze(D3DXVECTOR3(0, 0, 0));
	camera->setPosition(D3DXVECTOR3(0, 0, -1));
	camera->setUpVector(D3DXVECTOR3(0, 1, 0));

	keyOpe.initialize(direct3D9->device, 0);
}

void Operation::update() {

	camera->update();

	keyOpe.update();

	if (input->wasKeyPressed(VK_RETURN))changeScene(nextScene);

}

void Operation::render(Direct3D9* direct3D9) {
	//1Pカメラ・ウィンドウ
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera->view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera->projection);
	direct3D9->changeViewportFullWindow();
	render3D(direct3D9);
	//UI
	renderUI(direct3D9->device);
}

void Operation::render3D(Direct3D9* direct3D9) {

}

void Operation::renderUI(LPDIRECT3DDEVICE9 device) {

	keyOpe.render(device);
}

void Operation::collisions() {

}

void Operation::AI() {

}

void Operation::uninitialize() {

	keyOpe.uninitialize();
}
