#include "Pbullet.h"

Pbullet::Pbullet() : FBXobj3d()
{
	
}



void Pbullet::create(const XMFLOAT3& Playerpos, const XMFLOAT3& velocity)
{
	////FBX関連
	////デバイスをセット
	//FBXobj3d::SetDevice(dxCommon->GetDevice());
	////カメラをセット
	//FBXobj3d::SetCamera(camera);
	////FBXパイプライン生成
	//FBXobj3d::CreateGraphicsPipeline();
	//modelballet = FbxLoader::GetInstance()->LoadModelFromFile("bullet");
	//ballet = new FBXobj3d;
	//ballet->Initialize();
	//ballet->SetPosition({ 0.0f,5.0f,0.0f });
	//ballet->SetModel(modelballet);

	position = Playerpos;
	Vel = velocity;
}

void Pbullet::bulupdate()
{

	position.z += Vel.z;


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

	position.z += Vel.z;
	
}

//void Pbullet::SetPos(XMFLOAT3 pos)
//{
//	Pbullet::position = pos;
//}
//
//void Pbullet::deleate(int flag)
//{
//	if (position.z=20)
//	{
//		flag = 0;
//	}
//}
