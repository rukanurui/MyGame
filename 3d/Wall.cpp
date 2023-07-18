#include"Wall.h"

Wall::Wall() : FBXobj3d()
{

}

void Wall::WallInitialize()
{
	//‘®«‚Ì’Ç‰Á
	collider->SetColor(COLLISION_COLOR_LANDSHAPE);
}

void Wall::objgunInitialize()
{
	//‘®«‚Ì’Ç‰Á
	collider->SetColor(COLLISION_COLOR_OBJGUN);
}

void Wall::OnCollision(const CollisionInfo& info)
{
	
	if (collider->color== 64 && (info.collider->color == 4 || info.collider->color == 2))
	{
		scale.x = 0, scale.y = 0, scale.z = 0;

		if (infohave == false)
		{
			infohave = true;
		}
	}

}

void Wall::Sethave(bool Have)
{

	infohave = Have;

}
