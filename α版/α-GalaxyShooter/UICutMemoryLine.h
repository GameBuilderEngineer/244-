//============================================================================================================================================
// Document
//============================================================================================================================================
// UICutMemoryLine.h
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/08/07
//============================================================================================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//============================================================================================================================================
// NameSpace
// 名前空間
//============================================================================================================================================
namespace uiCutMemoryLineNS
{
	const int WIDTH = (960);																	//	幅
	const int HEIGHT = (100);																	//	高さ
	const float POSITION_X_PLAYER_1 = ((WINDOW_WIDTH / 2) - (uiCutMemoryLineNS::WIDTH / 2));	//	座標 x ( Player1 )
	const float POSITION_X_PLAYER_2 = (POSITION_X_PLAYER_1 + (WINDOW_WIDTH / 2));				//	座標 x ( Player2 )
	const float POSITION_Y = (WINDOW_HEIGHT / 4);												//	座標 y
}
//============================================================================================================================================
// Class
// クラス
//============================================================================================================================================
class UICutMemoryLine
{
private:
	static int instanceIndex;			//	インスタンスインデックス
	static LPDIRECT3DTEXTURE9 texture;	//	テクスチャ
	Sprite sprite;						//	スプライト
	bool renderFlag;					//	描画フラグ
public:
	UICutMemoryLine(void);
	~UICutMemoryLine(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 _device, int _playerIndex, TextureLoader* _textureLoader);
	void release(void);
	void update(D3DXVECTOR3 _playerPosition1, D3DXVECTOR3 _playerPosition2);
	void updateRenderFlag(D3DXVECTOR3 _playerPosition1, D3DXVECTOR3 _playerPosition2);
	void render(LPDIRECT3DDEVICE9 _device);
};