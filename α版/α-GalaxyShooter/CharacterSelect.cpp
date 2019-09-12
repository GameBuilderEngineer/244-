//============================================================================================================================================
// Document
//============================================================================================================================================
// CharacterSelect.cpp
// HAL���� GP-12A-332 09 �T���v��
// 2019/08/25
//============================================================================================================================================
#include "CharacterSelect.h"
//============================================================================================================================================
// Using Declaration
// using�錾
//============================================================================================================================================
using namespace characterSelectNS;
//============================================================================================================================================
// Constructor
// �R���X�g���N�^
//============================================================================================================================================
CharacterSelect::CharacterSelect(void)
{
	// ���̃V�[��( �L�����N�^�[�Z���N�g )
	sceneName = ("Scene -CharacterSelect-");

	// ���̃V�[��( �Q�[�� )
	nextScene = SceneList::GAME;

	// ������
	selectTime = SELECT_TIME;

	return;
}
//============================================================================================================================================
// Destructor
// �f�X�g���N�^
//============================================================================================================================================
CharacterSelect::~CharacterSelect(void)
{
	// �T�E���h�̒�~
	sound->stop(soundNS::TYPE::BGM_CHARACTER_SELECT);

	uninitialize();

	return;
}
//============================================================================================================================================
// initialize
// ������
//============================================================================================================================================
void CharacterSelect::initialize(Direct3D9* _direct3D9, Input* _input, Sound* _sound, TextureLoader* _textureLoader, StaticMeshLoader* _staticMeshLoader, ShaderLoader* _shaderLoader, TextManager* _textManager)
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
	sound->play(soundNS::TYPE::BGM_CHARACTER_SELECT, soundNS::METHOD::LOOP);

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

	// ��ʕ������̏�����
	uiScreenSplitLine.initialize(_direct3D9->device, textureLoader);

	// �L�����N�^�[�Z���N�gUI�̏�����
	uiCharacterSelect.initialize(_direct3D9->device, _textureLoader);

	// �V�[���G�t�F�N�g������
	sceneEffect.initialize(_direct3D9->device, textureLoader, *shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD));

	return;
}
//============================================================================================================================================
// uninitialize
// ���
//============================================================================================================================================
void CharacterSelect::uninitialize(void)
{
	uiCharacterSelect.release();

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
void CharacterSelect::update(float _frameTime)
{
	// �J�����X�V
	camera->update();

	// ���ԍX�V
	updateTime(_frameTime);

	// �J�ڍX�V
	updateScene();

	// �L�����N�^�[�Z���N�gUI�X�V
	uiCharacterSelect.update(input, sound);

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
// updateScene
// �X�V - �V�[��
//============================================================================================================================================
void CharacterSelect::updateScene(void)
{
	// �O�̑J�ڂ֖߂�
	updateSceneBack();

	// ���̑J�ڂ֐i��
	updateSceneNext();

	return;
}
//============================================================================================================================================
// updateSceneBack
// �X�V - �V�[��( �߂� )
//============================================================================================================================================
void CharacterSelect::updateSceneBack(void)
{
	if (((uiCharacterSelect.getProgressState(inputNS::DINPUT_1P) == uiCharacterSelectNS::PROGRESS_TYPE::CHARACTER_SELECT) &&
		input->wasKeyPressed(VK_BACK)) ||
		input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::B))
	{
		// �T�E���h�̍Đ�
		sound->play(soundNS::TYPE::SE_CANCEL, soundNS::METHOD::PLAY);
		// ���̑J�ڐ��ݒ�
		nextScene = (SceneList::TITLE);
		// �J��
		changeScene(nextScene);

		return;
	}
	else if (((uiCharacterSelect.getProgressState(inputNS::DINPUT_2P) == uiCharacterSelectNS::PROGRESS_TYPE::CHARACTER_SELECT) &&
		input->wasKeyPressed(VK_DELETE)) ||
		input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::B))
	{
		// �T�E���h�̍Đ�
		sound->play(soundNS::TYPE::SE_CANCEL, soundNS::METHOD::PLAY);
		// ���̑J�ڐ��ݒ�
		nextScene = (SceneList::TITLE);
		// �J��
		changeScene(nextScene);

		return;
	}

	return;
}
//============================================================================================================================================
// updateSceneNext
// �X�V - �V�[��( �i�� )
//============================================================================================================================================
void CharacterSelect::updateSceneNext(void)
{
	if ((uiCharacterSelect.getProgressState(inputNS::DINPUT_1P) == uiCharacterSelectNS::PROGRESS_TYPE::WAITING) &&
		(uiCharacterSelect.getProgressState(inputNS::DINPUT_2P) == uiCharacterSelectNS::PROGRESS_TYPE::WAITING))
	{
		// �T�E���h�̍Đ�
		sound->play(soundNS::TYPE::SE_READY, soundNS::METHOD::PLAY);
		// �L�����N�^�[�̐ݒ�
		gameMaster->setPlayerCharacter(playerNS::PLAYER1, gameMasterNS::PLAYER_CHARACTER, uiCharacterSelect.getSelectState(uiCharacterSelectNS::PLAYER_TYPE::PLAYER_1));
		gameMaster->setPlayerCharacter(playerNS::PLAYER2, gameMasterNS::PLAYER_CHARACTER, uiCharacterSelect.getSelectState(uiCharacterSelectNS::PLAYER_TYPE::PLAYER_2));
		// �J��
		changeScene(nextScene);
	}

	return;
}
//============================================================================================================================================
// updateTime
// �X�V - ����
//============================================================================================================================================
void CharacterSelect::updateTime(float _frameTime)
{
	// �I�����Ԃ̍X�V
	selectTime -= _frameTime;

	// ���Ԑ���
	if (selectTime <= 0.0f)
	{
		// �J��
		changeScene(nextScene);
	}

	return;
}
//============================================================================================================================================
// render
// �`��
//============================================================================================================================================
void CharacterSelect::render(Direct3D9* _direct3D9)
{
	// �J�����E�E�B���h�E
	_direct3D9->device->SetTransform(D3DTS_VIEW, &camera[PLAYER_TYPE::PLAYER_1].view);
	_direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera[PLAYER_TYPE::PLAYER_1].projection);
	_direct3D9->changeViewportFullWindow();

	// 3D
	render3D(_direct3D9, camera[PLAYER_TYPE::PLAYER_1]);

	// ���u�����h������
	_direct3D9->device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// ���\�[�X�J���[�̎w��
	_direct3D9->device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	// ���f�X�e�B�l�[�V�����J���[�̎w��
	_direct3D9->device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// 2D
	render2D(_direct3D9->device);

	// Time
	renderTime();

	return;
}
//============================================================================================================================================
// render3D
// �`�� - 3D
//============================================================================================================================================
void CharacterSelect::render3D(Direct3D9* _direct3D9, Camera _currentCamera)
{
	// �V�[���G�t�F�N�g�̕`��
	sceneEffect.render(_direct3D9->device, _currentCamera.view, _currentCamera.projection, _currentCamera.position);

	return;
}
//============================================================================================================================================
// render2D
// �`�� - 2D
//============================================================================================================================================
void CharacterSelect::render2D(LPDIRECT3DDEVICE9 _device)
{
	// �L�����N�^�[�Z���N�gUI
	uiCharacterSelect.render(_device);

	// ��ʕ�����
	uiScreenSplitLine.render(_device);

	// �^�C��UI
	uiCharacterSelect.renderTime(_device);

	return;
}
//============================================================================================================================================
// time
// ����
//============================================================================================================================================
void CharacterSelect::renderTime(void)
{
	if (selectTime <= 9.5f)
	{
		textManager->text[textManagerNS::TYPE::NEW_RODIN_CHARACTER_SELECT_TIME]->print(POSITION_TIME_X, POSITION_TIME_Y, "0%.0f", selectTime);

		return;
	}

	textManager->text[textManagerNS::TYPE::NEW_RODIN_CHARACTER_SELECT_TIME]->print(POSITION_TIME_X, POSITION_TIME_Y, "%.0f", selectTime);

	return;
}
//============================================================================================================================================
// None
//============================================================================================================================================
void CharacterSelect::collisions(void)
{
	// None
	return;
}
void CharacterSelect::AI(void)
{
	// None
	return;
}