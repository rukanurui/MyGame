#pragma once
#include"Pbullet.h"
#include"melee.h"
#include"PlayerGun.h"
#include"PickUp.h"
#include"../3d/fbxobj3d.h"
#include"../Collider/SphereCollider.h"
#include "../3d/FbxLoader.h"
#include "../3d/Modelfbx.h"
#include"../3d/PartManager.h"
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

	//弾更新
	void BulUpdate();
	//近接更新
	void meleeUpdate();
	//銃拾う動作更新
	void pickUpdate();
	//投げた銃更新
	void throwgunUpdate();
	//手に持っているときの銃更新
	void gunUpdate(const XMFLOAT3& cameratarget, const XMFLOAT3& cameraeye);

	//描画
	void Draw(ID3D12GraphicsCommandList* cmdList);


	//particle関連処理
	void PartUpdate();

	/// 注視点座標の取得
	const XMFLOAT3& GetTarget() { return target; }

	//移動速度の取得
	const XMFLOAT3& GetVelocity() { return Velocity; }

	void MoveVector(const XMVECTOR& move);

	/// 注視点座標の設定
	void SetTarget(XMFLOAT3 target);

	void SetoldTarget(XMFLOAT3 target);
	
	void Setoldpos(XMFLOAT3 Oldpos);

	//銃のフラグのゲッターとセッター
	const int& Gethave() { return have; }
	void Sethave(bool Have);

	//残弾数のゲッター
	const int& Getmagazin() { return magazin; }
	//残弾数のセッター
	void SetMagazin(int Magazin) { this->magazin = Magazin; }

	//collider関連
	void OnCollision(const CollisionInfo& info);
	void colUpdate();
	void ColInitialize();
	//壁との排斥処理
	void QueryWall();
	void Setwallhit(bool flag) { this->wallhit = flag; }

	//hitのゲッター
	const bool& Gethit() { return hit; }

	const bool& Getwallhit() { return wallhit; }

	void sethit(bool Hit) { this->hit = Hit; }

	//面のセット
	void setscene(int &scene) { this->nowscene = scene; }
	//チュートリアルのセット
	void setnowtuto(int &tuto) { this->nowtuto = tuto; }
	//チュートリアルのセット
	void settuto(int &tutoNum) { this->tutonum = tutoNum; }
	


private://メンバ変数
	//ポインタ
	Input* input = nullptr;
	FbxModel* modelballet = nullptr;
	FbxModel* modelgun = nullptr;
	FbxModel* model2 = nullptr;
	FbxModel* gunpix = nullptr;

	//銃本体
	std::unique_ptr<PlayerGun> Pgun;

	//投げるときに生成される銃
	std::list<std::unique_ptr<PlayerGun>> Guns;
	//弾
	std::list<std::unique_ptr<Pbullet>> bullets;
	//格闘
	std::list<std::unique_ptr<melee>> melees;
	//銃拾う
	std::list<std::unique_ptr<Pick>> picks;
	//パーティクル
	std::list<std::unique_ptr<PartManager>> particles;

	//パーティクルの数
	const int partnum = 15;

	//パーティクルの数カウント
	int partcount = 0;
	int parttimer = 0;

	//現在の面
	int nowscene = 0;
	//現在のチュートリアル
	int nowtuto = 0;
	//面ごとのチュートリアルの数
	int tutonum = 0;

	//注視点
	XMFLOAT3 target{ 0.0f,4.0f,0.0f };
	//注視点までのきょり
	float distance = 5.0f;

	//持っている銃の場所決め(右下)
	const float gundistance = 1.5f;
	XMFLOAT3 guntarget{};
	XMFLOAT3 gunpos;
	XMFLOAT3 Velocity{};
	XMVECTOR Velocity2{ -gundistance,-gundistance,gundistance };

	XMFLOAT3 currentangle;

	//敵に当たったか
	bool hit = false;

	//壁に当たっているか
	bool wallhit = false;
	

	//攻撃関連
	//武器を持っているか
	bool have = true;
	//残弾
	int magazin = 5;
	//弾のクールタイム
	int ctime = 0;

	//格闘のクールタイム
	int mctime = 0;
	//銃拾うクールタイム
	int picktime = 0;

	XMFLOAT3 oldpos;
	XMFLOAT3 oldtarget;
};

