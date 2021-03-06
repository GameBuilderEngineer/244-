//=============================================================================
// エフェクト基本処理 [ScreenEffectBase.cpp]
// 制作者 飯塚春輝
//=============================================================================
#include "ScreenEffectBase.h"
//=============================================================================
// コンストラクタ
//=============================================================================
ScreenEffectBase::ScreenEffectBase()
{
}
//=============================================================================
// デストラクタ
//=============================================================================
ScreenEffectBase::~ScreenEffectBase()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
void ScreenEffectBase::initialize()
{
	// エフェクトを使用していない
	isActive = false;

	// エフェクト生存時間
	settingFrame = 0;
}
//=============================================================================
// 終了処理
//=============================================================================
void ScreenEffectBase::uninitialize(void)
{
}
//=============================================================================
// 描画処理
//=============================================================================
void ScreenEffectBase::render()
{
}
//=============================================================================
// エフェクト使用
//=============================================================================
void ScreenEffectBase::activate(int second)
{
	// エフェクト有効
	isActive = true;

	// エフェクト生存時間
	settingFrame = second;
}
//=============================================================================
// エフェクト削除
//=============================================================================
void ScreenEffectBase::inactivate(void)
{
	// エフェクト不使用
	isActive = false;
}


