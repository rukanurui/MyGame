#pragma once
#include "Player.h"
#include"QueryCallback.h"
#include"CollisionManager.h";


Player::Player():FBXobj3d()
{
};

void Player::PlayerInitialize(Input* Input)
{
	assert(Input);
	this->input = Input;
	//属性の追加
	collider->SetColor(COLLISION_COLOR_PLAYER);

	modelballet = FbxLoader::GetInstance()->LoadModelFromFile("bullet");
	modelgun = FbxLoader::GetInstance()->LoadModelFromFile("gun");


	//銃の生成と初期化
	PlayerGun* newGun = new PlayerGun();
	newGun->Initialize();
	newGun->SetScale({ 0.01f,0.01f,0.01f });
	newGun->SetModel(modelgun);
	//newGun->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
	//newGun->GunInitialize();
	newGun->staycreate(position);
	//銃の登録
	Pgun.reset(newGun);

}

void Player::MoveVector(const XMVECTOR& move)
{
	XMFLOAT3 pos_moved = GetPos();

	pos_moved.x += move.m128_f32[0];
	pos_moved.y += move.m128_f32[1];
	pos_moved.z += move.m128_f32[2];

	SetPosition(pos_moved);

}


void Player::PlayerUpdate()
{

	//弾の削除
	bullets.remove_if([](std::unique_ptr<Pbullet>& bullet) {
		return bullet->Getdead();
		});

	//投げた銃の削除
	Guns.remove_if([](std::unique_ptr<PlayerGun>& gun) {
		return gun->Getdead();
		});

	//格闘の削除
	melees.remove_if([](std::unique_ptr<melee>& melee) {
		return melee->Getdead();
		});

	UpdateWorld();

	//当たり判定更新
	if (collider)
	{
		collider->Update();
	}

	ctime--;
	mctime--;

	if (ctime <= 0)
	{
		ctime = 0;
	}

	if (mctime <= 0)
	{
		mctime = 0;
	}


	if (input->TriggerKey(DIK_SPACE)&&ctime<=0 && magazin>=1&&have==true)
	{
		//弾の速度
		const float bulspeed = 1.5f;
		XMVECTOR Velocity{ 0,0,bulspeed };

		Velocity={ target.x - position.x, target.y - position.y, target.z - position.z };

		Velocity = XMVector3Normalize(Velocity) * bulspeed;

		//弾の生成と初期化
		//bullet->create(position, Velocity);
		std::unique_ptr<Pbullet>newBullet = std::make_unique<Pbullet>();
		newBullet->Initialize();
		newBullet->SetScale({ 0.01f,0.01f,0.01f });
		newBullet->SetModel(modelballet);
		newBullet->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
		newBullet->BulInitialize();
		newBullet->create(position, Velocity);
		//弾の登録
		bullets.push_back(std::move(newBullet));
		ctime = 30;
		//残弾減らす
		magazin--;
	}

	if (input->TriggerKey(DIK_Q) && have==true)
	{
		//弾の速度
		const float bulspeed = 1.0f;
		XMVECTOR Velocity{ 0,0,bulspeed };

		Velocity = { target.x - position.x, target.y - position.y, target.z - position.z };

		Velocity = XMVector3Normalize(Velocity) * bulspeed;

		//弾の生成と初期化
		std::unique_ptr<PlayerGun>newGun = std::make_unique<PlayerGun>();
		newGun->Initialize();
		newGun->SetScale({ 0.01f,0.01f,0.01f });
		newGun->SetModel(modelgun);
		newGun->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
		newGun->GunInitialize();
		newGun->create(position, Velocity);
		//弾の登録
		Guns.push_back(std::move(newGun));
		//残弾減らす
		magazin=0;
		//フラグ変更
		have = false;
	}

	if (input->TriggerKey(DIK_SPACE) && have==false&&mctime<=0)
	{
		//弾の速度
		const float bulspeed = 0.7f;
		XMVECTOR Velocity{ 0,0,bulspeed };

		Velocity = { target.x - position.x, target.y - position.y, target.z - position.z };

		Velocity = XMVector3Normalize(Velocity) * bulspeed;

		//格闘の生成と初期化
		std::unique_ptr<melee>newMelee = std::make_unique<melee>();
		newMelee->Initialize();
		newMelee->SetScale({ 0.05f,0.05f,0.01f });
		newMelee->SetModel(modelballet);
		newMelee->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
		newMelee->meleeInitialize();
		newMelee->create(position, Velocity);
		//格闘の登録
		melees.push_back(std::move(newMelee));
		mctime = 30;
	}

	//弾の更新
	for (std::unique_ptr<Pbullet>& bullet : bullets)
	{
		bullet->bulupdate();
		bullet->Update();
	}

	//銃の更新
	XMVECTOR Velocity{ 0,0,0};

	Velocity = { target.x - position.x, target.y - position.y, target.z - position.z };

	Velocity = XMVector3Normalize(Velocity);

	Pgun->gunupdate(position, rotation);
	Pgun->Update();

	//投げた銃の更新
	for (std::unique_ptr<PlayerGun>& gun : Guns)
	{
		gun->throwgunUpdate();
		gun->Update();
	}

	//格闘の更新
	for (std::unique_ptr<melee>& melee : melees)
	{
		melee->meleeupdate();
		melee->Update();
	}


}

void Player::BulUpdate()
{
	for (std::unique_ptr<Pbullet>& bullet : bullets)
	{
		bullet->Update();
	}
}

void Player::meleeUpdate()
{
	for (std::unique_ptr<melee>& melee : melees)
	{
		melee->Update();
	}
}

void Player::throwgunUpdate()
{
	for (std::unique_ptr<PlayerGun>& gun : Guns)
	{
		gun->Update();
	}
}

void Player::gunUpdate()
{
	Pgun->gunupdate(position, rotation);
}

void Player::BulDraw(ID3D12GraphicsCommandList* cmdList)
{

	for (std::unique_ptr<Pbullet>& bullet : bullets)
	{
		bullet->Draw(cmdList);
	}
}

void Player::meleeDraw(ID3D12GraphicsCommandList* cmdList)
{
	for (std::unique_ptr<melee>& melee : melees)
	{
		melee->Draw(cmdList);
	}
}

void Player::throwgunDraw(ID3D12GraphicsCommandList* cmdList)
{
	for (std::unique_ptr<PlayerGun>& gun : Guns)
	{
		gun->Draw(cmdList);
	}
}

void Player::gunDraw(ID3D12GraphicsCommandList* cmdList)
{
	if (have==true)
	{
		Pgun->Draw(cmdList);
	}
	
}

void Player::OnCollision(const CollisionInfo& info)
{
	if (info.collider->color == 8)
	{
		hit = 1;
	}

	if (info.collider->color == 1)
	{
		wallhit = 1;
		position = oldpos;
		target = oldtarget;
	}
	else
	{
		wallhit = 0;
	}

	
	UpdateWorld();

	//当たり判定更新
	if (collider)
	{
		collider->Update();
	}

}

void Player::colUpdate()
{


}

void Player::SetTarget(XMFLOAT3 target)
{
	Player::target = target;

}

void Player::SetoldTarget(XMFLOAT3 target)
{
	oldtarget = target;
}

void Player::Setoldpos(XMFLOAT3 Oldpos)
{
	oldpos = Oldpos;
}

void Player::ColInitialize()
{
	//属性の追加
	collider->SetColor(COLLISION_COLOR_PLAYER);
}

void Player::sethit(int Hit)
{
	hit = Hit;
}
