//=============================================================================
// リザルト処理 [Result.cpp]
// 制作者 飯塚春輝
////===========================================================================
#include "Result.h"
// チュートリアル名前空間有効
using namespace resultNS;
//=============================================================================
// コンストラクタ
//=============================================================================
Result::Result()
{
	// 現在のシーン(リザルト)
	sceneName = "Scene -Result-";
	// 次のシーン(タイトル)
	nextScene = SceneList::TITLE;
}
//=============================================================================
// デストラクタ
//=============================================================================
Result::~Result()
{
	// サウンドの停止
	sound->stop(soundNS::TYPE::BGM_RESULT);
}
//=============================================================================
// 初期化処理
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

	// サウンドの再生
	sound->play(soundNS::TYPE::BGM_RESULT, soundNS::METHOD::LOOP);

	//camera
	camera = new Camera;
	camera->initialize(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
	camera->setGaze(D3DXVECTOR3(0, 0, 0));
	camera->setPosition(D3DXVECTOR3(0, 0, -1));
	camera->setUpVector(D3DXVECTOR3(0, 1, 0));

	// リザルト2D初期化
	result2D.initialize(direct3D9->device, 0, _textureLoader);
}
//=============================================================================
// 更新処理
//=============================================================================
void Result::update(float frameTime)
{
	// カメラ更新
	camera->update();

	//Enterまたは〇ボタンでタイトルへ
	if (input->anyKeyPressed()||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::A)
		)changeScene(nextScene);
}
//=============================================================================
// 描画処理
//=============================================================================
void Result::render(Direct3D9* direct3D9)
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
void Result::render3D(Direct3D9* direct3D9)
{
}
//=============================================================================
// 2D描画処理
//=============================================================================
void Result::renderUI(LPDIRECT3DDEVICE9 device)
{
	// リザルト2D描画
	result2D.render(device);
}
//=============================================================================
// コリジョン処理
//=============================================================================
void Result::collisions()
{
}
//=============================================================================
// AI処理
//=============================================================================
void Result::AI()
{
}
//=============================================================================
// 終了処理
//=============================================================================
void Result::uninitialize()
{
	// リザルト2D終了
	result2D.uninitialize();
}