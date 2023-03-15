#pragma once
#include"Pbullet.h"
#include"melee.h"
#include"PlayerGun.h"
#include"../3d/fbxobj3d.h"
#include"../Collider/SphereCollider.h"
#include "../3d/FbxLoader.h"
#include "../3d/Modelfbx.h"
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

	void OnCollision(const CollisionInfo& info);

	void colUpdate();

	void ColInitialize();

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

	const float gundistance = 1.5f;
	const float gunTdistance = 0.5;
	XMFLOAT3 guntarget{};
	XMFLOAT3 gunpos;
	XMVECTOR Velocity2{ -gundistance,-gundistance,gundistance };
	

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
