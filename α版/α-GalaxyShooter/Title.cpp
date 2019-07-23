#include "Title.h"
using namespace titleNS;

static int titletransition = 0;	//�I���ʒu�L���ϐ�

Title::Title()
{
	sceneName = "Scene -Title-";
}

Title::~Title()
{
	//BGM�̒�~
	audio->stopCue(audioCue::TITLE_BGM);
}

void Title::initialize(
	Direct3D9* direct3D9,
	Input* _input,
	Audio* _audio,
	TextureLoader* _textureLoader,
	StaticMeshLoader* _staticMeshLoader,
	ShaderLoader* _shaderLoader) {
	//Input
	input = _input;
	//audio
	audio = _audio;
	//textureLoader
	textureLoader = _textureLoader;
	//staticMeshLoader
	staticMeshLoader = _staticMeshLoader;
	//shaderLoader
	shaderLoader = _shaderLoader;
	//camera
	camera = new Camera;
	camera->initialize(WINDOW_WIDTH/2, WINDOW_HEIGHT);
	camera->setGaze(D3DXVECTOR3(0, 0, 0));
	camera->setPosition(D3DXVECTOR3(0, 0, -1));
	camera->setUpVector(D3DXVECTOR3(0, 1, 0));

	backGround.initialize(
		direct3D9->device, 
		*textureLoader->getTexture(textureLoaderNS::WHITE_TEXTURE),
		spriteNS::TOP_LEFT,								// ���_
		WINDOW_WIDTH,											// ����
		WINDOW_HEIGHT,											// ����
		D3DXVECTOR3(0, 0, 0),		// ���W
		D3DXVECTOR3(0, 0, 0),					// ��]
		TITLE_TRANSPOS_COLOR							// �F
	);
	titleTrans.initialize(direct3D9->device, 0, _textureLoader);
	titleTransPos.initialize(direct3D9->device, 0, _textureLoader);

	//BGM�̍Đ�
	audio->playCue(audioCue::TITLE_BGM);
}

void Title::update(float frameTime) {

	camera->update();

	// �L�[����������I��UI�ړ�
	if (input->wasKeyPressed(VK_DOWN))
	{
		titletransition++;
	}
	else if (input->wasKeyPressed(VK_UP))
	{
		titletransition--;
	}

	// �I��UI���E
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
	titleTransPos.cntTitle = titletransition;

	// �I��UI�J�ڏ���
	titleTransition();

	titleTrans.update();
	titleTransPos.update();
}

void Title::render(Direct3D9* direct3D9) {
	//1P�J�����E�E�B���h�E
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera->view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera->projection);
	direct3D9->changeViewportFullWindow();
	render3D(direct3D9);
	//UI
	renderUI(direct3D9->device);
}

void Title::render3D(Direct3D9* direct3D9) {

}

void Title::renderUI(LPDIRECT3DDEVICE9 device) {

	backGround.render(device);
	titleTransPos.render(device);
	titleTrans.render(device);
}

void Title::collisions() {

}

void Title::AI(){

}

void Title::uninitialize() {
	backGround.uninitialize();
	titleTrans.uninitialize();
	titleTransPos.uninitialize();
}

//=============================================================================
// �I��UI�J�ڏ���
//=============================================================================
void Title::titleTransition(void)
{
	switch (titleTransPos.cntTitle)
	{
		// �Q�[���J�n
	case 0:

		nextScene = SceneList::SELECT_CHARACTER;
		if (input->wasKeyPressed(VK_RETURN))changeScene(nextScene);
		break;

		// �`���[�g���A��
	case 1:

		nextScene = SceneList::TUTORIAL;
		if (input->wasKeyPressed(VK_RETURN))changeScene(nextScene);
		break;

		// ������@
	case 2:

		nextScene = SceneList::OPERATION;
		if (input->wasKeyPressed(VK_RETURN))changeScene(nextScene);
		break;

		// �N���W�b�g
	case 3:

		nextScene = SceneList::CREDIT;
		if (input->wasKeyPressed(VK_RETURN))changeScene(nextScene);
		break;

		// �Q�[���I��
	case 4:

		if (input->wasKeyPressed(VK_RETURN))PostQuitMessage(0);
		break;
	}
}
