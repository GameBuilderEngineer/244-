//=============================================================================
// チュートリアル描画ヘッダー [Tutorial2D.h]
// 制作者 飯塚春輝
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TUTORIAL2D_COLOR		(D3DCOLOR_RGBA(255, 255, 255, 255))	// チュートリアルの色
//*****************************************************************************
// クラス定義
//*****************************************************************************
class Tutorial2D :public Sprite
{
private:

	Sprite tuto2;
	Sprite tuto3;
	Sprite tuto4;

	// Data
	int playerNumber;								// プレイヤー番号
	static int cntUI;								// インスタンスの数を数える
	static LPDIRECT3DTEXTURE9 textureTutorial2D;	// テクスチャ1
	static LPDIRECT3DTEXTURE9 textureTutorial2D2;	// テクスチャ2
	static LPDIRECT3DTEXTURE9 textureTutorial2D3;	// テクスチャ3
	static LPDIRECT3DTEXTURE9 textureTutorial2D4;	// テクスチャ4

public:
	Tutorial2D(void);
	~Tutorial2D(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
	int next;

};

