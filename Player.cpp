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
	//�����̒ǉ�
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

	// �X�P�[���A��]�A���s�ړ��s��̌v�Z
	matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));
	matRot *= XMMatrixRotationX(XMConvertToRadians(rotation.x));
	matRot *= XMMatrixRotationY(XMConvertToRadians(rotation.y));
	matTrans = XMMatrixTranslation(position.x, position.y, position.z);

	// ���[���h�s��̍���
	matWorld = XMMatrixIdentity(); // �ό`�����Z�b�g
	matWorld *= matScale; // ���[���h�s��ɃX�P�[�����O�𔽉f
	matWorld *= matRot; // ���[���h�s��ɉ�]�𔽉f
	matWorld *= matTrans; // ���[���h�s��ɕ��s�ړ��𔽉f

	const XMMATRIX& matViewProjection =
		camera->GetViewProjectionMatrix();

	//�J�������W
	const XMFLOAT3& camerapos = camera->GetEye();

	//�����蔻��X�V
	if (collider)
	{
		collider->Update();
	}


	if (input->TriggerKey(DIK_SPACE))
	{
		//�e�̑��x
		const float bulspeed = 1.5f;
		XMVECTOR Velocity{ 0,0,bulspeed };

		Velocity={ target.x - position.x, target.y - position.y, target.z - position.z };
		//Velocity = { target.x - eye.x, target.y - eye.y, target.z - eye.z };

		Velocity = XMVector3Normalize(Velocity) * bulspeed;

		//�e�̐����Ə�����
		bullet->create(position, Velocity);
	}

	//�e�̍X�V
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
	
	// �X�P�[���A��]�A���s�ړ��s��̌v�Z
	matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));
	matRot *= XMMatrixRotationX(XMConvertToRadians(rotation.x));
	matRot *= XMMatrixRotationY(XMConvertToRadians(rotation.y));
	matTrans = XMMatrixTranslation(position.x, position.y, position.z);

	// ���[���h�s��̍���
	matWorld = XMMatrixIdentity(); // �ό`�����Z�b�g
	matWorld *= matScale; // ���[���h�s��ɃX�P�[�����O�𔽉f
	matWorld *= matRot; // ���[���h�s��ɉ�]�𔽉f
	matWorld *= matTrans; // ���[���h�s��ɕ��s�ړ��𔽉f

	const XMMATRIX& matViewProjection =
		camera->GetViewProjectionMatrix();
	
	//�J�������W
	const XMFLOAT3& camerapos = camera->GetEye();

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
