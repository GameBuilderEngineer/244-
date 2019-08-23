//=============================================================================
// 賃金数表示処理 [ChinginCnt.cpp]
// 制作者 飯塚春輝
//=============================================================================
#include "ChinginCnt.h"
//*****************************************************************************
// 定数
//*****************************************************************************
#ifdef _DEBUG
const static float		CHINGIN_CNT_POSITION_X = 150.0f;		// 賃金数X座標
const static float		CHINGIN_CNT_POSITION_Y = 300.0f;		// 賃金数Y座標
const static float		CHINGIN2_CNT_POSITION_X = 620.0f;		// 賃金数X座標2
const static float		CHINGIN2_CNT_POSITION_Y = 300.0f;		// 賃金数Y座標2
#else
const static float		CHINGIN_CNT_POSITION_X = 300.0f;	// リリース時賃金数X座標
const static float		CHINGIN_CNT_POSITION_Y = 600.0f;	// リリース時賃金数Y座標
const static float		CHINGIN2_CNT_POSITION_X = 1240.0f;	// リリース時賃金数X座標2
const static float		CHINGIN2_CNT_POSITION_Y = 600.0f;	// リリース時賃金数Y座標2
#endif 
//*****************************************************************************
// グローバル変数
//*****************************************************************************
//=============================================================================
// コンストラクタ
//=============================================================================
ChinginCnt::ChinginCnt(void)
{
}
//=============================================================================
// デストラクタ
//=============================================================================
ChinginCnt::~ChinginCnt(void)
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT ChinginCnt::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader, TextManager* _textManager)
{
	// テキストマネージャ
	textManager = _textManager;
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void ChinginCnt::uninitialize(void)
{
}
//=============================================================================
// 更新処理
//=============================================================================
void ChinginCnt::update(void)
{
}
//=============================================================================
// 描画処理
//=============================================================================
void ChinginCnt::render(LPDIRECT3DDEVICE9 device, float _chinginCnt, float _chinginCnt2)
{
	// 賃金数描画
	textManager->text[textManagerNS::TYPE::NEW_RODIN_GAME_TIME]->print(CHINGIN_CNT_POSITION_X, CHINGIN_CNT_POSITION_Y, "★ %.0f", _chinginCnt);

	// 賃金数描画2
	textManager->text[textManagerNS::TYPE::NEW_RODIN_GAME_TIME]->print(CHINGIN2_CNT_POSITION_X, CHINGIN2_CNT_POSITION_Y, "★ %.0f", _chinginCnt2);

}