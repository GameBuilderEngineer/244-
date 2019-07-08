//-----------------------------------------------------------------------------
// �u���b�N�{�[�h��ꏈ�� [BlackBoardBase.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/15
//-----------------------------------------------------------------------------
#pragma once

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class BlackBoardBase {
protected:
	// Data
	void** index;

public:
	// Method
	BlackBoardBase(void);
	~BlackBoardBase(void);
	virtual void initialize(void);					// ����������
	virtual void uninitialize(void);				// �I������
	virtual bool getAccessPermission(int tag) = 0;	// ���W���[���ɃA�N�Z�X����Ԃ�
	void* getPage(int page) { return index[page]; }	// �y�[�W���擾
};