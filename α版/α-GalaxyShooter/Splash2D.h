//=============================================================================
// スプラッシュ描画ヘッダー [Splash2D.h]
// 制作者 飯塚春輝
//=============================================================================
#pragma once
#include "AbstractScene.h"
#include "Sprite.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SPLASH2D_COLOR		(D3DCOLOR_RGBA(255, 255, 255,alphaColor))	// スプラッシュの色
#define SPLASH_ALPHA_MAX	(255)										// スプラッシュ最大アルファ値
#define SPLASH_TIME			(200)										// スプラッシュ消滅時間
//*****************************************************************************
// クラス定義
//*****************************************************************************
class Splash2D :public Sprite
{
private:
	// Data
	int playerNumber;								// プレイヤー番号
	static int cntUI;								// インスタンスの数を数える
	static LPDIRECT3DTEXTURE9 textureSplash2D;		// テクスチャ

public:
	Splash2D(void);
	~Splash2D(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber,TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
	void fade(void);								// フェード処理
	void fadein(void);								// フェードイン
	void fadeout(void);								// フェードアウト
	bool fadeon;									// フェードフラグ
	bool gotitle;									// タイトル遷移フラグ
};

