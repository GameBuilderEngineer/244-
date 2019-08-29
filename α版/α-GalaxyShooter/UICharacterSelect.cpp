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
	selectState[PLAYER_TYPE::PLAYER_1] = 0;
	selectState[PLAYER_TYPE::PLAYER_2] = 1;
	progressState[PLAYER_TYPE::PLAYER_1] = PROGRESS_TYPE::CHARACTER_SELECT;
	progressState[PLAYER_TYPE::PLAYER_2] = PROGRESS_TYPE::CHARACTER_SELECT;

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

	// テクスチャ読み込み( 準備完了 + 待ち )
	texture[TYPE::READY_PLAYER_1_BACKGROUND] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::UI_CHARACTER_SELECT_READY_BACKGROUND);
	texture[TYPE::READY_PLAYER_2_BACKGROUND] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::UI_CHARACTER_SELECT_READY_BACKGROUND);
	texture[TYPE::READY_PLAYER_1_BAR] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::UI_CHARACTER_SELECT_READY_BAR);
	texture[TYPE::READY_PLAYER_2_BAR] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::UI_CHARACTER_SELECT_READY_BAR);
	texture[TYPE::READY_PLAYER_1_CANCEL] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::UI_CHARACTER_SELECT_READY_CANCEL);
	texture[TYPE::READY_PLAYER_2_CANCEL] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::UI_CHARACTER_SELECT_READY_CANCEL);
	texture[TYPE::READY_PLAYER_1_WAITING] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::UI_CHARACTER_SELECT_READY_WAITING);
	texture[TYPE::READY_PLAYER_2_WAITING] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::UI_CHARACTER_SELECT_READY_WAITING);

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
	case TYPE::READY_PLAYER_1_BACKGROUND:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			READY_BACKGROUND_WIDTH,				//	横幅
			READY_BACKGROUND_HEIGHT,			//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_READY_BACKGROUND_1,	//	座標 x
				POSITION_Y_READY_BACKGROUND,	//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::READY_PLAYER_2_BACKGROUND:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			READY_BACKGROUND_WIDTH,				//	横幅
			READY_BACKGROUND_HEIGHT,			//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_READY_BACKGROUND_2,	//	座標 x
				POSITION_Y_READY_BACKGROUND,	//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::READY_PLAYER_1_BAR:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			READY_BAR_WIDTH,					//	横幅
			READY_BAR_HEIGHT,					//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_READY_BAR_1,			//	座標 x
				POSITION_Y_READY_BAR,			//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::READY_PLAYER_2_BAR:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			READY_BAR_WIDTH,					//	横幅
			READY_BAR_HEIGHT,					//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_READY_BAR_2,			//	座標 x
				POSITION_Y_READY_BAR,			//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::READY_PLAYER_1_CANCEL:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			READY_CANCEL_WIDTH,					//	横幅
			READY_CANCEL_HEIGHT,				//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_READY_CANCEL_1,		//	座標 x
				POSITION_Y_READY_CANCEL,		//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::READY_PLAYER_2_CANCEL:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			READY_CANCEL_WIDTH,					//	横幅
			READY_CANCEL_HEIGHT,				//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_READY_CANCEL_2,		//	座標 x
				POSITION_Y_READY_CANCEL,		//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::READY_PLAYER_1_WAITING:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			READY_WAITING_WIDTH,				//	横幅
			READY_WAITING_HEIGHT,				//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_READY_WAITING_1,		//	座標 x
				POSITION_Y_READY_WAITING,		//	座標 y
				0.0f							//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
		);
		break;
	case TYPE::READY_PLAYER_2_WAITING:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	テクスチャ
			spriteNS::CENTER,					//	原点
			READY_WAITING_WIDTH,				//	横幅
			READY_WAITING_HEIGHT,				//	高さ
			D3DXVECTOR3							//	座標
			(
				POSITION_X_READY_WAITING_2,		//	座標 x
				POSITION_Y_READY_WAITING,		//	座標 y
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
// updateInputCharacterSelect
// 更新 - 入力( キャラクターセレクト )
//============================================================================================================================================
void UICharacterSelect::updateInput(Input* _input, Sound *_sound)
{
	// Player 1
	switch (progressState[PLAYER_TYPE::PLAYER_1])
	{
	case PROGRESS_TYPE::CHARACTER_SELECT:
		updateInputCharacterSelectPlayer1(_input, _sound);
		break;
	case PROGRESS_TYPE::READY:
		updateInputReadyPlayer1(_input, _sound);
		break;
	case PROGRESS_TYPE::WAITING:
		updateInputWaitingPlayer1(_input, _sound);
		break;
	default:
		break;
	}

	// Player 2
	switch (progressState[PLAYER_TYPE::PLAYER_2])
	{
	case PROGRESS_TYPE::CHARACTER_SELECT:
		updateInputCharacterSelectPlayer2(_input, _sound);
		break;
	case PROGRESS_TYPE::READY:
		updateInputReadyPlayer2(_input, _sound);
		break;
	case PROGRESS_TYPE::WAITING:
		updateInputWaitingPlayer2(_input, _sound);
		break;
	default:
		break;
	}

	return;
}
//============================================================================================================================================
// updateInputCharacterSelectPlayer1
// 更新 - 入力( キャラクターセレクト：プレイヤー1 )
//============================================================================================================================================
void UICharacterSelect::updateInputCharacterSelectPlayer1(Input* _input, Sound *_sound)
{
	if (_input->wasKeyPressed(VK_RETURN) || _input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::A))
	{
		// サウンドの再生
		_sound->play(soundNS::TYPE::SE_READY, soundNS::METHOD::PLAY);
		progressState[PLAYER_TYPE::PLAYER_1] = PROGRESS_TYPE::READY;

		return;
	}

	if (_input->wasKeyPressed('D') || _input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::RIGHT))
	{
		// サウンドの再生
		_sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		selectState[PLAYER_TYPE::PLAYER_1] += 1;

		return;
	}
	else if (_input->wasKeyPressed('A') || _input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::LEFT))
	{
		// サウンドの再生
		_sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		selectState[PLAYER_TYPE::PLAYER_1] -= 1;

		return;
	}

	return;
}
//============================================================================================================================================
// updateInputCharacterSelectPlayer2
// 更新 - 入力( キャラクターセレクト：プレイヤー2 )
//============================================================================================================================================
void UICharacterSelect::updateInputCharacterSelectPlayer2(Input* _input, Sound *_sound)
{
	if (_input->wasKeyPressed(VK_SPACE) || _input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::A))
	{
		// サウンドの再生
		_sound->play(soundNS::TYPE::SE_READY, soundNS::METHOD::PLAY);
		progressState[PLAYER_TYPE::PLAYER_2] = PROGRESS_TYPE::READY;

		return;
	}

	if (_input->wasKeyPressed(VK_RIGHT) || _input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::RIGHT))
	{
		// サウンドの再生
		_sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		selectState[PLAYER_TYPE::PLAYER_2] += 1;

		return;
	}
	else if (_input->wasKeyPressed(VK_LEFT) || _input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::LEFT))
	{
		// サウンドの再生
		_sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		selectState[PLAYER_TYPE::PLAYER_2] -= 1;

		return;
	}

	return;
}
//============================================================================================================================================
// updateInputReadyPlayer1
// 更新 - 入力( 準備完了：プレイヤー1 )
//============================================================================================================================================
void UICharacterSelect::updateInputReadyPlayer1(Input* _input, Sound *_sound)
{
	if (_input->wasKeyPressed(VK_BACK) || _input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::B))
	{
		// サウンドの再生
		_sound->play(soundNS::TYPE::SE_CANCEL, soundNS::METHOD::PLAY);
		progressState[PLAYER_TYPE::PLAYER_1] = PROGRESS_TYPE::CHARACTER_SELECT;

		return;
	}

	if (_input->wasKeyPressed(VK_RETURN) || _input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::A))
	{
		// サウンドの再生
		_sound->play(soundNS::TYPE::SE_READY, soundNS::METHOD::PLAY);
		progressState[PLAYER_TYPE::PLAYER_1] = PROGRESS_TYPE::WAITING;

		return;
	}

	return;
}
//============================================================================================================================================
// updateInputReadyPlayer2
// 更新 - 入力( 準備完了：プレイヤー2 )
//============================================================================================================================================
void UICharacterSelect::updateInputReadyPlayer2(Input* _input, Sound *_sound)
{
	if (_input->wasKeyPressed(VK_DELETE) || _input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::B))
	{
		// サウンドの再生
		_sound->play(soundNS::TYPE::SE_CANCEL, soundNS::METHOD::PLAY);
		progressState[PLAYER_TYPE::PLAYER_2] = PROGRESS_TYPE::CHARACTER_SELECT;

		return;
	}

	if (_input->wasKeyPressed(VK_SPACE) || _input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::A))
	{
		// サウンドの再生
		_sound->play(soundNS::TYPE::SE_READY, soundNS::METHOD::PLAY);
		progressState[PLAYER_TYPE::PLAYER_2] = PROGRESS_TYPE::WAITING;

		return;
	}

	return;
}
//============================================================================================================================================
// updateInputWaitingPlayer1
// 更新 - 入力( 待ち：プレイヤー1 )
//============================================================================================================================================
void UICharacterSelect::updateInputWaitingPlayer1(Input* _input, Sound *_sound)
{
	if (_input->wasKeyPressed(VK_BACK) || _input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::B))
	{
		// サウンドの再生
		_sound->play(soundNS::TYPE::SE_CANCEL, soundNS::METHOD::PLAY);
		progressState[PLAYER_TYPE::PLAYER_1] = PROGRESS_TYPE::CHARACTER_SELECT;
	}

	return;
}
//============================================================================================================================================
// updateInputWaitingPlayer2
// 更新 - 入力( 待ち：プレイヤー2 )
//============================================================================================================================================
void UICharacterSelect::updateInputWaitingPlayer2(Input* _input, Sound *_sound)
{
	if (_input->wasKeyPressed(VK_DELETE) || _input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::B))
	{
		// サウンドの再生
		_sound->play(soundNS::TYPE::SE_CANCEL, soundNS::METHOD::PLAY);
		progressState[PLAYER_TYPE::PLAYER_2] = PROGRESS_TYPE::CHARACTER_SELECT;
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
	// キャラクターセレクト
	renderCharacterSelect1(_device);
	renderCharacterSelect2(_device);

	// 準備完了 + 待ち
	renderReadyWaiting1(_device);
	renderReadyWaiting2(_device);

	return;
}
//============================================================================================================================================
// renderCharacterSelect1
// 描画 - キャラクターセレクト：プレイヤー1
//============================================================================================================================================
void UICharacterSelect::renderCharacterSelect1(LPDIRECT3DDEVICE9 _device)
{
	// BackGround
	sprite[TYPE::BACKGROUND_1].render(_device);

	// Character
	if (selectState[PLAYER_TYPE::PLAYER_1] == gameMasterNS::MODEL_ADAM)
	{
		sprite[TYPE::CHARACTER_PLAYER_1_ADAM].render(_device);
	}
	else
	{
		sprite[TYPE::CHARACTER_PLAYER_1_EVE].render(_device);
	}

	// Bar
	sprite[TYPE::BAR_1].render(_device);

	// Name
	if (selectState[PLAYER_TYPE::PLAYER_1] == gameMasterNS::MODEL_ADAM)
	{
		sprite[TYPE::NAME_PLAYER_1_ADAM].render(_device);
	}
	else
	{
		sprite[TYPE::NAME_PLAYER_1_EVE].render(_device);
	}

	// Cursor
	sprite[TYPE::CURSOR_1].render(_device);

	return;
}
//============================================================================================================================================
// renderCharacterSelect2
// 描画 - キャラクターセレクト：プレイヤー2
//============================================================================================================================================
void UICharacterSelect::renderCharacterSelect2(LPDIRECT3DDEVICE9 _device)
{
	// BackGround
	sprite[TYPE::BACKGROUND_2].render(_device);

	// Character
	if (selectState[PLAYER_TYPE::PLAYER_2] == gameMasterNS::MODEL_ADAM)
	{
		sprite[TYPE::CHARACTER_PLAYER_2_ADAM].render(_device);
	}
	else
	{
		sprite[TYPE::CHARACTER_PLAYER_2_EVE].render(_device);
	}

	// Bar
	sprite[TYPE::BAR_2].render(_device);

	// Name
	if (selectState[PLAYER_TYPE::PLAYER_2] == gameMasterNS::MODEL_ADAM)
	{
		sprite[TYPE::NAME_PLAYER_2_ADAM].render(_device);
	}
	else
	{
		sprite[TYPE::NAME_PLAYER_2_EVE].render(_device);
	}

	// Cursor
	sprite[TYPE::CURSOR_2].render(_device);

	return;
}
//============================================================================================================================================
// renderReadyWaiting1
// 描画 - 準備完了 + 待ち：プレイヤー1
//============================================================================================================================================
void UICharacterSelect::renderReadyWaiting1(LPDIRECT3DDEVICE9 _device)
{
	if (progressState[PLAYER_TYPE::PLAYER_1] == PROGRESS_TYPE::CHARACTER_SELECT) { return; }

	sprite[TYPE::READY_PLAYER_1_BACKGROUND].render(_device);

	if (progressState[PLAYER_TYPE::PLAYER_1] == PROGRESS_TYPE::READY)
	{
		sprite[TYPE::READY_PLAYER_1_BAR].render(_device);
		sprite[TYPE::READY_PLAYER_1_CANCEL].render(_device);

		return;
	}

	if (progressState[PLAYER_TYPE::PLAYER_1] == PROGRESS_TYPE::WAITING)
	{
		sprite[TYPE::READY_PLAYER_1_WAITING].render(_device);
		sprite[TYPE::READY_PLAYER_1_CANCEL].render(_device);

		return;
	}

	return;
}
//============================================================================================================================================
// renderReadyWaiting2
// 描画 - 準備完了 + 待ち：プレイヤー2
//============================================================================================================================================
void UICharacterSelect::renderReadyWaiting2(LPDIRECT3DDEVICE9 _device)
{
	if (progressState[PLAYER_TYPE::PLAYER_2] == PROGRESS_TYPE::CHARACTER_SELECT) { return; }

	sprite[TYPE::READY_PLAYER_2_BACKGROUND].render(_device);

	if (progressState[PLAYER_TYPE::PLAYER_2] == PROGRESS_TYPE::READY)
	{
		sprite[TYPE::READY_PLAYER_2_BAR].render(_device);
		sprite[TYPE::READY_PLAYER_2_CANCEL].render(_device);

		return;
	}

	if (progressState[PLAYER_TYPE::PLAYER_2] == PROGRESS_TYPE::WAITING)
	{
		sprite[TYPE::READY_PLAYER_2_WAITING].render(_device);
		sprite[TYPE::READY_PLAYER_2_CANCEL].render(_device);

		return;
	}

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