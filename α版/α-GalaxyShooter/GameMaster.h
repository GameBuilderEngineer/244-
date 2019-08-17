//===================================================================================================================================
//�yGameMaster.h�z
// [�쐬��] HAL����GP12A332 11 ���� ��
// [�쐬��] 2019/07/31
// [�X�V��] 2019/08/04
//===================================================================================================================================
#pragma once
#include "Base.h"
#include "StaticMeshLoader.h"
#include "Player.h"

namespace gameMasterNS {
	const float GAME_TIME = 60.0f * 2.0f;	//4��
	const float COUNT_DOWN_TIME = 3.0f;		//3�b

	enum PLAYER_TYPE
	{
		PLAYER_CHARACTER,
		NON_PLAYER_CHARACTER,
		TYPE_NUM
	};

	enum RESULT_LIST
	{
		WIN_1P,
		WIN_2P,
		DRAW,
	};

	const int MODEL_ADAM = staticMeshNS::ADULT;
	const int MODEL_EVE = staticMeshNS::CHILD;

}

struct playerTable
{
	int playerType;		//PC|NPC
	int modelType;		//�v���C���[�̃��f���^�C�v
	int wage;			//�`���M��
};

//===================================================================================================================================
//�y�Q�[���Ǘ��N���X�z
// [�p�r]	���̃N���X�́A�V�[�����܂����ŏ��̋��n�����s���B
//			�X�V��ݒ�́A�e�V�[���ōs���B
//===================================================================================================================================
class GameMaster :public Base
{
private:
	float gameTimer;										//�Q�[������
	float countDownTimer;									//�J�E���g�_�E������
	playerTable playerInformation[playerNS::NUM_PLAYER];	//�v���C���[���

public:
	GameMaster();
	~GameMaster();
	
	//processing
	void initialize();
	void update(float frameTime);

	//operation
	void updateGameTime(float frameTime);					//�Q�[�����Ԃ̍X�V
	void resetGameTime();									//�Q�[�����Ԃ̃��Z�b�g

	//setter
	void setPlayerCharacter(int playerNo, int playerType, int modelType);	//�L�����N�^�[�����Z�b�g
	void addWage(int playerNo, int modelType);								//�`���M�������Z
	
	//getter
	playerTable* getPlayerInfomation();
	int getResult();
	float getGameTime();
	bool whetherGameOver();
};

