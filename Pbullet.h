#pragma once
#include"3d/fbxobj3d.h"
#include"SphereCollider.h"


class Pbullet 
: public FBXobj3d 
{

public:
	Pbullet();
	/*void Initialize();*/
	void create(const XMFLOAT3& Playerpos,const XMVECTOR& velocity);
	void bulupdate();
	//void deleate(int flag);
	
	///Getter
	// 座標の取得
	//const XMFLOAT3& GetPos(){ return position; }
	////回転の取得
	//const XMFLOAT3& GetRoatation() { return rotation; }
	//

	//setter
	//void SetPos(XMFLOAT3 pos);

	//衝突時コールバック関数
	void OnCollision(const CollisionInfo& info)override;


private:
	
	//速度
	XMVECTOR Vel={ 0,0,0 };
	//bool colisionflag;
	//bool areaflag;

	int aliveflag = 0;

};

