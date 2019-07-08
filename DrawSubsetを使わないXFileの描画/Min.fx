//グローバル
float4x4 mWV;//ワールド→ビュー→プロジェクションまでの3D変換行列

//バーテックス・シェーダ
float4 VS(
	float3 position : POSITION,
	float3 worldPos : TEXCOORD1
) : POSITION
{
	float4 outPos;
	outPos = float4(
		position.x + worldPos.x,
		position.y + worldPos.y,
		position.z + worldPos.z,
		1.0f);
	return mul(outPos,mWV);//3D変換
}

//ピクセル・シェーダー
float4 PS(float4 ScreenColor : COLOR) : COLOR
{
	return float4(0.4,1.0,0.7,1);//黄色単色
	//return ScreenColor;
}

//テクニック
technique tecMinimum
{
	pass P0
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}
}