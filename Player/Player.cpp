#pragma once
#include "Player.h"
#include"../Collider/QueryCallback.h"
#include"../Collider/CollisionManager.h";
#include"../Collider/BoxCollider.h"


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
	model2 = FbxLoader::GetInstance()->LoadModelFromFile("testfbx");
	gunpix = FbxLoader::GetInstance()->LoadModelFromFile("gunpix");


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
	XMFLOAT3 tag_moved = GetTarget();

	pos_moved.x += move.m128_f32[0];
	pos_moved.y += move.m128_f32[1];
	pos_moved.z += move.m128_f32[2];

	tag_moved.x += move.m128_f32[0];
	tag_moved.y += move.m128_f32[1];
	tag_moved.z += move.m128_f32[2];

	SetPosition(pos_moved);
	SetTarget(tag_moved);
	

}


void Player::PlayerUpdate(const XMFLOAT3& cameratarget)
{

	//�e�������ɓ���������particle�o��
	for (std::unique_ptr<Pbullet>& bullet : bullets)
	{
		if (bullet->Getdead() == true)
		{
			//20�܂�particle����
			for (int i = 0; i < partnum; i++)
			{
				std::unique_ptr<PartManager>newPart = std::make_unique<PartManager>();
				newPart->Initialize();
				newPart->SetScale({ 0.003f,0.003f,0.003f });
				newPart->SetModel(model2);
				newPart->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 0.5f));
				newPart->PartInitialize(bullet->GetPos());

				//particle�̓o�^
				particles.push_back(std::move(newPart));
			}
		}
	}


	//�������e�������ɓ���������particle�o��
	for (std::unique_ptr<PlayerGun>& newgun : Guns)
	{
		if (newgun->Getdead() == true)
		{
			//20�܂�particle����
			for (int i = 0; i < partnum; i++)
			{
				std::unique_ptr<PartManager>newPart = std::make_unique<PartManager>();
				newPart->Initialize();
				newPart->SetScale({ 0.003f,0.003f,0.003f });
				newPart->SetModel(gunpix);
				newPart->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
				newPart->PartInitialize(newgun->GetPos());

				//particle�̓o�^
				particles.push_back(std::move(newPart));
			}
		}
	}


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

	//�E���A�N�V�����̍폜
	/*picks.remove_if([](std::unique_ptr<Pick>& pick) {
		return pick->Getdead();
		});*/

	//particle�̍폜
	particles.remove_if([](std::unique_ptr<PartManager>& part) {
		return part->Getdead();
		});

	UpdateWorld();

	QueryWall();

	//�����蔻��X�V
	if (collider)
	{
		collider->Update();
	}

	ctime--;
	mctime--;
	picktime--;

	if (ctime <= 0)ctime = 0;
	
	if (mctime <= 0)mctime = 0;
	
	if (picktime <= 0)picktime = 0;
	
	if (tutonum>=nowtuto)
	{
		//�e�̔���
		if (input->PushclickLeft() && ctime <= 0 && magazin >= 1 && have == true)
		{
			//�e�̑��x
			const float bulspeed = 1.5f;
			XMVECTOR Velocity{ 0,0,bulspeed };

			Velocity = { cameratarget.x - position.x, cameratarget.y - position.y, cameratarget.z - position.z };

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

		//�e�𓊂���
		if (input->PushclickRight() && have == true)
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
			//�c�e�߂�
			magazin = 5;
			//�t���O�ύX
			have = false;
		}

		//�ߐ�
		if (input->PushclickLeft() && have == false && mctime <= 0)
		{
			//�e�̑��x
			const float bulspeed = 1.0f;
			XMVECTOR Velocity{ 0,0,bulspeed };

			XMFLOAT3 meleepos = position;


			Velocity = { target.x - position.x, target.y - position.y, target.z - position.z };

			Velocity = XMVector3Normalize(Velocity) * bulspeed;

			//�i���̐����Ə�����
			std::unique_ptr<melee>newMelee = std::make_unique<melee>();
			newMelee->Initialize();
			newMelee->SetScale({ 0.01f,0.01f,0.03f });
			newMelee->SetModel(model2);
			newMelee->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
			newMelee->meleeInitialize();
			newMelee->create(position, Velocity);
			//�i���̓o�^
			melees.push_back(std::move(newMelee));
			mctime = 30;
		}

		//�e���E��
		/*
		if (input->TriggerKey(DIK_F) && have == false)
		{
			const float bulspeed = 1.0f;
			XMVECTOR Velocity{ 0,0,bulspeed };

			XMFLOAT3 meleepos = position;


			Velocity = { target.x - position.x, target.y - position.y, target.z - position.z };

			Velocity = XMVector3Normalize(Velocity) * bulspeed;

			//�i���̐����Ə�����
			std::unique_ptr<Pick>newpick = std::make_unique<Pick>();
			newpick->Initialize();
			newpick->SetScale({ 0.01f,0.01f,0.03f });
			newpick->SetModel(model2);
			newpick->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 2.0f));
			newpick->pickInitialize();
			newpick->create(position, Velocity);
			//�i���̓o�^
			picks.push_back(std::move(newpick));
			picktime = 15;
		}*/
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

	//�E���A�N�V�����̍X�V
	/*for (std::unique_ptr<Pick>& pick : picks)
	{
		pick->pickupdate();
		pick->Update();
	}*/

	//particle�̍X�V
	for (std::unique_ptr<PartManager>& part : particles)
	{
		part->PartUpdate();
		part->Update();
	}

	UpdateWorld();
}


