#include "Credit.h"
using namespace creditNS;

Credit::Credit()
{
	sceneName = "Scene -Credit-";
	nextScene = SceneList::TITLE;
}

Credit::~Credit()
{
	// サウンドの停止
	sound->stop(soundNS::TYPE::BGM_CREDIT);
}

void Credit::initialize(
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

	// サウンドの再生
	sound->play(soundNS::TYPE::BGM_CREDIT, soundNS::METHOD::LOOP);

	//camera
	camera = new Camera;
	camera->initialize(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
	camera->setGaze(D3DXVECTOR3(0, 0, 0));
	camera->setPosition(D3DXVECTOR3(0, 0, -1));
	camera->setUpVector(D3DXVECTOR3(0, 1, 0));

	credit2D.initialize(direct3D9->device, 0, _textureLoader);
}

void Credit::update(float frameTime) {

	camera->update();

	credit2D.update();

	// 前の遷移へ戻る
	if (input->wasKeyPressed(VK_BACK) ||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::B) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::B))
	{
		// サウンドの再生
		sound->play(soundNS::TYPE::SE_CANCEL, soundNS::METHOD::PLAY);
		nextScene = SceneList::TITLE;
		changeScene(nextScene);
		return;
	}

	if (input->wasKeyPressed(VK_RETURN) ||
		input->wasKeyPressed(VK_BACK) ||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::A) ||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::B) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::B)
		)changeScene(nextScene);
}

void Credit::render(Direct3D9* direct3D9) {
	//1Pカメラ・ウィンドウ
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
