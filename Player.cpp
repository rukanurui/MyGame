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
		//弾の速度
		const float bulspeed = 10;
		XMFLOAT3 Velocity{ 0,0,bulspeed };

		//弾の生成と初期化
		Pbullet* newbullet = new Pbullet();
		newbullet->create(pos,Velocity);
		bullet = newbullet;
	}
	//弾の更新
	if (bullet)
	{
		bullet->bulupdate();
	}
}

void Player::Draw()
{
}
