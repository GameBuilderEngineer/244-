#include "Select.h"
using namespace selectNS;

Select::Select()
{
	sceneName = "Scene -Select-";
	nextScene = SceneList::GAME;
}

Select::~Select()
{

}

void Select::initialize(Direct3D9* direct3D9, Input* _input, TextureLoader* _textureLoader, StaticMeshLoader* _staticMeshLoader) {
	//Input
	input = _input;
	//textureLoader
	textureLoader = _textureLoader;
	//staticMeshLoader
	staticMeshLoader = _staticMeshLoader;
	//camera
	camera = new Camera[NUM_PLAYER];
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		camera[i].initialize(WINDOW_WIDTH, WINDOW_HEIGHT);
		camera[i].setTarget(selectPlayer[i].getPosition());
		camera[i].setTargetX(&selectPlayer[i].getAxisX()->direction);
		camera[i].setTargetY(&selectPlayer[i].getAxisY()->direction);
		camera[i].setTargetZ(&selectPlayer[i].getAxisZ()->direction);
		camera[i].setRelative(CAMERA_RELATIVE_QUATERNION[0]);
		camera[i].setGaze(D3DXVECTOR3(0, 0, 0));
		camera[i].setRelativeGaze(D3DXVECTOR3(0, 0, 0));
		camera[i].setUpVector(D3DXVECTOR3(0, 1, 0));
	}

	//light
	light = new Light;
	light->initialize(direct3D9);


	for (int i = 0; i < NUM_PLAYER; i++)
	{
		selectPlayer[i].initialize(direct3D9->device, &staticMeshLoader->staticMesh[staticMeshNS::SAMPLE_TOON_MESH], &(D3DXVECTOR3)selectNS::PLAYER_POSITION[i]);
		selectPlayer[i].setPosition(D3DXVECTOR3(-15, 100, 15));
	}
}

void Select::update(float frameTime) {

	for (int i = 0; i < NUM_PLAYER; i++)
	{
		// カメラアップデート
		camera[i].setUpVector(selectPlayer[i].getAxisY()->direction);
		camera[i].update();
	}

	if (input->wasKeyPressed(VK_RETURN))changeScene(nextScene);
}

void Select::render(Direct3D9* direct3D9) {
	//1Pカメラ・ウィンドウ
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera[0].view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera[0].projection);
	direct3D9->changeViewport1PWindow();
	render3D(direct3D9, camera[0]);

	//2Pカメラ・ウィンドウ
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera[1].view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera[1].projection);
	direct3D9->changeViewport2PWindow();
	render3D(direct3D9, camera[1]);
	//UI
	renderUI(direct3D9->device);
}

void Select::render3D(Direct3D9* direct3D9, Camera currentCamera) {
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		selectPlayer[i].toonRender(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);
	}
}

void Select::renderUI(LPDIRECT3DDEVICE9 device) {

}

void Select::collisions() {

}

void Select::AI() {

}

void Select::uninitialize() {

}

