#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib,"winmm.lib")

//================================================================================================
//�C���N���[�h
//================================================================================================
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define SAFE_RELEASE(p) {if(p) {(p)->Release(); (p) = NULL;}}

//�O���[�o���ϐ�
LPDIRECT3D9 pD3d;
LPDIRECT3DDEVICE9 pDevice;

LPD3DXMESH pMesh = NULL;
D3DMATERIAL9* pMeshMaterials = NULL;
LPDIRECT3DTEXTURE9* pMeshTextures = NULL;
DWORD dwNumMaterials = 0;

D3DXATTRIBUTERANGE* pAttrTable;
DWORD dwNumAttr;

IDirect3DVertexBuffer9 *vtxBuf;
IDirect3DIndexBuffer9 *indexBuf;

LPDIRECT3DINDEXBUFFER9 lpIB;
LPDIRECT3DVERTEXBUFFER9 lpVB;

LPDIRECT3DVERTEXBUFFER9 worldPosBuf;
IDirect3DVertexDeclaration9 *pvertexDec;

WORD* indexNums;
DWORD vertexNum;
DWORD polygonNum;

LPD3DXEFFECT g_pEffect = NULL;

const int WIDTH_NUM = 10;
const int HEIGHT_NUM = 10;
const int DIPTH_NUM = 10;
const int MODEL_NUM = WIDTH_NUM * HEIGHT_NUM * DIPTH_NUM;

// ���_�o�b�t�@
struct Vtx {
	float x, y, z; //���_�ʒu
};
Vtx* saveVtx;

//���[���h���W�ʒu�o�b�t�@
struct WorldPos {
	float x, y,z;
};

//�֐��v���g�^�C�v�̐錾
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT InitD3d(HWND);
VOID Render();
VOID FreeDx();

