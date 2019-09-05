//-----------------------------------------------------------------------------
// ���C���G�t�F�N�g���� [LineEffect.cpp]
// ����� �ђˏt�P
//-----------------------------------------------------------------------------
#include "LineEffect.h"
//=============================================================================
// ����������
//=============================================================================
void LineEffect::initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect)
{
	D3DXCreateSphere(device, 3.0f, 9, 9, &sphere, NULL);	// �����蔻��p�ɃX�t�B�A�����

	// ���C���G�t�F�N�g������
	for (int i = 0; i < LINE_EFFECT; i++)
	{
		lineEffect[i].setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		lineEffect[i].setSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		D3DXMatrixIdentity(lineEffect[i].getMatrixWorld());
		lineEffect[i].getCollider()->initialize(device, lineEffect[i].getPosition(), sphere);
		lineEffect[i].setUse(false);
		lineEffect[i].time = 0;
	}

	numOfUse = 0;
	renderList = NULL;
	// �C���X�^���V���O������
	instancingProcedure.initialize(device, effect, *_textureLoader->getTexture(textureLoaderNS::LINE_EFFECT));
}
//=============================================================================
// �X�V����
//=============================================================================
void LineEffect::update(float frameTime)
{
	// �g�p���̃G�t�F�N�g�̋������X�V����
	for (int i = 0; i < LINE_EFFECT; i++)
	{
		// �o�Ă��Ȃ�������X�V���Ȃ�
		if (lineEffect[i].getUse() == false) { continue; }

		// ���Ԃ��t���[���ɍ��킹��
		lineEffect[i].time += frameTime;

		// ���ԂɂȂ�����I��
		if (lineEffect[i].time >= 0.2)
		{
			lineEffect[i].setUse(false);
			numOfUse--;
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void LineEffect::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	// �g�p���̃G�t�F�N�g���C���X�^���V���O�`��ɗ���
	renderList = new D3DXVECTOR3[numOfUse];
	for (int i = 0; i < numOfUse; i++)
	{
		if (lineEffect[i].getUse() == false) { continue; }

		renderList[i] = *lineEffect[i].getPosition();
	}
	instancingProcedure.setNumOfRender(device, numOfUse, renderList);
	SAFE_DELETE_ARRAY(renderList)

		// �C���X�^���V���O�`��
		instancingProcedure.render(device, view, projection, cameraPosition);
}
//==================================================================
// �G�t�F�N�g�𔭐�������
//========================================================================================
void LineEffect::generateLineEffect(int num, D3DXVECTOR3 positionToGenerate, D3DXVECTOR3 effectVec)
{
	// �G�t�F�N�g�J�E���g������
	int cnt = 0;

	for (int i = 0; i < LINE_EFFECT; i++)
	{
		// �G�t�F�N�g���g�p����Ă��������Ȃ�
		if (lineEffect[i].getUse()) { continue; }

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
			lineEffect[i].time = 0.0;
			// �G�t�F�N�g�ʒu�ݒ�
			lineEffect[i].setPosition(positionToGenerate);
			// �G�t�F�N�g�X�s�[�h�ݒ�
			lineEffect[i].setSpeed(resultVec*((float)(rand() % 10) / 10.0f));
			D3DXMatrixIdentity(lineEffect[i].getMatrixWorld());
			// �g�p��
			lineEffect[i].setUse(true);
			// �g�p���G�t�F�N�g�J�E���g���Z
			numOfUse++;
		}
		// �G�t�F�N�g�J�E���g���Z
		cnt++;
	}
}
