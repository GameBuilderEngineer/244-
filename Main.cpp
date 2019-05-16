//こんにちは
//必要なヘッダーファイルのインクルード
#include <windows.h>
#include <d3dx9.h>
//必要なライブラリファイルのロード
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
// シンボル定義及びマクロ
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define SAFE_DELETE(p) { if(p) { delete (p);     (p) = NULL; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p) = NULL; } }
//
enum VIEW
{
	NO_SPLIT,//（通常）分割無し
	TOP,//（分割有り）上からの視点
	FRONT,//（分割有り）正面からの視点
	LEFT,//（分割有り）左からの視点
	BIRD//（分割有り）鳥瞰視点　Bird's-Eye View
};
//グローバルなインスタンスを宣言
LPDIRECT3D9 pD3d = NULL;
LPDIRECT3DDEVICE9 pDevice = NULL;
D3DVIEWPORT9 g_VP;
LPD3DXMESH pMesh = NULL;
D3DMATERIAL9* pMeshMaterials = NULL;
LPDIRECT3DTEXTURE9* pMeshTextures  = NULL; 
DWORD dwNumMaterials = 0;
D3DXVECTOR3 g_vPosition(0,0,0);
FLOAT fYaw=0,fPitch=0,fRoll=0;
FLOAT fScale=1;
BOOL boQuad=true;
//関数プロトタイプの宣言
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HRESULT InitD3d(HWND);
HRESULT ChangeViewport(DWORD,DWORD,DWORD,DWORD);
VOID Render();
HRESULT ViewRender(D3DXCOLOR);
VOID FreeDx();
//
//INT WINAPI WinMain( HINSTANCE hInst,HINSTANCE hPrevInst,LPSTR szStr,INT iCmdShow)
//アプリケーションのエントリー関数
INT WINAPI WinMain( HINSTANCE hInst,HINSTANCE hPrevInst,LPSTR szStr,INT iCmdShow)
{
	HWND hWnd = NULL;
	MSG msg;
	// ウィンドウの初期化
	static char szAppName[] = "異なるビューを分割レンダリング スペースキーで画面切替え。矢印、Z,X,C,V,A,S,B,Nでオブジェクト操作";     
     WNDCLASSEX  wndclass;

     wndclass.cbSize           = sizeof (wndclass);
     wndclass.style              = CS_HREDRAW | CS_VREDRAW;
     wndclass.lpfnWndProc    = WndProc;
     wndclass.cbClsExtra      = 0;
     wndclass.cbWndExtra     = 0;
     wndclass.hInstance        = hInst;
     wndclass.hIcon             = LoadIcon (NULL, IDI_APPLICATION);
     wndclass.hCursor          = LoadCursor (NULL, IDC_ARROW);
     wndclass.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
     wndclass.lpszMenuName = NULL;
     wndclass.lpszClassName = szAppName;
     wndclass.hIconSm         = LoadIcon (NULL, IDI_APPLICATION);

     RegisterClassEx (&wndclass);

     hWnd = CreateWindow (szAppName,szAppName,WS_OVERLAPPEDWINDOW,   
                    0,0,WINDOW_WIDTH,WINDOW_HEIGHT,NULL,NULL,hInst,NULL);	

    ShowWindow (hWnd,SW_SHOW);
    UpdateWindow (hWnd);
	// ダイレクト３Dの初期化関数を呼ぶ
	if(FAILED(InitD3d(hWnd)))
	{
		return 0;
	}
	// メッセージループ
    ZeroMemory( &msg, sizeof(msg) );
    while( msg.message!=WM_QUIT )
     {
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
         {
			TranslateMessage( &msg );
             DispatchMessage( &msg );
         }
         else
		{
			Render();
		}                    
	}
	// メッセージループから抜けたらオブジェクトを全て開放する
	FreeDx();
	// OSに戻る（アプリケーションを終了する）
     return (INT)msg.wParam;
}
//
//LRESULT CALLBACK WndProc(HWND hWnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
// ウィンドウプロシージャ関数
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{	
	switch(iMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
		return 0;
		case WM_KEYDOWN:
		switch((CHAR)wParam)
		{
			case VK_ESCAPE:
				PostQuitMessage(0);
			return 0;
			case 'A':
				fScale+=0.1f;
				break;
			case 'S':
				fScale-=0.1f;
				break;
			case 'Z':
				fYaw+=0.1f;
				break;
			case 'X':
				fYaw-=0.1f;
				break;
			case 'C':
				fPitch+=0.1f;
				break;
			case 'V':
				fPitch-=0.1f;
				break;
			case 'B':
				fRoll+=0.1f;
				break;
			case 'N':
				fRoll-=0.1f;
				break;		
			case VK_UP:
				g_vPosition.z+=0.1f;
				break;
			case VK_DOWN:
				g_vPosition.z-=0.1f;
				break;
			case VK_LEFT:
				g_vPosition.x-=0.1f;
				break;
			case VK_RIGHT:
				g_vPosition.x+=0.1f;
				break;
			case VK_SPACE:
				boQuad ? boQuad=false : boQuad=true;			
				break;
		}
		break;
	}
	return DefWindowProc (hWnd, iMsg, wParam, lParam);	
}
//
//HRESULT InitD3d(HWND hWnd)
//ダイレクト3Dの初期化関数
HRESULT InitD3d(HWND hWnd)
{
	// 「Direct3D」オブジェクトの作成
	if( NULL == ( pD3d = Direct3DCreate9( D3D_SDK_VERSION ) ) )
	{
		MessageBox(0,"Direct3Dの作成に失敗しました","",MB_OK);
        return E_FAIL;
	}
	// 「DIRECT3Dデバイス」オブジェクトの作成
	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory( &d3dpp, sizeof(d3dpp) );   
	d3dpp.BackBufferFormat =D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount=1;	
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	
	d3dpp.Windowed = true;
    d3dpp.EnableAutoDepthStencil = true;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	

	if( FAILED( pD3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                      &d3dpp, &pDevice ) ) )
    {
		if( FAILED( pD3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &pDevice ) ) )
		{	
			MessageBox(0,"HALモードでDIRECT3Dデバイスを作成できません\nREFモードで再試行します",NULL,MB_OK);
			if( FAILED( pD3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
                                      D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                      &d3dpp, &pDevice ) ) )
			{				
				if( FAILED( pD3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &pDevice ) ) )
				{
					MessageBox(0,"DIRECT3Dデバイスの作成に失敗しました",NULL,MB_OK);			
					return E_FAIL;
				}
			}
		}
	}
	// Xファイルからメッシュをロードする	
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	if( FAILED( D3DXLoadMeshFromX( "RobotB.x", D3DXMESH_SYSTEMMEM, 
            pDevice, NULL, &pD3DXMtrlBuffer, NULL,
			&dwNumMaterials, &pMesh ) ) )
    {
            MessageBox(NULL, "Xファイルの読み込みに失敗しました",NULL, MB_OK);
            return E_FAIL;   
    }
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
    pMeshMaterials = new D3DMATERIAL9[dwNumMaterials];
    pMeshTextures  = new LPDIRECT3DTEXTURE9[dwNumMaterials];

	for( DWORD i=0; i<dwNumMaterials; i++ )
	{ 
		pMeshMaterials[i] = d3dxMaterials[i].MatD3D;		
        pMeshMaterials[i].Ambient = pMeshMaterials[i].Diffuse;
        pMeshTextures[i] = NULL;
        if( d3dxMaterials[i].pTextureFilename != NULL && 
            lstrlen(d3dxMaterials[i].pTextureFilename) > 0 )
        {       
            if( FAILED( D3DXCreateTextureFromFile( pDevice, 
                                                d3dxMaterials[i].pTextureFilename, 
                                                &pMeshTextures[i] ) ) )
            {      
                MessageBox(NULL, "テクスチャの読み込みに失敗しました", NULL, MB_OK);
			}
        }
    }
	pD3DXMtrlBuffer->Release();
	pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );  
	
	// Zバッファー処理を有効にする
    pDevice->SetRenderState( D3DRS_ZENABLE, true );  
	// ライトを有効にする
	pDevice->SetRenderState( D3DRS_LIGHTING, true );
	// アンビエントライト（環境光）を設定する
	pDevice->SetRenderState( D3DRS_AMBIENT, 0x22111111 );
	// スペキュラ（光沢反射）を有効にする
	pDevice->SetRenderState(D3DRS_SPECULARENABLE,true);
	//
	pDevice->GetViewport(&g_VP);

	return S_OK;
}
//
//HRESULT ChangeViewport(DWORD dwX,DWORD dwY,DWORD dwWidth,DWORD dwHeight)
//ビューポート　切り替え
HRESULT ChangeViewport(DWORD dwX,DWORD dwY,DWORD dwWidth,DWORD dwHeight)
{
	D3DVIEWPORT9 vp;

	vp.X=dwX;
	vp.Y=dwY;
	vp.Width=dwWidth;
	vp.Height=dwHeight;
	vp.MinZ=0;
	vp.MaxZ=1;	

	if(FAILED(pDevice->SetViewport(&vp)))
	{
		MessageBox(0,"ビューポート切り替え失敗","エラー",MB_OK);
		return E_FAIL;
	}
	return S_OK;
}
//
//VOID SetViewMatrix(VIEW vi)
//ビュー変換行列の作成を関数化した。
VOID SetViewMatrix(VIEW vi)
{
	// ビュートランスフォーム（ワールド座標→カメラ座標への変換）
	D3DXMATRIX mView;
	D3DXVECTOR3 vEyePt(0,0,0); //カメラ（視点）位置
	D3DXVECTOR3 vLookatPt(0, 0,0);//注視位置
	D3DXVECTOR3 vUpVec(0,1,0);//上方ベクトル定義	
	switch(vi)
	{
	case NO_SPLIT:
		vEyePt=D3DXVECTOR3(0,0,-4);
		break;
	case TOP:
		vEyePt=D3DXVECTOR3(0,4,0.01);
		break;
	case FRONT:
		vEyePt=D3DXVECTOR3(0,0,-4);
		break;
	case LEFT:
		vEyePt=D3DXVECTOR3(-3,0,0);
		break;
	case BIRD:
		vEyePt=D3DXVECTOR3(4,4,-4);
		break;
	}
	D3DXMatrixLookAtLH( &mView, &vEyePt, &vLookatPt, &vUpVec );
	pDevice->SetTransform( D3DTS_VIEW, &mView );
}
//
//VOID Render()
//Xファイルから読み込んだメッシュをレンダリングする関数
VOID Render()
{
	if(boQuad)
	{
		SetViewMatrix(TOP);
		ChangeViewport(0,0,g_VP.Width/2,g_VP.Height/2);
		ViewRender(D3DXCOLOR(1,0,0,1));
		
		SetViewMatrix(FRONT);
		ChangeViewport(0,g_VP.Height/2,g_VP.Width/2,g_VP.Height/2);
		ViewRender(D3DXCOLOR(0,1,0,1));
		
		SetViewMatrix(LEFT);
		ChangeViewport(g_VP.Width/2,g_VP.Height/2,g_VP.Width/2,g_VP.Height/2);
		ViewRender(D3DXCOLOR(0,0,1,1));
		
		SetViewMatrix(BIRD);
		ChangeViewport(g_VP.Width/2,0,g_VP.Width/2,g_VP.Height/2);
		ViewRender(D3DXCOLOR(1,1,0,1));
	}
	else
	{
		SetViewMatrix(NO_SPLIT);
		ChangeViewport(0,0,g_VP.Width,g_VP.Height);
		ViewRender(D3DXCOLOR(1,1,1,1));
	}
	pDevice->Present( NULL, NULL, NULL, NULL );
}
//
//HHRESULT ViewRender(D3DXCOLOR BGColor)
//個々のビューポートをレンダリングする
HRESULT ViewRender(D3DXCOLOR BGColor)
{	
	//ワールドトランスフォーム（ローカル座標→ワールド座標への変換）
	D3DXMATRIX mWorld,mScale,mRotation,mPosition;
     D3DXMatrixScaling(&mScale,fScale,fScale,fScale);//スケーリング（拡大縮小）行列を作成
	D3DXMatrixRotationYawPitchRoll(&mRotation,fYaw,fPitch,fRoll);//回転行列を作成
	D3DXMatrixTranslation(&mPosition,g_vPosition.x,g_vPosition.y,g_vPosition.z);//平行移動行列を作成
	mWorld=mScale*mRotation*mPosition;//スケーリング x 回転 x 平行移動 の順番で合成する（掛ける）
     pDevice->SetTransform( D3DTS_WORLD, &mWorld );
	// プロジェクショントランスフォーム（カメラ座標→スクリーン座標への変換）
	D3DXMATRIX mProj;
	D3DXMatrixPerspectiveFovLH( &mProj, D3DX_PI/4,
		(FLOAT)WINDOW_WIDTH/(FLOAT)WINDOW_HEIGHT, 0.1f, 10.0f );
	pDevice->SetTransform( D3DTS_PROJECTION, &mProj );   
	// ライトをあてる 白色で光沢反射ありに設定
	D3DXVECTOR3 vDirection(0,-1,1);
     D3DLIGHT9 light;
     ZeroMemory( &light, sizeof(D3DLIGHT9) );
     light.Type       = D3DLIGHT_DIRECTIONAL;
     light.Diffuse.r  = 1.0f;
     light.Diffuse.g  = 1.0f;
     light.Diffuse.b  = 1.0f;
	light.Diffuse.a=0.2; 
	light.Specular=light.Diffuse;
     D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vDirection );
     light.Range       = 20.0f;
     pDevice->SetLight( 0, &light );
     pDevice->LightEnable( 0, true );
	
	// レンダリング
	pDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER ,
		BGColor, 1.0f, 0 );

	if( SUCCEEDED( pDevice->BeginScene() ) )
	{		
		for( DWORD i=0; i<dwNumMaterials; i++ )
        {
            pDevice->SetMaterial( &pMeshMaterials[i] );
            pDevice->SetTexture( 0, pMeshTextures[i] ); 
            pMesh->DrawSubset( i );
        }
		pDevice->EndScene();
	}	
	
	return S_OK;
}
//
//VOID FreeDx()
// 作成したDirectXオブジェクトの開放
VOID FreeDx()
{	
	SAFE_DELETE( pMeshMaterials );
	for(DWORD k=0;k<dwNumMaterials;k++)
	{		
		SAFE_RELEASE( pMeshTextures[k] );
	}
	SAFE_RELEASE( pMesh );
	SAFE_RELEASE( pDevice );
	SAFE_RELEASE( pD3d );
}