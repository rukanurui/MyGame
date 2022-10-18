#pragma once
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

private:
	CollisionManager() = default;
	CollisionManager(const CollisionManager&) = delete;
	~CollisionManager() = default;
	CollisionManager& operator=(const CollisionManager&) = delete;
	//コライダーのリスト
	std::forward_list<BaseCollider*> colliders;
};

