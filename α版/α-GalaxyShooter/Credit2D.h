//=============================================================================
// クレジット描画ヘッダー [Credit2D.h]
// 制作者 飯塚春輝
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CREDIT2D_COLOR		(D3DCOLOR_RGBA(255, 255, 255, 255))			// クレジット2Dの色
//*****************************************************************************
// クラス定義
//*****************************************************************************
class Credit2D :public Sprite
{
private:
	// Data
	int playerNumber;								// プレイヤー番号
	static int cntUI;								// インスタンスの数を数える
	static LPDIRECT3DTEXTURE9 textureCredit2D;		// テクスチャ

public:
	Credit2D(void);
	~Credit2D(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
};

