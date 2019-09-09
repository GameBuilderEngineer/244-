//-----------------------------------------------------------------------------
// �r�w�C�r�A�c���[ �����m�[�h���� [ConditionalNode.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/23
//-----------------------------------------------------------------------------
#include "ConditionalNode.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
ConditionalNode::ConditionalNode(int treeType, int parentNumber, NODE_TYPE type, NODE_TAG tag): BehaviorNodeBase(treeType, parentNumber,type, tag)
{
		
}


//=============================================================================
// ���s
//=============================================================================
NODE_STATUS ConditionalNode::run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	if (conditionList(recognitionBB, memoryBB, bodyBB))
	{
		return NODE_STATUS::SUCCESS;
	}
	else
	{
		return  NODE_STATUS::FAILED;
	}
}


//=============================================================================
// �������X�g
//=============================================================================
bool ConditionalNode::conditionList(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	switch (tag)
	{
	case IF_OPPONENT_NEAR:				return ifOpponentNear(recognitionBB, memoryBB, bodyBB);
	case IF_BULLET_NEAR:				return ifBulletNear(recognitionBB, memoryBB, bodyBB);
	case IF_SHOCK_WAVE_MAY_BE_HAPPEN:	return ifShockWaveMayBeHappen(recognitionBB, memoryBB, bodyBB);
	case IF_FIVE_SECONDS_LATER:			return if5secondsLater(recognitionBB, memoryBB, bodyBB);
	case IF_THREE_SECONDS_LATER:		return if3secondsLater(recognitionBB, memoryBB, bodyBB);
	case IF_ONE_SECOND_LATER:			return if1secondLater(recognitionBB, memoryBB, bodyBB);
	case IF_RECURSION_IS_RUNNING:		return ifRecursionIsRunning(recognitionBB, memoryBB, bodyBB);
	case IF_DESTINATION_DECIDED:		return ifDestinationDecided(recognitionBB, memoryBB, bodyBB);

	default:
		MessageBox(NULL, TEXT("�������X�g�ɂȂ��m�[�h�ł�"), TEXT("Behavior Tree Error"), MB_OK);
		return false;
	}
}


//=============================================================================
// �����F���肪�߂��ɂ�����
//=============================================================================
bool ConditionalNode::ifOpponentNear(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	return true;
}


//=============================================================================
// �����F�o���b�g���߂��Ȃ�
//=============================================================================
bool ConditionalNode::ifBulletNear(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
 	if (recognitionBB->getIsBulletNear())
	{
		return true;
	}
	else
	{
		return false;
	}
}


//=============================================================================
// �����F�Ռ��g�������������Ȃ�
//=============================================================================
bool ConditionalNode::ifShockWaveMayBeHappen(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	return recognitionBB->getMayHappenShockWave();
}


//=============================================================================
// �����F5�b�o������
//=============================================================================
bool ConditionalNode::if5secondsLater(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	if (memoryBB->getTimer()[this]++ > 5 * 60/*1sec = 60fps*/)
	{
		memoryBB->getTimer()[this] = 0;
		return true;
	}
	
	return false;
}


//=============================================================================
// �����F3�b�o������
//=============================================================================
bool ConditionalNode::if3secondsLater(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	if (memoryBB->getTimer()[this]++ > 3 * 60/*1sec = 60fps*/)
	{
		memoryBB->getTimer()[this] = 0;
		return true;
	}

	return false;
}


//=============================================================================
// �����F1�b�o������
//=============================================================================
bool ConditionalNode::if1secondLater(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	if (memoryBB->getTimer()[this]++ > 60/*1sec = 60fps*/)
	{
		memoryBB->getTimer()[this] = 0;
		return true;
	}

	return false;
}


//=============================================================================
// �����F���J�[�W�������s���Ȃ�
//=============================================================================
bool ConditionalNode::ifRecursionIsRunning(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	return recognitionBB->getIsRecursionRunning();
}


//=============================================================================
// �����F�ړ�����W����ςȂ�
//=============================================================================
bool ConditionalNode::ifDestinationDecided(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	return recognitionBB->getWhetherDestinationDecided();
}
