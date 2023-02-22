#pragma once
#include"Pbullet.h"
#include"melee.h"
#include"PlayerGun.h"
#include"3d/fbxobj3d.h"
#include"SphereCollider.h"
#include "3d/FbxLoader.h"
#include "3d/Modelfbx.h"
#include <memory>
#include <list>

class Player : public FBXobj3d
	//public Camera
{

public://メンバ関数
	Player();
	//初期化
	void PlayerInitialize(Input*Input);
	//更新
	void PlayerUpdate(const XMFLOAT3& cameratarget);

	void BulUpdate();
	void meleeUpdate();
	void throwgunUpdate();
	void gunUpdate(const XMFLOAT3& cameratarget, const XMMATRIX& cameramatRot);
	

	/// 注視点座標の取得
	const XMFLOAT3& GetTarget() { return target; }

	void MoveVector(const XMVECTOR& move);

	/// 注視点座標の設定
	void SetTarget(XMFLOAT3 target);

	void SetoldTarget(XMFLOAT3 target);
	
	void Setoldpos(XMFLOAT3 Oldpos);

	//銃のフラグのゲッターとセッター
	const int& Gethave() { return have; }
	void Sethave(bool Have);


	void OnCollision(const CollisionInfo& info);

	void colUpdate();

	void ColInitialize();

	//hitのゲッター
	const int& Gethit() { return hit; }

	const int& Getwallhit() { return wallhit; }


	void sethit(int Hit);

	int hit = 0;

	int wallhit = 0;

	//描画
	void BulDraw(ID3D12GraphicsCommandList* cmdList);

	void meleeDraw(ID3D12GraphicsCommandList* cmdList);

	void throwgunDraw(ID3D12GraphicsCommandList* cmdList);

	void gunDraw(ID3D12GraphicsCommandList* cmdList);

	


private://メンバ変数
	//ポインタ
	Input* input = nullptr;
	FbxModel* modelballet = nullptr;
	FbxModel* modelgun = nullptr;

	//銃本体
	std::unique_ptr<PlayerGun> Pgun;

	//投げるときに生成される銃
	std::list<std::unique_ptr<PlayerGun>> Guns;


	std::list<std::unique_ptr<Pbullet>> bullets;
	std::list<std::unique_ptr<melee>> melees;

	//注視点
	XMFLOAT3 target{ 0.0f,4.0f,0.0f };
	//注視点までのきょり
	float distance = 5.0f;

	//持っている銃の場所決め(右下)

	const float gundistance = 1.5f;
	const float gunTdistance = 0.5;
	XMFLOAT3 guntarget{};
	XMFLOAT3 gunpos;
	XMVECTOR Velocity2{ -gundistance,-gundistance,gundistance };
	

	//攻撃関連
	//武器を持っているか
	bool have = true;
	//残弾
	int magazin = 5;
	//弾のクールタイム
	int ctime = 0;

	//格闘のクールタイム
	int mctime = 0;

	XMFLOAT3 oldpos;
	XMFLOAT3 oldtarget;
};

