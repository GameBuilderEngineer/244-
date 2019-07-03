//=============================================================================
// Credit描画処理 [Credit2D.h]
//
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"


#define CREDIT2D_COLOR		(D3DCOLOR_RGBA(255, 255, 255, 255))			// クレジットの色
//*****************************************************************************
// クラス定義
//*****************************************************************************
class Credit2D :public Sprite
{

private:
	// Data
	int playerNumber;								// プレイヤー番号
	static int cntUI;								// インスタンスの数を数える
	static LPDIRECT3DTEXTURE9 textureCredit2D;		// テクスチャ１
	Sprite credit2D;								// クレジット2D

public:
	Credit2D(void);
	~Credit2D(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
};

