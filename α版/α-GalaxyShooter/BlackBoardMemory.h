//-----------------------------------------------------------------------------
// �L���u���b�N�{�[�h���� [BlackBoardMemory.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/19
//-----------------------------------------------------------------------------
#pragma once
#include "BlackBoardBase.h"
#include <unordered_map>

// �O���錾
class BehaviorNodeBase;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class MemoryBB : public BlackBoardBase {
private:
	std::unordered_map<BehaviorNodeBase*, int> onOffRecord;	// ONOFF�m�[�h�̋L�^
	std::unordered_map<BehaviorNodeBase*, int> timer;		// �^�C�}�[
	// ���A���P�[�^�����ɂ��鏉�������˂�̂��߂���Ă�����Ă�

public:
	// Method
	MemoryBB(void);
	void initialize(void) override;				// ����������

	std::unordered_map<BehaviorNodeBase*, int>& getOnOffRecord(void) { return onOffRecord; }
	std::unordered_map<BehaviorNodeBase*, int>& getTimer(void) { return timer; }
};