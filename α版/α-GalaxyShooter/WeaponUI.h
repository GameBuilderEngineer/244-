//=============================================================================
// 現在の武器UI処理 [WeaponUI.h]
//
// Author : HAL東京昼間部 2年制ゲーム学科 GP12A332 32 中込和輝
// 作成日 : 2019/6/9
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class WeaponUI :public Sprite{
	// どういうUIになるか分からないから今はただのスプライト

private:
	// Data
	int playerNumber;								// プレイヤー番号
	static int cntUI;								// インスタンスの数を数える
	static LPDIRECT3DTEXTURE9 buffTexture;			// テクスチャ

public:
	// Method
	WeaponUI(void);
	~WeaponUI(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
};
