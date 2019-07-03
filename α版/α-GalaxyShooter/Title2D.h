//=============================================================================
// Title描画処理 [Title2D.h]
//
//=============================================================================
#pragma once
#include "Sprite.h"
#include "Input.h"


#define TITLE2D_COLOR		(D3DCOLOR_RGBA(255, 255, 255, 255))	// タイトルの色
#define CNT_TITLE_MAX		(4)									// 選択UI上限値
#define CNT_TITLE_START		(322)								// 選択UIスタート値
#define CNT_TITLE_TUTORIAL	(390)								// 選択UIチュートリアル値
#define CNT_TITLE_OPERATION	(458)								// 選択UI操作方法値
#define CNT_TITLE_CREDIT	(522)								// 選択UIクレジット値
#define CNT_TITLE_END		(590)								// 選択UI終了値

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Title2D :public Sprite
{
private:
	// Data
	int playerNumber;											// プレイヤー番号
	static int cntUI;											// インスタンスの数を数える
	static LPDIRECT3DTEXTURE9 titleTexture2D;					// タイトル2Dテクスチャ
	static LPDIRECT3DTEXTURE9 choiceTexture;					// 選択画像
	Sprite title2D;												// タイトル2D
	Sprite choice;												// 選択画像
public:
	Title2D(void);
	~Title2D(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
	void titleUImove(void);										// 選択UI移動処理
	int	cntTitle;												// 選択UI位置
};

