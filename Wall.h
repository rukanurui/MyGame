#pragma once
#include"3d/fbxobj3d.h"
#include"BoxCollider.h"

class Wall : public FBXobj3d
{

public:

	Wall();

	//�Փˎ��R�[���o�b�N�֐�
	void OnCollision(const CollisionInfo& info)override;

};