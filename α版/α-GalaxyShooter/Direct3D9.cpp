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
	//Direct3D�I�u�W�F�N�g�̍쐬
	if (NULL == (d3d = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		MSG("Direct3D�̍쐬�Ɏ��s���܂���");
		return E_FAIL;
	}
	//�uDIRECT3D�f�o�C�X�v�I�u�W�F�N�g�̍쐬
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
			MessageBox(0, "HAL���[�h��DIRECT3D�f�o�C�X���쐬�ł��܂���\nREF���[�h�ōĎ��s���܂�", NULL, MB_OK);
			if (FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, targetWnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING,
				&d3dpp, &device)))
			{
				if (FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, targetWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&d3dpp, &device)))
				{
					MessageBox(0, "DIRECT3D�f�o�C�X�̍쐬�Ɏ��s���܂���", NULL, MB_OK);
					return E_FAIL;
				}
			}
		}
	}

	// Z�o�b�t�@�[������L���ɂ���
	device->SetRenderState(D3DRS_ZENABLE, true);
	// ���C�g��L���ɂ���
	device->SetRenderState(D3DRS_LIGHTING, true);
	// �A���r�G���g���C�g�i�����j��ݒ肷��
	device->SetRenderState(D3DRS_AMBIENT, 0x22111111);
	// �X�y�L�����i���򔽎ˁj��L���ɂ���
	device->SetRenderState(D3DRS_SPECULARENABLE, true);
	// �J�����O�͂��Ȃ�
	//device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	// �J�����O��L���ɂ���
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//�A���`�G�C���A�V���O��������
	device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, true);
	// ���u�����h���s��
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// ���\�[�X�J���[�̎w��
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	// ���f�X�e�B�l�[�V�����J���[�̎w��
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	// �r���[�|�[�g���擾
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
	//��ʃN���A�i���ۂ͒P�F�ŉ�ʂ�h��Ԃ������j
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
}

HRESULT Direct3D9::present()
{
	//��ʍX�V�i�o�b�N�o�b�t�@���t�����g�o�b�t�@�ɂ���j
	device->Present(NULL, NULL, NULL, NULL);
	return S_OK;
}

HRESULT Direct3D9::beginScene()
{
	if (device == NULL)return E_FAIL;
	return device->BeginScene();//�`��̂��߂̃V�[�����J�n����
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
	changeViewport(0, 0, viewPort.Width/2, viewPort.Height);
	return S_OK;
}

HRESULT Direct3D9::changeViewport2PWindow()
{
	changeViewport(viewPort.Width/2, 0, viewPort.Width/2, viewPort.Height);
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

	MFAIL(device->SetViewport(&vp),"�r���[�|�[�g�؂�ւ����s");

	return S_OK;
}