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

bool Enemy::EnemyInitialize()
{
	//コライダーの追加
	float radius = 1.5f;
	//半径分だけ足元から浮いた座標を球の中心にする
	SetCollider(new SphereCollider(XMVECTOR({ 0,radius,0,0 }), radius));
	return true;
}

void Enemy::EnemyUpdate()
{

	if (col == 1)
	{

		G -= 0.01f;

		if (G <= -0.1f)
		{
			G = -0.1f;
		}

		DivVel.m128_f32[1] += G;

		position.x += DivVel.m128_f32[0];
		position.y += DivVel.m128_f32[1];
		position.z += DivVel.m128_f32[2];

		/*if (position.x >= 10 || position.x <= 0)
		{
			DivVel.m128_f32[0] = 0.0f;
		}

		if (position.z >= 40 || position.z <= 15)
		{
			DivVel.m128_f32[2] = 0.0f;
		}*/

		if (position.y<=0)
		{
			position.y = 0;
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


	

	////当たり判定更新
	//if (collider)
	//{
	//	collider->Update();
	//}
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


	if (scale.x >= 1)
	{
		scale.x = 0.5; scale.y = 0.5; scale.z = 0.5;
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

	////当たり判定更新
	//if (collider)
	//{
	//	collider->Update();
	//}
}


void Enemy::EnemyDeleate()
{
	position.x = 100.0f;
}

void Enemy::colReset()
{
	col = 0;
}
;


