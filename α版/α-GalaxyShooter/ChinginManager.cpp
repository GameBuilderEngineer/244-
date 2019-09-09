//-----------------------------------------------------------------------------
// チンギン処理 [Chingin.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/8/1
//-----------------------------------------------------------------------------
#include "ChinginManager.h"

//=============================================================================
// 初期化処理
//=============================================================================
void ChinginManager::initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect)
{
	D3DXCreateSphere(device, 3.0f, 9, 9, &sphere, NULL);		// 当たり判定用にスフィアを作る
	chinginMax = INITIAL_NUM_CHINGIN;							// 初期チンギン数を設定
	chingin = (Chingin**)malloc(sizeof(Chingin*) * chinginMax);	// ポインタ配列確保
	if (chingin == NULL)
	{
		MessageBox(NULL, TEXT("メモリの確保に失敗しました。\nアプリケーションを終了します。"),
			TEXT("SystemError"), MB_OK);
		PostQuitMessage(0);
	}
	ZeroMemory(chingin, sizeof(Chingin*) * INITIAL_NUM_CHINGIN);// 配列にnullをセットする
	
	numOfUse = 0;
	renderList = NULL;

	// 賃金エフェクト初期化
	chinginEffect.initialize(device, _textureLoader, effect);

	instancingProcedure.initialize(device, effect, *_textureLoader->getTexture(textureLoaderNS::UI_REVIVAL_GAUGE));
}

//=============================================================================
// 終了処理
//=============================================================================
void ChinginManager::uninitialize(void)
{
	for (int i = 0; i < chinginMax; i++)
	{
		if (chingin[i] != NULL) { SAFE_DELETE(chingin[i]) }
	}
	free(chingin);
}


//=============================================================================
// 更新処理
//=============================================================================
void ChinginManager::update(Sound* _sound, float frameTime)
{
	// 賃金エフェクトの更新
	chinginEffect.update(frameTime);

	// 使用中のチンギンの挙動を更新する
	for (int i = 0; i < chinginMax; i++)
	{
		if (chingin[i] == NULL) { continue; }

		chingin[i]->setSpeed(moveSpeed(*chingin[i]->getPosition(), *chingin[i]->getTarget()->getPosition()));
		chingin[i]->setPosition(*chingin[i]->getPosition() + *chingin[i]->getSpeed());

		D3DXMatrixIdentity(chingin[i]->getMatrixWorld());
		D3DXMatrixTranslation(chingin[i]->getMatrixWorld(),
			chingin[i]->getPosition()->x, chingin[i]->getPosition()->y, chingin[i]->getPosition()->z);

		// プレイヤーに当たったらメモリ解放
		if (chingin[i]->getCollider()->collide(
			chingin[i]->getTarget()->bodyCollide.getCenter(), chingin[i]->getTarget()->bodyCollide.getRadius(),
			*chingin[i]->getMatrixWorld(), *chingin[i]->getTarget()->getMatrixWorld()))
		{

			// 賃金エフェクト発生
			chinginEffect.generateChinginEffect(1, *chingin[i]->getTarget()->getPosition(), chingin[i]->getTarget()->upVec());

			// サウンドの再生
			_sound->play(soundNS::TYPE::SE_CHINGIN, soundNS::METHOD::PLAY);

			SAFE_DELETE(chingin[i])
			numOfUse--;
		}
	}

#if 1	// チンギンが一つも使われていないタイミング(=ポインタ配列が全てnull)で配列もリサイズする
	if (numOfUse == 0 && chinginMax > INITIAL_NUM_CHINGIN)
	{
		chinginMax = INITIAL_NUM_CHINGIN;
		Chingin** temp = (Chingin**)realloc(chingin, sizeof(Chingin*) * INITIAL_NUM_CHINGIN);
		if (temp == NULL)
		{
			MessageBox(NULL, TEXT("メモリの確保に失敗しました。\nアプリケーションを終了します。"),
				TEXT("SystemError"), MB_OK);
			PostQuitMessage(0);
		}
		chingin = temp;
	}
#endif
}


//=============================================================================
// 描画処理
//=============================================================================
void ChinginManager::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	// 使用中のチンギンをインスタンシング描画に流す
	renderList = new D3DXVECTOR3[numOfUse];
	int renderIndex = 0;
	for (int i = 0; i < chinginMax; i++)
	{
		if (chingin[i] == NULL) { continue; }

		renderList[renderIndex++] = *chingin[i]->getPosition();
	}
	instancingProcedure.setNumOfRender(device, numOfUse, renderList);
	SAFE_DELETE_ARRAY(renderList)

	instancingProcedure.render(device, view, projection, cameraPosition);

	// 賃金エフェクトの描画
	chinginEffect.render(device, view, projection, cameraPosition);

}


//=============================================================================
// チンギンの移動を設定
//=============================================================================
D3DXVECTOR3 ChinginManager::moveSpeed(D3DXVECTOR3 position, D3DXVECTOR3 targetPosition)
{
	D3DXVECTOR3 speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 moveDirection = targetPosition - position;
	//float distance = D3DXVec3Length(&moveDirection);
	//float magneticeForce = (target.amount*amount) / distance;
	D3DXVec3Normalize(&moveDirection, &moveDirection);
	speed += moveDirection * 2.0f;// このへんはまだ適当

	return speed;
}


//=============================================================================
// チンギンを発生させる
//=============================================================================
void ChinginManager::generateChingin(int num, D3DXVECTOR3 setPosition, Player* target)
{
	int newIndex = 0;	// 新規生成チンギンインスタンスの数

	for (int i = 0; i < chinginMax; i++)
	{
		if (newIndex == num) { break; }
		if (chingin[i] != NULL) { continue; }

		chingin[i] = new Chingin;
		newIndex++;

		// パラメータ設定
		chingin[i]->setPosition(setPosition);
		chingin[i]->setTarget(target);
		chingin[i]->setSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		D3DXMatrixIdentity(chingin[i]->getMatrixWorld());
		numOfUse++;

		//----------------------------------------------------------------------------
		// ポインタ配列の要素数を超えてチンギンが確保された場合に配列自体を確保し直す
		//----------------------------------------------------------------------------
		static const int ADDITIONAL_NUM_CHINGIN = 200;	// 追加要素数
		if (i == chinginMax - 1 && newIndex == num)
		{
			chinginMax += ADDITIONAL_NUM_CHINGIN;
			Chingin** temp = (Chingin**)realloc(chingin, sizeof(Chingin*) * chinginMax);
			if (temp == NULL)
			{
				MessageBox(NULL, TEXT("メモリの確保に失敗しました。\nアプリケーションを終了します。"),
					TEXT("SystemError"), MB_OK);
				PostQuitMessage(0);
			}
			chingin = temp;

			// 新規確保分のメモリにnullをセットする
			ZeroMemory(&chingin[i + 1], sizeof(Chingin*) * ADDITIONAL_NUM_CHINGIN);
		}
	}
}


//void ChinginManager::reverseAmount()
//{
//	amount *= -1.0f;
//}

