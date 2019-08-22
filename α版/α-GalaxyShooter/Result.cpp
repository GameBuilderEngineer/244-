//=============================================================================
// ���U���g���� [Result.cpp]
// ����� �ђˏt�P
////===========================================================================
#include "Result.h"
// �`���[�g���A�����O��ԗL��
using namespace resultNS;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
Result::Result()
{
	// ���݂̃V�[��(���U���g)
	sceneName = "Scene -Result-";
	// ���̃V�[��(�^�C�g��)
	nextScene = SceneList::TITLE;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
Result::~Result()
{
}
//=============================================================================
// ����������
//=============================================================================
void Result::initialize(
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

	for (int i = 0; i < NUM_PLAYER; i++)
	{
		// ���U���g2D������
		result2D[i].initialize(direct3D9->device, i, _textureLoader);
	}

	resultTransition = NULL;				// ���U���g�摜����ւ�
	result2Transition = NULL;				// ���U���g2�摜����ւ�
}
//=============================================================================
// �X�V����
//=============================================================================
void Result::update(float frameTime)
{
	// �J�����X�V
	camera->update();

	//Enter�܂��́Z�{�^���Ń^�C�g����
	if (input->wasKeyPressed(VK_RETURN) ||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::A)
		)changeScene(nextScene);
}
//=============================================================================
// �`�揈��
//=============================================================================
void Result::render(Direct3D9* direct3D9)
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
void Result::render3D(Direct3D9* direct3D9)
{
}
//=============================================================================
// 2D�`�揈��
//=============================================================================
void Result::renderUI(LPDIRECT3DDEVICE9 device)
{
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		// ���U���g2D�`��
		result2D[i].render(device, resultTransition, result2Transition);
	}
}
//=============================================================================
// �R���W��������
//=============================================================================
void Result::collisions()
{
}
//=============================================================================
// AI����
//=============================================================================
void Result::AI()
{
}
//=============================================================================
// �I������
//=============================================================================
void Result::uninitialize()
{
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		// ���U���g2D�I��
		result2D[i].uninitialize();
	}
}