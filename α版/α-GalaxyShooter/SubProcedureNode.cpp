//-----------------------------------------------------------------------------
// �r�w�C�r�A�c���[ �T�u�v���V�[�W���m�[�h���� [SubProcedureNode.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/23
//-----------------------------------------------------------------------------
#include "SubProcedureNode.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
SubProcedureNode::SubProcedureNode(int treeType, int parentNumber, NODE_TYPE type, NODE_TAG tag) : BehaviorNodeBase(treeType, parentNumber, type, tag)
{
}


//=============================================================================
// ���s
//=============================================================================
NODE_STATUS SubProcedureNode::run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	return subProcedureList(recognitionBB, memoryBB, bodyBB);
}


//=============================================================================
// ���������X�g
//=============================================================================
NODE_STATUS SubProcedureNode::subProcedureList(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	switch (tag)
	{
	case SET_DESTINATION_OPPONENT:				return setMovingDestinationOpponent(recognitionBB, memoryBB, bodyBB);
	case SET_DESTINATION_RANDOM:				return setMovingDestinationRandom(recognitionBB, memoryBB, bodyBB);
	case SET_DESTINATION_NEXT_PILE:				return setMovingDestinationNextPile(recognitionBB, memoryBB, bodyBB);
	case SET_DESTINATION_TO_RECUASION:			return setMovingDestinationToRecuasion(recognitionBB, memoryBB, bodyBB);
	case SET_DESTINATION_TO_CUT_LINE:			return setMovingDestinationToCutLine(recognitionBB, memoryBB, bodyBB);
	case SET_TARGET_OPPONENT:					return setShootingTargetOpponent(recognitionBB, memoryBB, bodyBB);
	case SET_RECURSION_RECOGNITION:				return setRecursionRecognition(recognitionBB, memoryBB, bodyBB);
	case SET_RECURSION_RECOGNITION_FOR_OPPONENT:return setRecursionRecognitionForOpponent(recognitionBB, memoryBB, bodyBB);
	case SET_RECUASION_STATE:					return setRecursionState(recognitionBB, memoryBB, bodyBB);
	case SET_RECUASION_OPPONENT_STATE:			return setRecursionStateForOpponent(recognitionBB, memoryBB, bodyBB);
	case SET_BULLET_SWITCH:						return setBulletSwith(recognitionBB, memoryBB, bodyBB);
	default:
		MessageBox(NULL, TEXT("���������X�g�ɂȂ��m�[�h�ł�"), TEXT("Behavior Tree Error"), MB_OK);
		return NODE_STATUS::_NOT_FOUND;
	}
}


//=============================================================================
// �������F�ړI�n�𑊎�ɐݒ�
//=============================================================================
NODE_STATUS SubProcedureNode::setMovingDestinationOpponent(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	bodyBB->configMovingDestination(opponent->getPosition());
	return NODE_STATUS::SUCCESS;
}


//=============================================================================
// �������F�����_���Ƀm�[�h��ړI�n�ɐݒ肷��
//=============================================================================
NODE_STATUS SubProcedureNode::setMovingDestinationRandom(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	//if (recognitionBB->getWhetherDestinationDecided()) { return NODE_STATUS::RUNNING; }

	int number = rand() % Map::getMapNode().size();
	D3DXVECTOR3* newDestination = Map::getMapNode()[number]->getPosition();
	bodyBB->configMovingDestination(Map::getMapNode()[number]->getPosition());

	recognitionBB->setWhetherDestinationDecided(true);
	return NODE_STATUS::SUCCESS;
}


//=============================================================================
// �������F���̃p�C���ݒu���W��ړI�n�ɐݒ肷��
//=============================================================================
NODE_STATUS SubProcedureNode::setMovingDestinationNextPile(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	// ���J�[�W�������s���łȂ��Ȃ�return
	if (recognitionBB->getIsRecursionRunning() == false) { return NODE_STATUS::FAILED; }
	bodyBB->configMovingDestination(
		&recognitionBB->getRunningRecursion()->pilePosition[recognitionBB->getElementMemoryPile()]);

	return NODE_STATUS::SUCCESS;
}


//=============================================================================
// �������F���J�[�W�������邽�߂̖ړI�n��ݒ肷��
//=============================================================================
NODE_STATUS SubProcedureNode::setMovingDestinationToRecuasion(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	//if (recognitionBB->getWhetherDestinationDecided()) { return NODE_STATUS::RUNNING; }

	std::list<MapNode*> memorizedMap = recognitionBB->getMemorizedMap();
	std::list<MapNode*>::iterator itr;
	std::list<MapNode*>::iterator dest;
	int numMaxWasuremono = 0;

	for (itr = memorizedMap.begin(); itr != memorizedMap.end(); itr++)
	{
		if ((*itr)->getWasuremonoCount() > numMaxWasuremono)
		{
			numMaxWasuremono = (*itr)->getWasuremonoCount();
			dest = itr;
		}
	}

	if (numMaxWasuremono != 0)
	{
		bodyBB->configMovingDestination((*dest)->getPosition());	// ���X�����m�̑����m�[�h
		recognitionBB->setWhetherDestinationDecided(true);
		return NODE_STATUS::SUCCESS;
	}
	else
	{
		return NODE_STATUS::FAILED;
	}
}


//=============================================================================
// �������F�������[���C����؂���W��ړI�n�ɐݒ肷��
//=============================================================================
NODE_STATUS SubProcedureNode::setMovingDestinationToCutLine(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	bodyBB->setIsArrival(false);
	bodyBB->configMovingDestination(recognitionBB->getLineCutCoordPointer());
	return NODE_STATUS::SUCCESS;
}


