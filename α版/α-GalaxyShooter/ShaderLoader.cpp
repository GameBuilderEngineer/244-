//===================================================================================================================================
//【ShaderLoader.cpp】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/07/16
// [更新日]2019/09/03
//===================================================================================================================================
#include "ShaderLoader.h"
using namespace shaderNS;


ShaderLoader::ShaderLoader()
{
	shaderName[TOON] = { "ToonShader.fx" };
	shaderName[INSTANCE_BILLBOARD] = { "InstancingBillboard.fx" };
	shaderName[INSTANCE_STATIC_MESH] = { "InstancingStaticMesh.fx" };
	shaderName[RECURSION] = { "Recursion.fx" };
	shaderName[SHOCK_WAVE] = { "ShockWave.fx" };
	shaderName[LAMBERT] = { "Lambert.fx" };
}

ShaderLoader::~ShaderLoader()
{
	release();
}

void ShaderLoader::load(LPDIRECT3DDEVICE9 device)
{
	//シェーダーを読み込む
	setShaderDirectory();
	HRESULT hr;
	LPD3DXBUFFER err = NULL;
	for (int i = 0; i < MAX_SHADER; i++)
	{
		if (FAILED(hr = D3DXCreateEffectFromFile(device, shaderName[i], NULL, NULL, 0, NULL, &effect[i], &err)))
		{
			MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), shaderName[i], MB_OK);
		}
	}
}

void ShaderLoader::release()
{
	for (int i = 0; i < MAX_SHADER; i++)
	{
		if (effect[i] != NULL)
		{//エフェクトの解放
			effect[i]->Release();
			effect[i] = NULL;
		}
	}
}