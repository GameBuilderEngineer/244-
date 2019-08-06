//=============================================================================
// タイトル遷移画像描画処理 [TitleTransition.h]
//
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"

#define DEFAULT_COLOR	(D3DCOLOR_RGBA(255, 255, 255, 255))			// タイトル遷移位置の色
#define TITLE_GAME_POS			(235)								// ゲーム選択位置
#define TITLE_TUTORIAL_POS		(285)								// チュートリアル選択位置
#define TITLE_OPERATION_POS		(335)								// オペレーション選択位置
#define TITLE_CREDIT_POS		(385)								// クレジット選択位置
#define TITLE_GAMEEND_POS		(435)								// ゲームエンド選択位置
#define RELEASE_START_POS		(470)								// リリース時タイトル選択位置スタート値
#define RELEASE_TUTORIAL_POS	(570)								// リリース時タイトル選択位置チュートリアル値
#define RELEASE_OPERATION_POS	(670)								// リリース時タイトル選択位置操作方法値
#define RELEASE_CREDIT_POS		(870)								// リリース時タイトル選択位置クレジット値
#define RELEASE_GAMEEND_POS		(970)								// リリース時タイトル選択位置終了値
//*****************************************************************************
// クラス定義
//*****************************************************************************
class TitleTransition :public Sprite
{
private:
	// Data
	int playerNumber;											// プレイヤー番号
	static int cntUI;											// インスタンスの数を数える
	static LPDIRECT3DTEXTURE9 titleGameTex;						// ゲーム遷移テクスチャ
	static LPDIRECT3DTEXTURE9 titleTutorialTex;					// チュートリアル遷移テクスチャ
	static LPDIRECT3DTEXTURE9 titleOperationTex;				// オペレーション遷移テクスチャ
	static LPDIRECT3DTEXTURE9 titleCreditTex;					// クレジット遷移テクスチャ
	static LPDIRECT3DTEXTURE9 titleGameendTex;					// ゲームエンド遷移テクスチャ
	static LPDIRECT3DTEXTURE9 titleGameBTex;					// ゲーム遷移時テクスチャ
	static LPDIRECT3DTEXTURE9 titleTutorialBTex;				// チュートリアル遷移時テクスチャ
	static LPDIRECT3DTEXTURE9 titleOperationBTex;				// オペレーション遷移時テクスチャ
	static LPDIRECT3DTEXTURE9 titleCreditBTex;					// クレジット遷移時テクスチャ
	static LPDIRECT3DTEXTURE9 titleGameendBTex;					// ゲームエンド遷移時テクスチャ

	Sprite TitleGame;
	Sprite TitleTutorial;
	Sprite TitleOperation;
	Sprite TitleCredit;
	Sprite TitleGameend;
	Sprite TitleGameB;
	Sprite TitleTutorialB;
	Sprite TitleOperationB;
	Sprite TitleCreditB;
	Sprite TitleGameendB;
public:
	TitleTransition(void);
	~TitleTransition(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
	void titleTransBlack(LPDIRECT3DDEVICE9 device);
	int	cntTitle;											// タイトル選択位置変数

};

