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
	//�����̒ǉ�
	collider->SetColor(COLLISION_COLOR_PLAYER);

	modelballet = FbxLoader::GetInstance()->LoadModelFromFile("bullet");
	modelgun = FbxLoader::GetInstance()->LoadModelFromFile("gun");


	//�e�̐����Ə�����
	PlayerGun* newGun = new PlayerGun();
	newGun->Initialize();
	newGun->SetScale({ 0.01f,0.01f,0.01f });
	newGun->SetModel(modelgun);
	newGun->staycreate(position);
	//�e�̓o�^
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


void Player::PlayerUpdate(const XMFLOAT3& cameratarget)
{

	//�e�̍폜
	bullets.remove_if([](std::unique_ptr<Pbullet>& bullet) {
		return bullet->Getdead();
		});

	//�������e�̍폜
	Guns.remove_if([](std::unique_ptr<PlayerGun>& gun) {
		return gun->Getdead();
		});

	//�i���̍폜
	melees.remove_if([](std::unique_ptr<melee>& melee) {
		return melee->Getdead();
		});

	UpdateWorld();

	//�����蔻��X�V
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
		//�e�̑��x
		const float bulspeed = 1.5f;
		XMVECTOR Velocity{ 0,0,bulspeed };

		Velocity={ cameratarget.x - position.x, cameratarget.y - position.y, cameratarget.z - position.z };

		Velocity = XMVector3Normalize(Velocity) * bulspeed;

		//�e�̐����Ə�����
		//bullet->create(position, Velocity);
		std::unique_ptr<Pbullet>newBullet = std::make_unique<Pbullet>();
		newBullet->Initialize();
		newBullet->SetScale({ 0.01f,0.01f,0.01f });
		newBullet->SetModel(modelballet);
		newBullet->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
		newBullet->BulInitialize();
		newBullet->create(position, Velocity);
		//�e�̓o�^
		bullets.push_back(std::move(newBullet));
		ctime = 30;
		//�c�e���炷
		magazin--;
	}

	if (input->TriggerKey(DIK_Q) && have==true)
	{
		//�e�̑��x
		const float bulspeed = 1.0f;
		XMVECTOR Velocity{ 0,0,bulspeed };

		Velocity = { target.x - position.x, target.y - position.y, target.z - position.z };

		Velocity = XMVector3Normalize(Velocity) * bulspeed;

		//�e�̐����Ə�����
		std::unique_ptr<PlayerGun>newGun = std::make_unique<PlayerGun>();
		newGun->Initialize();
		newGun->SetScale({ 0.01f,0.01f,0.01f });
		newGun->SetModel(modelgun);
		newGun->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
		newGun->GunInitialize();
		newGun->create(position, Velocity);
		//�e�̓o�^
		Guns.push_back(std::move(newGun));
		//�c�e���炷
		magazin=0;
		//�t���O�ύX
		have = false;
	}

	if (input->TriggerKey(DIK_SPACE) && have==false&&mctime<=0)
	{
		//�e�̑��x
		const float bulspeed = 0.7f;
		XMVECTOR Velocity{ 0,0,bulspeed };

		Velocity = { target.x - position.x, target.y - position.y, target.z - position.z };

		Velocity = XMVector3Normalize(Velocity) * bulspeed;

		//�i���̐����Ə�����
		std::unique_ptr<melee>newMelee = std::make_unique<melee>();
		newMelee->Initialize();
		newMelee->SetScale({ 0.05f,0.05f,0.01f });
		newMelee->SetModel(modelballet);
		newMelee->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
		newMelee->meleeInitialize();
		newMelee->create(position, Velocity);
		//�i���̓o�^
		melees.push_back(std::move(newMelee));
		mctime = 30;
	}

	//�e�̍X�V
	for (std::unique_ptr<Pbullet>& bullet : bullets)
	{
		bullet->bulupdate();
		bullet->Update();
	}


	//�������e�̍X�V
	for (std::unique_ptr<PlayerGun>& gun : Guns)
	{
		gun->throwgunUpdate();
		gun->Update();
	}

	//�i���̍X�V
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

void Player::gunUpdate(const XMFLOAT3& cameratarget,const XMMATRIX& cameramatRot)
{

	//�e�̍X�V
	gunpos = position;

	XMMATRIX cameramatrot = cameramatRot;

	Velocity2 = { cameratarget.x - position.x, cameratarget.y - position.y, cameratarget.z - position.z };

	Velocity2 = XMVector3Normalize(Velocity2);

	XMVECTOR move = { -2.0f,-2.0f,0,0 };
	move = XMVector3Transform(move, cameramatrot);

	gunpos.x += move.m128_f32[0]; gunpos.y += move.m128_f32[1]; gunpos.z += move.m128_f32[2];

	Pgun->gunupdate(gunpos, Velocity2);
	Pgun->Update();

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

	//�����蔻��X�V
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
	//�����̒ǉ�
	collider->SetColor(COLLISION_COLOR_PLAYER);
}

void Player::sethit(int Hit)
{
	hit = Hit;
}
