#pragma once
#include"../3d/fbxobj3d.h"
#include "../3d/FbxLoader.h"
#include "../3d/Modelfbx.h"
#include"../Collider/SphereCollider.h"

#include <memory>
#include <list>

#include"EnemyBullet.h"
#include"../3d/PartManager.h"
#include "../2d/Partmanager2d.h"
#include"../Engine/DXCommon.h"



class Enemy : public FBXobj3d
{
public://�����o�֐�
	Enemy();

	void EnemyInitialize(bool Shot, Camera* camera,DXCommon* dxcommon);

	void SetModelNum(int &num) { this->modelnum = num; }

	//�G�ŗL����
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
	void BullisticUpdate();

	void CreateParticles(XMFLOAT3 Pos);

	void PartDraw(ID3D12GraphicsCommandList* cmdList);
	void PartDraw2d(ID3D12GraphicsCommandList* cmdList);
	void BullisticDraw(ID3D12GraphicsCommandList* cmdList);

	void LastUpdate();

	const int & getbulnum() { return bulnum; }

	const bool die = true;

private:

	//�|�C���^
	FbxModel* modelballet = nullptr;
	FbxModel* modelenemy = nullptr;
	FbxModel* modelbullistic = nullptr;
	WindowsApp* Windows = nullptr;
	DXCommon* dxCommon = nullptr;
	ParticleManager2d* particle2d = nullptr;
	
	
	//���X�g
	std::list<std::unique_ptr<Enemybullet>> bullets;
	std::list<std::unique_ptr<PartManager>> particle;
	//�e��
	std::list<std::unique_ptr<PartManager>> bullistic;
	//std::list<std::unique_ptr<ParticleManager2d>> particle2d;
	
	//���f���̔ԍ�
	int modelnum = 0;

	//�����������̃t���O
	bool col = false;
	bool death = false;

	XMVECTOR Velocity2{};

	//�p�[�e�B�N���̐�
	const int partnum = 20;

	//�p�[�e�B�N���̐��J�E���g
	int partcount = 0;
	int parttimer = 0;

	bool partflag = false;

	//�e�̐��J�E���g
	int bulnum = 0;


	float G = -0.1;//�d�͉����x

	XMVECTOR Vel = { 0,0,0 };

	XMVECTOR Playerpos;

	XMVECTOR Vecpos;

	//�e��łG���ǂ���
	bool Shot;

	//�e�̃N�[���^�C��
	float count=0;

	

};

