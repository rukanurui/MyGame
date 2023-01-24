#pragma once
#include"3d/fbxobj3d.h"
#include"BoxCollider.h"
#include"CollisionColor.h"

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

private:

	bool infohave = false;

};