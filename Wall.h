#pragma once
#include"3d/fbxobj3d.h"
#include"BoxCollider.h"
#include"CollisionColor.h"

class Wall : public FBXobj3d
{

public:

	Wall();

	void WallInitialize();

	//�Փˎ��R�[���o�b�N�֐�
	void OnCollision(const CollisionInfo& info)override;

};