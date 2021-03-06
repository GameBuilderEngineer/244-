//===================================================================================================================================
//yUtiltyFunction.hz
// [์ฌา]HALGP12A332 11 ์ ๗
// [์ฌ๚]2019/08/07
// [XV๚]2019/08/07
//===================================================================================================================================
#pragma once
#include <stdio.h>
#include <crtdbg.h>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <assert.h>
#include <cmath>
#include <iostream>
//KvศCut@Cฬ[h
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
//x๑\ฆ
#pragma warning(disable:4305)
#pragma warning(disable:4996)
#pragma warning(disable:4018)
#pragma warning(disable:4111)

namespace utility
{
	struct Polar3D
	{
		float radius;	//ฎa			[่`ๆ] 0<= raduys <= 
		float theta;	//ษp(Vธp)  [่`ๆ] 0<= theta  <= ฮ
		float phi;		//๛สp(ฮp)  [่`ๆ] 0<= phi    <  2ฮ
	};
}

class UtilityFunction
{
public:
	UtilityFunction();
	~UtilityFunction();

	static int wrap(int x, int low, int high);
	static float wrap(float x, float low, float high);
	template<typename T>
	static T clamp(T x, T low, T high);

	//yฯทzษภW->ผ๐ภW
	//Polar Coordinates Transformation
	static D3DXVECTOR3 fromTransformationPolar3D(float radius, float theta, float phi);
	//yฯทzผ๐ภW->ษภW
	static utility::Polar3D fromRectangular3D(D3DXVECTOR3 coordinate);
	//1โิึ
	static float lerp(float start, float end, float time);
};