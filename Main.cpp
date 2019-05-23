//����ɂ���
//�K�v�ȃw�b�_�[�t�@�C���̃C���N���[�h
#include "Main.h"

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
LPD3DXFONT pFont = NULL;
D3DVIEWPORT9 g_VP;
LPD3DXMESH pMesh = NULL;
D3DMATERIAL9* pMeshMaterials = NULL;
LPDIRECT3DTEXTURE9* pMeshTextures  = NULL; 
DWORD dwNumMaterials = 0;
D3DXVECTOR3 g_vPosition(0,0,0);
//FLOAT fYaw=0,fPitch=0,fRoll=0;
D3DXQUATERNION qtnAttitude(0, 0, 0, 1);
FLOAT fScale=1;
BOOL boQuad=true;
THING Thing[THING_AMOUNT + 1];

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

    hWnd = CreateWindow (szAppName,szAppName,WS_OVERLAPPEDWINDOW,0,0,WINDOW_WIDTH,WINDOW_HEIGHT,NULL,NULL,hInst,NULL);	

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
	D3DXQUATERNION qtnDelta;
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
			// Q���N�H�[�^�j�I���AV�����x�N�g���A�Ƃ���]�p�Ƃ���� Q=cos(1/2�Ɓj+sin(1/2��)*V   
			//D3DXQUATERNION��w�͎����Ax,y,z�͋����̎����i��]���x�N�g���Ƃ��ĐU�����A�A���A�P�ʃx�N�g���ł���K�v������j
			//case 'A':
			//	fScale+=0.1f;
			//	break;
			//case 'S':
			//	fScale-=0.1f;
			//	break;
			//case 'Z':
			//	fYaw+=0.1f;
			//	break;
			//case 'X':
			//	fYaw-=0.1f;
			//	break;
			//case 'C':
			//	fPitch+=0.1f;
			//	break;
			//case 'V':
			//	fPitch-=0.1f;
			//	break;
			//case 'B':
			//	fRoll+=0.1f;
			//	break;
			//case 'N':
			//	fRoll-=0.1f;
			//	break;		
			//case VK_UP:
			//	g_vPosition.z+=0.1f;
			//	break;
			//case VK_DOWN:
			//	g_vPosition.z-=0.1f;
			//	break;
			//case VK_LEFT:
			//	g_vPosition.x-=0.1f;
			//	break;
			//case VK_RIGHT:
			//	g_vPosition.x+=0.1f;
			//	break;
			//case VK_SPACE:
			//	boQuad ? boQuad=false : boQuad=true;			
			//	break;
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
	// X�t�@�C�����Ƀ��b�V�����쐬����
	InitThing(&Thing[0], "planet.x", &D3DXVECTOR3(0, -100, 0));
	InitThing(&Thing[1], "robotB_still_back.x", &D3DXVECTOR3(0, 3, 0));

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
	// �J�����O�͂��Ȃ�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//
	pDevice->GetViewport(&g_VP);
	//�����񃌃��_�����O�̏�����
	if (FAILED(D3DXCreateFont(pDevice, 0, 8, FW_REGULAR, NULL, false, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "tahoma", &pFont))) return E_FAIL;


	return S_OK;
}
//HRESULT InitThing(THING *pThing,LPSTR szXFileName,D3DXVECTOR3* pvPosition)
//
HRESULT InitThing(THING *pThing, LPSTR szXFileName, D3DXVECTOR3* pvPosition)
{
	// ���b�V���̏����ʒu
	memcpy(&pThing->vPosition, pvPosition, sizeof(D3DXVECTOR3));
	// X�t�@�C�����烁�b�V�������[�h����	
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	if (FAILED(D3DXLoadMeshFromX(szXFileName, D3DXMESH_SYSTEMMEM,
		pDevice, NULL, &pD3DXMtrlBuffer, NULL,
		&pThing->dwNumMaterials, &pThing->pMesh)))
	{
		MessageBox(NULL, "X�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", szXFileName, MB_OK);
		return E_FAIL;
	}
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	pThing->pMeshMaterials = new D3DMATERIAL9[pThing->dwNumMaterials];
	pThing->pMeshTextures = new LPDIRECT3DTEXTURE9[pThing->dwNumMaterials];

	for (DWORD i = 0; i < pThing->dwNumMaterials; i++)
	{
		pThing->pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		pThing->pMeshMaterials[i].Ambient = pThing->pMeshMaterials[i].Diffuse;
		pThing->pMeshTextures[i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL &&
			lstrlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			if (FAILED(D3DXCreateTextureFromFile(pDevice,
				d3dxMaterials[i].pTextureFilename,
				&pThing->pMeshTextures[i])))
			{
				MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
			}
		}
	}
	pD3DXMtrlBuffer->Release();

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
		vEyePt=D3DXVECTOR3(0,10,0.01);
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
	vEyePt += Thing[1].vPosition;
	vLookatPt = Thing[1].vPosition;
	D3DXMatrixLookAtLH( &mView, &vEyePt, &vLookatPt, &vUpVec );
	pDevice->SetTransform( D3DTS_VIEW, &mView );
}
//
//VOID Render()
//X�t�@�C������ǂݍ��񂾃��b�V���������_�����O����֐�
VOID Render()
{
	//���{�b�g����
	Thing[1].vDir = D3DXVECTOR3(0, 0, 0);

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

	//�����蔻��
	FLOAT fDistance = 0;
	D3DXVECTOR3 vNormal;

	//���ƃv���C���[�ւ̏d�͐�
	D3DXVECTOR3 toPlanet = Thing[0].vPosition - Thing[1].vPosition;
	//�d�͕t���ƁA�n�ʂƂ̓����蔻��
	Collide(Thing[1].vPosition, toPlanet, &Thing[0], &fDistance, &vNormal);
	D3DXVECTOR3 vGrav = -vNormal;
	D3DXVec3Normalize(&vGrav, &vGrav);
	Thing[1].gravity = vGrav;
	vGrav*=0.05;
	Thing[1].vDir += vGrav;//�d�́i�������̃x�N�g�������Z�j

	//Thing[1].vPosition.y -= 0.7;
	if (Collide(Thing[1].vPosition, Thing[1].vDir, &Thing[0], &fDistance, &vNormal))
	{
		Thing[1].distance[0] = fDistance;
		Thing[1].normal[0] = vNormal;
		if(fDistance <= 1.0)
		{
			//�������ԂȂ̂ŁA���点��
			Thing[1].vDir = Slip(Thing[1].vDir, vNormal);//����x�N�g�����v�Z

			//����x�N�g����̒n�ʓˋN�Ƃ̃��C���� �Q�d�ɔ���	
			if (Collide(Thing[1].vPosition, Thing[1].vDir, &Thing[0], &fDistance, &vNormal))
			{
				Thing[1].distance[1] = fDistance;
				Thing[1].normal[1] = vNormal;
				if(fDistance <= 0.7)
				{//�Q�i�ڂ̓������ԂȂ̂ŁA���点�� �����炭�オ�����		
					Thing[1].vDir = Slip(Thing[1].vDir, vNormal);//����x�N�g�����v�Z
				}
			}
		}
	}

	D3DXVECTOR3 moveDirection;
	if (GetKeyState('W') & 0x80)
	{
		Thing[1].vDir += Thing[1].vAxisZ*0.05;
	}
	if (GetKeyState('S') & 0x80)
	{
		Thing[1].vDir += -Thing[1].vAxisZ*0.05;
	}
	if (GetKeyState('A') & 0x80)
	{
		Thing[1].vDir = -Thing[1].vAxisX*0.05;
	}
	if (GetKeyState('D') & 0x80)
	{
		Thing[1].vDir = Thing[1].vAxisX*0.05;
	}

	D3DXQUATERNION qtnDelta;
	if (GetKeyState(VK_LEFT) & 0x80)
	{
		//sin(1/2��)*(0,1,0)
		qtnDelta.x = 0;
		qtnDelta.y = sin(-DELTA_ANGLE / 2.0f);
		qtnDelta.z = 0;
		qtnDelta.w = cos(-DELTA_ANGLE / 2.0f);
		Thing[1].qtnAttitude *= qtnDelta;
		//Thing[1].fYaw -= 0.05;
	}
	if (GetKeyState(VK_RIGHT) & 0x80)
	{
		//sin(1/2��)*(0,1,0)
		qtnDelta.x = 0;
		qtnDelta.y = sin(DELTA_ANGLE / 2.0f);
		qtnDelta.z = 0;
		qtnDelta.w = cos(DELTA_ANGLE / 2.0f);
		Thing[1].qtnAttitude *= qtnDelta;
		//Thing[1].fYaw += 0.05;
	}

	//Thing[1].vPosition.y += 0.7;

	//���{�b�g�@�ʒu�X�V
	Thing[1].vPosition += Thing[1].vDir;
}
//
//HHRESULT ViewRender(D3DXCOLOR BGColor)
//�X�̃r���[�|�[�g�������_�����O����
HRESULT ViewRender(D3DXCOLOR BGColor)
{	
	//���[���h�g�����X�t�H�[���i���[�J�����W�����[���h���W�ւ̕ϊ��j
	D3DXMATRIX mWorld,mScale,mRotation,mPosition;
	D3DXMatrixScaling(&mScale,fScale,fScale,fScale);//�X�P�[�����O�i�g��k���j�s����쐬
	//�N�H�[�^�j�I���iqtnAttitude�j����]�ʃp�����[�^�[�Ɏg�p����
	{
		D3DXMatrixRotationQuaternion(&mRotation, &qtnAttitude);
		//D3DXMatrixRotationYawPitchRoll(&mRotation,fYaw,fPitch,fRoll);//��]�s����쐬
	}

	
	D3DXMatrixTranslation(&mPosition,g_vPosition.x,g_vPosition.y,g_vPosition.z);//���s�ړ��s����쐬
	mWorld=mScale*mRotation*mPosition;//�X�P�[�����O x ��] x ���s�ړ� �̏��Ԃō�������i�|����j
    pDevice->SetTransform( D3DTS_WORLD, &mWorld );
	
	// �v���W�F�N�V�����g�����X�t�H�[���i�J�������W���X�N���[�����W�ւ̕ϊ��j
	D3DXMATRIX mProj;
	D3DXMatrixPerspectiveFovLH( &mProj, D3DX_PI/4,(FLOAT)WINDOW_WIDTH/(FLOAT)WINDOW_HEIGHT, 0.1f, 100000.0f );
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
		pDevice->SetRenderState(D3DRS_LIGHTING, false);
		RenderThing(&Thing[0]);
		pDevice->SetRenderState(D3DRS_LIGHTING, true);
		RenderThing(&Thing[1]);
		//�@���C�̃����_�����O
		D3DXVECTOR3 vGrav = Thing[0].vPosition - Thing[1].vPosition;
		D3DXVec3Normalize(&vGrav, &vGrav);
		RenderRay(pDevice, Thing[1].vPosition, Thing[1].gravity);

		//�����\��
		TCHAR szStr[MAX_PATH + 1];
		sprintf(szStr, "��ڂ̏Փ˃|���S���̖@���F(%.1f,%.1f,%.1f)\n���� %3.1f",
			Thing[1].normal[0].x, Thing[1].normal[0].y, Thing[1].normal[0].z, Thing[1].distance[0]);
		RenderString(szStr, 10, 10);
		sprintf(szStr, "��ڂ̏Փ˃|���S���̖@���F(%.1f,%.1f,%.1f)\n���� %3.1f",
			Thing[1].normal[1].x, Thing[1].normal[1].y, Thing[1].normal[1].z, Thing[1].distance[1]);
		RenderString(szStr, 10, 100);

		pDevice->EndScene();
	}	
	
	return S_OK;
}
//
//VOID RenderString(LPSTR szStr,INT iX,INT iY)
// ���\���p���[�`��
VOID RenderString(LPSTR szStr, INT iX, INT iY)
{
	RECT rect = { iX,iY,0,0 };
	//������̃T�C�Y���v�Z
	pFont->DrawText(NULL, szStr, -1, &rect, DT_CALCRECT, NULL);
	// ���̃T�C�Y�Ń����_�����O
	pFont->DrawText(NULL, szStr, -1, &rect, DT_LEFT | DT_BOTTOM, 0xff00ff00);
}
//
//VOID RenderThing(THING* pThing)
//
VOID RenderThing(THING* pThing)
{
	//���[���h�g�����X�t�H�[���i���[�J�����W�����[���h���W�ւ̕ϊ��j	
	D3DXMatrixTranslation(&pThing->mPosition, pThing->vPosition.x, pThing->vPosition.y,
		pThing->vPosition.z);

	//�N�H�[�^�j�I���iqtnAttitude�j����]�ʃp�����[�^�[�Ɏg�p����
	{
		D3DXMatrixRotationQuaternion(&pThing->mRotation, &pThing->qtnAttitude);
		//D3DXMatrixRotationY(&pThing->mRotation, pThing->fYaw);
	}
	D3DXMatrixMultiply(&pThing->mWorld, &pThing->mRotation, &pThing->mPosition);
	
	
	pDevice->SetTransform(D3DTS_WORLD, &pThing->mWorld);

	//��]�ɂ��A���[�J�������Ȃ���
	D3DXVec3TransformCoord(&pThing->vAxisX, &D3DXVECTOR3(1, 0, 0), &pThing->mRotation);
	D3DXVec3TransformCoord(&pThing->vAxisZ, &D3DXVECTOR3(0, 0, 1), &pThing->mRotation);

	// �����_�����O			
	for (DWORD i = 0; i < pThing->dwNumMaterials; i++)
	{
		pDevice->SetMaterial(&pThing->pMeshMaterials[i]);
		pDevice->SetTexture(0, pThing->pMeshTextures[i]);
		pThing->pMesh->DrawSubset(i);
	}
}
//
//D3DXVECTOR3 Slip(D3DXVECTOR3 L,D3DXVECTOR3 N)
// L:���˃x�N�g���i���C�j N:�|���S���̖@��
D3DXVECTOR3 Slip(D3DXVECTOR3 L, D3DXVECTOR3 N)
{
	D3DXVECTOR3 S; //����x�N�g���i��������j

	//����x�N�g�� S=L-(N * L)/(|N|^2)*N
	S = L - ((D3DXVec3Dot(&N, &L)) / (pow(D3DXVec3Length(&N), 2))) * N;

	return S;
}
//
//VOID FreeDx()
// �쐬����DirectX�I�u�W�F�N�g�̊J��
VOID FreeDx()
{	
	SAFE_RELEASE(pFont);
	SAFE_DELETE( pMeshMaterials );
	for(DWORD k=0;k<dwNumMaterials;k++)
	{		
		SAFE_RELEASE( pMeshTextures[k] );
	}
	SAFE_RELEASE( pMesh );
	SAFE_RELEASE( pDevice );
	SAFE_RELEASE( pD3d );
}