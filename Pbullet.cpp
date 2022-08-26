#include "Pbullet.h"

void Pbullet::create(XMFLOAT3 bulpos,int flag)
{
	pos = bulpos;
	flag = 1;
}

void Pbullet::update()
{
	pos.z += 0.1f;
}

void Pbullet::deleate(int flag)
{
	if (pos.z=20)
	{
		flag = 0;
	}
}

void Pbullet::draw()
{
	
}
