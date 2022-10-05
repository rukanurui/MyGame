#include "Pbullet.h"

void Pbullet::Initialize(FbxModel*model)
{
	modelballet = FbxLoader::GetInstance()->LoadModelFromFile("bullet");
}

void Pbullet::create(FbxModel* model,const XMFLOAT3& Playerpos, const XMFLOAT3& velocity)
{
	assert(model);
	modelballet = model;
	modelballet = FbxLoader::GetInstance()->LoadModelFromFile("bullet");
	ballet = new FBXobj3d;
	ballet->Initialize();
	ballet->SetPosition({ 0.0f,5.0f,0.0f });
	ballet->SetModel(modelballet);

	pos = Playerpos;
	Vel = velocity;
}

void Pbullet::update()
{
	ballet->Update();
	pos.z += Vel.z;

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
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	ballet->Draw()
}
