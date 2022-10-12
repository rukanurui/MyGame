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

	if (input->PushKey(DIK_SPACE))
	{
		//’e‚Ì‘¬“x
		const float bulspeed = 0.1f;
		XMFLOAT3 Velocity{ 0,0,bulspeed };

		//’e‚Ì¶¬‚Æ‰Šú‰»
		
		bullet->create(eye, Velocity);
	}

	//’e‚ÌXV
	if (bullet)
	{
		bullet->bulupdate();
	}
}

