//=============================================================================
// SelectCharacter描画処理 [SelectCharacter.h]
//
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"

#define DEFAULT_COLOR			(D3DCOLOR_RGBA(255, 255, 255, 255))	// セレクトの色
//*****************************************************************************
// クラス定義
//*****************************************************************************
class SelectCharacter2D :public Sprite
{
private:
	// Data
	int playerNumber;									// プレイヤー番号
	static int cntUI;									// インスタンスの数を数える
	static LPDIRECT3DTEXTURE9 SelectBgTexture;			// セレクトBGテクスチャ
	static LPDIRECT3DTEXTURE9 SelectPlayerTexture;		// セレクトプレイヤーテクスチャ
	static LPDIRECT3DTEXTURE9 SelectPlayer2Texture;		// セレクトプレイヤー2テクスチャ
	static LPDIRECT3DTEXTURE9 Select2PlayerTexture;		// セレクトプレイヤーテクスチャ
	static LPDIRECT3DTEXTURE9 Select2Player2Texture;	// セレクトプレイヤー2テクスチャ
	static LPDIRECT3DTEXTURE9 selectPlayerBGTexture;	// セレクトプレイヤーBGテクスチャ

	Sprite selectBG;
	Sprite selectPlayer;
	Sprite selectPlayer2;
	Sprite select2Player;
	Sprite select2Player2;
	Sprite charaSelectBG;

public:
	SelectCharacter2D(void);
	~SelectCharacter2D(void);

	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device, int selectNo, int select2No);

};

