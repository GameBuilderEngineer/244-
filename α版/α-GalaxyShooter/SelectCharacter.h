//=============================================================================
// �Z���N�g�L�����N�^�[�w�b�_�[ [SelectCharacter.h]
// ����� �ђˏt�P
//=============================================================================
#pragma once
#include "AbstractScene.h"
#include "SelectCharacter2D.h"
#include "CharaSelectBarUI.h"
#include "TimerUI.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SELECT_TRANS_MAX (1)	// �Z���N�g�ړ����E
#define SELECT_TIME_MAX (99)	// �Z���N�g����
#define SELECT_FLAME_MAX (60)	// �Z���N�g�t���[��
//=============================================================================
// ���O���
//=============================================================================
namespace selectCharacterNS
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
class SelectCharacter :public AbstractScene
{
private:
	// �Z���N�g�L�����N�^�[2D
	SelectCharacter2D selectCharacter2D[selectCharacterNS::NUM_PLAYER];
	// �L�����N�^�[�Z���N�g�o�[
	CharaSelectBarUI charaSelectBar[selectCharacterNS::NUM_PLAYER];
	// �^�C�}�[UI
	TimerUI timerUI;
public:
	SelectCharacter();
	~SelectCharacter();
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

	int selectTransition;	// �Z���N�g�摜����ւ�
	int select2Transition;	// �Z���N�g2�摜����ւ�
	float selectTime;		// �Z���N�g����
	int selectFlameTime;	// �Q�[��������
};