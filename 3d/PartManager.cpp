#include "PartManager.h"
#include"../Collider/QueryCallback.h"
#include "../Collider/CollisionManager.h"

PartManager::PartManager()
{
}

void PartManager::PartInitialize(XMFLOAT3 pos)
{

	position = pos;

	srand(rand());
	int pcount = rand() % 10 + 1;

	Vel.m128_f32[0] = (float)rand() / RAND_MAX;
	Vel.m128_f32[1] = (float)rand() / RAND_MAX;
	Vel.m128_f32[2] = (float)rand() / RAND_MAX;

	//方向を設定
	if (pcount >= 4)
	{
		Vel.m128_f32[0] *= -1;
	}
	if (pcount % 2 == 0)
	{
		Vel.m128_f32[1] *= -1;
	}
	if (pcount % 2 == 1)
	{
		Vel.m128_f32[2] *= -1;
	}

	//コライダーの属性設定
	collider->SetColor(COLLISION_COLOR_PART);
}

void PartManager::BullisticInitialize(XMFLOAT3& pos,XMVECTOR& Velocity,XMFLOAT3& angle)
{

	position = pos;

	//angleにかける定数値
	const int reverveangle = 55;

	//弾のベクトルを代入
	Vel = Velocity;

	rotation.y = angle.y * reverveangle;
	rotation.x = angle.x * -reverveangle;
	
	//コライダーの属性設定
	collider->SetColor(COLLISION_COLOR_PART);
}

void PartManager::BullisticInitializeEnemy(XMFLOAT3& pos, XMVECTOR& Velocity, XMFLOAT3& angle, int& num)
{

	numbullistic = num;

	position = pos;

	//angleにかける定数値
	const int reverveangle = 58;

	//弾のベクトルを代入
	Vel = Velocity;

	rotation.y = angle.y * reverveangle;
	//rotation.x = angle.x * -55;

	//コライダーの属性設定
	collider->SetColor(COLLISION_COLOR_PART);
}

void PartManager::OnCollision(const CollisionInfo& info)
{

}

void PartManager::PartUpdate()
{
	
	//重力加算
	G -= 0.01f;
	if (G <= -0.1f)
	{
		G = -0.1f;
	}
	
	Vel.m128_f32[1] += G;
	
	//座標変更
	position.x += Vel.m128_f32[0];
	position.y += Vel.m128_f32[1];
	position.z += Vel.m128_f32[2];
	
	
	//地面貫通しないように
	if (position.y <= 0)
	{
		position.y = 0;
	}

	//出現時間カウント
	alivecount++;

	//1秒経過したら
	if (alivecount >= alivelimit)
	{
		dead = true;
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

}

void PartManager::BullisticUpdate()
{

	const int wait = 15;
	count++;

	if (count>=wait)
	{
		//positionを変える
		position.x += Vel.m128_f32[0];
		position.y += Vel.m128_f32[1];
		position.z += Vel.m128_f32[2];
		//座標更新
		UpdateWorld();
	}
	else
	{
		//スケールを伸ばす
		MoveScaleZ(Vel.m128_f32[2] * 0.01);
		//座標更新
		UpdateWorld();
	}
}

void PartManager::BullisticUpdateEnemy()
{
	const int wait = 45;
	count++;

	if (count >= wait)
	{
		//positionを変える
		position.x += Vel.m128_f32[0];
		position.y += Vel.m128_f32[1];
		position.z += Vel.m128_f32[2];
		//座標更新
		UpdateWorld();
	}
	else
	{
		//スケールを伸ばす
		MoveScaleZ(Vel.m128_f32[2] * 0.01);
		//座標更新
		UpdateWorld();
	}
}



