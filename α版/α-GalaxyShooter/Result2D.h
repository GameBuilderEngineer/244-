//=============================================================================
// リザルト描画ヘッダー [Result2D.h]
// 制作者 飯塚春輝
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define RESULT2D_COLOR	(D3DCOLOR_RGBA(255, 255, 255, 255))	// リザルト2Dの色
//*****************************************************************************
// クラス定義
//*****************************************************************************
class Result2D :public Sprite
{
private:
	// Data
	int playerNumber;								// プレイヤー番号
	static int cntUI;								// インスタンスの数を数える
	static LPDIRECT3DTEXTURE9 result2DTexture;		// テクスチャ

public:
	Result2D(void);
	~Result2D(void);

	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
};

