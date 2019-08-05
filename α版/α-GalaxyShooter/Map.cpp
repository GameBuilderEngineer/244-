//-----------------------------------------------------------------------------
// マップ処理 [Map.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/27
//-----------------------------------------------------------------------------
#include "Map.h"
using namespace MapNS;

#if 0	// マップノードのコリジョンを表示する場合は1
#define MAP_COLLISION_VIEW
#endif
#if 1	// マップノードのマークを表示する場合は1
#define MAP_MARK_VIEW
#endif 

//*****************************************************************************
// 静的メンバ
//*****************************************************************************
int MapNode::instanceCount = -1;
std::vector<MapNode*> Map::mapNode;
Planet* Map::field;// ●当座の措置



//=============================================================================
// 初期化処理
//=============================================================================
void Map::initialize(LPDIRECT3DDEVICE9 device, Planet* _field)
{
	field = _field;

	// D3DXCreateSphere(デバイス, 球の半径, スライス数, スタック数, メッシュ, 隣接性データ)
	// ノードのバウンディングスフィア用メッシュ
	D3DXCreateSphere(device, 28.0f, 9, 9, &sphere, NULL);
	// ノードの表示マーク用メッシュ
	D3DXCreateSphere(device, 1.0f, 5, 5, &mapCoodMark, NULL);

	// ノードの表示マーク用メッシュのマテリアル
	// ライトは切るのでDiffuse, Ambientは不透明だけでよい
	mapCoodMat.Diffuse = { 0.0f, 0.0f, 0.0f, 1.0f };
	mapCoodMat.Ambient = { 0.0f, 0.0f, 0.0f, 1.0f };
	mapCoodMat.Emissive = { 0.0f, 1.0f, 1.0f, 1.0f };
	targetCoodMat.Diffuse = { 0.0f, 0.0f, 0.0f, 1.0f };
	targetCoodMat.Ambient = { 0.0f, 0.0f, 0.0f, 1.0f };
	targetCoodMat.Emissive = { 1.0f, 0.0f, 0.0f, 1.0f };

	// フィールドの半径を測る
	ruler.start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	ruler.direction = D3DXVECTOR3(0.0f, 10000.0f, 0.0f);
	float radius = 0.0f;
	if (ruler.rayIntersect(*field->getMesh(), field->getMatrixWorld()))
	{
		radius = ruler.distance;
	}

	//---------------
	// ノードを配置
	//---------------
	// 北極点に配置
	ruler.direction = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Scale(&ruler.direction, &ruler.direction, ruler.distance);
	createNode(device);

	// レイを回転させながら一定の緯度経度ごとに配置
	D3DXMATRIX rotationMatrix;
	for (int i = 0; i < STACKS; i++)
	{
		ruler.direction = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVec3Scale(&ruler.direction, &ruler.direction, ruler.distance);

		// Z軸回転
		D3DXMatrixIdentity(&rotationMatrix);
		D3DXMatrixRotationZ(&rotationMatrix, (i + 1) * D3DX_PI / (float)STACKS);
		D3DXVec3TransformCoord(&ruler.direction, &ruler.direction, &rotationMatrix);

		for (int j = 0; j < SLICES; j++)
		{
			// Y軸回転
			D3DXMatrixIdentity(&rotationMatrix);
			D3DXMatrixRotationY(&rotationMatrix, j * 2.0f * D3DX_PI / (float)SLICES);
			D3DXVec3TransformCoord(&ruler.direction, &ruler.direction, &rotationMatrix);

			createNode(device);
		}
	}

	// 南極点に配置
	ruler.direction = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	D3DXVec3Scale(&ruler.direction, &ruler.direction, ruler.distance);
	createNode(device);


// ノードを均等に散らそうとしたができなかった残骸
//D3DXVECTOR2 tempVector(ruler.direction.x, ruler.direction.z);
//float tempRadius = D3DXVec2Length(&tempVector);
//float tempCircumference = tempRadius * 2.0f * D3DX_PI;
//float percentage = tempCircumference / circumference;
//int slices = (int)(SLICES * percentage + 0.9f);
//int slices;
//switch (i)
//{
//case 1:	slices = 6; break;
//case 2:	slices = 8; break;
//case 3:	slices = 10; break;
//case 4:	slices = 12; break;
//case 5:	slices = 10; break;
//case 6:	slices = 8; break;
//case 7:	slices = 6; break;
//}
}


//=============================================================================
// 終了処理
//=============================================================================
void Map::uninitialize(void)
{
	for (size_t i = 0; i < mapNode.size(); i++)
	{
		delete mapNode[i];
	}
	mapNode.clear();
}


//=============================================================================
// 描画処理
//=============================================================================
void Map::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
#ifdef _DEBUG

// コリジョンの描画
#ifdef MAP_COLLISION_VIEW
	for (size_t i = 0; i < mapNode.size(); i++)
	{
		mapNode[i]->boundingSphere.render(device, *mapNode[i]->getWorldMatrix());
	}
#endif// MAP_COLLISION_VIEW

// マークの描画
#ifdef MAP_MARK_VIEW

	D3DMATERIAL9 matDef;
	device->GetMaterial(&matDef);
	device->LightEnable(0, false);
	for (size_t i = 0; i < mapNode.size(); i++)
	{
		if (i == 5)
		{
			device->SetMaterial(&targetCoodMat);
		}
		else
		{
			device->SetMaterial(&mapCoodMat);
		}
		device->SetTransform(D3DTS_WORLD, mapNode[i]->getWorldMatrix());
		mapCoodMark->DrawSubset(0);
	}
	device->LightEnable(0, true);
	device->SetMaterial(&matDef);
#endif// MAP_MARK_VIEW

#endif// _DEBUG
}


//=============================================================================
// ノード生成
//=============================================================================
void Map::createNode(LPDIRECT3DDEVICE9 device)
{
	MapNode *newNode = new MapNode;
	newNode->setNumber(newNode->getInstanceCount());
	newNode->setPosition(ruler.direction);
	D3DXMatrixIdentity(newNode->getWorldMatrix());
	D3DXMatrixTranslation(newNode->getWorldMatrix(),
		newNode->getPosition().x, newNode->getPosition().y, newNode->getPosition().z);
	newNode->setWasuremonoCount(0);
	newNode->boundingSphere.initialize(device, &newNode->getPosition(), sphere);
	mapNode.emplace_back(newNode);
}