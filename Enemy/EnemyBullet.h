#pragma once
#include"../3d/fbxobj3d.h"
#include"../Collider/SphereCollider.h"

class Enemybullet
	: public FBXobj3d
{

public:
	Enemybullet();
	void BulInitialize();
	void create(const XMFLOAT3& Enemypos, const XMVECTOR& velocity);
	void bulupdate();
	//void deleate(int flag);

	//衝突時コールバック関数
	void OnCollision(const CollisionInfo& info)override;

	const bool& Gethit() { return dead; }

	void Sethit(bool hit) { this->dead = hit; }

private:

	//速度
	XMVECTOR Vel = { 0,0,0 };

	bool dead = false;


};