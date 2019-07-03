#include "Credit.h"
using namespace creditNS;

Credit::Credit()
{
	sceneName = "Scene -Credit-";
	nextScene = SceneList::TITLE;
}

Credit::~Credit()
{
}

void Credit::initialize(Direct3D9* direct3D9, Input* _input) {
	//Input
	input = _input;
	//camera
	camera = new Camera;
	camera->initialize(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
	camera->setGaze(D3DXVECTOR3(0, 0, 0));
	camera->setPosition(D3DXVECTOR3(0, 0, -1));
	camera->setUpVector(D3DXVECTOR3(0, 1, 0));

	credit2D.initialize(direct3D9->device, 0);
}

void Credit::update() {

	camera->update();

	credit2D.update();

	if (input->wasKeyPressed(VK_RETURN))changeScene(nextScene);

}

void Credit::render(Direct3D9* direct3D9) {
	//1P�J�����E�E�B���h�E
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera->view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera->projection);
	direct3D9->changeViewportFullWindow();
	render3D(direct3D9);
	//UI
	renderUI(direct3D9->device);
}

void Credit::render3D(Direct3D9* direct3D9) {

}

void Credit::renderUI(LPDIRECT3DDEVICE9 device) {

	credit2D.render(device);
}

void Credit::collisions() {

}

void Credit::AI() {

}

void Credit::uninitialize() {

	credit2D.uninitialize();
}
