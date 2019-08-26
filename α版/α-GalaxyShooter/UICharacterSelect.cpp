//============================================================================================================================================
// Document
//============================================================================================================================================
// UICharacterSelect.cpp
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/08/25
//============================================================================================================================================
#include "UICharacterSelect.h"
//============================================================================================================================================
// Using Declaration
// using宣言
//============================================================================================================================================
using namespace uiCharacterSelectNS;
//============================================================================================================================================
// Global Variable
// グローバル変数
//============================================================================================================================================
int UICharacterSelect::instanceIndex = 0;						//	インスタンスインデックス
LPDIRECT3DTEXTURE9 UICharacterSelect::texture[TYPE::TYPE_MAX];	//	テクスチャ
//============================================================================================================================================
// Constructor
// コンストラクタ
//============================================================================================================================================
UICharacterSelect::UICharacterSelect(void)
{
	// インスタンスインデックスを加算
	instanceIndex++;

	// テクスチャのクリア
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		texture[i] = NULL;
	}

	// 初期化
	for (int i = 0; i < PLAYER_TYPE::PLAYER_TYPE_MAX; i++)
	{
		selectState[i] = NULL;
	}

	return;
}
//============================================================================================================================================
// Destructor
// デストラクタ
//============================================================================================================================================
UICharacterSelect::~UICharacterSelect(void)
{
	// 解放
	release();

	return;
}
//============================================================================================================================================
// initialize
// 初期化
//============================================================================================================================================
HRESULT UICharacterSelect::initialize(LPDIRECT3DDEVICE9 _device, TextureLoader* _textureLoader)
{
	// ディレクトリ設定
	setVisualDirectory();

	// テクスチャ読み込み( キャラクター )
	texture[TYPE::CHARACTER_PLAYER_1_ADAM] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::CHARACTER_ADAM);
	texture[TYPE::CHARACTER_PLAYER_1_EVE] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::CHARACTER_EVE);
	texture[TYPE::CHARACTER_PLAYER_2_ADAM] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::CHARACTER_ADAM);
	texture[TYPE::CHARACTER_PLAYER_2_EVE] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::CHARACTER_EVE);

	// テクスチャ読み込み( キャラクター名 )
	texture[TYPE::NAME_PLAYER_1_ADAM] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::UI_CHARACTER_SELECT_NAME_ADAM);
	texture[TYPE::NAME_PLAYER_1_EVE] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::UI_CHARACTER_SELECT_NAME_EVE);
	texture[TYPE::NAME_PLAYER_2_ADAM] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::UI_CHARACTER_SELECT_NAME_ADAM);
	texture[TYPE::NAME_PLAYER_2_EVE] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::UI_CHARACTER_SELECT_NAME_EVE);

	// テクスチャローダーのリザルトUIインデックスのスタート位置（テクスチャローダーをオブジェクトごとに定数分割すればもう少し便利になるかも？）
	int textureLoaderIndex = textureLoaderNS::TEXTURE_NUMBER::UI_CHARACTER_SELECT_BACKGROUND_1;

	// テクスチャ読み込み( リザルト )
	for (int i = TYPE::BACKGROUND_1; i < TYPE::TYPE_MAX; i++)
	{
		texture[i] = *_textureLoader->getTexture(textureLoaderIndex);
		textureLoaderIndex++;
	}

	// スプライト初期化
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		initializeSprite(_device, i);
	}

	return S_OK;
}
//============================================================================================================================================
// initializeSprite
// 初期化 - スプライト
//============================================================================================================================================
void UICharacterSelect::initializeSprite(LPDIRECT3DDEVICE9 _device, int _index)
{
	switch (_index)
	{
	case TYPE::CHARACTER_PLAYER_1_ADAM:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			CHARACTER_WIDTH,					//	横幅
			CHARACTER_HEIGHT,					//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_CHARACTER_1,			//	座標 x
				POSITION_Y_CHARACTER,			//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::CHARACTER_PLAYER_1_EVE:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			CHARACTER_WIDTH,					//	横幅
			CHARACTER_HEIGHT,					//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_CHARACTER_1,			//	座標 x
				POSITION_Y_CHARACTER,			//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::CHARACTER_PLAYER_2_ADAM:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			CHARACTER_WIDTH,					//	横幅
			CHARACTER_HEIGHT,					//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_CHARACTER_2,			//	座標 x
				POSITION_Y_CHARACTER,			//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::CHARACTER_PLAYER_2_EVE:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			CHARACTER_WIDTH,					//	横幅
			CHARACTER_HEIGHT,					//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_CHARACTER_2,			//	座標 x
				POSITION_Y_CHARACTER,			//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::NAME_PLAYER_1_ADAM:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			NAME_WIDTH,							//	横幅
			NAME_HEIGHT,						//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_NAME_1,				//	座標 x
				POSITION_Y_NAME,				//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::NAME_PLAYER_1_EVE:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			NAME_WIDTH,							//	横幅
			NAME_HEIGHT,						//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_NAME_1,				//	座標 x
				POSITION_Y_NAME,				//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::NAME_PLAYER_2_ADAM:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			NAME_WIDTH,							//	横幅
			NAME_HEIGHT,						//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_NAME_2,				//	座標 x
				POSITION_Y_NAME,				//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::NAME_PLAYER_2_EVE:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			NAME_WIDTH,							//	横幅
			NAME_HEIGHT,						//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_NAME_2,				//	座標 x
				POSITION_Y_NAME,				//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::BACKGROUND_1:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			BACKGROUND_WIDTH,					//	横幅
			BACKGROUND_HEIGHT,					//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_BACKGROUND_1,		//	座標 x
				POSITION_Y_BACKGROUND,			//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::BACKGROUND_2:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			BACKGROUND_WIDTH,					//	横幅
			BACKGROUND_HEIGHT,					//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_BACKGROUND_2,		//	座標 x
				POSITION_Y_BACKGROUND,			//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::BAR_1:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			BAR_WIDTH,							//	横幅
			BAR_HEIGHT,							//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_BAR_1,				//	座標 x
				POSITION_Y_BAR,					//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::BAR_2:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			BAR_WIDTH,							//	横幅
			BAR_HEIGHT,							//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_BAR_2,				//	座標 x
				POSITION_Y_BAR,					//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::CURSOR_1:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			CURSOR_WIDTH,						//	横幅
			CURSOR_HEIGHT,						//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_CURSOR_1,			//	座標 x
				POSITION_Y_CURSOR,				//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::CURSOR_2:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			CURSOR_WIDTH,						//	横幅
			CURSOR_HEIGHT,						//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_CURSOR_2,			//	座標 x
				POSITION_Y_CURSOR,				//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::TIME:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			TIME_WIDTH,							//	横幅
			TIME_HEIGHT,						//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_TIME,				//	座標 x
				POSITION_Y_TIME,				//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	default:
		break;
	}

	return;
}
//============================================================================================================================================
// release
// 解放
//============================================================================================================================================
void UICharacterSelect::release(void)
{
	// スプライトのクリア
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		sprite[i].setTexture(NULL);
	}

	// インスタンスインデックスを減算
	instanceIndex--;

	return;
}
//============================================================================================================================================
// update
// 更新
//============================================================================================================================================
void UICharacterSelect::update(Input* _input, Sound *_sound)
{
	// 入力の更新
	updateInput(_input, _sound);

	// UIの制御
	updateControl();

	return;
}
//============================================================================================================================================
// updateInput
// 更新 - 入力
//============================================================================================================================================
void UICharacterSelect::updateInput(Input* _input, Sound *_sound)
{
	// 各プレイヤーの入力更新
	updateInputPlayer1(_input, _sound);
	updateInputPlayer2(_input, _sound);

	return;
}
//============================================================================================================================================
// updateInputPlayer1
// 更新 - 入力( プレイヤー1 )
//============================================================================================================================================
void UICharacterSelect::updateInputPlayer1(Input* _input, Sound *_sound)
{
	// UI切り替え( Player 1 )
	if (_input->wasKeyPressed('D') || _input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::RIGHT))
	{
		// サウンドの再生
		_sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		selectState[PLAYER_TYPE::PLAYER_1] += 1;
	}
	else if (_input->wasKeyPressed('A') || _input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::LEFT))
	{
		// サウンドの再生
		_sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		selectState[PLAYER_TYPE::PLAYER_1] -= 1;
	}

	return;
}
//============================================================================================================================================
// updateInputPlayer2
// 更新 - 入力( プレイヤー2 )
//============================================================================================================================================
void UICharacterSelect::updateInputPlayer2(Input* _input, Sound *_sound)
{
	// UI切り替え( Player 2 )
	if (_input->wasKeyPressed(VK_RIGHT) || _input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::RIGHT))
	{
		// サウンドの再生
		_sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		selectState[PLAYER_TYPE::PLAYER_2] += 1;
	}
	else if (_input->wasKeyPressed(VK_LEFT) || _input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::LEFT))
	{
		// サウンドの再生
		_sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		selectState[PLAYER_TYPE::PLAYER_2] -= 1;
	}

	return;
}
//============================================================================================================================================
// updateControl
// 更新 - 制御
//============================================================================================================================================
void UICharacterSelect::updateControl(void)
{
	// 各プレイヤーのUI制御
	updateControlPlayer1();
	updateControlPlayer2();

	return;
}
//============================================================================================================================================
// updateControlPlayer1
// 更新 - 制御( プレイヤー1 )
//============================================================================================================================================
void UICharacterSelect::updateControlPlayer1(void)
{
	// UI制御( Player 1 )
	if (selectState[PLAYER_TYPE::PLAYER_1] > gameMasterNS::MODEL_EVE)
	{
		selectState[PLAYER_TYPE::PLAYER_1] = gameMasterNS::MODEL_ADAM;
	}
	else if (selectState[PLAYER_TYPE::PLAYER_1] < gameMasterNS::MODEL_ADAM)
	{
		selectState[PLAYER_TYPE::PLAYER_1] = gameMasterNS::MODEL_EVE;
	}

	return;
}
//============================================================================================================================================
// updateControlPlayer2
// 更新 - 制御( プレイヤー2 )
//============================================================================================================================================
void UICharacterSelect::updateControlPlayer2(void)
{
	// UI制御( Player 2 )
	if (selectState[PLAYER_TYPE::PLAYER_2] > gameMasterNS::MODEL_EVE)
	{
		selectState[PLAYER_TYPE::PLAYER_2] = gameMasterNS::MODEL_ADAM;
	}
	else if (selectState[PLAYER_TYPE::PLAYER_2] < gameMasterNS::MODEL_ADAM)
	{
		selectState[PLAYER_TYPE::PLAYER_2] = gameMasterNS::MODEL_EVE;
	}

	return;
}
//============================================================================================================================================
// render
// 描画
//============================================================================================================================================
void UICharacterSelect::render(LPDIRECT3DDEVICE9 _device)
{
	// BackGround
	sprite[TYPE::BACKGROUND_1].render(_device);
	sprite[TYPE::BACKGROUND_2].render(_device);

	// Character
	if (selectState[PLAYER_TYPE::PLAYER_1] == gameMasterNS::MODEL_ADAM)
	{
		sprite[TYPE::CHARACTER_PLAYER_1_ADAM].render(_device);
	}
	else
	{
		sprite[TYPE::CHARACTER_PLAYER_1_EVE].render(_device);
	}

	if (selectState[PLAYER_TYPE::PLAYER_2] == gameMasterNS::MODEL_ADAM)
	{
		sprite[TYPE::CHARACTER_PLAYER_2_ADAM].render(_device);
	}
	else
	{
		sprite[TYPE::CHARACTER_PLAYER_2_EVE].render(_device);
	}

	// Bar
	sprite[TYPE::BAR_1].render(_device);
	sprite[TYPE::BAR_2].render(_device);

	// Name
	if (selectState[PLAYER_TYPE::PLAYER_1] == gameMasterNS::MODEL_ADAM)
	{
		sprite[TYPE::NAME_PLAYER_1_ADAM].render(_device);
	}
	else
	{
		sprite[TYPE::NAME_PLAYER_1_EVE].render(_device);
	}

	if (selectState[PLAYER_TYPE::PLAYER_2] == gameMasterNS::MODEL_ADAM)
	{
		sprite[TYPE::NAME_PLAYER_2_ADAM].render(_device);
	}
	else
	{
		sprite[TYPE::NAME_PLAYER_2_EVE].render(_device);
	}

	// Cursor
	sprite[TYPE::CURSOR_1].render(_device);
	sprite[TYPE::CURSOR_2].render(_device);

	return;
}
//============================================================================================================================================
// renderTime
// 描画 - 時間
//============================================================================================================================================
void UICharacterSelect::renderTime(LPDIRECT3DDEVICE9 _device)
{
	// Time
	sprite[TYPE::TIME].render(_device);

	return;
}
//============================================================================================================================================
// getSelectState
// 取得 - 選択状態
//============================================================================================================================================
int UICharacterSelect::getSelectState(int _index)
{ 
	return selectState[_index];
}