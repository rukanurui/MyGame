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
		XMVECTOR Velocity{ 0,0,bulspeed };

		Velocity={ target.x - eye.x, target.y - eye.y, target.z - eye.z };

		Velocity = XMVector3Normalize(Velocity) * bulspeed;

		//���x�x�N�g�������@�̌����ɍ��킹�ĉ�]������
		//Velocity=target

		//�e�̐����Ə�����
		bullet->create(eye, Velocity);
	}

	//�e�̍X�V
	if (bullet)
	{
		bullet->bulupdate();
	}
}

