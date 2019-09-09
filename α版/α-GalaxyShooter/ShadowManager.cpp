//-----------------------------------------------------------------------------
// �e���� [ShadowManager.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/9/9
//-----------------------------------------------------------------------------
#include "ShadowManager.h"

//=============================================================================
// �C���X�^���V���O�`��N���X�F����������
//=============================================================================
HRESULT InstancingShadowRender::initialize(LPDIRECT3DDEVICE9 device, LPD3DXEFFECT effect, LPDIRECT3DTEXTURE9 texture)
{
	InstancingBillboard::initialize(device, effect, texture);
	return S_OK;
}


//=============================================================================
// �C���X�^���V���O�`��N���X�F�`�揈��
//=============================================================================
void InstancingShadowRender::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
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
}


//=============================================================================
//  �e�Ǘ��N���X�F����������
//=============================================================================
void ShadowManager::initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect)
{
	shadowMax = INITIAL_NUM_SHADOW;							// �Q�[���J�n���̉e�̐���ݒ�
	shadow = (Shadow**)malloc(sizeof(Shadow*) * shadowMax);	// �|�C���^�z��m��
	if (shadow == NULL)
	{
		MessageBox(NULL, TEXT("�������̊m�ۂɎ��s���܂����B\n�A�v���P�[�V�������I�����܂��B"),
			TEXT("SystemError"), MB_OK);
		PostQuitMessage(0);
	}
	ZeroMemory(shadow, sizeof(Shadow*) * INITIAL_NUM_SHADOW);// �z���null���Z�b�g����
	
	numOfUse = 0;
	renderList = NULL;

	instancingProcedure.initialize(device, effect, *_textureLoader->getTexture(textureLoaderNS::UI_REVIVAL_GAUGE));
}


////=============================================================================
////  �e�Ǘ��N���X�F�I������
////=============================================================================
//void ShadowManager::uninitialize(void)
//{
//	for (int i = 0; i < shadowMax; i++)
//	{
//		if (shadow[i] != NULL) { SAFE_DELETE(shadow[i]) }
//	}
//	free(shadow);
//}
//
//
////=============================================================================
////  �e�Ǘ��N���X�F�X�V����
////=============================================================================
//void ShadowManager::update(Sound* _sound, float frameTime)
//{
//	// �g�p���̉e�̋������X�V����
//	for (int i = 0; i < shadowMax; i++)
//	{
//		if (shadow[i] == NULL) { continue; }
//
//	}
//
//#if 1	// �e������g���Ă��Ȃ��^�C�~���O(=�|�C���^�z�񂪑S��null)�Ŕz������T�C�Y����
//	if (numOfUse == 0 && shadowMax > INITIAL_NUM_SHADOW)
//	{
//		shadowMax = INITIAL_NUM_SHADOW;
//		Shadow** temp = (Shadow**)realloc(shadow, sizeof(Shadow*) * INITIAL_NUM_SHADOW);
//		if (temp == NULL)
//		{
//			MessageBox(NULL, TEXT("�������̊m�ۂɎ��s���܂����B\n�A�v���P�[�V�������I�����܂��B"),
//				TEXT("SystemError"), MB_OK);
//			PostQuitMessage(0);
//		}
//		shadow = temp;
//	}
//#endif
//}
//
//
////=============================================================================
////  �e�Ǘ��N���X�F�`�揈��
////=============================================================================
//void ShadowManager::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
//{
//	// �g�p���̉e���C���X�^���V���O�`��ɗ���
//	renderList = new D3DXVECTOR3[numOfUse];
//	int renderIndex = 0;
//	for (int i = 0; i < shadowMax; i++)
//	{
//		if (shadow[i] == NULL) { continue; }
//
//		renderList[renderIndex++] = *shadow[i]->getPosition();
//	}
//	instancingProcedure.setNumOfRender(device, numOfUse, renderList);
//	SAFE_DELETE_ARRAY(renderList)
//
//	instancingProcedure.render(device, view, projection, cameraPosition);
//}
//
//
////=============================================================================
//// �e�̈ړ���ݒ�
////=============================================================================
//D3DXVECTOR3 ShadowManager::moveSpeed(D3DXVECTOR3 position, D3DXVECTOR3 targetPosition)
//{
//	D3DXVECTOR3 speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	D3DXVECTOR3 moveDirection = targetPosition - position;
//	//float distance = D3DXVec3Length(&moveDirection);
//	//float magneticeForce = (target.amount*amount) / distance;
//	D3DXVec3Normalize(&moveDirection, &moveDirection);
//	speed += moveDirection * 2.0f;// ���̂ւ�͂܂��K��
//
//	return speed;
//}


////=============================================================================
//// �e�𔭐�������
////=============================================================================
//void ShadowManager::generateShadow(int num, D3DXVECTOR3 setPosition, Player* target)
//{
//	int newIndex = 0;	// �V�K�����e�C���X�^���X�̐�
//
//	for (int i = 0; i < shadowMax; i++)
//	{
//		if (newIndex == num) { break; }
//		if (shadow[i] != NULL) { continue; }
//
//		shadow[i] = new Shadow;
//		newIndex++;
//
//		// �p�����[�^�ݒ�
//		shadow[i]->setPosition(setPosition);
//		shadow[i]->setTarget(target);
//		shadow[i]->setSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
//		D3DXMatrixIdentity(shadow[i]->getMatrixWorld());
//		numOfUse++;
//
//		//----------------------------------------------------------------------------
//		// �|�C���^�z��̗v�f���𒴂��ĉe���m�ۂ��ꂽ�ꍇ�ɔz�񎩑̂��m�ۂ�����
//		//----------------------------------------------------------------------------
//		static const int ADDITIONAL_NUM_SHADOW = 200;	// �ǉ��v�f��
//		if (i == shadowMax - 1 && newIndex == num)
//		{
//			shadowMax += ADDITIONAL_NUM_SHADOW;
//			Shadow** temp = (Shadow**)realloc(shadow, sizeof(Shadow*) * shadowMax);
//			if (temp == NULL)
//			{
//				MessageBox(NULL, TEXT("�������̊m�ۂɎ��s���܂����B\n�A�v���P�[�V�������I�����܂��B"),
//					TEXT("SystemError"), MB_OK);
//				PostQuitMessage(0);
//			}
//			shadow = temp;
//
//			// �V�K�m�ە��̃�������null���Z�b�g����
//			ZeroMemory(&shadow[i + 1], sizeof(Shadow*) * ADDITIONAL_NUM_SHADOW);
//		}
//	}
//}


//void ShadowManager::reverseAmount()
//{
//	amount *= -1.0f;
//}

