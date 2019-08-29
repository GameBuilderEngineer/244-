//============================================================================================================================================
// Document
//============================================================================================================================================
// UIResult.cpp
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/08/24
//============================================================================================================================================
#include "UIResult.h"
//============================================================================================================================================
// Using Declaration
// using宣言
//============================================================================================================================================
using namespace uiResultNS;
//============================================================================================================================================
// Global Variable
// グローバル変数
//============================================================================================================================================
int UIResult::instanceIndex = 0;						//	インスタンスインデックス
LPDIRECT3DTEXTURE9 UIResult::texture[TYPE::TYPE_MAX];	//	テクスチャ
//============================================================================================================================================
// Constructor
// コンストラクタ
//============================================================================================================================================
UIResult::UIResult(void)
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
UIResult::~UIResult(void)
{
	// 解放
	release();

	return;
}
//============================================================================================================================================
// initialize
// 初期化
//============================================================================================================================================
HRESULT UIResult::initialize(LPDIRECT3DDEVICE9 _device, TextureLoader* _textureLoader, TextManager* _textManager, GameMaster* _gameMaster)
{
	// テキストマネージャ
	textManager = _textManager;

	// ディレクトリ設定
	setVisualDirectory();

	// テクスチャ読み込み( キャラクター )
	texture[TYPE::CHARACTER_PLAYER_1_ADAM] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::CHARACTER_ADAM);
	texture[TYPE::CHARACTER_PLAYER_1_EVE] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::CHARACTER_EVE);
	texture[TYPE::CHARACTER_PLAYER_2_ADAM] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::CHARACTER_ADAM);
	texture[TYPE::CHARACTER_PLAYER_2_EVE] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::CHARACTER_EVE);

	// テクスチャ読み込み( リザルト )
	texture[TYPE::WIN_1] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::RESULT_WIN);
	texture[TYPE::WIN_2] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::RESULT_WIN);
	texture[TYPE::LOSE_1] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::RESULT_LOSE);
	texture[TYPE::LOSE_2] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::RESULT_LOSE);
	texture[TYPE::DRAW_1] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::RESULT_DRAW);
	texture[TYPE::DRAW_2] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::RESULT_DRAW);

	// テクスチャローダーのリザルトUIインデックスのスタート位置（テクスチャローダーをオブジェクトごとに定数分割すればもう少し便利になるかも？）
	int textureLoaderIndex = textureLoaderNS::TEXTURE_NUMBER::RESULT_WINDOW;

	// テクスチャ読み込み( リザルト )
	for (int i = TYPE::WINDOW; i < TYPE::TYPE_MAX; i++)
	{
		texture[i] = *_textureLoader->getTexture(textureLoaderIndex);
		textureLoaderIndex++;
	}

	// スプライト初期化
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		initializeSprite(_device, i);
	}
	
	// リザルト初期化
	playerTable = _gameMaster->getPlayerInfomation();
	result = _gameMaster->getResult();

	return S_OK;
}
//============================================================================================================================================
// initializeSprite
// 初期化 - スプライト
//============================================================================================================================================
void UIResult::initializeSprite(LPDIRECT3DDEVICE9 _device, int _index)
{
	switch (_index)
	{
	case TYPE::CHARACTER_PLAYER_1_ADAM:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			PLAYER_WIDTH,						//	横幅
			PLAYER_HEIGHT,						//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_PLAYER_CHARACTER_1,	//	座標 x
				POSITION_Y_PLAYER_CHARACTER,	//	座標 y
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
			PLAYER_WIDTH,						//	横幅
			PLAYER_HEIGHT,						//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_PLAYER_CHARACTER_1,	//	座標 x
				POSITION_Y_PLAYER_CHARACTER,	//	座標 y
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
			PLAYER_WIDTH,						//	横幅
			PLAYER_HEIGHT,						//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_PLAYER_CHARACTER_2,	//	座標 x
				POSITION_Y_PLAYER_CHARACTER,	//	座標 y
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
			PLAYER_WIDTH,						//	横幅
			PLAYER_HEIGHT,						//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_PLAYER_CHARACTER_2,	//	座標 x
				POSITION_Y_PLAYER_CHARACTER,	//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::WIN_1:
	case TYPE::LOSE_1:
	case TYPE::DRAW_1:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			RESULT_WIDTH,						//	横幅
			RESULT_HEIGHT,						//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_1,					//	座標 x
				POSITION_Y,						//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::WIN_2:
	case TYPE::LOSE_2:
	case TYPE::DRAW_2:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			RESULT_WIDTH,						//	横幅
			RESULT_HEIGHT,						//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_2,					//	座標 x
				POSITION_Y,						//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::WINDOW:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			RESULT_WINDOW_WIDTH,				//	横幅
			RESULT_WINDOW_HEIGHT,				//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_RESULT_WINDOW,		//	座標 x
				POSITION_Y_RESULT_WINDOW,		//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::PLAYER_NUMBER_1:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			PLAYER_NUMBER_WIDTH,				//	横幅
			PLAYER_NUMBER_HEIGHT,				//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_PLAYER_NUMBER_1,		//	座標 x
				POSITION_Y_PLAYER_NUMBER,		//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::PLAYER_NUMBER_2:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			PLAYER_NUMBER_WIDTH,				//	横幅
			PLAYER_NUMBER_HEIGHT,				//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_PLAYER_NUMBER_2,		//	座標 x
				POSITION_Y_PLAYER_NUMBER,		//	座標 y
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
void UIResult::release(void)
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
void UIResult::update(void)
{
	return;
}
//============================================================================================================================================
// render
// 描画
//============================================================================================================================================
void UIResult::render(LPDIRECT3DDEVICE9 _device)
{
	// チンギン完成までの仮
	int chingin[2] = { 2353,3294 };

	// Window
	sprite[TYPE::WINDOW].render(_device);

	// Character
	if ((playerTable + gameMasterNS::PLAYER_TYPE::PLAYER_CHARACTER)->playerType == gameMasterNS::MODEL_ADAM)
	{
		sprite[TYPE::CHARACTER_PLAYER_1_ADAM].render(_device);
	}
	else
	{
		sprite[TYPE::CHARACTER_PLAYER_1_EVE].render(_device);
	}
	if ((playerTable + gameMasterNS::PLAYER_TYPE::NON_PLAYER_CHARACTER)->playerType == gameMasterNS::MODEL_ADAM)
	{
		sprite[TYPE::CHARACTER_PLAYER_2_ADAM].render(_device);
	}
	else
	{
		sprite[TYPE::CHARACTER_PLAYER_2_EVE].render(_device);
	}

	// PlayerNumber
	sprite[TYPE::PLAYER_NUMBER_1].render(_device);
	sprite[TYPE::PLAYER_NUMBER_2].render(_device);

	// Result
	switch (result)
	{
	case gameMasterNS::RESULT_LIST::WIN_1P:
		sprite[TYPE::WIN_1].render(_device);
		sprite[TYPE::LOSE_2].render(_device);
		break;
	case gameMasterNS::RESULT_LIST::WIN_2P:
		sprite[TYPE::WIN_2].render(_device);
		sprite[TYPE::LOSE_1].render(_device);
		break;
	case gameMasterNS::RESULT_LIST::DRAW:
		sprite[TYPE::DRAW_1].render(_device);
		sprite[TYPE::DRAW_2].render(_device);
		break;
	default:
		break;
	}

	// Chingin
	renderChingin();

	return;
}
//============================================================================================================================================
// renderChingin
// 描画 - チンギン
//============================================================================================================================================
void UIResult::renderChingin(void)
{
	// Player 1
	textManager->text[textManagerNS::TYPE::NEW_RODIN_RESULT_CHINGIN_BACK]->print((POSITION_X_PLAYER_CHARACTER_1 - 280.0f), ((WINDOW_HEIGHT / 2) + 60.0f), "★ %d ★", (playerTable + gameMasterNS::PLAYER_TYPE::PLAYER_CHARACTER)->wage);
	textManager->text[textManagerNS::TYPE::NEW_RODIN_RESULT_CHINGIN]->print((POSITION_X_PLAYER_CHARACTER_1 - 290.0f), ((WINDOW_HEIGHT / 2) + 50.0f), "★ %d ★", (playerTable + gameMasterNS::PLAYER_TYPE::PLAYER_CHARACTER)->wage);
	// Player 2
	textManager->text[textManagerNS::TYPE::NEW_RODIN_RESULT_CHINGIN_BACK]->print((POSITION_X_PLAYER_CHARACTER_2 - 280.0f), ((WINDOW_HEIGHT / 2) + 60.0f), "★ %d ★", (playerTable + gameMasterNS::PLAYER_TYPE::NON_PLAYER_CHARACTER)->wage);
	textManager->text[textManagerNS::TYPE::NEW_RODIN_RESULT_CHINGIN]->print((POSITION_X_PLAYER_CHARACTER_2 - 290.0f), ((WINDOW_HEIGHT / 2) + 50.0f), "★ %d ★", (playerTable + gameMasterNS::PLAYER_TYPE::NON_PLAYER_CHARACTER)->wage);
	
	return;
}