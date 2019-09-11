//=============================================================================
// スプラッシュ処理 [Splash.cpp]
// 制作者 飯塚春輝
////===========================================================================
#include "Splash.h"
#include "Sound.h"
// スプラッシュ名前空間有効
using namespace splashNS;
//=============================================================================
// コンストラクタ
//=============================================================================
Splash::Splash()
{
	// 現在のシーン(スプラッシュ)
	sceneName = "Scene -Splash-";
	// 次のシーン(タイトル)
	nextScene = SceneList::TITLE;
}
//=============================================================================
// デストラクタ
//=============================================================================
Splash::~Splash()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
void Splash::initialize(
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

	// サウンドの再生
	sound->play(soundNS::TYPE::BGM_SPLASH, soundNS::METHOD::PLAY);

	//camera
	camera = new Camera;
	camera->initialize(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
	camera->setGaze(D3DXVECTOR3(0, 0, 0));
	camera->setPosition(D3DXVECTOR3(0, 0, -1));
	camera->setUpVector(D3DXVECTOR3(0, 1, 0));

	// スプラッシュ2D初期化
	splash2D.initialize(direct3D9->device,0, _textureLoader);
}
//=============================================================================
// 更新処理
//=============================================================================
void Splash::update(float frameTime)
{
	// カメラ更新
	camera->update();

	// スプラッシュ2D更新
	splash2D.update();

	//Enter,Spaceまたは〇ボタン,Optionsでタイトルへ
	if (input->wasKeyPressed(VK_RETURN) ||
		input->wasKeyPressed(VK_SPACE) ||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::A) ||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::SPECIAL_MAIN) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::SPECIAL_MAIN)
		)changeScene(nextScene);

	// フェードが終わったらタイトルへ
	if (splash2D.gotitle)changeScene(nextScene);
}
//=============================================================================
// 描画処理
//=============================================================================
void Splash::render(Direct3D9* direct3D9)
{
	//1Pカメラ・ウィンドウ
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera->view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera->projection);
	direct3D9->changeViewportFullWindow();
	render3D(direct3D9);
	//UI
	renderUI(direct3D9->device);
}
//=============================================================================
// 3D描画処理
//=============================================================================
void Splash::render3D(Direct3D9* direct3D9)
{
}
//=============================================================================
// 2D描画処理
//=============================================================================
void Splash::renderUI(LPDIRECT3DDEVICE9 device)
{
	// αテストを有効に
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			// αソースカラーの指定
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// αデスティネーションカラーの指定

	device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// スプラッシュ2D描画
	splash2D.render(device);

	// αテストを無効に
	device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
//=============================================================================
// コリジョン処理
//=============================================================================
void Splash::collisions()
{
}
//=============================================================================
// AI処理
//=============================================================================
void Splash::AI()
{
}
//=============================================================================
// 終了処理
//=============================================================================
void Splash::uninitialize()
{
	// サウンドの停止
	sound->stop(soundNS::TYPE::BGM_SPLASH);

	SAFE_DELETE(camera);
}