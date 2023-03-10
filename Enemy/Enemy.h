#pragma once
#include"../3d/fbxobj3d.h"
#include "../3d/FbxLoader.h"
#include "../3d/Modelfbx.h"
#include"../Collider/SphereCollider.h"

#include <memory>
#include <list>

#include"EnemyBullet.h"
#include"PartEnemy.h"

class Enemy : public FBXobj3d
{
public://�����o�֐�
	Enemy();

	void EnemyInitialize(bool Shot);

	//
	void EnemyUpdate(XMFLOAT3 playerpos);

	//�U������
	void Attack(XMFLOAT3 playerpos);

	//�Փˎ��R�[���o�b�N�֐�
	void OnCollision(const CollisionInfo& info)override;

	//�����蔻�胊�Z�b�g
	void colReset();
	//�����蔻��Z�b�g
	void setcol(bool Col);
	const bool& getcol() { return col; }
	const bool& getdeath() { return death; }

	void move();

	//�e�֘A����
	void BulUpdate();

	void BulDraw(ID3D12GraphicsCommandList* cmdList);

	//particle�֘A����
	void PartUpdate();

	void PartDraw(ID3D12GraphicsCommandList* cmdList);

	const int die = 1;

private:

	//�|�C���^
	FbxModel* modelballet = nullptr;
	FbxModel* model2 = nullptr;
	//Enemybullet* bullet=nullptr;
	std::list<std::unique_ptr<Enemybullet>> bullets;
	std::list<std::unique_ptr<PartEnemy>> particle;
	
	//bool�ɕύX����
	//�����������̃t���O
	bool col = false;
	bool death = false;

	//�p�[�e�B�N���̐�
	const int partnum = 20;

	//�p�[�e�B�N���̐��J�E���g
	int partcount = 0;
	int parttimer = 0;



	float G = -0.1;//�d�͉����x

	XMVECTOR Vel = { 0,0,0 };

	XMVECTOR Playerpos;

	XMVECTOR Vecpos;

	//�e��łG���ǂ���
	bool Shot;

	//�e�̃N�[���^�C��
	float count=0;

	

};

