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

	//普通のパーティクルの初期化
	void PartInitialize(XMFLOAT3 pos);

	//弾道の初期化
	void BullisticInitialize(XMFLOAT3& pos,XMVECTOR& Vel,XMFLOAT3& angle);

	//普通のパーティクルの更新
	void PartUpdate();

	//弾道の更新
	void BullisticUpdate();

	const bool& Getdead() { return dead; }

	//消去フラグのsetter
	void Setdead(bool flag) { this->dead = flag; }

private:

	XMVECTOR Vel{0.0f,0.0f,0.0f};

	float G = -0.1f;//重力加速度

	//消去フラグ
	bool dead = false;

	//経過時間
	float alivecount = 0;

	//最大持続時間
	const float alivelimit = 60;



};

