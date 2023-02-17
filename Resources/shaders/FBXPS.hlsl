#include"FBX.hlsli"

//0番スロットに設定されたテクスチャ
Texture2D<float4> tex : register(t0);
//0番スロットに追加されたサンプラー
SamplerState smp : register(s0);

struct PSOutput
{
	float4 target0 : SV_TARGET0;
	float4 target1 : SV_TARGET1;
};


//エントリーポイント
PSOutput main(VSOutput input)
{
	PSOutput output;
	//テクスチャマッピング
	float4 texcolor = tex.Sample(smp, input.uv);

	//Lambert反射
	float3 Light = normalize(float3(1, -1, 1));//右下奥向きのライト
	//phong反射
	float4 ambient = texcolor * 0.2;//アンビエント
	float3 eyeDir = normalize(camerapos.xyz - input.normal);//視線ベクトル
	float3 halfvec = normalize(Light + eyeDir);//ハーフベクトル
	float intensity =
		saturate(dot(normalize(input.normal), halfvec));
	float millar = pow(intensity, 30);
	float4 specularColor = float4(1, 1, 1, 1);
	float specular = specularColor * millar;
	float diffuse = saturate(dot(-Light, input.normal));
	float brightness = diffuse + 0.3f;
	//float brightness = ambient + diffuse + specular;
	//float4 shadecolor = float4(brightness, brightness, brightness, 1.0f);
	float4 phong = float4(brightness, brightness, brightness, 1.0f);
	//float4 shadecolor = float4(1,0,0,1.0f);//単色で塗りつぶす
	//陰影とテクスチャの色を合成
	//output.target0 = shadecolor * texcolor;
	//output.target1 = shadecolor * texcolor;
	output.target0 = phong * texcolor;
	output.target1 = float4((phong * texcolor).rgb, 1);
	return output;
}