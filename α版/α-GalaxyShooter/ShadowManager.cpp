////-----------------------------------------------------------------------------
//// 影処理 [ShadowManager.cpp]
//// Author：GP12A332 32 中込和輝
//// 作成日：2019/9/9
////-----------------------------------------------------------------------------
//#include "ShadowManager.h"
//
////=============================================================================
//// インスタンシング描画クラス：初期化処理
////=============================================================================
//HRESULT InstancingShadowRender::initialize(LPDIRECT3DDEVICE9 device, LPD3DXEFFECT effect, LPDIRECT3DTEXTURE9 texture)
//{
//	InstancingBillboard::initialize(device, effect, texture);
//	return S_OK;
//}
//
//
////=============================================================================
//// インスタンシング描画クラス：描画処理
////=============================================================================
//void InstancingShadowRender::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
//{
//	if (!onRender)return;
//	if (renderNum <= 0)return;
//	// 回転を打ち消す。
//	D3DXMATRIX cancelRotation = view;
//	cancelRotation._41 = cancelRotation._42 = cancelRotation._43 = 0;
//	D3DXMatrixInverse(&cancelRotation, NULL, &cancelRotation);
//
//	//αテスト
//	device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
//	device->SetRenderState(D3DRS_ALPHAREF, 0x00);
//
//	// αブレンドを行う
//	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
//	// αソースカラーの指定
//	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	// αデスティネーションカラーの指定
//	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
//
//	//インスタンス宣言
//	device->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | renderNum);
//	device->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);
//
//	// 頂点宣言を通知
//	device->SetVertexDeclaration(declation);
//
//	//デバイスデータストリームにメッシュの頂点バッファをバインド
//	device->SetStreamSource(0, vertexBuffer, 0, sizeof(InstancingBillboardVertex));
//	device->SetStreamSource(1, positionBuffer, 0, sizeof(D3DXVECTOR3));
//
//	//インデックスバッファをセット
//	device->SetIndices(indexBuffer);
//
//	effect->SetTechnique("mainTechnique");
//	//effect->SetMatrix("cancelRotation", &cancelRotation);
//	effect->SetMatrix("matrixProjection", &projection);
//	effect->SetMatrix("matrixView", &view);
//	effect->SetTexture("planeTexture", texture);
//	effect->Begin(0, 0);
//	effect->BeginPass(0);
//
//	//device->SetTexture(0, texture);
//	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
//	////device->SetTexture(0, NULL);
//	effect->EndPass();
//	effect->End();
//
//	//後始末
//	device->SetStreamSourceFreq(0, 1);
//	device->SetStreamSourceFreq(1, 1);
//	// αブレンドを切る
//	device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
//}
//
//
////=============================================================================
////  影管理クラス：初期化処理
////=============================================================================
//void ShadowManager::initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect)
//{
//	shadowMax = INITIAL_NUM_SHADOW;							// ゲーム開始時の影の数を設定
//	shadow = (Shadow**)malloc(sizeof(Shadow*) * shadowMax);	// ポインタ配列確保
//	if (shadow == NULL)
//	{
//		MessageBox(NULL, TEXT("メモリの確保に失敗しました。\nアプリケーションを終了します。"),
//			TEXT("SystemError"), MB_OK);
//		PostQuitMessage(0);
//	}
//	ZeroMemory(shadow, sizeof(Shadow*) * INITIAL_NUM_SHADOW);// 配列にnullをセットする
//	
//	numOfUse = 0;
//	renderList = NULL;
//
//	instancingProcedure.initialize(device, effect, *_textureLoader->getTexture(textureLoaderNS::UI_REVIVAL_GAUGE));
//}
//
//
//////=============================================================================
//////  影管理クラス：終了処理
//////=============================================================================
////void ShadowManager::uninitialize(void)
////{
////	for (int i = 0; i < shadowMax; i++)
////	{
////		if (shadow[i] != NULL) { SAFE_DELETE(shadow[i]) }
////	}
////	free(shadow);
////}
////
////
//////=============================================================================
//////  影管理クラス：更新処理
//////=============================================================================
////void ShadowManager::update(Sound* _sound, float frameTime)
////{
////	// 使用中の影の挙動を更新する
////	for (int i = 0; i < shadowMax; i++)
////	{
////		if (shadow[i] == NULL) { continue; }
////
////	}
////
////#if 1	// 影が一つも使われていないタイミング(=ポインタ配列が全てnull)で配列もリサイズする
////	if (numOfUse == 0 && shadowMax > INITIAL_NUM_SHADOW)
////	{
////		shadowMax = INITIAL_NUM_SHADOW;
////		Shadow** temp = (Shadow**)realloc(shadow, sizeof(Shadow*) * INITIAL_NUM_SHADOW);
////		if (temp == NULL)
////		{
////			MessageBox(NULL, TEXT("メモリの確保に失敗しました。\nアプリケーションを終了します。"),
////				TEXT("SystemError"), MB_OK);
////			PostQuitMessage(0);
////		}
////		shadow = temp;
////	}
////#endif
////}
////
////
//////=============================================================================
//////  影管理クラス：描画処理
//////=============================================================================
////void ShadowManager::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
////{
////	// 使用中の影をインスタンシング描画に流す
////	renderList = new D3DXVECTOR3[numOfUse];
////	int renderIndex = 0;
////	for (int i = 0; i < shadowMax; i++)
////	{
////		if (shadow[i] == NULL) { continue; }
////
////		renderList[renderIndex++] = *shadow[i]->getPosition();
////	}
////	instancingProcedure.setNumOfRender(device, numOfUse, renderList);
////	SAFE_DELETE_ARRAY(renderList)
////
////	instancingProcedure.render(device, view, projection, cameraPosition);
////}
////
////
//////=============================================================================
////// 影の移動を設定
//////=============================================================================
////D3DXVECTOR3 ShadowManager::moveSpeed(D3DXVECTOR3 position, D3DXVECTOR3 targetPosition)
////{
////	D3DXVECTOR3 speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
////	D3DXVECTOR3 moveDirection = targetPosition - position;
////	//float distance = D3DXVec3Length(&moveDirection);
////	//float magneticeForce = (target.amount*amount) / distance;
////	D3DXVec3Normalize(&moveDirection, &moveDirection);
////	speed += moveDirection * 2.0f;// このへんはまだ適当
////
////	return speed;
////}
//
//
//////=============================================================================
////// 影を発生させる
//////=============================================================================
////void ShadowManager::generateShadow(int num, D3DXVECTOR3 setPosition, Player* target)
////{
////	int newIndex = 0;	// 新規生成影インスタンスの数
////
////	for (int i = 0; i < shadowMax; i++)
////	{
////		if (newIndex == num) { break; }
////		if (shadow[i] != NULL) { continue; }
////
////		shadow[i] = new Shadow;
////		newIndex++;
////
////		// パラメータ設定
////		shadow[i]->setPosition(setPosition);
////		shadow[i]->setTarget(target);
////		shadow[i]->setSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
////		D3DXMatrixIdentity(shadow[i]->getMatrixWorld());
////		numOfUse++;
////
////		//----------------------------------------------------------------------------
////		// ポインタ配列の要素数を超えて影が確保された場合に配列自体を確保し直す
////		//----------------------------------------------------------------------------
////		static const int ADDITIONAL_NUM_SHADOW = 200;	// 追加要素数
////		if (i == shadowMax - 1 && newIndex == num)
////		{
////			shadowMax += ADDITIONAL_NUM_SHADOW;
////			Shadow** temp = (Shadow**)realloc(shadow, sizeof(Shadow*) * shadowMax);
////			if (temp == NULL)
////			{
////				MessageBox(NULL, TEXT("メモリの確保に失敗しました。\nアプリケーションを終了します。"),
////					TEXT("SystemError"), MB_OK);
////				PostQuitMessage(0);
////			}
////			shadow = temp;
////
////			// 新規確保分のメモリにnullをセットする
////			ZeroMemory(&shadow[i + 1], sizeof(Shadow*) * ADDITIONAL_NUM_SHADOW);
////		}
////	}
////}
//
//
////void ShadowManager::reverseAmount()
////{
////	amount *= -1.0f;
////}
//
