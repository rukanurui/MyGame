#pragma once
#include"3d/fbxobj3d.h"
#include"SphereCollider.h"

class PlayerGun
	: public FBXobj3d
{
public:
	PlayerGun();
	void GunInitialize();
	void create(const XMFLOAT3& Playerpos, const XMVECTOR& velocity);
	void staycreate(const XMFLOAT3& Playerpos);
	void gunupdate(const XMFLOAT3& Playerpos, const XMVECTOR& velocity);
	void throwgunUpdate();

	//void deleate(int flag);

	//衝突時コールバック関数
	void OnCollision(const CollisionInfo& info)override;
	const bool& Getdead() { return dead; }

private:

	//速度
	XMVECTOR Vel = { 0,0,0 };

	//角度
	XMFLOAT3 angle = { 0,0,0 };

	bool release = false;
	bool have = true;
	bool dead = false;
};

