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
	// �T�E���h�̒�~
	sound->stop(soundNS::TYPE::BGM_RESULT);
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

	// �T�E���h�̍Đ�
	sound->play(soundNS::TYPE::BGM_RESULT, soundNS::METHOD::LOOP);

	//camera
	camera = new Camera;
	camera->initialize(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
	camera->setGaze(D3DXVECTOR3(0, 0, 0));
	camera->setPosition(D3DXVECTOR3(0, 0, -1));
	camera->setUpVector(D3DXVECTOR3(0, 1, 0));

	// ���U���g2D������
	result2D.initialize(direct3D9->device, 0, _textureLoader);
}
//=============================================================================
// �X�V����
//=============================================================================
void Result::update(float frameTime)
{
	// �J�����X�V
	camera->update();

	//Enter�܂��́Z�{�^���Ń^�C�g����
	if (input->anyKeyPressed()||
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
	// ���U���g2D�`��
	result2D.render(device);
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
	// ���U���g2D�I��
	result2D.uninitialize();
}