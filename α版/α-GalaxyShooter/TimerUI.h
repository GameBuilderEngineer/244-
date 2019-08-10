//=============================================================================
// タイマーUIヘッダー [TimerUI.h]
// 制作者 飯塚春輝
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TIMER_UI_COLOR	(D3DCOLOR_RGBA(255, 255, 255, 255))	// タイマーの色
//*****************************************************************************
// クラス定義
//*****************************************************************************
class TimerUI :public Sprite
{
private:
	// Data
	int playerNumber;								// プレイヤー番号
	static int cntUI;								// インスタンスの数を数える
	static LPDIRECT3DTEXTURE9 timerTexture;			// タイマーテクスチャ
	TextManager* textManager;						//	テキストマネージャ
public:
	// Method
	TimerUI(void);
	~TimerUI(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader, TextManager* _textManager);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device, float _uiTimer);
};

