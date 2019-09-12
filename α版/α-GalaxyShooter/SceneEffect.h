//-----------------------------------------------------------------------------
// �V�[���G�t�F�N�g�w�b�_�[ [SceneEffectEffect.h]
// ����� �ђˏt�P
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "InstancingEffect.h"
#include "TextureLoader.h"
#include "BoundingSphere.h"
#include "EffectManager.h"

static const int SCENE_EFFECT = 2000;		// �����ɕ\�����邤���őÓ������Ȑ�

//--------------------
// �V�[���G�t�F�N�g�N���X
//--------------------
class SceneEffect :public EffectManager
{
private:
	InstancingEffect instancingProcedure;	// �r���{�[�h�̃C���X�^���V���O�`�揈���N���X
	EffectIns sceneEffect[SCENE_EFFECT];	// �G�t�F�N�g�z��
	int numOfUse;							// �g�p���̐�
	D3DXVECTOR3* renderList;				// �C���X�^���V���O�`�悷��G�t�F�N�g�̍��W

public:
	virtual void initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect);
	virtual void update(float frameTime);
	virtual void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);

	// �V�[���G�t�F�N�g�𔭐�������
	void generateSceneEffect(int num, D3DXVECTOR3 positionToGenerate);
};

