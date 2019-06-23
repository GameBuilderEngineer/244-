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
	virtual void initialize(void);			// ����������
	virtual void uninitialize(void);		// �I������
	void* getPage(int page) { return index[page]; }
};