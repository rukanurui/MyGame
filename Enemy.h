#pragma once
#include"3d/fbxobj3d.h"
#include"SphereCollider.h"


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

};

