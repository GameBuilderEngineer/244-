//=============================================================================
// Operation描画処理 [Operation2D.h]
//
//=============================================================================
#pragma once
#include "Sprite.h"

#define OPERATION2D_COLOR		(D3DCOLOR_RGBA(255, 255, 255, 255))			// 操作確認の色
//*****************************************************************************
// クラス定義
//*****************************************************************************
class Operation2D :public Sprite
{

private:
	// Data
	int playerNumber;								// プレイヤー番号
	static int cntUI;								// インスタンスの数を数える
	static LPDIRECT3DTEXTURE9 textureOperation2D;	// テクスチャ１
	Sprite operation2D;								// 操作確認2D

public:
	Operation2D(void);
	~Operation2D(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
};

