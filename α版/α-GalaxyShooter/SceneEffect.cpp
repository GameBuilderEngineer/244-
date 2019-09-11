//-----------------------------------------------------------------------------
// �V�[���G�t�F�N�g���� [SceneEffect.cpp]
// ����� �ђˏt�P
//-----------------------------------------------------------------------------
#include "SceneEffect.h"
//=============================================================================
// ����������
//=============================================================================
void SceneEffect::initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect)
{
	D3DXCreateSphere(device, 3.0f, 9, 9, &sphere, NULL);	// �����蔻��p�ɃX�t�B�A�����

	// �V�[���G�t�F�N�g������
	for (int i = 0; i < SCENE_EFFECT; i++)
	{
		sceneEffect[i].setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		sceneEffect[i].setSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		D3DXMatrixIdentity(sceneEffect[i].getMatrixWorld());
		sceneEffect[i].getCollider()->initialize(device, sceneEffect[i].getPosition(), sphere);
		sceneEffect[i].setUse(false);
		sceneEffect[i].time = 0;
	}

	numOfUse = 0;
	renderList = NULL;

	// �C���X�^���V���O������
	instancingProcedure.initialize(device, effect, *_textureLoader->getTexture(textureLoaderNS::LIGHT_001));

}
//=============================================================================
// �X�V����
//=============================================================================
void SceneEffect::update(float frameTime)
{

	// �g�p���̃G�t�F�N�g�̋������X�V����
	for (int i = 0; i < SCENE_EFFECT; i++)
	{
		// �o�ĂȂ�������X�V���Ȃ�
		if (sceneEffect[i].getUse() == false) { continue; }

		// ���Ԃ��t���[���ɍ��킹��
		sceneEffect[i].time += frameTime;

		// �V�[���G�t�F�N�g�ʒu�X�V
		sceneEffect[i].setPosition(*sceneEffect[i].getPosition() + *sceneEffect[i].getSpeed());

		// ���ԂɂȂ�����I��
		if (sceneEffect[i].time >= (float)(rand() % SCENE_EFFECT + 1))
		{
			sceneEffect[i].setUse(false);
			numOfUse--;
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void SceneEffect::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	// �g�p���̃G�t�F�N�g���C���X�^���V���O�`��ɗ���
	renderList = new D3DXVECTOR3[numOfUse];
	for (int i = 0; i < numOfUse; i++)
	{
		if (sceneEffect[i].getUse() == false) { continue; }

		renderList[i] = *sceneEffect[i].getPosition();
	}
	instancingProcedure.setNumOfRender(device, numOfUse, renderList);
	SAFE_DELETE_ARRAY(renderList)

		// �C���X�^���V���O�����_�[
		instancingProcedure.render(device, view, projection, cameraPosition);
}
//==================================================================
// �G�t�F�N�g�𔭐�������
//========================================================================================
void SceneEffect::generateSceneEffect(int num, D3DXVECTOR3 positionToGenerate)
{
	// �G�t�F�N�g�J�E���g������
	int cnt = 0;

	for (int i = 0; i < SCENE_EFFECT; i++)
	{
		// �G�t�F�N�g���g�p����Ă��������Ȃ�
		if (sceneEffect[i].getUse()) { continue; }

		if (cnt < num)
		{
			// �������ԏ�����
			sceneEffect[i].time = 0.0;
			// �G�t�F�N�g�ʒu�ݒ�
			sceneEffect[i].setPosition(positionToGenerate);
			// �G�t�F�N�g�X�s�[�h�ݒ�
			sceneEffect[i].setSpeed(D3DXVECTOR3(0.0,(float)(rand()%1+0.1),0.0));
			D3DXMatrixIdentity(sceneEffect[i].getMatrixWorld());
			// �g�p��
			sceneEffect[i].setUse(true);
			// �g�p���G�t�F�N�g�J�E���g���Z
			numOfUse++;
		}
		// �G�t�F�N�g�J�E���g���Z
		cnt++;
	}
}
