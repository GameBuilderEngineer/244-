//-----------------------------------------------------------------------------
// �C���X�^���V���O�G�t�F�N�g���� [InstancingEffect.cpp]
// ����� �ђˏt�P
//-----------------------------------------------------------------------------
#include "InstancingEffect.h"
//=============================================================================
// ����������
//=============================================================================
HRESULT InstancingEffect::initialize(LPDIRECT3DDEVICE9 device, LPD3DXEFFECT effect, LPDIRECT3DTEXTURE9 texture)
{
	InstancingBillboard::initialize(device, effect, texture);

	return S_OK;
}
//=============================================================================
// �`�揈��
//=============================================================================
void InstancingEffect::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
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

	//���Z����
	device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);	// ���� = �]����(DEST) �{ �]����(SRC)
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ���C���e�B���O�𖳌��ɂ���
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

	// ���C���e�B���O��L���ɂ���
	device->SetRenderState(D3DRS_LIGHTING, TRUE);
}
