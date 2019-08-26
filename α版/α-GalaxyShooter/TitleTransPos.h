//=============================================================================
// タイトル選択位置描画ヘッダー [TitleTransPos.h]
// 制作者 飯塚春輝
//=============================================================================
#pragma once
#include "TitleTransition.h"
#include "AbstractScene.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TITLE_TRANSPOS_COLOR	(D3DCOLOR_RGBA(255, 255, 255, 255))			// タイトル選択位置の色
#define CNT_TITLE_MAX			(4)											// タイトル選択位置上限値
#define CNT_TITLE_START			(235)										// タイトル選択位置スタート値
#define CNT_TITLE_TUTORIAL		(285)										// タイトル選択位置チュートリアル値
#define CNT_TITLE_OPERATION		(335)										// タイトル選択位置操作方法値
#define CNT_TITLE_CREDIT		(385)										// タイトル選択位置クレジット値
#define CNT_TITLE_END			(435)										// タイトル選択位置終了値
#define CNT_RELEASE_START		(475)										// リリース時タイトル選択位置スタート値
#define CNT_RELEASE_TUTORIAL	(575)										// リリース時タイトル選択位置チュートリアル値
#define CNT_RELEASE_OPERATION	(675)										// リリース時タイトル選択位置操作方法値
#define CNT_RELEASE_CREDIT		(775)										// リリース時タイトル選択位置クレジット値
#define CNT_RELEASE_END			(875)										// リリース時タイトル選択位置終了値
//*****************************************************************************
// クラス定義
//*****************************************************************************
class TitleTransPos :public TitleTransition
{
private:
	// Data
	int playerNumber;											// プレイヤー番号
	static int cntUI;											// インスタンスの数を数える
	static LPDIRECT3DTEXTURE9 titleTransPosTex;					// タイトル選択位置画像

public:
	TitleTransPos(void);
	~TitleTransPos(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
	virtual void titleTransPosMove(void);						// タイトル選択位置移動処理
};

