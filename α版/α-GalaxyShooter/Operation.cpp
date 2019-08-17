//=============================================================================
// �I�y���[�V�������� [Operation.cpp]
// ����� �ђˏt�P
////===========================================================================
#include "Operation.h"
// �I�y���[�V�������O��ԗL��
using namespace operationNS;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
Operation::Operation()
{
	// ���݂̃V�[��(�I�y���[�V����)
	sceneName = "Scene -Operation-";
	// ���̃V�[��(�^�C�g��)
	nextScene = SceneList::TITLE;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
Operation::~Operation()
{
}
//=============================================================================
// ����������
//=============================================================================
void Operation::initialize(
	Direct3D9* direct3D9,
	Input* _input,
	Sound* _sound,
	TextureLoader* _textureLoader,
	StaticMeshLoader* _staticMeshLoader,
	ShaderLoader* _shaderLoader, 
	TextManager* _textManager)
{
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

	// �L�[�{�[�h����������
	keyOpe.initialize(direct3D9->device, 0, _textureLoader);

	// �p�b�h����������
	padOpe.initialize(direct3D9->device, 0, _textureLoader);

	opeTransition = NULL; // �I�y���[�V�����摜����ւ�
}

void Operation::update(float frameTime)
{
	// �J�����X�V
	camera->update();

	// �L�[����������I��UI�ړ�
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

	// �I��UI����
	if (opeTransition > OPE_MAX)
	{
		opeTransition = 0;
	}
	// �I��UI���
	else if (opeTransition < 0)
	{
		opeTransition = OPE_MAX;
	}

	//Enter�܂��́Z�{�^���Ń��U���g��
	if (input->wasKeyPressed(VK_RETURN)||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::A)
		)changeScene(nextScene);
}
//=============================================================================
// �`�揈��
//=============================================================================
void Operation::render(Direct3D9* direct3D9)
{
	//1P�J�����E�E�B���h�E
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera->view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera->projection);
	direct3D9->changeViewportFullWindow();
	render3D(direct3D9);
	//UI
	renderUI(direct3D9->device);
}
//=============================================================================
// 3D�`�揈��
//=============================================================================
void Operation::render3D(Direct3D9* direct3D9)
{
}
//=============================================================================
// 2D�`�揈��
//=============================================================================
void Operation::renderUI(LPDIRECT3DDEVICE9 device)
{
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
//=============================================================================
// �R���W��������
//=============================================================================
void Operation::collisions()
{
}
//=============================================================================
// AI����
//=============================================================================
void Operation::AI()
{
}
//=============================================================================
// �I������
//=============================================================================
void Operation::uninitialize()
{
	// �L�[�{�[�h�����I��
	keyOpe.uninitialize();

	// �p�b�h�����I��
	padOpe.uninitialize();
}
