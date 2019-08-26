////====================================================================================================================================================================================
//// 概要
//// ファイル名：Animation_3D.h
//// コーディングフォント：Ricty Diminished( 16サイズ )
//// 作成者：HAL東京 GP-11B-341 07 亀岡竣介
//// 作成日：2018/12/10
////====================================================================================================================================================================================
//#ifndef _ANIMATION_3D_H_
//#define _ANIMATION_3D_H_
////====================================================================================================================================================================================
//// インクルード
////====================================================================================================================================================================================
//#include "Allocate_Hierarchy.h"
////====================================================================================================================================================================================
//// マクロ定義
////====================================================================================================================================================================================
//#define ANIMATION_3D_MAX (ANIMATION_3D_TYPE_MAX)	//	アニメーション( 3D )の最大数
////====================================================================================================================================================================================
//// 列挙型定義
////====================================================================================================================================================================================
//enum ANIMATION_TYPE
//{
//	ANIMATION_3D_TYPE_IDLE,
//	ANIMATION_3D_TYPE_WALK,
//	ANIMATION_3D_TYPE_RUN,
//	ANIMATION_3D_TYPE_JUMP,
//	ANIMATION_3D_TYPE_RUN_JUMP,
//	ANIMATION_3D_TYPE_STAND_UP,
//	ANIMATION_3D_TYPE_SUPER_NATURAL,
//	ANIMATION_3D_TYPE_SUPER_NATURAL_POSE,
//	ANIMATION_3D_TYPE_LUMINA,
//	ANIMATION_3D_TYPE_SIT_DOWN,
//	ANIMATION_3D_TYPE_SIT_DOWN_POSE,
//	ANIMATION_3D_TYPE_JUMP_OFF,
//	ANIMATION_3D_TYPE_FALL,
//	ANIMATION_3D_TYPE_IN_THE_SEA,
//	ANIMATION_3D_TYPE_IN_THE_SEA_POSE,
//	ANIMATION_3D_TYPE_STAND_UP_INITIAL,
//	ANIMATION_3D_TYPE_MAX,
//};
////====================================================================================================================================================================================
//// 構造体定義
////====================================================================================================================================================================================
//typedef struct
//{
//	ID3DXAnimationSet *Animation_Set;	//	アニメーションセット
//	LPCSTR Animation_Set_Name;			//	アニメーションセットの名前
//	float Shift_Time;					//	シフトするのに必要な時間
//	float Weight_Time_Current;			//	現在のウェイト時間
//}ANIMATION_3D_MANAGEMENT;
//struct ANIMATION_3D
//{
//	// メンバ変数
//	ANIMATION_3D_MANAGEMENT *Animation_3D_Management;	//	アニメーションセットの管理
//	LPD3DXANIMATIONCONTROLLER Animation_Controller;		//	アニメーションコントローラ
//	ALLOCATE_HIERARCHY *Allocate_Hierarchy;				//	Xファイルの情報
//	LPD3DXFRAME Root_Frame;								//	ルートフレーム( フレーム階層構造の最上位フレーム )
//	UINT Playing_Animation_Identification_Current;		//	現在、再生しているアニメーションID
//	UINT Playing_Animation_Identification_Past;			//	過去、再生していたアニメーションID
//	int Animation_Set_Max;								//	アニメーションセットの最大数
//	int Key_Frame_Count;								//	コールバック( Key_Frame )の処理数
//	bool Animation_End_Flag;							//	アニメーションの終了フラグ
//	bool Move_Stop_Flag;								//	移動停止フラグ
//	bool Animation_Play_Flag = NULL;					//	アニメーションの再生フラグ
//	// メンバ関数
//	HRESULT(*Initialize_Animation_3D)(ANIMATION_3D *Animation, LPCSTR Set_Name, int Set_No);
//	void(*Release_Animation_3D)(ANIMATION_3D *Animation);
//	void(*Update_Animation_3D)(ANIMATION_3D *Animation, float Time);
//	void(*Draw_Animation_3D)(ORIGIN_DEVICE *Device, ANIMATION_3D *Animation, LPD3DXMATRIX World_Matrix);
//	void(*Switching_Animation_3D)(ANIMATION_3D *Animation, UINT Animation_Identification, float Play_Speed);
//	void(*Set_Shift_Time_Animation_3D)(ANIMATION_3D *Animation, UINT Animation_Identification, float Interval);
//};
//struct CALL_BACK_ANIMATION_3D : public ID3DXAnimationCallbackHandler
//{
//	ANIMATION_3D *Animation_Pointer;											//	アニメーションポインタ
//	LPCSTR Set_Name;															//	セット名
//	int Animation_Status;														//	アニメーションステータス
//	HRESULT CALLBACK HandleCallback(THIS_ UINT Track, LPVOID pCallbackData);	//	コールバックハンドル
//};
////====================================================================================================================================================================================
//// プロトタイプ宣言
////====================================================================================================================================================================================
//// Initialize
//HRESULT Initialize_Animation_3D(ANIMATION_3D *Animation, LPCSTR Set_Name, int Set_No);
//
//// Release
//void Release_Animation_3D(ANIMATION_3D *Animation);
//
//// Update
//void Update_Animation_3D(ANIMATION_3D *Animation, float Time);
//void Update_Frame_Matrix(LPDIRECT3DDEVICE9 Device, LPD3DXFRAME Base_Frame, LPD3DXMATRIX Parent_Matrix);
//
//// Draw
//void Draw_Animation_3D(ORIGIN_DEVICE *Device, ANIMATION_3D *Animation, LPD3DXMATRIX World_Matrix);
//void Draw_Frame(ORIGIN_DEVICE *Device, ANIMATION_3D *Animation, LPD3DXFRAME Frame);
//void Draw_Mesh_Container(LPD3DXMESHCONTAINER Base_Mesh_Container, LPD3DXFRAME Base_Frame);
//
//// Switching
//void Switching_Animation_3D(ANIMATION_3D *Animation, UINT Animation_Identification, float Play_Speed);
//
//// Create
//ANIMATION_3D* Create_Object_Animation_3D(void);
//
//// Load
//HRESULT Load_X_File(ANIMATION_3D *Animation, LPCTSTR File_Name);
//
//// Search
//D3DXFRAME_DERIVED* Search_Bone_Frame(ANIMATION_3D *Animation, const char *Bone_Name, D3DXFRAME *Frame);
//
//// Set
//void Set_Shift_Time_Animation_3D(ANIMATION_3D *Animation, UINT Animation_Identification, float Interval);
//HRESULT Set_Bone_Matrix(LPD3DXFRAME Base_Frame, LPD3DXFRAME Root_Frame);
//HRESULT Set_Call_Back_Key_Frame(ANIMATION_3D *Animation, LPCSTR Set_Name);
//
//// Get
//D3DXMATRIX Get_Bone_Matrix(ANIMATION_3D *Animation, const char *Bone_Name);
//#endif