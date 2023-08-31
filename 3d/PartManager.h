#pragma once
#include"fbxobj3d.h"
#include"../Collider/SphereCollider.h"


class PartManager : public FBXobj3d
{

public://メンバ関数

	PartManager();
	//衝突時コールバック関数
	void OnCollision(const CollisionInfo& info)override;

	//普通のパーティクルの初期化
	void PartInitialize(XMFLOAT3 pos);

	//弾道の初期化
	void BullisticInitialize(XMFLOAT3& pos,XMVECTOR& Velocity,XMFLOAT3& angle);

	//弾道の初期化(敵)
	void BullisticInitializeEnemy(XMFLOAT3& pos, XMVECTOR& Velocity, XMFLOAT3& angle, int& num);

	//普通のパーティクルの更新
	void PartUpdate();

	//弾道の更新
	void BullisticUpdate();
	void BullisticUpdateEnemy();

	const bool& Getdead() { return dead; }

	const int& Getbullisticnum() { return numbullistic; }

	//消去フラグのsetter
	void Setdead(bool flag) { this->dead = flag; }


private:

	XMVECTOR Vel{0.0f,0.0f,0.0f};

	float G = -0.1f;//重力加速度

	//何個目の弾道か
	int numbullistic = 0;

	//消去フラグ
	bool dead = false;

	//経過時間
	float alivecount = 0;

	//数値カウント用変数
	int count = 0;

	//最大持続時間
	const float alivelimit = 60;



};

