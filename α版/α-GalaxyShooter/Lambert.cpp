#include "Lambert.h"

Lambert::Lambert(LPDIRECT3DDEVICE9 _device)
{
	device = _device;
	effect = NULL;
}

Lambert::~Lambert()
{
	SAFE_RELEASE(effect);
}

void Lambert::invalidate()
{
	if (effect)
	{
		effect->OnLostDevice();
	}
}

void Lambert::restore()
{
	if (effect)
	{
		effect->OnResetDevice();
	}
}

HRESULT Lambert::load()
{
	D3DCAPS9 caps;
	device->GetDeviceCaps(&caps);
	LPD3DXBUFFER err = NULL;
	HRESULT hr = D3DXCreateEffectFromFile(device, "Lambert.fx", NULL, NULL, 0, NULL, &effect, &err);

	technique		= effect->GetTechniqueByName("main");
	WVP				= effect->GetParameterByName(NULL, "matrixWVP");
	lightDirection	= effect->GetParameterByName(NULL, "lightDirection");
	ambient			= effect->GetParameterByName(NULL,"ambient");
	farZ			= effect->GetParameterByName(NULL,"farZ");

	effect->SetTechnique(technique);
	return S_OK;
}

void Lambert::begin()
{
	if (!effect)return;
	device->GetTransform(D3DTS_VIEW, &matrixView);
	device->GetTransform(D3DTS_PROJECTION, &matrixProjection);
	effect->Begin(NULL,0);
}

void Lambert::beginPass()
{
	if (!effect)return;
	effect->BeginPass(0);
}

void Lambert::setAmbient(float _ambient)
{
	if (effect) 
	{
		D3DXVECTOR4 A;
		A = D3DXVECTOR4(_ambient, _ambient, _ambient, 1.0f);
		effect->SetVector(ambient, &A);
	}
	else
	{
		D3DMATERIAL9 oldMaterial;
		device->GetMaterial(&oldMaterial);
		oldMaterial.Ambient.r = _ambient;
		oldMaterial.Ambient.g = _ambient;
		oldMaterial.Ambient.b = _ambient;
		oldMaterial.Ambient.a = 1.0f;
		device->SetMaterial(&oldMaterial);
	}
}

void Lambert::setAmbient(D3DXVECTOR4* _ambient)
{
	if (effect)
	{
		effect->SetVector(ambient, _ambient);
	}
	else
	{
		D3DMATERIAL9 oldMaterial;
		oldMaterial.Ambient.r = _ambient->x;
		oldMaterial.Ambient.g = _ambient->y;
		oldMaterial.Ambient.b = _ambient->z;
		oldMaterial.Ambient.a = _ambient->w;
		device->SetMaterial(&oldMaterial);
	}
}

void Lambert::setMatrix(D3DXMATRIX* matrixWorld, D3DXVECTOR4* _lightDir, float _farZ)
{
	if (effect)
	{
		D3DXMATRIX m, m1;
		D3DXVECTOR4 lightDir;
		D3DXVECTOR4 v;
		//�ˉe�s��ɍ�����W�n���ߎˉe�s����g�p����
		m = (*matrixWorld)*matrixView * matrixProjection;
		effect->SetMatrix(WVP, &m);

		//Light
		lightDir = *_lightDir;
		D3DXMatrixInverse(&m1, NULL, matrixWorld);
		D3DXVec4Transform(&v, &lightDir, &m1);
		D3DXVec4Normalize(&v, &v);
		effect->SetVector(lightDirection, &v);

		//���ߎˉe�s��̍ŉ��ߋ������Z�b�g
		effect->SetFloat(farZ, _farZ);
	}
	else
	{
		device->SetTransform(D3DTS_WORLD, matrixWorld);
	}
}

void Lambert::commitChanges()
{
	if (effect)
		effect->CommitChanges();
}

void Lambert::endPass()
{
	if (effect)
		effect->EndPass();
}

void Lambert::end()
{
	if (effect)
		effect->End();
}

BOOL Lambert::isOK()
{
	if (effect)
	{
		return TRUE;
	}
	return FALSE;
}