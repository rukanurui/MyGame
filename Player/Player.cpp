#pragma once
#include "Player.h"
#include"../Collider/QueryCallback.h"
#include"../Collider/CollisionManager.h";


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
	newGun->staycreate(position);
	//銃の登録
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

	//座標の操作

	/*if (!input->PushKey(DIK_W) && !input->PushKey(DIK_S)) Velocity.z = 0;

	if (!input->PushKey(DIK_A) && !input->PushKey(DIK_D)) Velocity.x = 0;

	if (input->PushKey(DIK_A) || input->PushKey(DIK_D))
	{

		if (input->PushKey(DIK_A)) Velocity.x = -0.1f;
		else
		{
			if (input->PushKey(DIK_D)) Velocity.x = 0.1f;
		}


		XMVECTOR move = { Velocity.x,Velocity.y,0,0 };

		move = XMVector3Transform(move, matRot);
		MoveVector(move);

	}

	if (input->PushKey(DIK_W) || input->PushKey(DIK_S))
	{
		if (input->PushKey(DIK_S)) Velocity.z = -0.1f;
		else
		{
			if (input->PushKey(DIK_W)) Velocity.z = 0.1f;
		}

		XMVECTOR move = { 0,0,Velocity.z,0 };

		move = XMVector3Transform(move, matRot);
		MoveVector(move);

	}*/

	UpdateWorld();


	//弾の発射
	if (input->PushclickLeft() && ctime <= 0 && magazin >= 1 && have == true)
	{
		//弾の速度
		const float bulspeed = 1.5f;
		XMVECTOR Velocity{ 0,0,bulspeed };

		Velocity={ cameratarget.x - position.x, cameratarget.y - position.y, cameratarget.z - position.z };

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
	//銃を投げる
	if (input->PushclickRight() && have==true)
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
		//残弾戻す
		magazin=5;
		//フラグ変更
		have = false;
	}
	//近接
	if (input->PushclickLeft() && have==false&&mctime<=0)
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

	UpdateWorld();
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

void Player::gunUpdate(const XMFLOAT3& cameratarget,const XMFLOAT3& cameraeye)
{

	XMFLOAT3 angle;

	//銃の更新
	gunpos = cameraeye;

	float cameramatrot = atan2(cameratarget.y,cameratarget.x);

	Velocity2 = { cameratarget.x - cameraeye.x, cameratarget.y - cameraeye.y, cameratarget.z - cameraeye.z };

	Velocity2 = XMVector3Normalize(Velocity2);

	XMVECTOR move = { -2.0f,-2.0f,0,0 };
	//move = XMVector3Transform(move, cameramatrot);

	//座標移動処理
	gunpos.x += move.m128_f32[0]; gunpos.y += move.m128_f32[1]; gunpos.z += move.m128_f32[2];

	angle.x = atan2(Velocity2.m128_f32[2], Velocity2.m128_f32[1]);
	angle.y = atan2(Velocity2.m128_f32[0], Velocity2.m128_f32[2]);

	Pgun->gunupdate(gunpos, Velocity2,angle);
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
		/*position = oldpos;
		target = oldtarget;*/
		//球コライダー取得
		SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collider);
		assert(sphereCollider);

		class PlayerQueryCallback :public QueryCallback
		{
		public:
			PlayerQueryCallback(Sphere* sphere) :sphere(sphere) {};

			//衝突時コールバック関数
			bool OnQueryHit(const QueryHit& info)
			{
				//ワールドの上方向
				const XMVECTOR up = { 0,1,0,0 };
				//排斥方向
				XMVECTOR rejectDir = XMVector3Normalize(info.reject);
				//上方向と左右方向の角度差のコサイン値
				float cos = XMVector3Dot(rejectDir, up).m128_f32[0];

				//押し出し処理
				sphere->center += info.reject;
				move += info.reject;

				return true;
			}

			//クエリ―に使用する球
			Sphere* sphere = nullptr;
			//排斥による移動量(累積)
			XMVECTOR move = {};
		};

		//クエリ―コールバックの関数オブジェクト
		PlayerQueryCallback callback(sphereCollider);

		//敵と壁の交差を検索
		CollisionManager::GetInstance()->CheckQueryBox(*sphereCollider, &callback, COLLISION_COLOR_LANDSHAPE);
		//交差による排斥分動かす
		position.x += callback.move.m128_f32[0];
		//position.y += callback.move.m128_f32[1] * 0.15f;
		position.z += callback.move.m128_f32[2];
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

void Player::Sethave(bool Have)
{
	have = Have;
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