void Player::FbxUpdate()
{
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

void Player::PartUpdate()
{
	for (std::unique_ptr<PartManager>& part : particles)
	{
		part->Update();
	}
}

void Player::gunUpdate(const XMFLOAT3& cameratarget,const XMFLOAT3& cameraeye)
{

	XMFLOAT3 angle;

	//�e�̍X�V
	gunpos = cameraeye;

	float cameramatrot = atan2(cameratarget.y,cameratarget.x);

	Velocity2 = { cameratarget.x - cameraeye.x, cameratarget.y - cameraeye.y, cameratarget.z - cameraeye.z };

	Velocity2 = XMVector3Normalize(Velocity2);

	XMVECTOR move = { -2.0f,-2.0f,0,0 };
	//move = XMVector3Transform(move, cameramatrot);

	//���W�ړ�����
	gunpos.x += move.m128_f32[0]; gunpos.y += move.m128_f32[1]; gunpos.z += move.m128_f32[2];

	angle.x = atan2(Velocity2.m128_f32[2], Velocity2.m128_f32[1]);
	angle.y = atan2(Velocity2.m128_f32[0], Velocity2.m128_f32[2]);

	Pgun->gunupdate(gunpos, Velocity2,angle);
	Pgun->Update();

}

void Player::Draw(ID3D12GraphicsCommandList* cmdList)
{

	for (std::unique_ptr<PartManager>& part : particles)
	{
		part->Draw(cmdList);
	}

	for (std::unique_ptr<Pbullet>& bullet : bullets)
	{
		bullet->Draw(cmdList);
	}

	for (std::unique_ptr<melee>& melee : melees)
	{
		melee->Draw(cmdList);
	}

	for (std::unique_ptr<PlayerGun>& gun : Guns)
	{
		gun->Draw(cmdList);
	}

	if (have == true)
	{
		Pgun->Draw(cmdList);
	}

}


void Player::OnCollision(const CollisionInfo& info)
{
	if (info.collider->color == 8 || info.collider->color == 16)
	{
		hit = true;
	}

	if (info.collider->color == 1)
	{
		wallhit = true;

		QueryWall();
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

void Player::Sethave(bool Have)
{
	have = Have;
}

void Player::ColInitialize()
{
	//�����̒ǉ�
	collider->SetColor(COLLISION_COLOR_PLAYER);
}

void Player::QueryWall()
{
	//���R���C�_�[�擾
	SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collider);
	assert(sphereCollider);


	class PlayerQueryCallback :public QueryCallback
	{
	public:
		PlayerQueryCallback(Sphere* sphere) :sphere(sphere) {};

		//�Փˎ��R�[���o�b�N�֐�
		bool OnQueryHit(const QueryHit& info)
		{
			//���[���h�̏����
			const XMVECTOR up = { 0,1,0,0 };
			//�r�˕���
			XMVECTOR rejectDir = XMVector3Normalize(info.reject);
			//������ƍ��E�����̊p�x���̃R�T�C���l
			float cos = XMVector3Dot(rejectDir, up).m128_f32[0];

			//�����o������
			sphere->center += info.reject;
			move += info.reject;

			return true;
		}

		//�N�G���\�Ɏg�p���鋅
		Sphere* sphere = nullptr;
		//�r�˂ɂ��ړ���(�ݐ�)
		XMVECTOR move = {};
	};

	//�N�G���\�R�[���o�b�N�̊֐��I�u�W�F�N�g
	PlayerQueryCallback callback(sphereCollider);

	//�v���C���[�ƕǂ̌���������
	CollisionManager::GetInstance()->CheckQueryBox(*sphereCollider, &callback, COLLISION_COLOR_LANDSHAPE);
	//�����ɂ��r�˕�������
	position.x += callback.move.m128_f32[0];
	//position.y += callback.move.m128_f32[1] * 0.15f;
	position.z += callback.move.m128_f32[2];

	UpdateWorld();
}

