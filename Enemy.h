#pragma once
#include"Fbxobj3d.h"
class Enemy : public FBXobj3d
{
public://メンバ関数
	Enemy();
	void EnemyUpdate();

private:
	float Div = 10;

};

