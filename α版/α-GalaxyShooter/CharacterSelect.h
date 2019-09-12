//============================================================================================================================================
// Document
//============================================================================================================================================
// CharacterSelect.h
// HAL���� GP-12A-332 09 �T���v��
// 2019/08/25
//============================================================================================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
#include "UICharacterSelect.h"
#include "UIScreenSplitLine.h"
#include "SceneEffect.h"

//============================================================================================================================================
// NameSpace
// ���O���
//============================================================================================================================================
namespace characterSelectNS
{
	static const float EFFECT_MAX = 1500;	// �G�t�F�N�g���

	const float SELECT_TIME = (60.0f);
	const float POSITION_TIME_X = ((uiCharacterSelectNS::POSITION_X_TIME) - 38.0f);
	const float POSITION_TIME_Y = ((uiCharacterSelectNS::POSITION_Y_TIME) - 125.0f);

	enum PLAYER_TYPE
	{
		PLAYER_1,
		PLAYER_2,
		PLAYER_TYPE_MAX
	};
	const D3DXQUATERNION CAMERA_RELATIVE_QUATERNION[characterSelectNS::PLAYER_TYPE::PLAYER_TYPE_MAX] =
	{
		D3DXQUATERNION(0.0f,20.0f,-40.0f,0.0f),
#ifdef _DEBUG
		D3DXQUATERNION(0.0f,20.0f,-40.0f,0.0f)
#else
		D3DXQUATERNION(0.0f,20.0f,-40.0f,0.0f)
#endif // _DEBUG
	};

}
//============================================================================================================================================
// Class
// �N���X
//============================================================================================================================================
class CharacterSelect :public AbstractScene
{
private:
	UICharacterSelect uiCharacterSelect;	//	�L�����N�^�[�Z���N�gUI
	UIScreenSplitLine uiScreenSplitLine;	//	��ʕ�����UI
	float selectTime;						//	�I������
	TextManager* textManager;				//	�e�L�X�g�}�l�[�W��
	SceneEffect sceneEffect;				//	�V�[���G�t�F�N�g

public:
	CharacterSelect(void);
	~CharacterSelect(void);
	virtual void initialize(Direct3D9* _direct3D9, Input* _input, Sound* _sound, TextureLoader* _textureLoader, StaticMeshLoader* _staticMeshLoader, ShaderLoader* _shaderLoader, TextManager* _textManager) override;
	virtual void uninitialize(void) override;
	virtual void update(float _frameTime) override;
	void updateScene(void);
	void updateSceneBack(void);
	void updateSceneNext(void);
	void updateTime(float _frameTime);
	virtual void render(Direct3D9* _direct3D9) override;
	void render3D(Direct3D9* _direct3D9, Camera _currentCamera);
	void render2D(LPDIRECT3DDEVICE9 _device);
	void renderTime(void);
	// None
	virtual void collisions(void) override;
	virtual void AI(void) override;
};