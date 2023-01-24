#include"Wall.h"

Wall::Wall() : FBXobj3d()
{

}

void Wall::WallInitialize()
{
	//属性の追加
	collider->SetColor(COLLISION_COLOR_LANDSHAPE);
}

void Wall::objgunInitialize()
{
	//属性の追加
	collider->SetColor(COLLISION_COLOR_OBJGUN);
}

void Wall::OnCollision(const CollisionInfo& info)
{
	
	if (collider->color==32&&info.collider->color==4)
	{
		scale.x = 0, scale.y = 0, scale.z = 0;

		if (infohave == false)
		{
			infohave = true;
		}
	}

	

}
