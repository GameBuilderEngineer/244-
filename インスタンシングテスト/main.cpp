#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib,"winmm.lib")

//================================================================================================
//インクルード
//================================================================================================
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "main.h"
#include "Object.h"

//================================================================================================
//定数
//================================================================================================
const char* modeStr = 0;
const char* modeStr_instancing = "Instancing";
const char* modeStr_normal = "Normal";
const int texPx = 64;					//テクスチャのピクセルサイズ
const int tipPx = 16;					//チップのピクセルサイズ
const float u = (float)tipPx / texPx;	//チップのUVサイズ
const int tipNumInTex = texPx / tipPx;	//テクスチャ内のチップの並び数
const int W = WINDOW_WIDTH / tipPx;		//スクリーン上に並べる板ポリの横数
const int H = WINDOW_HEIGHT / tipPx;	//スクリーン上に並べる板ポリの横数
const int tipNum = W * H;				//スクリーン上のチップ総数


//================================================================================================
//グローバル変数
//================================================================================================
LPDIRECT3D9 pD3d;
LPDIRECT3DDEVICE9 pDevice;
ID3DXFont *pD3DFont = 0;
LARGE_INTEGER startTime;
double lapTime = 0.0f;
int mode = 0; //0:instancing, 1:normal
Object object;

//================================================================================================
//関数プロトタイプの宣言
//================================================================================================
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);								//ウィンドウプロシージャ
HRESULT InitD3d(HWND);																//DirectX9の初期化
void initialize();																	//初期化処理
VOID Render();																		//描画処理
VOID FreeDx();																		//解放処理
void startLap();																	//
void endLap();																		//
void drawLapTime();																	//

//================================================================================================
//クラスの定義
//================================================================================================
//ノーマルモードクラス
class NormalMode {
	UV *uv;
	WorldPos* worldPos;
	IDirect3DVertexBuffer9* vtxBuf;
	IDirect3DIndexBuffer9* indexBuf;
	IDirect3DVertexDeclaration9* decl;
	ID3DXEffect* effect;
	IDirect3DTexture9* tex;
public:
	NormalMode() : uv(), worldPos(), vtxBuf(), indexBuf(), decl(), tex() {

		Vtx vtx[4] = {	//単位板ポリバッファ
			{0.0f,0.0f,0.0f,0.0f},
			{tipPx,0.0f,u,0.0f},
			{0.0f,tipPx,0.0f,u},
			{tipPx,tipPx,u,u}
		};

		uv = new UV[tipNum];	//チップUVバッファ
		for (int i = 0; i < tipNum; i++) {
			uv[i].u = u * (rand() % tipNumInTex);
			uv[i].v = u * (rand() % tipNumInTex);
		}

		worldPos = new WorldPos[tipNum]; //ワールド座標位置バッファ
		for (int w = 0; w < W; w++) {
			for (int h = 0; h < H; h++) {
				int e = h * W + w;
				worldPos[e].x = tipPx * w;
				worldPos[e].y = tipPx * h;
			}
		}

		//頂点バッファ作成
		pDevice->CreateVertexBuffer(sizeof(vtx), 0, 0, D3DPOOL_MANAGED, &vtxBuf, 0);
		copyBuf(sizeof(vtx), vtx, vtxBuf);

		//インデックスバッファ
		WORD index[6] = { 0,1,2,2,1,3 };
		pDevice->CreateIndexBuffer(sizeof(index), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuf, 0);
		void *p = 0;
		indexBuf->Lock(0, 0, &p, 0);
		memcpy(p, index, sizeof(index));
		indexBuf->Unlock();

		//頂点宣言作成
		D3DVERTEXELEMENT9 declElems[] = {
			{0,0,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},	// Locla coord
			{0,8,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0},	// UV
			D3DDECL_END()
		};

		pDevice->CreateVertexDeclaration(declElems, &decl);

		//シェーダ作成
		ID3DXBuffer* errBuf = 0;
		D3DXCreateEffectFromFileA(pDevice, "tip_normal.fx", 0, 0, 0, 0, &effect, &errBuf);
		if (errBuf) {
			const char* errMsg = (const char*)errBuf->GetBufferPointer();
			OutputDebugStringA(errMsg);
			return;
		}

		//チップテクスチャ
		D3DXCreateTextureFromFileA(pDevice, "tips.bmp", &tex);

	}

	~NormalMode() {
		delete[] uv;
		delete[] worldPos;
		vtxBuf->Release();
		indexBuf->Release();
		decl->Release();
		tex->Release();
	}

	void draw() {
		modeStr = modeStr_normal;

		// 頂点とインデックスを設定して描画
		pDevice->SetVertexDeclaration(decl);
		pDevice->SetStreamSource(0, vtxBuf, 0, sizeof(Vtx));
		effect->SetTechnique("tech");
		UINT passNum = 0;
		effect->Begin(&passNum, 0);
		effect->BeginPass(0);

		for (int i = 0; i < tipNum; i++)
		{
			effect->CommitChanges();
			effect->SetTexture("tex", tex);
			effect->SetFloat("screenW", WINDOW_WIDTH / 2);
			effect->SetFloat("screenH", WINDOW_HEIGHT / 2);
			effect->SetVector("tipUV", &D3DXVECTOR4(uv[i].u, uv[i].v, 0.0f, 0.0f));
			effect->SetVector("worldPos", &D3DXVECTOR4(worldPos[i].x, worldPos[i].y, 0.0f, 0.0f));
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
		}
		effect->EndPass();
		effect->End();
	}
};

