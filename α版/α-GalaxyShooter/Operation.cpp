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

void Operation::initialize(
	Direct3D9* direct3D9,
	Input* _input,
	Audio* _audio,
	TextureLoader* _textureLoader,
	StaticMeshLoader* _staticMeshLoader,
	ShaderLoader* _shaderLoader) {
	//Input
	input = _input;
	//audio
	audio = _audio;
	//textureLoader
	textureLoader = _textureLoader;
	//staticMeshLoader
	staticMeshLoader = _staticMeshLoader;
	//shaderLoader
	shaderLoader = _shaderLoader;
	//camera
	camera = new Camera;
	camera->initialize(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
	camera->setGaze(D3DXVECTOR3(0, 0, 0));
	camera->setPosition(D3DXVECTOR3(0, 0, -1));
	camera->setUpVector(D3DXVECTOR3(0, 1, 0));

	keyOpe.initialize(direct3D9->device, 0, _textureLoader);
	padOpe.initialize(direct3D9->device, 0, _textureLoader);

	opeTransition = 0; // オペレーション画像入れ替え


}

void Operation::update(float frameTime) {

	camera->update();

	// キーを押したら選択UI移動
	if (input->wasKeyPressed(VK_RIGHT)||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::RIGHT) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::RIGHT)
		)
	{
		opeTransition++;
	}
	else if (input->wasKeyPressed(VK_LEFT)||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::LEFT) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::LEFT)
		)
	{
		opeTransition--;
	}

	// 選択UI限界
	if (opeTransition > 1)
	{
		opeTransition = 0;
	}
	// 選択UI上限
	else if (opeTransition < 0)
	{
		opeTransition = 1;
	}

	if (input->wasKeyPressed(VK_RETURN)||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::A)
		)changeScene(nextScene);

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

	switch (opeTransition)
	{
		// パッド説明
	case 0:

		padOpe.render(device);
		keyOpe.render(device);

		break;
		// キーボード説明
	case 1:

		keyOpe.render(device);
		padOpe.render(device);

		break;
	}
}

void Operation::collisions() {

}

void Operation::AI() {

}

void Operation::uninitialize() {

	keyOpe.uninitialize();
	padOpe.uninitialize();
}
