//=============================================================================
// �I�y���[�V�����w�b�_�[ [Operation.h]
// ����� �ђˏt�P
//=============================================================================
#pragma once
#include "AbstractScene.h"
#include "KeyOpe.h"
#include "PadOpe.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define OPE_MAX (1)		// �I�y���[�V�����ړ����E
//=============================================================================
// ���O���
//=============================================================================
namespace operationNS
{
	// �v���C���[�l��
	enum {
		PLAYER1,
		PLAYER2,
		NUM_PLAYER,
	};
}
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Operation : public AbstractScene
{
private:
	// �L�[�{�[�h����
	KeyOpe keyOpe;
	// �p�b�h����
	PadOpe padOpe;

public:
	Operation();
	~Operation();
	virtual void initialize(
		Direct3D9* direct3D9,
		Input* _input,
		Sound* _sound,
		TextureLoader* _textureLoader,
		StaticMeshLoader* _staticMeshLoader,
		ShaderLoader* _shaderLoader,
		TextManager* _textManager) override;
	virtual void update(float frameTime) override;
	virtual void render(Direct3D9* direct3D9) override;
	virtual void collisions() override;
	virtual void AI() override;
	virtual void uninitialize() override;

	void render3D(Direct3D9* direct3D9);
	void renderUI(LPDIRECT3DDEVICE9 device);
	int opeTransition;	// �I�y���[�V�����摜����ւ�
};