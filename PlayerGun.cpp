#include "PlayerGun.h"


PlayerGun::PlayerGun() : FBXobj3d()
{

}



void PlayerGun::create(const XMFLOAT3& Playerpos, const XMVECTOR& velocity)
{
	position = Playerpos;
	//position.y -= 1.5f;
	position.y = 4.0f;
	Vel = velocity;
}

void PlayerGun::staycreate(const XMFLOAT3& Playerpos)
{
	position = Playerpos;
	//position.y -= 1.5f;
	position.y = 4.0f;
}

void PlayerGun::GunInitialize()
{
	//属性の追加
	collider->SetColor(COLLISION_COLOR_PBULET);
}

void PlayerGun::gunupdate(const XMFLOAT3& Playerpos,const XMFLOAT3& Rotation)
{

	position = Playerpos;
	rotation = Rotation;

	HRESULT result;
	UpdateWorld();

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

void PlayerGun::throwgunUpdate()
{
	position.x += Vel.m128_f32[0];
	position.y += Vel.m128_f32[1];
	position.z += Vel.m128_f32[2];
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

void PlayerGun::OnCollision(const CollisionInfo& info)
{

	if (info.collider->color != 2)
	{

		dead = true;


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

}