#include "Tutorial.h"
using namespace tutorialNS;

Tutorial::Tutorial()
{
	sceneName = "Scene -Tutorial-";
	nextScene = SceneList::RESULT;
}

Tutorial::~Tutorial()
{
	// �T�E���h�̒�~
	sound->stop(soundNS::TYPE::BGM_TUTORIAL);
}

void Tutorial::initialize(
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

	// �T�E���h�̍Đ�
	sound->play(soundNS::TYPE::BGM_TUTORIAL, soundNS::METHOD::LOOP);

	//camera
	camera = new Camera;
	camera->initialize(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
	camera->setGaze(D3DXVECTOR3(0, 0, 0));
	camera->setPosition(D3DXVECTOR3(0, 0, -1));
	camera->setUpVector(D3DXVECTOR3(0, 1, 0));

	tutorial2D.initialize(direct3D9->device, 0, _textureLoader);
}

void Tutorial::update(float frameTime) {

	camera->update();

	tutorial2D.update();

	// �O�̑J�ڂ֖߂�
	if (input->wasKeyPressed(VK_BACK) ||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::B) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::B))
	{
		// �T�E���h�̍Đ�
		sound->play(soundNS::TYPE::SE_CANCEL, soundNS::METHOD::PLAY);
		nextScene = SceneList::TITLE;
		changeScene(nextScene);
		return;
	}

	if (input->wasKeyPressed(VK_RETURN)||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::A)
		)changeScene(nextScene);

}

void Tutorial::render(Direct3D9* direct3D9) {
	//1P�J�����E�E�B���h�E
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera->view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera->projection);
	direct3D9->changeViewportFullWindow();
	render3D(direct3D9);
	//UI
	renderUI(direct3D9->device);
}

void Tutorial::render3D(Direct3D9* direct3D9) {

}

void Tutorial::renderUI(LPDIRECT3DDEVICE9 device) {

	tutorial2D.render(device);
}

void Tutorial::collisions() {

}

void Tutorial::AI() {

}

void Tutorial::uninitialize() {

	tutorial2D.uninitialize();
}
