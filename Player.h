#pragma once
#include"Pbullet.h"
#include"3d/fbxobj3d.h"
#include"SphereCollider.h"

class Player : public FBXobj3d
	//public Camera
{

public://�����o�֐�
	Player(Pbullet* bullet);
	//������
	void PlayerInitialize(Input*Input);
	//�X�V
	void PlayerUpdate();
	
	//�U������
	void Shot();

	/// �����_���W�̎擾
	const XMFLOAT3& GetTarget() { return target; }

	void MoveVector(const XMVECTOR& move);

	/// �����_���W�̐ݒ�
	void SetTarget(XMFLOAT3 target);

	void SetoldTarget(XMFLOAT3 target);
	
	void Setoldpos(XMFLOAT3 Oldpos);

	void OnCollision(const CollisionInfo& info);

	void colUpdate();

	void ColInitialize();

	const int& Gethit() { return hit; }

	const int& Getwallhit() { return wallhit; }

	void sethit(int Hit);

	int hit = 0;

	int wallhit = 0;

	


private://�����o�ϐ�
	Input* input = nullptr;
	//Pbullet* bullet = nullptr;
	Pbullet*bullet;
	XMFLOAT3 target{ 0,4,0 };
	float distance = 5.0f;

	XMFLOAT3 oldpos;
	XMFLOAT3 oldtarget;
};

