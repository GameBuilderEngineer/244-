//======================================================================================================================================================
// Document
//======================================================================================================================================================
// UIChingin.h
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/08/01
//======================================================================================================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//======================================================================================================================================================
// NameSpace
// 名前空間
//======================================================================================================================================================
namespace uiChinginNS
{
	const int WIDTH = (360);																		//	幅
	const int HEIGHT = (75);																		//	高さ
	const float POSITION_X_PLAYER_1 = (uiChinginNS::WIDTH / 2);										//	座標 x ( Player1 )
	const float POSITION_X_PLAYER_2 = (uiChinginNS::POSITION_X_PLAYER_1 + (WINDOW_WIDTH / 2.0f));	//	座標 x ( Player2 )
	const float POSITION_Y = (140.0f);																//	座標 y
}
//======================================================================================================================================================
// Class
// クラス
//======================================================================================================================================================
class UIChingin
{
private:
	static int instanceIndex;			//	インスタンスインデックス
	static LPDIRECT3DTEXTURE9 texture;	//	テクスチャ
	Sprite sprite;						//	スプライト
	TextManager* textManager;			//	テキストマネージャ
	int playerIndex;					//	プレイヤーインデックス
public:
	UIChingin(void);
	~UIChingin(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 _device, int _playerIndex, TextureLoader* _textureLoader, TextManager* _textManager);
	void release(void);
	void render(LPDIRECT3DDEVICE9 _device, float _sceneTimer, int _chingin);
};