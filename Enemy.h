#pragma once
#include"3d/fbxobj3d.h"
#include"SphereCollider.h"
#include"DebugText.h"

class Enemy : public FBXobj3d
{
public://�����o�֐�
	Enemy();

	bool EnemyInitialize();

	void EnemyUpdate();

	//�Փˎ��R�[���o�b�N�֐�
	void OnCollision(const CollisionInfo& info)override;

private:

	float Div = 10;
	XMVECTOR DivVel = { 0.1f,0.1f,0.1f };



	DebugText* Debugtext = nullptr;

};

