#pragma once
#include"../3d/fbxobj3d.h"
#include"SphereCollider.h"

class PlayerCol : public FBXobj3d
{
public:
	PlayerCol();

	void OnCollision(const CollisionInfo& info);

	void colUpdate();

	void ColInitialize();

	const int& Gethit() { return hit; }

	int hit = 0;
};

