#pragma once
#include"3d/fbxobj3d.h"
#include"SphereCollider.h"
#include"DebugText.h"

class Enemy : public FBXobj3d
{
public://�����o�֐�
	Enemy();

	void EnemyInitialize();

	void EnemyUpdate();

	void Enemycol(XMFLOAT3 pos,XMVECTOR vel);

	//�Փˎ��R�[���o�b�N�֐�
	void OnCollision(const CollisionInfo& info)override;


	void colReset();

	void move();

private:

	XMVECTOR DivVel = { 0.1f,0.1f,0.1f };

	int col = 0;

	float G = -0.1;//�d�͉����x

	XMVECTOR Vel = { 0,0,0 };



	DebugText* Debugtext = nullptr;

};

