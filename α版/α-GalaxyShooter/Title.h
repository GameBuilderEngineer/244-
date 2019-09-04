//============================================================================================================================================
// Document
//============================================================================================================================================
// Title.h
// HAL���� GP-12A-332 09 �T���v��
// 2019/08/29
//============================================================================================================================================
#pragma once
#include "AbstractScene.h"
#include "UITitle.h"
#include "EffectDew.h"
//============================================================================================================================================
// NameSpace
// ���O���
//============================================================================================================================================
namespace titleNS
{
	enum PLAYER_TYPE
	{
		PLAYER_1,
		PLAYER_2,
		PLAYER_TYPE_MAX
	};

	// �v���C���[���W
	const D3DXVECTOR3 PLAYER_POSITION[titleNS::PLAYER_TYPE::PLAYER_TYPE_MAX] =
	{
		D3DXVECTOR3(0,100,0),
		D3DXVECTOR3(60,100,0)
	};
	// �J�����p�x
	const D3DXQUATERNION CAMERA_RELATIVE_QUATERNION[titleNS::PLAYER_TYPE::PLAYER_TYPE_MAX] =
	{
		D3DXQUATERNION(0.0f,20.0f,-40.0f,0.0f),
		D3DXQUATERNION(0.0f,20.0f,-400,0.0f)
	};
}
//============================================================================================================================================
// Class
// �N���X
//============================================================================================================================================
class Title : public AbstractScene
{
private:
	Player player[titleNS::PLAYER_TYPE::PLAYER_TYPE_MAX];	//	�v���C���[
	UITitle uiTitle;										//	�^�C�g��UI
	InstancingBillboard plane;								//	�C���X�^���V���O�r���{�[�h
	EffectDewManager effectDewManager;						//	�I�G�t�F�N�g
public:
	Title(void);
	~Title(void);
	virtual void initialize(Direct3D9* _direct3D9, Input* _input, Sound* _sound, TextureLoader* _textureLoader, StaticMeshLoader* _staticMeshLoader, ShaderLoader* _shaderLoader, TextManager* _textManager) override;
	virtual void uninitialize(void) override;
	virtual void update(float _frameTime) override;
	void updateInput(void);
	virtual void render(Direct3D9* _direct3D9) override;
	void render3D(Direct3D9* _direct3D9, Camera _currentCamera);
	void render2D(LPDIRECT3DDEVICE9 _device);
	// None
	virtual void collisions(void) override;
	virtual void AI(void) override;
};