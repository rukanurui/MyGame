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
		//’e‚Ì¶¬‚Æ‰Šú‰»
		Pbullet* newbullet = new Pbullet();
		newbullet->create();
		bullet = newbullet;
	}
}

void Player::Draw()
{
}
