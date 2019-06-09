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

void Game::initialize(Direct3D9* direct3D9,Input* _input) {
	//Input
	input = _input;
	//camera
	camera = new Camera[3];
	camera[0].initialize(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
	camera[0].setGaze(D3DXVECTOR3(0, 0, 0));
	camera[0].setPosition(D3DXVECTOR3(0, 100, -150));
	camera[0].setUpVector(D3DXVECTOR3(0, 1, 0));
	camera[1].initialize(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
	camera[1].setGaze(D3DXVECTOR3(0, 0, 0));
	camera[1].setPosition(D3DXVECTOR3(0, 30, -200));
	camera[1].setUpVector(D3DXVECTOR3(0, 1, 0));
	camera[2].initialize(WINDOW_WIDTH, WINDOW_HEIGHT);
	camera[2].setGaze(D3DXVECTOR3(0, 0, 0));
	camera[2].setPosition(D3DXVECTOR3(0, 0, -1));
	camera[2].setUpVector(D3DXVECTOR3(0, 1, 0));

	for (int i = 0; i < NUM_PLAYER; i++)
	{//プレイヤーの初期化
		player[i].initialize(direct3D9->device, (LPSTR)"planet.x", &D3DXVECTOR3(0, -100, 0));
		hp[i].initialize(direct3D9->device, i);
		sp[i].initialize(direct3D9->device, i);
		colonyHp[i].initialize(direct3D9->device, i);
		missileInfomation[i].initialize(direct3D9->device, i);
		weaponInfomation[i].initialize(direct3D9->device, i);
	}

	onChange = false;
}

void Game::update() {

	for (int i = 0; i < 3; i++)
	{
		camera[i].update();
	}

	for (int i = 0; i < NUM_PLAYER; i++)
	{
		hp[i].update();
		sp[i].update();
		colonyHp[i].update();
		missileInfomation[i].update();
		weaponInfomation[i].update();
	}
}

void Game::render(Direct3D9* direct3D9) {
	//1Pカメラ・ウィンドウ
	//direct3D9->device->SetTransform(D3DTS_VIEW, &camera[0].view);
	//direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera[0].projection);
	direct3D9->changeViewport1PWindow();
	render3D(direct3D9,camera[0]);
	//2Pカメラ・ウィンドウ
	//direct3D9->device->SetTransform(D3DTS_VIEW, &camera[1].view);
	//direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera[1].projection);
	direct3D9->changeViewport2PWindow();
	render3D(direct3D9,camera[1]);
	//UI
	//direct3D9->device->SetTransform(D3DTS_VIEW, &camera[2].view);
	//direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera[2].projection);
	direct3D9->changeViewportFullWindow();
	renderUI(direct3D9->device);
}

void Game::render3D(Direct3D9* direct3D9,Camera currentCamera) {
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		player[i].render(direct3D9->device,currentCamera.view,currentCamera.projection,currentCamera.position);
	}
}

void Game::renderUI(LPDIRECT3DDEVICE9 device){
	// このへんは全体のinitializeのほうがいいかもしれない＠なかごみ
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			// αソースカラーの指定
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// αデスティネーションカラーの指定
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		hp[i].render(device);
		sp[i].render(device);
		colonyHp[i].render(device);
		missileInfomation[i].render(device);
		weaponInfomation[i].render(device);
	}
}

void Game::collisions() {

}

void Game::AI() {

}

void Game::uninitialize() {
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		hp[i].uninitialize();
		sp[i].uninitialize();
		colonyHp[i].uninitialize();
		missileInfomation[i].uninitialize();
		weaponInfomation[i].uninitialize();
	}
}