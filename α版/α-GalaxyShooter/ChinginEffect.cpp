//-----------------------------------------------------------------------------
// �����G�t�F�N�g���� [ChinginEffect.cpp]
// ����� �ђˏt�P
//-----------------------------------------------------------------------------
#include "ChinginEffect.h"
//=============================================================================
// ����������
//=============================================================================
void ChinginEffect::initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect)
{
	D3DXCreateSphere(device, 3.0f, 9, 9, &sphere, NULL);	// �����蔻��p�ɃX�t�B�A�����

	// �����G�t�F�N�g������
	for (int i = 0; i < CHINGIN_EFFECT; i++)
	{
		chinginEffect[i].setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		chinginEffect[i].setSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		D3DXMatrixIdentity(chinginEffect[i].getMatrixWorld());
		chinginEffect[i].getCollider()->initialize(device, chinginEffect[i].getPosition(), sphere);
		chinginEffect[i].setUse(false);
		chinginEffect[i].time = 0;
	}

	numOfUse = 0;
	renderList = NULL;
	// �C���X�^���V���O������
	instancingProcedure.initialize(device, effect, *_textureLoader->getTexture(textureLoaderNS::CHINGIN_EFFECT));
}
//=============================================================================
// �X�V����
//=============================================================================
void ChinginEffect::update(float frameTime)
{

	// �g�p���̃G�t�F�N�g�̋������X�V����
	for (int i = 0; i < CHINGIN_EFFECT; i++)
	{
		// �o�ĂȂ�������X�V���Ȃ�
		if (chinginEffect[i].getUse() == false) { continue; }

		// ���Ԃ��t���[���ɍ��킹��
		chinginEffect[i].time += frameTime;

		// �����G�t�F�N�g�ʒu�X�V
		chinginEffect[i].setPosition(*chinginEffect[i].getPosition() + *chinginEffect[i].getSpeed());

		// ���ԂɂȂ�����I��
		if (chinginEffect[i].time >= CHINGIN_EFFECT_TIME)
		{
			chinginEffect[i].setUse(false);
			numOfUse--;
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void ChinginEffect::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	// �g�p���̃G�t�F�N�g���C���X�^���V���O�`��ɗ���
	renderList = new D3DXVECTOR3[numOfUse];
	for (int i = 0; i < numOfUse; i++)
	{
		if (chinginEffect[i].getUse() == false) { continue; }

		renderList[i] = *chinginEffect[i].getPosition();
	}
	instancingProcedure.setNumOfRender(device, numOfUse, renderList);
	SAFE_DELETE_ARRAY(renderList)

		// �C���X�^���V���O�����_�[
		instancingProcedure.render(device, view, projection, cameraPosition);
}
//==================================================================
// �G�t�F�N�g�𔭐�������
//========================================================================================
void ChinginEffect::generateChinginEffect(int num, D3DXVECTOR3 positionToGenerate, D3DXVECTOR3 effectVec)
{
	// �G�t�F�N�g�J�E���g������
	int cnt = 0;

	for (int i = 0; i < CHINGIN_EFFECT; i++)
	{
		// �G�t�F�N�g���g�p����Ă��������Ȃ�
		if (chinginEffect[i].getUse()) { continue; }

		if (cnt < num)
		{
			// �����_���̃x�N�g���쐬
			D3DXVECTOR3 randVec((float)(rand() % 100 - 50), (float)(rand() % 100 - 50), (float)(rand() % 100 - 50));
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
			// �������ԏ�����
			chinginEffect[i].time = 0.0;
			// �G�t�F�N�g�ʒu�ݒ�
			chinginEffect[i].setPosition(positionToGenerate - (effectVec * 6));
			// �G�t�F�N�g�X�s�[�h�ݒ�
			chinginEffect[i].setSpeed(resultVec*((float)(rand() % 6 + 1) / 10.0f));
			D3DXMatrixIdentity(chinginEffect[i].getMatrixWorld());
			// �g�p��
			chinginEffect[i].setUse(true);
			// �g�p���G�t�F�N�g�J�E���g���Z
			numOfUse++;
		}
		// �G�t�F�N�g�J�E���g���Z
		cnt++;
	}
}
