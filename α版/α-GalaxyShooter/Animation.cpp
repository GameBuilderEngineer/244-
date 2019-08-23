////====================================================================================================================================================================================
//// 概要
//// ファイル名：Animation_3D.cpp
//// コーディングフォント：Ricty Diminished( 16サイズ )
//// 作成者：HAL東京 GP-11B-341 07 亀岡竣介
//// 作成日：2018/12/10
////====================================================================================================================================================================================
//
////====================================================================================================================================================================================
//// インクルード
////====================================================================================================================================================================================
//#include "Main.h"
//#include "Allocate_Hierarchy.h"
//#include "Animation_3D.h"
//#include "Message.h"
//#include "Player.h"
////====================================================================================================================================================================================
//// 領域 - 初期化
////====================================================================================================================================================================================
//#pragma region Initialize
////====================================================================================================================================================================================
//// アニメーション( 3D )の初期化
//// 関数名：HRESULT Initialize_Animation_3D
//// 戻り値：HRESULT
//// 引数 1：ANIMATION_3D*
//// 引数 2：LPCSTR
//// 引数 3：int
////====================================================================================================================================================================================
//HRESULT Initialize_Animation_3D(ANIMATION_3D *Animation, LPCSTR Set_Name, int Set_No)
//{
//	Animation->Animation_Controller->GetAnimationSetByName(Set_Name, &Animation->Animation_3D_Management[Set_No].Animation_Set);
//
//	Animation->Animation_3D_Management[Set_No].Animation_Set_Name = Animation->Animation_3D_Management[Set_No].Animation_Set->GetName();
//
//	// 正常終了
//	return S_OK;
//}
//#pragma endregion
////====================================================================================================================================================================================
//// 領域 - 解放
////====================================================================================================================================================================================
//#pragma region Release
////====================================================================================================================================================================================
//// アニメーション( 3D )の解放
//// 関数名：void Release_Animation_3D
//// 戻り値：void
//// 引数 2：ANIMATION_3D*
////====================================================================================================================================================================================
//void Release_Animation_3D(ANIMATION_3D *Animation)
//{
//	D3DXFrameDestroy(Animation->Root_Frame, Animation->Allocate_Hierarchy);
//
//	Start_Critical_Section();
//	SAFE_DELETE(Animation->Animation_3D_Management);
//	SAFE_RELEASE(Animation->Animation_Controller);
//	SAFE_DELETE(Animation->Allocate_Hierarchy);
//	SAFE_DELETE(Animation);
//	End_Critical_Section();
//
//	return;
//}
//#pragma endregion
////====================================================================================================================================================================================
//// 領域 - 更新
////====================================================================================================================================================================================
//#pragma region Update
////====================================================================================================================================================================================
//// アニメーション( 3D )の更新
//// 関数名：void Update_Animation_3D
//// 戻り値：void
//// 引数 1：ANIMATION_3D*
//// 引数 2：float
////====================================================================================================================================================================================
//void Update_Animation_3D(ANIMATION_3D *Animation, float Time)
//{
//	// 変数宣言
//	CALL_BACK_ANIMATION_3D Call_Back_Animation;	//	コールバックハンドル
//
//	// ハンドルにポインタを代入
//	Call_Back_Animation.Animation_Pointer = Animation;
//	Call_Back_Animation.Set_Name = Animation->Animation_3D_Management[Animation->Playing_Animation_Identification_Current].Animation_Set_Name;
//
//	// 合成中かの判定
//	Animation->Animation_3D_Management[Animation->Playing_Animation_Identification_Current].Weight_Time_Current += Time;
//
//	// 合成中
//	if (Animation->Animation_3D_Management[Animation->Playing_Animation_Identification_Current].Weight_Time_Current <= Animation->Animation_3D_Management[Animation->Playing_Animation_Identification_Current].Shift_Time)
//	{
//		// ウェイトを算出
//
//		// 変数宣言：初期化
//		float Weight = Animation->Animation_3D_Management[Animation->Playing_Animation_Identification_Current].Weight_Time_Current / Animation->Animation_3D_Management[Animation->Playing_Animation_Identification_Current].Shift_Time;
//		
//		// ウェイトを登録
//
//		// 現在のアニメーション
//		Animation->Animation_Controller->SetTrackWeight(0, Weight);
//
//		// 過去のアニメーション
//		Animation->Animation_Controller->SetTrackWeight(1, 1 - Weight);
//	}
//	// 合成終了
//	else
//	{
//		// 通常アニメーションの"Track0"のウェイトを最大値に設定
//
//		// 現在のアニメーション
//		Animation->Animation_Controller->SetTrackWeight(0, 1.0f);
//
//		// 過去のアニメーションを無効化
//		Animation->Animation_Controller->SetTrackEnable(1, false);
//	}
//
//	// 時間を更新
//
//	// もし現在がコールバック時間なら、"AdvanceTime"関数内でコールバックが実行
//	Animation->Animation_Controller->AdvanceTime(Time, &Call_Back_Animation);
//
//	return;
//}
//
////====================================================================================================================================================================================
//// フレーム内の、変更された代替正方形座を更新
//// 関数名：void Update_Frame_Matrix
//// 戻り値：void
//// 引数 1：ORIGIN_DEVICE*
//// 引数 2：LPD3DXFRAME
//// 引数 3：LPD3DXMATRIX
////====================================================================================================================================================================================
//void Update_Frame_Matrix(LPDIRECT3DDEVICE9 Device, LPD3DXFRAME Base_Frame, LPD3DXMATRIX Parent_Matrix)
//{
//	// ポインタ変数宣言：初期化
//	D3DXFRAME_DERIVED *Frame_Pointer = (D3DXFRAME_DERIVED*)Base_Frame;	//	フレームポインタ
//
//	// 早期リターン
//	if (Base_Frame == NULL || Parent_Matrix == NULL)
//	{
//		return;
//	}
//
//	// このボーンは累積計算を行うために、親スケルトンのオフセット方程式マトリクスに対して相対的
//	D3DXMatrixMultiply(&Frame_Pointer->Combined_Transformation_Matrix, &Frame_Pointer->TransformationMatrix, Parent_Matrix);
//
//	// 兄弟ボーンの更新
//	Update_Frame_Matrix(Device, Frame_Pointer->pFrameSibling, Parent_Matrix);
//
//	// 子ボーンの更新
//	Update_Frame_Matrix(Device, Frame_Pointer->pFrameFirstChild, &Frame_Pointer->Combined_Transformation_Matrix);
//
//	return;
//}
//#pragma endregion
////====================================================================================================================================================================================
//// 領域 - 描画
////====================================================================================================================================================================================
//#pragma region Draw
////====================================================================================================================================================================================
//// アニメーション( 3D )の描画
//// 関数名：void Draw_Animation_3D
//// 戻り値：void
//// 引数 1：ORIGIN_DEVICE*
//// 引数 2：ANIMATION_3D*
//// 引数 3：LPD3DXMATRIX
////====================================================================================================================================================================================
//void Draw_Animation_3D(ORIGIN_DEVICE *Device, ANIMATION_3D *Animation, LPD3DXMATRIX World_Matrix)
//{
//	Update_Frame_Matrix(Device->Interface, Animation->Root_Frame, World_Matrix);
//
//	Draw_Frame(Device, Animation, Animation->Root_Frame);
//
//	return;
//}
//
////====================================================================================================================================================================================
//// フレーム( ボーン )の描画
//// 関数名：void Draw_Bone
//// 戻り値：void
//// 引数 1：ORIGIN_DEVICE*
//// 引数 2：ANIMATION_3D*
//// 引数 3：LPD3DXFRAME
////====================================================================================================================================================================================
//void Draw_Frame(ORIGIN_DEVICE *Device, ANIMATION_3D *Animation, LPD3DXFRAME Frame)
//{
//	// 変数宣言：初期化
//	LPD3DXMESHCONTAINER Mesh_Container = NULL;	//	メッシュコンテナ
//
//	// 早期リターン
//	if (Frame == NULL)
//	{
//		return;
//	}
//
//	// メッシュコンテナの取得
//	Mesh_Container = Frame->pMeshContainer;
//
//	// メッシュコンテナの描画
//	while (Mesh_Container != NULL)
//	{
//		// スキンメッシュの描画
//		Draw_Mesh_Container(Mesh_Container, Frame);
//
//		// 全てのメッシュコンテナを検索
//		Mesh_Container = Mesh_Container->pNextMeshContainer;
//	}
//
//	// 兄弟フレームの描画
//	Draw_Frame(Device, Animation, Frame->pFrameSibling);
//
//	// 子フレームの描画
//	Draw_Frame(Device, Animation, Frame->pFrameFirstChild);
//
//	return;
//}
//
////====================================================================================================================================================================================
//// メッシュコンテナ( スキンメッシュ )の描画
//// 関数名：void Draw_Mesh_Container
//// 戻り値：void
//// 引数 1：LPD3DXMESHCONTAINER
//// 引数 2：LPD3DXFRAME
////====================================================================================================================================================================================
//void Draw_Mesh_Container(LPD3DXMESHCONTAINER Base_Mesh_Container, LPD3DXFRAME Base_Frame)
//{
//	// 変数宣言：初期化
//	D3DCAPS9 Caps;				//	キャップ
//	D3DXMATRIXA16 Local_Matrix;	//	ローカルマトリクス
//	UINT Matrix_Index = NULL;	//	マトリクスインデックス
//	UINT Blend_Number = NULL;	//	ブレンド数
//
//	// ポインタ変数宣言：初期化
//	D3DXMESHCONTAINER_DERIVED *Mesh_Container_Pointer = (D3DXMESHCONTAINER_DERIVED*)Base_Mesh_Container;	//	メッシュコンテナポインタ
//	D3DXFRAME_DERIVED *Frame_Pointer = (D3DXFRAME_DERIVED*)Base_Frame;										//	フレームポインタ
//
//	// キャップの調査
//	Get_Device_Caps(&Caps);
//
//	// スキニングの最初のチェック
//	if (Mesh_Container_Pointer->pSkinInfo != NULL)
//	{
//		// 変数宣言：初期化
//		LPD3DXBONECOMBINATION Bone_Combination = NULL;	//	ボーンの組み合わせ
//		DWORD Attribute_Index_Past = NULL;				//	アトリビュートインデックス( 過去 )
//
//		Attribute_Index_Past = UNUSED32;
//
//		Bone_Combination = reinterpret_cast<LPD3DXBONECOMBINATION>(Mesh_Container_Pointer->Bone_Combination_Buffer->GetBufferPointer());
//
//		// デバイスのデフォルトの頂点処理( 通常はHW )を使用して描画
//		for (UINT Attribute_Index = 0; Attribute_Index < Mesh_Container_Pointer->Bone_Max; Attribute_Index++)
//		{
//			Blend_Number = 0;
//
//			for (DWORD i = 0; i < Mesh_Container_Pointer->Bone_Weight_Max; ++i)
//			{
//				if (Bone_Combination[Attribute_Index].BoneId[i] != UINT_MAX)
//				{
//					Blend_Number = i;
//				}
//			}
//
//			if (Caps.MaxVertexBlendMatrices >= Blend_Number + 1)
//			{
//				// 最初に、現在のブレンドウェイトセットのワールドマトリクスを計算し、ブレンド数の正確なカウントを取得
//				for (DWORD i = 0; i < Mesh_Container_Pointer->Bone_Weight_Max; ++i)
//				{
//					Matrix_Index = Bone_Combination[Attribute_Index].BoneId[i];
//
//					if (Matrix_Index != UINT_MAX)
//					{
//						D3DXMatrixMultiply(&Local_Matrix, &Mesh_Container_Pointer->Bone_Offset_Matrix[Matrix_Index], Mesh_Container_Pointer->Bone_Matrix[Matrix_Index]);
//
//						Set_Transform(D3DTS_WORLDMATRIX(i), &Local_Matrix);
//					}
//				}
//
//				// レンダリングステートの設定
//				Set_Rendering_State(D3DRS_VERTEXBLEND, Blend_Number);
//
//				// 部分集合に使用されているマテリアルを検索
//				if ((Attribute_Index_Past != Bone_Combination[Attribute_Index].AttribId) || (Attribute_Index_Past == UNUSED32))
//				{
//					Set_Material(&Mesh_Container_Pointer->pMaterials[Bone_Combination[Attribute_Index].AttribId].MatD3D);
//					Set_Texture(0, Mesh_Container_Pointer->Texture[Bone_Combination[Attribute_Index].AttribId]);
//
//					Attribute_Index_Past = Bone_Combination[Attribute_Index].AttribId;
//				}
//				// 正しい材料と行列がロードされたので、サブセットを描画
//				Mesh_Container_Pointer->MeshData.pMesh->DrawSubset(Attribute_Index);
//			}
//		}
//		// レンダリングステートの設定
//		Set_Rendering_State(D3DRS_VERTEXBLEND, 0);
//	}
//	// 標準メッシュ、材料特性を設定した後に描画
//	else
//	{
//		Set_Transform(D3DTS_WORLD, &Frame_Pointer->Combined_Transformation_Matrix);
//
//		for (UINT Material_Index = 0; Material_Index < Mesh_Container_Pointer->NumMaterials; Material_Index++)
//		{
//			Set_Material(&Mesh_Container_Pointer->pMaterials[Material_Index].MatD3D);
//			Set_Texture(0, Mesh_Container_Pointer->Texture[Material_Index]);
//
//			Mesh_Container_Pointer->MeshData.pMesh->DrawSubset(Material_Index);
//		}
//	}
//
//	return;
//}
//#pragma endregion
////====================================================================================================================================================================================
//// 領域 - 切り替え
////====================================================================================================================================================================================
//#pragma region Switching
////====================================================================================================================================================================================
//// アニメーション( 3D )の切り替え
//// 関数名：void Switching_Animation_3D
//// 戻り値：void
//// 引数 1：ANIMATION_3D*
//// 引数 2：UINT
//// 引数 3：float
////====================================================================================================================================================================================
//void Switching_Animation_3D(ANIMATION_3D *Animation, UINT Animation_Identification, float Play_Speed)
//{
//	// 変数宣言：初期化
//	D3DXTRACK_DESC Track_Description;	//	トラックの能力
//
//	Animation->Animation_End_Flag = false;
//
//	Animation->Move_Stop_Flag = false;
//
//	Animation->Key_Frame_Count = 0;
//
//	// 指定のアニメーションIDの存在を調査
//	if (Animation_Identification > (UINT)Animation->Animation_Set_Max)
//	{
//		// 終了
//		return;
//	}
//
//	// 指定のアニメーションIDが、現在のアニメーションIDと同じであれば、更新不要のため終了
//	if (Animation->Playing_Animation_Identification_Current == Animation_Identification)
//	{
//		// 終了
//		return;
//	}
//
//	// 現在のアニメーションセットの設定値を取得
//	Animation->Animation_Controller->GetTrackDesc(0, &Track_Description);
//
//	// 現在のアニメーションをトラック１に移行し、トラックの設定値も移行
//	Animation->Animation_Controller->SetTrackAnimationSet(1, Animation->Animation_3D_Management[Animation->Playing_Animation_Identification_Current].Animation_Set);
//	Animation->Animation_Controller->SetTrackDesc(1, &Track_Description);
//	Animation->Animation_Controller->SetTrackSpeed(1, 0.0f);
//
//	// 新しいアニメーションセットをトラック０に設定
//	Animation->Animation_Controller->SetTrackAnimationSet(0, Animation->Animation_3D_Management[Animation_Identification].Animation_Set);
//
//	// トラック０のスピードの設定
//	Animation->Animation_Controller->SetTrackSpeed(0, Play_Speed);
//
//	// トラック０の位置を、開始位置に設定
//	Animation->Animation_Controller->SetTrackPosition(0, 0.0f);
//
//	// トラックの合成を許可
//	Animation->Animation_Controller->SetTrackEnable(0, true);
//	Animation->Animation_Controller->SetTrackEnable(1, true);
//
//	// ウェイト時間を初期化
//	Animation->Animation_3D_Management[Animation_Identification].Weight_Time_Current = 0.0f;
//	Animation->Animation_Controller->ResetTime();
//
//	// 現在のアニメーション番号を切り替え
//	Animation->Playing_Animation_Identification_Past = Animation->Playing_Animation_Identification_Current;
//	Animation->Playing_Animation_Identification_Current = Animation_Identification;
//
//	return;
//}
//#pragma endregion
////====================================================================================================================================================================================
//// 領域 - 作成
////====================================================================================================================================================================================
//#pragma region Create
////====================================================================================================================================================================================
//// アニメーション( 3D )オブジェクトを作成
//// 関数名：ANIMATION_3D* Create_Object_Animation_3D
//// 戻り値：ANIMATION_3D*
////====================================================================================================================================================================================
//ANIMATION_3D* Create_Object_Animation_3D(void)
//{
//	// ポインタ変数宣言：初期化
//	ANIMATION_3D *Object = (ANIMATION_3D*)calloc(1, sizeof(ANIMATION_3D));	//	オブジェクトポインタ
//
//	Object->Initialize_Animation_3D = Initialize_Animation_3D;
//	Object->Release_Animation_3D = Release_Animation_3D;
//	Object->Update_Animation_3D = Update_Animation_3D;
//	Object->Draw_Animation_3D = Draw_Animation_3D;
//	Object->Switching_Animation_3D = Switching_Animation_3D;
//	Object->Set_Shift_Time_Animation_3D = Set_Shift_Time_Animation_3D;
//
//	// 終了
//	return Object;
//}
//#pragma endregion
////====================================================================================================================================================================================
//// 領域 - 読み込み
////====================================================================================================================================================================================
//#pragma region Load
////====================================================================================================================================================================================
//// Xファイルの読み込み
//// 関数名：HRESULT Load_X_File
//// 戻り値：HRESULT
//// 引数 1：ANIMATION_3D*
//// 引数 2：LPCTSTR
////====================================================================================================================================================================================
//HRESULT Load_X_File(ANIMATION_3D *Animation, LPCTSTR File_Name)
//{
//	Animation->Allocate_Hierarchy = new ALLOCATE_HIERARCHY(_device);
//
//	Load_Mesh_Hierarchy(File_Name, Animation->Allocate_Hierarchy, &Animation->Root_Frame, &Animation->Animation_Controller);
//
//	Set_Bone_Matrix(Animation->Root_Frame, Animation->Root_Frame);
//
//	Animation->Animation_End_Flag = false;
//
//	Animation->Animation_Set_Max = Animation->Animation_Controller->GetMaxNumAnimationSets();
//
//	// Xファイル内のアニメーションセットの数に基づいて、アニメーションセットメンバ変数に、配列を動的に割り当てる
//	if (FAILED(Animation->Animation_3D_Management = (ANIMATION_3D_MANAGEMENT*)malloc(sizeof(ANIMATION_3D_MANAGEMENT) * Animation->Animation_Set_Max)))
//	{
//		// エラーメッセージの出力
//		Message_Window(MESSAGE_WINDOW_TYPE_ERROR_MEMORY_ALLOCATE);
//	}
//
//	// 正常終了
//	return S_OK;
//}
//#pragma endregion
////====================================================================================================================================================================================
//// 領域 - 調査
////====================================================================================================================================================================================
//#pragma region Search
////====================================================================================================================================================================================
//// 特定のボーンフレームを調査
//// 関数名：D3DXFRAME_DERIVED* Search_Bone_Frame
//// 戻り値：D3DXFRAME_DERIVED*
//// 引数 1：ANIMATION_3D*
//// 引数 2：const char*
//// 引数 3：D3DXFRAME*
////====================================================================================================================================================================================
//D3DXFRAME_DERIVED* Search_Bone_Frame(ANIMATION_3D *Animation, const char *Bone_Name, D3DXFRAME *Frame)
//{
//	// ポインタ変数宣言：初期化
//	D3DXFRAME_DERIVED *Frame_Pointer = NULL;	//	フレームポインタ
//
//	// 早期リターン
//	if (Frame == NULL)
//	{
//		return NULL;
//	}
//
//	if (Frame->Name != NULL && strcmp(Frame->Name, Bone_Name) == 0)
//	{
//		Frame_Pointer = (D3DXFRAME_DERIVED*)Frame;
//
//		return Frame_Pointer;
//	}
//
//	if (Frame->pFrameSibling != NULL)
//	{
//		Frame_Pointer = Search_Bone_Frame(Animation, Bone_Name, Frame->pFrameSibling);
//
//		if (Frame_Pointer != NULL && strcmp(Frame_Pointer->Name, Bone_Name) == 0)
//		{
//			return Frame_Pointer;
//		}
//	}
//
//	if (Frame->pFrameFirstChild != NULL)
//	{
//		Frame_Pointer = Search_Bone_Frame(Animation, Bone_Name, Frame->pFrameFirstChild);
//
//		if (Frame_Pointer != NULL && strcmp(Frame_Pointer->Name, Bone_Name) == 0)
//		{
//			return Frame_Pointer;
//		}
//	}
//
//	// 終了
//	return NULL;
//}
//#pragma endregion
////====================================================================================================================================================================================
//// 領域 - 設定
////====================================================================================================================================================================================
//#pragma region Set
////====================================================================================================================================================================================
//// 動作開始に必要な時間を設定
//// 関数名：void Set_Shift_Time_Animation_3D
//// 戻り値：void
//// 引数 1：ANIMATION_3D*
//// 引数 2：UINT
//// 引数 3：float
////====================================================================================================================================================================================
//void Set_Shift_Time_Animation_3D(ANIMATION_3D *Animation, UINT Animation_Identification, float Interval)
//{
//	// 指定のアニメーションIDの存在を調査
//
//	// 早期リターン
//	if (Animation_Identification > (UINT)Animation->Animation_Set_Max)
//	{
//		return;
//	}
//
//	// シフト時間を登録
//	Animation->Animation_3D_Management[Animation_Identification].Shift_Time = Interval;
//
//	return;
//}
//
////====================================================================================================================================================================================
//// 各レベルフレームの組み合わせ変換行列を設定
//// 関数名：HRESULT Set_Bone_Matrix
//// 戻り値：HRESULT
//// 引数 1：LPD3DXFRAME
//// 引数 2：LPD3DXFRAME
////====================================================================================================================================================================================
//HRESULT Set_Bone_Matrix(LPD3DXFRAME Base_Frame, LPD3DXFRAME Root_Frame)
//{
//	if (Base_Frame->pMeshContainer != NULL)
//	{
//		// ポインタ変数宣言：初期化
//		D3DXFRAME_DERIVED *Frame_Pointer = NULL;																	//	フレームポインタ
//		D3DXMESHCONTAINER_DERIVED *Mesh_Container_Pointer = (D3DXMESHCONTAINER_DERIVED*)Base_Frame->pMeshContainer;	//	メッシュコンテナポインタ
//
//		// スキンメッシュが存在する場合は、ボーンマトリクスを設定
//		if (Mesh_Container_Pointer->pSkinInfo != NULL)
//		{
//			// 変数宣言：初期化
//			UINT Count_Bone = Mesh_Container_Pointer->pSkinInfo->GetNumBones();	//	ボーンカウント
//
//			Mesh_Container_Pointer->Bone_Matrix = new D3DXMATRIX*[Count_Bone];
//
//			for (UINT Index_Bone = 0; Index_Bone < Count_Bone; Index_Bone++)
//			{
//				Frame_Pointer = (D3DXFRAME_DERIVED*)D3DXFrameFind(Root_Frame, Mesh_Container_Pointer->pSkinInfo->GetBoneName(Index_Bone));
//
//				if (Frame_Pointer == NULL)
//				{
//					return E_FAIL;
//				}
//				Mesh_Container_Pointer->Bone_Matrix[Index_Bone] = &Frame_Pointer->Combined_Transformation_Matrix;
//			}
//		}
//	}
//
//	if (Base_Frame->pFrameSibling != NULL)
//	{
//		Set_Bone_Matrix(Base_Frame->pFrameSibling, Root_Frame);
//	}
//
//	if (Base_Frame->pFrameFirstChild != NULL)
//	{
//		Set_Bone_Matrix(Base_Frame->pFrameFirstChild, Root_Frame);
//	}
//
//	// 正常終了
//	return S_OK;
//}
//
////====================================================================================================================================================================================
//// アニメーション中断イベント( キーフレーム )を設置
//// 関数名：HRESULT Set_Call_Back_Key_Frame
//// 戻り値：HRESULT Set_Call_Back_Key_Frame
//// 引数 1：ANIMATION_3D*
//// 引数 2：LPCSTR
////====================================================================================================================================================================================
//HRESULT Set_Call_Back_Key_Frame(ANIMATION_3D *Animation, LPCSTR Set_Name)
//{
//	// 変数宣言：初期化
//	// 設置するコールバックキーの数
//	const UINT Call_Back_Number = 2;						//	２つめのコールバック
//	D3DXKEY_CALLBACK Key[Call_Back_Number] = { NULL,NULL };	//	キーコールバック
//	ID3DXBuffer *Compressed_Information = 0;				//	圧縮情報
//	double Time_Scale_Coefficient = NULL;					//	タイムスケール係数
//
//	// ポインタ変数宣言：初期化
//	ID3DXKeyframedAnimationSet *Animation_Set_Key_Framed = 0;	// キーフレームを設置するアニメーションセット
//	ID3DXCompressedAnimationSet *Animation_Set_Compressed = 0;	// キーフレームを設置後の新しいアニメーションセット
//
//	Animation->Animation_Controller->GetAnimationSetByName(Set_Name, (ID3DXAnimationSet**)&Animation_Set_Key_Framed);
//
//	// 圧縮
//	Animation_Set_Key_Framed->Compress(D3DXCOMPRESS_DEFAULT, 0.5f, 0, &Compressed_Information);
//
//	Time_Scale_Coefficient = Animation_Set_Key_Framed->GetSourceTicksPerSecond();	//	GetSourceTicksPerSecond関数："D3DXCreateKeyFrameInterpolator"に渡すタイムスケール係数を返す：この値は、ローカルタイムをグローバル( アプリケーション )タイムにスケーリングするために使用する
//
//	Key[0].Time = (float)(Animation_Set_Key_Framed->GetPeriod() * (90.0f / 125.0f) * Time_Scale_Coefficient);
//
//	// アニメーションの最後にコールバックを実行するように、２番目のコールバックキーを設定
//	Key[1].Time = (float)(Animation_Set_Key_Framed->GetPeriod() * 0.9f * Time_Scale_Coefficient);
//
//	D3DXCreateCompressedAnimationSet
//	(
//		Animation_Set_Key_Framed->GetName(),
//		Animation_Set_Key_Framed->GetSourceTicksPerSecond(),
//		Animation_Set_Key_Framed->GetPlaybackType(),
//		Compressed_Information,
//		Call_Back_Number,
//		Key,
//		&Animation_Set_Compressed
//	);
//
//	// 圧縮情報の解放
//	Start_Critical_Section();
//	SAFE_RELEASE(Compressed_Information);
//	End_Critical_Section();
//
//	// 過去の( 圧縮されていない )アニメーションセットを削除
//	Animation->Animation_Controller->UnregisterAnimationSet(Animation_Set_Key_Framed);
//	Start_Critical_Section();
//	SAFE_RELEASE(Animation_Set_Key_Framed);
//	End_Critical_Section();
//
//	// 新しい( 圧縮された )アニメーションセットを追加
//	Animation->Animation_Controller->RegisterAnimationSet(Animation_Set_Compressed);
//	Start_Critical_Section();
//	SAFE_RELEASE(Animation_Set_Compressed);
//	End_Critical_Section();
//
//	// 正常終了
//	return S_OK;
//}
//#pragma endregion
////====================================================================================================================================================================================
//// 領域 - 取得
////====================================================================================================================================================================================
//#pragma region Get
////====================================================================================================================================================================================
//// 特定のボーンマトリクスを取得
//// 関数名：D3DXMATRIX Get_Bone_Matrix
//// 戻り値：D3DXMATRIX
//// 引数 1：ANIMATION_3D*
//// 引数 2：const char*
////====================================================================================================================================================================================
//D3DXMATRIX Get_Bone_Matrix(ANIMATION_3D *Animation, const char *Bone_Name)
//{
//	// ポインタ変数宣言：初期化
//	D3DXFRAME_DERIVED *Frame_Pointer = Search_Bone_Frame(Animation, Bone_Name, Animation->Root_Frame);	//	フレームポインタ
//
//	// ボーンを発見成功
//	if ((Frame_Pointer != NULL) && (Frame_Pointer->Name != NULL) && (strcmp(Frame_Pointer->Name, Bone_Name) == 0))
//	{
//		return Frame_Pointer->Combined_Transformation_Matrix;
//	}
//
//	// ボーンを発見失敗
//
//	// 変数宣言：初期化
//	D3DXMATRIX Local_Matrix;	//	ローカルマトリクス
//
//	D3DXMatrixIdentity(&Local_Matrix);
//
//	return Local_Matrix;
//}
//#pragma endregion
////====================================================================================================================================================================================
//// 領域 - コールバック
////====================================================================================================================================================================================
//#pragma region Call_Back
////====================================================================================================================================================================================
//// アニメーション再生中の、中断コールバック
//// 関数名：HRESULT CALL_BACK_ANIMATION_3D Call_Back_Animation
//// 戻り値：HRESULT CALL_BACK_ANIMATION_3D
//// 引数 1：UINT
//// 引数 2：LPVOID
////====================================================================================================================================================================================
//HRESULT CALL_BACK_ANIMATION_3D::HandleCallback(UINT Track, LPVOID pCallbackData)
//{
//	// 変数宣言：初期化
//	UINT Storage_Track = Track;				//	警告回避用
//	LPVOID Storage_Data = pCallbackData;	//	警告回避用
//
//	// 警告回避のため、適当な処理
//	Storage_Track = NULL;
//	Storage_Data = NULL;
//
//	if (Animation_Pointer->Key_Frame_Count == 0)
//	{
//		Animation_Pointer->Move_Stop_Flag = true;
//	}
//	else if (Animation_Pointer->Key_Frame_Count == 1)
//	{
//		Animation_Pointer->Animation_End_Flag = true;
//
//		return D3D_OK;
//	}
//
//	Animation_Pointer->Key_Frame_Count++;
//
//	return D3D_OK;
//}
//#pragma endregion