#pragma once
#include"Pbullet.h"
#include"Camera.h"


class Player : public Camera
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
};

