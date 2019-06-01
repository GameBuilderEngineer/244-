#pragma once
//必要なヘッダーファイルのインクルード
#include <stdio.h>
#include <windows.h>
#include <d3dx9.h>
//必要なライブラリファイルのロード
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
// シンボル定義及びマクロ
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900
#define DELTA_ANGLE 0.05f
#define SAFE_DELETE(p) { if(p) { delete (p);     (p) = NULL; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p) = NULL; } }
#define THING_AMOUNT 3

//ユーザー定義データ型
struct THING
{
	LPD3DXMESH pMesh;
	D3DMATERIAL9* pMeshMaterials;
	LPDIRECT3DTEXTURE9* pMeshTextures;
	DWORD dwNumMaterials;
	D3DXVECTOR3 vPosition;
	
	//FLOAT fYaw;

	D3DXQUATERNION qtnAttitude;
	D3DXQUATERNION quaternionMove;
	D3DXVECTOR3 vAxisZ;
	D3DXVECTOR3 vAxisY;
	D3DXVECTOR3 vAxisX;
	D3DXVECTOR3 vDir;
	D3DXMATRIX mPosition;
	D3DXMATRIX mRotation;
	D3DXMATRIX mWorld;
	D3DXVECTOR3 gravity;
	D3DXVECTOR3 normal[2];		//レイが衝突したポリゴンの法線
	float distance[2];	//レイが衝突したポリゴンとの距離


	THING()
	{
		ZeroMemory(this, sizeof(THING));
		D3DXMatrixIdentity(&mRotation);
		qtnAttitude = D3DXQUATERNION(0, 0, 0, 1);
		quaternionMove = D3DXQUATERNION(0, 0, 0, 1);
		gravity = D3DXVECTOR3(0, 0, 0);
		vAxisX = D3DXVECTOR3(1, 0, 0);
		vAxisY = D3DXVECTOR3(1, 0, 0);
		vAxisZ = D3DXVECTOR3(0, 0, 1);
	}
};
//関数プロトタイプの宣言
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT InitD3d(HWND);

VOID Render();
VOID RenderString(LPSTR, INT, INT);

HRESULT ChangeViewport(DWORD, DWORD, DWORD, DWORD);
HRESULT ViewRender(D3DXCOLOR);
D3DXVECTOR3 Slip(D3DXVECTOR3 L, D3DXVECTOR3 N);
VOID FreeDx();

// nakagomi