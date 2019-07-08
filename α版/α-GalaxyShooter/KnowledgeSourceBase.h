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
	static BlackBoardBase* blackBoard[BB::NUM_MAX];	// �u���b�N�{�[�h

public:
	KnowledgeSourceBase(void);
	~KnowledgeSourceBase(void);
	// ����������
	virtual void initialize(void);
	// �I������
	virtual void uninitialize(void);
	// �X�V����
	virtual void update(void) = 0;
	// �X�V����ݒ�
	void setUpdatePermission(bool setting) { canUpdate = setting; }	
	// �X�V�����擾
	bool getUpdatePermission(void) { return canUpdate; }
	// �u���b�N�{�[�h�̃y�[�W�ǂݍ���
	template<typename dataType> const dataType& read(int type, int page);
	// �u���b�N�{�[�h�̃y�[�W�R�s�[
	template<typename dataType> dataType copy(int type, int page);
	// �u���b�N�{�[�h�Ƀy�[�W��������
	template<typename dataType> void write(int type, int page, dataType src);
	// ���W���[���ƃu���b�N�{�[�h��ڑ�
	friend void setBlackBoard(int type, BlackBoardBase* p);
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
// ���W���[���ƃu���b�N�{�[�h��ڑ�
void setBlackBoard(int type, BlackBoardBase* p);


//=============================================================================
// �u���b�N�{�[�h�̃y�[�W�ǂݍ���
//=============================================================================
template<typename dataType> 
const dataType& KnowledgeSourceBase::read(int type, int page)
{
	if (blackBoard[type]->getAccessPermission(moduleTag) == false)
	{
		MessageBox(NULL, "���W���[���̃A�N�Z�X�ᔽ\n>�ǂݍ���", "Error", MB_OK);
	}

	dataType *out = (dataType*)(blackBoard[type]->getPage(page));
	return *out;
}


//=============================================================================
// �u���b�N�{�[�h�̃y�[�W�R�s�[
//=============================================================================
template<typename dataType> 
dataType KnowledgeSourceBase::copy(int type, int page)
{
	if (blackBoard[type]->getAccessPermission(moduleTag) == false)
	{
		MessageBox(NULL, "���W���[���̃A�N�Z�X�ᔽ\n>�R�s�[", "Error", MB_OK);
	}

	dataType *out = (dataType*)(blackBoard[type]->getPage(page));
	return *out;
}


//=============================================================================
// �u���b�N�{�[�h�Ƀy�[�W��������
//=============================================================================
template<typename dataType>
void KnowledgeSourceBase::write(int type, int page, dataType src)
{
	if (blackBoard[type]->getAccessPermission(moduleTag))
	{
		dataType *dest = (dataType*)(blackBoard[type]->getPage(page));
		*dest = src;
	}
	else
	{
		MessageBox(NULL, "���W���[���̃A�N�Z�X�ᔽ\n>��������", "Error", MB_OK);
	}
}

