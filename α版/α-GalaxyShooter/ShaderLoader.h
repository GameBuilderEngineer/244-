//===================================================================================================================================
//【ShaderLoader.h】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/07/16
// [更新日]2019/08/07
//===================================================================================================================================
#pragma once
#include "Base.h"

namespace shaderNS
{
	enum SHADER_NUMBER {
		TOON,
		INSTANCE_BILLBOARD,
		INSTANCE_STATIC_MESH,
		RECURSION,
		SHOCK_WAVE,
		LAMBERT,
		MAX_SHADER,
	};
}

class ShaderLoader :public Base
{
private:
	const char* shaderName[shaderNS::MAX_SHADER];
	LPD3DXEFFECT effect[shaderNS::MAX_SHADER];
public:
	ShaderLoader();
	~ShaderLoader();
	void load(LPDIRECT3DDEVICE9 device);
	void release();

	LPD3DXEFFECT* getEffect(int shaderNo) { return &effect[shaderNo]; }
};

