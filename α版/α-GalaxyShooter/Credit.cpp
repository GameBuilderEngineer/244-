//=============================================================================
// クレジット処理 [Credit.cpp]
// 制作者 飯塚春輝
////===========================================================================
#include "Credit.h"
// クレジット名前空間有効
using namespace creditNS;
//=============================================================================
// コンストラクタ
//=============================================================================
Credit::Credit()
{
	// 現在のシーン(クレジット)
	sceneName = "Scene -Credit-";
	// 次のシーン(タイトル)
	nextScene = SceneList::TITLE;
}
//=============================================================================
// デストラクタ
//=============================================================================
Credit::~Credit()
{
	// サウンドの停止
	sound->stop(soundNS::TYPE::BGM_CREDIT);
}
//=============================================================================
// 初期化処理
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

	// サウンドの再生
	sound->play(soundNS::TYPE::BGM_CREDIT, soundNS::METHOD::LOOP);

	//camera
	camera = new Camera;
	camera->initialize(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
	camera->setGaze(D3DXVECTOR3(0, 0, 0));
	camera->setPosition(D3DXVECTOR3(0, 0, -1));
	camera->setUpVector(D3DXVECTOR3(0, 1, 0));

	// クレジット2D初期化
	credit2D.initialize(direct3D9->device, 0, _textureLoader);
}
//=============================================================================
// 更新処理
//=============================================================================
void Credit::update(float frameTime)
{
	// カメラ更新
	camera->update();

	// クレジット2D更新
	credit2D.update();

	//Enter,BackSpaceまたは〇ボタン,×ボタンでタイトルへ
	// 前の遷移へ戻る
	if (input->wasKeyPressed(VK_RETURN) ||
		input->wasKeyPressed(VK_BACK) ||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::A) ||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::B) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::B) )
	{
		// サウンドの再生
		sound->play(soundNS::TYPE::SE_CANCEL, soundNS::METHOD::PLAY);
		nextScene = SceneList::TITLE;
		changeScene(nextScene);
		return;
	}

}
//=============================================================================
// 描画処理
//=============================================================================
void Credit::render(Direct3D9* direct3D9)
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
void Credit::render3D(Direct3D9* direct3D9)
{
}
//=============================================================================
// 2D描画処理
//=============================================================================
void Credit::renderUI(LPDIRECT3DDEVICE9 device)
{
	// クレジット2D描画
	credit2D.render(device);
}
//=============================================================================
// コリジョン処理
//=============================================================================
void Credit::collisions()
{
}
//=============================================================================
// AI処理
//=============================================================================
void Credit::AI()
{
}
//=============================================================================
// 終了処理
//=============================================================================
void Credit::uninitialize()
{
	// クレジット2D終了
	credit2D.uninitialize();
}
