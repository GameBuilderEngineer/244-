//===================================================================================================================================
//【Base.h】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/05/16
// [更新日]2019/08/07
//===================================================================================================================================
#pragma once
#include <stdio.h>
#include <crtdbg.h>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dsound.h>

//必要なライブラリファイルのロード
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dsound.lib")

//警告非表示
#pragma warning(disable:4305)
#pragma warning(disable:4996)
#pragma warning(disable:4018)
#pragma warning(disable:4111)
//マクロ定義
#ifdef _DEBUG
#define APP_NAME (LPSTR)"Galaxy Shooter ver.α-Debug-"
#define DEBUG_NAME (LPSTR)"DebugWindow"
#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540
#define   new                   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define   malloc(s)             _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   calloc(c, s)          _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   realloc(p, s)         _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _recalloc(p, c, s)    _recalloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _expand(p, s)         _expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define APP_NAME (LPSTR)"Galaxy Shooter ver.α"
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#endif // _DEBUG
#define SAFE_DELETE(p) {if(p){delete(p);(p)=NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p){delete[](p);(p)=NULL;}}
#define SAFE_RELEASE(p) {if(p){(p)->Release();(p)=NULL;}}
#define MFAIL(code,string) if(FAILED(code)){MessageBox(0,string,"error",MB_OK);return E_FAIL;}
#define MFALSE(code,string) if(!(code)) {MessageBox(0,string,"error",MB_OK);return E_FAIL;}
#define MSG(text) MessageBox(0,text,0,MB_OK);

struct Vertex3D
{
	D3DXVECTOR3 coord;
};
struct Vertex2D
{
	D3DXVECTOR2 coord;
};
struct UV
{
	D3DXVECTOR2 coord;
};
struct Line
{
	D3DXVECTOR3 start;
	D3DXVECTOR3 end;
};

class Base
{
public:
	//姿勢制御
	static void postureControl(D3DXQUATERNION* quaternion, D3DXVECTOR3 currentDirection, D3DXVECTOR3 nextDirection, float t);
	//任意軸線型補間回転
	static void anyAxisRotationSlerp(D3DXQUATERNION* quaternion, D3DXVECTOR3 axis, float radian, float t);
	//任意軸回転
	static void anyAxisRotation(D3DXQUATERNION* quaternion,D3DXVECTOR3 axis, float degree);
	//二つのベクトルのなす角を計算
	static bool formedRadianAngle(float* out, D3DXVECTOR3 v1, D3DXVECTOR3 v2);
	//スリップ関数(入射ベクトルLのベクトルNに反するベクトル成分を打ち消す。）
	D3DXVECTOR3 slip(D3DXVECTOR3 L, D3DXVECTOR3 N);
	//２つの位置ベクトル間の距離を計算する
	float between2VectorLength(D3DXVECTOR3 position1, D3DXVECTOR3 position2);
	//２つの位置ベクトル間の距離の計算に加え、
	//位置１から位置２に向かう（1→2）ベクトルを作成する(ノルム1)
	float between2VectorDirection(D3DXVECTOR3* out, D3DXVECTOR3 position1, D3DXVECTOR3 position2);
	//頂点バッファへのコピー
	void copyVertexBuffer(unsigned size, void *sorce, IDirect3DVertexBuffer9 *buffer);
	//ある点との線分上で最も近い点を求める
	D3DXVECTOR3 nearestPointOnLine(D3DXVECTOR3 start,D3DXVECTOR3 end,D3DXVECTOR3 point);
};

//プロトタイプ宣言
void initializeDirectory(char* root);
void setRootDirectory();
void setDataDirectory();
void setVisualDirectory();
void setShaderDirectory();
void setSoundDirectory();