//グローバル
float4x4 mWVP;//ワールド→ビュー→プロジェクションまでの3D変換行列

//バーテックス・シェーダ
float4 VS(float4 f4Position : POSITION) : POSITION
{
	return mul(f4Position, mWVP);//3D変換
}

//ピクセル・シェーダー
float4 PS(float4 ScreenColor : COLOR) : COLOR
{
	//return float4(1,1,0,1);//黄色単色
	return ScreenColor;//黄色単色
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