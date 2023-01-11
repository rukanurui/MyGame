#pragma once
#include"Pbullet.h"
#include"melee.h"
#include"PlayerGun.h"
#include"3d/fbxobj3d.h"
#include"SphereCollider.h"
#include "3d/FbxLoader.h"
#include "3d/Modelfbx.h"
#include <memory>
#include <list>

class Player : public FBXobj3d
	//public Camera
{

public://�����o�֐�
	Player();
	//������
	void PlayerInitialize(Input*Input);
	//�X�V
	void PlayerUpdate();
	void BulUpdate();
	void meleeUpdate();
	void throwgunUpdate();
	void gunUpdate();
	

	/// �����_���W�̎擾
	const XMFLOAT3& GetTarget() { return target; }

	void MoveVector(const XMVECTOR& move);

	/// �����_���W�̐ݒ�
	void SetTarget(XMFLOAT3 target);

	void SetoldTarget(XMFLOAT3 target);
	
	void Setoldpos(XMFLOAT3 Oldpos);

	void Sethave(bool have);

	void OnCollision(const CollisionInfo& info);

	void colUpdate();

	void ColInitialize();

	const int& Gethit() { return hit; }

	const int& Getwallhit() { return wallhit; }


	void sethit(int Hit);

	int hit = 0;

	int wallhit = 0;

	void BulDraw(ID3D12GraphicsCommandList* cmdList);

	void meleeDraw(ID3D12GraphicsCommandList* cmdList);

	void throwgunDraw(ID3D12GraphicsCommandList* cmdList);

	void gunDraw(ID3D12GraphicsCommandList* cmdList);

	


private://�����o�ϐ�
	//�|�C���^
	Input* input = nullptr;
	FbxModel* modelballet = nullptr;
	FbxModel* modelgun = nullptr;

	//�e�{��
	std::unique_ptr<PlayerGun> Pgun;

	//������Ƃ��ɐ��������e
	std::list<std::unique_ptr<PlayerGun>> Guns;


	std::list<std::unique_ptr<Pbullet>> bullets;
	std::list<std::unique_ptr<melee>> melees;

	//�����_
	XMFLOAT3 target{ 0.0f,4.0f,0.0f };
	//�����_�܂ł̂����
	float distance = 5.0f;

	//�����Ă���e�̏ꏊ����(�E��)
	float gundistance;

	//�U���֘A
	//����������Ă��邩
	bool have = true;
	//�c�e
	int magazin = 5;
	//�e�̃N�[���^�C��
	int ctime = 0;

	//�i���̃N�[���^�C��
	int mctime = 0;

	XMFLOAT3 oldpos;
	XMFLOAT3 oldtarget;
};

