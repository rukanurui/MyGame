#pragma once
#include"../3d/fbxobj3d.h"
#include "../3d/FbxLoader.h"
#include "../3d/Modelfbx.h"
#include"../Collider/SphereCollider.h"

#include <memory>
#include <list>

#include"EnemyBullet.h"
#include"PartEnemy.h"

class Enemy : public FBXobj3d
{
public://メンバ関数
	Enemy();

	void EnemyInitialize(bool Shot);

	//
	void EnemyUpdate(XMFLOAT3 playerpos);

	//攻撃処理
	void Attack(XMFLOAT3 playerpos);

	//衝突時コールバック関数
	void OnCollision(const CollisionInfo& info)override;

	//当たり判定リセット
	void colReset();
	//当たり判定セット
	void setcol(bool Col);
	const bool& getcol() { return col; }
	const bool& getdeath() { return death; }

	void move();

	//弾関連処理
	void BulUpdate();

	void BulDraw(ID3D12GraphicsCommandList* cmdList);

	//particle関連処理
	void PartUpdate();

	void PartDraw(ID3D12GraphicsCommandList* cmdList);

	const int die = 1;

private:

	//ポインタ
	FbxModel* modelballet = nullptr;
	FbxModel* model2 = nullptr;
	//Enemybullet* bullet=nullptr;
	std::list<std::unique_ptr<Enemybullet>> bullets;
	std::list<std::unique_ptr<PartEnemy>> particle;
	
	//boolに変更する
	//当たったかのフラグ
	bool col = false;
	bool death = false;

	//パーティクルの数
	const int partnum = 20;

	//パーティクルの数カウント
	int partcount = 0;
	int parttimer = 0;



	float G = -0.1;//重力加速度

	XMVECTOR Vel = { 0,0,0 };

	XMVECTOR Playerpos;

	XMVECTOR Vecpos;

	//弾を打つ敵かどうか
	bool Shot;

	//弾のクールタイム
	float count=0;

	

};

