#include"Wall.h"

Wall::Wall() : FBXobj3d()
{

}

void Wall::WallInitialize()
{
	//�����̒ǉ�
	collider->SetColor(COLLISION_COLOR_LANDSHAPE);
}

void Wall::OnCollision(const CollisionInfo& info)
{

}
