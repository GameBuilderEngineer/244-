//=============================================================================
// �N���W�b�g���� [Credit.cpp]
// ����� �ђˏt�P
////===========================================================================
#include "Credit.h"
// �N���W�b�g���O��ԗL��
using namespace creditNS;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
Credit::Credit()
{
	// ���݂̃V�[��(�N���W�b�g)
	sceneName = "Scene -Credit-";
	// ���̃V�[��(�^�C�g��)
	nextScene = SceneList::TITLE;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
Credit::~Credit()
{
	// �T�E���h�̒�~
	sound->stop(soundNS::TYPE::BGM_CREDIT);
}
//=============================================================================
// ����������
//=============================================================================
void Credit::initialize(
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
	sound->play(soundNS::TYPE::BGM_CREDIT, soundNS::METHOD::LOOP);

	//camera
	camera = new Camera;
	camera->initialize(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
	camera->setGaze(D3DXVECTOR3(0, 0, 0));
	camera->setPosition(D3DXVECTOR3(0, 0, -1));
	camera->setUpVector(D3DXVECTOR3(0, 1, 0));

	// �N���W�b�g2D������
	credit2D.initialize(direct3D9->device, 0, _textureLoader);
}
//=============================================================================
// �X�V����
//=============================================================================
void Credit::update(float frameTime)
{
	// �J�����X�V
	camera->update();

	// �N���W�b�g2D�X�V
	credit2D.update();

	//Enter,BackSpace�܂��́Z�{�^��,�~�{�^���Ń^�C�g����
	// �O�̑J�ڂ֖߂�
	if (input->wasKeyPressed(VK_BACK) ||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::B) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::B))
	{
		// �T�E���h�̍Đ�
		sound->play(soundNS::TYPE::SE_CANCEL, soundNS::METHOD::PLAY);
		nextScene = SceneList::TITLE;
		changeScene(nextScene);
		return;
	}

}
//=============================================================================
// �`�揈��
//=============================================================================
void Credit::render(Direct3D9* direct3D9)
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
void Credit::render3D(Direct3D9* direct3D9)
{
}
//=============================================================================
// 2D�`�揈��
//=============================================================================
void Credit::renderUI(LPDIRECT3DDEVICE9 device)
{
	// �N���W�b�g2D�`��
	credit2D.render(device);
}
//=============================================================================
// �R���W��������
//=============================================================================
void Credit::collisions()
{
}
//=============================================================================
// AI����
//=============================================================================
void Credit::AI()
{
}
//=============================================================================
// �I������
//=============================================================================
void Credit::uninitialize()
{
}
