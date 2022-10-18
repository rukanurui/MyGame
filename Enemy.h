#pragma once
#include"3d/fbxobj3d.h"
#include"SphereCollider.h"


class Enemy : public FBXobj3d
{
public://メンバ関数
	Enemy();

	bool EnemyInitialize();

	void EnemyUpdate();

	//衝突時コールバック関数
	void OnCollision(const CollisionInfo& info)override;

private:
	float Div = 10;

};

