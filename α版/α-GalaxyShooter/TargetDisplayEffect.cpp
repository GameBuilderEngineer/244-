#include "TargetDisplayEffect.h"

//*****************************************************************************
// �萔�E�}�N��
//*****************************************************************************
const static int		WIDTH = 1000;						// ���T�C�Y
const static int		HEIGHT = 1000;						// �c�T�C�Y	
															// X���W
const static float		POSITION_X_PLAYER1 = 0.0f;
const static float		POSITION_Y = WINDOW_HEIGHT - 700.0f;	// Y���W
#define DEFAULT_COLOR	(D3DCOLOR_RGBA(255, 255, 255, 255))	// �o�[�̐F

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 TargetDisplayEffect::TargetTexture = NULL;	// �e�N�X�`��
int TargetDisplayEffect::cntUI = -1;

TargetDisplayEffect::TargetDisplayEffect()
{

}


TargetDisplayEffect::~TargetDisplayEffect()
{

}

HRESULT TargetDisplayEffect::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader *textureLoader, StaticMeshLoader* _staticMeshLoader)
{
	playerNumber = _playerNumber;

	// �e�N�X�`����ǂݍ���
	setVisualDirectory();

	TargetTexture = *textureLoader->getTexture(textureLoaderNS::TARGET);

	//staticMeshLoader
	staticMeshLoader = _staticMeshLoader;

	image.initialize(device,
		TargetTexture,						// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		WIDTH,								// ����
		HEIGHT,								// ����
		D3DXVECTOR3(POSITION_X_PLAYER1, POSITION_Y, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);

	isActive = true;



return S_OK;
}

void TargetDisplayEffect::uninitialize(void)
{
	image.setTexture(NULL);

	// �C���X�^���X�����݂��Ȃ���΃e�N�X�`�����
	cntUI--;
	if (cntUI < 0)
	{
		SAFE_RELEASE(TargetTexture)
	}

	inactivate();
}

void TargetDisplayEffect::update(void)
{

}

void TargetDisplayEffect::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	
	if (!isActive) return;

	image.render(device);

	// �X�e���V���e�X�g�֎~
	device->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	device->Present(NULL, NULL, NULL, NULL);

}

void TargetDisplayEffect::renderStencilMask(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	device->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p

	device->Clear(0, 0, D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL | D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	device->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	// �X�e���V���}�X�N�̐ݒ�
	device->SetRenderState(D3DRS_STENCILMASK, 0xff);

	// �X�e���V���e�X�g�ɋ����I�ɍ��i
	device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);

	// �o�b�N�o�b�t�@��RBG�l���������܂Ȃ�
	device->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00);

	// �X�e���V���e�X�g�ɕs���i�̏ꍇ�̓X�e���V���l�ɉ������Ȃ�
	device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);

	// Z�e�X�g�ɕs���i�ȏꍇ�̓X�e���V���l�ɉ������Ȃ�
	device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);

	// �X�e���V���e�X�g�ɍ��i�̏ꍇ�X�e���V���l��1�ɂ���
	device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCRSAT);
}

void TargetDisplayEffect::renderEffectImage(LPDIRECT3DDEVICE9 device)
{

	// �X�e���V���o�b�t�@�̒l�Ɣ�r����Q�ƒl
	device->SetRenderState(D3DRS_STENCILREF, 0x01);

	// ��r�֐��������^�̂Ƃ��X�e���V���e�X�g���i
	device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL);

	// �X�e���V���e�X�g�ɍ��i�����ꍇ�X�e���V���l�ɂ͉������Ȃ�
	device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

	// �X�e���V���o�b�t�@�̒l�Ɣ�r����Q�ƒl
	device->SetRenderState(D3DRS_STENCILREF, 0x01);

	// ��r�֐��̐ݒ�
	device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL);

	// �t���[���o�b�t�@��RGB���������߂�悤�ɂ���
	device->SetRenderState(D3DRS_COLORWRITEENABLE,
		D3DCOLORWRITEENABLE_RED |
		D3DCOLORWRITEENABLE_GREEN |
		D3DCOLORWRITEENABLE_BLUE |
		D3DCOLORWRITEENABLE_ALPHA);

	// Z�o�b�t�@�ւ̏������݂�������
	device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}