void copyBuf(unsigned sz, void *src, IDirect3DVertexBuffer9 *buf) {
	void *p = 0;
	buf->Lock(0, 0, &p, 0);
	memcpy(p, src, sz);
	buf->Unlock();
}

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStgr, INT iCmdShow)
{
	HWND hWnd = NULL;
	MSG msg;

	// �E�B���h�E�̏�����
	static char szAppName[] = "�ŏ��V�F�[�_�[";
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
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	InitD3d(hWnd);
	//===============================================================================================
	// X�t�@�C�����烁�b�V�������[�h����	
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	if (FAILED(D3DXLoadMeshFromX("Box.x", D3DXMESH_SYSTEMMEM,
		pDevice, NULL, &pD3DXMtrlBuffer, NULL,
		&dwNumMaterials, &pMesh)))
	{
		MessageBox(NULL, "X�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
		return E_FAIL;
	}
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	pMeshMaterials = new D3DMATERIAL9[dwNumMaterials];
	pMeshTextures = new LPDIRECT3DTEXTURE9[dwNumMaterials];

	for (DWORD i = 0; i < dwNumMaterials; i++)
	{
		pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		pMeshMaterials[i].Ambient = pMeshMaterials[i].Diffuse;
		pMeshTextures[i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL &&
			lstrlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			if (FAILED(D3DXCreateTextureFromFile(pDevice,
				d3dxMaterials[i].pTextureFilename,
				&pMeshTextures[i])))
			{
				MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
			}
		}
	}
	pD3DXMtrlBuffer->Release();
	//===============================================================================================

	HRESULT hr;
	//===============================================================================================
	//�V�F�[�_��ǂݍ���
	hr = D3DXCreateEffectFromFile(pDevice, "Min.fx", NULL, NULL, 0, NULL, &g_pEffect, NULL);
	//===============================================================================================

	//������
	pAttrTable = NULL;
	dwNumAttr = 0;

	//���b�V���̑����e�[�u���̎擾
	//���b�V���̃e�[�u�����擾
	pMesh->GetAttributeTable(NULL, &dwNumAttr);
	//�e�[�u���̐���
	pAttrTable = new D3DXATTRIBUTERANGE[dwNumAttr];
	//�擾
	pMesh->GetAttributeTable(pAttrTable, &dwNumAttr);

	float size = 3.0f;
	Vtx vtx[8] = {				// �P�ʔ|���o�b�t�@
		{ -1.0f, -1.0f, -1.0f},
		{ +1.0f, -1.0f, -1.0f},
		{ +1.0f, -1.0f, +1.0f},
		{ -1.0f, -1.0f, +1.0f},
		{ -1.0f, 1.0f, -1.0f},
		{ +1.0f, 1.0f, -1.0f},
		{ +1.0f, 1.0f, +1.0f},
		{ -1.0f, 1.0f, +1.0f}
	};
	//�o�[�e�b�N�X�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(vtx), 0, 0, D3DPOOL_MANAGED, &vtxBuf, 0);
	copyBuf(sizeof(vtx), vtx, vtxBuf);

	// �C���f�b�N�X�o�b�t�@�̍쐬
	WORD index[36] = { 
		//top
		7, 6, 5,
		4, 7, 5,
		//front
		4, 5, 1,
		4, 1, 0,
		//right
		5, 6, 2,
		5, 2, 1,
		//back
		6, 7, 3,
		6, 3, 2,
		//bottom
		1, 2, 3,
		1, 3, 0,
		//left
		4, 3, 7,
		3, 4, 0
	};
	pDevice->CreateIndexBuffer(sizeof(index), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuf, 0);
	void *p = 0;
	indexBuf->Lock(0, 0, &p, 0);
	memcpy(p, index, sizeof(index));
	indexBuf->Unlock();



	//�C���f�b�N�X�o�b�t�@�̎擾
	pMesh->GetIndexBuffer(&lpIB);

	//�o�[�e�b�N�X�o�b�t�@�[�̎擾
	pMesh->GetVertexBuffer(&lpVB);
	

	//���_�f�[�^�̃T�C�Y���擾
	DWORD dwStride = pMesh->GetNumBytesPerVertex();
	//���_�����擾
	vertexNum = pMesh->GetNumVertices();
	//�|���S�������擾
	polygonNum = pMesh->GetNumFaces();

	//saveVtx = new Vtx[vertexNum];

	BYTE *pbVertices = NULL;
	FLOAT* pfVetices = NULL;
	if (SUCCEEDED(lpVB->Lock(0, 0, (VOID**)&pbVertices, 0)))
	{

		saveVtx = (Vtx*)pbVertices;
		//for (int i = 0; i < (int)vertexNum; i++) {
		//	pfVetices = (FLOAT*)&pbVertices[dwStride*i];
		//	saveVtx[i].x = pfVetices[0];
		//	saveVtx[i].y = pfVetices[1];
		//	saveVtx[i].z = pfVetices[2];
		//}

		pMesh->UnlockIndexBuffer();
		lpVB->Unlock();
		lpVB->Release();
	}
	//�o�[�e�b�N�X�o�b�t�@�̍쐬
	//pDevice->CreateVertexBuffer(sizeof(saveVtx), 0, 0, D3DPOOL_MANAGED, &vtxBuf, 0);
	//copyBuf(sizeof(saveVtx), saveVtx, vtxBuf);

	//�C���f�b�N�X�ԍ��̃T�C�Y���擾
	WORD* pwPoly = NULL;
	pMesh->LockIndexBuffer(D3DLOCK_READONLY, (VOID**)&pwPoly);
	indexNums = new WORD[polygonNum*3];
	BYTE *pbPolygons = NULL;
	INT* pPolygons = NULL;
	if (SUCCEEDED(lpIB->Lock(0, 0, (VOID**)&pbPolygons, 0)))
	{
		for (int i = 0; i < (int)polygonNum; i++)
		{
			indexNums[i * 3 + 0] = pwPoly[i * 3 + 0];
			indexNums[i * 3 + 1] = pwPoly[i * 3 + 1];
			indexNums[i * 3 + 2] = pwPoly[i * 3 + 2];
		}
		pMesh->UnlockIndexBuffer();
	}
	//pDevice->CreateIndexBuffer(sizeof(indexNums), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuf, 0);
	//void *p = 0;
	//indexBuf->Lock(0, 0, &p, 0);
	//memcpy(p, indexNums, sizeof(indexNums));
	//indexBuf->Unlock();


	float space = size + 10.0f;
	//���[���h�ʒu���W�o�b�t�@�̍쐬
	WorldPos* worldPos = new WorldPos[MODEL_NUM]; //���[���h���W�ʒu�o�b�t�@
	for (int w = 0; w < WIDTH_NUM; w++) {
		for (int h = 0; h < HEIGHT_NUM; h++) {
			for (int d = 0; d < DIPTH_NUM; d++) {
				int e = d * WIDTH_NUM*HEIGHT_NUM + h * HEIGHT_NUM + w;
				worldPos[e].x = space * w - (WIDTH_NUM	/ 2 * space);
				worldPos[e].y = space * h - (HEIGHT_NUM	/ 2 * space);
				worldPos[e].z = space * d - (DIPTH_NUM	/ 2 * space);
			}
		}
	}
	pDevice->CreateVertexBuffer(sizeof(WorldPos)*MODEL_NUM, 0, 0, D3DPOOL_MANAGED, &worldPosBuf, 0);
	copyBuf(sizeof(WorldPos) * MODEL_NUM, worldPos, worldPosBuf);
	//void* p = 0;
	//worldPosBuf->Lock(0, 0, &p, 0);
	//memcpy(p, worldPos, sizeof(WorldPos)*10*10);
	//worldPosBuf->Unlock();
	delete[] worldPos;

	//���_�錾
	D3DVERTEXELEMENT9 vertexElem[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },	//���_���W
		{ 1, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD, 1 },	//���[���h�ʒu
		D3DDECL_END()
	};

	//���_�錾�I�u�W�F�N�g����
	pDevice->CreateVertexDeclaration(vertexElem, &pvertexDec);



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
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

HRESULT InitD3d(HWND hWnd)
{
	// �uDirect3D�v�I�u�W�F�N�g�̍쐬
	if (NULL == (pD3d = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		MessageBox(0, "Direct3D�̍쐬�Ɏ��s���܂���", "", MB_OK);
		return E_FAIL;
	}
	// �uDIRECT3D�f�o�C�X�v�I�u�W�F�N�g�̍쐬
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &pDevice)))
	{
		if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &pDevice)))
		{
			MessageBox(0, "HAL���[�h��DIRECT3D�f�o�C�X���쐬�ł��܂���\nREF���[�h�ōĎ��s���܂�", NULL, MB_OK);
			if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING,
				&d3dpp, &pDevice)))
			{
				if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&d3dpp, &pDevice)))
				{
					MessageBox(0, "DIRECT3D�f�o�C�X�̍쐬�Ɏ��s���܂���", NULL, MB_OK);
					return E_FAIL;
				}
			}
		}
	}

	//Z�o�b�t�@�[������L���ɂ���
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	return S_OK;
}

