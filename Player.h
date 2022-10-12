#pragma once
#include"Pbullet.h"
#include"Camera.h"


class Player : public Camera
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
};

