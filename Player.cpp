#pragma once
#include "Player.h"


Player::Player(Pbullet* bullet):FBXobj3d()
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
		//’e‚Ì‘¬“x
		const float bulspeed = 1.5f;
		XMVECTOR Velocity{ 0,0,bulspeed };

		Velocity={ target.x - position.x, target.y - position.y, target.z - position.z };

		Velocity = XMVector3Normalize(Velocity) * bulspeed;

		//’e‚Ì¶¬‚Æ‰Šú‰»
		bullet->create(position, Velocity);
	}

	//’e‚ÌXV
	if (bullet)
	{
		bullet->bulupdate();
	}



	XMVECTOR vTargetEye = { 0.0f, 0.0f, -distance, 1.0f };

}

