#pragma once
#include "Player.h"
#include"QueryCallback.h"
#include"CollisionManager.h";


Player::Player(Pbullet* bullet):FBXobj3d()
{
	this->bullet = bullet;
};

void Player::PlayerInitialize(Input* Input)
{
	assert(Input);
	this->input = Input;
	//属性の追加
	collider->SetColor(COLLISION_COLOR_PLAYER);
	
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

	

	HRESULT result;

	// スケール、回転、平行移動行列の計算
	matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));
	matRot *= XMMatrixRotationX(XMConvertToRadians(rotation.x));
	matRot *= XMMatrixRotationY(XMConvertToRadians(rotation.y));
	matTrans = XMMatrixTranslation(position.x, position.y, position.z);

	// ワールド行列の合成
	matWorld = XMMatrixIdentity(); // 変形をリセット
	matWorld *= matScale; // ワールド行列にスケーリングを反映
	matWorld *= matRot; // ワールド行列に回転を反映
	matWorld *= matTrans; // ワールド行列に平行移動を反映

	const XMMATRIX& matViewProjection =
		camera->GetViewProjectionMatrix();

	//カメラ座標
	const XMFLOAT3& camerapos = camera->GetEye();

	//当たり判定更新
	if (collider)
	{
		collider->Update();
	}


	if (input->TriggerKey(DIK_SPACE))
	{
		//弾の速度
		const float bulspeed = 1.5f;
		XMVECTOR Velocity{ 0,0,bulspeed };

		Velocity={ target.x - position.x, target.y - position.y, target.z - position.z };
		//Velocity = { target.x - eye.x, target.y - eye.y, target.z - eye.z };

		Velocity = XMVector3Normalize(Velocity) * bulspeed;

		//弾の生成と初期化
		bullet->create(position, Velocity);
	}

	//弾の更新
	if (bullet)
	{
		bullet->bulupdate();
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


	HRESULT result;
	
	// スケール、回転、平行移動行列の計算
	matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));
	matRot *= XMMatrixRotationX(XMConvertToRadians(rotation.x));
	matRot *= XMMatrixRotationY(XMConvertToRadians(rotation.y));
	matTrans = XMMatrixTranslation(position.x, position.y, position.z);

	// ワールド行列の合成
	matWorld = XMMatrixIdentity(); // 変形をリセット
	matWorld *= matScale; // ワールド行列にスケーリングを反映
	matWorld *= matRot; // ワールド行列に回転を反映
	matWorld *= matTrans; // ワールド行列に平行移動を反映

	const XMMATRIX& matViewProjection =
		camera->GetViewProjectionMatrix();
	
	//カメラ座標
	const XMFLOAT3& camerapos = camera->GetEye();

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
