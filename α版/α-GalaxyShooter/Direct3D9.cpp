#include "Direct3D9.h"

Direct3D9::Direct3D9()
{
	ZeroMemory(this, sizeof(Direct3D9));
}

Direct3D9::~Direct3D9()
{
	SAFE_RELEASE(device);
	SAFE_RELEASE(d3d);
}

HRESULT Direct3D9::initialize(HWND targetWnd)
{
	//Direct3Dオブジェクトの作成
	if (NULL == (d3d = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		MSG("Direct3Dの作成に失敗しました");
		return E_FAIL;
	}
	//「DIRECT3Dデバイス」オブジェクトの作成
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = true;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	if (FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, targetWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &device)))
	{
		if (FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, targetWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &device)))
		{
			MessageBox(0, "HALモードでDIRECT3Dデバイスを作成できません\nREFモードで再試行します", NULL, MB_OK);
			if (FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, targetWnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING,
				&d3dpp, &device)))
			{
				if (FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, targetWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&d3dpp, &device)))
				{
					MessageBox(0, "DIRECT3Dデバイスの作成に失敗しました", NULL, MB_OK);
					return E_FAIL;
				}
			}
		}
	}

	// Zバッファー処理を有効にする
	device->SetRenderState(D3DRS_ZENABLE, true);
	// ライトを有効にする
	device->SetRenderState(D3DRS_LIGHTING, true);
	// アンビエントライト（環境光）を設定する
	device->SetRenderState(D3DRS_AMBIENT, 0x22111111);
	// スペキュラ（光沢反射）を有効にする
	device->SetRenderState(D3DRS_SPECULARENABLE, true);
	// カリングはしない
	//device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	// カリングを有効にする
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//アンチエイリアシングをかける
	device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, true);
	// αブレンドを行う
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// αソースカラーの指定
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	// αデスティネーションカラーの指定
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	// ビューポートを取得
	device->GetViewport(&viewPort);
	return S_OK;
}

void Direct3D9::showFPS()
{
	static INT frames = 0, FPS = 0;
	static LARGE_INTEGER frq = { 0 }, previous = { 0 }, current = { 0 };
	DOUBLE time = 0;
	//char sz[11] = { 0 };

	QueryPerformanceFrequency(&frq);

	QueryPerformanceCounter(&current);
	time = (DOUBLE)(current.QuadPart - previous.QuadPart);
	time *= (DOUBLE)1100.0 / (DOUBLE)frq.QuadPart;
	if (time >= 1100.000)
	{
		previous = current;
		FPS = frames;
		frames = 0;
	}

	frames++;
}

void Direct3D9::clear()
{
	//画面クリア（実際は単色で画面を塗りつぶす処理）
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
}

HRESULT Direct3D9::present()
{
	//画面更新（バックバッファをフロントバッファにする）
	device->Present(NULL, NULL, NULL, NULL);
	return S_OK;
}

HRESULT Direct3D9::beginScene()
{
	if (device == NULL)return E_FAIL;
	return device->BeginScene();//描画のためのシーンを開始する
}

HRESULT Direct3D9::endScene()
{
	if (device == NULL)return E_FAIL;
	return device->EndScene();
}

HRESULT Direct3D9::changeViewportFullWindow()
{
	changeViewport(0, 0, viewPort.Width, viewPort.Height);
	return S_OK;
}

HRESULT Direct3D9::changeViewport1PWindow()
{
	changeViewport(0, 0, viewPort.Width/2-3, viewPort.Height);
	return S_OK;
}

HRESULT Direct3D9::changeViewport2PWindow()
{
	changeViewport(viewPort.Width/2+3, 0, viewPort.Width/2-3, viewPort.Height);
	return S_OK;
}


HRESULT Direct3D9::changeViewport(DWORD x, DWORD y, DWORD width, DWORD height)
{
	D3DVIEWPORT9 vp;

	vp.X = x;
	vp.Y = y;
	vp.Width = width;
	vp.Height = height;
	vp.MinZ = 0;
	vp.MaxZ = 1;

	MFAIL(device->SetViewport(&vp),"ビューポート切り替え失敗");

	return S_OK;
}