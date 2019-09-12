//============================================================================================================================================
// Document
//============================================================================================================================================
// UIChingin.cpp
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/08/01
//============================================================================================================================================
#include "UIChingin.h"
//============================================================================================================================================
// Using Declaration
// using宣言
//============================================================================================================================================
using namespace uiChinginNS;
//============================================================================================================================================
// Global Variable
// グローバル変数
//============================================================================================================================================
int UIChingin::instanceIndex = 0;		//	インスタンスインデックス
LPDIRECT3DTEXTURE9 UIChingin::texture;	//	テクスチャ
//============================================================================================================================================
// Constructor
// コンストラクタ
//============================================================================================================================================
UIChingin::UIChingin(void)
{
	// インスタンスインデックスを加算
	instanceIndex++;

	// テクスチャのクリア
	texture = NULL;

	return;
}
//============================================================================================================================================
// Destructor
// デストラクタ
//============================================================================================================================================
UIChingin::~UIChingin(void)
{
	// 解放
	release();

	return;
}
//============================================================================================================================================
// initialize
// 初期化
//============================================================================================================================================
HRESULT UIChingin::initialize(LPDIRECT3DDEVICE9 _device, int _playerIndex, TextureLoader* _textureLoader, TextManager* _textManager)
{
	// テキストマネージャ
	textManager = _textManager;

	// ディレクトリ設定
	setVisualDirectory();

	// テクスチャ読み込み
	texture = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::UI_PLAY_TIME_CHINGIN);

	// スプライト初期化
	sprite.initialize
	(
		_device,
		texture,														//	テクスチャ
		spriteNS::CENTER,												//	原点
		WIDTH,															//	横幅
		HEIGHT,															//	高さ
		D3DXVECTOR3														//	座標
		(
			!_playerIndex ? POSITION_X_PLAYER_1 : POSITION_X_PLAYER_2,	//	座標 x
			POSITION_Y,													//	座標 y
			0.0f														//	座標 z
		),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),									//	回転
		D3DCOLOR_RGBA(255, 255, 255, 255)								//	色
	);

	return S_OK;
}
//============================================================================================================================================
// release
// 解放
//============================================================================================================================================
void UIChingin::release(void)
{
	// スプライトのクリア
	sprite.setTexture(NULL);

	// インスタンスインデックスを減算
	instanceIndex--;

	return;
}
//============================================================================================================================================
// render
// 描画
//============================================================================================================================================
void UIChingin::render(LPDIRECT3DDEVICE9 _device, float _time, int _chingin,int playerID)
{
	// UI背景
	sprite.render(_device);
	switch (playerID)
	{
	case playerNS::PLAYER1:
		// テキスト
		textManager->text[textManagerNS::TYPE::NEW_RODIN_GAME_TIME]->print(POSITION_X_PLAYER_1 - 165.0f, POSITION_Y - 25.0f, "SCORE");
		// ゲーム時間が半分（２分）を切ったら、チンギンを隠す（表示を「???」に変更）
		if (_time > gameMasterNS::GAME_TIME / 2.0f)
		{
			textManager->text[textManagerNS::TYPE::NEW_RODIN_GAME_TIME]->print(POSITION_X_PLAYER_1 - 30.0f, POSITION_Y - 25.0f, "%05d", _chingin);
		}
		else {
			textManager->text[textManagerNS::TYPE::NEW_RODIN_GAME_TIME]->print(POSITION_X_PLAYER_1 - 30.0f, POSITION_Y - 25.0f, "?????");
		}
		break;
	case playerNS::PLAYER2:
		// テキスト
		textManager->text[textManagerNS::TYPE::NEW_RODIN_GAME_TIME]->print(POSITION_X_PLAYER_2 - 165.0f, POSITION_Y - 25.0f, "SCORE");
		// ゲーム時間が半分（２分）を切ったら、チンギンを隠す（表示を「???」に変更）
		if (_time > gameMasterNS::GAME_TIME / 2.0f)
		{
			textManager->text[textManagerNS::TYPE::NEW_RODIN_GAME_TIME]->print(POSITION_X_PLAYER_2 - 30.0f, POSITION_Y - 25.0f, "%05d", _chingin);
		}
		else {
			textManager->text[textManagerNS::TYPE::NEW_RODIN_GAME_TIME]->print(POSITION_X_PLAYER_2 - 30.0f, POSITION_Y - 25.0f, "?????");
		}
		break;
	}
}