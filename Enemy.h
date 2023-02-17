#pragma once
#include"3d/fbxobj3d.h"
#include "3d/FbxLoader.h"
#include "3d/Modelfbx.h"
#include"SphereCollider.h"

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
	void setcol(int Col);

	void move();

	//弾関連処理
	void BulUpdate();

	void BulDraw(ID3D12GraphicsCommandList* cmdList);

	//particle関連処理
	void PartUpdate();

	void PartDraw(ID3D12GraphicsCommandList* cmdList);

private:

	//ポインタ
	FbxModel* modelballet = nullptr;
	FbxModel* model2 = nullptr;
	//Enemybullet* bullet=nullptr;
	std::list<std::unique_ptr<Enemybullet>> bullets;
	std::list<std::unique_ptr<PartEnemy>> particle;
	
	//boolに変更する
	//当たったかのフラグ
	int col = 0;

	//パーティクルの数
	const int partnum = 20;

	//パーティクルの数カウント
	int partcount = 0;



	float G = -0.1;//重力加速度

	XMVECTOR Vel = { 0,0,0 };

	XMVECTOR Playerpos;

	XMVECTOR Vecpos;

	//弾を打つ敵かどうか
	bool Shot;

	//弾のクールタイム
	float count=0;

	

};

