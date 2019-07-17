//=============================================================================
// Pose描画処理 [Pose2D.h]
//
//=============================================================================
#pragma once
#include "AbstractScene.h"
#include "Sprite.h"

#define POSE2D_COLOR		(D3DCOLOR_RGBA(255, 255, 255, 255))	// ポーズの色
//*****************************************************************************
// クラス定義
//*****************************************************************************
class Pose2D :public Sprite
{

private:
	// Data
	int playerNumber;								// プレイヤー番号
	static int cntUI;								// インスタンスの数を数える
	static LPDIRECT3DTEXTURE9 texturePose2D;		// テクスチャ

public:
	Pose2D(void);
	~Pose2D(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
};

