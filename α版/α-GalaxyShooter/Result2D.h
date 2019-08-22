//=============================================================================
// リザルト描画ヘッダー [Result2D.h]
// 制作者 飯塚春輝
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define RESULT2D_COLOR	(D3DCOLOR_RGBA(255, 255, 255, 255))	// リザルト2Dの色
//*****************************************************************************
// クラス定義
//*****************************************************************************
class Result2D :public Sprite
{
private:
	// Data
	int playerNumber;											// プレイヤー番号
	static int cntUI;											// インスタンスの数を数える
	static LPDIRECT3DTEXTURE9 result2DTexture;					// リザルト2Dテクスチャ
	static LPDIRECT3DTEXTURE9 resultPlayerTexture;				// リザルトプレイヤーテクスチャ
	static LPDIRECT3DTEXTURE9 resultPlayer2Texture;				// リザルトプレイヤー2テクスチャ
	static LPDIRECT3DTEXTURE9 result2PlayerTexture;				// リザルト2プレイヤーテクスチャ
	static LPDIRECT3DTEXTURE9 result2Player2Texture;			// リザルト2プレイヤー2テクスチャ
	static LPDIRECT3DTEXTURE9 resultPlayerBGTexture;			// リザルトプレイヤーBGテクスチャ
	static LPDIRECT3DTEXTURE9 resultPlayerNumberTexture;		// リザルトプレイヤーナンバーテクスチャ
	static LPDIRECT3DTEXTURE9 resultPlayer2NumberTexture;		// リザルトプレイヤー2ナンバーテクスチャ
	static LPDIRECT3DTEXTURE9 resultJadgeTexture;				// リザルトジャッジテクスチャ
	static LPDIRECT3DTEXTURE9 resultJadge2Texture;				// リザルトジャッジ2テクスチャ
public:
	Result2D(void);
	~Result2D(void);
	Sprite resultPlayer;										// リザルトプレイヤー
	Sprite resultPlayer2;										// リザルトプレイヤー2
	Sprite result2Player;										// リザルト2プレイヤー
	Sprite result2Player2;										// リザルト2プレイヤー2
	Sprite charaResultBG;										// キャラクターリザルトBG
	Sprite resultPlayerNumber;									// リザルトプレイヤーナンバー
	Sprite resultPlayer2Number;									// リザルトプレイヤー2ナンバー
	Sprite resultJadge;											// リザルトジャッジ
	Sprite resultJadge2;										// リザルトジャッジ2

	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device, int resultNo, int result2No);
};

