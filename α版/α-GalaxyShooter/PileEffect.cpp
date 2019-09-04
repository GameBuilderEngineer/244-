//-----------------------------------------------------------------------------
// �p�C���G�t�F�N�g���� [PileEffect.cpp]
// ����� �ђˏt�P
//-----------------------------------------------------------------------------
#include "PileEffect.h"
//=============================================================================
// ����������
//=============================================================================
void PileEffect::initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect)
{
	D3DXCreateSphere(device, 3.0f, 9, 9, &sphere, NULL);	// �����蔻��p�ɃX�t�B�A�����

	for (int i = 0; i < PILE_EFFECT; i++)
	{
		pileEffect[i].setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		pileEffect[i].setSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		D3DXMatrixIdentity(pileEffect[i].getMatrixWorld());
		pileEffect[i].getCollider()->initialize(device, pileEffect[i].getPosition(), sphere);
		pileEffect[i].setUse(false);
		pileEffect[i].time = 0;
	}

	numOfUse = 0;
	renderList = NULL;

	instancingProcedure.initialize(device, effect, *_textureLoader->getTexture(textureLoaderNS::LOSE));
}
//=============================================================================
// �X�V����
//=============================================================================
void PileEffect::update(float frameTime)
{

	// �g�p���̃G�t�F�N�g�̋������X�V����
	for (int i = 0; i < PILE_EFFECT; i++)
	{
		if (pileEffect[i].getUse() == false) { continue; }

		pileEffect[i].time += frameTime;

		pileEffect[i].setPosition(*pileEffect[i].getPosition() + *pileEffect[i].getSpeed());


		// �I��
		if (pileEffect[i].time >= 0.05)
		{
			pileEffect[i].setUse(false);
			numOfUse--;
		}

	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void PileEffect::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	// �g�p���̃G�t�F�N�g���C���X�^���V���O�`��ɗ���
	renderList = new D3DXVECTOR3[numOfUse];
	for (int i = 0; i < numOfUse; i++)
	{
		if (pileEffect[i].getUse() == false) { continue; }

		renderList[i] = *pileEffect[i].getPosition();
	}
	instancingProcedure.setNumOfRender(device, numOfUse, renderList);
	SAFE_DELETE_ARRAY(renderList)

		instancingProcedure.render(device, view, projection, cameraPosition);
}
//==================================================================
// �G�t�F�N�g�𔭐�������
//========================================================================================
void PileEffect::generatePileEffect(int num, D3DXVECTOR3 positionToGenerate, D3DXVECTOR3 effectVec)
{
	int cnt = 0;


	for (int i = 0; i < PILE_EFFECT; i++)
	{
		if (pileEffect[i].getUse()) { continue; }

		if (cnt < num)
		{
			// �����_���̃x�N�g���쐬
			D3DXVECTOR3 randVec(0.0,0.0,0.0);
			// �O�σx�N�g���쐬
			D3DXVECTOR3 crossVec(0.0, 0.0, 0.0);
			// ���ʃx�N�g���쐬
			D3DXVECTOR3 resultVec(0.0, 0.0, 0.0);
			// �O�όv�Z
			D3DXVec3Cross(&crossVec, &effectVec, &randVec);
			D3DXVec3Normalize(&crossVec, &crossVec);//���K��
			// ���ʌv�Z
			resultVec = effectVec + crossVec;
			D3DXVec3Normalize(&resultVec, &resultVec);//���K��

			pileEffect[i].time = 0.0;
			pileEffect[i].setPosition(positionToGenerate);
			pileEffect[i].setSpeed(resultVec);
			D3DXMatrixIdentity(pileEffect[i].getMatrixWorld());
			pileEffect[i].setUse(true);
			numOfUse++;
		}
		cnt++;
	}
}
