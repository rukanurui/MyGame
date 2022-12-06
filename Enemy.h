#pragma once
#include"3d/fbxobj3d.h"
#include"SphereCollider.h"
#include"DebugText.h"

#include"EnemyBullet.h"

class Enemy : public FBXobj3d
{
public://メンバ関数
	Enemy();

	void EnemyInitialize(bool Shot);

	void EnemyUpdate(XMFLOAT3 playerpos);

	void Shot();


	//衝突時コールバック関数
	void OnCollision(const CollisionInfo& info)override;


	void colReset();

	void move();

private:

	Enemybullet* bullet = nullptr;

	int col = 0;

	float G = -0.1;//重力加速度

	XMVECTOR Vel = { 0,0,0 };

	XMVECTOR Playerpos;

	XMVECTOR Vecpos;

	DebugText* Debugtext = nullptr;

	//弾を打つ敵かどうか
	bool Shot;

	//弾のクールタイム
	float count=0;

	

};

