//=============================================================================
// オペレーション処理 [Operation.cpp]
// 制作者 飯塚春輝
////===========================================================================
#include "Operation.h"
// オペレーション名前空間有効
using namespace operationNS;
//=============================================================================
// コンストラクタ
//=============================================================================
Operation::Operation()
{
	// 現在のシーン(オペレーション)
	sceneName = "Scene -Operation-";
	// 次のシーン(タイトル)
	nextScene = SceneList::TITLE;
}
//=============================================================================
// デストラクタ
//=============================================================================
Operation::~Operation()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
void Operation::initialize(
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

	// キーボード説明初期化
	keyOpe.initialize(direct3D9->device, 0, _textureLoader);

	// パッド説明初期化
	padOpe.initialize(direct3D9->device, 0, _textureLoader);

	opeTransition = NULL; // オペレーション画像入れ替え
}

void Operation::update(float frameTime)
{
	// カメラ更新
	camera->update();

	// キーを押したら選択UI移動
	if (input->wasKeyPressed(VK_RIGHT)||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::RIGHT) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::RIGHT)
		)
	{
		opeTransition++;
	}
	else if (input->wasKeyPressed(VK_LEFT)||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::LEFT) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::LEFT)
		)
	{
		opeTransition--;
	}

	// 選択UI下限
	if (opeTransition > OPE_MAX)
	{
		opeTransition = 0;
	}
	// 選択UI上限
	else if (opeTransition < 0)
	{
		opeTransition = OPE_MAX;
	}

	//Enterまたは〇ボタンでリザルトへ
	if (input->wasKeyPressed(VK_RETURN)||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::A)
		)changeScene(nextScene);
}
//=============================================================================
// 描画処理
//=============================================================================
void Operation::render(Direct3D9* direct3D9)
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
void Operation::render3D(Direct3D9* direct3D9)
{
}
//=============================================================================
// 2D描画処理
//=============================================================================
void Operation::renderUI(LPDIRECT3DDEVICE9 device)
{
	switch (opeTransition)
	{
		// パッド説明
	case 0:

		padOpe.render(device);
		keyOpe.render(device);

		break;
		// キーボード説明
	case 1:

		keyOpe.render(device);
		padOpe.render(device);

		break;
	}
}
//=============================================================================
// コリジョン処理
//=============================================================================
void Operation::collisions()
{
}
//=============================================================================
// AI処理
//=============================================================================
void Operation::AI()
{
}
//=============================================================================
// 終了処理
//=============================================================================
void Operation::uninitialize()
{
}
