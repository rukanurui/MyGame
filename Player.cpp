#include "Player.h"

void Player::Initialize(Input* Input)
{
	assert(Input);
	this->input = Input;
}

void Player::Update()
{

	if (input->PushKey(DIK_SPACE))
	{
		//’e‚Ì‘¬“x
		const float bulspeed = 0.1f;
		XMFLOAT3 Velocity{ 0,0,bulspeed };

		//’e‚Ì¶¬‚Æ‰Šú‰»
		Pbullet* newbullet = new Pbullet();
		newbullet->create(pos,Velocity);
		bullet = newbullet;
	}
	//’e‚ÌXV
	if (bullet)
	{
		bullet->update();
	}
}

void Player::Draw()
{
}
