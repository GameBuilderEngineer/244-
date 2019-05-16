//����ɂ���
//�K�v�ȃw�b�_�[�t�@�C���̃C���N���[�h
#include <windows.h>
#include <d3dx9.h>
//�K�v�ȃ��C�u�����t�@�C���̃��[�h
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
// �V���{����`�y�у}�N��
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define SAFE_DELETE(p) { if(p) { delete (p);     (p) = NULL; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p) = NULL; } }
//
enum VIEW
{
	NO_SPLIT,//�i�ʏ�j��������
	TOP,//�i�����L��j�ォ��̎��_
	FRONT,//�i�����L��j���ʂ���̎��_
	LEFT,//�i�����L��j������̎��_
	BIRD//�i�����L��j���Վ��_�@Bird's-Eye View
};
//�O���[�o���ȃC���X�^���X��錾
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
//�֐��v���g�^�C�v�̐錾
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HRESULT InitD3d(HWND);
HRESULT ChangeViewport(DWORD,DWORD,DWORD,DWORD);
VOID Render();
HRESULT ViewRender(D3DXCOLOR);
VOID FreeDx();
//
//INT WINAPI WinMain( HINSTANCE hInst,HINSTANCE hPrevInst,LPSTR szStr,INT iCmdShow)
//�A�v���P�[�V�����̃G���g���[�֐�
INT WINAPI WinMain( HINSTANCE hInst,HINSTANCE hPrevInst,LPSTR szStr,INT iCmdShow)
{
	HWND hWnd = NULL;
	MSG msg;
	// �E�B���h�E�̏�����
	static char szAppName[] = "�قȂ�r���[�𕪊������_�����O �X�y�[�X�L�[�ŉ�ʐؑւ��B���AZ,X,C,V,A,S,B,N�ŃI�u�W�F�N�g����";     
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
	// �_�C���N�g�RD�̏������֐����Ă�
	if(FAILED(InitD3d(hWnd)))
	{
		return 0;
	}
	// ���b�Z�[�W���[�v
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
	// ���b�Z�[�W���[�v���甲������I�u�W�F�N�g��S�ĊJ������
	FreeDx();
	// OS�ɖ߂�i�A�v���P�[�V�������I������j
     return (INT)msg.wParam;
}
//
//LRESULT CALLBACK WndProc(HWND hWnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
// �E�B���h�E�v���V�[�W���֐�
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
//�_�C���N�g3D�̏������֐�
HRESULT InitD3d(HWND hWnd)
{
	// �uDirect3D�v�I�u�W�F�N�g�̍쐬
	if( NULL == ( pD3d = Direct3DCreate9( D3D_SDK_VERSION ) ) )
	{
		MessageBox(0,"Direct3D�̍쐬�Ɏ��s���܂���","",MB_OK);
        return E_FAIL;
	}
	// �uDIRECT3D�f�o�C�X�v�I�u�W�F�N�g�̍쐬
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
			MessageBox(0,"HAL���[�h��DIRECT3D�f�o�C�X���쐬�ł��܂���\nREF���[�h�ōĎ��s���܂�",NULL,MB_OK);
			if( FAILED( pD3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
                                      D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                      &d3dpp, &pDevice ) ) )
			{				
				if( FAILED( pD3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &pDevice ) ) )
				{
					MessageBox(0,"DIRECT3D�f�o�C�X�̍쐬�Ɏ��s���܂���",NULL,MB_OK);			
					return E_FAIL;
				}
			}
		}
	}
	// X�t�@�C�����烁�b�V�������[�h����	
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	if( FAILED( D3DXLoadMeshFromX( "RobotB.x", D3DXMESH_SYSTEMMEM, 
            pDevice, NULL, &pD3DXMtrlBuffer, NULL,
			&dwNumMaterials, &pMesh ) ) )
    {
            MessageBox(NULL, "X�t�@�C���̓ǂݍ��݂Ɏ��s���܂���",NULL, MB_OK);
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
                MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
			}
        }
    }
	pD3DXMtrlBuffer->Release();
	pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );  
	
	// Z�o�b�t�@�[������L���ɂ���
    pDevice->SetRenderState( D3DRS_ZENABLE, true );  
	// ���C�g��L���ɂ���
	pDevice->SetRenderState( D3DRS_LIGHTING, true );
	// �A���r�G���g���C�g�i�����j��ݒ肷��
	pDevice->SetRenderState( D3DRS_AMBIENT, 0x22111111 );
	// �X�y�L�����i���򔽎ˁj��L���ɂ���
	pDevice->SetRenderState(D3DRS_SPECULARENABLE,true);
	//
	pDevice->GetViewport(&g_VP);

	return S_OK;
}
//
//HRESULT ChangeViewport(DWORD dwX,DWORD dwY,DWORD dwWidth,DWORD dwHeight)
//�r���[�|�[�g�@�؂�ւ�
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
		MessageBox(0,"�r���[�|�[�g�؂�ւ����s","�G���[",MB_OK);
		return E_FAIL;
	}
	return S_OK;
}
//
//VOID SetViewMatrix(VIEW vi)
//�r���[�ϊ��s��̍쐬���֐��������B
VOID SetViewMatrix(VIEW vi)
{
	// �r���[�g�����X�t�H�[���i���[���h���W���J�������W�ւ̕ϊ��j
	D3DXMATRIX mView;
	D3DXVECTOR3 vEyePt(0,0,0); //�J�����i���_�j�ʒu
	D3DXVECTOR3 vLookatPt(0, 0,0);//�����ʒu
	D3DXVECTOR3 vUpVec(0,1,0);//����x�N�g����`	
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
//X�t�@�C������ǂݍ��񂾃��b�V���������_�����O����֐�
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
//�X�̃r���[�|�[�g�������_�����O����
HRESULT ViewRender(D3DXCOLOR BGColor)
{	
	//���[���h�g�����X�t�H�[���i���[�J�����W�����[���h���W�ւ̕ϊ��j
	D3DXMATRIX mWorld,mScale,mRotation,mPosition;
     D3DXMatrixScaling(&mScale,fScale,fScale,fScale);//�X�P�[�����O�i�g��k���j�s����쐬
	D3DXMatrixRotationYawPitchRoll(&mRotation,fYaw,fPitch,fRoll);//��]�s����쐬
	D3DXMatrixTranslation(&mPosition,g_vPosition.x,g_vPosition.y,g_vPosition.z);//���s�ړ��s����쐬
	mWorld=mScale*mRotation*mPosition;//�X�P�[�����O x ��] x ���s�ړ� �̏��Ԃō�������i�|����j
     pDevice->SetTransform( D3DTS_WORLD, &mWorld );
	// �v���W�F�N�V�����g�����X�t�H�[���i�J�������W���X�N���[�����W�ւ̕ϊ��j
	D3DXMATRIX mProj;
	D3DXMatrixPerspectiveFovLH( &mProj, D3DX_PI/4,
		(FLOAT)WINDOW_WIDTH/(FLOAT)WINDOW_HEIGHT, 0.1f, 10.0f );
	pDevice->SetTransform( D3DTS_PROJECTION, &mProj );   
	// ���C�g�����Ă� ���F�Ō��򔽎˂���ɐݒ�
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
	
	// �����_�����O
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
// �쐬����DirectX�I�u�W�F�N�g�̊J��
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