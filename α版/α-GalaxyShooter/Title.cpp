//=============================================================================
// �^�C�g������ [title.cpp]
// ����� �ђˏt�P
////===========================================================================
#include "Title.h"
// �^�C�g�����O��ԗL��
using namespace titleNS;
//*****************************************************************************
// �萔
//*****************************************************************************
static int titletransition = NULL;	//�I���ʒu�L���ϐ�
//=============================================================================
// �R���X�g���N�^
//=============================================================================
Title::Title()
{
	// ���݂̃V�[��(�^�C�g��)
	sceneName = "Scene -Title-";
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
Title::~Title()
{
}
//=============================================================================
// ����������
//=============================================================================
void Title::initialize(
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
	camera = new Camera[NUM_PLAYER];

	for (int i = 0; i < NUM_PLAYER; i++)
	{
		camera[i].initialize(WINDOW_WIDTH, WINDOW_HEIGHT);
		camera[i].setTarget(titlePlayer[i].getPosition());
		camera[i].setTargetX(&titlePlayer[i].getAxisX()->direction);
		camera[i].setTargetY(&titlePlayer[i].getAxisY()->direction);
		camera[i].setTargetZ(&titlePlayer[i].getAxisZ()->direction);
		camera[i].setRelative(CAMERA_RELATIVE_QUATERNION[0]);
		camera[i].setGaze(D3DXVECTOR3(0, 0, 0));
		camera[i].setRelativeGaze(D3DXVECTOR3(0, 0, 0));
		camera[i].setUpVector(D3DXVECTOR3(0, 1, 0));
	}

	//light
	light = new Light;
	light->initialize(direct3D9);

	// �^�C�g���J�ډ摜�`�揈��������
	titleTrans.initialize(direct3D9->device, 0, _textureLoader);

	// �^�C�g���w��ʒu�`�揈��������
	titleTransPos.initialize(direct3D9->device, 0, _textureLoader);

	//// �^�C�g��2D������
	//title2D.initialize(direct3D9->device, 0, _textureLoader);

	//�C���X�^���X�v���[��
	plane.createPositionSpherical(direct3D9->device, 3000, 250.0f);
	plane.initialize(direct3D9->device, *shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD), *textureLoader->getTexture(textureLoaderNS::RING));

	titlePlayer[0].initialize(playerNS::TITLE_PLAYER, gameMaster->getPlayerInfomation()[0].modelType,direct3D9->device,staticMeshLoader,textureLoader,shaderLoader);
	titlePlayer[0].setPosition(D3DXVECTOR3(-20, 100, 25));
}
//=============================================================================
// �X�V����
//=============================================================================
void Title::update(float frameTime)
{
	// �L�[����������I��UI�ړ�
	if (input->wasKeyPressed(VK_DOWN)||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::DOWN) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::DOWN)
		)
	{
		sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		titletransition++;
	}
	else if (input->wasKeyPressed(VK_UP)||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::UP) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::UP)
		)
	{
		sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		titletransition--;
	}

	// �I��UI����
	if (titletransition > CNT_TITLE_MAX)
	{
		titletransition = 0;
	}
	// �I��UI���
	else if (titletransition < 0)
	{
		titletransition = CNT_TITLE_MAX;
	}

	// �ʒu�L��
	titleTrans.cntTitle = titletransition;
	titleTransPos.cntTitle = titletransition;

	// �I��UI�J�ڏ���
	titleTransitionPos();

	// �^�C�g���J�ډ摜�`�揈���X�V
	titleTrans.update();

	// �^�C�g���w��ʒu�`�揈���X�V
	titleTransPos.update();

	// �J�����A�b�v�f�[�g
	camera[0].setUpVector(titlePlayer[0].getAxisY()->direction);
	camera[0].update();
}
//=============================================================================
// �`�揈��
//=============================================================================
void Title::render(Direct3D9* direct3D9)
{
	//1P�J�����E�E�B���h�E
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera[0].view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera[0].projection);
	direct3D9->changeViewportFullWindow();
	render3D(direct3D9, camera[0]);
	//UI
	renderUI(direct3D9->device);
}
//=============================================================================
// 3D�`�揈��
//=============================================================================
void Title::render3D(Direct3D9* direct3D9, Camera currentCamera)
{
	//(��)//�v���[���̕`��(�C���X�^���V���O)
	plane.render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);

	// �^�C�g���v���C���[�`��
	titlePlayer[0].toonRender(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position,
		*shaderLoader->getEffect(shaderNS::TOON),
		*textureLoader->getTexture(textureLoaderNS::TOON_SHADE),
		*textureLoader->getTexture(textureLoaderNS::TOON_OUT_LINE));
}
//=============================================================================
// 2D�`�揈��
//=============================================================================
void Title::renderUI(LPDIRECT3DDEVICE9 device)
{
	//// �^�C�g��2D�`��
	//title2D.render(device);

	// �^�C�g���J�ډ摜�`�揈���`��
	titleTransPos.render(device);

	// �^�C�g���w��ʒu�`�揈���`��
	titleTrans.render(device);
}
//=============================================================================
// �R���W��������
//=============================================================================
void Title::collisions()
{
}
//=============================================================================
// AI����
//=============================================================================
void Title::AI()
{
}
//=============================================================================
// �I������
//=============================================================================
void Title::uninitialize()
{
	// ���C�g���
	SAFE_DELETE(light);

	// �J�������
	SAFE_DELETE_ARRAY(camera);

	// �^�C�g���J�ډ摜�`�揈���I��
	titleTrans.uninitialize();

	// �^�C�g���w��ʒu�`�揈���I��
	titleTransPos.uninitialize();

	//// �^�C�g��2D�I��
	//title2D.uninitialize();
}
//=============================================================================
// �I��UI�J�ڏ���
//=============================================================================
void Title::titleTransitionPos(void)
{
	switch (titletransition)
	{
		// �Z���N�g
	case 0:
		//Enter�܂��́Z�{�^���ŃZ���N�g��
		nextScene = SceneList::SELECT;
		if (input->wasKeyPressed(VK_RETURN)||
			input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
			input->getController()[PLAYER2]->wasButton(virtualControllerNS::A)
			)changeScene(nextScene);
		break;

		// �`���[�g���A��
	case 1:
		//Enter�܂��́Z�{�^���Ń`���[�g���A����
		nextScene = SceneList::TUTORIAL;
		if (input->wasKeyPressed(VK_RETURN)||
			input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
			input->getController()[PLAYER2]->wasButton(virtualControllerNS::A)
			)
		{
			sound->play(soundNS::TYPE::SE_DECISION, soundNS::METHOD::PLAY);
			changeScene(nextScene);
		}
		break;

		// ������@
	case 2:
		//Enter�܂��́Z�{�^���ŃI�y���[�V������
		nextScene = SceneList::OPERATION;
		if (input->wasKeyPressed(VK_RETURN)||
			input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
			input->getController()[PLAYER2]->wasButton(virtualControllerNS::A)
			)
		{
			sound->play(soundNS::TYPE::SE_DECISION, soundNS::METHOD::PLAY);
			changeScene(nextScene);
		}
		break;

		// �N���W�b�g
	case 3:
		//Enter�܂��́Z�{�^���ŃN���W�b�g��
		nextScene = SceneList::CREDIT;
		if (input->wasKeyPressed(VK_RETURN)||
			input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
			input->getController()[PLAYER2]->wasButton(virtualControllerNS::A)
			) 
		{
			sound->play(soundNS::TYPE::SE_DECISION, soundNS::METHOD::PLAY);
			changeScene(nextScene);
		}
		break;

		// �Q�[���I��
	case 4:
		//Enter�܂��́Z�{�^���ŃQ�[���I��
		if (input->wasKeyPressed(VK_RETURN)||
			input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
			input->getController()[PLAYER2]->wasButton(virtualControllerNS::A)
			)PostQuitMessage(0);
		break;
	}
}
