#pragma once
#include"3d/fbxobj3d.h"

class Pbullet 
: public FBXobj3d
{

public:
	Pbullet();
	/*void Initialize();*/
	void create(const XMFLOAT3& Playerpos,const XMFLOAT3& velocity);
	void bulupdate();
	//void deleate(int flag);
	
	///Getter
	// À•W‚Ìæ“¾
	const XMFLOAT3& GetPos(){ return position; }
	////‰ñ“]‚Ìæ“¾
	//const XMFLOAT3& GetRoatation() { return rotation; }
	//

	//setter
	//void SetPos(XMFLOAT3 pos);

private:
	
	//‘¬“x
	XMFLOAT3 Vel={ 0,0,0 };
	//bool colisionflag;
	//bool areaflag;

};

