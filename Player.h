#pragma once
#include"Pbullet.h"
#include"3d/fbxobj3d.h"


class Player : public FBXobj3d
{

public://メンバ関数
	Player(Pbullet* bullet);
	//初期化
	void PlayerInitialize(Input*Input);
	//更新
	void PlayerUpdate();
	//攻撃処理
	void Shot();



private://メンバ変数
	Input* input = nullptr;
	//Pbullet* bullet = nullptr;
	Pbullet*bullet;
	XMFLOAT3 target{ 0,0,0 };
	float distance = 5;
};

