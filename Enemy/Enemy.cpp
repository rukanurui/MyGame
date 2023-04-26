#include "Enemy.h"
#include <time.h>

#include"../Collider/QueryCallback.h"
#include"../Collider/CollisionManager.h";



Enemy::Enemy() : FBXobj3d()
{
}


void Enemy::EnemyInitialize(bool shot)
{
	//属性の追加
	collider->SetColor(COLLISION_COLOR_ENEMY);
	Shot = shot;
	//モデル読み込み
	modelballet = FbxLoader::GetInstance()->LoadModelFromFile("bullet");
	model2 = FbxLoader::GetInstance()->LoadModelFromFile("testfbx");
	count = 0;

	for (std::unique_ptr<Enemybullet>& bullet : bullets)
	{
		bullet->SetPosition(position);
	}
}

void Enemy::EnemyUpdate(XMFLOAT3 playerpos)
{

	//敵の移動(自機追従)
	if (col==false)
	{
		if (Shot==false)
		{
			//プレイヤーの座標
			Playerpos.m128_f32[0] = playerpos.x;
			Playerpos.m128_f32[1] = playerpos.y;
			Playerpos.m128_f32[2] = playerpos.z;

			//敵の座標
			Vecpos.m128_f32[0] = position.x;
			Vecpos.m128_f32[1] = position.y;
			Vecpos.m128_f32[2] = position.z;

			//差分ベクトルの計算
			XMVECTOR Toenemy;
			Toenemy = Playerpos - Vecpos;
			Toenemy = XMVector3Normalize(Toenemy);

			//敵の速度
			Vel = Toenemy * 0.48f;


			XMMATRIX matScale, matRot, matTrans;
			// スケール、回転、平行移動行列の計算
			matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
			matRot = XMMatrixIdentity();
			matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));
			matRot *= XMMatrixRotationX(XMConvertToRadians(rotation.x));
			matRot *= XMMatrixRotationY(XMConvertToRadians(rotation.y));
			matTrans = XMMatrixTranslation(position.x += Vel.m128_f32[0], position.y += Vel.m128_f32[1], position.z += Vel.m128_f32[2]);

			// ワールド行列の合成
			matWorld = XMMatrixIdentity(); // 変形をリセット
			matWorld *= matScale; // ワールド行列にスケーリングを反映
			matWorld *= matRot; // ワールド行列に回転を反映
			matWorld *= matTrans; // ワールド行列に平行移動を反映

			//球コライダー取得
			SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collider);
			assert(sphereCollider);

			class EnemyQueryCallback :public QueryCallback
			{
			public:
				EnemyQueryCallback(Sphere* sphere) :sphere(sphere) {};

				//衝突時コールバック関数
				bool OnQueryHit(const QueryHit& info)
				{
					//ワールドの上方向
					const XMVECTOR up = { 0,1,0,0 };
					//排斥方向
					XMVECTOR rejectDir = XMVector3Normalize(info.reject);
					//上方向と左右方向の角度差のコサイン値
					float cos = XMVector3Dot(rejectDir, up).m128_f32[0];

					//押し出し処理
					sphere->center += info.reject;
					move += info.reject;

					return true;
				}

				//クエリ―に使用する球
				Sphere* sphere = nullptr;
				//排斥による移動量(累積)
				XMVECTOR move = {};
			};

			//クエリ―コールバックの関数オブジェクト
			EnemyQueryCallback callback(sphereCollider);

			//敵と敵の交差を検索
			CollisionManager::GetInstance()->CheckQuerySphere(*sphereCollider, &callback, COLLISION_COLOR_ENEMY);
			//交差による排斥分動かす
			position.x += callback.move.m128_f32[0];
			position.y += callback.move.m128_f32[1];
			position.z += callback.move.m128_f32[2];

			//敵と壁の交差を検索
			CollisionManager::GetInstance()->CheckQueryBox(*sphereCollider, &callback, COLLISION_COLOR_LANDSHAPE);
			//交差による排斥分動かす
			position.x += callback.move.m128_f32[0]*0.05f;
			position.y += callback.move.m128_f32[1]*0.05f;
			position.z += callback.move.m128_f32[2]*0.05f;

		}
		
		if (Shot)
		{
			Attack(playerpos);
		}
	}

	//死亡していたら
	if (col==true)
	{
		//20個までparticle生成
		if (partcount <= partnum)
		{
			std::unique_ptr<PartEnemy>newPart = std::make_unique<PartEnemy>();
			newPart->Initialize();
			newPart->SetScale({ 0.01f,0.01f,0.01f });
			newPart->SetModel(model2);
			newPart->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
			newPart->PartInitialize(position);

			//弾の登録
			particle.push_back(std::move(newPart));

			partcount++;
		}

		//particleの更新
		if (parttimer<=150)
		{
			for (std::unique_ptr<PartEnemy>& part : particle)
			{
				part->PartUpdate();
				part->Update();
			}
			parttimer++;
		}
		else
		{
			death = true;
		}
		

	}
	
	Update();

	//当たり判定更新
	if (collider)
	{
		collider->Update();
	}


}


