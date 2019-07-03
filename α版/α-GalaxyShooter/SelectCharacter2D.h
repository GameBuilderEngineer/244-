//=============================================================================
// SelectCharacter描画処理 [SelectCharacter.h]
//
//=============================================================================
#pragma once
#include "Sprite.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class SelectCharacter2D :public Sprite
{
private:
	// Data
	int playerNumber;								// プレイヤー番号
	static int cntUI;								// インスタンスの数を数える
	static LPDIRECT3DTEXTURE9 buffTexture;			// テクスチャ

public:
	SelectCharacter2D(void);
	~SelectCharacter2D(void);

	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);

};

