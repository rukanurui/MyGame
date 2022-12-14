#pragma once
#include"Pbullet.h"
#include"3d/fbxobj3d.h"
#include"SphereCollider.h"

class Player : public FBXobj3d
	//public Camera
{

public://メンバ関数
	Player(Pbullet* bullet);
	//初期化
	void PlayerInitialize(Input*Input);
	//更新
	void PlayerUpdate();
	
	//攻撃処理
	void Shot();

	/// 注視点座標の取得
	const XMFLOAT3& GetTarget() { return target; }

	void MoveVector(const XMVECTOR& move);

	/// 注視点座標の設定
	void SetTarget(XMFLOAT3 target);

	void SetoldTarget(XMFLOAT3 target);
	
	void Setoldpos(XMFLOAT3 Oldpos);

	void OnCollision(const CollisionInfo& info);

	void colUpdate();

	void ColInitialize();

	const int& Gethit() { return hit; }

	const int& Getwallhit() { return wallhit; }

	void sethit(int Hit);

	int hit = 0;

	int wallhit = 0;

	


private://メンバ変数
	Input* input = nullptr;
	//Pbullet* bullet = nullptr;
	Pbullet*bullet;
	XMFLOAT3 target{ 0,4,0 };
	float distance = 5.0f;

	XMFLOAT3 oldpos;
	XMFLOAT3 oldtarget;
};