//インスタンシングモードクラス
class InstancingMode {
	IDirect3DVertexBuffer9* vtxBuf;
	IDirect3DVertexBuffer9* uvBuf;
	IDirect3DVertexBuffer9* worldPosBuf;
	IDirect3DVertexDeclaration9* decl;
	IDirect3DIndexBuffer9* indexBuf;
	IDirect3DTexture9* tex;
	ID3DXEffect* effect;
public:
	InstancingMode() : vtxBuf(), uvBuf(), worldPosBuf(), decl(), indexBuf(), tex(), effect() {

		Vtx vtx[4] = {	//単位板ポリバッファ
			{0.0f,0.0f,0.0f,0.0f},
			{tipPx,0.0f,u,0.0f},
			{0.0f,tipPx,0.0f,u},
			{tipPx,tipPx,u,u}
		};

		UV* uv = new UV[tipNum];	//チップUVバッファ
		for (int i = 0; i < tipNum; i++) {
			uv[i].u = u * (rand() % tipNumInTex);
			uv[i].v = u * (rand() % tipNumInTex);
		}

		WorldPos* worldPos = new WorldPos[tipNum]; //ワールド座標位置バッファ
		for (int w = 0; w < W; w++) {
			for (int h = 0; h < H; h++) {
				int e = h * W + w;
				worldPos[e].x = tipPx * w;
				worldPos[e].y = tipPx * h;
			}
		}

		//頂点バッファ作成
		pDevice->CreateVertexBuffer(sizeof(vtx), 0, 0, D3DPOOL_MANAGED, &vtxBuf, 0);
		pDevice->CreateVertexBuffer(sizeof(WorldPos)*tipNum, 0, 0, D3DPOOL_MANAGED, &worldPosBuf, 0);
		pDevice->CreateVertexBuffer(sizeof(UV)*tipNum, 0, 0, D3DPOOL_MANAGED, &uvBuf, 0);

		copyBuf(sizeof(vtx), vtx, vtxBuf);
		copyBuf(sizeof(WorldPos)*tipNum, worldPos , worldPosBuf);
		copyBuf(sizeof(UV)*tipNum, uv, uvBuf);

		delete[] uv;
		delete[] worldPos;

		//インデックスバッファ
		WORD index[6] = { 0,1,2,2,1,3 };
		pDevice->CreateIndexBuffer(sizeof(index), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuf, 0);
		void* p = 0;
		indexBuf->Lock(0, 0, &p,0);
		memcpy(p, index, sizeof(index));
		indexBuf->Unlock();

		//頂点宣言作成
		D3DVERTEXELEMENT9 declElems[] = {
			{0,0,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},	//Local coord
			{0,8,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0},	//UV
			{1,0,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,1},	//ワールド位置
			{2,0,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,2},	//チップUV
			D3DDECL_END()
		};
		pDevice->CreateVertexDeclaration(declElems, &decl);

		//シェーダ作成
		ID3DXBuffer* errBuf = 0;
		D3DXCreateEffectFromFileA(pDevice, "tip.fx", 0, 0, 0, 0, &effect, &errBuf);
		if (errBuf) {
			const char* errMsg = (const char*)errBuf->GetBufferPointer();
			OutputDebugStringA(errMsg);
			return;
		}

		//チップテクスチャ
		D3DXCreateTextureFromFileA(pDevice, "tips.bmp", &tex);

	}
	~InstancingMode() {
		vtxBuf->Release();
		uvBuf->Release();
		worldPosBuf->Release();
		decl->Release();
		indexBuf->Release();
		tex->Release();
		effect->Release();
	}

	void draw() {
		modeStr = modeStr_instancing;
		
		//インスタンス宣言
		pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | (W*H));
		pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);
		pDevice->SetStreamSourceFreq(2, D3DSTREAMSOURCE_INSTANCEDATA | 1);

		//頂点とインデックスを設定して描画
		pDevice->SetVertexDeclaration(decl);
		pDevice->SetStreamSource(0, vtxBuf, 0, sizeof(Vtx));
		pDevice->SetStreamSource(1, worldPosBuf, 0, sizeof(WorldPos));
		pDevice->SetStreamSource(2, uvBuf, 0, sizeof(UV));
		pDevice->SetIndices(indexBuf);

		effect->SetTechnique("tech");
		UINT passNum = 0;
		effect->Begin(&passNum, 0);
		effect->BeginPass(0);

		effect->SetTexture("tex", tex);
		effect->SetFloat("screenW", WINDOW_WIDTH / 2);
		effect->SetFloat("screenH", WINDOW_HEIGHT / 2);

		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

		effect->EndPass();
		effect->End();

		//後始末
		pDevice->SetStreamSourceFreq(0, 1);
		pDevice->SetStreamSourceFreq(1, 1);
		pDevice->SetStreamSourceFreq(2, 1);
	}
};
InstancingMode* instancingMode = NULL;
NormalMode* normalMode = NULL;

