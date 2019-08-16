//===================================================================================================================================
//【VolumeLight.cpp】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/05/16
// [更新日]2019/08/06
//===================================================================================================================================
#include "VolumeLight.h"

VolumeLight::VolumeLight(LPDIRECT3DDEVICE9 _device, D3DPRESENT_PARAMETERS* _parameters)
{
	device = _device;
	parameters = _parameters;
	effect = NULL;
}

VolumeLight::~VolumeLight()
{
	//SafeReleaseは関数ではなくマクロ
	//#define SafeRelease(x) { if(x) { (x)->Release(); (x)=NULL; } }
	SAFE_RELEASE(effect);
}

void VolumeLight::invalidate()
{
	if (effect)
		effect->OnLostDevice();
}

void VolumeLight::restore()
{
	if (effect)
		effect->OnResetDevice();
}

HRESULT VolumeLight::load()
{
	D3DCAPS9 caps;
	HRESULT hr;

	device->GetDeviceCaps(&caps);
	if (caps.VertexShaderVersion >= D3DVS_VERSION(1, 1) && caps.PixelShaderVersion >= D3DPS_VERSION(2, 0))
	{
		hr = load();
		if (FAILED(hr))
			return -1;

		//シェーダーの初期化
		LPD3DXBUFFER pErr = NULL;
		hr = D3DXCreateEffectFromFile(device, "VolumeLight.fx", NULL, NULL, 0, NULL, &effect, &pErr);
		if (FAILED(hr))
			return -2;

		technique = effect->GetTechniqueByName("main");
		WVP = effect->GetParameterByName(NULL, "WVP");
		color = effect->GetParameterByName(NULL, "color");
		farZ = effect->GetParameterByName(NULL, "farZ");

		effect->SetTechnique(technique);
	}

	else
	{
		return -3;
	}

	return S_OK;

}

//****************************************************************
//ボリュームライトの手前面のＺ値を取得
//****************************************************************
void VolumeLight::step1Begin()
{
	if (effect)
	{
		device->GetTransform(D3DTS_VIEW, &matrixView);
		device->GetTransform(D3DTS_PROJECTION, &matrixProjection);

		effect->Begin(NULL, 0);
	}
}

void VolumeLight::step1BeginPass()
{
	if (effect)
	{
		effect->BeginPass(0);
	}
}

void VolumeLight::step1SetMatrix(D3DXMATRIX* _materialWorld, float _farZ)
{
	if (effect)
	{
		D3DXMATRIX m;

		//ワールド × ビュー 遠近射影行列
		m = (*_materialWorld) * matrixView * matrixProjection;
		effect->SetMatrix(WVP, &m);

		//遠近射影行列の最遠近距離を設定
		effect->SetFloat(farZ, _farZ);
	}

	else
		device->SetTransform(D3DTS_WORLD, _materialWorld);
}

void VolumeLight::step1EndPass()
{
	if (effect)
	{
		effect->EndPass();
	}
}

void VolumeLight::step1End()
{
	if (effect)
	{
		effect->End();
	}
}

//****************************************************************
//ボリュームライトの奥面のＺ値を取得
//****************************************************************
void VolumeLight::step2Begin()
{
	if (effect)
	{
		//新しいピクセル値が、現在のピクセル値より大きいときにＺバッファに書きこむ。
		device->SetRenderState(D3DRS_ZFUNC, D3DCMP_GREATER);

		//背面を右回りでカリングする。奥面をレンダリングする。
		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

		effect->Begin(NULL, 0);
	}
}

void VolumeLight::step2BeginPass()
{
	if (effect)
	{
		effect->BeginPass(0);
	}
}

void VolumeLight::step2SetMatrix(D3DXMATRIX* _matrixWorld, float _farZ)
{
	if (effect)
	{
		D3DXMATRIX m;

		//ワールド × ビュー 遠近射影行列
		m = (*_matrixWorld) * matrixView * matrixProjection;
		effect->SetMatrix(WVP, &m);

		//遠近射影行列の最遠近距離を設定
		effect->SetFloat(farZ, _farZ);
	}

	else
		device->SetTransform(D3DTS_WORLD, _matrixWorld);
}

void VolumeLight::step2EndPass()
{
	if (effect)
	{
		effect->EndPass();
	}
}

void VolumeLight::step2End()
{
	if (effect)
	{
		effect->End();

		//新しいピクセル値が、現在のピクセル値より小さいときにＺバッファに書き込む。
		device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

		//背面を左回りでカリングする。手前面をレンダリングする。
		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	}
}

//****************************************************************
//ボリュームライトの厚みを計算し、シーンのカラー情報と合成
//****************************************************************
void VolumeLight::step3Render(D3DXVECTOR4* _color)
{
	if (effect)
	{
		D3DXVECTOR4 Color;

		if (_color == NULL)
			Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		else
			CopyMemory(&Color, _color, sizeof(D3DXVECTOR4));

		//ボリュームライトの色を設定する
		effect->SetVector(color, &Color);

		effect->Begin(NULL, 0);
		effect->BeginPass(1);

		//D3D2DSQUARE::Render();

		effect->EndPass();
		effect->End();
	}
}

void VolumeLight::commitChanges()
{
	if (effect)
		effect->CommitChanges();
}

BOOL VolumeLight::isOK()
{
	if (effect)
		return TRUE;

	return FALSE;
}