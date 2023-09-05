#include "Particle.hlsli"

VSOutput main(float4 pos : POSITION, float scale : TEXCOORD,float roatation : ROATATION)
{
	VSOutput output; // ピクセルシェーダーに渡す値
	output.pos = pos;
	output.scale = scale;
	output.roatation = roatation;
	return output;
}