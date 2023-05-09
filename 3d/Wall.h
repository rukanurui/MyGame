#pragma once
#include"fbxobj3d.h"
#include"../Collider/BoxCollider.h"
#include"../Collider/CollisionColor.h"

class Wall : public FBXobj3d
{

public:

	Wall();

	void WallInitialize();

	void objgunInitialize();

	//衝突時コールバック関数
	void OnCollision(const CollisionInfo& info)override;

	//銃のフラグ
	const int& Gethave() { return infohave; }
	void Sethave(bool Have);

	const int die = 1;

private:

	bool infohave = false;

};