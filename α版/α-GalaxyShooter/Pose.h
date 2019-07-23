//=============================================================================
// Pose描画処理 [Pose.h]
//
//=============================================================================
#pragma once
#include "AbstractScene.h"
#include "Sprite.h"

#define POSE_COLOR		(D3DCOLOR_RGBA(255, 255, 255, 255))	// スプラッシュの色
//*****************************************************************************
// クラス定義
//*****************************************************************************
class Pose :public Sprite
{

private:
	// Data
	int playerNumber;								// プレイヤー番号
	static int cntUI;								// インスタンスの数を数える
	static LPDIRECT3DTEXTURE9 texturePose;		// テクスチャ

public:
	Pose(void);
	~Pose(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
	bool poseon;									// ポーズフラグ
};

