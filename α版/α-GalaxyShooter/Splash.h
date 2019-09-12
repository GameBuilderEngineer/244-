//=============================================================================
// �X�v���b�V���w�b�_�[ [Splash.h]
// ����� �ђˏt�P
//=============================================================================
#pragma once
#include "AbstractScene.h"
#include "Splash2D.h"

//=============================================================================
// ���O���
//=============================================================================
namespace splashNS
{
	static const float EFFECT_MAX = 1500;	// �G�t�F�N�g���

	enum PLAYER_TYPE
	{
		PLAYER_1,
		PLAYER_2,
		PLAYER_TYPE_MAX
	};
	const D3DXQUATERNION CAMERA_RELATIVE_QUATERNION[splashNS::PLAYER_TYPE::PLAYER_TYPE_MAX] =
	{
		D3DXQUATERNION(0.0f,20.0f,-40.0f,0.0f),
#ifdef _DEBUG
		D3DXQUATERNION(0.0f,20.0f,-40.0f,0.0f)
#else
		D3DXQUATERNION(0.0f,20.0f,-40.0f,0.0f)
#endif // _DEBUG
	};
}
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Splash :public AbstractScene
{
private:
	// �X�v���b�V��2D
	Splash2D splash2D;

public:
	Splash();
	~Splash();
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

	void render3D(Direct3D9* direct3D9, Camera _currentCamera);
	void renderUI(LPDIRECT3DDEVICE9 device);
};

