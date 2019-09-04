//-----------------------------------------------------------------------------
// �e�G�t�F�N�g���� [BulletEffect.cpp]
// ����� �ђˏt�P
//-----------------------------------------------------------------------------
#include "BulletEffect.h"
//=============================================================================
// ����������
//=============================================================================
void BulletEffect::initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect)
{
	D3DXCreateSphere(device, 3.0f, 9, 9, &sphere, NULL);	// �����蔻��p�ɃX�t�B�A�����

	// �e�G�t�F�N�g������
	for (int i = 0; i < BULLET_EFFECT; i++)
	{
		bulletEffect[i].setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		bulletEffect[i].setSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		D3DXMatrixIdentity(bulletEffect[i].getMatrixWorld());
		bulletEffect[i].getCollider()->initialize(device, bulletEffect[i].getPosition(), sphere);
		bulletEffect[i].setUse(false);
		bulletEffect[i].time = 0;
	}

	numOfUse = 0;
	renderList = NULL;

	// �C���X�^���V���O������
	instancingProcedure.initialize(device, effect, *_textureLoader->getTexture(textureLoaderNS::BULLET_EFFECT));

}
//=============================================================================
// �X�V����
//=============================================================================
void BulletEffect::update(float frameTime)
{

	// �g�p���̃G�t�F�N�g�̋������X�V����
	for (int i = 0; i < BULLET_EFFECT; i++)
	{
		// �o�ĂȂ�������X�V���Ȃ�
		if (bulletEffect[i].getUse() == false) { continue; }

		// ���Ԃ��t���[���ɍ��킹��
		bulletEffect[i].time += frameTime;

		// �e�G�t�F�N�g�ʒu�X�V
		bulletEffect[i].setPosition(*bulletEffect[i].getPosition() + *bulletEffect[i].getSpeed());

		// ���ԂɂȂ�����I��
		if (bulletEffect[i].time >= BULLET_EFFECT_TIME)
		{
			bulletEffect[i].setUse(false);
			numOfUse--;
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void BulletEffect::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	// �g�p���̃G�t�F�N�g���C���X�^���V���O�`��ɗ���
	renderList = new D3DXVECTOR3[numOfUse];
	for (int i = 0; i < numOfUse; i++)
	{
		if (bulletEffect[i].getUse() == false) { continue; }

		renderList[i] = *bulletEffect[i].getPosition();
	}
	instancingProcedure.setNumOfRender(device, numOfUse, renderList);
	SAFE_DELETE_ARRAY(renderList)

	// �C���X�^���V���O�����_�[
	instancingProcedure.render(device, view, projection, cameraPosition);
}
//==================================================================
// �G�t�F�N�g�𔭐�������
//========================================================================================
void BulletEffect::generateBulletEffect(int num, D3DXVECTOR3 positionToGenerate, D3DXVECTOR3 effectVec)
{
	// �G�t�F�N�g�J�E���g������
	int cnt = 0;

	for (int i = 0; i < BULLET_EFFECT; i++)
	{
		// �G�t�F�N�g���g�p����Ă��������Ȃ�
		if (bulletEffect[i].getUse()) { continue; }

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
			resultVec = effectVec + crossVec * 0.6;
			D3DXVec3Normalize(&resultVec, &resultVec);//���K��
			// �������ԏ�����
			bulletEffect[i].time = 0.0;
			// �G�t�F�N�g�ʒu�ݒ�
			bulletEffect[i].setPosition(positionToGenerate);
			// �G�t�F�N�g�X�s�[�h�ݒ�
			bulletEffect[i].setSpeed(resultVec*((float)(rand() % 20) / 10.0f));
			D3DXMatrixIdentity(bulletEffect[i].getMatrixWorld());
			// �g�p��
			bulletEffect[i].setUse(true);
			// �g�p���G�t�F�N�g�J�E���g���Z
			numOfUse++;
		}
		// �G�t�F�N�g�J�E���g���Z
		cnt++;
	}
}
