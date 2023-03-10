#pragma once
#include<DirectXMath.h>


class FBXobj3d;
class BaseCollider;

//衝突情報
struct CollisionInfo

{
protected:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	CollisionInfo(FBXobj3d* object, BaseCollider* collider, const XMVECTOR& inter)
	{
		this->object = object;
		this->collider = collider;
		this->inter = inter;
	}

	//衝突相手のオブジェクト
	FBXobj3d* object = nullptr;
	//衝突相手のコライダー
	BaseCollider* collider = nullptr;
	//衝突点
	XMVECTOR inter;

};

