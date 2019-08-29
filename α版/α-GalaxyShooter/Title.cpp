//============================================================================================================================================
// Document
//============================================================================================================================================
// Title.cpp
// HAL���� GP-12A-332 09 �T���v��
// 2019/08/29
//============================================================================================================================================
#include "Title.h"
//============================================================================================================================================
// Using Declaration
// using�錾
//============================================================================================================================================
using namespace titleNS;
//============================================================================================================================================
// Constructor
// �R���X�g���N�^
//============================================================================================================================================
Title::Title(void)
{
	// ���̃V�[��( �^�C�g�� )
	sceneName = ("Scene -Title-");
	
	return;
}
//============================================================================================================================================
// Destructor
// �f�X�g���N�^
//============================================================================================================================================
Title::~Title(void)
{
	// �T�E���h�̒�~
	sound->stop(soundNS::TYPE::BGM_TITLE);

	uninitialize();

	return;
}
//============================================================================================================================================
// initialize
// ������
//============================================================================================================================================
void Title::initialize(Direct3D9* _direct3D9, Input* _input, Sound* _sound, TextureLoader* _textureLoader, StaticMeshLoader* _staticMeshLoader, ShaderLoader* _shaderLoader, TextManager* _textManager)
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

	// �T�E���h�̍Đ�
	sound->play(soundNS::TYPE::BGM_TITLE, soundNS::METHOD::LOOP);

	// Camera
	camera = new Camera[PLAYER_TYPE::PLAYER_TYPE_MAX];

	for (int i = 0; i < PLAYER_TYPE::PLAYER_TYPE_MAX; i++)
	{
		camera[i].initialize(WINDOW_WIDTH, WINDOW_HEIGHT);
		camera[i].setTarget(player[i].getPosition());
		camera[i].setTargetX(&player[i].getAxisX()->direction);
		camera[i].setTargetY(&player[i].getAxisY()->direction);
		camera[i].setTargetZ(&player[i].getAxisZ()->direction);
		camera[i].setRelative(CAMERA_RELATIVE_QUATERNION[0]);
		camera[i].setGaze(D3DXVECTOR3(0, 0, 0));
		camera[i].setRelativeGaze(D3DXVECTOR3(0, 0, 0));
		camera[i].setUpVector(D3DXVECTOR3(0, 1, 0));
	}

	// Light
	light = new Light;
	light->initialize(_direct3D9);

	// �^�C�g��UI�̏�����
	uiTitle.initialize(_direct3D9->device, _textureLoader);

	// �C���X�^���X�v���[���̏�����
	plane.createPositionSpherical(_direct3D9->device, 3000, 250.0f);
	plane.initialize(_direct3D9->device, *shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD), *textureLoader->getTexture(textureLoaderNS::BACKGROUND_DUST));

	// �v���C���[�̏�����
	player[PLAYER_TYPE::PLAYER_1].initialize(playerNS::TITLE_PLAYER, gameMaster->getPlayerInfomation()[PLAYER_TYPE::PLAYER_1].modelType, _direct3D9->device, staticMeshLoader, textureLoader, shaderLoader);
	player[PLAYER_TYPE::PLAYER_1].setPosition(D3DXVECTOR3(-20.0f, 100.0f, 25.0f));

	return;
}
//============================================================================================================================================
// uninitialize
// ���
//============================================================================================================================================
void Title::uninitialize(void)
{
	// ���C�g
	SAFE_DELETE(light);

	// �J����
	SAFE_DELETE_ARRAY(camera);

	// �^�C�g��UI
	uiTitle.release();

	return;
}
//============================================================================================================================================
// update
// �X�V
//============================================================================================================================================
void Title::update(float _frameTime)
{
	// �J����
	camera[0].setUpVector(player[PLAYER_TYPE::PLAYER_1].getAxisY()->direction);
	camera[0].update();

	// �^�C�g��UI
	uiTitle.update(input, sound);

	if (input->wasKeyPressed(VK_RETURN) ||
		input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::A) ||
		input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::A))
	{
		// �T�E���h�̍Đ�
		sound->play(soundNS::TYPE::SE_DECISION, soundNS::METHOD::PLAY);
		updateInput();
	}

	return;
}
//============================================================================================================================================
// updateInput
// �X�V - ����
//============================================================================================================================================
void Title::updateInput(void)
{
	switch (uiTitle.getSelectState())
	{
	case uiTitleNS::TITLE_MENU_TYPE::MENU_GAME_START:
		nextScene = (SceneList::SELECT);
		changeScene(nextScene);
		break;
	case uiTitleNS::TITLE_MENU_TYPE::MENU_TUTORIAL:
		nextScene = (SceneList::TUTORIAL);
		changeScene(nextScene);
		break;
	case uiTitleNS::TITLE_MENU_TYPE::MENU_OPERATION:
		nextScene = (SceneList::OPERATION);
		changeScene(nextScene);
		break;
	case uiTitleNS::TITLE_MENU_TYPE::MENU_CREDIT:
		nextScene = (SceneList::CREDIT);
		changeScene(nextScene);
		break;
	case uiTitleNS::TITLE_MENU_TYPE::MENU_GAME_EXIT:
		break;
	default:
		break;
	}

	return;
}
//============================================================================================================================================
// render
// �`��
//============================================================================================================================================
void Title::render(Direct3D9* _direct3D9)
{
	// �J�����E�E�B���h�E
	_direct3D9->device->SetTransform(D3DTS_VIEW, &camera[0].view);
	_direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera[0].projection);
	_direct3D9->changeViewportFullWindow();

	// 3D
	render3D(_direct3D9, camera[0]);

	// 2D
	render2D(_direct3D9->device);

	return;
}
//============================================================================================================================================
// render3D
// �`�� - 3D
//============================================================================================================================================
void Title::render3D(Direct3D9* _direct3D9, Camera _currentCamera)
{
	// �v���[��( �C���X�^���V���O )
	plane.render(_direct3D9->device, _currentCamera.view, _currentCamera.projection, _currentCamera.position);

	// �^�C�g���v���C���[�`��
	player[0].toonRender
	(
		_direct3D9->device,
		_currentCamera.view,
		_currentCamera.projection,
		_currentCamera.position,
		*shaderLoader->getEffect(shaderNS::TOON),
		*textureLoader->getTexture(textureLoaderNS::TOON_SHADE),
		*textureLoader->getTexture(textureLoaderNS::TOON_OUT_LINE)
	);

	return;
}
//============================================================================================================================================
// render2D
// �`�� - 2D
//============================================================================================================================================
void Title::render2D(LPDIRECT3DDEVICE9 _device)
{
	// �^�C�g��UI
	uiTitle.render(_device);

	return;
}
//============================================================================================================================================
// None
//============================================================================================================================================
void Title::collisions(void)
{
	// None
}
void Title::AI(void)
{
	// None
}