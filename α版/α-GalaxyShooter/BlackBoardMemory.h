//-----------------------------------------------------------------------------
// �L���u���b�N�{�[�h���� [BlackBoardMemory.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/19
//-----------------------------------------------------------------------------
#pragma once
#include "BlackBoardBase.h"
#include "Map.h"
#include "Bullet.h"
#include <unordered_map>
#include <list>


// �O���錾
class BehaviorNodeBase;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class MemoryBB : public BlackBoardBase {
private:
	std::list<MapNode*> memorizedMap;						// �}�b�v�L�����X�g
	std::list<Bullet*> memorizedBullet;						// �o���b�g�L�����X�g
	std::unordered_map<BehaviorNodeBase*, int> onOffRecord;	// ONOFF�m�[�h�̋L�^�i�r�w�C�r�A�c���[�Ŏg�p�j
	std::unordered_map<BehaviorNodeBase*, int> timer;		// �^�C�}�[�i�r�w�C�r�A�c���[�Ŏg�p�j
	std::unordered_map<BehaviorNodeBase*, bool> flag;		// �t���O�i�r�w�C�r�A�c���[�Ŏg�p�j

public:
	// Method
	MemoryBB(void);
	void initialize(void) override;
	std::unordered_map<BehaviorNodeBase*, int>& getOnOffRecord(void) { return onOffRecord; }// ONOFF�m�[�h�L�^���擾
	std::unordered_map<BehaviorNodeBase*, int>& getTimer(void) { return timer; }// �^�C�}�[�擾
	std::list<MapNode*>& getMemorizedMap(void) { return memorizedMap; }			// �}�b�v�L�����X�g���擾
	std::list<Bullet*>& getMemorizedBullet(void) { return memorizedBullet; }	// �o���b�g�L�����X�g���擾
};