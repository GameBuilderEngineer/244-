#include "Object.h"
#include "Base.h"
Object::Object()
{
	ZeroMemory(this, sizeof(Object));
	D3DXMatrixIdentity(&matrixRotation);
	quaternion = D3DXQUATERNION(0, 0, 0, 1);
	axisX.initialize(D3DXVECTOR3(0, 0, 0),D3DXVECTOR3(1, 0, 0));
	axisY.initialize(D3DXVECTOR3(0, 0, 0),D3DXVECTOR3(0, 1, 0));
	axisZ.initialize(D3DXVECTOR3(0, 0, 0),D3DXVECTOR3(0, 0, 1));
	reverseAxisX.initialize(D3DXVECTOR3(0, 0, 0),D3DXVECTOR3(-1, 0, 0));
	reverseAxisY.initialize(D3DXVECTOR3(0, 0, 0),D3DXVECTOR3(0, -1, 0));
	reverseAxisZ.initialize(D3DXVECTOR3(0, 0, 0),D3DXVECTOR3(0, 0, -1));
#ifdef _DEBUG
	axisX.color = D3DXCOLOR(255, 0, 0, 255);
	axisY.color = D3DXCOLOR(0, 255, 0, 255);
	axisZ.color = D3DXCOLOR(0, 0, 255, 255);
	reverseAxisX.color = D3DXCOLOR(255, 0, 0, 255);
	reverseAxisY.color = D3DXCOLOR(0, 255, 0, 255);
	reverseAxisZ.color = D3DXCOLOR(0, 0, 255, 255);
#endif // _DEBUG
}

Object::~Object()
{
	
}

HRESULT Object::initialize(LPDIRECT3DDEVICE9 device, StaticMesh* _staticMesh, D3DXVECTOR3* _position)
{
	//読込クラスからポインタをもらう
	staticMesh = _staticMesh;
	// メッシュの初期位置
	memcpy(position, _position, sizeof(D3DXVECTOR3));

	setVisualDirectory();
	MFAIL(D3DXCreateTextureFromFile(device, "Shade.bmp", &textureShade), "Shade.bmpの読み込みに失敗しました");
	MFAIL(D3DXCreateTextureFromFile(device, "Outline.bmp", &textureLine), "Outline.bmpの読み込みに失敗しました");
	//シェーダーを読み込む
	setShaderDirectory();
	MFAIL(D3DXCreateEffectFromFile(device, "ToonShader.fx", NULL, NULL, 0, NULL, &effect, NULL), "シェーダーファイル読み込み失敗");
	
	update();

	return S_OK;
}

void Object::update()
{
	if (onActive == false)return;
	//ワールドトランスフォーム（ローカル座標→ワールド座標への変換）	
	D3DXMatrixTranslation(&matrixPosition, position.x, position.y, position.z);

	//クォータニオンを回転量パラメーターに使用する
	D3DXMatrixRotationQuaternion(&matrixRotation, &quaternion);
	D3DXMatrixMultiply(&matrixWorld, &matrixRotation, &matrixPosition);
	//ワールド座標から自身の軸レイを更新する

	axisX.update(position, D3DXVECTOR3(matrixWorld._11,matrixWorld._12,matrixWorld._13));
	axisY.update(position, D3DXVECTOR3(matrixWorld._21,matrixWorld._22,matrixWorld._23));
	axisZ.update(position, D3DXVECTOR3(matrixWorld._31,matrixWorld._32,matrixWorld._33));
	reverseAxisX.update(position, -D3DXVECTOR3(matrixWorld._11, matrixWorld._12, matrixWorld._13));
	reverseAxisY.update(position, -D3DXVECTOR3(matrixWorld._21, matrixWorld._22, matrixWorld._23));
	reverseAxisZ.update(position, -D3DXVECTOR3(matrixWorld._31, matrixWorld._32, matrixWorld._33));
}


