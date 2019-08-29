//============================================================================================================================================
// Document
//============================================================================================================================================
// Result.cpp
// HAL���� GP-12A-332 09 �T���v��
// 2019/08/28
//============================================================================================================================================
#include "Result.h"
//============================================================================================================================================
// Using Declaration
// using�錾
//============================================================================================================================================
using namespace resultNS;
//============================================================================================================================================
// Constructor
// �R���X�g���N�^
//============================================================================================================================================
Result::Result(void)
{
	// ���̃V�[��( �L�����N�^�[�Z���N�g )
	sceneName = ("Scene -Result-");

	// ���̃V�[��( �Q�[�� )
	nextScene = SceneList::TITLE;

	return;
}
//============================================================================================================================================
// Destructor
// �f�X�g���N�^
//============================================================================================================================================
Result::~Result(void)
{
	// �T�E���h�̒�~
	sound->stop(soundNS::TYPE::BGM_RESULT);

	return;
}
//============================================================================================================================================
// initialize
// ������
//============================================================================================================================================
void Result::initialize(Direct3D9* _direct3D9, Input* _input, Sound* _sound, TextureLoader* _textureLoader, StaticMeshLoader* _staticMeshLoader, ShaderLoader* _shaderLoader, TextManager* _textManager)
{
	// Input
	input = _input;
	// Sound
	sound = _sound;
	// TextureLoader
	textureLoader = _textureLoader;
	// StaticMeshLoader
	staticMeshLoader = _staticMeshLoader;
	// ShaderLoader
	shaderLoader = _shaderLoader;
	// �e�L�X�g�}�l�[�W��
	textManager = _textManager;

	// �T�E���h�̍Đ�
	sound->play(soundNS::TYPE::BGM_RESULT, soundNS::METHOD::LOOP);

	// Camera
	camera = new Camera;
	camera->initialize(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
	camera->setGaze(D3DXVECTOR3(0, 0, 0));
	camera->setPosition(D3DXVECTOR3(0, 0, -1));
	camera->setUpVector(D3DXVECTOR3(0, 1, 0));

	// ���U���gUI�̏�����
	uiResult.initialize(_direct3D9->device, _textureLoader, _textManager, gameMaster);

	return;
}
//============================================================================================================================================
// uninitialize
// ���
//============================================================================================================================================
void Result::uninitialize(void)
{
	uiResult.release();

	return;
}
//============================================================================================================================================
// update
// �X�V
//============================================================================================================================================
void Result::update(float _frameTime)
{
	// �J�����X�V
	camera->update();

	// Enter�܂��́Z�{�^���Ń^�C�g����
	if (input->wasKeyPressed(VK_RETURN) ||
		input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::A) ||
		input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::A))
	{
		// �T�E���h�̍Đ�
		sound->play(soundNS::TYPE::SE_DECISION, soundNS::METHOD::PLAY);
		// �J��
		changeScene(nextScene);
	}

	return;
}
//============================================================================================================================================
// render
// �`��
//============================================================================================================================================
void Result::render(Direct3D9* _direct3D9)
{
	// �J�����E�E�B���h�E
	_direct3D9->device->SetTransform(D3DTS_VIEW, &camera->view);
	_direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera->projection);
	_direct3D9->changeViewportFullWindow();

	// ���U���gUI
	uiResult.render(_direct3D9->device);

	return;
}
//============================================================================================================================================
// None
//============================================================================================================================================
void Result::collisions(void)
{
	// None
	return;
}
void Result::AI(void)
{
	// None
	return;
}