//================================================================================================
//エントリポイント
//================================================================================================
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStgr, INT iCmdShow)
{
	HWND hWnd = NULL;
	MSG msg;

	// ウィンドウの初期化
	static char szAppName[] = "最小シェーダー";
	WNDCLASSEX  wndclass;
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInst;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wndclass);
	hWnd = CreateWindow(szAppName, szAppName, WS_OVERLAPPEDWINDOW,
		0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInst, NULL);
	
	//タイトルバー分ウィンドウを補正
	RECT clientRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	::AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, FALSE);
	hWnd = CreateWindow(szAppName, szAppName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0,
		clientRect.right - clientRect.left, clientRect.bottom - clientRect.top,
		NULL, NULL, hInst, NULL);
	
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	InitD3d(hWnd);

	//===============================================================================================
	//シェーダを読み込む
	//HRESULT hr;
	//hr = D3DXCreateEffectFromFile(pDevice, "Min.fx", NULL, NULL, 0, NULL, &g_pEffect, NULL);
	//===============================================================================================

	initialize();

	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Render();
		}
	}

	FreeDx();

	return (INT)msg.wParam;
}

//================================================================================================
//ウィンドウプロシージャ（メッセージ処理）
//================================================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		switch ((CHAR)wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
		}
		break;
	case WM_CHAR:
		if (wParam == 'c')
			mode = (++mode) % 2;
		break;
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}


//================================================================================================
//================================================================================================
//以下：関数の定義
//================================================================================================
//================================================================================================
void copyBuf(unsigned sz, void* src, IDirect3DVertexBuffer9* buf)
{
	void* p = 0;
	buf->Lock(0, 0, &p, 0);
	memcpy(p, src, sz);
	buf->Unlock();
}
void startLap()
{
	QueryPerformanceCounter(&startTime);
	lapTime = 0.0;
}
void endLap() {
	LARGE_INTEGER e, f;
	QueryPerformanceCounter(&e);
	QueryPerformanceFrequency(&f);
	lapTime = (double)(e.QuadPart - startTime.QuadPart) / f.QuadPart;
}
void drawLapTime() {
	RECT r = { 0,0,0,0 };
	char c[512];
	sprintf_s(c, 512, "mode = %s, time = %f", modeStr, lapTime);
	pD3DFont->DrawTextA(NULL, c, -1, &r, DT_LEFT | DT_SINGLELINE | DT_NOCLIP, 0xffffffff);
}
//================================================================================================
//DirectXの初期化
//================================================================================================
HRESULT InitD3d(HWND hWnd)
{
	// 「Direct3D」オブジェクトの作成
	if (NULL == (pD3d = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		MessageBox(0, "Direct3Dの作成に失敗しました", "", MB_OK);
		return E_FAIL;
	}
	// 「DIRECT3Dデバイス」オブジェクトの作成
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &pDevice)))
	{
		if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &pDevice)))
		{
			MessageBox(0, "HALモードでDIRECT3Dデバイスを作成できません\nREFモードで再試行します", NULL, MB_OK);
			if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING,
				&d3dpp, &pDevice)))
			{
				if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&d3dpp, &pDevice)))
				{
					MessageBox(0, "DIRECT3Dデバイスの作成に失敗しました", NULL, MB_OK);
					return E_FAIL;
				}
			}
		}
	}

	//Zバッファー処理を有効にする
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	return S_OK;
}

//================================================================================================
//初期化処理
//================================================================================================
void initialize()
{
	// フォント生成
	int fontsize = 24;
	D3DXFONT_DESC lf = { fontsize, 0, 0, 1, 0, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS,
		PROOF_QUALITY, FIXED_PITCH | FF_MODERN, _T("ＭＳ ゴシック") };
	if (FAILED(D3DXCreateFontIndirect(pDevice, &lf, &pD3DFont))) {
		pDevice->Release(); pD3d->Release();
	}

	instancingMode = new InstancingMode;
	normalMode = new NormalMode;
	object.initialize(pDevice);
}

//================================================================================================
//描画処理
//================================================================================================
VOID Render()
{
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(100, 100, 100), 1.0f, 0);
	//レンダリング	
	if (SUCCEEDED(pDevice->BeginScene()))
	{
		startLap();

		object.render(pDevice);

		//if (mode == 0)
		//	instancingMode->draw();
		//else
		//	normalMode->draw();

		endLap();
		drawLapTime();
		pDevice->EndScene();
	}
	pDevice->Present(NULL, NULL, NULL, NULL);
}

//================================================================================================
//終了処理
//================================================================================================
VOID FreeDx()
{
	SAFE_DELETE(instancingMode);
	SAFE_DELETE(normalMode);
	SAFE_RELEASE(pDevice);
	SAFE_RELEASE(pD3d);
}