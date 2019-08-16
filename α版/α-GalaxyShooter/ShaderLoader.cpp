//===================================================================================================================================
//�yShaderLoader.cpp�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/07/16
// [�X�V��]2019/08/07
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
}

ShaderLoader::~ShaderLoader()
{
	release();
}

void ShaderLoader::load(LPDIRECT3DDEVICE9 device)
{
	//�V�F�[�_�[��ǂݍ���
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
		{//�G�t�F�N�g�̉��
			effect[i]->Release();
			effect[i] = NULL;
		}
	}
}