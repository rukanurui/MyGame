#pragma once
#include"3d/fbxobj3d.h"
#include "3d/FbxLoader.h"
#include "3d/Modelfbx.h"
#include"SphereCollider.h"


#include"EnemyBullet.h"

class Enemy : public FBXobj3d
{
public://�����o�֐�
	Enemy();

	void EnemyInitialize(bool Shot);

	void EnemyUpdate(XMFLOAT3 playerpos);

	void Attack(XMFLOAT3 playerpos);

	//�Փˎ��R�[���o�b�N�֐�
	void OnCollision(const CollisionInfo& info)override;


	void colReset();

	void move();

	void BulDraw(ID3D12GraphicsCommandList* cmdList);

private:

	//�|�C���^
	FbxModel* modelballet = nullptr;
	Enemybullet* bullet=nullptr;
	
	int col = 0;

	float G = -0.1;//�d�͉����x

	XMVECTOR Vel = { 0,0,0 };

	XMVECTOR Playerpos;

	XMVECTOR Vecpos;

	//�e��łG���ǂ���
	bool Shot;

	//�e�̃N�[���^�C��
	float count=0;

	

};

