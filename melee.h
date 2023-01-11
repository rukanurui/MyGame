#pragma once
#include"3d/fbxobj3d.h"
#include"SphereCollider.h"

class melee
	: public FBXobj3d
{

public:
	melee();
	void meleeInitialize();
	void create(const XMFLOAT3& Playerpos,const XMVECTOR& velocity);
	void meleeupdate();
	

	//衝突時コールバック関数
	void OnCollision(const CollisionInfo& info)override;
	const bool& Getdead() { return dead; }

private:

	//速度
	XMVECTOR Vel = { 0,0,0 };

	//寿命
	static const int32_t ktime = 15;
	//タイマー
	int32_t timer = ktime;

	bool dead = false;


};

