#pragma once
#include"Pbullet.h"
#include"melee.h"
#include"PlayerGun.h"
#include"../3d/fbxobj3d.h"
#include"../Collider/SphereCollider.h"
#include "../3d/FbxLoader.h"
#include "../3d/Modelfbx.h"
#include"../3d/PartManager.h"
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
	void PlayerUpdate(const XMFLOAT3& cameratarget);

	void BulUpdate();
	void meleeUpdate();
	void throwgunUpdate();
	void gunUpdate(const XMFLOAT3& cameratarget, const XMFLOAT3& cameraeye);
	

	/// �����_���W�̎擾
	const XMFLOAT3& GetTarget() { return target; }

	//�ړ����x�̎擾
	const XMFLOAT3& GetVelocity() { return Velocity; }

	void MoveVector(const XMVECTOR& move);

	/// �����_���W�̐ݒ�
	void SetTarget(XMFLOAT3 target);

	void SetoldTarget(XMFLOAT3 target);
	
	void Setoldpos(XMFLOAT3 Oldpos);

	//�e�̃t���O�̃Q�b�^�[�ƃZ�b�^�[
	const int& Gethave() { return have; }
	void Sethave(bool Have);

	//�c�e���̃Q�b�^�[
	const int& Getmagazin() { return magazin; }
	//�c�e���̃Z�b�^�[
	void SetMagazin(int Magazin) { this->magazin = Magazin; }

	//collider�֘A
	void OnCollision(const CollisionInfo& info);
	void colUpdate();
	void ColInitialize();
	//�ǂƂ̔r�ˏ���
	void QueryWall();
	void Setwallflag(bool flag) { this->wallhit = flag; }


	//hit�̃Q�b�^�[
	const int& Gethit() { return hit; }

	const int& Getwallhit() { return wallhit; }

	void sethit(int Hit);

	int hit = 0;

	int wallhit = 0;

	//�`��
	void BulDraw(ID3D12GraphicsCommandList* cmdList);

	void meleeDraw(ID3D12GraphicsCommandList* cmdList);

	void throwgunDraw(ID3D12GraphicsCommandList* cmdList);

	void gunDraw(ID3D12GraphicsCommandList* cmdList);

	


private://�����o�ϐ�
	//�|�C���^
	Input* input = nullptr;
	FbxModel* modelballet = nullptr;
	FbxModel* modelgun = nullptr;
	FbxModel* model2 = nullptr;

	//�e�{��
	std::unique_ptr<PlayerGun> Pgun;

	//������Ƃ��ɐ��������e
	std::list<std::unique_ptr<PlayerGun>> Guns;
	//�e
	std::list<std::unique_ptr<Pbullet>> bullets;
	//�i��
	std::list<std::unique_ptr<melee>> melees;
	//�p�[�e�B�N��
	std::list<std::unique_ptr<PartManager>> particle;

	//�p�[�e�B�N���̐�
	const int partnum = 20;

	//�p�[�e�B�N���̐��J�E���g
	int partcount = 0;
	int parttimer = 0;

	//�����_
	XMFLOAT3 target{ 0.0f,4.0f,0.0f };
	//�����_�܂ł̂����
	float distance = 5.0f;

	//�����Ă���e�̏ꏊ����(�E��)
	const float gundistance = 1.5f;
	const float gunTdistance = 0.5;
	XMFLOAT3 guntarget{};
	XMFLOAT3 gunpos;
	XMFLOAT3 Velocity{};
	XMVECTOR Velocity2{ -gundistance,-gundistance,gundistance };

	XMFLOAT3 currentangle;
	

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

