#pragma once
#include"../3d/fbxobj3d.h"
#include"../Collider/SphereCollider.h"

class Pick
	: public FBXobj3d
{

public:
	Pick();
	void pickInitialize();
	void create(const XMFLOAT3& Playerpos, const XMVECTOR& velocity);
	void pickupdate();


	//衝突時コールバック関数
	void OnCollision(const CollisionInfo& info)override;
	const bool& Getdead() { return dead; }
	const bool& Getpick() { return pickflag; }

private:

	//速度
	XMVECTOR Vel = { 0,0,0 };

	//寿命
	static const int32_t ktime = 15;
	//タイマー
	int32_t timer = ktime;

	//衝突フラグ
	bool dead = false;
	//拾ったかのフラグ
	bool pickflag = false;


};

