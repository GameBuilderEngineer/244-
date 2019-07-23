//-----------------------------------------------------------------------------
// �i���b�W�\�[�X��ꏈ�� [KnowledgeSourceBase.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/15
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "AICommon.h"
#include "BlackBoardBase.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class KnowledgeSourceBase {
protected:
	// Data
	Module::TYPE moduleTag;							// ���W���[���^�C�v������								
	bool canUpdate;									// �X�V�\����\���t���O

public:
	KnowledgeSourceBase(void);
	~KnowledgeSourceBase(void);
	// ����������
	virtual void initialize(void) = 0;
	// �I������
	virtual void uninitialize(void) = 0;
	// �X�V����
	virtual void update(void) = 0;
	// �X�V����ݒ�
	void setUpdatePermission(bool setting) { canUpdate = setting; }	
	// �X�V�����擾
	bool getUpdatePermission(void) { return canUpdate; }

};
