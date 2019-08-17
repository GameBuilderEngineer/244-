//=============================================================================
// チュートリアル処理 [Tutorial.cpp]
// 制作者 飯塚春輝
////===========================================================================
#include "Tutorial.h"
// チュートリアル名前空間有効
using namespace tutorialNS;
//=============================================================================
// コンストラクタ
//=============================================================================
Tutorial::Tutorial()
{
	// 現在のシーン(チュートリアル)
	sceneName = "Scene -Tutorial-";
	// 次のシーン(リザルト)
	nextScene = SceneList::RESULT;
}
//=============================================================================
// デストラクタ
//=============================================================================
Tutorial::~Tutorial()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
void Tutorial::initialize(
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

	// チュートリアル2D初期化
	tutorial2D.initialize(direct3D9->device, 0, _textureLoader);
}
//=============================================================================
// 更新処理
//=============================================================================
void Tutorial::update(float frameTime)
{
	// カメラ更新
	camera->update();

	// チュートリアル2D更新
	tutorial2D.update();

	//Enterまたは〇ボタンでリザルトへ
	if (input->wasKeyPressed(VK_RETURN)||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::A)
		)changeScene(nextScene);

}
//=============================================================================
// 描画処理
//=============================================================================
void Tutorial::render(Direct3D9* direct3D9)
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
void Tutorial::render3D(Direct3D9* direct3D9)
{
}
//=============================================================================
// 2D描画処理
//=============================================================================
void Tutorial::renderUI(LPDIRECT3DDEVICE9 device)
{
	// チュートリアル2D描画
	tutorial2D.render(device);
}
//=============================================================================
// コリジョン処理
//=============================================================================
void Tutorial::collisions()
{
}
//=============================================================================
// AI処理
//=============================================================================
void Tutorial::AI()
{
}
//=============================================================================
// 終了処理
//=============================================================================
void Tutorial::uninitialize()
{
	// チュートリアル2D終了
	tutorial2D.uninitialize();
}
