//============================================================================================================================================
// Document
//============================================================================================================================================
// UICountDown.h
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/09/10
//============================================================================================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//============================================================================================================================================
// NameSpace
// 名前空間
//============================================================================================================================================
namespace uiCountDownNS
{
	const int WIDTH_COUNT_DOWN = (260);												//	幅
	const int HEIGHT_COUNT_DOWN = (260);											//	高さ
	const float POSITION_X_PLAYER_1 = (WINDOW_WIDTH / 4);							//	座標 x ( Player1 )
	const float POSITION_X_PLAYER_2 = (POSITION_X_PLAYER_1 + (WINDOW_WIDTH / 2));	//	座標 x ( Player2 )
	const float POSITION_Y = (WINDOW_HEIGHT / 2);									//	座標 y

	enum TYPE
	{
		GO,
		ONE,
		TWO,
		THREE,
		TYPE_MAX
	};
	enum PLAYER_TYPE
	{
		PLAYER_1,
		PLAYER_2,
		PLAYER_TYPE_MAX,
	};
}
//============================================================================================================================================
// Class
// クラス
//============================================================================================================================================
class UICountDown
{
private:
	static int instanceIndex;											//	インスタンスインデックス
	static LPDIRECT3DTEXTURE9 texture[uiCountDownNS::TYPE::TYPE_MAX];	//	テクスチャ
	Sprite sprite[uiCountDownNS::TYPE::TYPE_MAX];						//	スプライト
	int alpha;															//	アルファ値
public:
	UICountDown(void);
	~UICountDown(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 _device, int _playerIndex, TextureLoader* _textureLoader);
	void initializeSprite(LPDIRECT3DDEVICE9 _device, int _playerIndex, int _index);
	void release(void);
	void update(bool _startFlag);
	void updateFadeOut(void);
	void render(LPDIRECT3DDEVICE9 _device, int _renderIndex);
};