////============================================================================================================================================
//// Document
////============================================================================================================================================
//// PlayerAnimation.cpp
//// HAL東京 GP-12A-332 09 亀岡竣介
//// 2019/09/04
////============================================================================================================================================
//#include "PlayerAnimation.h"
////============================================================================================================================================
//// Using Declaration
//// using宣言
////============================================================================================================================================
//using namespace playerAnimationNS;
////============================================================================================================================================
//// Constructor
//// コンストラクタ
////============================================================================================================================================
//PlayerAnimation::PlayerAnimation(void)
//{
//	animation = NULL;				//	アニメーション
//	animationID = { NULL,NULL };	//	アニメーションID
//
//	return;
//}
////============================================================================================================================================
//// Destructor
//// デストラクタ
////============================================================================================================================================
//PlayerAnimation::~PlayerAnimation(void)
//{
//	// 解放
//	release();
//
//	return;
//}
////============================================================================================================================================
//// initialize
//// 初期化
////============================================================================================================================================
//HRESULT PlayerAnimation::initialize(LPDIRECT3DDEVICE9 _device)
//{
//	const char* animationSetName[animationNS::TYPE::TYPE_MAX] =	//	アニメーションセット名
//	{
//		"Idle",
//		"FastRun"
//	};
//
//	// アニメーションを作成
//	animation = createObject();
//
//	// ディレクトリ設定
//	setVisualDirectory();
//
//	// Xファイルを読み込む
//	loadXFile(_device, animation, ("Character_Adam.x"));
//
//	//// アニメーションコールバックの設定
//	//setCallBackKeyFrame(animation, animationSetName[ANIMATION_3D_TYPE_JUMP]);
//
//	// アニメーションセットの初期化
//	for (int i = 0; i < animation->animationSetMax; i++)
//	{
//		animation->initialize(animation, animationSetName[i], i);
//	}
//
//	// アニメーションIDの設定
//	animation->animationIdCurrent = animationNS::TYPE::IDLE;
//	animation->switching(animation, animationNS::TYPE::IDLE, 1.0f);
//	animation->flag.animationPlaying = true;
//	animation->update(animation, TIME_PER_FRAME);
//
//	// アニメーションの設定
//	animation->setShiftTime(animation, animation->animationIdCurrent, 1.0f);
//
//	// アニメーションシフトタイムの初期化
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
//// 解放
////============================================================================================================================================
//void PlayerAnimation::release(void)
//{
//	// アニメーションの解放
//	animation->release(animation);
//
//	return;
//}
////============================================================================================================================================
//// update
//// 更新
////============================================================================================================================================
//void PlayerAnimation::update(void)
//{
//	updateAnimationCurrent();
//	updateAnimationNext();
//
//	// アニメーションの更新
//	updateAnimation();
//
//	return;
//}
////============================================================================================================================================
//// updateAnimation
//// 更新 - アニメーション
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
//// 更新 - アニメーション( 今 )
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
//// 更新 - アニメーション( 次 )
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
//// 更新 - アニメーション( 今：アイドル )
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
//	//// ジャンプ
//	//else if ((Get_Keyboard_Trigger(DIK_SPACE)) || (Game_Pad_Button_Triggered(0, DUALSHOCK_4_BUTTON_CROSS)))
//	//{
//	//	Update_Player_Animation_Set_Current_Idol_to_Jump();
//	//	return;
//	//}
//
//	return;
//}
//////====================================================================================================================================================================================
////// プレイヤーの更新( アニメーションセット：今 - アイドル → ジャンプ )
////// 関数名：void Update_Player_Animation_Set_Current_Idol_to_Jump
////// 戻り値：void
//////====================================================================================================================================================================================
////void Update_Player_Animation_Set_Current_Idol_to_Jump(void)
////{
////	// 早期リターン
////	if (Get_Progress_Tutorial() < TUTORIAL_PROGRESS_TYPE_JUMP)
////	{
////		return;
////	}
////
////	Set_Complete_Switch_Tutorial_Process(TUTORIAL_TYPE_004_JUMP);
////
////	Player_State.Animation_Identification_Next = ANIMATION_3D_TYPE_JUMP;
////
////	// 早期リターン
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
//// 更新 - アニメーション( 今：走る )
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
//	// アイドル
//	animationID.next = animationNS::TYPE::IDLE;
//
//	return;
//}
//
//////====================================================================================================================================================================================
////// プレイヤーの更新( アニメーションセット：今 - 歩く → 走る )
////// 関数名：void Update_Player_Animation_Set_Current_Walk_to_Run
////// 戻り値：void
//////====================================================================================================================================================================================
////void Update_Player_Animation_Set_Current_Walk_to_Run(void)
////{
////	// 早期リターン
////	if (Get_Progress_Tutorial() < TUTORIAL_PROGRESS_TYPE_RUN)
////	{
////		return;
////	}
////
////	Set_Complete_Switch_Tutorial_Process(TUTORIAL_TYPE_003_RUN);
////
////	Player_State.Animation_Identification_Next = ANIMATION_3D_TYPE_RUN;
////
////	// 早期リターン
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
////// プレイヤーの更新( アニメーションセット：今 - 歩く → ジャンプ )
////// 関数名：void Update_Player_Animation_Set_Current_Walk_to_Jump
////// 戻り値：void
//////====================================================================================================================================================================================
////void Update_Player_Animation_Set_Current_Walk_to_Jump(void)
////{
////	// 早期リターン
////	if (Get_Progress_Tutorial() < TUTORIAL_PROGRESS_TYPE_JUMP)
////	{
////		return;
////	}
////
////	Set_Complete_Switch_Tutorial_Process(TUTORIAL_TYPE_004_JUMP);
////	Player_State.Animation_Identification_Next = ANIMATION_3D_TYPE_JUMP;
////
////	// 早期リターン
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
////// プレイヤーの更新( アニメーションセット：今 - 走る )
////// 関数名：void Update_Player_Animation_Set_Current_Run
////// 戻り値：void
////// 引数 1：MANAGEMENT*
//////====================================================================================================================================================================================
////void Update_Player_Animation_Set_Current_Run(MANAGEMENT *Management)
////{
////	// 早期リターン
////	if (Management->Switch[SWITCH_TYPE_OPERATION_BAN])
////	{
////		Player_State.Animation_Identification_Next = ANIMATION_3D_TYPE_IDLE;
////		return;
////	}
////
////	// 歩く
////	if ((Get_Keyboard_Press(DIK_W) || Get_Keyboard_Press(DIK_A) || Get_Keyboard_Press(DIK_S) || Get_Keyboard_Press(DIK_D) ||
////		(Game_Pad_Button_Pressed(0, DUALSHOCK_4_LEFT_STICK_UP)) ||
////		(Game_Pad_Button_Pressed(0, DUALSHOCK_4_LEFT_STICK_LEFT)) ||
////		(Game_Pad_Button_Pressed(0, DUALSHOCK_4_LEFT_STICK_DOWN)) ||
////		(Game_Pad_Button_Pressed(0, DUALSHOCK_4_LEFT_STICK_RIGHT))))
////	{
////		// 走る
////		if ((Get_Keyboard_Press(DIK_LSHIFT)) || (Game_Pad_Button_Pressed(0, DUALSHOCK_4_BUTTON_SQUARE)))
////		{
////			// ランジャンプ
////			if ((Get_Keyboard_Trigger(DIK_SPACE)) || (Game_Pad_Button_Triggered(0, DUALSHOCK_4_BUTTON_CROSS)))
////			{
////				Update_Player_Animation_Set_Current_Run_to_Run_Jump();
////				return;
////			}
////
////			// 走る
////			else
////			{
////				Update_Player_Animation_Set_Current_Run_to_Run(Management);
////				return;
////			}
////
////			return;
////		}
////
////		// 歩く
////		else
////		{
////			Update_Player_Animation_Set_Current_Run_to_Walk();
////			return;
////		}
////
////		return;
////	}
////
////	// アイドル
////	Player_State.Animation_Identification_Next = ANIMATION_3D_TYPE_IDLE;
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// プレイヤーの更新( アニメーションセット：今 - 走る → 走る )
////// 関数名：void Update_Player_Animation_Set_Current_Run_to_Run
////// 戻り値：void
////// 引数 1：MANAGEMENT*
//////====================================================================================================================================================================================
////void Update_Player_Animation_Set_Current_Run_to_Run(MANAGEMENT *Management)
////{
////	Player_State.Animation_Identification_Next = ANIMATION_3D_TYPE_RUN;
////	Update_Player_Control(PLAYER_CONTROL_TYPE_RUN, Management);
////
////	// 早期リターン
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
////// プレイヤーの更新( アニメーションセット：今 - 走る → ランジャンプ )
////// 関数名：void Update_Player_Animation_Set_Current_Run_to_Run_Jump
////// 戻り値：void
//////====================================================================================================================================================================================
////void Update_Player_Animation_Set_Current_Run_to_Run_Jump(void)
////{
////	// 早期リターン
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
////// プレイヤーの更新( アニメーションセット：今 - 走る → 歩く )
////// 関数名：void Update_Player_Animation_Set_Current_Run_to_Walk
////// 戻り値：void
//////====================================================================================================================================================================================
////void Update_Player_Animation_Set_Current_Run_to_Walk(void)
////{
////	Player_State.Animation_Identification_Next = ANIMATION_3D_TYPE_WALK;
////
////	// 早期リターン
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
////// プレイヤーの更新( アニメーションセット：今 - ジャンプ )
////// 関数名：void Update_Player_Animation_Set_Current_Jump
////// 戻り値：void
//////====================================================================================================================================================================================
////void Update_Player_Animation_Set_Current_Jump(void)
////{
////	// 早期リターン
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
////// プレイヤーの更新( アニメーションセット：今 - ランジャンプ )
////// 関数名：void Update_Player_Animation_Set_Current_Run_Jump
////// 戻り値：void
////// 引数 1：MANAGEMENT*
//////====================================================================================================================================================================================
////void Update_Player_Animation_Set_Current_Run_Jump(MANAGEMENT *Management)
////{
////	// ランジャンプ
////	Update_Player_Control(PLAYER_CONTROL_TYPE_RUN_JUMP, Management);
////
////	return;
////}
////============================================================================================================================================
//// updateAnimationNextIdle
//// 更新 - アニメーション( 次：アイドル )
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
//// 更新 - アニメーション( 次：走る )
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
////// プレイヤーの更新( アニメーションセット：次 - 走る )
////// 関数名：void Update_Player_Animation_Set_Next_Run
////// 戻り値：void
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
////// プレイヤーの更新( アニメーションセット：次 - ジャンプ )
////// 関数名：void Update_Player_Animation_Set_Next_Jump
////// 戻り値：void
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
////	// 早期リターン
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
////// プレイヤーの更新( アニメーションセット：次 - ランジャンプ )
////// 関数名：void Update_Player_Animation_Set_Next_Run_Jump
////// 戻り値：void
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
////	// 早期リターン
////	if ((!Player_State.Animation->Animation_End_Flag) || (Get_Switch(SWITCH_TYPE_OPERATION_BAN)))
////	{
////		return;
////	}
////
////	// 歩く
////	if ((Get_Keyboard_Press(DIK_W) || Get_Keyboard_Press(DIK_A) || Get_Keyboard_Press(DIK_S) || Get_Keyboard_Press(DIK_D) ||
////		(Game_Pad_Button_Pressed(0, DUALSHOCK_4_LEFT_STICK_UP)) ||
////		(Game_Pad_Button_Pressed(0, DUALSHOCK_4_LEFT_STICK_LEFT)) ||
////		(Game_Pad_Button_Pressed(0, DUALSHOCK_4_LEFT_STICK_DOWN)) ||
////		(Game_Pad_Button_Pressed(0, DUALSHOCK_4_LEFT_STICK_RIGHT))))
////	{
////		// 走る
////		if ((Get_Keyboard_Press(DIK_LSHIFT)) || (Game_Pad_Button_Pressed(0, DUALSHOCK_4_BUTTON_SQUARE)))
////		{
////			Player_State.Animation_Identification = ANIMATION_3D_TYPE_RUN;
////			Player_State.Animation->Switching_Animation_3D(Player_State.Animation, ANIMATION_3D_TYPE_RUN, 1.0f);
////
////			return;
////		}
////
////		// 歩く
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
////	// アイドル
////	Player_State.Animation_Identification = ANIMATION_3D_TYPE_IDLE;
////	Player_State.Animation->Switching_Animation_3D(Player_State.Animation, ANIMATION_3D_TYPE_IDLE, 1.0f);
////
////	return;
////}
//////====================================================================================================================================================================================
////// プレイヤーの更新( 制御 )
////// 関数名：void Update_Player_Control
////// 戻り値：void
////// 引数 1：int
////// 引数 2：MANAGEMENT*
//////====================================================================================================================================================================================
////void Update_Player_Control(int Control_Type, MANAGEMENT *Management)
////{
////	// 早期リターン
////	if (Management->Switch[SWITCH_TYPE_OPERATION_BAN])
////	{
////		Player_State.Animation_Identification_Next = ANIMATION_3D_TYPE_IDLE;
////		return;
////	}
////
////	// ゲームパッド
////	if (Get_Game_Pad_Connection_Count() > 0)
////	{
////		Update_Player_Control_Game_Pad(Control_Type);
////		return;
////	}
////
////	// キーボード
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
////// プレイヤーの更新( キーボード制御 )
////// 関数名：void Update_Player_Control
////// 戻り値：void
////// 引数 1：int
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
////// プレイヤーの更新( キーボード制御：歩く )
////// 関数名：void Update_Player_Control_Keyboard_Walk
////// 戻り値：void
//////====================================================================================================================================================================================
////void Update_Player_Control_Keyboard_Walk(void)
////{
////	// 早期リターン
////	if (Get_Progress_Tutorial() < TUTORIAL_PROGRESS_TYPE_WALK)
////	{
////		return;
////	}
////
////	// ポインタ変数宣言：初期化
////	CAMERA_KEYBOARD *Camera_Keyboard = Get_Camera_Keyboard();	//	カメラ( キーボード )ポインタ
////
////	// 左
////	if (Get_Keyboard_Press(DIK_A))
////	{
////		// 前
////		if ((Get_Keyboard_Press(DIK_W)) && (Get_Camera_Keyboard_Type() != CAMERA_TYPE_SIDE_VIEW))
////		{
////			Player_State.Move.x += sinf(Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.75f) * PLAYER_MOVE_VALUE;
////			Player_State.Move.z += cosf(Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.75f) * PLAYER_MOVE_VALUE;
////			Player_State.Target_Angle = Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.25f;
////		}
////		// 後
////		else if ((Get_Keyboard_Press(DIK_S)) && (Get_Camera_Keyboard_Type() != CAMERA_TYPE_SIDE_VIEW))
////		{
////			Player_State.Move.x += sinf(Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.25f) * PLAYER_MOVE_VALUE;
////			Player_State.Move.z += cosf(Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.25f) * PLAYER_MOVE_VALUE;
////			Player_State.Target_Angle = Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.75f;
////		}
////		// 左
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
////	// 右
////	else if (Get_Keyboard_Press(DIK_D))
////	{
////		// 前
////		if ((Get_Keyboard_Press(DIK_W)) && (Get_Camera_Keyboard_Type() != CAMERA_TYPE_SIDE_VIEW))
////		{
////			Player_State.Move.x += sinf(Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.75f) * PLAYER_MOVE_VALUE;
////			Player_State.Move.z += cosf(Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.75f) * PLAYER_MOVE_VALUE;
////			Player_State.Target_Angle = Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.25f;
////		}
////		// 後
////		else if ((Get_Keyboard_Press(DIK_S)) && (Get_Camera_Keyboard_Type() != CAMERA_TYPE_SIDE_VIEW))
////		{
////			Player_State.Move.x += sinf(Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.25f) * PLAYER_MOVE_VALUE;
////			Player_State.Move.z += cosf(Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.25f) * PLAYER_MOVE_VALUE;
////			Player_State.Target_Angle = Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.75f;
////		}
////		// 右
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
////	// 前
////	else if ((Get_Keyboard_Press(DIK_W)) && (Get_Camera_Keyboard_Type() != CAMERA_TYPE_SIDE_VIEW))
////	{
////		Player_State.Move.x += sinf(D3DX_PI + Camera_Keyboard->Angle_Axis.y) * PLAYER_MOVE_VALUE;
////		Player_State.Move.z += cosf(D3DX_PI + Camera_Keyboard->Angle_Axis.y) * PLAYER_MOVE_VALUE;
////		Player_State.Target_Angle = Camera_Keyboard->Angle_Axis.y;
////
////		Set_Complete_Switch_Tutorial_Process(TUTORIAL_TYPE_002_WALK);
////	}
////
////	// 後
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
////// プレイヤーの更新( キーボード制御：走る )
////// 関数名：void Update_Player_Control_Keyboard_Run
////// 戻り値：void
//////====================================================================================================================================================================================
////void Update_Player_Control_Keyboard_Run(void)
////{
////	// 早期リターン
////	if (Get_Progress_Tutorial() < TUTORIAL_PROGRESS_TYPE_RUN)
////	{
////		return;
////	}
////
////	// ポインタ変数宣言：初期化
////	CAMERA_KEYBOARD *Camera_Keyboard = Get_Camera_Keyboard();	//	カメラ( キーボード )ポインタ
////
////	// 左
////	if (Get_Keyboard_Press(DIK_A))
////	{
////		// 前
////		if ((Get_Keyboard_Press(DIK_W)) && (Get_Camera_Keyboard_Type() != CAMERA_TYPE_SIDE_VIEW))
////		{
////			Player_State.Move.x += (sinf(Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.75f) * PLAYER_MOVE_VALUE) * 2;
////			Player_State.Move.z += (cosf(Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.75f) * PLAYER_MOVE_VALUE) * 2;
////			Player_State.Target_Angle = Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.25f;
////		}
////		// 後
////		else if ((Get_Keyboard_Press(DIK_S)) && (Get_Camera_Keyboard_Type() != CAMERA_TYPE_SIDE_VIEW))
////		{
////			Player_State.Move.x += (sinf(Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.25f) * PLAYER_MOVE_VALUE) * 2;
////			Player_State.Move.z += (cosf(Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.25f) * PLAYER_MOVE_VALUE) * 2;
////			Player_State.Target_Angle = Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.75f;
////		}
////		// 左
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
////	// 右
////	else if (Get_Keyboard_Press(DIK_D))
////	{
////		// 前
////		if ((Get_Keyboard_Press(DIK_W)) && (Get_Camera_Keyboard_Type() != CAMERA_TYPE_SIDE_VIEW))
////		{
////			Player_State.Move.x += (sinf(Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.75f) * PLAYER_MOVE_VALUE) * 2;
////			Player_State.Move.z += (cosf(Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.75f) * PLAYER_MOVE_VALUE) * 2;
////			Player_State.Target_Angle = Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.25f;
////		}
////		// 後
////		else if ((Get_Keyboard_Press(DIK_S)) && (Get_Camera_Keyboard_Type() != CAMERA_TYPE_SIDE_VIEW))
////		{
////			Player_State.Move.x += (sinf(Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.25f) * PLAYER_MOVE_VALUE) * 2;
////			Player_State.Move.z += (cosf(Camera_Keyboard->Angle_Axis.y - D3DX_PI * 0.25f) * PLAYER_MOVE_VALUE) * 2;
////			Player_State.Target_Angle = Camera_Keyboard->Angle_Axis.y + D3DX_PI * 0.75f;
////		}
////		// 右
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
////	// 前
////	else if ((Get_Keyboard_Press(DIK_W)) && (Get_Camera_Keyboard_Type() != CAMERA_TYPE_SIDE_VIEW))
////	{
////		Player_State.Move.x += (sinf(D3DX_PI + Camera_Keyboard->Angle_Axis.y) * PLAYER_MOVE_VALUE) * 2;
////		Player_State.Move.z += (cosf(D3DX_PI + Camera_Keyboard->Angle_Axis.y) * PLAYER_MOVE_VALUE) * 2;
////		Player_State.Target_Angle = Camera_Keyboard->Angle_Axis.y;
////
////		Set_Complete_Switch_Tutorial_Process(TUTORIAL_TYPE_003_RUN);
////	}
////
////	// 後
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
////// プレイヤーの更新( キーボード制御：ランジャンプ )
////// 関数名：void Update_Player_Control_Keyboard_Run_Jump
////// 戻り値：void
//////====================================================================================================================================================================================
////void Update_Player_Control_Keyboard_Run_Jump(void)
////{
////	// 早期リターン
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
////// プレイヤーの更新( ゲームパッド制御 )
////// 関数名：void Update_Player_Control
////// 戻り値：void
////// 引数 1：int
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
////// プレイヤーの更新( ゲームパッド制御：歩く )
////// 関数名：void Update_Player_Control_Game_Pad_Walk
////// 戻り値：void
//////====================================================================================================================================================================================
////void Update_Player_Control_Game_Pad_Walk(void)
////{
////	// 早期リターン
////	if (Get_Progress_Tutorial() < TUTORIAL_PROGRESS_TYPE_WALK)
////	{
////		return;
////	}
////
////	// ポインタ変数宣言：初期化
////	GAME_PAD_MANAGEMENT *Game_Pad_Management = Get_Game_Pad_Management();	//	ゲームパッド管理ポインタ
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
////// プレイヤーの更新( ゲームパッド制御：走る )
////// 関数名：void Update_Player_Control_Game_Pad_Run
////// 戻り値：void
//////====================================================================================================================================================================================
////void Update_Player_Control_Game_Pad_Run(void)
////{
////	// 早期リターン
////	if (Get_Progress_Tutorial() < TUTORIAL_PROGRESS_TYPE_RUN)
////	{
////		return;
////	}
////
////	// ポインタ変数宣言：初期化
////	GAME_PAD_MANAGEMENT *Game_Pad_Management = Get_Game_Pad_Management();	//	ゲームパッド管理ポインタ
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
////// プレイヤーの更新( ゲームパッド制御：ランジャンプ )
////// 関数名：void Update_Player_Control_Game_Pad_Run_Jump
////// 戻り値：void
//////====================================================================================================================================================================================
////void Update_Player_Control_Game_Pad_Run_Jump(void)
////{
////	// 早期リターン
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
////// プレイヤーの更新( 算出 )
////// 関数名：void Update_Player_Calculation
////// 戻り値：void
//////====================================================================================================================================================================================
////void PlayerK::updateCalculation(void)
////{
////	static float playerRotateDifferenceY = NULL;	//	プレイヤーの回転差分
////
////	// 移動量の慣性を計算
////	move.x -= (move.x * PLAYER_INERTIA_MOVE);
////	move.y -= (move.y * PLAYER_INERTIA_MOVE);
////	move.z -= (move.z * PLAYER_INERTIA_MOVE);
////
////	// プレイヤーの移動更新
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
////	// 目的角度までの差分を計算
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
////	// 目的角度までの慣性を計算
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
//// 描画
////============================================================================================================================================
//void PlayerAnimation::render(LPDIRECT3DDEVICE9 _device, D3DXMATRIX* _matrixWorld)
//{
//	D3DMATERIAL9 materialDefault;	//	マテリアル
//
//	// ワールドマトリクスの設定
//	_device->SetTransform(D3DTS_WORLD, _matrixWorld);
//
//	// 現在のマテリアルを取得
//	_device->GetMaterial(&materialDefault);
//
//	// アニメーションの描画
//	animation->render(_device, animation, _matrixWorld);
//
//	// マテリアルを戻す
//	_device->SetMaterial(&materialDefault);
//
//	return;
//}
////============================================================================================================================================
//// installation
//// 設置
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
////// プレイヤーの位置を設定
////// 関数名：void Set_Position_Player
////// 戻り値：void
////// 引数 1：D3DXVECTOR3
//////====================================================================================================================================================================================
////void Set_Position_Player(D3DXVECTOR3 Position)
////{
////	Player_State.Position = Position;
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// プレイヤーの位置( 過去 )を設定
////// 関数名：void Set_Position_Past_Player
////// 戻り値：void
////// 引数 1：D3DXVECTOR3
//////====================================================================================================================================================================================
////void Set_Position_Past_Player(D3DXVECTOR3 Position_Past)
////{
////	Player_State.Position_Past = Position_Past;
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// プレイヤーの位置を位置( 過去 )に設定
////// 関数名：void Set_Position_for_Position_Past
////// 戻り値：void
//////====================================================================================================================================================================================
////void Set_Position_for_Position_Past(void)
////{
////	Player_State.Position = Player_State.Position_Past;
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// プレイヤーの回転を設定
////// 関数名：void Set_Rotation_Player
////// 戻り値：void
////// 引数 1：D3DXVECTOR3
//////====================================================================================================================================================================================
////void Set_Rotation_Player(D3DXVECTOR3 Rotation)
////{
////	Player_State.Rotation = Rotation;
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// プレイヤーの拡大縮小を設定
////// 関数名：void Set_Scale_Player
////// 戻り値：void
////// 引数 1：D3DXVECTOR3
//////====================================================================================================================================================================================
////void Set_Scale_Player(D3DXVECTOR3 Scale)
////{
////	Player_State.Scale = Scale;
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// プレイヤーのアニメーションIDを設定
////// 関数名：void Set_Player_Animation_Identification
////// 戻り値：void
////// 引数 1：int
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
////// プレイヤーのアニメーションを設定
////// 関数名：void Set_Player_Animation
////// 戻り値：void
////// 引数 1：int
////// 引数 2：float
//////====================================================================================================================================================================================
////void Set_Player_Animation(int Animation_Index, float Play_Speed)
////{
////	Player_State.Animation->Switching_Animation_3D(Player_State.Animation, Animation_Index, Play_Speed);
////
////	return;
////}
////
//////====================================================================================================================================================================================
////// プレイヤーの目的アングルを設定
////// 関数名：void Set_Player_Target_Angle
////// 戻り値：void
////// 引数 1：float
//////====================================================================================================================================================================================
////void Set_Player_Target_Angle(float Target_Angle)
////{
////	Player_State.Target_Angle = Target_Angle;
////
////	return;
////}
//////====================================================================================================================================================================================
////// プレイヤーのアニメーション取得
////// 関数名：ANIMATION_3D *Get_Player_Animation
////// 戻り値：ANIMATION_3D
//////====================================================================================================================================================================================
////ANIMATION_3D *Get_Player_Animation(void)
////{
////	return Player_State.Animation;
////}
////
//////====================================================================================================================================================================================
////// プレイヤーの位置取得
////// 関数名：D3DXVECTOR3 Get_Position_Player
////// 戻り値：D3DXVECTOR3
//////====================================================================================================================================================================================
////D3DXVECTOR3 Get_Position_Player(void)
////{
////	return Player_State.Position;
////}
////
//////====================================================================================================================================================================================
////// プレイヤーの位置( 過去 )取得
////// 関数名：D3DXVECTOR3 Get_Position_Past_Player
////// 戻り値：D3DXVECTOR3
//////====================================================================================================================================================================================
////D3DXVECTOR3 Get_Position_Past_Player(void)
////{
////	return Player_State.Position_Past;
////}
////
//////====================================================================================================================================================================================
////// プレイヤーの回転取得
////// 関数名：D3DXVECTOR3 Get_Rotation_Player
////// 戻り値：D3DXVECTOR3
//////====================================================================================================================================================================================
////D3DXVECTOR3 Get_Rotation_Player(void)
////{
////	return Player_State.Rotation;
////}
////
//////====================================================================================================================================================================================
////// プレイヤーの拡大縮小取得
////// 関数名：D3DXVECTOR3 Get_Scale_Player
////// 戻り値：D3DXVECTOR3
//////====================================================================================================================================================================================
////D3DXVECTOR3 Get_Scale_Player(void)
////{
////	return Player_State.Scale;
////}
////
//////====================================================================================================================================================================================
////// プレイヤーのアニメーションIDの取得
////// 関数名：int Get_Player_Animation_Identification
////// 戻り値：int
//////====================================================================================================================================================================================
////int Get_Player_Animation_Identification(void)
////{
////	return Player_State.Animation_Identification;
////}
////
//////====================================================================================================================================================================================
////// プレイヤーのターゲットアングルを取得
////// 関数名：float Get_Player_Target_Angle
////// 戻り値：float
//////====================================================================================================================================================================================
////float Get_Player_Target_Angle(void)
////{
////	return Player_State.Target_Angle;
////}
//
