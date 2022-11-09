#include "Enemy.h"
#include <time.h>



Enemy::Enemy() : FBXobj3d()
{
}

//Enemy* Enemy::Create()
//{
//	//3Dオブジェクトのインスタンスを生成
//	Enemy* instance = new Enemy();
//	if (instance == nullptr) {
//		return nullptr;
//	}
//
//	// 初期化
//	if (!instance->Initialize()) {
//		delete instance;
//		assert(0);
//	}
//	return instance;
//}

void Enemy::EnemyInitialize()
{
	//属性の追加
	collider->SetColor(COLLISION_COLOR_ENEMY);
}

void Enemy::EnemyUpdate()
{

	

	//当たり判定更新
	if (collider)
	{
		collider->Update();
	}
}

void Enemy::Enemycol(XMFLOAT3 pos,XMVECTOR vel)
{

	if (col==0)
	{
		
		position = pos;

		DivVel = vel;

		G = 0.01f;

		col = 1;
	}
	
}


void Enemy::OnCollision(const CollisionInfo& info)
{


	if (scale.x >= 0.01f)
	{
		scale.x = 0.005f; scale.y = 0.005f; scale.z = 0.005f;
	}


	HRESULT result;
	XMMATRIX matScale, matRot, matTrans;

	// スケール、回転、平行移動行列の計算
	matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));
	matRot *= XMMatrixRotationX(XMConvertToRadians(rotation.x));
	matRot *= XMMatrixRotationY(XMConvertToRadians(rotation.y));
	matTrans = XMMatrixTranslation(position.x, position.y, position.z);

	// ワールド行列の合成
	matWorld = XMMatrixIdentity(); // 変形をリセット
	matWorld *= matScale; // ワールド行列にスケーリングを反映
	matWorld *= matRot; // ワールド行列に回転を反映
	matWorld *= matTrans; // ワールド行列に平行移動を反映

	//こっからカメラ
	//ビュープロジェクション行列
	const XMMATRIX& matViewProjection =
		camera->GetViewProjectionMatrix();
	//モデルのメッシュトランスフォーム
	const XMMATRIX& modelTransform = fbxmodel->GetModelTransform();
	//カメラ座標
	const XMFLOAT3& camerapos = camera->GetEye();

	//アニメーション
	if (isPlay) {
		//1フレーム進める
		currentTime += frameTime;
		//最後まで再生したら先頭に戻す
		if (currentTime > endTime) {
			currentTime = startTime;
		}
	}

	//ボーン配列
	std::vector<FbxModel::Bone>& bones = fbxmodel->GetBones();

	// スキンの定数バッファへデータ転送
	ConstBufferDataSkin* constMapSkin = nullptr;
	result = constBuffSkin->Map(0, nullptr, (void**)&constMapSkin);
	for (int i = 0; i < bones.size(); i++)
	{
		//今の姿勢行列
		XMMATRIX matCurrentPose;
		//今の姿勢行列を取得
		FbxAMatrix fbxCurrentPose =
			bones[i].fbxCluster->GetLink()->EvaluateGlobalTransform(currentTime);
		//XMMATRIXに変換
		FbxLoader::ConvertMatrixFromFbx(&matCurrentPose, fbxCurrentPose);
		//合成してスキニング行列に
		constMapSkin->bones[i] = bones[i].invInitialPose * matCurrentPose;
	}
	constBuffSkin->Unmap(0, nullptr);

	//定数バッファへデータ転送
	ConstBufferDataTransform* constMap = nullptr;
	result = constBufferTransform->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result))
	{
		constMap->viewproj = matViewProjection;
		constMap->world = modelTransform * matWorld;
		constMap->camerapos = camerapos;
		constBufferTransform->Unmap(0, nullptr);
	}

	//当たり判定更新
	if (collider)
	{
		collider->Update();
	}
}



void Enemy::colReset()
{
	col = 0;
}


void Enemy::move()
{

}
;


