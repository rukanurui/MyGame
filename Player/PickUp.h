#pragma once
#include"../3d/fbxobj3d.h"
#include"../Collider/SphereCollider.h"

class Pick
	: public FBXobj3d
{

public:
	Pick();
	void pickInitialize();
	void create(const XMFLOAT3& Playerpos, const XMVECTOR& velocity);
	void pickupdate();


	//�Փˎ��R�[���o�b�N�֐�
	void OnCollision(const CollisionInfo& info)override;
	const bool& Getdead() { return dead; }
	const bool& Getpick() { return pickflag; }

private:

	//���x
	XMVECTOR Vel = { 0,0,0 };

	//����
	static const int32_t ktime = 15;
	//�^�C�}�[
	int32_t timer = ktime;

	//�Փ˃t���O
	bool dead = false;
	//�E�������̃t���O
	bool pickflag = false;


};

