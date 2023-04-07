#pragma once
#include"CollisionPrimitive.h"
#include"RayCastHit.h"
#include"QueryCallback.h"

#include<d3d12.h>
#include<forward_list>

class BaseCollider;

class CollisionManager
{
public://静的メンバ変数
	static CollisionManager* GetInstance();

public://メンバ関数
	//コライダーの追加
	inline void ADDCollider(BaseCollider* collider) {
		colliders.push_front(collider);
	}

	//コライダーの削除
	inline void RemoveCollider(BaseCollider* collider) {
		colliders.remove(collider);
	}

	//全ての衝突チェック
	void CheckAllCollisions();

	//コールバック用の衝突チェック(球)
	void CheckQuerySphere(const Sphere& sphere,QueryCallback* callback,unsigned short color = (unsigned short)0xffffffff);

	//コールバック用の衝突チェック(AABB)
	void CheckQueryBox(const Sphere& sphere, QueryCallback* callback, unsigned short color = (unsigned short)0xffffffff);

	//レイとすべてのコライダーとの衝突判定
	bool RayCast(const Ray& ray, RayCastHit* hitinfo = nullptr, float MaxDistance = D3D12_FLOAT32_MAX);

	void CheckBoxShere();

	//平面と球のコライダーとの衝突判定


private:
	CollisionManager() = default;
	CollisionManager(const CollisionManager&) = delete;
	~CollisionManager() = default;
	CollisionManager& operator=(const CollisionManager&) = delete;
	//コライダーのリスト
	std::forward_list<BaseCollider*> colliders;
};

