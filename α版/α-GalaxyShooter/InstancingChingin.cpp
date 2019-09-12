//-----------------------------------------------------------------------------
// �`���M������ [Chingin.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/8/1
//-----------------------------------------------------------------------------
#include "InstancingChingin.h"


//=============================================================================
// ����������
//=============================================================================
HRESULT InstancingChingin::initialize(LPDIRECT3DDEVICE9 device, LPD3DXEFFECT effect, LPDIRECT3DTEXTURE9 texture)
{
	InstancingBillboard::initialize(device, effect, texture);

	return S_OK;
}


//=============================================================================
// �`�揈��
//=============================================================================
void InstancingChingin::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	if (!onRender)return;
	if (renderNum <= 0)return;
	// ��]��ł������B
	D3DXMATRIX cancelRotation = view;
	cancelRotation._41 = cancelRotation._42 = cancelRotation._43 = 0;
	D3DXMatrixInverse(&cancelRotation, NULL, &cancelRotation);
	//���e�X�g
	device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	device->SetRenderState(D3DRS_ALPHAREF, 0x00);
	// ���u�����h���s��
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// ���\�[�X�J���[�̎w��
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	// ���f�X�e�B�l�[�V�����J���[�̎w��
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
	//// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	//device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);	// �A���t�@�u�����f�B���O����
	//device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_CURRENT);		// �ŏ��̃A���t�@����
	//device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);		// �Q�Ԗڂ̃A���t�@����

	// Z�o�b�t�@�؂�
	device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// ���C�e�B���O�𖳌��ɂ���
	device->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�C���X�^���X�錾
	device->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | renderNum);
	device->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	// ���_�錾��ʒm
	device->SetVertexDeclaration(declation);

	//�f�o�C�X�f�[�^�X�g���[���Ƀ��b�V���̒��_�o�b�t�@���o�C���h
	device->SetStreamSource(0, vertexBuffer, 0, sizeof(InstancingBillboardVertex));
	device->SetStreamSource(1, positionBuffer, 0, sizeof(D3DXVECTOR3));

	//�C���f�b�N�X�o�b�t�@���Z�b�g
	device->SetIndices(indexBuffer);

	effect->SetTechnique("mainTechnique");
	//effect->SetMatrix("cancelRotation", &cancelRotation);
	effect->SetMatrix("matrixProjection", &projection);
	effect->SetMatrix("matrixView", &view);
	effect->SetTexture("planeTexture", texture);
	effect->Begin(0, 0);
	effect->BeginPass(0);

	//device->SetTexture(0, texture);
	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	////device->SetTexture(0, NULL);
	effect->EndPass();
	effect->End();

	//��n��
	device->SetStreamSourceFreq(0, 1);
	device->SetStreamSourceFreq(1, 1);
	// ���u�����h��؂�
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	// ���C�e�B���O��L���ɂ���
	device->SetRenderState(D3DRS_LIGHTING, TRUE);
	// Z�o�b�t�@�I��
	device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}



