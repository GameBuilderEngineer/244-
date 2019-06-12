#include "Game.h"
#include "Direct3D9.h"
using namespace gameNS;

Game::Game()
{
	sceneName = "Scene -Game-";
	nextScene = SceneList::NONE_SCENE;
}

Game::~Game()
{

}

void Game::initialize(Direct3D9* direct3D9) {
	//camera
	camera = new Camera[3];
	camera[0].initialize(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
	camera[0].setGaze(D3DXVECTOR3(0, 0, 0));
	camera[0].setPosition(D3DXVECTOR3(0, 0, -1));
	camera[0].setUpVector(D3DXVECTOR3(0, 1, 0));
	camera[1].initialize(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
	camera[1].setGaze(D3DXVECTOR3(0, 0, 0));
	camera[1].setPosition(D3DXVECTOR3(0, 0, -1));
	camera[1].setUpVector(D3DXVECTOR3(0, 1, 0));
	camera[2].initialize(WINDOW_WIDTH, WINDOW_HEIGHT);
	camera[2].setGaze(D3DXVECTOR3(0, 0, 0));
	camera[2].setPosition(D3DXVECTOR3(0, 0, -1));
	camera[2].setUpVector(D3DXVECTOR3(0, 1, 0));

	//light
	light = new Light;
	light->initialize(direct3D9);

	planet.initialize(direct3D9->device, (LPSTR)"planet.x", &D3DXVECTOR3(10, -98, 0));

	colony[0].initialize(direct3D9->device, (LPSTR)"planet.x", &D3DXVECTOR3(150, 0, 300));
	colony[1].initialize(direct3D9->device, (LPSTR)"planet.x", &D3DXVECTOR3(-150, 0, 300));

	for (int i = 0; i < NUM_PLAYER; i++)
	{
		player[i].initialize(direct3D9->device, (LPSTR)"robotB_still_back.x", &D3DXVECTOR3(10, 3, 0));
	}

	for (int i = 0; i < JUNK_MAX; i++)
	{
		junk[i].initialize(direct3D9->device, (LPSTR)"RobotB.x", &D3DXVECTOR3(5+i, 3, 3));
	}

	onChange = false;
}

void Game::update() {


	camera[0].setGaze(player[0].getPosition());
	camera[0].setPosition(player[0].getPosition()+D3DXVECTOR3(0,4,-10));
	camera[0].setUpVector(player[0].getAxisY());

	camera[1].setGaze(player[1].getPosition());
	camera[1].setPosition(player[1].getPosition() + D3DXVECTOR3(0, 4, -10));
	camera[1].setUpVector(player[1].getAxisY());

	// プラネットアップデート
	planet.update();

	// プレイヤーアップデート
	player[0].update();
	
	// コロニーアップデート
	colony[0].update();

	for (int i = 0; i < JUNK_MAX; i++)
	{
		// ガラクタアップデート
		junk[i].update();
	}

	for (int i = 0; i < 3; i++)
	{
		// カメラアップデート
		camera[i].update();
	}


}

void Game::render(Direct3D9* direct3D9) {

	//1Pカメラ・ウィンドウ
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera[0].view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera[0].projection);
	direct3D9->changeViewport1PWindow();
	render3D(direct3D9);
	//2Pカメラ・ウィンドウ
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera[1].view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera[1].projection);
	direct3D9->changeViewport2PWindow();
	render3D(direct3D9);
	//UI
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera[2].view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera[2].projection);
	direct3D9->changeViewportFullWindow();
	renderUI();
}

void Game::render3D(Direct3D9* direct3D9) {

	planet.render(direct3D9->device);

	for (int i = 0; i < NUM_PLAYER; i++)
	{
		player[i].render(direct3D9->device);
	}

	direct3D9->device->SetRenderState(D3DRS_LIGHTING, false);

	for (int i = 0; i < NUM_COLONY; i++)
	{
		colony[i].render(direct3D9->device);
	}

	direct3D9->device->SetRenderState(D3DRS_LIGHTING, true);

	for (int i = 0; i < JUNK_MAX; i++)
	{
		junk[i].render(direct3D9->device);
	}

}

void Game::renderUI() {

}

void Game::collisions() {

}

void Game::AI() {

}

void Game::uninitialize() {
	SAFE_DELETE(light);
	SAFE_DELETE_ARRAY(camera);
}