//=============================================================================
// �������F���s���郊�J�[�W�����F����ݒ肷��
//=============================================================================
NODE_STATUS SubProcedureNode::setRecursionRecognition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	// ���J�[�W���������s���Ȃ�RUNNING
	if (recognitionBB->getIsRecursionRunning()) { return NODE_STATUS::RUNNING; }

	float largestWeight = 0.0f;				// �d�ݍő�l
	float mostExpensiveAmout = 0.0f;		// �ő�`���M���z 
	float leastRadius = 1000.0f;			// �ŏ����a
	int cntActiveRecursionRecognition = 0;	// ���F���u���b�N�{�[�h�̃��J�[�W�����F���̂����L���ȃf�[�^�������Ă��鐔
	int largestWeightRecognition = -1;		// �F�����Ă��钆�ōł��̗p�E�F�C�g�̎v�����J�[�W�����F��������
	int mostExpensiveRecognition = -1;		// �F�����Ă��钆�ōł��`���M���z�̑������J�[�W�����F��������
	int	leastRadiusRecognition = -1;		// �F�����Ă��钆�ōł����a�̏��������J�[�W�����F��������

	// ���J�[�W�������j���ƂɔF����������
	for (int i = 0; i < NUM_RECURSION_RECOGNITION; i++)
	{
		// �񊈐��̓p�X
		if (recognitionBB->getIsActiveRecursionRecognition(i) == false) { continue; }

		cntActiveRecursionRecognition++;
		if (largestWeight < recognitionBB->getRecursionRecognition()[i].fuzzySelectionWeight)
		{
			largestWeight = recognitionBB->getRecursionRecognition()[i].fuzzySelectionWeight;
			largestWeightRecognition = i;
		}
		if (mostExpensiveAmout < recognitionBB->getRecursionRecognition()[i].totalAmount)
		{
			mostExpensiveAmout = recognitionBB->getRecursionRecognition()[i].totalAmount;
			mostExpensiveRecognition = i;
		}
		if (leastRadius > recognitionBB->getRecursionRecognition()[i].radius)
		{
			leastRadius = recognitionBB->getRecursionRecognition()[i].radius;
			leastRadiusRecognition = i;
		}
	}

	// �L���ȃ��J�[�W�����F�����Ȃ��ꍇ�͎��s
	if (cntActiveRecursionRecognition == 0)
	{
		return NODE_STATUS::FAILED;
	}

	// ���s���J�[�W�����F���Ƃ��đI��
	switch (recognitionBB->getRecursionPolicy())
	{
	case LARGEST_WEIGHT:
		*recognitionBB->getRunningRecursion() = recognitionBB->getRecursionRecognition()[largestWeightRecognition];
		break;
	case MOST_EXPENSIVE:
		*recognitionBB->getRunningRecursion() = recognitionBB->getRecursionRecognition()[mostExpensiveRecognition];
		break;
	case LEAST_RADIUS:
		*recognitionBB->getRunningRecursion() = recognitionBB->getRecursionRecognition()[leastRadiusRecognition];
		break;
	}

	recognitionBB->setIsRecursionRunning(true);						// ���J�[�W�������s���ɃZ�b�g
	setMovingDestinationNextPile(recognitionBB, memoryBB, bodyBB);	// �ŏ��̖ړI�n������
	return NODE_STATUS::SUCCESS;									// ����
}


//=============================================================================
// �������F���s���郊�J�[�W�����F���i����j��ݒ肷��
//=============================================================================
NODE_STATUS SubProcedureNode::setRecursionRecognitionForOpponent(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	// ���J�[�W���������s���Ȃ�RUNNING
	if (recognitionBB->getIsRecursionRunning()) { return NODE_STATUS::RUNNING; }

	*recognitionBB->getRunningRecursion() = *recognitionBB->getRecursionRecognitionForOpponent();
	recognitionBB->setIsRecursionRunning(true);						// ���J�[�W�������s���ɃZ�b�g
	setMovingDestinationNextPile(recognitionBB, memoryBB, bodyBB);	// �ŏ��̖ړI�n������
	return NODE_STATUS::SUCCESS;									// ����
}


//=============================================================================
// �������F���J�[�W�����X�e�[�g���Z�b�g�i�J�ځj
//=============================================================================
NODE_STATUS SubProcedureNode::setRecursionState(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	recognitionBB->setIsStartRecursion(true);
	return NODE_STATUS::SUCCESS;
}


//=============================================================================
// �������F���J�[�W�����X�e�[�g���Z�b�g�i�J�ځj
//=============================================================================
NODE_STATUS SubProcedureNode::setRecursionStateForOpponent(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
 	recognitionBB->setIsStartRecursionForOpponent(true);
	return NODE_STATUS::SUCCESS;
}


//=============================================================================
// �������F�V���b�g�^�[�Q�b�g�𑊎�ɐݒ�
//=============================================================================
NODE_STATUS SubProcedureNode::setShootingTargetOpponent(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	bodyBB->setTargetCoordValue(*opponent->getPosition());
	return NODE_STATUS::SUCCESS;
}


//=============================================================================
// �������F�o���b�g�̔��ː؂�ւ�
//=============================================================================
NODE_STATUS SubProcedureNode::setBulletSwith(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	recognitionBB->changeBulletSwitch();
	return NODE_STATUS::SUCCESS;
}