void Enemy::Attack(XMFLOAT3 playerpos)
{
	count++;

	//弾の削除
	bullets.remove_if([](std::unique_ptr<Enemybullet>& bullet) {
		return bullet->Gethit();
		});

	//if (count != 0)
	//{
	//	//プレイヤーの座標
	//	Playerpos.m128_f32[0] = playerpos.x;
	//	Playerpos.m128_f32[1] = playerpos.y;
	//	Playerpos.m128_f32[2] = playerpos.z;

	//	//敵の座標
	//	Vecpos.m128_f32[0] = position.x;
	//	Vecpos.m128_f32[1] = position.y;
	//	Vecpos.m128_f32[2] = position.z;

	//	//差分ベクトルの計算
	//	XMVECTOR Toenemy;
	//	Toenemy = Playerpos - Vecpos;
	//	Toenemy = XMVector3Normalize(Toenemy);

	//	Vel = Toenemy * 0.12f;

	//	XMMATRIX matScale, matRot, matTrans;
	//	// スケール、回転、平行移動行列の計算
	//	matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	//	matRot = XMMatrixIdentity();
	//	matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));
	//	matRot *= XMMatrixRotationX(XMConvertToRadians(rotation.x));
	//	matRot *= XMMatrixRotationY(XMConvertToRadians(rotation.y));
	//	matTrans = XMMatrixTranslation(position.x += Vel.m128_f32[0], position.y += Vel.m128_f32[1], position.z += Vel.m128_f32[2]);

	//	// ワールド行列の合成
	//	matWorld = XMMatrixIdentity(); // 変形をリセット
	//	matWorld *= matScale; // ワールド行列にスケーリングを反映
	//	matWorld *= matRot; // ワールド行列に回転を反映
	//	matWorld *= matTrans; // ワールド行列に平行移動を反映

	//	//球コライダー取得
	//	SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collider);
	//	assert(sphereCollider);

	//	class EnemyQueryCallback :public QueryCallback
	//	{
	//	public:
	//		EnemyQueryCallback(Sphere* sphere) :sphere(sphere) {};

	//		//衝突時コールバック関数
	//		bool OnQueryHit(const QueryHit& info)
	//		{
	//			//ワールドの上方向
	//			const XMVECTOR up = { 0,1,0,0 };
	//			//排斥方向
	//			XMVECTOR rejectDir = XMVector3Normalize(info.reject);
	//			//上方向と左右方向の角度差のコサイン値
	//			float cos = XMVector3Dot(rejectDir, up).m128_f32[0];

	//			//押し出し処理
	//			sphere->center += info.reject;
	//			move += info.reject;

	//			return true;
	//		}
	//		//クエリ―に使用する球
	//		Sphere* sphere = nullptr;
	//		//排斥による移動量(累積)
	//		XMVECTOR move = {};
	//	};

	//	//クエリ―コールバックの関数オブジェクト
	//	EnemyQueryCallback callback(sphereCollider);

	//	//敵と敵の交差を検索
	//	CollisionManager::GetInstance()->CheckQuerySphere(*sphereCollider, &callback, COLLISION_COLOR_ENEMY);
	//	//交差による排斥分動かす
	//	position.x += callback.move.m128_f32[0];
	//	position.y += callback.move.m128_f32[1];
	//	position.z += callback.move.m128_f32[2];
	//}

	if (count >= 180)
	{
		count = 0;

		//弾の速度
		const float bulspeed = 0.5f;
		XMVECTOR Velocity{ 0,0,bulspeed };

		//Velocity={ target.x - position.x, target.y - position.y, target.z - position.z };
		Velocity = { playerpos.x - position.x, playerpos.y - position.y, playerpos.z - position.z };

		Velocity = XMVector3Normalize(Velocity) * bulspeed;

		//弾の生成と初期化
		std::unique_ptr<Enemybullet>newBullet = std::make_unique<Enemybullet>();
		newBullet->Initialize();
		newBullet->SetScale({ 0.01f,0.01f,0.01f });
		newBullet->SetModel(modelballet);
		newBullet->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
		newBullet->BulInitialize();
		newBullet->create(position, Velocity);
		
		//弾の登録
		bullets.push_back(std::move(newBullet));
	}

	//弾の更新
	for (std::unique_ptr<Enemybullet>& bullet:bullets)
	{
		bullet->bulupdate();
		bullet->Update();
	}
}


void Enemy::OnCollision(const CollisionInfo& info)
{

	//弾と当たった時
	if (info.collider->color == 4)
	{

	if (scale.x >= 0.01f)
	{
		scale.x = 0.0f; scale.y = 0.0f; scale.z = 0.0f;
	}

	col = true;

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

	if (info.collider->color == 6)
	{
		
	}

	//当たり判定更新
	if (collider)
	{
		collider->Update();
	}


}



void Enemy::colReset()
{
	col = false;
}


void Enemy::move()
{

}

void Enemy::BulUpdate()
{
	for (std::unique_ptr<Enemybullet>& bullet : bullets)
	{
		bullet->Update();
	}

}


void Enemy::BulDraw(ID3D12GraphicsCommandList* cmdList)
{

	for (std::unique_ptr<Enemybullet>& bullet : bullets)
	{
		bullet->Draw(cmdList);
	}
}

void Enemy::PartUpdate()
{
	for (std::unique_ptr<PartEnemy>& part : particle)
	{
		part->Update();
	}
}

void Enemy::PartDraw(ID3D12GraphicsCommandList* cmdList)
{
	for (std::unique_ptr<PartEnemy>& part : particle)
	{
		part->Draw(cmdList);
	}
}

void Enemy::LastUpdate()
{
	//死亡していたら
	if (col == true)
	{
		//20個までparticle生成
		if (partcount <= partnum)
		{
			std::unique_ptr<PartEnemy>newPart = std::make_unique<PartEnemy>();
			newPart->Initialize();
			newPart->SetScale({ 0.01f,0.01f,0.01f });
			newPart->SetModel(model2);
			newPart->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
			newPart->PartInitialize(position);

			//弾の登録
			particle.push_back(std::move(newPart));

			partcount++;
		}

		//particleの更新
		if (parttimer <= 150)
		{
			for (std::unique_ptr<PartEnemy>& part : particle)
			{
				part->PartUpdate();
				part->Update();
			}
			parttimer++;
		}
		else
		{
			death = true;
		}


	}
}

void Enemy::setcol(bool Col)
{
	col = Col;
}

