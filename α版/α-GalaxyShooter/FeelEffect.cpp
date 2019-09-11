//-----------------------------------------------------------------------------
// �񕜃G�t�F�N�g���� [FeelEffect.cpp]
// ����� �ђˏt�P
//-----------------------------------------------------------------------------
#include "FeelEffect.h"
//=============================================================================
// ����������
//=============================================================================
void FeelEffect::initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect)
{
	D3DXCreateSphere(device, 3.0f, 9, 9, &sphere, NULL);	// �����蔻��p�ɃX�t�B�A�����

	// �񕜃G�t�F�N�g������
	for (int i = 0; i < FEEL_EFFECT; i++)
	{
		feelEffect[i].setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		feelEffect[i].setSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		D3DXMatrixIdentity(feelEffect[i].getMatrixWorld());
		feelEffect[i].getCollider()->initialize(device, feelEffect[i].getPosition(), sphere);
		feelEffect[i].setUse(false);
		feelEffect[i].time = 0;
	}

	numOfUse = 0;
	renderList = NULL;
	feel = false;
	// �C���X�^���V���O������
	instancingProcedure.initialize(device, effect, *_textureLoader->getTexture(textureLoaderNS::EFFECT_FEEL));
}
//=============================================================================
// �X�V����
//=============================================================================
void FeelEffect::update(float frameTime)
{
	// �g�p���̃G�t�F�N�g�̋������X�V����
	for (int i = 0; i < FEEL_EFFECT; i++)
	{
		// �o�Ă��Ȃ�������X�V���Ȃ�
		if (feelEffect[i].getUse() == false) { continue; }

		// ���Ԃ��t���[���ɍ��킹��
		feelEffect[i].time += frameTime;

		// �G�t�F�N�g�ʒu�X�V
		feelEffect[i].setPosition(*feelEffect[i].getPosition() + *feelEffect[i].getSpeed());

		// ���ԂɂȂ�����I��
		if (feelEffect[i].time >= 0.2)
		{
			feelEffect[i].setUse(false);
			numOfUse--;
			feel = false;
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void FeelEffect::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	// �g�p���̃G�t�F�N�g���C���X�^���V���O�`��ɗ���
	renderList = new D3DXVECTOR3[numOfUse];
	for (int i = 0; i < numOfUse; i++)
	{
		if (feelEffect[i].getUse() == false) { continue; }

		renderList[i] = *feelEffect[i].getPosition();
	}
	instancingProcedure.setNumOfRender(device, numOfUse, renderList);
	SAFE_DELETE_ARRAY(renderList)

		// �C���X�^���V���O�`��
		instancingProcedure.render(device, view, projection, cameraPosition);
}
//==================================================================
// �G�t�F�N�g�𔭐�������
//========================================================================================
void FeelEffect::generateFeelEffect(int num, D3DXVECTOR3 positionToGenerate, D3DXVECTOR3 effectVec)
{
	// �G�t�F�N�g�J�E���g������
	int cnt = 0;

	for (int i = 0; i < FEEL_EFFECT; i++)
	{
		// �G�t�F�N�g���g�p����Ă��������Ȃ�
		if (feelEffect[i].getUse()) { continue; }

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
			resultVec = effectVec + crossVec * 0.8;
			D3DXVec3Normalize(&resultVec, &resultVec);//���K��
			// �������ԏ�����
			feelEffect[i].time = 0.0;
			// �G�t�F�N�g�ʒu�ݒ�
			feelEffect[i].setPosition(positionToGenerate - (effectVec * 8));
			// �G�t�F�N�g�X�s�[�h�ݒ�
			feelEffect[i].setSpeed(resultVec*((float)(rand() % 20) / 10.0f));
			D3DXMatrixIdentity(feelEffect[i].getMatrixWorld());
			// �g�p��
			feelEffect[i].setUse(true);
			// �g�p���G�t�F�N�g�J�E���g���Z
			numOfUse++;
		}
		// �G�t�F�N�g�J�E���g���Z
		cnt++;
	}
}
