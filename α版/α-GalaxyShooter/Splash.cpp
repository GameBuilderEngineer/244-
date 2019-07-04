#include "Splash.h"
using namespace splashNS;

Splash::Splash()
{
	sceneName = "Scene -Splash-";
	nextScene = SceneList::TITLE;
}

Splash::~Splash()
{
}

void Splash::initialize(Direct3D9* direct3D9, Input* _input, TextureLoader* _textureLoader, StaticMeshLoader* _staticMeshLoader) {
	//Input
	input = _input;
	//textureLoader
	textureLoader = _textureLoader;
	//staticMeshLoader
	staticMeshLoader = _staticMeshLoader;

	//camera
	camera = new Camera;
	camera->initialize(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
	camera->setGaze(D3DXVECTOR3(0, 0, 0));
	camera->setPosition(D3DXVECTOR3(0, 0, -1));
	camera->setUpVector(D3DXVECTOR3(0, 1, 0));

	splash2D.initialize(direct3D9->device,0, _textureLoader);

}

void Splash::update(float frameTime) {

	camera->update();

	splash2D.update();

	// �L�[����������^�C�g����
	if (input->wasKeyPressed(VK_SPACE)|| input->wasKeyPressed(VK_RETURN))changeScene(nextScene);

	// �t�F�[�h���I�������^�C�g����
	if (splash2D.gotitle)changeScene(nextScene);

}

void Splash::render(Direct3D9* direct3D9) {


	//1P�J�����E�E�B���h�E
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera->view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera->projection);
	direct3D9->changeViewportFullWindow();
	render3D(direct3D9);
	//UI
	renderUI(direct3D9->device);
}

void Splash::render3D(Direct3D9* direct3D9) {

}

void Splash::renderUI(LPDIRECT3DDEVICE9 device) {

	// ���e�X�g��L����
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			// ���\�[�X�J���[�̎w��
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// ���f�X�e�B�l�[�V�����J���[�̎w��

	device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	splash2D.render(device);

	// ���e�X�g�𖳌���
	device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

void Splash::collisions() {

}

void Splash::AI() {

}

void Splash::uninitialize() {

	splash2D.uninitialize();

}