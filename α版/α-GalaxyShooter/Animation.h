//============================================================================================================================================
// Document
//============================================================================================================================================
// Animation.h
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/09/03
//============================================================================================================================================
#pragma once
#include "Base.h"
#include "AllocateHierarchy.h"
//============================================================================================================================================
// NameSpace
// 名前空間
//============================================================================================================================================
namespace animationNS
{
	enum TYPE
	{
		IDLE,
		//WALK,
		TYPE_MAX,
	};
}
//============================================================================================================================================
// Structure
// 構造体
//============================================================================================================================================
struct AnimationManager
{
	ID3DXAnimationSet* animationSet;	//	アニメーションセット
	LPCSTR animationSetName;			//	アニメーションセットの名前
	float shiftTime;					//	シフトするのに必要な時間
	float weightTime;					//	現在のウェイト時間
};
struct AnimationFlag
{
	bool animationPlaying = NULL;	//	アニメーションの再生フラグ
	bool animationEnd;				//	アニメーションの終了フラグ
	bool moveStop;					//	移動停止フラグ
};
struct Animation
{
	AnimationManager* animationManager;				//	アニメーションセットの管理
	LPD3DXANIMATIONCONTROLLER animationController;	//	アニメーションコントローラ
	AllocateHierarchy* allocateHierarchy;			//	Xファイルの情報
	LPD3DXFRAME rootFrame;							//	ルートフレーム( フレーム階層構造の最上位フレーム )
	AnimationFlag flag;								//	アニメーションフラグ
	UINT animationIdCurrent;						//	現在、再生しているアニメーションID
	UINT animationIdPast;							//	過去、再生していたアニメーションID
	int animationSetMax;							//	アニメーションセットの最大数
	int keyFrameCount;								//	コールバック( Key_Frame )の処理数
	HRESULT(*initializeAnimation)(Animation* _animation, LPCSTR _setName, int _setNo);
	void(*releaseAnimation)(Animation* _animation);
	void(*updateAnimation)(Animation* _animation, float _time);
	void(*renderAnimation)(LPDIRECT3DDEVICE9 _device, Animation* _animation, LPD3DXMATRIX _worldMatrix);
	void(*switchingAnimation)(Animation* _animation, UINT _animationIdentification, float _playSpeed);
	void(*setShiftTimeAnimation)(Animation* _animation, UINT _animationIdentification, float _interval);
};
struct CallBackAnimation : public ID3DXAnimationCallbackHandler
{
	Animation* animation;														//	アニメーション
	LPCSTR setName;																//	セット名
	int status;																	//	ステータス
	HRESULT CALLBACK HandleCallback(THIS_ UINT Track, LPVOID pCallbackData);	//	コールバックハンドル
};
//============================================================================================================================================
// Prototype Declaration
// プロトタイプ宣言
//============================================================================================================================================
HRESULT initializeAnimation(Animation* _animation, LPCSTR _setName, int _setNo);
void releaseAnimation(Animation* _animation);
void updateAnimation(Animation* _animation, float _time);
void updateFrameMatrix(LPDIRECT3DDEVICE9* _device, LPD3DXFRAME _baseFrame, LPD3DXMATRIX _parentMatrix);
void renderAnimation(LPDIRECT3DDEVICE9 _device, Animation* _animation, LPD3DXMATRIX _worldMatrix);
void renderFrame(LPDIRECT3DDEVICE9 _device, Animation* _animation, LPD3DXFRAME _frame);
void renderMeshContainer(LPDIRECT3DDEVICE9 _device, LPD3DXMESHCONTAINER _baseMeshContainer, LPD3DXFRAME _baseFrame);
void switchingAnimation(Animation* _animation, UINT _animationIdentification, float _playSpeed);
Animation* createObjectAnimation(void);
HRESULT loadXFile(LPDIRECT3DDEVICE9 _device, Animation* _animation, LPCTSTR _fileName);
D3DXFRAMEDerived* searchBoneFrame(Animation* _animation, const char* _boneName, D3DXFRAME* _frame);
void setShiftTimeAnimation(Animation* _animation, UINT _animationIdentification, float _interval);
HRESULT setBoneMatrix(LPD3DXFRAME _baseFrame, LPD3DXFRAME _rootFrame);
HRESULT setCallBackKeyFrame(Animation* _animation, LPCSTR _setName);
D3DXMATRIX getBoneMatrix(Animation* _animation, const char* _boneName);