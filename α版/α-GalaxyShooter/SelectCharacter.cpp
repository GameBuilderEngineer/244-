//=============================================================================
// セレクトキャラクター処理 [SelectCharacter.cpp]
// 制作者 飯塚春輝
////===========================================================================
#include "SelectCharacter.h"
// セレクトキャラクター名前空間有効
using namespace selectCharacterNS;
//=============================================================================
// コンストラクタ
//=============================================================================
SelectCharacter::SelectCharacter()
{
	// 現在のシーン(セレクトキャラクター)
	sceneName = "Scene -SelectCharacter-";
	// 次のシーン(ゲーム)
	nextScene = SceneList::GAME;
}
//=============================================================================
// デストラクタ
//=============================================================================
SelectCharacter::~SelectCharacter()
{
	// サウンドの停止
	sound->stop(soundNS::TYPE::BGM_CHARACTER_SELECT);
}
//=============================================================================
// 初期化処理
//=============================================================================
void SelectCharacter::initialize(
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
	sound->play(soundNS::TYPE::BGM_CHARACTER_SELECT, soundNS::METHOD::LOOP);

	//camera
	camera = new Camera;
	camera->initialize(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
	camera->setGaze(D3DXVECTOR3(0, 0, 0));
	camera->setPosition(D3DXVECTOR3(0, 0, -1));
	camera->setUpVector(D3DXVECTOR3(0, 1, 0));

	// 画面分割線の初期化
	uiScreenSplitLine.initialize(direct3D9->device, textureLoader);

	for (int i = 0; i < NUM_PLAYER; i++)
	{
		// セレクトキャラクター2D初期化
		selectCharacter2D[i].initialize(direct3D9->device, i, _textureLoader);
		// キャラクターセレクトバー初期化
		charaSelectBar[i].initialize(direct3D9->device, i, _textureLoader);
	}

	// タイマーUI初期化
	timerUI.initialize(direct3D9->device, 0, _textureLoader, _textManager);

	selectTransition = NULL;				// セレクト画像入れ替え
	select2Transition = NULL;				// セレクト2画像入れ替え
	selectTime = SELECT_TIME_MAX;			// セレクト時間初期化
	selectOneTime = SELECT_ONE_TIME_MAX;	// セレクト時間1桁初期化
	selectTenTime = SELECT_TEN_TIME_MAX;	// セレクト時間10桁初期化
	selectOneFlameTime = NULL;				// フレーム時間1桁初期化
	selectTenFlameTime = NULL;				// フレーム時間10初期化
}
//=============================================================================
// 更新処理
//=============================================================================
void SelectCharacter::update(float frameTime)
{
	// カメラ更新
	camera->update();

	// 前の遷移へ戻る
	if (input->wasKeyPressed(VK_BACK) ||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::B) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::B))
	{
		// サウンドの再生
		sound->play(soundNS::TYPE::SE_CANCEL, soundNS::METHOD::PLAY);
		nextScene = SceneList::TITLE;
		changeScene(nextScene);
		return;
	}

	// キーを押したら選択UI移動
	if (input->wasKeyPressed('D') ||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::RIGHT))
	{
		// サウンドの再生
		sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		selectTransition++;
	}
	else if (input->wasKeyPressed('A') ||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::LEFT))
	{
		// サウンドの再生
		sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		selectTransition--;
	}

	// キーを押したら選択UI2移動
	if (input->wasKeyPressed(VK_RIGHT) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::RIGHT))
	{
		// サウンドの再生
		sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		select2Transition++;
	}
	else if (input->wasKeyPressed(VK_LEFT) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::LEFT))
	{
		// サウンドの再生
		sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		select2Transition--;
	}

	// 選択UI下限
	if (selectTransition > SELECT_TRANS_MAX)
	{
		selectTransition = 0;
	}
	// 選択UI上限
	else if (selectTransition < 0)
	{
		selectTransition = SELECT_TRANS_MAX;
	}

	// 選択UI2下限
	if (select2Transition > SELECT_TRANS_MAX)
	{
		select2Transition = 0;
	}
	// 選択UI2上限
	else if (select2Transition < 0)
	{
		select2Transition = SELECT_TRANS_MAX;
	}

	// フレーム時間加算
	selectOneFlameTime++;

	selectTenFlameTime++;

	// 60フレーム対応
	if (selectOneFlameTime == SELECT_ONE_FLAME_MAX)
	{
		// セレクトタイム減算
		selectTime--;

		// セレクトタイム1桁減算
		selectOneTime--;

		// フレーム時間初期化
		selectOneFlameTime = NULL;

		if (selectOneTime < NULL)
		{
			selectOneTime = SELECT_ONE_TIME_MAX;
		}
	}

	int selectModel1P = 0;
	int selectModel2P = 0;
	//モデル選択
	switch (selectTransition)
	{
	case 0:	selectModel1P = gameMasterNS::MODEL_ADAM; break;
	case 1:	selectModel1P = gameMasterNS::MODEL_EVE; break;
	} 
	switch (select2Transition)
	{
	case 0:	selectModel2P = gameMasterNS::MODEL_ADAM; break;
	case 1:	selectModel2P = gameMasterNS::MODEL_EVE; break;
	} 

	if (selectTenFlameTime == SELECT_TEN_FLAME_MAX)
	{
		// セレクトタイム10桁減算
		selectTenTime--;

		// フレーム時間初期化
		selectTenFlameTime = NULL;
	}

	//Enterまたは〇ボタンでゲームへ
	if (input->wasKeyPressed(VK_RETURN)||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::A)
		)
	{
		gameMaster->setPlayerCharacter(playerNS::PLAYER1, gameMasterNS::PLAYER_CHARACTER, selectModel1P);
		gameMaster->setPlayerCharacter(playerNS::PLAYER1, gameMasterNS::PLAYER_CHARACTER, selectModel2P);
		changeScene(nextScene);
	}

	// タイムアウト時
	if (selectTime <= NULL)
	{
		// セレクトタイム初期化
		selectOneTime = NULL;

		// セレクトタイム初期化
		selectTenTime = NULL;

		// ゲームへ
		changeScene(nextScene);
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void SelectCharacter::render(Direct3D9* direct3D9)
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
void SelectCharacter::render3D(Direct3D9* direct3D9)
{
}
//=============================================================================
// 2D描画処理
//=============================================================================
void SelectCharacter::renderUI(LPDIRECT3DDEVICE9 device)
{
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		// セレクトキャラクター2D描画
		selectCharacter2D[i].render(device, selectTransition, select2Transition);

		// キャラクターセレクトバー描画
		charaSelectBar[i].render(device, selectTransition, select2Transition);
	}

	// 画面分割線
	uiScreenSplitLine.render(device);

	// タイマーUI描画
	timerUI.render(device, selectOneTime, selectTenTime);
}
//=============================================================================
// コリジョン処理
//=============================================================================
void SelectCharacter::collisions()
{
}
//=============================================================================
// AI処理
//=============================================================================
void SelectCharacter::AI()
{
}
//=============================================================================
// 終了処理
//=============================================================================
void SelectCharacter::uninitialize()
{
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		// セレクトキャラクター2D終了
		selectCharacter2D[i].uninitialize();

		// キャラクターセレクトバー終了
		charaSelectBar[i].uninitialize();
	}
	// タイマーUI修了
	timerUI.uninitialize();
}