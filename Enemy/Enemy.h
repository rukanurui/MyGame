#pragma once
#include"../3d/fbxobj3d.h"
#include "../3d/FbxLoader.h"
#include "../3d/Modelfbx.h"
#include"../Collider/SphereCollider.h"

#include <memory>
#include <list>

#include"EnemyBullet.h"
#include"../3d/PartManager.h"
#include "../2d/Partmanager2d.h"
#include"../Engine/DXCommon.h"



class Enemy : public FBXobj3d
{
public://メンバ関数
	Enemy();

	void EnemyInitialize(bool Shot, Camera* camera,DXCommon* dxcommon);

	void SetModelNum(int &num) { this->modelnum = num; }

	//敵固有処理
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
	void BullisticUpdate();

	void CreateParticles(XMFLOAT3 Pos);

	void PartDraw(ID3D12GraphicsCommandList* cmdList);
	void PartDraw2d(ID3D12GraphicsCommandList* cmdList);
	void BullisticDraw(ID3D12GraphicsCommandList* cmdList);

	void LastUpdate();

	const int & getbulnum() { return bulnum; }

	const bool die = true;

private:

	//ポインタ
	FbxModel* modelballet = nullptr;
	FbxModel* modelenemy = nullptr;
	FbxModel* modelbullistic = nullptr;
	WindowsApp* Windows = nullptr;
	DXCommon* dxCommon = nullptr;
	ParticleManager2d* particle2d = nullptr;
	
	
	//リスト
	std::list<std::unique_ptr<Enemybullet>> bullets;
	std::list<std::unique_ptr<PartManager>> particle;
	//弾道
	std::list<std::unique_ptr<PartManager>> bullistic;
	//std::list<std::unique_ptr<ParticleManager2d>> particle2d;
	
	//モデルの番号
	int modelnum = 0;

	//当たったかのフラグ
	bool col = false;
	bool death = false;

	XMVECTOR Velocity2{};

	//パーティクルの数
	const int partnum = 20;

	//パーティクルの数カウント
	int partcount = 0;
	int parttimer = 0;

	bool partflag = false;

	//弾の数カウント
	int bulnum = 0;


	float G = -0.1;//重力加速度

	XMVECTOR Vel = { 0,0,0 };

	XMVECTOR Playerpos;

	XMVECTOR Vecpos;

	//弾を打つ敵かどうか
	bool Shot;

	//弾のクールタイム
	float count=0;

	

};

