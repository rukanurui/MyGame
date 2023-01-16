#include "PostEffect.hlsli"

Texture2D<float4> tex0 : register(t0);//0�Ԗڂɐݒ肳�ꂽ�e�N�X�`��
Texture2D<float4> tex1 : register(t1);//1�Ԗڂɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);//0�Ԗڂɐݒ肳�ꂽ�T���v���[

float4 main(VSOutput input) : SV_TARGET
{
	float2 samplePoint = input.uv;
	samplePoint.x += 0.05;

	//�c��
	samplePoint -= float2(0.5, 0.5);
	float distPower = pow(length(samplePoint), 1);
	samplePoint *= float2(distPower, distPower);
	samplePoint += float2(0.5, 0.5);
	float4 Tex = tex0.Sample(smp, samplePoint);

	/*float4 colortex0 = tex0.Sample(smp, input.uv);
	float4 colortex1 = tex1.Sample(smp, input.uv);
	float4 color = colortex0;
	return float4(color.rgb, 1);*/

	return Tex;
}

