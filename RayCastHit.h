#pragma once
#include"BaseCollider.h"
#include<DirectXMath.h>

class FBXobj3d;

struct RayCastHit
{
	//衝突相手のオブジェクト
	FBXobj3d* object = nullptr;
	//衝突相手のコライダー
	BaseCollider* collider = nullptr;
	//衝突点
	DirectX::XMVECTOR inter;
	//衝突点までの距離
	float distance = 0.0f;
};

