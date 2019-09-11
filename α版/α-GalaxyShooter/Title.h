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
#include "SceneEffect.h"

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
	
	static const float EFFECT_MAX = 1500;	// �G�t�F�N�g���

	// �v���C���[���W
	const D3DXVECTOR3 PLAYER_POSITION[titleNS::PLAYER_TYPE::PLAYER_TYPE_MAX] =
	{
		D3DXVECTOR3(-8.0f, 101.0f, 33.0f),
		D3DXVECTOR3(-15.0f, 95.0f, 30.0f)
	};
}
//============================================================================================================================================
// Class
// �N���X
//============================================================================================================================================
class Title : public AbstractScene
{
private:
	//Player player[titleNS::PLAYER_TYPE::PLAYER_TYPE_MAX];	//	�v���C���[
	SceneEffect sceneEffect;								//	�V�[���G�t�F�N�g
	UITitle uiTitle;										//	�^�C�g��UI
	InstancingBillboard plane;								//	�C���X�^���V���O�r���{�[�h
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