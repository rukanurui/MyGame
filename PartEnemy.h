#pragma once
#include"3d/fbxobj3d.h"
#include"SphereCollider.h"
#include"DebugText.h"

class PartEnemy : public FBXobj3d
{

public://�����o�֐�

	PartEnemy();
	//�Փˎ��R�[���o�b�N�֐�
	void OnCollision(const CollisionInfo& info)override;

	void PartInitialize();

	void PartUpdate();


private:

private:

	XMVECTOR Vel{0.0f,0.0f,0.0f};

	int col = 0;

	float G = -0.1;//�d�͉����x



};

