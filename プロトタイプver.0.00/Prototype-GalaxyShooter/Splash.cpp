#include "Splash.h"
using namespace splashNS;

Splash::Splash()
{
	sceneName = "Scene -Splash-";
	nextScene = SceneList::GAME;
}

Splash::~Splash()
{
}

void Splash::initialize(Direct3D9* direct3D9, Input* _input) {
	//Input
	input = _input;
	//camera
	camera = new Camera;
	camera->initialize(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
	camera->setGaze(D3DXVECTOR3(0, 0, 0));
	camera->setPosition(D3DXVECTOR3(0, 0, -1));
	camera->setUpVector(D3DXVECTOR3(0, 1, 0));
}

void Splash::update() {

	camera->update();
}

void Splash::render(Direct3D9* direct3D9) {
	//1Pカメラ・ウィンドウ
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera->view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera->projection);
	direct3D9->changeViewportFullWindow();
	render3D(direct3D9);
	//UI
	renderUI();
	if (input->anyKeyPressed())changeScene(nextScene);
}

void Splash::render3D(Direct3D9* direct3D9) {

}

void Splash::renderUI() {

}

void Splash::collisions() {

}

void Splash::AI() {

}

void Splash::uninitialize() {

}