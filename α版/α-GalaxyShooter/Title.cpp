//=============================================================================
// タイトル処理 [title.cpp]
// 制作者 飯塚春輝
////===========================================================================
#include "Title.h"
// タイトル名前空間有効
using namespace titleNS;
//*****************************************************************************
// 定数
//*****************************************************************************
static int titletransition = NULL;	//選択位置記憶変数
//=============================================================================
// コンストラクタ
//=============================================================================
Title::Title()
{
	// 現在のシーン(タイトル)
	sceneName = "Scene -Title-";
}
//=============================================================================
// デストラクタ
//=============================================================================
Title::~Title()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
void Title::initialize(
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
	camera = new Camera[NUM_PLAYER];

	for (int i = 0; i < NUM_PLAYER; i++)
	{
		camera[i].initialize(WINDOW_WIDTH, WINDOW_HEIGHT);
		camera[i].setTarget(titlePlayer[i].getPosition());
		camera[i].setTargetX(&titlePlayer[i].getAxisX()->direction);
		camera[i].setTargetY(&titlePlayer[i].getAxisY()->direction);
		camera[i].setTargetZ(&titlePlayer[i].getAxisZ()->direction);
		camera[i].setRelative(CAMERA_RELATIVE_QUATERNION[0]);
		camera[i].setGaze(D3DXVECTOR3(0, 0, 0));
		camera[i].setRelativeGaze(D3DXVECTOR3(0, 0, 0));
		camera[i].setUpVector(D3DXVECTOR3(0, 1, 0));
	}

	//light
	light = new Light;
	light->initialize(direct3D9);

	// タイトル遷移画像描画処理初期化
	titleTrans.initialize(direct3D9->device, 0, _textureLoader);

	// タイトル指定位置描画処理初期化
	titleTransPos.initialize(direct3D9->device, 0, _textureLoader);

	//// タイトル2D初期化
	//title2D.initialize(direct3D9->device, 0, _textureLoader);

	//インスタンスプレーン
	plane.createPositionSpherical(direct3D9->device, 3000, 250.0f);
	plane.initialize(direct3D9->device, *shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD), *textureLoader->getTexture(textureLoaderNS::RING));

	titlePlayer[0].initialize(playerNS::TITLE_PLAYER, gameMaster->getPlayerInfomation()[0].modelType,direct3D9->device,staticMeshLoader,textureLoader,shaderLoader);
	titlePlayer[0].setPosition(D3DXVECTOR3(-20, 100, 25));
}
//=============================================================================
// 更新処理
//=============================================================================
void Title::update(float frameTime)
{
	// キーを押したら選択UI移動
	if (input->wasKeyPressed(VK_DOWN)||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::DOWN) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::DOWN)
		)
	{
		sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		titletransition++;
	}
	else if (input->wasKeyPressed(VK_UP)||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::UP) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::UP)
		)
	{
		sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		titletransition--;
	}

	// 選択UI下限
	if (titletransition > CNT_TITLE_MAX)
	{
		titletransition = 0;
	}
	// 選択UI上限
	else if (titletransition < 0)
	{
		titletransition = CNT_TITLE_MAX;
	}

	// 位置記憶
	titleTrans.cntTitle = titletransition;
	titleTransPos.cntTitle = titletransition;

	// 選択UI遷移処理
	titleTransitionPos();

	// タイトル遷移画像描画処理更新
	titleTrans.update();

	// タイトル指定位置描画処理更新
	titleTransPos.update();

	// カメラアップデート
	camera[0].setUpVector(titlePlayer[0].getAxisY()->direction);
	camera[0].update();
}
//=============================================================================
// 描画処理
//=============================================================================
void Title::render(Direct3D9* direct3D9)
{
	//1Pカメラ・ウィンドウ
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera[0].view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera[0].projection);
	direct3D9->changeViewportFullWindow();
	render3D(direct3D9, camera[0]);
	//UI
	renderUI(direct3D9->device);
}
//=============================================================================
// 3D描画処理
//=============================================================================
void Title::render3D(Direct3D9* direct3D9, Camera currentCamera)
{
	//(仮)//プレーンの描画(インスタンシング)
	plane.render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);

	// タイトルプレイヤー描画
	titlePlayer[0].toonRender(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position,
		*shaderLoader->getEffect(shaderNS::TOON),
		*textureLoader->getTexture(textureLoaderNS::TOON_SHADE),
		*textureLoader->getTexture(textureLoaderNS::TOON_OUT_LINE));
}
//=============================================================================
// 2D描画処理
//=============================================================================
void Title::renderUI(LPDIRECT3DDEVICE9 device)
{
	//// タイトル2D描画
	//title2D.render(device);

	// タイトル遷移画像描画処理描画
	titleTransPos.render(device);

	// タイトル指定位置描画処理描画
	titleTrans.render(device);
}
//=============================================================================
// コリジョン処理
//=============================================================================
void Title::collisions()
{
}
//=============================================================================
// AI処理
//=============================================================================
void Title::AI()
{
}
//=============================================================================
// 終了処理
//=============================================================================
void Title::uninitialize()
{
	// ライト解放
	SAFE_DELETE(light);

	// カメラ解放
	SAFE_DELETE_ARRAY(camera);
}
//=============================================================================
// 選択UI遷移処理
//=============================================================================
void Title::titleTransitionPos(void)
{
	switch (titletransition)
	{
		// セレクト
	case 0:
		//Enterまたは〇ボタンでセレクトへ
		nextScene = SceneList::SELECT;
		if (input->wasKeyPressed(VK_RETURN)||
			input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
			input->getController()[PLAYER2]->wasButton(virtualControllerNS::A)
			)changeScene(nextScene);
		break;

		// チュートリアル
	case 1:
		//Enterまたは〇ボタンでチュートリアルへ
		nextScene = SceneList::TUTORIAL;
		if (input->wasKeyPressed(VK_RETURN)||
			input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
			input->getController()[PLAYER2]->wasButton(virtualControllerNS::A)
			)
		{
			sound->play(soundNS::TYPE::SE_DECISION, soundNS::METHOD::PLAY);
			changeScene(nextScene);
		}
		break;

		// 操作方法
	case 2:
		//Enterまたは〇ボタンでオペレーションへ
		nextScene = SceneList::OPERATION;
		if (input->wasKeyPressed(VK_RETURN)||
			input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
			input->getController()[PLAYER2]->wasButton(virtualControllerNS::A)
			)
		{
			sound->play(soundNS::TYPE::SE_DECISION, soundNS::METHOD::PLAY);
			changeScene(nextScene);
		}
		break;

		// クレジット
	case 3:
		//Enterまたは〇ボタンでクレジットへ
		nextScene = SceneList::CREDIT;
		if (input->wasKeyPressed(VK_RETURN)||
			input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
			input->getController()[PLAYER2]->wasButton(virtualControllerNS::A)
			) 
		{
			sound->play(soundNS::TYPE::SE_DECISION, soundNS::METHOD::PLAY);
			changeScene(nextScene);
		}
		break;

		// ゲーム終了
	case 4:
		//Enterまたは〇ボタンでゲーム終了
		if (input->wasKeyPressed(VK_RETURN)||
			input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
			input->getController()[PLAYER2]->wasButton(virtualControllerNS::A)
			)PostQuitMessage(0);
		break;
	}
}