VOID Object::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	if (onRender == false)return;
	device->SetTransform(D3DTS_WORLD, &matrixWorld);
	device->SetRenderState(D3DRS_LIGHTING, true);

	D3DMATERIAL9 matDef;
	device->GetMaterial(&matDef);

	//インスタンス宣言
	//device->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | 1);
	//device->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	//頂点宣言を追加
	//device->SetVertexDeclaration(staticMesh->declaration);
	//device->SetFVF(staticMesh->mesh->GetFVF());
	//ストリームにメッシュの頂点バッファをバインド
	//device->SetStreamSource(0, staticMesh->vertexBuffer, 0, sizeof(staticMesh->numBytesPerVertex));

	//インデックスバッファをセット
	//device->SetIndices(staticMesh->indexBuffer);

	// レンダリング			
	for (DWORD i = 0; i < staticMesh->attributeTableSize; i++)
	{
		device->SetMaterial(&staticMesh->materials[i]);
		device->SetTexture(0,staticMesh->textures[i]);
		

		//device->DrawIndexedPrimitive(
		//	D3DPT_TRIANGLELIST,									//D3DPRIMITIVETYPE Type
		//	0,													//INT BaseVertexIndex
		//	staticMesh->attributeTable[i].VertexStart,			//UINT MinIndex
		//	staticMesh->attributeTable[i].VertexCount,			//UINT NumVertices
		//	staticMesh->attributeTable[i].FaceStart * 3,		//UINT StartIndex
		//	staticMesh->attributeTable[i].FaceCount);			//UINT PrimitiveCount
		staticMesh->mesh->DrawSubset(i);
	}

	// マテリアルをデフォルトに戻す
	device->SetMaterial(&matDef);
	// テクスチャの設定をNULLにする
	device->SetTexture(0, NULL);

	//後始末
	//device->SetStreamSourceFreq(0, 1);
	//device->SetStreamSourceFreq(1, 1);


#ifdef _DEBUG
	axisX.render(device, 10.0f);
	axisY.render(device, 10.0f);
	axisZ.render(device, 10.0f);
	reverseAxisX.render(device, 10.0f);
	reverseAxisY.render(device, 10.0f);
	reverseAxisZ.render(device, 10.0f);
#endif // _DEBUG
}

VOID Object::toonRender(LPDIRECT3DDEVICE9 device,D3DXMATRIX view,D3DXMATRIX projection,D3DXVECTOR3 cameraPositon)
{
	device->SetTransform(D3DTS_WORLD, &matrixWorld);

	effect->SetTechnique("ToonShading");
	effect->SetMatrix("mProj", &projection);
	effect->SetMatrix("mView", &view);
	effect->SetMatrix("mWorld", &matrixWorld);
	effect->SetTexture("ShadeTexture", textureShade);
	effect->SetTexture("LineTexture", textureLine);

	effect->SetVector("LightPos", &D3DXVECTOR4(0, 0, 5, 1));
	effect->SetVector("EyePos", (D3DXVECTOR4*)&cameraPositon);
	effect->Begin(NULL, 0);

	// レンダリング			
	for (DWORD i = 0; i <staticMesh->numMaterial; i++)
	{
		effect->BeginPass(0);
		effect->SetFloatArray("Diffuse", (FLOAT*)&staticMesh->materials[i].Diffuse, 4);
		//effect->SetTexture("DecalTexture", meshTextures[i]);
		//device->SetMaterial(&meshMaterials[i]);
		//device->SetTexture(0, meshTextures[i]);
		staticMesh->mesh->DrawSubset(i);
		effect->EndPass();
	}
	effect->End();

#ifdef _DEBUG
	axisX.render(device, 10.0f);
	axisY.render(device, 10.0f);
	axisZ.render(device, 10.0f);
	reverseAxisX.render(device, 10.0f);
	reverseAxisY.render(device, 10.0f);
	reverseAxisZ.render(device, 10.0f);
#endif // _DEBUG

}

void Object::setGravity(D3DXVECTOR3 source, float power)
{
	D3DXVec3Normalize(&gravity, &source);
	//gravity *= min(power, reverseAxisY.distance);
	gravity *= power;
	
	if (onGravity)speed += gravity;
}

void Object::activation()
{
	onRender = true;
	onActive = true;
}
void Object::inActivation()
{
	onRender = false;
	onActive = false;
}
