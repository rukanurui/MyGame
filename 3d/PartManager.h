#pragma once
#include"fbxobj3d.h"
#include"../Collider/SphereCollider.h"
#include"../2d/DebugText.h"

class PartManager : public FBXobj3d
{

public://メンバ関数

	PartManager();
	//衝突時コールバック関数
	void OnCollision(const CollisionInfo& info)override;

	void PartInitialize(XMFLOAT3 pos);

	void PartUpdate();

	void setcol(int Col);

	const bool& Getdead() { return dead; }

private:

	XMVECTOR Vel{0.0f,0.0f,0.0f};

	int col = 0;

	float G = -0.1f;//重力加速度

	bool dead = false;

	float alivecount = 0;

	float alivelimit = 60;



};

