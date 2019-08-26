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
//============================================================================================================================================
// NameSpace
// ���O���
//============================================================================================================================================
namespace characterSelectNS
{
	const float SELECT_TIME = (60.0f);
	const float POSITION_TIME_X = ((uiCharacterSelectNS::POSITION_X_TIME) - 20.0f);
	const float POSITION_TIME_Y = ((uiCharacterSelectNS::POSITION_Y_TIME) - 125.0f);
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
public:
	CharacterSelect(void);
	~CharacterSelect(void);
	virtual void initialize(Direct3D9* _direct3D9, Input* _input, Sound* _sound, TextureLoader* _textureLoader, StaticMeshLoader* _staticMeshLoader, ShaderLoader* _shaderLoader, TextManager* _textManager) override;
	virtual void uninitialize(void) override;
	virtual void update(float _frameTime) override;
	bool updateInput(void);
	void updateTime(float _frameTime);
	virtual void render(Direct3D9* _direct3D9) override;
	void render3D(Direct3D9* _direct3D9);
	void render2D(LPDIRECT3DDEVICE9 _device);
	void renderTime(float _time);
	// None
	virtual void collisions(void) override;
	virtual void AI(void) override;
};