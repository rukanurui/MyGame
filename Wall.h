#pragma once
#include"3d/fbxobj3d.h"
#include"BoxCollider.h"
#include"CollisionColor.h"

class Wall : public FBXobj3d
{

public:

	Wall();

	void WallInitialize();

	void objgunInitialize();

	//�Փˎ��R�[���o�b�N�֐�
	void OnCollision(const CollisionInfo& info)override;

	//�e�̃t���O
	const int& Gethave() { return infohave; }
	void Sethave(bool Have);

private:

	bool infohave = false;

};