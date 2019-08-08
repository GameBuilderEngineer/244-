//======================================================================================================================================================
// Document
//======================================================================================================================================================
// UIRecursion.cpp
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/07/27
//======================================================================================================================================================
#include "UIRecursion.h"
//======================================================================================================================================================
// Using Declaration
// using宣言
//======================================================================================================================================================
using namespace uiRecursionNS;
//======================================================================================================================================================
// Global Variable
// グローバル変数
//======================================================================================================================================================
int UIRecursion::instanceIndex = 0;							//	インスタンスインデックス
LPDIRECT3DTEXTURE9 UIRecursion::texture[TYPE::TYPE_MAX];	//	テクスチャ
//======================================================================================================================================================
// Constructor
// コンストラクタ
//======================================================================================================================================================
UIRecursion::UIRecursion(void)
{
	// インスタンスインデックスを加算
	instanceIndex++;

	// 初期化
	moveFlag = false;
	moveValue = 1.5f;

	// テクスチャのクリア
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		texture[i] = NULL;
		positionIndex[i] = POSITION::POP;
	}

	return;
}
//======================================================================================================================================================
// Destructor
// デストラクタ
//======================================================================================================================================================
UIRecursion::~UIRecursion(void)
{
	// 解放
	release();

	return;
}
//======================================================================================================================================================
// initialize
// 初期化
//======================================================================================================================================================
HRESULT UIRecursion::initialize(LPDIRECT3DDEVICE9 _device, int _playerIndex, TextureLoader* _textureLoader, Input* _input)
{

	input = _input;

	// テクスチャローダーのリカージョンUIインデックスのスタート位置（テクスチャローダーをオブジェクトごとに定数分割すればもう少し便利になるかも？）
	int textureLoaderIndex = textureLoaderNS::TEXTURE_NUMBER::UI_RECURSION_BICYCLE;

	// ディレクトリ設定
	setVisualDirectory();

	// テクスチャ読み込み
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		texture[i] = *_textureLoader->getTexture(textureLoaderIndex);
		textureLoaderIndex++;
	}

	// スプライト初期化
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		initializeSprite(_device, _playerIndex, i);
	}

	return S_OK;
}
//======================================================================================================================================================
// initializeSprite
// 初期化 - スプライト
//======================================================================================================================================================
void UIRecursion::initializeSprite(LPDIRECT3DDEVICE9 _device, int _playerIndex, int _index)
{
	switch (_index)
	{
	case TYPE::BICYCLE:
		sprite[_index].initialize
		(
			_device,
			texture[_index],												//	テクスチャ
			spriteNS::CENTER,												//	原点
			uiRecursionNS::WIDTH,											//	横幅
			uiRecursionNS::HEIGHT,											//	高さ
			D3DXVECTOR3														//	座標
			(
				_playerIndex ? POSITION_X_PLAYER_2 : POSITION_X_PLAYER_1,	//	座標 x
				POSITION_Y_POP,												//	座標 y
				0.0f														//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),									//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)								//	色
		);
		break;
	//case TYPE::BLACK_PHONE:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																			//	テクスチャ
	//		spriteNS::CENTER,																			//	原点
	//		uiRecursionNS::WIDTH,																		//	横幅
	//		uiRecursionNS::HEIGHT,																		//	高さ
	//		D3DXVECTOR3																					//	座標
	//		(
	//			playerIndex ? uiRecursionNS::POSITION_X_PLAYER_2 : uiRecursionNS::POSITION_X_PLAYER_1,	//	座標 x
	//			uiRecursionNS::POSITION_Y_POP,															//	座標 y
	//			0.0f																					//	座標 z
	//		),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																//	回転
	//		D3DCOLOR_RGBA(255, 255, 255, 255)															//	色
	//	);
	//	break;
	//case TYPE::CHEWING_GUM:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																			//	テクスチャ
	//		spriteNS::CENTER,																			//	原点
	//		uiRecursionNS::WIDTH,																		//	横幅
	//		uiRecursionNS::HEIGHT,																		//	高さ
	//		D3DXVECTOR3																					//	座標
	//		(
	//			playerIndex ? uiRecursionNS::POSITION_X_PLAYER_2 : uiRecursionNS::POSITION_X_PLAYER_1,	//	座標 x
	//			uiRecursionNS::POSITION_Y_POP,															//	座標 y
	//			0.0f																					//	座標 z
	//		),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																//	回転
	//		D3DCOLOR_RGBA(255, 255, 255, 255)															//	色
	//	);
	//	break;
	//case TYPE::FAN:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																			//	テクスチャ
	//		spriteNS::CENTER,																			//	原点
	//		uiRecursionNS::WIDTH,																		//	横幅
	//		uiRecursionNS::HEIGHT,																		//	高さ
	//		D3DXVECTOR3																					//	座標
	//		(
	//			playerIndex ? uiRecursionNS::POSITION_X_PLAYER_2 : uiRecursionNS::POSITION_X_PLAYER_1,	//	座標 x
	//			uiRecursionNS::POSITION_Y_POP,															//	座標 y
	//			0.0f																					//	座標 z
	//		),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																//	回転
	//		D3DCOLOR_RGBA(255, 255, 255, 255)															//	色
	//	);
	//	break;
	//case TYPE::KENDAMA:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																			//	テクスチャ
	//		spriteNS::CENTER,																			//	原点
	//		uiRecursionNS::WIDTH,																		//	横幅
	//		uiRecursionNS::HEIGHT,																		//	高さ
	//		D3DXVECTOR3																					//	座標
	//		(
	//			playerIndex ? uiRecursionNS::POSITION_X_PLAYER_2 : uiRecursionNS::POSITION_X_PLAYER_1,	//	座標 x
	//			uiRecursionNS::POSITION_Y_POP,															//	座標 y
	//			0.0f																					//	座標 z
	//		),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																//	回転
	//		D3DCOLOR_RGBA(255, 255, 255, 255)															//	色
	//	);
	//	break;
	//case TYPE::NAWATOBI:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																			//	テクスチャ
	//		spriteNS::CENTER,																			//	原点
	//		uiRecursionNS::WIDTH,																		//	横幅
	//		uiRecursionNS::HEIGHT,																		//	高さ
	//		D3DXVECTOR3																					//	座標
	//		(
	//			playerIndex ? uiRecursionNS::POSITION_X_PLAYER_2 : uiRecursionNS::POSITION_X_PLAYER_1,	//	座標 x
	//			uiRecursionNS::POSITION_Y_POP,															//	座標 y
	//			0.0f																					//	座標 z
	//		),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																//	回転
	//		D3DCOLOR_RGBA(255, 255, 255, 255)															//	色
	//	);
	//	break;
	//case TYPE::NINGEN:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																			//	テクスチャ
	//		spriteNS::CENTER,																			//	原点
	//		uiRecursionNS::WIDTH,																		//	横幅
	//		uiRecursionNS::HEIGHT,																		//	高さ
	//		D3DXVECTOR3																					//	座標
	//		(
	//			playerIndex ? uiRecursionNS::POSITION_X_PLAYER_2 : uiRecursionNS::POSITION_X_PLAYER_1,	//	座標 x
	//			uiRecursionNS::POSITION_Y_POP,															//	座標 y
	//			0.0f																					//	座標 z
	//		),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																//	回転
	//		D3DCOLOR_RGBA(255, 255, 255, 255)															//	色
	//	);
	//	break;
	//case TYPE::RABBIT_DOLL:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																			//	テクスチャ
	//		spriteNS::CENTER,																			//	原点
	//		uiRecursionNS::WIDTH,																		//	横幅
	//		uiRecursionNS::HEIGHT,																		//	高さ
	//		D3DXVECTOR3																					//	座標
	//		(
	//			playerIndex ? uiRecursionNS::POSITION_X_PLAYER_2 : uiRecursionNS::POSITION_X_PLAYER_1,	//	座標 x
	//			uiRecursionNS::POSITION_Y_POP,															//	座標 y
	//			0.0f																					//	座標 z
	//		),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																//	回転
	//		D3DCOLOR_RGBA(255, 255, 255, 255)															//	色
	//	);
	//	break;
	//case TYPE::SOCCER_BALL:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																			//	テクスチャ
	//		spriteNS::CENTER,																			//	原点
	//		uiRecursionNS::WIDTH,																		//	横幅
	//		uiRecursionNS::HEIGHT,																		//	高さ
	//		D3DXVECTOR3																					//	座標
	//		(
	//			playerIndex ? uiRecursionNS::POSITION_X_PLAYER_2 : uiRecursionNS::POSITION_X_PLAYER_1,	//	座標 x
	//			uiRecursionNS::POSITION_Y_POP,															//	座標 y
	//			0.0f																					//	座標 z
	//		),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																//	回転
	//		D3DCOLOR_RGBA(255, 255, 255, 255)															//	色
	//	);
	//	break;
	//case TYPE::TELEVISION:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																			//	テクスチャ
	//		spriteNS::CENTER,																			//	原点
	//		uiRecursionNS::WIDTH,																		//	横幅
	//		uiRecursionNS::HEIGHT,																		//	高さ
	//		D3DXVECTOR3																					//	座標
	//		(
	//			playerIndex ? uiRecursionNS::POSITION_X_PLAYER_2 : uiRecursionNS::POSITION_X_PLAYER_1,	//	座標 x
	//			uiRecursionNS::POSITION_Y_POP,															//	座標 y
	//			0.0f																					//	座標 z
	//		),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																//	回転
	//		D3DCOLOR_RGBA(255, 255, 255, 255)															//	色
	//	);
	//	break;
	//case TYPE::XMAS_TREE:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																			//	テクスチャ
	//		spriteNS::CENTER,																			//	原点
	//		uiRecursionNS::WIDTH,																		//	横幅
	//		uiRecursionNS::HEIGHT,																		//	高さ
	//		D3DXVECTOR3																					//	座標
	//		(
	//			playerIndex ? uiRecursionNS::POSITION_X_PLAYER_2 : uiRecursionNS::POSITION_X_PLAYER_1,	//	座標 x
	//			uiRecursionNS::POSITION_Y_POP,															//	座標 y
	//			0.0f																					//	座標 z
	//		),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																//	回転
	//		D3DCOLOR_RGBA(255, 255, 255, 255)															//	色
	//	);
	//	break;
	default:
		break;
	}

	return;
}
//======================================================================================================================================================
// release
// 解放
//======================================================================================================================================================
void UIRecursion::release(void)
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
//======================================================================================================================================================
// update
// 更新
//======================================================================================================================================================
void UIRecursion::update(void)
{
	if (moveFlag)
	{
		updateMove();
		return;
	}

	if (input->wasKeyPressed(VK_RETURN))
	{
		moveFlag = !moveFlag;
	}

	return;
}
//======================================================================================================================================================
// updateMove
// 更新 - 移動
//======================================================================================================================================================
void UIRecursion::updateMove(void)
{
	D3DXVECTOR3 spritePosition = sprite[TYPE::BICYCLE].getPosition();

	switch (positionIndex[TYPE::BICYCLE])
	{
	case POSITION::POP:
		if (moveValue > 0.01f) { moveValue -= 0.01f; }

		sprite[TYPE::BICYCLE].setPosition2(D3DXVECTOR3(spritePosition.x, spritePosition.y - moveValue, spritePosition.z));
		sprite[TYPE::BICYCLE].setVertex();

		if (spritePosition.y <= POSITION_Y_MOVE_1)
		{
			moveFlag = !moveFlag;
			positionIndex[TYPE::BICYCLE]++;
			moveValue = INITIAL_MOVE_VALUE;
		}
		break;
	case POSITION::MOVE_01:
		if (moveValue > 0.01f) { moveValue -= 0.01f; }

		sprite[TYPE::BICYCLE].setPosition2(D3DXVECTOR3(spritePosition.x, spritePosition.y - moveValue, spritePosition.z));
		sprite[TYPE::BICYCLE].setVertex();

		if (spritePosition.y <= POSITION_Y_MOVE_2)
		{
			moveFlag = !moveFlag;
			positionIndex[TYPE::BICYCLE]++;
			moveValue = INITIAL_MOVE_VALUE;
		}
		break;
	case POSITION::MOVE_02:
		if (moveValue > 0.01f) { moveValue -= 0.01f; }

		sprite[TYPE::BICYCLE].setPosition2(D3DXVECTOR3(spritePosition.x, spritePosition.y - moveValue, spritePosition.z));
		sprite[TYPE::BICYCLE].setVertex();

		if (spritePosition.y <= POSITION_Y_CLOSE)
		{
			moveFlag = !moveFlag;
			positionIndex[TYPE::BICYCLE]++;
			moveValue = INITIAL_MOVE_VALUE;
		}
		break;
	case POSITION::CLOSE:
		break;
	default:
		break;
	}

	return;
}
//======================================================================================================================================================
// render
// 描画
//======================================================================================================================================================
void UIRecursion::render(LPDIRECT3DDEVICE9 _device)
{
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		sprite[i].render(_device);
	}

	return;
}