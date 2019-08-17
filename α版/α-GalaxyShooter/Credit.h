//=============================================================================
// �N���W�b�g�w�b�_�[ [Credit.h]
// ����� �ђˏt�P
//=============================================================================
#pragma once
#include "AbstractScene.h"
#include "Credit2D.h"
//=============================================================================
// ���O���
//=============================================================================
namespace creditNS
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
class Credit : public AbstractScene
{
private:
	// �N���W�b�g2D
	Credit2D credit2D;
public:
	Credit();
	~Credit();
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
