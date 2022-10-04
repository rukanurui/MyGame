#include "Player.h"

void Player::Initialize(Input* input)
{
	assert(input);
	this->input = input;
}

void Player::Update()
{

	if (input->PushclickLeft())
	{
		//弾の生成と初期化
		Pbullet* newbullet = new Pbullet();
		newbullet->create();
		bullet = newbullet;
	}
}

void Player::Draw()
{
}
