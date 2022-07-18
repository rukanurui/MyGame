#include "FBX.hlsli"
//エントリーポイント

//スキニンぐ後の要点・法線が入る
struct SkinOutPut
{
	float4 pos;
	float3 normal;
};

//好き人ぐ敬さん
SkinOutPut ComputeSkin(VSInput input)
{
	//ゼロクリア
	SkinOutPut output = (SkinOutPut)0;

	uint iBone;//計算するボーン番号
	float weight;//ボーンウェイト(重み)
	matrix m;//スキニンぐ行列

	//ボーン0
	iBone = input.boneIndices.x;
	weight = input.boneWeights.x;
	m = matSkinning[iBone];
	output.pos += weight * mul(m, input.pos);
	output.normal += weight * mul((float3x3)m, input.normal);
	//ボーン1
	iBone = input.boneIndices.y;
	weight = input.boneWeights.y;
	m = matSkinning[iBone];
	output.pos += weight * mul(m, input.pos);
	output.normal += weight * mul((float3x3)m, input.normal);
	//ボーン2
	iBone = input.boneIndices.z;
	weight = input.boneWeights.z;
	m = matSkinning[iBone];
	output.pos += weight * mul(m, input.pos);
	output.normal += weight * mul((float3x3)m, input.normal);
	//ボーン3
	iBone = input.boneIndices.w;
	weight = input.boneWeights.w;
	m = matSkinning[iBone];
	output.pos += weight * mul(m, input.pos);
	output.normal += weight * mul((float3x3)m, input.normal);

	return output;
}

VSOutput main(VSInput input)
{
	//スキニンぐ計算
	SkinOutPut skinned = ComputeSkin(input);
	//法線にワールド行列によるスケーリング・回転を適用
	float4 wnormal = normalize(mul(world, float4(skinned.normal, 0)));
	//ピクセルシェーダーに戻す値
	VSOutput output;
	//行列による座標返還
	output.svpos = mul(mul(viewproj, world), skinned.pos);
	//ワールド法線を次のステージに渡す
	output.normal = wnormal.xyz;
	//入力値をそのまま次のステージに渡す
	output.uv = input.uv;

	return output;
}