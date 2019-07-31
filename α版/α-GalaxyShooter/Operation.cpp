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
	Sound* _sound,
	TextureLoader* _textureLoader,
	StaticMeshLoader* _staticMeshLoader,
	ShaderLoader* _shaderLoader) {
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
	//camera
	camera = new Camera;
	camera->initialize(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
	camera->setGaze(D3DXVECTOR3(0, 0, 0));
	camera->setPosition(D3DXVECTOR3(0, 0, -1));
	camera->setUpVector(D3DXVECTOR3(0, 1, 0));

	keyOpe.initialize(direct3D9->device, 0, _textureLoader);
	padOpe.initialize(direct3D9->device, 0, _textureLoader);

	opeTransition = 0; // �I�y���[�V�����摜����ւ�


}

void Operation::update(float frameTime) {

	camera->update();

	// �L�[����������I��UI�ړ�
	if (input->wasKeyPressed(VK_RIGHT))
	{
		opeTransition++;
	}
	else if (input->wasKeyPressed(VK_LEFT))
	{
		opeTransition--;
	}

	// �I��UI���E
	if (opeTransition > 1)
	{
		opeTransition = 0;
	}
	// �I��UI���
	else if (opeTransition < 0)
	{
		opeTransition = 1;
	}

	if (input->wasKeyPressed(VK_RETURN))changeScene(nextScene);

}

void Operation::render(Direct3D9* direct3D9) {
	//1P�J�����E�E�B���h�E
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
		// �p�b�h����
	case 0:

		padOpe.render(device);
		keyOpe.render(device);

		break;
		// �L�[�{�[�h����
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
