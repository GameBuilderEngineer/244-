//�O���[�o��
float4x4 mWV;//���[���h���r���[���v���W�F�N�V�����܂ł�3D�ϊ��s��

//�o�[�e�b�N�X�E�V�F�[�_
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
	return mul(outPos,mWV);//3D�ϊ�
}

//�s�N�Z���E�V�F�[�_�[
float4 PS(float4 ScreenColor : COLOR) : COLOR
{
	return float4(0.4,1.0,0.7,1);//���F�P�F
	//return ScreenColor;
}

//�e�N�j�b�N
technique tecMinimum
{
	pass P0
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}
}