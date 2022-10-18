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
		XMVECTOR Velocity{ 0,0,bulspeed };

		Velocity={ target.x - eye.x, target.y - eye.y, target.z - eye.z };

		Velocity = XMVector3Normalize(Velocity) * bulspeed;

		//‘¬“xƒxƒNƒgƒ‹‚ðŽ©‹@‚ÌŒü‚«‚É‡‚í‚¹‚Ä‰ñ“]‚³‚¹‚é
		//Velocity=target

		//’e‚Ì¶¬‚Æ‰Šú‰»
		bullet->create(eye, Velocity);
	}

	//’e‚ÌXV
	if (bullet)
	{
		bullet->bulupdate();
	}
}

