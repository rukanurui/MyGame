#include "PostEffect.hlsli"

Texture2D<float4> tex0 : register(t0);//0番目に設定されたテクスチャ
Texture2D<float4> tex1 : register(t1);//1番目に設定されたテクスチャ
SamplerState smp : register(s0);//0番目に設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
	float2 samplePoint = input.uv;
	//samplePoint.x += 0.05;

	
	//湾曲
	/*samplePoint -= float2(0.5, 0.5);
	float distPower = pow(length(samplePoint), 0.15);
	samplePoint *= float2(distPower, distPower);
	samplePoint += float2(0.5, 0.5);*/
	//float4 Tex = tex0.Sample(smp, samplePoint);

	//モザイク
	float dest = 500;
	float4 Tex = tex0.Sample(smp, floor(samplePoint * dest) / dest);

	////走査線ノイズ
	//float sinv = sin(input.uv.y * 2 + time * -0.1);
	//float steped = step(0.99, sinv * sinv);
	//Tex.rgb -= (1 - steped) * abs(sin(input.uv.y * 50.0 + time * 1.0)) * 0.05;
	//Tex.rgb -= (1 - steped) * abs(sin(input.uv.y * 100.0 - time * 2.0)) * 0.08;
	//Tex.rgb += steped * 0.1;

	//rgbずらし
	samplePoint.x += 0.005;
	Tex.b = tex0.Sample(smp, samplePoint).b;

	//ビネット
	float vignette = length(float2(0.5, 0.5) - input.uv);
	vignette = clamp(vignette - 0.35, 0, 1);
	Tex.rgb -= vignette;
	
	float4 color = Tex;

	return float4(color.rgb,1.0f);
}



