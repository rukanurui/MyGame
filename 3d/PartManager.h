#pragma once
#include"fbxobj3d.h"
#include"../Collider/SphereCollider.h"
#include"../2d/DebugText.h"

class PartManager : public FBXobj3d
{

public://�����o�֐�

	PartManager();
	//�Փˎ��R�[���o�b�N�֐�
	void OnCollision(const CollisionInfo& info)override;

	//���ʂ̃p�[�e�B�N���̏�����
	void PartInitialize(XMFLOAT3 pos);

	//�e���̏�����
	void BullisticInitialize(XMFLOAT3& pos,XMVECTOR& Vel,XMFLOAT3& angle);

	//���ʂ̃p�[�e�B�N���̍X�V
	void PartUpdate();

	//�e���̍X�V
	void BullisticUpdate();

	const bool& Getdead() { return dead; }

	//�����t���O��setter
	void Setdead(bool flag) { this->dead = flag; }

private:

	XMVECTOR Vel{0.0f,0.0f,0.0f};

	float G = -0.1f;//�d�͉����x

	//�����t���O
	bool dead = false;

	//�o�ߎ���
	float alivecount = 0;

	//�ő厝������
	const float alivelimit = 60;



};

