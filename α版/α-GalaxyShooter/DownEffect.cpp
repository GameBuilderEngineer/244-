//-----------------------------------------------------------------------------
// �_�E���G�t�F�N�g���� [DownEffect.cpp]
// ����� �ђˏt�P
//-----------------------------------------------------------------------------
#include "DownEffect.h"
//=============================================================================
// ����������
//=============================================================================
void DownEffect::initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect)
{
	D3DXCreateSphere(device, 3.0f, 9, 9, &sphere, NULL);	// �����蔻��p�ɃX�t�B�A�����

	// �_�E���G�t�F�N�g������
	for (int i = 0; i < DOWN_EFFECT; i++)
	{
		downEffect[i].setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		downEffect[i].setSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		D3DXMatrixIdentity(downEffect[i].getMatrixWorld());
		downEffect[i].getCollider()->initialize(device, downEffect[i].getPosition(), sphere);
		downEffect[i].setUse(false);
		downEffect[i].time = 0;
	}

	numOfUse = 0;
	renderList = NULL;

	// �C���X�^���V���O������
	instancingProcedure.initialize(device, effect, *_textureLoader->getTexture(textureLoaderNS::DOWN_EFFECT));
}
//=============================================================================
// �X�V����
//=============================================================================
void DownEffect::update(float frameTime)
{

	// �g�p���̃G�t�F�N�g�̋������X�V����
	for (int i = 0; i < DOWN_EFFECT; i++)
	{
		// �o�ĂȂ�������X�V���Ȃ�
		if (downEffect[i].getUse() == false) { continue; }

		// ���Ԃ��t���[���ɍ��킹��
		downEffect[i].time += frameTime;

		// �_�E���G�t�F�N�g�ʒu�X�V
		downEffect[i].setPosition(*downEffect[i].getPosition() + *downEffect[i].getSpeed());

		// ���ԂɂȂ�����I��
		if (downEffect[i].time >= DOWN_EFFECT_TIME)
		{
			downEffect[i].setUse(false);
			numOfUse--;
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DownEffect::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	// �g�p���̃G�t�F�N�g���C���X�^���V���O�`��ɗ���
	renderList = new D3DXVECTOR3[numOfUse];
	for (int i = 0; i < numOfUse; i++)
	{
		if (downEffect[i].getUse() == false) { continue; }

		renderList[i] = *downEffect[i].getPosition();
	}
	instancingProcedure.setNumOfRender(device, numOfUse, renderList);
	SAFE_DELETE_ARRAY(renderList)

	// �C���X�^���V���O�����_�[
	instancingProcedure.render(device, view, projection, cameraPosition);
}
//==================================================================
// �G�t�F�N�g�𔭐�������
//========================================================================================
void DownEffect::generateDownEffect(int num, D3DXVECTOR3 positionToGenerate, D3DXVECTOR3 effectVec)
{
	// �G�t�F�N�g�J�E���g������
	int cnt = 0;

	for (int i = 0; i < DOWN_EFFECT; i++)
	{
		// �G�t�F�N�g���g�p����Ă��������Ȃ�
		if (downEffect[i].getUse()) { continue; }

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
			resultVec = effectVec + crossVec*0.8;
			D3DXVec3Normalize(&resultVec, &resultVec);//���K��
			// �������ԏ�����
			downEffect[i].time = 0.0;
			// �G�t�F�N�g�ʒu�ݒ�
			downEffect[i].setPosition(positionToGenerate - (effectVec*6));
			// �G�t�F�N�g�X�s�[�h�ݒ�
			downEffect[i].setSpeed(resultVec*((float)(rand() % 6+1) / 10.0f));
			D3DXMatrixIdentity(downEffect[i].getMatrixWorld());
			// �g�p��
			downEffect[i].setUse(true);
			// �g�p���G�t�F�N�g�J�E���g���Z
			numOfUse++;
		}
		// �G�t�F�N�g�J�E���g���Z
		cnt++;
	}
}
