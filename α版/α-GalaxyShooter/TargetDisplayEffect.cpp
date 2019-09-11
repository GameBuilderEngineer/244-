//=============================================================================
// �X�e���V������ [TargetDisplayEffect.cpp]
// ����� �ђˏt�P
//=============================================================================
#include "TargetDisplayEffect.h"
//*****************************************************************************
// �萔
//*****************************************************************************
const static int		WIDTH = WINDOW_WIDTH;						// �X�e���V�����T�C�Y
const static int		HEIGHT = WINDOW_HEIGHT;						// �X�e���V���c�T�C�Y	
const static float		POSITION_X_PLAYER1 = 0.0f;					// �X�e���V��X���W
const static float		POSITION_Y = 0.0f;							// �X�e���V��Y���W
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 TargetDisplayEffect::TargetTexture = NULL;		// �X�e���V���e�N�X�`��
int TargetDisplayEffect::cntUI = -1;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
TargetDisplayEffect::TargetDisplayEffect()
{
	cntUI++;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
TargetDisplayEffect::~TargetDisplayEffect()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT TargetDisplayEffect::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader *textureLoader, StaticMeshLoader* _staticMeshLoader)
{
	// �v���C���[�i���o�[
	playerNumber = _playerNumber;

	// �e�N�X�`����ǂݍ���
	setVisualDirectory();

	TargetTexture = *textureLoader->getTexture(textureLoaderNS::TARGET);

	//staticMeshLoader
	staticMeshLoader = _staticMeshLoader;

	// �X�e���V��������
	image.initialize(device,
		TargetTexture,						// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		WIDTH,								// ����
		HEIGHT,								// ����
		D3DXVECTOR3(POSITION_X_PLAYER1, POSITION_Y, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		TRGET_COLOR							// �F
	);

	// �X�e���V���L��
	isActive = true;

return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void TargetDisplayEffect::uninitialize(void)
{

	// �X�e���V���I��
	inactivate();
}
//=============================================================================
// �X�V����
//=============================================================================
void TargetDisplayEffect::update(void)
{
}
//=============================================================================
// �`�揈��
//=============================================================================
void TargetDisplayEffect::render(LPDIRECT3DDEVICE9 device)
{
	//device->SetRenderState(D3DRS_LIGHTING, false);
	image.render(device);
}
//=============================================================================
// �X�e���V���}�X�N����
//=============================================================================
void TargetDisplayEffect::renderStencilMask(LPDIRECT3DDEVICE9 device, unsigned char ste, D3DCMPFUNC cmp_func)
{
	// Z�o�b�t�@���g�p���Ȃ�
	device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// �X�e���V���o�b�t�@���g�p����
	device->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	// �X�e���V���o�b�t�@�̒l�Ɣ�r����Q�ƒl
	device->SetRenderState(D3DRS_STENCILREF, 2);

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
//=============================================================================
// �X�e���V���`�揈��
//=============================================================================
void TargetDisplayEffect::renderEffectImage(LPDIRECT3DDEVICE9 device, unsigned char ste, D3DCMPFUNC cmp_func)
{
	// �X�e���V���o�b�t�@�̒l�Ɣ�r����Q�ƒl
	device->SetRenderState(D3DRS_STENCILREF, ste);

	// ��r�֐��������^�̂Ƃ��X�e���V���e�X�g���i
	device->SetRenderState(D3DRS_STENCILFUNC, cmp_func);

	// �X�e���V���e�X�g�ɍ��i�����ꍇ�X�e���V���l�ɂ͉������Ȃ�
	device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

	// �t���[���o�b�t�@��RGB���������߂�悤�ɂ���
	device->SetRenderState(D3DRS_COLORWRITEENABLE,
		D3DCOLORWRITEENABLE_RED |
		D3DCOLORWRITEENABLE_GREEN |
		D3DCOLORWRITEENABLE_BLUE |
		D3DCOLORWRITEENABLE_ALPHA);

	// Z�o�b�t�@�ւ̏������݂�������
	device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}
//=============================================================================
// �X�e���V���J�n����
//=============================================================================
void TargetDisplayEffect::renderSetUp(LPDIRECT3DDEVICE9 device)
{
	// ������
	device->Clear(0, 0, D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL , D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	device->BeginScene();
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	device->SetRenderState(D3DRS_ALPHAREF, 0x01);
}
//=============================================================================
// �X�e���V���I������
//=============================================================================
void TargetDisplayEffect::renderStencilEnd(LPDIRECT3DDEVICE9 device)
{
	// �X�e���V���e�X�g�֎~
	device->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	device->Present(NULL, NULL, NULL, NULL);
}
//=============================================================================
// ��ʃX�e���V���`�揈��
//=============================================================================
void TargetDisplayEffect::renderGeneral(LPDIRECT3DDEVICE9 device, unsigned char ste, D3DCMPFUNC cmp_func)
{
	// Z�o�b�t�@�ݒ� => �L��
	device->SetRenderState(D3DRS_ZENABLE, TRUE);

	// ZBUFFER��r�ݒ�ύX => (�Q�ƒl <= �o�b�t�@�l)
	device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// �X�e���V���o�b�t�@ => �L��
	device->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	// �X�e���V���o�b�t�@�Ɣ�r����Q�ƒl�ݒ� => ref
	device->SetRenderState(D3DRS_STENCILREF, ste);

	// �X�e���V���o�b�t�@�̒l�ɑ΂��Ẵ}�X�N�ݒ� => 0xff(�S�Đ^)
	device->SetRenderState(D3DRS_STENCILMASK, 0xff);

	// �X�e���V���e�X�g�̔�r���@�ݒ� => 
	//		���̕`��ł̎Q�ƒl >= �X�e���V���o�b�t�@�̎Q�ƒl�Ȃ獇�i
	device->SetRenderState(D3DRS_STENCILFUNC, cmp_func);

	// �X�e���V���e�X�g�̌��ʂɑ΂��Ă̔��f�ݒ�
	device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
	device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
}
