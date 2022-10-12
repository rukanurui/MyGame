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
		//�e�̑��x
		const float bulspeed = 0.1f;
		XMFLOAT3 Velocity{ 0,0,bulspeed };

		//�e�̐����Ə�����
		
		bullet->create(eye, Velocity);
	}

	//�e�̍X�V
	if (bullet)
	{
		bullet->bulupdate();
	}
}

