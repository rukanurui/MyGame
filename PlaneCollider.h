#pragma once
#include"BaseCollider.h"
#include"CollisionPrimitive.h"
#include<DirectXMath.h>

class PlaneCollider :public BaseCollider, public Plane
{
private://エイリアス
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	PlaneCollider(XMVECTOR offset = { 0,0,0,0 }) :
		offset(offset)
	{
		//平面
		shapeType = COLLISIONSHAPE_PLANE;
	}

	//更新
	void Update()override;



private:
	//オブジェクト中心からのオフセット
	XMVECTOR offset;

};