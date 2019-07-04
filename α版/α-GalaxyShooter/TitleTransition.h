//=============================================================================
// タイトル遷移画像描画処理 [TitleTransition.h]
//
//=============================================================================
#pragma once
#include "Sprite.h"
#include "Input.h"
#include "AbstractScene.h"

#define TITLE_TRANS_COLOR		(D3DCOLOR_RGBA(255, 255, 255, 255))	// タイトル遷移画像の色
//*****************************************************************************
// クラス定義
//*****************************************************************************
class TitleTransition :public Sprite
{
private:
	// Data
	int playerNumber;											// プレイヤー番号
	static int cntUI;											// インスタンスの数を数える
	static LPDIRECT3DTEXTURE9 titleTransTex;					// タイトル遷移テクスチャ
	Sprite titleTrans;											// タイトル遷移画像
public:
	TitleTransition(void);
	~TitleTransition(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
};

