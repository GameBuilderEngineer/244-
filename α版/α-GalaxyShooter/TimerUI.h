//=============================================================================
// タイマーUI処理 [TimerUI.h]
//
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class TimerUI :public Sprite {

private:
	// Data
	int playerNumber;								// プレイヤー番号
	static int cntUI;								// インスタンスの数を数える
	static LPDIRECT3DTEXTURE9 timerTexture;			// タイマーテクスチャ

public:
	// Method
	TimerUI(void);
	~TimerUI(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
};

