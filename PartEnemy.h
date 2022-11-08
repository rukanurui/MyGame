#pragma once
#include"3d/fbxobj3d.h"
#include"SphereCollider.h"
#include"DebugText.h"

class PartEnemy : public FBXobj3d
{

public://メンバ関数

	PartEnemy();
	//衝突時コールバック関数
	void OnCollision(const CollisionInfo& info)override;

	void PartInitialize();

	void PartUpdate();


private:

private:

	XMVECTOR Vel{0.0f,0.0f,0.0f};

	int col = 0;

	float G = -0.1;//重力加速度



};

