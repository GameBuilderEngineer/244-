//=============================================================================
// �I�y���[�V�����w�b�_�[ [Operation.h]
// ����� �ђˏt�P
//=============================================================================
#pragma once
#include "AbstractScene.h"
#include "KeyOpe.h"
#include "PadOpe.h"
#include "SceneEffect.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define OPE_MAX (1)		// �I�y���[�V�����ړ����E
//=============================================================================
// ���O���
//=============================================================================
namespace operationNS
{
	static const float EFFECT_MAX = 1500;	// �G�t�F�N�g���

	enum PLAYER_TYPE
	{
		PLAYER_1,
		PLAYER_2,
		PLAYER_TYPE_MAX
	};
	const D3DXQUATERNION CAMERA_RELATIVE_QUATERNION[operationNS::PLAYER_TYPE::PLAYER_TYPE_MAX] =
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
class Operation : public AbstractScene
{
private:
	// �L�[�{�[�h����
	KeyOpe keyOpe;
	// �p�b�h����
	PadOpe padOpe;
	SceneEffect sceneEffect;//	�V�[���G�t�F�N�g

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

	void render3D(Direct3D9* direct3D9, Camera _currentCamera);
	void renderUI(LPDIRECT3DDEVICE9 device);
	int opeTransition;	// �I�y���[�V�����摜����ւ�
};