#pragma once
#include "Player.h"


Player::Player(Pbullet* bullet):Camera(input, windows)
{
	this->bullet = bullet;
};

void Player::PlayerInitialize(Input* Input)
{
	assert(Input);
	this->input = Input;
}

void Player::PlayerUpdate()
{

	if (input->TriggerKey(DIK_SPACE))
	{
		//弾の速度
		const float bulspeed = 0.1f;
		XMVECTOR Velocity{ 0,0,bulspeed };

		Velocity={ target.x - eye.x, target.y - eye.y, target.z - eye.z };

		Velocity = XMVector3Normalize(Velocity) * bulspeed;

		//速度ベクトルを自機の向きに合わせて回転させる
		//Velocity=target

		//弾の生成と初期化
		bullet->create(eye, Velocity);
	}

	//弾の更新
	if (bullet)
	{
		bullet->bulupdate();
	}
}

