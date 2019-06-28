#include "SelectCharacter.h"

using namespace selectCharacterNS;


SelectCharacter::SelectCharacter()
{

}


SelectCharacter::~SelectCharacter()
{

}

void SelectCharacter::initialize(Direct3D9* direct3D9, Input* _input, TextureLoader* _textureLoader, StaticMeshLoader* _staticMeshLoader) {
	//Input
	input = _input;
	//textureLoader
	textureLoader = _textureLoader;
	//staticMeshLoader
	staticMeshLoader = _staticMeshLoader;

	//camera
	camera = new Camera;
	camera->initialize(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
	camera->setGaze(D3DXVECTOR3(0, 0, 0));
	camera->setPosition(D3DXVECTOR3(0, 0, -1));
	camera->setUpVector(D3DXVECTOR3(0, 1, 0));
}

void SelectCharacter::update(float frameTime) {

	camera->update();
}

void SelectCharacter::render(Direct3D9* direct3D9) {
	//1Pカメラ・ウィンドウ
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera->view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera->projection);
	direct3D9->changeViewportFullWindow();
	render3D(direct3D9);
	//UI
	renderUI();
	if (input->anyKeyPressed())changeScene(nextScene);
}

void SelectCharacter::render3D(Direct3D9* direct3D9) {

}

void SelectCharacter::renderUI() {

}

void SelectCharacter::collisions() {

}

void SelectCharacter::AI() {

}

void SelectCharacter::uninitialize() {

}