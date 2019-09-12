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
	// ���̃V�[��( ���U���g )
	sceneName = ("Scene -Result-");

	// ���̃V�[��( �^�C�g�� )
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
	camera = new Camera[PLAYER_TYPE::PLAYER_TYPE_MAX];

	for (int i = 0; i < PLAYER_TYPE::PLAYER_TYPE_MAX; i++)
	{
		camera[i].initialize(WINDOW_WIDTH, WINDOW_HEIGHT);
		//camera[i].setTarget(player[i].getPosition());
		//camera[i].setTargetX(&player[i].getAxisX()->direction);
		//camera[i].setTargetY(&player[i].getAxisY()->direction);
		//camera[i].setTargetZ(&player[i].getAxisZ()->direction);
		camera[i].setRelative(CAMERA_RELATIVE_QUATERNION[0]);
		camera[i].setGaze(D3DXVECTOR3(0, 0, 0));
		camera[i].setRelativeGaze(D3DXVECTOR3(0, 0, 0));
		camera[i].setUpVector(D3DXVECTOR3(0, 1, 0));
		camera[i].setFieldOfView(D3DX_PI / 2.5);
	}

	// Light
	light = new Light;
	light->initialize(_direct3D9);

	// ���U���gUI�̏�����
	uiResult.initialize(_direct3D9->device, _textureLoader, _textManager, gameMaster);

	// �V�[���G�t�F�N�g������
	sceneEffect.initialize(_direct3D9->device, textureLoader, *shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD));

	return;
}
//============================================================================================================================================
// uninitialize
// ���
//============================================================================================================================================
void Result::uninitialize(void)
{
	uiResult.release();

	// �J����
	SAFE_DELETE_ARRAY(camera);

	// ���C�g
	SAFE_DELETE(light);

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

	// �V�[���G�t�F�N�g�̍X�V
	sceneEffect.update(_frameTime);

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		// �V�[���G�t�F�N�g����
		sceneEffect.generateSceneEffect(1, D3DXVECTOR3((float)(rand() % 100 - 50), (float)(rand() % 100 - 50), (float)(rand() % 100 - 50)));
	}

	return;
}
//============================================================================================================================================
// render
// �`��
//============================================================================================================================================
void Result::render(Direct3D9* _direct3D9)
{
	//1P�J�����E�E�B���h�E
	_direct3D9->device->SetTransform(D3DTS_VIEW, &camera[PLAYER_TYPE::PLAYER_1].view);
	_direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera[PLAYER_TYPE::PLAYER_1].projection);
	_direct3D9->changeViewportFullWindow();

	render3D(_direct3D9, camera[PLAYER_TYPE::PLAYER_1]);

	// ���u�����h������
	_direct3D9->device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// ���\�[�X�J���[�̎w��
	_direct3D9->device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	// ���f�X�e�B�l�[�V�����J���[�̎w��
	_direct3D9->device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//UI
	renderUI(_direct3D9->device);

	return;
}
//=============================================================================
// 3D�`�揈��
//=============================================================================
void Result::render3D(Direct3D9* direct3D9, Camera _currentCamera)
{
	// �V�[���G�t�F�N�g�̕`��
	sceneEffect.render(direct3D9->device, _currentCamera.view, _currentCamera.projection, _currentCamera.position);

}
//=============================================================================
// 2D�`�揈��
//=============================================================================
void Result::renderUI(LPDIRECT3DDEVICE9 device)
{
	// ���U���gUI
	uiResult.render(device);
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