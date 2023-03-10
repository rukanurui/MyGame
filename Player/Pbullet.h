#pragma once
#include"../3d/fbxobj3d.h"
#include"../Collider/SphereCollider.h"


class Pbullet 
: public FBXobj3d 
{

public:
	Pbullet();
	void BulInitialize();
	void create(const XMFLOAT3& Playerpos,const XMVECTOR& velocity);
	void bulupdate();
	//void deleate(int flag);

	//衝突時コールバック関数
	void OnCollision(const CollisionInfo& info)override;
	const bool& Getdead() { return dead; }

private:
	
	//速度
	XMVECTOR Vel={ 0,0,0 };
	
	
	bool dead = false;

};

