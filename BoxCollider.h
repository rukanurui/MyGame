#pragma once
#include"BaseCollider.h"
#include"CollisionPrimitive.h"
#include<DirectXMath.h>

//球衝突判定
class BoxCollider :public BaseCollider, public Box
{
private://エイリアス
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	BoxCollider(XMVECTOR offset = { 0,0,0,0 }, float radius = 1.0f) :
		offset(offset),
		radius(radius)
	{
		//直方体
		shapeType = COLLISIONSHAPE_BOX;
	}

	//更新
	void Update()override;

	inline void SetRadius(float radius) { this->radius = radius; }

private:
	//オブジェクト中心からのオフセット
	XMVECTOR offset;
	//半径
	float radius;
};

