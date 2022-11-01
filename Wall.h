#pragma once
#include"3d/fbxobj3d.h"
#include"BoxCollider.h"

class Wall : public FBXobj3d
{

public:

	Wall();

	//衝突時コールバック関数
	void OnCollision(const CollisionInfo& info)override;

};