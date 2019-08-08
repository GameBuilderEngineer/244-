#include "SelectCharacter.h"

using namespace selectCharacterNS;


SelectCharacter::SelectCharacter()
{
	sceneName = "Scene -SelectCharacter-";
	nextScene = SceneList::GAME;
}


SelectCharacter::~SelectCharacter()
{
	// �T�E���h�̒�~
	sound->stop(soundNS::TYPE::BGM_CHARACTER_SELECT);
}

void SelectCharacter::initialize(
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
	sound->play(soundNS::TYPE::BGM_CHARACTER_SELECT, soundNS::METHOD::LOOP);

	//camera
	camera = new Camera;
	camera->initialize(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
	camera->setGaze(D3DXVECTOR3(0, 0, 0));
	camera->setPosition(D3DXVECTOR3(0, 0, -1));
	camera->setUpVector(D3DXVECTOR3(0, 1, 0));

	// ��ʕ������̏�����
	uiScreenSplitLine.initialize(direct3D9->device, textureLoader);

	for (int i = 0; i < NUM_PLAYER; i++)
	{
		selectCharacter2D[i].initialize(direct3D9->device, i, _textureLoader);
		charaSelectBar[i].initialize(direct3D9->device, i, _textureLoader);
	}

	timerUI.initialize(direct3D9->device, 0, _textureLoader);


	selectTransition = 0; // �Z���N�g�摜����ւ�
	select2Transition = 0; // �Z���N�g2�摜����ւ�

}

void SelectCharacter::update(float frameTime) {

	camera->update();

	// �L�[����������I��UI�ړ�
	if (input->wasKeyPressed('D') ||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::RIGHT))
	{
		// �T�E���h�̍Đ�
		sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		selectTransition++;
	}
	else if (input->wasKeyPressed('A') ||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::LEFT))
	{
		// �T�E���h�̍Đ�
		sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		selectTransition--;
	}

	// �L�[����������I��UI2�ړ�
	if (input->wasKeyPressed(VK_RIGHT) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::RIGHT))
	{
		// �T�E���h�̍Đ�
		sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		select2Transition++;
	}
	else if (input->wasKeyPressed(VK_LEFT) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::LEFT))
	{
		// �T�E���h�̍Đ�
		sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		select2Transition--;
	}

	// �I��UI���E
	if (selectTransition > 1)
	{
		selectTransition = 0;
	}
	// �I��UI���
	else if (selectTransition < 0)
	{
		selectTransition = 1;
	}

	// �I��UI2���E
	if (select2Transition > 1)
	{
		select2Transition = 0;
	}
	// �I��UI2���
	else if (select2Transition < 0)
	{
		select2Transition = 1;
	}

	if (input->wasKeyPressed(VK_RETURN) ||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::A)
		)changeScene(nextScene);
}

void SelectCharacter::render(Direct3D9* direct3D9) {
	//1P�J�����E�E�B���h�E
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera->view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera->projection);
	direct3D9->changeViewportFullWindow();
	render3D(direct3D9);
	//UI
	renderUI(direct3D9->device);
}

void SelectCharacter::render3D(Direct3D9* direct3D9) {

}

void SelectCharacter::renderUI(LPDIRECT3DDEVICE9 device) {

	for (int i = 0; i < NUM_PLAYER; i++)
	{
		selectCharacter2D[i].render(device, selectTransition, select2Transition);
		charaSelectBar[i].render(device, selectTransition, select2Transition);
	}

	// ��ʕ�����
	uiScreenSplitLine.render(device);

	timerUI.render(device);
}

void SelectCharacter::collisions() {

}

void SelectCharacter::AI() {

}

void SelectCharacter::uninitialize() {

	for (int i = 0; i < NUM_PLAYER; i++)
	{
		selectCharacter2D[i].uninitialize();
		charaSelectBar[i].uninitialize();
	}

	timerUI.uninitialize();
}