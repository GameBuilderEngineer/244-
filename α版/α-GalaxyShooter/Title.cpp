#include "Title.h"
#include "Direct3D9.h"
using namespace titleNS;

Title::Title()
{
	sceneName = "Scene -Title-";
	nextScene = SceneList::GAME;
}

Title::~Title()
{
}

void Title::initialize(Direct3D9* direct3D9,Input* _input) {
	//Input
	input = _input;
	//camera
	camera = new Camera;
	camera->initialize(WINDOW_WIDTH/2, WINDOW_HEIGHT);
	camera->setGaze(D3DXVECTOR3(0, 0, 0));
	camera->setPosition(D3DXVECTOR3(0, 0, -1));
	camera->setUpVector(D3DXVECTOR3(0, 1, 0));
}

void Title::update(float frameTime) {

	camera->update();
}

void Title::render(Direct3D9* direct3D9) {
	//1Pカメラ・ウィンドウ
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera->view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera->projection);
	direct3D9->changeViewportFullWindow();
	render3D(direct3D9);
	//UI
	renderUI();
	if(input->anyKeyPressed())changeScene(nextScene);
}

void Title::render3D(Direct3D9* direct3D9) {

}

void Title::renderUI() {

}

void Title::collisions() {

}

void Title::AI(){

}

void Title::uninitialize() {

}