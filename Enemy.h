#pragma once
#include"3d/fbxobj3d.h"
#include"SphereCollider.h"
#include"DebugText.h"

class Enemy : public FBXobj3d
{
public://メンバ関数
	Enemy();

	void EnemyInitialize();

	void EnemyUpdate(XMFLOAT3 playerpos);


	//衝突時コールバック関数
	void OnCollision(const CollisionInfo& info)override;


	void colReset();

	void move();

private:


	int col = 0;

	float G = -0.1;//重力加速度

	XMVECTOR Vel = { 0,0,0 };

	XMVECTOR Playerpos;

	XMVECTOR Vecpos;

	DebugText* Debugtext = nullptr;

	

};

