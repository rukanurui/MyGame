#pragma once
#include"Fbxobj3d.h"
class Enemy : public FBXobj3d
{
public://�����o�֐�
	Enemy();
	void EnemyUpdate();

private:
	float Div = 10;

};

