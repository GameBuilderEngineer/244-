#include "Splash.h"

#include "Sound.h"

using namespace splashNS;

Splash::Splash()
{
	sceneName = "Scene -Splash-";
	nextScene = SceneList::TITLE;
}

Splash::~Splash()
{

}

void Splash::initialize(
	Direct3D9* direct3D9,
	Input* _input,
	Sound* _sound,
	TextureLoader* _textureLoader,
	StaticMeshLoader* _staticMeshLoader,
	ShaderLoader* _shaderLoader, 
	TextManager* _textManager) {
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

	// サウンドの再生
	sound->play(soundNS::TYPE::BGM_SPLASH_TITLE, soundNS::METHOD::LOOP);

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

	// キーを押したらタイトルへ
	if (input->wasKeyPressed(VK_SPACE)|| input->wasKeyPressed(VK_RETURN))changeScene(nextScene);

	// フェードが終わったらタイトルへ
	if (splash2D.gotitle)changeScene(nextScene);

}

void Splash::render(Direct3D9* direct3D9) {


	//1Pカメラ・ウィンドウ
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

	// αテストを有効に
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			// αソースカラーの指定
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// αデスティネーションカラーの指定

	device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	splash2D.render(device);

	// αテストを無効に
	device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

void Splash::collisions() {

}

void Splash::AI() {

}

void Splash::uninitialize() {

	splash2D.uninitialize();

}