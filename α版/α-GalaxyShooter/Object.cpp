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

HRESULT Object::initialize(LPDIRECT3DDEVICE9 device, LPSTR xFileName, D3DXVECTOR3* _position)
{
	// メッシュの初期位置
	memcpy(position, _position, sizeof(D3DXVECTOR3));
	// Xファイルからメッシュをロードする	
	LPD3DXBUFFER materialBuffer = NULL;
	setVisualDirectory();
	if (FAILED(D3DXLoadMeshFromX(xFileName, D3DXMESH_SYSTEMMEM,
		device, NULL, &materialBuffer, NULL,
		&numMaterials, &mesh)))
	{
		MessageBox(NULL, "Xファイルの読み込みに失敗しました", xFileName, MB_OK);
		return E_FAIL;
	}
	D3DXMATERIAL* materials = (D3DXMATERIAL*)materialBuffer->GetBufferPointer();
	meshMaterials = new D3DMATERIAL9[numMaterials];
	meshTextures = new LPDIRECT3DTEXTURE9[numMaterials];

	for (DWORD i = 0; i < numMaterials; i++)
	{
		meshMaterials[i] = materials[i].MatD3D;
		meshMaterials[i].Ambient = meshMaterials[i].Diffuse;
		meshTextures[i] = NULL;
		if (materials[i].pTextureFilename != NULL &&
			lstrlen(materials[i].pTextureFilename) > 0)
		{
			if (FAILED(D3DXCreateTextureFromFile(device,
				materials[i].pTextureFilename,
				&meshTextures[i])))
			{
				MessageBox(NULL, "テクスチャの読み込みに失敗しました", NULL, MB_OK);
			}
		}
	}
	MFAIL(D3DXCreateTextureFromFile(device, "Shade.bmp", &textureShade), "Shade.bmpの読み込みに失敗しました");
	MFAIL(D3DXCreateTextureFromFile(device, "Outline.bmp", &textureLine), "Outline.bmpの読み込みに失敗しました");
	materialBuffer->Release();
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
	// レンダリング			
	for (DWORD i = 0; i < numMaterials; i++)
	{
		device->SetMaterial(&meshMaterials[i]);
		device->SetTexture(0, meshTextures[i]);
		mesh->DrawSubset(i);
	}

	// マテリアルをデフォルトに戻す
	device->SetMaterial(&matDef);
	// テクスチャの設定をNULLにする
	device->SetTexture(0, NULL);

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
	for (DWORD i = 0; i < numMaterials; i++)
	{
		effect->BeginPass(0);
		effect->SetFloatArray("Diffuse", (FLOAT*)&meshMaterials[i].Diffuse, 4);
		//effect->SetTexture("DecalTexture", meshTextures[i]);
		//device->SetMaterial(&meshMaterials[i]);
		//device->SetTexture(0, meshTextures[i]);
		mesh->DrawSubset(i);
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
