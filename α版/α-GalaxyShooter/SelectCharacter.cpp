#include "SelectCharacter.h"

using namespace selectCharacterNS;


SelectCharacter::SelectCharacter()
{
	sceneName = "Scene -SelectCharacter-";
	nextScene = SceneList::GAME;
}


SelectCharacter::~SelectCharacter()
{
	//BGM�̒�~
	audio->stopCue(audioCue::SELECT_CHARACTER_BGM);
}

void SelectCharacter::initialize(
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

	for (int i = 0; i < NUM_PLAYER; i++)
	{
		selectCharacter2D[i].initialize(direct3D9->device, i, _textureLoader);
		charaSelectBar[i].initialize(direct3D9->device, i, _textureLoader);
	}

	timerUI.initialize(direct3D9->device, 0, _textureLoader);

	//BGM�̍Đ�
	audio->playCue(audioCue::SELECT_CHARACTER_BGM);

	selectTransition = 0; // �Z���N�g�摜����ւ�
	select2Transition = 0; // �Z���N�g2�摜����ւ�

}

void SelectCharacter::update(float frameTime) {

	camera->update();

	// �L�[����������I��UI�ړ�
	if (input->wasKeyPressed('D'))
	{
		selectTransition++;
	}
	else if (input->wasKeyPressed('A'))
	{
		selectTransition--;
	}

	// �L�[����������I��UI2�ړ�
	if (input->wasKeyPressed(VK_RIGHT))
	{
		select2Transition++;
	}
	else if (input->wasKeyPressed(VK_LEFT))
	{
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

	if (input->wasKeyPressed(VK_RETURN))changeScene(nextScene);

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
		charaSelectBar[i].render(device);
	}

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