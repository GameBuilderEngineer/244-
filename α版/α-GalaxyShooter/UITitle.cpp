//============================================================================================================================================
// Document
//============================================================================================================================================
// UITitle.cpp
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/08/29
//============================================================================================================================================
#include "UITitle.h"
//============================================================================================================================================
// Using Declaration
// using宣言
//============================================================================================================================================
using namespace uiTitleNS;
//============================================================================================================================================
// Global Variable
// グローバル変数
//============================================================================================================================================
int UITitle::instanceIndex = 0;							//	インスタンスインデックス
LPDIRECT3DTEXTURE9 UITitle::texture[TYPE::TYPE_MAX];	//	テクスチャ
//============================================================================================================================================
// Constructor
// コンストラクタ
//============================================================================================================================================
UITitle::UITitle(void)
{
	// インスタンスインデックスを加算
	instanceIndex++;

	// テクスチャのクリア
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		texture[i] = NULL;
	}

	return;
}
//============================================================================================================================================
// Destructor
// デストラクタ
//============================================================================================================================================
UITitle::~UITitle(void)
{
	// 解放
	release();

	return;
}
//============================================================================================================================================
// initialize
// 初期化
//============================================================================================================================================
HRESULT UITitle::initialize(LPDIRECT3DDEVICE9 _device, TextureLoader* _textureLoader, int _selectStateMemory)
{
	// ディレクトリ設定
	setVisualDirectory();

	// テクスチャローダーのタイトルUIインデックスのスタート位置（テクスチャローダーをオブジェクトごとに定数分割すればもう少し便利になるかも？）
	int textureLoaderIndex = textureLoaderNS::TEXTURE_NUMBER::TITLE_LOGO;

	// テクスチャ読み込み
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		texture[i] = *_textureLoader->getTexture(textureLoaderIndex);
		textureLoaderIndex++;
	}

	// スプライト初期化
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		initializeSprite(_device, i);
	}

	selectState = _selectStateMemory;

	return S_OK;
}
//============================================================================================================================================
// initializeSprite
// 初期化 - スプライト
//============================================================================================================================================
void UITitle::initializeSprite(LPDIRECT3DDEVICE9 _device, int _index)
{
	switch (_index)
	{
	case TYPE::TITLE_LOGO:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			WIDTH_TITLE_LOGO,					//	横幅
			HEIGHT_TITLE_LOGO,					//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_TITLE_LOGO_X,			//	座標 x
				POSITION_TITLE_LOGO_Y,			//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::TITLE_BAR:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			WIDTH_TITLE_BAR,					//	横幅
			HEIGHT_TITLE_BAR,					//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_TITLE_BAR_X,			//	座標 x
				POSITION_TITLE_BAR_Y,			//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::GAME_START:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			WIDTH_GAME_START,					//	横幅
			HEIGHT_GAME_START,					//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_GAME_START_X,			//	座標 x
				POSITION_GAME_START_Y,			//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::GAME_START_SELECT:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			WIDTH_GAME_START,					//	横幅
			HEIGHT_GAME_START,					//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_GAME_START_X,			//	座標 x
				POSITION_GAME_START_Y,			//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::TUTORIAL:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			WIDTH_TUTORIAL,						//	横幅
			HEIGHT_TUTORIAL,					//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_TUTORIAL_X,			//	座標 x
				POSITION_TUTORIAL_Y,			//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::TUTORIAL_SELECT:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			WIDTH_TUTORIAL,						//	横幅
			HEIGHT_TUTORIAL,					//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_TUTORIAL_X,			//	座標 x
				POSITION_TUTORIAL_Y,			//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::OPERATION:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			WIDTH_OPERATION,					//	横幅
			HEIGHT_OPERATION,					//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_OPERATION_X,			//	座標 x
				POSITION_OPERATION_Y,			//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::OPERATION_SELECT:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			WIDTH_OPERATION,					//	横幅
			HEIGHT_OPERATION,					//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_OPERATION_X,			//	座標 x
				POSITION_OPERATION_Y,			//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::CREDIT:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			WIDTH_CREDIT,						//	横幅
			HEIGHT_CREDIT,						//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_CREDIT_X,				//	座標 x
				POSITION_CREDIT_Y,				//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::CREDIT_SELECT:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			WIDTH_CREDIT,						//	横幅
			HEIGHT_CREDIT,						//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_CREDIT_X,				//	座標 x
				POSITION_CREDIT_Y,				//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::GAME_EXIT:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			WIDTH_GAME_EXIT,					//	横幅
			HEIGHT_GAME_EXIT,					//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_GAME_EXIT_X,			//	座標 x
				POSITION_GAME_EXIT_Y,			//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::GAME_EXIT_SELECT:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			WIDTH_GAME_EXIT,					//	横幅
			HEIGHT_GAME_EXIT,					//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_GAME_EXIT_X,			//	座標 x
				POSITION_GAME_EXIT_Y,			//	座標 y
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
void UITitle::release(void)
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
void UITitle::update(Input* _input, Sound* _sound)
{
	if (_input->wasKeyPressed(VK_DOWN) ||
		_input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::DOWN) ||
		_input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::DOWN))
	{
		_sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		selectState++;
	}
	else if (_input->wasKeyPressed(VK_UP) ||
		_input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::UP) ||
		_input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::UP))
	{
		_sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		selectState--;
	}

	if (selectState > TITLE_MENU_TYPE::MENU_GAME_EXIT)
	{
		selectState = TITLE_MENU_TYPE::MENU_GAME_START;
	}
	else if (selectState < TITLE_MENU_TYPE::MENU_GAME_START)
	{
		selectState = TITLE_MENU_TYPE::MENU_GAME_EXIT;
	}

	updateBar();

	return;
}
//============================================================================================================================================
// updateBar
// 更新 - バー
//============================================================================================================================================
void UITitle::updateBar(void)
{
	switch (selectState)
	{
	case TITLE_MENU_TYPE::MENU_GAME_START:
		sprite[TYPE::TITLE_BAR].setPosition(D3DXVECTOR3(POSITION_TITLE_BAR_X, POSITION_GAME_START_Y, 0.0f));
		break;
	case TITLE_MENU_TYPE::MENU_TUTORIAL:
		sprite[TYPE::TITLE_BAR].setPosition(D3DXVECTOR3(POSITION_TITLE_BAR_X, POSITION_TUTORIAL_Y, 0.0f));
		break;
	case TITLE_MENU_TYPE::MENU_OPERATION:
		sprite[TYPE::TITLE_BAR].setPosition(D3DXVECTOR3(POSITION_TITLE_BAR_X, POSITION_OPERATION_Y, 0.0f));
		break;
	case TITLE_MENU_TYPE::MENU_CREDIT:
		sprite[TYPE::TITLE_BAR].setPosition(D3DXVECTOR3(POSITION_TITLE_BAR_X, POSITION_CREDIT_Y, 0.0f));
		break;
	case TITLE_MENU_TYPE::MENU_GAME_EXIT:
		sprite[TYPE::TITLE_BAR].setPosition(D3DXVECTOR3(POSITION_TITLE_BAR_X, POSITION_GAME_EXIT_Y, 0.0f));
		break;
	default:
		break;
	}

	sprite[TYPE::TITLE_BAR].setVertex();

	return;
}
//============================================================================================================================================
// render
// 描画
//============================================================================================================================================
void UITitle::render(LPDIRECT3DDEVICE9 _device)
{
	// Bar
	sprite[TYPE::TITLE_BAR].render(_device);

	// Game Start
	if (selectState == TITLE_MENU_TYPE::MENU_GAME_START)
	{
		sprite[TYPE::GAME_START_SELECT].render(_device);
	}
	else
	{
		sprite[TYPE::GAME_START].render(_device);
	}

	// Tutorial
	if (selectState == TITLE_MENU_TYPE::MENU_TUTORIAL)
	{
		sprite[TYPE::TUTORIAL_SELECT].render(_device);
	}
	else
	{
		sprite[TYPE::TUTORIAL].render(_device);
	}

	// Operation
	if (selectState == TITLE_MENU_TYPE::MENU_OPERATION)
	{
		sprite[TYPE::OPERATION_SELECT].render(_device);
	}
	else
	{
		sprite[TYPE::OPERATION].render(_device);
	}

	// Credit
	if (selectState == TITLE_MENU_TYPE::MENU_CREDIT)
	{
		sprite[TYPE::CREDIT_SELECT].render(_device);
	}
	else
	{
		sprite[TYPE::CREDIT].render(_device);
	}

	// Game Exit
	if (selectState == TITLE_MENU_TYPE::MENU_GAME_EXIT)
	{
		sprite[TYPE::GAME_EXIT_SELECT].render(_device);
	}
	else
	{
		sprite[TYPE::GAME_EXIT].render(_device);
	}

	// Title Logo
	sprite[TYPE::TITLE_LOGO].render(_device);

	return;
}