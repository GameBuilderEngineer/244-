////============================================================================================================================================
//// Document
////============================================================================================================================================
//// playerK.h
//// HAL東京 GP-12A-332 09 亀岡竣介
//// 2019/09/04
////============================================================================================================================================
//#pragma once
//#include "Sprite.h"
//#include "AbstractScene.h"
//#include "Animation.h"
////====================================================================================================================================================================================
//// マクロ定義（あとでnamespaceに移す）
////====================================================================================================================================================================================
//#define OBJECT_FILE_PLAYER ("02 Visual File/Character_Adam.x")	//	オブジェクトファイル
//#define PLAYER_MOVE_VALUE (0.3f)					//	プレイヤーの平行移動量
//#define PLAYER_ROTATION_VALUE (D3DX_PI * 0.01f)		//	プレイヤーの回転量
//#define PLAYER_SCALING_VALUE (0.005f)				//	プレイヤーの拡大縮小量
//#define	PLAYER_INERTIA_MOVE (0.20f)					//	プレイヤーの移動慣性係数
//#define	PLAYER_INERTIA_ROTATION (0.20f)				//	プレイヤーの回転慣性係数
//#define PLAYER_INFLOW_TIME (8000)					//	流入状態への必要時間
//#define TIME_PER_FRAME (0.0167f)					//	1/60秒
////====================================================================================================================================================================================
//// 列挙型定義（あとでnamespaceに移す）
////====================================================================================================================================================================================
//enum PLAYER_CONTROL_TYPE
//{
//	PLAYER_CONTROL_TYPE_WALK,
//	PLAYER_CONTROL_TYPE_RUN,
//	PLAYER_CONTROL_TYPE_RUN_JUMP,
//	PLAYER_CONTROL_TYPE_MAX,
//};
////============================================================================================================================================
//// NameSpace
//// 名前空間
////============================================================================================================================================
//namespace playerKNS
//{
//
//}
////============================================================================================================================================
//// Class
//// クラス
////============================================================================================================================================
//class PlayerK
//{
//private:
//	DWORD materialMax = NULL;						//	マテリアルの最大数
//	D3DXVECTOR3 position = { NULL,NULL,NULL };		//	位置
//	D3DXVECTOR3 positionPast = { NULL,NULL,NULL };	//	１フレーム前の位置
//	D3DXVECTOR3 rotation = { NULL,NULL,NULL };		//	回転
//	D3DXVECTOR3 scale = { NULL,NULL,NULL };			//	拡大縮小
//	D3DXVECTOR3 move = { NULL,NULL,NULL };			//	移動量
//	Animation* animation = NULL;					//	アニメーション
//	int animationId = NULL;							//	アニメーションID
//	int animationIdNext = NULL;						//	アニメーションID( 次 )
//	float targetAngle = NULL;						//	目標角度( 今 )
//public:
//	PlayerK(void);
//	~PlayerK(void);
//	HRESULT initialize(LPDIRECT3DDEVICE9 _device);
//	void release(void);
//	void update(void);
//	void updateAnimation(void);
//	void updateAnimationSet(void);
//	void updateAnimationSetCurrent(void);
//	void render(LPDIRECT3DDEVICE9 _device);
//	void setMatrix(void);
//	void installation(void);
//};
////====================================================================================================================================================================================
//// プロトタイプ宣言
////====================================================================================================================================================================================
//// Initialize
//HRESULT Initialize_Player(void);
//
//// Release
//void Release_Player(void);
//
//// Update
//void Update_Player(MANAGEMENT *Management);
//void Update_Player_Animation(void);
//void Update_Player_Animation_Set(MANAGEMENT *Management);
//void Update_Player_Voez(MANAGEMENT *Management);
//void Update_Player_Cut_Scene(MANAGEMENT *Management);
//void Update_Player_Cut_Scene_Game(MANAGEMENT *Management);
//void Update_Player_Cut_Scene_Ending(MANAGEMENT *Management);
//void Update_Player_Cut_Scene_Ending_Cut_Scene_002_Fall(void);
//void Update_Player_Cut_Scene_Ending_Cut_Scene_003_Credit(void);
//void Update_Player_Cut_Scene_Ending_Cut_Scene_004_Credit(void);
//
//// Update ----- Animation_Set Third_Person
//void Update_Player_Animation_Set_Current(MANAGEMENT *Management);
//void Update_Player_Animation_Set_Next(void);
//// Update ----- Animation_Set Third_Person - Component
//void Update_Player_Animation_Set_Current_Idol(MANAGEMENT *Management);
//void Update_Player_Animation_Set_Current_Idol_to_Walk(void);
//void Update_Player_Animation_Set_Current_Idol_to_Jump(void);
//void Update_Player_Animation_Set_Current_Idol_to_Super_Natural(MANAGEMENT *Management);
//void Update_Player_Animation_Set_Current_Idol_to_Lumina(MANAGEMENT *Management);
//void Update_Player_Animation_Set_Current_Walk(MANAGEMENT *Management);
//void Update_Player_Animation_Set_Current_Walk_to_Walk(MANAGEMENT *Management);
//void Update_Player_Animation_Set_Current_Walk_to_Run(void);
//void Update_Player_Animation_Set_Current_Walk_to_Jump(void);
//void Update_Player_Animation_Set_Current_Walk_to_Super_Natural(MANAGEMENT *Management);
//void Update_Player_Animation_Set_Current_Walk_to_Lumina(MANAGEMENT *Management);
//void Update_Player_Animation_Set_Current_Run(MANAGEMENT *Management);
//void Update_Player_Animation_Set_Current_Run_to_Run(MANAGEMENT *Management);
//void Update_Player_Animation_Set_Current_Run_to_Run_Jump(void);
//void Update_Player_Animation_Set_Current_Run_to_Walk(void);
//void Update_Player_Animation_Set_Current_Jump(void);
//void Update_Player_Animation_Set_Current_Run_Jump(MANAGEMENT *Management);
//void Update_Player_Animation_Set_Current_Super_Natural(MANAGEMENT *Management);
//void Update_Player_Animation_Set_Current_Super_Natural_to_Super_Natural_Pose(MANAGEMENT *Management);
//void Update_Player_Animation_Set_Current_Super_Natural_to_Idol(void);
//void Update_Player_Animation_Set_Current_Super_Natural_Pose(MANAGEMENT *Management);
//void Update_Player_Animation_Set_Current_Super_Natural_Pose_to_Super_Natural_Pose(void);
//void Update_Player_Animation_Set_Current_Super_Natural_Pose_to_Idol(void);
//void Update_Player_Animation_Set_Current_Lumina(void);
//void Update_Player_Animation_Set_Next_Idol(void);
//void Update_Player_Animation_Set_Next_Walk(void);
//void Update_Player_Animation_Set_Next_Run(void);
//void Update_Player_Animation_Set_Next_Jump(void);
//void Update_Player_Animation_Set_Next_Run_Jump(void);
//void Update_Player_Animation_Set_Next_Super_Natural(void);
//void Update_Player_Animation_Set_Next_Super_Natural_Pose(void);
//void Update_Player_Animation_Set_Next_Lumina(void);
//
//// Update ----- Animation_Set Side_View
//void Update_Player_Animation_Set_Current_Side_View(MANAGEMENT *Management);
//void Update_Player_Animation_Set_Next_Side_View(MANAGEMENT *Management);
//// Update ----- Animation_Set Side_View - Component
//void Update_Player_Animation_Set_Current_Side_View_Idol(MANAGEMENT *Management);
//void Update_Player_Animation_Set_Current_Side_View_Walk(MANAGEMENT *Management);
//void Update_Player_Animation_Set_Current_Side_View_Run(MANAGEMENT *Management);
//void Update_Player_Animation_Set_Current_Side_View_Jump(void);
//void Update_Player_Animation_Set_Current_Side_View_Run_Jump(MANAGEMENT *Management);
//void Update_Player_Animation_Set_Next_Side_View_Idle(void);
//void Update_Player_Animation_Set_Next_Side_View_Walk(void);
//void Update_Player_Animation_Set_Next_Side_View_Run(void);
//void Update_Player_Animation_Set_Next_Side_View_Jump(void);
//void Update_Player_Animation_Set_Next_Side_View_Run_Jump(MANAGEMENT *Management);
//
//// Update ----- Animation_Set_Cut_Scene
//void Update_Player_Animation_Set_Current_Cut_Scene(MANAGEMENT *Management);
//void Update_Player_Animation_Set_Next_Cut_Scene(void);
//// Update ----- Animation_Set_Cut_Scene - Component
//void Update_Player_Animation_Set_Current_Cut_Scene_Idle(void);
//void Update_Player_Animation_Set_Current_Cut_Scene_Stand_Up_Initial(MANAGEMENT *Management);
//void Update_Player_Animation_Set_Current_Cut_Scene_Stand_Up(void);
//void Update_Player_Animation_Set_Current_Cut_Scene_Sit_Down(void);
//void Update_Player_Animation_Set_Current_Cut_Scene_Sit_Down_Pose(void);
//void Update_Player_Animation_Set_Current_Cut_Scene_Jump_Off(void);
//void Update_Player_Animation_Set_Current_Cut_Scene_Fall(void);
//void Update_Player_Animation_Set_Next_Cut_Scene_Idle(void);
//void Update_Player_Animation_Set_Next_Cut_Scene_Stand_Up_Initial(void);
//void Update_Player_Animation_Set_Next_Cut_Scene_Stand_Up(void);
//void Update_Player_Animation_Set_Next_Cut_Scene_Sit_Down(void);
//void Update_Player_Animation_Set_Next_Cut_Scene_Sit_Down_Pose(void);
//void Update_Player_Animation_Set_Next_Cut_Scene_Jump_Off(void);
//void Update_Player_Animation_Set_Next_Cut_Scene_Fall(void);
//
//// Update_Control
//void Update_Player_Control(int Control_Type, MANAGEMENT *Management);
//void Update_Player_Control_Keyboard(int Control_Type);
//void Update_Player_Control_Keyboard_Walk(void);
//void Update_Player_Control_Keyboard_Run(void);
//void Update_Player_Control_Keyboard_Run_Jump(void);
//void Update_Player_Control_Game_Pad(int Control_Type);
//void Update_Player_Control_Game_Pad_Walk(void);
//void Update_Player_Control_Game_Pad_Run(void);
//void Update_Player_Control_Game_Pad_Run_Jump(void);
//void Update_Player_Calculation(void);
//
//// Update_Hit_Judgment
//void Update_Player_Hit_Judgment(void);
//void Update_Player_Hit_Judgment_Game(void);
//void Update_Player_Hit_Judgment_Ending(void);
//void Update_Player_Hit_Judgment_Ending_Walk_Through(void);
//void Update_Player_Hit_Judgment_Ending_Rooftop(void);
//void Update_Hit_Judgment_Player_Bench(void);
//void Update_Hit_Judgment_Player_Coffin(void);
//void Update_Hit_Judgment_Player_Grave(void);
//void Update_Hit_Judgment_Player_Monolith(void);
//void Update_Hit_Judgment_Player_Television(void);
//void Update_Hit_Judgment_Player_Tree(void);
//void Update_Hit_Judgment_Player_Rooftop(void);
//void Update_Hit_Judgment_Player_Jump_Off(void);
//
//// Draw
//void Draw_Player(ORIGIN_DEVICE *Device, ORIGIN_MATRIX *Matrix);
//
//// Installation
//void Installation_Player(void);
//
//// Set
//void Set_Matrix_Player(void);
//void Set_Position_Player(D3DXVECTOR3 Position);
//void Set_Position_Past_Player(D3DXVECTOR3 Position_Past);
//void Set_Position_for_Position_Past(void);
//void Set_Rotation_Player(D3DXVECTOR3 Rotation);
//void Set_Scale_Player(D3DXVECTOR3 Scale);
//void Set_Player_Animation_Identification(int Animation_Index);
//void Set_Player_Animation(int Animation_Index, float Play_Speed);
//void Set_Player_Target_Angle(float Target_Angle);
//
//// Get
//ANIMATION_3D *Get_Player_Animation(void);
//COLLISION *Get_Collision_Player(void);
//float Get_Collision_Radius_Player(void);
//D3DXVECTOR3 Get_Position_Player(void);
//D3DXVECTOR3 Get_Position_Past_Player(void);
//D3DXVECTOR3 Get_Rotation_Player(void);
//D3DXVECTOR3 Get_Scale_Player(void);
//int Get_Player_Animation_Identification(void);
//float Get_Player_Target_Angle(void);
//PLAYER *Get_Player(void);
//
//// Debug
//#ifdef _DEBUG
//void Draw_Player_Debug(DEBUG *Debug);
//void Draw_Animation_3D_Debug(DEBUG *Debug);
//#endif
//#endif