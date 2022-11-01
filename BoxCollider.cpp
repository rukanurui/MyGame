#include"BoxCollider.h"

using namespace DirectX;

void BoxCollider::Update()
{
	//ワールド行列から座標を抽出
	const XMMATRIX& matWorld = fbxobject->GetMatWorld();

	//球のメンバ変数を更新
	Box::center = matWorld.r[3] + offset;
	
	Box::radius = radius;

	Box::minpos.m128_f32[0] = center.m128_f32[0] - radius;
	Box::minpos.m128_f32[1] = center.m128_f32[1] - radius;
	Box::minpos.m128_f32[2] = center.m128_f32[2] - radius;

	Box::maxpos.m128_f32[0] = center.m128_f32[0] + radius;
	Box::maxpos.m128_f32[1] = center.m128_f32[1] + radius;
	Box::maxpos.m128_f32[2] = center.m128_f32[2] + radius;

}
