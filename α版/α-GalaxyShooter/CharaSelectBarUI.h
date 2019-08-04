//=============================================================================
// キャラクターセレクトバーUI処理 [CharaSelectBarUI.h]
//
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"

namespace charaSelectBarUINS
{
	enum {
		PLAYER1,
		PLAYER2,
		NUM_PLAYER,
	};
}

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CharaSelectBarUI :public Sprite {

private:
	// Data
	int playerNumber;									// プレイヤー番号
	static int cntUI;									// インスタンスの数を数える
	static LPDIRECT3DTEXTURE9 selectBarLightTexture;	// セレクトバーライトテクスチャ
	static LPDIRECT3DTEXTURE9 selectBarLightTexture2;	// セレクトバーライトテクスチャ2
	static LPDIRECT3DTEXTURE9 selectNoTexture;			// セレクトナンバーテクスチャ
	static LPDIRECT3DTEXTURE9 selectNoTexture2;			// セレクトナンバーテクスチャ2
	static LPDIRECT3DTEXTURE9 selectCursorTexture;		// セレクトカーソルテクスチャ
	static LPDIRECT3DTEXTURE9 selectCursorTexture2;		// セレクトカーソルテクスチャ2
	static LPDIRECT3DTEXTURE9 selectPlayerLogoTexture;	// セレクトプレイヤーロゴテクスチャ
	static LPDIRECT3DTEXTURE9 nameEveEngTexture;		// イヴ名前英語テクスチャ
	static LPDIRECT3DTEXTURE9 nameEveEngTexture2;		// イヴ名前英語テクスチャ2
	static LPDIRECT3DTEXTURE9 nameAdamEngTexture;		// アダム名前英語テクスチャ
	static LPDIRECT3DTEXTURE9 nameAdamEngTexture2;		// アダム名前英語テクスチャ2
	static LPDIRECT3DTEXTURE9 nameEveJpTexture;			// イヴ名前日本語テクスチャ
	static LPDIRECT3DTEXTURE9 nameEveJpTexture2;		// イヴ名前日本語テクスチャ2
	static LPDIRECT3DTEXTURE9 nameAdamJpTexture;		// アダム名前日本語テクスチャ
	static LPDIRECT3DTEXTURE9 nameAdamJpTexture2;		// アダム名前日本語テクスチャ2

	Sprite charaSelectBar;
	Sprite charaSelectBar2;
	Sprite charaSelectNo;
	Sprite charaSelectNo2;
	Sprite charaSelectCursor;
	Sprite charaSelectCursor2;
	Sprite charaSelectLogo;
	Sprite nameEveEng;
	Sprite nameEveEng2;
	Sprite nameAdamEng;
	Sprite nameAdamEng2;
	Sprite nameEveJp;
	Sprite nameEveJp2;
	Sprite nameAdamJp;
	Sprite nameAdamJp2;

public:
	// Method
	CharaSelectBarUI(void);
	~CharaSelectBarUI(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device, int selectNo, int select2No);
};
