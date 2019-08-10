//=============================================================================
// �Z���N�g�L�����N�^�[���� [SelectCharacter.cpp]
// ����� �ђˏt�P
////===========================================================================
#include "SelectCharacter.h"
// �Z���N�g�L�����N�^�[���O��ԗL��
using namespace selectCharacterNS;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
SelectCharacter::SelectCharacter()
{
	// ���݂̃V�[��(�Z���N�g�L�����N�^�[)
	sceneName = "Scene -SelectCharacter-";
	// ���̃V�[��(�Q�[��)
	nextScene = SceneList::GAME;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
SelectCharacter::~SelectCharacter()
{
}
//=============================================================================
// ����������
//=============================================================================
void SelectCharacter::initialize(
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
		// �Z���N�g�L�����N�^�[2D������
		selectCharacter2D[i].initialize(direct3D9->device, i, _textureLoader);
		// �L�����N�^�[�Z���N�g�o�[������
		charaSelectBar[i].initialize(direct3D9->device, i, _textureLoader);
	}

	// �^�C�}�[UI������
	timerUI.initialize(direct3D9->device, 0, _textureLoader, _textManager);

	selectTransition = NULL;				// �Z���N�g�摜����ւ�
	select2Transition = NULL;				// �Z���N�g2�摜����ւ�
	selectTime = SELECT_TIME_MAX;			// �Z���N�g���ԏ�����
	selectOneTime = SELECT_ONE_TIME_MAX;	// �Z���N�g����1��������
	selectTenTime = SELECT_TEN_TIME_MAX;	// �Z���N�g����10��������
	selectOneFlameTime = NULL;				// �t���[������1��������
	selectTenFlameTime = NULL;				// �t���[������10������
}
//=============================================================================
// �X�V����
//=============================================================================
void SelectCharacter::update(float frameTime)
{
	// �J�����X�V
	camera->update();

	// �L�[����������I��UI�ړ�
	if (input->wasKeyPressed('D') ||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::RIGHT))
	{
		selectTransition++;
	}
	else if (input->wasKeyPressed('A') ||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::LEFT))
	{
		selectTransition--;
	}

	// �L�[����������I��UI2�ړ�
	if (input->wasKeyPressed(VK_RIGHT)||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::RIGHT))
	{
		select2Transition++;
	}
	else if (input->wasKeyPressed(VK_LEFT)||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::LEFT))
	{
		select2Transition--;
	}

	// �I��UI����
	if (selectTransition > SELECT_TRANS_MAX)
	{
		selectTransition = 0;
	}
	// �I��UI���
	else if (selectTransition < 0)
	{
		selectTransition = SELECT_TRANS_MAX;
	}

	// �I��UI2����
	if (select2Transition > SELECT_TRANS_MAX)
	{
		select2Transition = 0;
	}
	// �I��UI2���
	else if (select2Transition < 0)
	{
		select2Transition = SELECT_TRANS_MAX;
	}

	// �t���[�����ԉ��Z
	selectOneFlameTime++;

	selectTenFlameTime++;

	// 60�t���[���Ή�
	if (selectOneFlameTime == SELECT_ONE_FLAME_MAX)
	{
		// �Z���N�g�^�C�����Z
		selectTime--;

		// �Z���N�g�^�C��1�����Z
		selectOneTime--;

		// �t���[�����ԏ�����
		selectOneFlameTime = NULL;

		if (selectOneTime < NULL)
		{
			selectOneTime = SELECT_ONE_TIME_MAX;
		}
	}

	if (selectTenFlameTime == SELECT_TEN_FLAME_MAX)
	{
		// �Z���N�g�^�C��10�����Z
		selectTenTime--;

		// �t���[�����ԏ�����
		selectTenFlameTime = NULL;
	}

	//Enter�܂��́Z�{�^���ŃQ�[����
	if (input->wasKeyPressed(VK_RETURN)||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::A)
		)changeScene(nextScene);

	// �^�C���A�E�g��
	if (selectTime <= NULL)
	{
		// �Z���N�g�^�C��������
		selectOneTime = NULL;

		// �Z���N�g�^�C��������
		selectTenTime = NULL;

		// �Q�[����
		changeScene(nextScene);
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void SelectCharacter::render(Direct3D9* direct3D9)
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
void SelectCharacter::render3D(Direct3D9* direct3D9)
{
}
//=============================================================================
// 2D�`�揈��
//=============================================================================
void SelectCharacter::renderUI(LPDIRECT3DDEVICE9 device)
{
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		// �Z���N�g�L�����N�^�[2D�`��
		selectCharacter2D[i].render(device, selectTransition, select2Transition);

		// �L�����N�^�[�Z���N�g�o�[�`��
		charaSelectBar[i].render(device, selectTransition, select2Transition);
	}
	// �^�C�}�[UI�`��
	timerUI.render(device, selectOneTime, selectTenTime);
}
//=============================================================================
// �R���W��������
//=============================================================================
void SelectCharacter::collisions()
{
}
//=============================================================================
// AI����
//=============================================================================
void SelectCharacter::AI()
{
}
//=============================================================================
// �I������
//=============================================================================
void SelectCharacter::uninitialize()
{
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		// �Z���N�g�L�����N�^�[2D�I��
		selectCharacter2D[i].uninitialize();

		// �L�����N�^�[�Z���N�g�o�[�I��
		charaSelectBar[i].uninitialize();
	}
	// �^�C�}�[UI�C��
	timerUI.uninitialize();
}