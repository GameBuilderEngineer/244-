//=============================================================================
// SPのUI処理 [SkillPointUI.h]
//
// Author : HAL東京昼間部 2年制ゲーム学科 GP12A332 32 中込和輝
// 作成日 : 2019/6/9
//=============================================================================
#pragma once
#include "Sprite.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class SkillPointUI {
private:
	// Data
	int playerNumber;								// プレイヤー番号
	static int cntUI;								// インスタンスの数を数える
	static LPDIRECT3DTEXTURE9 textureGaugeBase;		// テクスチャ１
	static LPDIRECT3DTEXTURE9 textureGaugeBar;		// テクスチャ２
	static LPDIRECT3DTEXTURE9 textureGaugeCover;	// テクスチャ３
	Sprite gaugeBase;								// ゲージベース
	Sprite gaugeBar;								// ゲージバー
	Sprite gaugeCover;								// ゲージカバー

public:
	// Method
	SkillPointUI(void);
	~SkillPointUI(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber);	
	void uninitialize(void);
	void update(int sp, int spMax);
	void render(LPDIRECT3DDEVICE9 device);
};
