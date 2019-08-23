//=============================================================================
// タイトル描画ヘッダー [Title2D.h]
// 制作者 飯塚春輝
//=============================================================================
#pragma once
#include "AbstractScene.h"
#include "Sprite.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TITLE2D_COLOR		(D3DCOLOR_RGBA(255, 255, 255,255))	// タイトルの色
//*****************************************************************************
// クラス定義
//*****************************************************************************
class Title2D :public Sprite
{
private:
	// Data
	int playerNumber;								// プレイヤー番号
	static int cntUI;								// インスタンスの数を数える
	static LPDIRECT3DTEXTURE9 textureTitle2D;		// テクスチャ

public:
	Title2D(void);
	~Title2D(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
};

