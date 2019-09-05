////============================================================================================================================================
//// Document
////============================================================================================================================================
//// PlayerAnimation.cpp
//// HAL���� GP-12A-332 09 �T���v��
//// 2019/09/04
////============================================================================================================================================
//#include "PlayerAnimation.h"
////============================================================================================================================================
//// Using Declaration
//// using�錾
////============================================================================================================================================
//using namespace playerAnimationNS;
////============================================================================================================================================
//// Constructor
//// �R���X�g���N�^
////============================================================================================================================================
//PlayerAnimation::PlayerAnimation(void)
//{
//	animation = NULL;				//	�A�j���[�V����
//	animationID = { NULL,NULL };	//	�A�j���[�V����ID
//
//	return;
//}
////============================================================================================================================================
//// Destructor
//// �f�X�g���N�^
////============================================================================================================================================
//PlayerAnimation::~PlayerAnimation(void)
//{
//	// ���
//	release();
//
//	return;
//}
////============================================================================================================================================
//// initialize
//// ������
////============================================================================================================================================
//HRESULT PlayerAnimation::initialize(LPDIRECT3DDEVICE9 _device)
//{
//	const char* animationSetName[animationNS::TYPE::TYPE_MAX] =	//	�A�j���[�V�����Z�b�g��
//	{
//		"Idle",
//		"FastRun"
//	};
//
//	// �A�j���[�V�������쐬
//	animation = createObject();
//
//	// �f�B���N�g���ݒ�
//	setVisualDirectory();
//
//	// X�t�@�C����ǂݍ���
//	loadXFile(_device, animation, ("Character_Adam.x"));
//
//	//// �A�j���[�V�����R�[���o�b�N�̐ݒ�
//	//setCallBackKeyFrame(animation, animationSetName[ANIMATION_3D_TYPE_JUMP]);
//
//	// �A�j���[�V�����Z�b�g�̏�����
//	for (int i = 0; i < animation->animationSetMax; i++)
//	{
//		animation->initialize(animation, animationSetName[i], i);
//	}
//
//	// �A�j���[�V����ID�̐ݒ�
//	animation->animationIdCurrent = animationNS::TYPE::IDLE;
//	animation->switching(animation, animationNS::TYPE::IDLE, 1.0f);
//	animation->flag.animationPlaying = true;
//	animation->update(animation, TIME_PER_FRAME);
//
//	// �A�j���[�V�����̐ݒ�
//	animation->setShiftTime(animation, animation->animationIdCurrent, 1.0f);
//
//	// �A�j���[�V�����V�t�g�^�C���̏�����
//	for (int i = 0; i < animation->animationSetMax; i++)
//	{
//		switch (i)
//		{
//		case animationNS::TYPE::IDLE:
//			animation->setShiftTime(animation, i, 0.5f);
//			break;
//		case animationNS::TYPE::FAST_RUN:
//			animation->setShiftTime(animation, i, 0.25f);
//			break;
//		default:
//			break;
//		}
//	}
//
//	return S_OK;
//}
////============================================================================================================================================
//// release
//// ���
////============================================================================================================================================
//void PlayerAnimation::release(void)
//{
//	// �A�j���[�V�����̉��
//	animation->release(animation);
//
//	return;
//}
////============================================================================================================================================
//// update
//// �X�V
////============================================================================================================================================
//void PlayerAnimation::update(void)
//{
//	updateAnimationCurrent();
//	updateAnimationNext();
//
//	// �A�j���[�V�����̍X�V
//	updateAnimation();
//
//	return;
//}
////============================================================================================================================================
//// updateAnimation
//// �X�V - �A�j���[�V����
////============================================================================================================================================
//void PlayerAnimation::updateAnimation(void)
//{
//	if (!animation->flag.animationPlaying) { return; }
//
//	animation->update(animation, TIME_PER_FRAME);
//
//	return;
//}
////============================================================================================================================================
//// updateAnimationCurrent
//// �X�V - �A�j���[�V����( �� )
////============================================================================================================================================
//void PlayerAnimation::updateAnimationCurrent(void)
//{
//	switch (animationID.current)
//	{
//	case animationNS::TYPE::IDLE:
//		updateAnimationCurrentIdle();
//		break;
//	case animationNS::TYPE::FAST_RUN:
//		updateAnimationCurrentFastRun();
//		break;
//	default:
//		break;
//	}
//
//	return;
//}
////============================================================================================================================================
//// updateAnimationNext
//// �X�V - �A�j���[�V����( �� )
////============================================================================================================================================
//void PlayerAnimation::updateAnimationNext(void)
//{
//	switch (animationID.next)
//	{
//	case animationNS::TYPE::IDLE:
//		updateAnimationNextIdle();
//		break;
//	case animationNS::TYPE::FAST_RUN:
//		updateAnimationNextFastRun();
//		break;
//	default:
//		return;
//		break;
//	}
//
//	return;
//}
////============================================================================================================================================
//// updateAnimationCurrentIdle
//// �X�V - �A�j���[�V����( ���F�A�C�h�� )
////============================================================================================================================================
//void PlayerAnimation::updateAnimationCurrentIdle(void)
//{
//	if (animation->flag.moveStop)
//	{
//		animationID.next = animationNS::TYPE::IDLE;
//		return;
//	}
//
//	if (input->isKeyDown('w') ||
//		input->isKeyDown('s') ||
//		input->isKeyDown('a') ||
//		input->isKeyDown('d'))
//	{
//		animationID.next = animationNS::TYPE::FAST_RUN;
//		return;
//	}
//
//	//// �W�����v
//	//else if ((Get_Keyboard_Trigger(DIK_SPACE)) || (Game_Pad_Button_Triggered(0, DUALSHOCK_4_BUTTON_CROSS)))
//	//{
//	//	Update_Player_Animation_Set_Current_Idol_to_Jump();
//	//	return;
//	//}
//
//	return;
//}
//////====================================================================================================================================================================================
////// �v���C���[�̍X�V( �A�j���[�V�����Z�b�g�F�� - �A�C�h�� �� �W�����v )
////// �֐����Fvoid Update_Player_Animation_Set_Current_Idol_to_Jump
////// �߂�l�Fvoid
//////====================================================================================================================================================================================
////void Update_Player_Animation_Set_Current_Idol_to_Jump(void)
////{
////	// �������^�[��
////	if (Get_Progress_Tutorial() < TUTORIAL_PROGRESS_TYPE_JUMP)
////	{
////		return;
////	}
////
////	Set_Complete_Switch_Tutorial_Process(TUTORIAL_TYPE_004_JUMP);
////
////	Player_State.Animation_Identification_Next = ANIMATION_3D_TYPE_JUMP;
////
////	// �������^�[��
////	if (Check_Play_Flag_Sound(SOUND_TYPE_SOUND_EFFECT_002_GAME_RUN))
////	{
////		return;
////	}
////
////	Stop_Sound(SOUND_TYPE_SOUND_EFFECT_001_GAME_WALK);
////	Play_Sound(SOUND_TYPE_SOUND_EFFECT_002_GAME_RUN, SOUND_PLAY_TYPE_PLAY);
////
////	return;
////}
////============================================================================================================================================
//// updateAnimationCurrentFastRun
//// �X�V - �A�j���[�V����( ���F���� )
////============================================================================================================================================
//void PlayerAnimation::updateAnimationCurrentFastRun(void)
//{
//	if (animation->flag.moveStop)
//	{
//		animationID.next = animationNS::TYPE::IDLE;
//		return;
//	}
//
//	if (input->isKeyDown(keyTable.front) ||
//		input->isKeyDown(keyTable.back) ||
//		input->isKeyDown(keyTable.left) ||
//		input->isKeyDown(keyTable.right))
//	{
//		animationID.next = animationNS::TYPE::FAST_RUN;
//		return;
//	}
//
//	// �A�C�h��
//	animationID.next = animationNS::TYPE::IDLE;
//
//	return;
//}
//
//////====================================================================================================================================================================================
////// �v���C���[�̍X�V( �A�j���[�V�����Z�b�g�F�� - ���� �� ���� )
////// �֐����Fvoid Update_Player_Animation_Set_Current_Walk_to_Run
////// �߂�l�Fvoid
//////====================================================================================================================================================================================
////void Update_Player_Animation_Set_Current_Walk_to_Run(void)
////{
////	// �������^�[��
////	if (Get_Progress_Tutorial() < TUTORIAL_PROGRESS_TYPE_RUN)
////	{
////		return;
////	}
////
////	Set_Complete_Switch_Tutorial_Process(TUTORIAL_TYPE_003_RUN);
////
////	Player_State.Animation_Identification_Next = ANIMATION_3D_TYPE_RUN;
////
////	// �������^�[��
////	if (Check_Play_Flag_Sound(SOUND_TYPE_SOUND_EFFECT_002_GAME_RUN))
////	{
////		return;
////	}
////
////	Stop_Sound(SOUND_TYPE_SOUND_EFFECT_001_GAME_WALK);
////	Play_Sound(SOUND_TYPE_SOUND_EFFECT_002_GAME_RUN, SOUND_PLAY_TYPE_PLAY);
////
////	return;
////}
//
//////====================================================================================================================================================================================
////// �v���C���[�̍X�V( �A�j���[�V�����Z�b�g�F�� - ���� �� �W�����v )
////// �֐����Fvoid Update_Player_Animation_Set_Current_Walk_to_Jump
////// �߂�l�Fvoid
//////====================================================================================================================================================================================
////void Update_Player_Animation_Set_Current_Walk_to_Jump(void)
////{
////	// �������^�[��
////	if (Get_Progress_Tutorial() < TUTORIAL_PROGRESS_TYPE_JUMP)
////	{
////		return;
////	}
////
////	Set_Complete_Switch_Tutorial_Process(TUTORIAL_TYPE_004_JUMP);
////	Player_State.Animation_Identification_Next = ANIMATION_3D_TYPE_JUMP;
////
////	// �������^�[��
////	if (Check_Play_Flag_Sound(SOUND_TYPE_SOUND_EFFECT_002_GAME_RUN))
////	{
////		return;
////	}
////
////	Stop_Sound(SOUND_TYPE_SOUND_EFFECT_001_GAME_WALK);
////	Play_Sound(SOUND_TYPE_SOUND_EFFECT_002_GAME_RUN, SOUND_PLAY_TYPE_PLAY);
////
////	return;
////}
//////====================================================================================================================================================================================
////// �v���C���[�̍X�V( �A�j���[�V�����Z�b�g�F�� - ���� )
////// �֐����Fvoid Update_Player_Animation_Set_Current_Run
////// �߂�l�Fvoid
////// ���� 1�FMANAGEMENT*
//////====================================================================================================================================================================================
////void Update_Player_Animation_Set_Current_Run(MANAGEMENT *Management)
////{
////	// �������^�[��
////	if (Management->Switch[SWITCH_TYPE_OPERATION_BAN])
////	{
////		Player_State.Animation_Identification_Next = ANIMATION_3D_TYPE_IDLE;
////		return;
////	}
////
////	// ����
////	if ((Get_Keyboard_Press(DIK_W) || Get_Keyboard_Press(DIK_A) || Get_Keyboard_Press(DIK_S) || Get_Keyboard_Press(DIK_D) ||
////		(Game_Pad_Button_Pressed(0, DUALSHOCK_4_LEFT_STICK_UP)) ||
////		(Game_Pad_Button_Pressed(0, DUALSHOCK_4_LEFT_STICK_LEFT)) ||
////		(Game_Pad_Button_Pressed(0, DUALSHOCK_4_LEFT_STICK_DOWN)) ||
////		(Game_Pad_Button_Pressed(0, DUALSHOCK_4_LEFT_STICK_RIGHT))))
////	{
////		// ����
////		if ((Get_Keyboard_Press(DIK_LSHIFT)) || (Game_Pad_Button_Pressed(0, DUALSHOCK_4_BUTTON_SQUARE)))
////		{
////			// �����W�����v
////			if ((Get_Keyboard_Trigger(DIK_SPACE)) || (Game_Pad_Button_Triggered(0, DUALSHOCK_4_BUTTON_CROSS)))
////			{
////				Update_Player_Animation_Set_Current_Run_to_Run_Jump();
////				return;
////			}
////
////			// ����
////			else
////			{
////				Update_Player_Animation_Set_Current_Run_to_Run(Management);
////				return;
////			}
////
////			return;
////		}
////
////		// ����
////		else
////		{
////			Update_Player_Animation_Set_Current_Run_to_Walk();
////			return;
////		}
////
////		return;
////	}
////
////	// �A�C�h��
////	Player_State.Animation_Identification_Next = ANIMATION_3D_TYPE_IDLE;
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// �v���C���[�̍X�V( �A�j���[�V�����Z�b�g�F�� - ���� �� ���� )
////// �֐����Fvoid Update_Player_Animation_Set_Current_Run_to_Run
////// �߂�l�Fvoid
////// ���� 1�FMANAGEMENT*
//////====================================================================================================================================================================================
////void Update_Player_Animation_Set_Current_Run_to_Run(MANAGEMENT *Management)
////{
////	Player_State.Animation_Identification_Next = ANIMATION_3D_TYPE_RUN;
////	Update_Player_Control(PLAYER_CONTROL_TYPE_RUN, Management);
////
////	// �������^�[��
////	if (Check_Play_Flag_Sound(SOUND_TYPE_SOUND_EFFECT_002_GAME_RUN))
////	{
////		return;
////	}
////
////	Stop_Sound(SOUND_TYPE_SOUND_EFFECT_001_GAME_WALK);
////	Play_Sound(SOUND_TYPE_SOUND_EFFECT_002_GAME_RUN, SOUND_PLAY_TYPE_PLAY);
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// �v���C���[�̍X�V( �A�j���[�V�����Z�b�g�F�� - ���� �� �����W�����v )
////// �֐����Fvoid Update_Player_Animation_Set_Current_Run_to_Run_Jump
////// �߂�l�Fvoid
//////====================================================================================================================================================================================
////void Update_Player_Animation_Set_Current_Run_to_Run_Jump(void)
////{
////	// �������^�[��
////	if (Get_Progress_Tutorial() < TUTORIAL_PROGRESS_TYPE_RUN_JUMP)
////	{
////		return;
////	}
////
////	Set_Complete_Switch_Tutorial_Process(TUTORIAL_TYPE_005_RUN_JUMP);
////
////	Player_State.Animation_Identification_Next = ANIMATION_3D_TYPE_RUN_JUMP;
////
////	Play_Sound(SOUND_TYPE_SOUND_EFFECT_002_GAME_RUN, SOUND_PLAY_TYPE_PLAY);
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// �v���C���[�̍X�V( �A�j���[�V�����Z�b�g�F�� - ���� �� ���� )
////// �֐����Fvoid Update_Player_Animation_Set_Current_Run_to_Walk
////// �߂�l�Fvoid
//////====================================================================================================================================================================================
////void Update_Player_Animation_Set_Current_Run_to_Walk(void)
////{
////	Player_State.Animation_Identification_Next = ANIMATION_3D_TYPE_WALK;
////
////	// �������^�[��
////	if (Check_Play_Flag_Sound(SOUND_TYPE_SOUND_EFFECT_001_GAME_WALK))
////	{
////		return;
////	}
////
////	Stop_Sound(SOUND_TYPE_SOUND_EFFECT_002_GAME_RUN);
////	Play_Sound(SOUND_TYPE_SOUND_EFFECT_001_GAME_WALK, SOUND_PLAY_TYPE_PLAY);
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// �v���C���[�̍X�V( �A�j���[�V�����Z�b�g�F�� - �W�����v )
////// �֐����Fvoid Update_Player_Animation_Set_Current_Jump
////// �߂�l�Fvoid
//////====================================================================================================================================================================================
////void Update_Player_Animation_Set_Current_Jump(void)
////{
////	// �������^�[��
////	if (Player_State.Animation_Identification_Next != ANIMATION_3D_TYPE_JUMP)
////	{
////		return;
////	}
////
////	Player_State.Animation_Identification_Next = ANIMATION_3D_TYPE_IDLE;
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// �v���C���[�̍X�V( �A�j���[�V�����Z�b�g�F�� - �����W�����v )
////// �֐����Fvoid Update_Player_Animation_Set_Current_Run_Jump
////// �߂�l�Fvoid
////// ���� 1�FMANAGEMENT*
//////====================================================================================================================================================================================
////void Update_Player_Animation_Set_Current_Run_Jump(MANAGEMENT *Management)
////{
////	// �����W�����v
////	Update_Player_Control(PLAYER_CONTROL_TYPE_RUN_JUMP, Management);
////
////	return;
////}
////============================================================================================================================================
//// updateAnimationNextIdle
//// �X�V - �A�j���[�V����( ���F�A�C�h�� )
////============================================================================================================================================
//void PlayerAnimation::updateAnimationNextIdle(void)
//{
//	if (animationID.current == animationNS::TYPE::IDLE)
//	{
//		animationID.current = animationNS::TYPE::IDLE;
//		animation->switching(animation, animationNS::TYPE::IDLE, 1.0f);
//
//		return;
//	}
//
//	if (!animation->flag.animationEnd) { return; }
//
//	animationID.current = animationNS::TYPE::IDLE;
//	animation->switching(animation, animationNS::TYPE::IDLE, 1.0f);
//
//	return;
//}
////============================================================================================================================================
//// updateAnimationNextFastRun
//// �X�V - �A�j���[�V����( ���F���� )
////============================================================================================================================================
//void PlayerAnimation::updateAnimationNextFastRun(void)
//{
//	animationID.current = animationNS::TYPE::FAST_RUN;
//	animation->switching(animation, animationNS::TYPE::FAST_RUN, 1.0f);
//
//	return;
//}
////
//////====================================================================================================================================================================================
////// �v���C���[�̍X�V( �A�j���[�V�����Z�b�g�F�� - ���� )
////// �֐����Fvoid Update_Player_Animation_Set_Next_Run
////// �߂�l�Fvoid
//////====================================================================================================================================================================================
////void Update_Player_Animation_Set_Next_Run(void)
////{
////	Player_State.Animation_Identification = ANIMATION_3D_TYPE_RUN;
////	Player_State.Animation->Switching_Animation_3D(Player_State.Animation, ANIMATION_3D_TYPE_RUN, 1.0f);
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// �v���C���[�̍X�V( �A�j���[�V�����Z�b�g�F�� - �W�����v )
////// �֐����Fvoid Update_Player_Animation_Set_Next_Jump
////// �߂�l�Fvoid
//////====================================================================================================================================================================================
////void Update_Player_Animation_Set_Next_Jump(void)
////{
////	if ((Player_State.Animation_Identification == ANIMATION_3D_TYPE_IDLE) ||
////		(Player_State.Animation_Identification == ANIMATION_3D_TYPE_WALK))
////	{
////		Player_State.Animation_Identification = ANIMATION_3D_TYPE_JUMP;
////		Player_State.Animation->Switching_Animation_3D(Player_State.Animation, ANIMATION_3D_TYPE_JUMP, 1.0f);
////
////		return;
////	}
////
////	// �������^�[��
////	if (!Player_State.Animation->Animation_End_Flag)
////	{
////		Player_State.Animation_Identification = ANIMATION_3D_TYPE_JUMP;
////		Player_State.Animation->Switching_Animation_3D(Player_State.Animation, ANIMATION_3D_TYPE_JUMP, 1.0f);
////
////		return;
////	}
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// �v���C���[�̍X�V( �A�j���[�V�����Z�b�g�F�� - �����W�����v )
////// �֐����Fvoid Update_Player_Animation_Set_Next_Run_Jump
////// �߂�l�Fvoid
//////====================================================================================================================================================================================
////void Update_Player_Animation_Set_Next_Run_Jump(void)
////{
////	if (Player_State.Animation_Identification == ANIMATION_3D_TYPE_RUN)
////	{
////		Player_State.Animation_Identification = ANIMATION_3D_TYPE_RUN_JUMP;
////		Player_State.Animation->Switching_Animation_3D(Player_State.Animation, ANIMATION_3D_TYPE_RUN_JUMP, 1.0f);
////
////		return;
////	}
////
////	// �������^�[��
////	if ((!Player_State.Animation->Animation_End_Flag) || (Get_Switch(SWITCH_TYPE_OPERATION_BAN)))
////	{
////		return;
////	}
////
////	// ����
////	if ((Get_Keyboard_Press(DIK_W) || Get_Keyboard_Press(DIK_A) || Get_Keyboard_Press(DIK_S) || Get_Keyboard_Press(DIK_D) ||
////		(Game_Pad_Button_Pressed(0, DUALSHOCK_4_LEFT_STICK_UP)) ||
////		(Game_Pad_Button_Pressed(0, DUALSHOCK_4_LEFT_STICK_LEFT)) ||
////		(Game_Pad_Button_Pressed(0, DUALSHOCK_4_LEFT_STICK_DOWN)) ||
////		(Game_Pad_Button_Pressed(0, DUALSHOCK_4_LEFT_STICK_RIGHT))))
////	{
////		// ����
////		if ((Get_Keyboard_Press(DIK_LSHIFT)) || (Game_Pad_Button_Pressed(0, DUALSHOCK_4_BUTTON_SQUARE)))
////		{
////			Player_State.Animation_Identification = ANIMATION_3D_TYPE_RUN;
////			Player_State.Animation->Switching_Animation_3D(Player_State.Animation, ANIMATION_3D_TYPE_RUN, 1.0f);
////
////			return;
////		}
////
////		// ����
////		else
////		{
////			Player_State.Animation_Identification = ANIMATION_3D_TYPE_WALK;
////			Player_State.Animation->Switching_Animation_3D(Player_State.Animation, ANIMATION_3D_TYPE_WALK, 1.0f);
////
////			return;
////		}
////
////		return;
////	}
////
////	// �A�C�h��
////	Player_State.Animation_Identification = ANIMATION_3D_TYPE_IDLE;
////	Player_State.Animation->Switching_Animation_3D(Player_State.Animation, ANIMATION_3D_TYPE_IDLE, 1.0f);
////
////	return;
////}
//////====================================================================================================================================================================================
////// �v���C���[�̍X�V( ���� )
////// �֐����Fvoid Update_Player_Control
////// �߂�l�Fvoid
////// ���� 1�Fint
////// ���� 2�FMANAGEMENT*
//////====================================================================================================================================================================================
////void Update_Player_Control(int Control_Type, MANAGEMENT *Management)
////{
////	// �������^�[��
////	if (Management->Switch[SWITCH_TYPE_OPERATION_BAN])
////	{
////		Player_State.Animation_Identification_Next = ANIMATION_3D_TYPE_IDLE;
////		return;
////	}
////
////	// �Q�[���p�b�h
////	if (Get_Game_Pad_Connection_Count() > 0)
////	{
////		Update_Player_Control_Game_Pad(Control_Type);
////		return;
////	}
////
////	// �L�[�{�[�h
////	else
////	{
////		Update_Player_Control_Keyboard(Control_Type);
////		//Update_Player_Control_Mouse(Control_Type);
////		return;
////	}
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// �v���C���[�̍X�V( �L�[�{�[�h���� )
////// �֐����Fvoid Update_Player_Control
////// �߂�l�Fvoid
////// ���� 1�Fint
//////====================================================================================================================================================================================
////void Update_Player_Control_Keyboard(int Control_Type)
////{
////	switch (Control_Type)
////	{
////	case PLAYER_CONTROL_TYPE_WALK:
////		Update_Player_Control_Keyboard_Walk();
////		return;
////		break;
////	case PLAYER_CONTROL_TYPE_RUN:
////		Update_Player_Control_Keyboard_Run();
////		return;
////		break;
////	case PLAYER_CONTROL_TYPE_RUN_JUMP:
////		Update_Player_Control_Keyboard_Run_Jump();
////		return;
////		break;
////	default:
////		return;
////		break;
////	}
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// �v���C���[�̍X�V( �L�[�{�[�h����F���� )
////// �֐����Fvoid Update_Player_Control_Keyboard_Walk
////// �߂�l�Fvoid
//////====================================================================================================================================================================================
////void Update_Player_Control_Keyboard_Walk(void)
////{
////	// �������^�[��
////	if (Get_Progress_Tutorial() < TUTORIAL_PROGRESS_TYPE_WALK)
////	{
////		return;
////	}
////
////	// �|�C���^�ϐ��錾�F������
////	CAMERA_KEYBOARD *Camera_Keyboard = Get_Camera_Keyboard();	//	�J����( �L�[�{�[�h )�|�C���^
////
////	// ��
////	if (Get_Keyboard_Press(DIK_A))
////	{
////		// �O
////		if ((Get_Keyboard_Press(DIK_W)) && (Get_Camera_Keyboard_Type() != CAMERA_TYPE_SIDE_VIEW))
////		{
////			Player_State.Move.x += sinf(Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.75f) * PLAYER_MOVE_VALUE;
////			Player_State.Move.z += cosf(Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.75f) * PLAYER_MOVE_VALUE;
////			Player_State.Target_Angle = Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.25f;
////		}
////		// ��
////		else if ((Get_Keyboard_Press(DIK_S)) && (Get_Camera_Keyboard_Type() != CAMERA_TYPE_SIDE_VIEW))
////		{
////			Player_State.Move.x += sinf(Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.25f) * PLAYER_MOVE_VALUE;
////			Player_State.Move.z += cosf(Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.25f) * PLAYER_MOVE_VALUE;
////			Player_State.Target_Angle = Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.75f;
////		}
////		// ��
////		else
////		{
////			Player_State.Move.x += sinf(Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.50f) * PLAYER_MOVE_VALUE;
////			Player_State.Move.z += cosf(Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.50f) * PLAYER_MOVE_VALUE;
////			Player_State.Target_Angle = Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.50f;
////		}
////
////		Set_Complete_Switch_Tutorial_Process(TUTORIAL_TYPE_002_WALK);
////	}
////
////	// �E
////	else if (Get_Keyboard_Press(DIK_D))
////	{
////		// �O
////		if ((Get_Keyboard_Press(DIK_W)) && (Get_Camera_Keyboard_Type() != CAMERA_TYPE_SIDE_VIEW))
////		{
////			Player_State.Move.x += sinf(Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.75f) * PLAYER_MOVE_VALUE;
////			Player_State.Move.z += cosf(Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.75f) * PLAYER_MOVE_VALUE;
////			Player_State.Target_Angle = Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.25f;
////		}
////		// ��
////		else if ((Get_Keyboard_Press(DIK_S)) && (Get_Camera_Keyboard_Type() != CAMERA_TYPE_SIDE_VIEW))
////		{
////			Player_State.Move.x += sinf(Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.25f) * PLAYER_MOVE_VALUE;
////			Player_State.Move.z += cosf(Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.25f) * PLAYER_MOVE_VALUE;
////			Player_State.Target_Angle = Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.75f;
////		}
////		// �E
////		else
////		{
////			Player_State.Move.x += sinf(Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.50f) * PLAYER_MOVE_VALUE;
////			Player_State.Move.z += cosf(Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.50f) * PLAYER_MOVE_VALUE;
////			Player_State.Target_Angle = Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.50f;
////		}
////
////		Set_Complete_Switch_Tutorial_Process(TUTORIAL_TYPE_002_WALK);
////	}
////
////	// �O
////	else if ((Get_Keyboard_Press(DIK_W)) && (Get_Camera_Keyboard_Type() != CAMERA_TYPE_SIDE_VIEW))
////	{
////		Player_State.Move.x += sinf(D3DX_PI + Camera_Keyboard->Angle_Axis.y) * PLAYER_MOVE_VALUE;
////		Player_State.Move.z += cosf(D3DX_PI + Camera_Keyboard->Angle_Axis.y) * PLAYER_MOVE_VALUE;
////		Player_State.Target_Angle = Camera_Keyboard->Angle_Axis.y;
////
////		Set_Complete_Switch_Tutorial_Process(TUTORIAL_TYPE_002_WALK);
////	}
////
////	// ��
////	else if ((Get_Keyboard_Press(DIK_S)) && (Get_Camera_Keyboard_Type() != CAMERA_TYPE_SIDE_VIEW))
////	{
////		Player_State.Move.x += sinf(Camera_Keyboard->Angle_Axis.y) * PLAYER_MOVE_VALUE;
////		Player_State.Move.z += cosf(Camera_Keyboard->Angle_Axis.y) * PLAYER_MOVE_VALUE;
////		Player_State.Target_Angle = D3DX_PI + Camera_Keyboard->Angle_Axis.y;
////
////		Set_Complete_Switch_Tutorial_Process(TUTORIAL_TYPE_002_WALK);
////	}
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// �v���C���[�̍X�V( �L�[�{�[�h����F���� )
////// �֐����Fvoid Update_Player_Control_Keyboard_Run
////// �߂�l�Fvoid
//////====================================================================================================================================================================================
////void Update_Player_Control_Keyboard_Run(void)
////{
////	// �������^�[��
////	if (Get_Progress_Tutorial() < TUTORIAL_PROGRESS_TYPE_RUN)
////	{
////		return;
////	}
////
////	// �|�C���^�ϐ��錾�F������
////	CAMERA_KEYBOARD *Camera_Keyboard = Get_Camera_Keyboard();	//	�J����( �L�[�{�[�h )�|�C���^
////
////	// ��
////	if (Get_Keyboard_Press(DIK_A))
////	{
////		// �O
////		if ((Get_Keyboard_Press(DIK_W)) && (Get_Camera_Keyboard_Type() != CAMERA_TYPE_SIDE_VIEW))
////		{
////			Player_State.Move.x += (sinf(Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.75f) * PLAYER_MOVE_VALUE) * 2;
////			Player_State.Move.z += (cosf(Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.75f) * PLAYER_MOVE_VALUE) * 2;
////			Player_State.Target_Angle = Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.25f;
////		}
////		// ��
////		else if ((Get_Keyboard_Press(DIK_S)) && (Get_Camera_Keyboard_Type() != CAMERA_TYPE_SIDE_VIEW))
////		{
////			Player_State.Move.x += (sinf(Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.25f) * PLAYER_MOVE_VALUE) * 2;
////			Player_State.Move.z += (cosf(Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.25f) * PLAYER_MOVE_VALUE) * 2;
////			Player_State.Target_Angle = Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.75f;
////		}
////		// ��
////		else
////		{
////			Player_State.Move.x += (sinf(Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.50f) * PLAYER_MOVE_VALUE) * 2;
////			Player_State.Move.z += (cosf(Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.50f) * PLAYER_MOVE_VALUE) * 2;
////			Player_State.Target_Angle = Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.50f;
////		}
////
////		Set_Complete_Switch_Tutorial_Process(TUTORIAL_TYPE_003_RUN);
////	}
////
////	// �E
////	else if (Get_Keyboard_Press(DIK_D))
////	{
////		// �O
////		if ((Get_Keyboard_Press(DIK_W)) && (Get_Camera_Keyboard_Type() != CAMERA_TYPE_SIDE_VIEW))
////		{
////			Player_State.Move.x += (sinf(Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.75f) * PLAYER_MOVE_VALUE) * 2;
////			Player_State.Move.z += (cosf(Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.75f) * PLAYER_MOVE_VALUE) * 2;
////			Player_State.Target_Angle = Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.25f;
////		}
////		// ��
////		else if ((Get_Keyboard_Press(DIK_S)) && (Get_Camera_Keyboard_Type() != CAMERA_TYPE_SIDE_VIEW))
////		{
////			Player_State.Move.x += (sinf(Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.25f) * PLAYER_MOVE_VALUE) * 2;
////			Player_State.Move.z += (cosf(Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.25f) * PLAYER_MOVE_VALUE) * 2;
////			Player_State.Target_Angle = Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.75f;
////		}
////		// �E
////		else
////		{
////			Player_State.Move.x += (sinf(Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.50f) * PLAYER_MOVE_VALUE) * 2;
////			Player_State.Move.z += (cosf(Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.50f) * PLAYER_MOVE_VALUE) * 2;
////			Player_State.Target_Angle = Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.50f;
////		}
////
////		Set_Complete_Switch_Tutorial_Process(TUTORIAL_TYPE_003_RUN);
////	}
////
////	// �O
////	else if ((Get_Keyboard_Press(DIK_W)) && (Get_Camera_Keyboard_Type() != CAMERA_TYPE_SIDE_VIEW))
////	{
////		Player_State.Move.x += (sinf(D3DX_PI + Camera_Keyboard->Angle_Axis.y) * PLAYER_MOVE_VALUE) * 2;
////		Player_State.Move.z += (cosf(D3DX_PI + Camera_Keyboard->Angle_Axis.y) * PLAYER_MOVE_VALUE) * 2;
////		Player_State.Target_Angle = Camera_Keyboard->Angle_Axis.y;
////
////		Set_Complete_Switch_Tutorial_Process(TUTORIAL_TYPE_003_RUN);
////	}
////
////	// ��
////	else if ((Get_Keyboard_Press(DIK_S)) && (Get_Camera_Keyboard_Type() != CAMERA_TYPE_SIDE_VIEW))
////	{
////		Player_State.Move.x += (sinf(Camera_Keyboard->Angle_Axis.y) * PLAYER_MOVE_VALUE) * 2;
////		Player_State.Move.z += (cosf(Camera_Keyboard->Angle_Axis.y) * PLAYER_MOVE_VALUE) * 2;
////		Player_State.Target_Angle = D3DX_PI + Camera_Keyboard->Angle_Axis.y;
////
////		Set_Complete_Switch_Tutorial_Process(TUTORIAL_TYPE_003_RUN);
////	}
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// �v���C���[�̍X�V( �L�[�{�[�h����F�����W�����v )
////// �֐����Fvoid Update_Player_Control_Keyboard_Run_Jump
////// �߂�l�Fvoid
//////====================================================================================================================================================================================
////void Update_Player_Control_Keyboard_Run_Jump(void)
////{
////	// �������^�[��
////	if (Player_State.Animation->Move_Stop_Flag)
////	{
////		return;
////	}
////
////	Player_State.Move.x += (-(sinf(Player_State.Target_Angle) * 1.5f));
////	Player_State.Move.z += (-(cosf(Player_State.Target_Angle) * 1.5f));
////
////	Set_Complete_Switch_Tutorial_Process(TUTORIAL_TYPE_005_RUN_JUMP);
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// �v���C���[�̍X�V( �Q�[���p�b�h���� )
////// �֐����Fvoid Update_Player_Control
////// �߂�l�Fvoid
////// ���� 1�Fint
//////====================================================================================================================================================================================
////void Update_Player_Control_Game_Pad(int Control_Type)
////{
////	switch (Control_Type)
////	{
////	case PLAYER_CONTROL_TYPE_WALK:
////		Update_Player_Control_Game_Pad_Walk();
////		return;
////		break;
////	case PLAYER_CONTROL_TYPE_RUN:
////		Update_Player_Control_Game_Pad_Run();
////		return;
////		break;
////	case PLAYER_CONTROL_TYPE_RUN_JUMP:
////		Update_Player_Control_Game_Pad_Run_Jump();
////		return;
////		break;
////	default:
////		return;
////		break;
////	}
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// �v���C���[�̍X�V( �Q�[���p�b�h����F���� )
////// �֐����Fvoid Update_Player_Control_Game_Pad_Walk
////// �߂�l�Fvoid
//////====================================================================================================================================================================================
////void Update_Player_Control_Game_Pad_Walk(void)
////{
////	// �������^�[��
////	if (Get_Progress_Tutorial() < TUTORIAL_PROGRESS_TYPE_WALK)
////	{
////		return;
////	}
////
////	// �|�C���^�ϐ��錾�F������
////	GAME_PAD_MANAGEMENT *Game_Pad_Management = Get_Game_Pad_Management();	//	�Q�[���p�b�h�Ǘ��|�C���^
////
////	Player_State.Target_Angle = ((Get_Camera_Keyboard_Angle_Axis().y) + D3DX_PI_HALF) + ((float)atan2(Game_Pad_Management->Game_Pad_Bit_State.lY, Game_Pad_Management->Game_Pad_Bit_State.lX));
////	Player_State.Move.x += (-(sinf(Player_State.Target_Angle) * PLAYER_MOVE_VALUE));
////	Player_State.Move.z += (-(cosf(Player_State.Target_Angle) * PLAYER_MOVE_VALUE));
////
////	Set_Complete_Switch_Tutorial_Process(TUTORIAL_TYPE_002_WALK);
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// �v���C���[�̍X�V( �Q�[���p�b�h����F���� )
////// �֐����Fvoid Update_Player_Control_Game_Pad_Run
////// �߂�l�Fvoid
//////====================================================================================================================================================================================
////void Update_Player_Control_Game_Pad_Run(void)
////{
////	// �������^�[��
////	if (Get_Progress_Tutorial() < TUTORIAL_PROGRESS_TYPE_RUN)
////	{
////		return;
////	}
////
////	// �|�C���^�ϐ��錾�F������
////	GAME_PAD_MANAGEMENT *Game_Pad_Management = Get_Game_Pad_Management();	//	�Q�[���p�b�h�Ǘ��|�C���^
////
////	Player_State.Target_Angle = ((Get_Camera_Keyboard_Angle_Axis().y) + D3DX_PI_HALF) + ((float)atan2(Game_Pad_Management->Game_Pad_Bit_State.lY, Game_Pad_Management->Game_Pad_Bit_State.lX));
////	Player_State.Move.x += (-(sinf(Player_State.Target_Angle) * PLAYER_MOVE_VALUE)) * 3;
////	Player_State.Move.z += (-(cosf(Player_State.Target_Angle) * PLAYER_MOVE_VALUE)) * 3;
////
////	Set_Complete_Switch_Tutorial_Process(TUTORIAL_TYPE_003_RUN);
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// �v���C���[�̍X�V( �Q�[���p�b�h����F�����W�����v )
////// �֐����Fvoid Update_Player_Control_Game_Pad_Run_Jump
////// �߂�l�Fvoid
//////====================================================================================================================================================================================
////void Update_Player_Control_Game_Pad_Run_Jump(void)
////{
////	// �������^�[��
////	if ((Player_State.Animation->Move_Stop_Flag) || (Get_Progress_Tutorial() < TUTORIAL_PROGRESS_TYPE_RUN))
////	{
////		return;
////	}
////
////	Player_State.Move.x += (-(sinf(Player_State.Target_Angle) * 1.4f));
////	Player_State.Move.z += (-(cosf(Player_State.Target_Angle) * 1.4f));
////
////	Set_Complete_Switch_Tutorial_Process(TUTORIAL_TYPE_005_RUN_JUMP);
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// �v���C���[�̍X�V( �Z�o )
////// �֐����Fvoid Update_Player_Calculation
////// �߂�l�Fvoid
//////====================================================================================================================================================================================
////void PlayerK::updateCalculation(void)
////{
////	static float playerRotateDifferenceY = NULL;	//	�v���C���[�̉�]����
////
////	// �ړ��ʂ̊������v�Z
////	move.x -= (move.x * PLAYER_INERTIA_MOVE);
////	move.y -= (move.y * PLAYER_INERTIA_MOVE);
////	move.z -= (move.z * PLAYER_INERTIA_MOVE);
////
////	// �v���C���[�̈ړ��X�V
////	position.x += (move.x);
////	position.y += (move.y);
////
////	if (Player_State.Position.y < 0.0f)
////	{
////		Player_State.Position.y = 0.0f;
////	}
////	if (Player_State.Position.y > 75.0f)
////	{
////		Player_State.Position.y = 75.0f;
////	}
////	Player_State.Position.z += Player_State.Move.z;
////
////	// �ړI�p�x�܂ł̍������v�Z
////	Player_Rotate_Difference_Y = Player_State.Target_Angle - Player_State.Rotation.y;
////
////	if (Player_Rotate_Difference_Y > D3DX_PI)
////	{
////		Player_Rotate_Difference_Y -= D3DX_PI_DOUBLE;
////	}
////	if (Player_Rotate_Difference_Y < -D3DX_PI)
////	{
////		Player_Rotate_Difference_Y += D3DX_PI_DOUBLE;
////	}
////
////	// �ړI�p�x�܂ł̊������v�Z
////	Player_State.Rotation.y += Player_Rotate_Difference_Y * PLAYER_INERTIA_ROTATION;
////
////	if (Player_State.Rotation.y > D3DX_PI)
////	{
////		Player_State.Rotation.y -= D3DX_PI_DOUBLE;
////	}
////	if (Player_State.Rotation.y < -D3DX_PI)
////	{
////		Player_State.Rotation.y += D3DX_PI_DOUBLE;
////	}
////
////	return;
////}
////============================================================================================================================================
//// render
//// �`��
////============================================================================================================================================
//void PlayerAnimation::render(LPDIRECT3DDEVICE9 _device, D3DXMATRIX* _matrixWorld)
//{
//	D3DMATERIAL9 materialDefault;	//	�}�e���A��
//
//	// ���[���h�}�g���N�X�̐ݒ�
//	_device->SetTransform(D3DTS_WORLD, _matrixWorld);
//
//	// ���݂̃}�e���A�����擾
//	_device->GetMaterial(&materialDefault);
//
//	// �A�j���[�V�����̕`��
//	animation->render(_device, animation, _matrixWorld);
//
//	// �}�e���A����߂�
//	_device->SetMaterial(&materialDefault);
//
//	return;
//}
////============================================================================================================================================
//// installation
//// �ݒu
////============================================================================================================================================
//void PlayerAnimation::installation(void)
//{
//	animationID.current = animationNS::TYPE::IDLE;
//	animationID.next = animationNS::TYPE::IDLE;
//	animation->animationIdCurrent = animationNS::TYPE::IDLE;
//	animation->switching(animation, animationNS::TYPE::IDLE, 1.0f);
//
//	return;
//}
//////====================================================================================================================================================================================
////// �v���C���[�̈ʒu��ݒ�
////// �֐����Fvoid Set_Position_Player
////// �߂�l�Fvoid
////// ���� 1�FD3DXVECTOR3
//////====================================================================================================================================================================================
////void Set_Position_Player(D3DXVECTOR3 Position)
////{
////	Player_State.Position = Position;
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// �v���C���[�̈ʒu( �ߋ� )��ݒ�
////// �֐����Fvoid Set_Position_Past_Player
////// �߂�l�Fvoid
////// ���� 1�FD3DXVECTOR3
//////====================================================================================================================================================================================
////void Set_Position_Past_Player(D3DXVECTOR3 Position_Past)
////{
////	Player_State.Position_Past = Position_Past;
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// �v���C���[�̈ʒu���ʒu( �ߋ� )�ɐݒ�
////// �֐����Fvoid Set_Position_for_Position_Past
////// �߂�l�Fvoid
//////====================================================================================================================================================================================
////void Set_Position_for_Position_Past(void)
////{
////	Player_State.Position = Player_State.Position_Past;
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// �v���C���[�̉�]��ݒ�
////// �֐����Fvoid Set_Rotation_Player
////// �߂�l�Fvoid
////// ���� 1�FD3DXVECTOR3
//////====================================================================================================================================================================================
////void Set_Rotation_Player(D3DXVECTOR3 Rotation)
////{
////	Player_State.Rotation = Rotation;
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// �v���C���[�̊g��k����ݒ�
////// �֐����Fvoid Set_Scale_Player
////// �߂�l�Fvoid
////// ���� 1�FD3DXVECTOR3
//////====================================================================================================================================================================================
////void Set_Scale_Player(D3DXVECTOR3 Scale)
////{
////	Player_State.Scale = Scale;
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// �v���C���[�̃A�j���[�V����ID��ݒ�
////// �֐����Fvoid Set_Player_Animation_Identification
////// �߂�l�Fvoid
////// ���� 1�Fint
//////====================================================================================================================================================================================
////void Set_Player_Animation_Identification(int Animation_Index)
////{
////	Player_State.Animation_Identification = Animation_Index;
////	Player_State.Animation_Identification_Next = Animation_Index;
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// �v���C���[�̃A�j���[�V������ݒ�
////// �֐����Fvoid Set_Player_Animation
////// �߂�l�Fvoid
////// ���� 1�Fint
////// ���� 2�Ffloat
//////====================================================================================================================================================================================
////void Set_Player_Animation(int Animation_Index, float Play_Speed)
////{
////	Player_State.Animation->Switching_Animation_3D(Player_State.Animation, Animation_Index, Play_Speed);
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// �v���C���[�̖ړI�A���O����ݒ�
////// �֐����Fvoid Set_Player_Target_Angle
////// �߂�l�Fvoid
////// ���� 1�Ffloat
//////====================================================================================================================================================================================
////void Set_Player_Target_Angle(float Target_Angle)
////{
////	Player_State.Target_Angle = Target_Angle;
////
////	return;
////}
//////====================================================================================================================================================================================
////// �v���C���[�̃A�j���[�V�����擾
////// �֐����FANIMATION_3D *Get_Player_Animation
////// �߂�l�FANIMATION_3D
//////====================================================================================================================================================================================
////ANIMATION_3D *Get_Player_Animation(void)
////{
////	return Player_State.Animation;
////}
////
//////====================================================================================================================================================================================
////// �v���C���[�̈ʒu�擾
////// �֐����FD3DXVECTOR3 Get_Position_Player
////// �߂�l�FD3DXVECTOR3
//////====================================================================================================================================================================================
////D3DXVECTOR3 Get_Position_Player(void)
////{
////	return Player_State.Position;
////}
////
//////====================================================================================================================================================================================
////// �v���C���[�̈ʒu( �ߋ� )�擾
////// �֐����FD3DXVECTOR3 Get_Position_Past_Player
////// �߂�l�FD3DXVECTOR3
//////====================================================================================================================================================================================
////D3DXVECTOR3 Get_Position_Past_Player(void)
////{
////	return Player_State.Position_Past;
////}
////
//////====================================================================================================================================================================================
////// �v���C���[�̉�]�擾
////// �֐����FD3DXVECTOR3 Get_Rotation_Player
////// �߂�l�FD3DXVECTOR3
//////====================================================================================================================================================================================
////D3DXVECTOR3 Get_Rotation_Player(void)
////{
////	return Player_State.Rotation;
////}
////
//////====================================================================================================================================================================================
////// �v���C���[�̊g��k���擾
////// �֐����FD3DXVECTOR3 Get_Scale_Player
////// �߂�l�FD3DXVECTOR3
//////====================================================================================================================================================================================
////D3DXVECTOR3 Get_Scale_Player(void)
////{
////	return Player_State.Scale;
////}
////
//////====================================================================================================================================================================================
////// �v���C���[�̃A�j���[�V����ID�̎擾
////// �֐����Fint Get_Player_Animation_Identification
////// �߂�l�Fint
//////====================================================================================================================================================================================
////int Get_Player_Animation_Identification(void)
////{
////	return Player_State.Animation_Identification;
////}
////
//////====================================================================================================================================================================================
////// �v���C���[�̃^�[�Q�b�g�A���O�����擾
////// �֐����Ffloat Get_Player_Target_Angle
////// �߂�l�Ffloat
//////====================================================================================================================================================================================
////float Get_Player_Target_Angle(void)
////{
////	return Player_State.Target_Angle;
////}
//
