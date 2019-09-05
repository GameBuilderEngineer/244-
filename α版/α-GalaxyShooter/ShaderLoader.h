//===================================================================================================================================
//ÅyShaderLoader.hÅz
// [çÏê¨é“]HALìåãûGP12A332 11 êõñÏ é˜
// [çÏê¨ì˙]2019/07/16
// [çXêVì˙]2019/08/07
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

