#pragma once
#include<DirectXMath.h>

class FBXobj3d;
class BaseCollider;

//クエリーによる情報を得るための構造体
struct QueryHit
{
	//衝突相手のオブジェクト
	FBXobj3d* object = nullptr;
	//衝突相手のコライダー
	BaseCollider* collider = nullptr;
	//衝突点
	DirectX::XMVECTOR inter;
	//排斥ベクトル
	DirectX::XMVECTOR reject;
};

class QueryCallback
{
public:
	QueryCallback() = default;
	virtual~QueryCallback() = default;

	//交差時コールバック
	virtual bool OnQueryHit(const QueryHit& info) = 0;
};
