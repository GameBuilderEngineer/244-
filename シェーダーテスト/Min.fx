//�O���[�o��
float4x4 mWVP;//���[���h���r���[���v���W�F�N�V�����܂ł�3D�ϊ��s��

//�o�[�e�b�N�X�E�V�F�[�_
float4 VS(float4 f4Position : POSITION) : POSITION
{
	return mul(f4Position, mWVP);//3D�ϊ�
}

//�s�N�Z���E�V�F�[�_�[
float4 PS(float4 ScreenColor : COLOR) : COLOR
{
	//return float4(1,1,0,1);//���F�P�F
	return ScreenColor;//���F�P�F
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