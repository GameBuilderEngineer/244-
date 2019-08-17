//===================================================================================================================================
//�yPointSprite.h�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/05/16
// [�X�V��]2019/08/07
//===================================================================================================================================
#include "PointSprite.h"
using namespace pointSpriteNS;

PointSprite::PointSprite()
{
	pTexture = NULL;
}

PointSprite::~PointSprite()
{

}

HRESULT PointSprite::initilaize(LPDIRECT3DDEVICE9 device)
{
	setVisualDirectory();
	//�|�C���g�X�v���C�g�ɓ\��e�N�X�`���I�u�W�F�N�g���쐬
	if (FAILED(D3DXCreateTextureFromFileEx(device, "Sprite.jpg", (UINT)WIDTH, (UINT)HEIGHT, 0, 0, D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT,
		0xff000000, NULL, NULL, &pTexture)))
	{
		MessageBox(0, "�e�N�X�`���̍쐬�Ɏ��s���܂���", "", MB_OK);
		return E_FAIL;
	}
	for (int i = 0; i < POINT_NUM; i++)
	{
		vertex[i].coord = D3DXVECTOR3((float)((rand()%1000)-500),(float)((rand()%1000)-500),(float)((rand()%1000)-500));
		vertex[i].color = D3DCOLOR_ARGB(255, 255, 255, 255);
		vertex[i].scale = 0.001f;
		size[i] = (float)((rand() % 200)/1000);
	}
	return S_OK;
}

void PointSprite::render(LPDIRECT3DDEVICE9 device, D3DXVECTOR3 cameraPositon)
{
	for (int i = 0; i < POINT_NUM; i++)
	{
		float rate = 
			between2VectorLength(cameraPositon, vertex[i].coord) /
			between2VectorLength(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 500.0f));
		float scale = max(size[i] - size[i]*rate, 0.001f);
		vertex[i].scale = scale;

		size[i] += 0.001;
		if (size[i] > 0.2)size[i] = 0.001f;
	}

	//���̃����_�[�X�e�[�g�ɂ��A"�P�Ȃ�F�t���̃|�C���g"���ꂼ�ꂪ1���_�݂̂ŃX�v���C�g�ɂȂ��Ă����
	device->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	device->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	//device->SetRenderState(D3DRS_POINTSIZE, GET_ADDRESS(fScale[i]));//�Ȃ��A���_�ɃX�P�[�����iFVF_SCALE�j���������Ă���ꍇ�́A���̎w��͖�������܂��B�i�{�T���v���ł͗L���ł��j
	//���h����ǂ�����ׂɃA���t�@�u�����f�B���O��ݒ肷��
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//���C�e�B���O�v�Z�͂��Ȃ��B�[�x�o�b�t�@�ɂ͏������܂Ȃ�
	device->SetRenderState(D3DRS_LIGHTING, false);
	device->SetRenderState(D3DRS_ZWRITEENABLE, false);
	//�|�C���g�X�v���C�g�p�̃e�N�X�`�����Z�b�g
	device->SetTexture(0, pTexture);
	//���_�̌^���Z�b�g
	device->SetFVF(D3DFVF_XYZ| D3DFVF_PSIZE | D3DFVF_DIFFUSE);
	//�����_�����O�@�����2�̃|�C���g�X�v���C�g�̂�
	device->DrawPrimitiveUP(D3DPT_POINTLIST, POINT_NUM, &vertex, sizeof(COLOR_VERTEX));
	
	//���C�e�B���O�v�Z�͂��Ȃ��B�@�[�x�o�b�t�@�ɂ͏������܂Ȃ�
	device->SetRenderState(D3DRS_LIGHTING, true);
	device->SetRenderState(D3DRS_ZWRITEENABLE, true);
	//���̃����_�[�X�e�[�g�ɂ��A"�P�Ȃ�F�t���̃|�C���g"���ꂼ�ꂪ1���_�݂̂ŃX�v���C�g�ɂȂ��Ă����
	device->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	device->SetRenderState(D3DRS_POINTSCALEENABLE, false);

}