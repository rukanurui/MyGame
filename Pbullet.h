#pragma once
#include "FBXobj3d.h"

class Pbullet : public FBXobj3d
{

public:
	Pbullet();
	/*void Initialize();*/
	void create(const XMFLOAT3& Playerpos,const XMFLOAT3& velocity);
	void bulupdate();
	//void deleate(int flag);
	
	///Getter
	// 座標の取得
	const XMFLOAT3& GetPos() { return position; }
	////回転の取得
	//const XMFLOAT3& GetRoatation() { return rotation; }
	//

	//setter
	//void SetPos(XMFLOAT3 pos);

private:
	
	//速度
	XMFLOAT3 Vel{ 0,0,0 };
	//bool colisionflag;
	//bool areaflag;

};

