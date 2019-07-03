//=============================================================================
// キーボード操作説明処理 [KeyOpe.h]
//
//=============================================================================
#pragma once
#include "Sprite.h"

#define KEY_OPE_COLOR		(D3DCOLOR_RGBA(255, 255, 255, 255))			// キーボード操作説明の色
//*****************************************************************************
// クラス定義
//*****************************************************************************
class KeyOpe :public Sprite
{

private:
	// Data
	int playerNumber;								// プレイヤー番号
	static int cntUI;								// インスタンスの数を数える
	static LPDIRECT3DTEXTURE9 textureKeyOpe;		// キーボード操作説明テクスチャ
	Sprite keyOpe;									// キーボード操作説明

public:
	KeyOpe(void);
	~KeyOpe(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
};

