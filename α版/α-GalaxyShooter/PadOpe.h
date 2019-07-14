//=============================================================================
// パッド操作説明処理 [PadOpe.h]
//
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"

#define PAD_OPE_COLOR		(D3DCOLOR_RGBA(255, 255, 255, 255))			// パッド操作説明の色
//*****************************************************************************
// クラス定義
//*****************************************************************************
class PadOpe :public Sprite
{

private:
	// Data
	int playerNumber;								// プレイヤー番号
	static int cntUI;								// インスタンスの数を数える
	static LPDIRECT3DTEXTURE9 texturePadOpe;		// パッド操作説明テクスチャ

public:
	PadOpe(void);
	~PadOpe(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
};

