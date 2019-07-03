//=============================================================================
// Tutorial描画処理 [Tutorial2D.h]
//
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"


#define TUTORIAL2D_COLOR		(D3DCOLOR_RGBA(255, 255, 255, 255))			// チュートリアルの色
//*****************************************************************************
// クラス定義
//*****************************************************************************
class Tutorial2D :public Sprite
{

private:
	// Data
	int playerNumber;								// プレイヤー番号
	static int cntUI;								// インスタンスの数を数える
	static LPDIRECT3DTEXTURE9 textureTutorial2D;	// テクスチャ１
	Sprite tutorial2D;								// チュートリアル2D

public:
	Tutorial2D(void);
	~Tutorial2D(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
};

