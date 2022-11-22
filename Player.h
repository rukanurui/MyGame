#pragma once
#include"Pbullet.h"
#include"3d/fbxobj3d.h"


class Player : public FBXobj3d
{

public://�����o�֐�
	Player(Pbullet* bullet);
	//������
	void PlayerInitialize(Input*Input);
	//�X�V
	void PlayerUpdate();
	//�U������
	void Shot();



private://�����o�ϐ�
	Input* input = nullptr;
	//Pbullet* bullet = nullptr;
	Pbullet*bullet;
	XMFLOAT3 target{ 0,0,0 };
	float distance = 5;
};

