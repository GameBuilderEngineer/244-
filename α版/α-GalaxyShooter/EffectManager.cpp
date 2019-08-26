//-----------------------------------------------------------------------------
// �G�t�F�N�g�}�l�[�W���[���� [EffectManager.cpp]
// ����� �ђˏt�P
//-----------------------------------------------------------------------------
#include "EffectManager.h"
//=============================================================================
// ����������
//=============================================================================
void EffectManager::initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect)
{
	D3DXCreateSphere(device, 3.0f, 9, 9, &sphere, NULL);	// �����蔻��p�ɃX�t�B�A�����

	for (int i = 0; i < NUM_EFFECT; i++)
	{
		effectIns[i].setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		effectIns[i].setSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		D3DXMatrixIdentity(effectIns[i].getMatrixWorld());
		effectIns[i].getCollider()->initialize(device, effectIns[i].getPosition(), sphere);
		effectIns[i].setUse(false);
		effectIns[i].time = 0;
	}

	numOfUse = 0;
	renderList = NULL;

	instancingProcedure.initialize(device, effect, *_textureLoader->getTexture(textureLoaderNS::BULLET_EFFECT));
}
//=============================================================================
// �X�V����
//=============================================================================
void EffectManager::update(float frameTime, Player* player)
{

	// �g�p���̃G�t�F�N�g�̋������X�V����
	for (int i = 0; i < NUM_EFFECT; i++)
	{
		if (effectIns[i].getUse() == false) { continue; }

		effectIns[i].time += frameTime;

		effectIns[i].setPosition(*effectIns[i].getPosition() + *effectIns[i].getSpeed());

		// �I��
		if (effectIns[i].time >=0.1)
		{
			effectIns[i].setUse(false);
			numOfUse--;
		}

	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void EffectManager::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	// �g�p���̃G�t�F�N�g���C���X�^���V���O�`��ɗ���
	renderList = new D3DXVECTOR3[numOfUse];
	for (int i = 0; i < numOfUse; i++)
	{
		if (effectIns[i].getUse() == false) { continue; }

		renderList[i] = *effectIns[i].getPosition();
	}
	instancingProcedure.setNumOfRender(device, numOfUse, renderList);
	SAFE_DELETE_ARRAY(renderList)

		instancingProcedure.render(device, view, projection, cameraPosition);
}
//==================================================================
// �G�t�F�N�g�𔭐�������
//========================================================================================
void EffectManager::generateEffect(int num, D3DXVECTOR3 positionToGenerate, D3DXVECTOR3 effectVec)
{
	int cnt = 0;


	for (int i = 0; i < NUM_EFFECT; i++)
	{
		if (effectIns[i].getUse()) { continue; }

		if (cnt < num)
		{
			// �����_���̃x�N�g���쐬
			D3DXVECTOR3 randVec(rand()%100-50, rand() % 100 - 50, rand() % 100 - 50);
			// �O�σx�N�g���쐬
			D3DXVECTOR3 crossVec(0.0,0.0,0.0);
			// ���ʃx�N�g���쐬
			D3DXVECTOR3 resultVec(0.0, 0.0, 0.0);
			// �O�όv�Z
			D3DXVec3Cross(&crossVec, &effectVec, &randVec);
			D3DXVec3Normalize(&crossVec, &crossVec);//���K��
			// ���ʌv�Z
			resultVec=effectVec + crossVec*0.4;
			D3DXVec3Normalize(&resultVec, &resultVec);//���K��

			effectIns[i].time = 0.0;
			effectIns[i].setPosition(positionToGenerate);
			effectIns[i].setSpeed(resultVec*( (float)(rand() % 20) /10.0f));
			D3DXMatrixIdentity(effectIns[i].getMatrixWorld());
			effectIns[i].setUse(true);
			numOfUse++;
		}
		cnt++;
	}

}
//void ChinginManager::reverseAmount()
//{
//	amount *= -1.0f;
//}

