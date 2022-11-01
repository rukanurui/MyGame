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

	void Enemycol(XMFLOAT3 pos,XMVECTOR vel);

	//�Փˎ��R�[���o�b�N�֐�
	void OnCollision(const CollisionInfo& info)override;


	void colReset();

private:

	XMVECTOR DivVel = { 0.1f,0.1f,0.1f };

	int col = 0;

	float G = -0.1;//�d�͉����x



	DebugText* Debugtext = nullptr;

};

