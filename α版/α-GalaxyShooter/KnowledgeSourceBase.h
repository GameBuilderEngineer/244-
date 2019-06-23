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
	bool canUpdate;													// �X�V�\��
	BlackBoardBase* bb[NUM_BLACK_BOARD];							// �u���b�N�{�[�h

public:
	// Method
	KnowledgeSourceBase(void);
	~KnowledgeSourceBase(void);
	virtual void initialize(void);									// ����������
	virtual void uninitialize(void);								// �I������
	virtual void update(void) = 0;									// �X�V����

	void setUpdatePermission(bool setting) { canUpdate = setting; }	// �X�V����ݒ�
	bool getUpdatePermission(void) { return canUpdate; }			// �X�V�����擾

	// �u���b�N�{�[�h�̃y�[�W�ǂݍ���
	template<typename dataType> const dataType* read( BlackBoardBase* blackBoard, int page)
	{
		return (dataType*)(blackBoard->getPage(page));
	}
	// �u���b�N�{�[�h�̃y�[�W�R�s�[
	template<typename dataType> dataType copy(BlackBoardBase* blackBoard, int page)
	{
		dataType *out = (dataType*)(blackBoard->getPage(page));
		return *out;
	}
	// �u���b�N�{�[�h�Ƀy�[�W��������
	template<typename dataType> void write(BlackBoardBase* blackBoard, int page, dataType src)
	{
		dataType *dest = (dataType*)(blackBoard->getPage(page));
		*dest = src;
	}
};


