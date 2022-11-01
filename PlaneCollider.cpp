#include"PlaneCollider.h"

using namespace DirectX;

void PlaneCollider::Update()
{
	//ワールド行列から座標を抽出
	const XMMATRIX& matWorld = fbxobject->GetMatWorld();

	//球のメンバ変数を更新
	Plane::normal = matWorld.r[3] + offset;
	Plane::distance = distance;
}