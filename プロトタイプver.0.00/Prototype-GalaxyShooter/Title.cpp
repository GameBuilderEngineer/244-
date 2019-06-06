#include "Title.h"
#include "Direct3D9.h"
using namespace titleNS;

Title::Title()
{
	sceneName = "Scene -Title-";
	nextScene = SceneList::GAME;
	onChange = false;
}

Title::~Title()
{
}

void Title::initialize(Direct3D9* direct3D9) {
	//camera
	camera = new Camera;
	camera[0].initialize(WINDOW_WIDTH/2, WINDOW_HEIGHT);
	camera[0].setGaze(D3DXVECTOR3(0, 0, 0));
	camera[0].setPosition(D3DXVECTOR3(0, 0, -1));
	camera[0].setUpVector(D3DXVECTOR3(0, 1, 0));

}

void Title::update() {

	camera[0].update();

}

void Title::render(Direct3D9* direct3D9) {
	//1Pカメラ・ウィンドウ
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera[0].view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera[0].projection);
	direct3D9->changeViewportFullWindow();
	render3D(direct3D9);
	//UI
	renderUI();
	changeScene(nextScene);
}

void Title::render3D(Direct3D9* direct3D9) {
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		player[i].render(direct3D9->device);
	}
}

void Title::renderUI() {

}

void Title::collisions() {

}

void Title::AI(){

}

void Title::uninitialize() {

}