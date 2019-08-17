//=============================================================================
// �`���[�g���A���w�b�_�[ [Tutorial.h]
// ����� �ђˏt�P
//=============================================================================
#pragma once
#include "AbstractScene.h"
#include "Tutorial2D.h"
//=============================================================================
// ���O���
//=============================================================================
namespace tutorialNS
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
class Tutorial : public AbstractScene
{
private:
	// �`���[�g���A��2D
	Tutorial2D tutorial2D;

public:
	Tutorial();
	~Tutorial();
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
};