VOID FreeDx()
{
	SAFE_RELEASE(g_pEffect);
	SAFE_RELEASE(pMesh);
	SAFE_RELEASE(pDevice);
	SAFE_RELEASE(pD3d);
}

VOID Render()
{
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(100, 100, 100), 1.0f, 0);
	//���[���h�g�����X�t�H�[���i��΍��W�ϊ��j
	D3DXMATRIX mWorld, mRotation;
	D3DXMatrixRotationY(&mWorld, timeGetTime() / 1000.0f);
	D3DXMatrixRotationX(&mRotation, 0.0f);
	D3DXMatrixMultiply(&mWorld, &mWorld, &mRotation);

	// �r���[�g�����X�t�H�[���i���_���W�ϊ��j
	D3DXVECTOR3 vEyePt(0.0f, 5.0f, -30.0f); //�J�����i���_�j�ʒu
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);//�����ʒu
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);//����ʒu
	D3DXMATRIX mView;
	D3DXMatrixLookAtLH(&mView, &vEyePt, &vLookatPt, &vUpVec);
	// �v���W�F�N�V�����g�����X�t�H�[���i�ˉe�ϊ��j
	D3DXMATRIX mProj;
	D3DXMatrixPerspectiveFovLH(&mProj, D3DX_PI / 4, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 10000.0f);
	
	//�C���X�^���X�錾
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | MODEL_NUM);
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	// ���_�錾��ʒm
	pDevice->SetVertexDeclaration(pvertexDec);
	//�f�o�C�X�f�[�^�X�g���[���Ƀ��b�V���̒��_�o�b�t�@���o�C���h
	//pDevice->SetStreamSource(0, lpVB, 0, pMesh->GetNumBytesPerVertex());
	pDevice->SetStreamSource(0, vtxBuf, 0, sizeof(Vtx));
	pDevice->SetStreamSource(1, worldPosBuf, 0, sizeof(WorldPos));

	//�C���f�b�N�X�o�b�t�@���Z�b�g
	//pDevice->SetIndices(lpIB);
	pDevice->SetIndices(indexBuf);

	//�����_�����O	
	if (SUCCEEDED(pDevice->BeginScene()))
	{
		g_pEffect->SetTechnique("texMinimum");
		D3DXMATRIX mAll = mWorld * mView * mProj;
		g_pEffect->SetMatrix("mWV", &mAll);
		UINT passNum = 0;
		g_pEffect->Begin(&passNum, 0);
		g_pEffect->BeginPass(0);
		
		
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
		for (DWORD i = 0; i < dwNumAttr; i++)
		{
			//g_pEffect->SetTexture("texMinimum", pMeshTextures[i]);

			//pDevice->DrawIndexedPrimitive(
			//	D3DPT_TRIANGLELIST,
			//	0,
			//	pAttrTable[i].VertexStart, //�ŏ���INDEX
			//	pAttrTable[i].VertexCount, //���_��
			//	pAttrTable[i].FaceStart * 3, //INDEXBUFFER����INDEX
			//	pAttrTable[i].FaceCount //�J�E���g��
			//);
			//pMesh->DrawSubset(i);
		}
		g_pEffect->EndPass();
		g_pEffect->End();

		pDevice->EndScene();
	}
	pDevice->Present(NULL, NULL, NULL, NULL);
}