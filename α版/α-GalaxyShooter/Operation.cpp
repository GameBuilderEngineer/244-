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
	// �T�E���h�̒�~
	sound->stop(soundNS::TYPE::BGM_OPERATION);
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

	// �T�E���h�̍Đ�
	sound->play(soundNS::TYPE::BGM_OPERATION, soundNS::METHOD::PLAY);

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
	light->initialize(direct3D9);

	// �L�[�{�[�h����������
	keyOpe.initialize(direct3D9->device, 0, _textureLoader);

	// �p�b�h����������
	padOpe.initialize(direct3D9->device, 0, _textureLoader);

	opeTransition = NULL; // �I�y���[�V�����摜����ւ�

	// �V�[���G�t�F�N�g������
	sceneEffect.initialize(direct3D9->device, textureLoader, *shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD));

}

void Operation::update(float frameTime)
{
	// �J�����X�V
	camera->update();

	// �O�̑J�ڂ֖߂�
	if (input->wasKeyPressed(VK_BACK) ||
		input->getController()[PLAYER_TYPE::PLAYER_1]->wasButton(virtualControllerNS::B) ||
		input->getController()[PLAYER_TYPE::PLAYER_2]->wasButton(virtualControllerNS::B))
	{
		// �T�E���h�̍Đ�
		sound->play(soundNS::TYPE::SE_CANCEL, soundNS::METHOD::PLAY);
		nextScene = SceneList::TITLE;
		changeScene(nextScene);
		return;
	}

	// �L�[����������I��UI�ړ�
	if (input->wasKeyPressed(VK_RIGHT) ||
		input->getController()[PLAYER_TYPE::PLAYER_1]->wasButton(virtualControllerNS::RIGHT) ||
		input->getController()[PLAYER_TYPE::PLAYER_2]->wasButton(virtualControllerNS::RIGHT))
	{
		if (opeTransition < 1)
		{
			// �T�E���h�̍Đ�
			sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
			opeTransition++;
		}
	}
	else if (input->wasKeyPressed(VK_LEFT) ||
		input->getController()[PLAYER_TYPE::PLAYER_1]->wasButton(virtualControllerNS::LEFT) ||
		input->getController()[PLAYER_TYPE::PLAYER_2]->wasButton(virtualControllerNS::LEFT))
	{
		if (opeTransition > 0)
		{
			// �T�E���h�̍Đ�
			sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
			opeTransition--;
		}
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

	// �V�[���G�t�F�N�g�̍X�V
	sceneEffect.update(frameTime);

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		// �V�[���G�t�F�N�g����
		sceneEffect.generateSceneEffect(1, D3DXVECTOR3((float)(rand() % 100 - 50), (float)(rand() % 100 - 50), (float)(rand() % 100 - 50)));
	}

}
//=============================================================================
// �`�揈��
//=============================================================================
void Operation::render(Direct3D9* direct3D9)
{
	//1P�J�����E�E�B���h�E
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera[PLAYER_TYPE::PLAYER_1].view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera[PLAYER_TYPE::PLAYER_1].projection);
	direct3D9->changeViewportFullWindow();
	render3D(direct3D9 , camera[PLAYER_TYPE::PLAYER_1]);

	// ���u�����h������
	direct3D9->device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// ���\�[�X�J���[�̎w��
	direct3D9->device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	// ���f�X�e�B�l�[�V�����J���[�̎w��
	direct3D9->device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//UI
	renderUI(direct3D9->device);
}
//=============================================================================
// 3D�`�揈��
//=============================================================================
void Operation::render3D(Direct3D9* direct3D9, Camera _currentCamera)
{
	// �V�[���G�t�F�N�g�̕`��
	sceneEffect.render(direct3D9->device, _currentCamera.view, _currentCamera.projection, _currentCamera.position);

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
	// �J����
	SAFE_DELETE_ARRAY(camera);

	// ���C�g
	SAFE_DELETE(light);

}
