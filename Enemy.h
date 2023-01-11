#pragma once
#include"3d/fbxobj3d.h"
#include "3d/FbxLoader.h"
#include "3d/Modelfbx.h"
#include"SphereCollider.h"

#include <memory>
#include <list>

#include"EnemyBullet.h"

class Enemy : public FBXobj3d
{
public://メンバ関数
	Enemy();

	void EnemyInitialize(bool Shot);

	void EnemyUpdate(XMFLOAT3 playerpos);

	void Attack(XMFLOAT3 playerpos);

	//衝突時コールバック関数
	void OnCollision(const CollisionInfo& info)override;


	void colReset();

	void move();

	void BulUpdate();

	void BulDraw(ID3D12GraphicsCommandList* cmdList);

	void setcol(int Col);

private:

	//ポインタ
	FbxModel* modelballet = nullptr;
	//Enemybullet* bullet=nullptr;
	std::list<std::unique_ptr<Enemybullet>> bullets;
	
	int col = 0;

	float G = -0.1;//重力加速度

	XMVECTOR Vel = { 0,0,0 };

	XMVECTOR Playerpos;

	XMVECTOR Vecpos;

	//弾を打つ敵かどうか
	bool Shot;

	//弾のクールタイム
	float count=0;

	

};

