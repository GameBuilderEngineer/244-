//=============================================================================
// セレクトキャラクター描画ヘッダー [SelectCharacter2D.h]
// 制作者 飯塚春輝
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SELECT2D_COLOR			(D3DCOLOR_RGBA(255, 255, 255, 255))	// セレクト2Dの色
//*****************************************************************************
// クラス定義
//*****************************************************************************
class SelectCharacter2D :public Sprite
{
private:
	// Data
	int playerNumber;									// プレイヤー番号
	static int cntUI;									// インスタンスの数を数える
	static LPDIRECT3DTEXTURE9 selectBgTexture;			// セレクトBGテクスチャ
	static LPDIRECT3DTEXTURE9 selectPlayerTexture;		// セレクトプレイヤーテクスチャ
	static LPDIRECT3DTEXTURE9 selectPlayer2Texture;		// セレクトプレイヤー2テクスチャ
	static LPDIRECT3DTEXTURE9 select2PlayerTexture;		// セレクト2プレイヤーテクスチャ
	static LPDIRECT3DTEXTURE9 select2Player2Texture;	// セレクト2プレイヤー2テクスチャ
	static LPDIRECT3DTEXTURE9 selectPlayerBGTexture;	// セレクトプレイヤーBGテクスチャ

	Sprite selectBG;									// セレクトBG
	Sprite selectPlayer;								// セレクトプレイヤー
	Sprite selectPlayer2;								// セレクトプレイヤー2
	Sprite select2Player;								// セレクト2プレイヤー
	Sprite select2Player2;								// セレクト2プレイヤー2
	Sprite charaSelectBG;								// キャラクターセレクトBG

public:
	SelectCharacter2D(void);
	~SelectCharacter2D(void);

	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device, int selectNo, int select2No);

};

